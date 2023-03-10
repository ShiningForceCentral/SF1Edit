
int CharView = 0;

unsigned char Char[64][30];
char CharName[64][11];

unsigned char Stats[64][12];
short Learn[64][120][2];
short NumLearn[64];
char StatN[6][8] = {"ATT","DEF","AGI","HP","MP","CRIT"};

unsigned char Curves[4][20];
long CurvesOffset;
bool ChangeCurves;

unsigned char CharMapSprite[64];
unsigned char CharMapSprite2[64];
unsigned char CharPortrait[64];
unsigned char CharPortrait2[64];

unsigned char BattleSprite[64][2];
unsigned char BattleSprite2[64][2];

unsigned char CharPromotedAt[64];


long LearnOffset;
long CharOffset;
long UStatOffset;
long PStatOffset;
long BSprOffset;


bool LearnAdded=false;

void LoadChar(char *path,bool single=false){
	unsigned char r;
	unsigned char c,l,z;
	FILE * fp = fopen(path,"rb");
	char in=0;

	fseek(fp, 0x23A7C, SEEK_SET);
	fscanf(fp, "%c", &r);
	if (r != 0x4E) {
		NumChars = 30;
	} else {
		NumChars = MAX_CHARS;
	}

	if (NumChars == 30) {
		CharView = 0;
		select[mode] = 0;
	}

	for (int i = 0; i < 64; i++) {
		CharPromotedAt[i] = 0;
	}
	if (romsize >= 0x200000) {
		fseek(fp, 0x1E6000, SEEK_SET);
		for (int i = 0; i < NumChars; i++) {
			fscanf(fp, "%c", &r);
			if (r < 100)CharPromotedAt[i] = r;
		}
	}

	if (NumChars == 30) {
		for (int i = 0;i < 30;i++) {
			CharPortrait[i] = i;
			CharMapSprite[i] = i;
			CharMapSprite2[i] = i + 30;
		}
		for (int i = 30;i < MAX_CHARS;i++) {
			CharPortrait[i] = 0;
			CharMapSprite[i] = 0;
			CharMapSprite2[i] = 0;
		}

		CharMapSprite[30] = 57;
		CharPortrait[30] = 41;
		CharPortrait2[30] = 41;
		sprintf(CharName[30], "Nova");

		fseek(fp, 0x23A1E, SEEK_SET);
		for (int i = 0;i < NumChars;i++) {
			fscanf(fp, "%c", &(CharPortrait2[i]));
		}

	} else {
		fseek(fp, 0x70000, SEEK_SET);
		for (int i = 0;i < NumChars;i++) {
			fscanf(fp, "%c", &(CharPortrait[i]));
		}
		fseek(fp, 0x70040, SEEK_SET);
		for (int i = 0;i < NumChars;i++) {
			fscanf(fp, "%c", &(CharPortrait2[i]));
		}
		fseek(fp, 0x70100, SEEK_SET);
		for (int i = 0;i < NumChars;i++) {
			fscanf(fp, "%c", &(CharMapSprite[i]));
		}
		fseek(fp, 0x70140, SEEK_SET);
		for (int i = 0; i < NumChars; i++) {
			fscanf(fp, "%c", &(CharMapSprite2[i]));
		}

		if(CharMapSprite2[0]==162)
			for (int i = 0; i < NumChars; i++) {
				CharMapSprite2[i] = CharMapSprite[i] + 30;
			}
	}

	ChangeCurves=false;

	fseek(fp,0x203E8,SEEK_SET);
	fscanf(fp,"%c",&r);
	CurvesOffset = r;
	fscanf(fp,"%c",&r);
	CurvesOffset = CurvesOffset*256+r;
	fscanf(fp,"%c",&r);
	CurvesOffset = CurvesOffset*256+r;
	fscanf(fp,"%c",&r);
	CurvesOffset = CurvesOffset*256+r;

	for(int i=0;i<4;i++){
		fseek(fp,CurvesOffset+2*i,SEEK_SET);
		fscanf(fp,"%c",&c);
		fscanf(fp,"%c",&r);
		fseek(fp,CurvesOffset+c*256+r,SEEK_SET);
		l = 0;
		while(true){
			fscanf(fp,"%c",&c);
			fscanf(fp,"%c",&r);
			for(int j=l;j<c-1;j++){
				Curves[i][j] = 0xFF;
			}
			Curves[i][c-1] = r;
			l = c;
			if(c==20)break;
		}
	}

	long o = ftell(fp);

	if(!single){
		LearnAdded=false;
		memset(Learn,-1,64*120*sizeof(short));
		memset(NumLearn,0,64*sizeof(short));
	} else {
		LearnAdded=true;
		NumLearn[select[mode]]=0;
		for(int i=0;i<120;i++){
			Learn[select[mode]][i][0]=-1;
			Learn[select[mode]][i][1]=-1;
		}
	}
	fseek(fp,0x203F4,SEEK_SET);
	fscanf(fp,"%c",&r);
	LearnOffset = r;
	fscanf(fp,"%c",&r);
	LearnOffset = LearnOffset*256+r;
	fscanf(fp,"%c",&r);
	LearnOffset = LearnOffset*256+r;
	fscanf(fp,"%c",&r);
	LearnOffset = LearnOffset*256+r;


	r=0;
	fseek(fp,LearnOffset,SEEK_SET);
	fscanf(fp,"%c",&r);
	if(!single||mode==1)
	while(r!=255){
		c=r;
		fscanf(fp,"%c",&r);
		z=r;
		if(!single||c==select[mode])NumLearn[c]=z;
		for(int i=0;i<z;i++){
			fscanf(fp,"%c",&r);
			l=r;
			fscanf(fp,"%c",&r);
			if(single&&c!=select[mode])continue;
			Learn[c][i][0]=l;
			Learn[c][i][1]=r;
		}
		fscanf(fp,"%c",&r);
	}

	fseek(fp,0x203A8,SEEK_SET);
	fscanf(fp,"%c",&r);
	CharOffset = r;
	fscanf(fp,"%c",&r);
	CharOffset = CharOffset*256+r;
	fscanf(fp,"%c",&r);
	CharOffset = CharOffset*256+r;
	fscanf(fp,"%c",&r);
	CharOffset = CharOffset*256+r;

	fseek(fp,CharOffset,SEEK_SET);
	int i,j;
	if(!single||mode==0)
	for(i=0; i<NumChars; i++){
		for(j=0; j<10; j++){
			if(single&&i!=select[mode]){
				fscanf(fp,"%c",&c);
				continue;
			}
			fscanf(fp,"%c",&(CharName[i][j]));
			if(CharName[i][j]==9)CharName[i][j]=32;
		}
		if(!single||i==select[mode])CharName[i][10]=0;
		for(j=0; j<30; j++){
			if(single&&i!=select[mode]){
				fscanf(fp,"%c",&c);
				continue;
			}
			fscanf(fp,"%c",&(Char[i][j]));
		}
	}

	fseek(fp, 0x203AC, SEEK_SET);
	fscanf(fp, "%c", &r);
	BSprOffset = r;
	fscanf(fp, "%c", &r);
	BSprOffset = BSprOffset * 256 + r;
	fscanf(fp, "%c", &r);
	BSprOffset = BSprOffset * 256 + r;
	fscanf(fp, "%c", &r);
	BSprOffset = BSprOffset * 256 + r;

	fseek(fp, BSprOffset, SEEK_SET);
	if (!single || mode == 0)
		for (int i = 0; i<NumChars; i++) {
			fscanf(fp, "%c", &r);
			fscanf(fp, "%c", &c);
			if (single&&i != select[mode])continue;
			BattleSprite[i][0] = r;
			BattleSprite[i][1] = c;
		}

	if (NumChars == MAX_CHARS) {
		fseek(fp, 0x71380, SEEK_SET);
		for (int i = 0; i<NumChars; i++) {
			fscanf(fp, "%c", &r);
			fscanf(fp, "%c", &c);
			if (single&&i != select[mode])continue;
			BattleSprite2[i][0] = r;
			BattleSprite2[i][1] = c;
		}

		if (BattleSprite2[0][0] == 125) {
			for (int i = 0; i<NumChars; i++) {
				BattleSprite2[i][0] = BattleSprite[i][0]+19;
				BattleSprite2[i][1] = BattleSprite[i][1];
			}
		}
	} else {
		for (int i = 0; i<NumChars; i++) {
			BattleSprite2[i][0] = BattleSprite[i][0] + 19;
			BattleSprite2[i][1] = BattleSprite[i][1];
		}
	}

	fseek(fp, 0x203EC, SEEK_SET);
	fscanf(fp, "%c", &r);
	UStatOffset = r;
	fscanf(fp, "%c", &r);
	UStatOffset = UStatOffset * 256 + r;
	fscanf(fp, "%c", &r);
	UStatOffset = UStatOffset * 256 + r;
	fscanf(fp, "%c", &r);
	UStatOffset = UStatOffset * 256 + r;

	for(j=0;j<NumChars;j++){
		fseek(fp, UStatOffset +6*j,SEEK_SET);
		for(i=0;i<6;i++){
			if(single&&j!=select[mode]){
				fscanf(fp,"%c",&c);
				continue;
			}
			fscanf(fp,"%c",&(Stats[j][i]));
		}
	}

	int q = NumChars;
	if (q == 30)q = 27;

	fseek(fp, 0x203F0, SEEK_SET);
	fscanf(fp, "%c", &r);
	PStatOffset = r;
	fscanf(fp, "%c", &r);
	PStatOffset = PStatOffset * 256 + r;
	fscanf(fp, "%c", &r);
	PStatOffset = PStatOffset * 256 + r;
	fscanf(fp, "%c", &r);
	PStatOffset = PStatOffset * 256 + r;

	for(j=0;j<q;j++){
		fseek(fp, PStatOffset+6*j,SEEK_SET);
		for(i=0;i<6;i++){
			if(single&&j!=select[mode]){
				fscanf(fp,"%c",&c);
				continue;
			}
			fscanf(fp,"%c",&(Stats[j][i+6]));
		}
	}
	fclose(fp);
	sprintf(file,path);
}

void ImportChar(char *path){
	LearnAdded=false;
	unsigned char r,c,l,z;
	FILE * fp = fopen(path,"rb");
	int i,j;
	for(i=0; i<30; i++){
		for(j=0; j<10; j++){
			fscanf(fp,"%c",&(CharName[i][j]));
			if(CharName[i][j]==9)CharName[i][j]=32;
		}
		CharName[i][10]=0;
		for(j=0; j<30; j++){
			fscanf(fp,"%c",&(Char[i][j]));
		}
	}
	if(feof(fp)){
		fclose(fp);
		return;
	}
	for(j=0;j<30;j++){
		for(i=0;i<6;i++){
			fscanf(fp,"%c",&(Stats[j][i]));
		}
	}
	for(j=0;j<27;j++){
		for(i=0;i<6;i++){
			fscanf(fp,"%c",&(Stats[j][i+6]));
		}
	}

	fscanf(fp,"%c",&r);
	if(feof(fp))return;

	memset(Learn,-1,30*120*sizeof(short));

	LearnOffset = r;
	fscanf(fp,"%c",&r);
	LearnOffset = LearnOffset*256+r;
	fscanf(fp,"%c",&r);
	LearnOffset = LearnOffset*256+r;
	fscanf(fp,"%c",&r);
	LearnOffset = LearnOffset*256+r;

	r=0;
	fscanf(fp,"%c",&r);
	while(r!=255){
		c=r;
		fscanf(fp,"%c",&r);
		z=r;
		NumLearn[c]=z;
		for(i=0;i<z;i++){
			fscanf(fp,"%c",&r);
			l=r;
			fscanf(fp,"%c",&r);
			Learn[c][i][0]=l;
			Learn[c][i][1]=r;
		}
		fscanf(fp,"%c",&r);
	}
	fscanf(fp,"%c",&r);


	fscanf(fp,"%c",&r);
	if(feof(fp))return;
	CharOffset = r;
	fscanf(fp,"%c",&r);
	CharOffset = CharOffset*256+r;
	fscanf(fp,"%c",&r);
	CharOffset = CharOffset*256+r;
	fscanf(fp,"%c",&r);
	CharOffset = CharOffset*256+r;

	fclose(fp);
}

void CharImport(){
	int ret=IDYES;
	OPENFILENAME openFileName;
	char path[256];
	path[0] = '\0';    
	memset( &openFileName, 0, sizeof(openFileName) );
	openFileName.lStructSize = sizeof(openFileName);
	openFileName.hwndOwner = NULL;
	openFileName.hInstance = NULL;
	openFileName.lpstrFilter = "Shining Force Characters(*.sfc)\0*.sfc\0";
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
	openFileName.lpstrDefExt = "sfc";
	openFileName.lCustData = NULL;
	openFileName.lpfnHook = NULL;
	openFileName.lpTemplateName = NULL;

	if(GetOpenFileName(&openFileName)!=0){
		ImportChar(path);
	}
}