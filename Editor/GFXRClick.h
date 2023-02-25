	switch(submode[mode]){
		case 0:
			if(p.x>=82&&p.x<82+FSSize[subselect[mode][submode[mode]]][subselect[mode][submode[mode]+32]][0]*4&&p.y>=67&&p.y<67+FSSize[subselect[mode][submode[mode]]][subselect[mode][submode[mode]+32]][1]*4){
				color=ForceSprites[subselect[mode][submode[mode]]][subselect[mode][submode[mode]+32]][(p.x-82)/4+((p.y-67)/4)*FSSize[subselect[mode][submode[mode]]][subselect[mode][submode[mode]+32]][0]];
			}

			l = subselect[mode][submode[mode] + 64];
			for (i = 0; i<16; i++) {
				if (p.x >= 90 + 18 * i&&p.x <= 108 + 18 * i&&p.y >= 40 && p.y<59) {
					COLORREF c = RGB(FSPalette[subselect[mode][submode[mode]]][l][i][0], FSPalette[subselect[mode][submode[mode]]][l][i][1], FSPalette[subselect[mode][submode[mode]]][l][i][2]);
					chooseColor(c);
					GFXPaletteEdit = true;
					FSPalette[subselect[mode][submode[mode]]][l][i][0] = GetRValue(c);
					FSPalette[subselect[mode][submode[mode]]][l][i][1] = GetGValue(c);
					FSPalette[subselect[mode][submode[mode]]][l][i][2] = GetBValue(c);
					InvalidateRect(hWnd, NULL, 0);
				}
			}
			break;
		case 1:
			if(p.x>=82&&p.x<82+ESSize[subselect[mode][submode[mode]]][subselect[mode][submode[mode]+32]][0]*4&&p.y>=67&&p.y<67+ESSize[subselect[mode][submode[mode]]][subselect[mode][submode[mode]+32]][1]*4){
				color=EnemySprites[subselect[mode][submode[mode]]][subselect[mode][submode[mode]+32]][(p.x-82)/4+((p.y-67)/4)*ESSize[subselect[mode][submode[mode]]][subselect[mode][submode[mode]+32]][0]];
			}

			l = subselect[mode][submode[mode] + 64];
			for (i = 0; i<16; i++) {
				if (p.x >= 90 + 18 * i&&p.x <= 108 + 18 * i&&p.y >= 40 && p.y<59) {
					COLORREF c = RGB(ESPalette[subselect[mode][submode[mode]]][l][i][0], ESPalette[subselect[mode][submode[mode]]][l][i][1], ESPalette[subselect[mode][submode[mode]]][l][i][2]);
					chooseColor(c);
					GFXPaletteEdit = true;
					ESPalette[subselect[mode][submode[mode]]][l][i][0] = GetRValue(c);
					ESPalette[subselect[mode][submode[mode]]][l][i][1] = GetGValue(c);
					ESPalette[subselect[mode][submode[mode]]][l][i][2] = GetBValue(c);
					InvalidateRect(hWnd, NULL, 0);
				}
			}
			break;
		case 3:
			if(p.x>=82&&p.x<82+BGSize[subselect[mode][submode[mode]]][0]*4&&p.y>=67&&p.y<67+BGSize[subselect[mode][submode[mode]]][1]*4){
				color=Backgrounds[subselect[mode][submode[mode]]][(p.x-82)/4+((p.y-67)/4)*BGSize[subselect[mode][submode[mode]]][0]];
			}

			m = subselect[mode][submode[mode]];
			m = m - m % 2;

			l = subselect[mode][submode[mode] + 64];
			for (i = 0; i<16; i++) {
				if (p.x >= 90 + 18 * i&&p.x <= 108 + 18 * i&&p.y >= 40 && p.y<59) {
					COLORREF c = RGB(BGPalette[m][l][i][0], BGPalette[m][l][i][1], BGPalette[m][l][i][2]);
					chooseColor(c);
					GFXPaletteEdit = true;
					BGPalette[m][l][i][0] = GetRValue(c);
					BGPalette[m][l][i][1] = GetGValue(c);
					BGPalette[m][l][i][2] = GetBValue(c);
					InvalidateRect(hWnd, NULL, 0);
				}
			}
			break;
		case 4:
			if(p.x>=82&&p.x<82+PFSize[subselect[mode][submode[mode]]][0]*4&&p.y>=67&&p.y<67+PFSize[subselect[mode][submode[mode]]][1]*4){
				color=Platforms[subselect[mode][submode[mode]]][(p.x-82)/4+((p.y-67)/4)*PFSize[subselect[mode][submode[mode]]][0]];
			}

			for (i = 0; i<6; i++) {
				if (p.x >= 90 + 18 * i&&p.x <= 108 + 18 * i&&p.y >= 40 && p.y<59) {
					COLORREF c = RGB(PFPalette[subselect[mode][submode[mode]]][i][0], PFPalette[subselect[mode][submode[mode]]][i][1], PFPalette[subselect[mode][submode[mode]]][i][2]);
					chooseColor(c);
					GFXPaletteEdit = true;
					PFPalette[subselect[mode][submode[mode]]][i][0] = GetRValue(c);
					PFPalette[subselect[mode][submode[mode]]][i][1] = GetGValue(c);
					PFPalette[subselect[mode][submode[mode]]][i][2] = GetBValue(c);
					InvalidateRect(hWnd, NULL, 0);
				}
			}
			break;
		case 5:
			for (i = 0; i<16; i++) {
				if (p.x >= 190 + 18 * i&&p.x <= 208 + 18 * i&&p.y >= 10 && p.y<29) {
					COLORREF c;

					s = subselect[mode][submode[mode]];
					while (s>0 && CSPalOffset[s] == 0)s--;

					c = RGB(CSPalette[s][i][0], CSPalette[s][i][1], CSPalette[s][i][2]);
					chooseColor(c);
					GFXPaletteEdit = true;

					CSPalette[s][i][0] = GetRValue(c);
					CSPalette[s][i][1] = GetGValue(c);
					CSPalette[s][i][2] = GetBValue(c);

					InvalidateRect(hWnd, NULL, 0);
				}
			}
			break;
		case 6:
			if(p.x>=82&&p.x<82+POSize[subselect[mode][submode[mode]]][0]*4&&p.y>=67&&p.y<67+POSize[subselect[mode][submode[mode]]][1]*4){
				color=Portraits[subselect[mode][submode[mode]]][(p.x-82)/4+((p.y-67)/4)*POSize[subselect[mode][submode[mode]]][0]];
			}

			for(i=0;i<16;i++){
				if(p.x>=90+18*i&&p.x<=108+18*i&&p.y>=40&&p.y<59){
					COLORREF c = RGB(POPalette[subselect[mode][submode[mode]]][i][0],POPalette[subselect[mode][submode[mode]]][i][1],POPalette[subselect[mode][submode[mode]]][i][2]);
					chooseColor(c);
					GFXPaletteEdit = true;
					POPalette[subselect[mode][submode[mode]]][i][0]=GetRValue(c);
					POPalette[subselect[mode][submode[mode]]][i][1]=GetGValue(c);
					POPalette[subselect[mode][submode[mode]]][i][2]=GetBValue(c);
					InvalidateRect(hWnd,NULL,0);
				}
			}
			break;
		case 7:
			if(p.x>=82&&p.x<82+MSSize[subselect[mode][submode[mode]]][subselect[mode][submode[mode]+32]][0]*4&&p.y>=67&&p.y<67+MSSize[subselect[mode][submode[mode]]][subselect[mode][submode[mode]+32]][1]*4){
				color=MapSprites[subselect[mode][submode[mode]]][subselect[mode][submode[mode]+32]][(p.x-82)/4+((p.y-67)/4)*MSSize[subselect[mode][submode[mode]]][subselect[mode][submode[mode]+32]][0]];
			}

			for (i = 0; i<16; i++) {
				if (p.x >= 90 + 18 * i&&p.x <= 108 + 18 * i&&p.y >= 40 && p.y<59) {
					COLORREF c;
					if (MSPalette[subselect[mode][submode[mode]]])c = RGB(EMSPalette[i][0], EMSPalette[i][1], EMSPalette[i][2]);
					else c = RGB(FMSPalette[i][0], FMSPalette[i][1], FMSPalette[i][2]);
					chooseColor(c);
					GFXPaletteEdit = true;
					if (MSPalette[subselect[mode][submode[mode]]]) {
						EMSPalette[i][0] = GetRValue(c);
						EMSPalette[i][1] = GetGValue(c);
						EMSPalette[i][2] = GetBValue(c);
					} else {
						FMSPalette[i][0] = GetRValue(c);
						FMSPalette[i][1] = GetGValue(c);
						FMSPalette[i][2] = GetBValue(c);
					}
					InvalidateRect(hWnd, NULL, 0);
				}
			}
			break;
		case 8:
			if(p.x>=82&&p.x<82+TSSize[subselect[mode][submode[mode]]][0]*4&&p.y>=67&&p.y<67+TSSize[subselect[mode][submode[mode]]][1]*4){
				p.x-=82;
				p.y-=67;
				TilesetToPixel(p);
				color=Tilesets[subselect[mode][submode[mode]]][(p.x)/4+((p.y)/4)*TSSize[subselect[mode][submode[mode]]][0]];
			}

			m = TSPalNums[subselect[mode][submode[mode]]];

			for (i = 1; i<16; i++) {
				if (p.x >= 90 + 18 * i&&p.x <= 108 + 18 * i&&p.y >= 40 && p.y<59) {
					COLORREF c = RGB(TSPalette[m][i][0], TSPalette[m][i][1], TSPalette[m][i][2]);
					chooseColor(c);
					GFXPaletteEdit = true;
					TSPalette[m][i][0] = GetRValue(c);
					TSPalette[m][i][1] = GetGValue(c);
					TSPalette[m][i][2] = GetBValue(c);
					InvalidateRect(hWnd, NULL, 0);
				}
			}
			break;
		case 9:
			if(p.x>=82&&p.x<82+EFSize[subselect[mode][submode[mode]]][0]*4&&p.y>=67&&p.y<67+EFSize[subselect[mode][submode[mode]]][1]*4){
				color=Effects[subselect[mode][submode[mode]]][(p.x-82)/4+((p.y-67)/4)*EFSize[subselect[mode][submode[mode]]][0]];
			}
			break;

	}