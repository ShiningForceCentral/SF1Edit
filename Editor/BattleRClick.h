if(submode[mode]==2){
	switch(BattleMode){
		case 1:
			if(p.x>=50&&p.x<50+48*BMW&&p.y>=40&&p.y<=40+48*BMH){
				i = (p.x-50)*MapZoom/48+ViewX-MapHeader[BattleHeaderPos[select[mode]]][3]-1;
				j = (p.y-40)*MapZoom/48+ViewY-MapHeader[BattleHeaderPos[select[mode]]][5]-1;
				BattleTerrain=BattleLand[select[mode]][i+(j)*BattleSize[select[mode]][0]];
			}
			break;
		case 2:
			if(p.x>=50&&p.x<50+48*BMW&&p.y>=40&&p.y<=40+48*BMH){
				i = (p.x-50)*MapZoom/48+ViewX-MapHeader[BattleHeaderPos[select[mode]]][3]-1;
				j = (p.y-40)*MapZoom/48+ViewY-MapHeader[BattleHeaderPos[select[mode]]][5]-1;
				if(BattleLand[select[mode]][i+(j)*BattleSize[select[mode]][0]]){
					BattleReg=BattleAI[select[mode]][i+(j)*BattleSize[select[mode]][0]];
				}
			}
			break;
		case 4:
			if (p.x >= 50 && p.x<50 + 48 * BMW&&p.y >= 40 && p.y <= 40 + 48 * BMH) {
				if (BattleExitSet == 0) {
					i = (p.x - 50)*MapZoom / 48 + ViewX - MapHeader[BattleHeaderPos[select[mode]]][3];
					j = (p.y - 40)*MapZoom / 48 + ViewY - MapHeader[BattleHeaderPos[select[mode]]][5];
				} else {
					i = (p.x - 50)*MapZoom / 48 + ViewX;
					j = (p.y - 40)*MapZoom / 48 + ViewY;
				}
				if (j >= 0) {
					BattleExit = Exits[BattExits[select[mode]][BattleExitSet]][i + (j)*MapSize[MapHeader[BattleHeaderPos[select[mode]]][1]][0]];

					BattleTele = Exits[128+BattExits[select[mode]][BattleExitSet]][i + (j)*MapSize[MapHeader[BattleHeaderPos[select[mode]]][1]][0]];
				}
			}
			break;
	}
}