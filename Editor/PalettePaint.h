	TextOut(memdc,10,20,"Common",6);
	TextOut(memdc,10,40,"Force Map Sprites",17);
	TextOut(memdc,10,60,"Enemy Map Sprites",17);
	TextOut(memdc,10,80,"Enemy Sprite:",13);
	TextOut(memdc,30,100,"Palette 0:",9);
	if(NumESPalette[select[mode]]>1)TextOut(memdc,30,120,"Palette 1:",9);
	if(NumESPalette[select[mode]]>2)TextOut(memdc,30,140,"Palette 2:",9);
	if(NumESPalette[select[mode]]>3)TextOut(memdc,30,160,"Palette 3:",9);
	TextOut(memdc,10,320,"Item Sprite:",12);

	if (submode[mode] > 64) {
		Rectangle(memdc, 238, 333, 442, 363);
		TextOut(memdc, 258, 340, "Copy from Non-extended", 23);
	}

	TextOut(memdc,10,360,"Tileset:",8);
	TextOut(memdc,10,400,"Background:", 11);
	
	TextOut(memdc,10,180,"Force Sprite:",13);
	TextOut(memdc,30,200,"Palette 0:",9);
	if(NumFSPalette[subselect[mode][1]]>1)TextOut(memdc,30,220,"Palette 1:",9);
	if(NumFSPalette[subselect[mode][1]]>2)TextOut(memdc,30,240,"Palette 2:",9);
	if(NumFSPalette[subselect[mode][1]]>3)TextOut(memdc,30,260,"Palette 3:",9);
	if(NumFSPalette[subselect[mode][1]]>4)TextOut(memdc,30,280,"Palette 4:",9);
	if(NumFSPalette[subselect[mode][1]]>5)TextOut(memdc,30,300,"Palette 5:",9);

	SelectObject(bmpdc,minus);
	BitBlt(memdc,105,78,20,20,bmpdc,0,0,SRCCOPY);

	sprintf(out,"%d",select[mode]);
	if(focus==1&&cursor)sprintf(out,"%s|",out);
	TextOut(memdc,126,80,out,strlen(out));

	SelectObject(bmpdc,plus);
	BitBlt(memdc,166,78,20,20,bmpdc,0,0,SRCCOPY);

	SelectObject(bmpdc,minus);
	BitBlt(memdc,105,318,20,20,bmpdc,0,0,SRCCOPY);

	sprintf(out,"%d",submode[mode]);
	if(focus==2&&cursor)sprintf(out,"%s|",out);
	TextOut(memdc,126,320,out,strlen(out));

	SelectObject(bmpdc,plus);
	BitBlt(memdc,166,318,20,20,bmpdc,0,0,SRCCOPY);

	SelectObject(bmpdc,minus);
	BitBlt(memdc,105,358,20,20,bmpdc,0,0,SRCCOPY);

	sprintf(out,"%d",subselect[mode][0]);
	if(focus==3&&cursor)sprintf(out,"%s|",out);
	TextOut(memdc,126,360,out,strlen(out));

	SelectObject(bmpdc,plus);
	BitBlt(memdc,166,358,20,20,bmpdc,0,0,SRCCOPY);

	SelectObject(bmpdc, minus);
	BitBlt(memdc, 105, 398, 20, 20, bmpdc, 0, 0, SRCCOPY);

	sprintf(out, "%d", subselect[mode][2]);
	if (focus == 5 && cursor)sprintf(out, "%s|", out);
	TextOut(memdc, 126, 400, out, strlen(out));

	SelectObject(bmpdc, plus);
	BitBlt(memdc, 166, 398, 20, 20, bmpdc, 0, 0, SRCCOPY);

	SelectObject(bmpdc,minus);
	BitBlt(memdc,105,178,20,20,bmpdc,0,0,SRCCOPY);

	sprintf(out,"%d",subselect[mode][1]);
	if(focus==4&&cursor)sprintf(out,"%s|",out);
	TextOut(memdc,126,180,out,strlen(out));

	SelectObject(bmpdc,plus);
	BitBlt(memdc,166,178,20,20,bmpdc,0,0,SRCCOPY);

	for(i=0;i<16;i++){
		for(dx=0;dx<18;dx++){
			for(int dy=0;dy<18;dy++){
				SetPixel(memdc,160+18*i+dx,20+dy,RGB(IconPalette[i][0],IconPalette[i][1],IconPalette[i][2]));
			}
		}
		for(dx=0;dx<18;dx++){
			for(int dy=0;dy<18;dy++){
				SetPixel(memdc,160+18*i+dx,40+dy,RGB(FMSPalette[i][0],FMSPalette[i][1],FMSPalette[i][2]));
			}
		}
		for(dx=0;dx<18;dx++){
			for(int dy=0;dy<18;dy++){
				SetPixel(memdc,160+18*i+dx,60+dy,RGB(EMSPalette[i][0],EMSPalette[i][1],EMSPalette[i][2]));
			}
		}
		for(dx=0;dx<18;dx++){
			for(int dy=0;dy<18;dy++){
				SetPixel(memdc,160+18*i+dx,100+dy,RGB(ESPalette[select[mode]][0][i][0],ESPalette[select[mode]][0][i][1],ESPalette[select[mode]][0][i][2]));
				if(NumESPalette[select[mode]]>1)SetPixel(memdc,160+18*i+dx,120+dy,RGB(ESPalette[select[mode]][1][i][0],ESPalette[select[mode]][1][i][1],ESPalette[select[mode]][1][i][2]));
				if(NumESPalette[select[mode]]>2)SetPixel(memdc,160+18*i+dx,140+dy,RGB(ESPalette[select[mode]][2][i][0],ESPalette[select[mode]][2][i][1],ESPalette[select[mode]][2][i][2]));
				if(NumESPalette[select[mode]]>3)SetPixel(memdc,160+18*i+dx,160+dy,RGB(ESPalette[select[mode]][3][i][0],ESPalette[select[mode]][3][i][1],ESPalette[select[mode]][3][i][2]));
			}
		}

		int off=20;

		for(dx=0;dx<18;dx++){
			for(int dy=0+off;dy<18+off;dy++){
				SetPixel(memdc,160+18*i+dx,180+dy,RGB(FSPalette[subselect[mode][1]][0][i][0],FSPalette[subselect[mode][1]][0][i][1],FSPalette[subselect[mode][1]][0][i][2]));
				if(NumFSPalette[subselect[mode][1]]>1)SetPixel(memdc,160+18*i+dx,200+dy,RGB(FSPalette[subselect[mode][1]][1][i][0],FSPalette[subselect[mode][1]][1][i][1],FSPalette[subselect[mode][1]][1][i][2]));
				if(NumFSPalette[subselect[mode][1]]>2)SetPixel(memdc,160+18*i+dx,220+dy,RGB(FSPalette[subselect[mode][1]][2][i][0],FSPalette[subselect[mode][1]][2][i][1],FSPalette[subselect[mode][1]][2][i][2]));
				if(NumFSPalette[subselect[mode][1]]>3)SetPixel(memdc,160+18*i+dx,240+dy,RGB(FSPalette[subselect[mode][1]][3][i][0],FSPalette[subselect[mode][1]][3][i][1],FSPalette[subselect[mode][1]][3][i][2]));
				if(NumFSPalette[subselect[mode][1]]>4)SetPixel(memdc,160+18*i+dx,260+dy,RGB(FSPalette[subselect[mode][1]][4][i][0],FSPalette[subselect[mode][1]][4][i][1],FSPalette[subselect[mode][1]][4][i][2]));
				if(NumFSPalette[subselect[mode][1]]>5)SetPixel(memdc,160+18*i+dx,280+dy,RGB(FSPalette[subselect[mode][1]][5][i][0],FSPalette[subselect[mode][1]][5][i][1],FSPalette[subselect[mode][1]][5][i][2]));
			}
		}


		for (dx = 0; dx<18; dx++) {
			for (int dy = 0; dy<18; dy++) {
				m = subselect[mode][2];
				SetPixel(memdc, 160 + 18 * i + dx, 420 + dy, RGB(BGPalette[m-m%2][0][i][0], BGPalette[m - m % 2][0][i][1], BGPalette[m - m % 2][0][i][2]));
			}
		}
		

		if(i<15)
		for(dx=0;dx<18;dx++){
			for(int dy=0;dy<18;dy++){
				SetPixel(memdc,160+18*i+dx,380+dy,RGB(TSPalette[subselect[mode][0]][i+1][0],TSPalette[subselect[mode][0]][i+1][1],TSPalette[subselect[mode][0]][i+1][2]));
			}
		}


	}
	for(i=0;i<4;i++){
		for(int dx=0;dx<18;dx++){
			for(int dy=0;dy<18;dy++){
				SetPixel(memdc,160+18*i+dx,340+dy,RGB(ISPalette[submode[mode]][i][0],ISPalette[submode[mode]][i][1],ISPalette[submode[mode]][i][2]));
			}
		}
	}