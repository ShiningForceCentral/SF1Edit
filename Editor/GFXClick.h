if(!GraphicsLoaded&&strlen(file)){
	if(p.x>=50&&p.x<=176&&p.y>=30&&p.y<=52){
		LoadGFX(file);
	}
}

if(GraphicsLoaded){

	if (menu == 1) {

		for (int i = 0; i<(NUM_SOUNDS-69) / 3; i++) {

			if (p.x >= 50 && p.x <= dwidth + 50 + 200 && p.y >= 28 + i * 14 && p.y <= 28 + (i + 1) * 14) {

				MSTextSound[subselect[mode][submode[mode]]] = i + 1;

			}

			if (p.x >= 50 + 200 && p.x <= 50 + 400 && p.y >= 28 + i * 14 && p.y <= 28 + (i + 1) * 14) {

				MSTextSound[subselect[mode][submode[mode]]] = i + (NUM_SOUNDS - 69) / 3 + 1;

			}

			if (p.x >= 50 + 400 && p.x <= 50 + 600 && p.y >= 28 + i * 14 && p.y <= 28+ (i + 1) * 14) {

				MSTextSound[subselect[mode][submode[mode]]] = i + 2 * (NUM_SOUNDS - 69) / 3 + 1;

			}
		}

		menu = 0;
		return 0;
	}

	if (p.x >= 764 && p.x <= 777 && p.y >= 11 && p.y < 24) {
		GFXBG = !GFXBG;

		if (GFXBG) {
			WritePrivateProfileString("settings", "showbg", "1", inipath);
		} else {
			WritePrivateProfileString("settings", "showbg", "0", inipath);
		}
	}

	if (romsize >= 0x600000)
	if (p.x >= 764 && p.x <= 777 && p.y >= 502 && p.y < 515) {
		ExpandedGraphics = !ExpandedGraphics;
		GFXPaletteEdit = true;
		GFXSpace[31] = 0;
	}


	if(p.x>=0&&p.x<=40&&p.y>=35&&p.y<75){
		submode[mode]=0;
		subselect[mode][submode[mode]]=0;
		subselect[mode][submode[mode]+32]=0;
		subselect[mode][submode[mode]+64]=0;
	}
	if(p.x>=0&&p.x<=40&&p.y>=75&&p.y<115){
		submode[mode]=1;
		subselect[mode][submode[mode]]=0;
		subselect[mode][submode[mode]+32]=0;
		subselect[mode][submode[mode]+64]=0;
	}
	if(p.x>=0&&p.x<=40&&p.y>=115&&p.y<155){
		submode[mode]=2;
		subselect[mode][submode[mode]]=0;
		subselect[mode][submode[mode]+32]=0;
		subselect[mode][submode[mode]+64]=findWSPalette(subselect[mode][submode[mode]]);
	}
	if(p.x>=0&&p.x<=40&&p.y>=155&&p.y<195){
		submode[mode]=3;
		subselect[mode][submode[mode]]=0;
		subselect[mode][submode[mode]+32]=0;
		subselect[mode][submode[mode]+64]=0;
	}
	if(p.x>=0&&p.x<=40&&p.y>=195&&p.y<235){
		submode[mode]=4;
		subselect[mode][submode[mode]]=0;
		subselect[mode][submode[mode]+32]=0;
		subselect[mode][submode[mode]+64]=0;
	}
	if(p.x>=0&&p.x<=40&&p.y>=235&&p.y<275){
		submode[mode]=5;
		subselect[mode][submode[mode]]=0;
		subselect[mode][submode[mode]+32]=0;
		subselect[mode][submode[mode]+64]=0;
	}
	if(p.x>=0&&p.x<=40&&p.y>=275&&p.y<315){
		submode[mode]=6;
		subselect[mode][submode[mode]]=0;
		subselect[mode][submode[mode]+32]=0;
		subselect[mode][submode[mode]+64]=0;
	}
	if(p.x>=0&&p.x<=40&&p.y>=315&&p.y<355){
		submode[mode]=7;
		subselect[mode][submode[mode]]=0;
		subselect[mode][submode[mode]+32]=0;
		subselect[mode][submode[mode]+64]=0;
	}
	if(p.x>=0&&p.x<=40&&p.y>=355&&p.y<395){
		submode[mode]=8;
		subselect[mode][submode[mode]]=0;
		subselect[mode][submode[mode]+32]=0;
		subselect[mode][submode[mode]+64]=0;
	}
	if(p.x>=0&&p.x<=40&&p.y>=395&&p.y<435){
		submode[mode]=9;
		subselect[mode][submode[mode]]=0;
		subselect[mode][submode[mode]+32]=0;
		subselect[mode][submode[mode]+64]=0;
	}

	if(p.x>=76&&p.x<=145&&p.y>=10&&p.y<=25){
		focus=1;
	}

	if(p.x>=55&&p.x<=75&&p.y>=8&&p.y<=28){
		subselect[mode][submode[mode]]--;
		if(subselect[mode][submode[mode]]<0)subselect[mode][submode[mode]]=NumGFX[submode[mode]]-1;
		subselect[mode][submode[mode]+32]=0;
		subselect[mode][submode[mode]+64]=0;
		if(submode[mode]==2)subselect[mode][submode[mode]+64]=findWSPalette(subselect[mode][submode[mode]]);
		subselect[mode][submode[mode] + 128] = 0;
	}

	if(p.x>=146&&p.x<=166&&p.y>=8&&p.y<=28){
		subselect[mode][submode[mode]]++;
		subselect[mode][submode[mode]]%=NumGFX[submode[mode]];
		subselect[mode][submode[mode]+32]=0;
		subselect[mode][submode[mode]+64]=0;
		if(submode[mode]==2)subselect[mode][submode[mode]+64]=findWSPalette(subselect[mode][submode[mode]]);
		subselect[mode][submode[mode] + 128] = 0;
	}


	if(submode[mode]==0&&NumGFX[0]<80){
		if(p.x>=100&&p.x<=200&&p.y>=460&&p.y<=490){
			NumGFX[0]++;



			for(i=0;i<8;i++){
				for(k=0;k<12288;k++){
					ForceSprites[NumGFX[0]-1][i][k] = 0;
				}
				FSSize[NumGFX[0]-1][i][0] = 96;
				FSSize[NumGFX[0]-1][i][1] = 96;

				for(k=0;k<16;k++){
					FSPalette[NumGFX[0]-1][i][k][0]=FSPalette[subselect[mode][submode[mode]]][i][k][0];
					FSPalette[NumGFX[0]-1][i][k][1]=FSPalette[subselect[mode][submode[mode]]][i][k][1];
					FSPalette[NumGFX[0]-1][i][k][2]=FSPalette[subselect[mode][submode[mode]]][i][k][2];
				}
			}

			subselect[mode][submode[mode]]=NumGFX[0]-1;
			subselect[mode][submode[mode]+32]=0;
			subselect[mode][submode[mode]+64]=0;

			NumFSFrame[NumGFX[0]-1]=1;

			NumFSPalette[NumGFX[0]-1]=1;

			for (i = NumAnimSet; i < NumGFX[0]; i++)AnimSets[i][1] = 0xFF;

			NumAnimSet = NumGFX[0];
		}
	}

	if(submode[mode]==0&&NumGFX[0]>35){
		if(p.x>=100&&p.x<=200&&p.y>=500&&p.y<=530){
			NumGFX[0]--;
			NumAnimSet = NumGFX[0];
		}
	}

	if (submode[mode] == 0 && NumFSFrame[subselect[mode][submode[mode]]] > 1) {
		if (p.x >= 240 && p.x <= 340 && p.y >= 500 && p.y <= 530) {
			NumFSFrame[subselect[mode][submode[mode]]]--;
		}
	}

	if(submode[mode]==0&&NumFSFrame[subselect[mode][submode[mode]]]<8){
		if(p.x>=240&&p.x<=340&&p.y>=460&&p.y<=490){
			NumFSFrame[subselect[mode][submode[mode]]]++;
			subselect[mode][submode[mode]+32] = NumFSFrame[subselect[mode][submode[mode]]]-1;

			FSSize[subselect[mode][submode[mode]]][subselect[mode][submode[mode]+32]][0] = 96;
			FSSize[subselect[mode][submode[mode]]][subselect[mode][submode[mode]+32]][1] = 96;
		}
	}

	if (submode[mode] == 0 && NumFSPalette[subselect[mode][submode[mode]]] < 8) {
		if (p.x >= 380 && p.x <= 480 && p.y >= 460 && p.y <= 490) {
			NumFSPalette[subselect[mode][submode[mode]]]++;
		}
	}

	if (submode[mode] == 0 && NumFSPalette[subselect[mode][submode[mode]]] > 1) {
		if (p.x >= 380 && p.x <= 480 && p.y >= 500 && p.y <= 530) {
			NumFSPalette[subselect[mode][submode[mode]]]--;
		}
	}
	
	if (submode[mode] == 1 && NumGFX[1]<80) {
		if (p.x >= 100 && p.x <= 200 && p.y >= 460 && p.y <= 490) {
			NumGFX[1]++;



			for (i = 0;i<8;i++) {
				for (k = 0;k<12288;k++) {
					EnemySprites[NumGFX[1] - 1][i][k] = 0;
				}
				ESSize[NumGFX[1] - 1][i][0] = 128;
				ESSize[NumGFX[1] - 1][i][1] = 96;

				for (k = 0;k<16;k++) {
					ESPalette[NumGFX[1] - 1][i][k][0] = ESPalette[subselect[mode][submode[mode]]][i][k][0];
					ESPalette[NumGFX[1] - 1][i][k][1] = ESPalette[subselect[mode][submode[mode]]][i][k][1];
					ESPalette[NumGFX[1] - 1][i][k][2] = ESPalette[subselect[mode][submode[mode]]][i][k][2];
				}
			}

			subselect[mode][submode[mode]] = NumGFX[1] - 1;
			subselect[mode][submode[mode] + 32] = 0;
			subselect[mode][submode[mode] + 64] = 0;

			NumESFrame[NumGFX[1] - 1] = 1;

			NumESPalette[NumGFX[1] - 1] = 1;

			for (i = NumEAnimSet; i < NumGFX[1]; i++) {
				for(int q=0;q<256;q++)EAnimSets[i][q] = 0xFF;
			}
			NumEAnimSet = NumGFX[1];
		}
	}

	if (submode[mode] == 1 && NumGFX[1]>50) {
		if (p.x >= 100 && p.x <= 200 && p.y >= 500 && p.y <= 530) {
			NumGFX[1]--;
			NumEAnimSet = NumGFX[1];
			subselect[mode][submode[mode]] %= NumGFX[submode[mode]];
		}
	}

	if (submode[mode] == 2 && NumGFX[2]<64) {
		if (p.x >= 100 && p.x <= 200 && p.y >= 460 && p.y <= 490) {
			NumGFX[2]++;



			for (i = 0; i<6; i++) {
				for (k = 0; k<12288; k++) {
					WeaponSprites[NumGFX[2] - 1][i][k] = 0;
				}
				WSSize[NumGFX[2] - 1][i][0] = 128;
				WSSize[NumGFX[2] - 1][i][1] = 128;

			}

			WSRepeat[NumGFX[2] - 1] = 1;

			subselect[mode][submode[mode]] = NumGFX[2] - 1;
			subselect[mode][submode[mode] + 32] = 0;
			subselect[mode][submode[mode] + 64] = 0;
		}
	}

	if (submode[mode] == 2 && NumGFX[2]>15) {
		if (p.x >= 100 && p.x <= 200 && p.y >= 500 && p.y <= 530) {
			NumGFX[2]--;
			subselect[mode][submode[mode]] %= NumGFX[submode[mode]];
		}
	}

	if (submode[mode] == 1 && NumESFrame[subselect[mode][submode[mode]]]>1) {
		if (p.x >= 240 && p.x <= 340 && p.y >= 500 && p.y <= 530) {
			NumESFrame[subselect[mode][submode[mode]]]--;
		}
	}

	if (submode[mode] == 1 && NumESFrame[subselect[mode][submode[mode]]]<8) {
		if (p.x >= 240 && p.x <= 340 && p.y >= 460 && p.y <= 490) {
			NumESFrame[subselect[mode][submode[mode]]]++;
			subselect[mode][submode[mode] + 32] = NumESFrame[subselect[mode][submode[mode]]] - 1;
			subselect[mode][submode[mode] + 128] = 0;

			ESSize[subselect[mode][submode[mode]]][subselect[mode][submode[mode] + 32]][0] = 128;
			ESSize[subselect[mode][submode[mode]]][subselect[mode][submode[mode] + 32]][1] = 96;
		}
	}

	if (submode[mode] == 6 && NumGFX[6]<128) {
		if (p.x >= 100 && p.x <= 200 && p.y >= 460 && p.y <= 490) {
			NumGFX[6]++;

			subselect[mode][submode[mode] + 128] = 0;


			for (k = 0;k<12288;k++) {
				Portraits[NumGFX[6] - 1][k] = 0;
			}
			POSize[NumGFX[6] - 1][0] = 64;
			POSize[NumGFX[6] - 1][1] = 64;

			for (k = 0;k<16;k++) {
				POPalette[NumGFX[6] - 1][k][0] = POPalette[subselect[mode][submode[mode]]][k][0];
				POPalette[NumGFX[6] - 1][k][1] = POPalette[subselect[mode][submode[mode]]][k][1];
				POPalette[NumGFX[6] - 1][k][2] = POPalette[subselect[mode][submode[mode]]][k][2];
			}


			subselect[mode][submode[mode]] = NumGFX[6] - 1;
			subselect[mode][submode[mode] + 32] = 0;
			subselect[mode][submode[mode] + 64] = 0;
		}
	}

	if (submode[mode] == 6 && NumGFX[6]>52) {
		if (p.x >= 100 && p.x <= 200 && p.y >= 500 && p.y <= 530) {
			NumGFX[6]--;
			subselect[mode][submode[mode]] %= NumGFX[submode[mode]];
			subselect[mode][submode[mode] + 128] = 0;
		}
	}



	if (submode[mode] == 7 && NumGFX[7]<256) {
		if (p.x >= 100 && p.x <= 200 && p.y >= 460 && p.y <= 490) {
			NumGFX[7]++;



			for (i = 0;i<8;i++) {
				for (k = 0;k<12288;k++) {
					MapSprites[NumGFX[7] - 1][i][k] = 0;
				}
				MSSize[NumGFX[7] - 1][i][0] = 48;
				MSSize[NumGFX[7] - 1][i][1] = 24;

			}

			subselect[mode][submode[mode]] = NumGFX[7] - 1;
			subselect[mode][submode[mode] + 32] = 0;
			subselect[mode][submode[mode] + 64] = 0;

		}
	}

	if (submode[mode] == 7 && NumGFX[7]>160) {
		if (p.x >= 100 && p.x <= 200 && p.y >= 500 && p.y <= 530) {
			NumGFX[7]--;
			subselect[mode][submode[mode]] %= NumGFX[submode[mode]];
		}
	}

	if (submode[mode] == 7) {
		if (p.x >= 162 && p.x <= 212 && p.y >= 170 && p.y <= 190) {
			focus = 8;
		}
		if (p.x >= 190 && p.x <= 210 && p.y >= 168 && p.y <= 188) {
			menu = 1;
		}
	}

	if (submode[mode] == 7)
	if (p.x >= 277 + 18 * 17 && p.x <= 290 + 18 * 17 && p.y >= 62 && p.y <= 75) {
		ChooseMSPal = !ChooseMSPal;

		if (!ChooseMSPal)resetMSPalettes();
	}

	if (submode[mode] == 7 && ChooseMSPal)
		if (p.x >= 214 && p.x <= 227 && p.y >= 192 && p.y <= 205) {
			MSPalette[subselect[mode][submode[mode]]] = !MSPalette[subselect[mode][submode[mode]]];
		}


	if(submode[mode]<2||submode[mode]==7)
	if(p.x>=206&&p.x<=275&&p.y>=10&&p.y<=25){
		focus=2;
	}

	if(submode[mode]<2||submode[mode]==7)
	if(p.x>=185&&p.x<=205&&p.y>=8&&p.y<=28){
		subselect[mode][submode[mode]+32]--;
		if(submode[mode]==0)if(subselect[mode][submode[mode]+32]<0)subselect[mode][submode[mode]+32]=NumFSFrame[subselect[mode][submode[mode]]]-1;
		if(submode[mode]==1)if(subselect[mode][submode[mode]+32]<0)subselect[mode][submode[mode]+32]=NumESFrame[subselect[mode][submode[mode]]]-1;
		if(submode[mode]==7)if(subselect[mode][submode[mode]+32]<0)subselect[mode][submode[mode]+32]=NumMSFrame-1;
		subselect[mode][submode[mode] + 128] = 0;
	}

	int t;

	if (submode[mode] == 6){

		if (p.x >= 490 && p.x <= 503 && p.y >= 170 && p.y <= 183) {
			AnimGrid = !AnimGrid;
		}


		if (p.x >= 548 && p.x <= 652 && p.y >= 88 && p.y <= 118) {
			if (subselect[mode][submode[mode] + 96] == 1) {
				if (POData[subselect[mode][submode[mode]]][1] < 8) {
					POData[subselect[mode][submode[mode]]][1]++;

					t = POData[subselect[mode][submode[mode]]][1];

					for (int q = 127;q > 5 + 4 * (t - 1);q--) {
						POData[subselect[mode][submode[mode]]][q] = POData[subselect[mode][submode[mode]]][q-4];
					}

					POData[subselect[mode][submode[mode]]][2 + 4 * (t - 1)]=0;
					POData[subselect[mode][submode[mode]]][3 + 4 * (t - 1)]=0;
					POData[subselect[mode][submode[mode]]][4 + 4 * (t - 1)]=0;
					POData[subselect[mode][submode[mode]]][5 + 4 * (t - 1)]=0;
				}
			}

			if (subselect[mode][submode[mode] + 96] == 2) {
				l = 0;
				t = POData[subselect[mode][submode[mode]]][l++] * 256;
				t += POData[subselect[mode][submode[mode]]][l++];
				for (i = 0;i < t;i++) {
					l += 4;
				}

				if (POData[subselect[mode][submode[mode]]][l+1] < 8)POData[subselect[mode][submode[mode]]][l+1]++;

				t = POData[subselect[mode][submode[mode]]][l+1];
				POData[subselect[mode][submode[mode]]][l + 2 + 4 * (t - 1)] = 0;
				POData[subselect[mode][submode[mode]]][l + 3 + 4 * (t - 1)] = 0;
				POData[subselect[mode][submode[mode]]][l + 4 + 4 * (t - 1)] = 0;
				POData[subselect[mode][submode[mode]]][l + 5 + 4 * (t - 1)] = 0;
			}
		}
		


		if (p.x >= 548 && p.x <= 652 && p.y >= 328 && p.y <= 358) {
			int dx, dy, sx, sy, l;
			l = 0;
			int t = POData[subselect[mode][submode[mode]]][l++] * 256;
			t += POData[subselect[mode][submode[mode]]][l++];
			for (i = 0; i < t; i++) {
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
			if (subselect[mode][submode[mode] + 96] == 2) {
				t = POData[subselect[mode][submode[mode]]][l++] * 256;
				t += POData[subselect[mode][submode[mode]]][l++];
				for (i = 0; i < t; i++) {
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
				char out[256];
				sprintf(out, "POTile %d %d - %d %d", sx, sy, dx, dy);

				toClipboard(out);
			}
		}

		if (p.x >= 418 && p.x <= 532 && p.y >= 328 && p.y <= 358) {
			int dx, dy, sx, sy, l;
			l = 0;
			int t = POData[subselect[mode][submode[mode]]][l++] * 256;
			t += POData[subselect[mode][submode[mode]]][l++];
			for (i = 0; i < t; i++) {
					l += 4;
			}
			if (subselect[mode][submode[mode] + 96] == 2) {
				t = POData[subselect[mode][submode[mode]]][l++] * 256;
				t += POData[subselect[mode][submode[mode]]][l++];
			}

			if (t) {
				char out[256];
				char temp[32];
				

				fromClipboard(out);

				strncpy(temp, out, 32);
				temp[6] = 0;
				if (strcmp(temp, "POTile")) {
					MessageBox(hwnd, "Incorrect format", "Error", MB_OK);
					return 0;
				}

				sscanf(out, "POTile %d %d - %d %d", &sx, &sy, &dx, &dy);

				
				l = 0;

				t = POData[subselect[mode][submode[mode]]][l++] * 256;
				t += POData[subselect[mode][submode[mode]]][l++];
				for (i = 0; i < t; i++) {
					if (i == subselect[mode][submode[mode] + 128]) {

						POData[subselect[mode][submode[mode]]][l++] = dx;
						POData[subselect[mode][submode[mode]]][l++] = dy;
						POData[subselect[mode][submode[mode]]][l++] = 0;
						POData[subselect[mode][submode[mode]]][l++] = CtoN(sx, sy);


					} else {
						l += 4;
					}
				}
				if (subselect[mode][submode[mode] + 96] == 2) {
					t = POData[subselect[mode][submode[mode]]][l++] * 256;
					t += POData[subselect[mode][submode[mode]]][l++];
					for (i = 0; i < t; i++) {
						if (i == subselect[mode][submode[mode] + 128]) {

							POData[subselect[mode][submode[mode]]][l++] = dx;
							POData[subselect[mode][submode[mode]]][l++] = dy;
							POData[subselect[mode][submode[mode]]][l++] = 0;
							POData[subselect[mode][submode[mode]]][l++] = CtoN(sx, sy);
						} else {
							l += 4;
						}
					}
				}




			}

			InvalidateRect(hwnd, NULL, 0);
		}



		if (p.x >= 548 && p.x <= 652 && p.y >= 368 && p.y <= 398) {
			int dx, dy, sx, sy, l;
			l = 0;
			int t = POData[subselect[mode][submode[mode]]][l++] * 256;
			t += POData[subselect[mode][submode[mode]]][l++];

			char out[256];
			char temp[256];

			if (subselect[mode][submode[mode] + 96] == 1) {
				sprintf(out, "POAnim - %d\r\n",t);
			}

			

			for (i = 0; i < t; i++) {
				if (subselect[mode][submode[mode] + 96] == 1) {
					dx = POData[subselect[mode][submode[mode]]][l++];
					dy = POData[subselect[mode][submode[mode]]][l++];
					sx = POData[subselect[mode][submode[mode]]][l++];
					sy = POData[subselect[mode][submode[mode]]][l++];

					sx = NtoX(sy);
					sy = NtoY(sy);

					sprintf(temp, "POTile %d %d - %d %d\r\n", sx, sy, dx, dy);
					strcat(out, temp);
				} else {
					l += 4;
				}
			}
			if (subselect[mode][submode[mode] + 96] == 2) {
				t = POData[subselect[mode][submode[mode]]][l++] * 256;
				t += POData[subselect[mode][submode[mode]]][l++];

				sprintf(out, "POAnim - %d\r\n", t);

				for (i = 0; i < t; i++) {

					dx = POData[subselect[mode][submode[mode]]][l++];
					dy = POData[subselect[mode][submode[mode]]][l++];
					sx = POData[subselect[mode][submode[mode]]][l++];
					sy = POData[subselect[mode][submode[mode]]][l++];

					sx = NtoX(sy);
					sy = NtoY(sy);


					sprintf(temp, "POTile %d %d - %d %d\r\n", sx, sy, dx, dy);
					strcat(out, temp);
				}
			}



			if (t) {
				toClipboard(out);
			}
		}



		if (p.x >= 418 && p.x <= 532 && p.y >= 368 && p.y <= 398) {

			int dx, dy, sx, sy, l;

			char out[256];
			char temp[32];


			fromClipboard(out);

			strncpy(temp, out, 32);
			temp[6] = 0;
			if (strcmp(temp, "POAnim")) {
				MessageBox(hwnd, "Incorrect format", "Error", MB_OK);
				return 0;
			}

			int t, ot;
			char * line;

			sscanf(out, "POAnim - %d", &t);


			line = strtok(out, "\n");
			if (!line) {
				MessageBox(hwnd, "Incorrect format", "Error", MB_OK);
				return 0;
			}



			l = 0;

			if (subselect[mode][submode[mode] + 96] == 1) {
				ot = POData[subselect[mode][submode[mode]]][1];

				if(t>8) {
					MessageBox(hwnd, "Incorrect format", "Error", MB_OK);
					return 0;
				}

				if (t > ot) {

					for (int i = 127; i >= 2 + t * 4; i--) {
						POData[subselect[mode][submode[mode]]][i] = POData[subselect[mode][submode[mode]]][i - (t-ot)*4];
					}

				}

				if (t < ot) {

					for (int i = 2 + t * 4; i < 128; i++) {
						if (i + (ot - t) * 4 > 127)break;
						POData[subselect[mode][submode[mode]]][i] = POData[subselect[mode][submode[mode]]][i + (ot - t) * 4];
					}

				}
			}

			if (subselect[mode][submode[mode] + 96] == 2) {
				t = POData[subselect[mode][submode[mode]]][l++] * 256;
				t += POData[subselect[mode][submode[mode]]][l++];
				for (i = 0; i < t; i++) {
					l += 4;
				}
			}

			POData[subselect[mode][submode[mode]]][l++] = 0;
			POData[subselect[mode][submode[mode]]][l++] = t;

			for (int q = 0; q < t; q++) {

				line = strtok(NULL, "\n");
				if (!line) {
					MessageBox(hwnd, "Incorrect format", "Error", MB_OK);
					return 0;
				}

				sscanf(line, "POTile %d %d - %d %d", &sx, &sy, &dx, &dy);


				POData[subselect[mode][submode[mode]]][l++] = dx;
				POData[subselect[mode][submode[mode]]][l++] = dy;
				POData[subselect[mode][submode[mode]]][l++] = 0;
				POData[subselect[mode][submode[mode]]][l++] = CtoN(sx, sy);


			}
			InvalidateRect(hwnd, NULL, 0);

		}


		if (p.x >= 548 && p.x <= 652 && p.y >= 128 && p.y <= 158) {
			if (subselect[mode][submode[mode] + 96] == 1) {
				if (POData[subselect[mode][submode[mode]]][1] > 0) {
					POData[subselect[mode][submode[mode]]][1]--;
					subselect[mode][submode[mode] + 128] = 0;

					for (int q = 2 + 4 * POData[subselect[mode][submode[mode]]][1];q < 124;q++) {
						POData[subselect[mode][submode[mode]]][q] = POData[subselect[mode][submode[mode]]][q + 4];
					}
				}
			}

			if (subselect[mode][submode[mode] + 96] == 2) {
				l = 0;
				t = POData[subselect[mode][submode[mode]]][l++] * 256;
				t += POData[subselect[mode][submode[mode]]][l++];
				for (i = 0;i < t;i++) {
					l += 4;
				}

				if (POData[subselect[mode][submode[mode]]][l+1] > 0)POData[subselect[mode][submode[mode]]][l + 1]--;
				subselect[mode][submode[mode] + 128] = 0;
			}
		}


		if (p.x >= 185 && p.x <= 205 && p.y >= 8 && p.y <= 28) {
			subselect[mode][submode[mode] + 96]+=2;
			subselect[mode][submode[mode] + 96] %= 3;
			subselect[mode][submode[mode] + 128] = 0;
		}
		if (p.x >= 396 && p.x <= 416 && p.y >= 68 && p.y <= 88) {
			subselect[mode][submode[mode] + 128] -= 1;

			if (subselect[mode][submode[mode] + 96] == 1) {

				t = POData[subselect[mode][submode[mode]]][0] * 256;
				t += POData[subselect[mode][submode[mode]]][1];

				if(subselect[mode][submode[mode] + 128]<0)
					if(t)subselect[mode][submode[mode] + 128] += t;
					else subselect[mode][submode[mode] + 128] = 0;

			}
			if (subselect[mode][submode[mode] + 96] == 2) {
				l = 0;
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

				if (subselect[mode][submode[mode] + 128]<0)
					if(t)subselect[mode][submode[mode] + 128] += t;
					else subselect[mode][submode[mode] + 128] = 0;

			}
		}
	}

	if(submode[mode]<2||submode[mode]==7)
	if(p.x>=276&&p.x<=296&&p.y>=8&&p.y<=28){
		subselect[mode][submode[mode]+32]++;
		if(submode[mode]==0)subselect[mode][submode[mode]+32]%=NumFSFrame[subselect[mode][submode[mode]]];
		if(submode[mode]==1)subselect[mode][submode[mode]+32]%=NumESFrame[subselect[mode][submode[mode]]];
		if(submode[mode]==7)subselect[mode][submode[mode]+32]%=NumMSFrame;
	}

	if (submode[mode] == 6){
		if (p.x >= 276 && p.x <= 296 && p.y >= 8 && p.y <= 28) {
			subselect[mode][submode[mode] + 96]++;
			subselect[mode][submode[mode] + 96] %= 3;
			subselect[mode][submode[mode] + 128] = 0;
		}
		if (p.x >= 486 && p.x <= 506 && p.y >= 68 && p.y <= 88) {
			subselect[mode][submode[mode] + 128] += 1;

			if (subselect[mode][submode[mode] + 96] == 1) {

				t = POData[subselect[mode][submode[mode]]][0] * 256;
				t += POData[subselect[mode][submode[mode]]][1];

				if(t)subselect[mode][submode[mode] + 128] %= t;
				else subselect[mode][submode[mode] + 128] = 0;

			}
			if (subselect[mode][submode[mode] + 96] == 2) {
				l = 0;
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

				if(t)subselect[mode][submode[mode] + 128] %= t;
				else subselect[mode][submode[mode] + 128] = 0;

			}
		}
	}

	if(submode[mode]<3||submode[mode]==8)
	if(p.x>=336&&p.x<=405&&p.y>=10&&p.y<=25){
		focus=3;
	}

	if(submode[mode]<3)
	if(p.x>=315&&p.x<=335&&p.y>=8&&p.y<=28){
		subselect[mode][submode[mode]+64]--;
		if(submode[mode]==0)if(subselect[mode][submode[mode]+64]<0)subselect[mode][submode[mode]+64]=NumFSPalette[subselect[mode][submode[mode]]]-1;
		if(submode[mode]==1)if(subselect[mode][submode[mode]+64]<0)subselect[mode][submode[mode]+64]=NumESPalette[subselect[mode][submode[mode]]]-1;
		if(submode[mode]==2)if(subselect[mode][submode[mode]+64]<0)subselect[mode][submode[mode]+64]=NumItems-1;
	}

	if(submode[mode]<3)
	if(p.x>=414&&p.x<=434&&p.y>=8&&p.y<=28){
		subselect[mode][submode[mode]+64]++;
		if(submode[mode]==0){
			if(NumFSPalette[subselect[mode][submode[mode]]]>1)subselect[mode][submode[mode]+64]%=NumFSPalette[subselect[mode][submode[mode]]];
			else subselect[mode][submode[mode]+64]=0;
		}
		if(submode[mode]==1){
			if(NumESPalette[subselect[mode][submode[mode]]]>1)subselect[mode][submode[mode]+64]%=NumESPalette[subselect[mode][submode[mode]]];
			else subselect[mode][submode[mode]+64]=0;
		}
		if(submode[mode]==2){
			subselect[mode][submode[mode]+64]%=NumItems;
		}
	}

	if(p.x>=50&&p.x<=70&&p.y>=64&&p.y<84){
		Pencil=true;
	}
	if(p.x>=50&&p.x<=70&&p.y>=89&&p.y<109){
		Pencil=false;
	}

	if(p.x>=50&&p.x<=70&&p.y>=115&&p.y<135){
		size=1;
	}
	if(p.x>=50&&p.x<=70&&p.y>=140&&p.y<160){
		size=2;
	}
	if(p.x>=50&&p.x<=70&&p.y>=165&&p.y<185){
		size=4;
	}

	j=16;
	if(submode[mode]==9&&subselect[mode][submode[mode]]<14){
		j=6;
	}
	if(submode[mode]==4){
		j=6;
	}

	for(i=0;i<j;i++){
		if(p.x>=90+18*i&&p.x<=108+18*i&&p.y>=40&&p.y<59){
			color=i;
			if(i&&j==6&&submode[mode]==9)color+=j-1;
		}
	}

	switch(submode[mode]){
		case 0:
			if(p.x>=82&&p.x<82+FSSize[subselect[mode][submode[mode]]][subselect[mode][submode[mode]+32]][0]*4&&p.y>=67&&p.y<67+FSSize[subselect[mode][submode[mode]]][subselect[mode][submode[mode]+32]][1]*4){
				if(!Pencil){
					dx=color;
					color=0;
				}
				for(u=0;u<size&&x+u<FSSize[subselect[mode][submode[mode]]][subselect[mode][submode[mode]+32]][0];u++){
					for(v=0;v<size&&y+v<FSSize[subselect[mode][submode[mode]]][subselect[mode][submode[mode]+32]][1];v++){
						ForceSprites[subselect[mode][submode[mode]]][subselect[mode][submode[mode]+32]][(p.x-82)/4+u+((p.y-67)/4+v)*FSSize[subselect[mode][submode[mode]]][subselect[mode][submode[mode]+32]][0]]=color;
						x=(p.x-82)/4+u;
						y=(p.y-67)/4+10+v;
						l = subselect[mode][submode[mode]+64];

						for(i=0;i<4;i++){
							for(j=0;j<4;j++){
								SetPixel(hdc,x*4+i+82,y*4+j+67,RGB(FSPalette[subselect[mode][submode[mode]]][l][color][0],FSPalette[subselect[mode][submode[mode]]][l][color][1],FSPalette[subselect[mode][submode[mode]]][l][color][2]));
							}
						}
					}
				}
				if(!Pencil){
					color=dx;
				}

			}
			break;
		case 1:
			if(p.x>=82&&p.x<82+ESSize[subselect[mode][submode[mode]]][subselect[mode][submode[mode]+32]][0]*4&&p.y>=67&&p.y<67+ESSize[subselect[mode][submode[mode]]][subselect[mode][submode[mode]+32]][1]*4){
				if(!Pencil){
					dx=color;
					color=0;
				}
				for(u=0;u<size&&x+u<ESSize[subselect[mode][submode[mode]]][subselect[mode][submode[mode]+32]][0];u++){
					for(v=0;v<size&&y+v<ESSize[subselect[mode][submode[mode]]][subselect[mode][submode[mode]+32]][1];v++){
						EnemySprites[subselect[mode][submode[mode]]][subselect[mode][submode[mode]+32]][(p.x-82)/4+u+((p.y-67)/4+v)*ESSize[subselect[mode][submode[mode]]][subselect[mode][submode[mode]+32]][0]]=color;
						x=(p.x-82)/4+u;
						y=(p.y-67)/4+10+v;
						l = subselect[mode][submode[mode]+64];

						for(i=0;i<4;i++){
							for(j=0;j<4;j++){
								SetPixel(hdc,x*4+i+82,y*4+j+67,RGB(ESPalette[subselect[mode][submode[mode]]][l][color][0],ESPalette[subselect[mode][submode[mode]]][l][color][1],ESPalette[subselect[mode][submode[mode]]][l][color][2]));
							}
						}
					}
				}
				if(!Pencil){
					color=dx;
				}

			}
			break;
		case 3:
			if(p.x>=82&&p.x<82+BGSize[subselect[mode][submode[mode]]][0]*4&&p.y>=67&&p.y<67+BGSize[subselect[mode][submode[mode]]][1]*4){
				if(!Pencil){
					dx=color;
					color=0;
				}
				for(u=0;u<size&&x+u<BGSize[subselect[mode][submode[mode]]][0];u++){
					for(v=0;v<size&&y+v<BGSize[subselect[mode][submode[mode]]][1];v++){
						Backgrounds[subselect[mode][submode[mode]]][(p.x-82)/4+u+((p.y-67)/4+v)*BGSize[subselect[mode][submode[mode]]][0]]=color;
						x=(p.x-82)/4+u;
						y=(p.y-67)/4+10+v;
						l = subselect[mode][submode[mode]+64];

						for(i=0;i<4;i++){
							for(j=0;j<4;j++){
								SetPixel(hdc,x*4+i+82,y*4+j+67,RGB(BGPalette[subselect[mode][submode[mode]]][l][color][0],BGPalette[subselect[mode][submode[mode]]][l][color][1],BGPalette[subselect[mode][submode[mode]]][l][color][2]));
							}
						}
					}
				}
				if(!Pencil){
					color=dx;
				}

			}
			break;
		case 4:
			if(p.x>=82&&p.x<82+PFSize[subselect[mode][submode[mode]]][0]*4&&p.y>=67&&p.y<67+PFSize[subselect[mode][submode[mode]]][1]*4){
				if(!Pencil){
					dx=color;
					color=0;
				}
				for(u=0;u<size&&x+u<PFSize[subselect[mode][submode[mode]]][0];u++){
					for(v=0;v<size&&y+v<PFSize[subselect[mode][submode[mode]]][1];v++){
						Platforms[subselect[mode][submode[mode]]][(p.x-82)/4+u+((p.y-67)/4+v)*PFSize[subselect[mode][submode[mode]]][0]]=color;
						x=(p.x-82)/4+u;
						y=(p.y-67)/4+10+v;
						l = subselect[mode][submode[mode]+64];

						for(i=0;i<4;i++){
							for(j=0;j<4;j++){
								SetPixel(hdc,x*4+i+82,y*4+j+67,RGB(PFPalette[subselect[mode][submode[mode]]][color][0],PFPalette[subselect[mode][submode[mode]]][color][1],PFPalette[subselect[mode][submode[mode]]][color][2]));
							}
						}
					}
				}
				if(!Pencil){
					color=dx;
				}

			}
			break;
		case 6:

			if (p.x >= 496 && p.x <= 536 && p.y >= 88 && p.y <= 108)focus = 4;
			if (p.x >= 496 && p.x <= 536 && p.y >= 108 && p.y <= 128)focus = 5;
			if (p.x >= 496 && p.x <= 536 && p.y >= 128 && p.y <= 148)focus = 6;
			if (p.x >= 496 && p.x <= 536 && p.y >= 148 && p.y <= 168)focus = 7;

			if(p.x>=82&&p.x<82+POSize[subselect[mode][submode[mode]]][0]*4&&p.y>=67&&p.y<67+POSize[subselect[mode][submode[mode]]][1]*4){
				if(!Pencil){
					dx=color;
					color=0;
				}
				for(u=0;u<size&&x+u<POSize[subselect[mode][submode[mode]]][0];u++){
					for(v=0;v<size&&y+v<POSize[subselect[mode][submode[mode]]][1];v++){
						Portraits[subselect[mode][submode[mode]]][(p.x-82)/4+u+((p.y-67)/4+v)*POSize[subselect[mode][submode[mode]]][0]]=color;
						x=(p.x-82)/4+u;
						y=(p.y-67)/4+10+v;
						l = subselect[mode][submode[mode]+64];

						for(i=0;i<4;i++){
							for(j=0;j<4;j++){
								SetPixel(hdc,x*4+i+82,y*4+j+67,RGB(POPalette[subselect[mode][submode[mode]]][color][0],POPalette[subselect[mode][submode[mode]]][color][1],POPalette[subselect[mode][submode[mode]]][color][2]));
							}
						}
					}
				}
				if(!Pencil){
					color=dx;
				}

			}
			break;
		case 7:
			if(p.x>=82&&p.x<82+MSSize[subselect[mode][submode[mode]]][subselect[mode][submode[mode]+32]][0]*4&&p.y>=67&&p.y<67+MSSize[subselect[mode][submode[mode]]][subselect[mode][submode[mode]+32]][1]*4){
				if(!Pencil){
					dx=color;
					color=0;
				}
				for(u=0;u<size&&x+u<MSSize[subselect[mode][submode[mode]]][subselect[mode][submode[mode]+32]][0];u++){
					for(v=0;v<size&&y+v<MSSize[subselect[mode][submode[mode]]][subselect[mode][submode[mode]+32]][1];v++){
						MapSprites[subselect[mode][submode[mode]]][subselect[mode][submode[mode]+32]][(p.x-82)/4+u+((p.y-67)/4+v)*MSSize[subselect[mode][submode[mode]]][subselect[mode][submode[mode]+32]][0]]=color;
						x=(p.x-82)/4+u;
						y=(p.y-67)/4+10+v;
						l = subselect[mode][submode[mode]+64];

						for(i=0;i<4;i++){
							for(j=0;j<4;j++){
								if (MSPalette[subselect[mode][submode[mode]]])SetPixel(hdc,x*4+i+82,y*4+j+67,RGB(EMSPalette[color][0],EMSPalette[color][1],EMSPalette[color][2]));
								else SetPixel(hdc,x*4+i+82,y*4+j+67,RGB(FMSPalette[color][0],FMSPalette[color][1],FMSPalette[color][2]));
							}
						}
					}
				}
				if(!Pencil){
					color=dx;
				}

			}
			break;
		case 8:
			if(p.x>=82&&p.x<82+TSSize[subselect[mode][submode[mode]]][0]*4&&p.y>=67&&p.y<67+TSSize[subselect[mode][submode[mode]]][1]*4){
				if(!Pencil){
					dx=color;
					color=0;
				}
				for(u=0;u<size&&x+u<TSSize[subselect[mode][submode[mode]]][0];u++){
					for(v=0;v<size&&y+v<TSSize[subselect[mode][submode[mode]]][1];v++){
						p2.x=p.x-82;
						p2.y=p.y-67;
						TilesetToPixel(p2);
						Tilesets[subselect[mode][submode[mode]]][(p2.x)/4+u+((p2.y)/4+v)*TSSize[subselect[mode][submode[mode]]][0]]=color;
						x=(p.x-82)/4+u;
						y=(p.y-67)/4+10+v;
						l = subselect[mode][submode[mode]+64];

						for(i=0;i<4;i++){
							for(j=0;j<4;j++){
								SetPixel(hdc,x*4+i+82,y*4+j+67,RGB(TSPalette[TSPalNums[subselect[mode][submode[mode]]]][color][0],TSPalette[TSPalNums[subselect[mode][submode[mode]]]][color][1],TSPalette[TSPalNums[subselect[mode][submode[mode]]]][color][2]));
							}
						}
					}
				}
				if(!Pencil){
					color=dx;
				}

			}
			break;
		case 9:
			if(p.x>=82&&p.x<82+EFSize[subselect[mode][submode[mode]]][0]*4&&p.y>=67&&p.y<67+EFSize[subselect[mode][submode[mode]]][1]*4){
				if(!Pencil){
					dx=color;
					color=0;
				}
				for(u=0;u<size&&x+u<EFSize[subselect[mode][submode[mode]]][0];u++){
					for(v=0;v<size&&y+v<EFSize[subselect[mode][submode[mode]]][1];v++){
						Effects[subselect[mode][submode[mode]]][(p.x-82)/4+u+((p.y-67)/4+v)*EFSize[subselect[mode][submode[mode]]][0]]=color;
						x=(p.x-82)/4+u;
						y=(p.y-67)/4+10+v;
						l = subselect[mode][submode[mode]+64];

						for(i=0;i<4;i++){
							for(j=0;j<4;j++){
								SetPixel(hdc,x*4+i+82,y*4+j+67,RGB(EFPalette[subselect[mode][submode[mode]]][color][0],EFPalette[subselect[mode][submode[mode]]][color][1],EFPalette[subselect[mode][submode[mode]]][color][2]));
							}
						}
					}
				}
				if(!Pencil){
					color=dx;
				}

			}
			break;
	}
}