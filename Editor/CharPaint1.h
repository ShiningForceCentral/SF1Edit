if(submode[mode]==0){
				Rectangle(memdc,58+160*((select[mode] - CharView) /32),10+16*((select[mode] - CharView) %32),58+160*((select[mode] - CharView) /32)+120,10+16*((select[mode] - CharView) %32)+16);

				int q;
				q = 31;
				if (CharView + q > NumChars) q = NumChars - CharView;

				for(i=0;i<q;i++){
					if(i+CharView==select[mode]&&focus==1&&cursor){
						sprintf(out,"%s|",CharName[i+CharView]);
						TextOut(memdc,58,i*16+10,out,strlen(out));
					} else {
						TextOut(memdc,58,i*16+10,CharName[i + CharView],strlen(CharName[i + CharView]));
					}

					if (GraphicsLoaded) {
						width = MSSize[0][0][0];
						height = MSSize[0][0][1];

						m = CharMapSprite[i + CharView];

						for (x = 0; x < width / 2; x++) {
							for (y = 0; y < height; y++) {
								k = MapSprites[m][0][x + 24*cursor + y*width];
								if (k < 0)k = 0;
								if (k) {
									if (!MSPalette[m]) {
										if (i % 2)
											SetPixel(memdc, x + 2, y + 6 + 16 * i, RGB(FMSPalette[k][0], FMSPalette[k][1], FMSPalette[k][2]));
										else
											SetPixel(memdc, x + 2 + 24, y + 6 + 16 * i, RGB(FMSPalette[k][0], FMSPalette[k][1], FMSPalette[k][2]));
									} else {
										if (i % 2)
											SetPixel(memdc, x + 2, y + 6 + 16 * i, RGB(EMSPalette[k][0], EMSPalette[k][1], EMSPalette[k][2]));
										else
											SetPixel(memdc, x + 2 + 24, y + 6 + 16 * i, RGB(EMSPalette[k][0], EMSPalette[k][1], EMSPalette[k][2]));
									}
								}
							}
						}
					}
				}

				if (GraphicsLoaded) {
					width = POSize[select[mode]][0];
					height = POSize[select[mode]][1];

					m = CharPortrait[select[mode]];

					for (int px = 0; px < width * 3 / 4; px++) {
						for (int py = 0; py < height; py++) {

							int k = Portraits[m][px + py*width];
							if (k < 0)k = 0;

							SetPixel(memdc, 664 + px + 16, 417 + py + 8, RGB(POPalette[m][k][0], POPalette[m][k][1], POPalette[m][k][2]));

						}
					}


					m = CharPortrait2[select[mode]];


					for (int px = 0; px < width * 3 / 4; px++) {
						for (int py = 0; py < height; py++) {

							int k = Portraits[m][px + py*width];
							if (k < 0)k = 0;

							SetPixel(memdc, 664 + px + 16 + 48, 417 + py + 8, RGB(POPalette[m][k][0], POPalette[m][k][1], POPalette[m][k][2]));

						}
					}



					width = MSSize[0][0][0];
					height = MSSize[0][0][1];

					m = CharMapSprite[select[mode]];

					for (x = 0; x < width / 2; x++) {
						for (y = 0; y < height; y++) {
							k = MapSprites[m][0][x + 24 * cursor + y*width];
							if (k < 0)k = 0;
							if (k) {
								if (!MSPalette[m]) {
									SetPixel(memdc, x + 680 + 12, y + 500, RGB(FMSPalette[k][0], FMSPalette[k][1], FMSPalette[k][2]));
								} else {
									SetPixel(memdc, x + 680 + 12, y + 500, RGB(EMSPalette[k][0], EMSPalette[k][1], EMSPalette[k][2]));
								}
							}
						}
					}

					m = CharMapSprite2[select[mode]];

					for (x = 0; x < width / 2; x++) {
						for (y = 0; y < height; y++) {
							k = MapSprites[m][0][x + 24 * cursor + y*width];
							if (k < 0)k = 0;
							if (k) {
								if (!MSPalette[m]) {
									SetPixel(memdc, x + 680 + 12 + 48, y + 500, RGB(FMSPalette[k][0], FMSPalette[k][1], FMSPalette[k][2]));
								} else {
									SetPixel(memdc, x + 680 + 12 + 48, y + 500, RGB(EMSPalette[k][0], EMSPalette[k][1], EMSPalette[k][2]));
								}
							}
						}
					}
				}
				/*
				for(i=0;i<q;i++){
					sprintf(out,"%d",Char[select[mode]][i]);
					TextOut(memdc,200,i*16+10,out,strlen(out));
				}*/

				TextOut(memdc, 495, 5, "ID:", 3);
				sprintf(out, "%d", select[mode]);
				TextOut(memdc, 582, 5, out, strlen(out));

				TextOut(memdc,495,25,"Class:",6);

				if(focus==2&&cursor){
					sprintf(out,"%d|",Char[select[mode]][0]);
					TextOut(memdc, 582,25,out,strlen(out));
				} else {
					sprintf(out,"%d",Char[select[mode]][0]);
					TextOut(memdc, 582,25,out,strlen(out));
				}

				SelectObject(bmpdc,dots);
				BitBlt(memdc,473,24,20,20,bmpdc,0,0,SRCCOPY);

				sprintf(out,"(%s)",Classes[Char[select[mode]][0]]);
				TextOut(memdc,620,25,out,strlen(out));

				TextOut(memdc,495,45,"Level:",6);

				if(focus==3&&cursor){
					sprintf(out,"%d|",Char[select[mode]][1]);
					TextOut(memdc, 582,45,out,strlen(out));
				} else {
					sprintf(out,"%d",Char[select[mode]][1]);
					TextOut(memdc, 582,45,out,strlen(out));
				}

				TextOut(memdc, 620, 45, "Promoted At:", 12);

				if (focus == 42 && cursor) {
					sprintf(out, "%d|", CharPromotedAt[select[mode]]);
					TextOut(memdc, 707, 45, out, strlen(out));
				} else {
					sprintf(out, "%d", CharPromotedAt[select[mode]]);
					TextOut(memdc, 707, 45, out, strlen(out));
				}



				TextOut(memdc,495,65,"Attack:",7);

				if(focus==4&&cursor){
					sprintf(out,"%d|",Char[select[mode]][2]);
					TextOut(memdc, 582,65,out,strlen(out));
				} else {
					sprintf(out,"%d",Char[select[mode]][2]);
					TextOut(memdc, 582,65,out,strlen(out));
				}

				TextOut(memdc,495,85,"Defense:",8);

				if(focus==5&&cursor){
					sprintf(out,"%d|",Char[select[mode]][3]);
					TextOut(memdc, 582,85,out,strlen(out));
				} else {
					sprintf(out,"%d",Char[select[mode]][3]);
					TextOut(memdc, 582,85,out,strlen(out));
				}

				TextOut(memdc,495,105,"Agility:",8);

				if(focus==6&&cursor){
					sprintf(out,"%d|",Char[select[mode]][4]);
					TextOut(memdc, 582,105,out,strlen(out));
				} else {
					sprintf(out,"%d",Char[select[mode]][4]);
					TextOut(memdc, 582,105,out,strlen(out));
				}

				TextOut(memdc,495,125,"Move:",5);

				if(focus==7&&cursor){
					sprintf(out,"%d|",Char[select[mode]][5]);
					TextOut(memdc, 582,125,out,strlen(out));
				} else {
					sprintf(out,"%d",Char[select[mode]][5]);
					TextOut(memdc, 582,125,out,strlen(out));
				}

				TextOut(memdc,495,145,"Base Crit:",10);

				if(focus==8&&cursor){
					sprintf(out,"%d| %%",Char[select[mode]][6]);
					TextOut(memdc, 582,145,out,strlen(out));
				} else {
					sprintf(out,"%d %%",Char[select[mode]][6]);
					TextOut(memdc, 582,145,out,strlen(out));
				}

				TextOut(memdc,495,165,"HP:",3);

				if(focus==9&&cursor){
					sprintf(out,"%d|",Char[select[mode]][8]*256+Char[select[mode]][9]);
					TextOut(memdc, 582,165,out,strlen(out));
				} else {
					sprintf(out,"%d",Char[select[mode]][8]*256+Char[select[mode]][9]);
					TextOut(memdc, 582,165,out,strlen(out));
				}

				TextOut(memdc,495,185,"Max HP:",7);

				if(focus==10&&cursor){
					sprintf(out,"%d|",Char[select[mode]][10]*256+Char[select[mode]][11]);
					TextOut(memdc, 582,185,out,strlen(out));
				} else {
					sprintf(out,"%d",Char[select[mode]][10]*256+Char[select[mode]][11]);
					TextOut(memdc, 582,185,out,strlen(out));
				}

				TextOut(memdc,495,205,"MP:",3);

				if(focus==11&&cursor){
					sprintf(out,"%d|",Char[select[mode]][12]);
					TextOut(memdc, 582,205,out,strlen(out));
				} else {
					sprintf(out,"%d",Char[select[mode]][12]);
					TextOut(memdc, 582,205,out,strlen(out));
				}

				TextOut(memdc,495,225,"Max MP:",7);

				if(focus==12&&cursor){
					sprintf(out,"%d|",Char[select[mode]][13]);
					TextOut(memdc, 582,225,out,strlen(out));
				} else {
					sprintf(out,"%d",Char[select[mode]][13]);
					TextOut(memdc, 582,225,out,strlen(out));
				}

				SelectObject(bmpdc,dots);
				BitBlt(memdc,592,244,20,20,bmpdc,0,0,SRCCOPY);
				TextOut(memdc,495,245,"Items:",6);

				if(focus==13&&cursor){
					sprintf(out,"%d|",Char[select[mode]][16]);
					TextOut(memdc,612,245,out,strlen(out));
				} else {
					sprintf(out,"%d",Char[select[mode]][16]);
					TextOut(memdc,612,245,out,strlen(out));
				}
				if(Char[select[mode]][16]!=255){

					SelectObject(bmpdc, deleteicon);
					BitBlt(memdc, 572, 244, 20, 20, bmpdc, 0, 0, SRCCOPY);

					if(Char[select[mode]][16]>=128){
						SetTextColor(memdc, RGB(0, 96, 0));
						sprintf(out,"(%s, Eq)",ItemName[Char[select[mode]][16]%NumItems]);
					} else {
						sprintf(out,"(%s)",ItemName[Char[select[mode]][16]%NumItems]);
					}
					TextOut(memdc,642,245,out,strlen(out));
					SetTextColor(memdc, RGB(0, 0, 0));
				} else {
					TextOut(memdc, 642, 245, "(None)", 6);
				}

				SelectObject(bmpdc,dots);
				BitBlt(memdc,592,264,20,20,bmpdc,0,0,SRCCOPY);
				//TextOut(memdc,495 + 56,265,"Item 2:",7);

				if(focus==14&&cursor){
					sprintf(out,"%d|",Char[select[mode]][17]);
					TextOut(memdc,612,265,out,strlen(out));
				} else {
					sprintf(out,"%d",Char[select[mode]][17]);
					TextOut(memdc,612,265,out,strlen(out));
				}
				if(Char[select[mode]][17]!=255){

					SelectObject(bmpdc, deleteicon);
					BitBlt(memdc, 572, 264, 20, 20, bmpdc, 0, 0, SRCCOPY);

					if(Char[select[mode]][17]>=128){
						SetTextColor(memdc, RGB(0, 96, 0));
						sprintf(out,"(%s, Eq)",ItemName[Char[select[mode]][17]%NumItems]);
					} else {
						sprintf(out,"(%s)",ItemName[Char[select[mode]][17]%NumItems]);
					}
					TextOut(memdc,642,265,out,strlen(out));
					SetTextColor(memdc, RGB(0, 0, 0));
				} else {
					TextOut(memdc, 642, 265, "(None)", 6);
				}

				SelectObject(bmpdc,dots);
				BitBlt(memdc,592,284,20,20,bmpdc,0,0,SRCCOPY);
				//TextOut(memdc,495 + 56,285,"Item 3:",7);

				if(focus==15&&cursor){
					sprintf(out,"%d|",Char[select[mode]][18]);
					TextOut(memdc,612,285,out,strlen(out));
				} else {
					sprintf(out,"%d",Char[select[mode]][18]);
					TextOut(memdc,612,285,out,strlen(out));
				}

				if(Char[select[mode]][18]!=255){

					SelectObject(bmpdc, deleteicon);
					BitBlt(memdc, 572, 284, 20, 20, bmpdc, 0, 0, SRCCOPY);

					if(Char[select[mode]][18]>=128){
						SetTextColor(memdc, RGB(0, 96, 0));
						sprintf(out,"(%s, Eq)",ItemName[Char[select[mode]][18]%NumItems]);
					} else {
						sprintf(out,"(%s)",ItemName[Char[select[mode]][18]%NumItems]);
					}
					TextOut(memdc,642,285,out,strlen(out));
					SetTextColor(memdc, RGB(0, 0, 0));
				} else {
					TextOut(memdc, 642, 285, "(None)", 6);
				}

				SelectObject(bmpdc,dots);
				BitBlt(memdc,592,304,20,20,bmpdc,0,0,SRCCOPY);
				//TextOut(memdc,495 + 56,305,"Item 4:",7);

				if(focus==16&&cursor){
					sprintf(out,"%d|",Char[select[mode]][19]);
					TextOut(memdc,612,305,out,strlen(out));
				} else {
					sprintf(out,"%d",Char[select[mode]][19]);
					TextOut(memdc,612,305,out,strlen(out));
				}
				if(Char[select[mode]][19]!=255){

					SelectObject(bmpdc, deleteicon);
					BitBlt(memdc, 572, 304, 20, 20, bmpdc, 0, 0, SRCCOPY);

					if(Char[select[mode]][19]>=128){
						SetTextColor(memdc, RGB(0, 96, 0));
						sprintf(out,"(%s, Eq)",ItemName[Char[select[mode]][19]%NumItems]);
					} else {
						sprintf(out,"(%s)",ItemName[Char[select[mode]][19]%NumItems]);
					}
					TextOut(memdc,642,305,out,strlen(out));
					SetTextColor(memdc, RGB(0, 0, 0));
				} else {
					TextOut(memdc, 642, 305, "(None)", 6);
				}


				if (GraphicsLoaded)
					for (i = 0; i < 16; i++) {
						for (j = 0; j < 24; j++) {
							int m = Char[select[mode]][16] % NumItems;
							if (Char[select[mode]][16] == 255)m = 63;
							SetPixel(memdc, 537 + i, 267 + j, RGB(IconPalette[ItemImages[m][j * 16 + i]][0], IconPalette[ItemImages[m][j * 16 + i]][1], IconPalette[ItemImages[m][j * 16 + i]][2]));

							m = Char[select[mode]][17] % NumItems;
							if (Char[select[mode]][17] == 255)m = 63;
							SetPixel(memdc, 521 + i, 279 + j, RGB(IconPalette[ItemImages[m][j * 16 + i]][0], IconPalette[ItemImages[m][j * 16 + i]][1], IconPalette[ItemImages[m][j * 16 + i]][2]));

							m = Char[select[mode]][18] % NumItems;
							if (Char[select[mode]][18] == 255)m = 63;
							SetPixel(memdc, 553 + i, 279 + j, RGB(IconPalette[ItemImages[m][j * 16 + i]][0], IconPalette[ItemImages[m][j * 16 + i]][1], IconPalette[ItemImages[m][j * 16 + i]][2]));

							m = Char[select[mode]][19] % NumItems;
							if (Char[select[mode]][19] == 255)m = 63;
							SetPixel(memdc, 537 + i, 291 + j, RGB(IconPalette[ItemImages[m][j * 16 + i]][0], IconPalette[ItemImages[m][j * 16 + i]][1], IconPalette[ItemImages[m][j * 16 + i]][2]));
						}
					}

				SelectObject(bmpdc,dots);
				BitBlt(memdc,592,324,20,20,bmpdc,0,0,SRCCOPY);
				TextOut(memdc,495,325,"Spells:",7);

				if(focus==17&&cursor){
					sprintf(out,"%d|",Char[select[mode]][20]);
					TextOut(memdc,612,325,out,strlen(out));
				} else {
					sprintf(out,"%d",Char[select[mode]][20]);
					TextOut(memdc,612,325,out,strlen(out));
				}
				if(Char[select[mode]][20]%64<16){
					if(Char[select[mode]][20]<64){
						sprintf(out,"(%s)",SpellName[Char[select[mode]][20]%64]);
					} else {
						sprintf(out,"(%s %d)",SpellName[Char[select[mode]][20]%64],(Char[select[mode]][20]-Char[select[mode]][20]%64)/64+1);
					}
					TextOut(memdc,642,325,out,strlen(out));

					SelectObject(bmpdc, deleteicon);
					BitBlt(memdc, 572, 324, 20, 20, bmpdc, 0, 0, SRCCOPY);

				} else if(Char[select[mode]][20]==255){
					TextOut(memdc, 642, 325, "(None)", 6);
				}

				SelectObject(bmpdc,dots);
				BitBlt(memdc,592,344,20,20,bmpdc,0,0,SRCCOPY);
				//TextOut(memdc,495,345,"Spell 2:",8);

				if(focus==18&&cursor){
					sprintf(out,"%d|",Char[select[mode]][21]);
					TextOut(memdc,612,345,out,strlen(out));
				} else {
					sprintf(out,"%d",Char[select[mode]][21]);
					TextOut(memdc,612,345,out,strlen(out));
				}
				if(Char[select[mode]][21]%64<16){
					if(Char[select[mode]][21]<64){
						sprintf(out,"(%s)",SpellName[Char[select[mode]][21]%64]);
					} else {
						sprintf(out,"(%s %d)",SpellName[Char[select[mode]][21]%64],(Char[select[mode]][21]-Char[select[mode]][21]%64)/64+1);
					}
					TextOut(memdc,642,345,out,strlen(out));

					SelectObject(bmpdc, deleteicon);
					BitBlt(memdc, 572, 344, 20, 20, bmpdc, 0, 0, SRCCOPY);

				} else if (Char[select[mode]][20] == 255) {
					TextOut(memdc, 642, 345, "(None)", 6);
				}

				SelectObject(bmpdc,dots);
				BitBlt(memdc,592,364,20,20,bmpdc,0,0,SRCCOPY);
				//TextOut(memdc,495,365,"Spell 3:",8);

				if(focus==19&&cursor){
					sprintf(out,"%d|",Char[select[mode]][22]);
					TextOut(memdc,612,365,out,strlen(out));
				} else {
					sprintf(out,"%d",Char[select[mode]][22]);
					TextOut(memdc,612,365,out,strlen(out));
				}
				if(Char[select[mode]][22]%64<16){
					if(Char[select[mode]][22]<64){
						sprintf(out,"(%s)",SpellName[Char[select[mode]][22]%64]);
					} else {
						sprintf(out,"(%s %d)",SpellName[Char[select[mode]][22]%64],(Char[select[mode]][22]-Char[select[mode]][22]%64)/64+1);
					}
					TextOut(memdc,642,365,out,strlen(out));

					SelectObject(bmpdc, deleteicon);
					BitBlt(memdc, 572, 364, 20, 20, bmpdc, 0, 0, SRCCOPY);

				} else if (Char[select[mode]][22] == 255) {
					TextOut(memdc, 642, 365, "(None)", 6);
				}
				
				SelectObject(bmpdc,dots);
				BitBlt(memdc,592,384,20,20,bmpdc,0,0,SRCCOPY);
				//TextOut(memdc,495,385,"Spell 4:",8);

				if(focus==20&&cursor){
					sprintf(out,"%d|",Char[select[mode]][23]);
					TextOut(memdc,612,385,out,strlen(out));
				} else {
					sprintf(out,"%d",Char[select[mode]][23]);
					TextOut(memdc,612,385,out,strlen(out));
				}
				if(Char[select[mode]][23]%64<16){
					if(Char[select[mode]][23]<64){
						sprintf(out,"(%s)",SpellName[Char[select[mode]][23]%64]);
					} else {
						sprintf(out,"(%s %d)",SpellName[Char[select[mode]][23]%64],(Char[select[mode]][23]-Char[select[mode]][23]%64)/64+1);
					}
					TextOut(memdc,642,385,out,strlen(out));

					SelectObject(bmpdc, deleteicon);
					BitBlt(memdc, 572, 384, 20, 20, bmpdc, 0, 0, SRCCOPY);

				} else if (Char[select[mode]][23] == 255) {
					TextOut(memdc, 642, 385, "(None)", 6);
				}

				if (GraphicsLoaded)
					for (i = 0; i < 16; i++) {
						for (j = 0; j < 24; j++) {
							int m = Char[select[mode]][20] % 64;
							if (Char[select[mode]][20] == 255) {
								m = 63;
								SetPixel(memdc, 537 + i, 267 + j + 80, RGB(IconPalette[ItemImages[m][j * 16 + i]][0], IconPalette[ItemImages[m][j * 16 + i]][1], IconPalette[ItemImages[m][j * 16 + i]][2]));
							} else
							SetPixel(memdc, 537 + i, 267 + j + 80, RGB(IconPalette[SpellImages[m][j * 16 + i]][0], IconPalette[SpellImages[m][j * 16 + i]][1], IconPalette[SpellImages[m][j * 16 + i]][2]));

							m = Char[select[mode]][21] % 64;
							if (Char[select[mode]][21] == 255) {
								m = 63;
								SetPixel(memdc, 521 + i, 279 + j + 80, RGB(IconPalette[ItemImages[m][j * 16 + i]][0], IconPalette[ItemImages[m][j * 16 + i]][1], IconPalette[ItemImages[m][j * 16 + i]][2]));
							} else
							SetPixel(memdc, 521 + i, 279 + j + 80, RGB(IconPalette[SpellImages[m][j * 16 + i]][0], IconPalette[SpellImages[m][j * 16 + i]][1], IconPalette[SpellImages[m][j * 16 + i]][2]));

							m = Char[select[mode]][22] % 64;
							if (Char[select[mode]][22] == 255) {
								m = 63;
								SetPixel(memdc, 553 + i, 279 + j + 80, RGB(IconPalette[ItemImages[m][j * 16 + i]][0], IconPalette[ItemImages[m][j * 16 + i]][1], IconPalette[ItemImages[m][j * 16 + i]][2]));
							} else
							SetPixel(memdc, 553 + i, 279 + j + 80, RGB(IconPalette[SpellImages[m][j * 16 + i]][0], IconPalette[SpellImages[m][j * 16 + i]][1], IconPalette[SpellImages[m][j * 16 + i]][2]));

							m = Char[select[mode]][23] % 64;
							if (Char[select[mode]][23] == 255) {
								m = 63;
								SetPixel(memdc, 537 + i, 291 + j + 80, RGB(IconPalette[ItemImages[m][j * 16 + i]][0], IconPalette[ItemImages[m][j * 16 + i]][1], IconPalette[ItemImages[m][j * 16 + i]][2]));
							} else
							SetPixel(memdc, 537 + i, 291 + j + 80, RGB(IconPalette[SpellImages[m][j * 16 + i]][0], IconPalette[SpellImages[m][j * 16 + i]][1], IconPalette[SpellImages[m][j * 16 + i]][2]));
						}
					}


				/* Battle sprite selection */
				TextOut(memdc,495,425,"Battle:",7);
				if(focus == 34 && cursor) {
					sprintf(out, "%d|", BattleSprite[select[mode]][0]);
					TextOut(memdc, 562, 425, out, strlen(out));
				}
				else {
					sprintf(out, "%d", BattleSprite[select[mode]][0]);
					TextOut(memdc, 562, 425, out, strlen(out));
				}
				TextOut(memdc, 592, 425, "/", 1);
				if (focus == 40 && cursor) {
					sprintf(out, "%d|", BattleSprite2[select[mode]][0]);
					TextOut(memdc, 612, 425, out, strlen(out));
				}
				else {
					sprintf(out, "%d", BattleSprite2[select[mode]][0]);
					TextOut(memdc, 612, 425, out, strlen(out));
				}
				SelectObject(bmpdc, zoom);
				BitBlt(memdc, 640, 425, 20, 20, bmpdc, 0, 0, SRCCOPY);


				/* Battle palette selection */
				TextOut(memdc,495,445,"Palette:",8);
				if(focus==35&&cursor){
					sprintf(out, "%d|", BattleSprite[select[mode]][1]);
					TextOut(memdc, 562, 445, out, strlen(out));
				}
				else {
					sprintf(out, "%d", BattleSprite[select[mode]][1]);
					TextOut(memdc, 562, 445, out, strlen(out));
				}
				TextOut(memdc, 592, 445, "/", 1);
				if (focus == 41 && cursor) {
					sprintf(out, "%d|", BattleSprite2[select[mode]][1]);
					TextOut(memdc, 612, 445, out, strlen(out));
				}
				else {
					sprintf(out, "%d", BattleSprite2[select[mode]][1]);
					TextOut(memdc, 612, 445, out, strlen(out));
				}
				SelectObject(bmpdc, zoom);
				BitBlt(memdc, 640, 445, 20, 20, bmpdc, 0, 0, SRCCOPY);


				/* Portrait selection */
				TextOut(memdc, 495, 465, "Portrait:", 9);
				if (focus == 36 && cursor) {
					sprintf(out, "%d|", CharPortrait[select[mode]]);
					TextOut(memdc, 562, 465, out, strlen(out));
				}
				else {
					sprintf(out, "%d", CharPortrait[select[mode]]);
					TextOut(memdc, 562, 465, out, strlen(out));
				}
				TextOut(memdc, 592, 465, "/", 1);
				if (focus == 38 && cursor) {
					sprintf(out, "%d|", CharPortrait2[select[mode]]);
					TextOut(memdc, 612, 465, out, strlen(out));
				}
				else {
					sprintf(out, "%d", CharPortrait2[select[mode]]);
					TextOut(memdc, 612, 465, out, strlen(out));
				}
				SelectObject(bmpdc, zoom);
				BitBlt(memdc, 640, 465, 20, 20, bmpdc, 0, 0, SRCCOPY);


				/* Map sprite selection */
				TextOut(memdc, 495, 485, "Map:", 4);
				if (focus == 37 && cursor) {
					sprintf(out, "%d|", CharMapSprite[select[mode]]);
					TextOut(memdc, 562, 485, out, strlen(out));
				}
				else {
					sprintf(out, "%d", CharMapSprite[select[mode]]);
					TextOut(memdc, 562, 485, out, strlen(out));
				}
				TextOut(memdc, 592, 485, "/", 1);
				if (focus == 39 && cursor) {
					sprintf(out, "%d|", CharMapSprite2[select[mode]]);
					TextOut(memdc, 612, 485, out, strlen(out));
				}
				else {
					sprintf(out, "%d", CharMapSprite2[select[mode]]);
					TextOut(memdc, 612, 485, out, strlen(out));
				}
				SelectObject(bmpdc, zoom);
				BitBlt(memdc, 640, 485, 20, 20, bmpdc, 0, 0, SRCCOPY);

				/* Arrows */
				if (NumChars == MAX_CHARS) {
					SelectObject(bmpdc, uparrow);
					BitBlt(memdc, 20, 520, 20, 20, bmpdc, 0, 0, SRCCOPY);
					SelectObject(bmpdc, downarrow);
					BitBlt(memdc, 43, 520, 20, 20, bmpdc, 0, 0, SRCCOPY);
				}
				SelectObject(bmpdc, checkoff);

				TextOut(memdc, 515, 512, "Extend Chars", 12);
				BitBlt(memdc, 492, 513, 13, 13, bmpdc, 0, 0, SRCCOPY);



				SetBkMode(memdc, OPAQUE);
				SetBkColor(memdc, RGB(128, 128, 128));

				/* Display HQ messages box for everyone but Max and Nova */
				if (select[mode] > 0 && select[mode] != 30) {

					RoundRect(memdc, 630, 120, 770, 220, 12, 12);
					TextOut(memdc, 646, 112, " HQ MESSAGES ", 13);

					TextOut(memdc, 646, 136, "Active:", 7);
					sprintf(out, "%d", SpecialMessages[255] + select[mode] - 1);
					TextOut(memdc, 706, 136, out, strlen(out));
					SelectObject(bmpdc, zoom);
					BitBlt(memdc, 740, 136, 20, 20, bmpdc, 0, 0, SRCCOPY);

					TextOut(memdc, 646, 156, "Waiting:", 8);
					sprintf(out, "%d", SpecialMessages[255] + select[mode] + (NumChars -1) - 1);
					TextOut(memdc, 706, 156, out, strlen(out));
					SelectObject(bmpdc, zoom);
					BitBlt(memdc, 740, 156, 20, 20, bmpdc, 0, 0, SRCCOPY);

					TextOut(memdc, 646, 176, "On Ship:", 8);
					sprintf(out, "%d", SpecialMessages[255] + select[mode] + 2*(NumChars - 1) - 1);
					TextOut(memdc, 706, 176, out, strlen(out));
					SelectObject(bmpdc, zoom);
					BitBlt(memdc, 740, 176, 20, 20, bmpdc, 0, 0, SRCCOPY);
				}

				//SpecialMessages[255]


				RoundRect(memdc, 200, 43, 452, 530, 12, 12);

				TextOut(memdc,270,35," STAT GROWTH ",13);
				TextOut(memdc,212,55,"UNPROMOTED",10);
				if (select[mode] >= 0 && select[mode] < NumChars)TextOut(memdc,352,55,"PROMOTED",8);

				SetBkMode(memdc, TRANSPARENT);
				SetBkColor(memdc, RGB(255, 255, 255));

				for(i=0;i<6;i++){
					TextOut(memdc,212,90+70*i,StatN[i],strlen(StatN[i]));
					if(focus==21+i&&cursor){
						sprintf(out,"%d|",Stats[select[mode]][i]%64);
						TextOut(memdc, 212,110+70*i,out,strlen(out));
					} else {
						sprintf(out,"%d",Stats[select[mode]][i]%64);
						TextOut(memdc, 212,110+70*i,out,strlen(out));
					}
					TextOut(memdc,342,90+70*i,StatN[i],strlen(StatN[i]));
					if(focus==27+i&&cursor){
						sprintf(out,"%d|",Stats[select[mode]][i+6]%64);
						TextOut(memdc,342,110+70*i,out,strlen(out));
					} else {
						sprintf(out,"%d",Stats[select[mode]][i+6]%64);
						TextOut(memdc,342,110+70*i,out,strlen(out));
					}
					for(int j=0;j<4;j++){
						if(Stats[select[mode]][i]/64==j)SelectObject(bmpdc,rateon[j]);
						else SelectObject(bmpdc,rate[j]);
						BitBlt(memdc,260+30*(j%2),90+70*i+30*(j/2),20,20,bmpdc,0,0,SRCCOPY);
						if(Stats[select[mode]][i+6]/64==j)SelectObject(bmpdc,rateon[j]);
						else SelectObject(bmpdc,rate[j]);
						BitBlt(memdc,390+30*(j%2),90+70*i+30*(j/2),20,20,bmpdc,0,0,SRCCOPY);
					}
				}

				Rectangle(memdc,218,500,438,520);
				TextOut(memdc, 268, 502, "Edit Growth Curves",18);

				switch(menu){
					case 1://class
						r.top=41;
						r.left=456;
						r.right=570 + 114 * (NumClasses==64);
						r.bottom=530;
						FillRect(memdc,&r,(HBRUSH)GetStockObject(WHITE_BRUSH));
						for(i=0;i<32;i++){
							sprintf(out,"%s",Classes[i]);
							TextOut(memdc,458,43+15*i,out,strlen(out));

							if (NumClasses == 64) {
								sprintf(out, "%s", Classes[i+32]);
								TextOut(memdc, 458+114, 43 + 15 * i, out, strlen(out));
							}
						}
						break;
					case 2://item
						r.top=17+16*(submenu);
						r.left=302;
						r.right=772;
						r.bottom=295+16*(submenu);
						FillRect(memdc,&r,(HBRUSH)GetStockObject(WHITE_BRUSH));
						TextOut(memdc,307,20+16*submenu,"Equipped:",9);
						if(Char[select[mode]][16+submenu]&0x80){
							SelectObject(bmpdc,checkon);
						} else {
							SelectObject(bmpdc,checkoff);
						}
						BitBlt(memdc,377,20+16*submenu,13,13,bmpdc,0,0,SRCCOPY);

						if(NumItems==128){
							TextOut(memdc,400,20+16*submenu,"Extended:",9);
							if(Char[select[mode]][16+submenu]&0x40){
								SelectObject(bmpdc,checkon);
							} else {
								SelectObject(bmpdc,checkoff);
							}
							BitBlt(memdc,470,20+16*submenu,13,13,bmpdc,0,0,SRCCOPY);
						}

						if(Char[select[mode]][16+submenu]%64<63)Rectangle(memdc,307+115*(Char[select[mode]][16+submenu]%64-Char[select[mode]][16+submenu]%16)/16,36+Char[select[mode]][16+submenu]%16*16+16*(submenu),307+115*(Char[select[mode]][16+submenu]%64-Char[select[mode]][16+submenu]%16)/16+115,36+Char[select[mode]][16+submenu]%16*16+16+16*(submenu));
						for(j=0;j<4;j++){
							for(i=0;i<16;i++){
								if(j==3&&i==15)
									sprintf(out,"(None)");
								else
									if(NumItems==128){
										sprintf(out,"%s",ItemName[j*16+i+(Char[select[mode]][16+submenu]&0x40)]);
									} else {
										sprintf(out,"%s",ItemName[j*16+i]);
									}
								TextOut(memdc,307+115*j,36+16*i+16*(submenu),out,strlen(out));
							}
						}
						break;
					case 3://spell
						r.top=81+16*(submenu);
						r.left=302;
						r.right=612;
						r.bottom=343+16*(submenu);
						FillRect(memdc,&r,(HBRUSH)GetStockObject(WHITE_BRUSH));
						if(Char[select[mode]][20+submenu]%64<16)Rectangle(memdc,307+75*(Char[select[mode]][20+submenu]-Char[select[mode]][20+submenu]%64)/64,84+Char[select[mode]][20+submenu]%64*16+16*(submenu),307+75*(Char[select[mode]][20+submenu]-Char[select[mode]][20+submenu]%64)/64+75,84+Char[select[mode]][20+submenu]%64*16+16+16*(submenu));
						for(i=0;i<16;i++){
							sprintf(out,"%s",SpellName[i]);
							TextOut(memdc,307,84+16*i+16*(submenu),out,strlen(out));
							for(j=1;j<4;j++){
								sprintf(out,"%s %d",SpellName[i],j+1);
								TextOut(memdc,307+75*j,84+16*i+16*(submenu),out,strlen(out));
							}
						}
						break;
				}
}

if(submode[mode]==1){

	TextOut(memdc,40,30,"Curve:",6);

	l=0;
	for(int j=0;j<4;j++){
		if(subselect[mode][0]==j)SelectObject(bmpdc,rateon[j]);
		else SelectObject(bmpdc,rate[j]);
		BitBlt(memdc,90+30*(j),30,20,20,bmpdc,0,0,SRCCOPY);

		if(subselect[mode][0]==j){
			MoveToEx(memdc,340,440,0);
			for(int k=0;k<20;k++){
				if(Curves[j][k]!=0xFF){
					LineTo(memdc,340+k*20,440-Curves[j][k]*4);

					sprintf(out,"%d",k+1);
					TextOut(memdc,340+k*20,446,out,strlen(out));

					if(Curves[j][k]-l>4){
						sprintf(out,"%d",Curves[j][k]);
						TextOut(memdc,310,432-Curves[j][k]*4,out,strlen(out));
						l = Curves[j][k];
					}
				}
			}
		}
	}

	TextOut(memdc,40,70,"Level",5);
	TextOut(memdc,140,70,"Percent",7);

	for(int k=1;k<20;k++){
		sprintf(out,"%d",k+1);
		TextOut(memdc,40,70+20*k,out,strlen(out));
		if(Curves[subselect[mode][0]][k]==0xFF){
			sprintf(out,"(Empty)");
		} else {
			sprintf(out,"%d",Curves[subselect[mode][0]][k]);
		}
		if(focus==k&&cursor){
			sprintf(out,"%s|",out);
		}
		TextOut(memdc,140,70+20*k,out,strlen(out));
	}

	MoveToEx(memdc,340,40,0);
	LineTo(memdc,340,440);
	LineTo(memdc,740,440);

	TextOut(memdc,310,432,"0",1);
	TextOut(memdc,336,446,"1",1);

	TextOut(memdc,520,466,"Level",5);

	Rectangle(memdc,620,524,790,544);
	TextOut(memdc,690,526,"Back",4);
}