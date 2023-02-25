if (submode[mode] == 0) {
	HBRUSH tb;
	SelectObject(bmpdc, plus);
	BitBlt(memdc, 4, 10, 20, 20, bmpdc, 0, 0, SRCCOPY);
	SelectObject(bmpdc, minus);
	BitBlt(memdc, 4, 34, 20, 20, bmpdc, 0, 0, SRCCOPY);

	Rectangle(memdc, 50, 10 + 16 * (select[mode] % 30), 130, 25 + 16 * (select[mode] % 30));

	for (i = 0;i < 30 && (i + subselect[mode][0] < NumEffects);i++) {
		sprintf(out, "Effect %d", i + subselect[mode][0]);
		TextOut(memdc, 50, 10 + 16 * i, out, strlen(out));
	}
	if (NumEffects > 30) {
		SelectObject(bmpdc, uparrow);
		BitBlt(memdc, 50, 520, 20, 20, bmpdc, 0, 0, SRCCOPY);
		SelectObject(bmpdc, downarrow);
		BitBlt(memdc, 73, 520, 20, 20, bmpdc, 0, 0, SRCCOPY);
	}

	RoundRect(memdc, 150, 23, 765, 262, 12, 12);

	RoundRect(memdc, 150, 280, 765, 530, 12, 12);

	SetBkMode(memdc, OPAQUE);
	SetBkColor(memdc, RGB(128, 128, 128));

	TextOut(memdc, 411, 15, " EFFECT DATA ", 13);
	TextOut(memdc, 428, 272, " USED BY ", 9);


	SetBkMode(memdc, TRANSPARENT);
	SetBkColor(memdc, RGB(255, 255, 255));

	int ux = 154;
	int uy = 286;

	EffectAction = -1;
	EffectType = 4;

	if (NumEffects) {
		for (int i = 0;i < NUM_EFFECT_ROUTINE;i++) {
			if (EffectRoutineOffset[i] == Effect[select[mode]][6] * 256 + Effect[select[mode]][7]) {
				EffectAction = i;
				break;
			}
		}

		TextOut(memdc, 300, 50, "Action:", 7);

		tb = (HBRUSH)SelectObject(memdc, CreateSolidBrush(RGB(180, 180, 180)));
		RoundRect(memdc, 400, 48, 650, 68, 10, 10);
		DeleteObject(SelectObject(memdc, tb));

		TextOut(memdc, 406, 50, EffectRoutineName[EffectAction], strlen(EffectRoutineName[EffectAction]));



		TextOut(memdc, 300, 70, "Type:", 5);

		tb = (HBRUSH)SelectObject(memdc, CreateSolidBrush(RGB(180, 180, 180)));
		RoundRect(memdc, 400, 68, 550, 88, 10, 10);
		DeleteObject(SelectObject(memdc, tb));

		switch (Effect[select[mode]][0]) {
		case 0:
			EffectType = 0;
			break;
		case 128:
			EffectType = 1;
			break;
		case 129:
			EffectType = 2;
			break;
		case 255:
			EffectType = 3;
			break;
		default:
			EffectType = 4;
			break;
		}

		sprintf(out, "%s", EffectTypes[EffectType]);
		TextOut(memdc, 406, 70, out, strlen(out));


		switch (EffectAction) {
		case 0:
		case 3:
		case 5:
		case 6:
		case 11:
		case 12:
			TextOut(memdc, 300, 90, "Strength:", 9);
			sprintf(out, "%d", Effect[select[mode]][3]);
			if (focus == 1 && cursor)sprintf(out, "%s|", out);
			TextOut(memdc, 400, 90, out, strlen(out));
			break;
		case 7:
			TextOut(memdc, 300, 90, "Status Effect:", 14);

			tb = (HBRUSH)SelectObject(memdc, CreateSolidBrush(RGB(180, 180, 180)));
			RoundRect(memdc, 400, 88, 550, 108, 10, 10);
			DeleteObject(SelectObject(memdc, tb));

			sprintf(out, "%s", StatusEffectName[Effect[select[mode]][2]]);
			TextOut(memdc, 406, 90, out, strlen(out));



			TextOut(memdc, 300, 110, "Can Fail:", 9);

			if (Effect[select[mode]][3])SelectObject(bmpdc, checkon);
			else SelectObject(bmpdc, checkoff);
			BitBlt(memdc, 400, 112, 13, 13, bmpdc, 0, 0, SRCCOPY);
			break;
		case 10:
			TextOut(memdc, 300, 90, "Stat:", 5);

			tb = (HBRUSH)SelectObject(memdc, CreateSolidBrush(RGB(180, 180, 180)));
			RoundRect(memdc, 400, 88, 550, 108, 10, 10);
			DeleteObject(SelectObject(memdc, tb));

			sprintf(out, "%s", StatUps[Effect[select[mode]][2]]);
			TextOut(memdc, 406, 90, out, strlen(out));
			break;
		}

		switch (EffectAction) {
		case 3:
		case 5:
		case 6:
		case 12:
			TextOut(memdc, 300, 110, "Resistance:", 11);

			tb = (HBRUSH)SelectObject(memdc, CreateSolidBrush(RGB(180, 180, 180)));
			RoundRect(memdc, 400, 108, 550, 128, 10, 10);
			DeleteObject(SelectObject(memdc, tb));

			sprintf(out, "%s", EffectResist[Effect[select[mode]][2] & 0x07]);
			TextOut(memdc, 406, 110, out, strlen(out));
			break;

		}

		switch (EffectAction) {
		case 5:
		case 6:
		case 12:
			TextOut(memdc, 300, 130, "Crit:", 5);

			tb = (HBRUSH)SelectObject(memdc, CreateSolidBrush(RGB(180, 180, 180)));
			RoundRect(memdc, 400, 128, 550, 148, 10, 10);
			DeleteObject(SelectObject(memdc, tb));

			sprintf(out, "%s", EffectCrit[(Effect[select[mode]][2] >> 3) & 0x03]);
			TextOut(memdc, 406, 130, out, strlen(out));
			break;
		}
	}


	if (EffectType == 1 || EffectType == 2) {
		TextOut(memdc, 300, 150, "Animation:", 10);
		sprintf(out, "%d", Effect[select[mode]][1]);
		if (focus == 3 && cursor)sprintf(out, "%s|", out);
		TextOut(memdc, 400, 150, out, strlen(out));
	}

	if (NumEffects) {
		TextOut(memdc, 300, 170, "Text:", 5);
		if (Effect[select[mode]][4] < 128) {


			if (TextLoaded) {
				int tx = Effect[select[mode]][4] + 436;
				int ln = strlen(Text[tx]);
				if (ln > 40) {
					sprintf(out, "%s", Text[tx]);
					out[40] = '.';
					out[41] = '.';
					out[42] = '.';
					out[43] = 0;
				} else {
					sprintf(out, "%s", Text[tx]);
				}
				TextOut(memdc, 400, 190, out, strlen(out));
			}


			if (focus == 2 && cursor)sprintf(out, "%d|", Effect[select[mode]][4]);
			else sprintf(out, "%d", Effect[select[mode]][4]);
			TextOut(memdc, 400, 170, out, strlen(out));

			sprintf(out, "(%d)", Effect[select[mode]][4] + 436);
			TextOut(memdc, 434, 170, out, strlen(out));
		} else {
			if (focus == 2 && cursor)sprintf(out, "%d|", Effect[select[mode]][4]);
			else sprintf(out, "%d", Effect[select[mode]][4]);
			TextOut(memdc, 400, 170, out, strlen(out));

			TextOut(memdc, 440, 170, "(Default)", 9);
			
		}
	}

	if (NumEffects) {
		for (int i = 0;i < NumItems;i++) {

			if (((Item[i][4] & 4) && Item[i][9] == select[mode]) || ((Item[i][4] & 1) && Item[i][13] == select[mode])) {
				sprintf(out, "%s", ItemName[i]);
				TextOut(memdc, ux, uy, out, strlen(out));
				uy += 18;
				if (uy + 18 > 530 - 4) {
					uy = 286;
					ux += 122;
				}
			}
		}
		if(select[mode])
		for (int i = 0;i < 16 + 16 * ExpandSpells;i++) {

			for (int j = 0;j < 4;j++) {

				if (Spell[i][1 + 4 * j] == select[mode]) {

					if(j)sprintf(out, "%s %d", SpellName[i],j+1);
					else sprintf(out, "%s", SpellName[i]);
					TextOut(memdc, ux, uy, out, strlen(out));
					uy += 18;
					if (uy + 18 > 530 - 4) {
						uy = 286;
						ux += 122;
					}
				}
			}
		}
		if (select[mode])
			for (int i = 0; i < NumMonsters; i++) {
				if (ClassData[32+i][6] == select[mode]) {


					sprintf(out, "%s", MonsterName[i]);
					TextOut(memdc, ux, uy, out, strlen(out));
					uy += 18;
					if (uy + 18 > 530 - 4) {
						uy = 286;
						ux += 122;
					}
				}
			}

		switch (menu) {
			case 1:
				tb = (HBRUSH)SelectObject(memdc, CreateSolidBrush(RGB(180, 180, 180)));
				RoundRect(memdc, 400, 48, 650, 48 + NUM_EFFECT_ROUTINE * 20, 10, 10);
				DeleteObject(SelectObject(memdc, tb));

				
				for (int i = 0; i < NUM_EFFECT_ROUTINE; i++) {
					if (EffectAction == i) {
						RoundRect(memdc, 400, 48 + i * 20, 650, 68 + i * 20, 10, 10);
					}
					TextOut(memdc, 406, 50 + 20 * i, EffectRoutineName[i], strlen(EffectRoutineName[i]));
				}
				break;
			case 2:
				tb = (HBRUSH)SelectObject(memdc, CreateSolidBrush(RGB(180, 180, 180)));
				RoundRect(memdc, 400, 68, 550, 68 + 5 * 20, 10, 10);
				DeleteObject(SelectObject(memdc, tb));


				for (int i = 0; i < 5; i++) {
					if (EffectType == i) {
						RoundRect(memdc, 400, 68 + i * 20, 550, 88 + i * 20, 10, 10);
					}
					TextOut(memdc, 406, 70 + 20 * i, EffectTypes[i], strlen(EffectTypes[i]));
				}
				break;
			case 3:
				tb = (HBRUSH)SelectObject(memdc, CreateSolidBrush(RGB(180, 180, 180)));
				RoundRect(memdc, 400, 108, 550, 108 + 8 * 20, 10, 10);
				DeleteObject(SelectObject(memdc, tb));


				for (int i = 0; i < 8; i++) {
					if ((Effect[select[mode]][2] & 0x07) == i) {
						RoundRect(memdc, 400, 108 + i * 20, 550, 128 + i * 20, 10, 10);
					}
					TextOut(memdc, 406, 110 + 20 * i, EffectResist[i], strlen(EffectResist[i]));
				}
				break;
			case 4:
				tb = (HBRUSH)SelectObject(memdc, CreateSolidBrush(RGB(180, 180, 180)));
				RoundRect(memdc, 400, 128, 550, 128 + 3 * 20, 10, 10);
				DeleteObject(SelectObject(memdc, tb));


				for (int i = 0; i < 3; i++) {
					if (((Effect[select[mode]][2]>>3) & 0x03) == i) {
						RoundRect(memdc, 400, 128 + i * 20, 550, 148 + i * 20, 10, 10);
					}
					TextOut(memdc, 406, 130 + 20 * i, EffectCrit[i], strlen(EffectCrit[i]));
				}
				break;
			case 5:
				tb = (HBRUSH)SelectObject(memdc, CreateSolidBrush(RGB(180, 180, 180)));
				RoundRect(memdc, 400, 88, 550, 88 + 10 * 20, 10, 10);
				DeleteObject(SelectObject(memdc, tb));


				for (int i = 0; i < 10; i++) {
					if (Effect[select[mode]][2] == i) {
						RoundRect(memdc, 400, 88 + i * 20, 550, 108 + i * 20, 10, 10);
					}
					TextOut(memdc, 406, 90 + 20 * i, StatusEffectName[i], strlen(StatusEffectName[i]));
				}
				break;
			case 6:
				tb = (HBRUSH)SelectObject(memdc, CreateSolidBrush(RGB(180, 180, 180)));
				RoundRect(memdc, 400, 88, 550, 88 + NUM_STAT_UPS * 20, 10, 10);
				DeleteObject(SelectObject(memdc, tb));


				for (int i = 0; i < NUM_STAT_UPS; i++) {
					if (Effect[select[mode]][2] == i) {
						RoundRect(memdc, 400, 88 + i * 20, 550, 108 + i * 20, 10, 10);
					}
					TextOut(memdc, 406, 90 + 20 * i, StatUps[i], strlen(StatUps[i]));
				}
				break;
		}
	}
}

if (submode[mode] == 1) {
	SelectObject(bmpdc, plus);
	BitBlt(memdc, 4, 10, 20, 20, bmpdc, 0, 0, SRCCOPY);
	SelectObject(bmpdc, minus);
	BitBlt(memdc, 4, 34, 20, 20, bmpdc, 0, 0, SRCCOPY);

	Rectangle(memdc, 50, 10 + 16 * select[mode], 150, 25 + 16 * select[mode]);

	j = (NumEffects - (NumEffects) % 30) / 30;
	if ((NumEffects) % 30 > 0)j++;
	for (i = 0;i < j;i++) {
		if (i + 1 < j)sprintf(out, "Effects %d-%d", i * 30, (i + 1) * 30 - 1);
		else sprintf(out, "Effects %d-%d", i * 30, NumEffects - 1);
		TextOut(memdc, 50, 10 + 16 * i, out, strlen(out));
	}


	//TextOut(memdc,50,10,"Effects 0-29",12);
	//TextOut(memdc,50,26,"Effects 30-58",13);

	for (i = 0;i < 30 && i + 30 * select[mode] < NumEffects;i++) {
		sprintf(out, "%d", i + 30 * select[mode]);
		TextOut(memdc, 160, 26 + 16 * i, out, strlen(out));
		for (j = 0;j < 8;j++) {
			sprintf(out, "%d", Effect[i + 30 * select[mode]][j]);
			if (focus == j + 1 && subfocus == i&&cursor)sprintf(out, "%s|", out);
			TextOut(memdc, 200 + 65 * j, 26 + 16 * i, out, strlen(out));
		}
	}

	TextOut(memdc, 160, 10, "#", 1);
	TextOut(memdc, 200, 10, "Type", 4);
	TextOut(memdc, 265, 10, "Anim", 4);
	TextOut(memdc, 330, 10, "Status", 6);
	TextOut(memdc, 395, 10, "Damage", 6);
	TextOut(memdc, 460, 10, "Text", 4);
	TextOut(memdc, 525, 10, "?", 1);
	TextOut(memdc, 590, 10, "Routine", 7);
	//TextOut(memdc,655,10,"?",1);
}
