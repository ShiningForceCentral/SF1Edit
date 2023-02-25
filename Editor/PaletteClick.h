
	if(p.x>=105&&p.x<=125&&p.y>=78&&p.y<=98){
		select[mode]--;
		if(select[mode]<0)select[mode]=NumGFX[1]-1;
	}

	if(p.x>=166&&p.x<=186&&p.y>=78&&p.y<=98){
		select[mode]++;
		if(select[mode]>= NumGFX[1] - 1)select[mode]=0;
	}

	if(p.x>=105&&p.x<=125&&p.y>=318&&p.y<=338){
		submode[mode]--;
		if (NumItems == 128) {
			if (submode[mode] < 0)submode[mode] = 127;
		} else {
			if (submode[mode] < 0)submode[mode] = 62;
		}
	}

	if (submode[mode] > 64) {
		if (p.x >= 238 && p.x <= 442 && p.y >= 333 && p.y <= 363) {
			for (i = 0; i < 4; i++) {
				for (j = 0; j < 3; j++) {
					ISPalette[submode[mode]][i][j] = ISPalette[submode[mode] - 64][i][j];
				}
			}
		}
	}

	if(p.x>=166&&p.x<=186&&p.y>=318&&p.y<=338){
		submode[mode]++;
		if (NumItems == 128) {
			if (submode[mode] > 127)submode[mode] = 0;
		} else {
			if (submode[mode] > 62)submode[mode] = 0;
		}
	}

	if(p.x>=105&&p.x<=125&&p.y>=358&&p.y<=378){
		subselect[mode][0]--;
		if(subselect[mode][0]<0)subselect[mode][0]=26;
	}

	if(p.x>=166&&p.x<=186&&p.y>=358&&p.y<=378){
		subselect[mode][0]++;
		if(subselect[mode][0]>26)subselect[mode][0]=0;
	}

	if (p.x >= 105 && p.x <= 125 && p.y >= 398 && p.y <= 418) {
		subselect[mode][2]--;
		if (subselect[mode][2]<0)subselect[mode][2] = NumGFX[3];
	}

	if (p.x >= 166 && p.x <= 186 && p.y >= 398 && p.y <= 418) {
		subselect[mode][2]++;
		if (subselect[mode][2]>NumGFX[3])subselect[mode][2] = 0;
	}

	if(p.x>=105&&p.x<=125&&p.y>=180&&p.y<=198){
		subselect[mode][1]--;
		if(subselect[mode][1]<0)subselect[mode][1]=NumGFX[0]-1;
	}

	if(p.x>=166&&p.x<=186&&p.y>=180&&p.y<=198){
		subselect[mode][1]++;
		if(subselect[mode][1]>NumGFX[0]-1)subselect[mode][1]=0;
	}

	if(p.x>=126&&p.x<=161&&p.y>=80&&p.y<=96){
		focus=1;
	}
	if(p.x>=126&&p.x<=161&&p.y>=320&&p.y<=336){
		focus=2;
	}
	if(p.x>=126&&p.x<=161&&p.y>=360&&p.y<=376){
		focus=3;
	}
	if(p.x>=126&&p.x<=161&&p.y>=180&&p.y<=196){
		focus=4;
	}
	if (p.x >= 126 && p.x <= 161 && p.y >= 400 && p.y <= 416) {
		focus = 5;
	}

	for(i=0;i<16;i++){
		if(p.x>=160+18*i&&p.x<=177+18*i&&p.y>=20&&p.y<=38){
			COLORREF c = RGB(IconPalette[i][0],IconPalette[i][1],IconPalette[i][2]);
			chooseColor(c);
			IconPalette[i][0]=GetRValue(c);
			IconPalette[i][1]=GetGValue(c);
			IconPalette[i][2]=GetBValue(c);
		}
		if(p.x>=160+18*i&&p.x<=177+18*i&&p.y>=40&&p.y<=58){
			COLORREF c = RGB(FMSPalette[i][0],FMSPalette[i][1],FMSPalette[i][2]);
			chooseColor(c);
			FMSPalette[i][0]=GetRValue(c);
			FMSPalette[i][1]=GetGValue(c);
			FMSPalette[i][2]=GetBValue(c);
		}
		if(p.x>=160+18*i&&p.x<=177+18*i&&p.y>=60&&p.y<=78){
			COLORREF c = RGB(EMSPalette[i][0],EMSPalette[i][1],EMSPalette[i][2]);
			chooseColor(c);
			EMSPalette[i][0]=GetRValue(c);
			EMSPalette[i][1]=GetGValue(c);
			EMSPalette[i][2]=GetBValue(c);
		}
		for(j=0;j<NumESPalette[select[mode]];j++){
			if(p.x>=160+18*i&&p.x<=177+18*i&&p.y>=100+20*j&&p.y<=118+20*j){
				COLORREF c = RGB(ESPalette[select[mode]][j][i][0],ESPalette[select[mode]][j][i][1],ESPalette[select[mode]][j][i][2]);
				chooseColor(c);
				ESPalette[select[mode]][j][i][0]=GetRValue(c);
				ESPalette[select[mode]][j][i][1]=GetGValue(c);
				ESPalette[select[mode]][j][i][2]=GetBValue(c);
			}
		}

		for(j=0;j<NumFSPalette[subselect[mode][1]];j++){
			if(p.x>=160+18*i&&p.x<=177+18*i&&p.y>=200+20*j&&p.y<=218+20*j){
				COLORREF c = RGB(FSPalette[subselect[mode][1]][j][i][0],FSPalette[subselect[mode][1]][j][i][1],FSPalette[subselect[mode][1]][j][i][2]);
				chooseColor(c);
				FSPalette[subselect[mode][1]][j][i][0]=GetRValue(c);
				FSPalette[subselect[mode][1]][j][i][1]=GetGValue(c);
				FSPalette[subselect[mode][1]][j][i][2]=GetBValue(c);
			}
		}

		if (p.x >= 160 + 18 * i&&p.x <= 177 + 18 * i&&p.y >= 420 && p.y <= 438) {
			m = subselect[mode][2];
			COLORREF c = RGB(BGPalette[m-m%2][0][i][0], BGPalette[m - m % 2][0][i][1], BGPalette[m - m % 2][0][i][2]);
			chooseColor(c);
			BGPalette[m-m%2][0][i][0] = GetRValue(c);
			BGPalette[m-m%2][0][i][1] = GetGValue(c);
			BGPalette[m-m%2][0][i][2] = GetBValue(c);
		}

		if(i<15)
		if(p.x>=160+18*i&&p.x<=177+18*i&&p.y>=380&&p.y<=398){
			COLORREF c = RGB(TSPalette[subselect[mode][0]][i+1][0],TSPalette[subselect[mode][0]][i+1][1],TSPalette[subselect[mode][0]][i+1][2]);
			chooseColor(c);
			TSPalette[subselect[mode][0]][i+1][0]=GetRValue(c);
			TSPalette[subselect[mode][0]][i+1][1]=GetGValue(c);
			TSPalette[subselect[mode][0]][i+1][2]=GetBValue(c);
		}
	}
	for(i=0;i<4;i++){
		if(p.x>=160+18*i&&p.x<=177+18*i&&p.y>=340&&p.y<=358){
			COLORREF c = RGB(ISPalette[submode[mode]][i][0],ISPalette[submode[mode]][i][1],ISPalette[submode[mode]][i][2]);
			chooseColor(c);
			ISPalette[submode[mode]][i][0]=GetRValue(c);
			ISPalette[submode[mode]][i][1]=GetGValue(c);
			ISPalette[submode[mode]][i][2]=GetBValue(c);
		}
	}