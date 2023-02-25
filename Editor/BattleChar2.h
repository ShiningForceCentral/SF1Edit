c = wParam;


	if (c == 'z') {
		MapZoom *= 2;
		if (MapZoom == 8)MapZoom = 1;
	}
	switch (focus) {

		case 1:
			val = c - '0';
			if (val >= 0 && val < 10) {
				i = select[mode];
				if (i < 10) {
					i *= 10;
					i += val;
					select[mode] = i;
				}
			}
			if (c == 8) {
				i = select[mode];
				i = i - i % 10;
				i /= 10;
				select[mode] = i;
			}
			if (select[mode] > NUM_BATTLES)select[mode] = NUM_BATTLES;
			ViewX = 0;
			ViewY = 0;
			BattleSelect = -1;
			BattleDrag = -1;
			BattleEntrance = BattleIndex[select[mode]][3];
			break;
		case 14:

			val = c - '0';
			if (val >= 0 && val < 10) {
				i = BattleTerrain;
				if (i < 10) {
					i *= 10;
					i += val;
					BattleTerrain = i;
				}
			}
			if (c == 8) {
				i = BattleTerrain;
				i = i - i % 10;
				i /= 10;
				BattleTerrain = i;
			}
			if (BattleTerrain > 15)BattleTerrain = 15;
			break;
	}
		
	if (focus>15 && subfocus<32) {
		val = c - '0';
		if (val >= 0 && val<10) {
			i = NonBattleLandIndexes[select[mode]][focus - 16];
			if (i<100) {
				i *= 10;
				i += val;
				NonBattleLandIndexes[select[mode]][focus - 16] = i;
			}
		}
		if (c == 8) {
			i = NonBattleLandIndexes[select[mode]][focus - 16];
			i = i - i % 10;
			i /= 10;
			NonBattleLandIndexes[select[mode]][focus - 16] = i;
		}
	}

