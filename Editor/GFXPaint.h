if(!GraphicsLoaded){
	if(strlen(file)){
		Rectangle(memdc,50,30,176,52);
		TextOut(memdc,55,33,"Decompress GFX",14);
	} else {
		TextOut(memdc,55,33,"Load a ROM first.",17);
	}
} else {

	if(submode[mode]==0)SelectObject(bmpdc,charaon);
	else SelectObject(bmpdc,chara);
	BitBlt(memdc,0,35,40,40,bmpdc,0,0,SRCCOPY);
	if(submode[mode]==1)SelectObject(bmpdc,monsteron);
	else SelectObject(bmpdc,monster);
	BitBlt(memdc,0,75,40,40,bmpdc,0,0,SRCCOPY);
	if(submode[mode]==2)SelectObject(bmpdc,itemon);
	else SelectObject(bmpdc,item);
	BitBlt(memdc,0,115,40,40,bmpdc,0,0,SRCCOPY);
	if(submode[mode]==3)SelectObject(bmpdc,bgon);
	else SelectObject(bmpdc,bg);
	BitBlt(memdc,0,155,40,40,bmpdc,0,0,SRCCOPY);
	if(submode[mode]==4)SelectObject(bmpdc,platon);
	else SelectObject(bmpdc,plat);
	BitBlt(memdc,0,195,40,40,bmpdc,0,0,SRCCOPY);
	if (submode[mode] == 5)SelectObject(bmpdc, animon);
	else SelectObject(bmpdc, anim);
	BitBlt(memdc, 0, 235, 40, 40, bmpdc, 0, 0, SRCCOPY);
	if(submode[mode]==6)SelectObject(bmpdc,porton);
	else SelectObject(bmpdc,port);
	BitBlt(memdc,0,275,40,40,bmpdc,0,0,SRCCOPY);
	if(submode[mode]==7)SelectObject(bmpdc,spriteon);
	else SelectObject(bmpdc,sprite);
	BitBlt(memdc,0,315,40,40,bmpdc,0,0,SRCCOPY);
	if(submode[mode]==8)SelectObject(bmpdc,tileon);
	else SelectObject(bmpdc,tile);
	BitBlt(memdc,0,355,40,40,bmpdc,0,0,SRCCOPY);
	if(submode[mode]==9)SelectObject(bmpdc,spellon);
	else SelectObject(bmpdc,spell);
	BitBlt(memdc,0,395,40,40,bmpdc,0,0,SRCCOPY);


	int m,frame;

	m = subselect[mode][submode[mode]];
	frame = subselect[mode][submode[mode]+32];
	l = subselect[mode][submode[mode]+64];

	SelectObject(bmpdc,minus);
	BitBlt(memdc,55,8,20,20,bmpdc,0,0,SRCCOPY);

	sprintf(out,"Sprite: %d",m);
	if(focus==1&&cursor)sprintf(out,"%s|",out);
	TextOut(memdc,76,10,out,strlen(out));

	SelectObject(bmpdc,plus);
	BitBlt(memdc,146,8,20,20,bmpdc,0,0,SRCCOPY);

	TextOut(memdc, 652, 10, "Show BG Color: ", 16);
	if (GFXBG)SelectObject(bmpdc, checkon);
	else SelectObject(bmpdc, checkoff);
	BitBlt(memdc, 764, 11, 13, 13, bmpdc, 0, 0, SRCCOPY);

	if(GFXSpace[31]>0)


	if (ExpandedGraphics) {
		switch (submode[mode]) {
		case 0:
			sprintf(out, "Space Used:");
			TextOut(memdc, 615, 30, out, strlen(out));
			sprintf(out, "Space Left:");
			TextOut(memdc, 615, 50, out, strlen(out));

			sprintf(out, "%lu", GFXSpace[0]);
			TextOut(memdc, 704, 30, out, strlen(out));

			sprintf(out, "%ld", 0xC0000 - GFXSpace[0]);
			TextOut(memdc, 704, 50, out, strlen(out));
			break;
		case 1:
			sprintf(out, "Space Used:");
			TextOut(memdc, 615, 30, out, strlen(out));
			sprintf(out, "Space Left:");
			TextOut(memdc, 615, 50, out, strlen(out));

			sprintf(out, "%lu", GFXSpace[1]);
			TextOut(memdc, 704, 30, out, strlen(out));

			sprintf(out, "%ld", 0xB0000 - GFXSpace[1]);
			TextOut(memdc, 704, 50, out, strlen(out));
			break;
		case 3:
			sprintf(out, "Space Used:");
			TextOut(memdc, 615, 30, out, strlen(out));
			sprintf(out, "Space Left:");
			TextOut(memdc, 615, 50, out, strlen(out));

			sprintf(out, "%lu", GFXSpace[3]);
			TextOut(memdc, 704, 30, out, strlen(out));

			sprintf(out, "%ld", 0x50000 - GFXSpace[3]);
			TextOut(memdc, 704, 50, out, strlen(out));
			break;
		case 5:
			break;
		case 6:
			sprintf(out, "Space Used:");
			TextOut(memdc, 615, 30, out, strlen(out));
			sprintf(out, "Space Left:");
			TextOut(memdc, 615, 50, out, strlen(out));

			sprintf(out, "%lu", GFXSpace[6]);
			TextOut(memdc, 704, 30, out, strlen(out));

			sprintf(out, "%ld", 0x40000 - GFXSpace[6]);
			TextOut(memdc, 704, 50, out, strlen(out));
			break;
			break;
		default:
			sprintf(out, "Space Used:");
			TextOut(memdc, 615, 30, out, strlen(out));
			sprintf(out, "Space Left:");
			TextOut(memdc, 615, 50, out, strlen(out));

			sprintf(out, "%lu", GFXSpace[31]);
			TextOut(memdc, 704, 30, out, strlen(out));

			sprintf(out, "%ld", 0x100000 - GFXSpace[31]);
			TextOut(memdc, 704, 50, out, strlen(out));
			break;
		}
	} else {
		if (submode[mode] != 5) {
			sprintf(out, "Space Used:");
			TextOut(memdc, 615, 30, out, strlen(out));
			sprintf(out, "Space Left:");
			TextOut(memdc, 615, 50, out, strlen(out));

			sprintf(out, "%lu", GFXSpace[31]);
			TextOut(memdc, 704, 30, out, strlen(out));

			sprintf(out, "%ld", 0x1C0000 - GFXSpace[31]);
			TextOut(memdc, 704, 50, out, strlen(out));
		}
	}


	if (romsize >= 0x600000) {
		if (ExpandedGraphics)SelectObject(bmpdc, checkon);
		else SelectObject(bmpdc, checkoff);
		BitBlt(memdc, 764, 502, 13, 13, bmpdc, 0, 0, SRCCOPY);

		sprintf(out, "Expand Graphics:");
		TextOut(memdc, 644, 500, out, strlen(out));
	}
	if(submode[mode]==0&&NumGFX[0]<80){
		Rectangle(memdc, 98, 460, 202, 490);
		TextOut(memdc,118,467,"Add Sprite",10);
	}
	if(submode[mode]==0&&NumGFX[0]>35){
		Rectangle(memdc, 98, 500, 202, 530);
		TextOut(memdc,103,507,"Remove Sprite",13);
	}
	if (submode[mode] == 1 && NumGFX[1]<80) {
		Rectangle(memdc, 98, 460, 202, 490);
		TextOut(memdc, 118, 467, "Add Sprite", 10);
	}
	if (submode[mode] == 1 && NumGFX[1]>50) {
		Rectangle(memdc, 98, 500, 202, 530);
		TextOut(memdc, 103, 507, "Remove Sprite", 13);
	}

	if (submode[mode] == 2 && NumGFX[2]<64) {
		Rectangle(memdc, 98, 460, 202, 490);
		TextOut(memdc, 118, 467, "Add Sprite", 10);
	}
	if (submode[mode] == 2 && NumGFX[2]>15) {
		Rectangle(memdc, 98, 500, 202, 530);
		TextOut(memdc, 103, 507, "Remove Sprite", 13);
	}

	if (submode[mode] == 6 && NumGFX[6]<128) {
		Rectangle(memdc, 98, 460, 202, 490);
		TextOut(memdc, 118, 467, "Add Sprite", 10);
	}
	if (submode[mode] == 6 && NumGFX[6]>52) {
		Rectangle(memdc, 98, 500, 202, 530);
		TextOut(memdc, 103, 507, "Remove Sprite", 13);
	}

	if (submode[mode] == 7 && NumGFX[7]<256) {
		Rectangle(memdc, 98, 460, 202, 490);
		TextOut(memdc, 118, 467, "Add Sprite", 10);
	}
	if (submode[mode] == 7 && NumGFX[7]>160) {
		Rectangle(memdc, 98, 500, 202, 530);
		TextOut(memdc, 103, 507, "Remove Sprite", 13);
	}

	if(submode[mode]==0&&NumFSFrame[m]<8){
		Rectangle(memdc, 238, 460, 342, 490);
		TextOut(memdc,257,467,"Add Frame",9);
	}
	if(submode[mode]==0&&NumFSFrame[m]>1){
		Rectangle(memdc, 238, 500, 342, 530);
		TextOut(memdc,242,507,"Remove Frame",12);
	}
	if (submode[mode] == 1 && NumESFrame[m]<8) {
		Rectangle(memdc, 238, 460, 342, 490);
		TextOut(memdc, 257, 467, "Add Frame", 9);
	}
	if (submode[mode] == 1 && NumESFrame[m]>1) {
		Rectangle(memdc, 238, 500, 342, 530);
		TextOut(memdc, 242, 507, "Remove Frame", 12);
	}

	if (submode[mode] == 0 && NumFSPalette[m]<8) {
		Rectangle(memdc, 378, 460, 482, 490);
		TextOut(memdc, 395, 467, "Add Palette", 11);
	}
	if (submode[mode] == 0 && NumFSPalette[m]>1) {
		Rectangle(memdc, 378, 500, 482, 530);
		TextOut(memdc, 378, 507, "Remove Palette", 14);
	}

	if(submode[mode]<2||submode[mode]==7){

		SelectObject(bmpdc,minus);
		BitBlt(memdc,186,8,20,20,bmpdc,0,0,SRCCOPY);

		sprintf(out,"Frame: %d",frame);
		if(focus==2&&cursor)sprintf(out,"%s|",out);
		TextOut(memdc,206,10,out,strlen(out));

		SelectObject(bmpdc,plus);
		BitBlt(memdc,276,8,20,20,bmpdc,0,0,SRCCOPY);
	} else if (submode[mode] == 6) {
		SelectObject(bmpdc, minus);
		BitBlt(memdc, 186, 8, 20, 20, bmpdc, 0, 0, SRCCOPY);

		sprintf(out, "Anim: %d", subselect[mode][submode[mode] + 96]);
		if (focus == 2 && cursor)sprintf(out, "%s|", out);
		TextOut(memdc, 206, 10, out, strlen(out));

		SelectObject(bmpdc, plus);
		BitBlt(memdc, 276, 8, 20, 20, bmpdc, 0, 0, SRCCOPY);

		if (subselect[mode][submode[mode] + 96]) {
			SelectObject(bmpdc, minus);
			BitBlt(memdc, 396, 68, 20, 20, bmpdc, 0, 0, SRCCOPY);

			sprintf(out, "Tile: %d", subselect[mode][submode[mode] + 128]);
			SetTextColor(memdc, colorList[subselect[mode][submode[mode] + 128]]);
			TextOut(memdc, 416, 70, out, strlen(out));
			SetTextColor(memdc, RGB(0, 0, 0));

			SelectObject(bmpdc, plus);
			BitBlt(memdc, 486, 68, 20, 20, bmpdc, 0, 0, SRCCOPY);

			int dx;
			int dy;
			int sx;
			int sy;


			int t = POData[subselect[mode][submode[mode]]][l++] * 256;
			t += POData[subselect[mode][submode[mode]]][l++];
			for (i = 0;i < t;i++) {
				if (i == subselect[mode][submode[mode] + 128]) {
					dx = POData[subselect[mode][submode[mode]]][l++];
					dy = POData[subselect[mode][submode[mode]]][l++];
					sx = POData[subselect[mode][submode[mode]]][l++];
					sy = POData[subselect[mode][submode[mode]]][l++];

					sx = NtoX(sy);
					sy = NtoY(sy);
				} else {
					l += 4;
				}
			}
			if (subselect[mode][submode[mode] + 96]==2) {
				t = POData[subselect[mode][submode[mode]]][l++] * 256;
				t += POData[subselect[mode][submode[mode]]][l++];
				for (i = 0;i < t;i++) {
					if (i == subselect[mode][submode[mode] + 128]) {
						dx = POData[subselect[mode][submode[mode]]][l++];
						dy = POData[subselect[mode][submode[mode]]][l++];
						sx = POData[subselect[mode][submode[mode]]][l++];
						sy = POData[subselect[mode][submode[mode]]][l++];

						sx = NtoX(sy);
						sy = NtoY(sy);
					} else {
						l += 4;
					}
				}
			}
			if (t) {
				sprintf(out, "Source X:");
				TextOut(memdc, 396, 88, out, strlen(out));

				sprintf(out, "Source Y:");
				TextOut(memdc, 396, 108, out, strlen(out));

				sprintf(out, "Dest X:");
				TextOut(memdc, 396, 128, out, strlen(out));

				sprintf(out, "Dest Y:");
				TextOut(memdc, 396, 148, out, strlen(out));


				sprintf(out, "Show Grid:");
				TextOut(memdc, 396, 168, out, strlen(out));

				if (AnimGrid)SelectObject(bmpdc, checkon);
				else SelectObject(bmpdc, checkoff);
				BitBlt(memdc, 490, 170, 13, 13, bmpdc, 0, 0, SRCCOPY);

				sprintf(out, "%d", sx);
				if (focus == 4)sprintf(out, "%s|", out);
				TextOut(memdc, 496, 88, out, strlen(out));

				sprintf(out, "%d", sy);
				if (focus == 5)sprintf(out, "%s|", out);
				TextOut(memdc, 496, 108, out, strlen(out));

				sprintf(out, "%d", dx);
				if (focus == 6)sprintf(out, "%s|", out);
				TextOut(memdc, 496, 128, out, strlen(out));

				sprintf(out, "%d", dy);
				if (focus == 7)sprintf(out, "%s|", out);
				TextOut(memdc, 496, 148, out, strlen(out));
			}

			if (t<8) {
				Rectangle(memdc, 548, 88, 652, 118);
				TextOut(memdc, 574, 95, "Add Tile", 8);
			}
			if (t>0) {
				Rectangle(memdc, 548, 128, 652, 158);
				TextOut(memdc, 561, 135, "Remove Tile", 11);
			}



			if (t>0) {
				TextOut(memdc, 361, 335, "Tile:", 5);

				Rectangle(memdc, 418, 328, 532, 358);
				TextOut(memdc, 425, 335, "From Clipboard", 14);

				Rectangle(memdc, 548, 328, 652, 358);
				TextOut(memdc, 560, 335, "To Clipboard", 12);
			}


			TextOut(memdc, 361, 375, "Anim:", 5);

			Rectangle(memdc, 418, 368, 532, 398);
			TextOut(memdc, 425, 375, "From Clipboard", 14);

			Rectangle(memdc, 548, 368, 652, 398);
			TextOut(memdc, 560, 375, "To Clipboard", 12);


		}


	}
	if(submode[mode]<3){

		SelectObject(bmpdc,minus);
		BitBlt(memdc,316,8,20,20,bmpdc,0,0,SRCCOPY);

		sprintf(out,"Palette: %d",l);
		if(focus==3&&cursor)sprintf(out,"%s|",out);
		TextOut(memdc,336,10,out,strlen(out));

		SelectObject(bmpdc,plus);
		BitBlt(memdc,414,8,20,20,bmpdc,0,0,SRCCOPY);

	}

	int width,height;

	if(submode[mode]<2||submode[mode]==3||submode[mode]==4||submode[mode]==6||submode[mode]==7||submode[mode]==8||submode[mode]==9){
		if(Pencil){
			SelectObject(bmpdc,pencilon);
			BitBlt(memdc,50,64,20,20,bmpdc,0,0,SRCCOPY);
			SelectObject(bmpdc,eraser);
			BitBlt(memdc,50,89,20,20,bmpdc,0,0,SRCCOPY);
		} else {
			SelectObject(bmpdc,pencil);
			BitBlt(memdc,50,64,20,20,bmpdc,0,0,SRCCOPY);
			SelectObject(bmpdc,eraseron);
			BitBlt(memdc,50,89,20,20,bmpdc,0,0,SRCCOPY);
		}

		switch(size){
		case 1:
			SelectObject(bmpdc,oneon);
			BitBlt(memdc,50,115,20,20,bmpdc,0,0,SRCCOPY);
			SelectObject(bmpdc,two);
			BitBlt(memdc,50,140,20,20,bmpdc,0,0,SRCCOPY);
			SelectObject(bmpdc,four);
			BitBlt(memdc,50,165,20,20,bmpdc,0,0,SRCCOPY);
			break;
		case 2:
			SelectObject(bmpdc,one);
			BitBlt(memdc,50,115,20,20,bmpdc,0,0,SRCCOPY);
			SelectObject(bmpdc,twoon);
			BitBlt(memdc,50,140,20,20,bmpdc,0,0,SRCCOPY);
			SelectObject(bmpdc,four);
			BitBlt(memdc,50,165,20,20,bmpdc,0,0,SRCCOPY);
			break;
		case 4:
			SelectObject(bmpdc,one);
			BitBlt(memdc,50,115,20,20,bmpdc,0,0,SRCCOPY);
			SelectObject(bmpdc,two);
			BitBlt(memdc,50,140,20,20,bmpdc,0,0,SRCCOPY);
			SelectObject(bmpdc,fouron);
			BitBlt(memdc,50,165,20,20,bmpdc,0,0,SRCCOPY);
			break;
		}


	}
	int t, pl;
	int qx, qy, vx, vy;

	switch(submode[mode]){
		case 0:
			TextOut(memdc, 90 + 18 * 17, 40, "(Right Click to Edit Color)", 27);

			width=FSSize[m][frame][0];
			height=FSSize[m][frame][1];

			for(x=0;x<width;x++){
				for(y=0;y<height;y++){
					for(i=0;i<4;i++){
						for(j=0;j<4;j++){
							k = ForceSprites[subselect[mode][submode[mode]]][frame][x+y*width];
							if(k<0)k=0;

							if(k||GFXBG)SetPixel(memdc,x*4+i+82,y*4+j+67,RGB(FSPalette[m][l][k][0],FSPalette[m][l][k][1],FSPalette[m][l][k][2]));
						}
					}
				}
			}

			for(i=0;i<16;i++){
				for(int dx=0;dx<18;dx++){
					for(int dy=0;dy<18;dy++){
						SetPixel(memdc,90+18*i+dx,40+dy,RGB(FSPalette[m][l][i][0],FSPalette[m][l][i][1],FSPalette[m][l][i][2]));
					}
				}
			}

			for(i=0;i<18;i++){
				for(int dy=0;dy<18;dy++){
					SetPixel(memdc,50+i,188+dy,RGB(FSPalette[m][l][color][0],FSPalette[m][l][color][1],FSPalette[m][l][color][2]));
				}
			}

			break;
		case 1:
			TextOut(memdc, 90 + 18 * 17, 40, "(Right Click to Edit Color)", 27);

			width=ESSize[m][frame][0];
			height=ESSize[m][frame][1];

			for(x=0;x<width;x++){
				for(y=0;y<height;y++){
					for(i=0;i<4;i++){
						for(j=0;j<4;j++){
							k = EnemySprites[subselect[mode][submode[mode]]][frame][x+y*width];
							if(k<0)k=0;

							if (k || GFXBG)SetPixel(memdc,x*4+i+82,y*4+j+67,RGB(ESPalette[m][l][k][0],ESPalette[m][l][k][1],ESPalette[m][l][k][2]));
						}
					}
				}
			}

			for(i=0;i<16;i++){
				for(int dx=0;dx<18;dx++){
					for(int dy=0;dy<18;dy++){
						SetPixel(memdc,90+18*i+dx,40+dy,RGB(ESPalette[m][l][i][0],ESPalette[m][l][i][1],ESPalette[m][l][i][2]));
					}
				}
			}

			for(i=0;i<18;i++){
				for(int dy=0;dy<18;dy++){
					SetPixel(memdc,50+i,188+dy,RGB(ESPalette[m][l][color][0],ESPalette[m][l][color][1],ESPalette[m][l][color][2]));
				}
			}
			break;
		case 2:
			width=WSSize[m][frame][0];
			height=WSSize[m][frame][1];

			for(x=0;x<width;x++){
				for(y=0;y<height;y++){
					for(i=0;i<4;i++){
						for(j=0;j<4;j++){
							k = WeaponSprites[subselect[mode][submode[mode]]][frame][x+y*width];
							if(k<0)k=0;
							switch(k){
								case 15:
									k = 3;
									SetPixel(memdc,x*4+i+50,y*4+j+35,RGB(ISPalette[l][k][0],ISPalette[l][k][1],ISPalette[l][k][2]));
									break;
								case 14:
									SetPixel(memdc,x*4+i+50,y*4+j+35,RGB(0,0,0));
									break;
								case 13:
									k = 2;
									SetPixel(memdc,x*4+i+50,y*4+j+35,RGB(ISPalette[l][k][0],ISPalette[l][k][1],ISPalette[l][k][2]));
									break;
								case 12:
									k = 1;
									SetPixel(memdc,x*4+i+50,y*4+j+35,RGB(ISPalette[l][k][0],ISPalette[l][k][1],ISPalette[l][k][2]));
									break;
								case 11:
									k = 0;
									SetPixel(memdc,x*4+i+50,y*4+j+35,RGB(ISPalette[l][k][0],ISPalette[l][k][1],ISPalette[l][k][2]));
									break;
								case 0:
									break;
								case 1:
									SetPixel(memdc,x*4+i+50,y*4+j+35,RGB(255,255,255));
									break;
								default:
									k=k;
									break;
							}
							//SetPixel(memdc,x*4+i+50,y*4+j+35,RGB(WSPalette[m][k][0],WSPalette[m][k][1],WSPalette[m][k][2]));
							//SetPixel(memdc,x*4+i+50,y*4+j+35,RGB(FSPalette[m][l][k][0],FSPalette[m][l][k][1],FSPalette[m][l][k][2]));
						}
					}
				}
			}

			for(i=0;i<4;i++){
				for(int dx=0;dx<18;dx++){
					for(int dy=0;dy<18;dy++){
						SetPixel(memdc,440+18*i+dx,10+dy,RGB(ISPalette[l][i][0],ISPalette[l][i][1],ISPalette[l][i][2]));
					}
				}
			}
			break;
		case 3:
			TextOut(memdc, 90 + 18 * 17, 40, "(Right Click to Edit Color)", 27);

			width=BGSize[m][0];
			height=BGSize[m][1];

			for(x=0;x<width;x++){
				for(y=0;y<height;y++){
					for(i=0;i<4;i++){
						for(j=0;j<4;j++){
							k = Backgrounds[subselect[mode][submode[mode]]][x+y*width];
							if(k<0)k=0;

							if (k || GFXBG)SetPixel(memdc,x*4+i+82,y*4+j+67,RGB(BGPalette[m-m%2][l][k][0],BGPalette[m-m%2][l][k][1],BGPalette[m-m%2][l][k][2]));
						}
					}
				}
			}

			for(i=0;i<16;i++){
				for(int dx=0;dx<18;dx++){
					for(int dy=0;dy<18;dy++){
						SetPixel(memdc,90+18*i+dx,40+dy,RGB(BGPalette[m-m%2][l][i][0],BGPalette[m-m%2][l][i][1],BGPalette[m-m%2][l][i][2]));
					}
				}
			}

			for(i=0;i<18;i++){
				for(int dy=0;dy<18;dy++){
					SetPixel(memdc,50+i,188+dy,RGB(BGPalette[m-m%2][l][color][0],BGPalette[m-m%2][l][color][1],BGPalette[m-m%2][l][color][2]));
				}
			}
			break;
		case 4:
			TextOut(memdc, 90 + 18 * 17, 40, "(Right Click to Edit Color)", 27);

			width=PFSize[m][0];
			height=PFSize[m][1];

			for(x=0;x<width;x++){
				for(y=0;y<height;y++){
					for(i=0;i<4;i++){
						for(j=0;j<4;j++){
							k = Platforms[subselect[mode][submode[mode]]][x+y*width];
							if(k<0)k=0;
							if (k || GFXBG)SetPixel(memdc,x*4+i+82,y*4+j+67,RGB(PFPalette[m][k][0],PFPalette[m][k][1],PFPalette[m][k][2]));
						}
					}
				}
			}
			for(i=0;i<6;i++){
				for(int dx=0;dx<18;dx++){
					for(int dy=0;dy<18;dy++){
						SetPixel(memdc,90+18*i+dx,40+dy,RGB(PFPalette[m][i][0],PFPalette[m][i][1],PFPalette[m][i][2]));
					}
				}
			}

			for(i=0;i<18;i++){
				for(int dy=0;dy<18;dy++){
					SetPixel(memdc,50+i,188+dy,RGB(PFPalette[m][color][0],PFPalette[m][color][1],PFPalette[m][color][2]));
				}
			}
			break;
		case 5:
			TextOut(memdc, 490, 10, "(Right Click to Edit Color)", 27);

			width= CSSize[m][0];
			height= CSSize[m][1];

			qx = -1;
			qy = 0;

			r.left = 552;
			r.top = 35;
			r.right = 552 + 32 * 8;
			r.bottom = 35 + 12 * 8;

			

			s = subselect[mode][submode[mode]];
			pl = s;
			while (pl>0 && CSPalOffset[pl] == 0)pl--;

			if (s == 0) {
				brush = (HBRUSH)CreateSolidBrush(RGB(100, 1, 99));

				FillRect(memdc, &r, brush);

				DeleteObject(brush);

				for (vy = 0; vy < height / 8; vy++) {
					for (x = 0; x < width; x++) {
						for (y = 0; y < 8; y++) {

							vx = (x - x % 8) / 8;

							if (SplashLayout[vx + 16 * vy] == -255)continue;

							if (!(x % 8) && !(y % 8))
								if (SplashLayout[vx + 16 * vy] < 0) {
									for (l = 1; l < -1 * SplashLayout[vx + 16 * vy]; l++) {
										qx--;
										if (qx == 15) {
											qx = 31;
											qy--;
										}
									}
								} else
									for (l = 0; l <= SplashLayout[vx + 16 * vy]; l++) {
										qx++;
										if (qx == 16) {
											qx = 0;
											qy++;
											if (qy == 12) {
												qy = 0;
												qx = 16;
											}
										}
										if (qx == 32) {
											qx = 16;
											qy++;
										}
									}

								for (i = 0; i < 4; i++) {
									for (j = 0; j < 4; j++) {
										POINT p;
										p.x = x * 4;
										p.y = (8 * vy + y) * 4;
										TilesetToPixel(p);
										k = CutsceneGFX[s][p.x / 4 + p.y / 4 * width];
										if (k < 0)k = 0;

										//SetPixel(memdc,x*4+i+50,y*4+j+35,RGB(IconPalette[k][0],IconPalette[k][1],IconPalette[k][2]));
										SetPixel(memdc, x * 4 + i + 40, vy * 32 + y * 4 + j + 35, RGB(CSPalette[s][k][0], CSPalette[s][k][1], CSPalette[s][k][2]));

										if (!i && !j)SetPixel(memdc, qx * 8 + x % 8 + 552, qy * 8 + y % 8 + 35, RGB(CSPalette[s][k][0], CSPalette[s][k][1], CSPalette[s][k][2]));
									}
								}
						}

					}
				}
			} else {
				for (x = 0; x<width; x++) {
					for (y = 0; y<height; y++) {
						for (i = 0; i<4; i++) {
							for (j = 0; j<4; j++) {
								k = CutsceneGFX[s][x + y*width];
								if (k<0)k = 0;
								if (k || GFXBG)SetPixel(memdc, x * 4 + i + 82, y * 4 + j + 67, RGB(CSPalette[pl][k][0], CSPalette[pl][k][1], CSPalette[pl][k][2]));
							}
						}
					}
				}
			}

			for (i = 0; i<16; i++) {
				for (int dx = 0; dx<18; dx++) {
					for (int dy = 0; dy<18; dy++) {
						SetPixel(memdc, 190 + 18 * i + dx, 10 + dy, RGB(CSPalette[pl][i][0], CSPalette[pl][i][1], CSPalette[pl][i][2]));
					}
				}
			}

			break;
		case 6:
			TextOut(memdc, 90 + 18 * 17, 40, "(Right Click to Edit Color)", 27);

			width=POSize[m][0];
			height=POSize[m][1];

			for(x=0;x<width;x++){
				for(y=0;y<height;y++){
					for(i=0;i<4;i++){
						for(j=0;j<4;j++){
							k = Portraits[subselect[mode][submode[mode]]][x+y*width];
							if(k<0)k=0;

							if (k || GFXBG)SetPixel(memdc,x*4+i+82,y*4+j+67,RGB(POPalette[m][k][0],POPalette[m][k][1],POPalette[m][k][2]));
						}
					}
				}
			}
			l = 0;

			if (subselect[mode][submode[mode] + 96] && AnimGrid) {
				for (int i = 0; i < 8; i++) {
					MoveToEx(memdc, 82 + 32 * i, 67, 0);
					LineTo(memdc, 82 + 32 * i, 67 + 32 * 8);
					MoveToEx(memdc, 82, 67 + 32 * i, 0);
					LineTo(memdc, 82 + 32 * 8, 67 + 32 * i);
				}
			}

			switch (subselect[mode][submode[mode] + 96]) {
				case 1:
					t = POData[subselect[mode][submode[mode]]][l++] * 256;
					t+= POData[subselect[mode][submode[mode]]][l++];
					for (i = 0;i < t;i++) {
						int dx = POData[subselect[mode][submode[mode]]][l++];
						int dy = POData[subselect[mode][submode[mode]]][l++];
						int sx = POData[subselect[mode][submode[mode]]][l++];
						int sy = POData[subselect[mode][submode[mode]]][l++];
						sx = NtoX(sy);
						sy = NtoY(sy);
						for (x = 0;x < 8;x++) {
							for (y = 0;y < 8;y++) {
								k = Portraits[subselect[mode][submode[mode]]][sx*8 + x + (sy*8+y)*width];
								if (k<0)k = 0;

								for (int l2 = 0;l2 < 4;l2++) {
									for (int m2 = 0;m2 < 4;m2++) {
										if (k || GFXBG)SetPixel(memdc, (dx*8 + x) * 4 + l2 + 82, (dy*8 + y) * 4 + m2 + 67, RGB(POPalette[m][k][0], POPalette[m][k][1], POPalette[m][k][2]));
									}
								}
							}
						}
						HBRUSH tbr = CreateSolidBrush(colorList[i]);
						RECT tar;
						tar.top = (dy * 8) * 4 + 67;
						tar.left = (dx * 8) * 4 + 82;
						tar.right = tar.left + 32;
						tar.bottom = tar.top + 32;

						FrameRect(memdc, &tar, tbr);

						tar.top = (sy * 8) * 4 + 67;
						tar.left = (sx * 8) * 4 + 82;
						tar.right = tar.left + 32;
						tar.bottom = tar.top + 32;

						FrameRect(memdc, &tar, tbr);
						DeleteObject(tbr);
					}
					break;
				case 2:
					t = POData[subselect[mode][submode[mode]]][l++] * 256;
					t += POData[subselect[mode][submode[mode]]][l++];
					for (i = 0;i < t;i++) {
						int dx = POData[subselect[mode][submode[mode]]][l++];
						int dy = POData[subselect[mode][submode[mode]]][l++];
						int sx = POData[subselect[mode][submode[mode]]][l++];
						int sy = POData[subselect[mode][submode[mode]]][l++];
					}
					t = POData[subselect[mode][submode[mode]]][l++] * 256;
					t += POData[subselect[mode][submode[mode]]][l++];
					for (i = 0;i < t;i++) {
						int dx = POData[subselect[mode][submode[mode]]][l++];
						int dy = POData[subselect[mode][submode[mode]]][l++];
						int sx = POData[subselect[mode][submode[mode]]][l++];
						int sy = POData[subselect[mode][submode[mode]]][l++];
						sx = NtoX(sy);
						sy = NtoY(sy);
						for (x = 0;x < 8;x++) {
							for (y = 0;y < 8;y++) {
								k = Portraits[subselect[mode][submode[mode]]][sx * 8 + x + (sy * 8 + y)*width];
								if (k<0)k = 0;

								for (int l2 = 0;l2 < 4;l2++) {
									for (int m2 = 0;m2 < 4;m2++) {
										if (k || GFXBG)SetPixel(memdc, (dx * 8 + x) * 4 + l2 + 82, (dy * 8 + y) * 4 + m2 + 67, RGB(POPalette[m][k][0], POPalette[m][k][1], POPalette[m][k][2]));
									}
								}
							}
						}
						HBRUSH tbr = CreateSolidBrush(colorList[i]);
						RECT tar;
						tar.top = (dy * 8) * 4 + 67;
						tar.left = (dx * 8) * 4 + 82;
						tar.right = tar.left + 32;
						tar.bottom = tar.top + 32;

						FrameRect(memdc, &tar, tbr);

						tar.top = (sy * 8) * 4 + 67;
						tar.left = (sx * 8) * 4 + 82;
						tar.right = tar.left + 32;
						tar.bottom = tar.top + 32;

						FrameRect(memdc, &tar, tbr);
						DeleteObject(tbr);
					}
					break;
			}




			for(i=0;i<16;i++){
				for(int dx=0;dx<18;dx++){
					for(int dy=0;dy<18;dy++){
						SetPixel(memdc,90+18*i+dx,40+dy,RGB(POPalette[m][i][0],POPalette[m][i][1],POPalette[m][i][2]));
					}
				}
			}

			for(i=0;i<18;i++){
				for(int dy=0;dy<18;dy++){
					SetPixel(memdc,50+i,188+dy,RGB(POPalette[m][color][0],POPalette[m][color][1],POPalette[m][color][2]));
				}
			}
			break;
		case 7:
			TextOut(memdc, 90 + 18 * 17, 40, "(Right Click to Edit Color)", 27);

			TextOut(memdc, 90 + 18 * 17, 60, "Choose Map Sprite Palette:", 26);
			if (ChooseMSPal)SelectObject(bmpdc, checkon);
			else SelectObject(bmpdc, checkoff);
			BitBlt(memdc, 277 + 18 * 17, 62, 13, 13, bmpdc, 0, 0, SRCCOPY);

			TextOut(memdc, 82, 170, "Text Sound:", 11);
			sprintf(out, "%d", MSTextSound[subselect[mode][submode[mode]]]);
			if (focus == 8 && cursor)sprintf(out, "%s|", out);
			TextOut(memdc, 162, 170, out, strlen(out));

			SelectObject(bmpdc, dots);
			BitBlt(memdc, 190, 168, 20, 20, bmpdc, 0, 0, SRCCOPY);


			if (ChooseMSPal) {
				TextOut(memdc, 82, 190, "Use Enemy Palette:", 18);
				if (MSPalette[subselect[mode][submode[mode]]])SelectObject(bmpdc, checkon);
				else SelectObject(bmpdc, checkoff);
				BitBlt(memdc, 214, 192, 13, 13, bmpdc, 0, 0, SRCCOPY);
			}

			width=MSSize[m][frame][0];
			height=MSSize[m][frame][1];
			
			for(x=0;x<width;x++){
				for(y=0;y<height;y++){
					for(i=0;i<4;i++){
						for(j=0;j<4;j++){
							k = MapSprites[subselect[mode][submode[mode]]][frame][x+y*width];
							if(k<0)k=0;

							if (k || GFXBG)
							if(MSPalette[subselect[mode][submode[mode]]])SetPixel(memdc,x*4+i+82,y*4+j+67,RGB(EMSPalette[k][0], EMSPalette[k][1], EMSPalette[k][2]));
							else SetPixel(memdc, x * 4 + i + 82, y * 4 + j + 67, RGB(FMSPalette[k][0], FMSPalette[k][1], FMSPalette[k][2]));
						}
					}
				}
			}

			for(i=0;i<16;i++){
				for(int dx=0;dx<18;dx++){
					for(int dy=0;dy<18;dy++){
						if (MSPalette[subselect[mode][submode[mode]]])SetPixel(memdc,90+18*i+dx,40+dy,RGB(EMSPalette[i][0], EMSPalette[i][1], EMSPalette[i][2]));
						else SetPixel(memdc, 90 + 18 * i + dx, 40 + dy, RGB(FMSPalette[i][0], FMSPalette[i][1], FMSPalette[i][2]));
					}
				}
			}

			for(i=0;i<18;i++){
				for(int dy=0;dy<18;dy++){
					if (MSPalette[subselect[mode][submode[mode]]])SetPixel(memdc, 50 + i, 188 + dy, RGB(EMSPalette[color][0], EMSPalette[color][1], EMSPalette[color][2])); 
					else SetPixel(memdc, 50 + i, 188 + dy, RGB(FMSPalette[color][0], FMSPalette[color][1], FMSPalette[color][2]));
				}
			}
			break;
		case 8:
			TextOut(memdc, 90 + 18 * 17, 40, "(Right Click to Edit Color)", 27);

			width=TSSize[m][0];
			height=TSSize[m][1];

			for(x=0;x<width;x++){
				for(y=0;y<height;y++){
					for(i=0;i<4;i++){
						for(j=0;j<4;j++){
							k = Tilesets[subselect[mode][submode[mode]]][x+y*width];
							if(k<0)k=0;
							p.x=x*4;
							p.y=y*4;
							PixelToTileset(p);
							if (k || GFXBG)SetPixel(memdc,p.x+i+82,p.y+j+67,RGB(TSPalette[TSPalNums[m]][k][0],TSPalette[TSPalNums[m]][k][1],TSPalette[TSPalNums[m]][k][2]));
						}
					}
				}
			}

			for(i=0;i<16;i++){
				for(int dx=0;dx<18;dx++){
					for(int dy=0;dy<18;dy++){
						SetPixel(memdc,90+18*i+dx,40+dy,RGB(TSPalette[TSPalNums[m]][i][0],TSPalette[TSPalNums[m]][i][1],TSPalette[TSPalNums[m]][i][2]));
					}
				}
			}

			for(i=0;i<18;i++){
				for(int dy=0;dy<18;dy++){
					SetPixel(memdc,50+i,188+dy,RGB(TSPalette[TSPalNums[m]][color][0],TSPalette[TSPalNums[m]][color][1],TSPalette[TSPalNums[m]][color][2]));
				}
			}

			break;
		case 9:
			width=EFSize[m][0];
			height=EFSize[m][1];

			for(x=0;x<width;x++){
				for(y=0;y<height;y++){
					for(i=0;i<4;i++){
						for(j=0;j<4;j++){
							k = Effects[subselect[mode][submode[mode]]][x+y*width];
							if(k<0)k=0;
							if (k || GFXBG)SetPixel(memdc,x*4+i+82,y*4+j+67,RGB(EFPalette[m][k][0],EFPalette[m][k][1],EFPalette[m][k][2]));
						}
					}
				}
			}

			if(m==3){
				j=4;
				k=5;
			} else if(m<14){
				j=6;
				k=5;
			} else {
				j=16;
				k=0;
			}

			for(i=0;i<j;i++){
				for(int dx=0;dx<18;dx++){
					for(int dy=0;dy<18;dy++){
						if(i&&k)SetPixel(memdc,90+18*i+dx,40+dy,RGB(EFPalette[m][i+k][0],EFPalette[m][i+k][1],EFPalette[m][i+k][2]));
						else SetPixel(memdc,90+18*i+dx,40+dy,RGB(EFPalette[m][i][0],EFPalette[m][i][1],EFPalette[m][i][2]));

					}
				}
			}

			for(i=0;i<18;i++){
				for(int dy=0;dy<18;dy++){
					SetPixel(memdc,50+i,188+dy,RGB(EFPalette[m][color][0],EFPalette[m][color][1],EFPalette[m][color][2]));
				}
			}
			break;
	}


	if (menu == 1) {
		drawSoundList(memdc, 50, 28, MSTextSound[subselect[mode][submode[mode]]], 69);
	}
	//test graphics
		/*	width=8*8;
			height=16*8;

			for(x=0;x<width;x++){
				for(y=0;y<height;y++){
					for(i=0;i<4;i++){
						for(j=0;j<4;j++){
							k = TempGfx[x+y*width];
							if(k<0)k=0;

							SetPixel(memdc,x*4+i+82,y*4+j+67,RGB(FSPalette[m][l][k][0],FSPalette[m][l][k][1],FSPalette[m][l][k][2]));
						}
					}
				}
			}*/
	//


}