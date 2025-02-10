				Rectangle(memdc, 58 + 160 * ((select[mode] - CharView) / 32), 10 + 16 * ((select[mode] - CharView) % 32), 58 + 160 * ((select[mode] - CharView) / 32) + 120, 10 + 16 * ((select[mode] - CharView) % 32) + 16);

				int q;
				q = 31;
				if (CharView + q > NumChars) q = NumChars - CharView;

				for (i = 0; i < q; i++) {
					if (i + CharView == select[mode] && focus == 1 && cursor) {
						sprintf(out, "%s|", CharName[i + CharView]);
						TextOut(memdc, 58, i * 16 + 10, out, strlen(out));
					} else {
						TextOut(memdc, 58, i * 16 + 10, CharName[i + CharView], strlen(CharName[i + CharView]));
					}

					if (GraphicsLoaded) {
						width = MSSize[0][0][0];
						height = MSSize[0][0][1];

						m = CharMapSprite[i + CharView];

						for (x = 0; x < width / 2; x++) {
							for (y = 0; y < height; y++) {
								k = MapSprites[m][0][x + 24 * cursor + y*width];
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

				if (NumChars == MAX_CHARS) {
					SelectObject(bmpdc, uparrow);
					BitBlt(memdc, 20, 520, 20, 20, bmpdc, 0, 0, SRCCOPY);
					SelectObject(bmpdc, downarrow);
					BitBlt(memdc, 43, 520, 20, 20, bmpdc, 0, 0, SRCCOPY);
				}

				TextOut(memdc,450,10,"Table Offset:",13);

				sprintf(out,"%X",LearnOffset);
				if(focus==4&&cursor){
					sprintf(out,"%s|",out);
				}
				TextOut(memdc,535,10,out,strlen(out));

				SelectObject(bmpdc,plus);
				BitBlt(memdc,260,14,20,20,bmpdc,0,0,SRCCOPY);

				TextOut(memdc,290,10,"SPELLS LEARNED",14);
				TextOut(memdc,290,26,"LEVEL",5);
				TextOut(memdc,365,26,"SPELL",5);
				if((select[mode]>=0&&select[mode]<30) || NumChars > 30){
					k=0;
					for(i=0;i<NumLearn[select[mode]];i++){

						SelectObject(bmpdc, deleteicon);
						BitBlt(memdc, 270, k * 16 + 40, 20, 20, bmpdc, 0, 0, SRCCOPY);

						if (k % 2) {
							HPEN tp = (HPEN)SelectObject(memdc, GetStockObject(NULL_PEN));
							HBRUSH tb = (HBRUSH)SelectObject(memdc, CreateSolidBrush(RGB(180, 180, 180)));

							Rectangle(memdc, 290, k * 16 + 42, 500, k * 16 + 58);

							SelectObject(memdc, tp);
							DeleteObject(SelectObject(memdc, tb));

							int o = i;
							if (GraphicsLoaded)
								for (i = 0; i < 16; i++) {
									for (j = 0; j < 24; j++) {
										int m = Learn[select[mode]][o][1] % 64;
										SetPixel(memdc, 516 + i, j + k * 16 + 38, RGB(IconPalette[SpellImages[m][j * 16 + i]][0], IconPalette[SpellImages[m][j * 16 + i]][1], IconPalette[SpellImages[m][j * 16 + i]][2]));
									}
								}
							i = o;
						} else {
							int o = i;
							if (GraphicsLoaded)
								for (i = 0; i < 16; i++) {
									for (j = 0; j < 24; j++) {
										int m = Learn[select[mode]][o][1] % 64;
										SetPixel(memdc, 500 + i, j + k * 16 + 38, RGB(IconPalette[SpellImages[m][j * 16 + i]][0], IconPalette[SpellImages[m][j * 16 + i]][1], IconPalette[SpellImages[m][j * 16 + i]][2]));
									}
								}
							i = o;
						}
						
						sprintf(out,"%d",Learn[select[mode]][i][0]);
						if(k==subfocus&&focus==2&&cursor){
							sprintf(out,"%s|",out);
						}
						TextOut(memdc,290,42+16*k,out,strlen(out));
						SelectObject(bmpdc,dots);
						BitBlt(memdc,340,41+16*k,20,20,bmpdc,0,0,SRCCOPY);
						sprintf(out,"%d",Learn[select[mode]][i][1]);
						if(k==subfocus&&focus==3&&cursor){
							sprintf(out,"%s|",out);
						}
						TextOut(memdc,365,42+16*k,out,strlen(out));
						if(Learn[select[mode]][i][1]%64<16+16*ExpandSpells){
							if(Learn[select[mode]][i][1]<64){
								sprintf(out,"(%s)",SpellName[Learn[select[mode]][i][1]%64]);
							} else {
								sprintf(out,"(%s %d)",SpellName[Learn[select[mode]][i][1]%64],(Learn[select[mode]][i][1]-Learn[select[mode]][i][1]%64)/64+1);
							}
							TextOut(memdc,405,42+16*k,out,strlen(out));
						}



						k++;
					}
				}
				if(menu>0){
					if(!ExpandSpells){
						r.top=41+16*(menu-1);
						r.left=340;
						r.right=650;
						r.bottom=303+16*(menu-1);
						FillRect(memdc,&r,(HBRUSH)GetStockObject(WHITE_BRUSH));
						for(i=0;i<16;i++){
							sprintf(out,"%s",SpellName[i]);
							TextOut(memdc,345,44+16*i+16*(menu-1),out,strlen(out));
							for(j=1;j<4;j++){
								sprintf(out,"%s %d",SpellName[i],j+1);
								TextOut(memdc,345+75*j,44+16*i+16*(menu-1),out,strlen(out));
							}
						}
					} else {
						r.top=41;
						r.left=340;
						r.right=650;
						r.bottom=287+240;
						FillRect(memdc,&r,(HBRUSH)GetStockObject(WHITE_BRUSH));
						for(i=0;i<32;i++){
							sprintf(out,"%s",SpellName[i]);
							TextOut(memdc,345,44+15*i,out,strlen(out));
							for(j=1;j<4;j++){
								sprintf(out,"%s %d",SpellName[i],j+1);
								TextOut(memdc,345+75*j,44+15*i,out,strlen(out));
							}
						}
					}
				}
