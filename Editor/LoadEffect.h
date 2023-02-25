unsigned char Effect[256][8];

char EffectRoutineName[][32] = {"Heal","Cure Poison (Item)","Cure Poison (Spell)","Physical Attack","Doom Blade Attack","Physical Elemental Attack","Magical Elemental Attack","Status Effect","Desoul","Demon Rod","Max Stat Increase","MP Refill","Distributed Damage" };
unsigned long EffectRoutineOffset[] = {0x34,0xFC,0x102,0x160,0x2DA,0x2F6,0x2FE,0x36C,0x418,0x45C,0x4BE,0xEEEE,0xDDDD};

char StatusEffectName[][16] = { "Quick","Slow","Boost","Dispel","Shield","Muddle","Sleep","Poison","Curse","Jogurt" };
char StatUps[][16] = { "Attack", "Defense", "Move", "Agility", "HP", "MP" };
char EffectTypes[][16] = { "Attack", "Attack+Spell", "Spell", "None/Item", "?" };
char EffectResist[][16] = { "Blaze", "Freeze", "Bolt", "Sleep/Desoul", "Muddle","Slow","?","None" };

char EffectCrit[][16] = { "3%","4%","6%" };

char EffectAction = -1;
char EffectType = -1;

//long EffectOffset; Moved so mech editor had accesss
int NumEffects;

void LoadEffect(char *path, bool single=false){
	FILE * fp = fopen(path,"rb");
	char in=0;
	char c;


	fseek(fp,0x20C22,SEEK_SET);
	fscanf(fp,"%c",&in);

	if(in!=0x4E){
		EffectOffset = 0x20A04;
		if(!single)NumEffects = 59;
	} else {
		EffectOffset = 0x1AA120;
		fseek(fp,0x1AA110,SEEK_SET);
		if(!single)fscanf(fp,"%c",&NumEffects);
	}

	fseek(fp,EffectOffset,SEEK_SET);
	for(int i=0;i<NumEffects;i++){
		for(int j=0;j<8;j++){
			if(single&&i!=subfocus+30*select[mode]){
				fscanf(fp,"%c",&c);
				continue;
			}
			fscanf(fp,"%c",&(Effect[i][j]));
		}
	}

	fclose(fp);
	sprintf(file,path);
}

void ImportEffect(char *path){
	FILE * fp = fopen(path,"rb");
	char in=0;

	for(int i=0;i<59;i++){
		for(int j=0;j<8;j++){
			fscanf(fp,"%c",&(Effect[i][j]));
		}
	}

	fclose(fp);
}

void EffectImport(){
	int ret=IDYES;
	OPENFILENAME openFileName;
	char path[256];
	path[0] = '\0';    
	memset( &openFileName, 0, sizeof(openFileName) );
	openFileName.lStructSize = sizeof(openFileName);
	openFileName.hwndOwner = NULL;
	openFileName.hInstance = NULL;
	openFileName.lpstrFilter = "Shining Force Effect(*.sfe)\0*.sfe\0";
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
	openFileName.lpstrDefExt = "sfe";
	openFileName.lCustData = NULL;
	openFileName.lpfnHook = NULL;
	openFileName.lpTemplateName = NULL;

	if(GetOpenFileName(&openFileName)!=0){
		ImportEffect(path);
	}
}