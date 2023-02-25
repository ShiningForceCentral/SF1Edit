int CSHeader[256];
int CSScript[64][768];
long CSScriptO[64][768];

long CSHeaderOffset;

int CSPatterns[512][512];
int NumCSPatterns = 0;
int CSLength[512];
char CSNames[512][32];
int CSPatternNodes[512];

int CSArgs[16];
//int NumArgs = 0;
int CSBranches[128];
//int NumBranches = 0;

CSGraph * CSGraphs[64];

void addCSPattern(int len, int node, char * name, ...) {
	va_list vl;
	va_start(vl, name);
	int c = 0;
	for (int i = 0; i<len; i++) {
		CSPatterns[NumCSPatterns][c] = va_arg(vl, int);
		c++;
	}
	sprintf(CSNames[NumCSPatterns], name);
	CSLength[NumCSPatterns] = len;
	CSPatternNodes[NumCSPatterns] = node;
	NumCSPatterns++;
	va_end(vl);
}

//positive values just match bytes
//negative values
//		1-4  = 1-4 bytes, anything
//		5-8  = 1-4 bytes, must match next value as a relative branch offset
//		9-12 = 1-4 bytes, must match next value as an absolute branch offset
//		13-16 = 1-4 bytes, relative offset must lead to a RTS
//		17-20 = 1-4 bytes, relative branch positive, seek to target
//		21	  = 1 byte, check for branch opcode
//		25-28 = 1-4 bytes, relative branch negative just save
//		29-32 = 1-4 bytes, jump table offsets
bool checkCSEnd(FILE * fp);

bool checkCSPattern(FILE * fp, int pat) {
	int r = 0;
	int r2 = 0;
	int t, k;
	int v;
	long o, o2;
	NumArgs = 0;
	int lastarg = 0;
	for (int i = 0; i<CSLength[pat]; i++) {
		fscanf(fp, "%c", &r);
		t = CSPatterns[pat][i];
		if (t >= 0) {
			if (r != t)return false;
		} else {
			t *= -1;
			k = t % 4;
			if (!k)k = 4;
			k--;
			v = r;
			o = ftell(fp);
			for (int j = 0; j<k; j++) {
				fscanf(fp, "%c", &r);
				v *= 256;
				v += r;
			}

			if (k == 0)
				if (v & 0x80)
					v = v | (-1 - 0xFF);

			if (k == 1)
				if (v & 0x8000)v = v | (-1 - 0xFFFF);

			if (NumArgs&&lastarg>20 && lastarg<25)
				switch (CSArgs[NumArgs - 1]) {
					case 0x60://always
					case 0x64://carry clear
					case 0x65://carry set
					case 0x66://not equal
					case 0x67://equal
					case 0x6D://less than
						v += o;
						if (t % 2 == 0)v -= 1;
						break;
				}

			if (t > 28 && t < 33) {
				CSArgs[NumArgs] = o + v - 1;
				NumArgs++;
				for (int j = 1; j < v / 2; j++) {
					int v2 = 0;
					for (int j2 = 0; j2 <= k; j2++) {
						fscanf(fp, "%c", &r);
						v2 *= 256;
						v2 += r;
					}
					if (v2 < v)v = v2;
					CSArgs[NumArgs] = o + v2 - 1;

					NumArgs++;
				}
			} else {
				CSArgs[NumArgs] = v;
				NumArgs++;
			}

			if (t<5) {

			} else if (t<9) {
				i++;
				if (NumArgs&&lastarg>20 && lastarg<25) {
					if (v != CSPatterns[pat][i])return false;
				} else {
					if (o - 1 + v != CSPatterns[pat][i])return false;
					CSArgs[NumArgs - 1] = o - 1 + v;
				}
			} else if (t<13) {
				i++;
				if (v != CSPatterns[pat][i])return false;
			} else if (t<17) {
				o2 = ftell(fp);
				fseek(fp, v, SEEK_SET);
				fscanf(fp, "%c", &r);
				fscanf(fp, "%c", &r2);

				if (r == 0x60) {
					fseek(fp, o + v, SEEK_SET);
					if (!checkCSEnd(fp))return false;
				} else {
					if (r != 0x4E || r2 != 0x75)return false;
				}
				fseek(fp, o2, SEEK_SET);
			} else if (t<21) {
				if (v<0)return false;
				fseek(fp, o + v - k, SEEK_SET);//**** break here and make sure not missing.. something
			} else if (t<25) {
				switch (r) {
					case 0x60://always
					case 0x64://carry clear
					case 0x65://carry set
					case 0x66://not equal
					case 0x67://equal
					case 0x6D://less than
						break;
					default:
						return false;
				}
			} else if (t<29) {
				if (v >= 0)return false;
				CSArgs[NumArgs] = o + v - k;
				//negative branch
				if (!strcmp(CSNames[pat], "Branch"))
					fseek(fp, o + v - k, SEEK_SET);
			}
			lastarg = t;
		}
	}
	return true;
}

bool checkCSEnd(FILE * fp) {
	unsigned long o = ftell(fp);
	for (int i = 0; i<NumCSPatterns; i++) {
		if (!strcmp("End", CSNames[i])) {
			fseek(fp, o, SEEK_SET);
			if (checkCSPattern(fp, i))return true;
		}
	}
	return false;
}

bool checkCSEnd(int p) {
	if (p == NumCSPatterns - 2 || p == NumCSPatterns - 3)
		return false;
	if (!strcmp("End", CSNames[p]))return true;
	//if (CSPatterns[p][0] == 0x60)return true;
	//if (CSPatterns[p][0] == -21 && CSArgs[0] == 0x60)return true;
	if (CSPatterns[p][CSLength[p] - 2] == 0x4E && CSPatterns[p][CSLength[p] - 1] == 0xD5)
		return true;
	if (CSPatterns[p][CSLength[p] - 1] == -30)return true;
	return false;
}

int checkAllCSPatterns(FILE * fp) {
	unsigned long o = ftell(fp);
	for (int i = 0; i<NumCSPatterns; i++) {
		//if(!strcmp(BENames[i],"Clear Message Box?"))
		//	i=i;
		fseek(fp, o, SEEK_SET);
		if (checkCSPattern(fp, i))
			return i;
	}
	return -1;
}

int getCSPatternArgs(int pat) {
	int c = 0;
	for (int i = 0; i<CSLength[pat]; i++) {
		if (CSPatterns[pat][i]<0) {
			c++;
		}
	}
	return c;
}

void addCSNodeType(char * n, int s, char * l = "", char * l2 = "", char * l3 = "", char * l4 = "", int al = -1, int an = 0) {
	nodeTypesCS[NumCSNodeTypes].set(n, s, l, l2, l3, l4, al, an);
	NumCSNodeTypes++;
}

void setCSNodeOuts(int n, char * l = "", char * l2 = "", char * l3 = "", char * l4 = "") {
	nodeTypesCS[NumCSNodeTypes - 1].setout(n, l, l2, l3, l4);
}

void setCSNodeArgs(int n, int t = -1, char * l = "", int t2 = -1, char * l2 = "", int t3 = -1, char * l3 = "", int t4 = -1, char * l4 = "") {
	nodeTypesCS[NumCSNodeTypes - 1].setargs(n, t, l, t2, l2, t3, l3, t4, l4);
}

void setCSNodeHelp(char * h) {
	nodeTypesCS[NumCSNodeTypes - 1].setHelpText(h);
}


void initCS() {
	int i;
	for (i = 0; i<NUM_CS; i++) {
		CSGraphs[i] = new CSGraph(240, 50, 640, 480);
	}

	addCSNodeType("Start", 2, "Start");
	addCSNodeType("End", 3, "End");

	addCSNodeType("Set Event", 0, "Set", "Event", "", "", 3, 0);
		setCSNodeArgs(1, ARG_BYTE, "Event Number");
		setCSNodeHelp("Sets an event number as completed.\n\nEvent Number: Event to set");

	addCSNodeType("Clear Event", 0, "Clear", "Event", "", "", 3, 0);
		setCSNodeArgs(1, ARG_BYTE, "Event Number");
		setCSNodeHelp("Clears the completed state of an event number.\n\nEvent Number: Event to clear");

	addCSNodeType("Show Message Window", 0, "Show", "Message", "Window", "");
		setCSNodeHelp("Opens the message window.");

		addCSNodeType("Reset Message Window", 0, "Reset", "Message", "Window", "");
		setCSNodeHelp("Reset the message window, loading its graphics and clearing text/position.");

	addCSNodeType("Display Message", 0, "Display", "Message", "", "", 3, 0);
		setCSNodeArgs(1, ARG_MESSAGE, "Message Number");
		setCSNodeHelp("Displays a message to the screen.\n\nMessage Number: Message number to display.");

	addCSNodeType("More Text Prompt", 0, "More", "Text");
		setCSNodeHelp("Pauses the message and displays the flashing arrow indicating more text to follow.");

	addCSNodeType("Wait Frames", 0, "Wait", "Frames", "", "", 3, 0);
		setCSNodeArgs(1, ARG_BYTE, "Frames");
		setCSNodeHelp("Runs the game for a while.\n\nFrames: Number of frames to advance.");

	addCSNodeType("Set Region", 0, "Set", "Region", "", "", 3, 0);
		setCSNodeArgs(1, ARG_BYTE, "Region");
		setCSNodeHelp("Changes the current region.\n\nRegion: Region to change to.");

	addCSNodeType("Set Map", 0, "Set", "Map", "", "", 3, 0);
		setCSNodeArgs(1, ARG_BYTE, "Map");
		setCSNodeHelp("Changes the current map.\n\Map: Map to change to.");

	addCSNodeType("Set Map Version", 0, "Set", "Map", "Version", "", 3, 0);
		setCSNodeArgs(1, ARG_BYTE, "Map Version");
		setCSNodeHelp("Changes the current map version.\n\Map Version: Map Version to change to.");

	addCSNodeType("Play Sound", 0, "Play", "Sound", "", "", 3, 0);
		setCSNodeArgs(1, ARG_WORD, "Sound Effect");
		setCSNodeHelp("Plays a sound effect.");

	addCSNodeType("Set Text Sound?", 0, "Set", "Text", "Sound", "", 3, 0);
		setCSNodeArgs(2, ARG_BYTE, "Sound Type", ARG_IGNORE, "");
		setCSNodeHelp("Sets the sound type to use when displaying a messages. Different characters and enemies use slightly different sounds when speaking.");

	addCSNodeType("Sound Unknown 1", 0, "Sound", "Unknown", "1", "");
		setCSNodeHelp("?");

	addCSNodeType("Sound Unknown 2", 0, "Sound", "Unknown", "2", "");
		setCSNodeHelp("?");

	addCSNodeType("Save Chapter Number?", 0, "Save", "Chapter", "Number", "");
		setCSNodeHelp("?");

	addCSNodeType("Set Event Flags", 0, "Set", "Event", "Flags", "", 3, 0);
		setCSNodeArgs(1, ARG_WORD, "Value");
		setCSNodeHelp("Sets several event and battle related flags.");
		
	addCSNodeType("Set ? Flags", 0, "Set", "?", "Flags", "", 3, 0);
		setCSNodeArgs(1, ARG_BYTE, "Value");
		setCSNodeHelp("Sets several ? flags.");

	for (i = 0; i<NUM_CS; i++) {
		CSGraphs[i]->addNode(16, 16);

		CSGraphs[i]->buildList();
	}

	addCSPattern(6, 2, "Set Event", 0x70, -1, 0x4E, 0xB9, -12, 0x3054);
	addCSPattern(6, 2, "Set Event", 0x70, -1, 0x61, 0, -6, 0x3054);
	addCSPattern(6, 3, "Clear Event", 0x70, -1, 0x4E, 0xB9, -12, 0x3062);
	addCSPattern(6, 3, "Clear Event", 0x70, -1, 0x61, 0, -6, 0x3062);
	addCSPattern(2, 4, "Show Message Window", 0x4E, 0x45);
	addCSPattern(4, 5, "Reset Message Window", 0x4E, 0xB9, -12, 0x304);
	addCSPattern(5, 6, "Display Message", 0x30, 0x3C, -2, 0x4E, 0x48);
	addCSPattern(2, 7, "More Text Prompt", 0x4E, 0x47);
	addCSPattern(8, 8, "Wait Frames", 0x70, -1, 0x4E, 0xB9, 0, 0, 0x02, 0x44);
	addCSPattern(6, 9, "Set Region", 0x11, 0xFC, 0, -1, 0x9C, 0x01);
	addCSPattern(4, 9, "Set Region", 0x42, 0x38, 0x9C, 0x01);
	addCSPattern(6, 10, "Set Map", 0x11, 0xFC, 0, -1, 0x9C, 0x02);
	addCSPattern(4, 10, "Set Map", 0x42, 0x38, 0x9C, 0x02);
	addCSPattern(6, 11, "Set Map Version", 0x11, 0xFC, 0, -1, 0x9C, 0x03);
	addCSPattern(3, 12, "Play Sound", 0x4E, 0x40, -2);
	addCSPattern(6, 13, "Set Text Sound?", 0x31, 0xFC, 0, -1, 0xC0, 0xBE);
	addCSPattern(6, 14, "Sound Unknown 1", 0x4E, 0xB9, 0, 0, 0x02, 0x28);
	addCSPattern(6, 15, "Sound Unknown 2", 0x4E, 0xB9, 0, 0, 0x02, 0x2C);
	addCSPattern(10,16, "Save Chapter Number?", 0x42, 0x80, 0x10, 0x38, 0x9C, 0, 0x21, 0xC0, 0xF9, 0);
	addCSPattern(5, 17, "Set Event Flags", 0x31, 0xFC, -2, 0x9C, 0x88);
	addCSPattern(6, 18, "Set ? Flags", 0x11, 0xFC, 0, -1, 0x9C, 0x86);

	AdvancedNodes(CS, 19)

	addCSPattern(2, 1, "End", 0x60, -13);
	addCSPattern(3, 1, "End", 0x60, 0, -14);

	addCSPattern(3, 1, "Branch", 0x60, 0, -26);//just follow, shouldn't create a node
	addCSPattern(2, 1, "Branch", 0x60, -25);

	addCSPattern(3, 1, "Branch", 0x60, 0, -18);//just follow, shouldn't create a node
	addCSPattern(2, 1, "Branch", 0x60, -17);

	addCSPattern(2, 1, "End", 0x4E, 0x75);
}

int findCSLabel(int script, int label) {
	int i = 0;
	int p;
	while (CSScript[script][i] != -1) {
		p = CSScript[script][i];
		switch (p) {
			case -2:
				i++;
				if (CSScript[script][i] == label)return i + 1;
				break;
			case -3:
				i++;
				break;
			case -4:
				break;
			default:
				i += getCSPatternArgs(p);
				break;
		}
		i++;
	}
	return -1;
}

void labelCSBranches(CSGraphNode * node, int arg, bool set = false, bool yn = false) {
	switch (node->args[arg]) {
		case 0x64://carry clear
			sprintf(node->outlabel[1], "Less");
			sprintf(node->outlabel[0], "Not Less");
			break;
		case 0x65://carry set
			sprintf(node->outlabel[1], "Not Less");
			sprintf(node->outlabel[0], "Less");
			break;
		case 0x66://not equal
			if (!set) {
				if (!yn) {
					sprintf(node->outlabel[1], "Equal");
					sprintf(node->outlabel[0], "Not Equal");
				} else {
					sprintf(node->outlabel[1], "No");
					sprintf(node->outlabel[0], "Yes");
				}
			} else {
				sprintf(node->outlabel[1], "Clear");
				sprintf(node->outlabel[0], "Set");
			}
			break;
		case 0x67://equal
			if (!set) {
				if (!yn) {
					sprintf(node->outlabel[1], "Not Equal");
					sprintf(node->outlabel[0], "Equal");
				} else {
					sprintf(node->outlabel[1], "Yes");
					sprintf(node->outlabel[0], "No");
				}
			} else {
				sprintf(node->outlabel[1], "Set");
				sprintf(node->outlabel[0], "Clear");
			}
			break;
	}
}


void BuildCSGraphLine(int script, int start, int sx, int sy, CSGraphNode * prev = 0, int b = 0, int bb = 0) {

	CSGraphNode * last = prev;

	int i = start;

	int x = sx;
	int y = sy;

	int p, a;

	int bank = b;
	int bbank = bb;

	int oldline = maxline;

	while (CSScript[script][i] != -1) {
		p = CSScript[script][i];
		/*if(p==NumCSPatterns-2||p==NumCSPatterns-3){
		i+=2;
		continue;
		}*/
		switch (p) {
			case -2:
				i++;
				break;
			case -3:
				i++;
				if (last && last != CSGraphs[script]->nodes.head->data) {
					if (last->branch && last->branch != CSScript[script][i]) {
						last->branch2 = CSScript[script][i];
						last->brasec2 = false;
					} else {
						last->branch = CSScript[script][i];
						last->brasec = false;
					}
				} else {
					if (CSGraphs[script]->nodes.head->data->branch && CSGraphs[script]->nodes.head->data->branch != CSScript[script][i]) {
						CSGraphs[script]->nodes.head->data->branch2 = CSScript[script][i];
						CSGraphs[script]->nodes.head->data->brasec2 = true;
					} else {
						CSGraphs[script]->nodes.head->data->branch = CSScript[script][i];
						CSGraphs[script]->nodes.head->data->brasec = true;
					}
				}
				break;
			case -4:
				return;
			default:
				LLNode<CSGraphNode*>* cur = CSGraphs[script]->nodes.head;

				CSGraphNode * temp;
				if (last && last != CSGraphs[script]->nodes.head->data) {
					temp = last;
				} else {
					temp = CSGraphs[script]->nodes.head->data;
				}

				if (CSGraphs[script]->nodes.head->data->type->numout<3 && nodeTypesCS[CSPatternNodes[p]].numout<3)
				while (cur) {
					if (cur->data->offset == CSScriptO[script][i] && strcmp(cur->data->type->name, "End")) {
						CSGraphs[script]->connect(temp, cur->data);
						return;
					}
					cur = cur->next;
				}


				CSGraphs[script]->addNode(x, y, CSPatternNodes[p], CSScriptO[script][i]);
				switch (p) {
					default:
						a = getCSPatternArgs(p);
						break;
				}

				for (int j = 0; j<a; j++) {
					CSGraphs[script]->nodes.head->data->args[j] = CSScript[script][i + j + 1];
				}


				i += a;

				if (last) {
					CSGraphs[script]->connect(last, CSGraphs[script]->nodes.head->data);
					last = 0;
				} else {
					CSGraphs[script]->connect(CSGraphs[script]->nodes.head->next->data, CSGraphs[script]->nodes.head->data);
				}

				if (CSGraphs[script]->nodes.head->data->type->numout>1) {

					last = CSGraphs[script]->nodes.head->data;


					labelCSBranches(last, a - 2, strcmp(CSNames[p], "Check Event") == 0, strcmp(CSNames[p], "Branch on Yes/No") == 0);


					int lb = findCSLabel(script, CSScript[script][i]);

					LLNode<CSGraphNode*>* cur = CSGraphs[script]->nodes.head;
					if (CSGraphs[script]->nodes.head->data->type->numout<3)
					while (cur) {
						if (cur->data->offset == CSScript[script][i] && strcmp(cur->data->type->name, "End")) {
							CSGraphs[script]->connect(CSGraphs[script]->nodes.head->data, cur->data);
							lb = -1;
							break;
						}
						cur = cur->next;
					}

					if (lb != -1) {
						int topline = maxline;

						maxline++;


						BuildCSGraphLine(script, lb, x + 112, maxline * 96 + 16, CSGraphs[script]->nodes.head->data, bank, bbank);

						LLNode<CSGraphNode*>* curs = CSGraphs[script]->nodes.head;
						while (curs) {
							if (curs->data->y > topline * 96 + 16) {
								curs->data->y -= 96 * (topline - oldline);
								curs->data->y -= 10000;
							}
							curs = curs->next;
						}
						curs = CSGraphs[script]->nodes.head;
						while (curs) {
							if (curs->data->y > oldline * 96 + 16) {
								curs->data->y += 96 * (maxline - topline);
							}
							curs = curs->next;
						}
						curs = CSGraphs[script]->nodes.head;
						while (curs) {
							if (curs->data->y < -100) {
								curs->data->y += 10000;
							}
							curs = curs->next;
						}
					}
				}

				if (checkCSEnd(p)) {
					if (p == 5 || p == 6)return;
					int v;
					if (last)v = last->type->shape;
					else v = CSGraphs[script]->nodes.head->data->type->shape;
					if (v != 3) {
						CSGraphs[script]->addNode(x + 112, y, 1);
						if (last) {
							CSGraphs[script]->connect(last, CSGraphs[script]->nodes.head->data);
							last = 0;
						} else {
							CSGraphs[script]->connect(CSGraphs[script]->nodes.head->next->data, CSGraphs[script]->nodes.head->data);
						}
					}
					return;
				}
				x += 112;
				break;
		}
		i++;
	}
}

void BuildCSGraph(int script) {
	maxline = 0;

	CSGraphs[script]->clear();

	BuildCSGraphLine(script, 0, 128, 16);

	LLNode<CSGraphNode*>* cur = CSGraphs[script]->nodes.head;
	while (cur) {
		if (cur->data->type->shape == 3) {
			cur = cur->next;
			continue;
		}
		if (cur->data->out.size < cur->data->type->numout && cur->data->type->numargs && cur->data->type->numout<3) {

			LLNode<CSGraphNode*>* cur2 = CSGraphs[script]->nodes.head;
			while (cur2) {
				if (cur->data->branch < 0)cur->data->branch *= -1;
				if (cur2->data->offset == cur->data->branch && cur->data->branch) {
					CSGraphs[script]->connect(cur->data, cur2->data);

					if (cur->data->brasec && cur->data->out.size > 1) {
						CSGraphNode * temp = cur->data->out.head->data;

						cur->data->out.head->data = cur->data->out.tail->data;
						cur->data->out.tail->data = temp;
					}
				}

				if (cur->data->branch2 < 0)cur->data->branch2 *= -1;
				if (cur2->data->offset == cur->data->branch2 && cur->data->branch2) {
					CSGraphs[script]->connect(cur->data, cur2->data);

					if (cur->data->brasec2 && cur->data->out.size > 1) {
						CSGraphNode * temp = cur->data->out.head->data;

						cur->data->out.head->data = cur->data->out.tail->data;
						cur->data->out.tail->data = temp;
					}
				}

				cur2 = cur2->next;
			}

		}
		cur = cur->next;
	}
}


void LoadCS(char * path, bool single = false) {
	//return;
	unsigned char r, c;
	long o, mo, to;
	int i, j;

	mo = 0;

	for (int i = 0; i < 64; i++) {
		for (int j = 0; j < 768; j++) {
			CSScript[i][j] = 0;
			CSScriptO[i][j] = 0;
		}
	}

	FILE * fp = fopen(path, "rb");


	fseek(fp, 0x3AFE, SEEK_SET);
	fscanf(fp, "%c", &r);
	if (r != 0x4E) {
		CSHeaderOffset = 0x3B06;
	} else {
		CSHeaderOffset = 0x1F0F0;// relocate ***
	}

	fseek(fp, CSHeaderOffset, SEEK_SET);
	for (i = 0; i<NUM_CS; i++) {
		fscanf(fp, "%c", &r);
		fscanf(fp, "%c", &c);
		if (single&&i != subselect[mode][0])continue;
		CSHeader[i] = 256 * r;
		CSHeader[i] += c;
	}

	o = ftell(fp);

	for (i = 0; i<NUM_CS; i++) {
		if (single&&i != subselect[mode][0])continue;
		o = CSHeaderOffset + CSHeader[i];

		int p = 0;
		int c = 0;
		int k;

		for (k = 0; k<128; k++) {
			CSBranches[k] = 0;
		}

		CSBranches[0] = o;
		NumBranches = 1;

		while (NumBranches) {
			p = 0;
			o = 0;
			for (k = 0; k<128; k++) {
				if (CSBranches[k] && (CSBranches[k]<o || !o))o = CSBranches[k];
			}

			fseek(fp, o, SEEK_SET);

			while (!checkCSEnd(p)) {

				o = ftell(fp);
				if (o>mo)mo = o;

				for (k = 0; k<128; k++) {
					if (CSBranches[k] == o) {
						CSScript[i][c] = -2;
						c++;
						CSScript[i][c] = o;
						c++;
						CSBranches[k] = 0;

						for (int k2 = k; k2 < 127; k2++) {
							CSBranches[k2] = CSBranches[k2 + 1];
						}
						CSBranches[127] = 0;

						NumBranches--;
						for (; k<128; k++) {
							if (CSBranches[k] == o) {
								CSBranches[k] = 0;

								for (int k2 = k; k2 < 127; k2++) {
									CSBranches[k2] = CSBranches[k2 + 1];
								}
								CSBranches[127] = 0;

								NumBranches--;
							}
						}
					}
				}

				bool f = false;
				for (k = 0; k < c; k++) {
					if (CSScriptO[i][k] == o) {
						f = true;
						CSScript[i][c] = -3;
						CSScriptO[i][c] = 0;
						c++;
						CSScript[i][c] = o;
						CSScriptO[i][c] = 0;
						c++;
						CSScript[i][c] = -4;
						CSScriptO[i][c] = 0;
						c++;
						break;
					}
				}
				if (f)break;

				

				if (o == 0x401E) {
					o = o;
				}

				p = checkAllCSPatterns(fp);



				if (p == -1) {
					fseek(fp, o, SEEK_SET);
					char out[512];
					unsigned char r;
					sprintf(out, "Error parsing Chapter Start scripts.\n\nPlease submit a screenshot of this message to the forums.\n\nOffset: 0x%X Data:\n\n", o);
					for (i = 0; i<32; i++) {
						fscanf(fp, "%c", &r);
						sprintf(out, "%s%.2hX", out, r);
					}
					MessageBox(NULL, out, "Error", MB_OK);
					fclose(fp);
					return;
				}

				if (!strcmp(CSNames[p], "Branch")) {
					CSScript[i][c] = -3;
					CSScriptO[i][c] = 0;
					c++;
					CSScript[i][c] = CSArgs[1];
					CSScriptO[i][c] = 0;
					c++;
					continue;
				}

				CSScript[i][c] = p;
				CSScriptO[i][c] = o;
				c++;
				for (j = 0; j<NumArgs; j++) {
					CSScript[i][c] = CSArgs[j];
					c++;
				}

				j = 0;
				for (k = 0; k<128; k++) {
					if (CSBranches[k])j = k + 1;
				}

				switch (CSPatterns[p][CSLength[p] - 3]) {
					case -21:
						if (CSPatterns[p][CSLength[p] - 2] == 0) {
							if (to > o) {
								to = CSArgs[getCSPatternArgs(p) - 1];
								switch (to) {
									case 0x18074:
									case 0x1808A:
									case 0x180B4:

										break;
									default:
										CSBranches[j] = to;//+ftell(fp)-2;
										NumBranches++;
										break;
								}
							} else
								to = to;
						}
						break;
				}
				switch (CSPatterns[p][CSLength[p] - 2]) {
					case -21:
						if (CSPatterns[p][CSLength[p] - 1] == -1) {
							to = CSArgs[getCSPatternArgs(p) - 1];
							if (to > o) {
								switch (to) {
									case 0x18074:
									case 0x1808A:
									case 0x180B4:

										break;
									default:
										CSBranches[j] = to;//+ftell(fp)-2;
										NumBranches++;
										break;
								}
							} else
								to = to;
						}
						break;
				}

				for (int k = 0; k < CSLength[p]; k++) {
					if (CSPatterns[p][k] == -30) {

						int sarg = getCSPatternArgs(p) - 1;

						for (int iarg = sarg; iarg < NumArgs; iarg++) {
							to = CSArgs[iarg];

							for (k = 0; k < j; k++) {
								if (CSBranches[j] == CSBranches[k]) {
									to = 0;
									break;
								}
							}
							if (to > o) {
								if (to) {
									CSBranches[j] = to;
									NumBranches++;
									j++;
								}
							} else
								to = to;
						}
						break;
					}
				}

				if (CSBranches[j])
					for (k = 0; k<j; k++) {
						if (CSBranches[j] == CSBranches[k]) {
							CSBranches[j] = 0;
							NumBranches--;
							k = j;
						}
					}
			}
		}
		CSScript[i][c] = -1;
		BuildCSGraph(i);
	}
	o = ftell(fp);

	mo = mo;
	fclose(fp);
}
