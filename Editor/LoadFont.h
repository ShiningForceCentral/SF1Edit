int Font[80][32];

void LoadFont(char *path, bool single=false){
	char c;
	FILE * fp = fopen(path,"rb");
	fseek(fp,180543,SEEK_SET);
	for(int i=0; i<80; i++){
		for(int j=0; j<32; j++){
			if(single&&i!=select[mode]){
				fscanf(fp,"%c",&c);
				continue;
			}
			fscanf(fp,"%c",&(Font[i][j]));
			if(j==0){
				if(Font[i][j]>128)Font[i][j]-=256;
			}
		}
	}
	fclose(fp);
	sprintf(file,path);
}

void ImportFont(char *path){
	FILE * fp = fopen(path,"rb");
	for(int i=0; i<80; i++){
		for(int j=0; j<32; j++){
			fscanf(fp,"%c",&(Font[i][j]));
		}
	}
	fclose(fp);
}

void FontImport(){
	int ret=IDYES;
	OPENFILENAME openFileName;
	char path[256];
	path[0] = '\0';    
	memset( &openFileName, 0, sizeof(openFileName) );
	openFileName.lStructSize = sizeof(openFileName);
	openFileName.hwndOwner = NULL;
	openFileName.hInstance = NULL;
	openFileName.lpstrFilter = "Shining Force Font(*.sff)\0*.sff\0";
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
	openFileName.lpstrDefExt = "sff";
	openFileName.lCustData = NULL;
	openFileName.lpfnHook = NULL;
	openFileName.lpTemplateName = NULL;

	if(GetOpenFileName(&openFileName)!=0){
		ImportFont(path);
	}
}