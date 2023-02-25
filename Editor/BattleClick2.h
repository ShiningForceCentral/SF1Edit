BattleDrag = -1;

	if (p.x >= 0 && p.x <= 40 && p.y >= 10 && p.y <= 50) {
		mode = 5;

		focus = 0;
		menu = 0;
		BattleSelect = -1;
		return 0;
	}

	if (p.x >= 55 && p.x <= 75 && p.y >= 8 && p.y <= 28) {
		select[mode]--;
		if (select[mode]<0)select[mode] += 12;
		ViewX = 0;
		ViewY = 0;
		BattleSelect = -1;
		BattleDrag = -1;
		BattleEntrance = NonBattleIndex[select[mode]][3];
		subselect[mode][2] = 0;
	}
	if (p.x >= 76 && p.x <= 135 && p.y >= 10 && p.y <= 26) {
		focus = 1;
	}
	if (p.x >= 140 && p.x <= 160 && p.y >= 8 && p.y <= 28) {
		select[mode]++;
		select[mode] %= 12;
		ViewX = 0;
		ViewY = 0;
		BattleSelect = -1;
		BattleDrag = -1;
		BattleEntrance = NonBattleIndex[select[mode]][3];
		subselect[mode][2] = 0;
	}
	if (p.x >= 176 && p.x <= 237 && p.y >= 10 && p.y <= 26) {
		focus = 2;
	}
	if (p.x >= 238 && p.x <= 328 && p.y >= 10 && p.y <= 26) {
		focus = 3;
	}
	if (p.x >= 328 && p.x <= 377 && p.y >= 10 && p.y <= 26) {
		focus = 4;
	}
	if (p.x >= 378 && p.x <= 427 && p.y >= 10 && p.y <= 26) {
		focus = 5;
	}
	if (p.x >= 428 && p.x <= 477 && p.y >= 10 && p.y <= 26) {
		focus = 6;
	}
	if (p.x >= 478 && p.x <= 527 && p.y >= 10 && p.y <= 26) {
		focus = 7;
	}
	if (p.x >= 300 && p.x <= 313 && p.y >= (BMH - 10) * 48 + 522 && p.y <= (BMH - 10) * 48 + 535) {
		DisplayBorder = !DisplayBorder;
	}
	if (p.x >= 430 && p.x <= 443 && p.y >= (BMH - 10) * 48 + 522 && p.y <= (BMH - 10) * 48 + 535) {
		DisplayGrid = !DisplayGrid;
	}


	if (p.x >= dwidth + 700 && p.x <= dwidth + 713 && p.y >= 32 && p.y <= 45) {
		BattleMode = 1;
		BattleSelect = -1;
		subselect[mode][2] = 0;
	}

	if (p.x >= dwidth + 700 && p.x <= dwidth + 713 && p.y >= 48 && p.y <= 61) {
		BattleMode = 3;
		BattleSelect = -1;
		subselect[mode][2] = 0;
	}



	if (BattleMode == 1) {

		if (p.x >= dwidth + 560 && p.x < dwidth + 640 && p.y >= 98 && p.y < 118) {
			focus = 14;
		}
		if (p.x >= dwidth + 540 && p.x <= dwidth + 560 && p.y >= 98 && p.y < 118) {
			BattleTerrain--;
			if (BattleTerrain < 0)BattleTerrain = 15;
		}
		if (p.x >= dwidth + 640 && p.x <= dwidth + 660 && p.y >= 98 && p.y < 118) {
			BattleTerrain++;
			BattleTerrain %= 16;
		}

		if (p.x >= 50 && p.x < 50 + 48 * BMW&&p.y >= 40 && p.y <= 40 + 48 * BMH) {
			i = (p.x - 50)*MapZoom / 48 + ViewX - 1;
			j = (p.y - 40)*MapZoom / 48 + ViewY - 1;

			NonBattleLand[select[mode]][i + (j)*NonBattleSize[select[mode]][0]] = BattleTerrain;
		}

		for (i = 0; i < 8; i++) {
			if (p.x >= dwidth + 575 && p.x < dwidth + 650 && p.y >= 320 + 20 * i&&p.y <= 340 + 20 * i) {
				focus = 16 + i;
			}

			if (p.x >= dwidth + 675 && p.x < dwidth + 750 && p.y >= 320 + 20 * i&&p.y <= 340 + 20 * i) {
				focus = 24 + i;
			}
		}
	}

	if(BattleMode==3){
		if (p.x >= 50 && p.x<50 + 48 * BMW&&p.y >= 40 && p.y <= 40 + 48 * BMH) {
			i = (p.x - 50)*MapZoom / 48 + ViewX;
			j = (p.y - 40)*MapZoom / 48 + ViewY;
			for (k = 0; k<NumNonBattleStart[select[mode]][BattleEntrance]; k++) {
				if (NonBattleStart[select[mode]][BattleEntrance][k][0] == i&&NonBattleStart[select[mode]][BattleEntrance][k][1] == j)BattleDrag = k;
			}
			if (BattleSelect != BattleDrag)subselect[mode][2] = 0;
			BattleSelect = BattleDrag;

		}
		if (p.x >= dwidth + 540 && p.x <= dwidth + 560 && p.y >= 98 && p.y<118) {
			BattleEntrance--;
			if (BattleEntrance<0)BattleEntrance = 3;
		}
		if (p.x >= dwidth + 560 && p.x<dwidth + 640 && p.y >= 98 && p.y<118) {
			focus = 11;
		}
		if (p.x >= dwidth + 640 && p.x <= dwidth + 660 && p.y >= 98 && p.y<118) {
			BattleEntrance++;
			BattleEntrance %= 4;
		}

		if (p.x >= dwidth + 540 && p.x <= dwidth + 560 && p.y >= 118 && p.y<138) {
			if (NumNonBattleStart[select[mode]][BattleEntrance]>0)NumNonBattleStart[select[mode]][BattleEntrance]--;
			if (NumNonBattleStart[select[mode]][BattleEntrance]<0)NumNonBattleStart[select[mode]][BattleEntrance] = 0;
		}
		if (p.x >= dwidth + 540 && p.x<dwidth + 640 && p.y >= 118 && p.y<138) {
			focus = 12;
		}
		if (p.x >= dwidth + 650 && p.x <= dwidth + 670 && p.y >= 118 && p.y<138) {
			NumNonBattleStart[select[mode]][BattleEntrance]++;
			if (NumNonBattleStart[select[mode]][BattleEntrance]>12)NumNonBattleStart[select[mode]][BattleEntrance] = 12;
			else {
				NonBattleStart[select[mode]][BattleEntrance][NumNonBattleStart[select[mode]][BattleEntrance] - 1][0] = 4 + ViewX;
				NonBattleStart[select[mode]][BattleEntrance][NumNonBattleStart[select[mode]][BattleEntrance] - 1][1] = 4 + ViewY;

				if (NonBattleStart[select[mode]][BattleEntrance][NumNonBattleStart[select[mode]][BattleEntrance] - 1][0] < 0)NonBattleStart[select[mode]][BattleEntrance][NumNonBattleStart[select[mode]][BattleEntrance] - 1][0] = 0;
				if (NonBattleStart[select[mode]][BattleEntrance][NumNonBattleStart[select[mode]][BattleEntrance] - 1][1] < 0)NonBattleStart[select[mode]][BattleEntrance][NumNonBattleStart[select[mode]][BattleEntrance] - 1][1] = 0;

				if (NonBattleStart[select[mode]][BattleEntrance][NumNonBattleStart[select[mode]][BattleEntrance] - 1][0] >= NonBattleSize[select[mode]][0]) {
					if (4 + ViewX < 0)
						NonBattleStart[select[mode]][BattleEntrance][NumNonBattleStart[select[mode]][BattleEntrance] - 1][0] = 1;
					else
						NonBattleStart[select[mode]][BattleEntrance][NumNonBattleStart[select[mode]][BattleEntrance] - 1][0] = NonBattleSize[select[mode]][0];
				}
				if (NonBattleStart[select[mode]][BattleEntrance][NumNonBattleStart[select[mode]][BattleEntrance] - 1][1] >= NonBattleSize[select[mode]][1])NonBattleStart[select[mode]][BattleEntrance][NumNonBattleStart[select[mode]][BattleEntrance] - 1][1] = NonBattleSize[select[mode]][1] - 1;

				BattleSelect = NumNonBattleStart[select[mode]][BattleEntrance] - 1;

				bool overlap;
				int l = 0;

				do {
					overlap = false;
					for (k = 0; k < NumNonBattleStart[select[mode]][BattleEntrance] - 1; k++) {
						if ((NonBattleStart[select[mode]][BattleEntrance][k][0] == NonBattleStart[select[mode]][BattleEntrance][NumNonBattleStart[select[mode]][BattleEntrance] - 1][0] && NonBattleStart[select[mode]][BattleEntrance][k][1] == NonBattleStart[select[mode]][BattleEntrance][NumNonBattleStart[select[mode]][BattleEntrance] - 1][1]) || (NonBattleStart[select[mode]][BattleEntrance][NumNonBattleStart[select[mode]][BattleEntrance] - 1][0]<0) || (NonBattleStart[select[mode]][BattleEntrance][NumNonBattleStart[select[mode]][BattleEntrance] - 1][1]<0)) {
							overlap = true;
							switch (l) {
								case 0:
									NonBattleStart[select[mode]][BattleEntrance][NumNonBattleStart[select[mode]][BattleEntrance] - 1][0] -= 1;
									NonBattleStart[select[mode]][BattleEntrance][NumNonBattleStart[select[mode]][BattleEntrance] - 1][1] -= 0;
									break;
								case 1:
								case 9:
								case 10:
								case 11:
									NonBattleStart[select[mode]][BattleEntrance][NumNonBattleStart[select[mode]][BattleEntrance] - 1][0] -= 0;
									NonBattleStart[select[mode]][BattleEntrance][NumNonBattleStart[select[mode]][BattleEntrance] - 1][1] -= 1;
									break;
								case 2:
								case 3:
								case 12:
								case 13:
								case 14:
								case 15:
									NonBattleStart[select[mode]][BattleEntrance][NumNonBattleStart[select[mode]][BattleEntrance] - 1][0] += 1;
									NonBattleStart[select[mode]][BattleEntrance][NumNonBattleStart[select[mode]][BattleEntrance] - 1][1] -= 0;
									break;
								case 4:
								case 5:
								case 16:
								case 17:
								case 18:
								case 19:
									NonBattleStart[select[mode]][BattleEntrance][NumNonBattleStart[select[mode]][BattleEntrance] - 1][0] -= 0;
									NonBattleStart[select[mode]][BattleEntrance][NumNonBattleStart[select[mode]][BattleEntrance] - 1][1] += 1;
									break;
								case 6:
								case 7:
								case 8:
								case 20:
								case 21:
								case 22:
								case 23:
									NonBattleStart[select[mode]][BattleEntrance][NumNonBattleStart[select[mode]][BattleEntrance] - 1][0] -= 1;
									NonBattleStart[select[mode]][BattleEntrance][NumNonBattleStart[select[mode]][BattleEntrance] - 1][1] += 0;
									break;
								default:
									overlap = false;
							}
							l++;
							break;
						}
					}
				} while (overlap);
			}
		}
	}

		
	if (p.x >= 20 && p.x <= 40 && p.y >= (BMH - 10) * 48 + 500 && p.y <= (BMH - 10) * 48 + 520) {
		MapZoom *= 2;
		if (MapZoom == 8)MapZoom = 1;

		if (ViewX >= MapSize[MapHeader[NonBattleHeaderPos[select[mode]]][1]][0] - 10 * MapZoom)ViewX = MapSize[MapHeader[NonBattleHeaderPos[select[mode]]][1]][0] - 10 * MapZoom;
		if (ViewY >= MapSize[MapHeader[NonBattleHeaderPos[select[mode]]][1]][1] - 10 * MapZoom)ViewY = MapSize[MapHeader[NonBattleHeaderPos[select[mode]]][1]][1] - 10 * MapZoom;

		if (ViewX<0)ViewX = 0;
		if (ViewY<0)ViewY = 0;
	}


GetClientRect(hWnd, &r);

