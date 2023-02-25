struct ScriptItemType {
	COLORREF color;
	int type;
};

LinkedList<ScriptItemType*> ScriptTypes;

struct ScriptItem {
	ScriptItemType * type;
	char label[32];

	ScriptItem(ScriptItemType * t, char * l) {
		type = t;
		sprintf(label, l);
	}
};

struct ScriptLine {
	LinkedList<ScriptItem *> items;

	
	void animate(int x, int y) {
		int dx = 0;
		LLNode<ScriptItem *> * cur = items.head;

		while (cur) {
			RoundRect(memdc, x + dx, y, x + dx + 100, y + 20, 12, 12);
			TextOut(memdc, x + dx + 3, y + 2, cur->data->label, strlen(cur->data->label));

			dx += 100;
			cur = cur->next;
		}
	}
};

struct ScriptFunction {
	char label[32];
	LinkedList<ScriptLine *> lines;
	bool collapsed;

	ScriptFunction(char * l) {
		collapsed = false;
		sprintf(label, l);
	}
};

struct ScriptContainer{
	LinkedList<ScriptFunction *> functions;
	int x, y, h, w;

	ScriptContainer() {
		x = 50;
		y = 10;
		h = maxy - 10;
		w = 500;
	}

	void animate() {
		int i = 0;
		int ind = 0;


		char out[256];

		LLNode<ScriptFunction*> * cur = functions.head;
		while (cur) {

			if (i % 2) {
				HPEN tp = (HPEN)SelectObject(memdc, GetStockObject(NULL_PEN));
				HBRUSH tb = (HBRUSH)SelectObject(memdc, CreateSolidBrush(RGB(140, 140, 140)));

				Rectangle(memdc, x, y+ i * 20, x+w, y+(i+1)*20);

				SelectObject(memdc, tp);
				DeleteObject(SelectObject(memdc, tb));
			}

			sprintf(out, "function %s( )", cur->data->label);
			TextOut(memdc, x + 24, y + i * 20 + 2, out , strlen(out));

			if (cur->data->collapsed) {
				SelectObject(bmpdc, plus);
				BitBlt(memdc, x, y + i * 20, 20, 20, bmpdc, 0, 0, SRCCOPY);
				i++;
			} else {
				SelectObject(bmpdc, minus);
				BitBlt(memdc, x, y + i * 20, 20, 20, bmpdc, 0, 0, SRCCOPY);
				i++;
				ind++;

				LLNode<ScriptLine*> * curline = cur->data->lines.head;
				while (curline) {


					if (i % 2) {
						HPEN tp = (HPEN)SelectObject(memdc, GetStockObject(NULL_PEN));
						HBRUSH tb = (HBRUSH)SelectObject(memdc, CreateSolidBrush(RGB(140, 140, 140)));

						Rectangle(memdc, x, y + i * 20, x + w, y + (i + 1) * 20);

						SelectObject(memdc, tp);
						DeleteObject(SelectObject(memdc, tb));
					}

					curline->data->animate(x + ind * 25, y + i * 20);

					curline = curline->next;
					i++;

				}
			}

			ind = 0;


			cur = cur->next;
		}
	}

	void click(POINT p) {
		int i = 0;
		int ind = 0;

		LLNode<ScriptFunction*> * cur = functions.head;
		while (cur) {

			if (p.x >= x && p.x <= x + 20 && p.y >= y + i * 20 && p.y <= y + i * 20 + 20) {
				cur->data->collapsed = !cur->data->collapsed;
			}

			if (cur->data->collapsed) {

			} else {

			}

			ind = 0;

			i++;
			cur = cur->next;
		}


	}
};