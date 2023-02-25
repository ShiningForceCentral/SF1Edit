
HBRUSH tb = 0;


if (subselect[mode][7] == 0)tb = (HBRUSH)SelectObject(memdc, CreateSolidBrush(RGB(180, 180, 180)));
RoundRect(memdc, 580, 12, 680, 40, 12, 12);
if (tb) { DeleteObject(SelectObject(memdc, tb));tb = 0; }

if (subselect[mode][7] == 1)tb = (HBRUSH)SelectObject(memdc, CreateSolidBrush(RGB(180, 180, 180)));
RoundRect(memdc, 680, 12, 780, 40, 12, 12);
if (tb) { DeleteObject(SelectObject(memdc, tb));tb = 0; }

if (subselect[mode][7] == 2)tb = (HBRUSH)SelectObject(memdc, CreateSolidBrush(RGB(180, 180, 180)));
RoundRect(memdc, 580, 40, 680, 68, 12, 12);
if (tb) { DeleteObject(SelectObject(memdc, tb));tb = 0; }

if (subselect[mode][7] == 3)tb = (HBRUSH)SelectObject(memdc, CreateSolidBrush(RGB(180, 180, 180)));
RoundRect(memdc, 680, 40, 780, 68, 12, 12);
if (tb) { DeleteObject(SelectObject(memdc, tb));tb = 0; }



sprintf(out, "Preview");
TextOut(memdc, 600, 18, out, strlen(out));

sprintf(out, "Setup");
TextOut(memdc, 700, 18, out, strlen(out));

sprintf(out, "Graphics");
TextOut(memdc, 600, 46, out, strlen(out));

sprintf(out, "Sequence");
TextOut(memdc, 700, 46, out, strlen(out));

int ux;
int uy=0,uh;

switch (subselect[mode][7]) {
case 0:
	SelectObject(bmpdc, minus);
	BitBlt(memdc, 645, 80, 20, 20, bmpdc, 0, 0, SRCCOPY);

	sprintf(out, "Character: %d", subselect[mode][1]);
	if (focus == 1 && cursor)sprintf(out, "%s|", out);
	TextOut(memdc, 666, 82, out, strlen(out));

	SelectObject(bmpdc, plus);
	BitBlt(memdc, 761, 80, 20, 20, bmpdc, 0, 0, SRCCOPY);

	SelectObject(bmpdc, minus);
	BitBlt(memdc, 645, 100, 20, 20, bmpdc, 0, 0, SRCCOPY);

	sprintf(out, "Enemy: %d", subselect[mode][3]);
	if (focus == 2 && cursor)sprintf(out, "%s|", out);
	TextOut(memdc, 666, 102, out, strlen(out));

	SelectObject(bmpdc, plus);
	BitBlt(memdc, 761, 100, 20, 20, bmpdc, 0, 0, SRCCOPY);

	SelectObject(bmpdc, minus);
	BitBlt(memdc, 645, 120, 20, 20, bmpdc, 0, 0, SRCCOPY);

	sprintf(out, "Platform: %d", subselect[mode][4]);
	if (focus == 3 && cursor)sprintf(out, "%s|", out);
	TextOut(memdc, 666, 122, out, strlen(out));

	SelectObject(bmpdc, plus);
	BitBlt(memdc, 761, 120, 20, 20, bmpdc, 0, 0, SRCCOPY);

	SelectObject(bmpdc, minus);
	BitBlt(memdc, 645, 140, 20, 20, bmpdc, 0, 0, SRCCOPY);

	sprintf(out, "BG: %d", subselect[mode][5]);
	if (focus == 4 && cursor)sprintf(out, "%s|", out);
	TextOut(memdc, 666, 142, out, strlen(out));

	SelectObject(bmpdc, plus);
	BitBlt(memdc, 761, 140, 20, 20, bmpdc, 0, 0, SRCCOPY);

	SelectObject(bmpdc, minus);
	BitBlt(memdc, 645, 160, 20, 20, bmpdc, 0, 0, SRCCOPY);

	sprintf(out, "BG2: %d", subselect[mode][6]);
	if (focus == 5 && cursor)sprintf(out, "%s|", out);
	TextOut(memdc, 666, 162, out, strlen(out));

	if (DrawBG2)SelectObject(bmpdc, checkon);
	else SelectObject(bmpdc, checkoff);
	BitBlt(memdc, 620, 164, 13, 13, bmpdc, 0, 0, SRCCOPY);

	SelectObject(bmpdc, plus);
	BitBlt(memdc, 761, 160, 20, 20, bmpdc, 0, 0, SRCCOPY);


	TextOut(memdc, 620, 240, "Show Outlines:", 14);

	if (AnimBorder)SelectObject(bmpdc, checkon);
	else SelectObject(bmpdc, checkoff);
	BitBlt(memdc, 720, 242, 13, 13, bmpdc, 0, 0, SRCCOPY);

	break;
case 1:
	sprintf(out, "Flicker Color: ");
	TextOut(memdc, 626, 82, out, strlen(out));

	tb = (HBRUSH)SelectObject(memdc, CreateSolidBrush(RGB(FlickerColor[select[mode]][0], FlickerColor[select[mode]][1], FlickerColor[select[mode]][2])));
	Rectangle(memdc,725, 83, 742, 99);
	DeleteObject(SelectObject(memdc, tb));

	uh = 52;
	uy = subselect[mode][8];

	for (int i = 0; i <= PSLen[select[mode]]; i++) {
		if (uy + 120 + uh + 80 > bheight + dheight)break;
		if (uy >= 0) {

			if (i == PSLen[select[mode]]) {
				SelectObject(bmpdc, plus);
				BitBlt(memdc, 626 - 9 - 40, uy + 147, 20, 20, bmpdc, 0, 0, SRCCOPY);
				continue;
			}

			tb = (HBRUSH)SelectObject(memdc, CreateSolidBrush(RGB(180, 180, 180)));
			RoundRect(memdc, 626, uy + 120, 778, uy + 120 + uh, 16, 16);
			DeleteObject(SelectObject(memdc, tb));

			tb = (HBRUSH)SelectObject(memdc, CreateSolidBrush(RGB(200, 200, 200)));
			RoundRect(memdc, 626, uy + 120, 778, uy + 120 + 20, 16, 16);
			DeleteObject(SelectObject(memdc, tb));

			sprintf(out, "%s", PaletteActions[PaletteScript[select[mode]][i][0]]);
			TextOut(memdc, 634, uy + 122, out, strlen(out));

			switch (PaletteScript[select[mode]][i][0]) {
			case 0://load
			case 1://save
				break;
			case 2://filter

				r.top = uy + 147;
				r.left = 642;
				r.bottom = uy + 147 + 13;
				r.right = 642 + 13;

				tb = CreateSolidBrush(RGB(255, 0, 0));
				FillRect(memdc, &r, tb);
				DeleteObject(tb);

				if (PaletteScript[select[mode]][i][1])SelectObject(bmpdc, checkon);
				else SelectObject(bmpdc, checkoff);
				BitBlt(memdc, 658, uy + 147, 13, 13, bmpdc, 0, 0, SRCCOPY);

				r.top = uy + 147;
				r.left = 688;
				r.bottom = uy + 147 + 13;
				r.right = 688 + 13;

				tb = CreateSolidBrush(RGB(0, 255, 0));
				FillRect(memdc, &r, tb);
				DeleteObject(tb);

				if (PaletteScript[select[mode]][i][2])SelectObject(bmpdc, checkon);
				else SelectObject(bmpdc, checkoff);
				BitBlt(memdc, 704, uy + 147, 13, 13, bmpdc, 0, 0, SRCCOPY);

				r.top = uy + 147;
				r.left = 734;
				r.bottom = uy + 147 + 13;
				r.right = 734 + 13;

				tb = CreateSolidBrush(RGB(0, 0, 255));
				FillRect(memdc, &r, tb);
				DeleteObject(tb);

				if (PaletteScript[select[mode]][i][3])SelectObject(bmpdc, checkon);
				else SelectObject(bmpdc, checkoff);
				BitBlt(memdc, 750, uy + 147, 13, 13, bmpdc, 0, 0, SRCCOPY);
				break;
			case 3://shift

				TextOut(memdc, 636, uy + 145, "Up", 2);

				if (PaletteScript[select[mode]][i][1])SelectObject(bmpdc, checkon);
				else SelectObject(bmpdc, checkoff);
				BitBlt(memdc, 663, uy + 147, 13, 13, bmpdc, 0, 0, SRCCOPY);

				TextOut(memdc, 700, uy + 145, "Stored", 6);

				if (PaletteScript[select[mode]][i][2])SelectObject(bmpdc, checkon);
				else SelectObject(bmpdc, checkoff);
				BitBlt(memdc, 750, uy + 147, 13, 13, bmpdc, 0, 0, SRCCOPY);

				break;
			case 4://cap
				TextOut(memdc, 636, uy + 145, "Up", 2);

				if (PaletteScript[select[mode]][i][1])SelectObject(bmpdc, checkon);
				else SelectObject(bmpdc, checkoff);
				BitBlt(memdc, 663, uy + 147, 13, 13, bmpdc, 0, 0, SRCCOPY);

				TextOut(memdc, 700, uy + 145, "Stored", 6);

				if (PaletteScript[select[mode]][i][2])SelectObject(bmpdc, checkon);
				else SelectObject(bmpdc, checkoff);
				BitBlt(memdc, 750, uy + 147, 13, 13, bmpdc, 0, 0, SRCCOPY);

				break;
			case 5://mix
				break;
			case 6://set
				r.top = uy + 147;
				r.left = 642;
				r.bottom = uy + 147 + 13;
				r.right = 642 + 13;

				tb = CreateSolidBrush(RGB(255, 0, 0));
				FillRect(memdc, &r, tb);
				DeleteObject(tb);

				if (PaletteScript[select[mode]][i][1])SelectObject(bmpdc, checkon);
				else SelectObject(bmpdc, checkoff);
				BitBlt(memdc, 658, uy + 147, 13, 13, bmpdc, 0, 0, SRCCOPY);

				r.top = uy + 147;
				r.left = 688;
				r.bottom = uy + 147 + 13;
				r.right = 688 + 13;

				tb = CreateSolidBrush(RGB(0, 255, 0));
				FillRect(memdc, &r, tb);
				DeleteObject(tb);

				if (PaletteScript[select[mode]][i][2])SelectObject(bmpdc, checkon);
				else SelectObject(bmpdc, checkoff);
				BitBlt(memdc, 704, uy + 147, 13, 13, bmpdc, 0, 0, SRCCOPY);

				r.top = uy + 147;
				r.left = 734;
				r.bottom = uy + 147 + 13;
				r.right = 734 + 13;

				tb = CreateSolidBrush(RGB(0, 0, 255));
				FillRect(memdc, &r, tb);
				DeleteObject(tb);

				if (PaletteScript[select[mode]][i][3])SelectObject(bmpdc, checkon);
				else SelectObject(bmpdc, checkoff);
				BitBlt(memdc, 750, uy + 147, 13, 13, bmpdc, 0, 0, SRCCOPY);
				break;
			case 7://clear
				break;
			case 8://add
				r.top = uy + 147;
				r.left = 642;
				r.bottom = uy + 147 + 13;
				r.right = 642 + 13;

				tb = CreateSolidBrush(RGB(255, 0, 0));
				FillRect(memdc, &r, tb);
				DeleteObject(tb);

				if (PaletteScript[select[mode]][i][1])SelectObject(bmpdc, checkon);
				else SelectObject(bmpdc, checkoff);
				BitBlt(memdc, 658, uy + 147, 13, 13, bmpdc, 0, 0, SRCCOPY);

				r.top = uy + 147;
				r.left = 688;
				r.bottom = uy + 147 + 13;
				r.right = 688 + 13;

				tb = CreateSolidBrush(RGB(0, 255, 0));
				FillRect(memdc, &r, tb);
				DeleteObject(tb);

				if (PaletteScript[select[mode]][i][2])SelectObject(bmpdc, checkon);
				else SelectObject(bmpdc, checkoff);
				BitBlt(memdc, 704, uy + 147, 13, 13, bmpdc, 0, 0, SRCCOPY);

				r.top = uy + 147;
				r.left = 734;
				r.bottom = uy + 147 + 13;
				r.right = 734 + 13;

				tb = CreateSolidBrush(RGB(0, 0, 255));
				FillRect(memdc, &r, tb);
				DeleteObject(tb);

				if (PaletteScript[select[mode]][i][3])SelectObject(bmpdc, checkon);
				else SelectObject(bmpdc, checkoff);
				BitBlt(memdc, 750, uy + 147, 13, 13, bmpdc, 0, 0, SRCCOPY);
				break;
			case 9://reduce
				r.top = uy + 147;
				r.left = 642;
				r.bottom = uy + 147 + 13;
				r.right = 642 + 13;

				tb = CreateSolidBrush(RGB(255, 0, 0));
				FillRect(memdc, &r, tb);
				DeleteObject(tb);

				if (PaletteScript[select[mode]][i][1]==0)SelectObject(bmpdc, checkon);
				else SelectObject(bmpdc, checkoff);
				BitBlt(memdc, 658, uy + 147, 13, 13, bmpdc, 0, 0, SRCCOPY);

				r.top = uy + 147;
				r.left = 688;
				r.bottom = uy + 147 + 13;
				r.right = 688 + 13;

				tb = CreateSolidBrush(RGB(0, 255, 0));
				FillRect(memdc, &r, tb);
				DeleteObject(tb);

				if (PaletteScript[select[mode]][i][1]==1)SelectObject(bmpdc, checkon);
				else SelectObject(bmpdc, checkoff);
				BitBlt(memdc, 704, uy + 147, 13, 13, bmpdc, 0, 0, SRCCOPY);

				r.top = uy + 147;
				r.left = 734;
				r.bottom = uy + 147 + 13;
				r.right = 734 + 13;

				tb = CreateSolidBrush(RGB(0, 0, 255));
				FillRect(memdc, &r, tb);
				DeleteObject(tb);

				if (PaletteScript[select[mode]][i][1]==2)SelectObject(bmpdc, checkon);
				else SelectObject(bmpdc, checkoff);
				BitBlt(memdc, 750, uy + 147, 13, 13, bmpdc, 0, 0, SRCCOPY);
				break;
			case 10://duplicate
				break;
			case 11://mul/div
				sprintf(out, "Val: %d", PaletteScript[select[mode]][i][2]);
				if (focus == 1 && subfocus == i && cursor)sprintf(out, "%s|", out);
				TextOut(memdc, 636, uy + 145, out, strlen(out));

				TextOut(memdc, 700, uy + 145, "Divide", 6);

				if (PaletteScript[select[mode]][i][1])SelectObject(bmpdc, checkon);
				else SelectObject(bmpdc, checkoff);
				BitBlt(memdc, 750, uy + 147, 13, 13, bmpdc, 0, 0, SRCCOPY);

				break;
			}

			SelectObject(bmpdc, deleteicon);
			BitBlt(memdc, 626 - 8 - 40, uy + 124, 20, 20, bmpdc, 0, 0, SRCCOPY);

			if (i) {
				SelectObject(bmpdc, uparrow);
				BitBlt(memdc, 626 - 4 - 20, uy + 124, 20, 20, bmpdc, 0, 0, SRCCOPY);
			}

			SelectObject(bmpdc, plus);
			BitBlt(memdc, 626 - 9 - 40, uy + 147, 20, 20, bmpdc, 0, 0, SRCCOPY);

			if (i < PSLen[select[mode]] - 1) {
				SelectObject(bmpdc, downarrow);
				BitBlt(memdc, 626 - 4 - 20, uy + 148, 20, 20, bmpdc, 0, 0, SRCCOPY);
			}
		}

		uy += uh + 6;
	}

	SelectObject(bmpdc, uparrow);
	BitBlt(memdc, 670, bheight + dheight - 70, 20, 20, bmpdc, 0, 0, SRCCOPY);

	SelectObject(bmpdc, downarrow);
	BitBlt(memdc, 700, bheight + dheight - 70, 20, 20, bmpdc, 0, 0, SRCCOPY);

	uy = subselect[mode][8];

	if(menu==1)
	for (int i = 0; i < PSLen[select[mode]]; i++) {
		if (uy >= 0) {
			if (submenu == i) {

				if (uy + 160 + 12 * 20 <= bheight + dheight) {
					tb = (HBRUSH)SelectObject(memdc, CreateSolidBrush(RGB(200, 200, 200)));
					RoundRect(memdc, 626, uy + 120, 778, uy + 120 + 12 * 20, 16, 16);
					DeleteObject(SelectObject(memdc, tb));

					for (int j = 0; j < 12; j++) {
						if(PaletteScript[select[mode]][i][0]==j)
							RoundRect(memdc, 626, uy + 120 + 20 * j, 778, uy + 140 + 20 * j, 16, 16);

						sprintf(out, "%s", PaletteActions[j]);
						TextOut(memdc, 634, uy + 122 + 20 * j, out, strlen(out));
					}
				} else {
					tb = (HBRUSH)SelectObject(memdc, CreateSolidBrush(RGB(200, 200, 200)));
					RoundRect(memdc, 626, bheight + dheight - 40 - 12*20, 778, bheight + dheight - 40, 16, 16);
					DeleteObject(SelectObject(memdc, tb));

					for (int j = 0; j < 12; j++) {
						if (PaletteScript[select[mode]][i][0] == j)
							RoundRect(memdc, 626, bheight + dheight - 40 - 12 * 20 + 20 * j, 778, bheight + dheight - 20 - 12 * 20 + 20 * j, 16, 16);

						sprintf(out, "%s", PaletteActions[j]);
						TextOut(memdc, 634, bheight + dheight - 40 - 12 * 20 + 2 + 20 * j, out, strlen(out));
					}
				}
			}

		}
		uy += uh + 6;
	}

	break;
case 2:
	m = select[mode];
	width = SAGFXSize[m][0];
	height = SAGFXSize[m][1];

	for (x = 0; x<width; x++) {
		for (y = 0; y<height; y++) {
			for (i = 0; i<2; i++) {
				for (j = 0; j<2; j++) {
					k = SpellAnimGFX[m][x + y*width];
					if (k<0)k = 0;
					SetPixel(memdc, x * 2 + i + 82, y * 2 + j + 67, RGB(SpellAnimPal[m][k][0], SpellAnimPal[m][k][1], SpellAnimPal[m][k][2]));
				}
			}
		}
	}

	for (i = 0;i<5;i++) {
		for (int dx = 0;dx<18;dx++) {
			for (int dy = 0;dy<18;dy++) {
				SetPixel(memdc, 90 + 18 * i + dx, 40 + dy, RGB(SpellAnimPal[m][i+6][0], SpellAnimPal[m][i+6][1], SpellAnimPal[m][i+6][2]));
			}
		}
	}

	TextOut(memdc, 90 + 18 * 6, 40, "(Right Click to Edit Color)", 27);

	POINT p = NtoXY((unsigned char)AnimGFX[select[mode]][subselect[mode][9]][2], height/8);
	
	SelectObject(bmpdc, minus);
	BitBlt(memdc, 615, 80, 20, 20, bmpdc, 0, 0, SRCCOPY);

	sprintf(out, "Piece: %d", subselect[mode][9]);
	if (focus == 1 && cursor)sprintf(out, "%s|", out);
	TextOut(memdc, 636, 82, out, strlen(out));

	SelectObject(bmpdc, plus);
	BitBlt(memdc, 731, 80, 20, 20, bmpdc, 0, 0, SRCCOPY);

	TextOut(memdc, 636, 122, "X Offset:", 9);
	sprintf(out, "%d", AnimGFX[select[mode]][subselect[mode][9]][0]);
	if (focus == 2 && cursor)sprintf(out, "%s|", out);
	TextOut(memdc, 716, 122, out, strlen(out));

	TextOut(memdc, 636, 142, "Y Offset:", 9);
	sprintf(out, "%d", AnimGFX[select[mode]][subselect[mode][9]][1]);
	if (focus == 3 && cursor)sprintf(out, "%s|", out);
	TextOut(memdc, 716, 142, out, strlen(out));
	
	TextOut(memdc, 636, 162, "Start Tile:", 11);
	sprintf(out, "%d", (unsigned char)AnimGFX[select[mode]][subselect[mode][9]][2]);
	if (focus == 4 && cursor)sprintf(out, "%s|", out);
	TextOut(memdc, 716, 162, out, strlen(out));

	int cw,ch;
	cw = (AnimGFX[select[mode]][subselect[mode][9]][3] & 0x03) + 1;
	ch = (AnimGFX[select[mode]][subselect[mode][9]][3] & 0x0C) / 4 + 1;

	TextOut(memdc, 636, 182, "Width:", 6);
	sprintf(out, "%d", cw);
	if (focus == 5 && cursor)sprintf(out, "%s|", out);
	TextOut(memdc, 716, 182, out, strlen(out));

	TextOut(memdc, 636, 202, "Height:", 7);
	sprintf(out, "%d", ch);
	if (focus == 6 && cursor)sprintf(out, "%s|", out);
	TextOut(memdc, 716, 202, out, strlen(out));

	TextOut(memdc, 636, 222, "Flip X:", 7);
	if (AnimGFX[select[mode]][subselect[mode][9]][4] & 0x01)SelectObject(bmpdc, checkon);
	else SelectObject(bmpdc, checkoff);
	BitBlt(memdc, 716, 223, 13, 13, bmpdc, 0, 0, SRCCOPY);

	TextOut(memdc, 636, 242, "Flip Y:", 7);
	if (AnimGFX[select[mode]][subselect[mode][9]][4] & 0x02)SelectObject(bmpdc, checkon);
	else SelectObject(bmpdc, checkoff);
	BitBlt(memdc, 716, 243, 13, 13, bmpdc, 0, 0, SRCCOPY);

	if (NumAnimGFX[select[mode]] < 64) {
		Rectangle(memdc, 585, 268, 675, 318);
		TextOut(memdc, 617, 274, "Add", 3);
		TextOut(memdc, 611, 294, "Piece", 5);
	}
	if (NumAnimGFX[select[mode]] > 0) {
		Rectangle(memdc, 685, 268, 775, 318);
		TextOut(memdc, 704, 274, "Remove", 6);
		TextOut(memdc, 712, 294, "Piece", 5);
	}

	DrawChunkSource(memdc, 82, 67, RGB(0, 0, 0), cw, ch, 8*p.x, 8*p.y, width, height, 2);

	DrawChunk(memdc, 600 + 16 * (4 - cw), 400 + 16 * (4 - ch), SpellAnimGFX[m], SpellAnimPal[m], cw, ch, 8 * p.x, 8 * p.y, width, height, 4, AnimGFX[select[mode]][subselect[mode][9]][4] & 0x01, AnimGFX[select[mode]][subselect[mode][9]][4] & 0x02);
	break;
case 3:
	SpellAnimScript[select[mode]].animate();
	break;
}

if (subselect[mode][7] < 2) {
	int frame = 0;

	ux = 60;
	uy = 40;

	r.top = uy - 1;
	r.left = ux - 1;
	r.right = ux + 512 - 1;
	r.bottom = uy + 448 - 1;


	int bg = subselect[mode][5];
	int bg2 = subselect[mode][6];
	int fs = subselect[mode][1];
	int es = subselect[mode][3];
	int pf = subselect[mode][4];

	int fsf = 0;

	if (!TempPalReady) {
		if (SpellFrame < 12 || SpellFrame>52)restorePals(bg, bg2, pf, fs, es);
		else {
			//redPals(bg, bg2, pf, fs, es);
			restorePals(bg, bg2, pf, fs, es);
			runPaletteScript(PaletteScript[select[mode]], PSLen[select[mode]]);
		}
	}
	if (subframe != LastFrame) {
		SpellFrame++;
		SpellFrame %= 64;

		if (SpellFrame == 52 || LastFrame == -1)restorePals(bg, bg2, pf, fs, es);
		if (SpellFrame == 12) {
			//redPals(bg, bg2, pf, fs, es);
			restorePals(bg, bg2, pf, fs, es);
			runPaletteScript(PaletteScript[select[mode]], PSLen[select[mode]]);
		}

		LastFrame = subframe;
	}

	if (SpellFrame > 3 && SpellFrame < 8)fsf = 3;
	if (SpellFrame > 7 && SpellFrame < 52)fsf = 2;


	if (SpellFrame >= 12 && SpellFrame < 48) {

		frame = SpellFrame - 12;
		frame = frame - frame % 5;
		frame /= 5;

		if (frame % 2 == 0)tb = CreateSolidBrush(RGB(FlickerColor[select[mode]][0], FlickerColor[select[mode]][1], FlickerColor[select[mode]][2]));
		else tb = CreateSolidBrush(RGB(0, 0, 0));
	} else
		tb = CreateSolidBrush(RGB(0, 0, 0));

	FillRect(memdc, &r, tb);


	DeleteObject(tb);


	HPEN old = (HPEN)SelectObject(memdc, CreatePen(PS_NULL, 0, 0));

	//bg


	m = bg * 2;
	l = 0;

	width = BGSize[m][0];
	height = BGSize[m][1];

	for (x = 0;x < width;x++) {
		for (y = 0;y < height;y++) {
			//for (i = 0;i<2;i++) {
				//for (j = 0;j<2;j++) {
			k = Backgrounds[m][x + y*width];
			if (k < 0)k = 0;

			tb = (HBRUSH)SelectObject(memdc, CreateSolidBrush(RGB(TempBGPalette[k][0], TempBGPalette[k][1], TempBGPalette[k][2])));

			Rectangle(memdc, ux + x * 2 + 256 - 1, uy + y * 2 + 100 - 1, ux + x * 2 + 256 + 2, uy + y * 2 + 100 + 2);

			//SetPixel(memdc, ux + x * 2 + i + 256, uy + y * 2 + j + 110, RGB(TempBGPalette[k][0], TempBGPalette[k][1], TempBGPalette[k][2]));

			k = Backgrounds[m + 1][x + y*width];
			if (k < 0)k = 0;

			DeleteObject(SelectObject(memdc, CreateSolidBrush(RGB(TempBGPalette[k][0], TempBGPalette[k][1], TempBGPalette[k][2]))));

			Rectangle(memdc, ux + x * 2 - 1, uy + y * 2 + 100 - 1, ux + x * 2 + 2, uy + y * 2 + 100 + 2);

			//SetPixel(memdc, ux + x * 2 + i, uy + y * 2 + j + 110, RGB(TempBGPalette[k][0], TempBGPalette[k][1], TempBGPalette[k][2]));
			DeleteObject(SelectObject(memdc, tb));
			//}
		//}
		}
	}

	if (DrawBG2) {
		m = bg2 * 2;
		l = 0;

		width = BGSize[m][0];
		height = BGSize[m][1];

		for (x = 0; x < width; x++) {
			for (y = 0; y < height; y++) {
				//for (i = 0;i<2;i++) {
				//	for (j = 0;j<2;j++) {
				k = Backgrounds[m][x + y*width];
				if (k < 0)k = 0;

				if (k) {
					tb = (HBRUSH)SelectObject(memdc, CreateSolidBrush(RGB(TempBGPalette2[k][0], TempBGPalette2[k][1], TempBGPalette2[k][2])));
					Rectangle(memdc, ux + x * 2 + 256 - 1, uy + y * 2 + 100 - 1, ux + x * 2 + 256 + 2, uy + y * 2 + 100 + 2);
					DeleteObject(SelectObject(memdc, tb));
					//SetPixel(memdc, ux + x * 2 + i + 256, uy + y * 2 + j + 110, RGB(TempBGPalette2[k][0], TempBGPalette2[k][1], TempBGPalette2[k][2]));
				}

				k = Backgrounds[m + 1][x + y*width];
				if (k < 0)k = 0;

				if (k) {
					tb = (HBRUSH)SelectObject(memdc, CreateSolidBrush(RGB(TempBGPalette2[k][0], TempBGPalette2[k][1], TempBGPalette2[k][2])));
					Rectangle(memdc, ux + x * 2 - 1, uy + y * 2 + 100 - 1, ux + x * 2 + 2, uy + y * 2 + 100 + 2);
					DeleteObject(SelectObject(memdc, tb));
					//SetPixel(memdc, ux + x * 2 + i, uy + y * 2 + j + 110, RGB(TempBGPalette2[k][0], TempBGPalette2[k][1], TempBGPalette2[k][2]));
				}
				//}
			//}
			}
		}
	}

	m = pf;

	width = PFSize[m][0];
	height = PFSize[m][1];

	for (x = 0;x < width;x++) {
		for (y = 0;y < height;y++) {
			//for (i = 0;i<2;i++) {
			//	for (j = 0;j<2;j++) {
			k = Platforms[m][x + y*width];
			if (k < 0)k = 0;
			if (k) {
				tb = (HBRUSH)SelectObject(memdc, CreateSolidBrush(RGB(TempPFPalette[k][0], TempPFPalette[k][1], TempPFPalette[k][2])));
				Rectangle(memdc, ux + x * 2 + 256 - 1, uy + y * 2 + 268 - 1, ux + x * 2 + 256 + 2, uy + y * 2 + 268 + 2);
				DeleteObject(SelectObject(memdc, tb));

				//SetPixel(memdc, ux + x * 2 + i + 256, ux + y * 2 + j + 240, RGB(TempPFPalette[k][0], TempPFPalette[k][1], TempPFPalette[k][2]));
			}
			//	}
			//}
		}
	}

	m = es;
	l = 0;
	frame = 0;

	width = ESSize[m][frame][0];
	height = ESSize[m][frame][1];

	for (x = 0;x < width;x++) {
		for (y = 0;y < height;y++) {
			//for (i = 0;i<2;i++) {
			//	for (j = 0;j<2;j++) {
			k = EnemySprites[m][frame][x + y*width];
			if (k < 0)k = 0;

			if (k) {
				tb = (HBRUSH)SelectObject(memdc, CreateSolidBrush(RGB(TempESPalette[k][0], TempESPalette[k][1], TempESPalette[k][2])));
				Rectangle(memdc, ux + x * 2 + 32 - 1, uy + y * 2 + 94 - 1, ux + x * 2 + 32 + 2, uy + y * 2 + 94 + 2);
				DeleteObject(SelectObject(memdc, tb));

				//SetPixel(memdc, ux + x * 2 + i + 32, uy + y * 2 + j + 94, RGB(TempESPalette[k][0], TempESPalette[k][1], TempESPalette[k][2]));
			}
			//	}
			//}
		}
	}

	m = fs;
	l = 0;
	frame = fsf;

	width = FSSize[m][frame][0];
	height = FSSize[m][frame][1];

	//force
	for (x = 0;x < width;x++) {
		for (y = 0;y < height;y++) {
			//for (i = 0;i<2;i++) {
			//	for (j = 0;j<2;j++) {
			k = ForceSprites[m][frame][x + y*width];
			if (k < 0)k = 0;

			if (k) {
				tb = (HBRUSH)SelectObject(memdc, CreateSolidBrush(RGB(TempFSPalette[k][0], TempFSPalette[k][1], TempFSPalette[k][2])));
				Rectangle(memdc, ux + x * 2 + 272 - 1, uy + y * 2 + 116 - 1, ux + x * 2 + 272 + 2, uy + y * 2 + 116 + 2);
				DeleteObject(SelectObject(memdc, tb));

				//SetPixel(memdc, ux + x * 2 + i + 272, uy + y * 2 + j + 128, RGB(TempFSPalette[k][0], TempFSPalette[k][1], TempFSPalette[k][2]));
			}
			//	}
			//}
		}
	}


	if (SpellFrame >= 12 && SpellFrame < 48) {
		int f = ((SpellFrame - 12) - (SpellFrame - 12) % 4) / 4;

		m = select[mode];

		//DrawChunk(memdc, ux + 120 + 4 * 2, uy + 192 + 16 * 2, SpellAnimGFX[m], SpellAnimPal[m], 4, 3, 0, 0, 8 * 12, 8 * 16, 2, 0, 0);

		
		switch (f % 4) {
		case 0:
		case 1:
			DrawChunk(memdc, ux + 120 + 4 * 2, uy + 192 + 16 * 2, SpellAnimGFX[m], SpellAnimPal[m], 2, 2, 88, 64, 8 * 12, 8 * 16, 2, f % 2 == 1);
			DrawChunk(memdc, ux + 120 + 4 * 2, uy + 192 + 32 * 2, SpellAnimGFX[m], SpellAnimPal[m], 2, 2, 64, 96, 8 * 12, 8 * 16, 2, f % 2 == 1);
			break;
		case 2:
		case 3:
			DrawChunk(memdc, ux + 120, uy + 192,			 SpellAnimGFX[m], SpellAnimPal[m], 3, 3, 80, 48, 8 * 12, 8 * 16, 2, f % 2 == 1);
			DrawChunk(memdc, ux + 120, uy + 192 + 3 * 8 * 2, SpellAnimGFX[m], SpellAnimPal[m], 3, 3, 64, 88, 8 * 12, 8 * 16, 2, f % 2 == 1);
			break;
		}
	}

	DeleteObject(SelectObject(memdc, old));
}