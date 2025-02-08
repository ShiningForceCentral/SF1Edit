			if(submode[mode]==0){

				Rectangle(memdc,20,10+16*(select[mode]%32),20+70,10+16*(select[mode]%32)+16);

				for(i=0;i<NUM_BATTLES;i++){
					sprintf(out,"Battle %d",i+1);
					TextOut(memdc,20,i*16+10,out,strlen(out));
				}

				for(i=0;i<NumEnemies[select[mode]];i++){
					sprintf(out,"Enemy %d",i+1);
					sprintf(out,MonsterName[Battle[select[mode]][i][0]],i+1);
					TextOut(memdc,120,i*16+26,out,strlen(out));
					for(j=0;j<8;j++){
						if(focus==2+i*8+j&&cursor){
							sprintf(out,"%d|",Battle[select[mode]][i][j]);
						} else {
							sprintf(out,"%d",Battle[select[mode]][i][j]);
						}
						TextOut(memdc,240+60*j,i*16+26,out,strlen(out));
					}
					SelectObject(bmpdc,dots);
					BitBlt(memdc,219,i*16+25,20,20,bmpdc,0,0,SRCCOPY);	
					BitBlt(memdc,279,i*16+25,20,20,bmpdc,0,0,SRCCOPY);	
					BitBlt(memdc,339,i*16+25,20,20,bmpdc,0,0,SRCCOPY);
					BitBlt(memdc,399,i*16+25,20,20,bmpdc,0,0,SRCCOPY);
					BitBlt(memdc,740,i*16+25,20,20,bmpdc,0,0,SRCCOPY);
				}

				TextOut(memdc,240,10,"Enemy",5);
				TextOut(memdc,300,10,"Item 1",6);
				TextOut(memdc,360,10,"Item 2",6);
				TextOut(memdc,420,10,"Spell",5);
				TextOut(memdc,480,10,"X",1);
				TextOut(memdc,540,10,"Y",1);
				TextOut(memdc,600,10,"?",1);
				TextOut(memdc,660,10,"# Spawn",7);
				TextOut(memdc,740,10,"AI",2);

				sprintf(out,"Music: %d",MapHeader[BattleHeaderPos[select[mode]]][0]);
				TextOut(memdc,110,500,out,strlen(out));



				sprintf(out,"Map: %d",MapHeader[BattleHeaderPos[select[mode]]][1]);
				TextOut(memdc,180,500,out,strlen(out));

				if(menu==1){
					l=submenu;
					if(l>14)l=14;
					r.top=9+16*(l);
					r.left=279;
					r.right=749;
					r.bottom=287+16*(l);
					FillRect(memdc,&r,(HBRUSH)GetStockObject(WHITE_BRUSH));
					TextOut(memdc,284,12+16*l,"Equipped:",9);
					if(Battle[select[mode]][submenu][1]&0x80){
						SelectObject(bmpdc,checkon);
					} else {
						SelectObject(bmpdc,checkoff);
					}

					BitBlt(memdc,354,12+16*l,13,13,bmpdc,0,0,SRCCOPY);
					if(Battle[select[mode]][submenu][1]%128<63)Rectangle(memdc,284+115*(Battle[select[mode]][submenu][1]%128-Battle[select[mode]][submenu][1]%16)/16,28+Battle[select[mode]][submenu][1]%16*16+16*(l),284+115*(Battle[select[mode]][submenu][1]%128-Battle[select[mode]][submenu][1]%16)/16+115,28+Battle[select[mode]][submenu][1]%16*16+16+16*(l));
					for(j=0;j<4;j++){
						for(i=0;i<16;i++){
							if(j==3&&i==15)sprintf(out,"(None)");
							else sprintf(out,"%s",ItemName[j*16+i]);
							TextOut(memdc,284+115*j,28+16*i+16*(l),out,strlen(out));
						}
					}
				}

				if(menu==2){
					l=submenu;
					if(l>14)l=14;
					r.top=9+16*(l);
					r.left=339;
					r.right=809;
					r.bottom=287+16*(l);
					FillRect(memdc,&r,(HBRUSH)GetStockObject(WHITE_BRUSH));
					TextOut(memdc,344,12+16*l,"Equipped:",9);
					if(Battle[select[mode]][submenu][2]&0x80){
						SelectObject(bmpdc,checkon);
					} else {
						SelectObject(bmpdc,checkoff);
					}
					BitBlt(memdc,414,12+16*l,13,13,bmpdc,0,0,SRCCOPY);
					if(Battle[select[mode]][submenu][2]%128<63)Rectangle(memdc,344+115*(Battle[select[mode]][submenu][2]%128-Battle[select[mode]][submenu][2]%16)/16,28+Battle[select[mode]][submenu][2]%16*16+16*(l),344+115*(Battle[select[mode]][submenu][2]%128-Battle[select[mode]][submenu][2]%16)/16+115,28+Battle[select[mode]][submenu][2]%16*16+16+16*(l));
					for(j=0;j<4;j++){
						for(i=0;i<16;i++){
							if(j==3&&i==15)sprintf(out,"(None)");
							else sprintf(out,"%s",ItemName[j*16+i]);
							TextOut(memdc,344+115*j,28+16*i+16*(l),out,strlen(out));
						}
					}
				}

				if(menu==3){
					if(!ExpandSpells){
						r.top=25+16*(submenu);
						r.left=399;
						r.right=709;
						r.bottom=287+16*(submenu);
						FillRect(memdc,&r,(HBRUSH)GetStockObject(WHITE_BRUSH));
						if(Battle[select[mode]][submenu][3]%64<16)Rectangle(memdc,404+75*(Battle[select[mode]][submenu][3]-Battle[select[mode]][submenu][3]%64)/64,28+Battle[select[mode]][submenu][3]%64*16+16*(submenu),404+75*(Battle[select[mode]][submenu][3]-Battle[select[mode]][submenu][3]%64)/64+75,28+Battle[select[mode]][submenu][3]%64*16+16+16*(submenu));
						for(i=0;i<16;i++){
							sprintf(out,"%s",SpellName[i]);
							TextOut(memdc,404,28+16*i+16*(submenu),out,strlen(out));
							for(j=1;j<4;j++){
								sprintf(out,"%s %d",SpellName[i],j+1);
								TextOut(memdc,404+75*j,28+16*i+16*(submenu),out,strlen(out));
							}
						}
					} else {
						r.top=25;
						r.left=399;
						r.right=709;
						r.bottom=543;
						FillRect(memdc,&r,(HBRUSH)GetStockObject(WHITE_BRUSH));
						if(Battle[select[mode]][submenu][3]%64<16)Rectangle(memdc,404+75*(Battle[select[mode]][submenu][3]-Battle[select[mode]][submenu][3]%64)/64,28+Battle[select[mode]][submenu][3]%64*16,404+75*(Battle[select[mode]][submenu][3]-Battle[select[mode]][submenu][3]%64)/64+75,28+Battle[select[mode]][submenu][3]%64*16+16);
						for(i=0;i<32;i++){
							sprintf(out,"%s",SpellName[i]);
							TextOut(memdc,404,28+16*i,out,strlen(out));
							for(j=1;j<4;j++){
								sprintf(out,"%s %d",SpellName[i],j+1);
								TextOut(memdc,404+75*j,28+16*i,out,strlen(out));
							}
						}
					}
				}

				if(menu==4){
					l=submenu;
					if(l>14)l=14;
					r.top=25+16*(l);
					r.left=179;
					r.right=759;
					r.bottom=287+16*(l);
					FillRect(memdc,&r,(HBRUSH)GetStockObject(WHITE_BRUSH));
					//if(Battle[select[mode]][submenu][1]%128<63)Rectangle(memdc,284+115*(Battle[select[mode]][submenu][1]%128-Battle[select[mode]][submenu][1]%16)/16,28+Battle[select[mode]][submenu][1]%16*16+16*(submenu),284+115*(Battle[select[mode]][submenu][1]%128-Battle[select[mode]][submenu][1]%16)/16+115,28+Battle[select[mode]][submenu][1]%16*16+16+16*(submenu));
					for(j=0;j<5;j++){
						for(i=0;i<16;i++){
							if(j*16+i<73){
								if(Battle[select[mode]][submenu][0]==j*16+i)
									Rectangle(memdc,184+115*j,28+16*i+16*(l),184+115*(j+1),28+16*(i+1)+16*l);
								sprintf(out,"%s",MonsterName[j*16+i]);
								TextOut(memdc,184+115*j,28+16*i+16*(l),out,strlen(out));
							}
						}
					}
				}


			}

			if(submode[mode]==1){
				TextOut(memdc,10,5,"Number of Behaviors:",20);
				sprintf(out,"%d",NumBehaviors[select[mode]][menu]);
				if(focus==1&&cursor)sprintf(out,"%s|",out);
				TextOut(memdc,160,5,out,strlen(out));

				r.top=0;
				r.left=200;
				r.right=240;
				r.bottom=24;
				FillRect(memdc,&r,(HBRUSH)GetStockObject(WHITE_BRUSH));
				TextOut(memdc,204,4,"Back",4);

				for(j=0;j<NumBehaviors[select[mode]][menu];j++){
					sprintf(out,"Behavior %d",j+1);
					TextOut(memdc,15+260*(j%3),27+170*(j-j%3)/3,out,strlen(out));

					TextOut(memdc,25+260*(j%3),59+170*(j-j%3)/3,"Triggers",8);

					TextOut(memdc,25+260*(j%3),139+170*(j-j%3)/3,"Action:",7);
					sprintf(out,"%d",Behaviors[select[mode]][menu][j][1]);
					if(focus==2&&subfocus==j&&cursor)sprintf(out,"%s|",out);
					TextOut(memdc,85+260*(j%3),139+170*(j-j%3)/3,out,strlen(out));

					TextOut(memdc,25+260*(j%3),155+170*(j-j%3)/3,"Value 1:",8);

					if(Behaviors[select[mode]][menu][j][1]==2){
						Rectangle(memdc,85+260*(j%3),155+170*(j-j%3)/3, 197+260*(j%3),173+170*(j-j%3)/3);
						TextOut(memdc,112+260*(j%3),155+170*(j-j%3)/3,"Edit Path",9);
					} else {
						sprintf(out,"%d",Behaviors[select[mode]][menu][j][2]);
						if(focus==3&&subfocus==j&&cursor)sprintf(out,"%s|",out);
						TextOut(memdc,85+260*(j%3),155+170*(j-j%3)/3,out,strlen(out));
					}

					TextOut(memdc,25+260*(j%3),171+170*(j-j%3)/3,"Value 2:",8);
					sprintf(out,"%d",Behaviors[select[mode]][menu][j][3]);
					if(focus==4&&subfocus==j&&cursor)sprintf(out,"%s|",out);
					TextOut(memdc,85+260*(j%3),171+170*(j-j%3)/3,out,strlen(out));

					switch(Behaviors[select[mode]][menu][j][1]){
						case 0xFF:
							TextOut(memdc,115+260*(j%3),139+170*(j-j%3)/3,"(No Action)",11);
							TextOut(memdc,115+260*(j%3),155+170*(j-j%3)/3,"(Unused)",8);
							TextOut(memdc,115+260*(j%3),171+170*(j-j%3)/3,"(Unused)",8);
							break;
						case 0:
							TextOut(memdc,115+260*(j%3),139+170*(j-j%3)/3,"(Move To)",9);
							TextOut(memdc,115+260*(j%3),155+170*(j-j%3)/3,"(X)",3);
							TextOut(memdc,115+260*(j%3),171+170*(j-j%3)/3,"(Y)",3);
							break;
						case 1:
							TextOut(memdc,115+260*(j%3),139+170*(j-j%3)/3,"(Charge?)",9);
							TextOut(memdc,115+260*(j%3),155+170*(j-j%3)/3,"(?)",3);
							TextOut(memdc,115+260*(j%3),171+170*(j-j%3)/3,"(Unused)",8);
							break;
						case 2:
							TextOut(memdc,115+260*(j%3),139+170*(j-j%3)/3,"(Follow Path)",13);
							//TextOut(memdc,115+260*(j%3),155+170*(j-j%3)/3,"(Ignore This)",13);
							TextOut(memdc,115+260*(j%3),171+170*(j-j%3)/3,"(Unused)",8);
							break;
						default:
							TextOut(memdc,115+260*(j%3),139+170*(j-j%3)/3,"(Invalid)",9);
							TextOut(memdc,115+260*(j%3),155+170*(j-j%3)/3,"(Unused)",8);
							TextOut(memdc,115+260*(j%3),171+170*(j-j%3)/3,"(Unused)",8);
							break;
					}

					for(i=0;i<8;i++){
						if(Behaviors[select[mode]][menu][j][0]&(1<<i))SelectObject(bmpdc,checkon);
						else SelectObject(bmpdc,checkoff);
						BitBlt(memdc,165+(i%2)*90+260*(j%3),61+(i-i%2)/2*16+170*(j-j%3)/3,13,13,bmpdc,0,0,SRCCOPY);
						if(i){
							sprintf(out,"%d",i);
							TextOut(memdc,146+(i%2)*90+260*(j%3),61+(i-i%2)/2*16+170*(j-j%3)/3,out,strlen(out));
						}
					}

				}

			}

			GetClientRect(hWnd,&r);

	if(submode[mode]==2){

		SelectObject(bmpdc, battleon);
		BitBlt(memdc, 0, 10, 40, 40, bmpdc, 0, 0, SRCCOPY);
		SelectObject(bmpdc, map);
		BitBlt(memdc, 0, 50, 40, 40, bmpdc, 0, 0, SRCCOPY);

		BMW = 10 + dwidth/48;
		BMH = 10 + dheight/48;

		SelectObject(bmpdc,zoom);
		BitBlt(memdc,20,(BMH-10)*48+500,20,20,bmpdc,0,0,SRCCOPY);

		m = MapHeader[BattleHeaderPos[select[mode]]][1];

		SelectObject(bmpdc,minus);
		BitBlt(memdc,55,8,20,20,bmpdc,0,0,SRCCOPY);

		sprintf(out,"Battle: %d",select[mode]);
		if(focus==1&&cursor)sprintf(out,"%s|",out);
		TextOut(memdc,76,10,out,strlen(out));

		SelectObject(bmpdc,plus);
		BitBlt(memdc,140,8,20,20,bmpdc,0,0,SRCCOPY);

		sprintf(out,"Map: %d",m);
		if(focus==2&&cursor)sprintf(out,"%s|",out);
		TextOut(memdc,176,10,out,strlen(out));

		sprintf(out,"Music: %d",MapHeader[BattleHeaderPos[select[mode]]][0]);
		if(focus==3&&cursor)sprintf(out,"%s|",out);
		TextOut(memdc,233,10,out,strlen(out));

		SelectObject(bmpdc, dots);
		BitBlt(memdc, 305, 8, 20, 20, bmpdc, 0, 0, SRCCOPY);

		sprintf(out,"X: %d",MapHeader[BattleHeaderPos[select[mode]]][3]);
		if(focus==4&&cursor)sprintf(out,"%s|",out);
		TextOut(memdc,333,10,out,strlen(out));

		sprintf(out,"Y: %d",MapHeader[BattleHeaderPos[select[mode]]][5]);
		if(focus==5&&cursor)sprintf(out,"%s|",out);
		TextOut(memdc,378,10,out,strlen(out));

		sprintf(out,"W: %d",BattleSize[select[mode]][0]);
		if(focus==6&&cursor)sprintf(out,"%s|",out);
		TextOut(memdc,428,10,out,strlen(out));

		sprintf(out,"H: %d",BattleSize[select[mode]][1]);
		if(focus==7&&cursor)sprintf(out,"%s|",out);
		TextOut(memdc,478,10,out,strlen(out));

		TextOut(memdc,320,(BMH-10)*48+520,"Display Border",14);
		if(DisplayBorder)SelectObject(bmpdc,checkon);
		else SelectObject(bmpdc,checkoff);
		BitBlt(memdc,300,(BMH-10)*48+522,13,13,bmpdc,0,0,SRCCOPY);

		TextOut(memdc,450,(BMH-10)*48+520,"Display Grid",12);
		if(DisplayGrid)SelectObject(bmpdc,checkon);
		else SelectObject(bmpdc,checkoff);
		BitBlt(memdc,430,(BMH-10)*48+522,13,13,bmpdc,0,0,SRCCOPY);

		TextOut(memdc,dwidth+640,10,"Editing",7);

		TextOut(memdc,dwidth+560,30,"Enemies",7);
		if(BattleMode==0)SelectObject(bmpdc,checkon);
		else SelectObject(bmpdc,checkoff);
		BitBlt(memdc,dwidth+540,32,13,13,bmpdc,0,0,SRCCOPY);

		TextOut(memdc,dwidth+720,30,"Terrain",7);
		if(BattleMode==1)SelectObject(bmpdc,checkon);
		else SelectObject(bmpdc,checkoff);
		BitBlt(memdc,dwidth+700,32,13,13,bmpdc,0,0,SRCCOPY);

		TextOut(memdc,dwidth+560,46,"AI Regions",10);
		if(BattleMode==2)SelectObject(bmpdc,checkon);
		else SelectObject(bmpdc,checkoff);
		BitBlt(memdc,dwidth+540,48,13,13,bmpdc,0,0,SRCCOPY);

		TextOut(memdc,dwidth+720,46,"Force",5);
		if(BattleMode==3)SelectObject(bmpdc,checkon);
		else SelectObject(bmpdc,checkoff);
		BitBlt(memdc,dwidth+700,48,13,13,bmpdc,0,0,SRCCOPY);

		TextOut(memdc, dwidth + 560, 62, "Exits", 5);
		if (BattleMode==4)SelectObject(bmpdc, checkon);
		else SelectObject(bmpdc, checkoff);
		BitBlt(memdc, dwidth + 540, 64, 13, 13, bmpdc, 0, 0, SRCCOPY);

		SetBkMode(memdc,2);
		for(u=0;u<BMW*MapZoom;u++){
			for(v=0;v<BMH*MapZoom;v++){
				if(u+ViewX>=MapSize[MapHeader[BattleHeaderPos[select[mode]]][1]][0]||v+ViewY>=MapSize[MapHeader[BattleHeaderPos[select[mode]]][1]][1])continue;
				for(i=0;i<3;i++){
					for(j=0;j<3;j++){
						l = MapData[m][u+ViewX+(v+ViewY)*MapSize[m][0]];
						if(l<660)l+=MapTileset[m][0];
						else l+=MapTileset[m][1]-660;
						k = (Tiles[l][i*2+j*6]&0x07)*256;
						k += Tiles[l][i*2+j*6+1];
						k -= 0x3BE;

						if(k>255){
							SelectObject(bmpdc,tileset[MapGraphics[m][1]]);
							k-=256;
						} else SelectObject(bmpdc,tileset[MapGraphics[m][0]]);
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
						StretchBlt(memdc,50+(i*16+u*48)/MapZoom,40+(j*16+v*48)/MapZoom,16/MapZoom,16/MapZoom,bmpdc,x,y,8*dx,8*dy,SRCCOPY);
					}
				}
			}
		}
		if(DisplayGrid){
			MoveToEx(memdc,50+u*48/MapZoom,40,0);
			LineTo(memdc,50+u*48/MapZoom,40+v*48/MapZoom);
			LineTo(memdc,50,40+v*48/MapZoom);
		}
		brush = (HBRUSH)SelectObject(memdc,CreateSolidBrush(RGB(255,255,0)));
		if(DisplayBorder){
			for(x=0;x<BattleSize[select[mode]][0];x++){
				for(y=0;y<BattleSize[select[mode]][1];y++){
					i=x-ViewX+MapHeader[BattleHeaderPos[select[mode]]][3]+1;
					j=y-ViewY+MapHeader[BattleHeaderPos[select[mode]]][5]+1;
					if(i>=0&&i<BMW*MapZoom&&j>=0&&j<BMH*MapZoom){
						if(!x||x==BattleSize[select[mode]][0]-1){
							if(y<BattleSize[select[mode]][1]-1)PatBlt(memdc,50+(i*48+20)/MapZoom,40+(j*48+20)/MapZoom,8/MapZoom,28/MapZoom,PATCOPY);
							if(y)PatBlt(memdc,50+(i*48+20)/MapZoom,40+(j*48)/MapZoom,8/MapZoom,20/MapZoom,PATCOPY);
						}
						if(!y||y==BattleSize[select[mode]][1]-1){
							if(x<BattleSize[select[mode]][0]-1)PatBlt(memdc,50+(i*48+20)/MapZoom,40+(j*48+20)/MapZoom,28/MapZoom,8/MapZoom,PATCOPY);
							if(x)PatBlt(memdc,50+i*48/MapZoom,40+(j*48+20)/MapZoom,20/MapZoom,8/MapZoom,PATCOPY);
						}
						if(x==BattleSize[select[mode]][0]-1&&y==BattleSize[select[mode]][1]-1){
							PatBlt(memdc,50+(i*48+20)/MapZoom,40+(j*48+20)/MapZoom,8/MapZoom,8/MapZoom,PATCOPY);
						}
					}
				}
			}
		}
		DeleteObject(SelectObject(memdc,GetStockObject(NULL_BRUSH)));
		pen = (HPEN)SelectObject(memdc,CreatePen(PS_SOLID,2,RGB(255,255,255)));
		for(i=0;i<NumEnemies[select[mode]];i++){

			m = Battle[select[mode]][i][0];
			x = Battle[select[mode]][i][4]-ViewX+MapHeader[BattleHeaderPos[select[mode]]][3];
			y = Battle[select[mode]][i][5]-ViewY+MapHeader[BattleHeaderPos[select[mode]]][5];
			if(x>=0&&x<BMW*MapZoom&&y>=0&&y<BMH*MapZoom){
				if(BattleSelect==i&&BattleMode==0)Rectangle(memdc,50+x*48/MapZoom+1,40+y*48/MapZoom+1,50+(x*48+48)/MapZoom+1,40+(y*48+48)/MapZoom+1);
				for(dx=0;dx<24;dx++){
					for(dy=0;dy<24;dy++){
						switch(MapZoom){
							case 1:
								for(u=0;u<2;u++){
									for(v=0;v<2;v++){
										s = Monster[m][12];
										width = MSSize[s][0][0];
										k = MapSprites[s][0][dx+cursor*24+dy*width];
										if (k) {
											if(MSPalette[s])SetPixel(memdc, 50 + x * 48 + dx * 2 + u, 40 + y * 48 + dy * 2 + v, RGB(EMSPalette[k][0], EMSPalette[k][1], EMSPalette[k][2]));
											else SetPixel(memdc, 50 + x * 48 + dx * 2 + u, 40 + y * 48 + dy * 2 + v, RGB(FMSPalette[k][0], FMSPalette[k][1], FMSPalette[k][2]));
										}
									}
								}
								break;
							case 2:
								s = Monster[m][12];
								width = MSSize[s][0][0];
								k = MapSprites[s][0][dx+cursor*24+dy*width];
								if (k) {
									if (MSPalette[s])SetPixel(memdc, 50 + x * 24 + dx, 40 + y * 24 + dy, RGB(EMSPalette[k][0], EMSPalette[k][1], EMSPalette[k][2]));
									else SetPixel(memdc, 50 + x * 24 + dx, 40 + y * 24 + dy, RGB(FMSPalette[k][0], FMSPalette[k][1], FMSPalette[k][2]));
								}
								break;
							case 4:
								if(dx%2==0&&dy%2==0){
									s = Monster[m][12];
									width = MSSize[s][0][0];
									k = MapSprites[s][0][dx+cursor*24+dy*width];
									if (k) {
										if (MSPalette[s])SetPixel(memdc, 50 + x * 12 + dx / 2, 40 + y * 12 + dy / 2, RGB(EMSPalette[k][0], EMSPalette[k][1], EMSPalette[k][2]));
										else SetPixel(memdc, 50 + x * 12 + dx / 2, 40 + y * 12 + dy / 2, RGB(FMSPalette[k][0], FMSPalette[k][1], FMSPalette[k][2]));
									}
								}
								break;
						}
					}
				}
			}
		}



		for (i = 0; i<NumEnemies[select[mode]]; i++) {

			if (BattleSelect == i&&BattleMode == 0) {
				for (j = 0; j < NumBehaviors[select[mode]][i]; j++) {

					if (j == subselect[mode][2]) {



						for (u = 0; u < BMW*MapZoom; u++) {
							for (v = 0; v < BMH*MapZoom; v++) {
								if (u + ViewX >= MapSize[MapHeader[BattleHeaderPos[select[mode]]][1]][0] || v + ViewY >= MapSize[MapHeader[BattleHeaderPos[select[mode]]][1]][1])continue;

								int ti, tj;

								ti = u + ViewX - MapHeader[BattleHeaderPos[select[mode]]][3] - 1;
								tj = v + ViewY - MapHeader[BattleHeaderPos[select[mode]]][5] - 1;
								if (BattleLand[select[mode]][ti + (tj)*BattleSize[select[mode]][0]] && ti < BattleSize[select[mode]][0] && tj < BattleSize[select[mode]][1] && ti >= 0 && tj >= 0) {

									if (Behaviors[select[mode]][BattleSelect][subselect[mode][2]][0] & (1 << BattleAI[select[mode]][ti + (tj)*BattleSize[select[mode]][0]])) {

										SelectObject(bmpdc, highlight);
										BLENDFUNCTION ftn;
										ftn.BlendOp = AC_SRC_OVER;
										ftn.BlendFlags = 0;
										ftn.SourceConstantAlpha = 128;
										ftn.AlphaFormat = 0;

										AlphaBlend(memdc, 50 + u * 48 / MapZoom, 40 + v * 48 / MapZoom, 48 / MapZoom, 48 / MapZoom, bmpdc, 0, 0, 48 / MapZoom, 48 / MapZoom, ftn);


									}
								}



							}
						}

					}

					if (Behaviors[select[mode]][i][j][1] == 0) {
						x = Behaviors[select[mode]][i][j][2] - ViewX + MapHeader[BattleHeaderPos[select[mode]]][3];
						y = Behaviors[select[mode]][i][j][3] - ViewY + MapHeader[BattleHeaderPos[select[mode]]][5];
						if (x >= 0 && x < BMW*MapZoom&&y >= 0 && y < BMH*MapZoom) {
							HPEN pent = (HPEN)SelectObject(memdc, CreatePen(PS_SOLID, 2, RGB(0, 255, 0)));
							Rectangle(memdc, 50 + x * 48 / MapZoom + 1, 40 + y * 48 / MapZoom + 1, 50 + (x * 48 + 48) / MapZoom + 1, 40 + (y * 48 + 48) / MapZoom + 1);
							DeleteObject(SelectObject(memdc, pent));
							if (MapZoom < 4) {
								sprintf(out, "%d", j);
								TextOut(memdc, 52 + x * 48 / MapZoom + 1, 42 + y * 48 / MapZoom + 1, out, strlen(out));
							}
						}
					}

					if (Behaviors[select[mode]][i][j][1] == 2) {
						for (int l = 0; l < 8; l++) {
							if (AIPaths[select[mode]][i][j][l][0] == 0xFF)break;
							x = AIPaths[select[mode]][i][j][l][0] - ViewX + MapHeader[BattleHeaderPos[select[mode]]][3];
							y = AIPaths[select[mode]][i][j][l][1] - ViewY + MapHeader[BattleHeaderPos[select[mode]]][5];
							if (x >= 0 && x < BMW*MapZoom&&y >= 0 && y < BMH*MapZoom) {
								HPEN pent = (HPEN)SelectObject(memdc, CreatePen(PS_SOLID, 2, RGB(32, 32, 255)));
								Rectangle(memdc, 50 + x * 48 / MapZoom + 1, 40 + y * 48 / MapZoom + 1, 50 + (x * 48 + 48) / MapZoom + 1, 40 + (y * 48 + 48) / MapZoom + 1);

								BitBlt(gdc, 0, 0, maxx, maxy, memdc, 0, 0, SRCCOPY);

								if (l < 7 && AIPaths[select[mode]][i][j][l + 1][0] != 0xFF) {
									DeleteObject(SelectObject(gdc, CreatePen(PS_DOT, 2, RGB(64, 64, 255))));

									MoveToEx(gdc, 50 + x * 48 / MapZoom + 1 + 24 / MapZoom, 40 + y * 48 / MapZoom + 1 + 24 / MapZoom, 0);
									LineTo(gdc, 50 + x * 48 / MapZoom + 1 + 24 / MapZoom + 48 / MapZoom*(AIPaths[select[mode]][i][j][l + 1][0] - AIPaths[select[mode]][i][j][l][0]), 40 + y * 48 / MapZoom + 1 + 24 / MapZoom + 48 / MapZoom*(AIPaths[select[mode]][i][j][l + 1][1] - AIPaths[select[mode]][i][j][l][1]));
								}

								if (l) {
									DeleteObject(SelectObject(gdc, CreatePen(PS_DOT, 2, RGB(64, 64, 255))));

									MoveToEx(gdc, 50 + x * 48 / MapZoom + 1 + 24 / MapZoom, 40 + y * 48 / MapZoom + 1 + 24 / MapZoom, 0);
									LineTo(gdc, 50 + x * 48 / MapZoom + 1 + 24 / MapZoom + 48 / MapZoom*(AIPaths[select[mode]][i][j][l - 1][0] - AIPaths[select[mode]][i][j][l][0]), 40 + y * 48 / MapZoom + 1 + 24 / MapZoom + 48 / MapZoom*(AIPaths[select[mode]][i][j][l - 1][1] - AIPaths[select[mode]][i][j][l][1]));

									if (MapZoom < 4) {
										sprintf(out, "%d", l - 1);
										TextOut(gdc, 46 + x * 48 / MapZoom + 1 + 24 / MapZoom + 48 / MapZoom*(AIPaths[select[mode]][i][j][l - 1][0] - AIPaths[select[mode]][i][j][l][0]), 32 + y * 48 / MapZoom + 1 + 24 / MapZoom + 48 / MapZoom*(AIPaths[select[mode]][i][j][l - 1][1] - AIPaths[select[mode]][i][j][l][1]), out, strlen(out));
									}
								}

								BitBlt(memdc, 50, 50, BMW * 48, BMH * 48, gdc, 50, 50, SRCCOPY);

								DeleteObject(SelectObject(memdc, pent));
								if (MapZoom == 1) {
									sprintf(out, "%d", j);
									TextOut(memdc, 52 + x * 48 / MapZoom + 1, 42 + y * 48 / MapZoom + 1, out, strlen(out));
									sprintf(out, "%d", l);
									TextOut(memdc, 46 + x * 48 / MapZoom + 1 + 24 / MapZoom, 32 + y * 48 / MapZoom + 1 + 24 / MapZoom, out, strlen(out));
								}
							}
						}
					}
				}


				m = Battle[select[mode]][i][0];
				x = Battle[select[mode]][i][4] - ViewX + MapHeader[BattleHeaderPos[select[mode]]][3];
				y = Battle[select[mode]][i][5] - ViewY + MapHeader[BattleHeaderPos[select[mode]]][5];
				if (x >= 0 && x<BMW*MapZoom&&y >= 0 && y<BMH*MapZoom) {
					if (BattleSelect == i&&BattleMode == 0)Rectangle(memdc, 50 + x * 48 / MapZoom + 1, 40 + y * 48 / MapZoom + 1, 50 + (x * 48 + 48) / MapZoom + 1, 40 + (y * 48 + 48) / MapZoom + 1);
					for (dx = 0; dx<24; dx++) {
						for (dy = 0; dy<24; dy++) {
							switch (MapZoom) {
								case 1:
									for (u = 0; u<2; u++) {
										for (v = 0; v<2; v++) {
											s = Monster[m][12];
											width = MSSize[s][0][0];
											k = MapSprites[s][0][dx + cursor * 24 + dy*width];
											if (k) {
												if (MSPalette[s])SetPixel(memdc, 50 + x * 48 + dx * 2 + u, 40 + y * 48 + dy * 2 + v, RGB(EMSPalette[k][0], EMSPalette[k][1], EMSPalette[k][2]));
												else SetPixel(memdc, 50 + x * 48 + dx * 2 + u, 40 + y * 48 + dy * 2 + v, RGB(FMSPalette[k][0], FMSPalette[k][1], FMSPalette[k][2]));
											}
										}
									}
									break;
								case 2:
									s = Monster[m][12];
									width = MSSize[s][0][0];
									k = MapSprites[s][0][dx + cursor * 24 + dy*width];
									if (k) {
										if (MSPalette[s])SetPixel(memdc, 50 + x * 24 + dx, 40 + y * 24 + dy, RGB(EMSPalette[k][0], EMSPalette[k][1], EMSPalette[k][2]));
										else SetPixel(memdc, 50 + x * 24 + dx, 40 + y * 24 + dy, RGB(FMSPalette[k][0], FMSPalette[k][1], FMSPalette[k][2]));
									}
									break;
								case 4:
									if (dx % 2 == 0 && dy % 2 == 0) {
										s = Monster[m][12];
										width = MSSize[s][0][0];
										k = MapSprites[s][0][dx + cursor * 24 + dy*width];
										if (k) {
											if (MSPalette[s])SetPixel(memdc, 50 + x * 12 + dx / 2, 40 + y * 12 + dy / 2, RGB(EMSPalette[k][0], EMSPalette[k][1], EMSPalette[k][2]));
											else SetPixel(memdc, 50 + x * 12 + dx / 2, 40 + y * 12 + dy / 2, RGB(FMSPalette[k][0], FMSPalette[k][1], FMSPalette[k][2]));
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
		for(u=0;u<BMW*MapZoom;u++){
			for(v=0;v<BMH*MapZoom;v++){
				if(u+ViewX>=MapSize[MapHeader[BattleHeaderPos[select[mode]]][1]][0]||v+ViewY>=MapSize[MapHeader[BattleHeaderPos[select[mode]]][1]][1])continue;
				if(DisplayGrid){
					MoveToEx(memdc,50+u*48/MapZoom,40+v*48/MapZoom,0);
					LineTo(memdc,50+(u*48+48)/MapZoom,40+v*48/MapZoom);
					MoveToEx(memdc,50+u*48/MapZoom,40+v*48/MapZoom,0);
					LineTo(memdc,50+u*48/MapZoom,40+(v*48+48)/MapZoom);
				}
				if(BattleMode==1&&MapZoom<4){
					i=u+ViewX-MapHeader[BattleHeaderPos[select[mode]]][3]-1;
					j=v+ViewY-MapHeader[BattleHeaderPos[select[mode]]][5]-1;
					if(i<BattleSize[select[mode]][0]&&j<BattleSize[select[mode]][1]&&i>=0&&j>=0){
						sprintf(out,"%d",BattleLand[select[mode]][i+(j)*BattleSize[select[mode]][0]]);
						TextOut(memdc,50+u*48 / MapZoom,40+v*48 / MapZoom,out,strlen(out));
						/*k=i+(j)*BattleSize[select[mode]][0];
						k = BattleLand[select[mode]][k];
						k = BattleLandIndexes[select[mode]][k];
						k = Terrain[k][0];
						sprintf(out,"%d",LandEffectPercent[k+16]);
						TextOut(memdc,50+u*48,56+v*48,out,strlen(out));*/
					}
				}
				if(BattleMode==2&&MapZoom<4){
					i=u+ViewX-MapHeader[BattleHeaderPos[select[mode]]][3]-1;
					j=v+ViewY-MapHeader[BattleHeaderPos[select[mode]]][5]-1;
					if(BattleLand[select[mode]][i+(j)*BattleSize[select[mode]][0]]&&i<BattleSize[select[mode]][0]&&j<BattleSize[select[mode]][1]&&i>=0&&j>=0){
						sprintf(out,"%d",BattleAI[select[mode]][i+(j)*BattleSize[select[mode]][0]]);
						TextOut(memdc,50+u*48 / MapZoom,40+v*48 / MapZoom,out,strlen(out));
					}
				}
				
				if (BattleMode == 4 && MapZoom<4) {
					if (BattleExitSet == 0) {
						i = u + ViewX - MapHeader[BattleHeaderPos[select[mode]]][3];
						j = v + ViewY - MapHeader[BattleHeaderPos[select[mode]]][5];
					} else {
						i = u + ViewX;
						j = v + ViewY;
					}

					int mw = MapSize[MapHeader[BattleHeaderPos[select[mode]]][1]][0];

					if (Exits[BattExits[select[mode]][BattleExitSet]][i + (j)*mw] != 255) {
						sprintf(out, "%d", Exits[BattExits[select[mode]][BattleExitSet]][i + (j)*mw]);
						TextOut(memdc, 50 + u * 48 / MapZoom, 40 + v * 48 / MapZoom, out, strlen(out));
					}
				}
				//if(BattleMode==3){
					i=u+ViewX-MapHeader[BattleHeaderPos[select[mode]]][3];
					j=v+ViewY-MapHeader[BattleHeaderPos[select[mode]]][5];
					pen = (HPEN)SelectObject(memdc,CreatePen(PS_SOLID,2,RGB(255,255,255)));
					for(k=0;k<NumBattleStart[select[mode]][BattleEntrance];k++){
						if(BattleStart[select[mode]][BattleEntrance][k][0]==i&&BattleStart[select[mode]][BattleEntrance][k][1]==j){
							if(BattleSelect==k&&BattleMode==3)Rectangle(memdc,50+u*48/MapZoom+1,40+v*48/MapZoom+1,50+(u*48+48)/MapZoom+1,40+(v*48+48)/MapZoom+1);
							for(dx=0;dx<24;dx++){
								for(dy=0;dy<24;dy++){
									switch(MapZoom){
										case 1:
											for(x=0;x<2;x++){
												for(y=0;y<2;y++){
													width = MSSize[k][0][0];
													s = MapSprites[k][0][dx+cursor*24+dy*width];
													if (s) {
														if(MSPalette[k])SetPixel(memdc, 50 + u * 48 + dx * 2 + x, 40 + v * 48 + dy * 2 + y, RGB(EMSPalette[s][0], EMSPalette[s][1], EMSPalette[s][2]));
														else SetPixel(memdc, 50 + u * 48 + dx * 2 + x, 40 + v * 48 + dy * 2 + y, RGB(FMSPalette[s][0], FMSPalette[s][1], FMSPalette[s][2]));
													}
												}
											}
											break;
										case 2:
											width = MSSize[k][0][0];
											s = MapSprites[k][0][dx+cursor*24+dy*width];
											if (s) {
												if (MSPalette[k])SetPixel(memdc, 50 + u * 24 + dx, 40 + v * 24 + dy, RGB(EMSPalette[s][0], EMSPalette[s][1], EMSPalette[s][2]));
												else SetPixel(memdc, 50 + u * 24 + dx, 40 + v * 24 + dy, RGB(FMSPalette[s][0], FMSPalette[s][1], FMSPalette[s][2]));
											}
											break;
										case 4:
											if(dx%2==0&&dy%2==0){
												width = MSSize[k][0][0];
												s = MapSprites[k][0][dx+cursor*24+dy*width];
												if (s) {
													if (MSPalette[k])SetPixel(memdc, 50 + u * 12 + dx / 2, 40 + v * 12 + dy / 2, RGB(EMSPalette[s][0], EMSPalette[s][1], EMSPalette[s][2]));
													else SetPixel(memdc, 50 + u * 12 + dx / 2, 40 + v * 12 + dy / 2, RGB(FMSPalette[s][0], FMSPalette[s][1], FMSPalette[s][2]));
												}
											}
											break;
									}
								}
							}
							break;
						}
					}
					DeleteObject(SelectObject(memdc,pen));
				//}
			}
		}
		SelectObject(memdc,brush);
		SetBkMode(memdc,1);

		GetCursorPos(&p);
		ScreenToClient(hWnd,&p);
		p.y-=40;
		if(p.x>=50&&p.x<=(BMW-10)*48+530&&p.y>=40&&p.y<=(BMH-10)*48+520){
			x=(p.x-50)*MapZoom/48;
			y=(p.y-40)*MapZoom/48;
			x+=ViewX;
			y+=ViewY;
			sprintf(out,"%d, %d",x,y);
			if(!menu)TextOut(memdc,50,(BMH-10)*48+520,out,strlen(out));
		}

		int ti;

		switch(BattleMode){
		case 0:
			sprintf(out, "Add Enemy (%d/20)", NumEnemies[select[mode]]);
			if (NumEnemies[select[mode]] == 20)SetTextColor(memdc, RGB(255, 0, 0));
			TextOut(memdc, dwidth + 600, 92, out, strlen(out));
			if (NumEnemies[select[mode]] == 20)SetTextColor(memdc, RGB(0, 0, 0));

			SelectObject(bmpdc, plus);
			BitBlt(memdc, dwidth + 575, 90, 20, 20, bmpdc, 0, 0, SRCCOPY);


			if(BattleSelect>=0){
				sprintf(out, " - #%d", BattleSelect);
				TextOut(memdc, dwidth + 720, 92, out, strlen(out));



				sprintf(out,MonsterName[Battle[select[mode]][BattleSelect][0]]);
				TextOut(memdc,dwidth+590,120,out,strlen(out));

				sprintf(out,"%d",Battle[select[mode]][BattleSelect][0]);
				TextOut(memdc,dwidth+560,120,out,strlen(out));

				SelectObject(bmpdc,deleteicon);
				BitBlt(memdc,dwidth+720,119,20,20,bmpdc,0,0,SRCCOPY);

				BitBlt(memdc, dwidth + 720, 139, 20, 20, bmpdc, 0, 0, SRCCOPY);
				BitBlt(memdc, dwidth + 720, 159, 20, 20, bmpdc, 0, 0, SRCCOPY);
				BitBlt(memdc, dwidth + 720, 179, 20, 20, bmpdc, 0, 0, SRCCOPY);



				SelectObject(bmpdc,dots);
				BitBlt(memdc,dwidth+540,118,20,20,bmpdc,0,0,SRCCOPY);

				if(Battle[select[mode]][BattleSelect][1]!=255){
						if(NumItems==128&&Battle[select[mode]][BattleSelect][1]&0x40){
							sprintf(out,ItemName[Battle[select[mode]][BattleSelect][1]%64+64]);
						} else {
							sprintf(out,ItemName[Battle[select[mode]][BattleSelect][1]%64]);
						}

						if (Battle[select[mode]][BattleSelect][1] >= 128) {
							SetTextColor(memdc, RGB(0, 96, 0));
							sprintf(out, "%s, Eq", out);
						}

				}
				else sprintf(out,"No Item");

				TextOut(memdc,dwidth+590,140,out,strlen(out));
				SetTextColor(memdc, RGB(0, 0, 0));

				sprintf(out,"%d",Battle[select[mode]][BattleSelect][1]);
				TextOut(memdc,dwidth+560,140,out,strlen(out));

				BitBlt(memdc,dwidth+540,138,20,20,bmpdc,0,0,SRCCOPY);

				if(Battle[select[mode]][BattleSelect][2]!=255){
						if(NumItems==128&&Battle[select[mode]][BattleSelect][2]&0x40){
							sprintf(out,ItemName[Battle[select[mode]][BattleSelect][2]%64+64]);
						} else {
							sprintf(out,ItemName[Battle[select[mode]][BattleSelect][2]%64]);
						}

						if (Battle[select[mode]][BattleSelect][2] >= 128) {
							SetTextColor(memdc, RGB(0, 96, 0));
							sprintf(out, "%s, Eq", out);
						}
				}
				else sprintf(out,"No Item");

				TextOut(memdc,dwidth+590,160,out,strlen(out));
				SetTextColor(memdc, RGB(0, 0, 0));

				sprintf(out,"%d",Battle[select[mode]][BattleSelect][2]);
				TextOut(memdc,dwidth+560,160,out,strlen(out));

				BitBlt(memdc,dwidth+540,158,20,20,bmpdc,0,0,SRCCOPY);

				if(Battle[select[mode]][BattleSelect][3]!=255){
					if(Battle[select[mode]][BattleSelect][3]>=64){
						sprintf(out,"%s %d",SpellName[Battle[select[mode]][BattleSelect][3]%64],(Battle[select[mode]][BattleSelect][3]-Battle[select[mode]][BattleSelect][3]%64)/64+1);
					} else {
						sprintf(out,SpellName[Battle[select[mode]][BattleSelect][3]]);
					}
				}
				else sprintf(out,"No Spell");

				TextOut(memdc,dwidth+590,180,out,strlen(out));

				sprintf(out,"%d",Battle[select[mode]][BattleSelect][3]);
				TextOut(memdc,dwidth+560,180,out,strlen(out));

				BitBlt(memdc,dwidth+540,178,20,20,bmpdc,0,0,SRCCOPY);

				if(cursor&&focus==8)sprintf(out,"X: %d|",Battle[select[mode]][BattleSelect][4]);
				else sprintf(out,"X: %d",Battle[select[mode]][BattleSelect][4]);
				TextOut(memdc,dwidth+560,200,out,strlen(out));
				if(cursor&&focus==9)sprintf(out,"Y: %d|",Battle[select[mode]][BattleSelect][5]);
				else sprintf(out,"Y: %d",Battle[select[mode]][BattleSelect][5]);
				TextOut(memdc,dwidth+560,220,out,strlen(out));
				if(cursor&&focus==10)sprintf(out,"# Spawn: %d|",Battle[select[mode]][BattleSelect][7]);
				else sprintf(out,"# Spawn: %d",Battle[select[mode]][BattleSelect][7]);
				TextOut(memdc,dwidth+560,240,out,strlen(out));
				if(cursor&&focus==15)sprintf(out,"Hide Until: %d|",Battle[select[mode]][BattleSelect][6]);
				else sprintf(out,"Hide Until: %d",Battle[select[mode]][BattleSelect][6]);
				TextOut(memdc,dwidth+560,260,out,strlen(out));

				sprintf(out,"AI");
				TextOut(memdc,dwidth+560,280,out,strlen(out));
				BitBlt(memdc,dwidth+540,278,20,20,bmpdc,0,0,SRCCOPY);


				sprintf(out, "# of Behaviors: %d", NumBehaviors[select[mode]][BattleSelect]);
				if (focus == -1 && cursor)sprintf(out, "%s|", out);
				TextOut(memdc, dwidth + 560, 320, out, strlen(out));

				if (NumBehaviors[select[mode]][BattleSelect]) {

					SelectObject(bmpdc, minus);
					BitBlt(memdc, dwidth + 560, 360, 20, 20, bmpdc, 0, 0, SRCCOPY);

					sprintf(out, "Behavior: %d", subselect[mode][2]);
					TextOut(memdc, dwidth + 585, 360, out, strlen(out));

					SelectObject(bmpdc, plus);
					BitBlt(memdc, dwidth + 695, 360, 20, 20, bmpdc, 0, 0, SRCCOPY);

					sprintf(out, "Trigger Regions");
					TextOut(memdc, dwidth + 600, 380, out, strlen(out));

					for (i = 0;i<8;i++) {
						if (Behaviors[select[mode]][BattleSelect][subselect[mode][2]][0] & (1 << i))SelectObject(bmpdc, checkon);
						else SelectObject(bmpdc, checkoff);
						BitBlt(memdc, dwidth + 600 + (i % 2) * 90, 400 + (i - i % 2) / 2 * 16, 13, 13, bmpdc, 0, 0, SRCCOPY);
						if (i) {
							sprintf(out, "%d", i);
							TextOut(memdc, dwidth + 581 + (i % 2) * 90, 400 + (i - i % 2) / 2 * 16, out, strlen(out));
						}
					}


					TextOut(memdc, dwidth+570, 480, "Type:", 5);

					HBRUSH tb = (HBRUSH)SelectObject(memdc, CreateSolidBrush(RGB(180, 180, 180)));
					RoundRect(memdc, dwidth + 620, 478, dwidth + 720, 498, 10, 10);
					DeleteObject(SelectObject(memdc, tb));

					if (Behaviors[select[mode]][BattleSelect][subselect[mode][2]][1] < 3) {
						TextOut(memdc, dwidth + 626, 480, AIActions[Behaviors[select[mode]][BattleSelect][subselect[mode][2]][1]], strlen(AIActions[Behaviors[select[mode]][BattleSelect][subselect[mode][2]][1]]));
					}

					if (Behaviors[select[mode]][BattleSelect][subselect[mode][2]][1] == 0) {
						sprintf(out, "X: %d", Behaviors[select[mode]][BattleSelect][subselect[mode][2]][2]);
						if (focus == -2 && cursor)sprintf(out, "%s|", out);
						TextOut(memdc, dwidth + 570, 500, out, strlen(out));

						sprintf(out, "Y: %d", Behaviors[select[mode]][BattleSelect][subselect[mode][2]][3]);
						if (focus == -3 && cursor)sprintf(out, "%s|", out);
						TextOut(memdc, dwidth + 570, 520, out, strlen(out));
					} else {
						sprintf(out, "Value 1: %d", Behaviors[select[mode]][BattleSelect][subselect[mode][2]][2]);
						if (focus == -2 && cursor)sprintf(out, "%s|", out);
						TextOut(memdc, dwidth + 570, 500, out, strlen(out));

						sprintf(out, "Value 2: %d", Behaviors[select[mode]][BattleSelect][subselect[mode][2]][3]);
						if (focus == -3 && cursor)sprintf(out, "%s|", out);
						TextOut(memdc, dwidth + 570, 520, out, strlen(out));
					}

					if (Behaviors[select[mode]][BattleSelect][subselect[mode][2]][1] == 2) {
						TextOut(memdc, dwidth + 662, 500, "Add Point", 9);

						SelectObject(bmpdc, plus);
						BitBlt(memdc, dwidth + 756, 498, 20, 20, bmpdc, 0, 0, SRCCOPY);

						TextOut(memdc, dwidth + 662, 520, "Remove Point", 12);

						SelectObject(bmpdc, deleteicon);
						BitBlt(memdc, dwidth + 756, 518, 20, 20, bmpdc, 0, 0, SRCCOPY);
					}

				}

			}

		
			break;
		case 1:
			SelectObject(bmpdc,minus);
			BitBlt(memdc,dwidth+540,98,20,20,bmpdc,0,0,SRCCOPY);

			sprintf(out,"Terrain: %d",BattleTerrain);
			if(focus==14&&cursor)sprintf(out,"%s|",out);
			TextOut(memdc,dwidth+561,100,out,strlen(out));

			Rectangle(memdc,dwidth+673,98,dwidth+775,120);

			sprintf(out,"Edit Terrains");
			TextOut(memdc,dwidth+681,100,out,strlen(out));


			SelectObject(bmpdc,plus);
			BitBlt(memdc,dwidth+640,98,20,20,bmpdc,0,0,SRCCOPY);

			ti = Terrain[BattleLandIndexes[select[mode]][BattleTerrain]][0];

			sprintf(out,"Land Effect %%");
			TextOut(memdc,dwidth+561,140,out,strlen(out));

			sprintf(out,"%d, %d, %d, %d, %d, %d, %d, %d",LandEffectPercent[ti],LandEffectPercent[ti+16],LandEffectPercent[ti+16*2],LandEffectPercent[ti+16*3],LandEffectPercent[ti+16*4],LandEffectPercent[ti+16*5],LandEffectPercent[ti+16*6],LandEffectPercent[ti+16*7]);
			TextOut(memdc,dwidth+575,160,out,strlen(out));

			sprintf(out,"Movement Cost");
			TextOut(memdc,dwidth+561,200,out,strlen(out));

			sprintf(out,"%d, %d, %d, %d",LandEffectType[ti],LandEffectType[ti+16],LandEffectType[ti+16*2],LandEffectType[ti+16*3]);
			TextOut(memdc,dwidth+575,220,out,strlen(out));

			sprintf(out,"%d, %d, %d, %d",LandEffectType[ti+16*4],LandEffectType[ti+16*5],LandEffectType[ti+16*6],LandEffectType[ti+16*7]);
			TextOut(memdc,dwidth+575,240,out,strlen(out));

			
			sprintf(out,"Terrain Set");
			TextOut(memdc,dwidth+561,300,out,strlen(out));

			for(i=0;i<8;i++){
				sprintf(out,"%d",BattleLandIndexes[select[mode]][i]);
				if(focus==16+i&&cursor)sprintf(out,"%s|",out);
				TextOut(memdc,dwidth+575,320+20*i,out,strlen(out));

				sprintf(out,"%d",BattleLandIndexes[select[mode]][i+8]);
				if(focus==24+i&&cursor)sprintf(out,"%s|",out);
				TextOut(memdc,dwidth+675,320+20*i,out,strlen(out));
			}
			break;
		case 2:
			SelectObject(bmpdc,minus);
			BitBlt(memdc,dwidth+540,98,20,20,bmpdc,0,0,SRCCOPY);

			sprintf(out,"Region: %d",BattleReg);
			if(focus==13&&cursor)sprintf(out,"%s|",out);
			TextOut(memdc,dwidth+561,100,out,strlen(out));

			SelectObject(bmpdc,plus);
			BitBlt(memdc,dwidth+640,98,20,20,bmpdc,0,0,SRCCOPY);
			break;
		case 3:
			SelectObject(bmpdc,minus);
			BitBlt(memdc,dwidth+540,98,20,20,bmpdc,0,0,SRCCOPY);

			sprintf(out,"Entrance: %d",BattleEntrance);
			if(focus==11&&cursor)sprintf(out,"%s|",out);
			TextOut(memdc,dwidth+561,100,out,strlen(out));

			SelectObject(bmpdc,plus);
			BitBlt(memdc,dwidth+640,98,20,20,bmpdc,0,0,SRCCOPY);

			SelectObject(bmpdc,minus);
			BitBlt(memdc,dwidth+540,118,20,20,bmpdc,0,0,SRCCOPY);

			sprintf(out,"Members: %d",NumBattleStart[select[mode]][BattleEntrance]);
			if(focus==12&&cursor)sprintf(out,"%s|",out);
			TextOut(memdc,dwidth+561,120,out,strlen(out));

			SelectObject(bmpdc,plus);
			BitBlt(memdc,dwidth+650,118,20,20,bmpdc,0,0,SRCCOPY);
			break;
		case 4:
			SelectObject(bmpdc, minus);
			BitBlt(memdc, dwidth + 540, 98, 20, 20, bmpdc, 0, 0, SRCCOPY);

			sprintf(out, "Set: %d", BattleExitSet);
			if (focus == 13 && cursor)sprintf(out, "%s|", out);
			TextOut(memdc, dwidth + 561, 100, out, strlen(out));

			SelectObject(bmpdc, plus);
			BitBlt(memdc, dwidth + 640, 98, 20, 20, bmpdc, 0, 0, SRCCOPY);

			SelectObject(bmpdc, minus);
			BitBlt(memdc, dwidth + 540, 118, 20, 20, bmpdc, 0, 0, SRCCOPY);

			sprintf(out, "Exit: %d", BattleExit);
			if (focus == 14 && cursor)sprintf(out, "%s|", out);
			TextOut(memdc, dwidth + 561, 120, out, strlen(out));

			SelectObject(bmpdc, plus);
			BitBlt(memdc, dwidth + 640, 118, 20, 20, bmpdc, 0, 0, SRCCOPY);

			switch (BattleExit) {
				case -1:
					sprintf(out, "(No Exit)");
					TextOut(memdc, dwidth + 664, 120, out, strlen(out));
					break;
				case 127:
					sprintf(out, "(Teleport)");
					TextOut(memdc, dwidth + 664, 120, out, strlen(out));

					i = BattleTele % MapSize[MapHeader[BattleHeaderPos[select[mode]]][1]][0] + MapHeader[BattleHeaderPos[select[mode]]][3];
					j = (BattleTele - i) / MapSize[MapHeader[BattleHeaderPos[select[mode]]][1]][0] + MapHeader[BattleHeaderPos[select[mode]]][5];

					sprintf(out, "X: %d", i);
					if (focus == -4 && cursor)sprintf(out, "%s|", out);
					TextOut(memdc, dwidth + 584, 140, out, strlen(out));
					sprintf(out, "Y: %d", j);
					if (focus == -5 && cursor)sprintf(out, "%s|", out);
					TextOut(memdc, dwidth + 674, 140, out, strlen(out));

					x = i - ViewX;
					y = j - ViewY;
					if (x >= 0 && x<BMW*MapZoom&&y >= 0 && y<BMH*MapZoom) {
						HPEN pent = (HPEN)SelectObject(memdc, CreatePen(PS_SOLID, 2, RGB(0, 255, 0)));
						HBRUSH brut = (HBRUSH)SelectObject(memdc, GetStockObject(NULL_BRUSH));
						Rectangle(memdc, 50 + x * 48 / MapZoom + 1, 40 + y * 48 / MapZoom + 1, 50 + (x * 48 + 48) / MapZoom + 1, 40 + (y * 48 + 48) / MapZoom + 1);
						DeleteObject(SelectObject(memdc, pent));
						SelectObject(memdc, brut);
					}

					break;
				case 126:
					sprintf(out, "(Tele w/flash)");
					TextOut(memdc, dwidth + 664, 120, out, strlen(out));

					i = BattleTele % MapSize[MapHeader[BattleHeaderPos[select[mode]]][1]][0] + MapHeader[BattleHeaderPos[select[mode]]][3];
					j = (BattleTele - i) / MapSize[MapHeader[BattleHeaderPos[select[mode]]][1]][0] + MapHeader[BattleHeaderPos[select[mode]]][5];

					sprintf(out, "X: %d", i);
					if (focus == -4 && cursor)sprintf(out, "%s|", out);
					TextOut(memdc, dwidth + 584, 140, out, strlen(out));
					sprintf(out, "Y: %d", j);
					if (focus == -5 && cursor)sprintf(out, "%s|", out);
					TextOut(memdc, dwidth + 674, 140, out, strlen(out));

					x = i - ViewX;
					y = j - ViewY;
					if (x >= 0 && x<BMW*MapZoom&&y >= 0 && y<BMH*MapZoom) {
						HPEN pent = (HPEN)SelectObject(memdc, CreatePen(PS_SOLID, 2, RGB(0, 255, 0)));
						HBRUSH brut = (HBRUSH)SelectObject(memdc, GetStockObject(NULL_BRUSH));
						Rectangle(memdc, 50 + x * 48 / MapZoom + 1, 40 + y * 48 / MapZoom + 1, 50 + (x * 48 + 48) / MapZoom + 1, 40 + (y * 48 + 48) / MapZoom + 1);
						DeleteObject(SelectObject(memdc, pent));
						SelectObject(memdc, brut);
					}
					break;
				case 125:
					sprintf(out, "(End Chapter)");
					TextOut(memdc, dwidth + 664, 120, out, strlen(out));
					break;
			}


			if (BattleExit != 255 && BattleExit !=-1) {
				Rectangle(memdc, dwidth + 561, 162, dwidth + 660, 182);
				TextOut(memdc, dwidth + 576, 164, "View Script", 11);
			}
			break;
		}
		if(menu==1||menu==2){
			r.top=118;
			r.left=dwidth+279;
			r.right=dwidth+749;
			r.bottom=396;
			FillRect(memdc,&r,(HBRUSH)GetStockObject(WHITE_BRUSH));
			TextOut(memdc,dwidth+284,121,"Equipped:",9);
			if(Battle[select[mode]][BattleSelect][menu]&0x80)SelectObject(bmpdc,checkon);
			else SelectObject(bmpdc,checkoff);
			BitBlt(memdc,dwidth+354,121,13,13,bmpdc,0,0,SRCCOPY);
			if(Battle[select[mode]][BattleSelect][menu]%64<63)Rectangle(memdc,dwidth+284+115*(Battle[select[mode]][BattleSelect][menu]%64-Battle[select[mode]][BattleSelect][menu]%16)/16,137+Battle[select[mode]][BattleSelect][menu]%16*16,dwidth+284+115*(Battle[select[mode]][BattleSelect][menu]%64-Battle[select[mode]][BattleSelect][menu]%16)/16+115,137+Battle[select[mode]][BattleSelect][menu]%16*16+16);
			for(j=0;j<4;j++){
				for(i=0;i<16;i++){
					if(j==3&&i==15)sprintf(out,"(None)");
					else {
						if(NumItems==128&&Battle[select[mode]][BattleSelect][menu]&0x40){
							sprintf(out,"%s",ItemName[j*16+i+64]);
						} else {
							sprintf(out,"%s",ItemName[j*16+i]);
						}
					}
					TextOut(memdc,dwidth+284+115*j,137+16*i,out,strlen(out));
				}
			}

			if(NumItems==128){
				TextOut(memdc,dwidth+284+93,121,"Extended:",9);
				if(Battle[select[mode]][BattleSelect][menu]&0x40){
					SelectObject(bmpdc,checkon);
				} else {
					SelectObject(bmpdc,checkoff);
				}
				BitBlt(memdc,dwidth+284+163,121,13,13,bmpdc,0,0,SRCCOPY);
			}
		}
		if(menu==3){
			if(!ExpandSpells){
				r.top=158;
				r.left=dwidth+399;
				r.right=dwidth+709;
				r.bottom=420+16;
				FillRect(memdc,&r,(HBRUSH)GetStockObject(WHITE_BRUSH));
				if(Battle[select[mode]][BattleSelect][3]%64<16)Rectangle(memdc,dwidth+404+75*(Battle[select[mode]][BattleSelect][3]-Battle[select[mode]][BattleSelect][3]%64)/64,161+Battle[select[mode]][BattleSelect][3]%64*16,dwidth+404+75*(Battle[select[mode]][BattleSelect][3]-Battle[select[mode]][BattleSelect][3]%64)/64+75,161+Battle[select[mode]][BattleSelect][3]%64*16+16);
				for(i=0;i<16;i++){
					sprintf(out,"%s",SpellName[i]);
					TextOut(memdc,dwidth+404,161+16*i,out,strlen(out));
					for(j=1;j<4;j++){
						sprintf(out,"%s %d",SpellName[i],j+1);
						TextOut(memdc,dwidth+404+75*j,161+16*i,out,strlen(out));
					}
				}
				sprintf(out,"None");
				TextOut(memdc,dwidth+404,161+16*i,out,strlen(out));
			} else {
				r.top=25-16;
				r.left=dwidth+399;
				r.right=dwidth+709;
				r.bottom=25+3+16*32;
				FillRect(memdc,&r,(HBRUSH)GetStockObject(WHITE_BRUSH));
				if(Battle[select[mode]][BattleSelect][3]%64<16)Rectangle(memdc,dwidth+404+75*(Battle[select[mode]][BattleSelect][3]-Battle[select[mode]][BattleSelect][3]%64)/64,28+Battle[select[mode]][BattleSelect][3]%64*16-16,dwidth+404+75*(Battle[select[mode]][BattleSelect][3]-Battle[select[mode]][BattleSelect][3]%64)/64+75,28+Battle[select[mode]][BattleSelect][3]%64*16);
				for(i=0;i<32;i++){
					sprintf(out,"%s",SpellName[i]);
					TextOut(memdc,dwidth+404,28+16*i-16,out,strlen(out));
					for(j=1;j<4;j++){
						sprintf(out,"%s %d",SpellName[i],j+1);
						TextOut(memdc,dwidth+404+75*j,28+16*i-16,out,strlen(out));
					}
				}
				sprintf(out,"None");
				TextOut(memdc,dwidth+404,28+16*i-16,out,strlen(out));
			}
		}
		if(menu==4){
			r.top=40;
			r.left=dwidth+179;
			r.right=dwidth+759;
			r.bottom=302+262*(NumMonsters==146);
			FillRect(memdc,&r,(HBRUSH)GetStockObject(WHITE_BRUSH));
			int q = 16 + 16*(NumMonsters==146);
			for(j=0;j<5;j++){
				for(i=0;i<q;i++){
					if(j*q+i<NumMonsters){
						if(Battle[select[mode]][BattleSelect][0]==j*q+i)
							Rectangle(memdc,dwidth+184+115*j,43+16*i,dwidth+184+115*(j+1),43+16*(i+1));
						sprintf(out,"%s",MonsterName[j*q+i]);
						TextOut(memdc,dwidth+184+115*j,43+16*i,out,strlen(out));
					}
				}
			}
		}

		if (menu == 5) {

			HBRUSH tb = (HBRUSH)SelectObject(memdc, CreateSolidBrush(RGB(180, 180, 180)));
			RoundRect(memdc, dwidth + 620, 478, dwidth + 720, 478 + 3 * 20, 10, 10);
			DeleteObject(SelectObject(memdc, tb));


			for (int i = 0; i < 3; i++) {
				if (Behaviors[select[mode]][BattleSelect][subselect[mode][2]][1] == i) {
					RoundRect(memdc, dwidth + 620, 478 + i * 20, dwidth + 720, 498 + i * 20, 10, 10);
				}
				TextOut(memdc, dwidth + 626, 480 + 20 * i, AIActions[i], strlen(AIActions[i]));
			}

		}
		
		if (menu == 6) {//music
			drawSoundList(memdc, 50, 28, MapHeader[BattleHeaderPos[select[mode]]][0]);
		}
	}

	if(submode[mode]==3){

		if(subselect[mode][0]!=-1){
			Rectangle(memdc,673,520,775,540);

			sprintf(out,"Return");
			TextOut(memdc,702,522,out,strlen(out));
		}

		Rectangle(memdc,50,10+16*select[mode],150,27+16*select[mode]);

		j=(125-(125)%30)/30;
		if((125)%30>0)j++;
		for(i=0;i<j;i++){
			if(i+1<j)sprintf(out,"Terrain %d-%d",i*30,(i+1)*30-1);
			else sprintf(out,"Terrain %d-%d",i*30,125-1);
			TextOut(memdc,50,10+16*i,out,strlen(out));
		}

		for(i=0;i<16;i++){
			sprintf(out,"Type %d",i);
			TextOut(memdc,50,10+16*(7+i),out,strlen(out));
		}

		if(select[mode]<7){

			for(i=0;i<30&&i+30*select[mode]<125;i++){

				if(subselect[mode][0]!=-1){
					SetTextColor(memdc,RGB(0,0,0));
					for(int z=0;z<16;z++){
						if(BattleLandIndexes[subselect[mode][0]][z]==i+30*select[mode])SetTextColor(memdc,RGB(200,0,0));
					}
				}

				sprintf(out,"%d",i+30*select[mode]);
				TextOut(memdc,180,26+16*i,out,strlen(out));
				for(j=0;j<4;j++){
					sprintf(out,"%d",Terrain[i+30*select[mode]][j]);
					if(focus==j+1&&subfocus==i&&cursor)sprintf(out,"%s|",out);
					TextOut(memdc,240+95*j,26+16*i,out,strlen(out));
				}
			}

			SetTextColor(memdc,RGB(0,0,0));

			TextOut(memdc,180,10,"#",1);
			TextOut(memdc,240,10,"Type",4);
			TextOut(memdc,335,10,"?",1);
			TextOut(memdc,430,10,"Background",10);
			TextOut(memdc,525,10,"Platform",8);

		} else {
				sprintf(out,"Movement Type");
				TextOut(memdc,460,26,out,strlen(out));

				sprintf(out,"Land Effect %%");
				TextOut(memdc,180,58,out,strlen(out));

				for(j=0;j<8;j++){
					sprintf(out,"%d",LandEffectPercent[j*16+(select[mode]-7)]);
					if(focus==j+1&&cursor)sprintf(out,"%s|",out);
					TextOut(memdc,304+55*j,58,out,strlen(out));
				}

				sprintf(out,"Movement Cost");
				TextOut(memdc,180,90,out,strlen(out));

				for(j=0;j<8;j++){
					sprintf(out,"%d",LandEffectType[j*16+(select[mode]-7)]);
					if(focus==j+9&&cursor)sprintf(out,"%s|",out);
					TextOut(memdc,304+55*j,90,out,strlen(out));
				}
		}

		if(subselect[mode][0]!=-1){
			sprintf(out,"(Red entries are in use by current battle)");
			TextOut(memdc,244,515,out,strlen(out));
		}
	}

	if(submode[mode]==4){
		TextOut(memdc,50,30,"#",1);
		TextOut(memdc,80,30,"X",1);
		TextOut(memdc,110,30,"Y",1);

		SelectObject(bmpdc,plus);
		BitBlt(memdc,18,30,20,20,bmpdc,0,0,SRCCOPY);

		i = select[mode];
		j = menu;
		k = subselect[mode][1];

		for(int l=0;l<8;l++){
			if(AIPaths[i][j][k][l][0]==0xFF)break;
			SelectObject(bmpdc,deleteicon);
			BitBlt(memdc,18,50+20*l,20,20,bmpdc,0,0,SRCCOPY);

			sprintf(out,"%d",l);
			TextOut(memdc,50,50+20*l,out,strlen(out));
			sprintf(out,"%d",AIPaths[i][j][k][l][0]);
			if(cursor&&focus==2*l+1)sprintf(out,"%s|",out);
			TextOut(memdc,80,50+20*l,out,strlen(out));
			sprintf(out,"%d",AIPaths[i][j][k][l][1]);
			if(cursor&&focus==2*l+2)sprintf(out,"%s|",out);
			TextOut(memdc,110,50+20*l,out,strlen(out));
		}

		Rectangle(memdc,620,524,790,544);
		TextOut(memdc,690,526,"Back",4);
	}