void SaveChar(){
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
		int i,j;
		FILE * fp = fopen(file,"rb+");

		if(ChangeCurves)CurvesOffset = 0x1D8800;

		if(romsize<CurvesOffset){
			MessageBox(NULL,"Rom is too small, expand rom to save growth curves.","Error",MB_OK);
			fclose(fp);
			return;
		}

		fseek(fp, 0x6C05, SEEK_SET);
		fprintf(fp, "%c", 2*NumChars - 3);
		fseek(fp, 0x6C11, SEEK_SET);
		fprintf(fp, "%c", NumChars-2);

		if (NumChars == MAX_CHARS) {
			if (MSBankOffset == 0x39928) {
				MessageBox(NULL, "Graphics must first be saved before characters can be extended.", "Error", MB_OK);
				fclose(fp);
				return;
			}

			fseek(fp, 0x23A0A, SEEK_SET);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0xB9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x06);
			fprintf(fp, "%c", 0xFF);
			fprintf(fp, "%c", 0xE0);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0x71);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0x71);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0x71);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0x71);

			fseek(fp, 0x23A64, SEEK_SET);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0xB9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x07);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0xE0);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0x71);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0x71);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0x71);

			fseek(fp, 0x23A7C, SEEK_SET);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0x71);
			fprintf(fp, "%c", 0x64);
			fprintf(fp, "%c", 0x0E);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0x71);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0x71);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0x71);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0x71);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0x71);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0x71);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0x71);

			fseek(fp, 0x6FFE0, SEEK_SET);
			fprintf(fp, "%c", 0x42);
			fprintf(fp, "%c", 0x41);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0xB9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x02);
			fprintf(fp, "%c", 0x4A);
			fprintf(fp, "%c", 0xDA);
			fprintf(fp, "%c", 0x66);
			fprintf(fp, "%c", 0x06);//
			fprintf(fp, "%c", 0x12);
			fprintf(fp, "%c", 0x3B);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x14);//
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0x75);
			fprintf(fp, "%c", 0x12);
			fprintf(fp, "%c", 0x3B);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x4E);//
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0x75);

			fseek(fp, 0x700E0, SEEK_SET);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0xB9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x02);
			fprintf(fp, "%c", 0x3A);
			fprintf(fp, "%c", 0x94);
			fprintf(fp, "%c", 0x64);
			fprintf(fp, "%c", 0x0E);//

			fprintf(fp, "%c", 0x42);
			fprintf(fp, "%c", 0x41);

			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0xB9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x02);
			fprintf(fp, "%c", 0x4A);
			fprintf(fp, "%c", 0xDA);
			fprintf(fp, "%c", 0x66);
			fprintf(fp, "%c", 0x06);//

			fprintf(fp, "%c", 0x12);
			fprintf(fp, "%c", 0x3B);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x0C);//
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0x75);

			fprintf(fp, "%c", 0x12);
			fprintf(fp, "%c", 0x3B);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x46);//

			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0x75);

			fseek(fp, 0x70000, SEEK_SET);
			for (int i = 0;i < NumChars;i++) {
				fprintf(fp, "%c", (CharPortrait[i]));
			}
			fseek(fp, 0x70040, SEEK_SET);
			for (int i = 0;i < NumChars;i++) {
				fprintf(fp, "%c", (CharPortrait2[i]));
			}
			fseek(fp, 0x70100, SEEK_SET);
			for (int i = 0;i < NumChars;i++) {
				fprintf(fp, "%c", (CharMapSprite[i]));
			}

			fseek(fp, 0x70140, SEEK_SET);
			for (int i = 0; i < NumChars; i++) {
				fprintf(fp, "%c", (CharMapSprite2[i]));
			}

			fseek(fp, 0x21B20, SEEK_SET);
			fprintf(fp, "%c", 0xF0);
			fprintf(fp, "%c", 0x20);
			fprintf(fp, "%c", 0x30);
			fprintf(fp, "%c", 0x3C);
			fprintf(fp, "%c", 0x07);
			fprintf(fp, "%c", 0xD0);

			fseek(fp, 0x22602, SEEK_SET);
			fprintf(fp, "%c", 0xF0);
			fprintf(fp, "%c", 0x20);

			fseek(fp, 0x1643BC, SEEK_SET);
			fprintf(fp, "%c", 0xF0);
			fprintf(fp, "%c", 0x20);

			fseek(fp, 0x21B2E, SEEK_SET);
			fprintf(fp, "%c", 0xCC);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x30);
			fprintf(fp, "%c", 0x3C);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x3C);

			fseek(fp, 0x24922, SEEK_SET);
			fprintf(fp, "%c", 0xCC);
			fprintf(fp, "%c", 0x00);

			fseek(fp, 0x24AEC, SEEK_SET);
			fprintf(fp, "%c", 0xCC);
			fprintf(fp, "%c", 0x00);

			fseek(fp, 0x24B98, SEEK_SET);
			fprintf(fp, "%c", 0xCC);
			fprintf(fp, "%c", 0x00);

			fseek(fp, 0x220B8, SEEK_SET);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0xF9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x07);
			fprintf(fp, "%c", 0x14);
			fprintf(fp, "%c", 0x00);

			fseek(fp, 0x221D4, SEEK_SET);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0xF9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x07);
			fprintf(fp, "%c", 0x14);
			fprintf(fp, "%c", 0x00);

			fseek(fp, 0x71400, SEEK_SET);
			fprintf(fp, "%c", 0x48);
			fprintf(fp, "%c", 0xE7);
			fprintf(fp, "%c", 0xC0);
			fprintf(fp, "%c", 0x00);

			fprintf(fp, "%c", 0x0C);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x1E);
			fprintf(fp, "%c", 0x6C);
			fprintf(fp, "%c", 0x0C);

			fprintf(fp, "%c", 0x22);
			fprintf(fp, "%c", 0x38);
			fprintf(fp, "%c", 0x9C);
			fprintf(fp, "%c", 0x8A);
			fprintf(fp, "%c", 0x01);
			fprintf(fp, "%c", 0x01);
			fprintf(fp, "%c", 0x4C);
			fprintf(fp, "%c", 0xDF);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x03);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0x75);

			fprintf(fp, "%c", 0x04);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x1E);
			fprintf(fp, "%c", 0x22);
			fprintf(fp, "%c", 0x38);
			fprintf(fp, "%c", 0xCC);
			fprintf(fp, "%c", 0x80);
			fprintf(fp, "%c", 0x01);
			fprintf(fp, "%c", 0x01);
			fprintf(fp, "%c", 0x4C);
			fprintf(fp, "%c", 0xDF);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x03);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0x75);

			fseek(fp, 0x221B6, SEEK_SET);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0xB9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x07);
			fprintf(fp, "%c", 0x14);
			fprintf(fp, "%c", 0x40);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0x71);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0x71);

			fseek(fp, 0x71440, SEEK_SET);
			fprintf(fp, "%c", 0x0C);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x1E);

			fprintf(fp, "%c", 0x6C);
			fprintf(fp, "%c", 0x0C);
			fprintf(fp, "%c", 0x22);
			fprintf(fp, "%c", 0x38);
			fprintf(fp, "%c", 0x9C);
			fprintf(fp, "%c", 0x8A);
			fprintf(fp, "%c", 0x01);
			fprintf(fp, "%c", 0xC1);
			fprintf(fp, "%c", 0x21);
			fprintf(fp, "%c", 0xC1);
			fprintf(fp, "%c", 0x9C);
			fprintf(fp, "%c", 0x8A);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0x75);

			fprintf(fp, "%c", 0x04);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x1E);
			fprintf(fp, "%c", 0x22);
			fprintf(fp, "%c", 0x38);
			fprintf(fp, "%c", 0xCC);
			fprintf(fp, "%c", 0x80);
			fprintf(fp, "%c", 0x01);
			fprintf(fp, "%c", 0xC1);
			fprintf(fp, "%c", 0x21);
			fprintf(fp, "%c", 0xC1);
			fprintf(fp, "%c", 0xCC);
			fprintf(fp, "%c", 0x80);
			fprintf(fp, "%c", 0x06);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x1E);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0x75);
	
			fseek(fp, 0x21B3E, SEEK_SET);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x07);
			fprintf(fp, "%c", 0x14);
			fprintf(fp, "%c", 0x80);

			fseek(fp, 0x71480, SEEK_SET);
			fprintf(fp, "%c", 0x42);
			fprintf(fp, "%c", 0xB8);
			fprintf(fp, "%c", 0xCC);
			fprintf(fp, "%c", 0x80);

			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0xB9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x02);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x7C);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0x75);

			fseek(fp, 0x21B3A, SEEK_SET);
			fprintf(fp, "%c", 0x70);
			fprintf(fp, "%c", 0x31);

			fseek(fp, 0x21CE5, SEEK_SET);
			fprintf(fp, "%c", 0x40);

			fseek(fp, 0x21BE2, SEEK_SET);
			fprintf(fp, "%c", 0x9C);
			fprintf(fp, "%c", 0x94);

			fseek(fp, 0x21BE6, SEEK_SET);
			fprintf(fp, "%c", 0x03);

			fseek(fp, 0x225BA, SEEK_SET);
			fprintf(fp, "%c", 0x9C);
			fprintf(fp, "%c", 0x94);

			fseek(fp, 0x225E8, SEEK_SET);
			fprintf(fp, "%c", 0x9C);
			fprintf(fp, "%c", 0x94);

			fseek(fp, 0x22033, SEEK_SET);
			fprintf(fp, "%c", 0x32);


			fseek(fp, 0x98AA, SEEK_SET);
			fprintf(fp, "%c", 0x9C);
			fprintf(fp, "%c", 0x94);

			fseek(fp, 0x9942, SEEK_SET);
			fprintf(fp, "%c", 0x9C);
			fprintf(fp, "%c", 0x94);

			fseek(fp, 0x9AA4, SEEK_SET);
			fprintf(fp, "%c", 0x9C);
			fprintf(fp, "%c", 0x94);

			fseek(fp, 0xAB5E, SEEK_SET);
			fprintf(fp, "%c", 0x9C);
			fprintf(fp, "%c", 0x94);

			fseek(fp, 0x12D5A, SEEK_SET);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0xB9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x07);
			fprintf(fp, "%c", 0x15);
			fprintf(fp, "%c", 0x00);

			fseek(fp, 0x71500, SEEK_SET);
			fprintf(fp, "%c", 0x0C);
			fprintf(fp, "%c", 0x01);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x44);
			fprintf(fp, "%c", 0x6C);
			fprintf(fp, "%c", 0x08);
			fprintf(fp, "%c", 0x43);
			fprintf(fp, "%c", 0xF9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0xFF);
			fprintf(fp, "%c", 0x9C);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0x75);
			fprintf(fp, "%c", 0x43);
			fprintf(fp, "%c", 0xF9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0xFF);
			fprintf(fp, "%c", 0xEF);
			fprintf(fp, "%c", 0xDC);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0x75);

			fseek(fp, 0xA778, SEEK_SET);
			fprintf(fp, "%c", 0x9C);
			fprintf(fp, "%c", 0x94);

			fseek(fp, 0xA0F4, SEEK_SET);
			fprintf(fp, "%c", 0x9C);
			fprintf(fp, "%c", 0x94);

			fseek(fp, 0xB54E, SEEK_SET);
			fprintf(fp, "%c", 0x9C);
			fprintf(fp, "%c", 0x94);

			fseek(fp, 0xB476, SEEK_SET);
			fprintf(fp, "%c", 0x07);
			fprintf(fp, "%c", 0xFF);

			fseek(fp, 0x22081, SEEK_SET);
			fprintf(fp, "%c", 0x32);

			fseek(fp, 0x17354, SEEK_SET);
			fprintf(fp, "%c", 0xCC);
			fprintf(fp, "%c", 0x00);

			fseek(fp, 0xA148, SEEK_SET);
			fprintf(fp, "%c", 0x9C);
			fprintf(fp, "%c", 0xA4);

			fseek(fp, 0x9828, SEEK_SET);
			fprintf(fp, "%c", 0x9C);
			fprintf(fp, "%c", 0xA4);

			fseek(fp, 0x5A8C, SEEK_SET);
			fprintf(fp, "%c", 0x9C);
			fprintf(fp, "%c", 0xA4);

			fseek(fp, 0x24D13, SEEK_SET);
			fprintf(fp, "%c", 0x32);

			fseek(fp, 0x225CB, SEEK_SET);
			fprintf(fp, "%c", 0x32);

			fseek(fp, 0x225CF, SEEK_SET);
			fprintf(fp, "%c", 0x32);

			fseek(fp, 0x73D7, SEEK_SET);
			fprintf(fp, "%c", 0x32);

			fseek(fp, 0x71580, SEEK_SET);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0xB9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x02);
			fprintf(fp, "%c", 0x01);
			fprintf(fp, "%c", 0x0C);
			fprintf(fp, "%c", 0x0C);
			fprintf(fp, "%c", 0x51);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0xB9);
			fprintf(fp, "%c", 0x66);
			fprintf(fp, "%c", 0x06);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0xF9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x68);
			fprintf(fp, "%c", 0x2C);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0xF9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x68);
			fprintf(fp, "%c", 0x28);

			fseek(fp, 0x715A0, SEEK_SET);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0xB9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x02);
			fprintf(fp, "%c", 0x01);
			fprintf(fp, "%c", 0x0C);
			fprintf(fp, "%c", 0x0C);
			fprintf(fp, "%c", 0x51);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0xB9);
			fprintf(fp, "%c", 0x66);
			fprintf(fp, "%c", 0x06);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0xF9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x68);
			fprintf(fp, "%c", 0x60);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0xF9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x68);
			fprintf(fp, "%c", 0x5C);

			fseek(fp, 0x6822, SEEK_SET);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0xF9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x07);
			fprintf(fp, "%c", 0x15);
			fprintf(fp, "%c", 0x80);

			fseek(fp, 0x6856, SEEK_SET);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0xF9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x07);
			fprintf(fp, "%c", 0x15);
			fprintf(fp, "%c", 0xA0);


			fseek(fp, 0x71600, SEEK_SET);
			fprintf(fp, "%c", 0x12);
			fprintf(fp, "%c", 0x80);
			fprintf(fp, "%c", 0x54);
			fprintf(fp, "%c", 0x89);
			fprintf(fp, "%c", 0x30);
			fprintf(fp, "%c", 0x38);
			fprintf(fp, "%c", 0xC0);
			fprintf(fp, "%c", 0xB8);
			fprintf(fp, "%c", 0x66);
			fprintf(fp, "%c", 0x08);
			fprintf(fp, "%c", 0x43);
			fprintf(fp, "%c", 0xF9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x20);
			fprintf(fp, "%c", 0x40);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x60);
			fprintf(fp, "%c", 0x14);
			fprintf(fp, "%c", 0x0C);
			fprintf(fp, "%c", 0x40);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x01);
			fprintf(fp, "%c", 0x66);
			fprintf(fp, "%c", 0x08);
			fprintf(fp, "%c", 0x43);
			fprintf(fp, "%c", 0xF9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x20);
			fprintf(fp, "%c", 0x80);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x60);
			fprintf(fp, "%c", 0x06);
			fprintf(fp, "%c", 0x43);
			fprintf(fp, "%c", 0xF9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x20);
			fprintf(fp, "%c", 0xC0);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x41);
			fprintf(fp, "%c", 0xF9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0xFF);
			fprintf(fp, "%c", 0xF0);
			fprintf(fp, "%c", 0x20);
			fprintf(fp, "%c", 0x3E);
			fprintf(fp, "%c", 0x3C);
			fprintf(fp, "%c", 0x07);
			fprintf(fp, "%c", 0xD0);
			fprintf(fp, "%c", 0x12);
			fprintf(fp, "%c", 0x18);
			fprintf(fp, "%c", 0x12);
			fprintf(fp, "%c", 0xC1);
			fprintf(fp, "%c", 0x51);
			fprintf(fp, "%c", 0xCF);
			fprintf(fp, "%c", 0xFF);
			fprintf(fp, "%c", 0xFA);
			fprintf(fp, "%c", 0x41);
			fprintf(fp, "%c", 0xF9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0xFF);
			fprintf(fp, "%c", 0xCC);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x3E);
			fprintf(fp, "%c", 0x3C);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x90);
			fprintf(fp, "%c", 0x12);
			fprintf(fp, "%c", 0x18);
			fprintf(fp, "%c", 0x12);
			fprintf(fp, "%c", 0xC1);
			fprintf(fp, "%c", 0x51);
			fprintf(fp, "%c", 0xCF);
			fprintf(fp, "%c", 0xFF);
			fprintf(fp, "%c", 0xFA);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0x75);

			fseek(fp, 0x71660, SEEK_SET);
			fprintf(fp, "%c", 0xB0);
			fprintf(fp, "%c", 0x11);
			fprintf(fp, "%c", 0x54);
			fprintf(fp, "%c", 0x89);
			fprintf(fp, "%c", 0x30);
			fprintf(fp, "%c", 0x38);
			fprintf(fp, "%c", 0xC0);
			fprintf(fp, "%c", 0xB8);
			fprintf(fp, "%c", 0x66);
			fprintf(fp, "%c", 0x08);
			fprintf(fp, "%c", 0x41);
			fprintf(fp, "%c", 0xF9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x20);
			fprintf(fp, "%c", 0x40);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x60);
			fprintf(fp, "%c", 0x14);
			fprintf(fp, "%c", 0x0C);
			fprintf(fp, "%c", 0x40);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x01);
			fprintf(fp, "%c", 0x66);
			fprintf(fp, "%c", 0x08);
			fprintf(fp, "%c", 0x41);
			fprintf(fp, "%c", 0xF9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x20);
			fprintf(fp, "%c", 0x80);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x60);
			fprintf(fp, "%c", 0x06);
			fprintf(fp, "%c", 0x41);
			fprintf(fp, "%c", 0xF9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x20);
			fprintf(fp, "%c", 0xC0);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x43);
			fprintf(fp, "%c", 0xF9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0xFF);
			fprintf(fp, "%c", 0xF0);
			fprintf(fp, "%c", 0x20);
			fprintf(fp, "%c", 0x3E);
			fprintf(fp, "%c", 0x3C);
			fprintf(fp, "%c", 0x07);
			fprintf(fp, "%c", 0xD0);
			fprintf(fp, "%c", 0x12);
			fprintf(fp, "%c", 0x18);
			fprintf(fp, "%c", 0x12);
			fprintf(fp, "%c", 0xC1);
			fprintf(fp, "%c", 0x51);
			fprintf(fp, "%c", 0xCF);
			fprintf(fp, "%c", 0xFF);
			fprintf(fp, "%c", 0xFA);
			fprintf(fp, "%c", 0x43);
			fprintf(fp, "%c", 0xF9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0xFF);
			fprintf(fp, "%c", 0xCC);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x3E);
			fprintf(fp, "%c", 0x3C);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x90);
			fprintf(fp, "%c", 0x12);
			fprintf(fp, "%c", 0x18);
			fprintf(fp, "%c", 0x12);
			fprintf(fp, "%c", 0xC1);
			fprintf(fp, "%c", 0x51);
			fprintf(fp, "%c", 0xCF);
			fprintf(fp, "%c", 0xFF);
			fprintf(fp, "%c", 0xFA);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0x75);

			fseek(fp, 0x37D0, SEEK_SET);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0xF9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x07);
			fprintf(fp, "%c", 0x16);
			fprintf(fp, "%c", 0x00);

			fseek(fp, 0x37E8, SEEK_SET);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0xF9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x07);
			fprintf(fp, "%c", 0x16);
			fprintf(fp, "%c", 0x60);

			fseek(fp, 0x1BA, SEEK_SET);
			fprintf(fp, "%c", 0xFF);

			fseek(fp, 0x23B3B, SEEK_SET);
			fprintf(fp, "%c", 0x3A);

			fseek(fp, 0x23B51, SEEK_SET);
			fprintf(fp, "%c", 0x1C);

			fseek(fp, 0x23B5F, SEEK_SET);
			fprintf(fp, "%c", 0x0E);

			fseek(fp, 0x23B60, SEEK_SET);
			fprintf(fp, "%c", 0xD0);
			fprintf(fp, "%c", 0xC0);
			fprintf(fp, "%c", 0xD0);
			fprintf(fp, "%c", 0xC0);
			
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0xB9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x07);
			fprintf(fp, "%c", 0x16);
			fprintf(fp, "%c", 0xC0);

			fprintf(fp, "%c", 0x12);
			fprintf(fp, "%c", 0x18);
			fprintf(fp, "%c", 0x14);
			fprintf(fp, "%c", 0x10);
			fprintf(fp, "%c", 0x31);
			fprintf(fp, "%c", 0xC1);
			fprintf(fp, "%c", 0xCB);
			fprintf(fp, "%c", 0xA6);
			fprintf(fp, "%c", 0x31);
			fprintf(fp, "%c", 0xC2);
			fprintf(fp, "%c", 0xCB);
			fprintf(fp, "%c", 0xA8);
			fprintf(fp, "%c", 0x4C);
			fprintf(fp, "%c", 0xDF);
			fprintf(fp, "%c", 0x03);
			fprintf(fp, "%c", 0x07);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0x75);

			fseek(fp, 0x716C0, SEEK_SET);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0xB9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x02);
			fprintf(fp, "%c", 0x4A);
			fprintf(fp, "%c", 0xDA);
			fprintf(fp, "%c", 0x66);
			fprintf(fp, "%c", 0x08);
			fprintf(fp, "%c", 0x20);
			fprintf(fp, "%c", 0x79);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x02);
			fprintf(fp, "%c", 0x03);
			fprintf(fp, "%c", 0xAC);
			fprintf(fp, "%c", 0x60);
			fprintf(fp, "%c", 0x06);
			fprintf(fp, "%c", 0x41);
			fprintf(fp, "%c", 0xF9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x07);
			fprintf(fp, "%c", 0x13);
			fprintf(fp, "%c", 0x80);
			fprintf(fp, "%c", 0xD0);
			fprintf(fp, "%c", 0xC0);
			fprintf(fp, "%c", 0xD0);
			fprintf(fp, "%c", 0xC0);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0x75);
		} else {
			fseek(fp, 0x23A1E, SEEK_SET);
			for (int i = 0; i < NumChars; i++) {
				fprintf(fp, "%c", (CharPortrait2[i]));
			}

			fseek(fp, 0x23B3B, SEEK_SET);
			fprintf(fp, "%c", 0x44);

			fseek(fp, 0x23B51, SEEK_SET);
			fprintf(fp, "%c", 0x26);

			fseek(fp, 0x23B5F, SEEK_SET);
			fprintf(fp, "%c", 0x18);

			fseek(fp, 0x23B60, SEEK_SET);
			fprintf(fp, "%c", 0x20);
			fprintf(fp, "%c", 0x79);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x02);
			fprintf(fp, "%c", 0x03);
			fprintf(fp, "%c", 0xAC);
			fprintf(fp, "%c", 0xD0);
			fprintf(fp, "%c", 0xC0);
			fprintf(fp, "%c", 0xD0);
			fprintf(fp, "%c", 0xC0);
			fprintf(fp, "%c", 0x12);
			fprintf(fp, "%c", 0x18);
			fprintf(fp, "%c", 0x14);
			fprintf(fp, "%c", 0x10);
			fprintf(fp, "%c", 0x61);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x0F);
			fprintf(fp, "%c", 0x6A);
			fprintf(fp, "%c", 0x67);
			fprintf(fp, "%c", 0x04);
			fprintf(fp, "%c", 0x06);
			fprintf(fp, "%c", 0x41);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x13);
			fprintf(fp, "%c", 0x31);
			fprintf(fp, "%c", 0xC1);
			fprintf(fp, "%c", 0xCB);
			fprintf(fp, "%c", 0xA6);
			fprintf(fp, "%c", 0x31);
			fprintf(fp, "%c", 0xC2);
			fprintf(fp, "%c", 0xCB);
			fprintf(fp, "%c", 0xA8);
			fprintf(fp, "%c", 0x4C);
			fprintf(fp, "%c", 0xDF);
			fprintf(fp, "%c", 0x03);
			fprintf(fp, "%c", 0x07);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0x75);


			fseek(fp, 0x37D0, SEEK_SET);
			fprintf(fp, "%c", 0x12);
			fprintf(fp, "%c", 0x80);
			fprintf(fp, "%c", 0x54);
			fprintf(fp, "%c", 0x89);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0x75);

			fseek(fp, 0x37E8, SEEK_SET);
			fprintf(fp, "%c", 0xB0);
			fprintf(fp, "%c", 0x11);
			fprintf(fp, "%c", 0x54);
			fprintf(fp, "%c", 0x89);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0x75);

			fseek(fp, 0x6822, SEEK_SET);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0xB9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x02);
			fprintf(fp, "%c", 0x01);
			fprintf(fp, "%c", 0x0C);

			fseek(fp, 0x6856, SEEK_SET);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0xB9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x02);
			fprintf(fp, "%c", 0x01);
			fprintf(fp, "%c", 0x0C);

			fseek(fp, 0x73D7, SEEK_SET);
			fprintf(fp, "%c", 0x1F);

			fseek(fp, 0x24D13, SEEK_SET);
			fprintf(fp, "%c", 0x1E);

			fseek(fp, 0x225CB, SEEK_SET);
			fprintf(fp, "%c", 0x1F);

			fseek(fp, 0x225CF, SEEK_SET);
			fprintf(fp, "%c", 0x1F);

			fseek(fp, 0xA148, SEEK_SET);
			fprintf(fp, "%c", 0xA1);
			fprintf(fp, "%c", 0xC6);

			fseek(fp, 0x9828, SEEK_SET);
			fprintf(fp, "%c", 0xA1);
			fprintf(fp, "%c", 0xC6);

			fseek(fp, 0x5A8C, SEEK_SET);
			fprintf(fp, "%c", 0xA1);
			fprintf(fp, "%c", 0xC6);

			fseek(fp, 0x17354, SEEK_SET);
			fprintf(fp, "%c", 0xA1);
			fprintf(fp, "%c", 0x6A);

			fseek(fp, 0x22081, SEEK_SET);
			fprintf(fp, "%c", 0x1F);

			fseek(fp, 0xB476, SEEK_SET);
			fprintf(fp, "%c", 0x09);
			fprintf(fp, "%c", 0x7F);

			fseek(fp, 0xB54E, SEEK_SET);
			fprintf(fp, "%c", 0xA1);
			fprintf(fp, "%c", 0xB6);

			fseek(fp, 0xA778, SEEK_SET);
			fprintf(fp, "%c", 0xA1);
			fprintf(fp, "%c", 0xB6);

			fseek(fp, 0xA0F4, SEEK_SET);
			fprintf(fp, "%c", 0xA1);
			fprintf(fp, "%c", 0xB6);

			fseek(fp, 0x12D5A, SEEK_SET);
			fprintf(fp, "%c", 0x43);
			fprintf(fp, "%c", 0xF9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0xFF);
			fprintf(fp, "%c", 0x9C);
			fprintf(fp, "%c", 0x4E);

			fseek(fp, 0x98AA, SEEK_SET);
			fprintf(fp, "%c", 0xA1);
			fprintf(fp, "%c", 0xB6);

			fseek(fp, 0x9942, SEEK_SET);
			fprintf(fp, "%c", 0xA1);
			fprintf(fp, "%c", 0xB6);

			fseek(fp, 0x9AA4, SEEK_SET);
			fprintf(fp, "%c", 0xA1);
			fprintf(fp, "%c", 0xB6);

			fseek(fp, 0xAB5E, SEEK_SET);
			fprintf(fp, "%c", 0xA1);
			fprintf(fp, "%c", 0xB6);

			fseek(fp, 0x22033, SEEK_SET);
			fprintf(fp, "%c", 0x1E);

			fseek(fp, 0x21CE5, SEEK_SET);
			fprintf(fp, "%c", 0x20);

			fseek(fp, 0x21BE2, SEEK_SET);
			fprintf(fp, "%c", 0xA1);
			fprintf(fp, "%c", 0xB6);

			fseek(fp, 0x21BE6, SEEK_SET);
			fprintf(fp, "%c", 0x01);

			fseek(fp, 0x225BA, SEEK_SET);
			fprintf(fp, "%c", 0xA1);
			fprintf(fp, "%c", 0xB6);

			fseek(fp, 0x225E8, SEEK_SET);
			fprintf(fp, "%c", 0xA1);
			fprintf(fp, "%c", 0xB6);

			fseek(fp, 0x21B3A, SEEK_SET);
			fprintf(fp, "%c", 0x70);
			if (JogurtLevels) {
				fprintf(fp, "%c", 0x1D);
			} else {
				fprintf(fp, "%c", 0x1C);
			}

			fseek(fp, 0x21B3E, SEEK_SET);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x02);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x7C);

			fseek(fp, 0x221B6, SEEK_SET);
			fprintf(fp, "%c", 0x22);
			fprintf(fp, "%c", 0x38);
			fprintf(fp, "%c", 0x9C);
			fprintf(fp, "%c", 0x8A);
			fprintf(fp, "%c", 0x01);
			fprintf(fp, "%c", 0xC1);
			fprintf(fp, "%c", 0x21);
			fprintf(fp, "%c", 0xC1);
			fprintf(fp, "%c", 0x9C);
			fprintf(fp, "%c", 0x8A);

			fseek(fp, 0x220B8, SEEK_SET);
			fprintf(fp, "%c", 0x48);
			fprintf(fp, "%c", 0xE7);
			fprintf(fp, "%c", 0x40);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x22);
			fprintf(fp, "%c", 0x38);

			fseek(fp, 0x221D4, SEEK_SET);
			fprintf(fp, "%c", 0x48);
			fprintf(fp, "%c", 0xE7);
			fprintf(fp, "%c", 0x40);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x22);
			fprintf(fp, "%c", 0x38);

			fseek(fp, 0x21B2E, SEEK_SET);
			fprintf(fp, "%c", 0xA1);
			fprintf(fp, "%c", 0x6A);
			fprintf(fp, "%c", 0x30);
			fprintf(fp, "%c", 0x3C);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x1E);

			fseek(fp, 0x24922, SEEK_SET);
			fprintf(fp, "%c", 0xA1);
			fprintf(fp, "%c", 0x6A);

			fseek(fp, 0x24AEC, SEEK_SET);
			fprintf(fp, "%c", 0xA1);
			fprintf(fp, "%c", 0x6A);

			fseek(fp, 0x24B98, SEEK_SET);
			fprintf(fp, "%c", 0xA1);
			fprintf(fp, "%c", 0x6A);

			fseek(fp, 0x21B20, SEEK_SET);
			fprintf(fp, "%c", 0x9C);
			fprintf(fp, "%c", 0x92);
			fprintf(fp, "%c", 0x30);
			fprintf(fp, "%c", 0x3C);
			fprintf(fp, "%c", 0x04);
			fprintf(fp, "%c", 0xD7);

			fseek(fp, 0x22602, SEEK_SET);
			fprintf(fp, "%c", 0x9C);
			fprintf(fp, "%c", 0x92);

			fseek(fp, 0x1643BC, SEEK_SET);
			fprintf(fp, "%c", 0x9C);
			fprintf(fp, "%c", 0x92);

			fseek(fp, 0x23A0A, SEEK_SET);
			fprintf(fp, "%c", 0x42);
			fprintf(fp, "%c", 0x41);
			fprintf(fp, "%c", 0x12);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x61);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x10);
			fprintf(fp, "%c", 0xCA);
			fprintf(fp, "%c", 0x67);
			fprintf(fp, "%c", 0x04);
			fprintf(fp, "%c", 0x12);
			fprintf(fp, "%c", 0x3B);
			fprintf(fp, "%c", 0x10);
			fprintf(fp, "%c", 0x08);

			fseek(fp, 0x23A64, SEEK_SET);
			fprintf(fp, "%c", 0x0C);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x1E);
			fprintf(fp, "%c", 0x66);
			fprintf(fp, "%c", 0x06);
			fprintf(fp, "%c", 0x32);
			fprintf(fp, "%c", 0x3C);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x39);
			fprintf(fp, "%c", 0x60);
			fprintf(fp, "%c", 0x1E);

			fseek(fp, 0x23A7C, SEEK_SET);
			fprintf(fp, "%c", 0x61);
			fprintf(fp, "%c", 0x16);
			fprintf(fp, "%c", 0x64);
			fprintf(fp, "%c", 0x0E);
			fprintf(fp, "%c", 0x42);
			fprintf(fp, "%c", 0x41);
			fprintf(fp, "%c", 0x12);
			fprintf(fp, "%c", 0x00);

			fprintf(fp, "%c", 0x61);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x10);
			fprintf(fp, "%c", 0x54);
			fprintf(fp, "%c", 0x67);
			fprintf(fp, "%c", 0x04);
			fprintf(fp, "%c", 0x06);
			fprintf(fp, "%c", 0x41);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x1E);
		}



		if (romsize >= 0x200000) {
			fseek(fp, 0x21B30, SEEK_SET);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0xB9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x1F);
			fprintf(fp, "%c", 0xFC);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0x71);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0x71);

			fseek(fp, 0x1FFC00, SEEK_SET);
			fprintf(fp, "%c", 0x43);
			fprintf(fp, "%c", 0xF9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x1E);
			fprintf(fp, "%c", 0x60);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x30);
			fprintf(fp, "%c", 0x3C);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", NumChars);

			fprintf(fp, "%c", 0x12);
			fprintf(fp, "%c", 0x31);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x11);
			fprintf(fp, "%c", 0x81);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x51);
			fprintf(fp, "%c", 0xC8);
			fprintf(fp, "%c", 0xFF);
			fprintf(fp, "%c", 0xF6);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0x75);
		}
			/*revert
			fprintf(fp, "%c", 0x30);
			fprintf(fp, "%c", 0x3C);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x1E);
			fprintf(fp, "%c", 0x42);
			fprintf(fp, "%c", 0x18);
			fprintf(fp, "%c", 0x51);
			fprintf(fp, "%c", 0xC8);
			fprintf(fp, "%c", 0xFF);
			fprintf(fp, "%c", 0xFC);

		*/

		if (romsize >= 0x200000) {
			fseek(fp, 0x1E6000, SEEK_SET);
			for (int i = 0; i < NumChars; i++) {
				fprintf(fp, "%c", CharPromotedAt[i]);
			}
		}

		fseek(fp,0x203E8,SEEK_SET);
		fprintf(fp,"%c",(CurvesOffset&0xFF000000)/0x1000000);
		fprintf(fp,"%c",(CurvesOffset&0x00FF0000)/0x10000);
		fprintf(fp,"%c",(CurvesOffset&0x0000FF00)/0x100);
		fprintf(fp,"%c",(CurvesOffset&0x000000FF));

		i=8;
		for(j=0;j<4;j++){
			fseek(fp,CurvesOffset+2*j,SEEK_SET);
			fprintf(fp,"%c",(i&0x0000FF00)/0x100);
			fprintf(fp,"%c",(i&0x000000FF));
			fseek(fp,CurvesOffset+i,SEEK_SET);
			for(int k=0;k<20;k++){
				if(Curves[j][k]!=255){
					i+=2;
					fprintf(fp,"%c",k+1);
					fprintf(fp,"%c",Curves[j][k]);
				}
			}
		}

		if(LearnOffset==0x26D70&&romsize>0x1A5600)LearnOffset = 0x1A5600;
		if(romsize<0x1A5600&&LearnAdded){
			MessageBox(NULL,"Rom is too small, expand rom to save added spells.","Error",MB_OK);
			fclose(fp);
			return;
		}

		LearnAdded=false;

		fseek(fp,132084,SEEK_SET);
		fprintf(fp,"%c",(LearnOffset&0xFF000000)/0x1000000);
		fprintf(fp,"%c",(LearnOffset&0x00FF0000)/0x10000);
		fprintf(fp,"%c",(LearnOffset&0x0000FF00)/0x100);
		fprintf(fp,"%c",(LearnOffset&0x000000FF));

		fseek(fp,LearnOffset,SEEK_SET);

		for(i=0;i<NumChars;i++){

			for(int x=0;x<NumLearn[i];x++){
				for(int y=x+1;y<NumLearn[i];y++){
					if(Learn[i][y][0]<Learn[i][x][0]){
						j = Learn[i][x][0];
						Learn[i][x][0] = Learn[i][y][0];
						Learn[i][y][0] = j;
						j = Learn[i][x][1];
						Learn[i][x][1] = Learn[i][y][1];
						Learn[i][y][1] = j;
						y=x;
					}
				}
			}

			if(NumLearn[i]){
				fprintf(fp,"%c",i);
				fprintf(fp,"%c",NumLearn[i]);
				for(j=0;j<NumLearn[i];j++){
					fprintf(fp,"%c",Learn[i][j][0]);
					fprintf(fp,"%c",Learn[i][j][1]);
				}
			}
		}

		fprintf(fp,"%c",255);
		fprintf(fp,"%c",255);

		if (NumChars == MAX_CHARS)CharOffset = 0x70200;

		fseek(fp,132008,SEEK_SET);
		fprintf(fp,"%c",(CharOffset&0xFF000000)/0x1000000);
		fprintf(fp,"%c",(CharOffset&0x00FF0000)/0x10000);
		fprintf(fp,"%c",(CharOffset&0x0000FF00)/0x100);
		fprintf(fp,"%c",(CharOffset&0x000000FF));

		fseek(fp,CharOffset,SEEK_SET);
		for(i=0; i<NumChars; i++){
			for(j=0; j<10; j++){
				fprintf(fp,"%c",CharName[i][j]);
			}
			CharName[i][10]=0;
			for(j=0; j<30; j++){
				fprintf(fp,"%c",Char[i][j]);
			}
		}

		if (NumChars == MAX_CHARS) {
			BSprOffset = 0x71300;
		}

		fseek(fp, 0x203AC, SEEK_SET);
		fprintf(fp, "%c", (BSprOffset & 0xFF000000) / 0x1000000);
		fprintf(fp, "%c", (BSprOffset & 0x00FF0000) / 0x10000);
		fprintf(fp, "%c", (BSprOffset & 0x0000FF00) / 0x100);
		fprintf(fp, "%c", (BSprOffset & 0x000000FF));

		fseek(fp, BSprOffset, SEEK_SET);
		for (i = 0; i<NumChars; i++) {
			fprintf(fp, "%c", BattleSprite[i][0]);
			fprintf(fp, "%c", BattleSprite[i][1]);
		}

		if (NumChars == MAX_CHARS) {
			fseek(fp, 0x71380, SEEK_SET);
			for (i = 0; i<NumChars; i++) {
				fprintf(fp, "%c", BattleSprite2[i][0]);
				fprintf(fp, "%c", BattleSprite2[i][1]);
			}
		}

		if (NumChars == MAX_CHARS) {
			UStatOffset = 0x71000;
		}

		fseek(fp, 0x203EC, SEEK_SET);
		fprintf(fp, "%c", (UStatOffset & 0xFF000000) / 0x1000000);
		fprintf(fp, "%c", (UStatOffset & 0x00FF0000) / 0x10000);
		fprintf(fp, "%c", (UStatOffset & 0x0000FF00) / 0x100);
		fprintf(fp, "%c", (UStatOffset & 0x000000FF));

		for(j=0;j<NumChars;j++){
			fseek(fp, UStatOffset +6*j,SEEK_SET);
			for(i=0;i<6;i++){
				fprintf(fp,"%c",Stats[j][i]);
			}
		}

		int q = NumChars;
		if (q == 30)q = 27;

		if (NumChars == MAX_CHARS) {
			PStatOffset = 0x71180;
		}

		fseek(fp, 0x203F0, SEEK_SET);
		fprintf(fp, "%c", (PStatOffset & 0xFF000000) / 0x1000000);
		fprintf(fp, "%c", (PStatOffset & 0x00FF0000) / 0x10000);
		fprintf(fp, "%c", (PStatOffset & 0x0000FF00) / 0x100);
		fprintf(fp, "%c", (PStatOffset & 0x000000FF));

		for(j=0;j<q;j++){
			fseek(fp, PStatOffset +6*j,SEEK_SET);
			for(i=0;i<6;i++){
				fprintf(fp,"%c",Stats[j][i+6]);
			}
		}

		fclose(fp);
		MessageBox(NULL,"Characters Saved","Note",MB_OK);
	}
}

void ExportChar(char*path){
	FILE * fp = fopen(path,"wb");
	int i;
	int j;
	for(i=0; i<30; i++){
		for(j=0; j<10; j++){
			fprintf(fp,"%c",CharName[i][j]);
		}
		for(j=0; j<30; j++){
			fprintf(fp,"%c",Char[i][j]);
		}
	}
	for(j=0;j<30;j++){
		for(i=0;i<6;i++){
			fprintf(fp,"%c",Stats[j][i]);
		}
	}
	for(j=0;j<27;j++){
		for(i=0;i<6;i++){
			fprintf(fp,"%c",Stats[j][i+6]);
		}
	}
	fprintf(fp,"%c",(LearnOffset&0xFF000000)/0x1000000);
	fprintf(fp,"%c",(LearnOffset&0x00FF0000)/0x10000);
	fprintf(fp,"%c",(LearnOffset&0x0000FF00)/0x100);
	fprintf(fp,"%c",(LearnOffset&0x000000FF));


	for(i=0;i<30;i++){
		if(NumLearn[i]){
			fprintf(fp,"%c",i);
			fprintf(fp,"%c",NumLearn[i]);
			for(j=0;j<NumLearn[i];j++){
				fprintf(fp,"%c",Learn[i][j][0]);
				fprintf(fp,"%c",Learn[i][j][1]);
			}
		}
	}


	fprintf(fp,"%c",255);
	fprintf(fp,"%c",255);

	fprintf(fp,"%c",(CharOffset&0xFF000000)/0x1000000);
	fprintf(fp,"%c",(CharOffset&0x00FF0000)/0x10000);
	fprintf(fp,"%c",(CharOffset&0x0000FF00)/0x100);
	fprintf(fp,"%c",(CharOffset&0x000000FF));

	fclose(fp);
	MessageBox(NULL,"Characters Exported","Note",MB_OK);
}

void CharExport(){
	OPENFILENAME openFileName;
	char path[256];
	path[0] = '\0';  
	memset( &openFileName, 0, sizeof(openFileName) );
	openFileName.lStructSize = sizeof(openFileName);
	openFileName.hwndOwner = NULL;
	openFileName.hInstance = NULL;
	openFileName.lpstrFilter = "Shining Force Characters(*.sfc)\0*.sfc\0";
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
	openFileName.lpstrDefExt = "sfc";
	openFileName.lCustData = NULL;
	openFileName.lpfnHook = NULL;
	openFileName.lpTemplateName = NULL;

	if(GetSaveFileName(&openFileName)!=0){
		ExportChar(path);
	}
}