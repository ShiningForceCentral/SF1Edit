#define NUM_TILE 8713
int Tiles[NUM_TILE][18];

void LoadTile(char *path, bool single=false){
	FILE * fp = fopen(path,"rb");

	fseek(fp,534092,SEEK_SET);

	char c;

	for(int i=0; i<NUM_TILE; i++){
		for(int j=0; j<18; j++){
			if(single&&i!=select[mode]){
				fscanf(fp,"%c",&c);
				continue;
			}
			fscanf(fp,"%c",&(Tiles[i][j]));
		}
	}

	fclose(fp);
	sprintf(file,path);
}

void ImportTile(char *path){
	FILE * fp = fopen(path,"rb");

	for(int i=0; i<NUM_TILE; i++){
		for(int j=0; j<18; j++){
			fscanf(fp,"%c",&(Tiles[i][j]));
		}
	}

	fclose(fp);
}

void TileImport(){
	int ret=IDYES;
	OPENFILENAME openFileName;
	char path[256];
	path[0] = '\0';    
	memset( &openFileName, 0, sizeof(openFileName) );
	openFileName.lStructSize = sizeof(openFileName);
	openFileName.hwndOwner = NULL;
	openFileName.hInstance = NULL;
	openFileName.lpstrFilter = "Shining Force Tiles(*.sft)\0*.sft\0";
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
	openFileName.lpstrDefExt = "sft";
	openFileName.lCustData = NULL;
	openFileName.lpfnHook = NULL;
	openFileName.lpTemplateName = NULL;

	if(GetOpenFileName(&openFileName)!=0){
		ImportTile(path);
	}
}

