	GetCursorPos(&p);
	ScreenToClient(hWnd,&p);
	p.y-=40;

	if(submode[mode]==2){

		if(BattleMapDrag){
			if(p.x - BattleDragPos[0] >= 48/MapZoom){
				if(ViewX>0){
					ViewX--;
					BattleDragPos[0]+=48/MapZoom;
					InvalidateRect(hWnd,NULL,0);
				}
			}
			if(p.x - BattleDragPos[0] <= -48/MapZoom){
				if(ViewX<MapSize[MapHeader[BattleHeaderPos[select[mode]]][1]][0]-10){
					ViewX++;
					BattleDragPos[0]-=48/MapZoom;
					InvalidateRect(hWnd,NULL,0);
				}
			}

			if(p.y - BattleDragPos[1] >= 48/MapZoom){
				if(ViewY>0){
					ViewY--;
					BattleDragPos[1]+=48/MapZoom;
					InvalidateRect(hWnd,NULL,0);
				}
			}
			if(p.y - BattleDragPos[1] <= -48/MapZoom){
				if(ViewY<MapSize[MapHeader[BattleHeaderPos[select[mode]]][1]][1]-10){
					ViewY++;
					BattleDragPos[1]-=48/MapZoom;
					InvalidateRect(hWnd,NULL,0);
				}
			}
		}

		if(!menu){
			PatBlt(memdc,50,560+48*(BMH-10),150,20,PATCOPY);
			if(p.x>=50&&p.x<=(BMW-10)*48+530&&p.y>=40&&p.y<=(BMH-10)*48+520){
				x=(p.x-50)*MapZoom/48;
				y=(p.y-40)*MapZoom/48;
				x+=ViewX;
				y+=ViewY;
				sprintf(out,"%d, %d",x,y);
				TextOut(memdc,50,(BMH-10)*48+560,out,strlen(out));
			}
			BitBlt(hdc,50,560+48*(BMH-10),150,20,memdc,50,560+48*(BMH-10),SRCCOPY);
		}

		switch(BattleMode){
		case 0:
			if(wParam &	MK_LBUTTON){
				if(BattleDrag>=0&&p.x>=50&&p.x<50+48*BMW&&p.y>=40&&p.y<=40+48*BMH){
					i = (p.x-50)*MapZoom/48+ViewX-MapHeader[BattleHeaderPos[select[mode]]][3];
					j = (p.y-40)*MapZoom/48+ViewY-MapHeader[BattleHeaderPos[select[mode]]][5];
					if(BattleDrag<128){
						if(i>=0&&i<=BattleSize[select[mode]][0]+1){
							if(Battle[select[mode]][BattleDrag][4]!=i){
								InvalidateRect(hWnd,NULL,0);
								Battle[select[mode]][BattleDrag][4]=i;
							}
						}
						if(j>=0&&j<=BattleSize[select[mode]][1]+1){
							if(Battle[select[mode]][BattleDrag][5]!=j){
								InvalidateRect(hWnd,NULL,0);
								Battle[select[mode]][BattleDrag][5]=j;
							}
						}
					} else {
						int k = (BattleDrag - BattleDrag%256)/256 - 1;
						int l = BattleDrag%256;
						l = (l - l%32)/32;
						switch(Behaviors[select[mode]][BattleSelect][k][1]){
							case 0:
								if(i>=0&&i<=BattleSize[select[mode]][0]+1){
									if(Behaviors[select[mode]][BattleSelect][k][2]!=i){
										InvalidateRect(hWnd,NULL,0);
										Behaviors[select[mode]][BattleSelect][k][2]=i;
									}
								}
								if(j>=0&&j<=BattleSize[select[mode]][1]+1){
									if(Behaviors[select[mode]][BattleSelect][k][3]!=j){
										InvalidateRect(hWnd,NULL,0);
										Behaviors[select[mode]][BattleSelect][k][3]=j;
									}
								}
								break;
							case 2:
								if(i>=0&&i<=BattleSize[select[mode]][0]+1){
									if(AIPaths[select[mode]][BattleSelect][k][l][0]!=i){
										InvalidateRect(hWnd,NULL,0);
										AIPaths[select[mode]][BattleSelect][k][l][0]=i;
									}
								}
								if(j>=0&&j<=BattleSize[select[mode]][1]+1){
									if(AIPaths[select[mode]][BattleSelect][k][l][1]!=j){
										InvalidateRect(hWnd,NULL,0);
										AIPaths[select[mode]][BattleSelect][k][l][1]=j;
									}
								}
								break;
						}
					}
				}
			}
			break;
		case 1:
			if(wParam &	MK_LBUTTON){
				if(p.x>=50&&p.x<50+48*BMW&&p.y>=40&&p.y<=40+48*BMH){
					i = (p.x-50)*MapZoom/48+ViewX-MapHeader[BattleHeaderPos[select[mode]]][3]-1;
					j = (p.y-40)*MapZoom/48+ViewY-MapHeader[BattleHeaderPos[select[mode]]][5]-1;


					if (BattleTerrain) {
						if (!BattleLand[select[mode]][i + (j)*BattleSize[select[mode]][0]]) {
							BattleAI[select[mode]][i + (j)*BattleSize[select[mode]][0]] = 0;
						}
					}

					if (!BattleTerrain) {
						if (BattleLand[select[mode]][i + (j)*BattleSize[select[mode]][0]]) {
							BattleAI[select[mode]][i + (j)*BattleSize[select[mode]][0]] = 255;
						}
					}

					BattleLand[select[mode]][i + (j)*BattleSize[select[mode]][0]] = BattleTerrain;
				}
			}
			break;
		case 2:
			if(wParam &	MK_LBUTTON){
				if(p.x>=50&&p.x<50+48*BMW&&p.y>=40&&p.y<=40+48*BMH){
					i = (p.x-50)*MapZoom/48+ViewX-MapHeader[BattleHeaderPos[select[mode]]][3]-1;
					j = (p.y-40)*MapZoom/48+ViewY-MapHeader[BattleHeaderPos[select[mode]]][5]-1;
					if(BattleLand[select[mode]][i+(j)*BattleSize[select[mode]][0]]){
						BattleAI[select[mode]][i+(j)*BattleSize[select[mode]][0]]=BattleReg;
					}
				}
			}
			break;
		case 3:
			if(wParam &	MK_LBUTTON){
				if(BattleDrag>=0&&p.x>=50&&p.x<50+48*BMW&&p.y>=40&&p.y<=40+48*BMH){
					i = (p.x-50)*MapZoom/48+ViewX-MapHeader[BattleHeaderPos[select[mode]]][3];
					j = (p.y-40)*MapZoom/48+ViewY-MapHeader[BattleHeaderPos[select[mode]]][5];
					if(i>=0&&i<=BattleSize[select[mode]][0]+1){
						if(BattleStart[select[mode]][BattleEntrance][BattleDrag][0]!=i){
							InvalidateRect(hWnd,NULL,0);
							BattleStart[select[mode]][BattleEntrance][BattleDrag][0]=i;
						}
					}
					if(j>=0&&j<=BattleSize[select[mode]][1]+1){
						if(BattleStart[select[mode]][BattleEntrance][BattleDrag][1]!=j){
							InvalidateRect(hWnd,NULL,0);
							BattleStart[select[mode]][BattleEntrance][BattleDrag][1]=j;
						}
					}
				}
			}
			break;
		case 4:
			if (wParam & MK_LBUTTON) {
				if (p.x >= 50 && p.x<50 + 48 * BMW&&p.y >= 40 && p.y <= 40 + 48 * BMH) {
					if (BattleExitSet == 0) {
						i = (p.x - 50)*MapZoom / 48 + ViewX - MapHeader[BattleHeaderPos[select[mode]]][3];
						j = (p.y - 40)*MapZoom / 48 + ViewY - MapHeader[BattleHeaderPos[select[mode]]][5];
					} else {
						i = (p.x - 50)*MapZoom / 48 + ViewX;
						j = (p.y - 40)*MapZoom / 48 + ViewY;
					}
					if (j >= 0 && i < MapSize[MapHeader[BattleHeaderPos[select[mode]]][1]][0]) {
						Exits[BattExits[select[mode]][BattleExitSet]][i + (j)*MapSize[MapHeader[BattleHeaderPos[select[mode]]][1]][0]] = BattleExit;
						if (Exits[BattExits[select[mode]][BattleExitSet]][i + (j)*MapSize[MapHeader[BattleHeaderPos[select[mode]]][1]][0]] == -1)Exits[BattExits[select[mode]][BattleExitSet]][i + (j)*MapSize[MapHeader[BattleHeaderPos[select[mode]]][1]][0]] = 255;
						Exits[128 + BattExits[select[mode]][BattleExitSet]][i + (j)*MapSize[MapHeader[BattleHeaderPos[select[mode]]][1]][0]] = BattleTele;
					}
				}
			}
			break;
		}
	}