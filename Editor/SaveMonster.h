void SaveClass();

void SaveMonster(){
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

	int i;
	
	if(strlen(file)){

		FILE * fp = fopen(file,"rb+");

		fseek(fp, 0x16FFFF, SEEK_SET);
		fprintf(fp, "%c", NumMonsters);

		fseek(fp,MonsterNameOffset,SEEK_SET);
		for(i=0; i<NumMonsters; i++){

			if(MonsterName[i][0]==0){
				MonsterName[i][0]='-';
				MonsterName[i][1]=0;
			}

			fprintf(fp,"%c",strlen(MonsterName[i]));
			for(int j=0; j<strlen(MonsterName[i]); j++){
				fprintf(fp,"%c",MonsterName[i][j]);
			}
		}

		fseek(fp,0x21E52,SEEK_SET);
		if(MonsterDataOffset==0x2751C){
			fprintf(fp,"%c",0x42);
			fprintf(fp,"%c",0x41);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0xB9);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x02);
			fprintf(fp,"%c",0x01);
			fprintf(fp,"%c",0x40);

			fseek(fp,0x22010,SEEK_SET);
			fprintf(fp,"%c",0x02);
			fprintf(fp,"%c",0x41);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0xFF);
			fprintf(fp,"%c",0xE9);
			fprintf(fp,"%c",0x41);

			fseek(fp,0x26F50,SEEK_SET);
			fprintf(fp,"%c",0x45);
			fprintf(fp,"%c",0xFA);
			fprintf(fp,"%c",0x05);
			fprintf(fp,"%c",0xCA);
			fprintf(fp,"%c",0x21);
			fprintf(fp,"%c",0x4A);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x0C);
		} else {

			if(MonsterDataOffset>romsize-1){
				MessageBox(NULL,"Rom is too small, expand rom to use monster criticals.","Error",MB_OK);
				fclose(fp);
				return;
			}

			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0xB9);
			fprintf(fp,"%c",((MonsterDataOffset-10)&0xFF000000)/0x1000000);
			fprintf(fp,"%c",((MonsterDataOffset-10)&0x00FF0000)/0x10000);
			fprintf(fp,"%c",((MonsterDataOffset-10)&0x0000FF00)/0x100);
			fprintf(fp,"%c",((MonsterDataOffset-10)&0x000000FF));
			fprintf(fp,"%c",0x42);
			fprintf(fp,"%c",0x41);

			fseek(fp,MonsterDataOffset-10,SEEK_SET);
			fprintf(fp,"%c",0x12);
			fprintf(fp,"%c",0x2B);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x10);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0xF9);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x02);
			fprintf(fp,"%c",0x01);
			fprintf(fp,"%c",0x40);

			fseek(fp,0x26F50,SEEK_SET);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0xB9);
			fprintf(fp,"%c",((MonsterDataOffset-32)&0xFF000000)/0x1000000);
			fprintf(fp,"%c",((MonsterDataOffset-32)&0x00FF0000)/0x10000);
			fprintf(fp,"%c",((MonsterDataOffset-32)&0x0000FF00)/0x100);
			fprintf(fp,"%c",((MonsterDataOffset-32)&0x000000FF));
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0x71);

			fseek(fp,MonsterDataOffset-32,SEEK_SET);
			fprintf(fp,"%c",0x45);
			fprintf(fp,"%c",0xF9);
			fprintf(fp,"%c",((MonsterDataOffset)&0xFF000000)/0x1000000);
			fprintf(fp,"%c",((MonsterDataOffset)&0x00FF0000)/0x10000);
			fprintf(fp,"%c",((MonsterDataOffset)&0x0000FF00)/0x100);
			fprintf(fp,"%c",((MonsterDataOffset)&0x000000FF));
			fprintf(fp,"%c",0x21);
			fprintf(fp,"%c",0x4A);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x0C);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0x75);

			if(AddCritical){
				fseek(fp,0x22010,SEEK_SET);
				fprintf(fp,"%c",0x4E);
				fprintf(fp,"%c",0xB9);
				fprintf(fp,"%c",((MonsterDataOffset-20)&0xFF000000)/0x1000000);
				fprintf(fp,"%c",((MonsterDataOffset-20)&0x00FF0000)/0x10000);
				fprintf(fp,"%c",((MonsterDataOffset-20)&0x0000FF00)/0x100);
				fprintf(fp,"%c",((MonsterDataOffset-20)&0x000000FF));

				fseek(fp,MonsterDataOffset-20,SEEK_SET);
				fprintf(fp,"%c",0x02);
				fprintf(fp,"%c",0x41);
				fprintf(fp,"%c",0x00);
				fprintf(fp,"%c",0xFF);
				fprintf(fp,"%c",0xC2);
				fprintf(fp,"%c",0xFC);
				fprintf(fp,"%c",0x00);
				fprintf(fp,"%c",0x12);
				fprintf(fp,"%c",0x4E);
				fprintf(fp,"%c",0x75);
			} else {
				fseek(fp,0x22010,SEEK_SET);
				fprintf(fp,"%c",0x02);
				fprintf(fp,"%c",0x40);
				fprintf(fp,"%c",0x00);
				fprintf(fp,"%c",0xFF);
				fprintf(fp,"%c",0xE9);
				fprintf(fp,"%c",0x41);
			}

		}

		fseek(fp,MonsterDataOffset,SEEK_SET);
		for(i=0; i<NumMonsters; i++){
			for(int j=0; j<16; j++){
				fprintf(fp,"%c",Monster[i][j]);
			}
			if(AddCritical){
				fprintf(fp,"%c",Monster[i][16]);
				fprintf(fp,"%c",0);
			}
		}

		fclose(fp);
		MessageBox(NULL,"Monsters Saved","Note",MB_OK);
	}
}

void ExportMonster(char*path){
	FILE * fp = fopen(path,"wb");
	int i;
	for(i=0; i<60; i++){
		fprintf(fp,"%c",strlen(MonsterName[i]));
		for(int j=0; j<strlen(MonsterName[i]); j++){
			fprintf(fp,"%c",MonsterName[i][j]);
		}
	}
	for(i=0; i<60; i++){
		for(int j=0; j<16; j++){
			fprintf(fp,"%c",Monster[i][j]);
		}
	}
	for(i=0; i<13; i++){
		fprintf(fp,"%c",strlen(MonsterName[i+60]));
		for(int j=0; j<strlen(MonsterName[i+60]); j++){
			fprintf(fp,"%c",MonsterName[i+60][j]);
		}
	}
	for(i=0; i<13; i++){
		for(int j=0; j<16; j++){
			fprintf(fp,"%c",Monster[i+60][j]);
		}
	}
	fclose(fp);
	MessageBox(NULL,"Monsters Exported","Note",MB_OK);
}

void MonsterExport(){
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
	openFileName.Flags = OFN_OVERWRITEPROMPT | OFN_LONGNAMES | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY;
	openFileName.nFileOffset = 0;
	openFileName.nFileExtension = 0;
	openFileName.lpstrDefExt = "sfm";
	openFileName.lCustData = NULL;
	openFileName.lpfnHook = NULL;
	openFileName.lpTemplateName = NULL;

	if(GetSaveFileName(&openFileName)!=0){
		ExportMonster(path);
	}
}