unsigned char Spell[32][32];
char SpellName[33][24];
unsigned char SpellImages[32][384];

long SpellTargeting[32];

long SpellNameOffset;
long SpellOffset;
long SpellImagesOffset;
long SpellTargetOffset;

bool ExpandSpells;

//132040 name pointer
//132044 data pointer
//835616 images pointer

void LoadSpell(char *path, bool single=false){
	unsigned char r,c;
	FILE * fp = fopen(path,"rb");
	int i;

	fseek(fp,132040,SEEK_SET);
	fscanf(fp,"%c",&r);
	SpellNameOffset = r;
	fscanf(fp,"%c",&r);
	SpellNameOffset = SpellNameOffset*256+r;
	fscanf(fp,"%c",&r);
	SpellNameOffset = SpellNameOffset*256+r;
	fscanf(fp,"%c",&r);
	SpellNameOffset = SpellNameOffset*256+r;

	if(SpellNameOffset!=0x26404){
		ExpandSpells=true;
		SpellTargetOffset = 0x1C0100;
		fseek(fp,SpellTargetOffset,SEEK_SET);
		fscanf(fp,"%c",&r);
		if(r==0xFF)SpellTargetOffset = 0x2409C;
	} else {
		ExpandSpells=false;
		SpellTargetOffset = 0x2409C;
	}

	fseek(fp,SpellTargetOffset,SEEK_SET);
	for(i=0; i<16+16*ExpandSpells; i++){
		fscanf(fp,"%c",&r);
		fscanf(fp,"%c",&c);
		if(single&&i!=select[mode]){
			continue;
		}
		SpellTargeting[i] = r*256;
		SpellTargeting[i]+=c;

		if(SpellTargeting[i]==65535||(i>15&&SpellTargetOffset==0x2409C))SpellTargeting[i]=0x47A-2*i;
	}

	fseek(fp,SpellNameOffset,SEEK_SET);
	for(i=0; i<16+16*ExpandSpells; i++){
		fscanf(fp,"%c",&r);
		for(int j=0; j<r; j++){
			if(single&&i!=select[mode]){
				fscanf(fp,"%c",&c);
				continue;
			}
			fscanf(fp,"%c",&(SpellName[i][j]));
			if(SpellName[i][j]==9)SpellName[i][j]=32;
		}
		if(!single||i==select[mode])SpellName[i][r]='\0';
	}

	fseek(fp,132044,SEEK_SET);
	fscanf(fp,"%c",&r);
	SpellOffset = r;
	fscanf(fp,"%c",&r);
	SpellOffset = SpellOffset*256+r;
	fscanf(fp,"%c",&r);
	SpellOffset = SpellOffset*256+r;
	fscanf(fp,"%c",&r);
	SpellOffset = SpellOffset*256+r;

	fseek(fp,SpellOffset,SEEK_SET);
	for(i=0; i<16+16*ExpandSpells; i++){
		for(int j=0; j<16; j++){
			if(single&&i!=select[mode]){
				fscanf(fp,"%c",&c);
				continue;
			}
			fscanf(fp,"%c",&(Spell[i][j]));
		}
	}

	fseek(fp,835616,SEEK_SET);
	fscanf(fp,"%c",&r);
	SpellImagesOffset = r;
	fscanf(fp,"%c",&r);
	SpellImagesOffset = SpellImagesOffset*256+r;
	fscanf(fp,"%c",&r);
	SpellImagesOffset = SpellImagesOffset*256+r;
	fscanf(fp,"%c",&r);
	SpellImagesOffset = SpellImagesOffset*256+r;

	fseek(fp,SpellImagesOffset,SEEK_SET);
	for(i=0; i<16+16*ExpandSpells; i++){
		for(int c=0; c<6; c++){
			for(int j=0; j<32; j++){
				fscanf(fp,"%c",&r);
				if(single&&i!=select[mode]){
					continue;
				}
				int k=j*2;
				SpellImages[i][c%2*8+(c-c%2)*64+k%8+(k-k%8)*2+1]=r%16;
				r-=r%16;
				r/=16;
				SpellImages[i][c%2*8+(c-c%2)*64+k%8+(k-k%8)*2]=r;
			}
		}
	}

	fclose(fp);
	sprintf(file,path);
}

void ImportSpell(char *path){
	unsigned char r;
	FILE * fp = fopen(path,"rb");
	int i;
	for(i=0; i<16; i++){
		fscanf(fp,"%c",&r);
		for(int j=0; j<r; j++){
			fscanf(fp,"%c",&(SpellName[i][j]));
			if(SpellName[i][j]==9)SpellName[i][j]=32;
		}
		SpellName[i][r]='\0';
	}
	for(i=0; i<16; i++){
		for(int j=0; j<16; j++){
			fscanf(fp,"%c",&(Spell[i][j]));
		}
	}
	for(i=0; i<16; i++){
		for(int c=0; c<6; c++){
			for(int j=0; j<32; j++){
				fscanf(fp,"%c",&r);
				int k=j*2;
				SpellImages[i][c%2*8+(c-c%2)*64+k%8+(k-k%8)*2+1]=r%16;
				r-=r%16;
				r/=16;
				SpellImages[i][c%2*8+(c-c%2)*64+k%8+(k-k%8)*2]=r;
			}
		}
	}
	fclose(fp);
}

void SpellImport(){
	int ret=IDYES;
	OPENFILENAME openFileName;
	char path[256];
	path[0] = '\0';    
	memset( &openFileName, 0, sizeof(openFileName) );
	openFileName.lStructSize = sizeof(openFileName);
	openFileName.hwndOwner = NULL;
	openFileName.hInstance = NULL;
	openFileName.lpstrFilter = "Shining Force Spells(*.sfs)\0*.sfs\0";
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
	openFileName.lpstrDefExt = "sfs";
	openFileName.lCustData = NULL;
	openFileName.lpfnHook = NULL;
	openFileName.lpTemplateName = NULL;

	if(GetOpenFileName(&openFileName)!=0){
		ImportSpell(path);
	}
}


void PasteSelectedSpell() {
	unsigned int size[2] = { 16,24 };

	FromClipboard(SpellImages[select[mode]], size, IconPalette);
}