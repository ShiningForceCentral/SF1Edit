unsigned char Sprites[54][32][6];
unsigned char NumSprites[54];

long SpriteOffsets[54];

void LoadSprite(char *path){
	unsigned char r;
	FILE * fp = fopen(path,"rb");
	char in;

	fseek(fp,524304,SEEK_SET);

	for(int i=0; i<54; i++){
		fscanf(fp,"%c",&r);
		SpriteOffsets[i] = r;
		fscanf(fp,"%c",&r);
		SpriteOffsets[i] = SpriteOffsets[i]*256+r;
		fscanf(fp,"%c",&r);
		SpriteOffsets[i] = SpriteOffsets[i]*256+r;
		fscanf(fp,"%c",&r);
		SpriteOffsets[i] = SpriteOffsets[i]*256+r;
	}

	for(i=0; i<54; i++){
		fseek(fp,SpriteOffsets[i],SEEK_SET);
		int j=0;
		while(true){
			fscanf(fp,"%c",&in);
			if(in==-1||feof(fp)){
				fscanf(fp,"%c",&in);
				break;
			}
			Sprites[i][j][0]=in;
			for(int k=0;k<5;k++){
				fscanf(fp,"%c",&(Sprites[i][j][k+1]));
			}
			j++;
		}
		NumSprites[i]=j;
	}

	fclose(fp);
	sprintf(file,path);
}

void ImportSprite(char *path){
	unsigned char r;
	FILE * fp = fopen(path,"rb");
	char in;
	for(int i=0; i<54; i++){
		int j=0;
		while(true){
			fscanf(fp,"%c",&in);
			if(in==-1||feof(fp)){
				fscanf(fp,"%c",&in);
				break;
			}
			Sprites[i][j][0]=in;
			for(int k=0;k<5;k++){
				fscanf(fp,"%c",&(Sprites[i][j][k+1]));
			}
			j++;
		}
		NumSprites[i]=j;
	}
	fclose(fp);
}

void SpriteImport(){
	int ret=IDYES;
	OPENFILENAME openFileName;
	char path[256];
	path[0] = '\0';    
	memset( &openFileName, 0, sizeof(openFileName) );
	openFileName.lStructSize = sizeof(openFileName);
	openFileName.hwndOwner = NULL;
	openFileName.hInstance = NULL;
	openFileName.lpstrFilter = "Shining Force Sprites(*.sfsp)\0*.sfsp\0";
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
	openFileName.lpstrDefExt = "sfsp";
	openFileName.lCustData = NULL;
	openFileName.lpfnHook = NULL;
	openFileName.lpTemplateName = NULL;

	if(GetOpenFileName(&openFileName)!=0){
		ImportSprite(path);
	}
}

