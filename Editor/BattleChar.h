			c=wParam;
			if(submode[mode]==0){
				if(focus>1&&focus<2+NumEnemies[select[mode]]*8){
					val=c-'0';
					if(val>=0&&val<10){
						i=Battle[select[mode]][((focus-2)-(focus-2)%8)/8][(focus-2)%8];
						if(i<100){
							i*=10;
							i+=val;
							Battle[select[mode]][((focus-2)-(focus-2)%8)/8][(focus-2)%8]=i;
						}
					}
					if(c==8){
						i=Battle[select[mode]][((focus-2)-(focus-2)%8)/8][(focus-2)%8];
						i=i-i%10;
						i/=10;
						Battle[select[mode]][((focus-2)-(focus-2)%8)/8][(focus-2)%8]=i;
					}
				}
			}
			if(submode[mode]==1){
				switch(focus){
					case 1:
						val=c-'0';
						if(val>=0&&val<10){
							i=NumBehaviors[select[mode]][menu];
							if(i<10){
								i*=10;
								i+=val;
								NumBehaviors[select[mode]][menu]=i;
							}
						}
						if(c==8){
							i=NumBehaviors[select[mode]][menu];
							i=i-i%10;
							i/=10;
							NumBehaviors[select[mode]][menu]=i;
						}
						if(NumBehaviors[select[mode]][menu]>8)NumBehaviors[select[mode]][menu]=8;
						break;
					case 2:
						val=c-'0';
						if(val>=0&&val<10){
							i=Behaviors[select[mode]][menu][subfocus][1];
							if(i<100){
								i*=10;
								i+=val;
								Behaviors[select[mode]][menu][subfocus][1]=i;
							}
						}
						if(c==8){
							i=Behaviors[select[mode]][menu][subfocus][1];
							i=i-i%10;
							i/=10;
							Behaviors[select[mode]][menu][subfocus][1]=i;
						}
						Behaviors[select[mode]][menu][subfocus][1]%=256;
						break;
					case 3:
						val=c-'0';
						if(val>=0&&val<10){
							i=Behaviors[select[mode]][menu][subfocus][2];
							if(i<100){
								i*=10;
								i+=val;
								Behaviors[select[mode]][menu][subfocus][2]=i;
							}
						}
						if(c==8){
							i=Behaviors[select[mode]][menu][subfocus][2];
							i=i-i%10;
							i/=10;
							Behaviors[select[mode]][menu][subfocus][2]=i;
						}
						Behaviors[select[mode]][menu][subfocus][2]%=256;
						break;
					case 4:
						val=c-'0';
						if(val>=0&&val<10){
							i=Behaviors[select[mode]][menu][subfocus][3];
							if(i<100){
								i*=10;
								i+=val;
								Behaviors[select[mode]][menu][subfocus][3]=i;
							}
						}
						if(c==8){
							i=Behaviors[select[mode]][menu][subfocus][3];
							i=i-i%10;
							i/=10;
							Behaviors[select[mode]][menu][subfocus][3]=i;
						}
						Behaviors[select[mode]][menu][subfocus][3]%=256;
						break;
				}
			}
			if(submode[mode]==2){
				if(c=='z'){
					MapZoom*=2;
					if(MapZoom==8)MapZoom=1;
				}
				switch(focus){
					case -1:
						val = c - '0';
						if (val >= 0 && val<10) {
							i = NumBehaviors[select[mode]][BattleSelect];
							if (i<10) {
								i *= 10;
								i += val;
								NumBehaviors[select[mode]][BattleSelect] = i;
							}
						}
						if (c == 8) {
							i = NumBehaviors[select[mode]][BattleSelect];
							i = i - i % 10;
							i /= 10;
							NumBehaviors[select[mode]][BattleSelect] = i;
						}
						if (NumBehaviors[select[mode]][BattleSelect]>8)NumBehaviors[select[mode]][BattleSelect] = 8;
						break;
					case -2:
						val = c - '0';
						if (val >= 0 && val<10) {
							i = Behaviors[select[mode]][BattleSelect][subselect[mode][2]][2];
							if (i<100) {
								i *= 10;
								i += val;
								Behaviors[select[mode]][BattleSelect][subselect[mode][2]][2] = i;
							}
						}
						if (c == 8) {
							i = Behaviors[select[mode]][BattleSelect][subselect[mode][2]][2];
							i = i - i % 10;
							i /= 10;
							Behaviors[select[mode]][BattleSelect][subselect[mode][2]][2] = i;
						}
						break;
					case -3:
						val = c - '0';
						if (val >= 0 && val<10) {
							i = Behaviors[select[mode]][BattleSelect][subselect[mode][2]][3];
							if (i<100) {
								i *= 10;
								i += val;
								Behaviors[select[mode]][BattleSelect][subselect[mode][2]][3] = i;
							}
						}
						if (c == 8) {
							i = Behaviors[select[mode]][BattleSelect][subselect[mode][2]][3];
							i = i - i % 10;
							i /= 10;
							Behaviors[select[mode]][BattleSelect][subselect[mode][2]][3] = i;
						}
						break;


						//i = BattleTele % MapSize[MapHeader[BattleHeaderPos[select[mode]]][1]][0] + MapHeader[BattleHeaderPos[select[mode]]][3];
						//j = (BattleTele - i) / MapSize[MapHeader[BattleHeaderPos[select[mode]]][1]][0] + MapHeader[BattleHeaderPos[select[mode]]][5];

					case -4:
						val = c - '0';
						if (val >= 0 && val<10) {
							i = BattleTele % MapSize[MapHeader[BattleHeaderPos[select[mode]]][1]][0] + MapHeader[BattleHeaderPos[select[mode]]][3];
							j = i;
							if (i<100) {
								i *= 10;
								i += val;
								if (i > 64)i = 64;
								BattleTele = BattleTele - j + i;
							}
						}
						if (c == 8) {
							i = BattleTele % MapSize[MapHeader[BattleHeaderPos[select[mode]]][1]][0] + MapHeader[BattleHeaderPos[select[mode]]][3];
							j = i;
							i = i - i % 10;
							i /= 10;
							BattleTele = BattleTele - j + i;
						}
						break;
					case -5:
						val = c - '0';
						if (val >= 0 && val<10) {
							i = BattleTele % MapSize[MapHeader[BattleHeaderPos[select[mode]]][1]][0] + MapHeader[BattleHeaderPos[select[mode]]][3];
							j = i;
							i = (BattleTele - i) / MapSize[MapHeader[BattleHeaderPos[select[mode]]][1]][0] + MapHeader[BattleHeaderPos[select[mode]]][5];
							if (i<100) {
								i *= 10;
								i += val;
								if (i > 64)i = 64;
								BattleTele = i * MapSize[MapHeader[BattleHeaderPos[select[mode]]][1]][0] + MapHeader[BattleHeaderPos[select[mode]]][5] + j;
							}
						}
						if (c == 8) {
							i = BattleTele % MapSize[MapHeader[BattleHeaderPos[select[mode]]][1]][0] + MapHeader[BattleHeaderPos[select[mode]]][3];
							j = i;
							i = (BattleTele - i) / MapSize[MapHeader[BattleHeaderPos[select[mode]]][1]][0] + MapHeader[BattleHeaderPos[select[mode]]][5];
							i = i - i % 10;
							i /= 10;
							BattleTele = i * MapSize[MapHeader[BattleHeaderPos[select[mode]]][1]][0] + MapHeader[BattleHeaderPos[select[mode]]][5] + j;
						}
						break;

					case 1:
						val=c-'0';
						if(val>=0&&val<10){
							i=select[mode];
							if(i<10){
								i*=10;
								i+=val;
								select[mode]=i;
							}
						}
						if(c==8){
							i=select[mode];
							i=i-i%10;
							i/=10;
							select[mode]=i;
						}
						if(select[mode]>NUM_BATTLES)select[mode]= NUM_BATTLES;
						ViewX=0;
						ViewY=0;
						BattleSelect=-1;
						BattleDrag=-1;
						BattleEntrance=BattleIndex[select[mode]][3];
						break;
					case 2:
						val=c-'0';
						if(val>=0&&val<10){
							i=MapHeader[BattleHeaderPos[select[mode]]][1];
							if(i<10){
								i*=10;
								i+=val;
								MapHeader[BattleHeaderPos[select[mode]]][1]=i;
							}
						}
						if(c==8){
							i=MapHeader[BattleHeaderPos[select[mode]]][1];
							i=i-i%10;
							i/=10;
							MapHeader[BattleHeaderPos[select[mode]]][1]=i;
						}
						if(MapHeader[BattleHeaderPos[select[mode]]][1]>43)MapHeader[BattleHeaderPos[select[mode]]][1]=43;
						break;
					case 3:
						val=c-'0';
						if(val>=0&&val<10){
							i=MapHeader[BattleHeaderPos[select[mode]]][0];
							if(i<100){
								i*=10;
								i+=val;
								MapHeader[BattleHeaderPos[select[mode]]][0]=i;
							}
						}
						if(c==8){
							i=MapHeader[BattleHeaderPos[select[mode]]][0];
							i=i-i%10;
							i/=10;
							MapHeader[BattleHeaderPos[select[mode]]][0]=i;
						}
						if(MapHeader[BattleHeaderPos[select[mode]]][0]>255)MapHeader[BattleHeaderPos[select[mode]]][0]=255;
						break;
					case 4:
						val=c-'0';
						if(val>=0&&val<10){
							i=MapHeader[BattleHeaderPos[select[mode]]][3];
							if(i<10){
								i*=10;
								i+=val;
								MapHeader[BattleHeaderPos[select[mode]]][3]=i;
							}
						}
						if(c==8){
							i=MapHeader[BattleHeaderPos[select[mode]]][3];
							i=i-i%10;
							i/=10;
							MapHeader[BattleHeaderPos[select[mode]]][3]=i;
						}
						if(MapHeader[BattleHeaderPos[select[mode]]][3]>64)MapHeader[BattleHeaderPos[select[mode]]][3]=64;
						break;
					case 5:
						val=c-'0';
						if(val>=0&&val<10){
							i=MapHeader[BattleHeaderPos[select[mode]]][5];
							if(i<10){
								i*=10;
								i+=val;
								MapHeader[BattleHeaderPos[select[mode]]][5]=i;
							}
						}
						if(c==8){
							i=MapHeader[BattleHeaderPos[select[mode]]][5];
							i=i-i%10;
							i/=10;
							MapHeader[BattleHeaderPos[select[mode]]][5]=i;
						}
						if(MapHeader[BattleHeaderPos[select[mode]]][5]>64)MapHeader[BattleHeaderPos[select[mode]]][5]=64;
						break;
					case 6:
						val=c-'0';
						if(val>=0&&val<10){
							i=BattleSize[select[mode]][0];
							if(i<10){
								i*=10;
								i+=val;
								BattleSize[select[mode]][0]=i;
							}
						}
						if(c==8){
							i=BattleSize[select[mode]][0];
							i=i-i%10;
							i/=10;
							BattleSize[select[mode]][0]=i;
						}
						if(BattleSize[select[mode]][0]>64)BattleSize[select[mode]][0]=64;
						break;
					case 7:
						val=c-'0';
						if(val>=0&&val<10){
							i=BattleSize[select[mode]][1];
							if(i<10){
								i*=10;
								i+=val;
								BattleSize[select[mode]][1]=i;
							}
						}
						if(c==8){
							i=BattleSize[select[mode]][1];
							i=i-i%10;
							i/=10;
							BattleSize[select[mode]][1]=i;
						}
						if(BattleSize[select[mode]][1]>64)BattleSize[select[mode]][1]=64;
						break;
					case 8:
						val=c-'0';
						if(val>=0&&val<10){
							i=Battle[select[mode]][BattleSelect][4];
							if(i<10){
								i*=10;
								i+=val;
								Battle[select[mode]][BattleSelect][4]=i;
							}
						}
						if(c==8){
							i=Battle[select[mode]][BattleSelect][4];
							i=i-i%10;
							i/=10;
							Battle[select[mode]][BattleSelect][4]=i;
						}
						break;
					case 9:
						val=c-'0';
						if(val>=0&&val<10){
							i=Battle[select[mode]][BattleSelect][5];
							if(i<10){
								i*=10;
								i+=val;
								Battle[select[mode]][BattleSelect][5]=i;
							}
						}
						if(c==8){
							i=Battle[select[mode]][BattleSelect][5];
							i=i-i%10;
							i/=10;
							Battle[select[mode]][BattleSelect][5]=i;
						}
						break;
					case 10:
						val=c-'0';
						if(val>=0&&val<10){
							i=Battle[select[mode]][BattleSelect][7];
							if(i<100){
								i*=10;
								i+=val;
								Battle[select[mode]][BattleSelect][7]=i;
							}
						}
						if(c==8){
							i=Battle[select[mode]][BattleSelect][7];
							i=i-i%10;
							i/=10;
							Battle[select[mode]][BattleSelect][7]=i;
						}
						if(Battle[select[mode]][BattleSelect][7]>255)Battle[select[mode]][BattleSelect][7]=255;
						break;
					case 11:
						val=c-'0';
						if(val>=0&&val<10){
							i=BattleEntrance;
							if(i<10){
								i*=10;
								i+=val;
								BattleEntrance=i;
							}
						}
						if(c==8){
							i=BattleEntrance;
							i=i-i%10;
							i/=10;
							BattleEntrance=i;
						}
						if(BattleEntrance>3)BattleEntrance=3;
						break;
					case 12:
						val=c-'0';
						if(val>=0&&val<10){
							i=NumBattleStart[select[mode]][BattleEntrance];
							if(i<10){
								i*=10;
								i+=val;
								NumBattleStart[select[mode]][BattleEntrance]=i;
							}
						}
						if(c==8){
							i=NumBattleStart[select[mode]][BattleEntrance];
							i=i-i%10;
							i/=10;
							NumBattleStart[select[mode]][BattleEntrance]=i;
						}
						if(NumBattleStart[select[mode]][BattleEntrance]>12)NumBattleStart[select[mode]][BattleEntrance]=12;
						break;
					case 13:
						if (BattleMode == 4) {
							val = c - '0';
							if (val >= 0 && val < 10) {
								i = BattleExitSet;
								if (i < 10) {
									i *= 10;
									i += val;
									BattleExitSet = i;
								}
							}
							if (c == 8) {
								i = BattleExitSet;
								i = i - i % 10;
								i /= 10;
								BattleExitSet = i;
							}
							if (BattleExitSet > 2)BattleExitSet = 2;
							if (BattExits[select[mode]][BattleExitSet] == 255)BattleExitSet = 0;
						} else {
							val = c - '0';
							if (val >= 0 && val < 10) {
								i = BattleReg;
								if (i < 10) {
									i *= 10;
									i += val;
									BattleReg = i;
								}
							}
							if (c == 8) {
								i = BattleReg;
								i = i - i % 10;
								i /= 10;
								BattleReg = i;
							}
							if (BattleReg > 7)BattleReg = 7;
						}
						break;
					case 14:
						if (BattleMode == 4) {
							val = c - '0';
							if (val >= 0 && val < 10) {
								i = BattleExit;
								if (i < 10) {
									i *= 10;
									i += val;
									BattleExit = i;
								}
							}
							if (c == 8) {
								i = BattleExit;
								i = i - i % 10;
								i /= 10;
								BattleExit = i;
							}
							if (BattleExit > 7)BattleExit = 7;
						} else {
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
						}
						break;
					case 15:
						val=c-'0';
						if(val>=0&&val<10){
							i=Battle[select[mode]][BattleSelect][6];
							if(i<100){
								i*=10;
								i+=val;
								Battle[select[mode]][BattleSelect][6]=i;
							}
						}
						if(c==8){
							i=Battle[select[mode]][BattleSelect][6];
							i=i-i%10;
							i/=10;
							Battle[select[mode]][BattleSelect][6]=i;
						}
						if(Battle[select[mode]][BattleSelect][6]>255)Battle[select[mode]][BattleSelect][6]=255;
						break;
				}

				if(focus>15&&subfocus<32){
					val=c-'0';
					if(val>=0&&val<10){
						i=BattleLandIndexes[select[mode]][focus-16];
						if(i<100){
							i*=10;
							i+=val;
							BattleLandIndexes[select[mode]][focus-16]=i;
						}
					}
					if(c==8){
						i=BattleLandIndexes[select[mode]][focus-16];
						i=i-i%10;
						i/=10;
						BattleLandIndexes[select[mode]][focus-16]=i;
					}
				}

			}


			if(submode[mode]==3){
				if(select[mode]<7){
					if(focus>0&&subfocus+30*select[mode]<125){
						val=c-'0';
						if(val>=0&&val<10){
							i=Terrain[subfocus+30*select[mode]][focus-1];
							if(i<100){
								i*=10;
								i+=val;
								Terrain[subfocus+30*select[mode]][focus-1]=i;
							}
						}
						if(c==8){
							i=Terrain[subfocus+30*select[mode]][focus-1];
							i=i-i%10;
							i/=10;
							Terrain[subfocus+30*select[mode]][focus-1]=i;
						}
					}
				} else {
					if(focus>0&&focus<9){
						val=c-'0';
						if(val>=0&&val<10){
							i=LandEffectPercent[(focus-1)*16+(select[mode]-7)];
							if(i<100){
								i*=10;
								i+=val;
								LandEffectPercent[(focus-1)*16+(select[mode]-7)]=i;
							}
						}
						if(c==8){
							i=LandEffectPercent[(focus-1)*16+(select[mode]-7)];
							i=i-i%10;
							i/=10;
							LandEffectPercent[(focus-1)*16+(select[mode]-7)]=i;
						}
						if(LandEffectPercent[(focus-1)*16+(select[mode]-7)]>99)LandEffectPercent[(focus-1)*16+(select[mode]-7)]=99;
					} else if(focus>0){
						val=c-'0';
						if(val>=0&&val<10){
							i=LandEffectType[(focus-9)*16+(select[mode]-7)];
							if(i<100){
								i*=10;
								i+=val;
								if(i>255)i=255;
								LandEffectType[(focus-9)*16+(select[mode]-7)]=i;
							}
						}
						if(c==8){
							i=LandEffectType[(focus-9)*16+(select[mode]-7)];
							i=i-i%10;
							i/=10;
							LandEffectType[(focus-9)*16+(select[mode]-7)]=i;
						}
					}
				}
			}

			if(submode[mode]==4){
					if(focus){
					val=c-'0';
					int l = ((focus - 1)-((focus-1)%2))/2;
					int m = ((focus - 1)%2);
					if(val>=0&&val<10){
						i=AIPaths[select[mode]][menu][subselect[mode][1]][l][m];
						if(i<10){
							i*=10;
							i+=val;
							AIPaths[select[mode]][menu][subselect[mode][1]][l][m]=i;
						}
					}
					if(c==8){
						i=AIPaths[select[mode]][menu][subselect[mode][1]][l][m];
						i=i-i%10;
						i/=10;
						AIPaths[select[mode]][menu][subselect[mode][1]][l][m]=i;
					}
				}
			}
