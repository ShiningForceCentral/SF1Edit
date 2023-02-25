unsigned char Item[128][32];
char ItemName[128][24];
unsigned char ItemImages[128][384];

unsigned char ItemType[128];
unsigned char ItemWS[128];

bool ItemDrop[128];
bool ExtendDrops;

long ItemNameOffset;
long ItemOffset;
long ItemDropOffset;
long ItemIconOffset;
long ItemTypeOffset;
long ItemWSOffset;

long OutfitOffset;
long OutfitBOffset;

unsigned char ItemView = 0;

bool ExtendMapUses;
bool BattleOutfits;
bool ExtendEquip;

unsigned char MapItem[8];

unsigned char ItemOutfits[64][4];
unsigned char NumOutfits;

char MapUseLabels[][32] = {"Chaos Breaker Event","Cure Poison","Increase Attack","Increase Defense","Increase Agility","Increase Move","Increase HP","Increase MP"};

#define NUM_MAPUSES	8
//0xC6CD
long ItemExtendOffsets[] = {0x5BD1, 0x5D31, 0x5F7D, 0x72CB, 0xB835, 0xC6D1, 0xDC97, 0xEC0F, 0x16C33, 0x16AD3, 0x21661, 0x22E83, 0x22EF7, 0x23667, 0x238C5, 0x23BCB, 0x24E6D, 0x23AB3};

void LoadItem(char *path, bool single=false){
	unsigned char r,c;
	unsigned int in=0;
	FILE * fp = fopen(path,"rb");
	int i;

	bool TempExtendEquip;
	
	if (!single) {
		memset(Item, 0, 128 * 32);
	}

	fseek(fp, 0x22E84, SEEK_SET);
	fscanf(fp, "%c", &r);
	if (r == 0xEB) {
		TempExtendEquip = true;
	} else {
		TempExtendEquip = false;
	}


	fseek(fp,0x23A98,SEEK_SET);
	fscanf(fp,"%c",&r);
	if(r==0x4E){
		OutfitOffset = 0x1D8010;
	} else {
		OutfitOffset = 0x23ACE;
	}


	fseek(fp,OutfitOffset,SEEK_SET);
	NumOutfits=0;
	while(true){
		fscanf(fp,"%c",&r);
		if(r==0xFF)break;
		ItemOutfits[NumOutfits][0]=r;
		fscanf(fp,"%c",&r);
		ItemOutfits[NumOutfits][1]=r;
		fscanf(fp,"%c",&r);
		ItemOutfits[NumOutfits][2]=r;
		NumOutfits++;
		ItemOutfits[NumOutfits][3]=0;
	}

	fseek(fp,0x12632C,SEEK_SET);
	fscanf(fp,"%c",&r);
	if(r==0x4E){
		BattleOutfits=true;
	} else {
		BattleOutfits=false;
	}

	fseek(fp,0x1D8180,SEEK_SET);
	i=0;
	while(BattleOutfits){
		fscanf(fp,"%c",&r);
		if(r==0xFF)break;
		fscanf(fp,"%c",&r);
		fscanf(fp,"%c",&r);
		ItemOutfits[i][3]=r;
		i++;
	}

	fseek(fp,132016,SEEK_SET);
	fscanf(fp,"%c",&r);
	ItemNameOffset = r;
	fscanf(fp,"%c",&r);
	ItemNameOffset = ItemNameOffset*256+r;
	fscanf(fp,"%c",&r);
	ItemNameOffset = ItemNameOffset*256+r;
	fscanf(fp,"%c",&r);
	ItemNameOffset = ItemNameOffset*256+r;

	fseek(fp,ItemNameOffset,SEEK_SET);
	for(i=0; i<63; i++){
		fscanf(fp,"%c",&r);
		for(int j=0; j<r; j++){
			if(single&&i!=select[mode]){
				fscanf(fp,"%c",&c);
				continue;
			}
			fscanf(fp,"%c",&(ItemName[i][j]));
			if(ItemName[i][j]==9)ItemName[i][j]=32;
		}
		ItemName[i][r]='\0';
	}

	if(ItemNameOffset==0x1AC800)NumItems=128;
	else NumItems=64;

	if(NumItems==128){
		fscanf(fp,"%c",&r);
		for(i=0; i<63; i++){
			fscanf(fp,"%c",&r);
			for(int j=0; j<r; j++){
				if(single&&i!=select[mode]){
					fscanf(fp,"%c",&c);
					continue;
				}
				fscanf(fp,"%c",&(ItemName[i+64][j]));
				if(ItemName[i+64][j]==9)ItemName[i+64][j]=32;
			}
			ItemName[i+64][r]='\0';
		}
	}

	fseek(fp,132024,SEEK_SET);
	fscanf(fp,"%c",&r);
	ItemWSOffset = r;
	fscanf(fp,"%c",&r);
	ItemWSOffset = ItemWSOffset*256+r;
	fscanf(fp,"%c",&r);
	ItemWSOffset = ItemWSOffset*256+r;
	fscanf(fp,"%c",&r);
	ItemWSOffset = ItemWSOffset*256+r;

	fseek(fp,ItemWSOffset,SEEK_SET);
	if(ItemWSOffset!=0x25D06){
		fscanf(fp,"%c",&r);
		for(i=0; i<NumItems; i++){
			if(single&&i!=select[mode]){
				fscanf(fp,"%c",&c);
				continue;
			}
			fscanf(fp,"%c",&(ItemWS[i]));
		}
	} else {
		fscanf(fp,"%c",&r);
		for(i=0; i<r; i++){
			ItemWS[i]=255;
		}
		for(i=r; i<NumItems; i++){
			if(single&&i!=select[mode]){
				fscanf(fp,"%c",&c);
				continue;
			}
			fscanf(fp,"%c",&(ItemWS[i]));
		}
	}

	fseek(fp,132028,SEEK_SET);
	fscanf(fp,"%c",&r);
	ItemTypeOffset = r;
	fscanf(fp,"%c",&r);
	ItemTypeOffset = ItemTypeOffset*256+r;
	fscanf(fp,"%c",&r);
	ItemTypeOffset = ItemTypeOffset*256+r;
	fscanf(fp,"%c",&r);
	ItemTypeOffset = ItemTypeOffset*256+r;

	fseek(fp,ItemTypeOffset,SEEK_SET);
	for(i=0; i<NumItems; i++){
		if(single&&i!=select[mode]){
			fscanf(fp,"%c",&c);
			continue;
		}
		fscanf(fp,"%c",&(ItemType[i]));
	}

	fseek(fp,132020,SEEK_SET);
	fscanf(fp,"%c",&r);
	ItemOffset = r;
	fscanf(fp,"%c",&r);
	ItemOffset = ItemOffset*256+r;
	fscanf(fp,"%c",&r);
	ItemOffset = ItemOffset*256+r;
	fscanf(fp,"%c",&r);
	ItemOffset = ItemOffset*256+r;

	fseek(fp,ItemOffset,SEEK_SET);
	for(i=0; i<63; i++){
		for(int j=0; j<16 + 16 * (TempExtendEquip); j++){
			if(single&&i!=select[mode]){
				fscanf(fp,"%c",&c);
				continue;
			}
			fscanf(fp,"%c",&(Item[i][j]));
		}
	}
	if(NumItems==128){
		for(int j=0; j<16 + 16 * (TempExtendEquip); j++){
			fscanf(fp,"%c",&r);
		}
		for(i=0; i<63; i++){
			for(int j=0; j<16 + 16 * (TempExtendEquip); j++){
				if(single&&i!=select[mode]){
					fscanf(fp,"%c",&c);
					continue;
				}
				fscanf(fp,"%c",&(Item[i+64][j]));
			}
		}
	}

	fseek(fp,0xCC024,SEEK_SET);
	fscanf(fp,"%c",&r);
	ItemIconOffset = r;
	fscanf(fp,"%c",&r);
	ItemIconOffset = ItemIconOffset*256+r;
	fscanf(fp,"%c",&r);
	ItemIconOffset = ItemIconOffset*256+r;
	fscanf(fp,"%c",&r);
	ItemIconOffset = ItemIconOffset*256+r;

	fseek(fp,ItemIconOffset,SEEK_SET);


	for(i=0; i<65; i++){
		for(int c=0; c<6; c++){
			for(int j=0; j<32; j++){
				fscanf(fp,"%c",&r);
				if(single&&i!=select[mode])continue;
				int k=j*2;
				ItemImages[i][c%2*8+(c-c%2)*64+k%8+(k-k%8)*2+1]=r%16;
				r-=r%16;
				r/=16;
				ItemImages[i][c%2*8+(c-c%2)*64+k%8+(k-k%8)*2]=r;
			}
		}
	}
	if(NumItems==128){
		for(i=1; i<63; i++){
			for(int c=0; c<6; c++){
				for(int j=0; j<32; j++){
					fscanf(fp,"%c",&r);
					if(single&&i!=select[mode])continue;
					int k=j*2;
					ItemImages[i+64][c%2*8+(c-c%2)*64+k%8+(k-k%8)*2+1]=r%16;
					r-=r%16;
					r/=16;
					ItemImages[i+64][c%2*8+(c-c%2)*64+k%8+(k-k%8)*2]=r;
				}
			}
		}
	}

	if(!single){
		fseek(fp,143382,SEEK_SET);
		fscanf(fp,"%c",&r);
		if(r==0x4E){
			ExtendDrops=true;
			fscanf(fp,"%c",&r);
			fscanf(fp,"%c",&r);
			ItemDropOffset = r;
			fscanf(fp,"%c",&r);
			ItemDropOffset = ItemDropOffset*256+r;
			fscanf(fp,"%c",&r);
			ItemDropOffset = ItemDropOffset*256+r;
			fscanf(fp,"%c",&r);
			ItemDropOffset = ItemDropOffset*256+r;
		} else {
			ExtendDrops=false;
			ItemDropOffset=0x2303A;
		}

		fseek(fp,0x5BC6,SEEK_SET);
		fscanf(fp,"%c",&r);
		if(r==0x4E){
			ExtendMapUses=true;

			fseek(fp,0x1BF013,SEEK_SET);
			fscanf(fp,"%c",&MapItem[0]);

			fseek(fp,0x1BF01F,SEEK_SET);
			fscanf(fp,"%c",&MapItem[1]);

			for(i=0;i<6;i++){
				fseek(fp,0x1BF02B+12*i,SEEK_SET);
				fscanf(fp,"%c",&MapItem[2+i]);
			}

		} else {
			ExtendMapUses=false;
			MapItem[0] = 39;
			MapItem[1] = 2;
			MapItem[2] = 5;
			MapItem[3] = 6;
			MapItem[4] = 7;
			MapItem[5] = 8;
			MapItem[6] = 9;
			MapItem[7] = 255;
		}

		fseek(fp,ItemDropOffset+12*ExtendDrops,SEEK_SET);
		fscanf(fp,"%c",&r);
		while(r!=255){
			ItemDrop[r]=true;
			fscanf(fp,"%c",&r);
		}
	}
	

	fclose(fp);
	sprintf(file,path);
}

void ImportItem(char *path){
	unsigned char r;
	FILE * fp = fopen(path,"rb");
	int i,j;
	for(i=0; i<63; i++){
		fscanf(fp,"%c",&r);
		for(j=0; j<r; j++){
			fscanf(fp,"%c",&(ItemName[i][j]));
		}
		ItemName[i][r]='\0';
	}
	for(i=0; i<63; i++){
		for(j=0; j<16; j++){
			fscanf(fp,"%c",&(Item[i][j]));
		}
		for(j=0; j<384; j++){
			fscanf(fp,"%c",&(ItemImages[i][j]));
		}
	}

	fscanf(fp,"%c",&r);
	if(feof(fp))return;
	ItemNameOffset = r;
	fscanf(fp,"%c",&r);
	ItemNameOffset = ItemNameOffset*256+r;
	fscanf(fp,"%c",&r);
	ItemNameOffset = ItemNameOffset*256+r;
	fscanf(fp,"%c",&r);
	ItemNameOffset = ItemNameOffset*256+r;

	fscanf(fp,"%c",&r);
	ItemOffset = r;
	fscanf(fp,"%c",&r);
	ItemOffset = ItemOffset*256+r;
	fscanf(fp,"%c",&r);
	ItemOffset = ItemOffset*256+r;
	fscanf(fp,"%c",&r);
	ItemOffset = ItemOffset*256+r;

	fclose(fp);
}

void ItemImport(){
	int ret=IDYES;
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
	openFileName.Flags = OFN_LONGNAMES | OFN_PATHMUSTEXIST;
	openFileName.nFileOffset = 0;
	openFileName.nFileExtension = 0;
	openFileName.lpstrDefExt = "sfi";
	openFileName.lCustData = NULL;
	openFileName.lpfnHook = NULL;
	openFileName.lpTemplateName = NULL;

	if(GetOpenFileName(&openFileName)!=0){
		ImportItem(path);
	}
}


void PasteSelectedItem() {
	unsigned int size[2] = { 16,24 };

	FromClipboard(ItemImages[select[mode]],size, IconPalette);
}