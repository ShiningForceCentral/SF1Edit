if (p.x >= 580 && p.x <= 680 && p.y >= 12 && p.y <= 40) {
	subselect[mode][7] = 0;
}

if (p.x >= 680 && p.x <= 780 && p.y >= 12 && p.y <= 40) {
	subselect[mode][7] = 1;
}

if (p.x >= 580 && p.x <= 680 && p.y >= 40 && p.y <= 68) {
	subselect[mode][7] = 2;
}

if (p.x >= 680 && p.x <= 780 && p.y >= 40 && p.y <= 68) {
	subselect[mode][7] = 3;
}


if (subselect[mode][7] == 0) {

	if (p.x >= 645 && p.x <= 665 && p.y >= 80 && p.y <= 100) {
		TempPalReady = false;
		subselect[mode][1]--;
		if (subselect[mode][1] < 0)subselect[mode][1] = NumGFX[0] - 1;
	}

	if (p.x >= 761 && p.x <= 781 && p.y >= 80 && p.y <= 100) {
		TempPalReady = false;
		subselect[mode][1]++;
		if (subselect[mode][1] > NumGFX[0] - 1)subselect[mode][1] = 0;
	}

	if (p.x >= 645 && p.x <= 665 && p.y >= 100 && p.y <= 120) {
		TempPalReady = false;
		subselect[mode][3]--;
		if (subselect[mode][3] < 0)subselect[mode][3] = NumGFX[1] - 1;
	}

	if (p.x >= 761 && p.x <= 781 && p.y >= 100 && p.y <= 120) {
		TempPalReady = false;
		subselect[mode][3]++;
		if (subselect[mode][3] > NumGFX[1] - 1)subselect[mode][3] = 0;
	}

	if (p.x >= 645 && p.x <= 665 && p.y >= 120 && p.y <= 140) {
		TempPalReady = false;
		subselect[mode][4]--;
		if (subselect[mode][4] < 0)subselect[mode][4] = NumGFX[4] - 1;
	}

	if (p.x >= 761 && p.x <= 781 && p.y >= 120 && p.y <= 140) {
		TempPalReady = false;
		subselect[mode][4]++;
		if (subselect[mode][4] > NumGFX[4] - 1)subselect[mode][4] = 0;
	}

	if (p.x >= 645 && p.x <= 665 && p.y >= 140 && p.y <= 160) {
		TempPalReady = false;
		subselect[mode][5]--;
		if (subselect[mode][5] < 0)subselect[mode][5] = (NumGFX[3] - 2) / 2;
	}

	if (p.x >= 761 && p.x <= 781 && p.y >= 140 && p.y <= 160) {
		TempPalReady = false;
		subselect[mode][5]++;
		if (subselect[mode][5] > (NumGFX[3] - 2) / 2)subselect[mode][5] = 0;
	}

	if (p.x >= 645 && p.x <= 665 && p.y >= 160 && p.y <= 180) {
		TempPalReady = false;
		subselect[mode][6]--;
		if (subselect[mode][6] < 0)subselect[mode][6] = (NumGFX[3] - 2) / 2;
	}

	if (p.x >= 761 && p.x <= 781 && p.y >= 160 && p.y <= 180) {
		TempPalReady = false;
		subselect[mode][6]++;
		if (subselect[mode][6] > (NumGFX[3] - 2) / 2)subselect[mode][6] = 0;
	}

	if (p.x >= 666 && p.x <= 760 && p.y >= 80 && p.y <= 100) {
		focus = 1;
	}
	if (p.x >= 666 && p.x <= 760 && p.y >= 100 && p.y <= 120) {
		focus = 2;
	}
	if (p.x >= 666 && p.x <= 760 && p.y >= 120 && p.y <= 140) {
		focus = 3;
	}
	if (p.x >= 666 && p.x <= 760 && p.y >= 140 && p.y <= 160) {
		focus = 4;
	}
	if (p.x >= 666 && p.x <= 760 && p.y >= 160 && p.y <= 180) {
		focus = 5;
	}

	if (p.x >= 620 && p.x <= 633 && p.y >= 164 && p.y <= 177) {
		DrawBG2 = !DrawBG2;
	}
	if (p.x >= 720 && p.x <= 733 && p.y >= 242 && p.y < 255) {
		AnimBorder = !AnimBorder;
	}
}

if (subselect[mode][7] == 1) {
	if (p.x >= 725 && p.x <= 742 && p.y >= 83 && p.y<99) {
		COLORREF c = RGB(FlickerColor[0], FlickerColor[1], FlickerColor[2]);
		chooseColor(c);
		GFXPaletteEdit = true;
		FlickerColor[select[mode]][0] = GetRValue(c);
		FlickerColor[select[mode]][1] = GetGValue(c);
		FlickerColor[select[mode]][2] = GetBValue(c);
		InvalidateRect(hWnd, NULL, 0);
	}


	int uy = subselect[mode][8];
	int uh = 52;
	for (int i = 0; i <= PSLen[select[mode]]; i++) {
		if (uy + 120 + uh + 80 > bheight + dheight)break;
		if (uy >= 0) {
			if (i == PSLen[select[mode]]) {
				if(!menu)
					if (p.x >= 626 - 8 - 40 && p.x <= 626 - 8 - 40 + 13 && p.y >= uy + 147 && p.y < uy + 160) {
						TempPalReady = false;
						PSLen[select[mode]]++;

						PaletteScript[select[mode]][PSLen[select[mode]] - 1][0] = 0;
						PaletteScript[select[mode]][PSLen[select[mode]] - 1][1] = 0;
						PaletteScript[select[mode]][PSLen[select[mode]] - 1][2] = 0;
						PaletteScript[select[mode]][PSLen[select[mode]] - 1][3] = 0;
						return 0;
					}
				continue;
			}

			if (menu==1 && submenu == i) {

				if (uy + 160 + 12 * 20 <= bheight + dheight) {
					for (int j = 0; j < 12; j++) {
						if (p.x >= 626 && p.x <= 778 && p.y >= uy + 120 + 20*j && p.y < uy + 140 + 20 * j) {
							PaletteScript[select[mode]][i][0] = j;
							PaletteScript[select[mode]][i][1] = 0;
							PaletteScript[select[mode]][i][2] = 0;
							PaletteScript[select[mode]][i][3] = 0;
							return 0;
						}
					}
				} else {
					for (int j = 0; j < 12; j++) {
						if (p.x >= 626 && p.x <= 778 && p.y >= bheight + dheight - 40 - 12 * 20 + 20 * j && p.y < bheight + dheight - 20 - 12 * 20 + 20 * j) {
							PaletteScript[select[mode]][i][0] = j;
							PaletteScript[select[mode]][i][1] = 0;
							PaletteScript[select[mode]][i][2] = 0;
							PaletteScript[select[mode]][i][3] = 0;
							return 0;
						}
					}
				}
				menu = 0;
			}

			if (menu) {
				uy += uh + 6;
				continue;
			}
			if (p.x >= 626 && p.x <= 778 && p.y >= uy + 120 && p.y < uy + 140) {
				menu = 1;
				submenu = i;
				break;
			}

			switch (PaletteScript[select[mode]][i][0]) {
			case 0://load
			case 1://save
				break;
			case 2://filter

				if (p.x >= 658 && p.x <= 671 && p.y >= uy + 147 && p.y < uy + 160) {
					PaletteScript[select[mode]][i][1] = 0xE - PaletteScript[select[mode]][i][1];
					TempPalReady = false;
				}
				if (p.x >= 704 && p.x <= 717 && p.y >= uy + 147 && p.y < uy + 160) {
					PaletteScript[select[mode]][i][2] = 0xE - PaletteScript[select[mode]][i][2];
					TempPalReady = false;
				}
				if (p.x >= 750 && p.x <= 763 && p.y >= uy + 147 && p.y < uy + 160) {
					PaletteScript[select[mode]][i][3] = 0xE - PaletteScript[select[mode]][i][3];
					TempPalReady = false;
				}
				break;
			case 3://shift
				if (p.x >= 663 && p.x <= 676 && p.y >= uy + 147 && p.y < uy + 160) {
					PaletteScript[select[mode]][i][1] = 1 - PaletteScript[select[mode]][i][1];
					TempPalReady = false;
				}
				if (p.x >= 750 && p.x <= 763 && p.y >= uy + 147 && p.y < uy + 160) {
					PaletteScript[select[mode]][i][2] = 1 - PaletteScript[select[mode]][i][2];
					TempPalReady = false;
				}
				break;
			case 4://cap
				if (p.x >= 663 && p.x <= 676 && p.y >= uy + 147 && p.y < uy + 160) {
					PaletteScript[select[mode]][i][1] = 1 - PaletteScript[select[mode]][i][1];
					TempPalReady = false;
				}
				if (p.x >= 750 && p.x <= 763 && p.y >= uy + 147 && p.y < uy + 160) {
					PaletteScript[select[mode]][i][2] = 1 - PaletteScript[select[mode]][i][2];
					TempPalReady = false;
				}
				break;
			case 5://mix
				break;
			case 6://set
				if (p.x >= 658 && p.x <= 671 && p.y >= uy + 147 && p.y < uy + 160) {
					PaletteScript[select[mode]][i][1] = 1 - PaletteScript[select[mode]][i][1];
					TempPalReady = false;
				}
				if (p.x >= 704 && p.x <= 717 && p.y >= uy + 147 && p.y < uy + 160) {
					PaletteScript[select[mode]][i][2] = 1 - PaletteScript[select[mode]][i][2];
					TempPalReady = false;
				}
				if (p.x >= 750 && p.x <= 763 && p.y >= uy + 147 && p.y < uy + 160) {
					PaletteScript[select[mode]][i][3] = 1 - PaletteScript[select[mode]][i][3];
					TempPalReady = false;
				}
				break;
			case 7://clear
				break;
			case 8://add
				if (p.x >= 658 && p.x <= 671 && p.y >= uy + 147 && p.y < uy + 160) {
					PaletteScript[select[mode]][i][1] = 1 - PaletteScript[select[mode]][i][1];
					TempPalReady = false;
				}
				if (p.x >= 704 && p.x <= 717 && p.y >= uy + 147 && p.y < uy + 160) {
					PaletteScript[select[mode]][i][2] = 1 - PaletteScript[select[mode]][i][2];
					TempPalReady = false;
				}
				if (p.x >= 750 && p.x <= 763 && p.y >= uy + 147 && p.y < uy + 160) {
					PaletteScript[select[mode]][i][3] = 1 - PaletteScript[select[mode]][i][3];
					TempPalReady = false;
				}
				break;
			case 9://reduce
				if (p.x >= 658 && p.x <= 671 && p.y >= uy + 147 && p.y < uy + 160) {
					PaletteScript[select[mode]][i][1]= 0;
					TempPalReady = false;
				}
				if (p.x >= 704 && p.x <= 717 && p.y >= uy + 147 && p.y < uy + 160) {
					PaletteScript[select[mode]][i][1] = 1;
					TempPalReady = false;
				}
				if (p.x >= 750 && p.x <= 763 && p.y >= uy + 147 && p.y < uy + 160) {
					PaletteScript[select[mode]][i][1] = 2;
					TempPalReady = false;
				}
				break;
			case 10://duplicate
				break;
			case 11://mul/div
				if (p.x >= 636 && p.x <= 676 && p.y >= uy + 147 && p.y < uy + 160) {
					focus = 1;
					subfocus = i;
				}
				if (p.x >= 750 && p.x <= 763 && p.y >= uy + 147 && p.y < uy + 160) {
					PaletteScript[select[mode]][i][1] = 1 - PaletteScript[select[mode]][i][1];
					TempPalReady = false;
				}
				break;
			}


			if (p.x >= 626 - 8 - 40 && p.x <= 626 - 8 - 40 + 13 && p.y >= uy + 124 && p.y < uy + 147) {
				TempPalReady = false;
				PSLen[select[mode]]--;
				for (int j = i; j < PSLen[select[mode]]; j++) {
					PaletteScript[select[mode]][j][0] = PaletteScript[select[mode]][j + 1][0];
					PaletteScript[select[mode]][j][1] = PaletteScript[select[mode]][j + 1][1];
					PaletteScript[select[mode]][j][2] = PaletteScript[select[mode]][j + 1][2];
					PaletteScript[select[mode]][j][3] = PaletteScript[select[mode]][j + 1][3];
				}
				break;
			}
			if (p.x >= 626 - 8 - 40 && p.x <= 626 - 8 - 40 + 13 && p.y >= uy + 147 && p.y < uy + 160) {
				TempPalReady = false;
				PSLen[select[mode]]++;
				for (int j = PSLen[select[mode]] -1; j >= i + 1; j--) {
					PaletteScript[select[mode]][j][0] = PaletteScript[select[mode]][j - 1][0];
					PaletteScript[select[mode]][j][1] = PaletteScript[select[mode]][j - 1][1];
					PaletteScript[select[mode]][j][2] = PaletteScript[select[mode]][j - 1][2];
					PaletteScript[select[mode]][j][3] = PaletteScript[select[mode]][j - 1][3];
				}

				PaletteScript[select[mode]][i][0] = 0;
				PaletteScript[select[mode]][i][1] = 0;
				PaletteScript[select[mode]][i][2] = 0;
				PaletteScript[select[mode]][i][3] = 0;
				break;
			}

			if (i)
				if (p.x >= 626 - 4 - 20 && p.x <= 626 - 4 - 20 + 13 && p.y >= uy + 124 && p.y < uy + 147) {
					TempPalReady = false;


					PaletteScript[select[mode]][63][0] = PaletteScript[select[mode]][i - 1][0];
					PaletteScript[select[mode]][63][1] = PaletteScript[select[mode]][i - 1][1];
					PaletteScript[select[mode]][63][2] = PaletteScript[select[mode]][i - 1][2];
					PaletteScript[select[mode]][63][3] = PaletteScript[select[mode]][i - 1][3];

					PaletteScript[select[mode]][i - 1][0] = PaletteScript[select[mode]][i][0];
					PaletteScript[select[mode]][i - 1][1] = PaletteScript[select[mode]][i][1];
					PaletteScript[select[mode]][i - 1][2] = PaletteScript[select[mode]][i][2];
					PaletteScript[select[mode]][i - 1][3] = PaletteScript[select[mode]][i][3];

					PaletteScript[select[mode]][i][0] = PaletteScript[select[mode]][63][0];
					PaletteScript[select[mode]][i][1] = PaletteScript[select[mode]][63][1];
					PaletteScript[select[mode]][i][2] = PaletteScript[select[mode]][63][2];
					PaletteScript[select[mode]][i][3] = PaletteScript[select[mode]][63][3];

					break;
				}

			if (i < PSLen[select[mode]] - 1)
			if (p.x >= 626 - 4 - 20 && p.x <= 626 - 4 - 20 + 13 && p.y >= uy + 147 && p.y < uy + 160) {
				TempPalReady = false;


				PaletteScript[select[mode]][63][0] = PaletteScript[select[mode]][i + 1][0];
				PaletteScript[select[mode]][63][1] = PaletteScript[select[mode]][i + 1][1];
				PaletteScript[select[mode]][63][2] = PaletteScript[select[mode]][i + 1][2];
				PaletteScript[select[mode]][63][3] = PaletteScript[select[mode]][i + 1][3];

				PaletteScript[select[mode]][i + 1][0] = PaletteScript[select[mode]][i][0];
				PaletteScript[select[mode]][i + 1][1] = PaletteScript[select[mode]][i][1];
				PaletteScript[select[mode]][i + 1][2] = PaletteScript[select[mode]][i][2];
				PaletteScript[select[mode]][i + 1][3] = PaletteScript[select[mode]][i][3];

				PaletteScript[select[mode]][i][0] = PaletteScript[select[mode]][63][0];
				PaletteScript[select[mode]][i][1] = PaletteScript[select[mode]][63][1];
				PaletteScript[select[mode]][i][2] = PaletteScript[select[mode]][63][2];
				PaletteScript[select[mode]][i][3] = PaletteScript[select[mode]][63][3];

				break;
			}

		}

		uy += uh + 6;
	}

	if (p.x >= 670 && p.x <= 690 && p.y >= bheight + dheight - 70 && p.y < bheight + dheight - 50) {
		subselect[mode][8] += uh + 6;
		if (subselect[mode][8] > 0)subselect[mode][8] = 0;
	}

	if (p.x >= 700 && p.x <= 720 && p.y >= bheight + dheight - 70 && p.y < bheight + dheight - 50) {
		subselect[mode][8] -= uh + 6;
	}

}

if (subselect[mode][7] == 2) {
	if (p.x >= 615 && p.x <= 635 && p.y >= 80 && p.y <= 100) {
		subselect[mode][9]--;
		if (subselect[mode][9] < 0)subselect[mode][9] = NumAnimGFX[select[mode]] - 1;
	}
	if (p.x >= 665 && p.x <= 695 && p.y >= 80 && p.y <= 100) {
		focus = 1;
	}

	if (p.x >= 716 && p.x <= 756 && p.y >= 122 && p.y <= 142) {
		focus = 2;
	}
	if (p.x >= 716 && p.x <= 756 && p.y >= 142 && p.y <= 162) {
		focus = 3;
	}
	if (p.x >= 716 && p.x <= 756 && p.y >= 162 && p.y <= 182) {
		focus = 4;
	}
	if (p.x >= 716 && p.x <= 756 && p.y >= 182 && p.y <= 202) {
		focus = 5;
	}
	if (p.x >= 716 && p.x <= 756 && p.y >= 202 && p.y <= 222) {
		focus = 6;
	}

	if (p.x >= 716 && p.x <= 730 && p.y >= 223 && p.y <= 236) {
		AnimGFX[select[mode]][subselect[mode][9]][4] ^= 0x01;
	}
	if (p.x >= 716 && p.x <= 730 && p.y >= 243 && p.y <= 256) {
		AnimGFX[select[mode]][subselect[mode][9]][4] ^= 0x02;
	}

	if (p.x >= 731 && p.x <= 751 && p.y >= 80 && p.y <= 100) {
		subselect[mode][9]++;
		if (subselect[mode][9] > NumAnimGFX[select[mode]] - 1)subselect[mode][9] = 0;
	}

	if (p.x >= 585 && p.x <= 675 && p.y >= 268 && p.y <= 318) {
		if (NumAnimGFX[select[mode]] < 64) {
			NumAnimGFX[select[mode]]++;
		}
	}

	if (p.x >= 685 && p.x <= 775 && p.y >= 268 && p.y <= 318) {
		if (NumAnimGFX[select[mode]] > 1) {
			NumAnimGFX[select[mode]]--;
			if (subselect[mode][9] >= NumAnimGFX[select[mode]])subselect[mode][9] = NumAnimGFX[select[mode]] - 1;
		}
	}
}

if (subselect[mode][7] == 3) {
	SpellAnimScript[select[mode]].click(p);
}