
int CharView;

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

int PromotedMapspritesStart;
int PromotedBattlespritesStart;

long LearnOffset;
long CharOffset;
long UStatOffset;
long PStatOffset;
long BSprOffset;

long BSprOffset2 = 0;
long PortraitOffset = 0;
long PortraitOffset2 = 0;
long MSprOffset = 0;
long MSprOffset2 = 0;
long PromotedALevelsOffset = 0;


bool LearnAdded=false;

void LoadChar(char *path,bool single=false){
	unsigned char r;
	unsigned char c,l,z;
	int q;
	FILE * fp = fopen(path,"rb");
	char in=0;

	CharView = 0;
	select[mode] = 0;

	fseek(fp, 0x239FB, SEEK_SET);
	fscanf(fp, "%c", &r);
	NovaPortrait = r;

	fseek(fp, 0x23A6D, SEEK_SET);
	fscanf(fp, "%c", &r);
	NovaSprite = r;

	fseek(fp, 0x68C1, SEEK_SET);
	fscanf(fp, "%c", &r);
	BlueFlameSprite = r;

	fseek(fp, 0x23A79, SEEK_SET);
	fscanf(fp, "%c", &r);
	JogurtStatusSprite = r;

	fseek(fp, 0x23A8D, SEEK_SET);
	fscanf(fp, "%c", &r);
	PromotedMapspritesStart = r;

	fseek(fp, 0x23B77, SEEK_SET);
	fscanf(fp, "%c", &r);
	PromotedBattlespritesStart = r;


	NumChars = MIN_CHARS;
	NumCombatants = MIN_COMBATANTS;
	fseek(fp, 0x221D4, SEEK_SET);
	fscanf(fp, "%c", &r);
	if (r == 0x4E) {
		NumChars = EXT_CHARS;
	}
	fseek(fp, 0x37E8, SEEK_SET);
	fscanf(fp, "%c", &r);
	if (r == 0x4E) {
		NumChars = MAX_CHARS;
		NumCombatants = MAX_COMBATANTS;
	}


	fseek(fp, 0x23A0A, SEEK_SET);
	fscanf(fp, "%c", &r);
	if (r != 0x4E) {

		/* Initialize extended chars data */
		for (int i = 0; i < 30; i++) {
			CharPortrait[i] = i;
			CharMapSprite[i] = i;
			CharMapSprite2[i] = i + 30;
			if (i == 27 || i == 28) {
				CharPromotedAt[i] = 20; // Musashi and Hanzou start already promoted
			}
			else {
				CharPromotedAt[i] = 0;
			}
		}
		for (int i = MIN_CHARS; i < MAX_CHARS; i++) {
			CharPortrait[i] = 0;
			CharPortrait2[i] = 0;
			CharMapSprite[i] = 0;
			CharMapSprite2[i] = 0;
			CharPromotedAt[i] = 0;

			if (!Char[i][1]) {
				Char[i][1] = 1;
				Char[i][16] = 255;
				Char[i][17] = 255;
				Char[i][18] = 255;
				Char[i][19] = 255;
				Char[i][20] = 255;
				Char[i][21] = 255;
				Char[i][22] = 255;
				Char[i][23] = 255;
			}
		}

		fseek(fp, 0x23A1E, SEEK_SET);
		for (int i = 0; i < EXT_CHARS; i++) {
			fscanf(fp, "%c", &(CharPortrait2[i]));
		}

		CharMapSprite2[13] = CharMapSprite[13]; // Domingo
		CharMapSprite2[27] = CharMapSprite[27]; // Musashi
		CharMapSprite2[28] = CharMapSprite[28]; // Hanzou
		CharMapSprite2[29] = CharMapSprite[29]; // Jogurt

		CharMapSprite[30] = NovaSprite;
		CharMapSprite2[30] = NovaSprite;
		CharPortrait[30] = NovaPortrait;
		CharPortrait2[30] = NovaPortrait;

	}
	else {

		/* Load extended chars data */
		PortraitOffset = 0x140000;
		PortraitOffset2 = 0x140040;
		MSprOffset = 0x140100;
		MSprOffset2 = 0x140140;
		PromotedALevelsOffset = 0x1E6000;

		fseek(fp, PortraitOffset, SEEK_SET);
		for (int i = 0; i < MAX_CHARS; i++) {
			fscanf(fp, "%c", &(CharPortrait[i]));
		}
		fseek(fp, PortraitOffset2, SEEK_SET);
		for (int i = 0; i < MAX_CHARS; i++) {
			fscanf(fp, "%c", &(CharPortrait2[i]));
		}
		fseek(fp, MSprOffset, SEEK_SET);
		for (int i = 0; i < MAX_CHARS; i++) {
			fscanf(fp, "%c", &(CharMapSprite[i]));
		}
		fseek(fp, MSprOffset2, SEEK_SET);
		for (int i = 0; i < MAX_CHARS; i++) {
			fscanf(fp, "%c", &(CharMapSprite2[i]));
		}
		fseek(fp, PromotedALevelsOffset, SEEK_SET);
		for (int i = 0; i < MAX_CHARS; i++) {
			fscanf(fp, "%c", &r);
			if (r <= 20)CharPromotedAt[i] = r; // promoted at level can not exceed 20 (i.e., the stat growth projection level)
		}

		NovaPortrait = CharPortrait[30];
		NovaSprite = CharMapSprite[30];
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


	/* table_InitialForceData */
	fseek(fp,0x203A8,SEEK_SET);
	fscanf(fp,"%c",&r);
	CharOffset = r;
	fscanf(fp,"%c",&r);
	CharOffset = CharOffset*256+r;
	fscanf(fp,"%c",&r);
	CharOffset = CharOffset*256+r;
	fscanf(fp,"%c",&r);
	CharOffset = CharOffset*256+r;

	q = MAX_CHARS;
	if (CharOffset == 0x25154)q = MIN_CHARS;

	fseek(fp,CharOffset,SEEK_SET);
	int i, j;
	if(!single || mode == 0)
	for(i = 0; i < q; i++) {
		for(j = 0; j < 10; j++) {
			if (single && i != select[mode]) {
				fscanf(fp, "%c", &c);
				continue;
			}
			fscanf(fp, "%c", &(CharName[i][j]));
			if (CharName[i][j] == 9) CharName[i][j] = 32;
		}
		if (!single || i == select[mode]) CharName[i][10] = 0;
		for(j = 0; j < 30; j++){
			if(single && i != select[mode]){
				fscanf(fp, "%c", &c);
				continue;
			}
			fscanf(fp, "%c", &(Char[i][j]));
		}
	}
	if (q == 30) {
		/* Initialize character data for Nova */
		sprintf(CharName[30], "Nova");
		for (j = 0; j < 14; j++) {
			Char[30][j] = Char[0][j];
		}
		for (j = 0; j < 8; j++) {
			Char[30][j + 16] = 255;
		}
	}


	/* table_BattlespriteData */
	fseek(fp, 0x203AC, SEEK_SET);
	fscanf(fp, "%c", &r);
	BSprOffset = r;
	fscanf(fp, "%c", &r);
	BSprOffset = BSprOffset * 256 + r;
	fscanf(fp, "%c", &r);
	BSprOffset = BSprOffset * 256 + r;
	fscanf(fp, "%c", &r);
	BSprOffset = BSprOffset * 256 + r;

	q = MAX_CHARS;
	if (BSprOffset == 0x25604)q = MIN_CHARS;

	/* Load base battle sprites */
	fseek(fp, BSprOffset, SEEK_SET);
	if (!single || mode == 0) {
		for (int i = 0; i < q; i++) {
			fscanf(fp, "%c", &r);
			fscanf(fp, "%c", &c);
			if (single && i != select[mode])continue;
			BattleSprite[i][0] = r;
			BattleSprite[i][1] = c;
		}
	}

	/* Load promoted battle sprites */
	if (q == MIN_CHARS) {
		/* Initialize */
		for (int i = 0; i < 30; i++) {
			if (i == 13 || (i >= 27 && i <= 29)) {
				// If either Domingo, Musashi, Hanzou, or Jogurt; Promoted battle sprite = Base battle sprite
				BattleSprite2[i][0] = BattleSprite[i][0];
				BattleSprite2[i][1] = BattleSprite[i][1];
			}
			else {
				BattleSprite2[i][0] = BattleSprite[i][0] + 19;
				BattleSprite2[i][1] = BattleSprite[i][1];
			}
		}
	}
	else {
		/* Load */
		BSprOffset2 = 0x141380;
		fseek(fp, BSprOffset2, SEEK_SET);
		for (int i = 0; i < q; i++) {
			fscanf(fp, "%c", &r);
			fscanf(fp, "%c", &c);
			if (single && i != select[mode])continue;
			BattleSprite2[i][0] = r;
			BattleSprite2[i][1] = c;
		}
	}


	/* table_UnpromotedGrowths */
	fseek(fp, 0x203EC, SEEK_SET);
	fscanf(fp, "%c", &r);
	UStatOffset = r;
	fscanf(fp, "%c", &r);
	UStatOffset = UStatOffset * 256 + r;
	fscanf(fp, "%c", &r);
	UStatOffset = UStatOffset * 256 + r;
	fscanf(fp, "%c", &r);
	UStatOffset = UStatOffset * 256 + r;

	q = MAX_CHARS;
	if (UStatOffset == 0x26C1A)q = MIN_CHARS;

	for(j = 0; j < q; j++) {
		fseek(fp, UStatOffset +6*j,SEEK_SET);
		for(i = 0; i < 6; i++) {
			if(single && j != select[mode]) {
				fscanf(fp, "%c", &c);
				continue;
			}
			fscanf(fp, "%c", &(Stats[j][i]));
		}
	}


	/* table_PromotedGrowths */
	fseek(fp, 0x203F0, SEEK_SET);
	fscanf(fp, "%c", &r);
	PStatOffset = r;
	fscanf(fp, "%c", &r);
	PStatOffset = PStatOffset * 256 + r;
	fscanf(fp, "%c", &r);
	PStatOffset = PStatOffset * 256 + r;
	fscanf(fp, "%c", &r);
	PStatOffset = PStatOffset * 256 + r;

	q = MAX_CHARS;
	if (PStatOffset == 0x26CCE)q = MIN_CHARS - 3;

	for(j = 0; j < q; j++) {
		fseek(fp, PStatOffset + 6 * j, SEEK_SET);
		for(i = 0; i < 6; i++) {
			if(single && j != select[mode]) {
				fscanf(fp, "%c", &c);
				continue;
			}
			fscanf(fp, "%c", &(Stats[j][i + 6]));
		}
	}
	if (q == MIN_CHARS - 3) {
		/* Initialize promoted growths for Musashi and Hanzou */
		for (i = 0; i < 6; i++) {
			Stats[27][i + 6] = Stats[27][i];
			Stats[28][i + 6] = Stats[28][i];
			Stats[27][i] = 0;
			Stats[28][i] = 0;
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