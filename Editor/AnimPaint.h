

if(submode[mode]==0){
	if(!GraphicsLoaded){
		if(strlen(file)){
			Rectangle(memdc,50,30,176,52);
			TextOut(memdc,55,33,"Decompress GFX",14);
		} else {
			TextOut(memdc,55,33,"Load a ROM first.",17);
		}
	} else {

		HBRUSH temp = (HBRUSH)SelectObject(memdc, GetStockObject(NULL_BRUSH));
		HPEN tempp = (HPEN)SelectObject(memdc, CreatePen(PS_SOLID, 2, RGB(255, 200, 0)));
		Rectangle(memdc, -238 + dwidth / 2, 36, 789 + dwidth / 2, 499);
		SelectObject(memdc, temp);
		DeleteObject(SelectObject(memdc, tempp));

		int m = subselect[mode][2];

		width = WSSize[m][0][0];
		height = WSSize[m][0][1];

		int l = findWSPalette(m);

		u = WSAnim[select[mode]][subselect[mode][0]][4] & 0x0F;

		if (subselect[mode][0]) {
			dx = WSAnim[select[mode]][subselect[mode][0]][2] * 4 + 80;
			dy = WSAnim[select[mode]][subselect[mode][0]][3] * 4;
		} else {
			dx = 80;
			dy = 0;
		}

		if(m<127)
		for (x = width / 4 * u;x<width / 4 * (u + 1);x++) {
			for (y = 0;y<height / 2;y++) {
				for (i = 0;i<4;i++) {
					for (j = 0;j<4;j++) {
						k = WeaponSprites[m][0][x + y*width];
						if (k<0)k = 0;

						if (AnimBorder && (x== width / 4 * u || x == width / 4 * (u + 1) - 1 || y==0 || y==height/2-1))k = 1;

						v = x - width / 4 * u;

						if (WSAnim[select[mode]][subselect[mode][0]][4] & 0x10) {
							x += width / 2 - 2 * v - 1;
						}

						w = y;

						if (WSAnim[select[mode]][subselect[mode][0]][4] & 0x20) {
							y += height / 2 - 2 * w - 1;
						}

						x += WSAnim[select[mode]][subselect[mode][0]][6];
						y += WSAnim[select[mode]][subselect[mode][0]][7];

						switch (k) {
						case 15:
							k = 3;
							SetPixel(memdc, (x - width / 4 * u) * 4 + i + 225 + dwidth / 2 + dx, y * 4 + j + 67 + dy, RGB(ISPalette[l][k][0], ISPalette[l][k][1], ISPalette[l][k][2]));
							break;
						case 14:
							SetPixel(memdc, (x - width / 4 * u) * 4 + i + 225 + dwidth / 2 + dx, y * 4 + j + 67 + dy, RGB(0, 0, 0));
							break;
						case 13:
							k = 2;
							SetPixel(memdc, (x - width / 4 * u) * 4 + i + 225 + dwidth / 2 + dx, y * 4 + j + 67 + dy, RGB(ISPalette[l][k][0], ISPalette[l][k][1], ISPalette[l][k][2]));
							break;
						case 12:
							k = 1;
							SetPixel(memdc, (x - width / 4 * u) * 4 + i + 225 + dwidth / 2 + dx, y * 4 + j + 67 + dy, RGB(ISPalette[l][k][0], ISPalette[l][k][1], ISPalette[l][k][2]));
							break;
						case 11:
							k = 0;
							SetPixel(memdc, (x - width / 4 * u) * 4 + i + 225 + dwidth / 2 + dx, y * 4 + j + 67 + dy, RGB(ISPalette[l][k][0], ISPalette[l][k][1], ISPalette[l][k][2]));
							break;
						case 1:
							SetPixel(memdc, (x - width / 4 * u) * 4 + i + 225 + dwidth / 2 + dx, y * 4 + j + 67 + dy, RGB(255, 255, 255));
							break;

						}

						x -= WSAnim[select[mode]][subselect[mode][0]][6];
						y -= WSAnim[select[mode]][subselect[mode][0]][7];

						if (WSAnim[select[mode]][subselect[mode][0]][4] & 0x10) {
							x -= width / 2 - 2 * v - 1;
						}

						if (WSAnim[select[mode]][subselect[mode][0]][4] & 0x20) {
							y -= height / 2 - 2 * w - 1;
						}
					}
				}
			}
		}
		if (m<127)
		for (x = width / 4 * u;x<width / 4 * (u + 1);x++) {
			for (y = height / 2;y<height;y++) {
				for (i = 0;i<4;i++) {
					for (j = 0;j<4;j++) {
						k = WeaponSprites[m][0][x + y*width];
						if (k<0)k = 0;

						if (AnimBorder && (x == width / 4 * u || x == width / 4 * (u + 1) - 1 || y == height / 2 || y == height - 1))k = 1;

						v = x - width / 4 * u;

						if (WSAnim[select[mode]][subselect[mode][0]][4] & 0x10) {
							x += width / 2 - 2 * v - 1;
							x -= width / 4;
						} else {
							x += width / 4;
						}

						w = y - height / 2;

						if (WSAnim[select[mode]][subselect[mode][0]][4] & 0x20) {
							y += height / 2 - 2 * w - 1;
						}

						x += WSAnim[select[mode]][subselect[mode][0]][6];
						y += WSAnim[select[mode]][subselect[mode][0]][7];

						switch (k) {
						case 15:
							k = 3;
							SetPixel(memdc, (x - width / 4 * u) * 4 + i + 225 + dwidth / 2 + dx, (y - height / 2) * 4 + j + 67 + dy, RGB(ISPalette[l][k][0], ISPalette[l][k][1], ISPalette[l][k][2]));
							break;
						case 14:
							SetPixel(memdc, (x - width / 4 * u) * 4 + i + 225 + dwidth / 2 + dx, (y - height / 2) * 4 + j + 67 + dy, RGB(0, 0, 0));
							break;
						case 13:
							k = 2;
							SetPixel(memdc, (x - width / 4 * u) * 4 + i + 225 + dwidth / 2 + dx, (y - height / 2) * 4 + j + 67 + dy, RGB(ISPalette[l][k][0], ISPalette[l][k][1], ISPalette[l][k][2]));
							break;
						case 12:
							k = 1;
							SetPixel(memdc, (x - width / 4 * u) * 4 + i + 225 + dwidth / 2 + dx, (y - height / 2) * 4 + j + 67 + dy, RGB(ISPalette[l][k][0], ISPalette[l][k][1], ISPalette[l][k][2]));
							break;
						case 11:
							k = 0;
							SetPixel(memdc, (x - width / 4 * u) * 4 + i + 225 + dwidth / 2 + dx, (y - height / 2) * 4 + j + 67 + dy, RGB(ISPalette[l][k][0], ISPalette[l][k][1], ISPalette[l][k][2]));
							break;
						case 1:
							SetPixel(memdc, (x - width / 4 * u) * 4 + i + 225 + dwidth / 2 + dx, (y - height / 2) * 4 + j + 67 + dy, RGB(255, 255, 255));
							break;
						}

						x -= WSAnim[select[mode]][subselect[mode][0]][6];
						y -= WSAnim[select[mode]][subselect[mode][0]][7];

						if (WSAnim[select[mode]][subselect[mode][0]][4] & 0x10) {
							x += width / 4;
							x -= width / 2 - 2 * v - 1;
						} else {
							x -= width / 4;
						}

						if (WSAnim[select[mode]][subselect[mode][0]][4] & 0x20) {
							y -= height / 2 - 2 * w - 1;
						}
					}
				}
			}
		}

		m = subselect[mode][1];
		int frame = subselect[mode][0];
		l = 0;

		if (frame)frame = WSAnim[select[mode]][subselect[mode][0]][0] & 0x0F;
		while (frame == 0x0F && l<subselect[mode][0]) {
			l++;
			frame = WSAnim[select[mode]][subselect[mode][0] - l][0];
		}

		l = 0;

		width = FSSize[m][frame][0];
		height = FSSize[m][frame][1];

		for (x = 0;x<width;x++) {
			for (y = 0;y<height;y++) {
				for (i = 0;i<4;i++) {
					for (j = 0;j<4;j++) {
						k = ForceSprites[m][frame][x + y*width];
						if (k<0)k = 0;

						if (AnimBorder && (!x || !y || x == width - 1 || y == height - 1))k = -1;

						v = x;

						if (frame&&WSAnim[select[mode]][subselect[mode][0]][0] & 0x10) {
							x += width - 2 * v - 1;
						}

						if(k==-1)SetPixel(memdc, x * 4 + i + 225 + dwidth / 2 + dx, y * 4 + j + 67 + dy, RGB(0,0,255));
						else if (k)SetPixel(memdc, x * 4 + i + 225 + dwidth / 2 + dx, y * 4 + j + 67 + dy, RGB(FSPalette[m][l][k][0], FSPalette[m][l][k][1], FSPalette[m][l][k][2]));

						if (frame&&WSAnim[select[mode]][subselect[mode][0]][0] & 0x10) {
							x -= width - 2 * v - 1;
						}
					}
				}
			}
		}

		SelectObject(bmpdc,minus);
		BitBlt(memdc,55,8,20,20,bmpdc,0,0,SRCCOPY);

		sprintf(out,"Animation: %d",select[mode]);
		if(focus==1&&cursor)sprintf(out,"%s|",out);
		TextOut(memdc,76,10,out,strlen(out));

		SelectObject(bmpdc,plus);
		BitBlt(memdc,171,8,20,20,bmpdc,0,0,SRCCOPY);

		SelectObject(bmpdc,minus);
		BitBlt(memdc,201,8,20,20,bmpdc,0,0,SRCCOPY);

		sprintf(out,"Frame: %d",subselect[mode][0]);
		if(focus==2&&cursor)sprintf(out,"%s|",out);
		TextOut(memdc,222,10,out,strlen(out));

		SelectObject(bmpdc,plus);
		BitBlt(memdc,292,8,20,20,bmpdc,0,0,SRCCOPY);

		if (NumAnim < 256) {
			Rectangle(memdc, 330, 3, 434, 33);
			TextOut(memdc, 352, 10, "Add Anim", 8);
		}

		if (NumAnim) {
			Rectangle(memdc, 454, 3, 558, 33);
			TextOut(memdc, 461, 10, "Remove Anim", 11);
		}

		if(WSAnim[select[mode]][0][0]!=0xFF)
			sprintf(out,"# of Frames: %d",WSAnim[select[mode]][0][0]+1);
		else
			sprintf(out, "# of Frames:0");
		if(focus==3&&cursor)sprintf(out,"%s|",out);
		TextOut(memdc,60,40,out,strlen(out));

		if(focus==4&&editneg)sprintf(out,"Effect: -");
		else sprintf(out,"Effect: %d",WSAnim[select[mode]][0][2]);
		if(focus==4&&cursor)sprintf(out,"%s|",out);
		TextOut(memdc,60,60,out,strlen(out));

		sprintf(out,"?: %d",WSAnim[select[mode]][0][1]);
		if(focus==5&&cursor)sprintf(out,"%s|",out);
		TextOut(memdc,60,80,out,strlen(out));

		sprintf(out,"?: %d",WSAnim[select[mode]][0][3]);
		if(focus==6&&cursor)sprintf(out,"%s|",out);
		TextOut(memdc,60,100,out,strlen(out));

		if(subselect[mode][0]){
			sprintf(out,"Length: %d",(unsigned char)WSAnim[select[mode]][subselect[mode][0]][1]);
			if(focus==7&&cursor)sprintf(out,"%s|",out);
			TextOut(memdc,60,140,out,strlen(out));
		}

		sprintf(out,"Weapon");
		TextOut(memdc,60,180,out,strlen(out));

		sprintf(out,"Graphic: %d",WSAnim[select[mode]][subselect[mode][0]][4]&0x0F);
		if(focus==8&&cursor)sprintf(out,"%s|",out);
		TextOut(memdc,60,220,out,strlen(out));

		if(focus==9&&editneg)sprintf(out,"X: -");
		else sprintf(out,"X: %d",WSAnim[select[mode]][subselect[mode][0]][6]);
		if(focus==9&&cursor)sprintf(out,"%s|",out);
		TextOut(memdc,60,240,out,strlen(out));

		if(focus==10&&editneg)sprintf(out,"Y: -");
		else sprintf(out,"Y: %d",WSAnim[select[mode]][subselect[mode][0]][7]);
		if(focus==10&&cursor)sprintf(out,"%s|",out);
		TextOut(memdc,60,260,out,strlen(out));

		if(WSAnim[select[mode]][subselect[mode][0]][4]&0x10)SelectObject(bmpdc,checkon);
		else SelectObject(bmpdc,checkoff);
		BitBlt(memdc,60,280,13,13,bmpdc,0,0,SRCCOPY);

		sprintf(out,"X Flip");
		TextOut(memdc,80,280,out,strlen(out));

		if(WSAnim[select[mode]][subselect[mode][0]][4]&0x20)SelectObject(bmpdc,checkon);
		else SelectObject(bmpdc,checkoff);
		BitBlt(memdc,60,300,13,13,bmpdc,0,0,SRCCOPY);

		sprintf(out,"Y Flip");
		TextOut(memdc,80,300,out,strlen(out));

		if(subselect[mode][0]){

			sprintf(out,"Character");
			TextOut(memdc,60,340,out,strlen(out));

			sprintf(out,"Graphic: %d",WSAnim[select[mode]][subselect[mode][0]][0]&0x0F);
			if(focus==11&&cursor)sprintf(out,"%s|",out);
			TextOut(memdc,60,380,out,strlen(out));

			if(focus==12&&editneg)sprintf(out,"X: -");
			sprintf(out,"X: %d",WSAnim[select[mode]][subselect[mode][0]][2]);
			if(focus==12&&cursor)sprintf(out,"%s|",out);
			TextOut(memdc,60,400,out,strlen(out));

			if(focus==13&&editneg)sprintf(out,"Y: -");
			sprintf(out,"Y: %d",WSAnim[select[mode]][subselect[mode][0]][3]);
			if(focus==13&&cursor)sprintf(out,"%s|",out);
			TextOut(memdc,60,420,out,strlen(out));

			if(WSAnim[select[mode]][subselect[mode][0]][0]&0x10)SelectObject(bmpdc,checkon);
			else SelectObject(bmpdc,checkoff);
			BitBlt(memdc,60,440,13,13,bmpdc,0,0,SRCCOPY);

			sprintf(out,"X Flip");
			TextOut(memdc,80,440,out,strlen(out));

			/*
			if(WSAnim[select[mode]][subselect[mode][0]][0]&0x20)SelectObject(bmpdc,checkon);
			else SelectObject(bmpdc,checkoff);
			BitBlt(memdc,60,460,13,13,bmpdc,0,0,SRCCOPY);

			sprintf(out,"Y Flip");
			TextOut(memdc,80,460,out,strlen(out));
			*/

		}


		SelectObject(bmpdc,minus);
		BitBlt(memdc,dwidth+645,80,20,20,bmpdc,0,0,SRCCOPY);

		sprintf(out,"Character: %d",subselect[mode][1]);
		if(focus==14&&cursor)sprintf(out,"%s|",out);
		TextOut(memdc,dwidth+666,82,out,strlen(out));

		SelectObject(bmpdc,plus);
		BitBlt(memdc,dwidth+761,80,20,20,bmpdc,0,0,SRCCOPY);


		SelectObject(bmpdc,minus);
		BitBlt(memdc,dwidth+645,100,20,20,bmpdc,0,0,SRCCOPY);

		sprintf(out,"Weapon: %d",subselect[mode][2]);
		if(focus==15&&cursor)sprintf(out,"%s|",out);
		TextOut(memdc,dwidth+666,102,out,strlen(out));

		SelectObject(bmpdc,plus);
		BitBlt(memdc,dwidth+761,100,20,20,bmpdc,0,0,SRCCOPY);

		
		GetCursorPos(&p);
		ScreenToClient(hWnd, &p);
		p.y -= 40;

		if (!menu) {
			//PatBlt(memdc, 10, 560, 150, 20, PATCOPY);
			if (p.x >= -238 + dwidth / 2 && p.x <= 789 + dwidth / 2 && p.y >= 36 && p.y <= 499) {
				x = (p.x - (-238 + dwidth / 2));
				y = (p.y - 36);
				sprintf(out, "%d, %d", (x - x % 4) / 4, (y - y % 4) / 4);
				TextOut(memdc, 10, 520, out, strlen(out));
			}
			//BitBlt(hdc, 10, 560, 150, 20, memdc, 10, 560, SRCCOPY);
		}

		TextOut(memdc, 100, 520, "Show Outlines:", 14);

		if (AnimBorder)SelectObject(bmpdc, checkon);
		else SelectObject(bmpdc, checkoff);
		BitBlt(memdc, 200, 522, 13, 13, bmpdc, 0, 0, SRCCOPY);

	}
}

if(submode[mode]==1){
	SelectObject(bmpdc,minus);
	BitBlt(memdc,55,8,20,20,bmpdc,0,0,SRCCOPY);

	sprintf(out,"Sprite: %d",select[mode]);
	if(focus==1&&cursor)sprintf(out,"%s|",out);
	TextOut(memdc,76,10,out,strlen(out));

	SelectObject(bmpdc,plus);
	BitBlt(memdc,171,8,20,20,bmpdc,0,0,SRCCOPY);

	j=1;

	TextOut(memdc,200,40,"Equipped",8);
	TextOut(memdc,200,60,"Weapon Type",11);

	TextOut(memdc,300,60,"Animation",9);

	TextOut(memdc,400,40,"Display",7);
	TextOut(memdc,400,60,"Weapon Type",11);

	while(AnimSets[select[mode]][j]!=0xFF){
		sprintf(out,"%d",AnimSets[select[mode]][j++]);
		if(focus==3+(j+1)/3&&subfocus==0&&cursor)sprintf(out,"%s|",out);
		TextOut(memdc, 200, 60+18*((j+1)/3), out, strlen(out));
		sprintf(out,"%d",AnimSets[select[mode]][j++]);
		if(focus==3+(j)/3&&subfocus==1&&cursor)sprintf(out,"%s|",out);
		TextOut(memdc, 300, 60+18*((j)/3), out, strlen(out));
		sprintf(out,"%d",AnimSets[select[mode]][j++]);
		if(focus==3+(j-1)/3&&subfocus==2&&cursor)sprintf(out,"%s|",out);
		TextOut(memdc, 400, 60+18*((j-1)/3), out, strlen(out));
	}

	if(j<73){
		Rectangle(memdc,60,80,160,110);
		TextOut(memdc,84,87,"Add Set",7);
	}

	if(j>1){
		Rectangle(memdc,60,120,160,150);
		TextOut(memdc,70,127,"Remove Set",10);
	}

}

if (submode[mode] == 2) {
	if (!GraphicsLoaded) {
		if (strlen(file)) {
			Rectangle(memdc, 50, 30, 176, 52);
			TextOut(memdc, 55, 33, "Decompress GFX", 14);
		} else {
			TextOut(memdc, 55, 33, "Load a ROM first.", 17);
		}
	} else {

		HBRUSH temp = (HBRUSH)SelectObject(memdc, GetStockObject(NULL_BRUSH));
		HPEN tempp = (HPEN)SelectObject(memdc, CreatePen(PS_SOLID, 2, RGB(255, 200, 0)));
		Rectangle(memdc, 200-238 + dwidth / 2, 36, 200+789 + dwidth / 2, 499);
		SelectObject(memdc, temp);
		DeleteObject(SelectObject(memdc, tempp));

		m = subselect[mode][1];
		int frame = subselect[mode][0];
		l = 0;

		if (frame)frame = EAnim[select[mode]][subselect[mode][0]][0] & 0x0F;
		while (frame == 0x0F && l<subselect[mode][0]) {
			l++;
			frame = EAnim[select[mode]][subselect[mode][0] - l][0];
		}

		l = 0;

		width = ESSize[m][frame][0];
		height = ESSize[m][frame][1];

		if (subselect[mode][0]) {
			dx = EAnim[select[mode]][subselect[mode][0]][2] * 4 + 80;
			dy = EAnim[select[mode]][subselect[mode][0]][3] * 4;
		} else {
			dx = 80;
			dy = 0;
		}

		for (x = 0; x<width; x++) {
			for (y = 0; y<height; y++) {
				for (i = 0; i<4; i++) {
					for (j = 0; j<4; j++) {
						k = EnemySprites[m][frame][x + y*width];
						if (k<0)k = 0;

						if (AnimBorder && (!x || !y || x == width - 1 || y == height - 1))k = -1;

						v = x;

						if (frame&&EAnim[select[mode]][subselect[mode][0]][0] & 0x10) {
							x += width - 2 * v - 1;
						}

						if (k == -1)SetPixel(memdc,200 + x * 4 + i - 255 + dwidth / 2 + dx, y * 4 + j + 67 + dy, RGB(0, 0, 255));
						else if (k)SetPixel(memdc, 200 + x * 4 + i - 255 + dwidth / 2 + dx, y * 4 + j + 67 + dy, RGB(ESPalette[m][l][k][0], ESPalette[m][l][k][1], ESPalette[m][l][k][2]));

						if (frame&&EAnim[select[mode]][subselect[mode][0]][0] & 0x10) {
							x -= width - 2 * v - 1;
						}
					}
				}
			}
		}

		SelectObject(bmpdc, minus);
		BitBlt(memdc, 55, 8, 20, 20, bmpdc, 0, 0, SRCCOPY);

		sprintf(out, "Animation: %d", select[mode]);
		if (focus == 1 && cursor)sprintf(out, "%s|", out);
		TextOut(memdc, 76, 10, out, strlen(out));

		SelectObject(bmpdc, plus);
		BitBlt(memdc, 171, 8, 20, 20, bmpdc, 0, 0, SRCCOPY);

		SelectObject(bmpdc, minus);
		BitBlt(memdc, 201, 8, 20, 20, bmpdc, 0, 0, SRCCOPY);

		sprintf(out, "Frame: %d", subselect[mode][0]);
		if (focus == 2 && cursor)sprintf(out, "%s|", out);
		TextOut(memdc, 222, 10, out, strlen(out));

		SelectObject(bmpdc, plus);
		BitBlt(memdc, 292, 8, 20, 20, bmpdc, 0, 0, SRCCOPY);

		if (NumEAnim < 256) {
			Rectangle(memdc, 330, 3, 434, 33);
			TextOut(memdc, 352, 10, "Add Anim", 8);
		}

		if (NumEAnim) {
			Rectangle(memdc, 454, 3, 558, 33);
			TextOut(memdc, 461, 10, "Remove Anim", 11);
		}

		sprintf(out, "# of Frames: %d", EAnim[select[mode]][0][0] + 1);
		if (focus == 3 && cursor)sprintf(out, "%s|", out);
		TextOut(memdc, 60, 40, out, strlen(out));

		if (focus == 4 && editneg)sprintf(out, "Effect: -");
		else sprintf(out, "Effect: %d", EAnim[select[mode]][0][2]);
		if (focus == 4 && cursor)sprintf(out, "%s|", out);
		TextOut(memdc, 60, 60, out, strlen(out));

		sprintf(out, "?: %d", EAnim[select[mode]][0][1]);
		if (focus == 5 && cursor)sprintf(out, "%s|", out);
		TextOut(memdc, 60, 80, out, strlen(out));

		sprintf(out, "?: %d", EAnim[select[mode]][0][3]);
		if (focus == 6 && cursor)sprintf(out, "%s|", out);
		TextOut(memdc, 60, 100, out, strlen(out));

		if (subselect[mode][0]) {
			sprintf(out, "Length: %d", (unsigned char)EAnim[select[mode]][subselect[mode][0]][1]);
			if (focus == 7 && cursor)sprintf(out, "%s|", out);
			TextOut(memdc, 60, 140, out, strlen(out));
		}

		if (subselect[mode][0]) {

			sprintf(out, "Character");
			TextOut(memdc, 60, 340, out, strlen(out));

			sprintf(out, "Graphic: %d", EAnim[select[mode]][subselect[mode][0]][0] & 0x0F);
			if (focus == 11 && cursor)sprintf(out, "%s|", out);
			TextOut(memdc, 60, 380, out, strlen(out));

			if (focus == 12 && editneg)sprintf(out, "X: -");
			sprintf(out, "X: %d", EAnim[select[mode]][subselect[mode][0]][2]);
			if (focus == 12 && cursor)sprintf(out, "%s|", out);
			TextOut(memdc, 60, 400, out, strlen(out));

			if (focus == 13 && editneg)sprintf(out, "Y: -");
			sprintf(out, "Y: %d", EAnim[select[mode]][subselect[mode][0]][3]);
			if (focus == 13 && cursor)sprintf(out, "%s|", out);
			TextOut(memdc, 60, 420, out, strlen(out));

			if (EAnim[select[mode]][subselect[mode][0]][0] & 0x10)SelectObject(bmpdc, checkon);
			else SelectObject(bmpdc, checkoff);
			BitBlt(memdc, 60, 440, 13, 13, bmpdc, 0, 0, SRCCOPY);

			sprintf(out, "X Flip");
			TextOut(memdc, 80, 440, out, strlen(out));

			/*
			if(WSAnim[select[mode]][subselect[mode][0]][0]&0x20)SelectObject(bmpdc,checkon);
			else SelectObject(bmpdc,checkoff);
			BitBlt(memdc,60,460,13,13,bmpdc,0,0,SRCCOPY);

			sprintf(out,"Y Flip");
			TextOut(memdc,80,460,out,strlen(out));
			*/

		}


		SelectObject(bmpdc, minus);
		BitBlt(memdc, dwidth + 645, 80, 20, 20, bmpdc, 0, 0, SRCCOPY);

		sprintf(out, "Character: %d", subselect[mode][1]);
		if (focus == 14 && cursor)sprintf(out, "%s|", out);
		TextOut(memdc, dwidth + 666, 82, out, strlen(out));

		SelectObject(bmpdc, plus);
		BitBlt(memdc, dwidth + 761, 80, 20, 20, bmpdc, 0, 0, SRCCOPY);

		GetCursorPos(&p);
		ScreenToClient(hWnd, &p);
		p.y -= 40;

		if (!menu) {
			//PatBlt(memdc, 10, 560, 150, 20, PATCOPY);
			if (p.x >= -238 + dwidth / 2 && p.x <= 789 + dwidth / 2 && p.y >= 36 && p.y <= 499) {
				x = (p.x - (-238 + dwidth / 2));
				y = (p.y - 36);
				sprintf(out, "%d, %d", (x - x % 4) / 4, (y - y % 4) / 4);
				TextOut(memdc, 10, 520, out, strlen(out));
			}
			//BitBlt(hdc, 10, 560, 150, 20, memdc, 10, 560, SRCCOPY);
		}

		TextOut(memdc, 100, 520, "Show Outlines:", 14);

		if (AnimBorder)SelectObject(bmpdc, checkon);
		else SelectObject(bmpdc, checkoff);
		BitBlt(memdc, 200, 522, 13, 13, bmpdc, 0, 0, SRCCOPY);

	}
}

if (submode[mode] == 3) {
	SelectObject(bmpdc, minus);
	BitBlt(memdc, 55, 8, 20, 20, bmpdc, 0, 0, SRCCOPY);

	sprintf(out, "Sprite: %d", select[mode]);
	if (focus == 1 && cursor)sprintf(out, "%s|", out);
	TextOut(memdc, 76, 10, out, strlen(out));

	SelectObject(bmpdc, plus);
	BitBlt(memdc, 171, 8, 20, 20, bmpdc, 0, 0, SRCCOPY);

	j = 1;

	TextOut(memdc, 200, 40, "Equipped", 8);
	TextOut(memdc, 200, 60, "Weapon Type", 11);

	TextOut(memdc, 300, 60, "Animation", 9);

	TextOut(memdc, 400, 40, "Display", 7);
	TextOut(memdc, 400, 60, "Weapon Type", 11);

	while (EAnimSets[select[mode]][j] != 0xFF) {
		sprintf(out, "%d", EAnimSets[select[mode]][j++]);
		if (focus == 3 + (j + 1) / 3 && subfocus == 0 && cursor)sprintf(out, "%s|", out);
		TextOut(memdc, 200, 60 + 18 * ((j + 1) / 3), out, strlen(out));
		sprintf(out, "%d", EAnimSets[select[mode]][j++]);
		if (focus == 3 + (j) / 3 && subfocus == 1 && cursor)sprintf(out, "%s|", out);
		TextOut(memdc, 300, 60 + 18 * ((j) / 3), out, strlen(out));
		sprintf(out, "%d", EAnimSets[select[mode]][j++]);
		if (focus == 3 + (j - 1) / 3 && subfocus == 2 && cursor)sprintf(out, "%s|", out);
		TextOut(memdc, 400, 60 + 18 * ((j - 1) / 3), out, strlen(out));
	}

	if (j<73) {
		Rectangle(memdc, 60, 80, 160, 110);
		TextOut(memdc, 84, 87, "Add Set", 7);
	}

	if (j>1) {
		Rectangle(memdc, 60, 120, 160, 150);
		TextOut(memdc, 70, 127, "Remove Set", 10);
	}

}

if (submode[mode] == 4) {
	#include "SpellAnimPaint.h"
}

if (submode[mode] == 5) {
	SelectObject(bmpdc, minus);
	BitBlt(memdc, 55, 8, 20, 20, bmpdc, 0, 0, SRCCOPY);

	sprintf(out, "Force: %d", select[mode]);
	if (focus == 1 && cursor)sprintf(out, "%s|", out);
	TextOut(memdc, 76, 10, out, strlen(out));

	SelectObject(bmpdc, plus);
	BitBlt(memdc, 171, 8, 20, 20, bmpdc, 0, 0, SRCCOPY);

	SelectObject(bmpdc, minus);
	BitBlt(memdc, 201, 8, 20, 20, bmpdc, 0, 0, SRCCOPY);

	sprintf(out, "Entry: %d", subselect[mode][0]);
	if (focus == 2 && cursor)sprintf(out, "%s|", out);
	TextOut(memdc, 222, 10, out, strlen(out));

	SelectObject(bmpdc, plus);
	BitBlt(memdc, 292, 8, 20, 20, bmpdc, 0, 0, SRCCOPY);


	sprintf(out, "Character: %d", EndingForce[select[mode]][0]);
	if (focus == 3 && cursor)sprintf(out, "%s|", out);
	TextOut(memdc, 76, 50, out, strlen(out));

	sprintf(out, "Class: %d", EndingForce[select[mode]][1]);
	if (focus == 4 && cursor)sprintf(out, "%s|", out);
	TextOut(memdc, 76, 70, out, strlen(out));

	sprintf(out, "Weapon: %d", EndingForce[select[mode]][2]);
	if (focus == 5 && cursor)sprintf(out, "%s|", out);
	TextOut(memdc, 76, 90, out, strlen(out));





	sprintf(out, "Force Member: %d", EndingScenes[subselect[mode][0]][0]);
	if (focus == 6 && cursor)sprintf(out, "%s|", out);
	TextOut(memdc, 222, 50, out, strlen(out));

	sprintf(out, "Enemy: %d", EndingScenes[subselect[mode][0]][1]);
	if (focus == 7 && cursor)sprintf(out, "%s|", out);
	TextOut(memdc, 222, 70, out, strlen(out));

	sprintf(out, "Animation: %d", EndingScenes[subselect[mode][0]][2]);
	if (focus == 8 && cursor)sprintf(out, "%s|", out);
	TextOut(memdc, 222, 90, out, strlen(out));

	sprintf(out, "Effect: %d", EndingScenes[subselect[mode][0]][3]);
	if (focus == 9 && cursor)sprintf(out, "%s|", out);
	TextOut(memdc, 222, 110, out, strlen(out));
}

if (GraphicsLoaded) {
	if (submode[mode] == 0)SelectObject(bmpdc, charaon);
	else SelectObject(bmpdc, chara);
	BitBlt(memdc, 0, 35, 40, 40, bmpdc, 0, 0, SRCCOPY);
	if (submode[mode] == 1)SelectObject(bmpdc, liston);
	else SelectObject(bmpdc, list);
	BitBlt(memdc, 0, 75, 40, 40, bmpdc, 0, 0, SRCCOPY);

	if (submode[mode] == 2)SelectObject(bmpdc, monsteron);
	else SelectObject(bmpdc, monster);
	BitBlt(memdc, 0, 115, 40, 40, bmpdc, 0, 0, SRCCOPY);
	if (submode[mode] == 3)SelectObject(bmpdc, liston);
	else SelectObject(bmpdc, list);
	BitBlt(memdc, 0, 155, 40, 40, bmpdc, 0, 0, SRCCOPY);


	if (submode[mode] == 5)SelectObject(bmpdc, animon);
	else SelectObject(bmpdc, anim);
	BitBlt(memdc, 0, 235, 40, 40, bmpdc, 0, 0, SRCCOPY);
}