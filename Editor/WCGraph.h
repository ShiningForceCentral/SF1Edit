#include "WCGraphNode.h"

#define NUM_WC_COLORS	0
Triple<String, COLORREF, COLORREF> WCColors[] = {
	Triple<String, COLORREF, COLORREF>("Set Event" ,RGB(0,0,192),RGB(128,128,255)),
	Triple<String, COLORREF, COLORREF>("Clear Event" ,RGB(0,0,192),RGB(128,128,255)),
	Triple<String, COLORREF, COLORREF>("Check Event" ,RGB(0,0,192),RGB(128,128,255))
};

struct WCGraph {
	LinkedList<WCGraphNode*> nodes;
	WCGraphNode * sel;
	int selplace;
	bool scroll;
	bool drag;
	bool dragsel;
	LinkedList<WCGraphNode*> selgroup;

	LinkedList<int> choices;

	int x, y, w, h;

	int vx, vy;

	int lx, ly;

	int gridsize;

	int cpos;
	int graphzoom;

	WCGraph(int ix, int iy, int iw, int ih) {
		x = ix;
		y = iy;
		w = iw;
		h = ih;
		vx = 0;
		vy = 0;
		lx = 0;
		ly = 0;

		gridsize = 16;
		sel = 0;
		selplace = -1;
		cpos = 0;
		scroll = false;
		drag = false;
		dragsel = false;
		graphzoom = 1;
	}

	void clear() {
		nodes.clean();
		sel = 0;
		addNode(16, 16);
	}

	void copy() {

		char out[65536] = "";
		char temp[512];

		if (!selgroup.size) {
			sprintf(temp, "EMPTY");
			toClipboard(temp);
			return;
		}

		LLNode<WCGraphNode*>* cur = selgroup.head;
		LLNode<WCGraphNode*>* cur2;
		LLNode<WCGraphNode*>* cur3;

		sprintf(out, "WCNodes - %d\r\n", selgroup.size);

		int sx = selgroup.head->data->x;
		int sy = selgroup.head->data->y;

		int type;
		int i;

		while (cur) {
			type = cur->data->type - nodeTypesWC;

			sprintf(temp, "NODE %d,%d,%d\r\n", type, cur->data->x - sx, cur->data->y - sy);
			strcat(out, temp);

			for (i = 0; i < cur->data->type->numargs; i++) {
				sprintf(temp, "ARG %ul\r\n", cur->data->args[i]);
				strcat(out, temp);
			}

			cur2 = cur->data->out.head;
			while (cur2) {
				i = 0;

				cur3 = selgroup.head;
				while (cur3) {
					if (cur2->data == cur3->data) {
						sprintf(temp, "CONN %d\r\n", i);
						strcat(out, temp);
					}
					i++;
					cur3 = cur3->next;
				}

				cur2 = cur2->next;
			}

			cur = cur->next;
		}


		toClipboard(out);
	}

	void paste() {
		char out[65536] = "";
		char temp[512];


		fromClipboard(out, 65536);

		strncpy(temp, out, 32);
		temp[7] = 0;
		if (strcmp(temp, "WCNodes")) {
			MessageBox(hwnd, "Incorrect format", "Error", MB_OK);
			return;
		}

		int t, ot, j;
		char * line;

		WCGraphNode * add;

		sscanf(out, "WCNodes - %d", &t);

		line = strtok(out, "\n");
		if (!line) {
			MessageBox(hwnd, "Incorrect format", "Error", MB_OK);
			return;
		}

		sel = 0;
		selgroup.clean();

		int x, y, sx, sy;

		line = strtok(NULL, "\n");

		for (int q = 0; q < t; q++) {


			if (!line) {
				MessageBox(hwnd, "Incorrect format", "Error", MB_OK);
				return;
			}

			sscanf(line, "NODE %d,%d,%d", &ot, &x, &y);
			if (!q) {
				sx = vx + gridsize;
				sy = vy + gridsize;
				x = sx;
				y = sy;
			} else {
				x += sx;
				y += sy;
			}

			add = new WCGraphNode(x, y, 80, 80, ot);
			nodes.add(add);
			selgroup.append(add);
			if (!q)sel = add;

			line = strtok(NULL, "\n");
			j = 0;
			while (line && line[0] == 'A') {
				sscanf(line, "ARG %ul\r\n", &add->args[j++]);
				line = strtok(NULL, "\n");
			}

			j = 0;
			while (line && line[0] == 'C') {
				//sscanf(line, "ARG %ul\r\n", &add->args[j++]);
				line = strtok(NULL, "\n");
			}
		}

		fromClipboard(out);
		line = strtok(out, "\n");
		line = strtok(NULL, "\n");

		for (int q = 0; q < t; q++) {

			line = strtok(NULL, "\n");

			while (line && line[0] == 'A') {
				line = strtok(NULL, "\n");
			}

			while (line && line[0] == 'C') {
				sscanf(line, "CONN %d\r\n", &j);

				connect(selgroup[q]->data, selgroup[j]->data);

				line = strtok(NULL, "\n");
			}
		}



		InvalidateRect(hwnd, NULL, 0);



	}

	void buildList() {
		choices.clean();
		for (int i = 0; i<NumWCNodeTypes; i++) {
			if (nodeTypesWC[i].shape == select[mode])choices.append(i);
		}
	}

	char * branchName(int type, bool yn = false) {
		switch (type) {
			case 0x6C:
				return "Greater or Equal";
			case 0x6D:
				return "Less Than";

			case 0x64://carry clear
				return "Not Less Than";
			case 0x65://carry set
				return "Less Than";
				break;
			case 0x66://not equal
				if (yn)return "Yes";
				return "Not Equal";
				break;
			case 0x67://equal
				if (yn)return "No";
				return "Equal";
		}
	}

	char * sbranchName(int type) {
		switch (type) {
			case 0x66://not equal
				return "Set";
				break;
			case 0x67://equal
				return "Clear";
		}
	}

	WCGraphNode * findMessage(int mess, WCGraphNode * start = 0) {
		WCGraphNode * ret = 0;
		WCGraphNode * cur = start;
		if (!cur)cur = nodes.tail->data;

		if (searchmet)
			if (!strcmp(cur->type->name, "Display Message")) {
				if (cur->args[0] + cur->bank == mess)return cur;
			}

		if (cur == sel)searchmet = true;

		for (int i = 0; i<cur->out.size; i++) {
			ret = findMessage(mess, cur->out[i]->data);
			if (ret)return ret;
		}
		return ret;
	}

	WCGraphNode * findEvent(int event, WCGraphNode * start = 0) {
		WCGraphNode * ret = 0;
		WCGraphNode * cur = start;
		if (!cur)cur = nodes.tail->data;

		if (searchmet)
			if (!strcmp(cur->type->name, "Set Event") || !strcmp(cur->type->name, "Check Event") || !strcmp(cur->type->name, "Clear Event")) {
				if (cur->args[0] == event)return cur;
			}

		if (cur == sel)searchmet = true;

		for (int i = 0; i<cur->out.size; i++) {
			ret = findEvent(event, cur->out[i]->data);
			if (ret)return ret;
		}
		return ret;
	}

	WCGraphNode * findRegion(int region, WCGraphNode * start = 0) {
		WCGraphNode * ret = 0;
		WCGraphNode * cur = start;
		if (!cur)cur = nodes.tail->data;

		if (!strcmp(cur->type->name, "Branch On Region")) {
			if (region<cur->out.size)return cur->out[region]->data;
		}

		for (int i = 0; i<cur->out.size; i++) {
			ret = findRegion(region, cur->out[i]->data);
			if (ret)return ret;
		}
		if (start)return start;
		return nodes.tail->data;
	}

	WCGraphNode * findExit(int exit, WCGraphNode * start = 0, bool first = false) {
		WCGraphNode * ret = 0;
		WCGraphNode * cur = start;
		if (!cur)cur = nodes.tail->data;

		if (!strcmp(cur->type->name, "Branch On Exit")) {
			if (exit<cur->out.size)return cur->out[exit]->data;
		}

		for (int i = 0; i<cur->out.size; i++) {
			ret = findExit(exit, cur->out[i]->data);
			if (ret)return ret;
		}
		if (first)return start;
		return 0;
	}

	void paint(HDC target) {
		char out[1024];

		w = bwidth + dwidth - x - 24;
		h = bheight + dheight - y - 64;

		PatBlt(gdc, 0, 0, w*graphzoom, w*graphzoom, PATCOPY);

		HPEN temp = (HPEN)SelectObject(gdc, grid);
		HBRUSH tempb;

		SelectObject(bmpdc, minus);
		BitBlt(memdc, 55, 8, 20, 20, bmpdc, 0, 0, SRCCOPY);

		if (sel&&sel->offset) {
			sprintf(out, "Node Offset: %X", sel->offset);
			TextOut(memdc, 550, 30, out, strlen(out));
		}

		sprintf(out, "Script: %d", subselect[mode][0]);
		if (focus == 1 && cursor)sprintf(out, "%s|", out);
		TextOut(memdc, 76, 10, out, strlen(out));

		SelectObject(bmpdc, plus);
		BitBlt(memdc, 146, 8, 20, 20, bmpdc, 0, 0, SRCCOPY);

		SelectObject(bmpdc, zoom);
		BitBlt(target, 346, 8, 20, 20, bmpdc, 0, 0, SRCCOPY);

		POINT points[4];

		switch (select[mode]) {
			case 0:
				tempb = (HBRUSH)SelectObject(target, node);

				RoundRect(target, x - 238, y - 10, x - 2, y + 60, 24, 30);

				RoundRect(target, x - 130, y + 10, x - 2, y + 60, 24, 30);
				SelectObject(target, selnode);
				RoundRect(target, x - 238, y + 10, x - 110, y + 60, 24, 30);
				break;
			case 1:
				tempb = (HBRUSH)SelectObject(target, node);

				RoundRect(target, x - 238, y - 10, x - 2, y + 60, 24, 30);

				RoundRect(target, x - 238, y + 10, x - 110, y + 60, 24, 30);
				SelectObject(target, selnode);
				RoundRect(target, x - 130, y + 10, x - 2, y + 60, 24, 30);
				break;
			case 4:
				tempb = (HBRUSH)SelectObject(target, selnode);
				RoundRect(target, x - 238, y - 10, x - 2, y + 60, 24, 30);

				SelectObject(target, node);

				RoundRect(target, x - 238, y + 10, x - 110, y + 60, 24, 30);
				RoundRect(target, x - 130, y + 10, x - 2, y + 60, 24, 30);


				break;
		}

		TextOut(target, x - 195, y + 12, "Actions", 7);
		TextOut(target, x - 95, y + 12, "Checks", 6);
		TextOut(target, x - 155, y - 8, "Advanced", 8);

		SelectObject(target, bgbr);

		Rectangle(target, x - 238, y + 30, x - 22, y + 390);

		SelectObject(target, node);


		Rectangle(target, x - 230, y + 400, x - 120, y + 425);
		TextOut(target, x - 202, y + 404, "Add End", 7);

		Rectangle(target, x - 120, y + 400, x - 10, y + 425);
		TextOut(target, x - 92, y + 404, "Fill Ends", 9);

		if (sel&&sel->in.size>0) {
			Rectangle(target, x - 230, y + 430, x - 120, y + 455);
			TextOut(target, x - 222, y + 434, "Previous Node", 13);
		}

		if (sel&&sel->type->numout == 2) {
			Rectangle(target, x - 120, y + 430, x - 10, y + 455);
			TextOut(target, x - 112, y + 434, "Follow Branch", 13);
		}

		Rectangle(target, x - 230, y + 460, x - 120, y + 485);
		TextOut(target, x - 197, y + 464, "Search", 6);

		Rectangle(target, x - 120, y + 460, x - 10, y + 485);
		TextOut(target, x - 92, y + 464, "Clear All", 9);

		LLNode<int>* curi = choices[cpos];
		int i = 0;
		HPEN old;

		while (curi&&i<18) {

			for (int dc = 0; dc < NUM_WC_COLORS; dc++) {
				if (!strcmp(WCColors[dc].elemA, nodeTypesWC[curi->data].name)) {
					old = (HPEN)SelectObject(target, CreatePen(PS_SOLID, 1, WCColors[dc].elemB));
					SelectObject(target, CreateSolidBrush(WCColors[dc].elemC));
					break;
				}
			}

			Rectangle(target, x - 238, y + 30 + 20 * i, x - 22, y + 50 + 20 * i);

			for (int dc = 0; dc < NUM_WC_COLORS; dc++) {
				if (!strcmp(WCColors[dc].elemA, nodeTypesWC[curi->data].name)) {
					DeleteObject(SelectObject(target, old));
					DeleteObject(SelectObject(target, node));
					break;
				}
			}

			TextOut(target, x - 233, y + 32 + 20 * i, nodeTypesWC[curi->data].name, strlen(nodeTypesWC[curi->data].name));

			if (strlen(nodeTypesWC[curi->data].helptext)>0) {
				Rectangle(target, x - 42, y + 30 + 20 * i, x - 22, y + 50 + 20 * i);
				TextOut(target, x - 36, y + 32 + 20 * i, "?", 1);
			}

			curi = curi->next;
			i++;
		}

		Rectangle(target, x - 22, y + 30, x - 2, y + 50);
		Rectangle(target, x - 22, y + 370, x - 2, y + 390);

		SelectObject(target, GetStockObject(BLACK_BRUSH));

		points[0].x = x - 22 + 4;
		points[0].y = y + 50 - 7;

		points[1].x = x - 2 - 5;
		points[1].y = y + 50 - 7;

		points[2].x = x - 12;
		points[2].y = y + 30 + 6;

		Polygon(target, points, 3);

		points[0].x = x - 22 + 4;
		points[0].y = y + 370 + 6;

		points[1].x = x - 2 - 5;
		points[1].y = y + 370 + 6;

		points[2].x = x - 12;
		points[2].y = y + 390 - 7;

		Polygon(target, points, 3);


		SelectObject(target, bgbr);

		Rectangle(target, x - 22, y + 50, x - 2, y + 370);

		SelectObject(target, selnode);

		Rectangle(target, x - 22, y + 50 + cpos * 280 / (choices.size - 1), x - 2, y + 90 + cpos * 280 / (choices.size - 1));

		SelectObject(target, tempb);

		int dx, dy;
		dx = 0 - vx%gridsize;
		while (dx<w*graphzoom) {
			MoveToEx(gdc, dx, 0, 0);
			LineTo(gdc, dx, h*graphzoom);
			dx += gridsize;
		}

		dy = 0 - vy%gridsize;
		while (dy<h*graphzoom) {
			MoveToEx(gdc, 0, dy, 0);
			LineTo(gdc, w*graphzoom, dy);
			dy += gridsize;
		}

		SelectObject(gdc, temp);
		SelectObject(gdc, node);

		LLNode<WCGraphNode*>* cur = nodes.head;
		while (cur) {
			cur->data->x -= vx;
			cur->data->y -= vy;
			cur = cur->next;
		}
		cur = nodes.head;
		while (cur) {
			//if(cur->data->x>=0-cur->data->w && cur->data->x<=w && cur->data->y>=0-cur->data->h && cur->data->y<=h){
			if (cur->data->selected || selgroup.find(cur->data)) {
				SelectObject(gdc, selborder);
				SelectObject(gdc, selnode);
			} else {
				for (int dc = 0; dc < NUM_WC_COLORS; dc++) {
					if (!strcmp(WCColors[dc].elemA, cur->data->type->name)) {
						SelectObject(gdc, CreatePen(PS_SOLID, 2, WCColors[dc].elemB));
						SelectObject(gdc, CreateSolidBrush(WCColors[dc].elemC));
						break;
					}
				}
			}
			cur->data->paint(gdc);
			if (cur->data->selected || selgroup.find(cur->data)) {
				SelectObject(gdc, border);
				SelectObject(gdc, node);
			} else {
				for (int dc = 0; dc < NUM_WC_COLORS; dc++) {
					if (!strcmp(WCColors[dc].elemA, cur->data->type->name)) {
						DeleteObject(SelectObject(gdc, border));
						DeleteObject(SelectObject(gdc, node));
						break;
					}
				}
			}
			//}
			cur = cur->next;
		}
		cur = nodes.head;
		while (cur) {
			cur->data->x += vx;
			cur->data->y += vy;
			cur = cur->next;
		}

		if (vy>-h*graphzoom&&vy<h*graphzoom) {
			MoveToEx(gdc, 0, 0 - vy, 0);
			LineTo(gdc, w*graphzoom, 0 - vy);
		}

		if (vx>-w*graphzoom&&vx<w*graphzoom) {
			MoveToEx(gdc, 0 - vx, 0, 0);
			LineTo(gdc, 0 - vx, h*graphzoom);
		}

		temp = (HPEN)SelectObject(gdc, (HPEN)GetStockObject(NULL_PEN));

		if (vy>-h*graphzoom&&vy<h*graphzoom) {
			Rectangle(gdc, 0, 0 - vy, w*graphzoom, 0);
		}

		if (vx>-w*graphzoom&&vx<w*graphzoom) {
			Rectangle(gdc, 0 - vx, 0, 0, h*graphzoom);
		}

		SelectObject(gdc, temp);

		SelectObject(gdc, (HBRUSH)GetStockObject(NULL_BRUSH));

		if (dragsel && !menu) {
			POINT p;
			GetCursorPos(&p);
			ScreenToClient(hwnd, &p);
			p.y -= 40;

			int tx, tx2, ty, ty2;

			tx = lx;
			ty = ly;
			tx2 = p.x;
			ty2 = p.y;

			tx -= x;
			ty -= y;
			tx *= graphzoom;
			ty *= graphzoom;


			tx2 -= x;
			ty2 -= y;
			tx2 *= graphzoom;
			ty2 *= graphzoom;


			Rectangle(gdc, tx, ty, tx2, ty2);
		}

		SelectObject(gdc, bgbr);

		if (menu == 1) {
			Rectangle(gdc, w / 2 - 200, h / 2 - 150, w / 2 + 200, h / 2 + 180);

			SetTextAlign(gdc, TA_CENTER);

			TextOut(gdc, w / 2, h / 2 - 140, sel->type->name, strlen(sel->type->name));

			Rectangle(gdc, w / 2 - 185, h / 2 + 107, w / 2 - 15, h / 2 + 133);
			TextOut(gdc, w / 2 - 100, h / 2 + 110, "Disconnect", 10);

			Rectangle(gdc, w / 2 + 15, h / 2 + 107, w / 2 + 185, h / 2 + 133);
			TextOut(gdc, w / 2 + 100, h / 2 + 110, "Remove", 6);

			Rectangle(gdc, w / 2 - 185, h / 2 + 142, w / 2 - 15, h / 2 + 168);
			TextOut(gdc, w / 2 - 100, h / 2 + 145, "Disconnect Ins", 14);

			Rectangle(gdc, w / 2 + 15, h / 2 + 142, w / 2 + 185, h / 2 + 168);
			TextOut(gdc, w / 2 + 100, h / 2 + 145, "Disconnect Outs", 14);

			SetTextAlign(gdc, TA_LEFT);

			int dy = h / 2 - 150 + 60;
			int t;

			if (!strcmp("Display Portrait", sel->type->name) && GraphicsLoaded) {
				int m = sel->args[0];
				int width = POSize[m][0];
				int height = POSize[m][1];

				for (int tx = 0; tx<width; tx++) {
					for (int ty = 0; ty<height; ty++) {
						for (i = 0; i<2; i++) {
							for (int j = 0; j<2; j++) {
								int k = Portraits[m][tx + ty*width];
								if (k<0)k = 0;

								SetPixel(gdc, tx * 2 + i + w / 2 - 200 + 40, ty * 2 + j + dy + 20, RGB(POPalette[m][k][0], POPalette[m][k][1], POPalette[m][k][2]));
							}
						}
					}
				}
			}

			for (i = 0; i<4; i++) {
				switch (sel->type->argtypes[i]) {
					case ARG_MOVEMENT:

						int ie;
						ie = 0;

						sprintf(out, "(Left click to change, right to remove)");
						TextOut(gdc, w / 2 - 200 + 80, h/2 - 150 + 30, out, strlen(out));

						while (sel->extra[ie] != 0xFF) {
							switch (sel->extra[ie]) {
								case 0:
									SelectObject(bmpdc, moveup);
									break;
								case 1:
									SelectObject(bmpdc, movedown);
									break;
								case 2:
									SelectObject(bmpdc, moveright);
									break;
								case 3:
									SelectObject(bmpdc, moveleft);
									break;
							}
							
							BitBlt(gdc, w/2-200 + 8 + 24*(ie%16), h / 2 - 150 + 60 +40 + 24*((ie-ie%16)/16), 24, 24, bmpdc, 0, 0, SRCCOPY);
							ie++;
						}

						if (ie < 96) {
							SelectObject(bmpdc, moveadd);
							BitBlt(gdc, w / 2 - 200 + 8 + 24 * (ie % 16), h / 2 - 150 + 60 + 40 + 24 * ((ie - ie % 16) / 16), 24, 24, bmpdc, 0, 0, SRCCOPY);
						}

						break;
					case ARG_BYTE:
					case ARG_WORD:
					case ARG_LONG:
						TextOut(gdc, w / 2 - 200 + 40, dy, sel->type->arglabel[i], strlen(sel->type->arglabel[i]));
						sprintf(out, "%u", sel->args[i]);
						if (focus == 2 && subfocus == i&&cursor)sprintf(out, "%s|", out);
						TextOut(gdc, w / 2 - 200 + 180, dy, out, strlen(out));
						dy += 40;
						break;
					case ARG_ADDSUB:
						TextOut(gdc, w / 2 - 200 + 40, dy, sel->type->arglabel[i], strlen(sel->type->arglabel[i]));
						t = sel->args[i] & 0x0E;
						t = t /= 2;
						if (sel->args[i] & 0x01)t *= -1;
						sprintf(out, "%d", t);
						if (focus == 2 && subfocus == i&&cursor)sprintf(out, "%s|", out);
						TextOut(gdc, w / 2 - 200 + 180, dy, out, strlen(out));
						dy += 40;
						break;
					case ARG_YESNO:
						TextOut(gdc, w / 2 - 200 + 40, dy, sel->type->arglabel[i], strlen(sel->type->arglabel[i]));
						sprintf(out, "%d", (sel->args[i] & 0xFF00) / 0x100);
						if (focus == 2 && subfocus == i&&cursor)sprintf(out, "%s|", out);
						TextOut(gdc, w / 2 - 200 + 180, dy, out, strlen(out));
						sprintf(out, "%d", (sel->args[i] & 0xFF));
						if (focus == 2 && subfocus == -1 * i - 1 && cursor)sprintf(out, "%s|", out);
						TextOut(gdc, w / 2 - 200 + 230, dy, out, strlen(out));

						if (TextLoaded) {
							sprintf(out, "%s", Text[(sel->args[i] & 0xFF00) / 0x100 + sel->bank]);
							removeTags(out);
							if (strlen(out)>40) {
								out[40] = '.';
								out[41] = '.';
								out[42] = '.';
								out[43] = 0;
							}
							TextOut(gdc, w / 2 - 200 + 60, dy + 20, out, strlen(out));

							sprintf(out, "%s", Text[(sel->args[i] & 0xFF) + sel->bank]);
							removeTags(out);
							if (strlen(out)>40) {
								out[40] = '.';
								out[41] = '.';
								out[42] = '.';
								out[43] = 0;
							}
							TextOut(gdc, w / 2 - 200 + 60, dy + 40, out, strlen(out));
						}

						dy += 80;
						break;
					case ARG_BRANCH:
						TextOut(gdc, w / 2 - 200 + 40, dy, sel->type->arglabel[i], strlen(sel->type->arglabel[i]));
						sprintf(out, "%s", branchName(sel->args[i], strcmp(sel->type->name, "Branch on Yes/No") == 0));
						if (focus == 2 && subfocus == i&&cursor)sprintf(out, "%s|", out);
						TextOut(gdc, w / 2 - 200 + 180, dy, out, strlen(out));
						dy += 40;
						break;
					case ARG_SBRANCH:
						TextOut(gdc, w / 2 - 200 + 40, dy, sel->type->arglabel[i], strlen(sel->type->arglabel[i]));
						sprintf(out, "%s", sbranchName(sel->args[i]));
						if (focus == 2 && subfocus == i&&cursor)sprintf(out, "%s|", out);
						TextOut(gdc, w / 2 - 200 + 180, dy, out, strlen(out));
						dy += 40;
						break;
					case ARG_SPECIAL:
						TextOut(gdc, w / 2 - 200 + 40, dy, sel->type->arglabel[i], strlen(sel->type->arglabel[i]));
						switch (sel->args[i]) {
							case 0x180B4:
								sprintf(out, "No one is in that direction");
								break;
							case 0x18074:
								sprintf(out, "Nothing is unusual");
								break;
							case 0x1808A:
								sprintf(out, "Hero uses the item!");
								break;
							default:
								sprintf(out, "%d", sel->args[i]);
								break;
						}
						TextOut(gdc, w / 2 - 200 + 60, dy + 20, out, strlen(out));
						dy += 40;
						break;
					case ARG_MESSAGE:
						TextOut(gdc, w / 2 - 200 + 40, dy, sel->type->arglabel[i], strlen(sel->type->arglabel[i]));
						sprintf(out, "%d", sel->args[i]);
						if (focus == 2 && subfocus == i&&cursor)sprintf(out, "%s|", out);
						TextOut(gdc, w / 2 - 200 + 180, dy, out, strlen(out));
						if (TextLoaded) {
							sprintf(out, "%s", Text[sel->args[i]]);
							removeTags(out);
							if (strlen(out)>40) {
								out[40] = '.';
								out[41] = '.';
								out[42] = '.';
								out[43] = 0;
							}
							TextOut(gdc, w / 2 - 200 + 60, dy + 20, out, strlen(out));
						}
						dy += 60;
						break;
					case ARG_BANKED:
						TextOut(gdc, w / 2 - 200 + 40, dy, sel->type->arglabel[i], strlen(sel->type->arglabel[i]));
						sprintf(out, "%d", sel->args[i]);
						if (focus == 2 && subfocus == i&&cursor)sprintf(out, "%s|", out);
						TextOut(gdc, w / 2 - 200 + 180, dy, out, strlen(out));
						if (TextLoaded) {
							sprintf(out, "%s", Text[sel->args[i] + sel->bank]);
							removeTags(out);
							if (strlen(out)>40) {
								out[40] = '.';
								out[41] = '.';
								out[42] = '.';
								out[43] = 0;
							}
							TextOut(gdc, w / 2 - 200 + 60, dy + 20, out, strlen(out));
						}
						dy += 60;
						break;
					case ARG_DIR:
						if (sel->args[i] == 0) {
							Rectangle(gdc, w / 2 - 140 + 115, dy, w / 2 - 140 + 165, dy + 20);
						}
						if (sel->args[i] == 2) {
							Rectangle(gdc, w / 2 - 140 + 115, dy + 80, w / 2 - 140 + 165, dy + 100);
						}
						if (sel->args[i] == 3) {
							Rectangle(gdc, w / 2 - 140 + 40, dy + 40, w / 2 - 140 + 90, dy + 60);
						}
						if (sel->args[i] == 1) {
							Rectangle(gdc, w / 2 - 140 + 190, dy + 40, w / 2 - 140 + 240, dy + 60);
						}

						TextOut(gdc, w / 2 - 140 + 131, dy + 1, "Up", 2);
						TextOut(gdc, w / 2 - 140 + 51, dy + 41, "Left", 4);
						TextOut(gdc, w / 2 - 140 + 196, dy + 41, "Right", 5);
						TextOut(gdc, w / 2 - 140 + 121, dy + 81, "Down", 4);
						dy += 120;
						break;
					case ARG_DIR2:
						if (sel->args[i] == 0) {
							Rectangle(gdc, w / 2 - 140 + 115, dy, w / 2 - 140 + 165, dy + 20);
						}
						if (sel->args[i] == 16) {
							Rectangle(gdc, w / 2 - 140 + 115, dy + 80, w / 2 - 140 + 165, dy + 100);
						}
						if (sel->args[i] == 24) {
							Rectangle(gdc, w / 2 - 140 + 40, dy + 40, w / 2 - 140 + 90, dy + 60);
						}
						if (sel->args[i] == 8) {
							Rectangle(gdc, w / 2 - 140 + 190, dy + 40, w / 2 - 140 + 240, dy + 60);
						}

						TextOut(gdc, w / 2 - 140 + 131, dy + 1, "Up", 2);
						TextOut(gdc, w / 2 - 140 + 51, dy + 41, "Left", 4);
						TextOut(gdc, w / 2 - 140 + 196, dy + 41, "Right", 5);
						TextOut(gdc, w / 2 - 140 + 121, dy + 81, "Down", 4);
						dy += 120;
						break;
				}
			}
		}
		if (menu == 2) {
			Rectangle(gdc, w / 2 - 200, h / 2 - 150, w / 2 + 200, h / 2 + 150);

			SetTextAlign(gdc, TA_CENTER);

			TextOut(gdc, w / 2, h / 2 - 140, "Search", 6);

			SetTextAlign(gdc, TA_LEFT);

			TextOut(gdc, w / 2 - 200 + 40, h / 2 - 150 + 60, "Message Number", 14);
			sprintf(out, "%d", subselect[mode][8]);
			if (focus == 32 && cursor)sprintf(out, "%s|", out);
			TextOut(gdc, w / 2 - 200 + 175, h / 2 - 150 + 60, out, strlen(out));

			Rectangle(gdc, w / 2 - 200 + 258, h / 2 - 150 + 60, w / 2 - 200 + 348, h / 2 - 150 + 79);
			TextOut(gdc, w / 2 - 200 + 287, h / 2 - 150 + 60, "Find", 4);

			TextOut(gdc, w / 2 - 200 + 40, h / 2 - 150 + 80, "Event Number", 12);
			sprintf(out, "%d", subselect[mode][9]);
			if (focus == 33 && cursor)sprintf(out, "%s|", out);
			TextOut(gdc, w / 2 - 200 + 175, h / 2 - 150 + 80, out, strlen(out));

			Rectangle(gdc, w / 2 - 200 + 258, h / 2 - 150 + 80, w / 2 - 200 + 348, h / 2 - 150 + 99);
			TextOut(gdc, w / 2 - 200 + 287, h / 2 - 150 + 80, "Find", 4);

			if (searchmulti)SelectObject(bmpdc, checkon);
			else SelectObject(bmpdc, checkoff);
			BitBlt(gdc, w / 2 - 200 + 40, h / 2 + 122, 13, 13, bmpdc, 0, 0, SRCCOPY);
			TextOut(gdc, w / 2 - 200 + 60, h / 2 + 120, "Search all scripts", 18);
		}
		Rectangle(target, x, y, x + w, y + h);

		if (graphzoom == 1)BitBlt(target, x, y, w, h, gdc, 0, 0, SRCCOPY);
		else StretchBlt(target, x, y, w, h, gdc, 0, 0, w*graphzoom, h*graphzoom, SRCCOPY);

		if (searchstart != -1) {
			search(searchtype);
		}
	}

	void addNode(int x, int y, int t = 0, long o = 0) {
		if (x<0)x = 0;
		if (y<0)y = 0;
		nodes.add(new WCGraphNode(x, y, 80, 80, t, o));
	}

	void clearVisited() {
		LLNode<WCGraphNode*>* cur = nodes.head;

		while (cur) {
			cur->data->visited = false;
			cur = cur->next;
		}
	}

	void fillEnds() {
		LLNode<WCGraphNode*>* cur = nodes.head;

		while (cur) {
			if (cur->data->out.size == 0 && cur->data->type->shape != 3) {
				addNode(cur->data->x + 112, cur->data->y, 1);
				connect(cur->data, nodes.head->data);
			}
			if (cur->data->out.size == 1 && cur->data->type->shape == 1) {
				addNode(cur->data->x + 112, cur->data->y + 96, 1);
				connect(cur->data, nodes.head->data);
			}
			cur = cur->next;
		}
		InvalidateRect(hwnd, NULL, 0);
	}

	void keydown(int key) {
		switch (key) {
			case 219:
				removeIns();
				return;
			case 221:
				removeOuts();
				return;
			case VK_F3:
				search(searchtype);
				break;
			case VK_UP:
			case VK_LEFT:
				if (sel&&sel->in.size) {
					sel->selected = false;
					sel->selout = false;

					vx += sel->in.head->data->x - sel->x;
					vy += sel->in.head->data->y - sel->y;

					sel = sel->in.head->data;
					sel->selected = true;
					sel->selout = false;
				}
				break;
			case VK_DOWN:
				if (sel&&sel->out.size) {
					sel->selected = false;
					sel->selout = false;

					vx += sel->out.head->data->x - sel->x;
					vy += sel->out.head->data->y - sel->y;

					sel = sel->out.head->data;
					sel->selected = true;
					sel->selout = false;
				}
				break;
			case VK_RIGHT:
				if (sel&&sel->out.size) {
					sel->selected = false;
					sel->selout = false;

					vx += sel->out.tail->data->x - sel->x;
					vy += sel->out.tail->data->y - sel->y;

					sel = sel->out.tail->data;
					sel->selected = true;
					sel->selout = false;
				}
				break;
		}
	}

	void click(int px, int py) {
		WCGraphNode * node;
		if (menu == 1) {
			px -= x;
			py -= y;
			px *= graphzoom;
			py *= graphzoom;

			if (px >= w / 2 - 185 && px <= w / 2 - 15 && py >= h / 2 + 107 && py <= h / 2 + 133) {
				sel->selout = true;
				menu = 0;
				ignorerelease = true;
				remove();
				sel->selout = false;
				return;
			}

			if (px >= w / 2 + 15 && px <= w / 2 + 185 && py >= h / 2 + 107 && py <= h / 2 + 133) {
				sel->selout = false;
				menu = 0;
				ignorerelease = true;
				remove();
				return;
			}

			if (px >= w / 2 - 185 && px <= w / 2 - 15 && py >= h / 2 + 142 && py <= h / 2 + 168) {
				removeIns();
				return;
			}

			if (px >= w / 2 + 15 && px <= w / 2 + 185 && py >= h / 2 + 142 && py <= h / 2 + 168) {
				removeOuts();
				return;
			}

			if (px >= w / 2 - 200 && px <= w / 2 + 200 && py >= h / 2 - 150 && py <= h / 2 + 150) {
				int dy = h / 2 - 150 + 60;

				for (int i = 0; i<4; i++) {
					switch (sel->type->argtypes[i]) {
						case ARG_MOVEMENT:

							int ie;
							ie = 0;

							while (sel->extra[ie] != 0xFF) {

								if (px >= w / 2 - 200 + 8 + 24 * (ie % 16) && px <= w / 2 - 200 + 8 + 24 * (ie % 16)+24 && py >= h / 2 - 150 + 60 + 40 + 24 * ((ie - ie % 16) / 16) && py <= h / 2 - 150 + 60 + 40 + 24 * ((ie - ie % 16) / 16)+24) {
									sel->extra[ie]++;
									sel->extra[ie] %= 4;
								}

								ie++;
							}

							if (ie < 96) {
								if (px >= w / 2 - 200 + 8 + 24 * (ie % 16) && px <= w / 2 - 200 + 8 + 24 * (ie % 16) + 24 && py >= h / 2 - 150 + 60 + 40 + 24 * ((ie - ie % 16) / 16) && py <= h / 2 - 150 + 60 + 40 + 24 * ((ie - ie % 16) / 16)+24) {
									sel->extra[ie] = 0;
									sel->extra[ie + 1] = 0xFF;
								}
							}

							break;
						case ARG_BYTE:
						case ARG_WORD:
						case ARG_LONG:
						case ARG_BRANCH:
						case ARG_SBRANCH:
						case ARG_ADDSUB:
							if (px >= w / 2 - 200 + 180 && px <= w / 2 - 200 + 280 && py >= dy&&py <= dy + 20) {
								focus = 2;
								subfocus = i;
							}
							dy += 40;
							break;
						case ARG_YESNO:
							if (px >= w / 2 - 200 + 180 && px <= w / 2 - 200 + 230 && py >= dy&&py <= dy + 20) {
								focus = 2;
								subfocus = i;
							}
							if (px >= w / 2 - 200 + 230 && px <= w / 2 - 200 + 280 && py >= dy&&py <= dy + 20) {
								focus = 2;
								subfocus = -1 * i - 1;
							}
							dy += 80;
							break;
						case ARG_SPECIAL:
							if (px >= w / 2 - 200 + 60 && px <= w / 2 - 200 + 160 && py >= dy + 20 && py <= dy + 40) {
								switch (sel->args[i]) {
									case 0x180B4:
										sel->args[i] = 0x18074;
										break;
									case 0x18074:
										sel->args[i] = 0x1808A;
										break;
									case 0x1808A:
									default:
										sel->args[i] = 0x180B4;
										break;
								}
							}
							dy += 60;
							break;
						case ARG_MESSAGE:
						case ARG_BANKED:
							if (px >= w / 2 - 200 + 180 && px <= w / 2 - 200 + 280 && py >= dy&&py <= dy + 20) {
								focus = 2;
								subfocus = i;
							}
							dy += 60;
							break;
						case ARG_DIR:
							if (px >= w / 2 - 140 + 115 && px <= w / 2 - 140 + 165 && py >= dy&&py <= dy + 20) {
								sel->args[i] = 0;
							}
							if (px >= w / 2 - 140 + 115 && px <= w / 2 - 140 + 165 && py >= dy + 80 && py <= dy + 100) {
								sel->args[i] = 2;
							}
							if (px >= w / 2 - 140 + 40 && px <= w / 2 - 140 + 90 && py >= dy + 40 && py <= dy + 60) {
								sel->args[i] = 3;
							}
							if (px >= w / 2 - 140 + 190 && px <= w / 2 - 140 + 240 && py >= dy + 40 && py <= dy + 60) {
								sel->args[i] = 1;
							}
							dy += 120;
							break;
						case ARG_DIR2:
							if (px >= w / 2 - 140 + 115 && px <= w / 2 - 140 + 165 && py >= dy&&py <= dy + 20) {
								sel->args[i] = 0;
							}
							if (px >= w / 2 - 140 + 115 && px <= w / 2 - 140 + 165 && py >= dy + 80 && py <= dy + 100) {
								sel->args[i] = 16;
							}
							if (px >= w / 2 - 140 + 40 && px <= w / 2 - 140 + 90 && py >= dy + 40 && py <= dy + 60) {
								sel->args[i] = 24;
							}
							if (px >= w / 2 - 140 + 190 && px <= w / 2 - 140 + 240 && py >= dy + 40 && py <= dy + 60) {
								sel->args[i] = 8;
							}
							dy += 120;
							break;
					}
				}


			} else {
				if (sel)sel->selected = false;
				sel = 0;
				menu = 0;
				ignorerelease = true;
			}

			return;
		}
		if (menu == 2) {
			px -= x;
			py -= y;
			px *= graphzoom;
			py *= graphzoom;

			if (px >= w / 2 - 200 && px <= w / 2 + 200 && py >= h / 2 - 150 && py <= h / 2 + 150) {

				if (px >= w / 2 - 200 + 175 && px <= w / 2 - 200 + 258 && py >= h / 2 - 150 + 60 && py <= h / 2 - 150 + 80) {
					focus = 32;
				}
				if (px >= w / 2 - 200 + 258 && px <= w / 2 - 200 + 348 && py >= h / 2 - 150 + 60 && py <= h / 2 - 150 + 79) {
					search(0);
				}

				if (px >= w / 2 - 200 + 175 && px <= w / 2 - 200 + 258 && py >= h / 2 - 150 + 80 && py <= h / 2 - 150 + 100) {
					focus = 33;
				}
				if (px >= w / 2 - 200 + 258 && px <= w / 2 - 200 + 348 && py >= h / 2 - 150 + 80 && py <= h / 2 - 150 + 99) {
					search(1);
				}

				if (px >= w / 2 - 200 + 40 && px <= w / 2 - 200 + 53 && py >= h / 2 + 122 && py <= h / 2 + 135) {
					searchmulti = !searchmulti;
				}

			} else {
				if (sel)sel->selected = false;
				sel = 0;
				menu = 0;
				ignorerelease = true;
			}
			return;
		}
		if (px >= x - 230 && px <= x - 120 && py >= y + 400 && py <= y + 425) {
			addNode(vx + w / 2, vy + h / 2, 1);
			selplace = -1;
			InvalidateRect(hwnd, NULL, 0);
		}

		if (px >= x - 120 && px <= x - 10 && py >= y + 400 && py <= y + 425) {
			fillEnds();
		}

		if (px >= x - 230 && px <= x - 120 && py >= y + 430 && py <= y + 455) {
			if (sel&&sel->in.size>0) {
				sel->selected = false;
				sel = sel->in.tail->data;
				sel->selected = true;
				sel->selout = false;
				vx = sel->x - w / 2 + sel->w / 2;
				vy = sel->y - h / 2 + sel->h / 2;
				InvalidateRect(hwnd, NULL, 0);
				return;
			}
		}

		if (px >= x - 120 && px <= x - 10 && py >= y + 430 && py <= y + 455) {
			if (sel&&sel->type->numout == 2) {
				sel->selected = false;
				sel = sel->out.head->data;
				sel->selected = true;
				sel->selout = false;
				vx = sel->x - w / 2 + sel->w / 2;
				vy = sel->y - h / 2 + sel->h / 2;
				InvalidateRect(hwnd, NULL, 0);
				return;
			}
		}

		if (px >= x - 230 && px <= x - 120 && py >= y + 460 && py <= y + 485) {
			menu = 2;
			return;
		}
		if (px >= x - 120 && px <= x - 10 && py >= y + 460 && py <= y + 485) {
			if (MessageBox(NULL, "Are you sure you want to clear all nodes from this script?", "Confirm", MB_YESNO) == IDYES) {
				clear();
			}
		}

		if (px >= 346 && px <= 366 && py >= 8 && py <= 28) {
			graphzoom *= 2;
			if (graphzoom == 16)graphzoom = 1;
			return;
		}

		scroll = false;
		sel = 0;
		selplace = -1;
		lx = px;
		ly = py;
		LLNode<WCGraphNode*>* cur = nodes.head;

		if (px >= x - 22 && px <= x - 2 && py >= y + 50 + cpos * 280 / (choices.size - 1) && py <= y + 90 + cpos * 280 / (choices.size - 1)) {
			scroll = true;
		}

		if (px >= x - 238 && px <= x - 130 && py >= y + 10 && py <= y + 30) {
			select[mode] = 0;
			cpos = 0;
			buildList();
		}
		if (px >= x - 110 && px <= x - 2 && py >= y + 10 && py <= y + 30) {
			select[mode] = 1;
			cpos = 0;
			buildList();
		}
		if (px >= x - 238 && px <= x - 2 && py >= y - 10 && py <= y + 10) {
			select[mode] = 4;
			cpos = 0;
			buildList();
		}

		if (px >= x - 22 && px <= x - 2 && py >= y + 30 && py <= y + 50) {
			if (cpos)cpos--;
			InvalidateRect(hwnd, NULL, 0);
		}

		if (px >= x - 22 && px <= x - 2 && py >= y + 370 && py <= y + 390) {
			if (cpos<choices.size - 1)cpos++;
			InvalidateRect(hwnd, NULL, 0);
		}



		LLNode<int>* curi = choices[cpos];
		int i = 0;
		while (curi&&i<18) {
			if (strlen(nodeTypesWC[curi->data].helptext)>0)
				if (px >= x - 42 && px <= x - 22 && py >= y + 30 + 20 * i&&py <= y + 50 + 20 * i) {
					MessageBox(NULL, nodeTypesWC[curi->data].helptext, "Help", MB_OK);
					return;
				}

			if (px >= x - 238 && px <= x - 22 && py >= y + 30 + 20 * i&&py <= y + 50 + 20 * i) {
				selplace = curi->data;
			}
			curi = curi->next;
			i++;
		}

		if (px >= x&&px <= x + w*graphzoom&&py >= y&&py <= y + h*graphzoom) {
			px -= x;
			py -= y;
			px *= graphzoom;
			py *= graphzoom;
			px += vx;
			py += vy;
			cur = nodes.head;
			while (cur) {
				if (px >= cur->data->x&&px <= cur->data->x + cur->data->w&&py >= cur->data->y&&py <= cur->data->y + cur->data->h) {
					if (sel)sel->selected = false;
					cur->data->click(px - cur->data->x, py - cur->data->y);
					sel = cur->data;

					if (!selgroup.find(sel))selgroup.clean();
				} else {
					cur->data->selected = false;
				}
				cur = cur->next;
			}
			if (!sel) {
				selgroup.clean();

				if (GetKeyState(VK_SHIFT) & 0x80) 
					dragsel = true;
				else
					drag = true;

				SetCapture(hwnd);
			}
		} else {
			cur = nodes.head;
			while (cur) {
				cur->data->selected = false;
				cur = cur->next;
			}

		}


	}

	void search(int type) {
		if (type == -1)return;
		searchtype = type;

		WCGraphNode * node = 0;

		if (searchstart == -1) {
			searchstart = subselect[mode][0];
			if (sel)searchmet = false;
			else searchmet = true;
		} else {
			searchmet = true;
		}

		switch (type) {
			case 0:
				node = findMessage(subselect[mode][8]);

				if (sel && !node && !searchmulti) {
					searchmet = true;
					node = findMessage(subselect[mode][8]);
				}
				break;
			case 1:
				node = findEvent(subselect[mode][9]);

				if (sel && !node && !searchmulti) {
					searchmet = true;
					node = findEvent(subselect[mode][9]);
				}
				break;
		}

		if (node) {
			if (sel)sel->selected = false;
			node->selected = true;
			node->selout = false;
			sel = node;
			vx = sel->x - w / 2;
			vy = sel->y - h / 2;
			menu = 0;
			ignorerelease = true;
			searchstart = -1;
		} else {
			if (searchmulti && subselect[mode][0] != searchstart - 1 && (searchstart != 0 || subselect[mode][0] != NUM_WC - 1)) {
				subselect[mode][0]++;
				if (subselect[mode][0] == NUM_WC)subselect[mode][0] = 0;
			} else {
				searchstart = -1;
				MessageBox(NULL, "Not found.", "Note", MB_OK);
			}
		}
	}

	void rclick(int px, int py) {
		if (menu == 1) {
			px -= x;
			py -= y;
			px *= graphzoom;
			py *= graphzoom;

			if (px >= w / 2 - 200 && px <= w / 2 + 200 && py >= h / 2 - 150 && py <= h / 2 + 150) {
				int dy = h / 2 - 150 + 60;

				for (int i = 0; i<4; i++) {
					switch (sel->type->argtypes[i]) {
					case ARG_MOVEMENT:

						int ie;
						ie = 0;

						while (sel->extra[ie] != 0xFF) {

							if (px >= w / 2 - 200 + 8 + 24 * (ie % 16) && px <= w / 2 - 200 + 8 + 24 * (ie % 16) + 24 && py >= h / 2 - 150 + 60 + 40 + 24 * ((ie - ie % 16) / 16) && py <= h / 2 - 150 + 60 + 40 + 24 * ((ie - ie % 16) / 16) + 24) {
								for (int ier = ie; ier < 256; ier++) {
									sel->extra[ier] = sel->extra[ier + 1];
								}
								return;
							}

							ie++;
						}

						break;
					
					}
				}


			}

			return;
		}

		LLNode<WCGraphNode*>* cur;
		if (px >= x&&px <= x + w*graphzoom&&py >= y&&py <= y + h*graphzoom) {
			px -= x;
			py -= y;
			px *= graphzoom;
			py *= graphzoom;
			px += vx;
			py += vy;
			cur = nodes.head;
			while (cur) {
				if (px >= cur->data->x&&px <= cur->data->x + cur->data->w&&py >= cur->data->y&&py <= cur->data->y + cur->data->h) {
					if (sel)sel->selected = false;
					cur->data->click(px - cur->data->x, py - cur->data->y);
					sel = cur->data;
					menu = 1;
				}
				cur = cur->next;
			}
		}
	}

	void dclick(int px, int py) {
		if (menu == 1) {
			return;
		}

		LLNode<int>* curi = choices[cpos];
		int i = 0;
		while (curi&&i<18) {
			if (px >= x - 238 && px <= x - 22 && py >= y + 30 + 20 * i&&py <= y + 50 + 20 * i) {
				addNode(vx + w / 2, vy + h / 2, curi->data);
				selplace = -1;
				InvalidateRect(hwnd, NULL, 0);
				return;
			}
			curi = curi->next;
			i++;
		}

		LLNode<WCGraphNode*>* cur;
		if (px >= x&&px <= x + w*graphzoom&&py >= y&&py <= y + h*graphzoom) {
			px -= x;
			py -= y;
			px *= graphzoom;
			py *= graphzoom;
			px += vx;
			py += vy;
			cur = nodes.head;
			while (cur) {
				if (px >= cur->data->x&&px <= cur->data->x + cur->data->w&&py >= cur->data->y&&py <= cur->data->y + cur->data->h) {
					if (sel)sel->selected = false;
					cur->data->click(px - cur->data->x, py - cur->data->y);
					sel = cur->data;
					menu = 1;
					return;
				}
				cur = cur->next;
			}
		}

		click(px, py);
	}

	void move(int px, int py) {
		if (menu == 1) {
			return;
		}
		if (menu == 2) {
			return;
		}

		if (scroll) {
			cpos = (py - (y + 50)) / (280 / (choices.size - 1));
			if (cpos<0)cpos = 0;
			if (cpos>choices.size - 1)cpos = choices.size - 1;
			InvalidateRect(hwnd, NULL, 0);
			return;
		}
		if (drag) {//px>=x&&px<=x+w&&py>=y&&py<=y+h){
			if (!sel) {
				if (selplace == -1) {
					vx -= (px - lx)*graphzoom;
					vy -= (py - ly)*graphzoom;
					if (vx <= -w)vx = -w + 1;
					if (vy <= -h)vy = -h + 1;
					lx = px;
					ly = py;
					InvalidateRect(hwnd, NULL, 0);
				}

			}
		}
		if (dragsel) {
			int tx, ty, tx2, ty2;

			if (lx < px) {
				tx = lx;
				tx2 = px;
			} else {
				tx2 = lx;
				tx = px;
			}

			if (ly < py) {
				ty = ly;
				ty2 = py;
			} else {
				ty2 = ly;
				ty = py;
			}

			if (px >= x&&px <= x + w*graphzoom&&py >= y&&py <= y + h*graphzoom) {
				selgroup.clean();

				tx -= x;
				ty -= y;
				tx *= graphzoom;
				ty *= graphzoom;
				tx += vx;
				ty += vy;

				tx2 -= x;
				ty2 -= y;
				tx2 *= graphzoom;
				ty2 *= graphzoom;
				tx2 += vx;
				ty2 += vy;
				LLNode<WCGraphNode*>* cur;
				cur = nodes.head;
				while (cur) {

					if (cur->data->x + cur->data->w / 2 > tx && cur->data->x + cur->data->w / 2 < tx2 && cur->data->y + cur->data->h / 2 > ty && cur->data->y + cur->data->h / 2 < ty2) {
						selgroup.add(cur->data);
					}
					cur = cur->next;
				}
			}

		}
		if (px >= x&&px <= x + w*graphzoom&&py >= y&&py <= y + h*graphzoom) {
			if (!sel && selplace != -1) {
				addNode(px - x + vx, py - y + vy, selplace);
				sel = nodes.head->data;
				nodes.head->data->selected = true;
				nodes.head->data->selout = false;
				return;
			}
			px -= x;
			py -= y;
			px *= graphzoom;
			py *= graphzoom;
			px += vx;
			py += vy;
			if (sel) {
				px -= sel->w / 2;
				py -= sel->h / 2;

				int tx = sel->x;
				int ty = sel->y;

				sel->move(px, py, gridsize);
				InvalidateRect(hwnd, NULL, 0);

				if (selgroup.size) {
					LLNode<WCGraphNode*>* cur = selgroup.head;



					while (cur) {
						if (cur->data != sel) {
							cur->data->move(sel->x - tx + cur->data->x, sel->y - ty + cur->data->y, gridsize);
						}
						cur = cur->next;
					}
				}
			}
		}
	}

	void release(int px, int py) {
		drag = false;
		dragsel = false;
		ReleaseCapture();
		if (menu == 1) {
			return;
		}

		scroll = false;
		selplace = -1;
		if (sel) {
			if (sel->selout) {
				sel->selout = false;

				LLNode<WCGraphNode*>* cur;
				if (px >= x&&px <= x + w*graphzoom&&py >= y&&py <= y + h*graphzoom) {
					px -= x;
					py -= y;
					px *= graphzoom;
					py *= graphzoom;
					px += vx;
					py += vy;
					cur = nodes.head;
					while (cur) {
						if (px >= cur->data->x&&px <= cur->data->x + cur->data->w&&py >= cur->data->y&&py <= cur->data->y + cur->data->h) {
							if (cur->data->type->shape != 2)connect(sel, cur->data, sel->type->numout>1 && ((GetKeyState(VK_SHIFT) & 0x80)));
						}
						cur = cur->next;
					}
				}

				InvalidateRect(hwnd, NULL, 0);
			} else if (sel->type->shape == 3) {
				LLNode<WCGraphNode*>* cur;
				if (px >= x&&px <= x + w*graphzoom&&py >= y&&py <= y + h*graphzoom) {
					px -= x;
					py -= y;
					px *= graphzoom;
					py *= graphzoom;
					px += vx;
					py += vy;
					cur = nodes.head;
					while (cur) {
						if (cur->data != sel && px >= cur->data->x&&px <= cur->data->x + cur->data->w&&py >= cur->data->y&&py <= cur->data->y + cur->data->h) {
							if (!sel->in.find(cur->data) && cur->data->type->shape != 2 && cur->data->type->shape != 3) {

								if (MessageBox(hwnd, "Connect end to target?", "Confirm", MB_YESNO) == IDYES) {

									LLNode<WCGraphNode*>*find;
									LLNode<WCGraphNode*>*ins;


									ins = sel->in.head;
									while (ins) {
										find = ins->data->out.find(sel);

										if (find) {
											find->data = cur->data;
											cur->data->in.add(find->data);
										}
										ins = ins->next;
									}
									sel->in.clean();
									sel->out.clean();
									remove();

								}
							}
						}
						cur = cur->next;
					}
				}

				InvalidateRect(hwnd, NULL, 0);
			}
		}
	}

	void connect(WCGraphNode * a, WCGraphNode * b, bool prev = false) {

		if (a->out.size<a->type->numout || a->type->argtypes[0] == ARG_JUMP) {
			a->out.append(b);
			b->in.append(a);
		} else {
			a->out[a->type->numout - 1 - 1 * prev]->data->in.remove(a);
			a->out[a->type->numout - 1 - 1 * prev]->data = b;
			b->in.append(a);
		}
	}

	void removeIns() {
		if (!sel)return;
		LLNode<WCGraphNode*>*cur = sel->in.head;
		while (cur) {
			cur->data->out.remove(sel);
			cur = cur->next;
		}
		sel->in.clean();
	}

	void removeOuts() {
		if (!sel)return;
		LLNode<WCGraphNode*>*cur = sel->out.head;
		while (cur) {
			cur->data->in.remove(sel);
			cur = cur->next;
		}
		sel->out.clean();
	}

	void remove() {
		if (menu == 1) {
			return;
		}

		LLNode<WCGraphNode*>*cur;
		LLNode<WCGraphNode*>*find;

		if(sel && !selgroup.size) {
			if (sel->type->shape == 2)return;
			if (sel->selout) {
				cur = sel->out.head;
				while (cur) {
					cur->data->in.remove(sel);
					cur = cur->next;
				}
				cur = sel->in.head;
				while (cur) {
					if (cur->data->type->argtypes[0] == ARG_JUMP) {
						find = cur->data->out.find(sel);

						if (find) {
							addNode(sel->x - 28, sel->y, 1);
							find->data = nodes.head->data;
							find->data->in.add(cur->data);
							sel->x += 28;
						}
						cur = cur->next;
					} else {
						cur->data->out.remove(sel);
						cur = cur->next;
					}
				}
				sel->in.clean();
				sel->out.clean();
			} else {
				cur = sel->out.head;
				while (cur) {
					cur->data->in.remove(sel);
					cur = cur->next;
				}
				cur = sel->in.head;
				while (cur) {

					if (cur->data->type->argtypes[0] == ARG_JUMP) {
						find = cur->data->out.find(sel);

						if (find) {
							addNode(sel->x, sel->y, 1);
							find->data = nodes.head->data;
							find->data->in.add(cur->data);
						}
						cur = cur->next;
					} else {
						cur->data->out.remove(sel);
						cur = cur->next;
					}
				}
				nodes.remove(sel);
				delete sel;
				sel = 0;
			}
		}
		if (selgroup.size) {
			LLNode<WCGraphNode*>*cur2 = selgroup.head;

			while (cur2) {
				sel = cur2->data;
				LLNode<WCGraphNode*>*cur = sel->out.head;
				while (cur) {
					cur->data->in.remove(sel);
					cur = cur->next;
				}
				cur = sel->in.head;
				while (cur) {
					cur->data->out.remove(sel);
					cur = cur->next;
				}
				nodes.remove(sel);
				delete sel;

				cur2 = cur2->next;
			}

			selgroup.clean();
			sel = 0;
		}
	}
};