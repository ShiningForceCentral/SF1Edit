int WriteNode(FILE * fp, CSGraphNode * node, int script) {
	if (node->offset == 0x3F76) {
		node = node;
	}
	if (node->visited && node->type->shape != 3) {
		long o = ftell(fp) + 2;
		long d = node->offset - o;

		if (d < 0) {
			d = d;
		}

		fprintf(fp, "%c", 0x60);
		fprintf(fp, "%c", 0x0);
		fprintf(fp, "%c", (d & 0xFF00) >> 8);
		fprintf(fp, "%c", (d & 0xFF));


		//MessageBox(hwnd, "Infinite Loop Detected. Remove the loop and save again. (Note that closing without correcting may result in data loss.)","Error",MB_OK);
		//return -10000;
		return -10001;
	}
	node->visited = true;

	int type = node->type - nodeTypesCS;

	int pat = -1;
	int t, a, v, k, u, l;

	int ret = 0;

	if (type) {
		if (node->type->shape == 3)pat = NumCSPatterns - 1;
		else for (int i = 0; i<512; i++) {
			if (CSPatternNodes[i] == type) {
				pat = i;
				break;
			}
		}

		if (pat == -1)
			return 0;

		if (!strcmp(node->type->name, "Display Message From ID")) {
			if (node->args[0] == 0)pat++;
		}

		if (!strcmp(node->type->name, "Display Message")) {
			if (node->args[0] == -1)pat++;
		}

		a = 0;

		long o = ftell(fp);
		LLNode<CSGraphNode*>* cur2 = CSGraphs[script]->nodes.head;
		while (cur2) {

			if (cur2->data->branch == node->offset) {
				cur2->data->branch = -o;

			}
			if (cur2->data->branch2 == node->offset) {
				cur2->data->branch2 = -o;

			}

			cur2 = cur2->next;
		}

		node->offset = o;

		for (int i = 0; i<CSLength[pat]; i++) {
			t = CSPatterns[pat][i];
			if (t >= 0) {
				fprintf(fp, "%c", t);
			} else {
				ret = t;
				switch (t) {
					case -21:
						v = node->args[a];
						//ret = -21;
						break;
					case -6:
						i++;
						v = CSPatterns[pat][i];
						break;
					case -12:
						i++;
						v = CSPatterns[pat][i];
						if (node->args[a])v = node->args[a];
						break;
					case -30:
						return t;
					default:
						v = node->args[a];
						if (t == -12 && v == 0x59)
							t = t;
						break;
				}

				k = -1 * t;
				k = k % 4;
				if (!k)k = 4;

				u = 0x00FF << (8 * (k - 1));

				for (int j = 0; j<k; j++) {
					l = (v&u) >> (8 * (k - j - 1));
					fprintf(fp, "%c", l);
					u = u / 0x0100;
				}

				a++;
			}
		}
	}
	return ret;
}

bool WriteCSGraphLine(FILE * fp, int script, CSGraphNode * start = 0) {

	if (!start)CSGraphs[script]->clearVisited();

	int ia;
	int t;
	int a, p;
	long o, o2, o3;

	CSGraphNode * cur;
	if (start)cur = start;
	else cur = CSGraphs[script]->nodes.tail->data;

	while (cur) {

		t = WriteNode(fp, cur, script);

		if (t == -10000) {
			if (CSGraphs[script]->sel)CSGraphs[script]->sel->selected = false;
			cur->selected = true;
			cur->selout = false;
			CSGraphs[script]->sel = cur;
			CSGraphs[script]->vx = cur->x - CSGraphs[script]->w / 2;
			CSGraphs[script]->vy = cur->y - CSGraphs[script]->h / 2;
			return false;
		}

		if (t == -10001)return true;

		if (cur->out.size>1) {

			if (t == -30) {
				o = ftell(fp);

				t = cur->type - nodeTypesCS;

				if (t) {
					if (cur->type->shape == 3)p = NumCSPatterns - 1;
					else for (int i = 0; i < 512; i++) {
						if (CSPatternNodes[i] == t) {
							p = i;
							break;
						}
					}
				}

				a = cur->out.size;

				fseek(fp, 2 * a, SEEK_CUR);

				ia = 0;

				LLNode <CSGraphNode*> * curo = cur->out.head;
				while (curo) {

					o2 = ftell(fp);
					if (!WriteCSGraphLine(fp, script, curo->data))return false;
					o3 = ftell(fp);

					//write jump offset?
					fseek(fp, o + 2 * ia, SEEK_SET);
					fprintf(fp, "%c", ((o2 - o) & 0x00FF00) / 0x100);
					fprintf(fp, "%c", ((o2 - o) & 0x00FF));
					fseek(fp, o3, SEEK_SET);
					ia++;
					curo = curo->next;
				}
				return true;
			} else {
				if (t == -1) {
					fseek(fp, -1, SEEK_CUR);
					fprintf(fp, "%c", 0);
					o = ftell(fp);
				} else {
					o = ftell(fp) - 2;
				}

				if (!WriteCSGraphLine(fp, script, cur->out.tail->data))return false;
				o2 = ftell(fp);

				//write jump offset?
				fseek(fp, o, SEEK_SET);
				fprintf(fp, "%c", ((o2 - o) & 0x00FF00) / 0x100);
				fprintf(fp, "%c", ((o2 - o) & 0x00FF));
				fseek(fp, o2, SEEK_SET);
			}

		}

		if (cur->out.size) {
			cur = cur->out.head->data;
		} else cur = 0;
	}
	return true;
}

void SaveCS() {
	if (!strlen(file)) {
		int ret = IDYES;
		OPENFILENAME openFileName;
		char path[256];
		path[0] = '\0';
		memset(&openFileName, 0, sizeof(openFileName));
		openFileName.lStructSize = sizeof(openFileName);
		openFileName.hwndOwner = NULL;
		openFileName.hInstance = NULL;
		openFileName.lpstrFilter = "Genesis ROM(*.bin)\0*.bin\0";
		openFileName.lpstrCustomFilter = NULL;
		openFileName.nMaxCustFilter = 0;
		openFileName.nFilterIndex = 0;
		openFileName.lpstrFile = path;
		openFileName.nMaxFile = 256;
		openFileName.lpstrFileTitle = NULL;
		openFileName.nMaxFileTitle = 0;
		openFileName.lpstrInitialDir = ".";
		openFileName.lpstrTitle = NULL;
		openFileName.Flags = OFN_LONGNAMES | OFN_PATHMUSTEXIST;
		openFileName.nFileOffset = 0;
		openFileName.nFileExtension = 0;
		openFileName.lpstrDefExt = "bin";
		openFileName.lCustData = NULL;
		openFileName.lpfnHook = NULL;
		openFileName.lpTemplateName = NULL;

		if (GetOpenFileName(&openFileName) != 0) {
			sprintf(file, path);
		}
	}

	int i, j;

	if (strlen(file)) {


		FILE * fp = fopen(file, "rb+");

		if (0x1D8000>romsize) {
			MessageBox(NULL, "Rom is too small, expand rom to save Chapter Start changes.", "Error", MB_OK);
			fclose(fp);
			return;
		}

		//header code changes? ** Disabled until ready
		fseek(fp, 0x3AFE, SEEK_SET);
		fprintf(fp, "%c", 0x4E);
		fprintf(fp, "%c", 0xF9);
		fprintf(fp, "%c", 0x00);
		fprintf(fp, "%c", 0x01);
		fprintf(fp, "%c", 0xF0);
		fprintf(fp, "%c", 0xE0);

		fseek(fp, 0x1F0E0, SEEK_SET);
		fprintf(fp, "%c", 0x30);
		fprintf(fp, "%c", 0x3B);
		fprintf(fp, "%c", 0x00);
		fprintf(fp, "%c", 0x0E);
		fprintf(fp, "%c", 0x4E);
		fprintf(fp, "%c", 0xFB);
		fprintf(fp, "%c", 0x00);
		fprintf(fp, "%c", 0x0A);

		CSHeaderOffset = 0x1F0F0;

		long o = CSHeaderOffset;
		long o2;

		//script code changes?

		o2 = 0x1F100;

		for (i = 0; i<NUM_CS; i++) {
			CSGraphs[i]->fillEnds();

			fseek(fp, o, SEEK_SET);
			CSHeader[i] = o2 - CSHeaderOffset;
			fprintf(fp, "%c", (CSHeader[i] & 0xFF00) / 0x100);
			fprintf(fp, "%c", CSHeader[i] & 0x00FF);
			o += 2;
			fseek(fp, o2, SEEK_SET);
			//write CS script

			if (!WriteCSGraphLine(fp, i)) {
				fclose(fp);
				return;
			}

			o2 = ftell(fp);
		}

		fclose(fp);
		MessageBox(NULL, "Chapter Starts Saved", "Note", MB_OK);
	}
}
