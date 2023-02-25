void SaveClass(){
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
		unsigned char r;
		FILE * fp = fopen(file,"rb+");

		if (NumMonsters == 146 || NumClasses == 64) {
			ClassOffset = 0x1E2000;
			ClassNamesOffset = 0x1DC000;
		}
		
		if(ClassOffset+10000>romsize){
			MessageBox(NULL,"Rom is too small, expand rom to save class changes.","Error",MB_OK);
			fclose(fp);
			return;
		}
		
		

		



		fseek(fp, 0x22C3E, SEEK_SET);
		if (NumClasses == 64) {
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0xB9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x1F);
			fprintf(fp, "%c", 0xFD);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0x71);

			fseek(fp, 0x1FFD00, SEEK_SET);

			fprintf(fp, "%c", 0x48);
			fprintf(fp, "%c", 0xE7);
			fprintf(fp, "%c", 0xC0);
			fprintf(fp, "%c", 0x00);

			fprintf(fp, "%c", 0x10);
			fprintf(fp, "%c", 0x01);

			fprintf(fp, "%c", 0x43);
			fprintf(fp, "%c", 0xF9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x16);
			fprintf(fp, "%c", 0xFE);
			fprintf(fp, "%c", 0x20);
			
			fprintf(fp, "%c", 0x12);
			fprintf(fp, "%c", 0x31);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x00);

			fprintf(fp, "%c", 0x0C);
			fprintf(fp, "%c", 0x01);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0xFF);

			fprintf(fp, "%c", 0x67);
			fprintf(fp, "%c", 0x02);
			fprintf(fp, "%c", 0x74);
			fprintf(fp, "%c", 0x63);


			fprintf(fp, "%c", 0x4C);
			fprintf(fp, "%c", 0xDF);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x03);

			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0x75);

		} else {
			fprintf(fp, "%c", 0x0C);
			fprintf(fp, "%c", 0x41);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x0E);
			fprintf(fp, "%c", 0x65);
			fprintf(fp, "%c", 0x02);
			fprintf(fp, "%c", 0x74);
			fprintf(fp, "%c", 0x63);


		}


		fseek(fp, 0x22F8E, SEEK_SET);
		if (NumClasses == 32) {
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x02);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x78);
			fprintf(fp, "%c", 0x26);
			fprintf(fp, "%c", 0x11);
		} else {
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x16);
			fprintf(fp, "%c", 0xFF);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0x71);

			fseek(fp, 0x16FF00, SEEK_SET);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0xB9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x02);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x78);
			fprintf(fp, "%c", 0x0C);
			fprintf(fp, "%c", 0x01);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x20);
			fprintf(fp, "%c", 0x6C);
			fprintf(fp, "%c", 0x04);
			fprintf(fp, "%c", 0x26);
			fprintf(fp, "%c", 0x11);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0x75);
			fprintf(fp, "%c", 0x26);
			fprintf(fp, "%c", 0x29);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x10);
			fprintf(fp, "%c", 0x04);
			fprintf(fp, "%c", 0x41);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x20);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0x75);

		}

		if (NumClasses == 64) {
			fseek(fp, 0x16FE20, SEEK_SET);
			for (i = 0; i < 64; i++) {
				fprintf(fp, "%c", ClassPromote[i]);
			}

			fseek(fp, 0x1744C, SEEK_SET);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x16);
			fprintf(fp, "%c", 0xFD);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0x71);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0x71);
			fprintf(fp, "%c", 0x67);

			fseek(fp, 0x16FD00, SEEK_SET);
			fprintf(fp, "%c", 0x48);
			fprintf(fp, "%c", 0xE7);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x80);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0xB9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x16);
			fprintf(fp, "%c", 0xFE);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x0C);
			fprintf(fp, "%c", 0x01);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0xFF);
			fprintf(fp, "%c", 0x4C);
			fprintf(fp, "%c", 0xDF);
			fprintf(fp, "%c", 0x01);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0x75);

			fseek(fp, 0x2492A, SEEK_SET);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x16);
			fprintf(fp, "%c", 0xFE);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0x71);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0x71);

			fseek(fp, 0x16FE00, SEEK_SET);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0xB9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x02);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x78);
			fprintf(fp, "%c", 0x41);
			fprintf(fp, "%c", 0xF9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x16);
			fprintf(fp, "%c", 0xFE);
			fprintf(fp, "%c", 0x20);
			fprintf(fp, "%c", 0xD0);
			fprintf(fp, "%c", 0xC1);
			fprintf(fp, "%c", 0x12);
			fprintf(fp, "%c", 0x10);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0x75);
		} else {
			fseek(fp, 0x1744C, SEEK_SET);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x02);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x78);
			fprintf(fp, "%c", 0x0C);
			fprintf(fp, "%c", 0x41);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x0D);
			fprintf(fp, "%c", 0x6E);

			fseek(fp, 0x2492A, SEEK_SET);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x02);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x78);
			fprintf(fp, "%c", 0x06);
			fprintf(fp, "%c", 0x41);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x10);
		}
		if (NumClasses == 64) {
			fseek(fp, 0x2438A, SEEK_SET);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0xB9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x16);
			fprintf(fp, "%c", 0xFD);
			fprintf(fp, "%c", 0x20);

			fseek(fp, 0x16FD20, SEEK_SET);
			fprintf(fp, "%c", 0x41);
			fprintf(fp, "%c", 0xF9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x16);
			fprintf(fp, "%c", 0xFD);
			fprintf(fp, "%c", 0x40);
			fprintf(fp, "%c", 0x30);
			fprintf(fp, "%c", 0x11);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0x75);

			fseek(fp, 0x16FD40, SEEK_SET);
		} else {
			fseek(fp, 0x2438A, SEEK_SET);
			fprintf(fp, "%c", 0x41);
			fprintf(fp, "%c", 0xFA);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x1E);
			fprintf(fp, "%c", 0x30);
			fprintf(fp, "%c", 0x11);

			fseek(fp, 0x243AA, SEEK_SET);

		}
		for(i=0; i<NumClasses; i++){
			fprintf(fp,"%c",Priority[i]);
		}

		fseek(fp,132032,SEEK_SET);
		fprintf(fp,"%c",(ClassNamesOffset&0xFF000000)/0x1000000);
		fprintf(fp,"%c",(ClassNamesOffset&0x00FF0000)/0x10000);
		fprintf(fp,"%c",(ClassNamesOffset&0x0000FF00)/0x100);
		fprintf(fp,"%c",(ClassNamesOffset&0x000000FF));

		MonsterNameOffset = ClassNamesOffset;


		fseek(fp,ClassNamesOffset,SEEK_SET);
		for(i=0; i<NumClasses; i++){
			r=strlen(Classes[i]);
			MonsterNameOffset+=r+1;
			fprintf(fp,"%c",r);
			for(int j=0; j<r; j++){
				fprintf(fp,"%c",Classes[i][j]);
			}
			Classes[i][r]='\0';
		}

		fseek(fp,132036,SEEK_SET);
		fprintf(fp,"%c",(ClassOffset&0xFF000000)/0x1000000);
		fprintf(fp,"%c",(ClassOffset&0x00FF0000)/0x10000);
		fprintf(fp,"%c",(ClassOffset&0x0000FF00)/0x100);
		fprintf(fp,"%c",(ClassOffset&0x000000FF));

		fseek(fp,ClassOffset,SEEK_SET);
		for(i=0; i<NumClasses +NumMonsters; i++){
			for(int j=0;j<8;j++){
				fprintf(fp,"%c",ClassData[i][j]);
			}
		}

		fclose(fp);
		MessageBox(NULL,"Classes Saved","Note",MB_OK);
	}
}

void ExportClass(char*path){
	FILE * fp = fopen(path,"wb");
	int i;
	unsigned char r;
	fprintf(fp,"%c",(ClassNamesOffset&0xFF000000)/0x1000000);
	fprintf(fp,"%c",(ClassNamesOffset&0x00FF0000)/0x10000);
	fprintf(fp,"%c",(ClassNamesOffset&0x0000FF00)/0x100);
	fprintf(fp,"%c",(ClassNamesOffset&0x000000FF));

	for(i=0; i<32; i++){
		r=strlen(Classes[i]);
		fprintf(fp,"%c",r);
		for(int j=0; j<r; j++){
			fprintf(fp,"%c",Classes[i][j]);
		}
		Classes[i][r]='\0';
	}

	fprintf(fp,"%c",(ClassOffset&0xFF000000)/0x1000000);
	fprintf(fp,"%c",(ClassOffset&0x00FF0000)/0x10000);
	fprintf(fp,"%c",(ClassOffset&0x0000FF00)/0x100);
	fprintf(fp,"%c",(ClassOffset&0x000000FF));

	for(i=0; i<105; i++){
		for(int j=0;j<8;j++){
			fprintf(fp,"%c",ClassData[i][j]);
		}
	}
	fclose(fp);
	MessageBox(NULL,"Classes Exported","Note",MB_OK);
}

void ClassExport(){
	OPENFILENAME openFileName;
	char path[256];
	path[0] = '\0';  
	memset( &openFileName, 0, sizeof(openFileName) );
	openFileName.lStructSize = sizeof(openFileName);
	openFileName.hwndOwner = NULL;
	openFileName.hInstance = NULL;
	openFileName.lpstrFilter = "Shining Force Classes(*.sfcl)\0*.sfcl\0";
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
	openFileName.lpstrDefExt = "sfcl";
	openFileName.lCustData = NULL;
	openFileName.lpfnHook = NULL;
	openFileName.lpTemplateName = NULL;

	if(GetSaveFileName(&openFileName)!=0){
		ExportClass(path);
	}
}