struct CSGraphNode {
	bool selected;
	bool selout;
	int x, y, w, h;

	long offset;
	long branch;
	bool brasec;
	long branch2;
	bool brasec2;

	char label[4][32];
	char outlabel[16][32];

	LinkedList<CSGraphNode*> in;
	LinkedList<CSGraphNode*> out;

	NodeType * type;

	int ox, oy;

	long args[16];
	int argline;
	int argnum;

	int bank;
	int bbank;

	bool visited;

	CSGraphNode(int ix, int iy, int iw, int ih, int t = 0, long o = 0) {
		branch = 0;
		brasec = false;
		branch2 = 0;
		brasec2 = false;

		x = ix;
		y = iy;
		w = iw;
		h = ih;
		selected = false;
		selout = false;
		visited = false;
		offset = o;

		setLabel("", "", "", "");

		bank = 0;
		bbank = 0;

		type = &nodeTypesCS[t];

		setLabel(type->label[0], type->label[1], type->label[2], type->label[3]);
		setOutLabel(type->outlabel[0], type->outlabel[1], type->outlabel[2], type->outlabel[3]);
		for (int i = 4; i < 16; i++) {
			sprintf(outlabel[i], "%d", i);
		}

		argline = type->argline;
		argnum = type->argnum;

		for (int i = 0; i<16; i++) {
			switch (type->argtypes[i]) {
				case ARG_BRANCH:
				case ARG_SBRANCH:
				case ARG_IGNBRA:

					if (!strcmp(type->name, "Branch If Greater")) {
						args[i] = 0x6E;
					} else if (!strcmp(type->name, "Branch If Less")) {
						args[i] = 0x6D;
					} else
					args[i] = 0x67;
					break;

				default:
					args[i] = 0;
					break;
			}
		}
	}

	void setLabel(char * l, char * l2, char * l3, char * l4) {
		sprintf(label[0], l);
		sprintf(label[1], l2);
		sprintf(label[2], l3);
		sprintf(label[3], l4);
	}

	void setOutLabel(char * l, char * l2, char * l3, char * l4) {
		sprintf(outlabel[0], l);
		sprintf(outlabel[1], l2);
		sprintf(outlabel[2], l3);
		sprintf(outlabel[3], l4);
	}

	void paint(HDC target) {

		POINT points[6];
		int i;

		SetTextAlign(target, TA_CENTER);

		switch (type->shape) {
			case 0:
				RoundRect(target, x, y, x + w, y + h, w / 4, h / 4);


				for (i = 0; i<4; i++) {
					if (i == argline) {
						if (argnum<0) {
							sprintf(label[i], "%u %u", args[-1 * argnum - 1], args[-1 * argnum]);
						} else {
							if (type->argtypes[argnum] == ARG_MESSAGE) {
								sprintf(label[i], "%d", args[argnum]);
							} else {
								sprintf(label[i], "%u", args[argnum] & 0xFF);
							}
						}
					}
					TextOut(target, x + w / 2, y + 8 + i * 16, label[i], strlen(label[i]));
				}
				break;
			case 1:
				points[0].x = x + w / 2;
				points[0].y = y;

				points[1].x = x;
				points[1].y = y + h / 2;

				points[2].x = x + w / 2;
				points[2].y = y + h;

				points[3].x = x + w;
				points[3].y = y + h / 2;

				Polygon(target, points, 4);

				if (strlen(label[1])) {
					for (i = 0; i<3; i++) {
						if (i == argline) {
							sprintf(label[i], "%d", args[argnum]);
						}
						TextOut(target, x + w / 2, y + 22 + i * 16, label[i], strlen(label[i]));
					}
				} else {
					TextOut(target, x + w / 2, y + h / 2 - 8, label[0], strlen(label[0]));
				}
				break;
			case 2:
				points[0].x = x;
				points[0].y = y;

				points[1].x = x;
				points[1].y = y + h;

				points[2].x = x + w;
				points[2].y = y + h / 2;

				Polygon(target, points, 3);

				TextOut(target, x + w / 3, y + h / 2 - 8, label[0], strlen(label[0]));
				break;
			case 3:
				Ellipse(target, x, y, x + w, y + h);

				TextOut(target, x + w / 2, y + h / 2 - 8, label[0], strlen(label[0]));
				break;
			case 4:
				points[0].x = x + w / 2;
				points[0].y = y;

				points[1].x = x + w;
				points[1].y = y + h * 2 / 5;

				points[2].x = x + 4 * w / 5;
				points[2].y = y + h;

				points[3].x = x + 1 * w / 5;
				points[3].y = y + h;

				points[4].x = x;
				points[4].y = y + h * 2 / 5;

				Polygon(target, points, 5);

				for (i = 0; i<4; i++) {
					if (i == argline) {
						if (argnum<0) {
							sprintf(label[i], "%u %u", args[-1 * argnum - 1], args[-1 * argnum]);
						} else {
							sprintf(label[i], "%u", args[argnum] & 0xFF);
						}
					}
					TextOut(target, x + w / 2, y + 12 + i * 16, label[i], strlen(label[i]));
				}
				break;
		}

		LLNode<CSGraphNode*>*cur = out.head;
		i = 0;
		while (cur) {
			MoveToEx(target, x + w, y + h / 2, 0);
			LineTo(target, x + w + w / 8, y + h / 2);

			LineTo(target, cur->data->x - w / 8, cur->data->y + cur->data->h / 2);
			LineTo(target, cur->data->x, cur->data->y + cur->data->h / 2);



			if (strlen(outlabel[i]) == 1) {
				SetTextColor(target, RGB(0, 0, 0));
				TextOut(target, cur->data->x - 4 + 1, cur->data->y + cur->data->h / 2 - 8 + 1, outlabel[i], strlen(outlabel[i]));
				SetTextColor(target, RGB(255, 255, 255));
				TextOut(target, cur->data->x - 4, cur->data->y + cur->data->h / 2 - 8, outlabel[i], strlen(outlabel[i]));
			}

			if (abs(cur->data->x - x) <= 32 + 2 * w && cur->data->x > x) {

				LineTo(target, cur->data->x - w / 8, cur->data->y + cur->data->h / 2);
				LineTo(target, cur->data->x, cur->data->y + cur->data->h / 2);

				if (strlen(outlabel[i]) != 1) {
					SetTextColor(target, RGB(0, 0, 0));
					TextOut(target, (x + w + cur->data->x) / 2 + 1, (y + h / 2 + cur->data->y + cur->data->h / 2) / 2 - 16 + 1, outlabel[i], strlen(outlabel[i]));

					SetTextColor(target, RGB(255, 255, 255));
					TextOut(target, (x + w + cur->data->x) / 2, (y + h / 2 + cur->data->y + cur->data->h / 2) / 2 - 16, outlabel[i], strlen(outlabel[i]));
				}
			} else {

				if (cur->data->y <= y) {

					LineTo(target, x + w + w / 8, cur->data->y - h / 8);
					LineTo(target, cur->data->x + w / 2, cur->data->y - h / 8);
					LineTo(target, cur->data->x + w / 2, cur->data->y);

					if (strlen(outlabel[i]) != 1) {
						SetTextColor(target, RGB(0, 0, 0));
						TextOut(target, (x + w + cur->data->x) / 2 + 1, cur->data->y - h / 8 - 8 + 1, outlabel[i], strlen(outlabel[i]));

						SetTextColor(target, RGB(255, 255, 255));
						TextOut(target, (x + w + cur->data->x) / 2, cur->data->y - h / 8 - 8, outlabel[i], strlen(outlabel[i]));
					}

				} else {

					LineTo(target, x + w + w / 8, cur->data->y + h + h / 8);
					LineTo(target, cur->data->x + w / 2, cur->data->y + h + h / 8);
					LineTo(target, cur->data->x + w / 2, cur->data->y + h);

					if (strlen(outlabel[i]) != 1) {
						SetTextColor(target, RGB(0, 0, 0));
						TextOut(target, (x + w + cur->data->x) / 2 + 1, cur->data->y + h + h / 8 - 8 + 1, outlabel[i], strlen(outlabel[i]));

						SetTextColor(target, RGB(255, 255, 255));
						TextOut(target, (x + w + cur->data->x) / 2, cur->data->y + h + h / 8 - 8, outlabel[i], strlen(outlabel[i]));
					}
				}
			}

			cur = cur->next;
			i = i + 1;
		}

		SetTextColor(target, RGB(0, 0, 0));

		SetTextAlign(target, TA_LEFT);

		if (selected&&type->shape != 3) {
			Rectangle(target, x + w - 10, y + h / 2 - 5, x + w, y + h / 2 + 5);
			if (selout) {
				MoveToEx(target, x + w, y + h / 2, 0);
				LineTo(target, x + w + w / 8, y + h / 2);

				LineTo(target, x + ox - w / 8, y + oy);
				LineTo(target, x + ox, y + oy);


				int no;

				if (out.size<type->numout) {
					no = out.size;
				} else {
					no = type->numout - 1;
					if (no > 0 && (GetKeyState(VK_SHIFT) & 0x80))no--;
				}

				SetTextColor(target, RGB(0, 0, 0));
				TextOut(target, (2 * x + w + ox) / 2 + 1, (2 * y + h / 2 + oy) / 2 - 16 + 1, outlabel[no], strlen(outlabel[no]));
				SetTextColor(target, RGB(255, 255, 255));
				TextOut(target, (2 * x + w + ox) / 2, (2 * y + h / 2 + oy) / 2 - 16, outlabel[no], strlen(outlabel[no]));
				SetTextColor(target, RGB(0, 0, 0));
			}
		}
	}

	void click(int px, int py) {
		ox = px;
		oy = py;
		if (selected&&type->shape != 3 && px >= w - 10 && px <= w&&py >= h / 2 - 5 && py <= h / 2 + 5)selout = true;
		else selout = false;
		selected = true;
	}

	void move(int px, int py, int gridsize) {
		if (selout) {
			ox = px - x + w / 2;
			oy = py - y + h / 2;
			return;
		}
		px -= px%gridsize;
		py -= py%gridsize;
		x = px;
		y = py;
		if (x<0)x = 0;
		if (y<0)y = 0;
		//if(x+w>GRAPHSIZE)x=GRAPHSIZE-w;
		//if(y+h>GRAPHSIZE)y=GRAPHSIZE-h;
	}
};

