
	switch (wParam) {
		case VK_HOME:
			switch (BattleMode) {

				case 1:
					BattleTerrain--;
					if (BattleTerrain<0)BattleTerrain = 15;
					break;

				case 3:
					BattleEntrance--;
					if (BattleEntrance<0)BattleEntrance = 3;
					break;

			}
			break;
		case VK_END:
			switch (BattleMode) {

				case 1:
					BattleTerrain++;
					BattleTerrain %= 16;
					break;

				case 3:
					BattleEntrance++;
					BattleEntrance %= 4;
					break;

			}
			break;
		case VK_NEXT:
			select[mode] -= 1;
			select[mode] %= 12;
			BattleEntrance = NonBattleIndex[select[mode]][3];
			ViewX = 0;
			ViewY = 0;
			BattleSelect = -1;
			BattleDrag = -1;
			focus = 1;
			break;
		case VK_PRIOR:
			select[mode] += 1;
			select[mode] %= 12;
			BattleEntrance = NonBattleIndex[select[mode]][3];
			ViewX = 0;
			ViewY = 0;
			BattleSelect = -1;
			BattleDrag = -1;
			focus = 1;
			break;
		case VK_UP:
			if (ViewY>0)ViewY -= 1;
			break;
		case VK_LEFT:
			if (ViewX>0)ViewX -= 1;
			break;
		case VK_DOWN:
			if (ViewY<MapSize[MapHeader[NonBattleHeaderPos[select[mode]]][1]][1] - 10)ViewY += 1;
			break;
		case VK_RIGHT:
			if (ViewX<MapSize[MapHeader[NonBattleHeaderPos[select[mode]]][1]][0] - 10)ViewX += 1;
			break;
	}
