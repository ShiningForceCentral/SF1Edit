				if(p.x>=0&&p.x<=40&&p.y>=10&&p.y<=49){
					if(submode[mode]!=0){
						submode[mode]=0;
						select[mode]=0;
					}
				}
				if(p.x>=0&&p.x<=40&&p.y>=50&&p.y<=99){
					if(submode[mode]!=1){
						submode[mode]=1;
						select[mode]=0;
					}
				}
				if(p.x>=0&&p.x<=40&&p.y>=90&&p.y<=129){
					if(submode[mode]!=2){
						submode[mode]=2;
						select[mode]=0;

						curtiles = MapGraphics[select[mode]][0];
						curtiles2 = MapGraphics[select[mode]][1];
						if (ViewX >= MapSize[select[mode]][0] - 8 * MapZoom)ViewX = MapSize[select[mode]][0] - 8 * MapZoom;
						if (ViewY >= MapSize[select[mode]][1] - 8 * MapZoom)ViewY = MapSize[select[mode]][1] - 8 * MapZoom;

						if (ViewX<0)ViewX = 0;
						if (ViewY<0)ViewY = 0;

						if (MapSpriteSet[select[mode]] != 0xFF) subselect[mode][12] = MapSpriteSet[select[mode]];
					}
				}
				if(p.x>=0&&p.x<=40&&p.y>=130&&p.y<=169){
					if(submode[mode]!=3){
						submode[mode]=3;
						if (LastNPCScript != -1)select[mode] = LastNPCScript;
						else select[mode]=0;
					}
				}

				if(submode[mode]==0){
					if(p.x>=76&&p.x<=145&&p.y>=10&&p.y<=25){
						focus=1;
					}

					if(p.x>=55&&p.x<=75&&p.y>=8&&p.y<=28){
						select[mode]--;
						if(select[mode]<0)select[mode]=53;
					}

					if(p.x>=146&&p.x<=166&&p.y>=8&&p.y<=28){
						select[mode]++;
						if(select[mode]>53)select[mode]=0;
					}


					for(i=0;i<NumSprites[select[mode]];i++){
						for(j=0;j<6;j++){
							if(p.x>=240+80*j&&p.x<310+80*j&&p.y>=i*16+26&&p.y<i*16+42){
								focus=2+i*6+j;
							}
						}
					}
				}

				if(submode[mode]==1){

					if (menu) {
						switch (menu) {
						case 1:
							int doff = submenu;
							if (doff > 15)doff = 15;

							if (NumItems == 128)
								if (p.x >= 470 && p.x <= 483 && p.y >= 20 + 16 * doff&&p.y <= 33 + 16 * doff) {
									Chests[select[mode]][submenu][3] ^= 0x40;
									return 0;
								}
							for (i = 0; i<16; i++) {
								for (j = 0; j<4; j++) {
									if (p.x >= 307 + 115 * j&&p.x <= 421 + 115 * j&&p.y >= 36 + 16 * i + (doff)* 16 && p.y <= 51 + 16 * i + (doff)* 16) {
										if (NumItems == 128)Chests[select[mode]][submenu][3] &= 0xC0;
										else Chests[select[mode]][submenu][3] &= 0x80;
										Chests[select[mode]][submenu][3] |= i + j * 16;
										menu = 0;
										return 0;
									}
								}
							}
							break;
						}
						menu = 0;
						return 0;
					}

					for(i=0;i<8;i++){
						if(p.x>=50&&p.x<=120&&p.y>=i*16+10&&p.y<=i*16+25){
							select[mode]=i;
						}
					}
					for(i=0;i<32;i++){
						for(j=0;j<4;j++){
							if(p.x>=240+80*j&&p.x<=310+80*j&&p.y>=i*16+26&&p.y<=i*16+41){
								focus=2+i*4+j;
							}
						}

						if (p.x >= 516 && p.x <= 536 && p.y >= 25 + i * 16 && p.y <= 41 + i * 16) {
							menu = 1;
							submenu = i;
						}

					}
				}

				if(submode[mode]==2){
					if(menu==1){

						if(p.x<dwidth+168||p.x>dwidth+620||p.y<78||p.y>474){
							menu=-1;
							return 0;
						}

						if(p.x>=dwidth+198&&p.x<=dwidth+590&&p.y>=80&&p.y<=472){
							x=(p.x-(dwidth+198))/49;
							y=(p.y-80)/49;
							subselect[mode][0] = subselect[mode][2]*64+x+y*8;
							menu=-1;
							return 0;
						}
						if(!SecondLayer){
							if(p.x<dwidth+198){
								subselect[mode][2]--;
								if(subselect[mode][2]==0)subselect[mode][2]=15;
							}
							if(p.x>dwidth+590){
								subselect[mode][2]++;
								if(subselect[mode][2]==16)subselect[mode][2]=0;
							}
						}
						return 0;
					}
					if(menu==2){
						if(p.x>=dwidth+377&&p.x<=dwidth+397&&p.y>=20&&p.y<=33){
							subselect[mode][8]=128;
							menu=0;
							return 0;
						}
						for(i=0;i<16;i++){
							for(j=0;j<4;j++){
								if(p.x>=dwidth+307+115*j&&p.x<=dwidth+421+115*j&&p.y>=36+16*i&&p.y<=51+16*i){
									subselect[mode][8]=i+j*16;
									menu=0;
									return 0;
								}
							}
						}
						menu=0;
						return 0;
					}
					if(menu==3){
						for(j=0;j<numEvents;j++){
							if(p.x>=dwidth+585&&p.x<=dwidth+758&&p.y>=61+18*j&&p.y<=61+18*j+18){
								subselect[mode][3]=EventNums[j];
								menu=0;
								return 0;
							}
						}
						menu=0;
						return 0;
					}

					if (menu == 4) {

						for (int i = 0; i<NUM_SOUNDS / 3; i++) {

							if (p.x >= dwidth + 670 - 600 && p.x <= dwidth + 670 - 400 && p.y >= 520 - NUM_SOUNDS / 3 * 14 + i*14 && p.y <= 520 - NUM_SOUNDS / 3 * 14 + (i+1) * 14) {

								MapMusic[select[mode]][0] = i+1;
								
							}

							if (p.x >= dwidth + 670 - 400 && p.x <= dwidth + 670 - 200 && p.y >= 520 - NUM_SOUNDS / 3 * 14 + i * 14 && p.y <= 520 - NUM_SOUNDS / 3 * 14 + (i + 1) * 14) {

								MapMusic[select[mode]][0] = i+ NUM_SOUNDS / 3+1;

							}

							if (p.x >= dwidth + 670 - 200 && p.x <= dwidth + 670 - 0 && p.y >= 520 - NUM_SOUNDS / 3 * 14 + i * 14 && p.y <= 520 - NUM_SOUNDS / 3 * 14 + (i + 1) * 14) {

								MapMusic[select[mode]][0] = i+2* NUM_SOUNDS / 3+1;

							}
						}

						menu = 0;
						return 0;
					}

					if (p.x >= dwidth + 670 && p.x <= dwidth + 690 && p.y >= 520 && p.y <= 540) {
						menu = 4;
					}

					if(p.x>=dwidth+591&&p.x<=dwidth+691&&p.y>=522&&p.y<=542){
						focus=17;
					}

					if(p.x>=76&&p.x<=145&&p.y>=10&&p.y<=25){
						focus=1;
					}

					if(p.x>=55&&p.x<=75&&p.y>=8&&p.y<=28){
						select[mode]--;
						if(select[mode]<0)select[mode]=NUM_MAPS-1;
						curtiles=MapGraphics[select[mode]][0];
						curtiles2=MapGraphics[select[mode]][1];
						if(ViewX>=MapSize[select[mode]][0]-8*MapZoom)ViewX=MapSize[select[mode]][0]-8*MapZoom;
						if(ViewY>=MapSize[select[mode]][1]-8*MapZoom)ViewY=MapSize[select[mode]][1]-8*MapZoom;

						if(ViewX<0)ViewX=0;
						if(ViewY<0)ViewY=0;

						if(MapSpriteSet[select[mode]]!=0xFF) subselect[mode][12] = MapSpriteSet[select[mode]];
					}

					if(p.x>=136&&p.x<=156&&p.y>=8&&p.y<=28){
						select[mode]++;
						if(select[mode]>NUM_MAPS-1)select[mode]=0;
						curtiles=MapGraphics[select[mode]][0];
						curtiles2=MapGraphics[select[mode]][1];
						if(ViewX>=MapSize[select[mode]][0]-8*MapZoom)ViewX=MapSize[select[mode]][0]-8*MapZoom;
						if(ViewY>=MapSize[select[mode]][1]-8*MapZoom)ViewY=MapSize[select[mode]][1]-8*MapZoom;

						if(ViewX<0)ViewX=0;
						if(ViewY<0)ViewY=0;

						if(MapSpriteSet[select[mode]]!=0xFF) subselect[mode][12] = MapSpriteSet[select[mode]];
					}

					if(p.x>=186&&p.x<=265&&p.y>=10&&p.y<=25){
						focus=2;
					}

					if(p.x>=336&&p.x<=435&&p.y>=10&&p.y<=25){
						focus=3;
					}

					if(!SecondLayer){
						if(p.x>=165&&p.x<=185&&p.y>=8&&p.y<=28){
							MapTileset[select[mode]][0]--;
							if(MapTileset[select[mode]][0]<0)MapTileset[select[mode]][0]=8712;
							MapChanged = true;
						}

						if(p.x>=286&&p.x<=306&&p.y>=8&&p.y<=28){
							MapTileset[select[mode]][0]++;
							if(MapTileset[select[mode]][0]>8712)MapTileset[select[mode]][0]=0;
							MapChanged = true;
						}

						if(p.x>=315&&p.x<=335&&p.y>=8&&p.y<=28){
							MapTileset[select[mode]][1]--;
							if(MapTileset[select[mode]][1]<0)MapTileset[select[mode]][1]=8712;
							MapChanged = true;
						}

						if(p.x>=436&&p.x<=456&&p.y>=8&&p.y<=28){
							MapTileset[select[mode]][1]++;
							if(MapTileset[select[mode]][1]>8712)MapTileset[select[mode]][1]=0;
							MapChanged = true;
						}
					} else {
						if(p.x>=165&&p.x<=185&&p.y>=8&&p.y<=28){
							MapTileset[select[mode]][2]--;
							if(MapTileset[select[mode]][2]<0)MapTileset[select[mode]][2]=8712;
							MapChanged = true;
						}

						if(p.x>=286&&p.x<=306&&p.y>=8&&p.y<=28){
							MapTileset[select[mode]][2]++;
							if(MapTileset[select[mode]][2]>8712)MapTileset[select[mode]][2]=0;
							MapChanged = true;
						}

						if(p.x>=315&&p.x<=335&&p.y>=8&&p.y<=28){
							MapTileset[select[mode]][3]--;
							if(MapTileset[select[mode]][3]<0)MapTileset[select[mode]][3]=8712;
							MapChanged = true;
						}

						if(p.x>=436&&p.x<=456&&p.y>=8&&p.y<=28){
							MapTileset[select[mode]][3]++;
							if(MapTileset[select[mode]][3]>8712)MapTileset[select[mode]][3]=0;
							MapChanged = true;
						}
					}


					if(p.x>=486&&p.x<=591&&p.y>=10&&p.y<=25){
						focus=4;
					}

					if(p.x>=465&&p.x<=485&&p.y>=8&&p.y<=28){
						curtiles--;
						if(curtiles<0)curtiles=23;
						MapGraphics[select[mode]][0]=curtiles;
						MapChanged=true;
					}

					if(p.x>=592&&p.x<=612&&p.y>=8&&p.y<=28){
						curtiles++;
						if(curtiles>23)curtiles=0;
						MapGraphics[select[mode]][0]=curtiles;
						MapChanged=true;
					}

					if(p.x>=642&&p.x<=747&&p.y>=10&&p.y<=25){
						focus=5;
					}

					if(p.x>=621&&p.x<=641&&p.y>=8&&p.y<=28){
						curtiles2--;
						if(curtiles2<0)curtiles2=23;
						MapGraphics[select[mode]][1]=curtiles2;
						MapChanged=true;
					}

					if(p.x>=748&&p.x<=768&&p.y>=8&&p.y<=28){
						curtiles2++;
						if(curtiles2>23)curtiles2=0;
						MapGraphics[select[mode]][1]=curtiles2;
						MapChanged=true;
					}

					if(!DisplayEvent){
						if(!DisplaySprites){
							if (!DisplayHQ) {
								if (!DisplaySpecial) {
									if (p.x >= dwidth + 591 && p.x <= dwidth + 712 && p.y >= 50 && p.y <= 65) {
										focus = 6;
									}

									if (p.x >= dwidth + 570 && p.x <= dwidth + 591 && p.y >= 48 && p.y <= 68) {
										subselect[mode][0]--;
										if (subselect[mode][0] < 0)subselect[mode][0] = 1023;
										if (SecondLayer)subselect[mode][0] %= 64;
									}

									if (p.x >= dwidth + 713 && p.x <= dwidth + 733 && p.y >= 48 && p.y <= 68) {
										subselect[mode][0]++;
										if (SecondLayer)subselect[mode][0] %= 64;
										if (subselect[mode][0] > 1023)subselect[mode][0] = 0;
									}

									if (!SecondLayer) {
										if (p.x >= dwidth + 570 && p.x <= dwidth + 583 && p.y >= 152 && p.y <= 167) {
											Walkable = !Walkable;
										}

										if (p.x >= dwidth + 650 && p.x <= dwidth + 750 && p.y >= 240 && p.y <= 260) {
											focus = 18;
										}

										if (p.x >= dwidth + 650 && p.x <= dwidth + 750 && p.y >= 260 && p.y <= 280) {
											focus = 19;
										}
									} else {
										if (p.x >= dwidth + 590 && p.x <= dwidth + 790 && p.y >= 152 && p.y <= 167) {
											focus = 7;
										}

										if (p.x >= dwidth + 590 && p.x <= dwidth + 690 && p.y >= 170 && p.y <= 200) {
											subselect[mode][0] = -1;
											subselect[mode][1] = 0;
										}
									}

									if (p.x >= dwidth + 590 && p.x <= dwidth + 680 && p.y >= 80 && p.y <= 140) {
										menu = 1;
										if (SecondLayer)subselect[mode][2] = 0;
									}
								} else {

									if (p.x >= dwidth + 591 && p.x <= dwidth + 712 && p.y >= 50 && p.y <= 65) {
										focus = 8;
									}

									if (p.x >= dwidth + 570 && p.x <= dwidth + 791 && p.y >= 100 && p.y<120) {
										focus = 9;
									}
									if (p.x >= dwidth + 570 && p.x <= dwidth + 791 && p.y >= 120 && p.y<140) {
										focus = 10;
									}

									if (p.x >= dwidth + 570 && p.x <= dwidth + 791 && p.y >= 180 && p.y<200) {
										focus = 13;
									}

									if (p.x >= dwidth + 570 && p.x <= dwidth + 668 && p.y >= 210 && p.y < 240) {
										if (MapSpecialTiles[select[mode]][subselect[mode][13]][0] < 255 && MapSpecialTiles[select[mode]][subselect[mode][13]][1] < 255) {
											ViewX = MapSpecialTiles[select[mode]][subselect[mode][13]][0] - 3;
											ViewY = MapSpecialTiles[select[mode]][subselect[mode][13]][1] - 3;

											if (ViewX < 0)ViewX = 0;
											if (ViewY < 0)ViewY = 0;
										}
									}

									if (p.x >= dwidth + 570 && p.x <= dwidth + 591 && p.y >= 48 && p.y <= 68) {
										subselect[mode][13]--;
										if (subselect[mode][13] < 0)subselect[mode][13] = 4;
									}

									if (p.x >= dwidth + 713 && p.x <= dwidth + 733 && p.y >= 48 && p.y <= 68) {
										subselect[mode][13]++;
										if (subselect[mode][13] > 4)subselect[mode][13] = 0;
									}

								}
							} else {
								if (p.x >= dwidth + 591 && p.x <= dwidth + 712 && p.y >= 50 && p.y <= 65) {
									focus = 9;
								}

								if (p.x >= dwidth + 570 && p.x <= dwidth + 591 && p.y >= 48 && p.y <= 68) {
									MapSelect--;
									if (MapSelect < 0)MapSelect += 30;
									if (MapSelect >= 30)MapSelect = 29;
								}

								if (p.x >= dwidth + 713 && p.x <= dwidth + 733 && p.y >= 48 && p.y <= 68) {
									MapSelect++;
									if (MapSelect >= 30)MapSelect = 0;
								}

								if (p.x >= dwidth + 601 && p.x <= dwidth + 641 && p.y >= 90 && p.y <= 106) {
									focus = 10;
								}
								if (p.x >= dwidth + 601 && p.x <= dwidth + 641 && p.y >= 110 && p.y <= 126) {
									focus = 11;
								}
								if (p.x >= dwidth + 601 && p.x <= dwidth + 641 && p.y >= 130 && p.y <= 146) {
									focus = 12;
								}

								/*if (NumHQPos > 30) {
									if (p.x >= dwidth + 570 && p.x <= dwidth + 590 && p.y >= 168 && p.y <= 188) {
										NumHQPos--;
									}
								}

								if (NumHQPos < NumChars) {
									if (p.x >= dwidth + 673 && p.x <= dwidth + 693 && p.y >= 168 && p.y <= 188) {
										NumHQPos++;
										MapSelect = NumHQPos-1;
										HQPos[MapSelect][1] = 3 + ViewX;
										HQPos[MapSelect][2] = 3 + ViewY;
									}
								}*/
							}
						} else {

							if(p.x>=dwidth+590&&p.x<=dwidth+708&&p.y>=260&&p.y<=278){
								
								for(i=0;i<NUM_DIALOG;i++){
									if(DialogHeader[i][0] == subselect[mode][12]){

										DialogGraphNode * find = DialogGraphs[i]->findDialogNumber((Sprites[subselect[mode][12]][MapSelect][5]&0xF8)/8);

										if(find){
											mode=18;
											focus=0;
											menu=0;
											submode[mode]=0;

											u = subselect[mode][0];
											subselect[mode][0] = i;
											DialogGraphs[subselect[mode][0]]->w = DialogGraphs[u]->w;
											DialogGraphs[subselect[mode][0]]->h = DialogGraphs[u]->h;
											DialogGraphs[subselect[mode][0]]->vx=0;
											DialogGraphs[subselect[mode][0]]->vy=0;

											if(DialogGraphs[subselect[mode][0]]->sel)DialogGraphs[subselect[mode][0]]->sel->selected=false;
											find->selected = true;
											find->selout=false;
											DialogGraphs[subselect[mode][0]]->sel = find;
											DialogGraphs[subselect[mode][0]]->vx = DialogGraphs[subselect[mode][0]]->sel->x-DialogGraphs[subselect[mode][0]]->w/2;
											DialogGraphs[subselect[mode][0]]->vy = DialogGraphs[subselect[mode][0]]->sel->y-DialogGraphs[subselect[mode][0]]->h/2;
										} else {
											MessageBox(NULL,"Not found.","Note",MB_OK);
										}
										
										return false;
									}
								}
								MessageBox(NULL,"Not found.","Note",MB_OK);
								return false;
							}

							if(p.x>=dwidth+590&&p.x<=dwidth+708&&p.y>=72&&p.y<=90){
								
								for(i=0;i<NUM_DIALOG;i++){
									if(DialogHeader[i][0] == subselect[mode][12]){
										mode=18;
										focus=0;
										menu=0;
										submode[mode]=0;

										u = subselect[mode][0];
										subselect[mode][0] = i;
										DialogGraphs[subselect[mode][0]]->w = DialogGraphs[u]->w;
										DialogGraphs[subselect[mode][0]]->h = DialogGraphs[u]->h;
										DialogGraphs[subselect[mode][0]]->vx=0;
										DialogGraphs[subselect[mode][0]]->vy=0;
										
										return false;
									}
								}
								MessageBox(NULL,"Not found.","Note",MB_OK);
								return false;
							}

								if(p.x>=dwidth+591&&p.x<=dwidth+712&&p.y>=50&&p.y<=65){
									focus=8;
								}

								if(p.x>=dwidth+570&&p.x<=dwidth+591&&p.y>=48&&p.y<=68){
									subselect[mode][12]--;
									if(subselect[mode][12]<0)subselect[mode][12]=NumSpriteSets-1;
								}

								if(p.x>=dwidth+713&&p.x<=dwidth+733&&p.y>=48&&p.y<=68){
									subselect[mode][12]++;
									if(subselect[mode][12]>=NumSpriteSets)subselect[mode][12]=0;
								}

								if(p.x>=dwidth+670&&p.x<=dwidth+690&&p.y>=200&&p.y<220){
									submode[mode]=3;
									select[mode]=Sprites[subselect[mode][12]][MapSelect][4];
									MapSelect=-1;
								}

								if(p.x>=dwidth+570&&p.x<=dwidth+791&&p.y>=100&&p.y<120){
									focus=9;
								}
								if(p.x>=dwidth+570&&p.x<=dwidth+791&&p.y>=120&&p.y<140){
									focus=10;
								}
								if(p.x>=dwidth+570&&p.x<=dwidth+791&&p.y>=140&&p.y<160){
									focus=11;
								}
								if(p.x>=dwidth+570&&p.x<=dwidth+791&&p.y>=160&&p.y<180){
									focus=12;
								}
								if(p.x>=dwidth+570&&p.x<=dwidth+791&&p.y>=180&&p.y<200){
									focus=13;
								}

								if (p.x >= dwidth + 670 && p.x <= dwidth + 791 && p.y >= 180 && p.y<200) {
									focus = 18;
								}

								if(p.x>=dwidth+570&&p.x<=dwidth+791&&p.y>=200&&p.y<220){
									focus=14;
								}
								if(p.x>=dwidth+570&&p.x<=dwidth+791&&p.y>=220&&p.y<240){
									focus=15;
								}
								if(p.x>=dwidth+570&&p.x<=dwidth+791&&p.y>=240&&p.y<260){
									focus=16;
								}

								if (p.x >= dwidth + 730 && p.x <= dwidth + 750 && p.y >= 162 && p.y<182) {
									Sprites[subselect[mode][12]][MapSelect][2] ^= 0x20;
								}



								if(p.x>=dwidth+575&&p.x<=dwidth+595&&p.y>=298&&p.y<318){
									if(NumSprites[subselect[mode][12]]<32){
										NumSprites[subselect[mode][12]]++;
										MapSelect=NumSprites[subselect[mode][12]]-1;

										Sprites[subselect[mode][12]][MapSelect][0]=3+ViewX;
										Sprites[subselect[mode][12]][MapSelect][1]=3+ViewY;

										Sprites[subselect[mode][12]][MapSelect][2]=0;
										Sprites[subselect[mode][12]][MapSelect][3]=0;
										Sprites[subselect[mode][12]][MapSelect][4]=0;
										Sprites[subselect[mode][12]][MapSelect][5]=0;

									}
								}

								if(p.x>=dwidth+720&&p.x<=dwidth+740&&p.y>=99&&p.y<119){
									if(MapSelect!=255&&NumSprites[subselect[mode][12]]>0){
										NumSprites[subselect[mode][12]]--;
										
										if(MapSelect!=NumSprites[subselect[mode][12]]){

											Sprites[subselect[mode][12]][MapSelect][0]=Sprites[subselect[mode][12]][NumSprites[subselect[mode][12]]][0];
											Sprites[subselect[mode][12]][MapSelect][1]=Sprites[subselect[mode][12]][NumSprites[subselect[mode][12]]][1];

											Sprites[subselect[mode][12]][MapSelect][2]=Sprites[subselect[mode][12]][NumSprites[subselect[mode][12]]][2];
											Sprites[subselect[mode][12]][MapSelect][3]=Sprites[subselect[mode][12]][NumSprites[subselect[mode][12]]][3];
											Sprites[subselect[mode][12]][MapSelect][4]=Sprites[subselect[mode][12]][NumSprites[subselect[mode][12]]][4];
											Sprites[subselect[mode][12]][MapSelect][5]=Sprites[subselect[mode][12]][NumSprites[subselect[mode][12]]][5];
										
										}
										MapSelect=255;
									}
								}

						}
					} else {

						
						if(p.x>=dwidth+570&&p.x<=dwidth+668&&p.y>=180&&p.y<=210){
							if(subselect[mode][3]==12||subselect[mode][3]==16||subselect[mode][3]==104){
								if (subselect[mode][4] != -1) {
									select[mode] = subselect[mode][4];
									ViewX = subselect[mode][5] - 3;
									ViewY = subselect[mode][6] - 3;
									if (ViewX < 0)ViewX = 0;
									if (ViewY < 0)ViewY = 0;

									curtiles = MapGraphics[select[mode]][0];
									curtiles2 = MapGraphics[select[mode]][1];
									if (ViewX >= MapSize[select[mode]][0] - 8 * MapZoom)ViewX = MapSize[select[mode]][0] - 8 * MapZoom;
									if (ViewY >= MapSize[select[mode]][1] - 8 * MapZoom)ViewY = MapSize[select[mode]][1] - 8 * MapZoom;

									if (MapSpriteSet[select[mode]] != 0xFF) subselect[mode][12] = MapSpriteSet[select[mode]];


									InvalidateRect(hWnd, NULL, 0);
								} else {
									AddTele(subselect[mode][3], subselect[mode][5], subselect[mode][6], select[mode], 0, 0, 0, 0, 0);

									subselect[mode][4] = 0;
									subselect[mode][5] = 0;
									subselect[mode][6] = 0;
									subselect[mode][7] = 0;
									
								}
							}
						}

						if(p.x>=dwidth+591&&p.x<=dwidth+712&&p.y>=50&&p.y<=65){
							focus=8;
						}

						if(p.x>=dwidth+570&&p.x<=dwidth+591&&p.y>=48&&p.y<=68){
							subselect[mode][3]--;
							if(subselect[mode][3]<0)subselect[mode][3]=255;
						}

						if(p.x>=dwidth+713&&p.x<=dwidth+733&&p.y>=48&&p.y<=68){
							subselect[mode][3]++;
							if(subselect[mode][3]>255)subselect[mode][3]=0;
						}

						if(p.x>=dwidth+570&&p.x<=dwidth+791&&p.y>=100&&p.y<120){
							focus=9;
						}
						if(p.x>=dwidth+570&&p.x<=dwidth+791&&p.y>=120&&p.y<140){
							focus=10;
						}
						if(p.x>=dwidth+570&&p.x<=dwidth+791&&p.y>=140&&p.y<160){
							focus=11;
						}
						if(p.x>=dwidth+570&&p.x<=dwidth+791&&p.y>=160&&p.y<180){
							focus=12;
						}

						if(p.x>=dwidth+570&&p.x<=dwidth+670&&p.y>=120&&p.y<140&&subselect[mode][3]==100){
							focus=14;
						}
						if(p.x>=dwidth+570&&p.x<=dwidth+670&&p.y>=120&&p.y<140&&subselect[mode][3]==112){
							focus=13;
						}

						if(p.x>=dwidth+548&&p.x<=dwidth+568&&p.y>=120&&p.y<140&&subselect[mode][3]==112){
							menu=2;
						}

						if(p.x>=dwidth+740&&p.x<=dwidth+760&&p.y>=50&&p.y<70){
							menu=3;
						}

					}
					
					if(p.x>=dwidth+570&&p.x<=dwidth+583&&p.y>=362&&p.y<=375){
						DisplayNum=!DisplayNum;
					}

					if(p.x>=dwidth+570&&p.x<=dwidth+583&&p.y>=382&&p.y<=395){
						DisplayGrid=!DisplayGrid;
					}

					if(p.x>=dwidth+570&&p.x<=dwidth+583&&p.y>=402&&p.y<=415){
						DisplayWalk=!DisplayWalk;
					}

					if(p.x>=dwidth+570&&p.x<=dwidth+583&&p.y>=422&&p.y<=435){
						SecondLayer=!SecondLayer;
						if(SecondLayer)subselect[mode][0]%=64;
					}

					if(p.x>=dwidth+570&&p.x<=dwidth+583&&p.y>=442&&p.y<=455){
						DisplayGroup=!DisplayGroup;
					}

					if(p.x>=dwidth+570&&p.x<=dwidth+583&&p.y>=462&&p.y<=475){
						DisplaySpecial=!DisplaySpecial;
						DisplayEvent = false;
						DisplaySprites = false;
						DisplayHQ = false;
					}

					if(p.x>=dwidth+570&&p.x<=dwidth+583&&p.y>=482&&p.y<=495){
						DisplayEvent=!DisplayEvent;
						DisplaySprites=false;
						DisplayHQ = false;
						DisplaySpecial = false;
					}

					if(p.x>=dwidth+570&&p.x<=dwidth+583&&p.y>=502&&p.y<=515){
						DisplaySprites=!DisplaySprites;
						DisplayHQ = false;
						DisplayEvent=false;
						DisplaySpecial = false;
						if(!GraphicsLoaded&&strlen(file))LoadGFX(file);
						if(MapSpriteSet[select[mode]]!=0xFF) subselect[mode][12] = MapSpriteSet[select[mode]];
					}

					if (p.x >= dwidth + 710 && p.x <= dwidth + 723 && p.y >= 502 && p.y <= 515) {
						DisplayHQ  = !DisplayHQ;
						DisplaySprites = false;
						DisplayEvent = false;
						DisplaySpecial = false;

						if (DisplayHQ && MapSelect > 29)MapSelect = 29;

						if (!GraphicsLoaded&&strlen(file))LoadGFX(file);
					}

					if(p.x>=20&&p.x<=40&&p.y>=500+60*(MMH-8)&&p.y<=520+60*(MMH-8)){
						MapZoom*=2;
						if(MapZoom==8)MapZoom=1;

						if(ViewX>=MapSize[select[mode]][0]-8*MapZoom)ViewX=MapSize[select[mode]][0]-8*MapZoom;
						if(ViewY>=MapSize[select[mode]][1]-8*MapZoom)ViewY=MapSize[select[mode]][1]-8*MapZoom;

						if(ViewX<0)ViewX=0;
						if(ViewY<0)ViewY=0;
					}
					MapClick(p);
				}

				if(submode[mode]==3){
					if(menu>0){
						if(submenu==1){
							submenu=-1;
							for(int i=0;i<15;i++){
								l=0;
								if(p.x>=280&&p.x<=487&&p.y>=105+20*i&&p.y<=125+20*i){
									l = SpriteComLen[i] - SpriteComLen[SpriteScripts[select[mode]][menu-1]];
									SpriteScripts[select[mode]][menu-1]=i;
									MapChanged=true;
								}
								if(p.x>=488&&p.x<=695&&p.y>=105+20*i&&p.y<=125+20*i){
									l = SpriteComLen[i+15] - SpriteComLen[SpriteScripts[select[mode]][menu-1]];
									SpriteScripts[select[mode]][menu-1]=i+15;
									MapChanged=true;
								}
								SpriteScrLen[select[mode]]+=l;
								if(l>0){
									for(j=255;j>=menu;j--){
										SpriteScripts[select[mode]][j]=SpriteScripts[select[mode]][j-l];
									}
									for(j=0;j<SpriteComLen[SpriteScripts[select[mode]][menu-1]]-1;j++){
										SpriteScripts[select[mode]][menu+j]=0;
									}
								}
								if(l<0){
									for(j=menu;j<256+l;j++){
										SpriteScripts[select[mode]][j]=SpriteScripts[select[mode]][j-l];
									}
									for(j=256+l;j<256;j++){
										SpriteScripts[select[mode]][j]=25;
									}
									for(j=0;j<SpriteComLen[SpriteScripts[select[mode]][menu-1]]-1;j++){
										SpriteScripts[select[mode]][menu+j]=0;
									}
								}
							}
							return true;
						}
						if(p.x>=277&&p.x<=463&&p.y>=105&&p.y<=123){
							submenu=1;
							focus=0;
						}

						if(SpriteScripts[select[mode]][menu-1]==18){
							if(p.x>=225+115&&p.x<=225+165&&p.y>=175&&p.y<=195){
								SpriteScripts[select[mode]][menu+1]=0;
							}
							if(p.x>=225+115&&p.x<=225+245&&p.y>=255&&p.y<=275){
								SpriteScripts[select[mode]][menu+1]=2;
							}
							if(p.x>=225+40&&p.x<=225+90&&p.y>=215&&p.y<=235){
								SpriteScripts[select[mode]][menu+1]=3;
							}
							if(p.x>=225+190&&p.x<=225+240&&p.y>=215&&p.y<=235){
								SpriteScripts[select[mode]][menu+1]=1;
							}

						}

						if(p.x>=225+200&&p.x<=225+250&&p.y>=135&&p.y<=155)focus=1;
						if(p.x>=225+200&&p.x<=225+250&&p.y>=155&&p.y<=175)focus=2;
						if(p.x>=225+200&&p.x<=225+250&&p.y>=175&&p.y<=195)focus=3;


						if(p.x<225||p.y<100||p.x>500||p.y>300)menu=-1;
						return true;
					}


					if(p.x>=100&&p.x<=118&&p.y>=60&&p.y<=78){
						if(subselect[mode][11]>0)subselect[mode][11]--;
					}

					if(p.x>=100&&p.x<=118&&p.y>=520&&p.y<=538){
						subselect[mode][11]++;
					}

					if(p.x>=76&&p.x<=145&&p.y>=10&&p.y<=25){
						focus=1;
					}

					if(p.x>=55&&p.x<=75&&p.y>=8&&p.y<=28){
						subselect[mode][11]=0;
						select[mode]--;
						if(select[mode]<0)select[mode]=171;

						LastNPCScript = select[mode];
					}

					if(p.x>=146&&p.x<=166&&p.y>=8&&p.y<=28){
						subselect[mode][11]=0;
						select[mode]++;
						if(select[mode]>171)select[mode]=0;

						LastNPCScript = select[mode];
					}

					unsigned char in=0;
					i=0;
					x = 225;
					y=0 - 20 * subselect[mode][11];

					k=0;

					while(k<SpriteScrLen[select[mode]]){
					//while(in!=0x09&&in!=0x19&&in!=0x0E){
						in = SpriteScripts[select[mode]][i];
						k+=SpriteComLen[in];

							if(p.x>=x-62&&p.x<=x-42&&p.y>=60+y-1&&p.y<=60+y+19){
								x = SpriteComLen[in];
								for(int j=255;j>i;j--){
									SpriteScripts[select[mode]][j] = SpriteScripts[select[mode]][j-1];
								}
								SpriteScripts[select[mode]][i] = 0;
								SpriteScrLen[select[mode]]++;
								return true;
							}

						if(in!=0x19){

							if(p.x>=x-22&&p.x<=x-2&&p.y>=60+y-1&&p.y<=60+y+19){
								//edit
								menu=i+1;
								submenu=-1;
							}

							if(p.x>=x-42&&p.x<=x-22&&p.y>=60+y-1&&p.y<=60+y+19){
								x = SpriteComLen[in];
								SpriteScrLen[select[mode]]-=x;
								for(j=i;j<255-x;j++){
									SpriteScripts[select[mode]][j] = SpriteScripts[select[mode]][j+x];
								}
								for(j=255-x+1;j<=255;j++){
									SpriteScripts[select[mode]][j] = 0x19;
								}
								return true;
							}

							y+=20;
						}
						i+=SpriteComLen[in];
					}

				}