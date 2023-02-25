

GetClientRect(hWnd, &r);

	SelectObject(bmpdc, battle);
	BitBlt(memdc, 0, 10, 40, 40, bmpdc, 0, 0, SRCCOPY);
	SelectObject(bmpdc, mapon);
	BitBlt(memdc, 0, 50, 40, 40, bmpdc, 0, 0, SRCCOPY);

	BMW = 10 + dwidth / 48;
	BMH = 10 + dheight / 48;

	SelectObject(bmpdc, zoom);
	BitBlt(memdc, 20, (BMH - 10) * 48 + 500, 20, 20, bmpdc, 0, 0, SRCCOPY);

	m = MapHeader[NonBattleHeaderPos[select[mode]]][1];

	SelectObject(bmpdc, minus);
	BitBlt(memdc, 55, 8, 20, 20, bmpdc, 0, 0, SRCCOPY);

	sprintf(out, "Set: %d", select[mode]);
	if (focus == 1 && cursor)sprintf(out, "%s|", out);
	TextOut(memdc, 76, 10, out, strlen(out));

	SelectObject(bmpdc, plus);
	BitBlt(memdc, 140, 8, 20, 20, bmpdc, 0, 0, SRCCOPY);

	sprintf(out, "Map: %d", m);
	if (focus == 2 && cursor)sprintf(out, "%s|", out);
	TextOut(memdc, 176, 10, out, strlen(out));

	sprintf(out, "Music: %d", MapHeader[NonBattleHeaderPos[select[mode]]][0]);
	if (focus == 3 && cursor)sprintf(out, "%s|", out);
	TextOut(memdc, 238, 10, out, strlen(out));


	sprintf(out, "W: %d", NonBattleSize[select[mode]][0]);
	if (focus == 6 && cursor)sprintf(out, "%s|", out);
	TextOut(memdc, 428, 10, out, strlen(out));

	sprintf(out, "H: %d", NonBattleSize[select[mode]][1]);
	if (focus == 7 && cursor)sprintf(out, "%s|", out);
	TextOut(memdc, 478, 10, out, strlen(out));

	TextOut(memdc, 320, (BMH - 10) * 48 + 520, "Display Border", 14);
	if (DisplayBorder)SelectObject(bmpdc, checkon);
	else SelectObject(bmpdc, checkoff);
	BitBlt(memdc, 300, (BMH - 10) * 48 + 522, 13, 13, bmpdc, 0, 0, SRCCOPY);

	TextOut(memdc, 450, (BMH - 10) * 48 + 520, "Display Grid", 12);
	if (DisplayGrid)SelectObject(bmpdc, checkon);
	else SelectObject(bmpdc, checkoff);
	BitBlt(memdc, 430, (BMH - 10) * 48 + 522, 13, 13, bmpdc, 0, 0, SRCCOPY);


	TextOut(memdc, dwidth + 640, 10, "Editing", 7);


	TextOut(memdc, dwidth + 720, 30, "Terrain", 7);
	if (BattleMode == 1)SelectObject(bmpdc, checkon);
	else SelectObject(bmpdc, checkoff);
	BitBlt(memdc, dwidth + 700, 32, 13, 13, bmpdc, 0, 0, SRCCOPY);


	TextOut(memdc, dwidth + 720, 46, "Force", 5);
	if (BattleMode == 3)SelectObject(bmpdc, checkon);
	else SelectObject(bmpdc, checkoff);
	BitBlt(memdc, dwidth + 700, 48, 13, 13, bmpdc, 0, 0, SRCCOPY);


	SetBkMode(memdc, 2);
	for (u = 0; u<BMW*MapZoom; u++) {
		for (v = 0; v<BMH*MapZoom; v++) {
			if (u + ViewX >= MapSize[MapHeader[NonBattleHeaderPos[select[mode]]][1]][0] || v + ViewY >= MapSize[MapHeader[NonBattleHeaderPos[select[mode]]][1]][1])continue;
			for (i = 0; i<3; i++) {
				for (j = 0; j<3; j++) {
					l = MapData[m][u + ViewX + (v + ViewY)*MapSize[m][0]];
					if (l<660)l += MapTileset[m][0];
					else l += MapTileset[m][1] - 660;
					k = (Tiles[l][i * 2 + j * 6] & 0x07) * 256;
					k += Tiles[l][i * 2 + j * 6 + 1];
					k -= 0x3BE;

					if (k>255) {
						SelectObject(bmpdc, tileset[MapGraphics[m][1]]);
						k -= 256;
					} else SelectObject(bmpdc, tileset[MapGraphics[m][0]]);
					x = (k % 16) * 8;
					y = (k - k % 16) / 2;
					if (Tiles[l][i * 2 + j * 6] & 0x08) {
						x += 7;
						dx = -1;
					} else dx = 1;
					if (Tiles[l][i * 2 + j * 6] & 0x10) {
						y += 7;
						dy = -1;
					} else dy = 1;
					StretchBlt(memdc, 50 + (i * 16 + u * 48) / MapZoom, 40 + (j * 16 + v * 48) / MapZoom, 16 / MapZoom, 16 / MapZoom, bmpdc, x, y, 8 * dx, 8 * dy, SRCCOPY);
				}
			}
		}
	}
	if (DisplayGrid) {
		MoveToEx(memdc, 50 + u * 48 / MapZoom, 40, 0);
		LineTo(memdc, 50 + u * 48 / MapZoom, 40 + v * 48 / MapZoom);
		LineTo(memdc, 50, 40 + v * 48 / MapZoom);
	}
	brush = (HBRUSH)SelectObject(memdc, CreateSolidBrush(RGB(255, 255, 0)));
	if (DisplayBorder) {
		for (x = 0; x<NonBattleSize[select[mode]][0]; x++) {
			for (y = 0; y<NonBattleSize[select[mode]][1]; y++) {
				i = x - ViewX + 1;
				j = y - ViewY + 1;
				if (i >= 0 && i<BMW*MapZoom&&j >= 0 && j<BMH*MapZoom) {
					if (!x || x == NonBattleSize[select[mode]][0] - 1) {
						if (y<NonBattleSize[select[mode]][1] - 1)PatBlt(memdc, 50 + (i * 48 + 20) / MapZoom, 40 + (j * 48 + 20) / MapZoom, 8 / MapZoom, 28 / MapZoom, PATCOPY);
						if (y)PatBlt(memdc, 50 + (i * 48 + 20) / MapZoom, 40 + (j * 48) / MapZoom, 8 / MapZoom, 20 / MapZoom, PATCOPY);
					}
					if (!y || y == NonBattleSize[select[mode]][1] - 1) {
						if (x<NonBattleSize[select[mode]][0] - 1)PatBlt(memdc, 50 + (i * 48 + 20) / MapZoom, 40 + (j * 48 + 20) / MapZoom, 28 / MapZoom, 8 / MapZoom, PATCOPY);
						if (x)PatBlt(memdc, 50 + i * 48 / MapZoom, 40 + (j * 48 + 20) / MapZoom, 20 / MapZoom, 8 / MapZoom, PATCOPY);
					}
					if (x == NonBattleSize[select[mode]][0] - 1 && y == NonBattleSize[select[mode]][1] - 1) {
						PatBlt(memdc, 50 + (i * 48 + 20) / MapZoom, 40 + (j * 48 + 20) / MapZoom, 8 / MapZoom, 8 / MapZoom, PATCOPY);
					}
				}
			}
		}
	}
	DeleteObject(SelectObject(memdc, GetStockObject(NULL_BRUSH)));

	for (u = 0; u<BMW*MapZoom; u++) {
		for (v = 0; v<BMH*MapZoom; v++) {
			if (u + ViewX >= MapSize[MapHeader[NonBattleHeaderPos[select[mode]]][1]][0] || v + ViewY >= MapSize[MapHeader[NonBattleHeaderPos[select[mode]]][1]][1])continue;
			if (DisplayGrid) {
				MoveToEx(memdc, 50 + u * 48 / MapZoom, 40 + v * 48 / MapZoom, 0);
				LineTo(memdc, 50 + (u * 48 + 48) / MapZoom, 40 + v * 48 / MapZoom);
				MoveToEx(memdc, 50 + u * 48 / MapZoom, 40 + v * 48 / MapZoom, 0);
				LineTo(memdc, 50 + u * 48 / MapZoom, 40 + (v * 48 + 48) / MapZoom);
			}
			if (BattleMode==1 && MapZoom<4) {
				i = u + ViewX - 1;
				j = v + ViewY - 1;
				if (i<NonBattleSize[select[mode]][0] && j<NonBattleSize[select[mode]][1] && i >= 0 && j >= 0) {
					sprintf(out, "%d", NonBattleLand[select[mode]][i + (j)*NonBattleSize[select[mode]][0]]);
					TextOut(memdc, 50 + u * 48 / MapZoom, 40 + v * 48 / MapZoom, out, strlen(out));
					/*k=i+(j)*NonBattleSize[select[mode]][0];
					k = BattleLand[select[mode]][k];
					k = BattleLandIndexes[select[mode]][k];
					k = Terrain[k][0];
					sprintf(out,"%d",LandEffectPercent[k+16]);
					TextOut(memdc,50+u*48,56+v*48,out,strlen(out));*/
				}
			}

			i = u + ViewX;
			j = v + ViewY;
			pen = (HPEN)SelectObject(memdc, CreatePen(PS_SOLID, 2, RGB(255, 255, 255)));
			for (k = 0; k<NumNonBattleStart[select[mode]][BattleEntrance]; k++) {
				if (NonBattleStart[select[mode]][BattleEntrance][k][0] == i&&NonBattleStart[select[mode]][BattleEntrance][k][1] == j) {
					if (BattleSelect == k&&BattleMode == 3)Rectangle(memdc, 50 + u * 48 / MapZoom + 1, 40 + v * 48 / MapZoom + 1, 50 + (u * 48 + 48) / MapZoom + 1, 40 + (v * 48 + 48) / MapZoom + 1);
					for (dx = 0; dx<24; dx++) {
						for (dy = 0; dy<24; dy++) {
							switch (MapZoom) {
								case 1:
									for (x = 0; x<2; x++) {
										for (y = 0; y<2; y++) {
											width = MSSize[k][0][0];
											s = MapSprites[k][0][dx + cursor * 24 + dy*width];
											if (s) {
												if (MSPalette[k])SetPixel(memdc, 50 + u * 48 + dx * 2 + x, 40 + v * 48 + dy * 2 + y, RGB(EMSPalette[s][0], EMSPalette[s][1], EMSPalette[s][2]));
												else SetPixel(memdc, 50 + u * 48 + dx * 2 + x, 40 + v * 48 + dy * 2 + y, RGB(FMSPalette[s][0], FMSPalette[s][1], FMSPalette[s][2]));
											}
										}
									}
									break;
								case 2:
									width = MSSize[k][0][0];
									s = MapSprites[k][0][dx + cursor * 24 + dy*width];
									if (s) {
										if (MSPalette[k])SetPixel(memdc, 50 + u * 24 + dx, 40 + v * 24 + dy, RGB(EMSPalette[s][0], EMSPalette[s][1], EMSPalette[s][2]));
										else SetPixel(memdc, 50 + u * 24 + dx, 40 + v * 24 + dy, RGB(FMSPalette[s][0], FMSPalette[s][1], FMSPalette[s][2]));
									}
									break;
								case 4:
									if (dx % 2 == 0 && dy % 2 == 0) {
										width = MSSize[k][0][0];
										s = MapSprites[k][0][dx + cursor * 24 + dy*width];
										if (s) {
											if (MSPalette[k])SetPixel(memdc, 50 + u * 12 + dx / 2, 40 + v * 12 + dy / 2, RGB(EMSPalette[s][0], EMSPalette[s][1], EMSPalette[s][2]));
											else SetPixel(memdc, 50 + u * 12 + dx / 2, 40 + v * 12 + dy / 2, RGB(FMSPalette[s][0], FMSPalette[s][1], FMSPalette[s][2]));
										}
									}
									break;
							}
						}
					}
					break;
				}
			}
			DeleteObject(SelectObject(memdc, pen));
			
		}
	}
	SelectObject(memdc, brush);
	SetBkMode(memdc, 1);

	GetCursorPos(&p);
	ScreenToClient(hWnd, &p);
	p.y -= 40;
	if (p.x >= 50 && p.x <= (BMW - 10) * 48 + 530 && p.y >= 40 && p.y <= (BMH - 10) * 48 + 520) {
		x = (p.x - 50)*MapZoom / 48;
		y = (p.y - 40)*MapZoom / 48;
		x += ViewX;
		y += ViewY;
		sprintf(out, "%d, %d", x, y);
		if (!menu)TextOut(memdc, 50, (BMH - 10) * 48 + 520, out, strlen(out));
	}

	int ti;

	if (BattleMode == 1) {
		SelectObject(bmpdc, minus);
		BitBlt(memdc, dwidth + 540, 98, 20, 20, bmpdc, 0, 0, SRCCOPY);

		sprintf(out, "Terrain: %d", BattleTerrain);
		if (focus == 14 && cursor)sprintf(out, "%s|", out);
		TextOut(memdc, dwidth + 561, 100, out, strlen(out));



		SelectObject(bmpdc, plus);
		BitBlt(memdc, dwidth + 640, 98, 20, 20, bmpdc, 0, 0, SRCCOPY);

		ti = Terrain[NonBattleLandIndexes[select[mode]][BattleTerrain]][0];

		sprintf(out, "Land Effect %%");
		TextOut(memdc, dwidth + 561, 140, out, strlen(out));

		sprintf(out, "%d, %d, %d, %d, %d, %d, %d, %d", LandEffectPercent[ti], LandEffectPercent[ti + 16], LandEffectPercent[ti + 16 * 2], LandEffectPercent[ti + 16 * 3], LandEffectPercent[ti + 16 * 4], LandEffectPercent[ti + 16 * 5], LandEffectPercent[ti + 16 * 6], LandEffectPercent[ti + 16 * 7]);
		TextOut(memdc, dwidth + 575, 160, out, strlen(out));

		sprintf(out, "Movement Cost");
		TextOut(memdc, dwidth + 561, 200, out, strlen(out));

		sprintf(out, "%d, %d, %d, %d", LandEffectType[ti], LandEffectType[ti + 16], LandEffectType[ti + 16 * 2], LandEffectType[ti + 16 * 3]);
		TextOut(memdc, dwidth + 575, 220, out, strlen(out));

		sprintf(out, "%d, %d, %d, %d", LandEffectType[ti + 16 * 4], LandEffectType[ti + 16 * 5], LandEffectType[ti + 16 * 6], LandEffectType[ti + 16 * 7]);
		TextOut(memdc, dwidth + 575, 240, out, strlen(out));


		sprintf(out, "Terrain Set");
		TextOut(memdc, dwidth + 561, 300, out, strlen(out));

		for (i = 0; i < 8; i++) {
			sprintf(out, "%d", NonBattleLandIndexes[select[mode]][i]);
			if (focus == 16 + i&&cursor)sprintf(out, "%s|", out);
			TextOut(memdc, dwidth + 575, 320 + 20 * i, out, strlen(out));

			sprintf(out, "%d", NonBattleLandIndexes[select[mode]][i + 8]);
			if (focus == 24 + i&&cursor)sprintf(out, "%s|", out);
			TextOut(memdc, dwidth + 675, 320 + 20 * i, out, strlen(out));
		}
	}

	if (BattleMode == 3) {
		SelectObject(bmpdc, minus);
		BitBlt(memdc, dwidth + 540, 98, 20, 20, bmpdc, 0, 0, SRCCOPY);

		sprintf(out, "Entrance: %d", BattleEntrance);
		if (focus == 11 && cursor)sprintf(out, "%s|", out);
		TextOut(memdc, dwidth + 561, 100, out, strlen(out));

		SelectObject(bmpdc, plus);
		BitBlt(memdc, dwidth + 640, 98, 20, 20, bmpdc, 0, 0, SRCCOPY);

		SelectObject(bmpdc, minus);
		BitBlt(memdc, dwidth + 540, 118, 20, 20, bmpdc, 0, 0, SRCCOPY);

		sprintf(out, "Members: %d", NumNonBattleStart[select[mode]][BattleEntrance]);
		if (focus == 12 && cursor)sprintf(out, "%s|", out);
		TextOut(memdc, dwidth + 561, 120, out, strlen(out));

		SelectObject(bmpdc, plus);
		BitBlt(memdc, dwidth + 650, 118, 20, 20, bmpdc, 0, 0, SRCCOPY);
	}