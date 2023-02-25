void SaveEffect(){
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
		FILE * fp = fopen(file,"rb+");

		if(EffectOffset>romsize-1){
			MessageBox(NULL,"Rom is too small, expand rom or use a smaller offset.","Error",MB_OK);
			fclose(fp);
			return;
		}

		if(EffectOffset!=0x20A04){
			fseek(fp,0x20C22,SEEK_SET);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0xB9);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x1A);
			fprintf(fp,"%c",0xA1);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0x71);
			fseek(fp,0x1AA100,SEEK_SET);
			fprintf(fp,"%c",0x02);
			fprintf(fp,"%c",0x45);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0xFF);
			fprintf(fp,"%c",0x41);
			fprintf(fp,"%c",0xF9);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x1A);
			fprintf(fp,"%c",0xA1);
			fprintf(fp,"%c",0x20);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0x75);
			fseek(fp,0x1AA110,SEEK_SET);
			fprintf(fp,"%c",NumEffects);
		}

		fseek(fp,EffectOffset,SEEK_SET);
		for(int i=0;i<NumEffects;i++){
			for(int j=0;j<8;j++){
				fprintf(fp,"%c",Effect[i][j]);
			}
		}

		fclose(fp);
		MessageBox(NULL,"Effects Saved","Note",MB_OK);
	}
}

void ExportEffect(char*path){
	FILE * fp = fopen(path,"wb");

	for(int i=0;i<59;i++){
		for(int j=0;j<8;j++){
			fprintf(fp,"%c",Effect[i][j]);
		}
	}

	fclose(fp);
	MessageBox(NULL,"Effects Exported","Note",MB_OK);
}

void EffectExport(){
	OPENFILENAME openFileName;
	char path[256];
	path[0] = '\0';  
	memset( &openFileName, 0, sizeof(openFileName) );
	openFileName.lStructSize = sizeof(openFileName);
	openFileName.hwndOwner = NULL;
	openFileName.hInstance = NULL;
	openFileName.lpstrFilter = "Shining Force Effects(*.sfe)\0*.sfe\0";
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
	openFileName.lpstrDefExt = "sfe";
	openFileName.lCustData = NULL;
	openFileName.lpfnHook = NULL;
	openFileName.lpTemplateName = NULL;

	if(GetSaveFileName(&openFileName)!=0){
		ExportEffect(path);
	}
}