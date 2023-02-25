unsigned char Monster[146][17];
char MonsterName[146][20];

long MonsterNameOffset;

long MonsterDataOffset;

bool AddCritical;

int NumMonsters;
unsigned char NumClasses;

int MonsterView = 0;

void LoadMonster(char *path, bool single=false){
	unsigned char r,c;
	FILE * fp = fopen(path,"rb");

	fseek(fp,132032,SEEK_SET);
	fscanf(fp,"%c",&r);
	MonsterNameOffset = r;
	fscanf(fp,"%c",&r);
	MonsterNameOffset = MonsterNameOffset*256+r;
	fscanf(fp,"%c",&r);
	MonsterNameOffset = MonsterNameOffset*256+r;
	fscanf(fp,"%c",&r);
	MonsterNameOffset = MonsterNameOffset*256+r;

	fseek(fp, 0x16FFFF, SEEK_SET);
	fscanf(fp, "%c", &r);


	if(MonsterNameOffset==0x25D6C)
		NumMonsters=73;
	else {
		if(r == 0xFF)
			NumMonsters = 146;
		else
			NumMonsters = r;
	}

	fseek(fp,MonsterNameOffset,SEEK_SET);
	for(int i=0; i<NumClasses; i++){
		fscanf(fp,"%c",&r);
		MonsterNameOffset+=r+1;
		for(int j=0; j<r; j++){
			fscanf(fp,"%c",&c);
		}
	}

	fseek(fp,MonsterNameOffset,SEEK_SET);
	int i;
	for(i=0; i<NumMonsters; i++){
		fscanf(fp,"%c",&r);
		for(int j=0; j<r; j++){
			if(single&&i!=select[mode]){
				fscanf(fp,"%c",&c);
				continue;
			}
			fscanf(fp,"%c",&(MonsterName[i][j]));
			if(MonsterName[i][j]==9)MonsterName[i][j]=32;
		}
		if(!single||i==select[mode])MonsterName[i][r]='\0';
	}

	

	fseek(fp,0x21E57,SEEK_SET);
	fscanf(fp,"%c",&r);
	if(r!=2){
		AddCritical=true;
		fseek(fp,0x21E54,SEEK_SET);
		fscanf(fp,"%c",&r);
		MonsterDataOffset = r;
		fscanf(fp,"%c",&r);
		MonsterDataOffset = MonsterDataOffset*256+r;
		fscanf(fp,"%c",&r);
		MonsterDataOffset = MonsterDataOffset*256+r;
		fscanf(fp,"%c",&r);
		MonsterDataOffset = MonsterDataOffset*256+r;

		MonsterDataOffset+=10;
	} else {
		AddCritical=false;
		MonsterDataOffset = 0x2751C;
	}

	fseek(fp,MonsterDataOffset,SEEK_SET);
	for(i=0; i<NumMonsters; i++){
		for(int j=0; j<16; j++){
			if(single&&i!=select[mode]){
				fscanf(fp,"%c",&c);
				continue;
			}
			fscanf(fp,"%c",&(Monster[i][j]));
		}
		if(AddCritical){
			if(single&&i!=select[mode]){
				fscanf(fp,"%c",&c);
				fscanf(fp,"%c",&c);
				continue;
			}
			fscanf(fp,"%c",&(Monster[i][16]));
			fscanf(fp,"%c",&r);
		}
		else Monster[i][16]=0;
	}

	fclose(fp);
	sprintf(file,path);
}

void ImportMonster(char *path){
	unsigned char r;
	FILE * fp = fopen(path,"rb");
	int i;
	for(i=0; i<60; i++){
		fscanf(fp,"%c",&r);
		for(int j=0; j<r; j++){
			fscanf(fp,"%c",&(MonsterName[i][j]));
			if(MonsterName[i][j]==9)MonsterName[i][j]=32;
		}
		MonsterName[i][r]='\0';
	}
	for(i=0; i<60; i++){
		for(int j=0; j<16; j++){
			fscanf(fp,"%c",&(Monster[i][j]));
		}
	}
	if(feof(fp)){
		fclose(fp);
		return;
	}
	for(i=0; i<13; i++){
		fscanf(fp,"%c",&r);
		for(int j=0; j<r; j++){
			fscanf(fp,"%c",&(MonsterName[i+60][j]));
			if(MonsterName[i][j]==9)MonsterName[i+60][j]=32;
		}
		MonsterName[i][r]='\0';
	}
	for(i=0; i<13; i++){
		for(int j=0; j<16; j++){
			fscanf(fp,"%c",&(Monster[i+60][j]));
		}
	}
	fclose(fp);
}

void MonsterImport(){
	int ret=IDYES;
	OPENFILENAME openFileName;
	char path[256];
	path[0] = '\0';    
	memset( &openFileName, 0, sizeof(openFileName) );
	openFileName.lStructSize = sizeof(openFileName);
	openFileName.hwndOwner = NULL;
	openFileName.hInstance = NULL;
	openFileName.lpstrFilter = "Shining Force Monsters(*.sfm)\0*.sfm\0";
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
	openFileName.lpstrDefExt = "sfm";
	openFileName.lCustData = NULL;
	openFileName.lpfnHook = NULL;
	openFileName.lpTemplateName = NULL;

	if(GetOpenFileName(&openFileName)!=0){
		ImportMonster(path);
	}
}
