			c=wParam;
			if(submode[mode]==0){
				if(focus==1){
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
					select[mode]%=54;
					if(MapSpriteSet[select[mode]]!=0xFF) subselect[mode][12] = MapSpriteSet[select[mode]];
				}
				if(focus>1&&focus<2+NumSprites[select[mode]]*6){
					val=c-'0';
					if(val>=0&&val<10){
						i=Sprites[select[mode]][((focus-2)-(focus-2)%6)/6][(focus-2)%6];
						if(i<100){
							i*=10;
							i+=val;
							Sprites[select[mode]][((focus-2)-(focus-2)%6)/6][(focus-2)%6]=i;
						}
					}
					if(c==8){
						i=Sprites[select[mode]][((focus-2)-(focus-2)%6)/6][(focus-2)%6];
						i=i-i%10;
						i/=10;
						Sprites[select[mode]][((focus-2)-(focus-2)%6)/6][(focus-2)%6]=i;
					}
					if((focus-2)%6==3)CountMapSprites();
				}
			}

			if(submode[mode]==1){
				if(focus>1){
					val=c-'0';
					if(val>=0&&val<10){
						i=Chests[select[mode]][((focus-2)-(focus-2)%4)/4][(focus-2)%4];
						if(i<100){
							i*=10;
							i+=val;
							Chests[select[mode]][((focus-2)-(focus-2)%4)/4][(focus-2)%4]=i;
						}
					}
					if(c==8){
						i=Chests[select[mode]][((focus-2)-(focus-2)%4)/4][(focus-2)%4];
						i=i-i%10;
						i/=10;
						Chests[select[mode]][((focus-2)-(focus-2)%4)/4][(focus-2)%4]=i;
					}
				}
			}

			if(submode[mode]==2){
				if(c=='z'){
					MapZoom*=2;
					if(MapZoom==8)MapZoom=1;
				}
				if(focus==1){
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
					select[mode]%=54;
					curtiles=MapGraphics[select[mode]][0];
					curtiles2=MapGraphics[select[mode]][1];
				}
				if(!SecondLayer){
					if(focus==2){
						val=c-'0';
						if(val>=0&&val<10){
							i=MapTileset[select[mode]][0];
							if(i<1000){
								i*=10;
								i+=val;
								MapTileset[select[mode]][0]=i;
							}
						}
						if(c==8){
							i=MapTileset[select[mode]][0];
							i=i-i%10;
							i/=10;
							MapTileset[select[mode]][0]=i;
						}
						MapTileset[select[mode]][0]%=8712;
						MapChanged = true;
					}
					if(focus==3){
						val=c-'0';
						if(val>=0&&val<10){
							i=MapTileset[select[mode]][1];
							if(i<1000){
								i*=10;
								i+=val;
								MapTileset[select[mode]][1]=i;
							}
						}
						if(c==8){
							i=MapTileset[select[mode]][1];
							i=i-i%10;
							i/=10;
							MapTileset[select[mode]][1]=i;
						}
						MapTileset[select[mode]][1]%=8712;
						MapChanged = true;
					}
				} else {
					if(focus==2){
						val=c-'0';
						if(val>=0&&val<10){
							i=MapTileset[select[mode]][2];
							if(i<1000){
								i*=10;
								i+=val;
								MapTileset[select[mode]][2]=i;
							}
						}
						if(c==8){
							i=MapTileset[select[mode]][2];
							i=i-i%10;
							i/=10;
							MapTileset[select[mode]][2]=i;
						}
						MapTileset[select[mode]][2]%=8712;
						MapChanged = true;
					}
					if(focus==3){
						val=c-'0';
						if(val>=0&&val<10){
							i=MapTileset[select[mode]][3];
							if(i<1000){
								i*=10;
								i+=val;
								MapTileset[select[mode]][3]=i;
							}
						}
						if(c==8){
							i=MapTileset[select[mode]][3];
							i=i-i%10;
							i/=10;
							MapTileset[select[mode]][3]=i;
						}
						MapTileset[select[mode]][3]%=8712;
						MapChanged = true;
					}
				}
				if(focus==4){
					val=c-'0';
					if(val>=0&&val<10){
						i=curtiles;
						if(i<10){
							i*=10;
							i+=val;
							curtiles=i;
						}
					}
					if(c==8){
						i=curtiles;
						i=i-i%10;
						i/=10;
						curtiles=i;
					}
					curtiles%=24;
					MapGraphics[select[mode]][0]=curtiles;
					MapChanged=true;
				}
				if(focus==5){
					val=c-'0';
					if(val>=0&&val<10){
						i=curtiles2;
						if(i<10){
							i*=10;
							i+=val;
							curtiles2=i;
						}
					}
					if(c==8){
						i=curtiles2;
						i=i-i%10;
						i/=10;
						curtiles2=i;
					}
					curtiles2%=24;
					MapGraphics[select[mode]][1]=curtiles2;
					MapChanged=true;
				}
				if(focus==6){
					val=c-'0';
					if(val>=0&&val<10){
						i=subselect[mode][0];
						if(i<1000){
							i*=10;
							i+=val;
							subselect[mode][0]=i;
						}
					}
					if(c==8){
						i=subselect[mode][0];
						i=i-i%10;
						i/=10;
						subselect[mode][0]=i;
					}
					if(SecondLayer)subselect[mode][0]%=64;
					subselect[mode][0]%=8712;
				}
				if(focus==7){
					val=c-'0';
					if(val>=0&&val<10){
						i=subselect[mode][1];
						if(i==0){
							i*=10;
							i+=val;
							subselect[mode][1]=i;
						}
					}
					if(c==8){
						i=subselect[mode][1];
						i=i-i%10;
						i/=10;
						subselect[mode][1]=i;
					}
					subselect[mode][1]%=8;
				}
				if(focus==8){
					if(!DisplaySprites){
						if (!DisplaySpecial) {
							val = c - '0';
							if (val >= 0 && val < 10) {
								i = subselect[mode][3];
								if (i < 100) {
									i *= 10;
									i += val;
									subselect[mode][3] = i;
								}
							}
							if (c == 8) {
								i = subselect[mode][3];
								i = i - i % 10;
								i /= 10;
								subselect[mode][3] = i;
							}
						} else {
							val = c - '0';
							if (val >= 0 && val < 10) {
								i = subselect[mode][13];
								if (i < 100) {
									i *= 10;
									i += val;
									subselect[mode][13] = i;
								}
							}
							if (c == 8) {
								i = subselect[mode][13];
								i = i - i % 10;
								i /= 10;
								subselect[mode][13] = i;
							}

							if (subselect[mode][13] < 0)subselect[mode][13] = 4;
							if (subselect[mode][13] > 4)subselect[mode][13] = 0;

						}
					} else {
						val=c-'0';
						if(val>=0&&val<10){
							i=subselect[mode][12];
							if(i<100){
								i*=10;
								i+=val;
								subselect[mode][12]=i;
							}
						}
						if(c==8){
							i=subselect[mode][12];
							i=i-i%10;
							i/=10;
							subselect[mode][12]=i;
						}
						subselect[mode][12]%=NumSpriteSets;
					}
				}
				if(!DisplaySprites){
					if (!DisplayHQ) {
						if (!DisplaySpecial) {
							if (focus == 9) {
								val = c - '0';
								if (val >= 0 && val < 10) {
									i = subselect[mode][4];
									if (i < 100) {
										i *= 10;
										i += val;
										subselect[mode][4] = i;
									}
								}
								if (c == 8) {
									i = subselect[mode][4];
									i = i - i % 10;
									i /= 10;
									subselect[mode][4] = i;
								}
							}
							if (focus == 10) {
								val = c - '0';
								if (val >= 0 && val < 10) {
									i = subselect[mode][5];
									if (i < 100) {
										i *= 10;
										i += val;
										subselect[mode][5] = i;
									}
								}
								if (c == 8) {
									i = subselect[mode][5];
									i = i - i % 10;
									i /= 10;
									subselect[mode][5] = i;
								}
							}
							if (focus == 11) {
								val = c - '0';
								if (val >= 0 && val < 10) {
									i = subselect[mode][6];
									if (i < 100) {
										i *= 10;
										i += val;
										subselect[mode][6] = i;
									}
								}
								if (c == 8) {
									i = subselect[mode][6];
									i = i - i % 10;
									i /= 10;
									subselect[mode][6] = i;
								}
							}
							if (focus == 12) {
								val = c - '0';
								if (val >= 0 && val < 10) {
									i = subselect[mode][7];
									if (i < 100) {
										i *= 10;
										i += val;
										subselect[mode][7] = i;
									}
								}
								if (c == 8) {
									i = subselect[mode][7];
									i = i - i % 10;
									i /= 10;
									subselect[mode][7] = i;
								}
							}
							if (focus == 13) {
								val = c - '0';
								if (val >= 0 && val < 10) {
									i = subselect[mode][9];
									if (i < 10000) {
										i *= 10;
										i += val;
										subselect[mode][9] = i;
									}
								}
								if (c == 8) {
									i = subselect[mode][9];
									i = i - i % 10;
									i /= 10;
									subselect[mode][9] = i;
								}
								if (subselect[mode][9] > 32767)subselect[mode][9] = 32767;
							}
							if (focus == 14) {
								val = c - '0';
								if (val >= 0 && val < 10) {
									i = subselect[mode][10];
									if (i < 1000) {
										i *= 10;
										i += val;
										subselect[mode][10] = i;
									}
								}
								if (c == 8) {
									i = subselect[mode][10];
									i = i - i % 10;
									i /= 10;
									subselect[mode][10] = i;
								}
								if (subselect[mode][10] > 32767)subselect[mode][10] = 32767;
							}


							if (focus == 18) {
								val = c - '0';
								if (val >= 0 && val < 10) {
									i = MapPalOffsets[select[mode]];
									if (i < 0x600000) {
										i *= 16;
										i += val;
										MapPalOffsets[select[mode]] = i;
									}
								}

								val = c - 'a';
								if (val >= 0 && val < 6) {
									i = MapPalOffsets[select[mode]];
									if (i < 0x600000) {
										i *= 16;
										i += val+10;
										MapPalOffsets[select[mode]] = i;
									}
								}
								val = c - 'A';
								if (val >= 0 && val < 6) {
									i = MapPalOffsets[select[mode]];
									if (i < 0x600000) {
										i *= 16;
										i += val + 10;
										MapPalOffsets[select[mode]] = i;
									}
								}

								if (c == 8) {
									i = MapPalOffsets[select[mode]];
									i = i - i % 16;
									i /= 16;
									MapPalOffsets[select[mode]] = i;
								}
								if (MapPalOffsets[select[mode]] > 0x600000)MapPalOffsets[select[mode]] = 0x600000;
							}

							if (focus == 19) {
								val = c - '0';
								if (val >= 0 && val < 10) {
									i = MapGfxOffsets[select[mode]];
									if (i < 0x600000) {
										i *= 16;
										i += val;
										MapGfxOffsets[select[mode]] = i;
									}
								}

								val = c - 'a';
								if (val >= 0 && val < 6) {
									i = MapGfxOffsets[select[mode]];
									if (i < 0x600000) {
										i *= 16;
										i += val + 10;
										MapGfxOffsets[select[mode]] = i;
									}
								}
								val = c - 'A';
								if (val >= 0 && val < 6) {
									i = MapGfxOffsets[select[mode]];
									if (i < 0x600000) {
										i *= 16;
										i += val + 10;
										MapGfxOffsets[select[mode]] = i;
									}
								}

								if (c == 8) {
									i = MapGfxOffsets[select[mode]];
									i = i - i % 16;
									i /= 16;
									MapGfxOffsets[select[mode]] = i;
								}
								if (MapGfxOffsets[select[mode]] > 0x600000)MapGfxOffsets[select[mode]] = 0x600000;
							}
						} else {
							if (focus == 9) {
								val = c - '0';
								if (val >= 0 && val<10) {
									i = MapSpecialTiles[select[mode]][subselect[mode][13]][0];
									if (i<100) {
										i *= 10;
										i += val;
										MapSpecialTiles[select[mode]][subselect[mode][13]][0] = i;
									}
								}
								if (c == 8) {
									i = MapSpecialTiles[select[mode]][subselect[mode][13]][0];

									if (!i)i = 255;
									else {
										i = i - i % 10;
										i /= 10;
									}
									MapSpecialTiles[select[mode]][subselect[mode][13]][0] = i;
								}
								if(MapSpecialTiles[select[mode]][subselect[mode][13]][0]<255)
									MapSpecialTiles[select[mode]][subselect[mode][13]][0] %= MapSize[select[mode]][0];
							}
							if (focus == 10) {
								val = c - '0';
								if (val >= 0 && val<10) {
									i = MapSpecialTiles[select[mode]][subselect[mode][13]][1];
									if (i<100) {
										i *= 10;
										i += val;
										MapSpecialTiles[select[mode]][subselect[mode][13]][1] = i;
									}
								}
								if (c == 8) {
									i = MapSpecialTiles[select[mode]][subselect[mode][13]][1];
									if (!i)i = 255;
									else {
										i = i - i % 10;
										i /= 10;
									}
									MapSpecialTiles[select[mode]][subselect[mode][13]][1] = i;
								}
								if (MapSpecialTiles[select[mode]][subselect[mode][13]][1]<255)
									MapSpecialTiles[select[mode]][subselect[mode][13]][1] %= MapSize[select[mode]][1];
							}
							
							if (focus == 13) {
								val = c - '0';
								if (val >= 0 && val<4) {
									MapSpecialTiles[select[mode]][subselect[mode][13]][2] = val * 8;
								}
								if (c == 8) {
									MapSpecialTiles[select[mode]][subselect[mode][13]][2] = 0;
								}
							}
						}
					} else {
						if (focus == 9) {
							val = c - '0';
							if (val >= 0 && val < 10) {
								i = MapSelect;
								if (i < 100) {
									i *= 10;
									i += val;
									MapSelect = i;
								}
							}
							if (c == 8) {
								i = MapSelect;
								i = i - i % 10;
								i /= 10;
								MapSelect = i;
							}
							MapSelect %= 30;
						}
						if (focus == 10) {
							val = c - '0';
							if (val >= 0 && val < 10) {
								i = HQPos[MapSelect][1];
								if (i < 100) {
									i *= 10;
									i += val;
									HQPos[MapSelect][1] = i;
								}
							}
							if (c == 8) {
								i = HQPos[MapSelect][1];
								i = i - i % 10;
								i /= 10;
								HQPos[MapSelect][1] = i;
							}
						}
						if (focus == 11) {
							val = c - '0';
							if (val >= 0 && val < 10) {
								i = HQPos[MapSelect][2];
								if (i < 100) {
									i *= 10;
									i += val;
									HQPos[MapSelect][2] = i;
								}
							}
							if (c == 8) {
								i = HQPos[MapSelect][2];
								i = i - i % 10;
								i /= 10;
								HQPos[MapSelect][2] = i;
							}
						}
						if (focus == 12) {
							val = c - '0';
							if (val >= 0 && val < 10) {
								i = HQPos[MapSelect][0];
								if (i < 100) {
									i *= 10;
									i += val;
									HQPos[MapSelect][0] = i;
								}
							}
							if (c == 8) {
								i = HQPos[MapSelect][0];
								i = i - i % 10;
								i /= 10;
								HQPos[MapSelect][0] = i;
							}
							HQPos[MapSelect][0] %= 4;
						}
					}
				} else {
					if(focus==9){
						val=c-'0';
						if(val>=0&&val<10){
							i=Sprites[subselect[mode][12]][MapSelect][0];
							if(i<100){
								i*=10;
								i+=val;
								Sprites[subselect[mode][12]][MapSelect][0]=i;
							}
						}
						if(c==8){
							i=Sprites[subselect[mode][12]][MapSelect][0];
							i=i-i%10;
							i/=10;
							Sprites[subselect[mode][12]][MapSelect][0]=i;
						}

						Sprites[subselect[mode][12]][MapSelect][0]%=MapSize[select[mode]][0];
					}
					if(focus==10){
						val=c-'0';
						if(val>=0&&val<10){
							i=Sprites[subselect[mode][12]][MapSelect][1];
							if(i<100){
								i*=10;
								i+=val;
								Sprites[subselect[mode][12]][MapSelect][1]=i;
							}
						}
						if(c==8){
							i=Sprites[subselect[mode][12]][MapSelect][1];
							i=i-i%10;
							i/=10;
							Sprites[subselect[mode][12]][MapSelect][1]=i;
						}

						Sprites[subselect[mode][12]][MapSelect][1]%=MapSize[select[mode]][1];
					}
					if(focus==11){
						val=c-'0';
						if(val>=0&&val<10){
							i=Sprites[subselect[mode][12]][MapSelect][3];
							if(i<100){
								i*=10;
								i+=val;
								Sprites[subselect[mode][12]][MapSelect][3]=i;
							}
						}
						if(c==8){
							i=Sprites[subselect[mode][12]][MapSelect][3];
							i=i-i%10;
							i/=10;
							Sprites[subselect[mode][12]][MapSelect][3]=i;
						}

						Sprites[subselect[mode][12]][MapSelect][3]%=NumGFX[7];
						CountMapSprites();
					}
					if(focus==12){
						val=c-'0';
						if (val >= 0 && val<4) {
							Sprites[subselect[mode][12]][MapSelect][2] &= 0xE7;
							Sprites[subselect[mode][12]][MapSelect][2] += val << 3;
						}
						if (c == 8) {
							Sprites[subselect[mode][12]][MapSelect][2] &= 0xE7;
						}
					}
					if(focus==13){
						val=c-'0';
						if(val>=0&&val<4){
							Sprites[subselect[mode][12]][MapSelect][2]&=0x3F;
							Sprites[subselect[mode][12]][MapSelect][2]+=val<<6;
						}
						if(c==8){
							Sprites[subselect[mode][12]][MapSelect][2]&=0x3F;
						}
					}
					if (focus == 18) {
						val = c - '0';
						if (val >= 0 && val<8) {
							Sprites[subselect[mode][12]][MapSelect][2] &= 0xF8;
							Sprites[subselect[mode][12]][MapSelect][2] += val;
						}
						if (c == 8) {
							Sprites[subselect[mode][12]][MapSelect][2] &= 0xF8;
						}
					}
					if(focus==14){
						val=c-'0';
						if(val>=0&&val<10){
							i=Sprites[subselect[mode][12]][MapSelect][4];
							if(i<100){
								i*=10;
								i+=val;
								Sprites[subselect[mode][12]][MapSelect][4]=i;
							}
						}
						if(c==8){
							i=Sprites[subselect[mode][12]][MapSelect][4];
							i=i-i%10;
							i/=10;
							Sprites[subselect[mode][12]][MapSelect][4]=i;
						}

						Sprites[subselect[mode][12]][MapSelect][4]%=256;
					}
					if(focus==15){
						val=c-'0';
						if(val>=0&&val<10){
							i=(Sprites[subselect[mode][12]][MapSelect][5]&0xF8)/8;
							if(i<100){
								i*=10;
								i+=val;
								i*=8;
								i&=0xF8;
								Sprites[subselect[mode][12]][MapSelect][5]&=0x07;
								Sprites[subselect[mode][12]][MapSelect][5]|=i;
							}
						}
						if(c==8){
							i=(Sprites[subselect[mode][12]][MapSelect][5]&0xF8)/8;
							i=i-i%10;
							i/=10;
							i*=8;
							i&=0xF8;
							Sprites[subselect[mode][12]][MapSelect][5]&=0x07;
							Sprites[subselect[mode][12]][MapSelect][5]|=i;
						}
					}
					if(focus==16){
						val=c-'0';
						if(val>=0&&val<10){
							i=(Sprites[subselect[mode][12]][MapSelect][5]&0x07);
							if(i<100){
								i*=10;
								i+=val;
								i&=0x07;
								Sprites[subselect[mode][12]][MapSelect][5]&=0xF8;
								Sprites[subselect[mode][12]][MapSelect][5]|=i;
							}
						}
						if(c==8){
							i=(Sprites[subselect[mode][12]][MapSelect][5]&0x07);
							i=i-i%10;
							i/=10;
							i&=0x07;
							Sprites[subselect[mode][12]][MapSelect][5]&=0xF8;
							Sprites[subselect[mode][12]][MapSelect][5]|=i;
						}
					}

				}

				if(focus==17){
					val=c-'0';
					if(val>=0&&val<10){
						i=MapMusic[select[mode]][0];
						if(i<100){
							i*=10;
							i+=val;
							MapMusic[select[mode]][0]=i;
						}
					}
					if(c==8){
						i=MapMusic[select[mode]][0];
						i=i-i%10;
						i/=10;
						MapMusic[select[mode]][0]=i;
					}

					MapMusic[select[mode]][0]%=256;
				}

			}

			if(submode[mode]==3){
				if(menu>0){
					if(submenu==1){
						return true;
					}

					if(focus==1){
						switch(SpriteScripts[select[mode]][menu-1]){
							case 8:
							case 12:
							case 13:
							case 14:
							case 15:
							case 16:
							case 18:
							case 19:
							case 20:
							case 21:
							case 22:
							case 24:
								val=c-'0';
								if(val>=0&&val<10){
									MapChanged=true;
									i=SpriteScripts[select[mode]][menu];
									if(i<100){
										i*=10;
										i+=val;
										SpriteScripts[select[mode]][menu]=i;
									}
								}
								if(c==8){
									MapChanged=true;
									i=SpriteScripts[select[mode]][menu];
									i=i-i%10;
									i/=10;
									SpriteScripts[select[mode]][menu]=i;
								}
								SpriteScripts[select[mode]][menu]%=256;
								break;
							case 17:
								val=c-'0';
								if(val>=0&&val<10){
									MapChanged=true;
									i=SpriteScripts[select[mode]][menu]*256+SpriteScripts[select[mode]][menu+1];
									if(i<10000){
										i*=10;
										i+=val;
										SpriteScripts[select[mode]][menu+1]=i%256;
										SpriteScripts[select[mode]][menu]=(i-SpriteScripts[select[mode]][menu+1])/256;
									}
								}
								if(c==8){
									MapChanged=true;
									i=SpriteScripts[select[mode]][menu]*256+SpriteScripts[select[mode]][menu+1];
									i=i-i%10;
									i/=10;
									SpriteScripts[select[mode]][menu+1]=i%256;
									SpriteScripts[select[mode]][menu]=(i-SpriteScripts[select[mode]][menu+1])/256;
								}
								break;
						}
					}

					if(focus==2){
						switch(SpriteScripts[select[mode]][menu-1]){
							case 15:
							case 20:
							case 21:
							case 22:
							case 24:
								val=c-'0';
								if(val>=0&&val<10){
									MapChanged=true;
									i=SpriteScripts[select[mode]][menu+1];
									if(i<100){
										i*=10;
										i+=val;
										SpriteScripts[select[mode]][menu+1]=i;
									}
								}
								if(c==8){
									MapChanged=true;
									i=SpriteScripts[select[mode]][menu+1];
									i=i-i%10;
									i/=10;
									SpriteScripts[select[mode]][menu+1]=i;
								}
								SpriteScripts[select[mode]][menu+1]%=256;
								break;
						}
					}

					if(focus==3){
						switch(SpriteScripts[select[mode]][menu-1]){
							case 24:
								val=c-'0';
								if(val>=0&&val<10){
									MapChanged=true;
									i=SpriteScripts[select[mode]][menu+2];
									if(i<100){
										i*=10;
										i+=val;
										SpriteScripts[select[mode]][menu+2]=i;
									}
								}
								if(c==8){
									MapChanged=true;
									i=SpriteScripts[select[mode]][menu+2];
									i=i-i%10;
									i/=10;
									SpriteScripts[select[mode]][menu+2]=i;
								}
								SpriteScripts[select[mode]][menu+2]%=256;
								break;
						}
					}

					return true;
				}
				if(focus==1){
					val=c-'0';
					if(val>=0&&val<10){
						i=select[mode];
						if(i<100){
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
					select[mode]%=172;

					LastNPCScript = select[mode];
				}
			}