void SaveRange(){
	short sh;
	long lo;
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

	int j;
	
	if(strlen(file)){
		FILE * fp = fopen(file,"rb+");

		if(NumRanges>60)RangeDataOffset = 0x180300;

		if(RangeDataOffset>romsize-1){
			MessageBox(NULL,"Rom is too small, expand rom or use a smaller offset.","Error",MB_OK);
			fclose(fp);
			return;
		}
		
		if(RangeDataOffset==0x23178){
			fseek(fp,RangeDataOffset,SEEK_SET);
			for(int i=0;i<64;i++){
				for(j=0;j<8;j++){
					fprintf(fp,"%c",Range[i][j]);
				}
			}
			fseek(fp,143466,SEEK_SET);
			fprintf(fp,"%c",0x43);
			fprintf(fp,"%c",0xFA);
			fprintf(fp,"%c",0x01);
			fprintf(fp,"%c",0x0C);
			fprintf(fp,"%c",0x02);
			fprintf(fp,"%c",0x44);
			fprintf(fp,"%c",0);
			fprintf(fp,"%c",0xFF);
			fseek(fp,143474,SEEK_SET);
			fprintf(fp,"%c",0xE7);
		} else {
			fseek(fp,RangeDataOffset,SEEK_SET);
			fprintf(fp,"%c",0x02);
			fprintf(fp,"%c",0x44);
			fprintf(fp,"%c",0);
			fprintf(fp,"%c",0xFF);
			fprintf(fp,"%c",0x43);
			fprintf(fp,"%c",0xF9);
			fprintf(fp,"%c",((RangeDataOffset+12)&0xFF000000)/0x1000000);
			fprintf(fp,"%c",((RangeDataOffset+12)&0x00FF0000)/0x10000);
			fprintf(fp,"%c",((RangeDataOffset+12)&0x0000FF00)/0x100);
			fprintf(fp,"%c",((RangeDataOffset+12)&0x000000FF));
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0x75);
			for(int i=0;i<NumRanges;i++){
				for(j=0;j<4;j++){
					fprintf(fp,"%c",Range[i][j]);
				}
				fprintf(fp,"%c",0x4E);
				fprintf(fp,"%c",0xF9);
				lo = 0x23178 + (i)*8 + 6;
				sh = Range[i][6]*256+Range[i][7];
				lo += sh;
				fprintf(fp,"%c",((lo)&0xFF000000)/0x1000000);
				fprintf(fp,"%c",((lo)&0x00FF0000)/0x10000);
				fprintf(fp,"%c",((lo)&0x0000FF00)/0x100);
				fprintf(fp,"%c",((lo)&0x000000FF));
				for(j=0;j<6;j++){
					fprintf(fp,"%c",255);
				}
			}
			fprintf(fp,"%c",255);
			fseek(fp,143466,SEEK_SET);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0xB9);
			fprintf(fp,"%c",((RangeDataOffset)&0xFF000000)/0x1000000);
			fprintf(fp,"%c",((RangeDataOffset)&0x00FF0000)/0x10000);
			fprintf(fp,"%c",((RangeDataOffset)&0x0000FF00)/0x100);
			fprintf(fp,"%c",((RangeDataOffset)&0x000000FF));
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0x71);
			fseek(fp,143474,SEEK_SET);
			fprintf(fp,"%c",0xE9);
		}

		fseek(fp,143515,SEEK_SET);
		fprintf(fp,"%c",MaxRange);

		if(ExtendRange){
			if(RangeOffset>romsize-1){
				MessageBox(NULL,"Rom is too small, expand rom or use a smaller offset.","Error",MB_OK);
				fclose(fp);
				return;
			}
			fseek(fp,132710,SEEK_SET);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0xB9);
			fprintf(fp,"%c",((RangeOffset)&0xFF000000)/0x1000000);
			fprintf(fp,"%c",((RangeOffset)&0x00FF0000)/0x10000);
			fprintf(fp,"%c",((RangeOffset)&0x0000FF00)/0x100);
			fprintf(fp,"%c",((RangeOffset)&0x000000FF));
			fseek(fp,132736,SEEK_SET);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0xB9);
			fprintf(fp,"%c",((RangeOffset+14)&0xFF000000)/0x1000000);
			fprintf(fp,"%c",((RangeOffset+14)&0x00FF0000)/0x10000);
			fprintf(fp,"%c",((RangeOffset+14)&0x0000FF00)/0x100);
			fprintf(fp,"%c",((RangeOffset+14)&0x000000FF));

			fseek(fp,RangeOffset,SEEK_SET);
			fprintf(fp,"%c",0x36);
			fprintf(fp,"%c",0x01);
			fprintf(fp,"%c",0x02);
			fprintf(fp,"%c",0x41);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x0F);

			fprintf(fp,"%c",0x38);
			fprintf(fp,"%c",0x02);
			fprintf(fp,"%c",0x02);
			fprintf(fp,"%c",0x42);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x0F);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0x75);
			for(int i=0;i<rangesize;i++){
				fprintf(fp,"%c",rangeasm[i]);
			}
		} else {
			fseek(fp,132710,SEEK_SET);
			fprintf(fp,"%c",0x36);
			fprintf(fp,"%c",0x01);
			fprintf(fp,"%c",0x02);
			fprintf(fp,"%c",0x41);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x7F);
			fseek(fp,132736,SEEK_SET);
			fprintf(fp,"%c",0x65);
			fprintf(fp,"%c",0x04);
			fprintf(fp,"%c",0x08);
			fprintf(fp,"%c",0xD1);
			fprintf(fp,"%c",0);
			fprintf(fp,"%c",0);
		}
		if(ExtendArea&&ExtendRange){
			fseek(fp,AreaOffset,SEEK_SET);
			for(int i=0;i<areasize;i++){
				fprintf(fp,"%c",areaasm[i]);
			}
			fseek(fp,AreaOffset+0x06,SEEK_SET);
			fprintf(fp,"%c",((AreaOffset+0x0C)&0xFF000000)/0x1000000);
			fprintf(fp,"%c",((AreaOffset+0x0C)&0x00FF0000)/0x10000);
			fprintf(fp,"%c",((AreaOffset+0x0C)&0x0000FF00)/0x100);
			fprintf(fp,"%c",((AreaOffset+0x0C)&0x000000FF));
			fseek(fp,AreaOffset+0x62,SEEK_SET);
			fprintf(fp,"%c",((AreaOffset+0x6C)&0xFF000000)/0x1000000);
			fprintf(fp,"%c",((AreaOffset+0x6C)&0x00FF0000)/0x10000);
			fprintf(fp,"%c",((AreaOffset+0x6C)&0x0000FF00)/0x100);
			fprintf(fp,"%c",((AreaOffset+0x6C)&0x000000FF));
			fseek(fp,AreaOffset+0x09AA,SEEK_SET);
			fprintf(fp,"%c",((AreaOffset+0x0540)&0xFF000000)/0x1000000);
			fprintf(fp,"%c",((AreaOffset+0x0540)&0x00FF0000)/0x10000);
			fprintf(fp,"%c",((AreaOffset+0x0540)&0x0000FF00)/0x100);
			fprintf(fp,"%c",((AreaOffset+0x0540)&0x000000FF));
			fseek(fp,AreaOffset+0x0A0A,SEEK_SET);
			fprintf(fp,"%c",((AreaOffset+0x0D80)&0xFF000000)/0x1000000);
			fprintf(fp,"%c",((AreaOffset+0x0D80)&0x00FF0000)/0x10000);
			fprintf(fp,"%c",((AreaOffset+0x0D80)&0x0000FF00)/0x100);
			fprintf(fp,"%c",((AreaOffset+0x0D80)&0x000000FF));
			fseek(fp,AreaOffset+0x0A10,SEEK_SET);
			fprintf(fp,"%c",((AreaOffset+0x0A40)&0xFF000000)/0x1000000);
			fprintf(fp,"%c",((AreaOffset+0x0A40)&0x00FF0000)/0x10000);
			fprintf(fp,"%c",((AreaOffset+0x0A40)&0x0000FF00)/0x100);
			fprintf(fp,"%c",((AreaOffset+0x0A40)&0x000000FF));
			fseek(fp,AreaOffset+0x0C12,SEEK_SET);
			fprintf(fp,"%c",((AreaOffset+0x0180)&0xFF000000)/0x1000000);
			fprintf(fp,"%c",((AreaOffset+0x0180)&0x00FF0000)/0x10000);
			fprintf(fp,"%c",((AreaOffset+0x0180)&0x0000FF00)/0x100);
			fprintf(fp,"%c",((AreaOffset+0x0180)&0x000000FF));
			fseek(fp,AreaOffset+0x0C8E,SEEK_SET);
			fprintf(fp,"%c",((AreaOffset+0x0CE0)&0xFF000000)/0x1000000);
			fprintf(fp,"%c",((AreaOffset+0x0CE0)&0x00FF0000)/0x10000);
			fprintf(fp,"%c",((AreaOffset+0x0CE0)&0x0000FF00)/0x100);
			fprintf(fp,"%c",((AreaOffset+0x0CE0)&0x000000FF));

			fseek(fp,143550,SEEK_SET);
			fprintf(fp,"%c",0x6C);
			fprintf(fp,"%c",0x08);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0xB9);
			fprintf(fp,"%c",((AreaOffset)&0xFF000000)/0x1000000);
			fprintf(fp,"%c",((AreaOffset)&0x00FF0000)/0x10000);
			fprintf(fp,"%c",((AreaOffset)&0x0000FF00)/0x100);
			fprintf(fp,"%c",((AreaOffset)&0x000000FF));
			fprintf(fp,"%c",0x60);
			fprintf(fp,"%c",0x06);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0xB9);
			fprintf(fp,"%c",((AreaOffset+0x60)&0xFF000000)/0x1000000);
			fprintf(fp,"%c",((AreaOffset+0x60)&0x00FF0000)/0x10000);
			fprintf(fp,"%c",((AreaOffset+0x60)&0x0000FF00)/0x100);
			fprintf(fp,"%c",((AreaOffset+0x60)&0x000000FF));

			fseek(fp,34778,SEEK_SET);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0xB9);
			fprintf(fp,"%c",((AreaOffset+0x0C00)&0xFF000000)/0x1000000);
			fprintf(fp,"%c",((AreaOffset+0x0C00)&0x00FF0000)/0x10000);
			fprintf(fp,"%c",((AreaOffset+0x0C00)&0x0000FF00)/0x100);
			fprintf(fp,"%c",((AreaOffset+0x0C00)&0x000000FF));
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0x71);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0x71);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0x71);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0x71);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0x71);

			fseek(fp,34844,SEEK_SET);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0xB9);
			fprintf(fp,"%c",((AreaOffset+0x09A0)&0xFF000000)/0x1000000);
			fprintf(fp,"%c",((AreaOffset+0x09A0)&0x00FF0000)/0x10000);
			fprintf(fp,"%c",((AreaOffset+0x09A0)&0x0000FF00)/0x100);
			fprintf(fp,"%c",((AreaOffset+0x09A0)&0x000000FF));
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0x71);

			fseek(fp,40998,SEEK_SET);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0xB9);
			fprintf(fp,"%c",((AreaOffset+0xC0)&0xFF000000)/0x1000000);
			fprintf(fp,"%c",((AreaOffset+0xC0)&0x00FF0000)/0x10000);
			fprintf(fp,"%c",((AreaOffset+0xC0)&0x0000FF00)/0x100);
			fprintf(fp,"%c",((AreaOffset+0xC0)&0x000000FF));
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0x71);

			fseek(fp,143646,SEEK_SET);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0xB9);
			fprintf(fp,"%c",((AreaOffset+0x0A00)&0xFF000000)/0x1000000);
			fprintf(fp,"%c",((AreaOffset+0x0A00)&0x00FF0000)/0x10000);
			fprintf(fp,"%c",((AreaOffset+0x0A00)&0x0000FF00)/0x100);
			fprintf(fp,"%c",((AreaOffset+0x0A00)&0x000000FF));
		} else {
			fseek(fp,143550,SEEK_SET);
			fprintf(fp,"%c",0x6C);
			fprintf(fp,"%c",0x0A);
			fprintf(fp,"%c",0x02);
			fprintf(fp,"%c",0x41);
			fprintf(fp,"%c",0);
			fprintf(fp,"%c",0x7F);
			fprintf(fp,"%c",0x43);
			fprintf(fp,"%c",0xFA);
			fprintf(fp,"%c",0);
			fprintf(fp,"%c",0x29);
			fprintf(fp,"%c",0x60);
			fprintf(fp,"%c",0x04);
			fprintf(fp,"%c",0x43);
			fprintf(fp,"%c",0xFA);
			fprintf(fp,"%c",0);
			fprintf(fp,"%c",0x20);

			fseek(fp,34778,SEEK_SET);
			fprintf(fp,"%c",0x41);
			fprintf(fp,"%c",0xFA);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x78);
			fprintf(fp,"%c",0x42);
			fprintf(fp,"%c",0x40);
			fprintf(fp,"%c",0x10);
			fprintf(fp,"%c",0x38);
			fprintf(fp,"%c",0xB4);
			fprintf(fp,"%c",0xC7);
			fprintf(fp,"%c",0x02);
			fprintf(fp,"%c",0x40);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x0F);
			fprintf(fp,"%c",0xED);
			fprintf(fp,"%c",0x48);

			fseek(fp,34844,SEEK_SET);
			fprintf(fp,"%c",0x41);
			fprintf(fp,"%c",0xFA);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0xF6);
			fprintf(fp,"%c",0x30);
			fprintf(fp,"%c",0x38);
			fprintf(fp,"%c",0xB7);
			fprintf(fp,"%c",0xC2);

			fseek(fp,40998,SEEK_SET);
			fprintf(fp,"%c",0x10);
			fprintf(fp,"%c",0x38);
			fprintf(fp,"%c",0xB4);
			fprintf(fp,"%c",0xC5);
			fprintf(fp,"%c",0x61);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x2E);
			fprintf(fp,"%c",0xF2);

			fseek(fp,143646,SEEK_SET);
			fprintf(fp,"%c",0x12);
			fprintf(fp,"%c",0x29);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x02);
			fprintf(fp,"%c",0x42);
			fprintf(fp,"%c",0x02);
		}
		fclose(fp);
		MessageBox(NULL,"Ranges Saved","Note",MB_OK);
	}
}

void ExportRange(char*path){
	FILE * fp = fopen(path,"wb");

	for(int i=0;i<64;i++){
		for(int j=0;j<8;j++){
			fprintf(fp,"%c",Range[i][j]);
		}
	}

	fprintf(fp,"%c",MaxRange);

	fclose(fp);
	MessageBox(NULL,"Ranges Exported","Note",MB_OK);
}

void RangeExport(){
	OPENFILENAME openFileName;
	char path[256];
	path[0] = '\0';  
	memset( &openFileName, 0, sizeof(openFileName) );
	openFileName.lStructSize = sizeof(openFileName);
	openFileName.hwndOwner = NULL;
	openFileName.hInstance = NULL;
	openFileName.lpstrFilter = "Shining Force Ranges(*.sfr)\0*.sfr\0";
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
	openFileName.lpstrDefExt = "sfr";
	openFileName.lCustData = NULL;
	openFileName.lpfnHook = NULL;
	openFileName.lpTemplateName = NULL;

	if(GetSaveFileName(&openFileName)!=0){
		ExportRange(path);
	}
}