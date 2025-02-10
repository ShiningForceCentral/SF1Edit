
unsigned char Sprites[54][32][6];
unsigned char UniSprites[54];
unsigned char NumSprites[54];
int NumSpriteSets = 54;
unsigned char MapSelect = -1;
unsigned char MapSpriteSet[NUM_MAPS];
int LastNPCScript = -1;

unsigned char Chests[8][32][4];
unsigned int MapData[NUM_MAPS][4096];
char MapData2[NUM_MAPS][4096];
int MapTileset[NUM_MAPS][4];
bool MapWalk[NUM_MAPS][4096];
unsigned char MapFlag[NUM_MAPS][4096];
unsigned char MapFlag2[NUM_MAPS][4096];
unsigned char MapEvent[NUM_MAPS][4096];
unsigned char MapGroup[NUM_MAPS][4096];
unsigned char MapChest[NUM_MAPS][4096];
unsigned int MapRead[NUM_MAPS][4096];
unsigned int MapGold[NUM_MAPS][4096];
unsigned char MapMusic[NUM_MAPS][3];

unsigned long MapSpecialBankOffset = 0x10180;
unsigned char MapSpecialTiles[NUM_MAPS][5][3];
char SpecialDesc[][32] = { "Entrance","HQ Return To","Spawn/Egress","Alternate Entrance","Event Entrance" };

unsigned char HQPos[60][3];

int MapTele[1024][8];
int MapAltTele[32][6];
int NumMapTele;
bool MapDragging = false;
int MapDragPos[2];

long DialogHeaderOffset;

unsigned char SpriteScripts[172][256];
unsigned char SpriteComLen[30] = {1,1,1,1,1,1,1,1,2,1,1,1,2,2,2,3,2,3,3,2,3,3,3,1,4,1,1,1,1,1};
char SpriteComName[30][32] = {"End Frame","Face Random Direction","Face Up","Face Right","Face Down","Face Left","Rotate CW","Rotate CCW","Move Forward","Loop","Clear ? Flag","Set ? Flag","Move Forward Random","Set Script Speed","Jump To","Check Hero Position","Run Hero Script","Display Message","Set Sprite Direction","Run Check","Check Event Flags","Set Event Flags","Clear Event Flags","Turn Around","Move Sprite","End Event","Set ?? Flag","Clear ?? Flag","Lock Hero","Unlock Hero"};
unsigned int SpriteScrLen[172];

unsigned char PixelData[4096];

void AddChest(int, int, int, int, int,int);
void BaseChests(int);
void AddRead(int, int, int, int,int);
void BaseRead(int);

int  numEvents   = 6;
char EventNums[] = {8,12,20,76,100,112};
char EventDesc[][32] = {"Can Talk Through","Teleport","Door","No NPC Wander","Readable","Chest"};

byte NovaPortrait;
byte NovaSprite;
byte BlueFlameSprite;
byte JogurtStatusSprite;

char MapGraphics[NUM_MAPS][2];

long SpriteOffsets[54];
long MapOffsets[NUM_MAPS];
long MapGfxOffsets[NUM_MAPS];
long MapPalOffsets[NUM_MAPS];
long MapsOffset = 0x183560;//0xA8AEE;//
long TeleOffset;
char TeleSpecial;

int ViewX=0;
int ViewY=0;
unsigned char MapZoom=1;
int MMW=8;
int MMH=8;

bool MapChanged=false;
bool DisplayWalk=false;
bool Walkable=true;
bool DisplayGrid=false;
bool DisplayNum=false;
bool SecondLayer=false;
bool DisplayGroup=false;
bool DisplayEvent=false;
bool DisplaySprites=false;
bool DisplayHQ=false;
bool DisplaySpecial = false;


long HQPosOffset;
int  NumHQPos;

void CountMapSprites();

void LoadMap(char *path, bool single=false){
	MapChanged=single;
	unsigned char r;
	unsigned char r2;
	unsigned int c;
	unsigned long temp;
	int i,j;
	FILE * fp = fopen(path,"rb");
	char in,t;

	NumMapTele=0;

	long o;

	fseek(fp, 0x67D0, SEEK_SET);
	fscanf(fp, "%c", &r);

	if (r == 0x43) {
		HQPosOffset = 0x69D4;
		NumHQPos = 30;
	} else {
		HQPosOffset = 0x1E1000;
		fseek(fp, 0x1E0FFF, SEEK_SET);
		fscanf(fp, "%c", &NumHQPos);
	}

	fseek(fp, HQPosOffset, SEEK_SET);
	for (i = 0; i < NumHQPos; i++) {
		for (j = 0; j < 3; j++) {
			fscanf(fp, "%c", &r);
			HQPos[i][j] = r;
		}
	}

	for(i=0;i<NUM_MAPS;i++){
		MapMusic[i][0]=255;
		MapMusic[i][1]=255;
		MapMusic[i][2]=255;

		for (int j = 0; j < 5; j++) {
			MapSpecialTiles[i][j][0] = 0xFF;
			MapSpecialTiles[i][j][1] = 0xFF;
			MapSpecialTiles[i][j][2] = 0xFF;
		}
	}

	for (int j = 0; j < 5; j++) {
		fseek(fp, MapSpecialBankOffset + 4 * j, SEEK_SET);
		temp = 0;
		fscanf(fp, "%c", &r);
		temp = r;
		fscanf(fp, "%c", &r);
		temp = temp * 256 + r;
		fscanf(fp, "%c", &r);
		temp = temp * 256 + r;
		fscanf(fp, "%c", &r);
		temp = temp * 256 + r;

		fseek(fp, temp, SEEK_SET);

		for (;;) {
			fscanf(fp, "%c", &r);
			fscanf(fp, "%c", &r2);
			if (r2 == 0xFF)break;

			if (MapSpecialTiles[r][j][0] != 0xFF)
				r = r;

			MapSpecialTiles[r][j][0] = r2;

			fscanf(fp, "%c", &r2);
			MapSpecialTiles[r][j][1] = r2;
			fscanf(fp, "%c", &r2);
			MapSpecialTiles[r][j][2] = r2;
		}
	}





	c=0;
	fseek(fp,0x8FBE,SEEK_SET);
	for(i=0;i<NUM_MAPS+1;i++){
		fscanf(fp,"%c",&r);
		fscanf(fp,"%c",&c);
		if(c==11||c==17||c==38){
			MapMusic[c][0]=r;
			MapMusic[c][1]=0;
			MapMusic[c][2]=i;
		}
		fscanf(fp,"%c",&r);
		fscanf(fp,"%c",&r);
		fscanf(fp,"%c",&r);
		fscanf(fp,"%c",&r);
		fscanf(fp,"%c",&r);
		fscanf(fp,"%c",&r);
	}

	fseek(fp,0x1D37E,SEEK_SET);
	for(;;){
		fscanf(fp,"%c",&r);
		if(r==0xFF)break;
		fscanf(fp,"%c",&c);
		MapMusic[r][0]=c;
		MapMusic[r][1]=1;
	}

	fseek(fp,0x11B14,SEEK_SET);
	for(i=0;i<NUM_MAPS;i++){
		MapSpriteSet[i]=255;
	}
	for(;;){
		fscanf(fp,"%c",&r);
		if(r==0xFF)break;
		fscanf(fp,"%c",&c);
		MapSpriteSet[r]=c;
	}

	fseek(fp,0x80EFE,SEEK_SET);
	temp = 0;
	fscanf(fp,"%c",&r);
	temp = r;
	fscanf(fp,"%c",&r);
	temp = temp*256+r;
	fscanf(fp,"%c",&r);
	temp = temp*256+r;
	fscanf(fp,"%c",&r);
	temp = temp*256+r;

	if(!single||submode[mode]==3)
	for(i=0; i<172; i++){
		c=0;

		o = temp;

		fseek(fp,0x80EFE+4*i+4,SEEK_SET);
		temp = 0;
		fscanf(fp,"%c",&r);
		temp = r;
		fscanf(fp,"%c",&r);
		temp = temp*256+r;
		fscanf(fp,"%c",&r);
		temp = temp*256+r;
		fscanf(fp,"%c",&r);
		temp = temp*256+r;

		r=0;
		in=0;
		t=0;
		fseek(fp,o,SEEK_SET);
		while( (i==171&&t!=0x09&&t!=0x19&&t!=0x0E)||(i<171&&c<temp-o) ){
			c++;
			fscanf(fp,"%c",&t);
			if(!single||i==select[mode])SpriteScripts[i][r++]=t;
			switch(t){
				case 24:
					fscanf(fp,"%c",&in);
					if(!single||i==select[mode])SpriteScripts[i][r++]=in;
				case 15:
				case 17:
				case 18:
				case 20:
				case 21:
				case 22:
					fscanf(fp,"%c",&in);
					if(!single||i==select[mode])SpriteScripts[i][r++]=in;
				case 8:
				case 12:
				case 13:
				case 14:
				case 16:
				case 19:
					fscanf(fp,"%c",&in);
					if(!single||i==select[mode])SpriteScripts[i][r++]=in;
					break;

			}
		}
		if(!single||i==select[mode])SpriteScrLen[i]=c;
	}

	fseek(fp,524304,SEEK_SET);

	for(i=0; i<54; i++){
		fscanf(fp,"%c",&r);
		SpriteOffsets[i] = r;
		fscanf(fp,"%c",&r);
		SpriteOffsets[i] = SpriteOffsets[i]*256+r;
		fscanf(fp,"%c",&r);
		SpriteOffsets[i] = SpriteOffsets[i]*256+r;
		fscanf(fp,"%c",&r);
		SpriteOffsets[i] = SpriteOffsets[i]*256+r;
	}

	if(!single||submode[mode]==0)
	for(i=0; i<54; i++){
		UniSprites[i] = 0;
		fseek(fp,SpriteOffsets[i],SEEK_SET);
		int j=0;
		while(true){
			fscanf(fp,"%c",&in);
			if(in==-1||feof(fp)){
				//fscanf(fp,"%c",&in);
				break;
			}
			if(!single||i==select[mode])Sprites[i][j][0]=in;
			for(int k=0;k<5;k++){
				if(!single||i==select[mode])fscanf(fp,"%c",&(Sprites[i][j][k+1]));
				else fscanf(fp,"%c",&r);
			}
			j++;
		}
		if(!single||i==select[mode])NumSprites[i]=j;
	}

	CountMapSprites();

	fseek(fp,120462,SEEK_SET);

	if(!single||submode[mode]==1)
	for(i=0; i<8; i++){
		for(int j=0; j<32; j++){
			for(int k=0; k<4; k++){
				if(!single||i==select[mode])fscanf(fp,"%c",&(Chests[i][31-j][k]));
				else fscanf(fp,"%c",&r);
			}
		}
	}

	fseek(fp,0x820CC,SEEK_SET);

	if(!single||submode[mode]==2)
	for(i=0; i<NUM_MAPS; i++){
		fscanf(fp,"%c",&r);
		temp = r;
		fscanf(fp,"%c",&r);
		temp = temp*256+r;
		fscanf(fp,"%c",&r);
		temp = temp*256+r;
		fscanf(fp,"%c",&r);
		temp = temp*256+r;
		if(!single||i==select[mode])MapTileset[i][0]=(temp-0x8264C)/18;

		fscanf(fp,"%c",&r);
		temp = r;
		fscanf(fp,"%c",&r);
		temp = temp*256+r;
		fscanf(fp,"%c",&r);
		temp = temp*256+r;
		fscanf(fp,"%c",&r);
		temp = temp*256+r;
		if(!single||i==select[mode])MapTileset[i][1]=(temp-0x8264C)/18;

		fscanf(fp,"%c",&r);
		temp = r;
		fscanf(fp,"%c",&r);
		temp = temp*256+r;
		fscanf(fp,"%c",&r);
		temp = temp*256+r;
		fscanf(fp,"%c",&r);
		temp = temp*256+r;
		if(!single||i==select[mode])MapTileset[i][2]=(temp-0x8264C)/18;

		fscanf(fp,"%c",&r);
		temp = r;
		fscanf(fp,"%c",&r);
		temp = temp*256+r;
		fscanf(fp,"%c",&r);
		temp = temp*256+r;
		fscanf(fp,"%c",&r);
		temp = temp*256+r;
		if(!single||i==select[mode])MapTileset[i][3]=(temp-0x8264C)/18;

		fscanf(fp,"%c",&r);
		if(!single||i==select[mode])MapOffsets[i] = r;
		fscanf(fp,"%c",&r);
		if(!single||i==select[mode])MapOffsets[i] = MapOffsets[i]*256+r;
		fscanf(fp,"%c",&r);
		if(!single||i==select[mode])MapOffsets[i] = MapOffsets[i]*256+r;
		fscanf(fp,"%c",&r);
		if(!single||i==select[mode])MapOffsets[i] = MapOffsets[i]*256+r;

		fscanf(fp, "%c", &r);
		if (!single || i == select[mode])MapPalOffsets[i] = r;
		fscanf(fp, "%c", &r);
		if (!single || i == select[mode])MapPalOffsets[i] = MapPalOffsets[i] * 256 + r;
		fscanf(fp, "%c", &r);
		if (!single || i == select[mode])MapPalOffsets[i] = MapPalOffsets[i] * 256 + r;
		fscanf(fp, "%c", &r);
		if (!single || i == select[mode])MapPalOffsets[i] = MapPalOffsets[i] * 256 + r;

		fscanf(fp, "%c", &r);
		if (!single || i == select[mode])MapGfxOffsets[i] = r;
		fscanf(fp, "%c", &r);
		if (!single || i == select[mode])MapGfxOffsets[i] = MapGfxOffsets[i] * 256 + r;
		fscanf(fp, "%c", &r);
		if (!single || i == select[mode])MapGfxOffsets[i] = MapGfxOffsets[i] * 256 + r;
		fscanf(fp, "%c", &r);
		if (!single || i == select[mode])MapGfxOffsets[i] = MapGfxOffsets[i] * 256 + r;


		fseek(fp,4,SEEK_CUR);
	}

	BPDecompressor BPD(fp);
	SBDecompressor SBD(fp);
	ULDecompressor ULD(fp);

	if(!single||submode[mode]==2)
	for(j=0;j<1024;j++){
		if(!single||j==select[mode])MapTele[j][0]=-1;
	}

	if(!single||submode[mode]==2)
	for(i=0; i<NUM_MAPS; i++){
		if(single&&i!=select[mode])continue;
		fseek(fp,MapOffsets[i],SEEK_SET);
		fscanf(fp,"%c",&(MapSize[i][0]));
		fscanf(fp,"%c",&(MapSize[i][1]));
		BPD.GetData(MapSize[i][0],MapSize[i][0]*MapSize[i][1],MapData[i]);
		SBD.GetData(MapSize[i][0],MapSize[i][0]*MapSize[i][1],MapWalk[i],BPD.Barrel,BPD.Length);
		memset(MapData2[i],-1,4096);
		memset(MapFlag[i],0,4096);
		memset(MapFlag2[i],0,4096);
		memset(MapEvent[i],0,4096);
		memset(MapChest[i],-1,4096);
		memset(MapGold[i],0,4096);
		for(int j=0;j<4096;j++){
			MapRead[i][j]=-1;
		}
		ULD.GetData(i,MapSize[i][0],MapSize[i][0]*MapSize[i][1],MapFlag[i],MapFlag2[i],MapEvent[i],MapGroup[i],MapData2[i],SBD.Barrel,SBD.Length);
	}

	fseek(fp,0x12C62,SEEK_SET);
	fscanf(fp,"%c",&r);
	if(r==0x41){
		TeleOffset = 0x12D8A;
		
	} else {
		fscanf(fp,"%c",&r);
		fscanf(fp,"%c",&r);
		TeleOffset = r;
		fscanf(fp,"%c",&r);
		TeleOffset = TeleOffset*256+r;
		fscanf(fp,"%c",&r);
		TeleOffset = TeleOffset*256+r;
		fscanf(fp,"%c",&r);
		TeleOffset = TeleOffset*256+r;
	}

	if (TeleOffset != 0x1A5880) {
		fseek(fp, 0x17CE9, SEEK_SET);
	} else {
		fseek(fp, 0x17CEF, SEEK_SET);
	}
	fscanf(fp, "%c", &r);
	if (r != 0xF9) {
		DialogHeaderOffset = 0x17D62;
	} else {
		fscanf(fp, "%c", &r);
		DialogHeaderOffset = r;
		fscanf(fp, "%c", &r);
		DialogHeaderOffset = DialogHeaderOffset * 256 + r;
		fscanf(fp, "%c", &r);
		DialogHeaderOffset = DialogHeaderOffset * 256 + r;
		fscanf(fp, "%c", &r);
		DialogHeaderOffset = DialogHeaderOffset * 256 + r;
	}

	if(TeleOffset==0x12D8A){
		fseek(fp,TeleOffset,SEEK_SET);
	} else {
		/*fseek(fp,0x1A7400,SEEK_SET);
		for(i=0; i<NUM_MAPS; i++){
			fscanf(fp,"%c",&(MapGraphics[i][0]));
			fscanf(fp,"%c",&(MapGraphics[i][1]));
		}*/
		fseek(fp,TeleOffset+10,SEEK_SET);
	}


	



		MapGraphics[0][0]=0;
		MapGraphics[0][1]=3;
		MapGraphics[1][0]=0;
		MapGraphics[1][1]=5;
		MapGraphics[2][0]=0;
		MapGraphics[2][1]=1;
		MapGraphics[3][0]=0;
		MapGraphics[3][1]=1;
		MapGraphics[4][0]=0;
		MapGraphics[4][1]=7;
		MapGraphics[5][0]=0;
		MapGraphics[5][1]=6;
		MapGraphics[6][0]=0;
		MapGraphics[6][1]=7;
		MapGraphics[7][0]=0;
		MapGraphics[7][1]=11;
		MapGraphics[8][0]=0;
		MapGraphics[8][1]=10;
		MapGraphics[9][0]=0;
		MapGraphics[9][1]=13;
		MapGraphics[10][0]=0;
		MapGraphics[10][1]=13;
		MapGraphics[11][0]=0;
		MapGraphics[11][1]=6;
		MapGraphics[12][0]=0;
		MapGraphics[12][1]=13;
		MapGraphics[13][0]=0;
		MapGraphics[13][1]=8;
		MapGraphics[14][0]=0;
		MapGraphics[14][1]=3;
		MapGraphics[15][0]=0;
		MapGraphics[15][1]=9;
		MapGraphics[16][0]=0;
		MapGraphics[16][1]=10;
		MapGraphics[17][0]=0;
		MapGraphics[17][1]=5;
		MapGraphics[18][0]=2;
		MapGraphics[18][1]=4;
		MapGraphics[19][0]=2;
		MapGraphics[19][1]=4;
		MapGraphics[20][0]=2;
		MapGraphics[20][1]=4;
		MapGraphics[21][0]=2;
		MapGraphics[21][1]=4;
		MapGraphics[22][0]=2;
		MapGraphics[22][1]=4;
		MapGraphics[23][0]=2;
		MapGraphics[23][1]=4;
		MapGraphics[24][0]=2;
		MapGraphics[24][1]=20;
		MapGraphics[25][0]=0;
		MapGraphics[25][1]=0;
		MapGraphics[26][0]=25;
		MapGraphics[26][1]=24;
		MapGraphics[27][0]=25;
		MapGraphics[27][1]=29;
		MapGraphics[28][0]=25;
		MapGraphics[28][1]=24;
		MapGraphics[29][0]=0;
		MapGraphics[29][1]=14;
		MapGraphics[30][0]=0;
		MapGraphics[30][1]=17;
		MapGraphics[31][0]=0;
		MapGraphics[31][1]=16;
		MapGraphics[32][0]=0;
		MapGraphics[32][1]=15;
		MapGraphics[33][0]=0;
		MapGraphics[33][1]=17;
		MapGraphics[34][0]=0;
		MapGraphics[34][1]=18;
		MapGraphics[35][0]=0;
		MapGraphics[35][1]=12;
		MapGraphics[36][0]=0;
		MapGraphics[36][1]=19;
		MapGraphics[37][0]=0;
		MapGraphics[37][1]=30;
		MapGraphics[38][0]=0;
		MapGraphics[38][1]=31;
		MapGraphics[39][0]=4;
		MapGraphics[39][1]=21;
		MapGraphics[40][0]=26;
		MapGraphics[40][1]=27;
		MapGraphics[41][0]=26;
		MapGraphics[41][1]=27;
		MapGraphics[42][0]=22;
		MapGraphics[42][1]=28;
		MapGraphics[43][0]=22;
		MapGraphics[43][1]=23;
	

	curtiles=MapGraphics[select[8]][0];
	curtiles2=MapGraphics[select[8]][1];

	r=0;

	//int last[3];

	int k;

	bool wait=true;
	
	if(!single)
	while(r!=0xFF){
		fscanf(fp,"%c",&r);
		if(r!=0xFF){
			MapTele[NumMapTele][0]=r;
			fscanf(fp,"%c",&r);
			MapTele[NumMapTele][1]=r;
			fscanf(fp,"%c",&r);
			MapTele[NumMapTele][2]=r;
			fscanf(fp,"%c",&r);
			MapTele[NumMapTele][3]=r;
			fscanf(fp,"%c",&r);
			MapTele[NumMapTele][4]=r;
			fscanf(fp,"%c",&r);
			MapTele[NumMapTele][5]=r;
			fscanf(fp,"%c",&r);
			MapTele[NumMapTele][6]=r;
			fscanf(fp,"%c",&r);
			MapTele[NumMapTele][7]=r;
			NumMapTele++;
			/*
			i = r;
			fscanf(fp,"%c",&r);
			j = r;
			fscanf(fp,"%c",&r);
			j = r * MapSize[i][0] + j;
			fscanf(fp,"%c",&r);
			if(wait){
				wait=!wait;
			} else {
				MapTele[last[0]][last[1]][0]=i;
				MapTele[last[0]][last[1]][1]=j;
				MapTele[last[0]][last[1]][2]=r;
				MapTele[i][j][0]=last[0];
				MapTele[i][j][1]=last[1];
				MapTele[i][j][2]=last[2];
				wait=!wait;
			}
			last[0]=i;
			last[1]=j;
			last[2]=r;*/
		}
	}

	fseek(fp,0x138BC,SEEK_SET);
	fscanf(fp,"%c",&r);

	if(!single||submode[mode]==2)
	if(r!=0x4E){
		if(!single)BaseChests(-1);
		else BaseChests(select[mode]);
	} else {
		i=0;
		j=0;
		k=0;
		fseek(fp,0x1A6300,SEEK_SET);
		fscanf(fp,"%c",&r);
		while(r!=0xFF){
			fscanf(fp,"%c",&i);
			fscanf(fp,"%c",&j);
			fscanf(fp,"%c",&k);
			if(!single||r==select[mode])MapChest[r][i+j*MapSize[r][0]]=k;
			fscanf(fp,"%c",&k);
			if(!single||r==select[mode]){
				MapGold[r][i+j*MapSize[r][0]]=k;
				if(MapChest[r][i+j*MapSize[r][0]]>128){
					MapGold[r][i+j*MapSize[r][0]]+=(MapChest[r][i+j*MapSize[r][0]]&0x7F)*256;
					MapChest[r][i+j*MapSize[r][0]]=128;
				}
			}
			fscanf(fp,"%c",&r);
		}
	}

	fseek(fp,0x17CEC,SEEK_SET);
	fscanf(fp,"%c",&r);

	if(!single||submode[mode]==2)
	if(r!=0x4E && r!=0x68){
		if(!single)BaseRead(-1);
		else BaseRead(select[mode]);
	} else {
		i=0;
		j=0;
		k=0;
		fseek(fp,0x1A6890,SEEK_SET);
		fscanf(fp,"%c",&r);
		while(r!=0xFF){
			fscanf(fp,"%c",&i);
			fscanf(fp,"%c",&j);
			fscanf(fp,"%c",&k);
			if(!single||r==select[mode])MapRead[r][i+j*MapSize[r][0]]=k*256;
			fscanf(fp,"%c",&k);
			if(!single||r==select[mode])MapRead[r][i+j*MapSize[r][0]]+=k;
			fscanf(fp,"%c",&r);
		}
	}

	fclose(fp);
	sprintf(file,path);
}

void ImportMap(char *path){
	MapChanged = true;
	FILE * fp = fopen(path,"rb");
	char in;
	int i;
	for(i=0; i<54; i++){
		int j=0;
		while(true){
			fscanf(fp,"%c",&in);
			if(in==-1||feof(fp)){
				fscanf(fp,"%c",&in);
				break;
			}
			Sprites[i][j][0]=in;
			for(int k=0;k<5;k++){
				fscanf(fp,"%c",&(Sprites[i][j][k+1]));
			}
			j++;
		}
		NumSprites[i]=j;
	}
	for(i=0; i<8; i++){
		for(int j=0; j<32; j++){
			for(int k=0; k<4; k++){
				fscanf(fp,"%c",&in);
				if(feof(fp))return;
				Chests[i][31-j][k]=in;
			}
		}
	}

	fclose(fp);
}

void MapImport(){
	int ret=IDYES;
	OPENFILENAME openFileName;
	char path[256];
	path[0] = '\0';    
	memset( &openFileName, 0, sizeof(openFileName) );
	openFileName.lStructSize = sizeof(openFileName);
	openFileName.hwndOwner = NULL;
	openFileName.hInstance = NULL;
	openFileName.lpstrFilter = "Shining Force Maps(*.sfma)\0*.sfma\0";
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
	openFileName.lpstrDefExt = "sfma";
	openFileName.lCustData = NULL;
	openFileName.lpfnHook = NULL;
	openFileName.lpTemplateName = NULL;

	if(GetOpenFileName(&openFileName)!=0){
		ImportMap(path);
	}
}

void AddTele(int event, int x, int y, int map, int spec, int x2, int y2, int map2, int spec2){
	MapTele[NumMapTele][0]=map;
	MapTele[NumMapTele][1]=x;
	MapTele[NumMapTele][2]=y;
	MapTele[NumMapTele][3]=spec;
	MapTele[NumMapTele][4]=map2;
	MapTele[NumMapTele][5]=x2;
	MapTele[NumMapTele][6]=y2;
	MapTele[NumMapTele][7]=spec2;
	NumMapTele++;
}

int FindTele(int event, int x, int y, int map, bool load=true){
	int i;
	for(i=0;i<NumMapTele;i++){
		if(MapTele[i][0]==map&&MapTele[i][1]==x&&MapTele[i][2]==y){
			if(load){
				subselect[mode][4]=MapTele[i][4];
				subselect[mode][5]=MapTele[i][5];
				subselect[mode][6]=MapTele[i][6];
				subselect[mode][7]=MapTele[i][7];
			}
			return i;
		}
	}
	for(i=0;i<NumMapTele;i++){
		if(MapTele[i][4]==map&&MapTele[i][5]==x&&MapTele[i][6]==y){
			if(load){
				subselect[mode][4]=MapTele[i][0];
				subselect[mode][5]=MapTele[i][1];
				subselect[mode][6]=MapTele[i][2];
				subselect[mode][7]=MapTele[i][3];
			}
			return -1*i;
		}
	}
	return 1024;
}

void SetTele(int event, int x, int y, int map, int x2, int y2, int map2, int spec2){
	int i = FindTele(event, x, y, map, false);
	int temp[4];
	if(i>0){
		temp[0]=MapTele[i][4];
		temp[1]=MapTele[i][5];
		temp[2]=MapTele[i][6];
		temp[3]=MapTele[i][7];
		MapTele[i][4]=map2;
		MapTele[i][5]=x2;
		MapTele[i][6]=y2;
		MapTele[i][7]=spec2;
		if(FindTele(event, temp[1], temp[2], temp[0], false)==1024){
			AddTele(event,temp[1],temp[2],temp[0],temp[3],x,y,map,MapTele[i][3]);
		}
	} else {
		i*=-1;
		temp[0]=MapTele[i][0];
		temp[1]=MapTele[i][1];
		temp[2]=MapTele[i][2];
		temp[3]=MapTele[i][3];
		MapTele[i][0]=map2;
		MapTele[i][1]=x2;
		MapTele[i][2]=y2;
		MapTele[i][3]=spec2;
		if(FindTele(event, temp[1], temp[2], temp[0], false)==1024){
			AddTele(event,temp[1],temp[2],temp[0],temp[3],x,y,map,MapTele[i][3]);
		}
	}
}

void ClearTele(int event, int x, int y, int map, bool load=true){
	int i = FindTele(event, x, y, map, false);
	if(i!=1024){
		MapTele[i][0]=-1;
	}
}

void BaseChests(int target=-1){
	AddChest(0,42,5,63,0,target);
	AddChest(0,41,7,5,0,target);
	AddChest(0,43,7,6,0,target);
	AddChest(0,41,8,128,50,target);
	AddChest(0,43,8,4,0,target);
	AddChest(0,41,9,2,0,target);
	AddChest(0,43,9,0,0,target);
	AddChest(2,31,18,63,0,target);
	AddChest(3,31,18,63,0,target);
	AddChest(4,9,5,0,0,target);
	AddChest(4,52,5,63,0,target);
	AddChest(4,52,6,128,70,target);
	AddChest(4,54,6,40,0,target);
	AddChest(4,56,8,1,0,target);
	AddChest(4,37,15,1,0,target);
	AddChest(4,52,16,63,0,target);
	AddChest(4,52,17,30,0,target);
	AddChest(4,52,18,63,0,target);
	AddChest(4,56,19,1,0,target);
	AddChest(4,11,21,63,0,target);
	AddChest(4,22,25,5,0,target);
	AddChest(4,32,28,63,0,target);
	AddChest(4,33,28,128,50,target);
	AddChest(4,34,34,1,0,target);
	AddChest(4,35,34,128,50,target);
	AddChest(5,9,5,9,0,target);
	AddChest(5,9,6,30,0,target);
	AddChest(5,11,6,128,100,target);
	AddChest(5,13,6,53,0,target);
	AddChest(5,9,7,6,0,target);
	AddChest(5,53,11,63,0,target);
	AddChest(5,52,13,63,0,target);
	AddChest(5,53,13,128,50,target);
	AddChest(5,7,16,59,0,target);
	AddChest(5,8,18,1,0,target);
	AddChest(5,5,25,63,0,target);
	AddChest(6,25,22,63,0,target);
	AddChest(6,30,24,12,0,target);
	AddChest(6,15,38,63,0,target);
	AddChest(9,12,17,9,0,target);
	AddChest(9,36,17,63,0,target);
	AddChest(9,37,17,7,0,target);
	AddChest(9,15,28,63,0,target);
	AddChest(9,32,28,31,0,target);
	AddChest(10,32,17,36,0,target);
	AddChest(10,33,17,32,0,target);
	AddChest(10,11,22,63,0,target);
	AddChest(10,21,28,63,0,target);
	AddChest(14,12,34,63,0,target);
	AddChest(14,16,34,63,0,target);
	AddChest(30,17,5,63,0,target);
	AddChest(30,21,6,63,0,target);
	AddChest(31,25,5,3,0,target);
	AddChest(31,48,17,33,0,target);
	AddChest(31,2,21,63,0,target);
	AddChest(31,25,21,44,0,target);
	AddChest(31,16,35,63,0,target);
	AddChest(32,4,9,3,0,target);
	AddChest(32,5,9,13,0,target);
	AddChest(32,13,9,9,0,target);
	AddChest(32,15,9,6,0,target);
	AddChest(32,16,9,0,0,target);
	AddChest(32,53,46,63,0,target);
	AddChest(33,39,6,1,0,target);
	AddChest(33,40,6,55,0,target);
	AddChest(33,8,23,63,0,target);
	AddChest(33,12,23,63,0,target);
	AddChest(36,43,23,8,0,target);
	AddChest(36,18,24,47,0,target);
	AddChest(36,38,48,63,0,target);
	AddChest(36,39,48,43,0,target);
	AddChest(36,45,48,63,0,target);
	AddChest(36,46,48,63,0,target);
}

void AddChest(int map, int x, int y, int i, int g, int t){
	if(t!=-1&&t!=map)return;
	MapChest[map][x+y*MapSize[map][0]]=i;
	MapGold[map][x+y*MapSize[map][0]]=g;
}

void BaseRead(int target=-1){
	AddRead(0,12,5,578,target);
	AddRead(0,13,5,579,target);
	AddRead(0,14,5,580,target);
	AddRead(0,17,5,581,target);
	AddRead(0,11,29,582,target);
	AddRead(2,7,2,570,target);
	AddRead(2,18,2,571,target);
	AddRead(2,50,5,572,target);
	AddRead(2,37,13,573,target);
	AddRead(2,26,19,574,target);
	AddRead(2,31,22,575,target);
	AddRead(2,11,23,576,target);
	AddRead(2,28,31,577,target);
	AddRead(3,7,2,570,target);
	AddRead(3,18,2,571,target);
	AddRead(3,50,5,572,target);
	AddRead(3,37,13,573,target);
	AddRead(3,26,19,574,target);
	AddRead(3,31,22,575,target);
	AddRead(3,11,23,576,target);
	AddRead(3,28,31,577,target);
	AddRead(4,33,5,583,target);
	AddRead(4,38,15,584,target);
	AddRead(4,19,18,585,target);
	AddRead(4,11,25,586,target);
	AddRead(4,9,34,587,target);
	AddRead(4,29,34,588,target);
	AddRead(4,31,34,589,target);
	AddRead(4,18,35,590,target);
	AddRead(4,54,44,591,target);
	AddRead(5,51,4,592,target);
	AddRead(5,46,5,593,target);
	AddRead(5,50,10,594,target);
	AddRead(5,24,15,595,target);
	AddRead(6,50,4,596,target);
	AddRead(6,21,5,597,target);
	AddRead(6,7,8,598,target);
	AddRead(6,8,8,599,target);
	AddRead(6,12,8,600,target);
	AddRead(6,13,8,601,target);
	AddRead(6,29,8,602,target);
	AddRead(6,30,8,603,target);
	AddRead(6,48,16,604,target);
	AddRead(6,49,16,605,target);
	AddRead(6,7,21,606,target);
	AddRead(6,22,22,607,target);
	AddRead(6,51,28,608,target);
	AddRead(6,22,30,609,target);
	AddRead(6,24,30,610,target);
	AddRead(6,8,33,611,target);
	AddRead(6,16,43,612,target);
	AddRead(6,9,44,613,target);
	AddRead(6,22,44,614,target);
	AddRead(7,17,11,655,target);
	AddRead(7,58,15,656,target);
	AddRead(7,62,15,657,target);
	AddRead(7,64,17,658,target);
	AddRead(7,31,19,659,target);
	AddRead(7,32,19,660,target);
	AddRead(7,48,29,661,target);
	AddRead(7,25,33,662,target);
	AddRead(8,1,23,636,target);
	AddRead(8,2,23,637,target);
	AddRead(8,3,23,638,target);
	AddRead(8,4,23,639,target);
	AddRead(8,1,25,640,target);
	AddRead(8,2,25,641,target);
	AddRead(8,3,25,642,target);
	AddRead(8,6,26,643,target);
	AddRead(8,1,27,644,target);
	AddRead(8,2,27,645,target);
	AddRead(8,3,27,646,target);
	AddRead(8,6,27,647,target);
	AddRead(8,15,30,648,target);
	AddRead(8,16,30,649,target);
	AddRead(8,17,30,650,target);
	AddRead(8,12,31,651,target);
	AddRead(8,3,34,652,target);
	AddRead(8,5,34,653,target);
	AddRead(8,17,34,654,target);
	AddRead(9,15,6,663,target);
	AddRead(9,39,10,664,target);
	AddRead(9,24,17,665,target);
	AddRead(9,33,17,666,target);
	AddRead(9,43,17,667,target);
	AddRead(9,43,18,668,target);
	AddRead(9,43,19,669,target);
	AddRead(10,27,6,670,target);
	AddRead(10,19,11,671,target);
	AddRead(10,10,12,672,target);
	AddRead(10,29,17,673,target);
	AddRead(10,39,17,674,target);
	AddRead(10,39,18,675,target);
	AddRead(10,39,19,676,target);
	AddRead(10,13,22,677,target);
	AddRead(13,7,9,615,target);
	AddRead(13,12,9,616,target);
	AddRead(13,14,12,617,target);
	AddRead(13,11,15,618,target);
	AddRead(13,20,16,619,target);
	AddRead(13,21,16,620,target);
	AddRead(13,15,17,621,target);
	AddRead(13,26,18,622,target);
	AddRead(13,27,18,623,target);
	AddRead(13,28,18,624,target);
	AddRead(13,17,21,625,target);
	AddRead(13,23,21,626,target);
	AddRead(13,25,21,627,target);
	AddRead(13,10,22,628,target);
	AddRead(13,35,41,629,target);
	AddRead(13,46,42,630,target);
	AddRead(13,30,46,631,target);
	AddRead(13,35,47,632,target);
	AddRead(13,50,49,633,target);
	AddRead(13,33,50,634,target);
	AddRead(13,33,51,635,target);
	AddRead(14,38,6,730,target);
	AddRead(14,15,8,731,target);
	AddRead(14,16,8,732,target);
	AddRead(14,8,18,733,target);
	AddRead(14,15,24,734,target);
	AddRead(14,6,26,735,target);
	AddRead(14,9,26,736,target);
	AddRead(14,26,26,737,target);
	AddRead(14,30,27,738,target);
	AddRead(14,39,31,739,target);
	AddRead(14,11,36,740,target);
	AddRead(14,17,36,741,target);
	AddRead(14,26,37,742,target);
	AddRead(16,7,29,743,target);
	AddRead(16,15,29,744,target);
	AddRead(16,9,30,745,target);
	AddRead(16,13,30,746,target);
	AddRead(16,11,47,747,target);
	AddRead(29,33,18,678,target);
	AddRead(29,34,18,679,target);
	AddRead(30,18,8,708,target);
	AddRead(30,20,8,709,target);
	AddRead(30,23,12,710,target);
	AddRead(30,27,13,711,target);
	AddRead(30,18,15,712,target);
	AddRead(30,7,19,713,target);
	AddRead(30,26,20,714,target);
	AddRead(30,14,25,715,target);
	AddRead(31,41,17,700,target);
	AddRead(31,30,18,701,target);
	AddRead(31,31,18,702,target);
	AddRead(31,51,21,703,target);
	AddRead(31,52,21,704,target);
	AddRead(31,16,29,705,target);
	AddRead(31,49,30,706,target);
	AddRead(32,20,8,680,target);
	AddRead(32,1,19,681,target);
	AddRead(32,7,20,682,target);
	AddRead(32,11,20,683,target);
	AddRead(32,25,20,684,target);
	AddRead(32,28,47,685,target);
	AddRead(33,20,19,686,target);
	AddRead(33,7,25,687,target);
	AddRead(33,13,25,688,target);
	AddRead(33,20,26,689,target);
	AddRead(33,44,34,690,target);
	AddRead(33,18,41,691,target);
	AddRead(33,27,41,692,target);
	AddRead(33,30,41,693,target);
	AddRead(33,31,41,694,target);
	AddRead(33,16,42,695,target);
	AddRead(33,17,42,696,target);
	AddRead(33,1,44,697,target);
	AddRead(33,40,46,698,target);
	AddRead(33,17,47,699,target);
	AddRead(34,39,3,716,target);
	AddRead(34,45,3,717,target);
	AddRead(34,16,20,718,target);
	AddRead(34,32,23,719,target);
	AddRead(34,48,23,720,target);
	AddRead(34,10,40,721,target);
	AddRead(34,11,40,722,target);
	AddRead(34,13,40,723,target);
	AddRead(34,9,41,724,target);
	AddRead(34,13,41,725,target);
	AddRead(34,8,42,726,target);
	AddRead(34,11,42,727,target);
	AddRead(34,12,42,728,target);
	AddRead(34,33,55,729,target);
}

void AddRead(int map, int x, int y, int m, int t){
	if(t!=-1&&t!=map)return;
	MapRead[map][x+y*MapSize[map][0]]=m;
}

void CountMapSprites() {
	unsigned char sort[32][6];
	unsigned char sort2[32][6];
	int min = 10000;
	int mini = -1;

	for (int i = 0; i < 54; i++) {
		for (int j = 0; j < NumSprites[i]; j++) {
			for (int k = 0; k < 6; k++) {
				sort[j][k] = Sprites[i][j][k];
			}
		}

		for (int n = 0; n < NumSprites[i]; n++) {
			min = 1000;
			for (int j = 0; j < NumSprites[i]; j++) {
				if (sort[j][3] < min) {
					min = sort[j][3];
					mini = j;
				}
			}
			for (int k = 0; k < 6; k++) {
				sort2[n][k] = sort[mini][k];
			}
			sort[mini][3] = 255;
		}

		UniSprites[i] = 1;

		for (int n = 1; n < NumSprites[i]; n++) {
			if (sort2[n][3] != sort2[n - 1][3])UniSprites[i]++;
		}
	}
}