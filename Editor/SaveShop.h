void SaveShop(){
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
		unsigned char j;
		int i;

		FILE * fp = fopen(file,"rb+");

		fseek(fp,ShopOffset,SEEK_SET);

		if(ShopOffset>romsize-1){
			MessageBox(NULL,"Rom is too small, expand rom to save added items.","Error",MB_OK);
			fclose(fp);
			return;
		}

		for(i=0; i<12; i++){
			fprintf(fp,"%c",ShopTypes[i*2]);
			j=0;
			while(ShopItems[i*2][j]!=-1&&j<32){
				fprintf(fp,"%c",ShopItems[i*2][j]);
				j++;
			}
			fprintf(fp,"%c",255);
			fprintf(fp,"%c",ShopTypes[i*2+1]);
			j=0;
			while(ShopItems[i*2+1][j]!=-1&&j<32){
				fprintf(fp,"%c",ShopItems[i*2+1][j]);
				j++;
			}
			fprintf(fp,"%c",255);
		}

		unsigned int o=0;

		if(ShopOffset==0x16F92){
			fseek(fp,0x16F24,SEEK_SET);
			fprintf(fp,"%c",0x30);
			fprintf(fp,"%c",0x3B);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x3C);
			fprintf(fp,"%c",0x41);
			fprintf(fp,"%c",0xFB);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x68);

			fseek(fp,0x16F62,SEEK_SET);

		} else {
			fseek(fp,0x16F24,SEEK_SET);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0xB9);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x1C);
			fprintf(fp,"%c",0x02);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0x71);

			fseek(fp,0x1C0200,SEEK_SET);
			fprintf(fp,"%c",0x30);
			fprintf(fp,"%c",0x3B);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x08);
			fprintf(fp,"%c",0x41);
			fprintf(fp,"%c",0xFB);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x60);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0x75);
		}

		for(i=0;i<24;i++){
			fprintf(fp,"%c",(o&0xFF00)/0x100);
			fprintf(fp,"%c",(o&0xFF));
			j=0;
			while(ShopItems[i][j]!=-1&&j<32){
				o++;
				j++;
			}	
			o+=2;;
		}

		fclose(fp);
		MessageBox(NULL,"Shops Saved","Note",MB_OK);
	}
}

void ExportShop(char*path){
	FILE * fp = fopen(path,"wb");
	unsigned char j;

	for(int i=0; i<12; i++){
		fprintf(fp,"%c",ShopTypes[i*2]);
		j=0;
		while(ShopItems[i*2][j]!=-1&&j<32){
			fprintf(fp,"%c",ShopItems[i*2][j]);
			j++;
		}
		fprintf(fp,"%c",255);
		fprintf(fp,"%c",ShopTypes[i*2+1]);
		j=0;
		while(ShopItems[i*2+1][j]!=-1&&j<32){
			fprintf(fp,"%c",ShopItems[i*2+1][j]);
			j++;
		}
		fprintf(fp,"%c",255);
	}

	fclose(fp);
	MessageBox(NULL,"Shops Exported","Note",MB_OK);
}

void ShopExport(){
	OPENFILENAME openFileName;
	char path[256];
	path[0] = '\0';  
	memset( &openFileName, 0, sizeof(openFileName) );
	openFileName.lStructSize = sizeof(openFileName);
	openFileName.hwndOwner = NULL;
	openFileName.hInstance = NULL;
	openFileName.lpstrFilter = "Shining Force Shops(*.sfsh)\0*.sfsh\0";
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
	openFileName.lpstrDefExt = "sfb";
	openFileName.lCustData = NULL;
	openFileName.lpfnHook = NULL;
	openFileName.lpTemplateName = NULL;

	if(GetSaveFileName(&openFileName)!=0){
		ExportShop(path);
	}
}