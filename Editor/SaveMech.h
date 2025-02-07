long ArmorOffsets[] = {0x6CB6,0x70C8,0x71A2,0xD774,0xDB76,0xDAC4};

void SaveMech(){
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

		if (FixMuddle) {
			if (0x1FFB00 > romsize - 1) {
				MessageBox(NULL, "Rom is too small, expand rom to enable.", "Error", MB_OK);
				fclose(fp);
				return;
			}

			fseek(fp, 0x2123B, SEEK_SET);
			fprintf(fp, "%c", 0x02);

			fseek(fp, 0x2123D, SEEK_SET);
			fprintf(fp, "%c", 0x03);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0xB9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x1F);
			fprintf(fp, "%c", 0xFB);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0x71);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0x71);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0x71);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0x71);

			fseek(fp, 0x1FFB00, SEEK_SET);
			fprintf(fp, "%c", 0x48);
			fprintf(fp, "%c", 0xE7);
			fprintf(fp, "%c", 0xC0);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0xB9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x02);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0xCC);
			fprintf(fp, "%c", 0x08);
			fprintf(fp, "%c", 0x01);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x04);
			fprintf(fp, "%c", 0x66);
			fprintf(fp, "%c", 0x08);
			fprintf(fp, "%c", 0x08);
			fprintf(fp, "%c", 0x01);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x05);
			fprintf(fp, "%c", 0x66);
			fprintf(fp, "%c", 0x02);
			fprintf(fp, "%c", 0x60);
			fprintf(fp, "%c", 0x08);
			fprintf(fp, "%c", 0x74);
			fprintf(fp, "%c", 0x4B);
			fprintf(fp, "%c", 0x4C);
			fprintf(fp, "%c", 0xDF);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x03);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0x75);
			fprintf(fp, "%c", 0x4C);
			fprintf(fp, "%c", 0xDF);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x03);
			fprintf(fp, "%c", 0x48);
			fprintf(fp, "%c", 0xE7);
			fprintf(fp, "%c", 0xC0);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x10);
			fprintf(fp, "%c", 0x01);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0xB9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x02);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0xCC);
			fprintf(fp, "%c", 0x08);
			fprintf(fp, "%c", 0x01);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x04);
			fprintf(fp, "%c", 0x66);
			fprintf(fp, "%c", 0x08);
			fprintf(fp, "%c", 0x08);
			fprintf(fp, "%c", 0x01);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x05);
			fprintf(fp, "%c", 0x66);
			fprintf(fp, "%c", 0x02);
			fprintf(fp, "%c", 0x60);
			fprintf(fp, "%c", 0x02);
			fprintf(fp, "%c", 0x74);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x4C);
			fprintf(fp, "%c", 0xDF);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x03);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0x75);
		} else {
			fseek(fp, 0x2123B, SEEK_SET);
			fprintf(fp, "%c", 0x10);

			fseek(fp, 0x2123D, SEEK_SET);
			fprintf(fp, "%c", 0x19);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0xB9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x02);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0xCC);
			fprintf(fp, "%c", 0x08);
			fprintf(fp, "%c", 0x01);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x04);
			fprintf(fp, "%c", 0x66);
			fprintf(fp, "%c", 0x02);
			fprintf(fp, "%c", 0x74);
			fprintf(fp, "%c", 0x03);
		}

		if (ShowCrit) {
			if (0x1E3000>romsize - 1) {
				MessageBox(NULL, "Rom is too small, expand rom to enable.", "Error", MB_OK);
				fclose(fp);
				return;
			}
			fseek(fp, 0x248D4, SEEK_SET);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0xB9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x1E);
			fprintf(fp, "%c", 0x30);
			fprintf(fp, "%c", 0x00);

			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0x71);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0x71);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0x71);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0x71);

			fseek(fp, 0x1E3000, SEEK_SET);
			fprintf(fp, "%c", 0x12);
			fprintf(fp, "%c", 0x19);
			fprintf(fp, "%c", 0x67);
			fprintf(fp, "%c", 0x08);
			fprintf(fp, "%c", 0x20);
			fprintf(fp, "%c", 0x81);

			fprintf(fp, "%c", 0x30);
			fprintf(fp, "%c", 0x3C);
			fprintf(fp, "%c", 0x01);
			fprintf(fp, "%c", 0xF0);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0x48);

			fprintf(fp, "%c", 0x12);
			fprintf(fp, "%c", 0x19);
			fprintf(fp, "%c", 0x67);
			fprintf(fp, "%c", 0x08);
			fprintf(fp, "%c", 0x20);
			fprintf(fp, "%c", 0x81);

			fprintf(fp, "%c", 0x30);
			fprintf(fp, "%c", 0x3C);
			fprintf(fp, "%c", (SpecialMessages[3] & 0xFF00) / 0x100);
			fprintf(fp, "%c", (SpecialMessages[3] & 0x00FF));
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0x48);

			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0x75);

		} else {
			fseek(fp, 0x248D4, SEEK_SET);
			fprintf(fp, "%c", 0x12);
			fprintf(fp, "%c", 0x19);
			fprintf(fp, "%c", 0x67);
			fprintf(fp, "%c", 0x08);
			fprintf(fp, "%c", 0x20);
			fprintf(fp, "%c", 0x81);

			fprintf(fp, "%c", 0x30);
			fprintf(fp, "%c", 0x3C);
			fprintf(fp, "%c", 0x01);
			fprintf(fp, "%c", 0xF0);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0x48);
			fprintf(fp, "%c", 0x52);
			fprintf(fp, "%c", 0x89);
		}

		if (FixDoubles) {
			fseek(fp, 0x21986, SEEK_SET);

			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0x71);
			fprintf(fp, "%c", 0x72);
			fprintf(fp, "%c", 0x27);
			fprintf(fp, "%c", 0x60);
			fprintf(fp, "%c", 0x12);

			fprintf(fp, "%c", 0x3E);
			fprintf(fp, "%c", 0x01);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0xB9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x02);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x54);

			fprintf(fp, "%c", 0x0C);
			fprintf(fp, "%c", 0x47);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x03);

			fprintf(fp, "%c", 0x67);
			fprintf(fp, "%c", 0x18);

			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0x71);
		} else {
			fseek(fp, 0x21986, SEEK_SET);

			fprintf(fp, "%c", 0x0C);
			fprintf(fp, "%c", 0x47);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x27);
			fprintf(fp, "%c", 0x60);
			fprintf(fp, "%c", 0x1C);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0xB9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x02);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x54);
			fprintf(fp, "%c", 0x4A);
			fprintf(fp, "%c", 0x41);
			fprintf(fp, "%c", 0x67);
			fprintf(fp, "%c", 0x1C);
			fprintf(fp, "%c", 0x0C);
			fprintf(fp, "%c", 0x01);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x1C);
			fprintf(fp, "%c", 0x67);
			fprintf(fp, "%c", 0x16);
		}

		fseek(fp,0x23D0C,SEEK_SET);
		if(HealAI){
			if(0x1D8400>romsize-1){
				MessageBox(NULL,"Rom is too small, expand rom or use a smaller offset.","Error",MB_OK);
				fclose(fp);
				return;
			}

			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0xB9);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x1D);
			fprintf(fp,"%c",0x84);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0x71);

			fseek(fp,0x1D8400,SEEK_SET);
			fprintf(fp,"%c",0x48);
			fprintf(fp,"%c",0xE7);
			fprintf(fp,"%c",0xFF);
			fprintf(fp,"%c",0xFF);
			fprintf(fp,"%c",0x42);
			fprintf(fp,"%c",0x43);
			fprintf(fp,"%c",0x16);
			fprintf(fp,"%c",0x38);
			fprintf(fp,"%c",0xCB);
			fprintf(fp,"%c",0x40);
			fprintf(fp,"%c",0x38);
			fprintf(fp,"%c",0x03);
			fprintf(fp,"%c",0xE5);
			fprintf(fp,"%c",0x1C);
			fprintf(fp,"%c",0x02);
			fprintf(fp,"%c",0x44);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0xFF);
			fprintf(fp,"%c",0xE5);
			fprintf(fp,"%c",0x44);
			fprintf(fp,"%c",0x22);
			fprintf(fp,"%c",0x79);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x02);
			fprintf(fp,"%c",0x03);
			fprintf(fp,"%c",0xCC);
			fprintf(fp,"%c",0xD2);
			fprintf(fp,"%c",0xC4);
			fprintf(fp,"%c",0x10);
			fprintf(fp,"%c",0x29);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x01);
			fprintf(fp,"%c",0x43);
			fprintf(fp,"%c",0xF9);
			fprintf(fp,"%c",(EffectOffset&0xFF000000)/0x1000000);
			fprintf(fp,"%c",(EffectOffset&0x00FF0000)/0x10000);
			fprintf(fp,"%c",(EffectOffset&0x0000FF00)/0x100);
			fprintf(fp,"%c",(EffectOffset&0x000000FF));
			fprintf(fp,"%c",0xE7);
			fprintf(fp,"%c",0x40);
			fprintf(fp,"%c",0xD2);
			fprintf(fp,"%c",0xC0);
			fprintf(fp,"%c",0x30);
			fprintf(fp,"%c",0x29);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x06);
			fprintf(fp,"%c",0x0C);
			fprintf(fp,"%c",0x40);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x34);
			fprintf(fp,"%c",0x66);
			fprintf(fp,"%c",0x2E);
			fprintf(fp,"%c",0x1A);
			fprintf(fp,"%c",0x29);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x03);

			fprintf(fp,"%c",0x0C);
			fprintf(fp,"%c",0x05);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0xFF);
			fprintf(fp,"%c",0x67);
			fprintf(fp,"%c",0x18);

			fprintf(fp,"%c",0x10);
			fprintf(fp,"%c",0x38);
			fprintf(fp,"%c",0xA9);
			fprintf(fp,"%c",0x47);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0xB9);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x02);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0xD0);
			fprintf(fp,"%c",0x34);
			fprintf(fp,"%c",0x01);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0xB9);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x02);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0xD4);
			fprintf(fp,"%c",0x94);
			fprintf(fp,"%c",0x41);
			fprintf(fp,"%c",0xBA);
			fprintf(fp,"%c",0x02);
			fprintf(fp,"%c",0x6D);
			fprintf(fp,"%c",0x0C);
			fprintf(fp,"%c",0x11);
			fprintf(fp,"%c",0xC3);
			fprintf(fp,"%c",0xCB);
			fprintf(fp,"%c",0x40);
			fprintf(fp,"%c",0x04);
			fprintf(fp,"%c",0x43);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x40);
			fprintf(fp,"%c",0x65);
			fprintf(fp,"%c",0x02);
			fprintf(fp,"%c",0x60);
			fprintf(fp,"%c",0xA8);
			fprintf(fp,"%c",0x4C);
			fprintf(fp,"%c",0xDF);
			fprintf(fp,"%c",0xFF);
			fprintf(fp,"%c",0xFF);
			fprintf(fp,"%c",0x12);
			fprintf(fp,"%c",0xF8);
			fprintf(fp,"%c",0xCB);
			fprintf(fp,"%c",0x3F);
			fprintf(fp,"%c",0x12);
			fprintf(fp,"%c",0xF8);
			fprintf(fp,"%c",0xCB);
			fprintf(fp,"%c",0x40);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0x75);
		} else {
			fprintf(fp,"%c",0x12);
			fprintf(fp,"%c",0xF8);
			fprintf(fp,"%c",0xCB);
			fprintf(fp,"%c",0x3F);
			fprintf(fp,"%c",0x12);
			fprintf(fp,"%c",0xF8);
			fprintf(fp,"%c",0xCB);
			fprintf(fp,"%c",0x40);
		}

		fseek(fp,0x17441,SEEK_SET);
		fprintf(fp,"%c",ProLevel);

		fseek(fp,0x17361,SEEK_SET);
		fprintf(fp,"%c",ProLevelAdd);
		fseek(fp,0x24BCB,SEEK_SET);
		fprintf(fp,"%c",ProLevelAdd);

		fseek(fp, 0x20CC7, SEEK_SET);
		fprintf(fp, "%c", HPEXPPercent);

		fseek(fp, 0x20CCF, SEEK_SET);
		fprintf(fp, "%c", HPEXPMin);

		fseek(fp, 0x20CD5, SEEK_SET);
		fprintf(fp, "%c", HPEXPMin);

		fseek(fp, 0x24A21, SEEK_SET);
		fprintf(fp, "%c", PromotePercent);

		fseek(fp,150742,SEEK_SET);
		fprintf(fp,"%c",(PoisonOffset&0xFF000000)/0x1000000);
		fprintf(fp,"%c",(PoisonOffset&0x00FF0000)/0x10000);
		fprintf(fp,"%c",(PoisonOffset&0x0000FF00)/0x100);
		fprintf(fp,"%c",(PoisonOffset&0x000000FF));

		fseek(fp,135485,SEEK_SET);
		fprintf(fp,"%c",CritMult*2);

		fseek(fp,135557,SEEK_SET);
		fprintf(fp,"%c",DamageSpread);

		fseek(fp,135579,SEEK_SET);
		fprintf(fp,"%c",DamageBase);

		fseek(fp,0x216A1,SEEK_SET);
		fprintf(fp,"%c",BreakChance);

		fseek(fp,0x2199D,SEEK_SET);
		fprintf(fp,"%c",DoubleChance);

		if(DisallowRevive){
			fseek(fp,0x17378,SEEK_SET);
			fprintf(fp,"%c",0x01);
			fprintf(fp,"%c",0x9A);

			fseek(fp,0x1737E,SEEK_SET);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0xF9);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x01);
			fprintf(fp,"%c",0x73);
			fprintf(fp,"%c",0x92);
		} else {
			fseek(fp,0x17378,SEEK_SET);
			fprintf(fp,"%c",0x01);
			fprintf(fp,"%c",0x9F);

			fseek(fp,0x1737E,SEEK_SET);
			fprintf(fp,"%c",0x61);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0xFA);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0x61);
			fprintf(fp,"%c",0x00);
		}

		if(JogurtLevels){
			fseek(fp,0x24718,SEEK_SET);
			fprintf(fp, "%c", 0x4E); // nop
			fprintf(fp, "%c", 0x71);

			fseek(fp,0x2488C,SEEK_SET);
			fprintf(fp, "%c", 0x60); // bra.s   byte_2489A
			fprintf(fp, "%c", 0x0C);

			fseek(fp, 0x17436, SEEK_SET);
			fprintf(fp, "%c", 0x4E); // nop
			fprintf(fp, "%c", 0x71);

			fseek(fp, 0x1755A, SEEK_SET);
			fprintf(fp, "%c", 0x4E); // nop
			fprintf(fp, "%c", 0x71);
		} else {
			fseek(fp,0x24718,SEEK_SET);
			fprintf(fp, "%c", 0x67); // beq.s   loc_24722
			fprintf(fp, "%c", 0x08);

			fseek(fp,0x2488C,SEEK_SET);
			fprintf(fp, "%c", 0x66); // bne.s   byte_2489A
			fprintf(fp, "%c", 0x0C);

			fseek(fp, 0x17436, SEEK_SET);
			fprintf(fp, "%c", 0x67); // beq.s   loc_17456
			fprintf(fp, "%c", 0x1E);

			fseek(fp, 0x1755A, SEEK_SET);
			fprintf(fp, "%c", 0x67); // beq.s   loc_17562
			fprintf(fp, "%c", 0x06);
		}

		if(ExtendStatItems){
			if(0x1A5500>romsize-1){
				MessageBox(NULL,"Rom is too small, expand rom or use a smaller offset.","Error",MB_OK);
				fclose(fp);
				return;
			}
			fseek(fp,0x2339A,SEEK_SET);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0xF9);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x1A);
			fprintf(fp,"%c",0x55);
			fprintf(fp,"%c",0x00);

			fseek(fp,0x1A5500,SEEK_SET);

			fprintf(fp,"%c",0x34);
			fprintf(fp,"%c",0x07);
			fprintf(fp,"%c",0x0C);
			fprintf(fp,"%c",0x01);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x05);
			fprintf(fp,"%c",0x6A);
			fprintf(fp,"%c",0x0A);
			fprintf(fp,"%c",0x36);
			fprintf(fp,"%c",0x01);
			fprintf(fp,"%c",0xE5);
			fprintf(fp,"%c",0x43);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0xF9);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x02);
			fprintf(fp,"%c",0x33);
			fprintf(fp,"%c",0xA0);
			fprintf(fp,"%c",0x31);
			fprintf(fp,"%c",0xFC);

			fprintf(fp,"%c",(SpecialMessages[0]&0xFF00)/0x100);
			fprintf(fp,"%c",(SpecialMessages[0]&0x00FF));

			fprintf(fp,"%c",0xA9);
			fprintf(fp,"%c",0xE0);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0xB9);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x02);
			fprintf(fp,"%c",0x25);
			fprintf(fp,"%c",0x38);
			fprintf(fp,"%c",0xC3);
			fprintf(fp,"%c",0x42);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0xB9);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x02);
			fprintf(fp,"%c",0x2B);
			fprintf(fp,"%c",0xAE);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0xF9);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x02);
			fprintf(fp,"%c",0x33);
			fprintf(fp,"%c",0xAA);

		} else {
			fseek(fp,0x2339A,SEEK_SET);
			fprintf(fp,"%c",0x34);
			fprintf(fp,"%c",0x07);
			fprintf(fp,"%c",0x36);
			fprintf(fp,"%c",0x01);
			fprintf(fp,"%c",0xE5);
			fprintf(fp,"%c",0x43);
		}

		if (AddMPEffect) {
			if (0x1AB000 > romsize - 1) {
				MessageBox(NULL, "Rom is too small, expand rom or use a smaller offset.", "Error", MB_OK);
				fclose(fp);
				return;
			}

			fseek(fp, 0x1AA050, SEEK_SET);
			fprintf(fp, "%c", 0xD0);
			fprintf(fp, "%c", 0xC5);
			fprintf(fp, "%c", 0x3A);
			fprintf(fp, "%c", 0x28);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x06);
			fprintf(fp, "%c", 0x0C);
			fprintf(fp, "%c", 0x45);
			fprintf(fp, "%c", 0xEE);
			fprintf(fp, "%c", 0xEE);
			fprintf(fp, "%c", 0x66);
			fprintf(fp, "%c", 0x0C);
			fprintf(fp, "%c", 0x43);
			fprintf(fp, "%c", 0xF9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x1A);
			fprintf(fp, "%c", 0xA0);
			fprintf(fp, "%c", 0x90);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0xF9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x02);
			fprintf(fp, "%c", 0x0C);
			fprintf(fp, "%c", 0x36);

			fprintf(fp, "%c", 0x0C);
			fprintf(fp, "%c", 0x45);
			fprintf(fp, "%c", 0xDD);
			fprintf(fp, "%c", 0xDD);
			fprintf(fp, "%c", 0x66);
			fprintf(fp, "%c", 0x0C);
			fprintf(fp, "%c", 0x43);
			fprintf(fp, "%c", 0xF9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x1A);
			fprintf(fp, "%c", 0x9F);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0xF9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x02);
			fprintf(fp, "%c", 0x0C);
			fprintf(fp, "%c", 0x36);

			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0xF9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x02);
			fprintf(fp, "%c", 0x0C);
			fprintf(fp, "%c", 0x32);


			fseek(fp, 0x1AA090, SEEK_SET);
			fprintf(fp, "%c", 0x48);
			fprintf(fp, "%c", 0xE7);
			fprintf(fp, "%c", 0x30);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x48);
			fprintf(fp, "%c", 0xA7);
			fprintf(fp, "%c", 0xC0);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x30);
			fprintf(fp, "%c", 0x01);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0xB9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x02);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0xD8);
			fprintf(fp, "%c", 0x34);
			fprintf(fp, "%c", 0x01);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0xB9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x02);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0xDC);
			fprintf(fp, "%c", 0x94);
			fprintf(fp, "%c", 0x41);
			fprintf(fp, "%c", 0x4C);
			fprintf(fp, "%c", 0x9F);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x03);
			fprintf(fp, "%c", 0x16);
			fprintf(fp, "%c", 0x28);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x03);
			fprintf(fp, "%c", 0x0C);
			fprintf(fp, "%c", 0x03);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0xFF);
			fprintf(fp, "%c", 0x66);
			fprintf(fp, "%c", 0x04);
			fprintf(fp, "%c", 0x36);
			fprintf(fp, "%c", 0x02);
			fprintf(fp, "%c", 0x60);
			fprintf(fp, "%c", 0x06);
			fprintf(fp, "%c", 0x48);
			fprintf(fp, "%c", 0x83);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0xB9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x02);
			fprintf(fp, "%c", 0x11);
			fprintf(fp, "%c", 0x80);
			fprintf(fp, "%c", 0xB4);
			fprintf(fp, "%c", 0x43);
			fprintf(fp, "%c", 0x6C);
			fprintf(fp, "%c", 0x02);
			fprintf(fp, "%c", 0x36);
			fprintf(fp, "%c", 0x02);
			fprintf(fp, "%c", 0x31);
			fprintf(fp, "%c", 0xFC);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x01);
			fprintf(fp, "%c", 0xA9);
			fprintf(fp, "%c", 0xDE);
			fprintf(fp, "%c", 0x31);
			fprintf(fp, "%c", 0xC3);
			fprintf(fp, "%c", 0xA9);
			fprintf(fp, "%c", 0xDA);
			fprintf(fp, "%c", 0x31);
			fprintf(fp, "%c", 0xFC);
			fprintf(fp, "%c", (SpecialMessages[2] & 0xFF00) / 0x100);
			fprintf(fp, "%c", (SpecialMessages[2] & 0x00FF));
			fprintf(fp, "%c", 0xA9);
			fprintf(fp, "%c", 0xE0);
			fprintf(fp, "%c", 0x31);
			fprintf(fp, "%c", 0xC1);
			fprintf(fp, "%c", 0xA9);
			fprintf(fp, "%c", 0xE2);
			fprintf(fp, "%c", 0x48);
			fprintf(fp, "%c", 0xC3);
			fprintf(fp, "%c", 0x21);
			fprintf(fp, "%c", 0xC3);
			fprintf(fp, "%c", 0xA9);
			fprintf(fp, "%c", 0xE6);
			fprintf(fp, "%c", 0x4C);
			fprintf(fp, "%c", 0xDF);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x0C);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0x75);

			fseek(fp, 0x20C2C, SEEK_SET);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0xF9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x1A);
			fprintf(fp, "%c", 0xA0);
			fprintf(fp, "%c", 0x50);

			fseek(fp, 0x1A9F00, SEEK_SET);
			fprintf(fp, "%c", 0x48);
			fprintf(fp, "%c", 0xE7);
			fprintf(fp, "%c", 0x3F);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0xB9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x02);
			fprintf(fp, "%c", 0x11);
			fprintf(fp, "%c", 0xFC);
			fprintf(fp, "%c", 0x64);
			fprintf(fp, "%c", 0x06);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0xF9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x02);
			fprintf(fp, "%c", 0x0D);
			fprintf(fp, "%c", 0xE2);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0xB9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x02);
			fprintf(fp, "%c", 0x26);
			fprintf(fp, "%c", 0x10);
			fprintf(fp, "%c", 0x6D);
			fprintf(fp, "%c", 0x08);
			fprintf(fp, "%c", 0x31);
			fprintf(fp, "%c", 0xFC);
			fprintf(fp, "%c", 0x01);
			fprintf(fp, "%c", 0xBB);
			fprintf(fp, "%c", 0xA9);
			fprintf(fp, "%c", 0xE0);
			fprintf(fp, "%c", 0x60);
			fprintf(fp, "%c", 0x06);
			fprintf(fp, "%c", 0x31);
			fprintf(fp, "%c", 0xFC);
			fprintf(fp, "%c", 0x01);
			fprintf(fp, "%c", 0xBC);
			fprintf(fp, "%c", 0xA9);
			fprintf(fp, "%c", 0xE0);
			fprintf(fp, "%c", 0x31);
			fprintf(fp, "%c", 0xC1);
			fprintf(fp, "%c", 0xA9);
			fprintf(fp, "%c", 0xE2);
			fprintf(fp, "%c", 0x42);
			fprintf(fp, "%c", 0x78);
			fprintf(fp, "%c", 0xCB);
			fprintf(fp, "%c", 0x5E);
			fprintf(fp, "%c", 0x14);
			fprintf(fp, "%c", 0x28);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x02);
			fprintf(fp, "%c", 0x02);
			fprintf(fp, "%c", 0x02);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x07);
			fprintf(fp, "%c", 0x42);
			fprintf(fp, "%c", 0x43);
			fprintf(fp, "%c", 0x16);
			fprintf(fp, "%c", 0x28);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x03);
			fprintf(fp, "%c", 0x2F);
			fprintf(fp, "%c", 0x09);
			fprintf(fp, "%c", 0x43);
			fprintf(fp, "%c", 0xF8);
			fprintf(fp, "%c", 0xA9);
			fprintf(fp, "%c", 0x46);
			fprintf(fp, "%c", 0x48);
			fprintf(fp, "%c", 0x43);
			fprintf(fp, "%c", 0x42);
			fprintf(fp, "%c", 0x43);
			fprintf(fp, "%c", 0x48);
			fprintf(fp, "%c", 0x43);
			fprintf(fp, "%c", 0x42);
			fprintf(fp, "%c", 0x44);
			fprintf(fp, "%c", 0x0C);
			fprintf(fp, "%c", 0x11);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0xFF);
			fprintf(fp, "%c", 0x67);
			fprintf(fp, "%c", 0x06);
			fprintf(fp, "%c", 0x52);
			fprintf(fp, "%c", 0x04);
			fprintf(fp, "%c", 0x54);
			fprintf(fp, "%c", 0x89);
			fprintf(fp, "%c", 0x60);
			fprintf(fp, "%c", 0xF4);
			fprintf(fp, "%c", 0x87);
			fprintf(fp, "%c", 0xC4);
			fprintf(fp, "%c", 0x22);
			fprintf(fp, "%c", 0x5F);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0xB9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x02);
			fprintf(fp, "%c", 0x11);
			fprintf(fp, "%c", 0x80);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0xB9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x02);
			fprintf(fp, "%c", 0x11);
			fprintf(fp, "%c", 0xC6);
			fprintf(fp, "%c", 0x18);
			fprintf(fp, "%c", 0x28);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x02);
			fprintf(fp, "%c", 0x02);
			fprintf(fp, "%c", 0x44);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x18);
			fprintf(fp, "%c", 0xE4);
			fprintf(fp, "%c", 0x44);
			fprintf(fp, "%c", 0x38);
			fprintf(fp, "%c", 0x3B);
			fprintf(fp, "%c", 0x40);
			fprintf(fp, "%c", 0x1E);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0xB9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x02);
			fprintf(fp, "%c", 0x12);
			fprintf(fp, "%c", 0xA6);
			fprintf(fp, "%c", 0xBE);
			fprintf(fp, "%c", 0x44);
			fprintf(fp, "%c", 0x64);
			fprintf(fp, "%c", 0x06);
			fprintf(fp, "%c", 0x31);
			fprintf(fp, "%c", 0xFC);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x03);
			fprintf(fp, "%c", 0xCB);
			fprintf(fp, "%c", 0x5E);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0xB9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x02);
			fprintf(fp, "%c", 0x11);
			fprintf(fp, "%c", 0x28);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0xF9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x02);
			fprintf(fp, "%c", 0x0D);
			fprintf(fp, "%c", 0xCC);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x03);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x04);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x06);


		} else {
			fseek(fp, 0x20C2C, SEEK_SET);
			fprintf(fp, "%c", 0xD0);
			fprintf(fp, "%c", 0xC5);
			fprintf(fp, "%c", 0x3A);
			fprintf(fp, "%c", 0x28);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x06);
		}

		if(PoisonOffset==0x20244){
			fseek(fp,150739,SEEK_SET);
			fprintf(fp,"%c",Poison);
			fseek(fp,150578,SEEK_SET);
			fprintf(fp,"%c",0x21);
			fprintf(fp,"%c",0xFC);
			fprintf(fp,"%c",0);
			fprintf(fp,"%c",0);
			fprintf(fp,"%c",0);
			fprintf(fp,"%c",Poison);
			fprintf(fp,"%c",0xA9);
			fprintf(fp,"%c",0xD4);
		} else {
			if(PoisonOffset>romsize-1){
				MessageBox(NULL,"Rom is too small, expand rom or use a smaller offset.","Error",MB_OK);
				fclose(fp);
				return;
			}
			fseek(fp,150578,SEEK_SET);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0xB9);
			fprintf(fp,"%c",((PoisonOffset+0x1C)&0xFF000000)/0x1000000);
			fprintf(fp,"%c",((PoisonOffset+0x1C)&0x00FF0000)/0x10000);
			fprintf(fp,"%c",((PoisonOffset+0x1C)&0x0000FF00)/0x100);
			fprintf(fp,"%c",((PoisonOffset+0x1C)&0x000000FF));
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0x71);
			fseek(fp,PoisonOffset,SEEK_SET);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0xB9);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x02);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0xD0);
			fprintf(fp,"%c",0xC2);
			fprintf(fp,"%c",0xFC);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",Poison);
			fprintf(fp,"%c",0x82);
			fprintf(fp,"%c",0xFC);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x64);
			fprintf(fp,"%c",0x02);
			fprintf(fp,"%c",0x81);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0xFF);
			fprintf(fp,"%c",0xFF);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0xB9);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x02);
			fprintf(fp,"%c",0x02);
			fprintf(fp,"%c",0x44);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0x75);
			fprintf(fp,"%c",0x10);
			fprintf(fp,"%c",0x38);
			fprintf(fp,"%c",0xB5);
			fprintf(fp,"%c",0x3B);
			fprintf(fp,"%c",0x22);
			fprintf(fp,"%c",0x3C);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0xB9);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x02);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0xD0);
			fprintf(fp,"%c",0xC2);
			fprintf(fp,"%c",0xFC);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",Poison);
			fprintf(fp,"%c",0x82);
			fprintf(fp,"%c",0xFC);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x64);
			fprintf(fp,"%c",0x02);
			fprintf(fp,"%c",0x81);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0xFF);
			fprintf(fp,"%c",0xFF);
			fprintf(fp,"%c",0x23);
			fprintf(fp,"%c",0xC1);
			fprintf(fp,"%c",0xFF);
			fprintf(fp,"%c",0xFF);
			fprintf(fp,"%c",0xA9);
			fprintf(fp,"%c",0xD4);
			fprintf(fp,"%c",0x30);
			fprintf(fp,"%c",0x39);
			fprintf(fp,"%c",0xFF);
			fprintf(fp,"%c",0xFF);
			fprintf(fp,"%c",0xA9);
			fprintf(fp,"%c",0xD0);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0x75);
		}

		if(!RemoveMarks){
			//static text
			//attack
			fseek(fp,47647,SEEK_SET);
			fprintf(fp,"%c",0x41);
			fseek(fp,1,SEEK_CUR);
			fprintf(fp,"%c",0x54);
			fseek(fp,1,SEEK_CUR);
			fprintf(fp,"%c",0x54);
			fseek(fp,1,SEEK_CUR);
			fprintf(fp,"%c",0x41);
			fseek(fp,1,SEEK_CUR);
			fprintf(fp,"%c",0x43);
			fseek(fp,1,SEEK_CUR);
			fprintf(fp,"%c",0x4B);
			fseek(fp,1,SEEK_CUR);
			fprintf(fp,"%c",0x20);
			//hp
			fseek(fp,65,SEEK_CUR);
			fprintf(fp,"%c",0x2F);
			fseek(fp,1,SEEK_CUR);
			fprintf(fp,"%c",0x3F);
			fseek(fp,3,SEEK_CUR);
			fprintf(fp,"%c",0x20);
			//defense
			fseek(fp,1,SEEK_CUR);
			fprintf(fp,"%c",0x44);
			fseek(fp,1,SEEK_CUR);
			fprintf(fp,"%c",0x45);
			fseek(fp,1,SEEK_CUR);
			fprintf(fp,"%c",0x46);
			fseek(fp,1,SEEK_CUR);
			fprintf(fp,"%c",0x45);
			fseek(fp,1,SEEK_CUR);
			fprintf(fp,"%c",0x4E);
			fseek(fp,1,SEEK_CUR);
			fprintf(fp,"%c",0x53);
			fseek(fp,1,SEEK_CUR);
			fprintf(fp,"%c",0x45);
			fseek(fp,1,SEEK_CUR);
			fprintf(fp,"%c",0x20);
			//mp
			fseek(fp,65,SEEK_CUR);
			fprintf(fp,"%c",0x2F);
			fseek(fp,1,SEEK_CUR);
			fprintf(fp,"%c",0x3F);
			fseek(fp,3,SEEK_CUR);
			fprintf(fp,"%c",0x20);
			fseek(fp,1,SEEK_CUR);
			fprintf(fp,"%c",0x20);
			//mov
			fseek(fp,11,SEEK_CUR);
			fprintf(fp,"%c",0x45);
			fseek(fp,1,SEEK_CUR);
			fprintf(fp,"%c",0x20);
			//exp
			fseek(fp,67,SEEK_CUR);
			fprintf(fp,"%c",0x3F);
			fseek(fp,1,SEEK_CUR);
			fprintf(fp,"%c",0x3F);
			fseek(fp,1,SEEK_CUR);
			fprintf(fp,"%c",0x20);
			//agi
			fseek(fp,1,SEEK_CUR);
			fprintf(fp,"%c",0x41);
			fseek(fp,1,SEEK_CUR);
			fprintf(fp,"%c",0x47);
			fseek(fp,1,SEEK_CUR);
			fprintf(fp,"%c",0x49);
			fseek(fp,1,SEEK_CUR);
			fprintf(fp,"%c",0x4C);
			fseek(fp,1,SEEK_CUR);
			fprintf(fp,"%c",0x49);
			fseek(fp,1,SEEK_CUR);
			fprintf(fp,"%c",0x54);
			fseek(fp,1,SEEK_CUR);
			fprintf(fp,"%c",0x59);
			fseek(fp,1,SEEK_CUR);
			fprintf(fp,"%c",0x20);

			//data
			//level
			fseek(fp,46023,SEEK_SET);
			fprintf(fp,"%c",0x6E);
			fseek(fp,46025,SEEK_SET);
			fprintf(fp,"%c",0x02);

			fseek(fp, 0xB3F3, SEEK_SET);
			fprintf(fp, "%c", 0x6C);

			//hp
			fseek(fp,45886,SEEK_SET);
			fprintf(fp,"%c",0x0C);
			fprintf(fp,"%c",0x41);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x64);
			fprintf(fp,"%c",0x6C);
			fprintf(fp,"%c",0x0E);
			fseek(fp,45897,SEEK_SET);
			fprintf(fp,"%c",0x02);
			//max hp
			fseek(fp,45916,SEEK_SET);
			fprintf(fp,"%c",0x0C);
			fprintf(fp,"%c",0x41);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x64);
			fprintf(fp,"%c",0x6C);
			fprintf(fp,"%c",0x10);
			fseek(fp,45926,SEEK_SET);
			fprintf(fp,"%c",0x54);
			fseek(fp,45929,SEEK_SET);
			fprintf(fp,"%c",0x02);

			//mp
			fseek(fp,45948,SEEK_SET);
			fprintf(fp,"%c",0x0C);
			fprintf(fp,"%c",0x41);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x64);
			fprintf(fp,"%c",0x6C);
			fprintf(fp,"%c",0x0E);
			fseek(fp,45959,SEEK_SET);
			fprintf(fp,"%c",0x02);
			//max mp
			fseek(fp,45978,SEEK_SET);
			fprintf(fp,"%c",0x0C);
			fprintf(fp,"%c",0x41);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x64);
			fprintf(fp,"%c",0x6C);
			fprintf(fp,"%c",0x10);
			fseek(fp,45988,SEEK_SET);
			fprintf(fp,"%c",0x54);
			fseek(fp,45991,SEEK_SET);
			fprintf(fp,"%c",0x02);

			//exp
			fseek(fp,46047,SEEK_SET);
			fprintf(fp,"%c",0x76);

			fseek(fp, 0xB401, SEEK_SET);
			fprintf(fp, "%c", 0x74);

			//att
			fseek(fp,46101,SEEK_SET);
			fprintf(fp,"%c",0x84);
			fseek(fp,46103,SEEK_SET);
			fprintf(fp,"%c",0x02);

			//def
			fseek(fp,46125,SEEK_SET);
			fprintf(fp,"%c",0xDC);
			fseek(fp,46127,SEEK_SET);
			fprintf(fp,"%c",0x02);

			//mov
			fseek(fp,46149,SEEK_SET);
			fprintf(fp,"%c",0x34);
			fseek(fp,46151,SEEK_SET);
			fprintf(fp,"%c",0x02);

			//agi
			fseek(fp,46173,SEEK_SET);
			fprintf(fp,"%c",0x8C);
			fseek(fp,46175,SEEK_SET);
			fprintf(fp,"%c",0x02);
		} else {
			//static text
			//attack
			fseek(fp,47647,SEEK_SET);
			fprintf(fp,"%c",0x20);
			fseek(fp,1,SEEK_CUR);
			fprintf(fp,"%c",0x20);
			fseek(fp,1,SEEK_CUR);
			fprintf(fp,"%c",0x41);
			fseek(fp,1,SEEK_CUR);
			fprintf(fp,"%c",0x54);
			fseek(fp,1,SEEK_CUR);
			fprintf(fp,"%c",0x54);
			fseek(fp,1,SEEK_CUR);
			fprintf(fp,"%c",0x20);
			fseek(fp,1,SEEK_CUR);
			fprintf(fp,"%c",0x39);
			//hp
			fseek(fp,65,SEEK_CUR);
			fprintf(fp,"%c",0x3F);
			fseek(fp,1,SEEK_CUR);
			fprintf(fp,"%c",0x2F);
			fseek(fp,3,SEEK_CUR);
			fprintf(fp,"%c",0x3F);
			fseek(fp,1,SEEK_CUR);
			fprintf(fp,"%c",0x3F);
			//defense
			fseek(fp,1,SEEK_CUR);
			fprintf(fp,"%c",0x20);
			fseek(fp,1,SEEK_CUR);
			fprintf(fp,"%c",0x20);
			fseek(fp,1,SEEK_CUR);
			fprintf(fp,"%c",0x44);
			fseek(fp,1,SEEK_CUR);
			fprintf(fp,"%c",0x45);
			fseek(fp,1,SEEK_CUR);
			fprintf(fp,"%c",0x46);
			fseek(fp,1,SEEK_CUR);
			fprintf(fp,"%c",0x20);
			fseek(fp,1,SEEK_CUR);
			fprintf(fp,"%c",0x39);
			//mp
			fseek(fp,65,SEEK_CUR);
			fprintf(fp,"%c",0x3F);
			fseek(fp,1,SEEK_CUR);
			fprintf(fp,"%c",0x2F);
			fseek(fp,3,SEEK_CUR);
			fprintf(fp,"%c",0x3F);
			fseek(fp,1,SEEK_CUR);
			fprintf(fp,"%c",0x3F);
			//mov
			fseek(fp,11,SEEK_CUR);
			fprintf(fp,"%c",0x20);
			fseek(fp,1,SEEK_CUR);
			fprintf(fp,"%c",0x39);
			//exp
			fseek(fp,67,SEEK_CUR);
			fprintf(fp,"%c",0x20);
			fseek(fp,1,SEEK_CUR);
			fprintf(fp,"%c",0x20);
			fseek(fp,1,SEEK_CUR);
			fprintf(fp,"%c",0x3F);
			fseek(fp,1,SEEK_CUR);
			fprintf(fp,"%c",0x3F);
			//agi
			fseek(fp,1,SEEK_CUR);
			fprintf(fp,"%c",0x20);
			fseek(fp,1,SEEK_CUR);
			fprintf(fp,"%c",0x20);
			fseek(fp,1,SEEK_CUR);
			fprintf(fp,"%c",0x41);
			fseek(fp,1,SEEK_CUR);
			fprintf(fp,"%c",0x47);
			fseek(fp,1,SEEK_CUR);
			fprintf(fp,"%c",0x49);
			fseek(fp,1,SEEK_CUR);
			fprintf(fp,"%c",0x20);
			fseek(fp,1,SEEK_CUR);
			fprintf(fp,"%c",0x39);

			//data
			//level
			fseek(fp,46023,SEEK_SET);
			fprintf(fp,"%c",0x70);
			fseek(fp,46025,SEEK_SET);
			fprintf(fp,"%c",0x03);

			fseek(fp, 0xB3F3, SEEK_SET);
			fprintf(fp, "%c", 0x70);

			//hp
			fseek(fp,45886,SEEK_SET);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0x71);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0x71);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0x71);
			fseek(fp,45897,SEEK_SET);
			fprintf(fp,"%c",0x03);
			//max hp
			fseek(fp,45916,SEEK_SET);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0x71);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0x71);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0x71);
			fseek(fp,45926,SEEK_SET);
			fprintf(fp,"%c",0x58);
			fseek(fp,45929,SEEK_SET);
			fprintf(fp,"%c",0x03);

			//mp
			fseek(fp,45948,SEEK_SET);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0x71);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0x71);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0x71);
			fseek(fp,45959,SEEK_SET);
			fprintf(fp,"%c",0x03);
			//max mp
			fseek(fp,45978,SEEK_SET);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0x71);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0x71);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0x71);
			fseek(fp,45988,SEEK_SET);
			fprintf(fp,"%c",0x58);
			fseek(fp,45991,SEEK_SET);
			fprintf(fp,"%c",0x03);

			//exp
			fseek(fp,46047,SEEK_SET);
			fprintf(fp,"%c",0x7A);

			fseek(fp, 0xB401, SEEK_SET);
			fprintf(fp, "%c", 0x78);

			//att
			fseek(fp,46101,SEEK_SET);
			fprintf(fp,"%c",0x82);
			fseek(fp,46103,SEEK_SET);
			fprintf(fp,"%c",0x03);

			//def
			fseek(fp,46125,SEEK_SET);
			fprintf(fp,"%c",0xDA);
			fseek(fp,46127,SEEK_SET);
			fprintf(fp,"%c",0x03);

			//mov
			fseek(fp,46149,SEEK_SET);
			fprintf(fp,"%c",0x32);
			fseek(fp,46151,SEEK_SET);
			fprintf(fp,"%c",0x03);

			//agi
			fseek(fp,46173,SEEK_SET);
			fprintf(fp,"%c",0x8A);
			fseek(fp,46175,SEEK_SET);
			fprintf(fp,"%c",0x03);
		}

		if(!DisplayCrit){
			fseek(fp,0xBB83,SEEK_SET);
			fprintf(fp,"%c",0x20);
			fprintf(fp,"%c",0xC0);
			fprintf(fp,"%c",0x20);
			fprintf(fp,"%c",0xC0);
			fprintf(fp,"%c",0x20);
			fprintf(fp,"%c",0xC0);
			fprintf(fp,"%c",0x20);

			fseek(fp,0xBB97,SEEK_SET);
			fprintf(fp,"%c",0x4D);
			fprintf(fp,"%c",0xC0);
			fprintf(fp,"%c",0x41);
			fprintf(fp,"%c",0xC0);
			fprintf(fp,"%c",0x47);
			fprintf(fp,"%c",0xC0);
			fprintf(fp,"%c",0x49);
			fprintf(fp,"%c",0xC0);
			fprintf(fp,"%c",0x43);

			fseek(fp,0xBBA9,SEEK_SET);
			fprintf(fp,"%c",0x49);
			fprintf(fp,"%c",0xC0);
			fprintf(fp,"%c",0x54);
			fprintf(fp,"%c",0xC0);
			fprintf(fp,"%c",0x45);
			fprintf(fp,"%c",0xC0);
			fprintf(fp,"%c",0x4D);

			fseek(fp,0xB454,SEEK_SET);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0xB9);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x02);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x68);
		} else {
			if(0x1C0000>romsize-1){
				MessageBox(NULL,"Rom is too small, expand rom to save.","Error",MB_OK);
				fclose(fp);
				return;
			}
			fseek(fp,0xBB83,SEEK_SET);
			fprintf(fp,"%c",0x43);
			fprintf(fp,"%c",0xC0);
			fprintf(fp,"%c",0x52);
			fprintf(fp,"%c",0xC0);
			fprintf(fp,"%c",0x49);
			fprintf(fp,"%c",0xC0);
			fprintf(fp,"%c",0x54);

			fseek(fp,0xBB97,SEEK_SET);
			fprintf(fp,"%c",0x20);
			fprintf(fp,"%c",0xC0);
			fprintf(fp,"%c",0x20);
			fprintf(fp,"%c",0xC0);
			fprintf(fp,"%c",0x20);
			fprintf(fp,"%c",0xC0);
			fprintf(fp,"%c",0x20);
			fprintf(fp,"%c",0xC0);
			fprintf(fp,"%c",0x20);

			fseek(fp,0xBBA9,SEEK_SET);
			fprintf(fp,"%c",0x20);
			fprintf(fp,"%c",0xC0);
			fprintf(fp,"%c",0x20);
			fprintf(fp,"%c",0xC0);
			fprintf(fp,"%c",0x20);
			fprintf(fp,"%c",0xC0);
			fprintf(fp,"%c",0x20);

			fseek(fp,0xB454,SEEK_SET);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0xB9);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x1C);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x00);

			fseek(fp,0x1C0000,SEEK_SET);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0xB9);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x02);
			fprintf(fp,"%c",0x23);
			fprintf(fp,"%c",0x4C);

			fprintf(fp,"%c",0x43);
			fprintf(fp,"%c",0xF8);
			fprintf(fp,"%c",0xB9);
			fprintf(fp,"%c",0xE4);
			fprintf(fp,"%c",0x7E);
			fprintf(fp,"%c",0x02);
			fprintf(fp,"%c",0x30);
			fprintf(fp,"%c",0x01);
			fprintf(fp,"%c",0x48);
			fprintf(fp,"%c",0xC0);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0xB9);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0xB0);
			fprintf(fp,"%c",0x42);
			fprintf(fp,"%c",0x30);
			fprintf(fp,"%c",0x38);
			fprintf(fp,"%c",0xB7);
			fprintf(fp,"%c",0xC4);


			//level
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0xB9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x02);
			fprintf(fp, "%c", 0x25);
			fprintf(fp, "%c", 0xB0);

			fprintf(fp, "%c", 0x4A);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x6C);
			fprintf(fp, "%c", 0x1A);

			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0xB9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x02);
			fprintf(fp, "%c", 0x1F);
			fprintf(fp, "%c", 0xF0);
			fprintf(fp, "%c", 0x10);
			fprintf(fp, "%c", 0x29);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x03);
			fprintf(fp, "%c", 0x48);
			fprintf(fp, "%c", 0x80);
			fprintf(fp, "%c", 0x48);
			fprintf(fp, "%c", 0xC0);

			fprintf(fp, "%c", 0x7E);
			fprintf(fp, "%c", 0x03);

			fprintf(fp, "%c", 0x43);
			fprintf(fp, "%c", 0xF8);
			fprintf(fp, "%c", 0xB8);
			if(RemoveMarks)fprintf(fp, "%c", 0x70);
			else fprintf(fp, "%c", 0x6C);

			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0xB9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0xB0);
			fprintf(fp, "%c", 0x42);
			fprintf(fp, "%c", 0x30);
			fprintf(fp, "%c", 0x38);
			fprintf(fp, "%c", 0xB7);
			fprintf(fp, "%c", 0xC4);


			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0xB9);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x02);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x68);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0x75);
		}

		if(RemoveCaps){
			for(int i=0;i<11;i++){
				fseek(fp,StatCapOffsets[i],SEEK_SET);
				fprintf(fp,"%c",0x0C);
				fprintf(fp,"%c",0x41);
				fprintf(fp,"%c",0x00);
				fprintf(fp,"%c",0x7F);
				fseek(fp,2,SEEK_CUR);
				fprintf(fp,"%c",0x32);
				fprintf(fp,"%c",0x3C);
				fprintf(fp,"%c",0x00);
				fprintf(fp,"%c",0x7F);
			}

			fseek(fp,0x22BD9,SEEK_SET);
			fprintf(fp,"%c",0x7E);//makes 127 infinite mp
			fseek(fp,0x24805,SEEK_SET);
			fprintf(fp,"%c",0x7F);
		} else {
			for(int i=0;i<11;i++){
				fseek(fp,StatCapOffsets[i],SEEK_SET);
				fprintf(fp,"%c",0x0C);
				fprintf(fp,"%c",0x41);
				fprintf(fp,"%c",0x00);
				fprintf(fp,"%c",0x63);
				fseek(fp,2,SEEK_CUR);
				fprintf(fp,"%c",0x32);
				fprintf(fp,"%c",0x3C);
				fprintf(fp,"%c",0x00);
				fprintf(fp,"%c",0x63);
			}

			fseek(fp,0x22BD9,SEEK_SET);
			fprintf(fp,"%c",0x63);
			fseek(fp,0x24805,SEEK_SET);
			fprintf(fp,"%c",0x63);
		}

		if(LevelLimit>99){
			fseek(fp,StatCapOffsets[11],SEEK_SET);
			fprintf(fp,"%c",0x0C);
			fprintf(fp,"%c",0x41);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",LevelLimit);
			fseek(fp,2,SEEK_CUR);
			fprintf(fp,"%c",0x32);
			fprintf(fp,"%c",0x3C);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",LevelLimit);
			fseek(fp,0xD0D1,SEEK_SET);
			fprintf(fp,"%c",0x03);
			fseek(fp,0xEFE7,SEEK_SET);
			fprintf(fp,"%c",0x08);
			fseek(fp,0xF055,SEEK_SET);
			fprintf(fp,"%c",0x03);
		} else {
			fseek(fp,StatCapOffsets[11],SEEK_SET);
			fprintf(fp,"%c",0x0C);
			fprintf(fp,"%c",0x41);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",LevelLimit);
			fseek(fp,2,SEEK_CUR);
			fprintf(fp,"%c",0x32);
			fprintf(fp,"%c",0x3C);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",LevelLimit);
			fseek(fp,0xD0D1,SEEK_SET);
			fprintf(fp,"%c",0x02);
			fseek(fp,0xEFE7,SEEK_SET);
			fprintf(fp,"%c",0x0A);
			fseek(fp,0xF055,SEEK_SET);
			fprintf(fp,"%c",0x02);
		}

		
		if (NumClasses == 64) {
			fseek(fp, 0x1FFD17, SEEK_SET);
			fprintf(fp, "%c", LevelLimit);
		} else {
			fseek(fp, 0x22C45, SEEK_SET);
			fprintf(fp, "%c", LevelLimit);
		}

		fseek(fp,0x22C37,SEEK_SET);
		fprintf(fp,"%c",UnLevelLimit);
	
		if(MultiAttacks){
			fseek(fp,0x2199E,SEEK_SET);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0xB9);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x1A);
			fprintf(fp,"%c",0xA0);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0x71);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0x71);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0x71);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0x71);
			fseek(fp,0x1AA000,SEEK_SET);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0xB9);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x02);
			fprintf(fp,"%c",0x12);
			fprintf(fp,"%c",0xA6);
			fprintf(fp,"%c",0xBE);
			fprintf(fp,"%c",0x41);
			fprintf(fp,"%c",0x64);
			fprintf(fp,"%c",0x08);
			fprintf(fp,"%c",0x52);
			fprintf(fp,"%c",0x42);
			fprintf(fp,"%c",0x04);
			fprintf(fp,"%c",0x41);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",MultiFalloff);
			fprintf(fp,"%c",0x60);
			fprintf(fp,"%c",0xEE);
			fprintf(fp,"%c",0x31);
			fprintf(fp,"%c",0xC2);
			fprintf(fp,"%c",0xCB);
			fprintf(fp,"%c",0x5C);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0x75);
		} else {
			fseek(fp,0x2199E,SEEK_SET);
			fprintf(fp,"%c",0x61);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0xF9);
			fprintf(fp,"%c",0x06);
			fprintf(fp,"%c",0xBE);
			fprintf(fp,"%c",0x41);
			fprintf(fp,"%c",0x64);
			fprintf(fp,"%c",0x02);
			fprintf(fp,"%c",0x74);
			fprintf(fp,"%c",0x02);
			fprintf(fp,"%c",0x31);
			fprintf(fp,"%c",0xC2);
			fprintf(fp,"%c",0xCB);
			fprintf(fp,"%c",0x5C);
		}
		
		if(FixLE){
			if(0x1C3000>romsize-1){
				MessageBox(NULL,"Rom is too small, expand rom to apply changes.","Error",MB_OK);
				fclose(fp);
				return;
			}
			fseek(fp,0x2110A,SEEK_SET);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0xF9);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x1C);
			fprintf(fp,"%c",0x30);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0x71);

			fseek(fp,0x1C3000,SEEK_SET);
			fprintf(fp,"%c",0x96);
			fprintf(fp,"%c",0x41);
			fprintf(fp,"%c",0x12);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x30);
			fprintf(fp,"%c",0x1F);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0xB9);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x02);
			fprintf(fp,"%c",0x11);
			fprintf(fp,"%c",0xA8);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0xF9);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x02);
			fprintf(fp,"%c",0x11);
			fprintf(fp,"%c",0x12);
		} else {
			fseek(fp,0x2110A,SEEK_SET);
			fprintf(fp,"%c",0x96);
			fprintf(fp,"%c",0x41);
			fprintf(fp,"%c",0x30);
			fprintf(fp,"%c",0x1F);
			fprintf(fp,"%c",0x61);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x98);
		}

		if(ItemPassing){
			if(0x1C3100>romsize-1){
				MessageBox(NULL,"Rom is too small, expand rom to save changes.","Error",MB_OK);
				fclose(fp);
				return;
			}
			fseek(fp, 0x13908, SEEK_SET);
			fprintf(fp,"%c",0x52);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0xB9);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x1C);
			fprintf(fp,"%c",0x31);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x66);
			fprintf(fp,"%c",0x46);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0x71);

			fseek(fp,0x1C3100,SEEK_SET);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0xB9);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x02);
			fprintf(fp,"%c",0x21);
			fprintf(fp,"%c",0xD4);
			fprintf(fp,"%c",0x67);
			fprintf(fp,"%c",0x3C);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0xB9);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x02);

			fprintf(fp,"%c",0x02);
			fprintf(fp,"%c",0x4C);
			fprintf(fp,"%c",0x65);
			fprintf(fp,"%c",0x34);
			fprintf(fp,"%c",0x48);
			fprintf(fp,"%c",0xA7);
			fprintf(fp,"%c",0x80);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0x40);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x0D);

			fprintf(fp,"%c",0x30);
			fprintf(fp,"%c",0x3C);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x48);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0x48);
			fprintf(fp,"%c",0x4C);
			fprintf(fp,"%c",0x9F);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x01);
			fprintf(fp,"%c",0x31);
			fprintf(fp,"%c",0xC0);

			fprintf(fp,"%c",0xF8);
			fprintf(fp,"%c",0x44);
			fprintf(fp,"%c",0x30);
			fprintf(fp,"%c",0x3C);
			fprintf(fp, "%c", (SpecialMessages[1] & 0xFF00) / 0x100);
			fprintf(fp, "%c", (SpecialMessages[1] & 0x00FF));
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0x48);
			fprintf(fp,"%c",0x48);
			fprintf(fp,"%c",0xA7);
			fprintf(fp,"%c",0x40);
			fprintf(fp,"%c",0x00);

			fprintf(fp,"%c",0x30);
			fprintf(fp,"%c",0x3C);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0xFB);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0xB9);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x02);
			fprintf(fp,"%c",0xE4);
			fprintf(fp,"%c",0x4C);
			fprintf(fp,"%c",0x9F);

			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x02);
			fprintf(fp,"%c",0x0C);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x1F);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0x75);
			fprintf(fp,"%c",0x52);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x0C);
			fprintf(fp,"%c",0x00);

			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x1F);
			fprintf(fp,"%c",0x66);
			fprintf(fp,"%c",0xB4);
			fprintf(fp,"%c",0x30);
			fprintf(fp,"%c",0x3C);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x48);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0x48);
			fprintf(fp,"%c",0x30);
			fprintf(fp,"%c",0x3C);

			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x49);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0x48);

			fprintf(fp,"%c",0x0C);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x49);

			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0x75);

		} else {
			fseek(fp,0x13908,SEEK_SET);
			fprintf(fp,"%c",0x30);
			fprintf(fp,"%c",0x3C);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x48);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0x48);
			fprintf(fp,"%c",0x30);
			fprintf(fp,"%c",0x3C);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x49);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0x48);
		}


		if (ItemPassingBattle) {
			if (0x1C3100>romsize - 1) {
				MessageBox(NULL, "Rom is too small, expand rom to save changes.", "Error", MB_OK);
				fclose(fp);
				return;
			}
			fseek(fp, 0x77FE, SEEK_SET);
			fprintf(fp, "%c", 0x65);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x72);
			fprintf(fp, "%c", 0x4C);
			fprintf(fp, "%c", 0x9F);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x02);

			fseek(fp, 0x7872, SEEK_SET);
			fprintf(fp, "%c", 0x52);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0xB9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x1C);
			fprintf(fp, "%c", 0x31);
			fprintf(fp, "%c", 0x80);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0x71);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0x71);
			fprintf(fp, "%c", 0x4C);
			fprintf(fp, "%c", 0x9F);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x02);
			fprintf(fp, "%c", 0x66);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0xFF);
			fprintf(fp, "%c", 0x96);

			fseek(fp, 0x1C3180, SEEK_SET);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0xB9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x02);
			fprintf(fp, "%c", 0x21);
			fprintf(fp, "%c", 0xD4);
			fprintf(fp, "%c", 0x67);
			fprintf(fp, "%c", 0x3C);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0xB9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x02);

			fprintf(fp, "%c", 0x02);
			fprintf(fp, "%c", 0x5C);
			fprintf(fp, "%c", 0x65);
			fprintf(fp, "%c", 0x34);
			fprintf(fp, "%c", 0x48);
			fprintf(fp, "%c", 0xA7);
			fprintf(fp, "%c", 0x80);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0x40);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x0D);

			fprintf(fp, "%c", 0x30);
			fprintf(fp, "%c", 0x3C);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x48);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0x48);
			fprintf(fp, "%c", 0x4C);
			fprintf(fp, "%c", 0x9F);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x01);
			fprintf(fp, "%c", 0x31);
			fprintf(fp, "%c", 0xC0);

			fprintf(fp, "%c", 0xF8);
			fprintf(fp, "%c", 0x44);
			fprintf(fp, "%c", 0x30);
			fprintf(fp, "%c", 0x3C);
			fprintf(fp, "%c", (SpecialMessages[1] & 0xFF00) / 0x100);
			fprintf(fp, "%c", (SpecialMessages[1] & 0x00FF));
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0x48);
			fprintf(fp, "%c", 0x48);
			fprintf(fp, "%c", 0xA7);
			fprintf(fp, "%c", 0x40);
			fprintf(fp, "%c", 0x00);

			fprintf(fp, "%c", 0x30);
			fprintf(fp, "%c", 0x3C);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0xFB);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0xB9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x02);
			fprintf(fp, "%c", 0xE4);
			fprintf(fp, "%c", 0x4C);
			fprintf(fp, "%c", 0x9F);

			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x02);
			fprintf(fp, "%c", 0x0C);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x1F);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0x75);
			fprintf(fp, "%c", 0x52);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x0C);
			fprintf(fp, "%c", 0x00);

			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x1F);
			fprintf(fp, "%c", 0x66);
			fprintf(fp, "%c", 0xB4);
			fprintf(fp, "%c", 0x30);
			fprintf(fp, "%c", 0x3C);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x48);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0x48);
			fprintf(fp, "%c", 0x30);
			fprintf(fp, "%c", 0x3C);

			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x49);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0x48);

			fprintf(fp, "%c", 0x0C);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x49);

			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0x75);

		} else {
			fseek(fp, 0x77FE, SEEK_SET);
			fprintf(fp, "%c", 0x4C);
			fprintf(fp, "%c", 0x9F);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x02);
			fprintf(fp, "%c", 0x65);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x6E);

			fseek(fp, 0x7872, SEEK_SET);
			fprintf(fp, "%c", 0x48);
			fprintf(fp, "%c", 0xA7);
			fprintf(fp, "%c", 0x60);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x30);
			fprintf(fp, "%c", 0x3C);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x48);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0x48);
			fprintf(fp, "%c", 0x30);
			fprintf(fp, "%c", 0x3C);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x49);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0x48);
			fprintf(fp, "%c", 0x4C);
			fprintf(fp, "%c", 0x9F);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x06);
		}


		if(EXPOverflow){
			if(0x1C3200>romsize-1){
				MessageBox(NULL,"Rom is too small, expand rom to save changes.","Error",MB_OK);
				fclose(fp);
				return;
			}
			fseek(fp,0x22C16,SEEK_SET);
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
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0x71);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0x71);

			fseek(fp,0x124DE3,SEEK_SET);
			fprintf(fp,"%c",0x64);
			fprintf(fp,"%c",0x65);

			fseek(fp,0x24726,SEEK_SET);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x1C);
			fprintf(fp,"%c",0x32);
			fprintf(fp,"%c",0x00);

			fseek(fp,0x1C3200,SEEK_SET);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0xB9);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x02);
			fprintf(fp,"%c",0x24);
			fprintf(fp,"%c",0x2C);

			fprintf(fp,"%c",0x4A);
			fprintf(fp,"%c",0x01);
			fprintf(fp,"%c",0x67);
			fprintf(fp,"%c",0x04);

			fprintf(fp,"%c",0x04);
			fprintf(fp,"%c",0x01);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x64);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0xB9);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x02);
			fprintf(fp,"%c",0x01);
			fprintf(fp,"%c",0x44);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0x75);

		} else {
			fseek(fp,0x22C16,SEEK_SET);
			fprintf(fp,"%c",0x4A);
			fprintf(fp,"%c",0x41);
			fprintf(fp,"%c",0x6C);
			fprintf(fp,"%c",0x04);
			fprintf(fp,"%c",0x42);
			fprintf(fp,"%c",0x41);
			fprintf(fp,"%c",0x60);
			fprintf(fp,"%c",0x06);
			fprintf(fp,"%c",0xB2);
			fprintf(fp,"%c",0x43);
			fprintf(fp,"%c",0x6F);
			fprintf(fp,"%c",0x02);
			fprintf(fp,"%c",0x32);
			fprintf(fp,"%c",0x03);

			fseek(fp,0x124DE3,SEEK_SET);
			fprintf(fp,"%c",0x64);
			fprintf(fp,"%c",0x6D);

			fseek(fp,0x24726,SEEK_SET);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x02);
			fprintf(fp,"%c",0x01);
			fprintf(fp,"%c",0x44);
		}

		if(AddArmor){
			if(0x1C3480>romsize-1){
				MessageBox(NULL,"Rom is too small, expand rom to save changes.","Error",MB_OK);
				fclose(fp);
				return;
			}
			fseek(fp,0x5ECB,SEEK_SET);
			fprintf(fp,"%c",0x02);

			fseek(fp,0xA539,SEEK_SET);
			fprintf(fp,"%c",0x02);

			fseek(fp,0x72F4,SEEK_SET);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0xB9);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x1C);
			fprintf(fp,"%c",0x33);
			fprintf(fp,"%c",0x12);
			fprintf(fp,"%c",0x43);
			fprintf(fp,"%c",0xF9);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0xFF);
			fprintf(fp,"%c",0xB7);
			fprintf(fp,"%c",0xF4);
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

			fseek(fp,0xDCA4,SEEK_SET);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0xB9);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x1C);
			fprintf(fp,"%c",0x33);
			fprintf(fp,"%c",0x12);
			fprintf(fp,"%c",0x43);
			fprintf(fp,"%c",0xF9);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0xFF);
			fprintf(fp,"%c",0xB8);
			fprintf(fp,"%c",0x2E);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0x71);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0x71);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0x71);

			int i;

			for(i=0;i<3;i++){
				fseek(fp,ArmorOffsets[i],SEEK_SET);
				fprintf(fp,"%c",0x4E);
				fprintf(fp,"%c",0xB9);
				fprintf(fp,"%c",0x00);
				fprintf(fp,"%c",0x1C);
				fprintf(fp,"%c",0x33);
				fprintf(fp,"%c",0x60);
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
				fprintf(fp,"%c",0x4E);
				fprintf(fp,"%c",0x71);
			}
			for(i=3;i<6;i++){
				fseek(fp,ArmorOffsets[i],SEEK_SET);
				fprintf(fp,"%c",0x4E);
				fprintf(fp,"%c",0xB9);
				fprintf(fp,"%c",0x00);
				fprintf(fp,"%c",0x1C);
				fprintf(fp,"%c",0x33);
				fprintf(fp,"%c",0x60);
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
			}

			fseek(fp,0xA5D6,SEEK_SET);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0xF9);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x1C);
			fprintf(fp,"%c",0x33);
			fprintf(fp,"%c",0xB0);

			fseek(fp,0x5F42,SEEK_SET);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0xF9);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x1C);
			fprintf(fp,"%c",0x34);
			fprintf(fp,"%c",0x80);

			fseek(fp,0x1C3300,SEEK_SET);
			fprintf(fp,"WEAPONRING  ARMOR ");

			fseek(fp,0x1C3312,SEEK_SET);
			fprintf(fp,"%c",0x41);
			fprintf(fp,"%c",0xF9);
			fprintf(fp,"%c",0x0);
			fprintf(fp,"%c",0x1C);
			fprintf(fp,"%c",0x33);
			fprintf(fp,"%c",0x0);
			fprintf(fp,"%c",0x8);
			fprintf(fp,"%c",0x39);
			fprintf(fp,"%c",0x0);
			fprintf(fp,"%c",0x0);
			fprintf(fp,"%c",0x0);
			fprintf(fp,"%c",0xFF);
			fprintf(fp,"%c",0xB5);
			fprintf(fp,"%c",0x26);
			fprintf(fp,"%c",0x67);
			fprintf(fp,"%c",0x2);
			fprintf(fp,"%c",0x5C);
			fprintf(fp,"%c",0x48);
			fprintf(fp,"%c",0x8);
			fprintf(fp,"%c",0x39);
			fprintf(fp,"%c",0x0);
			fprintf(fp,"%c",0x1);
			fprintf(fp,"%c",0x0);
			fprintf(fp,"%c",0xFF);
			fprintf(fp,"%c",0xB5);
			fprintf(fp,"%c",0x26);
			fprintf(fp,"%c",0x67);
			fprintf(fp,"%c",0x4);
			fprintf(fp,"%c",0x5C);
			fprintf(fp,"%c",0x48);
			fprintf(fp,"%c",0x5C);
			fprintf(fp,"%c",0x48);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0x75);

			fseek(fp,0x1C3360,SEEK_SET);
			fprintf(fp,"%c",0x8);
			fprintf(fp,"%c",0x39);
			fprintf(fp,"%c",0x0);
			fprintf(fp,"%c",0x0);
			fprintf(fp,"%c",0x0);
			fprintf(fp,"%c",0xFF);
			fprintf(fp,"%c",0xB5);
			fprintf(fp,"%c",0x26);
			fprintf(fp,"%c",0x67);
			fprintf(fp,"%c",0x6);
			fprintf(fp,"%c",0x32);
			fprintf(fp,"%c",0x3C);
			fprintf(fp,"%c",0x2);
			fprintf(fp,"%c",0x0);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0x75);
			fprintf(fp,"%c",0x8);
			fprintf(fp,"%c",0x39);
			fprintf(fp,"%c",0x0);
			fprintf(fp,"%c",0x1);
			fprintf(fp,"%c",0x0);
			fprintf(fp,"%c",0xFF);
			fprintf(fp,"%c",0xB5);
			fprintf(fp,"%c",0x26);
			fprintf(fp,"%c",0x67);
			fprintf(fp,"%c",0x6);
			fprintf(fp,"%c",0x32);
			fprintf(fp,"%c",0x3C);
			fprintf(fp,"%c",0x0);
			fprintf(fp,"%c",0x2);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0x75);
			fprintf(fp,"%c",0x32);
			fprintf(fp,"%c",0x3C);
			fprintf(fp,"%c",0x1);
			fprintf(fp,"%c",0x0);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0x75);

			fseek(fp,0x1C33B0,SEEK_SET);
			fprintf(fp,"%c",0x32);
			fprintf(fp,"%c",0x3C);
			fprintf(fp,"%c",0x0);
			fprintf(fp,"%c",0x2);
			fprintf(fp,"%c",0x42);
			fprintf(fp,"%c",0x40);
			fprintf(fp,"%c",0x10);
			fprintf(fp,"%c",0x38);
			fprintf(fp,"%c",0xB4);
			fprintf(fp,"%c",0xC5);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0xB9);
			fprintf(fp,"%c",0x0);
			fprintf(fp,"%c",0x2);
			fprintf(fp,"%c",0x2);
			fprintf(fp,"%c",0x80);
			fprintf(fp,"%c",0x67);
			fprintf(fp,"%c",0x0);
			fprintf(fp,"%c",0x0);
			fprintf(fp,"%c",0x46);
			fprintf(fp,"%c",0x11);
			fprintf(fp,"%c",0xFC);
			fprintf(fp,"%c",0x0);
			fprintf(fp,"%c",0x2);
			fprintf(fp,"%c",0xB5);
			fprintf(fp,"%c",0x26);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0xB9);
			fprintf(fp,"%c",0x0);
			fprintf(fp,"%c",0x0);
			fprintf(fp,"%c",0xD7);
			fprintf(fp,"%c",0x74);
			fprintf(fp,"%c",0xC);
			fprintf(fp,"%c",0x40);
			fprintf(fp,"%c",0xFF);
			fprintf(fp,"%c",0xFF);
			fprintf(fp,"%c",0x66);
			fprintf(fp,"%c",0x32);
			fprintf(fp,"%c",0x42);
			fprintf(fp,"%c",0x40);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0xB9);
			fprintf(fp,"%c",0x0);
			fprintf(fp,"%c",0x0);
			fprintf(fp,"%c",0xAB);
			fprintf(fp,"%c",0x9C);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0xB9);
			fprintf(fp,"%c",0x0);
			fprintf(fp,"%c",0x0);
			fprintf(fp,"%c",0x2);
			fprintf(fp,"%c",0x40);
			fprintf(fp,"%c",0x32);
			fprintf(fp,"%c",0x3C);
			fprintf(fp,"%c",0x2);
			fprintf(fp,"%c",0x0);
			fprintf(fp,"%c",0x42);
			fprintf(fp,"%c",0x40);
			fprintf(fp,"%c",0x10);
			fprintf(fp,"%c",0x38);
			fprintf(fp,"%c",0xB4);
			fprintf(fp,"%c",0xC5);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0xB9);
			fprintf(fp,"%c",0x0);
			fprintf(fp,"%c",0x2);
			fprintf(fp,"%c",0x2);
			fprintf(fp,"%c",0x80);
			fprintf(fp,"%c",0x67);
			fprintf(fp,"%c",0x6);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0xF9);
			fprintf(fp,"%c",0x0);
			fprintf(fp,"%c",0x0);
			fprintf(fp,"%c",0xA5);
			fprintf(fp,"%c",0x8C);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0x71);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0x71);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0x71);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0xF9);
			fprintf(fp,"%c",0x0);
			fprintf(fp,"%c",0x0);
			fprintf(fp,"%c",0xA5);
			fprintf(fp,"%c",0xB0);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0xB9);
			fprintf(fp,"%c",0x0);
			fprintf(fp,"%c",0x0);
			fprintf(fp,"%c",0xD7);
			fprintf(fp,"%c",0x5A);
			fprintf(fp,"%c",0x42);
			fprintf(fp,"%c",0x40);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0xB9);
			fprintf(fp,"%c",0x0);
			fprintf(fp,"%c",0x0);
			fprintf(fp,"%c",0xAB);
			fprintf(fp,"%c",0x9C);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0xB9);
			fprintf(fp,"%c",0x0);
			fprintf(fp,"%c",0x0);
			fprintf(fp,"%c",0x2);
			fprintf(fp,"%c",0x40);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0xF9);
			fprintf(fp,"%c",0x0);
			fprintf(fp,"%c",0x0);
			fprintf(fp,"%c",0xA1);
			fprintf(fp,"%c",0x32);

			fseek(fp,0x1C3480,SEEK_SET);
			fprintf(fp,"%c",0x32);
			fprintf(fp,"%c",0x3C);
			fprintf(fp,"%c",0x0);
			fprintf(fp,"%c",0x2);
			fprintf(fp,"%c",0x30);
			fprintf(fp,"%c",0x38);
			fprintf(fp,"%c",0xB7);
			fprintf(fp,"%c",0xC4);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0xB9);
			fprintf(fp,"%c",0x0);
			fprintf(fp,"%c",0x2);
			fprintf(fp,"%c",0x2);
			fprintf(fp,"%c",0x94);
			fprintf(fp,"%c",0x67);
			fprintf(fp,"%c",0x0);
			fprintf(fp,"%c",0x0);
			fprintf(fp,"%c",0x36);
			fprintf(fp,"%c",0x11);
			fprintf(fp,"%c",0xFC);
			fprintf(fp,"%c",0x0);
			fprintf(fp,"%c",0x2);
			fprintf(fp,"%c",0xB5);
			fprintf(fp,"%c",0x26);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0xB9);
			fprintf(fp,"%c",0x0);
			fprintf(fp,"%c",0x0);
			fprintf(fp,"%c",0x6C);
			fprintf(fp,"%c",0xB6);
			fprintf(fp,"%c",0x4A);
			fprintf(fp,"%c",0x40);
			fprintf(fp,"%c",0x6A);
			fprintf(fp,"%c",0x24);
			fprintf(fp,"%c",0x32);
			fprintf(fp,"%c",0x3C);
			fprintf(fp,"%c",0x2);
			fprintf(fp,"%c",0x0);
			fprintf(fp,"%c",0x30);
			fprintf(fp,"%c",0x38);
			fprintf(fp,"%c",0xB7);
			fprintf(fp,"%c",0xC4);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0xB9);
			fprintf(fp,"%c",0x0);
			fprintf(fp,"%c",0x2);
			fprintf(fp,"%c",0x2);
			fprintf(fp,"%c",0x94);
			fprintf(fp,"%c",0x67);
			fprintf(fp,"%c",0x6);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0xF9);
			fprintf(fp,"%c",0x0);
			fprintf(fp,"%c",0x0);
			fprintf(fp,"%c",0x5F);
			fprintf(fp,"%c",0x8);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0x71);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0x71);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0x71);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0x71);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0xF9);
			fprintf(fp,"%c",0x0);
			fprintf(fp,"%c",0x0);
			fprintf(fp,"%c",0x5F);
			fprintf(fp,"%c",0x28);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0xB9);
			fprintf(fp,"%c",0x0);
			fprintf(fp,"%c",0x0);
			fprintf(fp,"%c",0x6C);
			fprintf(fp,"%c",0x6E);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0x47);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0x46);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0x75);
		} else {
			fseek(fp,0x5ECB,SEEK_SET);
			fprintf(fp,"%c",0x00);

			fseek(fp,0xA539,SEEK_SET);
			fprintf(fp,"%c",0x00);

			fseek(fp,0x72F4,SEEK_SET);
			fprintf(fp,"%c",0x41);
			fprintf(fp,"%c",0xFA);
			fprintf(fp,"%c",0x02);
			fprintf(fp,"%c",0x9E);
			fprintf(fp,"%c",0x43);
			fprintf(fp,"%c",0xF9);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0xFF);
			fprintf(fp,"%c",0xB7);
			fprintf(fp,"%c",0xF4);
			fprintf(fp,"%c",0x08);
			fprintf(fp,"%c",0x39);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0xFF);
			fprintf(fp,"%c",0xB5);
			fprintf(fp,"%c",0x23);
			fprintf(fp,"%c",0x67);
			fprintf(fp,"%c",0x02);
			fprintf(fp,"%c",0x5C);
			fprintf(fp,"%c",0x48);

			fseek(fp,0xDCA4,SEEK_SET);
			fprintf(fp,"%c",0x41);
			fprintf(fp,"%c",0xFA);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x6A);
			fprintf(fp,"%c",0x43);
			fprintf(fp,"%c",0xF8);
			fprintf(fp,"%c",0xB8);
			fprintf(fp,"%c",0x2E);
			fprintf(fp,"%c",0x08);
			fprintf(fp,"%c",0x38);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0xB5);
			fprintf(fp,"%c",0x26);
			fprintf(fp,"%c",0x67);
			fprintf(fp,"%c",0x02);
			fprintf(fp,"%c",0x5C);
			fprintf(fp,"%c",0x48);

			int i;

			for(i=0;i<3;i++){
				fseek(fp,ArmorOffsets[i],SEEK_SET);
				fprintf(fp,"%c",0x4A);
				fprintf(fp,"%c",0x39);
				fprintf(fp,"%c",0x00);
				fprintf(fp,"%c",0xFF);
				fprintf(fp,"%c",0xB5);
				fprintf(fp,"%c",0x26);
				fprintf(fp,"%c",0x66);
				fprintf(fp,"%c",0x06);
				fprintf(fp,"%c",0x32);
				fprintf(fp,"%c",0x3C);
				fprintf(fp,"%c",0x01);
				fprintf(fp,"%c",0x00);
				fprintf(fp,"%c",0x60);
				fprintf(fp,"%c",0x04);
				fprintf(fp,"%c",0x32);
				fprintf(fp,"%c",0x3C);
				fprintf(fp,"%c",0x02);
				fprintf(fp,"%c",0x00);
			}
			for(i=3;i<6;i++){
				fseek(fp,ArmorOffsets[i],SEEK_SET);
				fprintf(fp,"%c",0x4A);
				fprintf(fp,"%c",0x38);
				fprintf(fp,"%c",0xB5);
				fprintf(fp,"%c",0x26);
				fprintf(fp,"%c",0x66);
				fprintf(fp,"%c",0x06);
				fprintf(fp,"%c",0x32);
				fprintf(fp,"%c",0x3C);
				fprintf(fp,"%c",0x01);
				fprintf(fp,"%c",0x00);
				fprintf(fp,"%c",0x60);
				fprintf(fp,"%c",0x04);
				fprintf(fp,"%c",0x32);
				fprintf(fp,"%c",0x3C);
				fprintf(fp,"%c",0x02);
				fprintf(fp,"%c",0x00);
			}

			fseek(fp,0xA5D6,SEEK_SET);
			fprintf(fp,"%c",0x61);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x31);
			fprintf(fp,"%c",0x82);
			fprintf(fp,"%c",0x42);
			fprintf(fp,"%c",0x40);

			fseek(fp,0x5F42,SEEK_SET);
			fprintf(fp,"%c",0x61);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x0D);
			fprintf(fp,"%c",0x2A);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0x47);
		}

		fclose(fp);
		MessageBox(NULL,"Mechanics Saved","Note",MB_OK);
	}
}

void ExportMech(char*path){
	FILE * fp = fopen(path,"wb");

	fprintf(fp,"%c",(PoisonOffset&0xFF000000)/0x1000000);
	fprintf(fp,"%c",(PoisonOffset&0x00FF0000)/0x10000);
	fprintf(fp,"%c",(PoisonOffset&0x0000FF00)/0x100);
	fprintf(fp,"%c",(PoisonOffset&0x000000FF));

	fprintf(fp,"%c",Poison);

	fclose(fp);
	MessageBox(NULL,"Mechanics Exported","Note",MB_OK);
}

void MechExport(){
	OPENFILENAME openFileName;
	char path[256];
	path[0] = '\0';  
	memset( &openFileName, 0, sizeof(openFileName) );
	openFileName.lStructSize = sizeof(openFileName);
	openFileName.hwndOwner = NULL;
	openFileName.hInstance = NULL;
	openFileName.lpstrFilter = "Shining Force Mechanics(*.sfme)\0*.sfme\0";
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
	openFileName.lpstrDefExt = "sfme";
	openFileName.lCustData = NULL;
	openFileName.lpfnHook = NULL;
	openFileName.lpTemplateName = NULL;

	if(GetSaveFileName(&openFileName)!=0){
		ExportMech(path);
	}
}
 