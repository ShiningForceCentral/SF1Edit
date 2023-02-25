int BExitHeader[256];
int BExitScript[64][768];
long BExitScriptO[64][768];

long BExitHeaderOffset;

int BExitPatterns[512][512];
int NumBExitPatterns = 0;
int BExitLength[512];
char BExitNames[512][32];
int BExitPatternNodes[512];

int BExitArgs[16];
//int NumArgs = 0;
int BExitBranches[128];
//int NumBranches = 0;

BExitGraph * BExitGraphs[64];

void addBExitPattern(int len, int node, char * name, ...) {
	va_list vl;
	va_start(vl, name);
	int c = 0;
	for (int i = 0;i<len;i++) {
		BExitPatterns[NumBExitPatterns][c] = va_arg(vl, int);
		c++;
	}
	sprintf(BExitNames[NumBExitPatterns], name);
	BExitLength[NumBExitPatterns] = len;
	BExitPatternNodes[NumBExitPatterns] = node;
	NumBExitPatterns++;
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
bool checkBExitEnd(FILE * fp);

bool checkBExitPattern(FILE * fp, int pat) {
	int r = 0;
	int r2 = 0;
	int t, k;
	int v;
	long o, o2;
	NumArgs = 0;
	int lastarg = 0;
	for (int i = 0;i<BExitLength[pat];i++) {
		fscanf(fp, "%c", &r);
		t = BExitPatterns[pat][i];
		if (t >= 0) {
			if (r != t)return false;
		} else {
			t *= -1;
			k = t % 4;
			if (!k)k = 4;
			k--;
			v = r;
			o = ftell(fp);
			for (int j = 0;j<k;j++) {
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
				switch (BExitArgs[NumArgs - 1]) {
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
				BExitArgs[NumArgs] = o + v - 1;
				NumArgs++;
				for (int j = 1; j < v / 2; j++) {
					int v2 = 0;
					for (int j2 = 0; j2<=k; j2++) {
						fscanf(fp, "%c", &r);
						v2 *= 256;
						v2 += r;
					}
					if (v2 < v)v = v2;
					BExitArgs[NumArgs] = o + v2 - 1;

					NumArgs++;
				}
			} else {
				BExitArgs[NumArgs] = v;
				NumArgs++;
			}

			if (t<5) {

			} else if (t<9) {
				i++;
				if (NumArgs&&lastarg>20 && lastarg<25) {
					if (v != BExitPatterns[pat][i])return false;
				} else {
					if (o - 1 + v != BExitPatterns[pat][i])return false;
					BExitArgs[NumArgs - 1] = o - 1 + v;
				}
			} else if (t<13) {
				i++;
				if (v != BExitPatterns[pat][i])return false;
			} else if (t<17) {
				o2 = ftell(fp);
				fseek(fp, v, SEEK_SET);
				fscanf(fp, "%c", &r);
				fscanf(fp, "%c", &r2);

				if (r == 0x60) {
					fseek(fp, o + v, SEEK_SET);
					if (!checkBExitEnd(fp))return false;
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
				BExitArgs[NumArgs] = o + v - k;
				//negative branch
				if(!strcmp(BExitNames[pat],"Branch"))
					fseek(fp, o + v - k, SEEK_SET);
			}
			lastarg = t;
		}
	}
	return true;
}

bool checkBExitEnd(FILE * fp) {
	unsigned long o = ftell(fp);
	for (int i = 0;i<NumBExitPatterns;i++) {
		if (!strcmp("End", BExitNames[i])) {
			fseek(fp, o, SEEK_SET);
			if (checkBExitPattern(fp, i))return true;
		}
	}
	return false;
}

bool checkBExitEnd(int p) {
	if (p == NumBExitPatterns - 2 || p == NumBExitPatterns - 3)
		return false;
	if (!strcmp("End", BExitNames[p]))return true;
	//if (BExitPatterns[p][0] == 0x60)return true;
	//if (BExitPatterns[p][0] == -21 && BExitArgs[0] == 0x60)return true;
	if (BExitPatterns[p][BExitLength[p] - 2] == 0x4E && BExitPatterns[p][BExitLength[p] - 1] == 0xD5)
		return true;
	if (BExitPatterns[p][BExitLength[p] - 1] == -30)return true;
	return false;
}

int checkAllBExitPatterns(FILE * fp) {
	unsigned long o = ftell(fp);
	for (int i = 0;i<NumBExitPatterns;i++) {
		//if(!strcmp(BENames[i],"Clear Message Box?"))
		//	i=i;
		fseek(fp, o, SEEK_SET);
		if (checkBExitPattern(fp, i))
			return i;
	}
	return -1;
}

int getBExitPatternArgs(int pat) {
	int c = 0;
	for (int i = 0;i<BExitLength[pat];i++) {
		if (BExitPatterns[pat][i]<0) {
			c++;
		}
	}
	return c;
}

void addBExitNodeType(char * n, int s, char * l = "", char * l2 = "", char * l3 = "", char * l4 = "", int al = -1, int an = 0) {
	nodeTypesBExit[NumBExitNodeTypes].set(n, s, l, l2, l3, l4, al, an);
	NumBExitNodeTypes++;
}

void setBExitNodeOuts(int n, char * l = "", char * l2 = "", char * l3 = "", char * l4 = "") {
	nodeTypesBExit[NumBExitNodeTypes - 1].setout(n, l, l2, l3, l4);
}

void setBExitNodeArgs(int n, int t = -1, char * l = "", int t2 = -1, char * l2 = "", int t3 = -1, char * l3 = "", int t4 = -1, char * l4 = "") {
	nodeTypesBExit[NumBExitNodeTypes - 1].setargs(n, t, l, t2, l2, t3, l3, t4, l4);
}

void setBExitNodeHelp(char * h) {
	nodeTypesBExit[NumBExitNodeTypes - 1].setHelpText(h);
}


void initBExit() {
	int i;
	for (i = 0;i<NUM_BEXIT;i++) {
		BExitGraphs[i] = new BExitGraph(240, 50, 640, 480);
	}

	addBExitNodeType("Start", 2, "Start");
	addBExitNodeType("End", 3, "End");

	addBExitNodeType("Check Event", 1, "Check", "Event", "", "", 2, 0);
	setBExitNodeOuts(2, "Clear", "Set");
	setBExitNodeArgs(4, ARG_BYTE, "Event Number", ARG_IGNORE, "", ARG_SBRANCH, "Branch On", ARG_IGNORE, "");
	setBExitNodeHelp("Branches the script depending on whether a specific event has been set.\n\nEvent Number: Event to check");

	addBExitNodeType("Set Event", 0, "Set", "Event", "", "", 3, 0);
	setBExitNodeArgs(2, ARG_BYTE, "Event Number", ARG_IGNORE, "");
	setBExitNodeHelp("Sets an event number as completed.\n\nEvent Number: Event to set");

	addBExitNodeType("Clear Event", 0, "Clear", "Event", "", "", 3, 0);
	setBExitNodeArgs(2, ARG_BYTE, "Event Number", ARG_IGNORE, "");
	setBExitNodeHelp("Clears the completed state of an event number.\n\nEvent Number: Event to clear");

	addBExitNodeType("Clear Last Event", 0, "Clear", "Last", "Event", "");
	setBExitNodeArgs(1, ARG_IGNORE, "");
	setBExitNodeHelp("Clears the completed state of the just checked event.");

	addBExitNodeType("Branch On Region", 1, "Branch", "Region", "", "");
	setBExitNodeArgs(1, ARG_JUMP, "");
	setBExitNodeOuts(4, "0", "1", "2", "3");

	addBExitNodeType("Branch On Exit", 1, "Branch", "Exit", "", "");
	setBExitNodeArgs(1, ARG_JUMP, "");
	setBExitNodeOuts(4, "0", "1", "2", "3");

	addBExitNodeType("Test Exit", 1, "Test", "Exit", "", "");
	setBExitNodeOuts(2, "Set", "Clear");
	setBExitNodeArgs(2, ARG_SBRANCH, "Branch On", ARG_IGNORE, "");

	addBExitNodeType("Check Exit", 1, "Check", "Exit", "", "", 2, 0);
	setBExitNodeOuts(2, "Equal", "Not Equal");
	setBExitNodeArgs(3, ARG_BYTE, "Map Number", ARG_BRANCH, "Branch On", ARG_IGNORE, "");

	addBExitNodeType("Set Region", 0, "Set", "Region", "", "", 2, 0);
	setBExitNodeArgs(1, ARG_BYTE, "Region");

	addBExitNodeType("Set Exit", 0, "Set", "Exit", "", "", 2, 0);
	setBExitNodeArgs(1, ARG_BYTE, "Exit");

	addBExitNodeType("Set Version", 0, "Set", "Version", "", "", 2, 0);
	setBExitNodeArgs(1, ARG_BYTE, "Version");

	addBExitNodeType("Set Egress Location", 0, "Set", "Egress", "Location", "", 3, 0);//9C4C
	setBExitNodeArgs(1, ARG_BYTE, "?");

	addBExitNodeType("Set Victory Exit", 0, "Set", "Victory", "Exit", "", 3, 0);//9C4D
	setBExitNodeArgs(1, ARG_BYTE, "?");

	addBExitNodeType("Set Cutscene", 0, "Set", "Cutscene", "", "", 3, 0);//9C86
	setBExitNodeArgs(1, ARG_BYTE, "Cutscene");
	setBExitNodeHelp("Used for automatic map movement like cart and boats and a few special cutscenes.");

	addBExitNodeType("Check Map", 1, "Check", "Map", "", "", 2, 0);
	setBExitNodeOuts(2, "Equal", "Not Equal");
	setBExitNodeArgs(3, ARG_BYTE, "Map Number", ARG_BRANCH, "Branch On", ARG_IGNORE, "");

	for (i = 0;i<NUM_BEXIT;i++) {
		BExitGraphs[i]->addNode(16, 16);

		BExitGraphs[i]->buildList();
	}

	addBExitPattern(9, 2, "Check Event", 0x70, -1,  0x4E, 0xB9, -12, 0x3072, -21, 0, -2);
	addBExitPattern(8, 2, "Check Event",  0x70, -1, 0x4E, 0xB9, -12, 0x3072, -21, -1);
	addBExitPattern(6, 3, "Set Event",    0x70, -1, 0x4E, 0xB9, -12, 0x3054);
	addBExitPattern(6, 4, "Clear Event",  0x70, -1, 0x4E, 0xB9, -12, 0x3062);
	addBExitPattern(4, 5, "Clear Last Event",		0x4E, 0xB9, -12, 0x3062);
	//next two must not be pushed down
	addBExitPattern(17, 6, "Branch On Region", 0x42, 0x40, 0x10, 0x38, 0x9C, 0x01, 0xD0, 0x40, 0x30, 0x3B, 0x00, 0x06, 0x4E, 0xFB, 0x00, 0x02, -30);
	addBExitPattern(21, 7, "Branch On Exit", 0x42, 0x40, 0x10, 0x38, 0x9C, 0x02, 0x42, 0x38, 0x9C, 0x02, 0xD0, 0x40, 0x30, 0x3B, 0x00, 0x06, 0x4E, 0xFB, 0x00, 0x02, -30);

	addBExitPattern(9, 2, "Check Event", 0x70, -1, 0x61, 0, -6, 0x3072, -21, 0, -2);
	addBExitPattern(8, 2, "Check Event", 0x70, -1, 0x61, 0, -6, 0x3072, -21, -1);
	addBExitPattern(6, 3, "Set Event", 0x70, -1, 0x61, 0, -6, 0x3054);
	addBExitPattern(6, 4, "Clear Event", 0x70, -1, 0x61, 0, -6, 0x3062);
	addBExitPattern(4, 5, "Clear Last Event", 0x61, 0, -6, 0x3062);

	addBExitPattern(7, 8, "Test Exit", 0x4A, 0x38, 0x9C, 0x02, -21, 0, -2);
	addBExitPattern(6, 8, "Test Exit", 0x4A, 0x38, 0x9C, 0x02, -21, -1);
	addBExitPattern(9, 9, "Check Exit", 0x0C, 0x38, 0, -1, 0x9C, 0x02, -21, 0, -2);
	addBExitPattern(8, 9, "Check Exit", 0x0C, 0x38, 0, -1, 0x9C, 0x02, -21, -1);
	addBExitPattern(6, 10, "Set Region", 0x11, 0xFC, 0, -1, 0x9C, 0x01);
	addBExitPattern(4, 10, "Set Region", 0x42, 0x38, 0x9C, 0x01);//clear
	addBExitPattern(6, 11, "Set Exit", 0x11, 0xFC, 0, -1, 0x9C, 0x02);
	addBExitPattern(4, 11, "Set Exit", 0x42, 0x38, 0x9C, 0x02);//clear
	addBExitPattern(6, 12, "Set Version", 0x11, 0xFC, 0, -1, 0x9C, 0x03);
	addBExitPattern(4, 12, "Set Version", 0x42, 0x38, 0x9C, 0x03);//clear
	addBExitPattern(6, 13, "Set Unknown 1", 0x11, 0xFC, 0, -1, 0x9C, 0x4C);
	addBExitPattern(4, 13, "Set Unknown 1", 0x42, 0x38, 0x9C, 0x4C);//clear
	addBExitPattern(6, 14, "Set Unknown 2", 0x11, 0xFC, 0, -1, 0x9C, 0x4D);
	addBExitPattern(4, 14, "Set Unknown 2", 0x42, 0x38, 0x9C, 0x4D);//clear
	addBExitPattern(6, 15, "Set Unknown 3", 0x11, 0xFC, 0, -1, 0x9C, 0x86);
	addBExitPattern(4, 15, "Set Unknown 3", 0x42, 0x38, 0x9C, 0x86);//clear
	addBExitPattern(9, 16, "Check Map", 0x0C, 0x38, 0, -1, 0xF8, 0x07, -21, 0, -2);
	addBExitPattern(8, 16, "Check Map", 0x0C, 0x38, 0, -1, 0xF8, 0x07, -21, -1);

	AdvancedNodes(BExit, 17)

	addBExitPattern(2, 1, "End", 0x60, -13);
	addBExitPattern(3, 1, "End", 0x60, 0, -14);

	addBExitPattern(3, 1, "Branch", 0x60, 0, -26);//just follow, shouldn't create a node
	addBExitPattern(2, 1, "Branch", 0x60, -25);

	addBExitPattern(3, 1, "Branch", 0x60, 0, -18);//just follow, shouldn't create a node
	addBExitPattern(2, 1, "Branch", 0x60, -17);

	addBExitPattern(2, 1, "End", 0x4E, 0x75);
}

int findBExitLabel(int script, int label) {
	int i = 0;
	int p;
	while (BExitScript[script][i] != -1) {
		p = BExitScript[script][i];
		switch (p) {
		case -2:
			i++;
			if (BExitScript[script][i] == label)return i + 1;
			break;
		case -3:
			i++;
			break;
		case -4:
			break;
		case 5:
		case 6:
			while (BExitScript[script][i + 1] > 0)i++;
			break;
		default:
			i += getBExitPatternArgs(p);
			break;
		}
		i++;
	}
	return -1;
}

void labelBExitBranches(BExitGraphNode * node, int arg, bool set = false, bool yn = false) {
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


void BuildBExitGraphLine(int script, int start, int sx, int sy, BExitGraphNode * prev = 0, int b = 0, int bb = 0) {

	BExitGraphNode * last = prev;

	int i = start;

	int x = sx;
	int y = sy;

	int p, a;

	int bank = b;
	int bbank = bb;

	int oldline = maxline;

	while (BExitScript[script][i] != -1) {
		p = BExitScript[script][i];
		/*if(p==NumBExitPatterns-2||p==NumBExitPatterns-3){
		i+=2;
		continue;
		}*/
		switch (p) {
		case -2:
			i++;
			break;
		case -3:
			i++;
			if (last && last != BExitGraphs[script]->nodes.head->data) {
				if (last->branch && last->branch != BExitScript[script][i]) {
					last->branch2 = BExitScript[script][i];
					last->brasec2 = false;
				} else {
					last->branch = BExitScript[script][i];
					last->brasec = false;
				}
			} else {
				if (BExitGraphs[script]->nodes.head->data->branch && BExitGraphs[script]->nodes.head->data->branch != BExitScript[script][i]) {
					BExitGraphs[script]->nodes.head->data->branch2 = BExitScript[script][i];
					BExitGraphs[script]->nodes.head->data->brasec2 = true;
				} else {
					BExitGraphs[script]->nodes.head->data->branch = BExitScript[script][i];
					BExitGraphs[script]->nodes.head->data->brasec = true;
				}
			}
			break;
		case -4:
			return;
		default:

			if (BExitScriptO[script][i] == 0x3F5A) {
				i = i;
			}

			LLNode<BExitGraphNode*>* cur = BExitGraphs[script]->nodes.head;

			BExitGraphNode * temp;
			if (last && last != BExitGraphs[script]->nodes.head->data) {
				temp = last;
			} else {
				temp = BExitGraphs[script]->nodes.head->data;
			}

			if(nodeTypesBExit[BExitPatternNodes[p]].numout<3 && temp->type->numout<3)
			while (cur) {
				if (cur->data->offset == BExitScriptO[script][i] && strcmp(cur->data->type->name, "End")) {
					BExitGraphs[script]->connect(temp, cur->data);
					return;
				}
				cur = cur->next;
			}


			BExitGraphs[script]->addNode(x, y, BExitPatternNodes[p], BExitScriptO[script][i]);
			switch (p) {
			case 5:
				a = (BExitScript[script][i + 1] - BExitScriptO[script][i] - 16) / 2;
				break;
			case 6:
				a = (BExitScript[script][i + 1] - BExitScriptO[script][i] - 20) / 2;
				break;
			default:
				a = getBExitPatternArgs(p);
				break;
			}

			for (int j = 0;j<a;j++) {
				BExitGraphs[script]->nodes.head->data->args[j] = BExitScript[script][i + j + 1];
			}
			if (a&&BExitPatternNodes[p] == 17 && BExitGraphs[script]->nodes.head->data->args[0] == 0x180A6)
				BExitGraphs[script]->nodes.head->data->args[0] = 0x53;
			
			if(p!=5 && p!=6)i += a;

			if (last) {
				BExitGraphs[script]->connect(last, BExitGraphs[script]->nodes.head->data);
				last = 0;
			} else {
				BExitGraphs[script]->connect(BExitGraphs[script]->nodes.head->next->data, BExitGraphs[script]->nodes.head->data);
			}

			if (BExitGraphs[script]->nodes.head->data->type->numout>1) {
				
				last = BExitGraphs[script]->nodes.head->data;

				if (p == 5 || p == 6) {
					for (int k = 0; k < a; k++) {
						if(k)maxline++;
						i++;
						//labelBExitBranches(last, a - 2, strcmp(BExitNames[p], "Check Event") == 0, strcmp(BExitNames[p], "Branch on Yes/No") == 0);

						BuildBExitGraphLine(script, findBExitLabel(script, BExitScript[script][i]), x + 112, maxline * 96 + 16, last, bank, bbank);

						switch (p) {
						case 5:
							if ((BExitScript[script][i] - BExitScriptO[script][i - k - 1] - 16) / 2 < a)
								a = (BExitScript[script][i] - BExitScriptO[script][i - k - 1] - 16) / 2;
							break;
						case 6:
							if ((BExitScript[script][i] - BExitScriptO[script][i - k - 1] - 20) / 2 < a)
								a = (BExitScript[script][i] - BExitScriptO[script][i - k - 1] - 20) / 2;
							break;
						}


					}
				} else {
					
					

					



					int lb = findBExitLabel(script, BExitScript[script][i]);

					labelBExitBranches(last, a - 2, strcmp(BExitNames[p], "Check Event") == 0, strcmp(BExitNames[p], "Branch on Yes/No") == 0);


					LLNode<BExitGraphNode*>* cur = BExitGraphs[script]->nodes.head;
					if (BExitGraphs[script]->nodes.head->data->type->numout<3)
					while (cur) {
						if (cur->data->offset == BExitScript[script][i] && strcmp(cur->data->type->name, "End")) {
							BExitGraphs[script]->connect(BExitGraphs[script]->nodes.head->data, cur->data);
							lb = -1;
							break;
						}
						cur = cur->next;
					}

					if (lb != -1) {
						int topline = maxline;

						maxline++;


						BuildBExitGraphLine(script, lb, x + 112, maxline * 96 + 16, BExitGraphs[script]->nodes.head->data, bank, bbank);

						LLNode<BExitGraphNode*>* curs = BExitGraphs[script]->nodes.head;
						while (curs) {
							if (curs->data->y > topline * 96 + 16) {
								curs->data->y -= 96 * (topline - oldline);
								curs->data->y -= 10000;
							}
							curs = curs->next;
						}
						curs = BExitGraphs[script]->nodes.head;
						while (curs) {
							if (curs->data->y > oldline * 96 + 16) {
								curs->data->y += 96 * (maxline - topline);
							}
							curs = curs->next;
						}
						curs = BExitGraphs[script]->nodes.head;
						while (curs) {
							if (curs->data->y < -100) {
								curs->data->y += 10000;
							}
							curs = curs->next;
						}
					}
				}


				

			}

			if (checkBExitEnd(p)) {
				if (p == 5 || p == 6)return;
				int v;
				if (last)v = last->type->shape;
				else v = BExitGraphs[script]->nodes.head->data->type->shape;
				if (v != 3) {
					BExitGraphs[script]->addNode(x + 112, y, 1);
					if (last) {
						BExitGraphs[script]->connect(last, BExitGraphs[script]->nodes.head->data);
						last = 0;
					} else {
						BExitGraphs[script]->connect(BExitGraphs[script]->nodes.head->next->data, BExitGraphs[script]->nodes.head->data);
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

void BuildBExitGraph(int script) {
	maxline = 0;

	BExitGraphs[script]->clear();

	BuildBExitGraphLine(script, 0, 128, 16);

	LLNode<BExitGraphNode*>* cur = BExitGraphs[script]->nodes.head;
	while (cur) {
		if (cur->data->type->shape == 3) {
			cur = cur->next;
			continue;
		}
		if (cur->data->out.size < cur->data->type->numout && cur->data->type->numargs && cur->data->type->numout<3) {

			LLNode<BExitGraphNode*>* cur2 = BExitGraphs[script]->nodes.head;
			while (cur2) {
				if (cur->data->branch < 0)cur->data->branch *= -1;
				if (cur2->data->offset == cur->data->branch && cur->data->branch) {
					BExitGraphs[script]->connect(cur->data, cur2->data);

					if (cur->data->brasec && cur->data->out.size > 1) {
						BExitGraphNode * temp = cur->data->out.head->data;

						cur->data->out.head->data = cur->data->out.tail->data;
						cur->data->out.tail->data = temp;
					}
				}

				if (cur->data->branch2 < 0)cur->data->branch2 *= -1;
				if (cur2->data->offset == cur->data->branch2 && cur->data->branch2) {
					BExitGraphs[script]->connect(cur->data, cur2->data);

					if (cur->data->brasec2 && cur->data->out.size > 1) {
						BExitGraphNode * temp = cur->data->out.head->data;

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


void LoadBExit(char * path, bool single = false) {
	//return;
	unsigned char r, c;
	long o, mo, to;
	int i, j;

	mo = 0;

	for (int i = 0; i < 64; i++) {
		for (int j = 0; j < 768; j++) {
			BExitScript[i][j] = 0;
			BExitScriptO[i][j] = 0;
		}
	}

	FILE * fp = fopen(path, "rb");


	fseek(fp, 0x3F0E, SEEK_SET);
	fscanf(fp, "%c", &r);
	if (r != 0x4E) {
		BExitHeaderOffset = 0x3F26;
	} else {
		BExitHeaderOffset = 0x1DDA18;// relocate ***
	}

	fseek(fp, BExitHeaderOffset, SEEK_SET);
	for (i = 0; i<NUM_BEXIT; i++) {
		fscanf(fp, "%c", &r);
		fscanf(fp, "%c", &c);
		if (single&&i != subselect[mode][0])continue;
		BExitHeader[i] = 256 * r;
		BExitHeader[i] += c;
	}

	o = ftell(fp);

	for (i = 0; i<NUM_BEXIT; i++) {
		if (single&&i != subselect[mode][0])continue;
		o = BExitHeaderOffset + BExitHeader[i];

		int p = 0;
		int c = 0;
		int k;

		for (k = 0;k<128;k++) {
			BExitBranches[k] = 0;
		}

		BExitBranches[0] = o;
		NumBranches = 1;

		while (NumBranches) {
			p = 0;
			o = 0;
			for (k = 0;k<128;k++) {
				if (BExitBranches[k] && (BExitBranches[k]<o || !o))o = BExitBranches[k];
			}

			fseek(fp, o, SEEK_SET);

			while (!checkBExitEnd(p)) {

				o = ftell(fp);
				if (o>mo)mo = o;

				for (k = 0; k<128; k++) {
					if (BExitBranches[k] == o) {
						BExitScript[i][c] = -2;
						c++;
						BExitScript[i][c] = o;
						c++;
						BExitBranches[k] = 0;

						for (int k2 = k; k2 < 127; k2++) {
							BExitBranches[k2] = BExitBranches[k2 + 1];
						}
						BExitBranches[127] = 0;

						NumBranches--;
						for (; k<128; k++) {
							if (BExitBranches[k] == o) {
								BExitBranches[k] = 0;

								for (int k2 = k; k2 < 127; k2++) {
									BExitBranches[k2] = BExitBranches[k2 + 1];
								}
								BExitBranches[127] = 0;

								NumBranches--;
							}
						}
					}
				}

				if (o == 0x3F5A) {
					o = o;
				}

				bool f = false;
				for (k = 0; k < c; k++) {
					if (BExitScriptO[i][k] == o && strcmp(BExitNames[BExitScript[i][k]],"End")) {
						f = true;
						BExitScript[i][c] = -3;
						BExitScriptO[i][c] = 0;
						c++;
						BExitScript[i][c] = o;
						BExitScriptO[i][c] = 0;
						c++;
						BExitScript[i][c] = -4;
						BExitScriptO[i][c] = 0;
						c++;
						break;
					}
				}
				if (f)break;

				



				p = checkAllBExitPatterns(fp);



				if (p == -1) {
					fseek(fp, o, SEEK_SET);
					char out[512];
					unsigned char r;
					sprintf(out, "Error parsing Battle Exit scripts.\n\nPlease submit a screenshot of this message to the forums.\n\nOffset: 0x%X Data:\n\n", o);
					for (i = 0;i<32;i++) {
						fscanf(fp, "%c", &r);
						sprintf(out, "%s%.2hX", out, r);
					}
					MessageBox(NULL, out, "Error", MB_OK);
					fclose(fp);
					return;
				}

				if (!strcmp(BExitNames[p], "Branch")) {
					BExitScript[i][c] = -3;
					BExitScriptO[i][c] = 0;
					c++;
					BExitScript[i][c] = BExitArgs[1];
					BExitScriptO[i][c] = 0;
					c++;
					continue;
				}

				BExitScript[i][c] = p;
				BExitScriptO[i][c] = o;
				c++;
				for (j = 0;j<NumArgs;j++) {
					BExitScript[i][c] = BExitArgs[j];
					c++;
				}

				j = 0;
				for (k = 0;k<128;k++) {
					if (BExitBranches[k])j = k + 1;
				}

				switch (BExitPatterns[p][BExitLength[p] - 3]) {
				case -21:
					if (BExitPatterns[p][BExitLength[p] - 2] == 0) {
						to = BExitArgs[getBExitPatternArgs(p) - 1];
						if (to > o) {
							switch (to) {
								case 0x18074:
								case 0x1808A:
								case 0x180B4:

									break;
								default:
									BExitBranches[j] = to;//+ftell(fp)-2;
									NumBranches++;
									break;
							}
						} else
							to = to;
					}
					break;
				}
				switch (BExitPatterns[p][BExitLength[p] - 2]) {
				case -21:
					if (BExitPatterns[p][BExitLength[p] - 1] == -1) {
						to = BExitArgs[getBExitPatternArgs(p) - 1];
						if (to > o) {
							switch (to) {
								case 0x18074:
								case 0x1808A:
								case 0x180B4:

									break;
								default:
									BExitBranches[j] = to;//+ftell(fp)-2;
									NumBranches++;
									break;
							}
						} else
							to = to;
					}
					break;
				}

				for (int k = 0; k < BExitLength[p];k++){
					if(BExitPatterns[p][k]==-30) {

						int sarg = getBExitPatternArgs(p) - 1;

						for (int iarg = sarg; iarg < NumArgs; iarg++) {
							to = BExitArgs[iarg];

							for (k = 0; k < j; k++) {
								if (BExitBranches[j] == BExitBranches[k]) {
									to = 0;
									break;
								}
							}
							if (to > o) {
								if (to) {
									BExitBranches[j] = to;
									NumBranches++;
									j++;
								}
							} else
								to = to;
						}
						break;
					}
				}

				if (BExitBranches[j])
					for (k = 0;k<j;k++) {
						if (BExitBranches[j] == BExitBranches[k]) {
							BExitBranches[j] = 0;
							NumBranches--;
							k = j;
						}
					}
			}
		}
		BExitScript[i][c] = -1;
		BuildBExitGraph(i);
	}
	o = ftell(fp);

	mo = mo;
	fclose(fp);
}
