if (submode[mode] == 0) {
	HBRUSH tb;
	SelectObject(bmpdc, plus);
	BitBlt(memdc, 4, 10, 20, 20, bmpdc, 0, 0, SRCCOPY);
	SelectObject(bmpdc, minus);
	BitBlt(memdc, 4, 34, 20, 20, bmpdc, 0, 0, SRCCOPY);

	Rectangle(memdc, 50, 10 + 16 * (select[mode] % 30), 130, 25 + 16 * (select[mode] % 30));

	for (i = 0; i < 30 && (i + subselect[mode][0] < NumRanges); i++) {
		sprintf(out, "Range %d", i + subselect[mode][0]);
		TextOut(memdc, 50, 10 + 16 * i, out, strlen(out));
	}
	if (NumRanges > 30) {
		SelectObject(bmpdc, uparrow);
		BitBlt(memdc, 50, 520, 20, 20, bmpdc, 0, 0, SRCCOPY);
		SelectObject(bmpdc, downarrow);
		BitBlt(memdc, 73, 520, 20, 20, bmpdc, 0, 0, SRCCOPY);
	}

	RoundRect(memdc, 150, 23, 545, 222, 12, 12);
	RoundRect(memdc, 565, 23, 765, 222, 12, 12);

	RoundRect(memdc, 150, 234, 765, 536, 12, 12);

	SetBkMode(memdc, OPAQUE);
	SetBkColor(memdc, RGB(128, 128, 128));

	TextOut(memdc, 307, 15, " RANGE DATA ", 12);
	TextOut(memdc, 625, 15, " SETTINGS ", 10);
	
	if (RangePreview)
		TextOut(memdc, 428, 226, " PREVIEW ", 9);
	else
		TextOut(memdc, 428, 226, " USED BY ", 9);


	SetBkMode(memdc, TRANSPARENT);
	SetBkColor(memdc, RGB(255, 255, 255));

	TextOut(memdc, 590, 32, "Show Preview:", 13);
	if (RangePreview)SelectObject(bmpdc, checkon);
	else SelectObject(bmpdc, checkoff);
	BitBlt(memdc, 690, 34, 13, 13, bmpdc, 0, 0, SRCCOPY);

	TextOut(memdc, 590, 52, "Show Uses:", 10);
	if (!RangePreview)SelectObject(bmpdc, checkon);
	else SelectObject(bmpdc, checkoff);
	BitBlt(memdc, 690, 54, 13, 13, bmpdc, 0, 0, SRCCOPY);

	TextOut(memdc, 590, 72, "Maximum Range:", 14);

	sprintf(out, "%d", MaxRange);
	if (focus == 10 && cursor)sprintf(out, "%s|", out);
	TextOut(memdc, 710, 72, out, strlen(out));


	TextOut(memdc, 590, 92, "Advanced Ranges:", 16);
	if (ExtendRange)SelectObject(bmpdc, checkon);
	else SelectObject(bmpdc, checkoff);
	BitBlt(memdc, 720, 94, 13, 13, bmpdc, 0, 0, SRCCOPY);
	
	
	if (ExtendRange) {
		TextOut(memdc, 590, 112, "Advanced Areas:", 15);
		if (ExtendArea)SelectObject(bmpdc, checkon);
		else SelectObject(bmpdc, checkoff);
		BitBlt(memdc, 720, 114, 13, 13, bmpdc, 0, 0, SRCCOPY);
	}

	if (NumRanges) {
		TextOut(memdc, 220, 32, "Minimum:", 8);

		sprintf(out, "%d", Range[select[mode]][1]);
		if (focus == 1 && cursor)sprintf(out, "%s|", out);
		TextOut(memdc, 300, 32, out, strlen(out));

		TextOut(memdc, 220, 52, "Maximum:", 8);
		sprintf(out, "%d", Range[select[mode]][0] & 0x0F);
		if (focus == 2 && cursor)sprintf(out, "%s|", out);
		TextOut(memdc, 300, 52, out, strlen(out));

		if (ExtendRange) {
			TextOut(memdc, 220, 72, "Shape:", 6);

			tb = (HBRUSH)SelectObject(memdc, CreateSolidBrush(RGB(180, 180, 180)));
			RoundRect(memdc, 300, 70, 450, 90, 10, 10);
			DeleteObject(SelectObject(memdc, tb));

			RangeShape = (Range[select[mode]][0] & 0xF0) / 0x10;

			if (RangeShape >= 0 && RangeShape < 8)
				TextOut(memdc, 306, 72, RangeShapes[RangeShape], strlen(RangeShapes[RangeShape]));
		}


		TextOut(memdc, 220, 92, "Area:", 5);

		tb = (HBRUSH)SelectObject(memdc, CreateSolidBrush(RGB(180, 180, 180)));
		RoundRect(memdc, 300, 90, 450, 110, 10, 10);
		DeleteObject(SelectObject(memdc, tb));

		RangeArea = Range[select[mode]][2];

		switch (RangeArea) {
		case 0:
		case 1:
		case 2:
		case 3:
		case 4:
			RangeArea = RangeArea;
			break;
		case 130:
			RangeArea = 2;
			break;
		case 29:
		case 30:
		case 31:
		case 32:
			RangeArea = RangeArea - 24;
			break;
		default:
			RangeArea = -1;
			break;
		}

		if (RangeArea != 0xFF)TextOut(memdc, 306, 92, AreaShapes[RangeArea], strlen(AreaShapes[RangeArea]));

		TextOut(memdc, 220, 112, "Group:", 6);

		tb = (HBRUSH)SelectObject(memdc, CreateSolidBrush(RGB(180, 180, 180)));
		RoundRect(memdc, 300, 110, 450, 130, 10, 10);
		DeleteObject(SelectObject(memdc, tb));

		if (Range[select[mode]][3] >= 0 && Range[select[mode]][3] < 8)
			TextOut(memdc, 306, 112, RangeGroups[Range[select[mode]][3]], strlen(RangeGroups[Range[select[mode]][3]]));



		lo = 0x23178 + (select[mode]) * 8 + 6;
		sh = Range[select[mode]][6] * 256 + Range[select[mode]][7];
		lo += sh;


		RangeRoutine = -1;
		for (int i = 0; i < NUM_RANGE_ROUTINES; i++) {
			if (RangeRoutineOffsets[i] == lo) {
				RangeRoutine = i;
				break;
			}
		}

		TextOut(memdc, 220, 132, "Routine:", 8);

		tb = (HBRUSH)SelectObject(memdc, CreateSolidBrush(RGB(180, 180, 180)));
		RoundRect(memdc, 300, 130, 500, 150, 10, 10);
		DeleteObject(SelectObject(memdc, tb));

		if (RangeRoutine != 0xFF)
			TextOut(memdc, 306, 132, RangeRoutines[RangeRoutine], strlen(RangeRoutines[RangeRoutine]));
	}

	

	int ux;
	int uy;

	int delx,dely;

	int rf;

	if (NumRanges && RangePreview) {

		SelectObject(bmpdc, areas);

		ux = 595;
		uy = 370;

		switch (mainframe/2 % 8) {
			case 0:
				delx = 0;
				dely = -1;
				break;
			case 1:
				delx = 1;
				dely = -1;
				break;
			case 2:
				delx = 1;
				dely = 0;
				break;
			case 3:
				delx = 1;
				dely = 1;
				break;
			case 4:
				delx = 0;
				dely = 1;
				break;
			case 5:
				delx = -1;
				dely = 1;
				break;
			case 6:
				delx = -1;
				dely = 0;
				break;
			case 7:
				delx = -1;
				dely = -1;
				break;
		}

		switch (mainframe % 8) {
			case 0:
				rf = 0;
				break;
			case 1:
				rf = 1;
				break;
			case 2:
				rf = 2;
				break;
			case 3:
				rf = 3;
				break;
			case 4:
				rf = 3;
				break;
			case 5:
				rf = 2;
				break;
			case 6:
				rf = 1;
				break;
			case 7:
				rf = 0;
				break;
		}

		for (int dx = -4; dx <= 4; dx++) {
			for (int dy = -4; dy <= 4; dy++) {
				BitBlt(memdc, ux + dx*32, uy + dy * 32, 32, 32, bmpdc, 32, 0, SRCCOPY);
			}
		}

		auto DrawSprite = [](int xstart, int ystart, int group, int index) {
			int width, height, x, y,k;
			if (GraphicsLoaded && group>0 && group != 4) {
				width = MSSize[0][0][0];
				height = MSSize[0][0][1];

				for (x = 0; x < width / 2; x++) {
					for (y = 0; y < height; y++) {
						switch (group) {
						case 1:
							k = MapSprites[0+index][0][x + 24 * cursor + y*width];
							if (k < 0)k = 0;
							if (k)SetPixel(memdc, x + xstart + 4, y + ystart + 4, RGB(FMSPalette[k][0], FMSPalette[k][1], FMSPalette[k][2]));
							break;
						case 2:
							k = MapSprites[60 + index][0][x + 24 * cursor + y*width];
							if (k < 0)k = 0;
							if (k)SetPixel(memdc, x + xstart + 4, y + ystart + 4, RGB(EMSPalette[k][0], EMSPalette[k][1], EMSPalette[k][2]));
							break;
						case 3:
							if (x < width / 4) {
								k = MapSprites[0 + index][0][x + 24 * cursor + y*width];
								if (k < 0)k = 0;
								if (k)SetPixel(memdc, x + xstart + 4, y + ystart + 4, RGB(FMSPalette[k][0], FMSPalette[k][1], FMSPalette[k][2]));
							} else {
								k = MapSprites[60 + index][0][x + 24 * cursor + y*width];
								if (k < 0)k = 0;
								if (k)SetPixel(memdc, x + xstart + 4, y + ystart + 4, RGB(EMSPalette[k][0], EMSPalette[k][1], EMSPalette[k][2]));
							}
							break;
						}
					}
				}
			}

		};

		switch (Range[select[mode]][2]) {
			case 0:
				BitBlt(memdc, ux, uy, 32, 32, bmpdc, 0, 0, SRCCOPY);

				DrawSprite(ux, uy, Range[select[mode]][3], 0);

				break;
			case 1:
				BitBlt(memdc, ux, uy, 32, 32, bmpdc, 32, 32, SRCCOPY);

				DrawSprite(ux, uy, Range[select[mode]][3], 0);

				BitBlt(memdc, ux - 32 * 1, uy - 32 * 0, 32, 32, bmpdc, 32 * 7, 32 * 0, SRCCOPY);
				DrawSprite(ux-32, uy, Range[select[mode]][3], 1);
				BitBlt(memdc, ux + 32 * 1, uy - 32 * 0, 32, 32, bmpdc, 32 * 7, 32 * 1, SRCCOPY);
				DrawSprite(ux+32, uy, Range[select[mode]][3], 2);
				BitBlt(memdc, ux - 32 * 0, uy - 32 * 1, 32, 32, bmpdc, 32 * 6, 32 * 0, SRCCOPY);
				DrawSprite(ux, uy-32, Range[select[mode]][3], 3);
				BitBlt(memdc, ux - 32 * 0, uy + 32 * 1, 32, 32, bmpdc, 32 * 6, 32 * 1, SRCCOPY);
				DrawSprite(ux, uy+32, Range[select[mode]][3], 4);
				break;
			case 2:
			case 130:
				BitBlt(memdc, ux, uy, 32, 32, bmpdc, 0, 32, SRCCOPY);

				BitBlt(memdc, ux - 32 * 2, uy - 32 * 0, 32, 32, bmpdc, 32 * 7, 32 * 0, SRCCOPY);
				BitBlt(memdc, ux + 32 * 2, uy - 32 * 0, 32, 32, bmpdc, 32 * 7, 32 * 1, SRCCOPY);
				BitBlt(memdc, ux - 32 * 0, uy - 32 * 2, 32, 32, bmpdc, 32 * 6, 32 * 0, SRCCOPY);
				BitBlt(memdc, ux - 32 * 0, uy + 32 * 2, 32, 32, bmpdc, 32 * 6, 32 * 1, SRCCOPY);

				BitBlt(memdc, ux - 32 * 1, uy - 32 * 1, 32, 32, bmpdc, 32 * 2, 32 * 0, SRCCOPY);
				BitBlt(memdc, ux + 32 * 1, uy + 32 * 1, 32, 32, bmpdc, 32 * 3, 32 * 1, SRCCOPY);
				BitBlt(memdc, ux + 32 * 1, uy - 32 * 1, 32, 32, bmpdc, 32 * 3, 32 * 0, SRCCOPY);
				BitBlt(memdc, ux - 32 * 1, uy + 32 * 1, 32, 32, bmpdc, 32 * 2, 32 * 1, SRCCOPY);

				DrawSprite(ux, uy, Range[select[mode]][3], 0);

				DrawSprite(ux - 32 * 1, uy - 32 * 0, Range[select[mode]][3], 1);
				DrawSprite(ux - 32 * 2, uy - 32 * 0, Range[select[mode]][3], 2);
				DrawSprite(ux + 32 * 1, uy - 32 * 0, Range[select[mode]][3], 3);
				DrawSprite(ux + 32 * 2, uy - 32 * 0, Range[select[mode]][3], 4);
				DrawSprite(ux - 32 * 0, uy - 32 * 1, Range[select[mode]][3], 5);
				DrawSprite(ux - 32 * 0, uy - 32 * 2, Range[select[mode]][3], 6);
				DrawSprite(ux - 32 * 0, uy + 32 * 1, Range[select[mode]][3], 7);
				DrawSprite(ux - 32 * 0, uy + 32 * 2, Range[select[mode]][3], 8);
				DrawSprite(ux - 32 * 1, uy - 32 * 1, Range[select[mode]][3], 9);
				DrawSprite(ux + 32 * 1, uy - 32 * 1, Range[select[mode]][3], 11);
				DrawSprite(ux - 32 * 1, uy + 32 * 1, Range[select[mode]][3], 12);
				DrawSprite(ux + 32 * 1, uy + 32 * 1, Range[select[mode]][3], 13);

				break;
			case 3:
			case 4:
				BitBlt(memdc, ux, uy, 32, 32, bmpdc, 0, 32, SRCCOPY);

				BitBlt(memdc, ux - 32 * 1, uy - 32 * 0, 32, 32, bmpdc, 32 * 5, 32 * 0, SRCCOPY);
				BitBlt(memdc, ux + 32 * 1, uy - 32 * 0, 32, 32, bmpdc, 32 * 5, 32 * 1, SRCCOPY);
				BitBlt(memdc, ux - 32 * 0, uy - 32 * 1, 32, 32, bmpdc, 32 * 4, 32 * 0, SRCCOPY);
				BitBlt(memdc, ux - 32 * 0, uy + 32 * 1, 32, 32, bmpdc, 32 * 4, 32 * 1, SRCCOPY);

				BitBlt(memdc, ux - 32 * 1, uy - 32 * 1, 32, 32, bmpdc, 32 * 2, 32 * 0, SRCCOPY);
				BitBlt(memdc, ux + 32 * 1, uy + 32 * 1, 32, 32, bmpdc, 32 * 3, 32 * 1, SRCCOPY);
				BitBlt(memdc, ux + 32 * 1, uy - 32 * 1, 32, 32, bmpdc, 32 * 3, 32 * 0, SRCCOPY);
				BitBlt(memdc, ux - 32 * 1, uy + 32 * 1, 32, 32, bmpdc, 32 * 2, 32 * 1, SRCCOPY);

				if(Range[select[mode]][2]==3)DrawSprite(ux, uy, Range[select[mode]][3], 0);

				DrawSprite(ux - 32 * 1, uy - 32 * 0, Range[select[mode]][3], 1);
				DrawSprite(ux + 32 * 1, uy - 32 * 0, Range[select[mode]][3], 3);
				DrawSprite(ux - 32 * 0, uy - 32 * 1, Range[select[mode]][3], 5);
				DrawSprite(ux - 32 * 0, uy + 32 * 1, Range[select[mode]][3], 7);
				DrawSprite(ux - 32 * 1, uy - 32 * 1, Range[select[mode]][3], 9);
				DrawSprite(ux + 32 * 1, uy - 32 * 1, Range[select[mode]][3], 11);
				DrawSprite(ux - 32 * 1, uy + 32 * 1, Range[select[mode]][3], 12);
				DrawSprite(ux + 32 * 1, uy + 32 * 1, Range[select[mode]][3], 13);
				break;
			case 29:
			case 30:
			case 31:

				if(Range[select[mode]][3]>0 && Range[select[mode]][3]<4)DrawSprite(ux, uy, 1, 0);

				for (int i = 0; i < Range[select[mode]][2]-27; i++) {
					BitBlt(memdc, ux + 32 * ((i+1)*delx), uy + 32 * ((i + 1)*dely), 32, 32, bmpdc, 0, 0, SRCCOPY);
					DrawSprite(ux + 32 * ((i + 1)*delx), uy + 32 * ((i + 1)*dely), Range[select[mode]][3], 1+i);
				}

				break;
			case 32:
				BitBlt(memdc, ux, uy, 32, 32, bmpdc, 0, 32, SRCCOPY);

				BitBlt(memdc, ux - 32 * 1, uy - 32 * 1, 32, 32, bmpdc, 32 * 0, 32 * 0, SRCCOPY);
				BitBlt(memdc, ux + 32 * 1, uy + 32 * 1, 32, 32, bmpdc, 32 * 0, 32 * 0, SRCCOPY);
				BitBlt(memdc, ux + 32 * 1, uy - 32 * 1, 32, 32, bmpdc, 32 * 0, 32 * 0, SRCCOPY);
				BitBlt(memdc, ux - 32 * 1, uy + 32 * 1, 32, 32, bmpdc, 32 * 0, 32 * 0, SRCCOPY);

				DrawSprite(ux, uy, Range[select[mode]][3], 0);

				DrawSprite(ux - 32 * 1, uy - 32 * 1, Range[select[mode]][3], 1);
				DrawSprite(ux + 32 * 1, uy - 32 * 1, Range[select[mode]][3], 2);
				DrawSprite(ux - 32 * 1, uy + 32 * 1, Range[select[mode]][3], 3);
				DrawSprite(ux + 32 * 1, uy + 32 * 1, Range[select[mode]][3], 4);
				break;
		}

		if (Range[select[mode]][3] == 5 || Range[select[mode]][3] == 7) {
			DrawSprite(ux - 32 * 3, uy - 32 * 4, 1, 0);
			DrawSprite(ux + 32 * 2, uy - 32 * 3, 1, 1);
			DrawSprite(ux - 32 * 1, uy - 32 * 2, 1, 2);
			DrawSprite(ux - 32 * 2, uy - 32 * 1, 1, 3);
			DrawSprite(ux + 32 * 3, uy - 32 * 0, 1, 4);
			DrawSprite(ux - 32 * 2, uy + 32 * 2, 1, 5);
			DrawSprite(ux + 32 * 1, uy + 32 * 3, 1, 6);
		}

		if (Range[select[mode]][3] == 6 || Range[select[mode]][3] == 7) {
			DrawSprite(ux - 32 * 4, uy - 32 * 2, 2, 0);
			DrawSprite(ux + 32 * 1, uy - 32 * 2, 2, 1);
			DrawSprite(ux + 32 * 2, uy + 32 * 1, 2, 2);
			DrawSprite(ux - 32 * 1, uy + 32 * 2, 2, 3);
			DrawSprite(ux + 32 * 3, uy + 32 * 2, 2, 4);
			DrawSprite(ux - 32 * 3, uy + 32 * 3, 2, 5);
			DrawSprite(ux - 32 * 2, uy - 32 * 3, 2, 6);
		}

		ux = 300;
		uy = 378;

		bool good;

		for (int dx = -8; dx <= 8; dx++) {
			for (int dy = -8; dy <= 8; dy++) {

				good = true;

				int dist = abs(dx) + abs(dy);

				int max = Range[select[mode]][0] & 0x0F;

				if (max > MaxRange)max = MaxRange;

				int min = Range[select[mode]][1];

				if (dist > max || dist < min)good = false;

				if(good)
					switch ((Range[select[mode]][0] & 0xF0) / 0x10) {
					case 1:
						if (dx&&dy)good = false;
						break;
					case 2:
						if (dy)good = false;
						break;
					case 3:
						if (dx)good = false;
						break;
					case 4:
						if (abs(dx)==max||abs(dy)==max)good = false;
						break;
					case 5:
						if (abs(dx)!=abs(dy))good = false;
						break;
					case 6:
						if (abs(dx) != abs(dy) && ( dx && dy ))good = false;
						break;
					}

				if (good) {
					BitBlt(memdc, ux + dx * 16, uy + dy * 16, 16, 16, bmpdc, 0 + 16 * rf, 80, SRCCOPY);
				} else {
					BitBlt(memdc, ux + dx * 16, uy + dy * 16, 16, 16, bmpdc, 0, 64, SRCCOPY);
				}
			}
		}

	}

	if (NumRanges && !RangePreview) {
		ux = 154;
		uy = 236;

		for (int i = 0;i < NumItems;i++) {

			if (((Item[i][4] & 4) && Item[i][8] == select[mode]) || ((Item[i][4] & 1) && Item[i][12] == select[mode])) {
				sprintf(out, "%s", ItemName[i]);
				TextOut(memdc, ux, uy, out, strlen(out));
				uy += 18;
				if (uy + 18 > 530 - 4) {
					uy = 236;
					ux += 122;
				}
			}
		}

		if (select[mode])
			for (int i = 0;i < 16 + 16 * ExpandSpells;i++) {

				for (int j = 0;j < 4;j++) {

					if (Spell[i][0 + 4 * j] == select[mode]) {

						if (j)sprintf(out, "%s %d", SpellName[i], j + 1);
						else sprintf(out, "%s", SpellName[i]);
						TextOut(memdc, ux, uy, out, strlen(out));
						uy += 18;
						if (uy + 18 > 530 - 4) {
							uy = 236;
							ux += 122;
						}
					}
				}
			}
		if (select[mode] && select[mode]!=16)
			for (int i = 0; i < NumMonsters; i++) {
				if (ClassData[32 + i][5] == select[mode]) {


					sprintf(out, "%s", MonsterName[i]);
					TextOut(memdc, ux, uy, out, strlen(out));
					uy += 18;
					if (uy + 18 > 530 - 4) {
						uy = 236;
						ux += 122;
					}
				}
			}
	}

	switch (menu) {//shape, area, group, routine
		case 1:

			tb = (HBRUSH)SelectObject(memdc, CreateSolidBrush(RGB(180, 180, 180)));
			RoundRect(memdc, 300, 70, 450, 70 + 7 * 20, 10, 10);
			DeleteObject(SelectObject(memdc, tb));


			for (int i = 0; i < 7; i++) {
				if (RangeShape == i) {
					RoundRect(memdc, 300, 70 + i * 20, 450, 90 + i * 20, 10, 10);
				}
				TextOut(memdc, 306, 72 + 20 * i, RangeShapes[i], strlen(RangeShapes[i]));
			}
			break;
		case 2:

			tb = (HBRUSH)SelectObject(memdc, CreateSolidBrush(RGB(180, 180, 180)));
			RoundRect(memdc, 300, 90, 450, 90 + (3 + 6 * ExtendRange * ExtendArea) * 20, 10, 10);
			DeleteObject(SelectObject(memdc, tb));


			for (int i = 0; i < (3 + 6 * ExtendRange * ExtendArea); i++) {
				if (RangeArea == i) {
					RoundRect(memdc, 300, 90 + i * 20, 450, 110 + i * 20, 10, 10);
				}
				TextOut(memdc, 306, 92 + 20 * i, AreaShapes[i], strlen(AreaShapes[i]));
			}
			break;
		case 3:

			tb = (HBRUSH)SelectObject(memdc, CreateSolidBrush(RGB(180, 180, 180)));
			RoundRect(memdc, 300, 110, 450, 110 + 8 * 20, 10, 10);
			DeleteObject(SelectObject(memdc, tb));


			for (int i = 0; i < 8; i++) {
				if (Range[select[mode]][3] == i) {
					RoundRect(memdc, 300, 110 + i * 20, 450, 130 + i * 20, 10, 10);
				}
				TextOut(memdc, 306, 112 + 20 * i, RangeGroups[i], strlen(RangeGroups[i]));
			}
			break;
		case 4:

			tb = (HBRUSH)SelectObject(memdc, CreateSolidBrush(RGB(180, 180, 180)));
			RoundRect(memdc, 300, 130, 500, 130 + NUM_RANGE_ROUTINES * 20, 10, 10);
			DeleteObject(SelectObject(memdc, tb));


			for (int i = 0; i < NUM_RANGE_ROUTINES; i++) {
				if (RangeRoutine == i) {
					RoundRect(memdc, 300, 130 + i * 20, 500, 150 + i * 20, 10, 10);
				}
				TextOut(memdc, 306, 132 + 20 * i, RangeRoutines[i], strlen(RangeRoutines[i]));
			}
			break;
	}

}


if (submode[mode] == 1) {
	Rectangle(memdc, 50, 10 + 16 * select[mode], 150, 25 + 16 * select[mode]);

	j = (NumRanges - (NumRanges) % 32) / 32;
	if ((NumRanges) % 32 > 0)j++;
	for (i = 0; i < j; i++) {
		if (i + 1 < j)sprintf(out, "Ranges %d-%d", i * 32, (i + 1) * 32 - 1);
		else sprintf(out, "Ranges %d-%d", i * 32, NumRanges - 1);
		TextOut(memdc, 50, 10 + 16 * i, out, strlen(out));
	}

	for (i = 0; i < 32 && i + 32 * select[mode] < NumRanges; i++) {
		sprintf(out, "%d", i + 32 * select[mode]);
		TextOut(memdc, 160, 26 + 16 * i, out, strlen(out));
		if (ExtendRange) {
			SelectObject(bmpdc, dots);
			BitBlt(memdc, 179, 26 + 16 * i, 20, 20, bmpdc, 0, 0, SRCCOPY);
			if (ExtendArea) {
				BitBlt(memdc, 309, 26 + 16 * i, 20, 20, bmpdc, 0, 0, SRCCOPY);
			}
		}
		for (j = 0; j < 4; j++) {
			sprintf(out, "%d", Range[i + 32 * select[mode]][j]);
			if (focus == j + 1 && subfocus == i&&cursor)sprintf(out, "%s|", out);
			TextOut(memdc, 200 + 65 * j, 26 + 16 * i, out, strlen(out));
		}
		lo = 0x23178 + (i + 32 * select[mode]) * 8 + 6;
		sh = Range[i + 32 * select[mode]][6] * 256 + Range[i + 32 * select[mode]][7];
		lo += sh;

		if (focus == 5 && subfocus == i&&cursor) {
			sprintf(out, "%X| (%X)", (unsigned short)sh, lo);
		}
		else {
			sprintf(out, "%X  (%X)", (unsigned short)sh, lo);
		}
		TextOut(memdc, 200 + 65 * 4, 26 + 16 * i, out, strlen(out));
	}

	TextOut(memdc, 160, 10, "#", 1);
	TextOut(memdc, 200, 10, "Max", 3);
	TextOut(memdc, 265, 10, "Min", 3);
	TextOut(memdc, 330, 10, "Area", 4);
	TextOut(memdc, 395, 10, "Group", 5);
	TextOut(memdc, 460, 10, "Routine", 7);

	TextOut(memdc, 10, 400, "Relocate Table:", 15);
	if (RangeDataOffset != 0x23178)SelectObject(bmpdc, checkon);
	else SelectObject(bmpdc, checkoff);
	BitBlt(memdc, 114, 402, 13, 13, bmpdc, 0, 0, SRCCOPY);
	if (RangeDataOffset != 0x23178) {
		TextOut(memdc, 10, 416, "Offset:", 7);
		sprintf(out, "%X", RangeDataOffset);
		if (focus == 11 && cursor)sprintf(out, "%s|", out);
		TextOut(memdc, 56, 416, out, strlen(out));
		SelectObject(bmpdc, plus);
		BitBlt(memdc, 4, 10, 20, 20, bmpdc, 0, 0, SRCCOPY);
		SelectObject(bmpdc, minus);
		BitBlt(memdc, 4, 34, 20, 20, bmpdc, 0, 0, SRCCOPY);
	}

	TextOut(memdc, 10, 448, "Maximum Range:", 14);

	sprintf(out, "%d", MaxRange);
	if (focus == 10 && cursor)sprintf(out, "%s|", out);
	TextOut(memdc, 127, 448, out, strlen(out));

	TextOut(memdc, 10, 480, "Advanced Ranges:", 16);
	if (ExtendRange)SelectObject(bmpdc, checkon);
	else SelectObject(bmpdc, checkoff);
	BitBlt(memdc, 134, 482, 13, 13, bmpdc, 0, 0, SRCCOPY);
	if (ExtendRange) {
		TextOut(memdc, 10, 496, "Code Offset:", 12);
		sprintf(out, "%X", RangeOffset);
		if (focus == 9 && cursor)sprintf(out, "%s|", out);
		TextOut(memdc, 94, 496, out, strlen(out));

		TextOut(memdc, 10, 512, "Advanced Areas:", 15);
		if (ExtendArea)SelectObject(bmpdc, checkon);
		else SelectObject(bmpdc, checkoff);
		BitBlt(memdc, 134, 514, 13, 13, bmpdc, 0, 0, SRCCOPY);
		if (ExtendArea) {
			TextOut(memdc, 10, 528, "Code Offset:", 12);
			sprintf(out, "%X", AreaOffset);
			if (focus == 12 && cursor)sprintf(out, "%s|", out);
			TextOut(memdc, 94, 528, out, strlen(out));
		}
	}

	if (menu == 1 && ExtendRange) {
		r.top = 26 + 16 * (submenu);
		r.left = 179;
		r.right = 329;
		r.bottom = 214 + 16 * (submenu);
		y = 26 + 16 * submenu;
		if (y + 188 > 540) {
			r.top = 540 - 188;
			r.bottom = 540;
		}
		FillRect(memdc, &r, (HBRUSH)GetStockObject(WHITE_BRUSH));
		TextOut(memdc, r.left + 3, r.top + 5, "Range:", 6);
		sprintf(out, "%d", Range[submenu + 32 * select[mode]][0] & 0x0F);
		if (cursor)sprintf(out, "%s|", out);
		TextOut(memdc, r.left + 53, r.top + 5, out, strlen(out));
		TextOut(memdc, r.left + 3, r.top + 37, "Shape:", 6);
		c = Range[submenu + 32 * select[mode]][0];
		c &= 0x70;
		if (c == 0)SelectObject(bmpdc, checkon);
		else SelectObject(bmpdc, checkoff);
		BitBlt(memdc, r.left + 28, r.top + 54, 13, 13, bmpdc, 0, 0, SRCCOPY);
		TextOut(memdc, r.left + 46, r.top + 53, "Standard", 8);
		if (c == 16)SelectObject(bmpdc, checkon);
		else SelectObject(bmpdc, checkoff);
		BitBlt(memdc, r.left + 28, r.top + 70, 13, 13, bmpdc, 0, 0, SRCCOPY);
		TextOut(memdc, r.left + 46, r.top + 69, "Plus", 4);
		if (c == 32)SelectObject(bmpdc, checkon);
		else SelectObject(bmpdc, checkoff);
		BitBlt(memdc, r.left + 28, r.top + 86, 13, 13, bmpdc, 0, 0, SRCCOPY);
		TextOut(memdc, r.left + 46, r.top + 85, "Horizontal", 10);
		if (c == 48)SelectObject(bmpdc, checkon);
		else SelectObject(bmpdc, checkoff);
		BitBlt(memdc, r.left + 28, r.top + 102, 13, 13, bmpdc, 0, 0, SRCCOPY);
		TextOut(memdc, r.left + 46, r.top + 101, "Vertical", 8);
		if (c == 64)SelectObject(bmpdc, checkon);
		else SelectObject(bmpdc, checkoff);
		BitBlt(memdc, r.left + 28, r.top + 118, 13, 13, bmpdc, 0, 0, SRCCOPY);
		TextOut(memdc, r.left + 46, r.top + 117, "Block", 5);
		if (c == 80)SelectObject(bmpdc, checkon);
		else SelectObject(bmpdc, checkoff);
		BitBlt(memdc, r.left + 28, r.top + 134, 13, 13, bmpdc, 0, 0, SRCCOPY);
		TextOut(memdc, r.left + 46, r.top + 133, "Diagonals", 9);
		if (c == 96)SelectObject(bmpdc, checkon);
		else SelectObject(bmpdc, checkoff);
		BitBlt(memdc, r.left + 28, r.top + 150, 13, 13, bmpdc, 0, 0, SRCCOPY);
		TextOut(memdc, r.left + 46, r.top + 149, "Star", 4);
	}

	if (menu == 2 && ExtendRange&&ExtendArea) {
		r.top = 26 + 16 * (submenu);
		r.left = 309;
		r.right = 459;
		r.bottom = 214 + 16 * (submenu);
		y = 26 + 16 * submenu;
		if (y + 188 > 540) {
			r.top = 540 - 188;
			r.bottom = 540;
		}
		FillRect(memdc, &r, (HBRUSH)GetStockObject(WHITE_BRUSH));
		TextOut(memdc, r.left + 3, r.top + 5, "Shape:", 6);
		c = Range[submenu + 32 * select[mode]][2];
		c &= 0x7F;
		if (c == 0)SelectObject(bmpdc, checkon);
		else SelectObject(bmpdc, checkoff);
		BitBlt(memdc, r.left + 28, r.top + 22, 13, 13, bmpdc, 0, 0, SRCCOPY);
		TextOut(memdc, r.left + 46, r.top + 21, "1 Square", 8);
		if (c == 1)SelectObject(bmpdc, checkon);
		else SelectObject(bmpdc, checkoff);
		BitBlt(memdc, r.left + 28, r.top + 22 + 16, 13, 13, bmpdc, 0, 0, SRCCOPY);
		TextOut(memdc, r.left + 46, r.top + 21 + 16, "5 Squares", 9);
		if (c == 2)SelectObject(bmpdc, checkon);
		else SelectObject(bmpdc, checkoff);
		BitBlt(memdc, r.left + 28, r.top + 22 + 32, 13, 13, bmpdc, 0, 0, SRCCOPY);
		TextOut(memdc, r.left + 46, r.top + 21 + 32, "13 Squares", 10);
		if (c == 3)SelectObject(bmpdc, checkon);
		else SelectObject(bmpdc, checkoff);
		BitBlt(memdc, r.left + 28, r.top + 22 + 48, 13, 13, bmpdc, 0, 0, SRCCOPY);
		TextOut(memdc, r.left + 46, r.top + 21 + 48, "3x3 Block", 9);
		if (c == 4)SelectObject(bmpdc, checkon);
		else SelectObject(bmpdc, checkoff);
		BitBlt(memdc, r.left + 28, r.top + 22 + 64, 13, 13, bmpdc, 0, 0, SRCCOPY);
		TextOut(memdc, r.left + 46, r.top + 21 + 64, "Ring", 4);
		if (c == 29)SelectObject(bmpdc, checkon);
		else SelectObject(bmpdc, checkoff);
		BitBlt(memdc, r.left + 28, r.top + 22 + 80, 13, 13, bmpdc, 0, 0, SRCCOPY);
		TextOut(memdc, r.left + 46, r.top + 21 + 80, "2 Square Line", 13);
		if (c == 30)SelectObject(bmpdc, checkon);
		else SelectObject(bmpdc, checkoff);
		BitBlt(memdc, r.left + 28, r.top + 22 + 96, 13, 13, bmpdc, 0, 0, SRCCOPY);
		TextOut(memdc, r.left + 46, r.top + 21 + 96, "3 Square Line", 13);
		if (c == 31)SelectObject(bmpdc, checkon);
		else SelectObject(bmpdc, checkoff);
		BitBlt(memdc, r.left + 28, r.top + 22 + 112, 13, 13, bmpdc, 0, 0, SRCCOPY);
		TextOut(memdc, r.left + 46, r.top + 21 + 112, "4 Square Line", 13);
		if (c == 32)SelectObject(bmpdc, checkon);
		else SelectObject(bmpdc, checkoff);
		BitBlt(memdc, r.left + 28, r.top + 22 + 128, 13, 13, bmpdc, 0, 0, SRCCOPY);
		TextOut(memdc, r.left + 46, r.top + 21 + 128, "X", 1);
	}
}