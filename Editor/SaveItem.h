void SaveItem(){
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
		bool newline;
		int next;
		unsigned char r;

		int i;

		fseek(fp, 0x22E84, SEEK_SET);
		if (ExtendEquip) {
			fprintf(fp, "%c", 0xEB);
		} else {
			fprintf(fp, "%c", 0xE9);
		}

		for(i=0;i<NumOutfits;i++){
			for(int j=i-1;j>=0;j--){
				if(ItemOutfits[j+1][0]<ItemOutfits[j][0]){
					r = ItemOutfits[j][0];
					ItemOutfits[j][0] = ItemOutfits[j+1][0];
					ItemOutfits[j+1][0] = r;

					r = ItemOutfits[j][1];
					ItemOutfits[j][1] = ItemOutfits[j+1][1];
					ItemOutfits[j+1][1] = r;

					r = ItemOutfits[j][2];
					ItemOutfits[j][2] = ItemOutfits[j+1][2];
					ItemOutfits[j+1][2] = r;

					r = ItemOutfits[j][3];
					ItemOutfits[j][3] = ItemOutfits[j+1][3];
					ItemOutfits[j+1][3] = r;
				} else break;
			}
		}

		if(NumOutfits>2){
			if(0x1D8000>romsize-1){
				MessageBox(NULL,"Rom is too small, expand rom to save additional outfits.","Error",MB_OK);
				fclose(fp);
				return;
			}
			OutfitOffset = 0x1D8010;

			fseek(fp,0x23A98,SEEK_SET);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0xB9);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x1D);
			fprintf(fp,"%c",0x80);
			fprintf(fp,"%c",0x00);

			fseek(fp,0x23AA5,SEEK_SET);
			fprintf(fp,"%c",0x28);

			fseek(fp,0x23ACE,SEEK_SET);
			fprintf(fp,"%c",0xB0);
			fprintf(fp,"%c",0x19);
			fprintf(fp,"%c",0x60);
			fprintf(fp,"%c",0xCC);

			fseek(fp,0x1D8000,SEEK_SET);
			fprintf(fp,"%c",0x43);
			fprintf(fp,"%c",0xF9);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x1D);
			fprintf(fp,"%c",0x80);
			fprintf(fp,"%c",0x10);
			fprintf(fp,"%c",0xB0);
			fprintf(fp,"%c",0x19);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0x75);
		}

		fseek(fp,OutfitOffset,SEEK_SET);
		for(i=0;i<NumOutfits;i++){
			fprintf(fp,"%c",ItemOutfits[i][0]);
			fprintf(fp,"%c",ItemOutfits[i][1]);
			fprintf(fp,"%c",ItemOutfits[i][2]);
		}
		fprintf(fp,"%c",0xFF);
		fprintf(fp,"%c",0xFF);

		if(BattleOutfits){

			if(0x1D8000>romsize-1){
				MessageBox(NULL,"Rom is too small, expand rom to enable battle outfits.","Error",MB_OK);
				fclose(fp);
				return;
			}

			fseek(fp,0x12632C,SEEK_SET);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0xB9);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x1D);
			fprintf(fp,"%c",0x81);
			fprintf(fp,"%c",0x00);

			fseek(fp,0x1262D4,SEEK_SET);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0xB9);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x1D);
			fprintf(fp,"%c",0x81);
			fprintf(fp,"%c",0x00);

			fseek(fp,0x1D8100,SEEK_SET);
			//fprintf(fp,"%c",0x54);
			//fprintf(fp,"%c",0x48);
			fprintf(fp,"%c",0x48);
			fprintf(fp,"%c",0xE7);
			fprintf(fp,"%c",0x40);
			fprintf(fp,"%c",0xC0);
			fprintf(fp,"%c",0x48);
			fprintf(fp,"%c",0xE7);
			fprintf(fp,"%c",0x80);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x30);
			fprintf(fp,"%c",0x38);
			fprintf(fp,"%c",0xBC);
			fprintf(fp,"%c",0x74);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0xB9);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x02);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x54);
			fprintf(fp,"%c",0x10);
			fprintf(fp,"%c",0x01);
			fprintf(fp,"%c",0x43);
			fprintf(fp,"%c",0xF9);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x1D);
			fprintf(fp,"%c",0x81);
			fprintf(fp,"%c",0x80);

			fprintf(fp,"%c",0xB2);
			fprintf(fp,"%c",0x19);
			fprintf(fp,"%c",0x65);
			fprintf(fp,"%c",0x30);
			fprintf(fp,"%c",0x67);
			fprintf(fp,"%c",0x04);
			fprintf(fp,"%c",0x54);
			fprintf(fp,"%c",0x89);
			fprintf(fp,"%c",0x60);
			fprintf(fp,"%c",0xF6);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0xB9);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x02);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0xE4);
			fprintf(fp,"%c",0x72);
			fprintf(fp,"%c",0x03);
			fprintf(fp,"%c",0x14);
			fprintf(fp,"%c",0x18);
			fprintf(fp,"%c",0x02);
			fprintf(fp,"%c",0x02);
			fprintf(fp,"%c",0x00);
			if (NumItems == 128) {
				fprintf(fp, "%c", 0x7F);
			} else {
				fprintf(fp, "%c", 0x3F);
			}

			fprintf(fp,"%c",0xB4);
			fprintf(fp,"%c",0x11);
			fprintf(fp,"%c",0x66);
			fprintf(fp,"%c",0x14);
			fprintf(fp,"%c",0x42);
			fprintf(fp,"%c",0x40);
			fprintf(fp,"%c",0x10);
			fprintf(fp,"%c",0x29);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x01);
			fprintf(fp,"%c",0x58);
			fprintf(fp,"%c",0x8F);
			fprintf(fp,"%c",0x4C);
			fprintf(fp,"%c",0xDF);
			fprintf(fp,"%c",0x03);
			fprintf(fp,"%c",0x02);

			fprintf(fp,"%c",0xE5);
			fprintf(fp,"%c",0x48);
			fprintf(fp,"%c",0x20);
			fprintf(fp,"%c",0x70);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x00);

			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0x75);
			fprintf(fp,"%c",0x51);
			fprintf(fp,"%c",0xC9);
			fprintf(fp,"%c",0xFF);
			fprintf(fp,"%c",0xE0);
			fprintf(fp,"%c",0x4C);
			fprintf(fp,"%c",0xDF);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x01);
			fprintf(fp,"%c",0x4C);
			fprintf(fp,"%c",0xDF);
			fprintf(fp,"%c",0x03);
			fprintf(fp,"%c",0x02);
			fprintf(fp,"%c",0xE5);
			fprintf(fp,"%c",0x48);
			fprintf(fp,"%c",0x20);
			fprintf(fp,"%c",0x70);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0x75);

			fseek(fp,0x1D8180,SEEK_SET);
			for(i=0;i<NumOutfits;i++){
				fprintf(fp,"%c",ItemOutfits[i][0]);
				fprintf(fp,"%c",ItemOutfits[i][1]);
				fprintf(fp,"%c",ItemOutfits[i][3]);
			}
			fprintf(fp,"%c",0xFF);
			fprintf(fp,"%c",0xFF);
		} else {
			fseek(fp,0x12632C,SEEK_SET);
			fprintf(fp,"%c",0xE5);
			fprintf(fp,"%c",0x48);
			fprintf(fp,"%c",0x20);
			fprintf(fp,"%c",0x70);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x00);

			fseek(fp,0x1262D4,SEEK_SET);
			fprintf(fp,"%c",0xE5);
			fprintf(fp,"%c",0x48);
			fprintf(fp,"%c",0x20);
			fprintf(fp,"%c",0x70);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x00);
		}

		if(NumItems==128){
			ItemNameOffset = 0x1AC800;
			ItemOffset = 0x1E1000;
			ItemIconOffset = 0x1B7000;
			ItemTypeOffset = 0x1AD800;
			ItemWSOffset = 0x1AD880;
		}

		if(ItemNameOffset>romsize-1){
			MessageBox(NULL,"Rom is too small, expand rom to save extended items.","Error",MB_OK);
			fclose(fp);
			return;
		}

		fseek(fp,132016,SEEK_SET);
		fprintf(fp,"%c",(ItemNameOffset&0xFF000000)/0x1000000);
		fprintf(fp,"%c",(ItemNameOffset&0x00FF0000)/0x10000);
		fprintf(fp,"%c",(ItemNameOffset&0x0000FF00)/0x100);
		fprintf(fp,"%c",(ItemNameOffset&0x000000FF));

		fseek(fp,ItemNameOffset,SEEK_SET);
		for(i=0; i<63; i++){
			fprintf(fp,"%c",strlen(ItemName[i]));
			newline=false;
			for(int j=0; j<strlen(ItemName[i]); j++){
				next=0;
				if(ItemName[i][j]==32&&!newline&&strlen(ItemName[i])>8){
					for(int k=j+1; k<strlen(ItemName[i]); k++){
						if(ItemName[i][k]==32){
							next=k;
							k=strlen(ItemName[i]);
						}
					}
					if(next==0||next>9){
						newline=true;
						fprintf(fp,"%c",9);
					} else fprintf(fp,"%c",ItemName[i][j]);
				} else fprintf(fp,"%c",ItemName[i][j]);
			}
		}
		if(NumItems==128){
			fprintf(fp,"%c",0);
			for(i=0; i<63; i++){
				fprintf(fp,"%c",strlen(ItemName[i+64]));
				newline=false;
				for(int j=0; j<strlen(ItemName[i+64]); j++){
					next=0;
					if(ItemName[i+64][j]==32&&!newline&&strlen(ItemName[i+64])>8){
						for(int k=j+1; k<strlen(ItemName[i+64]); k++){
							if(ItemName[i+64][k]==32){
								next=k;
								k=strlen(ItemName[i+64]);
							}
						}
						if(next==0||next>9){
							newline=true;
							fprintf(fp,"%c",9);
						} else fprintf(fp,"%c",ItemName[i+64][j]);
					} else fprintf(fp,"%c",ItemName[i+64][j]);
				}
			}
		}

		fseek(fp,132024,SEEK_SET);
		fprintf(fp,"%c",(ItemWSOffset&0xFF000000)/0x1000000);
		fprintf(fp,"%c",(ItemWSOffset&0x00FF0000)/0x10000);
		fprintf(fp,"%c",(ItemWSOffset&0x0000FF00)/0x100);
		fprintf(fp,"%c",(ItemWSOffset&0x000000FF));

		fseek(fp,ItemWSOffset,SEEK_SET);
		if(ItemWSOffset!=0x25D06){
			fprintf(fp,"%c",0);
			for(i=0; i<NumItems; i++){
				fprintf(fp,"%c",ItemWS[i]);
			}
		} else {
			fprintf(fp,"%c",0x1B);
			for(i=0; i<0x1B; i++){
				ItemWS[i]=255;
			}
			for(i=0x1B; i<NumItems; i++){
				fprintf(fp,"%c",ItemWS[i]);
			}
		}


		fseek(fp,132028,SEEK_SET);
		fprintf(fp,"%c",(ItemTypeOffset&0xFF000000)/0x1000000);
		fprintf(fp,"%c",(ItemTypeOffset&0x00FF0000)/0x10000);
		fprintf(fp,"%c",(ItemTypeOffset&0x0000FF00)/0x100);
		fprintf(fp,"%c",(ItemTypeOffset&0x000000FF));

		fseek(fp,ItemTypeOffset,SEEK_SET);
		for(i=0; i<NumItems; i++){
			fprintf(fp,"%c",ItemType[i]);
		}

		fseek(fp,132020,SEEK_SET);
		fprintf(fp,"%c",(ItemOffset&0xFF000000)/0x1000000);
		fprintf(fp,"%c",(ItemOffset&0x00FF0000)/0x10000);
		fprintf(fp,"%c",(ItemOffset&0x0000FF00)/0x100);
		fprintf(fp,"%c",(ItemOffset&0x000000FF));

		fseek(fp,ItemOffset,SEEK_SET);
		for(i=0; i<63; i++){
			for(int j=0; j<16 + 16 * (ExtendEquip); j++){
				fprintf(fp,"%c",Item[i][j]);
			}
		}
		if(NumItems==128){
			for(int j=0; j<16 + 16 * (ExtendEquip); j++){
				fprintf(fp,"%c",255);
			}
			for(i=0; i<63; i++){
				for(int j=0; j<16 + 16 * (ExtendEquip); j++){
					fprintf(fp,"%c",Item[i+64][j]);
				}
			}
		}

		fseek(fp,0xCC024,SEEK_SET);
		fprintf(fp,"%c",(ItemIconOffset&0xFF000000)/0x1000000);
		fprintf(fp,"%c",(ItemIconOffset&0x00FF0000)/0x10000);
		fprintf(fp,"%c",(ItemIconOffset&0x0000FF00)/0x100);
		fprintf(fp,"%c",(ItemIconOffset&0x000000FF));

		fseek(fp,ItemIconOffset,SEEK_SET);

		for(i=0; i<65; i++){
			for(int c=0; c<6; c++){
				for(int j=0; j<32; j++){
					int k=j*2;
					r = ItemImages[i][c%2*8+(c-c%2)*64+k%8+(k-k%8)*2]*16+ItemImages[i][c%2*8+(c-c%2)*64+k%8+(k-k%8)*2+1];
					fprintf(fp,"%c",r);
				}
			}
		}
		if(NumItems==128){
			for(i=1; i<63; i++){
				for(int c=0; c<6; c++){
					for(int j=0; j<32; j++){
						int k=j*2;
						r = ItemImages[i+64][c%2*8+(c-c%2)*64+k%8+(k-k%8)*2]*16+ItemImages[i+64][c%2*8+(c-c%2)*64+k%8+(k-k%8)*2+1];
						fprintf(fp,"%c",r);
					}
				}
			}
		}

		if(false&&NumItems==128){//removed to go back to old break mechanics
			fseek(fp,0x2165C,SEEK_SET);
			fprintf(fp,"%c",0x60);

			fseek(fp,0x216A4,SEEK_SET);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0xF9);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x02);
			fprintf(fp,"%c",0x16);
			fprintf(fp,"%c",0x5E);
		} else {
			fseek(fp,0x2165C,SEEK_SET);
			fprintf(fp,"%c",0x67);

			fseek(fp,0x216A4,SEEK_SET);
			fprintf(fp,"%c",0x02);
			fprintf(fp,"%c",0x41);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x3F);
			fprintf(fp,"%c",0x42);
			fprintf(fp,"%c",0x42);
		}


		if(NumItems==128){
			if(0x1A0000>romsize-1){
				MessageBox(NULL,"Rom is too small, expand rom or use a smaller offset.","Error",MB_OK);
				fclose(fp);
				return;
			}

			fseek(fp, 0x21654, SEEK_SET);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0xB9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x1A);
			fprintf(fp, "%c", 0xD9);
			fprintf(fp, "%c", 0xA0);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0x71);

			fseek(fp, 0x1AD9A0, SEEK_SET);
			fprintf(fp, "%c", 0x32);
			fprintf(fp, "%c", 0x38);
			fprintf(fp, "%c", 0xCB);
			fprintf(fp, "%c", 0x62);
			fprintf(fp, "%c", 0x48);
			fprintf(fp, "%c", 0xE7);
			fprintf(fp, "%c", 0xF0);
			fprintf(fp, "%c", 0x00);



			fprintf(fp, "%c", 0x08);
			fprintf(fp, "%c", 0x01);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x06);
			fprintf(fp, "%c", 0x67);
			fprintf(fp, "%c", 0x0A);


			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0xB9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x02);
			fprintf(fp, "%c", 0x02);
			fprintf(fp, "%c", 0x6C);
			fprintf(fp, "%c", 0x08);
			fprintf(fp, "%c", 0x02);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x0F);
			fprintf(fp, "%c", 0x4C);
			fprintf(fp, "%c", 0xDF);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x0F);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0x75);

			fseek(fp,0xC6C6,SEEK_SET);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0xB9);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x1B);
			fprintf(fp,"%c",0xD0);
			fprintf(fp,"%c",0x40);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0x71);

			fseek(fp,0x1BD040,SEEK_SET);
			fprintf(fp,"%c",0x12);
			fprintf(fp,"%c",0x33);
			fprintf(fp,"%c",0x10);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0xB5);
			fprintf(fp,"%c",0xFC);
			fprintf(fp,"%c",(SpellImagesOffset&0xFF000000)/0x1000000);
			fprintf(fp,"%c",(SpellImagesOffset&0x00FF0000)/0x10000);
			fprintf(fp,"%c",(SpellImagesOffset&0x0000FF00)/0x100);
			fprintf(fp,"%c",(SpellImagesOffset&0x000000FF));
			fprintf(fp,"%c",0x66);
			fprintf(fp,"%c",0x16);

			fprintf(fp,"%c",0x02);
			fprintf(fp,"%c",0x41);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x3F);

			fprintf(fp,"%c",0x0C);
			fprintf(fp,"%c",0x41);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x3F);
			fprintf(fp,"%c",0x66);
			fprintf(fp,"%c",0x04);

			if(SpellImagesOffset==0x180E80){
				fprintf(fp,"%c",0x72);
				fprintf(fp,"%c",0x7F);
			} else {
				fprintf(fp,"%c",0x72);
				fprintf(fp,"%c",0x4F);
			}
			
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0x75);

			fprintf(fp,"%c",0x66);
			fprintf(fp,"%c",0x06);
			fprintf(fp,"%c",0x02);
			fprintf(fp,"%c",0x41);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x3F);

			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0x75);
			fprintf(fp,"%c",0x02);
			fprintf(fp,"%c",0x41);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x7F);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0x75);

			fseek(fp,0x16AEE,SEEK_SET);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0xF9);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x1A);
			fprintf(fp,"%c",0xD9);
			fprintf(fp,"%c",0x40);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0x71);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0x71);

			fseek(fp,0x1AD940,SEEK_SET);
			fprintf(fp,"%c",0x48);
			fprintf(fp,"%c",0xE7);
			fprintf(fp,"%c",0xF0);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0xB9);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x02);
			fprintf(fp,"%c",0x02);
			fprintf(fp,"%c",0x6C);
			fprintf(fp,"%c",0x08);
			fprintf(fp,"%c",0x02);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x0F);
			fprintf(fp,"%c",0x66);
			fprintf(fp,"%c",0x0A);
			fprintf(fp,"%c",0x4C);
			fprintf(fp,"%c",0xDF);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x0F);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0xF9);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x01);
			fprintf(fp,"%c",0x6A);
			fprintf(fp,"%c",0xFA);
			fprintf(fp,"%c",0x4C);
			fprintf(fp,"%c",0xDF);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x0F);
			fprintf(fp,"%c",0x32);
			fprintf(fp,"%c",0x2E);
			fprintf(fp,"%c",0xFF);
			fprintf(fp,"%c",0xF4);
			fprintf(fp,"%c",0x08);
			fprintf(fp,"%c",0x30);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x06);
			fprintf(fp,"%c",0x10);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0xF9);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x01);
			fprintf(fp,"%c",0x6A);
			fprintf(fp,"%c",0xF8);

			fseek(fp,0x12630C,SEEK_SET);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0xB9);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x1A);
			fprintf(fp,"%c",0xDA);
			fprintf(fp,"%c",0x00);

			fseek(fp,0x1ADA00,SEEK_SET);
			fprintf(fp,"%c",0x20);
			fprintf(fp,"%c",0x79);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x14);
			fprintf(fp,"%c",0x40);
			fprintf(fp,"%c",0x0C);
			fprintf(fp,"%c",0x02);
			fprintf(fp,"%c",0x40);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x7F);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0x75);


		} else {
			fseek(fp, 0x21654, SEEK_SET);
			fprintf(fp, "%c", 0x32);
			fprintf(fp, "%c", 0x38);
			fprintf(fp, "%c", 0xCB);
			fprintf(fp, "%c", 0x62);
			fprintf(fp, "%c", 0x08);
			fprintf(fp, "%c", 0x01);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x06);

			fseek(fp,0xC6C6,SEEK_SET);
			fprintf(fp,"%c",0x12);
			fprintf(fp,"%c",0x33);
			fprintf(fp,"%c",0x10);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x02);
			fprintf(fp,"%c",0x41);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x3F);

			fseek(fp,0x16AEE,SEEK_SET);
			fprintf(fp,"%c",0x32);
			fprintf(fp,"%c",0x2E);
			fprintf(fp,"%c",0xFF);
			fprintf(fp,"%c",0xF4);
			fprintf(fp,"%c",0x08);
			fprintf(fp,"%c",0x30);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x06);
			fprintf(fp,"%c",0x10);
			fprintf(fp,"%c",0x00);

			fseek(fp,0x12630C,SEEK_SET);
			fprintf(fp,"%c",0x20);
			fprintf(fp,"%c",0x79);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x14);
			fprintf(fp,"%c",0x40);
			fprintf(fp,"%c",0x0C);
		}

		fseek(fp, 0x24F05, SEEK_SET);
		fprintf(fp, "%c", NumItems - 1);
		fseek(fp, 0x24EEB, SEEK_SET);
		fprintf(fp, "%c", NumItems - 1);
		fseek(fp, 0x17F3D, SEEK_SET);
		fprintf(fp, "%c", NumItems - 1);

		for(i=0;i<18;i++){
			fseek(fp,ItemExtendOffsets[i],SEEK_SET);
			if(NumItems==128)fprintf(fp,"%c",0x7F);
			else fprintf(fp,"%c",0x3F);
		}

		fseek(fp,143382,SEEK_SET);
		if(ExtendDrops){
			if(ItemDropOffset>romsize-1){
				MessageBox(NULL,"Rom is too small, expand rom or use a smaller offset.","Error",MB_OK);
				fclose(fp);
				return;
			}
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0xB9);
			fprintf(fp,"%c",((ItemDropOffset)&0xFF000000)/0x1000000);
			fprintf(fp,"%c",((ItemDropOffset)&0x00FF0000)/0x10000);
			fprintf(fp,"%c",((ItemDropOffset)&0x0000FF00)/0x100);
			fprintf(fp,"%c",((ItemDropOffset)&0x000000FF));
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0x71);
			fseek(fp,ItemDropOffset,SEEK_SET);
			fprintf(fp,"%c",0x02);
			fprintf(fp,"%c",0x42);
			fprintf(fp,"%c",0x00);
			if(NumItems==128)
				fprintf(fp,"%c",0x7F);
			else
				fprintf(fp,"%c",0x3F);
			fprintf(fp,"%c",0x43);
			fprintf(fp,"%c",0xF9);
			fprintf(fp,"%c",((ItemDropOffset+12)&0xFF000000)/0x1000000);
			fprintf(fp,"%c",((ItemDropOffset+12)&0x00FF0000)/0x10000);
			fprintf(fp,"%c",((ItemDropOffset+12)&0x0000FF00)/0x100);
			fprintf(fp,"%c",((ItemDropOffset+12)&0x000000FF));
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0x75);
			for(i=0; i<63; i++){
				if(ItemDrop[i])fprintf(fp,"%c",i);
			}
			if(NumItems==128){
				for(i=0; i<63; i++){
					if(ItemDrop[i+64])fprintf(fp,"%c",i+64);
				}
			}
			fprintf(fp,"%c",255);
		} else {
			fprintf(fp,"%c",0x02);
			fprintf(fp,"%c",0x42);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x3F);
			fprintf(fp,"%c",0x43);
			fprintf(fp,"%c",0xFA);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x1E);
		}

		fseek(fp,0x5BC6,SEEK_SET);
		if(ExtendMapUses){
			if(0x1BF000>romsize-1){
				MessageBox(NULL,"Rom is too small, expand rom to save map uses.","Error",MB_OK);
				fclose(fp);
				return;
			}
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0xF9);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x1B);
			fprintf(fp,"%c",0xF0);
			fprintf(fp,"%c",0x00);
			fseek(fp,0x5C30,SEEK_SET);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0xF9);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x5C);
			fprintf(fp,"%c",0xE0);

			fseek(fp,0x5CBA,SEEK_SET);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0x71);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0xB9);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x1B);
			fprintf(fp,"%c",0xF1);
			fprintf(fp,"%c",0x80);

			fseek(fp,0x1BF000,SEEK_SET);
			fprintf(fp,"%c",0x10);
			fprintf(fp,"%c",0x38);
			fprintf(fp,"%c",0xB5);
			fprintf(fp,"%c",0x28);
			fprintf(fp,"%c",0x10);
			fprintf(fp,"%c",0x30);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x02);
			fprintf(fp,"%c",0x40);
			fprintf(fp,"%c",0x00);
			if(NumItems==64)
				fprintf(fp,"%c",0x3F);
			else
				fprintf(fp,"%c",0x7F);
			fprintf(fp,"%c",0x31);
			fprintf(fp,"%c",0xC0);
			fprintf(fp,"%c",0xF8);
			fprintf(fp,"%c",0x44);

			fprintf(fp,"%c",0x0C);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",MapItem[0]);
			fprintf(fp,"%c",0x66);
			fprintf(fp,"%c",0x06);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0xF9);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x5B);
			fprintf(fp,"%c",0xDE);

			fprintf(fp,"%c",0x0C);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",MapItem[1]);
			fprintf(fp,"%c",0x66);
			fprintf(fp,"%c",0x06);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0xF9);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x5C);
			fprintf(fp,"%c",0x38);

			for(unsigned char l=0;l<6;l++){
				fprintf(fp,"%c",0x0C);
				fprintf(fp,"%c",0x00);
				fprintf(fp,"%c",0x00);
				fprintf(fp,"%c",MapItem[2+l]);
				fprintf(fp,"%c",0x66);
				fprintf(fp,"%c",0x06);
				fprintf(fp,"%c",0x4E);
				fprintf(fp,"%c",0xF9);
				fprintf(fp,"%c",0x00);
				fprintf(fp,"%c",0x00);
				fprintf(fp,"%c",0x5C);
				fprintf(fp,"%c",0x8E);
			}

			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0xF9);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x5C);
			fprintf(fp,"%c",0xE0);

			fseek(fp,0x1BF180,SEEK_SET);
			for(i=0;i<6;i++){
				fprintf(fp,"%c",0x0C);
				fprintf(fp,"%c",0x01);
				fprintf(fp,"%c",0x00);
				fprintf(fp,"%c",MapItem[2+i]);
				fprintf(fp,"%c",0x66);
				fprintf(fp,"%c",0x08);
				fprintf(fp,"%c",0x72);
				fprintf(fp,"%c",i);
				fprintf(fp,"%c",0x4E);
				fprintf(fp,"%c",0xF9);
				fprintf(fp,"%c",0x00);
				fprintf(fp,"%c",0x02);
				fprintf(fp,"%c",0x02);
				fprintf(fp,"%c",0xB4);
			}
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0x75);

		} else {
			fprintf(fp,"%c",0x10);
			fprintf(fp,"%c",0x38);
			fprintf(fp,"%c",0xB5);
			fprintf(fp,"%c",0x28);
			fprintf(fp,"%c",0x10);
			fprintf(fp,"%c",0x30);

			fseek(fp,0x5CBA,SEEK_SET);
			fprintf(fp,"%c",0x5B);
			fprintf(fp,"%c",0x41);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0xB9);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x02);
			fprintf(fp,"%c",0x02);
			fprintf(fp,"%c",0xB4);

			fseek(fp,0x5BD1,SEEK_SET);
			if(NumItems==64)
				fprintf(fp,"%c",0x3F);
			else
				fprintf(fp,"%c",0x7F);

			fseek(fp,0x5C30,SEEK_SET);
			fprintf(fp,"%c",0x0C);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x02);
			fprintf(fp,"%c",0x66);
			fprintf(fp,"%c",0x00);
		}

		fclose(fp);
		MessageBox(NULL,"Items Saved","Note",MB_OK);
	}
}

void ExportItem(char*path){
	FILE * fp = fopen(path,"wb");
	int i,j;
	for(i=0; i<63; i++){
		fprintf(fp,"%c",strlen(ItemName[i]));
		for(j=0; j<strlen(ItemName[i]); j++){
			fprintf(fp,"%c",ItemName[i][j]);
		}
	}
	for(i=0; i<63; i++){
		for(j=0; j<16; j++){
			fprintf(fp,"%c",Item[i][j]);
		}
		for(j=0; j<384; j++){
			fprintf(fp,"%c",ItemImages[i][j]);
		}
	}
	fclose(fp);
	MessageBox(NULL,"Items Exported","Note",MB_OK);
}

void ItemExport(){
	OPENFILENAME openFileName;
	char path[256];
	path[0] = '\0';  
	memset( &openFileName, 0, sizeof(openFileName) );
	openFileName.lStructSize = sizeof(openFileName);
	openFileName.hwndOwner = NULL;
	openFileName.hInstance = NULL;
	openFileName.lpstrFilter = "Shining Force Items(*.sfi)\0*.sfi\0";
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
	openFileName.lpstrDefExt = "sfi";
	openFileName.lCustData = NULL;
	openFileName.lpfnHook = NULL;
	openFileName.lpTemplateName = NULL;

	if(GetSaveFileName(&openFileName)!=0){
		ExportItem(path);
	}
}

void CopySelectedItem() {
	unsigned int size[2] = { 16,24 };

	ToClipboard(ItemImages[select[mode]], size, IconPalette);
}