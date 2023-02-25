#define NUM_BATTLES 31

unsigned char Battle[NUM_BATTLES][48][8];

#define NUM_MAPS 44


unsigned char MapHeader[45][8];
unsigned char MapSize[NUM_MAPS][2];

unsigned char BattleRegions[NUM_BATTLES][16][4];

unsigned long BattleMapHeaderOffset;

unsigned long BattleDataOffsets[NUM_BATTLES][5];
unsigned long BattleStartOffsets[NUM_BATTLES][7];

RECT BattleRegion[NUM_BATTLES];

unsigned char NumEnemies[NUM_BATTLES];
unsigned char Behaviors[NUM_BATTLES][48][16][4];
unsigned char NumBehaviors[NUM_BATTLES][48];
unsigned char AIPaths[NUM_BATTLES][48][16][8][2];

unsigned char BattleSize[NUM_BATTLES][2];
unsigned char BattleLand[NUM_BATTLES][65536];
unsigned char BattleLandIndexes[NUM_BATTLES][16];
unsigned char LandEffectPercent[128];
unsigned char LandEffectType[128];
unsigned char Terrain[125][4];
unsigned char BattleStart[NUM_BATTLES][4][12][2];
unsigned char NumBattleStart[NUM_BATTLES][4];

unsigned char NonBattleSize[NUM_BATTLES][2];
unsigned char NonBattleLand[NUM_BATTLES][65536];
unsigned char NonBattleLandIndexes[NUM_BATTLES][16];
unsigned long NonBattleStartOffsets[NUM_BATTLES][7];

unsigned char NonBattleStart[NUM_BATTLES][4][12][2];
unsigned char NumNonBattleStart[NUM_BATTLES][4];

unsigned char BattleAI[NUM_BATTLES][65536];

unsigned long HQOffset[2];

bool BattleMapDrag = false;
int BattleDragPos[2];
int BattleDrag = -1;
char BattleSelect = -1;
char BattleEntrance=0;
int  BattleTele = 0;
char BattleExit = 0;
char BattleExitSet = 0;
char BattleReg=1;
char BattleTerrain=0;
unsigned char BattleMode = 0;
bool DisplayBorder = true;

int BMW = 10;
int BMH = 10;

char BattleHeaderPos[] = {3,2,8,4,10,12,13,14,16,15,17,18,20,23,25,26,27,28,30,29,31,32,34,35,33,37,38,40,42,43,44};
char NonBattleHeaderPos[] = { 2,10,10,18,20,20,18,36,39,40,39,0 };

//header pos 0 = normal HQ, 1 = ship HQ

char BattleIndex[][4] = { {1,1,0,0},{1,0,1,1},{1,0,2,0},{1,2,3,0},{2,1,0,0},{2,3,1,0},{2,4,2,0},{2,5,3,0},{3,1,0,0},{3,0,1,0},{3,2,2,0},{4,0,0,0},{4,2,1,0},{4,5,2,0},{5,1,0,0},{5,2,1,0},{5,3,2,0},{6,0,0,0},{6,2,1,0},{6,1,2,0},{6,3,3,0},{7,0,0,0},{7,2,1,0},{7,3,2,0},{7,1,3,0},{8,1,0,0},{8,2,1,0},{8,4,2,0},{8,6,3,0},{8,7,4,0},{9,0,0,0} };
int BattleOffset[NUM_BATTLES];
char NonBattleIndex[][4] = { {1,6,-1,1}, {2,0,-1,0}, {2,2,-1,0}, {4,1,-1,0}, {4,3,-1,0}, {4,4,-1,0}, {5,0,-1,0}, {8,0,-1,0}, {8,3,-1,0}, {8,5,-1,0}, {8,8,-1,0}, {1,-1,-1,0} }; 

char AIActions[][16] = { "Move To", "Charge", "Follow Path" };

unsigned int Exits[256][4096];
unsigned char BattExits[256][3];
unsigned long ExitOffset;

void LoadExits(FILE * fp) {
	BattleExitSet = 0;
	for (int i = 0; i < 256; i++) {
		for (int j = 0; j < 4096; j++) {
			Exits[i][j] = 255;
		}
	}
	for (int i = 0; i < 256; i++) {
		BattExits[i][0] = 255;
		BattExits[i][1] = 255;
		BattExits[i][2] = 255;
	}


	//16 * chapter + region
	BattExits[0][0] = 1;
	BattExits[1][0] = 0;
	BattExits[1][1] = 6;
	BattExits[2][0] = 0;
	BattExits[2][1] = 6;
	BattExits[3][0] = 2;
	BattExits[3][1] = 5;
	BattExits[4][0] = 17;
	BattExits[4][1] = 16;
	BattExits[4][2] = 18;
	BattExits[5][0] = 19;
	BattExits[6][0] = 20;
	BattExits[7][0] = 21;
	BattExits[7][1] = 24;
	BattExits[8][0] = 33;
	//BattExits[8][1] = 127+32;
	BattExits[9][0] = 32;
	BattExits[10][0] = 34;
	BattExits[11][0] = 48;
	BattExits[11][1] = 49;
	BattExits[12][0] = 50;
	BattExits[12][1] = 51;
	BattExits[12][2] = 52;
	BattExits[13][0] = 53;
	BattExits[13][1] = 56;
	BattExits[14][0] = 65;
	BattExits[14][1] = 69;
	BattExits[15][0] = 66;
	BattExits[15][1] = 68;
	BattExits[16][0] = 67;
	BattExits[16][1] = 69;
	BattExits[17][0] = 80;
	BattExits[18][0] = 82;
	BattExits[18][1] = 85;
	BattExits[19][0] = 81;
	BattExits[20][0] = 83;
	BattExits[21][0] = 96;
	BattExits[22][0] = 98;
	BattExits[22][1] = 101;
	BattExits[23][0] = 99;
	BattExits[23][1] = 100;
	BattExits[24][0] = 97;
	BattExits[24][1] = 96;
	BattExits[25][0] = 113;
	BattExits[25][1] = 121;
	BattExits[26][0] = 114;
	BattExits[26][1] = 121;
	BattExits[27][0] = 116;
	BattExits[27][1] = 117;
	BattExits[28][0] = 118;
	BattExits[29][0] = 119;
	BattExits[30][0] = 115;
	BattExits[30][1] = 120;
	BattExits[255][0] = 112;

	unsigned char r;

	fseek(fp, 0x1002C, SEEK_SET);
	fscanf(fp, "%c", &r);
	ExitOffset = r;
	fscanf(fp, "%c", &r);
	ExitOffset = ExitOffset * 256 + r;
	fscanf(fp, "%c", &r);
	ExitOffset = ExitOffset * 256 + r;
	fscanf(fp, "%c", &r);
	ExitOffset = ExitOffset * 256 + r;

	fseek(fp, ExitOffset, SEEK_SET);

	unsigned long o;

	fscanf(fp, "%c", &r);
	o = r;
	fscanf(fp, "%c", &r);
	o = o * 256 + r;
	fscanf(fp, "%c", &r);
	o = o * 256 + r;
	fscanf(fp, "%c", &r);
	o = o * 256 + r;

	fseek(fp, o, SEEK_SET);

	int i = 0;
	int p = 0;
	int p2 = 0;
	int b;
	for (int c = 0; c < 8; c++) {
		for (;;) {
			fscanf(fp, "%c", &r);
			if (r == 255) {
				fscanf(fp, "%c", &r);
				break;
			}
			i = r;
			fscanf(fp, "%c", &r);
			p = r;
			fscanf(fp, "%c", &r);

			for (int j = 0; j < NUM_BATTLES; j++) {
				if (BattExits[j][0] == i + 16 * c || BattExits[j][1] == i + 16 * c) {
					b = j;
					break;
				}
			}

			if (i + 16 * c == 112) {
				p += r * MapSize[24][0];
			} else {
				p += r * MapSize[MapHeader[BattleHeaderPos[b]][1]][0];
			}
			
			fscanf(fp, "%c", &r);
			Exits[i + 16 * c][p] = r;

			if (r == 126 || r == 127) {
				p2 = p;
				fscanf(fp, "%c", &r);
				if (r != 126 && r != 127) {
					fseek(fp, -1, SEEK_CUR);
				} else {
					fscanf(fp, "%c", &r);
					p = r;
					fscanf(fp, "%c", &r);
					if (i + 16 * c == 112) {
						p += r * MapSize[24][0];
					} else {
						p += r * MapSize[MapHeader[BattleHeaderPos[b]][1]][0];
					}
					fscanf(fp, "%c", &r);

					Exits[128 + i + 16 * c][p2] = p;
				}

			}
		}
	}
}

void LoadBattle(char *path, bool single=false){
	unsigned long l,o,d;
	FILE * fp = fopen(path,"rb");
	char in;
	unsigned char r;
	int i,j,k,m,n;

	if(!single){
		fseek(fp,0x26566,SEEK_SET);
		for(i=0; i<128; i++){
			fscanf(fp,"%c",&r);
			LandEffectType[i]=r;
		}

		fseek(fp,0x265E6,SEEK_SET);
		for(i=0; i<128; i++){
			fscanf(fp,"%c",&r);
			LandEffectPercent[i]=r;
		}

		fseek(fp,0x269FE,SEEK_SET);
		for(i=0; i<125; i++){
			for(k=0; k<4; k++){
				fscanf(fp,"%c",&r);
				Terrain[i][k]=r;
			}
		}

		fseek(fp,0x8FBE,SEEK_SET);
		for(i=0; i<45; i++){
			for(j=0;j<8;j++){
				fscanf(fp,"%c",&(MapHeader[i][j]));
			}
		}
	}

	fseek(fp,0x26F60,SEEK_SET);
	fscanf(fp,"%c",&r);
	if(r==0x4E)BattleMapHeaderOffset=0x1B0000;
	else BattleMapHeaderOffset=0x2704E;

	bool reset = false;

	for(i=0; i<NUM_BATTLES; i++){
		if (i == 30)
			i = i;
		fseek(fp,BattleMapHeaderOffset+2*BattleIndex[i][0]-2,SEEK_SET);
		fscanf(fp,"%c",&r);
		l=0;
		l = r;
		fscanf(fp,"%c",&r);
		l=l*256+r;
		if (i==30 && (l == 0xFFFF || l==0) && BattleMapHeaderOffset == 0x1B0000) {
			BattleMapHeaderOffset = 0x2704E;
			l = 0x4B8;
			reset = true;
		}
		fseek(fp,BattleMapHeaderOffset+l+2*BattleIndex[i][1]+2,SEEK_SET);
		fscanf(fp,"%c",&r);
		l=0;
		l = r;
		fscanf(fp,"%c",&r);
		l=l*256+r;
		fseek(fp,BattleMapHeaderOffset+l,SEEK_SET);

		o=ftell(fp);//header offset

		fscanf(fp,"%c",&r);
		l=0;
		l = r;
		fscanf(fp,"%c",&r);
		l=l*256+r;//walk/land effect

		fseek(fp,BattleMapHeaderOffset+l,SEEK_SET);

		for(k=0;k<16;k++){
			fscanf(fp,"%c",&r);
			if(single&&i!=select[mode]){
				continue;
			}
			BattleLandIndexes[i][k]=r;
		}

		fscanf(fp,"%c",&r);
		BattleSize[i][0]=r;
		fscanf(fp,"%c",&r);
		BattleSize[i][1]=r;

		d = ftell(fp);

		k=0;
		if(!single||i==select[mode])
		while(k<BattleSize[i][0]*BattleSize[i][1]){
			fscanf(fp,"%c",&r);
			j = r%16;
			m = (r-j)/16+1;
			for(n=0;n<m;n++){
				BattleLand[i][k++]=j;
			}
		}

		fseek(fp,o+4+2*BattleIndex[i][2],SEEK_SET);

		fscanf(fp,"%c",&r);
		l=0;
		l = r;
		fscanf(fp,"%c",&r);
		l=l*256+r;
		if(l)fseek(fp,BattleMapHeaderOffset+l,SEEK_SET);
		else fseek(fp, -2, SEEK_CUR);
		o=ftell(fp);//main pointers offset

		for(j=0;j<5;j++){
			fscanf(fp,"%c",&r);
			l=0;
			l = r;
			fscanf(fp,"%c",&r);
			l=l*256+r;
			if(l>=0x8000)l=(0x10000-l)*-1;
			if(single&&i!=select[mode]){
				continue;
			}
			if(l)BattleDataOffsets[i][j]=BattleMapHeaderOffset+l;
			else BattleDataOffsets[i][j]=0;
		}

		if (BattleIndex[i][0] < 9) {
			for (j = 0; j < 4; j++) {
				fscanf(fp, "%c", &r);
				l = 0;
				l = r;
				fscanf(fp, "%c", &r);
				l = l * 256 + r;
				if (single&&i != select[mode]) {
					continue;
				}
				BattleStartOffsets[i][j] = BattleMapHeaderOffset + l;
			}
		} else {
			for (j = 0; j < 4; j++) {
				BattleStartOffsets[i][j] = 0;
			}
			for (j = 0; j < 1; j++) {
				fscanf(fp, "%c", &r);
				l = 0;
				l = r;
				fscanf(fp, "%c", &r);
				l = l * 256 + r;
				if (single&&i != select[mode]) {
					continue;
				}
				BattleStartOffsets[i][j] = BattleMapHeaderOffset + l;
			}
		}

		for(k=0;k<65536;k++){
			BattleAI[i][k]=0xFF;
		}

		if(!single||i==select[mode])
		if(BattleDataOffsets[i][0]){
			fseek(fp,BattleDataOffsets[i][0],SEEK_SET);//AI Regions

			k=0;
			while(!BattleLand[i][k])k++;
			while(k<BattleSize[i][0]*BattleSize[i][1]){
				fscanf(fp,"%c",&r);
				j = r%16;
				m = (r-j)/16+1;
				for(n=0;n<m;n++){
					BattleAI[i][k++]=j;
					while(!BattleLand[i][k])k++;
					if(k>=BattleSize[i][0]*BattleSize[i][1])break;
				}
			}
		}

		if(!single||i==select[mode])
		for(k=0;k<4;k++){
			if(BattleStartOffsets[i][k]){
				fseek(fp,BattleStartOffsets[i][k],SEEK_SET);//Starting Locations
				fscanf(fp,"%c",&r);
				NumBattleStart[i][k]=r;
				if(NumBattleStart[i][k]>12)NumBattleStart[i][k]=12;
				for(j=0;j<NumBattleStart[i][k];j++){
					fscanf(fp,"%c",&r);
					BattleStart[i][k][j][0]=r;
					fscanf(fp,"%c",&r);
					BattleStart[i][k][j][1]=r;
				}
			} else NumBattleStart[i][k]=0;
		}

		//fseek(fp,offset[i],SEEK_SET);
		if(!single||i==select[mode])
		if(BattleDataOffsets[i][2]){
			fseek(fp,BattleDataOffsets[i][2],SEEK_SET);//Enemy Data
			j=0;

			while(true){
				fscanf(fp,"%c",&in);
				if(in==-1){
					fscanf(fp,"%c",&(NumEnemies[i]));
					break;
				}
				Battle[i][j][0]=in;
				fscanf(fp,"%c",&(Battle[i][j][1]));
				fscanf(fp,"%c",&(Battle[i][j][2]));
				fscanf(fp,"%c",&(Battle[i][j][3]));
				j++;
			}
			for(j=0;j<NumEnemies[i];j++){
				fscanf(fp,"%c",&(Battle[i][j][4]));
				fscanf(fp,"%c",&(Battle[i][j][5]));
				fscanf(fp,"%c",&(Battle[i][j][6]));
				fscanf(fp,"%c",&(Battle[i][j][7]));
			}
			if (BattleIndex[i][0] != 9) {
				for (j = 0; j < NumEnemies[i]; j++) {
					fscanf(fp, "%c", &(NumBehaviors[i][j]));
					for (int k = 0; k < NumBehaviors[i][j]; k++) {
						fscanf(fp, "%c", &(Behaviors[i][j][k][0]));
						fscanf(fp, "%c", &(Behaviors[i][j][k][1]));
						fscanf(fp, "%c", &(Behaviors[i][j][k][2]));
						fscanf(fp, "%c", &(Behaviors[i][j][k][3]));

						for (int l = 0; l < 8; l++) {
							AIPaths[i][j][k][l][0] = 0xFF;
							AIPaths[i][j][k][l][1] = 0xFF;
						}

						if (Behaviors[i][j][k][1] == 2) {
							long back = ftell(fp);
							fseek(fp, Behaviors[i][j][k][2] - 2, SEEK_CUR);
							for (int l = 0; l < 8; l++) {
								fscanf(fp, "%c", &(AIPaths[i][j][k][l][0]));
								fscanf(fp, "%c", &(AIPaths[i][j][k][l][1]));
								if (AIPaths[i][j][k][l][0] == 0xFF)break;
							}
							fseek(fp, back, SEEK_SET);
						}
					}
				}
			} else {
				for (j = 0; j < NumEnemies[i]; j++) {
					NumBehaviors[i][j] = 0;
				}
			}
		}
		o = ftell(fp);
	}

	if (reset)BattleMapHeaderOffset = 0x1B0000;

	if(!single)
	for(i=0; i<12; i++){
		fseek(fp,BattleMapHeaderOffset+2*NonBattleIndex[i][0]-2,SEEK_SET);
		fscanf(fp,"%c",&r);
		l=0;
		l = r;
		fscanf(fp,"%c",&r);
		l=l*256+r;
		fseek(fp,BattleMapHeaderOffset+l+2*NonBattleIndex[i][1]+2,SEEK_SET);
		fscanf(fp,"%c",&r);
		l=0;
		l = r;
		fscanf(fp,"%c",&r);
		l=l*256+r;
		fseek(fp,BattleMapHeaderOffset+l,SEEK_SET);
		o=ftell(fp);//header offset

		fscanf(fp,"%c",&r);
		l=0;
		l = r;
		fscanf(fp,"%c",&r);
		l=l*256+r;//walk/land effect

		fseek(fp,BattleMapHeaderOffset+l,SEEK_SET);

		for(k=0;k<16;k++){
			fscanf(fp,"%c",&r);
			NonBattleLandIndexes[i][k]=r;
		}

		fscanf(fp,"%c",&r);
		NonBattleSize[i][0]=r;
		fscanf(fp,"%c",&r);
		NonBattleSize[i][1]=r;

		k=0;
		while(k<NonBattleSize[i][0]*NonBattleSize[i][1]){
			fscanf(fp,"%c",&r);
			j = r%16;
			m = (r-j)/16+1;
			for(n=0;n<m;n++){
				NonBattleLand[i][k++]=j;
			}
		}

		fseek(fp,o+2,SEEK_SET);

		fscanf(fp,"%c",&r);
		l=0;
		l = r;
		fscanf(fp,"%c",&r);
		l=l*256+r;
		fseek(fp,BattleMapHeaderOffset+l,SEEK_SET);
		o=ftell(fp);//main pointers offset

		for(j=0;j<5;j++){
			fscanf(fp,"%c",&r);
			fscanf(fp,"%c",&r);
		}
		for(j=0;j<4;j++){
			fscanf(fp,"%c",&r);
			l=0;
			l = r;
			fscanf(fp,"%c",&r);
			l=l*256+r;
			NonBattleStartOffsets[i][j]=BattleMapHeaderOffset+l;
		}

		for(k=0;k<4;k++){
			if(NonBattleStartOffsets[i][k]){
				fseek(fp,NonBattleStartOffsets[i][k],SEEK_SET);//Starting Locations
				fscanf(fp,"%c",&r);
				NumNonBattleStart[i][k]=r;
				for(j=0;j<NumNonBattleStart[i][k];j++){
					fscanf(fp,"%c",&r);
					NonBattleStart[i][k][j][0]=r;
					fscanf(fp,"%c",&r);
					NonBattleStart[i][k][j][1]=r;
				}
			} else NumNonBattleStart[i][k]=0;
		}
	}

	
	LoadExits(fp);

	fclose(fp);
	sprintf(file,path);
}

void ImportBattle(char *path){
	FILE * fp = fopen(path,"rb");
	char in;

	int i;

	for(i=0; i<30; i++){
		int j=0;
		while(true){
			fscanf(fp,"%c",&in);
			if(in==-1){
				fscanf(fp,"%c",&(NumEnemies[i]));
				break;
			}
			Battle[i][j][0]=in;
			fscanf(fp,"%c",&(Battle[i][j][1]));
			fscanf(fp,"%c",&(Battle[i][j][2]));
			fscanf(fp,"%c",&(Battle[i][j][3]));
			j++;
		}
		for(j=0;j<NumEnemies[i];j++){
			fscanf(fp,"%c",&(Battle[i][j][4]));
			fscanf(fp,"%c",&(Battle[i][j][5]));
			fscanf(fp,"%c",&(Battle[i][j][6]));
			fscanf(fp,"%c",&(Battle[i][j][7]));
		}
	}
	for(i=0; i<30; i++){
		for(int j=0;j<NumEnemies[i];j++){
			fscanf(fp,"%c",&(NumBehaviors[i][j]));
			if(feof(fp))return;
			for(int k=0; k<NumBehaviors[i][j]; k++){
				fscanf(fp,"%c",&(Behaviors[i][j][k][0]));
				if(feof(fp))return;
				fscanf(fp,"%c",&(Behaviors[i][j][k][1]));
				fscanf(fp,"%c",&(Behaviors[i][j][k][2]));
				fscanf(fp,"%c",&(Behaviors[i][j][k][3]));
			}
		}
	}
	fclose(fp);
}

void BattleImport(){
	int ret=IDYES;
	OPENFILENAME openFileName;
	char path[256];
	path[0] = '\0';    
	memset( &openFileName, 0, sizeof(openFileName) );
	openFileName.lStructSize = sizeof(openFileName);
	openFileName.hwndOwner = NULL;
	openFileName.hInstance = NULL;
	openFileName.lpstrFilter = "Shining Force Battles(*.sfb)\0*.sfb\0";
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
	openFileName.lpstrDefExt = "sfb";
	openFileName.lCustData = NULL;
	openFileName.lpfnHook = NULL;
	openFileName.lpTemplateName = NULL;

	if(GetOpenFileName(&openFileName)!=0){
		ImportBattle(path);
	}
}

void RemoveEnemy(){
	if(BattleSelect==-1)return;

	BattleDrag=-1;

	int i;
	if(BattleSelect<NumEnemies[select[mode]]-1){
		for(i=0;i<8;i++){
			Battle[select[mode]][BattleSelect][i]=Battle[select[mode]][NumEnemies[select[mode]]-1][i];
		}
		NumBehaviors[select[mode]][BattleSelect]=NumBehaviors[select[mode]][NumEnemies[select[mode]]-1];
		for(i=0;i<NumBehaviors[select[mode]][BattleSelect];i++){
			for(int j=0;j<4;j++){
				Behaviors[select[mode]][BattleSelect][i][j]=Behaviors[select[mode]][NumEnemies[select[mode]]-1][i][j];
			}
		}
	}
	NumEnemies[select[mode]]--;
	BattleSelect=-1;
}