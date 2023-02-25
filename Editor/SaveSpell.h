void SaveSpell(){
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


		if(SpellNameOffset>romsize-1||SpellOffset>romsize-1||SpellImagesOffset>romsize-1){
			MessageBox(NULL,"Rom is too small, expand rom or use a smaller offset.","Error",MB_OK);
			fclose(fp);
			return;
		}

		fseek(fp,132040,SEEK_SET);
		fprintf(fp,"%c",(SpellNameOffset&0xFF000000)/0x1000000);
		fprintf(fp,"%c",(SpellNameOffset&0x00FF0000)/0x10000);
		fprintf(fp,"%c",(SpellNameOffset&0x0000FF00)/0x100);
		fprintf(fp,"%c",(SpellNameOffset&0x000000FF));

		fseek(fp,SpellNameOffset,SEEK_SET);
		for(i=0; i<16+16*ExpandSpells; i++){
			fprintf(fp,"%c",strlen(SpellName[i]));
			for(int j=0; j<strlen(SpellName[i]); j++){
				fprintf(fp,"%c",SpellName[i][j]);
			}
		}

		fseek(fp,132044,SEEK_SET);
		fprintf(fp,"%c",(SpellOffset&0xFF000000)/0x1000000);
		fprintf(fp,"%c",(SpellOffset&0x00FF0000)/0x10000);
		fprintf(fp,"%c",(SpellOffset&0x0000FF00)/0x100);
		fprintf(fp,"%c",(SpellOffset&0x000000FF));

		fseek(fp,SpellOffset,SEEK_SET);

		for(i=0; i<16+16*ExpandSpells; i++){
			for(int j=0; j<16; j++){
				fprintf(fp,"%c",Spell[i][j]);
			}
		}

		fseek(fp,835616,SEEK_SET);
		fprintf(fp,"%c",(SpellImagesOffset&0xFF000000)/0x1000000);
		fprintf(fp,"%c",(SpellImagesOffset&0x00FF0000)/0x10000);
		fprintf(fp,"%c",(SpellImagesOffset&0x0000FF00)/0x100);
		fprintf(fp,"%c",(SpellImagesOffset&0x000000FF));
		if(NumItems==128){
			fseek(fp,0x1BD046,SEEK_SET);
			fprintf(fp,"%c",(SpellImagesOffset&0xFF000000)/0x1000000);
			fprintf(fp,"%c",(SpellImagesOffset&0x00FF0000)/0x10000);
			fprintf(fp,"%c",(SpellImagesOffset&0x0000FF00)/0x100);
			fprintf(fp,"%c",(SpellImagesOffset&0x000000FF));

			fseek(fp, 0x1BD056, SEEK_SET);
			if (SpellImagesOffset == 0x180E80) {
				fprintf(fp, "%c", 0x72);
				fprintf(fp, "%c", 0x7F);
			} else {
				fprintf(fp, "%c", 0x72);
				fprintf(fp, "%c", 0x4F);
			}
		}


		fseek(fp,SpellImagesOffset,SEEK_SET);

		for(i=0; i<16+16*ExpandSpells; i++){
			for(int c=0; c<6; c++){
				for(int j=0; j<32; j++){
					int k=j*2;
					r = SpellImages[i][c%2*8+(c-c%2)*64+k%8+(k-k%8)*2]*16+SpellImages[i][c%2*8+(c-c%2)*64+k%8+(k-k%8)*2+1];
					fprintf(fp,"%c",r);
				}
			}
		}

		if(ExpandSpells){
			SpellTargetOffset = 0x1C0100;
		}

		if(SpellTargetOffset>romsize-1){
			MessageBox(NULL,"Rom is too small, expand rom to save.","Error",MB_OK);
			fclose(fp);
			return;
		}


		fseek(fp,SpellTargetOffset,SEEK_SET);
		for(i=0; i<16+16*ExpandSpells; i++){
			fprintf(fp,"%c",(SpellTargeting[i]&0xFF00)/0x100);
			fprintf(fp,"%c",(SpellTargeting[i]&0xFF));
		}

		if(ExpandSpells){
			fseek(fp,0x2408A,SEEK_SET);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0xB9);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x1C);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0xE2);


			fseek(fp,0x1C00E2,SEEK_SET);
			fprintf(fp,"%c",0x41);
			fprintf(fp,"%c",0xF9);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x1C);
			fprintf(fp,"%c",0x01);
			fprintf(fp,"%c",0x00);

			fprintf(fp,"%c",0xD0);
			fprintf(fp,"%c",0xC1);
			fprintf(fp,"%c",0x32);
			fprintf(fp,"%c",0x10);
			fprintf(fp,"%c",0x41);
			fprintf(fp,"%c",0xF9);

			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x02);
			fprintf(fp,"%c",0x40);
			fprintf(fp,"%c",0x9C);
			fprintf(fp,"%c",0xD0);
			fprintf(fp,"%c",0xC1);

			fprintf(fp,"%c",0x12);
			fprintf(fp,"%c",0x38);
			fprintf(fp,"%c",0xCB);
			fprintf(fp,"%c",0x40);
			fprintf(fp,"%c",0x02);
			fprintf(fp,"%c",0x41);

			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x3F);
			fprintf(fp,"%c",0xD2);
			fprintf(fp,"%c",0x41);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0x75);
		} else {
			fseek(fp,0x2408A,SEEK_SET);
			fprintf(fp,"%c",0x41);
			fprintf(fp,"%c",0xFB);
			fprintf(fp,"%c",0x10);
			fprintf(fp,"%c",0x10);
			fprintf(fp,"%c",0x32);
			fprintf(fp,"%c",0x10);
		}

		fclose(fp);
		MessageBox(NULL,"Spells Saved","Note",MB_OK);
	}
}

void ExportSpell(char*path){
	unsigned char r;
	FILE * fp = fopen(path,"wb");
	int i;
		for(i=0; i<16; i++){
			fprintf(fp,"%c",strlen(SpellName[i]));
			for(int j=0; j<strlen(SpellName[i]); j++){
				fprintf(fp,"%c",SpellName[i][j]);
			}
		}
		for(i=0; i<16; i++){
			for(int j=0; j<16; j++){
				fprintf(fp,"%c",Spell[i][j]);
			}
		}
		for(i=0; i<16; i++){
			for(int c=0; c<6; c++){
				for(int j=0; j<32; j++){
					int k=j*2;
					r = SpellImages[i][c%2*8+(c-c%2)*64+k%8+(k-k%8)*2]*16+SpellImages[i][c%2*8+(c-c%2)*64+k%8+(k-k%8)*2+1];
					fprintf(fp,"%c",r);
				}
			}
		}
	fclose(fp);
	MessageBox(NULL,"Spells Exported","Note",MB_OK);
}

void SpellExport(){
	OPENFILENAME openFileName;
	char path[256];
	path[0] = '\0';  
	memset( &openFileName, 0, sizeof(openFileName) );
	openFileName.lStructSize = sizeof(openFileName);
	openFileName.hwndOwner = NULL;
	openFileName.hInstance = NULL;
	openFileName.lpstrFilter = "Shining Force Spells(*.sfs)\0*.sfs\0";
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
	openFileName.lpstrDefExt = "sfs";
	openFileName.lCustData = NULL;
	openFileName.lpfnHook = NULL;
	openFileName.lpTemplateName = NULL;

	if(GetSaveFileName(&openFileName)!=0){
		ExportSpell(path);
	}
}


void CopySelectedSpell() {
	unsigned int size[2] = { 16,24 };

	ToClipboard(SpellImages[select[mode]], size, IconPalette);
}