int currentPage = 1; // 1 = EXP, 2 = Fixes, 3 = Mechanics

unsigned char Poison;
unsigned char DamageSpread;
unsigned char DamageBase;
unsigned char CritMult;
unsigned char DoubleChance;
bool MultiAttacks;
unsigned char MultiFalloff;
unsigned char BreakChance;
bool RemoveMarks;
bool RemoveCaps=false;
bool DisallowRevive;
unsigned char LevelLimit;
unsigned char UnLevelLimit;
bool JogurtLevels;
bool ExtendStatItems;
bool AddMPEffect;
bool DisplayCrit;
bool FixLE;
bool ItemPassing;
bool ItemPassingBattle;
bool EXPOverflow;
bool AddArmor;
bool HealAI;
bool ChooseMSPal;
bool FixDoubles;
bool ShowCrit;
bool FixMuddle;
bool AllHealEXP;

unsigned char StatusElement;

unsigned char PromotePercent;

unsigned char HPEXPPercent;
unsigned char HPEXPMin;
unsigned char DetoxEXP;
unsigned char SleepWakeChance;

unsigned char ProLevel;
unsigned char ProLevelAdd;
unsigned char EXP5Above; //character is 5 levels or more above the enemy
unsigned char EXPPlus4;
unsigned char EXPPlus3;
unsigned char EXPPlus2;
unsigned char EXPPlus1;
unsigned char SameLevel; //character and enemy are the same level
unsigned char EXPMinus1;
unsigned char EXPMinus2;
unsigned char EXP3Below; //character is 3 levels or more than the enemy

unsigned char HealerClasses[4]; // Stores IDs of healer classes

long PoisonOffset;

long StatCapOffsets[] = {0x228FC, 0x22926, 0x22950, 0x229A4, 0x229F8, 0x22A22, 0x22A4C, 0x22AA0, 0x22AC8, 0x22B1C, 0x24836, 0x229CE};

int NUM_EFFECT_ROUTINE = 11;
int NUM_STAT_UPS = 5;

void LoadMech(char *path){
	unsigned char r;
	FILE * fp = fopen(path,"rb");
	unsigned char in=0;

	fseek(fp, 0x248E0, SEEK_SET);
	fscanf(fp, "%c", &r);

	if (r == 0x4E) {
		ShowCrit = true;
	} else {
		ShowCrit = false;
	}


	fseek(fp, 0x2198B, SEEK_SET);
	fscanf(fp, "%c", &r);

	if (r == 0x12) {
		FixDoubles = true;
	} else {
		FixDoubles = false;
	}


	fseek(fp, 0x2123B, SEEK_SET);
	fscanf(fp, "%c", &r);

	if (r == 0x02) {
		FixMuddle = true;
	} else {
		FixMuddle = false;
	}

	// Load "All Classes Get Heal EXP" setting from offset 0x20CEC
	fseek(fp, 0x20CEC, SEEK_SET);
	unsigned char temp;
	fscanf(fp, "%c", &temp);
	if (temp == 0x4E) {
		AllHealEXP = true;
	}
	else {
		AllHealEXP = false;
	}


	fseek(fp, 0x20CC7, SEEK_SET);
	fscanf(fp, "%c", &HPEXPPercent);

	fseek(fp, 0x20CCF, SEEK_SET);
	fscanf(fp, "%c", &HPEXPMin);

	fseek(fp,0x17441,SEEK_SET);
	fscanf(fp,"%c",&ProLevel);

	fseek(fp, 0x20D65, SEEK_SET);
	fscanf(fp, "%c",&DetoxEXP);

	fseek(fp, 0x24D8B, SEEK_SET);
	fscanf(fp, "%c", &SleepWakeChance);

	fseek(fp, 0x20E8C, SEEK_SET);
	fscanf(fp, "%c", &EXP5Above);

	fseek(fp, 0x20E8D, SEEK_SET);
	fscanf(fp, "%c", &EXPPlus4);

	fseek(fp, 0x20E8E, SEEK_SET);
	fscanf(fp, "%c", &EXPPlus3);

	fseek(fp, 0x20E8F, SEEK_SET);
	fscanf(fp, "%c", &EXPPlus2);

	fseek(fp, 0x20E90, SEEK_SET);
	fscanf(fp, "%c", &EXPPlus1);

	fseek(fp, 0x20E91, SEEK_SET);
	fscanf(fp, "%c", &SameLevel);

	fseek(fp, 0x20E92, SEEK_SET);
	fscanf(fp, "%c", &EXPMinus1);

	fseek(fp, 0x20E93, SEEK_SET);
	fscanf(fp, "%c", &EXPMinus2);

	fseek(fp, 0x20E94, SEEK_SET);
	fscanf(fp, "%c", &EXP3Below);

	fseek(fp, 0x20CEF, SEEK_SET);
	fscanf(fp, "%c", &HealerClasses[0]); // Load first healer class
	fseek(fp, 0x20CF5, SEEK_SET);
	fscanf(fp, "%c", &HealerClasses[1]); // Load second healer class
	fseek(fp, 0x20CFB, SEEK_SET);
	fscanf(fp, "%c", &HealerClasses[2]); // Load third healer class
	fseek(fp, 0x20D01, SEEK_SET);
	fscanf(fp, "%c", &HealerClasses[3]); // Load fourth healer class

	/* effect_InflictStatus */
	fseek(fp, 0x20F94, SEEK_SET);
	fscanf(fp, "%c", &r);

	if (r == 0x74) {
		fseek(fp, 0x20F95, SEEK_SET);
		fscanf(fp, "%c", &StatusElement);
	}
	else {
		StatusElement = 0;
	}


	/* CalculateInitialStatValue */
	fseek(fp, 0x24A1A, SEEK_SET);
	fscanf(fp, "%c", &r);

	if (r == 0x4E) {
		fseek(fp, 0x14170F, SEEK_SET);
	}
	else {
		fseek(fp, 0x24A21, SEEK_SET);
	}
	fscanf(fp, "%c", &PromotePercent);


	fseek(fp,0x17361,SEEK_SET);
	fscanf(fp,"%c",&ProLevelAdd);

	fseek(fp,150742,SEEK_SET);
	fscanf(fp,"%c",&r);
	PoisonOffset = r;
	fscanf(fp,"%c",&r);
	PoisonOffset = PoisonOffset*256+r;
	fscanf(fp,"%c",&r);
	PoisonOffset = PoisonOffset*256+r;
	fscanf(fp,"%c",&r);
	PoisonOffset = PoisonOffset*256+r;

	if(PoisonOffset==0x20244){
		fseek(fp,150739,SEEK_SET);
		fscanf(fp,"%c",&Poison);
	} else {
		fseek(fp,PoisonOffset+9,SEEK_SET);
		fscanf(fp,"%c",&Poison);
	}

	fseek(fp,0x229D7,SEEK_SET);
	fscanf(fp,"%c",&LevelLimit);

	fseek(fp,0x22C37,SEEK_SET);
	fscanf(fp,"%c",&UnLevelLimit);

	fseek(fp,135485,SEEK_SET);
	fscanf(fp,"%c",&CritMult);
	CritMult/=2;

	fseek(fp,135557,SEEK_SET);
	fscanf(fp,"%c",&DamageSpread);

	fseek(fp,135579,SEEK_SET);
	fscanf(fp,"%c",&DamageBase);

	fseek(fp,0x2199D,SEEK_SET);
	fscanf(fp,"%c",&DoubleChance);
	fscanf(fp,"%c",&in);
	if(in==0x4E){
		MultiAttacks=true;
		fseek(fp,0x1AA00F,SEEK_SET);
		fscanf(fp,"%c",&MultiFalloff);
	} else {
		MultiAttacks=false;
		MultiFalloff=2;
	}

	fseek(fp,0x2110A,SEEK_SET);
	fscanf(fp,"%c",&in);
	if(in==0x4E)FixLE=true;
	else FixLE=false;

	fseek(fp,0x23D0C,SEEK_SET);
	fscanf(fp,"%c",&in);
	if(in!=0x12)HealAI=true;
	else HealAI=false;

	fseek(fp,0x24718,SEEK_SET);
	fscanf(fp,"%c",&in);
	if(in==0x4E)JogurtLevels=true;
	else JogurtLevels=false;

	fseek(fp,0x1737E,SEEK_SET);
	fscanf(fp,"%c",&in);
	if(in==0x4E)DisallowRevive=true;
	else DisallowRevive=false;

	fseek(fp,0x216A1,SEEK_SET);
	fscanf(fp,"%c",&BreakChance);

	fseek(fp,47647,SEEK_SET);
	fscanf(fp,"%c",&r);
	if(r!=0x20)RemoveMarks = false;
	else RemoveMarks = true;

	fseek(fp,0x22BD9,SEEK_SET);
	fscanf(fp,"%c",&r);
	if(r==0x63)RemoveCaps = false;
	else RemoveCaps = true;

	NUM_STAT_UPS = 5;

	fseek(fp,0x2339A,SEEK_SET);
	fscanf(fp,"%c",&in);
	if(in==0x4E){
		ExtendStatItems=true;
		fseek(fp,0x1A5514,SEEK_SET);
		fscanf(fp,"%c",&in);
		SpecialMessages[0]=in;
		fscanf(fp,"%c",&in);
		SpecialMessages[0]=SpecialMessages[0]*256+in;
		NUM_STAT_UPS++;
	} else {
		ExtendStatItems=false;
		SpecialMessages[0] = 543;
	}

	NUM_EFFECT_ROUTINE = 11;

	fseek(fp, 0x20C2C, SEEK_SET);
	fscanf(fp, "%c", &in);
	if (in == 0x4E) {
		AddMPEffect = true;
		NUM_EFFECT_ROUTINE+=2;
		fseek(fp, 0x1AA0D6, SEEK_SET);
		fscanf(fp, "%c", &in);
		SpecialMessages[2] = in;
		fscanf(fp, "%c", &in);
		SpecialMessages[2] = SpecialMessages[2] * 256 + in;

		if(SpecialMessages[2]==0xFFFF)SpecialMessages[2] = 445;
	} else {
		AddMPEffect = false;
		SpecialMessages[2] = 445;
	}

	fseek(fp,0xB457,SEEK_SET);
	fscanf(fp,"%c",&in);
	if(in!=2){
		DisplayCrit=true;
	} else {
		DisplayCrit=false;
	}


	fseek(fp,0x13908,SEEK_SET);
	fscanf(fp,"%c",&in);
	if(in==0x52){
		ItemPassing=true;
		fseek(fp,0x1C3128,SEEK_SET);
		fscanf(fp,"%c",&in);
		SpecialMessages[1]=in;
		fscanf(fp,"%c",&in);
		SpecialMessages[1]=SpecialMessages[1]*256+in;
	} else {
		ItemPassing=false;
		SpecialMessages[1] = 79;
	}

	fseek(fp, 0x7872, SEEK_SET);
	fscanf(fp, "%c", &in);
	if (in == 0x52) {
		ItemPassingBattle = true;
		fseek(fp, 0x1C31A8, SEEK_SET);
		fscanf(fp, "%c", &in);
		SpecialMessages[1] = in;
		fscanf(fp, "%c", &in);
		SpecialMessages[1] = SpecialMessages[1] * 256 + in;
	} else {
		ItemPassingBattle = false;
	}


	fseek(fp,0x22C16,SEEK_SET);
	fscanf(fp,"%c",&in);
	if(in==0x4E){
		EXPOverflow=true;
	} else {
		EXPOverflow=false;
	}

	fseek(fp,0x72F4,SEEK_SET);
	fscanf(fp,"%c",&in);
	if(in==0x4E){
		AddArmor=true;
	} else {
		AddArmor=false;
	}

	fclose(fp);
	sprintf(file,path);
}

void ImportMech(char *path){
	unsigned char r;
	FILE * fp = fopen(path,"rb");
	char in=0;

	fscanf(fp,"%c",&r);
	PoisonOffset = r;
	fscanf(fp,"%c",&r);
	PoisonOffset = PoisonOffset*256+r;
	fscanf(fp,"%c",&r);
	PoisonOffset = PoisonOffset*256+r;
	fscanf(fp,"%c",&r);
	PoisonOffset = PoisonOffset*256+r;

	fscanf(fp,"%c",&Poison);

	fclose(fp);
}

void MechImport(){
	int ret=IDYES;
	OPENFILENAME openFileName;
	char path[256];
	path[0] = '\0';    
	memset( &openFileName, 0, sizeof(openFileName) );
	openFileName.lStructSize = sizeof(openFileName);
	openFileName.hwndOwner = NULL;
	openFileName.hInstance = NULL;
	openFileName.lpstrFilter = "Shining Force Mechanics(*.sfme)\0*.sfme\0";
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
	openFileName.lpstrDefExt = "sfme";
	openFileName.lCustData = NULL;
	openFileName.lpfnHook = NULL;
	openFileName.lpTemplateName = NULL;

	if(GetOpenFileName(&openFileName)!=0){
		ImportMech(path);
	}
}