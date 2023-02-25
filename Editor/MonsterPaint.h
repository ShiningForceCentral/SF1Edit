			Rectangle(memdc,50+150*((select[mode]%73/37)),5+14*(select[mode]%73%37),50+150*((select[mode]%73/37))+120,5+14*(select[mode]%73%37)+16);

			for(i=0;i<37;i++){
				if(i==select[mode]%73&&focus==1&&cursor){
					sprintf(out,"%s|",MonsterName[i+MonsterView]);
					TextOut(memdc,50,i*14+5,out,strlen(out));
				} else {
					TextOut(memdc,50,i*14+5,MonsterName[i+MonsterView],strlen(MonsterName[i+MonsterView]));
				}
				sprintf(out,"%d",i+MonsterView);
				TextOut(memdc,20,i*14+5,out,strlen(out));
			}
			for(i=37;i<73;i++){
				if(i==select[mode]%73&&focus==1&&cursor){
					sprintf(out,"%s|",MonsterName[i+MonsterView]);
					TextOut(memdc,200,(i-37)*14+5,out,strlen(out));
				} else {
					TextOut(memdc,200,(i-37)*14+5,MonsterName[i+MonsterView],strlen(MonsterName[i+MonsterView]));
				}
				sprintf(out,"%d",i+MonsterView);
				TextOut(memdc,170,(i-37)*14+5,out,strlen(out));
			}

			TextOut(memdc,475,25,"Coins:",6);

			if(focus==2&&cursor){
				sprintf(out,"%d|",Monster[select[mode]][0]*256+Monster[select[mode]][1]);
				TextOut(memdc,612,25,out,strlen(out));
			} else {
				sprintf(out,"%d",Monster[select[mode]][0]*256+Monster[select[mode]][1]);
				TextOut(memdc,612,25,out,strlen(out));
			}

			TextOut(memdc,475,45,"Class:",6);

			if(focus==3&&cursor){
				sprintf(out,"%d|",Monster[select[mode]][2]);
				TextOut(memdc,612,45,out,strlen(out));
			} else {
				sprintf(out,"%d",Monster[select[mode]][2]);
				TextOut(memdc,612,45,out,strlen(out));
			}

			TextOut(memdc,475,65,"Effective Level:",16);

			if(focus==4&&cursor){
				sprintf(out,"%d|",Monster[select[mode]][3]);
				TextOut(memdc,612,65,out,strlen(out));
			} else {
				sprintf(out,"%d",Monster[select[mode]][3]);
				TextOut(memdc,612,65,out,strlen(out));
			}

			TextOut(memdc,475,85,"Attack:",7);

			if(focus==5&&cursor){
				sprintf(out,"%d|",Monster[select[mode]][4]);
				TextOut(memdc,612,85,out,strlen(out));
			} else {
				sprintf(out,"%d",Monster[select[mode]][4]);
				TextOut(memdc,612,85,out,strlen(out));
			}

			TextOut(memdc,475,105,"Defense:",8);

			if(focus==6&&cursor){
				sprintf(out,"%d|",Monster[select[mode]][5]);
				TextOut(memdc,612,105,out,strlen(out));
			} else {
				sprintf(out,"%d",Monster[select[mode]][5]);
				TextOut(memdc,612,105,out,strlen(out));
			}

			TextOut(memdc,475,125,"Agility:",8);

			if(focus==7&&cursor){
				sprintf(out,"%d|",Monster[select[mode]][6]);
				TextOut(memdc,612,125,out,strlen(out));
			} else {
				sprintf(out,"%d",Monster[select[mode]][6]);
				TextOut(memdc,612,125,out,strlen(out));
			}

			TextOut(memdc,475,145,"Move:",5);

			if(focus==8&&cursor){
				sprintf(out,"%d|",Monster[select[mode]][7]);
				TextOut(memdc,612,145,out,strlen(out));
			} else {
				sprintf(out,"%d",Monster[select[mode]][7]);
				TextOut(memdc,612,145,out,strlen(out));
			}

			TextOut(memdc,475,165,"HP:",3);

			if(focus==9&&cursor){
				sprintf(out,"%d|",Monster[select[mode]][8]*256+Monster[select[mode]][9]);
				TextOut(memdc,612,165,out,strlen(out));
			} else {
				sprintf(out,"%d",Monster[select[mode]][8]*256+Monster[select[mode]][9]);
				TextOut(memdc,612,165,out,strlen(out));
			}


			TextOut(memdc,475,185,"MP:",3);

			if(focus==10&&cursor){
				sprintf(out,"%d|",Monster[select[mode]][10]);
				TextOut(memdc,612,185,out,strlen(out));
			} else {
				sprintf(out,"%d",Monster[select[mode]][10]);
				TextOut(memdc,612,185,out,strlen(out));
			}

			TextOut(memdc,475,205,"Status:",7);

			if(focus==11&&cursor){
				sprintf(out,"%d|",Monster[select[mode]][11]);
				TextOut(memdc,612,205,out,strlen(out));
			} else {
				sprintf(out,"%d",Monster[select[mode]][11]);
				TextOut(memdc,612,205,out,strlen(out));
			}

			TextOut(memdc,475,225,"Map Sprite:",11);

			if(focus==12&&cursor){
				sprintf(out,"%d|",Monster[select[mode]][12]);
				TextOut(memdc,612,225,out,strlen(out));
			} else {
				sprintf(out,"%d",Monster[select[mode]][12]);
				TextOut(memdc,612,225,out,strlen(out));
			}

			if (GraphicsLoaded) {
				width = MSSize[0][0][0];
				height = MSSize[0][0][1];

				for (x = 0; x < width / 2; x++) {
					for (y = 0; y < height; y++) {
						k = MapSprites[Monster[select[mode]][12]][0][x + 24 * cursor + y*width];
						if (k < 0)k = 0;
						if (k) {

							if(MSPalette[Monster[select[mode]][12]])
								SetPixel(memdc, x + 680, y + 221, RGB(EMSPalette[k][0], EMSPalette[k][1], EMSPalette[k][2]));
							else
								SetPixel(memdc, x + 680, y + 221, RGB(FMSPalette[k][0], FMSPalette[k][1], FMSPalette[k][2]));
						}
					}
				}

				if (Monster[select[mode]][15] != 255) {
					width = POSize[Monster[select[mode]][15]][0];
					height = POSize[Monster[select[mode]][15]][1];

					for (int px = 0; px < width * 3 / 4; px++) {
						for (int py = 0; py < height; py++) {

							int k = Portraits[Monster[select[mode]][15]][px + py*width];
							if (k < 0)k = 0;

							SetPixel(memdc, 680 + px, 285 + py, RGB(POPalette[Monster[select[mode]][15]][k][0], POPalette[Monster[select[mode]][15]][k][1], POPalette[Monster[select[mode]][15]][k][2]));

						}
					}
				}

			}

			SelectObject(bmpdc, zoom);
			BitBlt(memdc, 640, 225, 20, 20, bmpdc, 0, 0, SRCCOPY);
			SelectObject(bmpdc, zoom);
			BitBlt(memdc, 640, 245, 20, 20, bmpdc, 0, 0, SRCCOPY);
			SelectObject(bmpdc, zoom);
			BitBlt(memdc, 640, 265, 20, 20, bmpdc, 0, 0, SRCCOPY);

			TextOut(memdc,475,245,"Battle Sprite:",14);

			if(focus==13&&cursor){
				sprintf(out,"%d|",Monster[select[mode]][13]);
				TextOut(memdc,612,245,out,strlen(out));
			} else {
				sprintf(out,"%d",Monster[select[mode]][13]);
				TextOut(memdc,612,245,out,strlen(out));
			}

			TextOut(memdc,475,265,"Battle Palette:",15);

			if(focus==14&&cursor){
				sprintf(out,"%d|",Monster[select[mode]][14]);
				TextOut(memdc,612,265,out,strlen(out));
			} else {
				sprintf(out,"%d",Monster[select[mode]][14]);
				TextOut(memdc,612,265,out,strlen(out));
			}

			TextOut(memdc,475,285,"Portrait:",9);

			if(focus==15&&cursor){
				sprintf(out,"%d|",Monster[select[mode]][15]);
				TextOut(memdc,612,285,out,strlen(out));
			} else {
				sprintf(out,"%d",Monster[select[mode]][15]);
				TextOut(memdc,612,285,out,strlen(out));
			}

			if(AddCritical){
				TextOut(memdc,475,305,"Critical:",9);

				if(focus==16&&cursor){
					sprintf(out,"%d| %%",Monster[select[mode]][16]);
					TextOut(memdc,612,305,out,strlen(out));
				} else {
					sprintf(out,"%d %%",Monster[select[mode]][16]);
					TextOut(memdc,612,305,out,strlen(out));
				}
			}

			TextOut(memdc,475,500,"Add Critical Stat",17);
			if(AddCritical)SelectObject(bmpdc,checkon);
			else SelectObject(bmpdc,checkoff);
			BitBlt(memdc,452,501,13,13,bmpdc,0,0,SRCCOPY);

			if(NumMonsters==146){
				SelectObject(bmpdc,uparrow);
				BitBlt(memdc,200,520,20,20,bmpdc,0,0,SRCCOPY);
				SelectObject(bmpdc,downarrow);
				BitBlt(memdc,223,520,20,20,bmpdc,0,0,SRCCOPY);
				SelectObject(bmpdc,checkon);
			} else SelectObject(bmpdc,checkoff);


			TextOut(memdc,475,516,"Extend Monsters",15);	
			BitBlt(memdc,452,517,13,13,bmpdc,0,0,SRCCOPY);

			switch(menu){
				case 1://class
					r.top=41;
					r.left=456;
					r.right=570;
					r.bottom=530;
					FillRect(memdc,&r,(HBRUSH)GetStockObject(WHITE_BRUSH));
					for(i=0;i<32;i++){
						sprintf(out,"%s",Classes[i]);
						TextOut(memdc,458,43+15*i,out,strlen(out));
					}
					break;
			}