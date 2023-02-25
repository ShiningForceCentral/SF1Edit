unsigned long TempOffset;
int TempTarget=-1;


void SaveExits(FILE * fp) {
	//BattExits[29][0] = 119;

	unsigned char r;

	ExitOffset = 0x1DCE00;

	fseek(fp, 0x1002C, SEEK_SET);
	fprintf(fp, "%c", (ExitOffset & 0xFF000000) / 0x1000000);
	fprintf(fp, "%c", (ExitOffset & 0x00FF0000) / 0x10000);
	fprintf(fp, "%c", (ExitOffset & 0x0000FF00) / 0x100);
	fprintf(fp, "%c", (ExitOffset & 0x000000FF));


	fseek(fp, ExitOffset, SEEK_SET);

	unsigned long o,o2;

	o = ExitOffset;
	o2 = o + 32;

	int i = 0;
	
	int e;
	int x, y, p2;
	for (int c = 0; c < 8; c++) {

		fseek(fp, o, SEEK_SET);
		fprintf(fp, "%c", (o2 & 0xFF000000) / 0x1000000);
		fprintf(fp, "%c", (o2 & 0x00FF0000) / 0x10000);
		fprintf(fp, "%c", (o2 & 0x0000FF00) / 0x100);
		fprintf(fp, "%c", (o2 & 0x000000FF));
		o += 4;
		fseek(fp, o2, SEEK_SET);

		for (int b = 0; b < NUM_BATTLES; b++) {
			e = BattExits[b][0];
			i = e % 16;
			bool g = false;
			if (e!=255 && ((e - i) / 16 == c || e > 120)) {
				g = true;
				for (int p = 0; p < 4096; p++) {
					if (Exits[e][p] != 255) {
						fprintf(fp, "%c", i);

						x = p % MapSize[MapHeader[BattleHeaderPos[b]][1]][0];
						y = (p - x) / MapSize[MapHeader[BattleHeaderPos[b]][1]][0];

						fprintf(fp, "%c", x);
						fprintf(fp, "%c", y);
						fprintf(fp, "%c", Exits[e][p]);

						if (Exits[e][p] == 126 || Exits[e][p] == 127) {
							p2 = Exits[e + 128][p];

							x = p2 % MapSize[MapHeader[BattleHeaderPos[b]][1]][0];
							y = (p2 - x) / MapSize[MapHeader[BattleHeaderPos[b]][1]][0];

							fprintf(fp, "%c", 0x7F);
							fprintf(fp, "%c", x);
							fprintf(fp, "%c", y);
							fprintf(fp, "%c", 0);
						}
					}
				}
			}
			e = BattExits[b][1];
			if(e<=120)i = e % 16;
			else i = e;
			if (e != 255 && ((e - i) / 16 == c || (e > 120 && g))) {
				for (int p = 0; p < 4096; p++) {
					if (Exits[e][p] != 255) {
						fprintf(fp, "%c", i);

						x = p % MapSize[MapHeader[BattleHeaderPos[b]][1]][0];
						y = (p - x) / MapSize[MapHeader[BattleHeaderPos[b]][1]][0];

						fprintf(fp, "%c", x);
						fprintf(fp, "%c", y);
						fprintf(fp, "%c", Exits[e][p]);
					}
				}
			}
			e = BattExits[b][2];
			if (e <= 120)i = e % 16;
			else i = e;
			if (e != 255 && ((e - i) / 16 == c || (e > 120 && g))) {
				for (int p = 0; p < 4096; p++) {
					if (Exits[e][p] != 255) {
						fprintf(fp, "%c", i);

						x = p % MapSize[MapHeader[BattleHeaderPos[b]][1]][0];
						y = (p - x) / MapSize[MapHeader[BattleHeaderPos[b]][1]][0];

						fprintf(fp, "%c", x);
						fprintf(fp, "%c", y);
						fprintf(fp, "%c", Exits[e][p]);
					}
				}
			}
		}

		//Map 24
		if(c==7){
			int b = 255;
			e = BattExits[b][0];
			i = e % 16;
			bool g = false;
			if (e != 255) {
				g = true;
				for (int p = 0; p < 4096; p++) {
					if (Exits[e][p] != 255) {
						fprintf(fp, "%c", i);



						x = p % MapSize[24][0];
						y = (p - x) / MapSize[24][0];

						fprintf(fp, "%c", x);
						fprintf(fp, "%c", y);
						fprintf(fp, "%c", Exits[e][p]);

						if (Exits[e][p] == 126 || Exits[e][p] == 127) {
							p2 = Exits[e + 128][p];

							x = p2 % MapSize[24][0];
							y = (p2 - x) / MapSize[24][0];

							fprintf(fp, "%c", 0x7F);
							fprintf(fp, "%c", x);
							fprintf(fp, "%c", y);
							fprintf(fp, "%c", 0);
						}
					}
				}
			}
		}

		fprintf(fp, "%c", 0xFF);
		fprintf(fp, "%c", 0xFF);
		o2 = ftell(fp);
	}
}

void InitChapterData(FILE * fp,unsigned long &o, unsigned long &o2, unsigned long &o3, unsigned long &o4, unsigned long &od){
		o2=o4;
		o3=o2+32;

		fseek(fp,o,SEEK_SET);
		unsigned long d = o2 - BattleMapHeaderOffset;
		fprintf(fp,"%c",(d-d%256)/256);
		fprintf(fp,"%c",d%256);
		o+=2;

		fseek(fp,o2,SEEK_SET);

		for(int i=0;i<32;i++){
			fprintf(fp,"%c",0);
		}

		fseek(fp,o2,SEEK_SET);

		if(o != BattleMapHeaderOffset+2){
			d = HQOffset[0] - BattleMapHeaderOffset;
			fprintf(fp,"%c",(d-d%256)/256);
			fprintf(fp,"%c",d%256);
			o2+=2;
		}
}

void WriteBattleData(FILE * fp,int battle,int versions,unsigned long &o, unsigned long &o2, unsigned long &o3, unsigned long &o4, unsigned long &od){
	unsigned long d,d2;
	int m,j,l;

	if (battle == 30)
		battle = 30;

	fseek(fp,o2,SEEK_SET);
	d = o3 - BattleMapHeaderOffset;
	fprintf(fp,"%c",(d-d%256)/256);
	fprintf(fp,"%c",d%256);
	o2+=2;

	fseek(fp,o3,SEEK_SET);
	d = od - BattleMapHeaderOffset;
	fprintf(fp,"%c",(d-d%256)/256);
	fprintf(fp,"%c",d%256);
	o3+=2;

	fseek(fp,od,SEEK_SET);
	int k;
	for(k=0;k<16;k++){
		fprintf(fp,"%c",BattleLandIndexes[battle][k]);
	}
	fprintf(fp,"%c",BattleSize[battle][0]);
	fprintf(fp,"%c",BattleSize[battle][1]);
	k=0;

	d2 = ftell(fp);

	while(k<BattleSize[battle][0]*BattleSize[battle][1]){
		m=0;
		l = BattleLand[battle][k];
		while(BattleLand[battle][k]==l&&m<16&&k<BattleSize[battle][0]*BattleSize[battle][1]){
			m++;
			k++;
		}
		fprintf(fp,"%c",16*(m-1)+l);
	}
	od = ftell(fp);

	o4 = o3 + 2*versions + 2*BattleIndex[battle][2];

	fseek(fp,o3,SEEK_SET);
	d = o4 - BattleMapHeaderOffset;
	fprintf(fp,"%c",(d-d%256)/256);
	fprintf(fp,"%c",d%256);
	o3+=2;
	
	fseek(fp, o4, SEEK_SET);
	fprintf(fp, "%c%c", 0, 0);
	o4 += 2;

	fprintf(fp, "%c", 0);//init routine
	fprintf(fp, "%c", 0);
	o4 += 2;

	fseek(fp, o4, SEEK_SET);
	fprintf(fp, "%c%c", 0, 0);
	o4 += 2;

	fseek(fp, o4, SEEK_SET);
	fprintf(fp, "%c%c", 0, 0);
	o4 += 2;

	fseek(fp, o4, SEEK_SET);
	fprintf(fp, "%c%c", 0, 0);
	o4 += 2;

	//starting location pointers & data
	if (battle != 30) {
		for (j = 0; j < 4; j++) {
			if (NumBattleStart[battle][j]) {
				fseek(fp, o4, SEEK_SET);
				d = od - BattleMapHeaderOffset;
				fprintf(fp, "%c", (d - d % 256) / 256);
				fprintf(fp, "%c", d % 256);
				o4 += 2;
				fseek(fp, od, SEEK_SET);
				fprintf(fp, "%c", NumBattleStart[battle][j]);
				od += 1;
				for (k = 0; k < NumBattleStart[battle][j]; k++) {
					fprintf(fp, "%c", BattleStart[battle][j][k][0]);
					fprintf(fp, "%c", BattleStart[battle][j][k][1]);
					od += 2;
				}
			} else {
				fseek(fp, o4, SEEK_SET);
				fprintf(fp, "%c%c", 0, 0);
				o4 += 2;
			}
		}
	} else {
		for (j = 0; j<1; j++) {
			if (NumBattleStart[battle][j]) {
				fseek(fp, o4, SEEK_SET);
				d = od - BattleMapHeaderOffset;
				fprintf(fp, "%c", (d - d % 256) / 256);
				fprintf(fp, "%c", d % 256);
				o4 += 2;
				fseek(fp, od, SEEK_SET);
				fprintf(fp, "%c", NumBattleStart[battle][j]);
				od += 1;
				for (k = 0; k<NumBattleStart[battle][j]; k++) {
					fprintf(fp, "%c", BattleStart[battle][j][k][0]);
					fprintf(fp, "%c", BattleStart[battle][j][k][1]);
					od += 2;
				}
			} else {
				fseek(fp, o4, SEEK_SET);
				fprintf(fp, "%c%c", 0, 0);
				o4 += 2;
			}
		}
	}

	int i;

	for(i=0;i<BattleIndex[battle][2];i++){
		fseek(fp,o3,SEEK_SET);
		fprintf(fp,"%c",0);
		fprintf(fp,"%c",0);
		o3+=2;
	}

	for(i=battle;i<battle+versions;i++){
		if (battle != 30) {
			fseek(fp, o3, SEEK_SET);

			d = o4 - BattleMapHeaderOffset;
			fprintf(fp, "%c", (d - d % 256) / 256);
			fprintf(fp, "%c", d % 256);
			o3 += 2;

			BattleOffset[i] = d;
			if (i == TempTarget) {
				TempTarget = -1;
				fseek(fp, TempOffset, SEEK_SET);
				fprintf(fp, "%c", (d - d % 256) / 256);
				fprintf(fp, "%c", d % 256);
			}
		} else {
			o4 -= 12;
		}

		if (BattleDataOffsets[i][0]) {
			fseek(fp, o4, SEEK_SET);
			d = od - BattleMapHeaderOffset;
			fprintf(fp, "%c", (d - d % 256) / 256);
			fprintf(fp, "%c", d % 256);
			o4 += 2;

			fseek(fp, od, SEEK_SET);
			//write regions
			k = 0;
			while (!BattleLand[i][k] && k < BattleSize[i][0] * BattleSize[i][1]) {
				k++;
			}
			while (k < BattleSize[i][0] * BattleSize[i][1]) {
				m = 0;
				l = BattleAI[i][k];
				if (l != 0xFF) {
					while ((BattleAI[i][k] == l || !BattleLand[i][k]) && m < 16 && k < BattleSize[i][0] * BattleSize[i][1]) {
						if (BattleAI[i][k] == l)m++;
						k++;
					}
					fprintf(fp, "%c", 16 * (m - 1) + l);
				} else {
					k++;
				}
			}
			od = ftell(fp);
		} else {
			fseek(fp, o4, SEEK_SET);
			fprintf(fp, "%c", 0);
			fprintf(fp, "%c", 0);
			o4 += 2;
		}


		fseek(fp,o4,SEEK_SET);

		if(i!=17 && false){// by sticking this routine in every battle, can make enemies hidden!
			fprintf(fp,"%c",0);//init routine
			fprintf(fp,"%c",0);
		} else {
			fprintf(fp,"%c",0xFF);//init routine
			fprintf(fp,"%c",0xE8);
		}
		o4+=2;

		d = od - BattleMapHeaderOffset;
		fprintf(fp,"%c",(d-d%256)/256);
		fprintf(fp,"%c",d%256);
		o4+=2;

		fseek(fp,od,SEEK_SET);
		for(j=0;j<NumEnemies[i];j++){
			fprintf(fp,"%c",Battle[i][j][0]);
			fprintf(fp,"%c",Battle[i][j][1]);
			fprintf(fp,"%c",Battle[i][j][2]);
			fprintf(fp,"%c",Battle[i][j][3]);
			od+=4;
		}
		fprintf(fp,"%c",255);
		od+=1;

		fseek(fp,o4,SEEK_SET);
		d = od - BattleMapHeaderOffset;
		fprintf(fp,"%c",(d-d%256)/256);
		fprintf(fp,"%c",d%256);
		o4+=2;

		fseek(fp,od,SEEK_SET);
		fprintf(fp, "%c", NumEnemies[i]);
		od += 1;

		for(j=0;j<NumEnemies[i];j++){
			fprintf(fp,"%c",Battle[i][j][4]);
			fprintf(fp,"%c",Battle[i][j][5]);
			fprintf(fp,"%c",Battle[i][j][6]);
			fprintf(fp,"%c",Battle[i][j][7]);
			od+=4;
		}

		if (BattleDataOffsets[i][4]) {
			fseek(fp, o4, SEEK_SET);
			d = od - BattleMapHeaderOffset;
			fprintf(fp, "%c", (d - d % 256) / 256);
			fprintf(fp, "%c", d % 256);
			o4 += 2;

			fseek(fp, od, SEEK_SET);
			for (j = 0; j < NumEnemies[i]; j++) {
				fprintf(fp, "%c", NumBehaviors[i][j]);
				od += 1;
				for (int k = 0; k < NumBehaviors[i][j]; k++) {
					fprintf(fp, "%c", Behaviors[i][j][k][0]);
					fprintf(fp, "%c", Behaviors[i][j][k][1]);

					if (Behaviors[i][j][k][1] == 2) {
						int del = (NumEnemies[i] - j - 1) * 1;
						del += (NumBehaviors[i][j] - k - 1) * 4;

						for (int j2 = j + 1; j2 < NumEnemies[i]; j2++) {
							del += 4 * NumBehaviors[i][j2];
						}

						for (int j2 = 0; j2 < j; j2++) {
							for (int k2 = 0; k2 < NumBehaviors[i][j2]; k2++) {
								if (Behaviors[i][j2][k2][1] == 2) {
									for (l = 0; l < 8; l++) {
										del += 2;
										if (AIPaths[i][j2][k2][l][0] == 0xFF)break;
									}
								}
							}
						}
						del += 2;
						fprintf(fp, "%c", del);
					} else {
						fprintf(fp, "%c", Behaviors[i][j][k][2]);
					}
					fprintf(fp, "%c", Behaviors[i][j][k][3]);
					od += 4;
				}
			}

			for (j = 0; j < NumEnemies[i]; j++) {
				for (int k = 0; k < NumBehaviors[i][j]; k++) {
					if (Behaviors[i][j][k][1] == 2) {
						for (l = 0; l < 8; l++) {
							od += 2;
							fprintf(fp, "%c", AIPaths[i][j][k][l][0]);
							fprintf(fp, "%c", AIPaths[i][j][k][l][1]);
							if (AIPaths[i][j][k][l][0] == 0xFF)break;
						}
					}
				}
			}
		} else {
			fprintf(fp, "%c", 0);
			fprintf(fp, "%c", 0);
			o4 += 2;
		}

		//starting location pointers & data
		if (battle != 30) {
			for (j = 0; j < 4; j++) {
				if (NumBattleStart[i][j]) {
					fseek(fp, o4, SEEK_SET);
					d = od - BattleMapHeaderOffset;
					fprintf(fp, "%c", (d - d % 256) / 256);
					fprintf(fp, "%c", d % 256);
					o4 += 2;
					fseek(fp, od, SEEK_SET);
					fprintf(fp, "%c", NumBattleStart[i][j]);
					od += 1;
					for (k = 0; k < NumBattleStart[i][j]; k++) {
						fprintf(fp, "%c", BattleStart[i][j][k][0]);
						fprintf(fp, "%c", BattleStart[i][j][k][1]);
						od += 2;
					}
				} else {
					fseek(fp, o4, SEEK_SET);
					fprintf(fp, "%c%c", 0, 0);
					o4 += 2;
				}
			}
		} else {
			for (j = 0; j < 1; j++) {
				if (NumBattleStart[i][j]) {
					fseek(fp, o4, SEEK_SET);
					d = od - BattleMapHeaderOffset;
					fprintf(fp, "%c", (d - d % 256) / 256);
					fprintf(fp, "%c", d % 256);
					o4 += 2;
					fseek(fp, od, SEEK_SET);
					fprintf(fp, "%c", NumBattleStart[i][j]);
					od += 1;
					for (k = 0; k < NumBattleStart[i][j]; k++) {
						fprintf(fp, "%c", BattleStart[i][j][k][0]);
						fprintf(fp, "%c", BattleStart[i][j][k][1]);
						od += 2;
					}
				} else {
					fseek(fp, o4, SEEK_SET);
					fprintf(fp, "%c%c", 0, 0);
					o4 += 2;
				}
			}
		}

	}
	o3=o4;
}

void WriteNonBattleData(FILE * fp,int battle,int base,unsigned long &o, unsigned long &o2, unsigned long &o3, unsigned long &o4, unsigned long &od){
	unsigned long d;
	int m,j,l;

	fseek(fp,o2,SEEK_SET);
	d = o3 - BattleMapHeaderOffset;
	fprintf(fp,"%c",(d-d%256)/256);
	fprintf(fp,"%c",d%256);
	o2+=2;

	if(battle==11){
		HQOffset[0]=o3;
	}

	fseek(fp,o3,SEEK_SET);
	d = od - BattleMapHeaderOffset;
	fprintf(fp,"%c",(d-d%256)/256);
	fprintf(fp,"%c",d%256);
	o3+=2;

	int k;

	fseek(fp,od,SEEK_SET);
	for(k=0;k<16;k++){
		fprintf(fp,"%c",NonBattleLandIndexes[battle][k]);
	}
	fprintf(fp,"%c",NonBattleSize[battle][0]);
	fprintf(fp,"%c",NonBattleSize[battle][1]);
	k=0;
	while(k<NonBattleSize[battle][0]*NonBattleSize[battle][1]){
		m=0;
		l = NonBattleLand[battle][k];
		while(NonBattleLand[battle][k]==l&&m<16&&k<NonBattleSize[battle][0]*NonBattleSize[battle][1]){
			m++;
			k++;
		}
		fprintf(fp,"%c",16*(m-1)+l);
	}
	od = ftell(fp);

	fseek(fp,o3,SEEK_SET);

	if(base!=0xFE){
		if(base!=0xFF){
			d = BattleOffset[base];
			fprintf(fp,"%c",(d-d%256)/256);
			fprintf(fp,"%c",d%256);
		} else {
			TempOffset = ftell(fp);
		}
		o3+=2;
		o4=o3;
	} else {

		o4 = o3 + 2;

		fseek(fp,o3,SEEK_SET);
		d = o4 - BattleMapHeaderOffset;
		fprintf(fp,"%c",(d-d%256)/256);
		fprintf(fp,"%c",d%256);
		o3+=2;
		
		fseek(fp,o4,SEEK_SET);
		fprintf(fp,"%c%c",0,0);
		o4+=2;

		fprintf(fp,"%c",0);
		fprintf(fp,"%c",0);
		o4+=2;

		fseek(fp,o4,SEEK_SET);
		fprintf(fp,"%c%c",0,0);
		o4+=2;

		fseek(fp,o4,SEEK_SET);
		fprintf(fp,"%c%c",0,0);
		o4+=2;

		fseek(fp,o4,SEEK_SET);
		fprintf(fp,"%c%c",0,0);
		o4+=2;

		//starting location pointers & data
		for(j=0;j<4;j++){
			if(NumNonBattleStart[battle][j]){
				fseek(fp,o4,SEEK_SET);
				d = od - BattleMapHeaderOffset;
				fprintf(fp,"%c",(d-d%256)/256);
				fprintf(fp,"%c",d%256);
				o4+=2;
				fseek(fp,od,SEEK_SET);
				fprintf(fp,"%c",NumNonBattleStart[battle][j]);
				od+=1;
				for(k=0;k<NumNonBattleStart[battle][j];k++){	
					fprintf(fp,"%c",NonBattleStart[battle][j][k][0]);
					fprintf(fp,"%c",NonBattleStart[battle][j][k][1]);
					od+=2;
				}
			} else {
				fseek(fp,o4,SEEK_SET);
				fprintf(fp,"%c%c",0,0);
				o4+=2;
			}
		}
		/*for(j=0;j<4;j++){
			if(NumBattleStart[TempTarget][j]){
				fseek(fp,o4,SEEK_SET);
				d = od - BattleMapHeaderOffset;
				fprintf(fp,"%c",(d-d%256)/256);
				fprintf(fp,"%c",d%256);
				o4+=2;
				fseek(fp,od,SEEK_SET);
				fprintf(fp,"%c",NumBattleStart[TempTarget][j]);
				od+=1;
				for(k=0;k<NumBattleStart[TempTarget][j];k++){	
					fprintf(fp,"%c",BattleStart[TempTarget][j][k][0]);
					fprintf(fp,"%c",BattleStart[TempTarget][j][k][1]);
					od+=2;
				}
			} else {
				fseek(fp,o4,SEEK_SET);
				fprintf(fp,"%c%c",0,0);
				o4+=2;
			}
		}*/

		o3=o4;
		TempTarget=-1;
	}
}

void SaveBattle(){
	if(!strlen(file)){
		int ret=IDYES;
		OPENFILENAME openFileName;
		char path[256];
		path[0] = '\0';    
		memset( &openFileName, 0, sizeof(openFileName) );
		openFileName.lStructSize = sizeof(openFileName);
		openFileName.hwndOwner = NULL;
		openFileName.hInstance = NULL;
		openFileName.lpstrFilter = "Genesis ROM(*.bin)\0*.bin\0";
		openFileName.lpstrCustomFilter = NULL;
		openFileName.nMaxCustFilter = 0;
		openFileName.nFilterIndex = 0;
		openFileName.lpstrFile =  path;
		openFileName.nMaxFile = 256;
		openFileName.lpstrFileTitle = NULL;
		openFileName.nMaxFileTitle = 0;
		openFileName.lpstrInitialDir = ".";
		openFileName.lpstrTitle = NULL;
		openFileName.Flags = OFN_LONGNAMES | OFN_PATHMUSTEXIST;
		openFileName.nFileOffset = 0;
		openFileName.nFileExtension = 0;
		openFileName.lpstrDefExt = "bin";
		openFileName.lCustData = NULL;
		openFileName.lpfnHook = NULL;
		openFileName.lpTemplateName = NULL;

		if(GetOpenFileName(&openFileName)!=0){
			sprintf(file,path);
		}
	}

	unsigned long o,o2,o3,o4,od;
	int i;
	char r;
	if(strlen(file)){
		FILE * fp = fopen(file,"rb+");

		fseek(fp,0x26566,SEEK_SET);
		for(i=0; i<128; i++){
			r=LandEffectType[i];
			fprintf(fp,"%c",r);
		}

		fseek(fp,0x265E6,SEEK_SET);
		for(i=0; i<128; i++){
			r=LandEffectPercent[i];
			fprintf(fp,"%c",r);
		}

		fseek(fp,0x269FE,SEEK_SET);
		for(i=0; i<125; i++){
			for(int k=0; k<4; k++){
				r=Terrain[i][k];
				fprintf(fp,"%c",r);
			}
		}

		if(0x1E0000>romsize){
			MessageBox(NULL,"Rom is too small, expand rom.","Error",MB_OK);
			fclose(fp);
			return;
		}

		SaveExits(fp);

		BattleMapHeaderOffset = 0x1B0000;

		o = BattleMapHeaderOffset;
		od = 0x1B1000;
		o4=o+18;

		InitChapterData(fp,o,o2,o3,o4,od);

		WriteNonBattleData(fp,11,254,o,o2,o3,o4,od);
		WriteBattleData(fp,1,2,o,o2,o3,o4,od);
		WriteBattleData(fp,0,1,o,o2,o3,o4,od);
		WriteBattleData(fp,3,1,o,o2,o3,o4,od);
		fprintf(fp,"%c%c",0,0);//unused region
		fprintf(fp,"%c%c",0,0);//unused region
		fprintf(fp,"%c%c",0,0);//unused region
		o2+=6;
		WriteNonBattleData(fp,0,254,o,o2,o3,o4,od);

		InitChapterData(fp,o,o2,o3,o4,od);

		WriteNonBattleData(fp,1,254,o,o2,o3,o4,od);
		WriteBattleData(fp,4,1,o,o2,o3,o4,od);
		WriteNonBattleData(fp,2,254,o,o2,o3,o4,od);
		WriteBattleData(fp,5,1,o,o2,o3,o4,od);
		WriteBattleData(fp,6,1,o,o2,o3,o4,od);
		WriteBattleData(fp,7,1,o,o2,o3,o4,od);

		InitChapterData(fp,o,o2,o3,o4,od);

		WriteBattleData(fp,9,1,o,o2,o3,o4,od);
		WriteBattleData(fp,8,1,o,o2,o3,o4,od);
		WriteBattleData(fp,10,1,o,o2,o3,o4,od);

		InitChapterData(fp,o,o2,o3,o4,od);

		WriteBattleData(fp,11,1,o,o2,o3,o4,od);
		WriteNonBattleData(fp,3,254,o,o2,o3,o4,od);
		WriteBattleData(fp,12,1,o,o2,o3,o4,od);
		WriteNonBattleData(fp,4,254,o,o2,o3,o4,od);
		WriteNonBattleData(fp,5,254,o,o2,o3,o4,od);
		WriteBattleData(fp,13,1,o,o2,o3,o4,od);

		InitChapterData(fp,o,o2,o3,o4,od);

		WriteNonBattleData(fp,6,254,o,o2,o3,o4,od);
		WriteBattleData(fp,14,1,o,o2,o3,o4,od);
		WriteBattleData(fp,15,1,o,o2,o3,o4,od);
		WriteBattleData(fp,16,1,o,o2,o3,o4,od);

		InitChapterData(fp,o,o2,o3,o4,od);
		
		WriteBattleData(fp,17,1,o,o2,o3,o4,od);
		WriteBattleData(fp,19,1,o,o2,o3,o4,od);
		WriteBattleData(fp,18,1,o,o2,o3,o4,od);
		WriteBattleData(fp,20,1,o,o2,o3,o4,od);

		InitChapterData(fp,o,o2,o3,o4,od);
		
		WriteBattleData(fp,21,1,o,o2,o3,o4,od);
		WriteBattleData(fp,24,1,o,o2,o3,o4,od);
		WriteBattleData(fp,22,1,o,o2,o3,o4,od);
		WriteBattleData(fp,23,1,o,o2,o3,o4,od);

		InitChapterData(fp,o,o2,o3,o4,od);
		
		WriteNonBattleData(fp,7,254,o,o2,o3,o4,od);
		WriteBattleData(fp,25,1,o,o2,o3,o4,od);
		WriteBattleData(fp,26,1,o,o2,o3,o4,od);
		WriteNonBattleData(fp,8,254,o,o2,o3,o4,od);
		WriteBattleData(fp,27,1,o,o2,o3,o4,od);
		WriteNonBattleData(fp,9,254,o,o2,o3,o4,od);
		WriteBattleData(fp,28,1,o,o2,o3,o4,od);
		WriteBattleData(fp,29,1,o,o2,o3,o4,od);
		WriteNonBattleData(fp,10,254,o,o2,o3,o4,od);

		InitChapterData(fp, o, o2, o3, o4, od);
		WriteBattleData(fp, 30, 1, o, o2, o3, o4, od);

		fseek(fp,0x26F60,SEEK_SET);
		fprintf(fp,"%c%c%c%c%c%c%c%c",0x4E,0xB9,0,0x1A,0xFF,0,0x4E,0x71);

		fseek(fp, 0x82DC, SEEK_SET);
		fprintf(fp, "%c%c%c%c%c%c", 0x4E, 0xB9, 0, 0x1A, 0xFF, 0x80);

		fseek(fp,0x1AFF80,SEEK_SET);
		fprintf(fp,"%c%c",0x42,0x40);
		for (int i = 1; i < 8; i++) {
			fprintf(fp, "%c%c%c%c%c%c%c%c%c%c", 0x30,0x3C,0x01,0xD0+i,0x4E,0xB9,0,0,0x03,0x90);
		}
		fprintf(fp, "%c%c%c%c%c%c%c%c", 0x42, 0x40, 0x10, 0x38, 0x9C, 0x03, 0x4E, 0x75);


		fseek(fp,0x1AFF00,SEEK_SET);
		fprintf(fp,"%c%c%c%c%c%c%c%c%c%c%c%c%c%c",0x43,0xF9,0,0x1B,0,0,0x47,0xF9,0,0x1B,0,0,0x4E,0x75);

		fseek(fp,0x1AFFE8,SEEK_SET);
		fprintf(fp,"%c%c%c%c%c%c%c%c%c%c%c%c",0x3F,0,0x10,0x39,0,0xFF,0x9C,0x88,0x80,0x39,0,0xFF);
		fprintf(fp,"%c%c%c%c%c%c%c%c%c%c%c%c",0xCB,0x4A,0x13,0xC0,0,0xFF,0x9C,0x88,0x30,0x1F,0x4E,0x75);

		fseek(fp,0x8FBE,SEEK_SET);
		for(i=0; i<45; i++){
			for(int j=0;j<8;j++){
				fprintf(fp,"%c",MapHeader[i][j]);
			}
		}

		/*for(i=0; i<NUM_BATTLES; i++){
			fseek(fp,BattleDataOffsets[i][2],SEEK_SET);
			for(int j=0;j<NumEnemies[i];j++){
				fprintf(fp,"%c",Battle[i][j][0]);
				fprintf(fp,"%c",Battle[i][j][1]);
				fprintf(fp,"%c",Battle[i][j][2]);
				fprintf(fp,"%c",Battle[i][j][3]);
			}
			fprintf(fp,"%c",255);
			fprintf(fp,"%c",NumEnemies[i]);

			for(j=0;j<NumEnemies[i];j++){
				fprintf(fp,"%c",Battle[i][j][4]);
				fprintf(fp,"%c",Battle[i][j][5]);
				fprintf(fp,"%c",Battle[i][j][6]);
				fprintf(fp,"%c",Battle[i][j][7]);
			}
			for(j=0;j<NumEnemies[i];j++){
				fprintf(fp,"%c",NumBehaviors[i][j]);
				for(int k=0; k<NumBehaviors[i][j]; k++){
					fprintf(fp,"%c",Behaviors[i][j][k][0]);
					fprintf(fp,"%c",Behaviors[i][j][k][1]);
					fprintf(fp,"%c",Behaviors[i][j][k][2]);
					fprintf(fp,"%c",Behaviors[i][j][k][3]);
				}
			}
		}*/

		fclose(fp);
		MessageBox(NULL,"Battles Saved","Note",MB_OK);
	}
}

void ExportBattle(char*path){
	FILE * fp = fopen(path,"wb");
	int i,j;
	for(i=0; i<30; i++){
		for(j=0;j<NumEnemies[i];j++){
			fprintf(fp,"%c",Battle[i][j][0]);
			fprintf(fp,"%c",Battle[i][j][1]);
			fprintf(fp,"%c",Battle[i][j][2]);
			fprintf(fp,"%c",Battle[i][j][3]);
		}
		fprintf(fp,"%c",255);
		fprintf(fp,"%c",NumEnemies[i]);

		for(j=0;j<NumEnemies[i];j++){
			fprintf(fp,"%c",Battle[i][j][4]);
			fprintf(fp,"%c",Battle[i][j][5]);
			fprintf(fp,"%c",Battle[i][j][6]);
			fprintf(fp,"%c",Battle[i][j][7]);
		}
	}

	for(i=0; i<30; i++){
		for(j=0;j<NumEnemies[i];j++){
			fprintf(fp,"%c",NumBehaviors[i][j]);
			for(int k=0; k<NumBehaviors[i][j]; k++){
				fprintf(fp,"%c",Behaviors[i][j][k][0]);
				fprintf(fp,"%c",Behaviors[i][j][k][1]);
				fprintf(fp,"%c",Behaviors[i][j][k][2]);
				fprintf(fp,"%c",Behaviors[i][j][k][3]);
			}
		}
	}

	fclose(fp);
	MessageBox(NULL,"Battles Exported","Note",MB_OK);
}

void BattleExport(){
	OPENFILENAME openFileName;
	char path[256];
	path[0] = '\0';  
	memset( &openFileName, 0, sizeof(openFileName) );
	openFileName.lStructSize = sizeof(openFileName);
	openFileName.hwndOwner = NULL;
	openFileName.hInstance = NULL;
	openFileName.lpstrFilter = "Shining Force Battle(*.sfb)\0*.sfb\0";
	openFileName.lpstrCustomFilter = NULL;
	openFileName.nMaxCustFilter = 0;
	openFileName.nFilterIndex = 0;
	openFileName.lpstrFile =  path;
	openFileName.nMaxFile = 256;
	openFileName.lpstrFileTitle = NULL;
	openFileName.nMaxFileTitle = 0;
	openFileName.lpstrInitialDir = ".";
	openFileName.lpstrTitle = NULL;
	openFileName.Flags = OFN_OVERWRITEPROMPT | OFN_LONGNAMES | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY;
	openFileName.nFileOffset = 0;
	openFileName.nFileExtension = 0;
	openFileName.lpstrDefExt = "sfb";
	openFileName.lCustData = NULL;
	openFileName.lpfnHook = NULL;
	openFileName.lpTemplateName = NULL;

	if(GetSaveFileName(&openFileName)!=0){
		ExportBattle(path);
	}
}