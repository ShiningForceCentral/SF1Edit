void SavePalette(){
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
		int o,o2;

		unsigned int pal[2];
		unsigned int frame[16];

		FILE * fp = fopen(file,"rb+");

		if (NumItems == 128 && 0x200000>romsize) {
			MessageBox(NULL, "Rom is too small, expand rom.", "Error", MB_OK);
			fclose(fp);
			return;
		}

		GFXPaletteEdit = false;

		fseek(fp,14732,SEEK_SET);
		writePalette(IconPalette,16,fp);
		
		fseek(fp,39438,SEEK_SET);
		writePalette(FMSPalette,16,fp);
		writePalette(EMSPalette,16,fp);

		fseek(fp, 0x11EE0, SEEK_SET);
		writePalette(EMSPalette, 16, fp);

		//fseek(fp, 0xC57C4, SEEK_SET);
		//writePalette(TitlePalette, 16, fp);

		//o = 0x100008;
		fseek(fp, 0x100000, SEEK_SET);
		fscanf(fp, "%c", &r);
		o = r;
		fscanf(fp, "%c", &r);
		o = o * 256 + r;
		fscanf(fp, "%c", &r);
		o = o * 256 + r;
		fscanf(fp, "%c", &r);
		o = o * 256 + r;

		int s;
		for(s=0;s<NumGFX[1];s++){

			fseek(fp,o,SEEK_SET);
			fscanf(fp,"%c",&r);
			o2 = r;
			fscanf(fp,"%c",&r);
			o2 = o2*256+r;
			fscanf(fp,"%c",&r);
			o2 = o2*256+r;
			fscanf(fp,"%c",&r);
			o2 = o2*256+r;
			o+=4;

			
			if (ExpandedGraphics)o2 += 0x200000;

			fseek(fp,o2,SEEK_SET);
			for(int i=0;i<2;i++){
				fscanf(fp,"%c",&r);
				pal[i]=r;
				fscanf(fp,"%c",&r);
				pal[i]=pal[i]*256+r;
			}

			frame[0]=0;
			fscanf(fp,"%c",&r);
			frame[0]=r;
			fscanf(fp,"%c",&r);
			frame[0]=frame[0]*256+r;

			NumESPalette[s]=(frame[0]-pal[1])/32;

			fseek(fp,o2+pal[1]+2,SEEK_SET);
			for(int p=0;p<NumESPalette[s];p++){
				writePalette(ESPalette[s][p],16,fp);
			}
		}
		/*for(int i=0;i<42;i++){
			fseek(fp,o,SEEK_SET);
			fscanf(fp,"%c",&r);
			o2 = r;
			fscanf(fp,"%c",&r);
			o2 = o2*256+r;
			fscanf(fp,"%c",&r);
			o2 = o2*256+r;
			fscanf(fp,"%c",&r);
			o2 = o2*256+r;
			fseek(fp,o2+2,SEEK_SET);
			fscanf(fp,"%c",&r);
			in = r*256;
			fscanf(fp,"%c",&r);
			in+=r;
			fscanf(fp,"%c",&r);
			fscanf(fp,"%c",&r);
			r=r-r%32;

			fseek(fp,o2+in+2,SEEK_SET);
			for(int j=0;j<NumESPalette[i];j++){
				writePalette(ESPalette[i][j],16,fp);
			}
			o+=4;
		}*/
		int i;
		if (NumItems == 128) {
			fseek(fp, 0x14400C, SEEK_SET);
			fprintf(fp, "%c", (0x1DD500 & 0xFF000000) / 0x1000000);
			fprintf(fp, "%c", (0x1DD500 & 0x00FF0000) / 0x10000);
			fprintf(fp, "%c", (0x1DD500 & 0x0000FF00) / 0x100);
			fprintf(fp, "%c", (0x1DD500 & 0x000000FF));

			fseek(fp, 0x1DD500, SEEK_SET);
			int i;
			for (i = 0; i<128; i++) {
				writePalette(ISPalette[i], 4, fp);
			}
		} else {
			fseek(fp, 0x14400C, SEEK_SET);
			fprintf(fp, "%c", (0x16186E & 0xFF000000) / 0x1000000);
			fprintf(fp, "%c", (0x16186E & 0x00FF0000) / 0x10000);
			fprintf(fp, "%c", (0x16186E & 0x0000FF00) / 0x100);
			fprintf(fp, "%c", (0x16186E & 0x000000FF));

			fseek(fp, 0x16186E, SEEK_SET);

			for (i = 0; i<63; i++) {
				writePalette(ISPalette[i], 4, fp);
			}
		}



		fseek(fp,0xB94CA,SEEK_SET);
		for(i=0;i<27;i++){
			writePalette(TSPalette[i]+1,15,fp);
		}

		fseek(fp,0x144000,SEEK_SET);
		fscanf(fp,"%c",&r);
		o = r;
		fscanf(fp,"%c",&r);
		o = o*256+r;
		fscanf(fp,"%c",&r);
		o = o*256+r;
		fscanf(fp,"%c",&r);
		o = o*256+r;

		for(s=0;s<NumGFX[0];s++){
			fseek(fp,o,SEEK_SET);
			fscanf(fp,"%c",&r);
			o2 = r;
			fscanf(fp,"%c",&r);
			o2 = o2*256+r;
			fscanf(fp,"%c",&r);
			o2 = o2*256+r;
			fscanf(fp,"%c",&r);
			o2 = o2*256+r;
			o+=4;

			if (ExpandedGraphics)o2 += 0x100000;

			fseek(fp,o2,SEEK_SET);
			for(int i=0;i<2;i++){
				fscanf(fp,"%c",&r);
				pal[i]=r;
				fscanf(fp,"%c",&r);
				pal[i]=pal[i]*256+r;
			}

			frame[0]=0;
			fscanf(fp,"%c",&r);
			frame[0]=r;
			fscanf(fp,"%c",&r);
			frame[0]=frame[0]*256+r;

			NumFSPalette[s]=(frame[0]-pal[1])/32;

			fseek(fp,o2+pal[1]+2,SEEK_SET);
			for(int p=0;p<NumFSPalette[s];p++){
				writePalette(FSPalette[s][p],16,fp);
			}
		}

		fseek(fp, 0xCC000, SEEK_SET);
		fscanf(fp, "%c", &r);
		o = r;
		fscanf(fp, "%c", &r);
		o = o * 256 + r;
		fscanf(fp, "%c", &r);
		o = o * 256 + r;
		fscanf(fp, "%c", &r);
		o = o * 256 + r;

		for (s = 0; s < NumGFX[3]; s++) {

			fseek(fp, o, SEEK_SET);
			fscanf(fp, "%c", &r);
			o2 = r;
			fscanf(fp, "%c", &r);
			o2 = o2 * 256 + r;
			fscanf(fp, "%c", &r);
			o2 = o2 * 256 + r;
			fscanf(fp, "%c", &r);
			o2 = o2 * 256 + r;
			o += 4;

			if (ExpandedGraphics)o2 += 0x200000;

			fseek(fp, o2, SEEK_SET);
			if(s%2==0)writePalette(BGPalette[s][0], 16, fp);
		}

		fclose(fp);
		MessageBox(NULL,"Palettes Saved","Note",MB_OK);
	}
}

void ExportPalette(char*path){
	FILE * fp = fopen(path,"wb");

		writePalette(IconPalette,16,fp);
		
		writePalette(FMSPalette,16,fp);
		writePalette(EMSPalette,16,fp);

		int i;
		for(i=0;i<50;i++){
			for(int j=0;j<NumESPalette[i];j++){
				writePalette(ESPalette[i][j],16,fp);
			}
		}

		for(i=0;i<63;i++){
			writePalette(ISPalette[i],4,fp);
		}

		for(i=0;i<24;i++){
			writePalette(TSPalette[i],15,fp);
		}

	fclose(fp);
	MessageBox(NULL,"Palettes Exported","Note",MB_OK);
}

void PaletteExport(){
	OPENFILENAME openFileName;
	char path[256];
	path[0] = '\0';  
	memset( &openFileName, 0, sizeof(openFileName) );
	openFileName.lStructSize = sizeof(openFileName);
	openFileName.hwndOwner = NULL;
	openFileName.hInstance = NULL;
	openFileName.lpstrFilter = "Shining Force Palettes(*.sfp)\0*.sfp\0";
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
	openFileName.lpstrDefExt = "sfp";
	openFileName.lCustData = NULL;
	openFileName.lpfnHook = NULL;
	openFileName.lpTemplateName = NULL;

	if(GetSaveFileName(&openFileName)!=0){
		ExportPalette(path);
	}
}