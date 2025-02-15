void SaveChar(){
	unsigned char r;
	int q;

	int SRAMEndAddress = 0x203FFF;
	int ExtendedForceFlagsAddress = 0;
	int ForceMembersDataAddress = 0xFF9C92;
	int ForceMembersDataByteSize = MIN_CHARS * 40;
	int PromotedAtLevelsAddress = 0xFFA16A;
	int ForceFlagsAddress = 0xFF9C8A;
	int CombatantDataAddress = 0xFFA1B6;

	bool ExtendCombatants = false;
	bool ExtendEventFlags = false;

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

		if (NumChars > MIN_CHARS && romsize < 0x200000) {
			MessageBox(NULL, "Rom is too small, expand rom to save character changes.", "Error", MB_OK);
			fclose(fp);
			return;
		}

		if(romsize<CurvesOffset){
			MessageBox(NULL,"Rom is too small, expand rom to save growth curves.","Error",MB_OK);
			fclose(fp);
			return;
		}
		if (ChangeCurves)CurvesOffset = 0x1D8800;


		if (NumChars > MIN_CHARS || NumClasses == 64) {

			PromotedALevelsOffset = 0x1E6000;

			/* InitializeNewGame */
			fseek(fp, 0x21B30, SEEK_SET);
			fprintf(fp, "%c", 0x4E); // jsr     InitializePromotedAtlevels
			fprintf(fp, "%c", 0xB9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x1F);
			fprintf(fp, "%c", 0xFC);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x4E); // nop
			fprintf(fp, "%c", 0x71);
			fprintf(fp, "%c", 0x4E); // nop
			fprintf(fp, "%c", 0x71);

			/* InitializePromotedAtlevels */
			fseek(fp, 0x1FFC00, SEEK_SET);
			fprintf(fp, "%c", 0x43); // lea     (table_InitialPromotedAtLevels).l,a1
			fprintf(fp, "%c", 0xF9);
			fprintf(fp, "%c", (PromotedALevelsOffset & 0xFF000000) / 0x1000000);
			fprintf(fp, "%c", (PromotedALevelsOffset & 0x00FF0000) / 0x10000);
			fprintf(fp, "%c", (PromotedALevelsOffset & 0x0000FF00) / 0x100);
			fprintf(fp, "%c", (PromotedALevelsOffset & 0x000000FF));
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
			if (PromotedALevelsOffset != 0) {
				fseek(fp, PromotedALevelsOffset, SEEK_SET);
				for (int i = 0; i < MAX_CHARS; i++) {
					if (CharPromotedAt[i] <= 20)fprintf(fp, "%c", CharPromotedAt[i]);
				}
			}

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
		else {

			/* InitializeNewGame */
			fseek(fp, 0x21B30, SEEK_SET);
			fprintf(fp, "%c", 0x30); // move.w  #NumChars-1,d0
			fprintf(fp, "%c", 0x3C);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", NumChars - 1);
			fprintf(fp, "%c", 0x42); // clr.b   (a0)+
			fprintf(fp, "%c", 0x18);
			fprintf(fp, "%c", 0x51); // dbf     d0,@ClearPromotedAtLevels_Loop
			fprintf(fp, "%c", 0xC8);
			fprintf(fp, "%c", 0xFF);
			fprintf(fp, "%c", 0xFC);

		}


		/* Extend Chars Data */
		if (NumChars > MIN_CHARS) {

			ForceMembersDataByteSize = MAX_CHARS * 40;
			PortraitOffset = 0x140000;
			PortraitOffset2 = PortraitOffset + 64;
			MSprOffset = 0x140100;
			MSprOffset2 = MSprOffset + 64;
			CharOffset = 0x140200;
			UStatOffset = 0x141000;
			PStatOffset = UStatOffset + 384;
			BSprOffset = 0x141300;
			BSprOffset2 = BSprOffset + 128;

			if (NumCombatants == MAX_COMBATANTS) {
				SRAMEndAddress = 0x20FFFF;
				CombatantDataAddress = 0xFF9C94;
				ForceMembersDataAddress = 0xFFF020;
				PromotedAtLevelsAddress = 0xFFCC00;
				ExtendedForceFlagsAddress = 0xFFCC80;
			}

			/* GetPortrait */
			fseek(fp, 0x239E4, SEEK_SET);
			fprintf(fp, "%c", 0x6C); // bge.s   @isChangedIntoJogurt
			fprintf(fp, "%c", 0x18);
			fseek(fp, 0x23A0A, SEEK_SET);
			fprintf(fp, "%c", 0x4E); // jsr     GetBaseOrPromotedPortrait
			fprintf(fp, "%c", 0xB9);
			fprintf(fp, "%c", ((PortraitOffset - 32) & 0xFF000000) / 0x1000000);
			fprintf(fp, "%c", ((PortraitOffset - 32) & 0x00FF0000) / 0x10000);
			fprintf(fp, "%c", ((PortraitOffset - 32) & 0x0000FF00) / 0x100);
			fprintf(fp, "%c", ((PortraitOffset - 32) & 0x000000FF));
			fprintf(fp, "%c", 0x4E); // nop
			fprintf(fp, "%c", 0x71);
			fprintf(fp, "%c", 0x4E); // nop
			fprintf(fp, "%c", 0x71);
			fprintf(fp, "%c", 0x4E); // nop
			fprintf(fp, "%c", 0x71);
			fprintf(fp, "%c", 0x4E); // nop
			fprintf(fp, "%c", 0x71);

			/* GetBaseOrPromotedPortrait */
			fseek(fp, (PortraitOffset - 32), SEEK_SET);
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

			/* table_Portraits1 */
			if (PortraitOffset != 0) {
				fseek(fp, PortraitOffset, SEEK_SET);
				for (int i = 0; i < MAX_CHARS; i++) {
					fprintf(fp, "%c", (CharPortrait[i]));
				}
			}

			/* table_Portraits2 */
			if (PortraitOffset2 != 0) {
				fseek(fp, PortraitOffset2, SEEK_SET);
				for (int i = 0; i < MAX_CHARS; i++) {
					fprintf(fp, "%c", (CharPortrait2[i]));
				}
			}

			/* InitializeHeadquarters */
			fseek(fp, 0x6808, SEEK_SET);
			fprintf(fp, "%c", 0x0C); // cmpi.b  #ALLY_NOVA,d1
			fprintf(fp, "%c", 0x01);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x1E);
			fprintf(fp, "%c", 0x67); // beq.s   @next
			fprintf(fp, "%c", 0x1A);
			fprintf(fp, "%c", 0x4E); // jsr     GetEntityMapspriteForBattlePartyMember
			fprintf(fp, "%c", 0xB9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x14);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0xC0);
			fprintf(fp, "%c", 0x4E); // nop
			fprintf(fp, "%c", 0x71);
			fseek(fp, 0x683C, SEEK_SET);
			fprintf(fp, "%c", 0x0C); // cmpi.b  #ALLY_NOVA,d1
			fprintf(fp, "%c", 0x01);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x1E);
			fprintf(fp, "%c", 0x67); // beq.s   @next
			fprintf(fp, "%c", 0x1A);
			fprintf(fp, "%c", 0x4E); // jsr     GetEntityMapspriteForBattlePartyMember
			fprintf(fp, "%c", 0xB9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x14);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0xC0);
			fprintf(fp, "%c", 0x4E); // nop
			fprintf(fp, "%c", 0x71);

			/* GetEntityMapspriteForBattlePartyMember */
			fseek(fp, 0x1400C0, SEEK_SET);
			fprintf(fp, "%c", 0x42); // clr.w   d2
			fprintf(fp, "%c", 0x42);
			fprintf(fp, "%c", 0x14); // move.b  (a1)+,d2
			fprintf(fp, "%c", 0x19);
			fprintf(fp, "%c", 0x4E); // jsr     j_SetEntityIndex
			fprintf(fp, "%c", 0xB9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x02);
			fprintf(fp, "%c", 0x01);
			fprintf(fp, "%c", 0x04);
			fprintf(fp, "%c", 0x4E); // jmp     (LoadHeadquartersMapsprite).w
			fprintf(fp, "%c", 0xF8);
			fprintf(fp, "%c", 0x68);
			fprintf(fp, "%c", 0x9C);

			/* GetMapsprite */
			fseek(fp, 0x23A56, SEEK_SET);
			fprintf(fp, "%c", 0x6C); // bge.s   @isChangedIntoJogurt
			fprintf(fp, "%c", 0x18);
			fseek(fp, 0x23A7C, SEEK_SET);
			fprintf(fp, "%c", 0x4E); // jsr     GetBaseOrPromotedMapsprite
			fprintf(fp, "%c", 0xB9);
			fprintf(fp, "%c", ((MSprOffset - 32) & 0xFF000000) / 0x1000000);
			fprintf(fp, "%c", ((MSprOffset - 32) & 0x00FF0000) / 0x10000);
			fprintf(fp, "%c", ((MSprOffset - 32) & 0x0000FF00) / 0x100);
			fprintf(fp, "%c", ((MSprOffset - 32) & 0x000000FF));
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
			fseek(fp, (MSprOffset - 32), SEEK_SET);
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

			/* table_Mapsprites1 */
			if (MSprOffset != 0) {
				fseek(fp, MSprOffset, SEEK_SET);
				for (int i = 0; i < MAX_CHARS; i++) {
					fprintf(fp, "%c", (CharMapSprite[i]));
				}
			}
			/* table_Mapsprites2 */
			if (MSprOffset2 != 0) {
				fseek(fp, MSprOffset2, SEEK_SET);
				for (int i = 0; i < MAX_CHARS; i++) {
					fprintf(fp, "%c", (CharMapSprite2[i]));
				}
			}

			/* InitializeHeadquarters */
			fseek(fp, 0x67BE, SEEK_SET);
			fprintf(fp, "%c", 0x7E); // moveq   #COMBATANT_ENTRIES_COUNTER-1,d7
			fprintf(fp, "%c", NumCombatants - 2);
			fseek(fp, 0x6816, SEEK_SET);
			fprintf(fp, "%c", 0x4E); // jsr     SetHeadquartersCombatantPosition
			fprintf(fp, "%c", 0xB9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x14);
			fprintf(fp, "%c", 0x15);
			fprintf(fp, "%c", 0x80);
			fprintf(fp, "%c", 0xB2); // cmpa.w  #sub_6A2E,a1
			fprintf(fp, "%c", 0xFC);
			fprintf(fp, "%c", 0x6A);
			fprintf(fp, "%c", 0x2E);
			fprintf(fp, "%c", 0x67); // beq.s   loc_682C
			fprintf(fp, "%c", 0x0A);
			fprintf(fp, "%c", 0x4E); // nop
			fprintf(fp, "%c", 0x71);
			fprintf(fp, "%c", 0x4E); // nop
			fprintf(fp, "%c", 0x71);
			fprintf(fp, "%c", 0x4E); // nop
			fprintf(fp, "%c", 0x71);
			fseek(fp, 0x684A, SEEK_SET);
			fprintf(fp, "%c", 0x4E); // jsr     SetHeadquartersCombatantPosition
			fprintf(fp, "%c", 0xB9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x14);
			fprintf(fp, "%c", 0x15);
			fprintf(fp, "%c", 0x80);
			fprintf(fp, "%c", 0xB2); // cmpa.w  #sub_6A2E,a1
			fprintf(fp, "%c", 0xFC);
			fprintf(fp, "%c", 0x6A);
			fprintf(fp, "%c", 0x2E);
			fprintf(fp, "%c", 0x67); // beq.s   loc_6860
			fprintf(fp, "%c", 0x0A);
			fprintf(fp, "%c", 0x4E); // nop
			fprintf(fp, "%c", 0x71);
			fprintf(fp, "%c", 0x4E); // nop
			fprintf(fp, "%c", 0x71);
			fprintf(fp, "%c", 0x4E); // nop
			fprintf(fp, "%c", 0x71);

			/* SetHeadquartersCombatantPosition */
			fseek(fp, 0x141580, SEEK_SET);
			fprintf(fp, "%c", 0x12); // move.b  (a1)+,d1
			fprintf(fp, "%c", 0x19);
			fprintf(fp, "%c", 0x4E); // jsr     j_SetCombatantX
			fprintf(fp, "%c", 0xB9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x02);
			fprintf(fp, "%c", 0x01);
			fprintf(fp, "%c", 0x08);
			fprintf(fp, "%c", 0x12); // move.b  (a1)+,d1
			fprintf(fp, "%c", 0x19);
			fprintf(fp, "%c", 0x4E); // jmp     j_SetCombatantY
			fprintf(fp, "%c", 0xF9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x02);
			fprintf(fp, "%c", 0x01);
			fprintf(fp, "%c", 0x0C);

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
			fprintf(fp, "%c", (BSprOffset2 & 0xFF000000) / 0x1000000);
			fprintf(fp, "%c", (BSprOffset2 & 0x00FF0000) / 0x10000);
			fprintf(fp, "%c", (BSprOffset2 & 0x0000FF00) / 0x100);
			fprintf(fp, "%c", (BSprOffset2 & 0x000000FF));
			fprintf(fp, "%c", 0xD0); // adda.w  d0,a0
			fprintf(fp, "%c", 0xC0);
			fprintf(fp, "%c", 0xD0); // adda.w  d0,a0
			fprintf(fp, "%c", 0xC0);
			fprintf(fp, "%c", 0x4E); // rts
			fprintf(fp, "%c", 0x75);

			/* CalculateInitialStatValue */
			fseek(fp, 0x24A1A, SEEK_SET);
			fprintf(fp, "%c", 0x4E); // jsr     ApplyGrowthTargetToInitialStatValue
			fprintf(fp, "%c", 0xB9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x14);
			fprintf(fp, "%c", 0x17);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x4E); // nop
			fprintf(fp, "%c", 0x71);
			fprintf(fp, "%c", 0x4E); // nop
			fprintf(fp, "%c", 0x71);
			fprintf(fp, "%c", 0x4E); // nop
			fprintf(fp, "%c", 0x71);

			/* ApplyGrowthTargetToInitialStatValue */
			fseek(fp, 0x141700, SEEK_SET);
			fprintf(fp, "%c", 0x32); // move.w  d2,d1
			fprintf(fp, "%c", 0x02);
			fprintf(fp, "%c", 0x02); // andi.w  #GROWTH_MASK_VALUE,d1
			fprintf(fp, "%c", 0x41);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x3F);
			fprintf(fp, "%c", 0x67); // beq.s   @return
			fprintf(fp, "%c", 0x10);
			fprintf(fp, "%c", 0x4E); // jsr     CalculateGrowthTarget
			fprintf(fp, "%c", 0xB9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x02);
			fprintf(fp, "%c", 0x4A);
			fprintf(fp, "%c", 0x44);
			fprintf(fp, "%c", 0xD8); // add.w   d1,d4
			fprintf(fp, "%c", 0x41);
			fprintf(fp, "%c", 0xC9); // muls.w  #PromotePercent,d4
			fprintf(fp, "%c", 0xFC);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", PromotePercent);
			fprintf(fp, "%c", 0x89); // divs.w  #100,d4
			fprintf(fp, "%c", 0xFC);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x64);
			fprintf(fp, "%c", 0x4E); // rts
			fprintf(fp, "%c", 0x75);

			/* InitializeNewGame */
			if (JogurtLevels) {
				fseek(fp, 0x21B46, SEEK_SET);
				fprintf(fp, "%c", 0x4E); // jsr     j_SetLevel
				fprintf(fp, "%c", 0xB9);
				fprintf(fp, "%c", 0x00);
				fprintf(fp, "%c", 0x02);
				fprintf(fp, "%c", 0x01);
				fprintf(fp, "%c", 0x2C);
			}
			else {
				fseek(fp, 0x21B46, SEEK_SET);
				fprintf(fp, "%c", 0x4E); // jsr     SetLevelIfNotJogurt
				fprintf(fp, "%c", 0xB9);
				fprintf(fp, "%c", 0x00);
				fprintf(fp, "%c", 0x14);
				fprintf(fp, "%c", 0x14);
				fprintf(fp, "%c", 0xC0);

				/* SetLevelIfNotJogurt */
				fseek(fp, 0x1414C0, SEEK_SET);
				fprintf(fp, "%c", 0x0C); // cmpi.b  #ALLY_JOGURT,d0
				fprintf(fp, "%c", 0x00);
				fprintf(fp, "%c", 0x00);
				fprintf(fp, "%c", 0x1D);
				fprintf(fp, "%c", 0x67); // beq.s   @return
				fprintf(fp, "%c", 0x06);
				fprintf(fp, "%c", 0x4E); // jmp     j_SetLevel
				fprintf(fp, "%c", 0xF9);
				fprintf(fp, "%c", 0x00);
				fprintf(fp, "%c", 0x02);
				fprintf(fp, "%c", 0x01);
				fprintf(fp, "%c", 0x2C);
				fprintf(fp, "%c", 0x4E); // rts
				fprintf(fp, "%c", 0x75);
			}

		}
		else {

			CharOffset = 0x25154;
			BSprOffset = 0x25604;
			UStatOffset = 0x26C1A;
			PStatOffset = 0x26CCE;

			/* GetPortrait */
			fseek(fp, 0x239E4, SEEK_SET);
			fprintf(fp, "%c", 0x6C); // bge.s   @ForceMember
			fprintf(fp, "%c", 0x0C);
			fseek(fp, 0x23A0A, SEEK_SET);
			fprintf(fp, "%c", 0x42); // clr.w   d1
			fprintf(fp, "%c", 0x41);
			fprintf(fp, "%c", 0x12); // move.b  d0,d1
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x61); // bsr.w   IsPromoted
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x10);
			fprintf(fp, "%c", 0xCA);
			fprintf(fp, "%c", 0x67); // beq.s   @Done
			fprintf(fp, "%c", 0x04);
			fprintf(fp, "%c", 0x12); // move.b  table_PromotedPortraits(pc,d1.w),d1
			fprintf(fp, "%c", 0x3B);
			fprintf(fp, "%c", 0x10);
			fprintf(fp, "%c", 0x08);

			/* table_Portraits2 */
			fseek(fp, 0x23A1E, SEEK_SET);
			for (int i = 0; i < EXT_CHARS; i++) {
				fprintf(fp, "%c", (CharPortrait2[i]));
			}

			/* InitializeHeadquarters */
			fseek(fp, 0x6808, SEEK_SET);
			fprintf(fp, "%c", 0x42); // clr.w   d2
			fprintf(fp, "%c", 0x42);
			fprintf(fp, "%c", 0x14); // move.b  (a1)+,d2
			fprintf(fp, "%c", 0x19);
			fprintf(fp, "%c", 0x4E); // jsr     j_SetEntityIndex
			fprintf(fp, "%c", 0xB9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x02);
			fprintf(fp, "%c", 0x01);
			fprintf(fp, "%c", 0x04);
			fprintf(fp, "%c", 0x4E); // jsr     LoadHeadquartersMapsprite(pc)
			fprintf(fp, "%c", 0xBA);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x88);
			fseek(fp, 0x6808, SEEK_SET);
			fprintf(fp, "%c", 0x42); // clr.w   d2
			fprintf(fp, "%c", 0x42);
			fprintf(fp, "%c", 0x14); // move.b  (a1)+,d2
			fprintf(fp, "%c", 0x19);
			fprintf(fp, "%c", 0x4E); // jsr     j_SetEntityIndex
			fprintf(fp, "%c", 0xB9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x02);
			fprintf(fp, "%c", 0x01);
			fprintf(fp, "%c", 0x04);
			fprintf(fp, "%c", 0x4E); // jsr     LoadHeadquartersMapsprite(pc)
			fprintf(fp, "%c", 0xBA);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x54);

			/* GetMapsprite */
			fseek(fp, 0x23A56, SEEK_SET);
			fprintf(fp, "%c", 0x6C); // bge.s   @ForceMember
			fprintf(fp, "%c", 0x0C);
			fseek(fp, 0x23A7C, SEEK_SET);
			fprintf(fp, "%c", 0x61); // bsr.s   ApplyOutfitItems
			fprintf(fp, "%c", 0x16);
			fprintf(fp, "%c", 0x64); // bcc.s   @Done
			fprintf(fp, "%c", 0x0E);
			fprintf(fp, "%c", 0x42); // clr.w   d1
			fprintf(fp, "%c", 0x41);
			fprintf(fp, "%c", 0x12); // move.b  d0,d1
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x61); // bsr.w   IsPromoted
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x10);
			fprintf(fp, "%c", 0x54);
			fprintf(fp, "%c", 0x67); // beq.s   @Done
			fprintf(fp, "%c", 0x04);
			fprintf(fp, "%c", 0x06); // addi.w  #PROMOTED_MAPSPRITES_START,d1
			fprintf(fp, "%c", 0x41);
			fprintf(fp, "%c", (PromotedMapspritesStart & 0xFF00) / 0x100);
			fprintf(fp, "%c", (PromotedMapspritesStart & 0x00FF));

			/* InitializeNewGame */
			fseek(fp, 0x21B3C, SEEK_SET);
			fprintf(fp, "%c", 0x4E); // jsr     j_GetLevel
			fprintf(fp, "%c", 0xB9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x02);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x7C);
			fseek(fp, 0x21B46, SEEK_SET);
			fprintf(fp, "%c", 0x4E); // jsr     j_SetLevel
			fprintf(fp, "%c", 0xB9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x02);
			fprintf(fp, "%c", 0x01);
			fprintf(fp, "%c", 0x2C);

			/* InitializeHeadquarters */
			fseek(fp, 0x6816, SEEK_SET);
			fprintf(fp, "%c", 0x4E); // nop
			fprintf(fp, "%c", 0x71);
			fprintf(fp, "%c", 0x12); // move.b  (a1)+,d1
			fprintf(fp, "%c", 0x19);
			fprintf(fp, "%c", 0x4E); // jsr     j_SetCombatantX
			fprintf(fp, "%c", 0xB9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x02);
			fprintf(fp, "%c", 0x01);
			fprintf(fp, "%c", 0x08);
			fprintf(fp, "%c", 0x12); // move.b  (a1)+,d1
			fprintf(fp, "%c", 0x19);
			fprintf(fp, "%c", 0x4E); // jsr     j_SetCombatantY
			fprintf(fp, "%c", 0xB9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x02);
			fprintf(fp, "%c", 0x01);
			fprintf(fp, "%c", 0x0C);
			fseek(fp, 0x684A, SEEK_SET);
			fprintf(fp, "%c", 0x4E); // nop
			fprintf(fp, "%c", 0x71);
			fprintf(fp, "%c", 0x12); // move.b  (a1)+,d1
			fprintf(fp, "%c", 0x19);
			fprintf(fp, "%c", 0x4E); // jsr     j_SetCombatantX
			fprintf(fp, "%c", 0xB9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x02);
			fprintf(fp, "%c", 0x01);
			fprintf(fp, "%c", 0x08);
			fprintf(fp, "%c", 0x12); // move.b  (a1)+,d1
			fprintf(fp, "%c", 0x19);
			fprintf(fp, "%c", 0x4E); // jsr     j_SetCombatantY
			fprintf(fp, "%c", 0xB9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x02);
			fprintf(fp, "%c", 0x01);
			fprintf(fp, "%c", 0x0C);

			/* LoadBattlespriteAndPaletteIndexes */
			fseek(fp, 0x23B60, SEEK_SET);
			fprintf(fp, "%c", 0x20); // movea.l (p_BattlespriteData).l,a0
			fprintf(fp, "%c", 0x79);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x02);
			fprintf(fp, "%c", 0x03);
			fprintf(fp, "%c", 0xAC);
			fprintf(fp, "%c", 0xD0); // adda.w  d0,a0
			fprintf(fp, "%c", 0xC0);
			fprintf(fp, "%c", 0xD0); // adda.w  d0,a0
			fprintf(fp, "%c", 0xC0);
			fprintf(fp, "%c", 0x12); // move.b  (a0)+,d1
			fprintf(fp, "%c", 0x18);
			fprintf(fp, "%c", 0x14); // move.b  (a0),d2
			fprintf(fp, "%c", 0x10);
			fprintf(fp, "%c", 0x61); // bsr.w   IsPromoted
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x0F);
			fprintf(fp, "%c", 0x6A);
			fprintf(fp, "%c", 0x67); // beq.s   @Load
			fprintf(fp, "%c", 0x04);
			fprintf(fp, "%c", 0x06); // addi.w  #PROMOTED_BATTLESPRITES_START,d1
			fprintf(fp, "%c", 0x41);
			fprintf(fp, "%c", (PromotedBattlespritesStart & 0xFF00) / 0x100);
			fprintf(fp, "%c", (PromotedBattlespritesStart & 0x00FF));

			/* CalculateInitialStatValue */
			fseek(fp, 0x24A1A, SEEK_SET);
			fprintf(fp, "%c", 0x61); // bsr.s   CalculateGrowthTarget
			fprintf(fp, "%c", 0x28);
			fprintf(fp, "%c", 0xD8); // add.w   d1,d4
			fprintf(fp, "%c", 0x41);
			fprintf(fp, "%c", 0xC9); // muls.w  #85,d4
			fprintf(fp, "%c", 0xFC);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x55);
			fprintf(fp, "%c", 0x89); // divs.w  #100,d4
			fprintf(fp, "%c", 0xFC);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x64);

		}


		/* Extend Save File */
		if (NumCombatants == MAX_COMBATANTS) {

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
			fprintf(fp, "%c", 0x48); // movem.l d0-d1,-(sp)
			fprintf(fp, "%c", 0xE7);
			fprintf(fp, "%c", 0xC0);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x0C); // cmpi.b  #32,d0
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x20);
			fprintf(fp, "%c", 0x6C); // bge.s   loc_141416
			fprintf(fp, "%c", 0x0C);
			fprintf(fp, "%c", 0x22); // move.l  ((FORCE_MEMBER_FLAGS-$1000000)).w,d1
			fprintf(fp, "%c", 0x38);
			fprintf(fp, "%c", (ForceFlagsAddress & 0xFF00) / 0x100);
			fprintf(fp, "%c", (ForceFlagsAddress & 0x00FF));
			fprintf(fp, "%c", 0x01); // btst    d0,d1
			fprintf(fp, "%c", 0x01);
			fprintf(fp, "%c", 0x4C); // movem.l (sp)+,d0-d1
			fprintf(fp, "%c", 0xDF);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x03);
			fprintf(fp, "%c", 0x4E); // rts
			fprintf(fp, "%c", 0x75);
			fprintf(fp, "%c", 0x04); // subi.b  #32,d0
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x20);
			fprintf(fp, "%c", 0x22); // move.l  ((FORCE_MEMBER_FLAGS_2-$1000000)).w,d1
			fprintf(fp, "%c", 0x38);
			fprintf(fp, "%c", (ExtendedForceFlagsAddress & 0xFF00) / 0x100);
			fprintf(fp, "%c", (ExtendedForceFlagsAddress & 0x00FF));
			fprintf(fp, "%c", 0x01); // btst    d0,d1
			fprintf(fp, "%c", 0x01);
			fprintf(fp, "%c", 0x4C); // movem.l (sp)+,d0-d1
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
			fprintf(fp, "%c", 0x0C); // cmpi.b  #32,d0
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x20);
			fprintf(fp, "%c", 0x6C); // bge.s   loc_141452
			fprintf(fp, "%c", 0x0C);
			fprintf(fp, "%c", 0x22); // move.l  ((FORCE_MEMBER_FLAGS-$1000000)).w,d1
			fprintf(fp, "%c", 0x38);
			fprintf(fp, "%c", (ForceFlagsAddress & 0xFF00) / 0x100);
			fprintf(fp, "%c", (ForceFlagsAddress & 0x00FF));
			fprintf(fp, "%c", 0x01); // bset    d0,d1
			fprintf(fp, "%c", 0xC1);
			fprintf(fp, "%c", 0x21); // move.l  d1,((FORCE_MEMBER_FLAGS-$1000000)).w
			fprintf(fp, "%c", 0xC1);
			fprintf(fp, "%c", (ForceFlagsAddress & 0xFF00) / 0x100);
			fprintf(fp, "%c", (ForceFlagsAddress & 0x00FF));
			fprintf(fp, "%c", 0x4E); // rts
			fprintf(fp, "%c", 0x75);
			fprintf(fp, "%c", 0x04); // subi.b  #32,d0
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x20);
			fprintf(fp, "%c", 0x22); // move.l  ((FORCE_MEMBER_FLAGS_2-$1000000)).w,d1
			fprintf(fp, "%c", 0x38);
			fprintf(fp, "%c", (ExtendedForceFlagsAddress & 0xFF00) / 0x100);
			fprintf(fp, "%c", (ExtendedForceFlagsAddress & 0x00FF));
			fprintf(fp, "%c", 0x01); // bset    d0,d1
			fprintf(fp, "%c", 0xC1);
			fprintf(fp, "%c", 0x21); // move.l  d1,((FORCE_MEMBER_FLAGS_2-$1000000)).w
			fprintf(fp, "%c", 0xC1);
			fprintf(fp, "%c", (ExtendedForceFlagsAddress & 0xFF00) / 0x100);
			fprintf(fp, "%c", (ExtendedForceFlagsAddress & 0x00FF));
			fprintf(fp, "%c", 0x06); // addi.b  #32,d0
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x20);
			fprintf(fp, "%c", 0x4E); // rts
			fprintf(fp, "%c", 0x75);

			/* InitializeNewGame */
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
			fprintf(fp, "%c", (ExtendedForceFlagsAddress & 0xFF00) / 0x100);
			fprintf(fp, "%c", (ExtendedForceFlagsAddress & 0x00FF));
			fprintf(fp, "%c", 0x4E); // jmp     j_GetLevel
			fprintf(fp, "%c", 0xF9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x02);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x7C);

			if (ExtendEventFlags) {
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
				fprintf(fp, "%c", 0x0C); // cmpi.b  #68,d1
				fprintf(fp, "%c", 0x01);
				fprintf(fp, "%c", 0x00); // bge.s   loc_14150E
				fprintf(fp, "%c", 0x44);
				fprintf(fp, "%c", 0x6C); // lea     (EVENT_FLAGS).l,a1
				fprintf(fp, "%c", 0x08);
				fprintf(fp, "%c", 0x43);
				fprintf(fp, "%c", 0xF9);
				fprintf(fp, "%c", 0x00);
				fprintf(fp, "%c", 0xFF);
				fprintf(fp, "%c", 0x9C);
				fprintf(fp, "%c", 0x4E);
				fprintf(fp, "%c", 0x4E); // rts
				fprintf(fp, "%c", 0x75);
				fprintf(fp, "%c", 0x43); // lea     ($FFEFDC).l,a1
				fprintf(fp, "%c", 0xF9);
				fprintf(fp, "%c", 0x00);
				fprintf(fp, "%c", 0xFF);
				fprintf(fp, "%c", 0xEF);
				fprintf(fp, "%c", 0xDC);
				fprintf(fp, "%c", 0x4E); // rts
				fprintf(fp, "%c", 0x75);
			}

			/* CopyBytesToSram */
			fseek(fp, 0x37BA, SEEK_SET);
			fprintf(fp, "%c", 0x66); // bne.w   return_3772
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0xB6);
			fseek(fp, 0x37D0, SEEK_SET);
			fprintf(fp, "%c", 0x4E); // jsr     CopyExtendedBytesToSram
			fprintf(fp, "%c", 0xF9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x14);
			fprintf(fp, "%c", 0x16);
			fprintf(fp, "%c", 0x00);

			/* CopyExtendedBytesToSram */
			fseek(fp, 0x141600, SEEK_SET);
			fprintf(fp, "%c", 0x12); // move.b  d0,(a1)
			fprintf(fp, "%c", 0x80);
			fprintf(fp, "%c", 0x54); // addq.l  #2,a1
			fprintf(fp, "%c", 0x89);
			fprintf(fp, "%c", 0x30); // move.w  ((CURRENT_SAVE_SLOT-$1000000)).w,d0
			fprintf(fp, "%c", 0x38);
			fprintf(fp, "%c", 0xC0);
			fprintf(fp, "%c", 0xB8);
			fprintf(fp, "%c", 0x66); // bne.s   loc_141612
			fprintf(fp, "%c", 0x08);
			fprintf(fp, "%c", 0x43); // lea     ($204000).l,a1
			fprintf(fp, "%c", 0xF9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x20);
			fprintf(fp, "%c", 0x40);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x60); // bra.s   loc_141626
			fprintf(fp, "%c", 0x14);
			fprintf(fp, "%c", 0x0C); // cmpi.w  #1,d0
			fprintf(fp, "%c", 0x40);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x01);
			fprintf(fp, "%c", 0x66); // bne.s   loc_141620
			fprintf(fp, "%c", 0x08);
			fprintf(fp, "%c", 0x43); // lea     ($208000).l,a1
			fprintf(fp, "%c", 0xF9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x20);
			fprintf(fp, "%c", 0x80);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x60); // bra.s   loc_141626
			fprintf(fp, "%c", 0x06);
			fprintf(fp, "%c", 0x43); // lea     ($20C000).l,a1
			fprintf(fp, "%c", 0xF9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x20);
			fprintf(fp, "%c", 0xC0);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x41); // lea     (FORCE_MEMBERS_DATA).l,a0
			fprintf(fp, "%c", 0xF9);
			fprintf(fp, "%c", (ForceMembersDataAddress & 0xFF000000) / 0x1000000);
			fprintf(fp, "%c", (ForceMembersDataAddress & 0x00FF0000) / 0x10000);
			fprintf(fp, "%c", (ForceMembersDataAddress & 0x0000FF00) / 0x100);
			fprintf(fp, "%c", (ForceMembersDataAddress & 0x000000FF));
			fprintf(fp, "%c", 0x3E); // move.w  #(MAX_CHARS*40)-1,d7
			fprintf(fp, "%c", 0x3C);
			fprintf(fp, "%c", ((ForceMembersDataByteSize - 1) & 0xFF00) / 0x100);
			fprintf(fp, "%c", ((ForceMembersDataByteSize - 1) & 0x00FF));
			fprintf(fp, "%c", 0x12); // move.b  (a0)+,d1
			fprintf(fp, "%c", 0x18);
			fprintf(fp, "%c", 0x12); // move.b  d1,(a1)+
			fprintf(fp, "%c", 0xC1);
			fprintf(fp, "%c", 0x51); // dbf     d7,loc_141630
			fprintf(fp, "%c", 0xCF);
			fprintf(fp, "%c", 0xFF);
			fprintf(fp, "%c", 0xFA);
			fprintf(fp, "%c", 0x41); // lea     (PROMOTED_AT_LEVELS).l,a0
			fprintf(fp, "%c", 0xF9);
			fprintf(fp, "%c", (PromotedAtLevelsAddress & 0xFF000000) / 0x1000000);
			fprintf(fp, "%c", (PromotedAtLevelsAddress & 0x00FF0000) / 0x10000);
			fprintf(fp, "%c", (PromotedAtLevelsAddress & 0x0000FF00) / 0x100);
			fprintf(fp, "%c", (PromotedAtLevelsAddress & 0x000000FF));
			fprintf(fp, "%c", 0x3E); // move.w  #NumChars-1,d7
			fprintf(fp, "%c", 0x3C);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", NumChars - 1);
			fprintf(fp, "%c", 0x12); // move.b  (a0)+,d1
			fprintf(fp, "%c", 0x18);
			fprintf(fp, "%c", 0x12); // move.b  d1,(a1)+
			fprintf(fp, "%c", 0xC1);
			fprintf(fp, "%c", 0x51);
			fprintf(fp, "%c", 0xCF); // dbf     d7,loc_141642
			fprintf(fp, "%c", 0xFF);
			fprintf(fp, "%c", 0xFA);
			fprintf(fp, "%c", 0x4E); // rts
			fprintf(fp, "%c", 0x75);

			/* CopyBytesFromSram */
			fseek(fp, 0x37E8, SEEK_SET);
			fprintf(fp, "%c", 0x4E); // jsr     CopyExtendedBytesFromSram
			fprintf(fp, "%c", 0xF9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x14);
			fprintf(fp, "%c", 0x16);
			fprintf(fp, "%c", 0x60);

			/* CopyExtendedBytesFromSram */
			fseek(fp, 0x141660, SEEK_SET);
			fprintf(fp, "%c", 0xB0); // cmp.b   (a1),d0
			fprintf(fp, "%c", 0x11);
			fprintf(fp, "%c", 0x54); // addq.l  #2,a1
			fprintf(fp, "%c", 0x89);
			fprintf(fp, "%c", 0x30); // move.w  ((CURRENT_SAVE_SLOT-$1000000)).w,d0
			fprintf(fp, "%c", 0x38);
			fprintf(fp, "%c", 0xC0);
			fprintf(fp, "%c", 0xB8);
			fprintf(fp, "%c", 0x66); // bne.s   loc_141672
			fprintf(fp, "%c", 0x08);
			fprintf(fp, "%c", 0x41); // lea     ($204000).l,a0
			fprintf(fp, "%c", 0xF9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x20);
			fprintf(fp, "%c", 0x40);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x60); // bra.s   loc_141686
			fprintf(fp, "%c", 0x14);
			fprintf(fp, "%c", 0x0C); // cmpi.w  #1,d0
			fprintf(fp, "%c", 0x40);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x01);
			fprintf(fp, "%c", 0x66); // bne.s   loc_141680
			fprintf(fp, "%c", 0x08);
			fprintf(fp, "%c", 0x41); // lea     ($208000).l,a0
			fprintf(fp, "%c", 0xF9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x20);
			fprintf(fp, "%c", 0x80);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x60); // bra.s   loc_141686
			fprintf(fp, "%c", 0x06);
			fprintf(fp, "%c", 0x41); // lea     ($20C000).l,a0
			fprintf(fp, "%c", 0xF9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x20);
			fprintf(fp, "%c", 0xC0);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x43); // lea     (FORCE_MEMBERS_DATA).l,a1
			fprintf(fp, "%c", 0xF9);
			fprintf(fp, "%c", (ForceMembersDataAddress & 0xFF000000) / 0x1000000);
			fprintf(fp, "%c", (ForceMembersDataAddress & 0x00FF0000) / 0x10000);
			fprintf(fp, "%c", (ForceMembersDataAddress & 0x0000FF00) / 0x100);
			fprintf(fp, "%c", (ForceMembersDataAddress & 0x000000FF));
			fprintf(fp, "%c", 0x3E); // move.w  #(MAX_CHARS*40)-1,d7
			fprintf(fp, "%c", 0x3C);
			fprintf(fp, "%c", ((ForceMembersDataByteSize - 1) & 0xFF00) / 0x100);
			fprintf(fp, "%c", ((ForceMembersDataByteSize - 1) & 0x00FF));
			fprintf(fp, "%c", 0x12); // move.b  (a0)+,d1
			fprintf(fp, "%c", 0x18);
			fprintf(fp, "%c", 0x12); // move.b  d1,(a1)+
			fprintf(fp, "%c", 0xC1);
			fprintf(fp, "%c", 0x51); // dbf     d7,loc_141690
			fprintf(fp, "%c", 0xCF);
			fprintf(fp, "%c", 0xFF);
			fprintf(fp, "%c", 0xFA);
			fprintf(fp, "%c", 0x43); // lea     (PROMOTED_AT_LEVELS).l,a1
			fprintf(fp, "%c", 0xF9);
			fprintf(fp, "%c", (PromotedAtLevelsAddress & 0xFF000000) / 0x1000000);
			fprintf(fp, "%c", (PromotedAtLevelsAddress & 0x00FF0000) / 0x10000);
			fprintf(fp, "%c", (PromotedAtLevelsAddress & 0x0000FF00) / 0x100);
			fprintf(fp, "%c", (PromotedAtLevelsAddress & 0x000000FF));
			fprintf(fp, "%c", 0x3E); // move.w  #143,d7
			fprintf(fp, "%c", 0x3C);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x8F);
			fprintf(fp, "%c", 0x12); // move.b  (a0)+,d1
			fprintf(fp, "%c", 0x18);
			fprintf(fp, "%c", 0x12); // move.b  d1,(a1)+
			fprintf(fp, "%c", 0xC1);
			fprintf(fp, "%c", 0x51); // dbf     d7,loc_1416A2
			fprintf(fp, "%c", 0xCF);
			fprintf(fp, "%c", 0xFF);
			fprintf(fp, "%c", 0xFA);
			fprintf(fp, "%c", 0x4E); // rts
			fprintf(fp, "%c", 0x75);

		}
		else {

			/* IsInForce */
			fseek(fp, 0x220B8, SEEK_SET);
			fprintf(fp, "%c", 0x48); // movem.l d1,-(sp)
			fprintf(fp, "%c", 0xE7);
			fprintf(fp, "%c", 0x40);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x22); // move.l  ((FORCE_MEMBER_FLAGS-$1000000)).w,d1
			fprintf(fp, "%c", 0x38);
			fprintf(fp, "%c", (ForceFlagsAddress & 0xFF00) / 0x100);
			fprintf(fp, "%c", (ForceFlagsAddress & 0x00FF));

			/* dup_IsInForce */
			fseek(fp, 0x221D4, SEEK_SET);
			fprintf(fp, "%c", 0x48); // movem.l d1,-(sp)
			fprintf(fp, "%c", 0xE7);
			fprintf(fp, "%c", 0x40);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x22); // move.l  ((FORCE_MEMBER_FLAGS-$1000000)).w,d1
			fprintf(fp, "%c", 0x38);
			fprintf(fp, "%c", (ForceFlagsAddress & 0xFF00) / 0x100);
			fprintf(fp, "%c", (ForceFlagsAddress & 0x00FF));

			/* JoinForce */
			fseek(fp, 0x221B6, SEEK_SET);
			fprintf(fp, "%c", 0x22); // move.l  ((FORCE_MEMBER_FLAGS-$1000000)).w,d1
			fprintf(fp, "%c", 0x38);
			fprintf(fp, "%c", (ForceFlagsAddress & 0xFF00) / 0x100);
			fprintf(fp, "%c", (ForceFlagsAddress & 0x00FF));
			fprintf(fp, "%c", 0x01); // bset    d0,d1
			fprintf(fp, "%c", 0xC1);
			fprintf(fp, "%c", 0x21); // move.l  d1,((FORCE_MEMBER_FLAGS-$1000000)).w
			fprintf(fp, "%c", 0xC1);
			fprintf(fp, "%c", (ForceFlagsAddress & 0xFF00) / 0x100);
			fprintf(fp, "%c", (ForceFlagsAddress & 0x00FF));

			/* MapTeleports */
			fseek(fp, 0x12D5A, SEEK_SET);
			fprintf(fp, "%c", 0x43); // lea     (EVENT_FLAGS).l,a1
			fprintf(fp, "%c", 0xF9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0xFF);
			fprintf(fp, "%c", 0x9C);
			fprintf(fp, "%c", 0x4E);

			/* CopyBytesToSram */
			fseek(fp, 0x37BA, SEEK_SET);
			fprintf(fp, "%c", 0x66); // bne.w   @return
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x18);
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
		}


		/* Header: SRAM end address */
		fseek(fp, 0x1B8, SEEK_SET);
		fprintf(fp, "%c", (SRAMEndAddress & 0xFF000000) / 0x1000000);
		fprintf(fp, "%c", (SRAMEndAddress & 0x00FF0000) / 0x10000);
		fprintf(fp, "%c", (SRAMEndAddress & 0x0000FF00) / 0x100);
		fprintf(fp, "%c", (SRAMEndAddress & 0x000000FF));

		/* table_InitialForceData */
		fseek(fp, 0x203A8, SEEK_SET);
		fprintf(fp, "%c", (CharOffset & 0xFF000000) / 0x1000000);
		fprintf(fp, "%c", (CharOffset & 0x00FF0000) / 0x10000);
		fprintf(fp, "%c", (CharOffset & 0x0000FF00) / 0x100);
		fprintf(fp, "%c", (CharOffset & 0x000000FF));
		q = NumChars;
		if (q > MIN_CHARS) q = MAX_CHARS;
		fseek(fp, CharOffset, SEEK_SET);
		for (i = 0; i < q; i++) {
			for (j = 0; j < 10; j++) {
				fprintf(fp, "%c", CharName[i][j]);
			}
			CharName[i][10] = 0;
			for (j = 0; j < 30; j++) {
				fprintf(fp, "%c", Char[i][j]);
			}
		}

		/* table_UnpromotedGrowths */
		q = NumChars;
		if (q > MIN_CHARS) q = MAX_CHARS;
		fseek(fp, 0x203EC, SEEK_SET);
		fprintf(fp, "%c", (UStatOffset & 0xFF000000) / 0x1000000);
		fprintf(fp, "%c", (UStatOffset & 0x00FF0000) / 0x10000);
		fprintf(fp, "%c", (UStatOffset & 0x0000FF00) / 0x100);
		fprintf(fp, "%c", (UStatOffset & 0x000000FF));
		for (j = 0; j < q; j++) {
			fseek(fp, UStatOffset + 6 * j, SEEK_SET);
			for (i = 0; i < 6; i++) {
				if (PStatOffset == 0x26CCE && (j == 27 || j == 28)) {
					fprintf(fp, "%c", Stats[j][i + 6]); // Save promoted growths for Musashi and Hanzou
				}
				else {
					fprintf(fp, "%c", Stats[j][i]);
				}
			}
		}

		/* table_PromotedGrowths */
		q = NumChars;
		if (q > MIN_CHARS) {
			q = MAX_CHARS;
		}
		else {
			q = MIN_CHARS - 3;
		}
		fseek(fp, 0x203F0, SEEK_SET);
		fprintf(fp, "%c", (PStatOffset & 0xFF000000) / 0x1000000);
		fprintf(fp, "%c", (PStatOffset & 0x00FF0000) / 0x10000);
		fprintf(fp, "%c", (PStatOffset & 0x0000FF00) / 0x100);
		fprintf(fp, "%c", (PStatOffset & 0x000000FF));
		for (j = 0; j < q; j++) {
			fseek(fp, PStatOffset + 6 * j, SEEK_SET);
			for (i = 0; i < 6; i++) {
					fprintf(fp, "%c", Stats[j][i + 6]);
			}
		}

		/* table_BattlespriteData */
		q = NumChars;
		if (q > MIN_CHARS) q = MAX_CHARS;
		fseek(fp, 0x203AC, SEEK_SET);
		fprintf(fp, "%c", (BSprOffset & 0xFF000000) / 0x1000000);
		fprintf(fp, "%c", (BSprOffset & 0x00FF0000) / 0x10000);
		fprintf(fp, "%c", (BSprOffset & 0x0000FF00) / 0x100);
		fprintf(fp, "%c", (BSprOffset & 0x000000FF));
		fseek(fp, BSprOffset, SEEK_SET);
		for (i = 0; i < q; i++) {
			fprintf(fp, "%c", BattleSprite[i][0]);
			fprintf(fp, "%c", BattleSprite[i][1]);
		}

		if (BSprOffset2 != 0) {
			fseek(fp, BSprOffset2, SEEK_SET);
			for (i = 0; i < q; i++) {
				fprintf(fp, "%c", BattleSprite2[i][0]);
				fprintf(fp, "%c", BattleSprite2[i][1]);
			}
		}

		/* InitializeNewGame */
		q = NumChars;
		if (q == MIN_CHARS) q = NumChars - 1;
		fseek(fp, 0x21B1E, SEEK_SET);
		fprintf(fp, "%c", 0x43); // lea     ((FORCE_MEMBERS_DATA-$1000000)).w,a1
		fprintf(fp, "%c", 0xF8);
		fprintf(fp, "%c", (ForceMembersDataAddress & 0xFF00) / 0x100);
		fprintf(fp, "%c", (ForceMembersDataAddress & 0x00FF));
		fprintf(fp, "%c", 0x30); // move.w  #ForceMembersDataByteSize-1,d0
		fprintf(fp, "%c", 0x3C);
		fprintf(fp, "%c", ((ForceMembersDataByteSize - 1) & 0xFF00) / 0x100);
		fprintf(fp, "%c", ((ForceMembersDataByteSize - 1) & 0x00FF));
		fseek(fp, 0x21B2C, SEEK_SET);
		fprintf(fp, "%c", 0x41); // lea     ((PROMOTED_AT_LEVELS-$1000000)).w,a0
		fprintf(fp, "%c", 0xF8);
		fprintf(fp, "%c", (PromotedAtLevelsAddress & 0xFF00) / 0x100);
		fprintf(fp, "%c", (PromotedAtLevelsAddress & 0x00FF));
		fseek(fp, 0x21B3A, SEEK_SET);
		fprintf(fp, "%c", 0x70); // moveq   #q-1,d0
		fprintf(fp, "%c", q - 1);

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

		/* GetEntityEntryAddress */
		fseek(fp, 0x22600, SEEK_SET);
		fprintf(fp, "%c", 0x41); // lea     ((FORCE_MEMBERS_DATA-$1000000)).w,a0
		fprintf(fp, "%c", 0xF8);
		fprintf(fp, "%c", (ForceMembersDataAddress & 0xFF00) / 0x100);
		fprintf(fp, "%c", (ForceMembersDataAddress & 0x00FF));

		/* CheckSavedGames */
		fseek(fp, 0x1643BA, SEEK_SET);
		fprintf(fp, "%c", 0x41); // lea     ((FORCE_MEMBERS_DATA-$1000000)).w,a0
		fprintf(fp, "%c", 0xF8);
		fprintf(fp, "%c", (ForceMembersDataAddress & 0xFF00) / 0x100);
		fprintf(fp, "%c", (ForceMembersDataAddress & 0x00FF));

		/* ExecuteChurchMenu */
		fseek(fp, 0x17352, SEEK_SET);
		fprintf(fp, "%c", 0x41); // lea     ((PROMOTED_AT_LEVELS-$1000000)).w,a0
		fprintf(fp, "%c", 0xF8);
		fprintf(fp, "%c", (PromotedAtLevelsAddress & 0xFF00) / 0x100);
		fprintf(fp, "%c", (PromotedAtLevelsAddress & 0x00FF));

		/* Promote */
		fseek(fp, 0x24920, SEEK_SET);
		fprintf(fp, "%c", 0x41); // lea     ((PROMOTED_AT_LEVELS-$1000000)).w,a0
		fprintf(fp, "%c", 0xF8);
		fprintf(fp, "%c", (PromotedAtLevelsAddress & 0xFF00) / 0x100);
		fprintf(fp, "%c", (PromotedAtLevelsAddress & 0x00FF));

		/* GetPromotedAtLevel */
		fseek(fp, 0x24AEA, SEEK_SET);
		fprintf(fp, "%c", 0x43); // lea     ((PROMOTED_AT_LEVELS-$1000000)).w,a1
		fprintf(fp, "%c", 0xF8);
		fprintf(fp, "%c", (PromotedAtLevelsAddress & 0xFF00) / 0x100);
		fprintf(fp, "%c", (PromotedAtLevelsAddress & 0x00FF));

		/* CalculateTotalLevel */
		fseek(fp, 0x24B96, SEEK_SET);
		fprintf(fp, "%c", 0x41); // lea     ((PROMOTED_AT_LEVELS-$1000000)).w,a0
		fprintf(fp, "%c", 0xF8);
		fprintf(fp, "%c", (PromotedAtLevelsAddress & 0xFF00) / 0x100);
		fprintf(fp, "%c", (PromotedAtLevelsAddress & 0x00FF));

		/* LoadEndingCreditsForce */
		fseek(fp, 0x26E1E, SEEK_SET);
		fprintf(fp, "%c", 0x45); // lea     (PROMOTED_AT_LEVELS).l,a2
		fprintf(fp, "%c", 0xF9);
		fprintf(fp, "%c", (PromotedAtLevelsAddress & 0xFF000000) / 0x1000000);
		fprintf(fp, "%c", (PromotedAtLevelsAddress & 0x00FF0000) / 0x10000);
		fprintf(fp, "%c", (PromotedAtLevelsAddress & 0x0000FF00) / 0x100);
		fprintf(fp, "%c", (PromotedAtLevelsAddress & 0x000000FF));

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

		/* ResetForceMembersStats */
		fseek(fp, 0x24D12, SEEK_SET);
		fprintf(fp, "%c", 0x70); // moveq   #NumChars-1,d0
		fprintf(fp, "%c", NumChars - 1);

		/* IsItemHeldByForce */
		fseek(fp, 0x24F06, SEEK_SET);
		fprintf(fp, "%c", 0x70); // moveq   #NumChars-1,d0
		fprintf(fp, "%c", NumChars - 1);

		if (ExtendCombatants) {
			/* LoadEndingCutsceneCombatantData */
			/*
			fseek(fp, 0x6A9E, SEEK_SET);
			fprintf(fp, "%c", 0x7E); // moveq   #COMBATANT_ENTRIES_COUNTER,d7 // Number of combatants during the ending overworld cutscene
			fprintf(fp, "%c", NumCombatants - 1);
			*/
			fseek(fp, 0x6AA0, SEEK_SET);
			fprintf(fp, "%c", 0x43); // lea     (COMBATANT_DATA).l,a1
			fprintf(fp, "%c", 0xF9);
			fprintf(fp, "%c", (CombatantDataAddress & 0xFF000000) / 0x1000000);
			fprintf(fp, "%c", (CombatantDataAddress & 0x00FF0000) / 0x10000);
			fprintf(fp, "%c", (CombatantDataAddress & 0x0000FF00) / 0x100);
			fprintf(fp, "%c", (CombatantDataAddress & 0x000000FF));

			/* FindCombatantSlot */
			fseek(fp, 0x73D6, SEEK_SET);
			fprintf(fp, "%c", 0x7E); // moveq   #COMBATANT_ENTRIES_COUNTER,d7
			fprintf(fp, "%c", NumCombatants - 1);

			/* BattleLoop */
			fseek(fp, 0x97FC, SEEK_SET);
			fprintf(fp, "%c", 0x7E); // moveq   #COMBATANT_ENTRIES_COUNTER,d7
			fprintf(fp, "%c", NumCombatants - 1);
			fseek(fp, 0x9802, SEEK_SET);
			fprintf(fp, "%c", 0x70); // moveq   #COMBATANT_ENTRIES_COUNTER,d0
			fprintf(fp, "%c", NumCombatants - 1);
			fseek(fp, 0x9858, SEEK_SET);
			fprintf(fp, "%c", 0x7E); // moveq   #COMBATANT_ENTRIES_COUNTER-1,d7
			fprintf(fp, "%c", NumCombatants - 2);
			fseek(fp, 0x985A, SEEK_SET);
			fprintf(fp, "%c", 0x70); // moveq   #COMBATANT_ENTRIES_COUNTER,d0
			fprintf(fp, "%c", NumCombatants - 1);

			/* Minimap */
			fseek(fp, 0x98A8, SEEK_SET);
			fprintf(fp, "%c", 0x41); // lea     ((COMBATANT_DATA-$1000000)).w,a0
			fprintf(fp, "%c", 0xF8);
			fprintf(fp, "%c", (CombatantDataAddress & 0x0000FF00) / 0x100);
			fprintf(fp, "%c", (CombatantDataAddress & 0x000000FF));
			fseek(fp, 0x98B2, SEEK_SET);
			fprintf(fp, "%c", 0x7E); // moveq   #COMBATANT_ENTRIES_COUNTER,d7
			fprintf(fp, "%c", NumCombatants - 1);
			fseek(fp, 0x98B4, SEEK_SET);
			fprintf(fp, "%c", 0x70); // moveq   #COMBATANT_ENTRIES_COUNTER,d0
			fprintf(fp, "%c", NumCombatants - 1);
			fseek(fp, 0xFB74, SEEK_SET);
			fprintf(fp, "%c", 0x7E); // moveq   #COMBATANT_ENTRIES_COUNTER,d7
			fprintf(fp, "%c", NumCombatants - 1);

			/* UpdateBattlefieldSprites */
			fseek(fp, 0x9940, SEEK_SET);
			fprintf(fp, "%c", 0x41); // lea     ((COMBATANT_DATA-$1000000)).w,a0
			fprintf(fp, "%c", 0xF8);
			fprintf(fp, "%c", (CombatantDataAddress & 0x0000FF00) / 0x100);
			fprintf(fp, "%c", (CombatantDataAddress & 0x000000FF));
			fseek(fp, 0x994A, SEEK_SET);
			fprintf(fp, "%c", 0x7E); // moveq   #COMBATANT_ENTRIES_COUNTER,d7
			fprintf(fp, "%c", NumCombatants - 1);
			fseek(fp, 0x994E, SEEK_SET);
			fprintf(fp, "%c", 0x70); // moveq   #COMBATANT_ENTRIES_COUNTER,d0
			fprintf(fp, "%c", NumCombatants - 1);

			/* StatusScreen */
			fseek(fp, 0x9AA2, SEEK_SET);
			fprintf(fp, "%c", 0x41); // lea     ((COMBATANT_DATA-$1000000)).w,a0
			fprintf(fp, "%c", 0xF8);
			fprintf(fp, "%c", (CombatantDataAddress & 0x0000FF00) / 0x100);
			fprintf(fp, "%c", (CombatantDataAddress & 0x000000FF));

			fseek(fp, 0xA0F2, SEEK_SET);
			fprintf(fp, "%c", 0x41); // lea     ((COMBATANT_DATA-$1000000)).w,a0
			fprintf(fp, "%c", 0xF8);
			fprintf(fp, "%c", (CombatantDataAddress & 0x0000FF00) / 0x100);
			fprintf(fp, "%c", (CombatantDataAddress & 0x000000FF));

			fseek(fp, 0xA776, SEEK_SET);
			fprintf(fp, "%c", 0x41); // lea     ((COMBATANT_DATA-$1000000)).w,a0
			fprintf(fp, "%c", 0xF8);
			fprintf(fp, "%c", (CombatantDataAddress & 0x0000FF00) / 0x100);
			fprintf(fp, "%c", (CombatantDataAddress & 0x000000FF));

			fseek(fp, 0xAB5C, SEEK_SET);
			fprintf(fp, "%c", 0x41); // lea     ((COMBATANT_DATA-$1000000)).w,a0
			fprintf(fp, "%c", 0xF8);
			fprintf(fp, "%c", (CombatantDataAddress & 0x0000FF00) / 0x100);
			fprintf(fp, "%c", (CombatantDataAddress & 0x000000FF));

			/* CheckBattleEnd */
			fseek(fp, 0xACE8, SEEK_SET);
			fprintf(fp, "%c", 0x7E); // moveq   #COMBATANT_ENTRIES_COUNTER,d7
			fprintf(fp, "%c", NumCombatants - 1);

			/* BuildMemberStatusScreen */
			fseek(fp, 0xB4B0, SEEK_SET);
			fprintf(fp, "%c", 0x70); // moveq   #COMBATANT_ENTRIES_COUNTER,d0
			fprintf(fp, "%c", NumCombatants - 1);
			fseek(fp, 0xB4E0, SEEK_SET);
			fprintf(fp, "%c", 0x76); // moveq   #COMBATANT_ENTRIES_COUNTER,d3
			fprintf(fp, "%c", NumCombatants - 1);

			fseek(fp, 0xB54C, SEEK_SET);
			fprintf(fp, "%c", 0x45); // lea     ((COMBATANT_DATA-$1000000)).w,a2
			fprintf(fp, "%c", 0xF8);
			fprintf(fp, "%c", (CombatantDataAddress & 0x0000FF00) / 0x100);
			fprintf(fp, "%c", (CombatantDataAddress & 0x000000FF));

			/* BlockSpacesOccupiedByOpponents */
			fseek(fp, 0x20546, SEEK_SET);
			fprintf(fp, "%c", 0x30); // move.w  #NumCombatants-1,d0
			fprintf(fp, "%c", 0x3C);
			fprintf(fp, "%c", ((NumCombatants - 1) & 0xFF00) / 0x100);
			fprintf(fp, "%c", ((NumCombatants - 1) & 0x00FF));

			/* ClearAllowedToStayAtFlags */
			fseek(fp, 0x205EA, SEEK_SET);
			fprintf(fp, "%c", 0x30); // move.w  #NumCombatants-1,d0
			fprintf(fp, "%c", 0x3C);
			fprintf(fp, "%c", ((NumCombatants - 1) & 0xFF00) / 0x100);
			fprintf(fp, "%c", ((NumCombatants - 1) & 0x00FF));

			/* BlockAllOccupiedSpaces */
			fseek(fp, 0x2092E, SEEK_SET);
			fprintf(fp, "%c", 0x70); // moveq   #COMBATANT_ENTRIES_COUNTER,d0
			fprintf(fp, "%c", NumCombatants - 1);

			/* IsSpaceOccupied */
			fseek(fp, 0x2092E, SEEK_SET);
			fprintf(fp, "%c", 0x70); // moveq   #COMBATANT_ENTRIES_COUNTER,d0
			fprintf(fp, "%c", NumCombatants - 1);

			/* RegenerateHp */
			fseek(fp, 0x2092E, SEEK_SET);
			fprintf(fp, "%c", 0x74); // moveq   #COMBATANT_ENTRIES_COUNTER,d2
			fprintf(fp, "%c", NumCombatants - 1);

			/* ClearCombatantData */
			fseek(fp, 0x21BE0, SEEK_SET);
			fprintf(fp, "%c", 0x41); // lea     ((COMBATANT_DATA-$1000000)).w,a0
			fprintf(fp, "%c", 0xF8);
			fprintf(fp, "%c", (CombatantDataAddress & 0x0000FF00) / 0x100);
			fprintf(fp, "%c", (CombatantDataAddress & 0x000000FF));

			/* alt_GetEntity */
			fseek(fp, 0x225B8, SEEK_SET);
			fprintf(fp, "%c", 0x41); // lea     ((COMBATANT_DATA-$1000000)).w,a0
			fprintf(fp, "%c", 0xF8);
			fprintf(fp, "%c", (CombatantDataAddress & 0x0000FF00) / 0x100);
			fprintf(fp, "%c", (CombatantDataAddress & 0x000000FF));

			/* FindCombatantEntry */
			fseek(fp, 0x225CA, SEEK_SET);
			fprintf(fp, "%c", 0x70); // moveq   #COMBATANT_ENTRIES_COUNTER,d0
			fprintf(fp, "%c", NumCombatants - 1);
			fseek(fp, 0x225CE, SEEK_SET);
			fprintf(fp, "%c", 0x70); // moveq   #COMBATANT_ENTRIES_COUNTER,d0
			fprintf(fp, "%c", NumCombatants - 1);

			/* GetCombatantEntryAddress */
			fseek(fp, 0x225E6, SEEK_SET);
			fprintf(fp, "%c", 0x41); // lea     ((COMBATANT_DATA-$1000000)).w,a0
			fprintf(fp, "%c", 0xF8);
			fprintf(fp, "%c", (CombatantDataAddress & 0x0000FF00) / 0x100);
			fprintf(fp, "%c", (CombatantDataAddress & 0x000000FF));

			/* PopulateTargetsList */
			fseek(fp, 0x23810, SEEK_SET);
			fprintf(fp, "%c", 0x70); // moveq   #COMBATANT_ENTRIES_COUNTER,d0
			fprintf(fp, "%c", NumCombatants - 1);

			/* TriggerAiRegions */
			fseek(fp, 0x24266, SEEK_SET);
			fprintf(fp, "%c", 0x70); // moveq   #COMBATANT_ENTRIES_COUNTER,d0
			fprintf(fp, "%c", NumCombatants - 1);

			/* ClearTerrainAtOccupiedSpaces */
			fseek(fp, 0x250E2, SEEK_SET);
			fprintf(fp, "%c", 0x70); // moveq   #COMBATANT_ENTRIES_COUNTER,d0
			fprintf(fp, "%c", NumCombatants - 1);

			/* FindEntityForCutscene */
			/*
			fseek(fp, 0x12BFB8, SEEK_SET);
			fprintf(fp, "%c", 0x7E); // moveq   #COMBATANT_ENTRIES_COUNTER,d7
			fprintf(fp, "%c", NumCombatants - 1);
			*/

			/* WasEntityKilledByLastAttack */
			fseek(fp, 0x12BFD0, SEEK_SET);
			fprintf(fp, "%c", 0x7E); // moveq   #COMBATANT_ENTRIES_COUNTER,d7
			fprintf(fp, "%c", NumCombatants - 1);

			/* KillChosenEnemies */
			fseek(fp, 0x12C1BA, SEEK_SET);
			fprintf(fp, "%c", 0x7E); // moveq   #COMBATANT_ENTRIES_COUNTER,d7
			fprintf(fp, "%c", NumCombatants - 1);

			/* mainMenuAction_Talk */
			fseek(fp, 0x5A88, SEEK_SET);
			fprintf(fp, "%c", 0x0C); // cmpi.b  #ALLY_NOVA,((COMBATANT_1_ENTITY-$1000000)).w
			fprintf(fp, "%c", 0x38);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x1E);
			fprintf(fp, "%c", ((CombatantDataAddress + 16) & 0x0000FF00) / 0x100);
			fprintf(fp, "%c", ((CombatantDataAddress + 16) & 0x000000FF));

			fseek(fp, 0x9824, SEEK_SET);
			fprintf(fp, "%c", 0x0C); // cmpi.b  #ALLY_NOVA,((COMBATANT_1_ENTITY-$1000000)).w
			fprintf(fp, "%c", 0x38);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x1E);
			fprintf(fp, "%c", ((CombatantDataAddress + 16) & 0x0000FF00) / 0x100);
			fprintf(fp, "%c", ((CombatantDataAddress + 16) & 0x000000FF));

			fseek(fp, 0xA144, SEEK_SET);
			fprintf(fp, "%c", 0x0C); // cmpi.b  #ALLY_NOVA,((COMBATANT_1_ENTITY-$1000000)).w
			fprintf(fp, "%c", 0x38);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x1E);
			fprintf(fp, "%c", ((CombatantDataAddress + 16) & 0x0000FF00) / 0x100);
			fprintf(fp, "%c", ((CombatantDataAddress + 16) & 0x000000FF));

			/* abcs29 */
			fseek(fp, 0x12B69E, SEEK_SET);
			fprintf(fp, "%c", 0x7E); // moveq   #COMBATANT_ENTRIES_COUNTER-1,d7
			fprintf(fp, "%c", NumCombatants - 2);
			fprintf(fp, "%c", 0x43); // lea     ((COMBATANT_1_Y-$1000000)).w,a1
			fprintf(fp, "%c", 0xF8);
			fprintf(fp, "%c", ((CombatantDataAddress + 18) & 0x0000FF00) / 0x100);
			fprintf(fp, "%c", ((CombatantDataAddress + 18) & 0x000000FF));
		}



		/* GrowthCurves */
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