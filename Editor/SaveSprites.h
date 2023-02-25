void SaveSprite(){
	if(!strlen(file)){
		int ret=IDYES;
		OPENFILENAME openFileName;
		char path[256];
		path[0] = '\0';    
		memset( &openFileName, 0, sizeof(openFileName) );
		openFileName.lStructSize = sizeof(openFileName);
		openFileName.hwndOwner = NULL;
		openFileName.hInstance = NULL;
		openFileName.lpstrFilter = "Genesis ROM(*.bin)\0*.bin\0";
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
		openFileName.lpstrDefExt = "bin";
		openFileName.lCustData = NULL;
		openFileName.lpfnHook = NULL;
		openFileName.lpTemplateName = NULL;

		if(GetOpenFileName(&openFileName)!=0){
			sprintf(file,path);
		}
	}

	
	if(strlen(file)){
		unsigned char r;
		FILE * fp = fopen(file,"rb+");

		for(int i=0; i<54; i++){
			fseek(fp,SpriteOffsets[i],SEEK_SET);
			for(int j=0; j<NumSprites[i]; j++){
				for(int k=0;k<6;k++){
					fprintf(fp,"%c",Sprites[i][j][k]);
				}
			}
			fprintf(fp,"%c",255);
			fprintf(fp,"%c",255);
		}

		fclose(fp);
		MessageBox(NULL,"Sprites Saved","Note",MB_OK);
	}
}

void ExportSprite(char*path){
	FILE * fp = fopen(path,"wb");

	for(int i=0; i<54; i++){
		for(int j=0; j<NumSprites[i]; j++){
			for(int k=0;k<6;k++){
				fprintf(fp,"%c",Sprites[i][j][k]);
			}
		}
		fprintf(fp,"%c",255);
		fprintf(fp,"%c",255);
	}

	fclose(fp);
	MessageBox(NULL,"Sprites Exported","Note",MB_OK);
}

void SpriteExport(){
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
	openFileName.Flags = OFN_OVERWRITEPROMPT | OFN_LONGNAMES | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY;
	openFileName.nFileOffset = 0;
	openFileName.nFileExtension = 0;
	openFileName.lpstrDefExt = "sfsp";
	openFileName.lCustData = NULL;
	openFileName.lpfnHook = NULL;
	openFileName.lpTemplateName = NULL;

	if(GetSaveFileName(&openFileName)!=0){
		ExportSprite(path);
	}
}