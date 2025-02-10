void SaveChar(){
	unsigned char r;

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

		/* GetPortrait */
		fseek(fp, 0x239E4, SEEK_SET);
		fprintf(fp, "%c", 0x6C); // bge.s   @isChangedIntoJogurt
		fprintf(fp, "%c", 0x18);
		fseek(fp, 0x23A0A, SEEK_SET);
		fprintf(fp, "%c", 0x4E); // jsr     GetBaseOrPromotedPortrait
		fprintf(fp, "%c", 0xB9);
		fprintf(fp, "%c", 0x00);
		fprintf(fp, "%c", 0x13);
		fprintf(fp, "%c", 0xFF);
		fprintf(fp, "%c", 0xE0);
		fprintf(fp, "%c", 0x4E); // nop
		fprintf(fp, "%c", 0x71);
		fprintf(fp, "%c", 0x4E); // nop
		fprintf(fp, "%c", 0x71);
		fprintf(fp, "%c", 0x4E); // nop
		fprintf(fp, "%c", 0x71);
		fprintf(fp, "%c", 0x4E); // nop
		fprintf(fp, "%c", 0x71);

		/* GetBaseOrPromotedPortrait */
		fseek(fp, 0x13FFE0, SEEK_SET);
		fprintf(fp, "%c", 0x42); // clr.w   d1
		fprintf(fp, "%c", 0x41);
		fprintf(fp, "%c", 0x4E); // jsr     IsPromoted
		fprintf(fp, "%c", 0xB9);
		fprintf(fp, "%c", 0x00);
		fprintf(fp, "%c", 0x02);
		fprintf(fp, "%c", 0x4A);
		fprintf(fp, "%c", 0xDA);
		fprintf(fp, "%c", 0x66); // bne.s   @promoted
		fprintf(fp, "%c", 0x06);
		fprintf(fp, "%c", 0x12); // move.b  table_Portraits1(pc,d0.w),d1
		fprintf(fp, "%c", 0x3B);
		fprintf(fp, "%c", 0x00);
		fprintf(fp, "%c", 0x14);
		fprintf(fp, "%c", 0x4E); // rts
		fprintf(fp, "%c", 0x75);
		fprintf(fp, "%c", 0x12); // move.b  table_Portraits2(pc,d0.w),d1
		fprintf(fp, "%c", 0x3B);
		fprintf(fp, "%c", 0x00);
		fprintf(fp, "%c", 0x4E);
		fprintf(fp, "%c", 0x4E); // rts
		fprintf(fp, "%c", 0x75);

		CharPortrait[30] = NovaPortrait;

		/* table_Portraits1 */
		fseek(fp, 0x140000, SEEK_SET);
		for (int i = 0; i < MAX_CHARS; i++) {
			fprintf(fp, "%c", (CharPortrait[i]));
		}
		/* table_Portraits2 */
		fseek(fp, 0x140040, SEEK_SET);
		for (int i = 0; i < MAX_CHARS; i++) {
			fprintf(fp, "%c", (CharPortrait2[i]));
		}

		/* GetMapsprite */
		fseek(fp, 0x23A56, SEEK_SET);
		fprintf(fp, "%c", 0x6C); // bge.s   @isChangedIntoJogurt
		fprintf(fp, "%c", 0x18);
		fseek(fp, 0x23A7C, SEEK_SET);
		fprintf(fp, "%c", 0x4E); // jsr     GetBaseOrPromotedMapsprite
		fprintf(fp, "%c", 0xB9);
		fprintf(fp, "%c", 0x00);
		fprintf(fp, "%c", 0x14);
		fprintf(fp, "%c", 0x00);
		fprintf(fp, "%c", 0xE0);
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
		fprintf(fp, "%c", 0x4E); // nop
		fprintf(fp, "%c", 0x71);

		/* GetBaseOrPromotedMapsprite */
		fseek(fp, 0x1400E0, SEEK_SET);
		fprintf(fp, "%c", 0x4E); // jsr     ApplyOutfitItems
		fprintf(fp, "%c", 0xB9);
		fprintf(fp, "%c", 0x00);
		fprintf(fp, "%c", 0x02);
		fprintf(fp, "%c", 0x3A);
		fprintf(fp, "%c", 0x94);
		fprintf(fp, "%c", 0x64); // bcc.s   @return
		fprintf(fp, "%c", 0x0E);
		fprintf(fp, "%c", 0x42); // clr.w   d1
		fprintf(fp, "%c", 0x41);
		fprintf(fp, "%c", 0x4E); // jsr     IsPromoted
		fprintf(fp, "%c", 0xB9);
		fprintf(fp, "%c", 0x00);
		fprintf(fp, "%c", 0x02);
		fprintf(fp, "%c", 0x4A);
		fprintf(fp, "%c", 0xDA);
		fprintf(fp, "%c", 0x66); // bne.s   @promoted
		fprintf(fp, "%c", 0x06);
		fprintf(fp, "%c", 0x12); // move.b  table_Mapsprites1(pc,d0.w),d1
		fprintf(fp, "%c", 0x3B);
		fprintf(fp, "%c", 0x00);
		fprintf(fp, "%c", 0x0C);
		fprintf(fp, "%c", 0x4E); // rts
		fprintf(fp, "%c", 0x75);
		fprintf(fp, "%c", 0x12); // move.b  table_Mapsprites2(pc,d0.w),d1
		fprintf(fp, "%c", 0x3B);
		fprintf(fp, "%c", 0x00);
		fprintf(fp, "%c", 0x46);
		fprintf(fp, "%c", 0x4E); // rts
		fprintf(fp, "%c", 0x75);

		CharMapSprite[30] = NovaSprite;

		/* table_Mapsprites1 */
		fseek(fp, 0x140100, SEEK_SET);
		for (int i = 0; i < MAX_CHARS; i++) {
			fprintf(fp, "%c", (CharMapSprite[i]));
		}
		/* table_Mapsprites2 */
		fseek(fp, 0x140140, SEEK_SET);
		for (int i = 0; i < MAX_CHARS; i++) {
			fprintf(fp, "%c", (CharMapSprite2[i]));
		}

		/* readerScreenAction_New */
		fseek(fp, 0x3490, SEEK_SET);
		fprintf(fp, "%c", 0x7E); // moveq   #NumChars-1,d7
		fprintf(fp, "%c", NumChars - 1);

		/* debugMode_ChapterTest */
		fseek(fp, 0x4DFA, SEEK_SET);
		fprintf(fp, "%c", 0x7E); // moveq   #NumChars-2,d7
		fprintf(fp, "%c", NumChars - 2);

		/* debugMode_BattleTest */
		fseek(fp, 0x4F60, SEEK_SET);
		fprintf(fp, "%c", 0x7E); // moveq   #NumChars-2,d7
		fprintf(fp, "%c", NumChars - 2);

		/* InitializeHeadquarters */
		fseek(fp, 0x67BE, SEEK_SET);
		fprintf(fp, "%c", 0x7E); // moveq   #NumChars-1,d7
		fprintf(fp, "%c", NumChars - 1);

		/* TalkMenuAction */
		fseek(fp, 0x6C04, SEEK_SET);
		fprintf(fp, "%c", 0x74); // moveq   #MAPSPRITE_NOVA,d2
		fprintf(fp, "%c", NovaSprite);
		fseek(fp, 0x6C10, SEEK_SET);
		fprintf(fp, "%c", 0x74); // moveq   #NumChars-2,d2
		fprintf(fp, "%c", NumChars - 2);

		/* InitializeNewGame */
		fseek(fp, 0x21B30, SEEK_SET);
		fprintf(fp, "%c", 0x4E); // jsr     InitializePromotedAtlevels
		fprintf(fp, "%c", 0xB9);
		fprintf(fp, "%c", 0x00);
		fprintf(fp, "%c", 0x14);
		fprintf(fp, "%c", 0x3C);
		fprintf(fp, "%c", 0x00);
		fprintf(fp, "%c", 0x4E); // nop
		fprintf(fp, "%c", 0x71);
		fprintf(fp, "%c", 0x4E); // nop
		fprintf(fp, "%c", 0x71);
		fprintf(fp, "%c", 0x70); // moveq   #NumChars-1,d0
		fprintf(fp, "%c", NumChars - 1);

		/* InitializePromotedAtlevels */
		fseek(fp, 0x143C00, SEEK_SET);
		fprintf(fp, "%c", 0x43); // lea     (table_InitialPromotedAtLevels).l,a1
		fprintf(fp, "%c", 0xF9);
		fprintf(fp, "%c", 0x00);
		fprintf(fp, "%c", 0x14);
		fprintf(fp, "%c", 0x3C);
		fprintf(fp, "%c", 0x20);
		fprintf(fp, "%c", 0x30); // move.w  #NumChars-1,d0
		fprintf(fp, "%c", 0x3C);
		fprintf(fp, "%c", 0x00);
		fprintf(fp, "%c", NumChars - 1);
		fprintf(fp, "%c", 0x12); // move.b  (a1,d0.w),d1
		fprintf(fp, "%c", 0x31);
		fprintf(fp, "%c", 0x00);
		fprintf(fp, "%c", 0x00);
		fprintf(fp, "%c", 0x11); // move.b  d1,(a0,d0.w)
		fprintf(fp, "%c", 0x81);
		fprintf(fp, "%c", 0x00);
		fprintf(fp, "%c", 0x00);
		fprintf(fp, "%c", 0x51); // dbf     d0,@loop
		fprintf(fp, "%c", 0xC8);
		fprintf(fp, "%c", 0xFF);
		fprintf(fp, "%c", 0xF6);
		fprintf(fp, "%c", 0x4E); // rts
		fprintf(fp, "%c", 0x75);

		/* table_InitialPromotedAtLevels */
		fseek(fp, 0x143C20, SEEK_SET);
		for (int i = 0; i < MAX_CHARS; i++) {
			if (CharPromotedAt[i] <= 20)fprintf(fp, "%c", CharPromotedAt[i]); // promoted at level can not exceed 20 (i.e., the stat growth projection level)
		}

		/* ResetCombatants */
		fseek(fp, 0x22032, SEEK_SET);
		fprintf(fp, "%c", 0x70); // moveq   #NumChars-1,d0
		fprintf(fp, "%c", NumChars - 1);

		/* RefreshMembersList */
		fseek(fp, 0x2207E, SEEK_SET);
		fprintf(fp, "%c", 0x0C); // cmpi.b  #NumChars,d0
		fprintf(fp, "%c", 0x00);
		fprintf(fp, "%c", 0x00);
		fprintf(fp, "%c", NumChars);

		/* RefillWholeForceHp */
		fseek(fp, 0x22222, SEEK_SET);
		fprintf(fp, "%c", 0x70); // moveq   #NumChars-1,d0
		fprintf(fp, "%c", NumChars - 1);

		/* KindanNoHako */
		fseek(fp, 0x23532, SEEK_SET);
		fprintf(fp, "%c", 0x74); // moveq   #NumChars-1,d2
		fprintf(fp, "%c", NumChars - 1);

		/* ResetForceMemberStats */
		fseek(fp, 0x24D12, SEEK_SET);
		fprintf(fp, "%c", 0x70); // moveq   #NumChars-1,d0
		fprintf(fp, "%c", NumChars - 1);

		/* IsItemHeldByForce */
		fseek(fp, 0x24F06, SEEK_SET);
		fprintf(fp, "%c", 0x70); // moveq   #NumChars-1,d0
		fprintf(fp, "%c", NumChars - 1);

		/* LoadBattlespriteAndPaletteIndexes */
		fseek(fp, 0x23B60, SEEK_SET);
		fprintf(fp, "%c", 0xD0); // adda.w  d0,a0
		fprintf(fp, "%c", 0xC0);
		fprintf(fp, "%c", 0xD0); // adda.w  d0,a0
		fprintf(fp, "%c", 0xC0);
		fprintf(fp, "%c", 0x4E); // jsr     GetBaseOrPromotedBattlesprite
		fprintf(fp, "%c", 0xB9);
		fprintf(fp, "%c", 0x00);
		fprintf(fp, "%c", 0x14);
		fprintf(fp, "%c", 0x16);
		fprintf(fp, "%c", 0xC0);
		fprintf(fp, "%c", 0x12); // move.b  (a0)+,d1
		fprintf(fp, "%c", 0x18);
		fprintf(fp, "%c", 0x14); // move.b  (a0),d2
		fprintf(fp, "%c", 0x10);
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
		fprintf(fp, "%c", 0x31); // move.w  d1,((BATTLESCENE_SPRITE_INDEX-$1000000)).w
		fprintf(fp, "%c", 0xC1);
		fprintf(fp, "%c", 0xCB);
		fprintf(fp, "%c", 0xA6);
		fprintf(fp, "%c", 0x31); // move.w  d2,((BATTLESCENE_PALETTE_INDEX-$1000000)).w
		fprintf(fp, "%c", 0xC2);
		fprintf(fp, "%c", 0xCB);
		fprintf(fp, "%c", 0xA8);

		/* GetBaseOrPromotedBattlesprite */
		fseek(fp, 0x1416C0, SEEK_SET);
		fprintf(fp, "%c", 0x4E); // jsr     IsPromoted
		fprintf(fp, "%c", 0xB9);
		fprintf(fp, "%c", 0x00);
		fprintf(fp, "%c", 0x02);
		fprintf(fp, "%c", 0x4A);
		fprintf(fp, "%c", 0xDA);
		fprintf(fp, "%c", 0x66); // bne.s   @promoted
		fprintf(fp, "%c", 0x08);
		fprintf(fp, "%c", 0x20);
		fprintf(fp, "%c", 0x79); // movea.l (p_BattlespriteData).l,a0
		fprintf(fp, "%c", 0x00);
		fprintf(fp, "%c", 0x02);
		fprintf(fp, "%c", 0x03);
		fprintf(fp, "%c", 0xAC);
		fprintf(fp, "%c", 0x60); // bra.s   loc_1416D6
		fprintf(fp, "%c", 0x06);
		fprintf(fp, "%c", 0x41); // lea     (table_Battlesprites2).l,a0
		fprintf(fp, "%c", 0xF9);
		fprintf(fp, "%c", 0x00);
		fprintf(fp, "%c", 0x14);
		fprintf(fp, "%c", 0x13);
		fprintf(fp, "%c", 0x80);
		fprintf(fp, "%c", 0xD0); // adda.w  d0,a0
		fprintf(fp, "%c", 0xC0);
		fprintf(fp, "%c", 0xD0); // adda.w  d0,a0
		fprintf(fp, "%c", 0xC0);
		fprintf(fp, "%c", 0x4E); // rts
		fprintf(fp, "%c", 0x75);

		if (NumChars == MAX_CHARS) {

			/* Header: SRAM end address */
			fseek(fp, 0x1B8, SEEK_SET);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x20);
			fprintf(fp, "%c", 0xFF);
			fprintf(fp, "%c", 0xFF);

			/* InitializeNewGame */
			fseek(fp, 0x21B1E, SEEK_SET);
			fprintf(fp, "%c", 0x43); // lea     ((FORCE_MEMBERS_DATA-$1000000)).w,a1
			fprintf(fp, "%c", 0xF8);
			fprintf(fp, "%c", 0xF0);
			fprintf(fp, "%c", 0x20);
			fprintf(fp, "%c", 0x30); // move.w  #MAX_CHARS*40,d0
			fprintf(fp, "%c", 0x3C);
			fprintf(fp, "%c", 0x07);
			fprintf(fp, "%c", 0xD0);
			fseek(fp, 0x21B2C, SEEK_SET);
			fprintf(fp, "%c", 0x41); // lea     ((PROMOTED_AT_LEVELS-$1000000)).w,a0
			fprintf(fp, "%c", 0xF8);
			fprintf(fp, "%c", 0xCC);
			fprintf(fp, "%c", 0x00);
			fseek(fp, 0x21B3C, SEEK_SET);
			fprintf(fp, "%c", 0x4E); // jsr     ClearForceMemberFlags2
			fprintf(fp, "%c", 0xB9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x14);
			fprintf(fp, "%c", 0x14);
			fprintf(fp, "%c", 0x80);

			/* ClearForceMemberFlags2 */
			fseek(fp, 0x141480, SEEK_SET);
			fprintf(fp, "%c", 0x42); // clr.l   ((FORCE_MEMBER_FLAGS_2-$1000000)).w
			fprintf(fp, "%c", 0xB8);
			fprintf(fp, "%c", 0xCC);
			fprintf(fp, "%c", 0x80);
			fprintf(fp, "%c", 0x4E); // jsr     j_GetLevel
			fprintf(fp, "%c", 0xB9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x02);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x7C);
			fprintf(fp, "%c", 0x4E); // rts
			fprintf(fp, "%c", 0x75);

			/* GetEntityEntryAddress */
			fseek(fp, 0x22600, SEEK_SET);
			fprintf(fp, "%c", 0x41); // lea     ((FORCE_MEMBERS_DATA-$1000000)).w,a0
			fprintf(fp, "%c", 0xF8);
			fprintf(fp, "%c", 0xF0);
			fprintf(fp, "%c", 0x20);

			/* CheckSavedGames */
			fseek(fp, 0x1643BA, SEEK_SET);
			fprintf(fp, "%c", 0x41); // lea     ((FORCE_MEMBERS_DATA-$1000000)).w,a0
			fprintf(fp, "%c", 0xF8);
			fprintf(fp, "%c", 0xF0);
			fprintf(fp, "%c", 0x20);

			/* Promote */
			fseek(fp, 0x24920, SEEK_SET);
			fprintf(fp, "%c", 0x41); // lea     ((PROMOTED_AT_LEVELS-$1000000)).w,a0
			fprintf(fp, "%c", 0xF8);
			fprintf(fp, "%c", 0xCC);
			fprintf(fp, "%c", 0x00);

			/* GetPromotedAtLevel */
			fseek(fp, 0x24AEA, SEEK_SET);
			fprintf(fp, "%c", 0x43); // lea     ((PROMOTED_AT_LEVELS-$1000000)).w,a1
			fprintf(fp, "%c", 0xF8);
			fprintf(fp, "%c", 0xCC);
			fprintf(fp, "%c", 0x00);

			/* CalculateTotalLevel */
			fseek(fp, 0x24B96, SEEK_SET);
			fprintf(fp, "%c", 0x41); // lea     ((PROMOTED_AT_LEVELS-$1000000)).w,a0
			fprintf(fp, "%c", 0xF8);
			fprintf(fp, "%c", 0xCC);
			fprintf(fp, "%c", 0x00);

			/* IsInForce */
			fseek(fp, 0x220B8, SEEK_SET);
			fprintf(fp, "%c", 0x4E); // jmp     GetForceMemberFlag
			fprintf(fp, "%c", 0xF9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x14);
			fprintf(fp, "%c", 0x14);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x4E); // nop
			fprintf(fp, "%c", 0x71);

			/* dup_IsInForce */
			fseek(fp, 0x221D4, SEEK_SET);
			fprintf(fp, "%c", 0x4E); // jmp     GetForceMemberFlag
			fprintf(fp, "%c", 0xF9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x14);
			fprintf(fp, "%c", 0x14);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x4E); // nop
			fprintf(fp, "%c", 0x71);

			/* GetForceMemberFlag */
			fseek(fp, 0x141400, SEEK_SET);
			fprintf(fp, "%c", 0x48); // 
			fprintf(fp, "%c", 0xE7);
			fprintf(fp, "%c", 0xC0);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x0C); // 
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x1E);
			fprintf(fp, "%c", 0x6C); // 
			fprintf(fp, "%c", 0x0C);
			fprintf(fp, "%c", 0x22); // 
			fprintf(fp, "%c", 0x38);
			fprintf(fp, "%c", 0x9C);
			fprintf(fp, "%c", 0x8A);
			fprintf(fp, "%c", 0x01); // 
			fprintf(fp, "%c", 0x01);
			fprintf(fp, "%c", 0x4C); // 
			fprintf(fp, "%c", 0xDF);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x03);
			fprintf(fp, "%c", 0x4E); // rts
			fprintf(fp, "%c", 0x75);
			fprintf(fp, "%c", 0x04); // 
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x1E);
			fprintf(fp, "%c", 0x22); // move.l  ((FORCE_MEMBER_FLAGS_2-$1000000)).w,d1
			fprintf(fp, "%c", 0x38);
			fprintf(fp, "%c", 0xCC);
			fprintf(fp, "%c", 0x80);
			fprintf(fp, "%c", 0x01); // 
			fprintf(fp, "%c", 0x01);
			fprintf(fp, "%c", 0x4C); // 
			fprintf(fp, "%c", 0xDF);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x03);
			fprintf(fp, "%c", 0x4E); // rts
			fprintf(fp, "%c", 0x75);

			/* JoinForce */
			fseek(fp, 0x221B6, SEEK_SET);
			fprintf(fp, "%c", 0x4E); // jsr     SetForceMemberFlag
			fprintf(fp, "%c", 0xB9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x14);
			fprintf(fp, "%c", 0x14);
			fprintf(fp, "%c", 0x40);
			fprintf(fp, "%c", 0x4E); // nop
			fprintf(fp, "%c", 0x71);
			fprintf(fp, "%c", 0x4E); // nop
			fprintf(fp, "%c", 0x71);

			/* SetForceMemberFlag */
			fseek(fp, 0x141440, SEEK_SET);
			fprintf(fp, "%c", 0x0C); // 
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x1E);
			fprintf(fp, "%c", 0x6C); // 
			fprintf(fp, "%c", 0x0C);
			fprintf(fp, "%c", 0x22); // 
			fprintf(fp, "%c", 0x38);
			fprintf(fp, "%c", 0x9C);
			fprintf(fp, "%c", 0x8A);
			fprintf(fp, "%c", 0x01); // 
			fprintf(fp, "%c", 0xC1);
			fprintf(fp, "%c", 0x21); // 
			fprintf(fp, "%c", 0xC1);
			fprintf(fp, "%c", 0x9C);
			fprintf(fp, "%c", 0x8A);
			fprintf(fp, "%c", 0x4E); // rts
			fprintf(fp, "%c", 0x75);
			fprintf(fp, "%c", 0x04); // 
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x1E);
			fprintf(fp, "%c", 0x22); // move.l  ((FORCE_MEMBER_FLAGS_2-$1000000)).w,d1
			fprintf(fp, "%c", 0x38);
			fprintf(fp, "%c", 0xCC);
			fprintf(fp, "%c", 0x80);
			fprintf(fp, "%c", 0x01); // 
			fprintf(fp, "%c", 0xC1);
			fprintf(fp, "%c", 0x21); // move.l  d1,((FORCE_MEMBER_FLAGS_2-$1000000)).w
			fprintf(fp, "%c", 0xC1);
			fprintf(fp, "%c", 0xCC);
			fprintf(fp, "%c", 0x80);
			fprintf(fp, "%c", 0x06); // 
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x1E);
			fprintf(fp, "%c", 0x4E); // rts
			fprintf(fp, "%c", 0x75);

			/* MapTeleports */
			fseek(fp, 0x12D5A, SEEK_SET);
			fprintf(fp, "%c", 0x4E); // jsr     GetEventFlagsAddress
			fprintf(fp, "%c", 0xB9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x14);
			fprintf(fp, "%c", 0x15);
			fprintf(fp, "%c", 0x00);

			/* GetEventFlagsAddress */
			fseek(fp, 0x141500, SEEK_SET);
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

			/* ClearCombatantData */
			fseek(fp, 0x21BE0, SEEK_SET);
			fprintf(fp, "%c", 0x41); // lea     ((COMBATANT_DATA-$1000000)).w,a0
			fprintf(fp, "%c", 0xF8);
			fprintf(fp, "%c", 0x9C);
			fprintf(fp, "%c", 0x94);

			/* alt_GetEntity */
			fseek(fp, 0x225B8, SEEK_SET);
			fprintf(fp, "%c", 0x41); // lea     ((COMBATANT_DATA-$1000000)).w,a0
			fprintf(fp, "%c", 0xF8);
			fprintf(fp, "%c", 0x9C);
			fprintf(fp, "%c", 0x94);

			/* GetCombatantEntryAddress */
			fseek(fp, 0x225E6, SEEK_SET);
			fprintf(fp, "%c", 0x41); // lea     ((COMBATANT_DATA-$1000000)).w,a0
			fprintf(fp, "%c", 0xF8);
			fprintf(fp, "%c", 0x9C);
			fprintf(fp, "%c", 0x94);

			fseek(fp, 0x98A8, SEEK_SET);
			fprintf(fp, "%c", 0x41); // lea     ((COMBATANT_DATA-$1000000)).w,a0
			fprintf(fp, "%c", 0xF8);
			fprintf(fp, "%c", 0x9C);
			fprintf(fp, "%c", 0x94);

			fseek(fp, 0x9940, SEEK_SET);
			fprintf(fp, "%c", 0x41); // lea     ((COMBATANT_DATA-$1000000)).w,a0
			fprintf(fp, "%c", 0xF8);
			fprintf(fp, "%c", 0x9C);
			fprintf(fp, "%c", 0x94);

			fseek(fp, 0x9AA2, SEEK_SET);
			fprintf(fp, "%c", 0x41); // lea     ((COMBATANT_DATA-$1000000)).w,a0
			fprintf(fp, "%c", 0xF8);
			fprintf(fp, "%c", 0x9C);
			fprintf(fp, "%c", 0x94);

			fseek(fp, 0xAB5C, SEEK_SET);
			fprintf(fp, "%c", 0x41); // lea     ((COMBATANT_DATA-$1000000)).w,a0
			fprintf(fp, "%c", 0xF8);
			fprintf(fp, "%c", 0x9C);
			fprintf(fp, "%c", 0x94);

			fseek(fp, 0xA776, SEEK_SET);
			fprintf(fp, "%c", 0x41); // lea     ((COMBATANT_DATA-$1000000)).w,a0
			fprintf(fp, "%c", 0xF8);
			fprintf(fp, "%c", 0x9C);
			fprintf(fp, "%c", 0x94);

			fseek(fp, 0xA0F2, SEEK_SET);
			fprintf(fp, "%c", 0x41); // lea     ((COMBATANT_DATA-$1000000)).w,a0
			fprintf(fp, "%c", 0xF8);
			fprintf(fp, "%c", 0x9C);
			fprintf(fp, "%c", 0x94);

			fseek(fp, 0xB54C, SEEK_SET);
			fprintf(fp, "%c", 0x45); // lea     ((COMBATANT_DATA-$1000000)).w,a2
			fprintf(fp, "%c", 0xF8);
			fprintf(fp, "%c", 0x9C);
			fprintf(fp, "%c", 0x94);

			fseek(fp, 0xB474, SEEK_SET);
			fprintf(fp, "%c", 0x30); // move.w  #2047,d0
			fprintf(fp, "%c", 0x3C);
			fprintf(fp, "%c", 0x07);
			fprintf(fp, "%c", 0xFF);

			/* ExecuteChurchMenu */
			fseek(fp, 0x17352, SEEK_SET);
			fprintf(fp, "%c", 0x41); // lea     ((PROMOTED_AT_LEVELS-$1000000)).w,a0
			fprintf(fp, "%c", 0xF8);
			fprintf(fp, "%c", 0xCC);
			fprintf(fp, "%c", 0x00);

			fseek(fp, 0xA144, SEEK_SET);
			fprintf(fp, "%c", 0x0C); // cmpi.b  #ALLY_NOVA,((COMBATANT_1_ENTITY-$1000000)).w
			fprintf(fp, "%c", 0x38);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x1E);
			fprintf(fp, "%c", 0x9C);
			fprintf(fp, "%c", 0xA4);

			fseek(fp, 0x9824, SEEK_SET);
			fprintf(fp, "%c", 0x0C); // cmpi.b  #ALLY_NOVA,((COMBATANT_1_ENTITY-$1000000)).w
			fprintf(fp, "%c", 0x38);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x1E);
			fprintf(fp, "%c", 0x9C);
			fprintf(fp, "%c", 0xA4);

			/* mainMenuAction_Talk */
			fseek(fp, 0x5A88, SEEK_SET);
			fprintf(fp, "%c", 0x0C); // cmpi.b  #ALLY_NOVA,((COMBATANT_1_ENTITY-$1000000)).w
			fprintf(fp, "%c", 0x38);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x1E);
			fprintf(fp, "%c", 0x9C);
			fprintf(fp, "%c", 0xA4);

			/* InitializeHeadquarters */
			fseek(fp, 0x6822, SEEK_SET);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0xF9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x14);
			fprintf(fp, "%c", 0x15);
			fprintf(fp, "%c", 0x80);
			fseek(fp, 0x6856, SEEK_SET);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0xF9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x14);
			fprintf(fp, "%c", 0x15);
			fprintf(fp, "%c", 0xA0);

			fseek(fp, 0x141580, SEEK_SET);
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

			fseek(fp, 0x1415A0, SEEK_SET);
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

			/* CopyBytesToSram */
			fseek(fp, 0x37D0, SEEK_SET);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0xF9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x14);
			fprintf(fp, "%c", 0x16);
			fprintf(fp, "%c", 0x00);

			/* CopyBytesFromSram */
			fseek(fp, 0x37E8, SEEK_SET);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0xF9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x14);
			fprintf(fp, "%c", 0x16);
			fprintf(fp, "%c", 0x60);

			fseek(fp, 0x141600, SEEK_SET);
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

			fseek(fp, 0x141660, SEEK_SET);
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

		}
		else {
			
			/* Header: SRAM end address */
			fseek(fp, 0x1B8, SEEK_SET);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x20);
			fprintf(fp, "%c", 0x3F);
			fprintf(fp, "%c", 0xFF);

			/* CopyBytesToSram */
			fseek(fp, 0x37D0, SEEK_SET);
			fprintf(fp, "%c", 0x12); // move.b  d0,(a1)
			fprintf(fp, "%c", 0x80);
			fprintf(fp, "%c", 0x54); // addq.l  #2,a1
			fprintf(fp, "%c", 0x89);
			fprintf(fp, "%c", 0x4E); // rts
			fprintf(fp, "%c", 0x75);

			/* CopyBytesFromSram */
			fseek(fp, 0x37E8, SEEK_SET);
			fprintf(fp, "%c", 0xB0); // cmp.b   (a1),d0
			fprintf(fp, "%c", 0x11);
			fprintf(fp, "%c", 0x54); // addq.l  #2,a1
			fprintf(fp, "%c", 0x89);
			fprintf(fp, "%c", 0x4E); // rts
			fprintf(fp, "%c", 0x75);

			/* InitializeHeadquarters */
			fseek(fp, 0x6822, SEEK_SET);
			fprintf(fp, "%c", 0x4E); // jsr     j_SetCombatantY
			fprintf(fp, "%c", 0xB9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x02);
			fprintf(fp, "%c", 0x01);
			fprintf(fp, "%c", 0x0C);
			fseek(fp, 0x6856, SEEK_SET);
			fprintf(fp, "%c", 0x4E); // jsr     j_SetCombatantY
			fprintf(fp, "%c", 0xB9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x02);
			fprintf(fp, "%c", 0x01);
			fprintf(fp, "%c", 0x0C);

			fseek(fp, 0xA144, SEEK_SET);
			fprintf(fp, "%c", 0x0C); // cmpi.b  #ALLY_NOVA,((COMBATANT_1_ENTITY-$1000000)).w
			fprintf(fp, "%c", 0x38);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x1E);
			fprintf(fp, "%c", 0xA1);
			fprintf(fp, "%c", 0xC6);

			fseek(fp, 0x9824, SEEK_SET);
			fprintf(fp, "%c", 0x0C); // cmpi.b  #ALLY_NOVA,((COMBATANT_1_ENTITY-$1000000)).w
			fprintf(fp, "%c", 0x38);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x1E);
			fprintf(fp, "%c", 0xA1);
			fprintf(fp, "%c", 0xC6);

			/* mainMenuAction_Talk */
			fseek(fp, 0x5A88, SEEK_SET);
			fprintf(fp, "%c", 0x0C); // cmpi.b  #ALLY_NOVA,((COMBATANT_1_ENTITY-$1000000)).w
			fprintf(fp, "%c", 0x38);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x1E);
			fprintf(fp, "%c", 0xA1);
			fprintf(fp, "%c", 0xC6);

			/* ExecuteChurchMenu */
			fseek(fp, 0x17352, SEEK_SET);
			fprintf(fp, "%c", 0x41); // lea     ((PROMOTED_AT_LEVELS-$1000000)).w,a0
			fprintf(fp, "%c", 0xF8);
			fprintf(fp, "%c", 0xA1);
			fprintf(fp, "%c", 0x6A);

			fseek(fp, 0xB54C, SEEK_SET);
			fprintf(fp, "%c", 0x45); // lea     ((COMBATANT_DATA-$1000000)).w,a2
			fprintf(fp, "%c", 0xF8);
			fprintf(fp, "%c", 0xA1);
			fprintf(fp, "%c", 0xB6);

			fseek(fp, 0xA776, SEEK_SET);
			fprintf(fp, "%c", 0x41); // lea     ((COMBATANT_DATA-$1000000)).w,a0
			fprintf(fp, "%c", 0xF8);
			fprintf(fp, "%c", 0xA1);
			fprintf(fp, "%c", 0xB6);

			fseek(fp, 0xA0F2, SEEK_SET);
			fprintf(fp, "%c", 0x41); // lea     ((COMBATANT_DATA-$1000000)).w,a0
			fprintf(fp, "%c", 0xF8);
			fprintf(fp, "%c", 0xA1);
			fprintf(fp, "%c", 0xB6);

			fseek(fp, 0x98A8, SEEK_SET);
			fprintf(fp, "%c", 0x41); // lea     ((COMBATANT_DATA-$1000000)).w,a0
			fprintf(fp, "%c", 0xF8);
			fprintf(fp, "%c", 0xA1);
			fprintf(fp, "%c", 0xB6);

			fseek(fp, 0x9940, SEEK_SET);
			fprintf(fp, "%c", 0x41); // lea     ((COMBATANT_DATA-$1000000)).w,a0
			fprintf(fp, "%c", 0xF8);
			fprintf(fp, "%c", 0xA1);
			fprintf(fp, "%c", 0xB6);

			fseek(fp, 0x9AA2, SEEK_SET);
			fprintf(fp, "%c", 0x41); // lea     ((COMBATANT_DATA-$1000000)).w,a0
			fprintf(fp, "%c", 0xF8);
			fprintf(fp, "%c", 0xA1);
			fprintf(fp, "%c", 0xB6);

			fseek(fp, 0xAB5C, SEEK_SET);
			fprintf(fp, "%c", 0x41); // lea     ((COMBATANT_DATA-$1000000)).w,a0
			fprintf(fp, "%c", 0xF8);
			fprintf(fp, "%c", 0xA1);
			fprintf(fp, "%c", 0xB6);

			/* MapTeleports */
			fseek(fp, 0x12D5A, SEEK_SET);
			fprintf(fp, "%c", 0x43); // lea     (EVENT_FLAGS).l,a1
			fprintf(fp, "%c", 0xF9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0xFF);
			fprintf(fp, "%c", 0x9C);
			fprintf(fp, "%c", 0x4E);

			/* ClearCombatantData */
			fseek(fp, 0x21BE0, SEEK_SET);
			fprintf(fp, "%c", 0x41); // lea     ((COMBATANT_DATA-$1000000)).w,a0
			fprintf(fp, "%c", 0xF8);
			fprintf(fp, "%c", 0xA1);
			fprintf(fp, "%c", 0xB6);

			/* alt_GetEntity */
			fseek(fp, 0x225B8, SEEK_SET);
			fprintf(fp, "%c", 0x41); // lea     ((COMBATANT_DATA-$1000000)).w,a0
			fprintf(fp, "%c", 0xF8);
			fprintf(fp, "%c", 0xA1);
			fprintf(fp, "%c", 0xB6);

			/* GetCombatantEntryAddress */
			fseek(fp, 0x225E6, SEEK_SET);
			fprintf(fp, "%c", 0x41); // lea     ((COMBATANT_DATA-$1000000)).w,a0
			fprintf(fp, "%c", 0xF8);
			fprintf(fp, "%c", 0xA1);
			fprintf(fp, "%c", 0xB6);

			/* JoinForce */
			fseek(fp, 0x221B6, SEEK_SET);
			fprintf(fp, "%c", 0x22); // move.l  ((FORCE_MEMBER_FLAGS-$1000000)).w,d1
			fprintf(fp, "%c", 0x38);
			fprintf(fp, "%c", 0x9C);
			fprintf(fp, "%c", 0x8A);
			fprintf(fp, "%c", 0x01); // bset    d0,d1
			fprintf(fp, "%c", 0xC1);
			fprintf(fp, "%c", 0x21); // move.l  d1,((FORCE_MEMBER_FLAGS-$1000000)).w
			fprintf(fp, "%c", 0xC1);
			fprintf(fp, "%c", 0x9C);
			fprintf(fp, "%c", 0x8A);

			/* IsInForce */
			fseek(fp, 0x220B8, SEEK_SET);
			fprintf(fp, "%c", 0x48); // movem.l d1,-(sp)
			fprintf(fp, "%c", 0xE7);
			fprintf(fp, "%c", 0x40);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x22); // move.l  ((FORCE_MEMBER_FLAGS-$1000000)).w,d1
			fprintf(fp, "%c", 0x38);
			fprintf(fp, "%c", 0x9C);
			fprintf(fp, "%c", 0x8A);

			/* dup_IsInForce */
			fseek(fp, 0x221D4, SEEK_SET);
			fprintf(fp, "%c", 0x48); // movem.l d1,-(sp)
			fprintf(fp, "%c", 0xE7);
			fprintf(fp, "%c", 0x40);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x22); // move.l  ((FORCE_MEMBER_FLAGS-$1000000)).w,d1
			fprintf(fp, "%c", 0x38);
			fprintf(fp, "%c", 0x9C);
			fprintf(fp, "%c", 0x8A);

			/* Promote */
			fseek(fp, 0x24920, SEEK_SET);
			fprintf(fp, "%c", 0x41); // lea     ((PROMOTED_AT_LEVELS-$1000000)).w,a0
			fprintf(fp, "%c", 0xF8);
			fprintf(fp, "%c", 0xA1);
			fprintf(fp, "%c", 0x6A);

			/* GetPromotedAtLevel */
			fseek(fp, 0x24AEA, SEEK_SET);
			fprintf(fp, "%c", 0x43); // lea     ((PROMOTED_AT_LEVELS-$1000000)).w,a1
			fprintf(fp, "%c", 0xF8);
			fprintf(fp, "%c", 0xA1);
			fprintf(fp, "%c", 0x6A);

			/* CalculateTotalLevel */
			fseek(fp, 0x24B96, SEEK_SET);
			fprintf(fp, "%c", 0x41); // lea     ((PROMOTED_AT_LEVELS-$1000000)).w,a0
			fprintf(fp, "%c", 0xF8);
			fprintf(fp, "%c", 0xA1);
			fprintf(fp, "%c", 0x6A);

			/* InitializeNewGame */
			fseek(fp, 0x21B1E, SEEK_SET);
			fprintf(fp, "%c", 0x43); // lea     ((FORCE_MEMBERS_DATA-$1000000)).w,a0
			fprintf(fp, "%c", 0xF8);
			fprintf(fp, "%c", 0x9C);
			fprintf(fp, "%c", 0x92);
			fprintf(fp, "%c", 0x30); // move.w  #FORCE_MEMBERS_DATA_BYTES_COUNTER,d0
			fprintf(fp, "%c", 0x3C);
			fprintf(fp, "%c", 0x04);
			fprintf(fp, "%c", 0xD7);
			fseek(fp, 0x21B2C, SEEK_SET);
			fprintf(fp, "%c", 0x41); // lea     ((PROMOTED_AT_LEVELS-$1000000)).w,a0
			fprintf(fp, "%c", 0xF8);
			fprintf(fp, "%c", 0xA1);
			fprintf(fp, "%c", 0x6A);
			fseek(fp, 0x21B3C, SEEK_SET);
			fprintf(fp, "%c", 0x4E); // jsr     j_GetLevel
			fprintf(fp, "%c", 0xB9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x02);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x7C);

			/* GetEntityEntryAddress */
			fseek(fp, 0x22600, SEEK_SET);
			fprintf(fp, "%c", 0x41); // lea     ((FORCE_MEMBERS_DATA-$1000000)).w,a0
			fprintf(fp, "%c", 0xF8);
			fprintf(fp, "%c", 0x9C);
			fprintf(fp, "%c", 0x92);

			/* CheckSavedGames */
			fseek(fp, 0x1643BA, SEEK_SET);
			fprintf(fp, "%c", 0x41); // lea     ((FORCE_MEMBERS_DATA-$1000000)).w,a0
			fprintf(fp, "%c", 0xF8);
			fprintf(fp, "%c", 0x9C);
			fprintf(fp, "%c", 0x92);
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

		for (i = 0;i < MAX_CHARS; i++) {

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

		/* table_InitialForceData */
		CharOffset = 0x140200;

		fseek(fp,0x203A8,SEEK_SET);
		fprintf(fp,"%c",(CharOffset&0xFF000000)/0x1000000);
		fprintf(fp,"%c",(CharOffset&0x00FF0000)/0x10000);
		fprintf(fp,"%c",(CharOffset&0x0000FF00)/0x100);
		fprintf(fp,"%c",(CharOffset&0x000000FF));

		fseek(fp, CharOffset, SEEK_SET);
		for(i = 0; i < MAX_CHARS; i++){
			for(j = 0; j < 10; j++){
				fprintf(fp, "%c", CharName[i][j]);
			}
			CharName[i][10] = 0;
			for(j = 0; j < 30; j++){
				fprintf(fp, "%c", Char[i][j]);
			}
		}


		/* table_BattlespriteData */
		BSprOffset = 0x141300;

		fseek(fp, 0x203AC, SEEK_SET);
		fprintf(fp, "%c", (BSprOffset & 0xFF000000) / 0x1000000);
		fprintf(fp, "%c", (BSprOffset & 0x00FF0000) / 0x10000);
		fprintf(fp, "%c", (BSprOffset & 0x0000FF00) / 0x100);
		fprintf(fp, "%c", (BSprOffset & 0x000000FF));

		fseek(fp, BSprOffset, SEEK_SET);
		for (i = 0; i < MAX_CHARS; i++) {
			fprintf(fp, "%c", BattleSprite[i][0]);
			fprintf(fp, "%c", BattleSprite[i][1]);
		}
		fseek(fp, 0x141380, SEEK_SET);
		for (i = 0; i < MAX_CHARS; i++) {
			fprintf(fp, "%c", BattleSprite2[i][0]);
			fprintf(fp, "%c", BattleSprite2[i][1]);
		}


		/* table_UnpromotedGrowths */
		UStatOffset = 0x141000;

		fseek(fp, 0x203EC, SEEK_SET);
		fprintf(fp, "%c", (UStatOffset & 0xFF000000) / 0x1000000);
		fprintf(fp, "%c", (UStatOffset & 0x00FF0000) / 0x10000);
		fprintf(fp, "%c", (UStatOffset & 0x0000FF00) / 0x100);
		fprintf(fp, "%c", (UStatOffset & 0x000000FF));

		for (j = 0; j < MAX_CHARS; j++) {
			fseek(fp, UStatOffset + 6 * j,SEEK_SET);
			for(i = 0; i < 6; i++){
				fprintf(fp, "%c", Stats[j][i]);
			}
		}


		/* table_PromotedGrowths */
		PStatOffset = 0x141180;

		fseek(fp, 0x203F0, SEEK_SET);
		fprintf(fp, "%c", (PStatOffset & 0xFF000000) / 0x1000000);
		fprintf(fp, "%c", (PStatOffset & 0x00FF0000) / 0x10000);
		fprintf(fp, "%c", (PStatOffset & 0x0000FF00) / 0x100);
		fprintf(fp, "%c", (PStatOffset & 0x000000FF));

		for (j = 0; j < MAX_CHARS; j++) {
			fseek(fp, PStatOffset + 6 * j, SEEK_SET);
			for (i= 0; i < 6; i++) {
				fprintf(fp, "%c", Stats[j][i + 6]);
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