	if(submode[mode]==0){
		SelectObject(bmpdc,charaon);
	} else {
		SelectObject(bmpdc,chara);
	}
	BitBlt(memdc,0,10,40,40,bmpdc,0,0,SRCCOPY);

	if(submode[mode]==1){
		SelectObject(bmpdc,cheston);
	} else {
		SelectObject(bmpdc,chest);
	}
	BitBlt(memdc,0,50,40,40,bmpdc,0,0,SRCCOPY);

	if(submode[mode]==2){
		SelectObject(bmpdc,mapon);
	} else {
		SelectObject(bmpdc,map);
	}
	BitBlt(memdc,0,90,40,40,bmpdc,0,0,SRCCOPY);

	if(submode[mode]==3){
		SelectObject(bmpdc,scripton);
	} else {
		SelectObject(bmpdc,script);
	}
	BitBlt(memdc,0,130,40,40,bmpdc,0,0,SRCCOPY);

	if(submode[mode]==0){
		SelectObject(bmpdc,minus);
		BitBlt(memdc,55,8,20,20,bmpdc,0,0,SRCCOPY);

		sprintf(out,"Set: %d",select[mode]);
		if(focus==1&&cursor)sprintf(out,"%s|",out);
		TextOut(memdc,76,10,out,strlen(out));

		SelectObject(bmpdc,plus);
		BitBlt(memdc,146,8,20,20,bmpdc,0,0,SRCCOPY);

		for (i = 0;i < NumSprites[select[mode]];i++) {

			if (i % 2) {
				HPEN tp = (HPEN)SelectObject(memdc, GetStockObject(NULL_PEN));
				HBRUSH tb = (HBRUSH)SelectObject(memdc, CreateSolidBrush(RGB(180, 180, 180)));

				Rectangle(memdc, 120, i * 16 + 26, 800, i * 16 + 42);

				SelectObject(memdc, tp);
				DeleteObject(SelectObject(memdc, tb));
			}
		}

		for(i=0;i<NumSprites[select[mode]];i++){

			sprintf(out,"Sprite %d",i+1);
			TextOut(memdc,120,i*16+26,out,strlen(out));
			for(j=0;j<6;j++){
				if(focus==2+i*6+j&&cursor){
					sprintf(out,"%d|",Sprites[select[mode]][i][j]);
				} else {
					sprintf(out,"%d",Sprites[select[mode]][i][j]);
				}
				TextOut(memdc,240+80*j,i*16+26,out,strlen(out));
			}

			width = MSSize[0][0][0];
			height = MSSize[0][0][1];

			for (x = 0;x<width/2;x++) {
				for (y = 0;y<height;y++) {
					k = MapSprites[Sprites[select[mode]][i][3]][0][x +24*cursor + y*width];
					if (k<0)k = 0;
					if (k) {
						if (MSPalette[Sprites[select[mode]][i][3]]) {
							if (i % 2)
								SetPixel(memdc, x + 240 + 240 + 32, y + 22 + 16 * i, RGB(EMSPalette[k][0], EMSPalette[k][1], EMSPalette[k][2]));
							else
								SetPixel(memdc, x + 240 + 240 + 56, y + 22 + 16 * i, RGB(EMSPalette[k][0], EMSPalette[k][1], EMSPalette[k][2]));
						} else {
							if (i % 2)
								SetPixel(memdc, x + 240 + 240 + 32, y + 22 + 16 * i, RGB(FMSPalette[k][0], FMSPalette[k][1], FMSPalette[k][2]));
							else
								SetPixel(memdc, x + 240 + 240 + 56, y + 22 + 16 * i, RGB(FMSPalette[k][0], FMSPalette[k][1], FMSPalette[k][2]));
						}
					}
				}
			}
		}

		TextOut(memdc,240,10,"X",1);
		TextOut(memdc,320,10,"Y",1);
		TextOut(memdc,400,10,"Dir/Anim",8);
		TextOut(memdc,480,10,"Gfx",3);
		TextOut(memdc,560,10,"Movement",8);
		TextOut(memdc,640,10,"Dialog",6);

		if (UniSprites[select[mode]] > 12)SetTextColor(memdc, RGB(255, 0, 0));
		sprintf(out, "(%d)", UniSprites[select[mode]]);
		TextOut(memdc, 510, 10, out, strlen(out));
		SetTextColor(memdc, RGB(0, 0, 0));

	}

	if(submode[mode]==1){

		Rectangle(memdc,50,10+16*select[mode],50+70,26+16*select[mode]);

		for(i=0;i<8;i++){
			sprintf(out,"Chapter %d",i+1);
			TextOut(memdc,50,i*16+10,out,strlen(out));
		}

		for (i = 0; i < 32; i++) {

			if (i % 2) {
				HPEN tp = (HPEN)SelectObject(memdc, GetStockObject(NULL_PEN));
				HBRUSH tb = (HBRUSH)SelectObject(memdc, CreateSolidBrush(RGB(180, 180, 180)));

				Rectangle(memdc, 240, i * 16 + 26, 800, i * 16 + 42);

				SelectObject(memdc, tp);
				DeleteObject(SelectObject(memdc, tb));
			}
		}
		for (i = 0; i<32; i++) {
			for(j=0;j<4;j++){
				if(focus==2+i*4+j&&cursor){
					sprintf(out,"%d|",Chests[select[mode]][i][j]);
				} else {
					sprintf(out,"%d",Chests[select[mode]][i][j]);
				}
				TextOut(memdc,240+80*j,i*16+26,out,strlen(out));
			}
			SelectObject(bmpdc, dots);
			BitBlt(memdc, 516, i * 16 + 25, 20, 20, bmpdc, 0, 0, SRCCOPY);

			sprintf(out, "%s", ItemName[Chests[select[mode]][i][3]]);
			TextOut(memdc, 550, i * 16 + 26, out, strlen(out));
		}

		TextOut(memdc,240,10,"Map",3);
		TextOut(memdc,320,10,"X",1);
		TextOut(memdc,400,10,"Y",1);
		TextOut(memdc,480,10,"Item",4);

		if (menu == 1) {
			int doff = submenu;
			if (doff > 15)doff = 15;

			r.top = 17 + 16 * (doff);
			r.left = 302;
			r.right = 772;
			r.bottom = 295 + 16 * (doff);
			FillRect(memdc, &r, (HBRUSH)GetStockObject(WHITE_BRUSH));

			if (NumItems == 128) {
				TextOut(memdc, 400, 20 + 16 * doff, "Extended:", 9);
				if (Chests[select[mode]][submenu][3] & 0x40) {
					SelectObject(bmpdc, checkon);
				} else {
					SelectObject(bmpdc, checkoff);
				}
				BitBlt(memdc, 470, 20 + 16 * doff, 13, 13, bmpdc, 0, 0, SRCCOPY);
			}

			if (Chests[select[mode]][submenu][3] % 64<63)Rectangle(memdc, 307 + 115 * (Chests[select[mode]][submenu][3] % 64 - Chests[select[mode]][submenu][3] % 16) / 16, 36 + Chests[select[mode]][submenu][3] % 16 * 16 + 16 * (doff), 307 + 115 * (Chests[select[mode]][submenu][3] % 64 - Chests[select[mode]][submenu][3] % 16) / 16 + 115, 36 + Chests[select[mode]][submenu][3] % 16 * 16 + 16 + 16 * (doff));
			for (j = 0; j<4; j++) {
				for (i = 0; i<16; i++) {
					if (j == 3 && i == 15)
						sprintf(out, "(None)");
					else
						if (NumItems == 128) {
							sprintf(out, "%s", ItemName[j * 16 + i + (Chests[select[mode]][submenu][3] & 0x40)]);
						} else {
							sprintf(out, "%s", ItemName[j * 16 + i]);
						}
					TextOut(memdc, 307 + 115 * j, 36 + 16 * i + 16 * (doff), out, strlen(out));
				}
			}
		}
	}

	if(submode[mode]==2){

		MMW = 8 + dwidth/60;
		MMH = 8 + dheight/60;

		SelectObject(bmpdc,zoom);
		BitBlt(memdc,20,500+60*(MMH-8),20,20,bmpdc,0,0,SRCCOPY);

		SelectObject(bmpdc,minus);
		BitBlt(memdc,55,8,20,20,bmpdc,0,0,SRCCOPY);

		sprintf(out,"Map: %d",select[mode]);
		if(focus==1&&cursor)sprintf(out,"%s|",out);
		TextOut(memdc,76,10,out,strlen(out));

		SelectObject(bmpdc,plus);
		BitBlt(memdc,136,8,20,20,bmpdc,0,0,SRCCOPY);

		SelectObject(bmpdc,minus);
		BitBlt(memdc,165,8,20,20,bmpdc,0,0,SRCCOPY);

		SelectObject(bmpdc,plus);
		BitBlt(memdc,286,8,20,20,bmpdc,0,0,SRCCOPY);

		SelectObject(bmpdc,minus);
		BitBlt(memdc,315,8,20,20,bmpdc,0,0,SRCCOPY);

		SelectObject(bmpdc,plus);
		BitBlt(memdc,436,8,20,20,bmpdc,0,0,SRCCOPY);

		if(!SecondLayer){
			sprintf(out,"Tileset 1: %d",MapTileset[select[mode]][0]);
			if(focus==2&&cursor)sprintf(out,"%s|",out);
			TextOut(memdc,186,10,out,strlen(out));

			sprintf(out,"Tileset 2: %d",MapTileset[select[mode]][1]);
			if(focus==3&&cursor)sprintf(out,"%s|",out);
			TextOut(memdc,336,10,out,strlen(out));
		} else {
			sprintf(out,"Tileset 3: %d",MapTileset[select[mode]][2]);
			if(focus==2&&cursor)sprintf(out,"%s|",out);
			TextOut(memdc,186,10,out,strlen(out));

			sprintf(out,"Tileset 4: %d",MapTileset[select[mode]][3]);
			if(focus==3&&cursor)sprintf(out,"%s|",out);
			TextOut(memdc,336,10,out,strlen(out));
		}

		SelectObject(bmpdc,minus);
		BitBlt(memdc,465,8,20,20,bmpdc,0,0,SRCCOPY);

		sprintf(out,"Graphics 1: %d",curtiles);
		if(focus==4&&cursor)sprintf(out,"%s|",out);
		TextOut(memdc,486,10,out,strlen(out));

		SelectObject(bmpdc,plus);
		BitBlt(memdc,592,8,20,20,bmpdc,0,0,SRCCOPY);

		SelectObject(bmpdc,minus);
		BitBlt(memdc,621,8,20,20,bmpdc,0,0,SRCCOPY);

		sprintf(out,"Graphics 2: %d",curtiles2);
		if(focus==5&&cursor)sprintf(out,"%s|",out);
		TextOut(memdc,642,10,out,strlen(out));

		SelectObject(bmpdc,plus);
		BitBlt(memdc,748,8,20,20,bmpdc,0,0,SRCCOPY);

		TextOut(memdc,dwidth+590,360,"Display Tile #",14);
		if(DisplayNum)SelectObject(bmpdc,checkon);
		else SelectObject(bmpdc,checkoff);
		BitBlt(memdc,dwidth+570,362,13,13,bmpdc,0,0,SRCCOPY);

		TextOut(memdc,dwidth+590,380,"Display Grid",12);
		if(DisplayGrid)SelectObject(bmpdc,checkon);
		else SelectObject(bmpdc,checkoff);
		BitBlt(memdc,dwidth+570,382,13,13,bmpdc,0,0,SRCCOPY);

		TextOut(memdc,dwidth+590,400,"Display Walkable",16);
		if(DisplayWalk)SelectObject(bmpdc,checkon);
		else SelectObject(bmpdc,checkoff);
		BitBlt(memdc,dwidth+570,402,13,13,bmpdc,0,0,SRCCOPY);

		TextOut(memdc,dwidth+590,420,"Upper Level",11);
		if(SecondLayer)SelectObject(bmpdc,checkon);
		else SelectObject(bmpdc,checkoff);
		BitBlt(memdc,dwidth+570,422,13,13,bmpdc,0,0,SRCCOPY);

		TextOut(memdc,dwidth+590,440,"Display Roof Group",18);
		if(DisplayGroup)SelectObject(bmpdc,checkon);
		else SelectObject(bmpdc,checkoff);
		BitBlt(memdc,dwidth+570,442,13,13,bmpdc,0,0,SRCCOPY);


		TextOut(memdc, dwidth + 590, 460, "Display Special Tiles", 21);
		if (DisplaySpecial)SelectObject(bmpdc, checkon);
		else SelectObject(bmpdc, checkoff);
		BitBlt(memdc, dwidth + 570, 462, 13, 13, bmpdc, 0, 0, SRCCOPY);


		TextOut(memdc,dwidth+590,480,"Display Event",13);
		if(DisplayEvent)SelectObject(bmpdc,checkon);
		else SelectObject(bmpdc,checkoff);
		BitBlt(memdc,dwidth+570,482,13,13,bmpdc,0,0,SRCCOPY);

		TextOut(memdc,dwidth+590,500,"Display Sprites",15);
		if(DisplaySprites)SelectObject(bmpdc,checkon);
		else SelectObject(bmpdc,checkoff);
		BitBlt(memdc,dwidth+570,502,13,13,bmpdc,0,0,SRCCOPY);

		TextOut(memdc, dwidth + 730, 500, "HQ", 2);
		if (DisplayHQ)SelectObject(bmpdc, checkon);
		else SelectObject(bmpdc, checkoff);
		BitBlt(memdc, dwidth + 710, 502, 13, 13, bmpdc, 0, 0, SRCCOPY);
		
		if(!DisplayEvent){
			if(!DisplaySprites){
				if(!DisplayHQ){
					if (!DisplaySpecial) {
						SelectObject(bmpdc, minus);
						BitBlt(memdc, dwidth + 570, 48, 20, 20, bmpdc, 0, 0, SRCCOPY);

						sprintf(out, "Current Tile: %d", subselect[mode][0]);
						if (focus == 6 && cursor)sprintf(out, "%s|", out);
						TextOut(memdc, dwidth + 591, 50, out, strlen(out));

						SelectObject(bmpdc, plus);
						BitBlt(memdc, dwidth + 713, 48, 20, 20, bmpdc, 0, 0, SRCCOPY);

						if (!SecondLayer) {
							TextOut(memdc, dwidth + 590, 150, "Walkable", 8);
							if (Walkable)SelectObject(bmpdc, checkon);
							else SelectObject(bmpdc, checkoff);
							BitBlt(memdc, dwidth + 570, 152, 13, 13, bmpdc, 0, 0, SRCCOPY);

							TextOut(memdc, dwidth + 590, 200, "Advanced Settings", 17);

							sprintf(out, "Palette Offset:    %X", MapPalOffsets[select[mode]]);
							if (focus == 18 && cursor)sprintf(out, "%s|", out);
							TextOut(memdc, dwidth + 590, 240, out, strlen(out));

							sprintf(out, "Graphics Offset: %X", MapGfxOffsets[select[mode]]);
							if (focus == 19 && cursor)sprintf(out, "%s|", out);
							TextOut(memdc, dwidth + 590, 260, out, strlen(out));
						} else {
							sprintf(out, "Roof Group: %d", subselect[mode][1]);
							if (focus == 7 && cursor)sprintf(out, "%s|", out);
							TextOut(memdc, dwidth + 590, 150, out, strlen(out));

							Rectangle(memdc, dwidth + 590, 170, dwidth + 690, 200);
							sprintf(out, "Remove Roof");
							TextOut(memdc, dwidth + 595, 176, out, strlen(out));
						}

						SelectObject(bmpdc, dots);
						BitBlt(memdc, dwidth + 595, 80, 20, 20, bmpdc, 0, 0, SRCCOPY);

						for (i = 0; i < 3; i++) {
							for (j = 0; j < 3; j++) {
								l = subselect[mode][0];
								if (l != -1) {
									if (!SecondLayer) {
										if (l < 660)l += MapTileset[select[mode]][0];
										else l += MapTileset[select[mode]][1] - 660;
									} else
										l += MapTileset[select[mode]][2];

									k = (Tiles[l][i * 2 + j * 6] & 0x07) * 256;
									k += Tiles[l][i * 2 + j * 6 + 1];
									k -= 0x3BE;

									if (k > 255) {
										SelectObject(bmpdc, tileset[curtiles2]);
										k -= 256;
									} else SelectObject(bmpdc, tileset[curtiles]);
									x = (k % 16) * 8;
									y = (k - k % 16) / 2;
									if (Tiles[l][i * 2 + j * 6] & 0x08) {
										x += 7;
										dx = -1;
									} else dx = 1;
									if (Tiles[l][i * 2 + j * 6] & 0x10) {
										y += 7;
										dy = -1;
									} else dy = 1;
									StretchBlt(memdc, dwidth + 620 + i * 20, 80 + j * 20, 20, 20, bmpdc, x, y, 8 * dx, 8 * dy, SRCCOPY);
								}
							}
						}




					} else {


						SelectObject(bmpdc, minus);
						BitBlt(memdc, dwidth + 570, 48, 20, 20, bmpdc, 0, 0, SRCCOPY);

						sprintf(out, "Tile Type: %d", subselect[mode][13]);
						if (focus == 8 && cursor)sprintf(out, "%s|", out);
						TextOut(memdc, dwidth + 591, 50, out, strlen(out));

						SelectObject(bmpdc, plus);
						BitBlt(memdc, dwidth + 713, 48, 20, 20, bmpdc, 0, 0, SRCCOPY);

						
						TextOut(memdc, dwidth + 613, 74, SpecialDesc[subselect[mode][13]], strlen(SpecialDesc[subselect[mode][13]]));


						sprintf(out, "X: %d", MapSpecialTiles[select[mode]][subselect[mode][13]][0]);
						if (focus == 9 && cursor)sprintf(out, "%s|", out);
						TextOut(memdc, dwidth + 570, 100, out, strlen(out));

						sprintf(out, "Y: %d", MapSpecialTiles[select[mode]][subselect[mode][13]][1]);
						if (focus == 10 && cursor)sprintf(out, "%s|", out);
						TextOut(memdc, dwidth + 570, 120, out, strlen(out));


						sprintf(out, "Dir: %d", MapSpecialTiles[select[mode]][subselect[mode][13]][2]/8);
						if (focus == 13 && cursor)sprintf(out, "%s|", out);
						TextOut(memdc, dwidth + 570, 180, out, strlen(out));


						Rectangle(memdc, dwidth + 570, 210, dwidth + 668, 240);
						TextOut(memdc, dwidth + 580, 217, "View Target", 11);

					}
				} else {
					SelectObject(bmpdc, minus);
					BitBlt(memdc, dwidth + 570, 48, 20, 20, bmpdc, 0, 0, SRCCOPY);

					sprintf(out, "Current Slot: %d", MapSelect);
					if (focus == 9 && cursor)sprintf(out, "%s|", out);
					TextOut(memdc, dwidth + 591, 50, out, strlen(out));

					SelectObject(bmpdc, plus);
					BitBlt(memdc, dwidth + 713, 48, 20, 20, bmpdc, 0, 0, SRCCOPY);

					if (MapSelect >= 0 && MapSelect < NumHQPos) {
						sprintf(out, "X: %d", HQPos[MapSelect][1]);
						if (focus == 10 && cursor)sprintf(out, "%s|", out);
						TextOut(memdc, dwidth + 591, 90, out, strlen(out));

						sprintf(out, "Y: %d", HQPos[MapSelect][2]);
						if (focus == 11 && cursor)sprintf(out, "%s|", out);
						TextOut(memdc, dwidth + 591, 110, out, strlen(out));

						sprintf(out, "Dir: %d", HQPos[MapSelect][0]);
						if (focus == 12 && cursor)sprintf(out, "%s|", out);
						TextOut(memdc, dwidth + 591, 130, out, strlen(out));
					}

					/*if (NumHQPos > 30) {
						SelectObject(bmpdc, minus);
						BitBlt(memdc, dwidth + 570, 168, 20, 20, bmpdc, 0, 0, SRCCOPY);
					}

					sprintf(out, "%d Slots", NumHQPos);
					TextOut(memdc, dwidth + 591, 170, out, strlen(out));

					if (NumHQPos < NumChars) {
						SelectObject(bmpdc, plus);
						BitBlt(memdc, dwidth + 673, 168, 20, 20, bmpdc, 0, 0, SRCCOPY);
					}*/
				}
			} else {
				SelectObject(bmpdc,minus);
				BitBlt(memdc,dwidth+570,48,20,20,bmpdc,0,0,SRCCOPY);

				sprintf(out,"Sprite Set: %d",subselect[mode][12]);
				if(focus==8&&cursor)sprintf(out,"%s|",out);
				TextOut(memdc,dwidth+591,50,out,strlen(out));

				SelectObject(bmpdc,plus);
				BitBlt(memdc,dwidth+713,48,20,20,bmpdc,0,0,SRCCOPY);

				Rectangle(memdc,dwidth+590,72,dwidth+708,90);
				TextOut(memdc,dwidth+613,74,"Find Script",11);

				if(MapSelect!=255){
					SelectObject(bmpdc,deleteicon);
					BitBlt(memdc,dwidth+720,99,20,20,bmpdc,0,0,SRCCOPY);

					sprintf(out,"X: %d",Sprites[subselect[mode][12]][MapSelect][0]);
					if(focus==9&&cursor)sprintf(out,"%s|",out);
					TextOut(memdc,dwidth+570,100,out,strlen(out));

					sprintf(out,"Y: %d",Sprites[subselect[mode][12]][MapSelect][1]);
					if(focus==10&&cursor)sprintf(out,"%s|",out);
					TextOut(memdc,dwidth+570,120,out,strlen(out));

					sprintf(out,"Sprite: %d",Sprites[subselect[mode][12]][MapSelect][3]);
					if(focus==11&&cursor)sprintf(out,"%s|",out);
					TextOut(memdc,dwidth+570,140,out,strlen(out));

					sprintf(out,"?: %d",(Sprites[subselect[mode][12]][MapSelect][2]&0x18)>>3);
					if(focus==12&&cursor)sprintf(out,"%s|",out);
					TextOut(memdc,dwidth+570,160,out,strlen(out));

					sprintf(out, "Sitting: ");
					TextOut(memdc, dwidth + 670, 160, out, strlen(out));
					if (Sprites[subselect[mode][12]][MapSelect][2] & 0x20) {
						SelectObject(bmpdc, checkon);
					} else {
						SelectObject(bmpdc, checkoff);
					}
					BitBlt(memdc, dwidth + 730, 162, 13, 13, bmpdc, 0, 0, SRCCOPY);

					sprintf(out,"Dir: %d",Sprites[subselect[mode][12]][MapSelect][2]>>6);
					if(focus==13&&cursor)sprintf(out,"%s|",out);
					TextOut(memdc,dwidth+570,180,out,strlen(out));

					sprintf(out, "Speed: %d", Sprites[subselect[mode][12]][MapSelect][2] & 0x07);
					if (focus == 18 && cursor)sprintf(out, "%s|", out);
					TextOut(memdc, dwidth + 670, 180, out, strlen(out));

					sprintf(out,"Movement: %d",Sprites[subselect[mode][12]][MapSelect][4]);
					if(focus==14&&cursor)sprintf(out,"%s|",out);
					TextOut(memdc,dwidth+570,200,out,strlen(out));

					SelectObject(bmpdc,dots);
					BitBlt(memdc,dwidth+670,200,20,20,bmpdc,0,0,SRCCOPY);

					sprintf(out,"Dialog Number: %d",(Sprites[subselect[mode][12]][MapSelect][5]&0xF8)/8);
					if(focus==15&&cursor)sprintf(out,"%s|",out);
					TextOut(memdc,dwidth+570,220,out,strlen(out));

					sprintf(out,"Dialog Group: %d",(Sprites[subselect[mode][12]][MapSelect][5]&0x07));
					if(focus==16&&cursor)sprintf(out,"%s|",out);
					TextOut(memdc,dwidth+570,240,out,strlen(out));

					sprintf(out, "(%d)", 4*(Sprites[subselect[mode][12]][MapSelect][5] & 0x07));
					TextOut(memdc, dwidth + 680, 240, out, strlen(out));

					Rectangle(memdc,dwidth+590,260,dwidth+708,278);
					TextOut(memdc,dwidth+615,262,"Find Code",11);

				}

				sprintf(out,"Add Sprite");
				TextOut(memdc,dwidth+600,300,out,strlen(out));

				SelectObject(bmpdc,plus);
				BitBlt(memdc,dwidth+575,298,20,20,bmpdc,0,0,SRCCOPY);

			}
		} else {
			SelectObject(bmpdc,minus);
			BitBlt(memdc,dwidth+570,48,20,20,bmpdc,0,0,SRCCOPY);

			sprintf(out,"Current Event: %d",subselect[mode][3]);
			if(focus==8&&cursor)sprintf(out,"%s|",out);
			TextOut(memdc,dwidth+591,50,out,strlen(out));

			SelectObject(bmpdc,plus);
			BitBlt(memdc,dwidth+713,48,20,20,bmpdc,0,0,SRCCOPY);

			SelectObject(bmpdc,dots);
			BitBlt(memdc,dwidth+740,50,20,20,bmpdc,0,0,SRCCOPY);

			switch(subselect[mode][3]){
				case 8:
					TextOut(memdc,dwidth+570,80,"Can Talk Through",16);
					break;
				case 12:
				case 16:
				case 104:
					TextOut(memdc, dwidth + 570, 80, "Teleport", 8);

					if (subselect[mode][4] != -1) {
						
						sprintf(out, "Map: %d", subselect[mode][4]);
						if (focus == 9 && cursor)sprintf(out, "%s|", out);
						TextOut(memdc, dwidth + 570, 100, out, strlen(out));
						sprintf(out, "X: %d", subselect[mode][5]);
						if (focus == 10 && cursor)sprintf(out, "%s|", out);
						TextOut(memdc, dwidth + 570, 120, out, strlen(out));
						sprintf(out, "Y: %d", subselect[mode][6]);
						if (focus == 11 && cursor)sprintf(out, "%s|", out);
						TextOut(memdc, dwidth + 570, 140, out, strlen(out));
						sprintf(out, "?: %d", subselect[mode][7]);
						if (focus == 12 && cursor)sprintf(out, "%s|", out);
						TextOut(memdc, dwidth + 570, 160, out, strlen(out));
						Rectangle(memdc, dwidth + 570, 180, dwidth + 668, 210);
						TextOut(memdc, dwidth + 580, 187, "View Target", 11);
					} else {
						TextOut(memdc, dwidth + 570, 120, "Undefined", 9);

						Rectangle(memdc, dwidth + 570, 180, dwidth + 668, 210);
						TextOut(memdc, dwidth + 582, 187, "Add Target", 10);
					}
					break;
				case 20:
					TextOut(memdc,dwidth+570,80,"Door",4);
					break;
				case 76:
					TextOut(memdc,dwidth+570,80,"No NPC Wander",13);
					break;
				case 100:
					TextOut(memdc,dwidth+570,80,"Readable",8);
					
					sprintf(out,"Message: %d",subselect[mode][10]);
					if(focus==14&&cursor)sprintf(out,"%s|",out);
					TextOut(memdc,dwidth+570,120,out,strlen(out));

					if(TextLoaded){
						i = 160;
						sprintf(temp,"%s",Text[subselect[mode][10]]);

						while(strstr(temp,"[Line]")){
							TextOut(memdc,dwidth+570,i,temp,strstr(temp,"[Line]")-temp);
							sprintf(temp,"%s",strstr(temp,"[Line]")+6);
							i+=20;
						}
						TextOut(memdc,dwidth+570,i,temp,strlen(temp));
					}

					break;
				case 112:
					TextOut(memdc,dwidth+570,80,"Chest",5);
					SelectObject(bmpdc,dots);
					BitBlt(memdc,dwidth+548,120,20,20,bmpdc,0,0,SRCCOPY);
					switch(subselect[mode][8]){
					case 63:
						TextOut(memdc,dwidth+570,120,"Empty",5);
						break;
					case 128:
						sprintf(out,"Gold: %d",subselect[mode][9]);
						if(focus==13&&cursor)sprintf(out,"%s|",out);
						TextOut(memdc,dwidth+570,120,out,strlen(out));
						break;
					case 255:
						break;
					default:
						sprintf(out,"%s",ItemName[subselect[mode][8]]);
						if(focus==9&&cursor)sprintf(out,"%s|",out);
						TextOut(memdc,dwidth+570,120,out,strlen(out));
						break;
					}
					break;
			}
		}

		sprintf(out,"Music: %d",MapMusic[select[mode]][0]);
		if(focus==17&&cursor)sprintf(out,"%s|",out);
		TextOut(memdc,dwidth+591,522,out,strlen(out));

		SelectObject(bmpdc, dots);
		BitBlt(memdc, dwidth+670, 520, 20, 20, bmpdc, 0, 0, SRCCOPY);

		SetBkMode(memdc,2);
		for(u=0;u<MMW*MapZoom;u++){
			for(v=0;v<MMH*MapZoom;v++){
				if(u+ViewX>=MapSize[select[mode]][0]||v+ViewY>=MapSize[select[mode]][1])continue;
				for(i=0;i<3;i++){
					for(j=0;j<3;j++){
						l = MapData[select[mode]][u+ViewX+(v+ViewY)*MapSize[select[mode]][0]];
						if(l<660)l+=MapTileset[select[mode]][0];
						else l+=MapTileset[select[mode]][1]-660;
						if(DisplayEvent&&MapEvent[select[mode]][u+ViewX+(v+ViewY)*MapSize[select[mode]][0]]==20)l=387;
						k = (Tiles[l][i*2+j*6]&0x07)*256;
						k += Tiles[l][i*2+j*6+1];
						k -= 0x3BE;

						if(k>255){
							SelectObject(bmpdc,tileset[curtiles2]);
							k-=256;
						} else SelectObject(bmpdc,tileset[curtiles]);
						if(DisplayEvent&&MapEvent[select[mode]][u+ViewX+(v+ViewY)*MapSize[select[mode]][0]]==20)SelectObject(bmpdc,tileset[0]);
						x = (k%16)*8;
						y = (k-k%16)/2;
						if(Tiles[l][i*2+j*6]&0x08){
							x+=7;
							dx=-1;
						} else dx=1;
						if(Tiles[l][i*2+j*6]&0x10){
							y+=7;
							dy=-1;
						} else dy=1;
						StretchBlt(memdc,50+(i*20+u*60)/MapZoom,40+(j*20+v*60)/MapZoom,20/MapZoom,20/MapZoom,bmpdc,x,y,8*dx,8*dy,SRCCOPY);
					}
				}
				if(DisplayGrid){
					MoveToEx(memdc,50+u*60/MapZoom,40+v*60/MapZoom,0);
					LineTo(memdc,50+(u*60+60)/MapZoom,40+v*60/MapZoom);
					MoveToEx(memdc,50+u*60/MapZoom,40+v*60/MapZoom,0);
					LineTo(memdc,50+u*60/MapZoom,40+(v*60+60)/MapZoom);
				}
				if(MapZoom<4){
					if(DisplayWalk)if(!MapWalk[select[mode]][u+ViewX+(v+ViewY)*MapSize[select[mode]][0]])TextOut(memdc,50+(u*60+26) / MapZoom,40+(v*60+24) / MapZoom,"X",1);
					sprintf(out,"%d",MapData[select[mode]][u+ViewX+(v+ViewY)*MapSize[select[mode]][0]]);
					if(DisplayNum)TextOut(memdc,50+(u*60) / MapZoom + 1,40+(v*60) / MapZoom + 1,out,strlen(out));
					sprintf(out,"%d",MapEvent[select[mode]][u+ViewX+(v+ViewY)*MapSize[select[mode]][0]]);
					if(DisplayEvent)TextOut(memdc,50+u*60 / MapZoom +1,40+v*60 / MapZoom +21 - (5 * (MapZoom-1)),out,strlen(out));
					sprintf(out,"%d",MapFlag[select[mode]][u+ViewX+(v+ViewY)*MapSize[select[mode]][0]]);
					if(DisplayEvent&&MapZoom==1)TextOut(memdc,50+u*60+1,40+v*60+41,out,strlen(out));
					sprintf(out,"%d",MapFlag2[select[mode]][u+ViewX+(v+ViewY)*MapSize[select[mode]][0]]);
					if(DisplayEvent&&MapZoom == 1)TextOut(memdc,50+u*60+21,40+v*60+41,out,strlen(out));
				}
			}
		}
		pen = (HPEN)SelectObject(memdc,CreatePen(PS_SOLID,2,RGB(255,255,255)));
		brush = (HBRUSH)SelectObject(memdc,GetStockObject(NULL_BRUSH));
		if(DisplaySprites){
			for(i=0;i<NumSprites[subselect[mode][12]];i++){
				bool tcursor = cursor;

				if (Sprites[subselect[mode][12]][i][2] & 0x20)cursor = false;

				s = Sprites[subselect[mode][12]][i][3];

				l = Sprites[subselect[mode][12]][i][2]>>6;
				switch(l){
					case 0:
						m=2;
						break;
					case 1:
						m=1;
						break;
					case 2:
						m=0;
						break;
					case 3:
						m=1;
						break;
				}

				x = Sprites[subselect[mode][12]][i][0]-ViewX;
				y = (Sprites[subselect[mode][12]][i][1]&0x7F)-ViewY;
				if(x>=0&&x<MMW*MapZoom&&y>=0&&y<MMH*MapZoom){
					if(MapSelect==i)Rectangle(memdc,50+x*60/MapZoom+1,40+y*60/MapZoom+1,50+(x*60+60)/MapZoom+1,40+(y*60+60)/MapZoom+1);
					for(dx=0;dx<24;dx++){
						for(dy=0;dy<24;dy++){
							switch(MapZoom){
								case 1:
									for(u=0;u<2;u++){
										for(v=0;v<2;v++){
											width = MSSize[s][0][0];
											if(l==1)k = MapSprites[s][m][23-dx+cursor*24+dy*width];
											else k = MapSprites[s][m][dx+cursor*24+dy*width];
											if (k) {
												if (MSPalette[s] || Sprites[subselect[mode][12]][i][1]&0x80)SetPixel(memdc, 50 + x * 60 + dx * 2 + u + 6, 40 + y * 60 + dy * 2 + v + 6, RGB(EMSPalette[k][0], EMSPalette[k][1], EMSPalette[k][2]));
												else SetPixel(memdc, 50 + x * 60 + dx * 2 + u + 6, 40 + y * 60 + dy * 2 + v + 6, RGB(FMSPalette[k][0], FMSPalette[k][1], FMSPalette[k][2]));
											}
										}
									}
									break;
								case 2:
									width = MSSize[s][0][0];
									if(l==1)k = MapSprites[s][m][23-dx+cursor*24+dy*width];
									else k = MapSprites[s][m][dx+cursor*24+dy*width];
									if (k) {
										if (MSPalette[s])SetPixel(memdc, 50 + x * 30 + dx + 3, 40 + y * 30 + dy + 3, RGB(EMSPalette[k][0], EMSPalette[k][1], EMSPalette[k][2]));
										else SetPixel(memdc, 50 + x * 30 + dx + 3, 40 + y * 30 + dy + 3, RGB(FMSPalette[k][0], FMSPalette[k][1], FMSPalette[k][2]));
									}
									break;
								case 4:
									if(dx%2==0&&dy%2==0){
										width = MSSize[s][0][0];
										if(l==1)k = MapSprites[s][m][23-dx+cursor*24+dy*width];
										k = MapSprites[s][m][dx+cursor*24+dy*width];
										if (k) {
											if (MSPalette[s])SetPixel(memdc, 50 + x * 15 + dx / 2 + 1, 40 + y * 15 + dy / 2 + 1, RGB(EMSPalette[k][0], EMSPalette[k][1], EMSPalette[k][2]));
											else SetPixel(memdc, 50 + x * 15 + dx / 2 + 1, 40 + y * 15 + dy / 2 + 1, RGB(FMSPalette[k][0], FMSPalette[k][1], FMSPalette[k][2]));
										}
									}
									break;
							}
						}
					}
				}
				cursor = tcursor;
			}
		}




		if (DisplaySpecial) {

			s = 0;

			l = MapSpecialTiles[select[mode]][subselect[mode][13]][2] / 8;

			switch (l) {
				case 0:
					m = 2;
					break;
				case 1:
					m = 1;
					break;
				case 2:
					m = 0;
					break;
				case 3:
					m = 1;
					break;
			}

			x = MapSpecialTiles[select[mode]][subselect[mode][13]][0] - ViewX;
			y = (MapSpecialTiles[select[mode]][subselect[mode][13]][1] & 0x7F) - ViewY;
			if (x >= 0 && x<MMW*MapZoom&&y >= 0 && y<MMH*MapZoom) {
				if (MapSelect == i)Rectangle(memdc, 50 + x * 60 / MapZoom + 1, 40 + y * 60 / MapZoom + 1, 50 + (x * 60 + 60) / MapZoom + 1, 40 + (y * 60 + 60) / MapZoom + 1);
				for (dx = 0; dx<24; dx++) {
					for (dy = 0; dy<24; dy++) {
						switch (MapZoom) {
							case 1:
								for (u = 0; u<2; u++) {
									for (v = 0; v<2; v++) {
										width = MSSize[s][0][0];
										if (l == 1)k = MapSprites[s][m][23 - dx + cursor * 24 + dy*width];
										else k = MapSprites[s][m][dx + cursor * 24 + dy*width];
										if (k) {
											if (MSPalette[s] || Sprites[subselect[mode][12]][i][1] & 0x80)SetPixel(memdc, 50 + x * 60 + dx * 2 + u + 6, 40 + y * 60 + dy * 2 + v + 6, RGB(EMSPalette[k][0], EMSPalette[k][1], EMSPalette[k][2]));
											else SetPixel(memdc, 50 + x * 60 + dx * 2 + u + 6, 40 + y * 60 + dy * 2 + v + 6, RGB(FMSPalette[k][0], FMSPalette[k][1], FMSPalette[k][2]));
										}
									}
								}
								break;
							case 2:
								width = MSSize[s][0][0];
								if (l == 1)k = MapSprites[s][m][23 - dx + cursor * 24 + dy*width];
								else k = MapSprites[s][m][dx + cursor * 24 + dy*width];
								if (k) {
									if (MSPalette[s])SetPixel(memdc, 50 + x * 30 + dx + 3, 40 + y * 30 + dy + 3, RGB(EMSPalette[k][0], EMSPalette[k][1], EMSPalette[k][2]));
									else SetPixel(memdc, 50 + x * 30 + dx + 3, 40 + y * 30 + dy + 3, RGB(FMSPalette[k][0], FMSPalette[k][1], FMSPalette[k][2]));
								}
								break;
							case 4:
								if (dx % 2 == 0 && dy % 2 == 0) {
									width = MSSize[s][0][0];
									if (l == 1)k = MapSprites[s][m][23 - dx + cursor * 24 + dy*width];
									k = MapSprites[s][m][dx + cursor * 24 + dy*width];
									if (k) {
										if (MSPalette[s])SetPixel(memdc, 50 + x * 15 + dx / 2 + 1, 40 + y * 15 + dy / 2 + 1, RGB(EMSPalette[k][0], EMSPalette[k][1], EMSPalette[k][2]));
										else SetPixel(memdc, 50 + x * 15 + dx / 2 + 1, 40 + y * 15 + dy / 2 + 1, RGB(FMSPalette[k][0], FMSPalette[k][1], FMSPalette[k][2]));
									}
								}
								break;
						}
					}
				}
			}

		}





		if (DisplayHQ) {
			for (i = 0; i<NumHQPos; i++) {
				if(i)s = i;
				else s = 57;

				l = HQPos[i][0];
				switch (l) {
				case 0:
					m = 2;
					break;
				case 1:
					m = 1;
					break;
				case 2:
					m = 0;
					break;
				case 3:
					m = 1;
					break;
				}

				x = HQPos[i][1] - ViewX;
				y = HQPos[i][2] - ViewY;
				if (x >= 0 && x<MMW*MapZoom&&y >= 0 && y<MMH*MapZoom) {
					if (MapSelect == i)Rectangle(memdc, 50 + x * 60 / MapZoom + 1, 40 + y * 60 / MapZoom + 1, 50 + (x * 60 + 60) / MapZoom + 1, 40 + (y * 60 + 60) / MapZoom + 1);
					for (dx = 0; dx<24; dx++) {
						for (dy = 0; dy<24; dy++) {
							switch (MapZoom) {
							case 1:
								for (u = 0; u<2; u++) {
									for (v = 0; v<2; v++) {
										width = MSSize[s][0][0];
										if (l == 1)k = MapSprites[s][m][23 - dx + cursor * 24 + dy*width];
										else k = MapSprites[s][m][dx + cursor * 24 + dy*width];
										if (k) {
											if (MSPalette[s])SetPixel(memdc, 50 + x * 60 + dx * 2 + u + 6, 40 + y * 60 + dy * 2 + v + 6, RGB(EMSPalette[k][0], EMSPalette[k][1], EMSPalette[k][2]));
											else SetPixel(memdc, 50 + x * 60 + dx * 2 + u + 6, 40 + y * 60 + dy * 2 + v + 6, RGB(FMSPalette[k][0], FMSPalette[k][1], FMSPalette[k][2]));
										}
									}
								}
								break;
							case 2:
								width = MSSize[s][0][0];
								if (l == 1)k = MapSprites[s][m][23 - dx + cursor * 24 + dy*width];
								else k = MapSprites[s][m][dx + cursor * 24 + dy*width];
								if (k) {
									if (MSPalette[s])SetPixel(memdc, 50 + x * 30 + dx + 3, 40 + y * 30 + dy + 3, RGB(EMSPalette[k][0], EMSPalette[k][1], EMSPalette[k][2]));
									else SetPixel(memdc, 50 + x * 30 + dx + 3, 40 + y * 30 + dy + 3, RGB(FMSPalette[k][0], FMSPalette[k][1], FMSPalette[k][2]));
								}
								break;
							case 4:
								if (dx % 2 == 0 && dy % 2 == 0) {
									width = MSSize[s][0][0];
									if (l == 1)k = MapSprites[s][m][23 - dx + cursor * 24 + dy*width];
									k = MapSprites[s][m][dx + cursor * 24 + dy*width];
									if (k) {
										if (MSPalette[s])SetPixel(memdc, 50 + x * 15 + dx / 2 + 1, 40 + y * 15 + dy / 2 + 1, RGB(EMSPalette[k][0], EMSPalette[k][1], EMSPalette[k][2]));
										else SetPixel(memdc, 50 + x * 15 + dx / 2 + 1, 40 + y * 15 + dy / 2 + 1, RGB(FMSPalette[k][0], FMSPalette[k][1], FMSPalette[k][2]));
									}
								}
								break;
							}
						}
					}
				}
			}
		}


		DeleteObject(SelectObject(memdc,pen));
		SelectObject(memdc,brush);
		if(SecondLayer)
		for(u=0;u<MMW*MapZoom;u++){
			for(v=0;v<MMH*MapZoom;v++){
				if(u+ViewX>=MapSize[select[mode]][0]||v+ViewY>=MapSize[select[mode]][1])continue;
				l = MapData2[select[mode]][u+ViewX+(v+ViewY)*MapSize[select[mode]][0]];
				if(l!=-1){
					l+=MapTileset[select[mode]][2];
					for(i=0;i<3;i++){
						for(j=0;j<3;j++){
							//l+=2126;
							k = (Tiles[l][i*2+j*6]&0x07)*256;
							k += Tiles[l][i*2+j*6+1];
							k -= 0x3BE;

							if(k>255){
								SelectObject(bmpdc,tileset[curtiles2]);
								k-=256;
							} else SelectObject(bmpdc,tileset[curtiles]);
							x = (k%16)*8;
							y = (k-k%16)/2;
							if(Tiles[l][i*2+j*6]&0x08){
								x+=7;
								dx=-1;
							} else dx=1;
							if(Tiles[l][i*2+j*6]&0x10){
								y+=7;
								dy=-1;
							} else dy=1;
							StretchBlt(memdc,50+(i*20+u*60)/MapZoom,40+(j*20+v*60)/MapZoom,20/MapZoom,20/MapZoom,bmpdc,x,y,8*dx,8*dy,SRCCOPY);
						}
					}
					if(DisplayGrid){
						MoveToEx(memdc,50+u*60/MapZoom,40+v*60/MapZoom,0);
						LineTo(memdc,50+(u*60+60)/MapZoom,40+v*60/MapZoom);
						MoveToEx(memdc,50+u*60/MapZoom,40+v*60/MapZoom,0);
						LineTo(memdc,50+u*60/MapZoom,40+(v*60+60)/MapZoom);
					}
					if(MapZoom<4){
						sprintf(out,"%d",MapData2[select[mode]][u+ViewX+(v+ViewY)*MapSize[select[mode]][0]]);
						if(DisplayNum)TextOut(memdc,50+u*60/MapZoom+1,40+v*60 / MapZoom +1,out,strlen(out));
						sprintf(out,"%d",MapGroup[select[mode]][u+ViewX+(v+ViewY)*MapSize[select[mode]][0]]);
						if(DisplayGroup)TextOut(memdc,50+(u*60+26) / MapZoom,40+(v*60+24) / MapZoom,out,strlen(out));
					}
				}
			}
		}
		if(DisplayGrid){
			MoveToEx(memdc,50+u*60/MapZoom,40,0);
			LineTo(memdc,50+u*60/MapZoom,40+v*60/MapZoom);
			LineTo(memdc,50,40+v*60/MapZoom);
		}
		SetBkMode(memdc,1);

		GetCursorPos(&p);
		ScreenToClient(hWnd,&p);
		p.y-=40;
		if(p.x>=50&&p.x<=50+60*MMW&&p.y>=40&&p.y<=40+60*MMH){
			x=(p.x-50)*MapZoom/60;
			y=(p.y-40)*MapZoom/60;
			x+=ViewX;
			y+=ViewY;
			sprintf(out,"%d, %d",x,y);
			TextOut(memdc,50,520+60*(MMH-8),out,strlen(out));
		}


		if(menu==1){
			r.top=78;
			r.left=dwidth+168;
			r.right=dwidth+620;
			r.bottom=474;
			FillRect(memdc,&r,(HBRUSH)GetStockObject(WHITE_BRUSH));
			if(!SecondLayer){
				SelectObject(bmpdc,prev);
				BitBlt(memdc,dwidth+178,241,20,40,bmpdc,0,0,SRCCOPY);
				SelectObject(bmpdc,next);
				BitBlt(memdc,dwidth+590,241,20,40,bmpdc,0,0,SRCCOPY);
			}
			for(u=0;u<8;u++){
				for(v=0;v<8;v++){
					for(i=0;i<3;i++){
						for(j=0;j<3;j++){
							l = subselect[mode][2]*64+u+v*8;
							if(SecondLayer)l+=MapTileset[select[mode]][2];
							else if(l<660)l+=MapTileset[select[mode]][0];
							else l+=MapTileset[select[mode]][1]-660;

							k = (Tiles[l][i*2+j*6]&0x07)*256;
							k += Tiles[l][i*2+j*6+1];
							k -= 0x3BE;

							if(k>255){
								SelectObject(bmpdc,tileset[curtiles2]);
								k-=256;
							} else SelectObject(bmpdc,tileset[curtiles]);

							x = (k%16)*8;
							y = (k-k%16)/2;
							if(Tiles[l][i*2+j*6]&0x08){
								x+=7;
								dx=-1;
							} else dx=1;
							if(Tiles[l][i*2+j*6]&0x10){
								y+=7;
								dy=-1;
							} else dy=1;
							StretchBlt(memdc,dwidth+198+i*16+u*49,80+j*16+v*49,16,16,bmpdc,x,y,8*dx,8*dy,SRCCOPY);
						}
					}
				}
			}
		}
		if(menu==2){//item
			r.top=17;
			r.left=dwidth+302;
			r.right=dwidth+772;
			r.bottom=295;
			FillRect(memdc,&r,(HBRUSH)GetStockObject(WHITE_BRUSH));
			TextOut(memdc,dwidth+307,20,"Gold:",5);
			if(subselect[mode][8]==128){
				SelectObject(bmpdc,checkon);
			} else {
				SelectObject(bmpdc,checkoff);
			}
			BitBlt(memdc,dwidth+377,20,13,13,bmpdc,0,0,SRCCOPY);
			for(j=0;j<4;j++){
				for(i=0;i<16;i++){
					if(subselect[mode][8]==j*16+i)Rectangle(memdc,dwidth+307+115*j,36+16*i,dwidth+307+115*j+115,36+16*i+16);
					if(j==3&&i==15)sprintf(out,"(None)");
					else sprintf(out,"%s",ItemName[j*16+i]);
					TextOut(memdc,dwidth+307+115*j,36+16*i,out,strlen(out));
				}
			}
			break;
		}
		if(menu==3){//event
			r.top=56;
			r.left=dwidth+580;
			r.right=dwidth+758;
			r.bottom=66+numEvents*18;
			FillRect(memdc,&r,(HBRUSH)GetStockObject(WHITE_BRUSH));

			for(j=0;j<numEvents;j++){
				sprintf(out,"%s",EventDesc[j]);
				TextOut(memdc,dwidth+585,61+18*j,out,strlen(out));
			}
			break;
		}
		if (menu == 4) {//music
			drawSoundList(memdc, dwidth + 670 - 600, 520 - NUM_SOUNDS/3 * 14, MapMusic[select[mode]][0]);
		}

	}

	if(submode[mode]==3){
		unsigned char r=0;
		unsigned char in=0;
		int y=subselect[mode][11]*-20;

		unsigned int c=0;

		unsigned int x=225;

		SelectObject(bmpdc,minus);
		BitBlt(memdc,55,8,20,20,bmpdc,0,0,SRCCOPY);

		sprintf(out,"Script: %d",select[mode]);
		if(focus==1&&cursor&&!menu)sprintf(out,"%s|",out);
		TextOut(memdc,76,10,out,strlen(out));

		SelectObject(bmpdc,plus);
		BitBlt(memdc,146,8,20,20,bmpdc,0,0,SRCCOPY);

		SelectObject(bmpdc,uparrow);
		BitBlt(memdc,100,60,18,18,bmpdc,0,0,SRCCOPY);

		SelectObject(bmpdc,downarrow);
		BitBlt(memdc,100,520,18,18,bmpdc,0,0,SRCCOPY);


		while(c<SpriteScrLen[select[mode]]){
		//while(in!=0x09&&in!=0x19&&in!=0x0E){

			in = SpriteScripts[select[mode]][r++];

			c+=SpriteComLen[in];

			if(y>=0){
				sprintf(out,"%d",r-1);
				TextOut(memdc,x-97,60+y,out,strlen(out));

				if(in!=0x19){
					SelectObject(bmpdc,dots);
					BitBlt(memdc,x-22,60+y-1,20,20,bmpdc,0,0,SRCCOPY);
					SelectObject(bmpdc,deleteicon);
					BitBlt(memdc,x-42,60+y-1,20,20,bmpdc,0,0,SRCCOPY);
				}

				SelectObject(bmpdc,plus);
				BitBlt(memdc,x-62,60+y-1,20,20,bmpdc,0,0,SRCCOPY);

				switch(in){
					case 0:
						TextOut(memdc,x,60+y,SpriteComName[0],strlen(SpriteComName[0]));
						break;
					case 1:
						TextOut(memdc,x,60+y,SpriteComName[1],strlen(SpriteComName[1]));
						break;
					case 2:
						TextOut(memdc,x,60+y,SpriteComName[2],strlen(SpriteComName[2]));
						break;
					case 3:
						TextOut(memdc,x,60+y,SpriteComName[3],strlen(SpriteComName[3]));
						break;
					case 4:
						TextOut(memdc,x,60+y,SpriteComName[4],strlen(SpriteComName[4]));
						break;
					case 5:
						TextOut(memdc,x,60+y,SpriteComName[5],strlen(SpriteComName[5]));
						break;
					case 6:
						TextOut(memdc,x,60+y,SpriteComName[6],strlen(SpriteComName[6]));
						break;
					case 7:
						TextOut(memdc,x,60+y,SpriteComName[7],strlen(SpriteComName[7]));
						break;
					case 8:
						sprintf(out,"%s - %d",SpriteComName[8],SpriteScripts[select[mode]][r++]);
						TextOut(memdc,x,60+y,out,strlen(out));
						break;
					case 9:
						TextOut(memdc,x,60+y,SpriteComName[9],strlen(SpriteComName[9]));
						break;
					case 10:
						TextOut(memdc,x,60+y,SpriteComName[10],strlen(SpriteComName[10]));
						break;
					case 11:
						TextOut(memdc,x,60+y,SpriteComName[11],strlen(SpriteComName[11]));
						break;
					case 12:
						sprintf(out,"%s - %d",SpriteComName[12],SpriteScripts[select[mode]][r++]);
						TextOut(memdc,x,60+y,out,strlen(out));
						break;
					case 13:
						sprintf(out,"%s - %d",SpriteComName[13],SpriteScripts[select[mode]][r++]);
						TextOut(memdc,x,60+y,out,strlen(out));
						break;
					case 14:
						sprintf(out,"%s %d",SpriteComName[14],SpriteScripts[select[mode]][r++]);
						TextOut(memdc,x,60+y,out,strlen(out));
						break;
					case 15:
						sprintf(out,"%s - %d %d",SpriteComName[15],SpriteScripts[select[mode]][r],SpriteScripts[select[mode]][r+1]);
						r+=2;
						TextOut(memdc,x,60+y,out,strlen(out));
						break;
					case 16:
						sprintf(out,"%s - %d",SpriteComName[16],SpriteScripts[select[mode]][r++]);
						TextOut(memdc,x,60+y,out,strlen(out));
						break;
					case 17:
						sprintf(out,"%s - %d",SpriteComName[17],SpriteScripts[select[mode]][r]*256+SpriteScripts[select[mode]][r+1]);
						r+=2;
						TextOut(memdc,x,60+y,out,strlen(out));
						break;
					case 18:
						sprintf(out,"%s - %d %d",SpriteComName[18],SpriteScripts[select[mode]][r],SpriteScripts[select[mode]][r+1]);
						r+=2;
						TextOut(memdc,x,60+y,out,strlen(out));
						break;
					case 19:
						sprintf(out,"%s %d",SpriteComName[19],SpriteScripts[select[mode]][r++]);
						TextOut(memdc,x,60+y,out,strlen(out));
						break;
					case 20:
						sprintf(out,"%s - %d %d",SpriteComName[20],SpriteScripts[select[mode]][r],SpriteScripts[select[mode]][r+1]);
						r+=2;
						TextOut(memdc,x,60+y,out,strlen(out));
						break;
					case 21:
						sprintf(out,"%s - %d %d",SpriteComName[21],SpriteScripts[select[mode]][r],SpriteScripts[select[mode]][r+1]);
						r+=2;
						TextOut(memdc,x,60+y,out,strlen(out));
						break;
					case 22:
						sprintf(out,"%s - %d %d",SpriteComName[22],SpriteScripts[select[mode]][r],SpriteScripts[select[mode]][r+1]);
						r+=2;
						TextOut(memdc,x,60+y,out,strlen(out));
						break;
					case 23:
						TextOut(memdc,x,60+y,SpriteComName[23],strlen(SpriteComName[23]));
						break;
					case 24:
						sprintf(out,"%s - %d %d %d",SpriteComName[24],SpriteScripts[select[mode]][r],SpriteScripts[select[mode]][r+1],SpriteScripts[select[mode]][r+2]);
						//sprintf(out,"Move Sprite - %d %d %d",SpriteScripts[select[mode]][r],SpriteScripts[select[mode]][r+1],SpriteScripts[select[mode]][r+2]);
						r+=3;
						TextOut(memdc,x,60+y,out,strlen(out));
						break;
					case 25:
						TextOut(memdc,x,60+y,SpriteComName[25],strlen(SpriteComName[25]));
						break;
					case 26:
						TextOut(memdc,x,60+y,SpriteComName[26],strlen(SpriteComName[26]));
						break;
					case 27:
						TextOut(memdc,x,60+y,SpriteComName[27],strlen(SpriteComName[27]));
						break;
					case 28:
						TextOut(memdc,x,60+y,SpriteComName[28],strlen(SpriteComName[28]));
						break;
					case 29:
						TextOut(memdc,x,60+y,SpriteComName[29],strlen(SpriteComName[29]));
						break;

				}
			} else {
				r+=SpriteComLen[in]-1;
			}
			y+=20;
		}
		if(menu>0){
			RECT r;
			Rectangle(memdc,x,100,500,300);

			r.top=103;
			r.left=x+52;
			r.right=x+217;
			r.bottom=125;
			FillRect(memdc,&r,(HBRUSH)GetStockObject(WHITE_BRUSH));

			TextOut(memdc, x+55, 105, SpriteComName[SpriteScripts[select[mode]][menu-1]], strlen(SpriteComName[SpriteScripts[select[mode]][menu-1]]));

			SelectObject(bmpdc,down);
			BitBlt(memdc,x+220,105,18,18,bmpdc,0,0,SRCCOPY);

			switch(SpriteScripts[select[mode]][menu-1]){
				case 0:
				case 1:
				case 2:
				case 3:
				case 4:
				case 5:
				case 6:
				case 7:
				case 9:
				case 10:
				case 11:
				case 23:
				case 25:
				case 26:
				case 27:
				case 28:
				case 29:
					TextOut(memdc, x+20, 135, "No additional data.",19);
					break;
				case 8:
					TextOut(memdc, x+20, 135, "Distance:",9);

					sprintf(out,"%d",SpriteScripts[select[mode]][menu]);
					if(focus==1&&cursor)sprintf(out,"%s|",out);
					TextOut(memdc,x+200,135,out,strlen(out));
					break;
				case 12:
					TextOut(memdc, x+20, 135, "Maximum Distance:",18);

					sprintf(out,"%d",SpriteScripts[select[mode]][menu]);
					if(focus==1&&cursor)sprintf(out,"%s|",out);
					TextOut(memdc,x+200,135,out,strlen(out));
					break;
				case 13:
					TextOut(memdc, x+20, 135, "Delay:",6);

					sprintf(out,"%d",SpriteScripts[select[mode]][menu]);
					if(focus==1&&cursor)sprintf(out,"%s|",out);
					TextOut(memdc,x+200,135,out,strlen(out));
					break;
				case 14:
					TextOut(memdc, x+20, 135, "Target:",7);

					sprintf(out,"%d",SpriteScripts[select[mode]][menu]);
					if(focus==1&&cursor)sprintf(out,"%s|",out);
					TextOut(memdc,x+200,135,out,strlen(out));
					break;
				case 16:
					TextOut(memdc, x+20, 135, "Script:",7);

					sprintf(out,"%d",SpriteScripts[select[mode]][menu]);
					if(focus==1&&cursor)sprintf(out,"%s|",out);
					TextOut(memdc,x+200,135,out,strlen(out));
					break;
				case 19:
					TextOut(memdc, x+20, 135, "Check Routine:",14);

					sprintf(out,"%d",SpriteScripts[select[mode]][menu]);
					if(focus==1&&cursor)sprintf(out,"%s|",out);
					TextOut(memdc,x+200,135,out,strlen(out));
					break;

				case 15:
					TextOut(memdc, x+20, 135, "X:",2);

					sprintf(out,"%d",SpriteScripts[select[mode]][menu]);
					if(focus==1&&cursor)sprintf(out,"%s|",out);
					TextOut(memdc,x+200,135,out,strlen(out));

					TextOut(memdc, x+20, 155, "Y:",2);

					sprintf(out,"%d",SpriteScripts[select[mode]][menu+1]);
					if(focus==2&&cursor)sprintf(out,"%s|",out);
					TextOut(memdc,x+200,155,out,strlen(out));
					break;
				case 17:
					TextOut(memdc, x+20, 135, "Message:",8);

					sprintf(out,"%d",SpriteScripts[select[mode]][menu]*256+SpriteScripts[select[mode]][menu+1]);
					if(focus==1&&cursor)sprintf(out,"%s|",out);
					TextOut(memdc,x+200,135,out,strlen(out));

					break;

				case 18:
					TextOut(memdc, x+20, 135, "Sprite:",7);

					sprintf(out,"%d",SpriteScripts[select[mode]][menu]);
					if(focus==1&&cursor)sprintf(out,"%s|",out);
					TextOut(memdc,x+200,135,out,strlen(out));


					if(SpriteScripts[select[mode]][menu+1]==0){
						Rectangle(memdc,x+115,175,x+165,195);
					}
					if(SpriteScripts[select[mode]][menu+1]==2){
						Rectangle(memdc,x+115,255,x+165,275);
					}
					if(SpriteScripts[select[mode]][menu+1]==3){
						Rectangle(memdc,x+40,215,x+90,235);
					}
					if(SpriteScripts[select[mode]][menu+1]==1){
						Rectangle(memdc,x+190,215,x+240,235);
					}

					TextOut(memdc,x+131,176,"Up",2);
					TextOut(memdc,x+ 51,216,"Left",4);
					TextOut(memdc,x+196,216,"Right",5);
					TextOut(memdc,x+121,256,"Down",4);

					break;
				case 20:
				case 21:
				case 22:
					TextOut(memdc, x+20, 135, "Flags:",6);

					sprintf(out,"%d",SpriteScripts[select[mode]][menu]);
					if(focus==1&&cursor)sprintf(out,"%s|",out);
					TextOut(memdc,x+200,135,out,strlen(out));

					TextOut(memdc, x+20, 155, "Group:",6);

					sprintf(out,"%d",SpriteScripts[select[mode]][menu+1]);
					if(focus==2&&cursor)sprintf(out,"%s|",out);
					TextOut(memdc,x+200,155,out,strlen(out));
					break;
				case 24:
					TextOut(memdc, x+20, 135, "Sprite:",7);

					sprintf(out,"%d",SpriteScripts[select[mode]][menu]);
					if(focus==1&&cursor)sprintf(out,"%s|",out);
					TextOut(memdc,x+200,135,out,strlen(out));

					TextOut(memdc, x+20, 155, "X:",2);

					sprintf(out,"%d",SpriteScripts[select[mode]][menu+1]);
					if(focus==2&&cursor)sprintf(out,"%s|",out);
					TextOut(memdc,x+200,155,out,strlen(out));

					TextOut(memdc, x+20, 175, "Y:",2);

					sprintf(out,"%d",SpriteScripts[select[mode]][menu+2]);
					if(focus==3&&cursor)sprintf(out,"%s|",out);
					TextOut(memdc,x+200,175,out,strlen(out));
					break;
			}
			if(submenu==1){
				r.top=103;
				r.left=x+52;
				r.right=x+217+250;
				r.bottom=407;
				FillRect(memdc,&r,(HBRUSH)GetStockObject(WHITE_BRUSH));

				for(int i=0;i<15;i++){
					if(SpriteScripts[select[mode]][menu-1]==i)
						Rectangle(memdc,x+55,105+20*i,x+55+207,105+20*i+20);
					if(SpriteScripts[select[mode]][menu-1]==i+15)
						Rectangle(memdc,x+263,105+20*i,x+263+207,105+20*i+20);
					TextOut(memdc, x+55,  105+20*i, SpriteComName[i], strlen(SpriteComName[i]));
					TextOut(memdc, x+263, 105+20*i, SpriteComName[i+15], strlen(SpriteComName[i+15]));
				}
			}
		}
	}