GetCursorPos(&p);
ScreenToClient(hWnd, &p);
p.y -= 40;



	if (BattleMapDrag) {
		if (p.x - BattleDragPos[0] >= 48 / MapZoom) {
			if (ViewX>0) {
				ViewX--;
				BattleDragPos[0] += 48 / MapZoom;
				InvalidateRect(hWnd, NULL, 0);
			}
		}
		if (p.x - BattleDragPos[0] <= -48 / MapZoom) {
			if (ViewX<MapSize[MapHeader[NonBattleHeaderPos[select[mode]]][1]][0] - 10) {
				ViewX++;
				BattleDragPos[0] -= 48 / MapZoom;
				InvalidateRect(hWnd, NULL, 0);
			}
		}

		if (p.y - BattleDragPos[1] >= 48 / MapZoom) {
			if (ViewY>0) {
				ViewY--;
				BattleDragPos[1] += 48 / MapZoom;
				InvalidateRect(hWnd, NULL, 0);
			}
		}
		if (p.y - BattleDragPos[1] <= -48 / MapZoom) {
			if (ViewY<MapSize[MapHeader[NonBattleHeaderPos[select[mode]]][1]][1] - 10) {
				ViewY++;
				BattleDragPos[1] -= 48 / MapZoom;
				InvalidateRect(hWnd, NULL, 0);
			}
		}
	}

	if (!menu) {
		PatBlt(memdc, 50, 560 + 48 * (BMH - 10), 150, 20, PATCOPY);
		if (p.x >= 50 && p.x <= (BMW - 10) * 48 + 530 && p.y >= 40 && p.y <= (BMH - 10) * 48 + 520) {
			x = (p.x - 50)*MapZoom / 48;
			y = (p.y - 40)*MapZoom / 48;
			x += ViewX;
			y += ViewY;
			sprintf(out, "%d, %d", x, y);
			TextOut(memdc, 50, (BMH - 10) * 48 + 560, out, strlen(out));
		}
		BitBlt(hdc, 50, 560 + 48 * (BMH - 10), 150, 20, memdc, 50, 560 + 48 * (BMH - 10), SRCCOPY);
	}

	if (BattleMode == 1) {
		if (wParam &	MK_LBUTTON) {
			if (p.x >= 50 && p.x < 50 + 48 * BMW&&p.y >= 40 && p.y <= 40 + 48 * BMH) {
				i = (p.x - 50)*MapZoom / 48 + ViewX - 1;
				j = (p.y - 40)*MapZoom / 48 + ViewY - 1;
				NonBattleLand[select[mode]][i + (j)*NonBattleSize[select[mode]][0]] = BattleTerrain;
			}
		}
	}
	if (BattleMode == 3) {
		if (wParam &	MK_LBUTTON) {
			if (BattleDrag >= 0 && p.x >= 50 && p.x<50 + 48 * BMW&&p.y >= 40 && p.y <= 40 + 48 * BMH) {
				i = (p.x - 50)*MapZoom / 48 + ViewX;
				j = (p.y - 40)*MapZoom / 48 + ViewY;
				if (i >= 0 && i <= NonBattleSize[select[mode]][0] + 1) {
					if (NonBattleStart[select[mode]][BattleEntrance][BattleDrag][0] != i) {
						InvalidateRect(hWnd, NULL, 0);
						NonBattleStart[select[mode]][BattleEntrance][BattleDrag][0] = i;
					}
				}
				if (j >= 0 && j <= BattleSize[select[mode]][1] + 1) {
					if (NonBattleStart[select[mode]][BattleEntrance][BattleDrag][1] != j) {
						InvalidateRect(hWnd, NULL, 0);
						NonBattleStart[select[mode]][BattleEntrance][BattleDrag][1] = j;
					}
				}
			}
		}
	}

