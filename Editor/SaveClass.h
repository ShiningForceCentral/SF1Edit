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

		if (romsize < 0x200000) {
			MessageBox(NULL, "Rom is too small, expand rom to save class changes.", "Error", MB_OK);
			fclose(fp);
			return;
		}

		if (NumMonsters == 146 || NumClasses == 64) {
			ClassOffset = 0x1E2000;
			ClassNamesOffset = 0x1DC000;
		}

		
		/* (Hardcoded) Fix Dark Dragon finisher check */
		fseek(fp, 0x214D4, SEEK_SET);
		fprintf(fp, "%c", 0x0C); // cmpi.b  #NumClasses + 59,d1
		fprintf(fp, "%c", 0x01);
		fprintf(fp, "%c", 0x00);
		fprintf(fp, "%c", NumClasses + 59);
		fseek(fp, 0x214DA, SEEK_SET);
		fprintf(fp, "%c", 0x0C); // cmpi.b  #NumClasses + 72,d1
		fprintf(fp, "%c", 0x01);
		fprintf(fp, "%c", 0x00);
		fprintf(fp, "%c", NumClasses + 72);

		/* Is initial promoted at levels table implemented? */
		fseek(fp, 0x21B30, SEEK_SET);
		fscanf(fp, "%c", &r);
		if (r != 0x4E) {
			/* CalculateInitialStatValue */
			fseek(fp, 0x24A10, SEEK_SET);
			fprintf(fp, "%c", 0x4E); // jsr     GetPromotedAtLevelIfRegularForceMember
			fprintf(fp, "%c", 0xB9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x1F);
			fprintf(fp, "%c", 0xFC);
			fprintf(fp, "%c", 0x60);
			fprintf(fp, "%c", 0x4A); // tst.b   d1
			fprintf(fp, "%c", 0x01);

			/* GetPromotedAtLevelIfRegularForceMember */
			fseek(fp, 0x1FFC60, SEEK_SET);
			fprintf(fp, "%c", 0x18); // move.b  (a0,d3.w),d4
			fprintf(fp, "%c", 0x30);
			fprintf(fp, "%c", 0x30);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x0C); // cmpi.b  #ALLY_MUSASHI,d0
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x1B);
			fprintf(fp, "%c", 0x65); // blo.s   loc_1FFC70
			fprintf(fp, "%c", 0x06);
			fprintf(fp, "%c", 0x0C); // cmpi.b  #ALLY_JOGURT,d0
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x1D);
			fprintf(fp, "%c", 0x63); // bls.s   loc_1FFC76
			fprintf(fp, "%c", 0x06);
			fprintf(fp, "%c", 0x4E); // jmp     GetPromotedAtLevel
			fprintf(fp, "%c", 0xF9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x02);
			fprintf(fp, "%c", 0x4A);
			fprintf(fp, "%c", 0xE6);
			fprintf(fp, "%c", 0x42); // clr.w   d1
			fprintf(fp, "%c", 0x41);
			fprintf(fp, "%c", 0x4E); // rts
			fprintf(fp, "%c", 0x75);
		}
		else {
			/* CalculateInitialStatValue */
			fseek(fp, 0x24A10, SEEK_SET);
			fprintf(fp, "%c", 0x18); // move.b  (a0,d3.w),d4
			fprintf(fp, "%c", 0x30);
			fprintf(fp, "%c", 0x30);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x61); // bsr.w   GetPromotedAtLevel
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0xD0);
		}

		/* Extend Classes */
		if (NumClasses == 64) {
			/* table_PromotedClasses */
			fseek(fp, 0x16FE20, SEEK_SET);
			for (i = 0; i < 64; i++) {
				fprintf(fp, "%c", ClassPromote[i]);
			}
			/* ExecuteChurchMenu */
			fseek(fp, 0x1744A, SEEK_SET);
			fprintf(fp, "%c", 0x4E); // jsr     IsClassPromotable
			fprintf(fp, "%c", 0xB9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x16);
			fprintf(fp, "%c", 0xFA);
			fprintf(fp, "%c", 0x80);
			fprintf(fp, "%c", 0x4E); // nop
			fprintf(fp, "%c", 0x71);
			fprintf(fp, "%c", 0x4E); // nop
			fprintf(fp, "%c", 0x71);
			fprintf(fp, "%c", 0x67); // beq.s   loc_17470
			fprintf(fp, "%c", 0x1A);
			fseek(fp, 0x174F4, SEEK_SET);
			fprintf(fp, "%c", 0x4E); // jsr     IsClassPromotable
			fprintf(fp, "%c", 0xB9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x16);
			fprintf(fp, "%c", 0xFA);
			fprintf(fp, "%c", 0x80);
			fprintf(fp, "%c", 0x4E); // nop
			fprintf(fp, "%c", 0x71);
			fprintf(fp, "%c", 0x4E); // nop
			fprintf(fp, "%c", 0x71);
			fprintf(fp, "%c", 0x66); // bne.s   loc_17510
			fprintf(fp, "%c", 0x0D);

			/* IsClassPromotable */
			fseek(fp, 0x16FA80, SEEK_SET);
			fprintf(fp, "%c", 0x48); // movem.l a0,-(sp)
			fprintf(fp, "%c", 0xE7);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x80);
			fprintf(fp, "%c", 0x4E); // jsr     GetPromotedClass
			fprintf(fp, "%c", 0xB9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x16);
			fprintf(fp, "%c", 0xFE);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x0C); // cmpi.b  #-1,d1
			fprintf(fp, "%c", 0x01);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0xFF);
			fprintf(fp, "%c", 0x4C); // movem.l (sp)+,a0
			fprintf(fp, "%c", 0xDF);
			fprintf(fp, "%c", 0x01);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x4E); // rts
			fprintf(fp, "%c", 0x75);

			/* IsAtLevelCap */
			fseek(fp, 0x22C3E, SEEK_SET);
			fprintf(fp, "%c", 0x4E); // jsr     AdjustLevelCapIfNotPromotable
			fprintf(fp, "%c", 0xB9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x1F);
			fprintf(fp, "%c", 0xFD);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x4E); // nop
			fprintf(fp, "%c", 0x71);

			/* AdjustLevelCapIfNotPromotable */
			fseek(fp, 0x1FFD00, SEEK_SET);
			fprintf(fp, "%c", 0x48); // movem.l d0-d1,-(sp)
			fprintf(fp, "%c", 0xE7);
			fprintf(fp, "%c", 0xC0);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x10); // move.b  d1,d0
			fprintf(fp, "%c", 0x01);
			fprintf(fp, "%c", 0x43); // lea     (table_PromotedClasses).l,a1
			fprintf(fp, "%c", 0xF9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x16);
			fprintf(fp, "%c", 0xFE);
			fprintf(fp, "%c", 0x20);
			fprintf(fp, "%c", 0x12); // move.b  (a1,d0.w),d1
			fprintf(fp, "%c", 0x31);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x0C); // cmpi.b  #-1,d1
			fprintf(fp, "%c", 0x01);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0xFF);
			fprintf(fp, "%c", 0x66); // bne.s   loc_1FFD18
			fprintf(fp, "%c", 0x02);
			fprintf(fp, "%c", 0x74); // moveq   #FORCE_LEVEL_CAP_PROMOTED,d2
			fprintf(fp, "%c", 0x63);
			fprintf(fp, "%c", 0x4C); // movem.l (sp)+,d0-d1
			fprintf(fp, "%c", 0xDF);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x03);
			fprintf(fp, "%c", 0x4E); // rts
			fprintf(fp, "%c", 0x75);

			/* IsItemEquippable */
			fseek(fp, 0x22F8C, SEEK_SET);
			fprintf(fp, "%c", 0x4E); // jsr     GetEquipFlags
			fprintf(fp, "%c", 0xB9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x16);
			fprintf(fp, "%c", 0xFF);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x4E); // nop
			fprintf(fp, "%c", 0x71);

			/* GetEquipFlags */
			fseek(fp, 0x16FF00, SEEK_SET);
			fprintf(fp, "%c", 0x4E); // jsr     j_GetClass
			fprintf(fp, "%c", 0xB9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x02);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x78);
			fprintf(fp, "%c", 0x0C); // cmpi.b  #32,d1
			fprintf(fp, "%c", 0x01);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x20);
			fprintf(fp, "%c", 0x6C); // bge.s   loc_16FF10
			fprintf(fp, "%c", 0x04);
			fprintf(fp, "%c", 0x26); // move.l  (a1),d3
			fprintf(fp, "%c", 0x11);
			fprintf(fp, "%c", 0x4E); // rts
			fprintf(fp, "%c", 0x75);
			fprintf(fp, "%c", 0x26); // move.l  16(a1),d3
			fprintf(fp, "%c", 0x29);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x10);
			fprintf(fp, "%c", 0x04); // subi.w  #32,d1
			fprintf(fp, "%c", 0x41);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x20);
			fprintf(fp, "%c", 0x4E); // rts
			fprintf(fp, "%c", 0x75);

			/* ApplyClassToTargetPriority */
			fseek(fp, 0x2438A, SEEK_SET);
			fprintf(fp, "%c", 0x4E); // jsr     GetAiPriority
			fprintf(fp, "%c", 0xB9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x16);
			fprintf(fp, "%c", 0xFA);
			fprintf(fp, "%c", 0xA0);

			/* GetAiPriority */
			fseek(fp, 0x16FAA0, SEEK_SET);
			fprintf(fp, "%c", 0x41); // lea     (table_AiPriority).l,a0
			fprintf(fp, "%c", 0xF9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x16);
			fprintf(fp, "%c", 0xFA);
			fprintf(fp, "%c", 0xC0);
			fprintf(fp, "%c", 0x30); // move.w  (a1),d0
			fprintf(fp, "%c", 0x11);
			fprintf(fp, "%c", 0x4E); // rts
			fprintf(fp, "%c", 0x75);

			/* Promote */
			fseek(fp, 0x24928, SEEK_SET);
			fprintf(fp, "%c", 0x4E); // jsr     GetPromotedClass
			fprintf(fp, "%c", 0xB9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x16);
			fprintf(fp, "%c", 0xFE);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x4E); // nop
			fprintf(fp, "%c", 0x71);
			fprintf(fp, "%c", 0x4E); // nop
			fprintf(fp, "%c", 0x71);

			/* GetPromotedClass */
			fseek(fp, 0x16FE00, SEEK_SET);
			fprintf(fp, "%c", 0x4E); // jsr     j_GetClass
			fprintf(fp, "%c", 0xB9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x02);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x78);
			fprintf(fp, "%c", 0x41); // lea     (table_PromotedClasses).l,a0
			fprintf(fp, "%c", 0xF9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x16);
			fprintf(fp, "%c", 0xFE);
			fprintf(fp, "%c", 0x20);
			fprintf(fp, "%c", 0xD0); // adda.w  d1,a0
			fprintf(fp, "%c", 0xC1);
			fprintf(fp, "%c", 0x12); // move.b  (a0),d1
			fprintf(fp, "%c", 0x10);
			fprintf(fp, "%c", 0x4E); // rts
			fprintf(fp, "%c", 0x75);

			/* CalculateEffectiveLevel */
			fseek(fp, 0x24BB6, SEEK_SET);
			fprintf(fp, "%c", 0x4E); // jsr     IsCombatantPromoted
			fprintf(fp, "%c", 0xB9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x1F);
			fprintf(fp, "%c", 0xFC);
			fprintf(fp, "%c", 0x80);
			fprintf(fp, "%c", 0x67); // beq.s   loc_24BCC
			fprintf(fp, "%c", 0x0E);
			fprintf(fp, "%c", 0x4E); // nop
			fprintf(fp, "%c", 0x71);
			fprintf(fp, "%c", 0x4E); // nop
			fprintf(fp, "%c", 0x71);
			fprintf(fp, "%c", 0x4E); // nop
			fprintf(fp, "%c", 0x71);
			fprintf(fp, "%c", 0x4E); // nop
			fprintf(fp, "%c", 0x71);
			fprintf(fp, "%c", 0x4E); // nop
			fprintf(fp, "%c", 0x71);

			/* IsCombatantPromoted */
			fseek(fp, 0x1FFC80, SEEK_SET);
			fprintf(fp, "%c", 0x48); // movem.w d0,-(sp)
			fprintf(fp, "%c", 0xA7);
			fprintf(fp, "%c", 0x80);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x4E); // jsr     alt_GetEntity
			fprintf(fp, "%c", 0xB9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x02);
			fprintf(fp, "%c", 0x25);
			fprintf(fp, "%c", 0xB0);
			fprintf(fp, "%c", 0x4A); // tst.b   d0
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x6A); // bpl.s   @continue
			fprintf(fp, "%c", 0x04);
			fprintf(fp, "%c", 0x42); // clr.w   d0
			fprintf(fp, "%c", 0x40);
			fprintf(fp, "%c", 0x60); // bra.s	@return
			fprintf(fp, "%c", 0x06);
			fprintf(fp, "%c", 0x4E); // jsr     IsPromoted
			fprintf(fp, "%c", 0xB9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x02);
			fprintf(fp, "%c", 0x4A);
			fprintf(fp, "%c", 0xDA);
			fprintf(fp, "%c", 0x4C); // movem.w (sp)+,d0
			fprintf(fp, "%c", 0x9F);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x01);
			fprintf(fp, "%c", 0x4E); // rts
			fprintf(fp, "%c", 0x75);

			/* table_AiPriority */
			fseek(fp, 0x16FAC0, SEEK_SET);
		}
		else {
			/* ExecuteChurchMenu */
			fseek(fp, 0x1744A, SEEK_SET);
			fprintf(fp, "%c", 0x4E); // jsr     j_GetClass
			fprintf(fp, "%c", 0xB9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x02);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x78);
			fprintf(fp, "%c", 0x0C); // cmpi.w  #BASE_CLASSES_END,d1
			fprintf(fp, "%c", 0x41);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x0D);
			fprintf(fp, "%c", 0x6E); // bgt.s   loc_17470
			fprintf(fp, "%c", 0x1A);
			fseek(fp, 0x174F4, SEEK_SET);
			fprintf(fp, "%c", 0x4E); // jsr     j_GetClass
			fprintf(fp, "%c", 0xB9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x02);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x78);
			fprintf(fp, "%c", 0x0C); // cmpi.w  #BASE_CLASSES_END,d1
			fprintf(fp, "%c", 0x41);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x0D);
			fprintf(fp, "%c", 0x6F); // ble.s   loc_17510
			fprintf(fp, "%c", 0x0D);

			/* IsAtLevelCap */
			fseek(fp, 0x22C3E, SEEK_SET);
			fprintf(fp, "%c", 0x0C); // cmpi.w  #PROMOTED_CLASSES_START,d1
			fprintf(fp, "%c", 0x41);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x0E);
			fprintf(fp, "%c", 0x65); // bcs.s   loc_22C46
			fprintf(fp, "%c", 0x02);
			fprintf(fp, "%c", 0x74); // moveq   #FORCE_LEVEL_CAP_PROMOTED,d2
			fprintf(fp, "%c", 0x63);

			/* IsItemEquippable */
			fseek(fp, 0x22F8C, SEEK_SET);
			fprintf(fp, "%c", 0x4E); // jsr     j_GetClass
			fprintf(fp, "%c", 0xB9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x02);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x78);
			fprintf(fp, "%c", 0x26); // move.l  (a1),d3
			fprintf(fp, "%c", 0x11);

			/* ApplyClassToTargetPriority */
			fseek(fp, 0x2438A, SEEK_SET);
			fprintf(fp, "%c", 0x41); // lea     table_AiPriority(pc), a0
			fprintf(fp, "%c", 0xFA);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x1E);
			fprintf(fp, "%c", 0x30); // move.w  (a1),d0
			fprintf(fp, "%c", 0x11);

			/* Promote */
			fseek(fp, 0x24928, SEEK_SET);
			fprintf(fp, "%c", 0x4E); // jsr     j_GetClass
			fprintf(fp, "%c", 0xB9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x02);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x78);
			fprintf(fp, "%c", 0x06); // addi.w  #16,d1
			fprintf(fp, "%c", 0x41);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x10);

			/* CalculateEffectiveLevel */
			fseek(fp, 0x24BB6, SEEK_SET);
			fprintf(fp, "%c", 0x4E); // jsr     j_GetClassForCombatant
			fprintf(fp, "%c", 0xB9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x02);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0xAC);
			fprintf(fp, "%c", 0x0C); // cmpi.w  #PROMOTED_CLASSES_START,d1
			fprintf(fp, "%c", 0x41);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x0E);
			fprintf(fp, "%c", 0x65); // bcs.s   loc_24BCC
			fprintf(fp, "%c", 0x0A);
			fprintf(fp, "%c", 0x0C); // cmpi.w  #CLASS_YGRT,d1
			fprintf(fp, "%c", 0x41);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x1E);
			fprintf(fp, "%c", 0x64); // bcc.s   loc_24BCC
			fprintf(fp, "%c", 0x04);

			/* table_AiPriority */
			fseek(fp, 0x243AA, SEEK_SET);
		}
		for (i = 0; i < NumClasses; i++) {
			fprintf(fp, "%c", Priority0[i]);
		}
		for (i = 0; i < NumClasses; i++) {
			fprintf(fp, "%c", Priority1[i]);
		}
		for (i = 0; i < NumClasses; i++) {
			fprintf(fp, "%c", Priority2[i]);
		}
		for (i = 0; i < NumClasses; i++) {
			fprintf(fp, "%c", Priority3[i]);
		}
		for (i = 0; i < NumClasses; i++) {
			fprintf(fp, "%c", Priority4[i]);
		}
		for (i = 0; i < NumClasses; i++) {
			fprintf(fp, "%c", Priority5[i]);
		}
		for (i = 0; i < NumClasses; i++) {
			fprintf(fp, "%c", Priority6[i]);
		}
		for (i = 0; i < NumClasses; i++) {
			fprintf(fp, "%c", Priority7[i]);
		}
		for (i = 0; i < NumClasses; i++) {
			fprintf(fp, "%c", Priority8[i]);
		}

		fseek(fp,0x203C0,SEEK_SET);
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

		fseek(fp,0x203C4,SEEK_SET);
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

		fseek(fp, 0x20CEF, SEEK_SET);
		fprintf(fp, "%c", HealerClasses[0]); // Save first healer class
		fseek(fp, 0x20CF5, SEEK_SET);
		fprintf(fp, "%c", HealerClasses[1]); // Save second healer class
		fseek(fp, 0x20CFB, SEEK_SET);
		fprintf(fp, "%c", HealerClasses[2]); // Save third healer class
		fseek(fp, 0x20D01, SEEK_SET);
		fprintf(fp, "%c", HealerClasses[3]); // Save fourth healer class

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