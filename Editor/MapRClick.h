				if(submode[mode]==2){
					if(!DisplayEvent){
						if(p.x>=50&&p.x<=530+60*(MMW-8)&&p.y>=40&&p.y<=520+60*(MMH-8)){
							x=(p.x-50)*MapZoom/60;
							y=(p.y-40)*MapZoom/60;
							if(!SecondLayer){
								subselect[mode][0]=MapData[select[mode]][x+ViewX+(y+ViewY)*MapSize[select[mode]][0]];
								Walkable=MapWalk[select[mode]][x+ViewX+(y+ViewY)*MapSize[select[mode]][0]];
							} else {
								subselect[mode][0]=MapData2[select[mode]][x+ViewX+(y+ViewY)*MapSize[select[mode]][0]];
								subselect[mode][1]=MapGroup[select[mode]][x+ViewX+(y+ViewY)*MapSize[select[mode]][0]];
							}
							if (DisplayHQ) {
								for (int i = 0; i<30; i++) {

									if (x == HQPos[i][1] - ViewX && y == HQPos[i][2] - ViewY) {
										HQPos[i][0]++;
										HQPos[i][0]%=4;
									}
								}
							}
						}
					} else {
						if(p.x>=50&&p.x<=530+60*(MMW-8)&&p.y>=40&&p.y<=520+60*(MMH-8)){
							x=(p.x-50)*MapZoom/60;
							y=(p.y-40)*MapZoom/60;
							subselect[mode][3]=MapEvent[select[mode]][x+ViewX+(y+ViewY)*MapSize[select[mode]][0]];
							switch(subselect[mode][3]){
								case 12:
								case 16:
								case 104:
									if (FindTele(subselect[mode][3], x + ViewX, y + ViewY, select[mode]) == 1024) {
										subselect[mode][4] = -1;
										subselect[mode][5] = x + ViewX;
										subselect[mode][6] = y + ViewY;
									}
									break;
								case 100:
									subselect[mode][10]=MapRead[select[mode]][x+ViewX+(y+ViewY)*MapSize[select[mode]][0]];
									break;
								case 112:
									subselect[mode][8]=MapChest[select[mode]][x+ViewX+(y+ViewY)*MapSize[select[mode]][0]];
									subselect[mode][9]=MapGold[select[mode]][x+ViewX+(y+ViewY)*MapSize[select[mode]][0]];
									break;
							}
						}
					}
				}
