unsigned char Range[256][8];
unsigned char NumRanges;

long RangeOffset=0;
long AreaOffset=0;
long RangeDataOffset=0;
bool ExtendRange=false;
bool ExtendArea=false;
unsigned char MaxRange=0;

char RangeShapes[][16] = { "Standard", "Plus", "Horizontal", "Vertical", "Block", "Diagonals", "Star" };
char AreaShapes[][16] =  { "1 Square", "5 Squares", "13 Squares", "3x3 Block", "Ring", "2 Square Line", "3 Square Line", "4 Square Line","X" };
char RangeGroups[][16] = { "None", "Allies", "Enemies", "Both","None","All Allies", "All Enemies", "Everyone" };

#define NUM_RANGE_ROUTINES 19

char RangeRoutines[][32] = { "Default (Use Effect)", "Egress", "Level Party", "Laser Eye","+ATT (Equip Effect)", "+DEF (Equip Effect)"
	, "+AGI (Equip Effect)", "+MOVE (Equip Effect)", "+ATT/CRIT (Equip Effect)", "+ATT/DEF (Equip Effect)", "+Jogurt (Equip Effect)"
	, "Nothing (Equip Effect)", "+HP (Unused)", "+MP (Unused)", "+Max HP (Unused)", "+ATK (Unused)"
	, "+DEF (Unused)", "+AGI (Unused)", "+MOVE (Unused)" };
long RangeRoutineOffsets[] = { 0x20C1C,0x23524,0x2352A,0x20BDC,0x23418,0x23426,0x23434,0x23442,0x234B2,0x234CA,0x2350A,0x23378,0x23450,0x2345E
	,0x2346C,0x2347A,0x23488,0x23496,0x234A4 };


unsigned char RangeRoutine = -1;
unsigned char RangeShape = -1;
unsigned char RangeArea = -1;

bool RangePreview = true;

void LoadRange(char *path, bool single=false){
	unsigned char r,c;
	FILE * fp = fopen(path,"rb");
	char in=0;
	long lo;
	short sh;
	unsigned short ush;

	fseek(fp,143466,SEEK_SET);
	fscanf(fp,"%c",&in);
	if(in==0x43){
		RangeDataOffset=0x23178;
	} else {
		fscanf(fp,"%c",&in);
		fscanf(fp,"%c",&r);
		RangeDataOffset = r;
		fscanf(fp,"%c",&r);
		RangeDataOffset = RangeDataOffset*256+r;
		fscanf(fp,"%c",&r);
		RangeDataOffset = RangeDataOffset*256+r;
		fscanf(fp,"%c",&r);
		RangeDataOffset = RangeDataOffset*256+r;
	}

	if(RangeDataOffset==0x23178){
		fseek(fp,RangeDataOffset,SEEK_SET);
		for(int i=0;i<64;i++){
			for(int j=0;j<8;j++){
				if(single&&i!=subfocus+32*select[mode]){
					fscanf(fp,"%c",&c);
					continue;
				}
				fscanf(fp,"%c",&(Range[i][j]));
			}
		}
		NumRanges=64;
	} else {
		fseek(fp,RangeDataOffset+12,SEEK_SET);
		int i=0;
		int j;
		while(i<256){
			for(j=0;j<4;j++){
				if(single&&i!=select[mode]){
					fscanf(fp,"%c",&c);
					continue;
				}
				fscanf(fp,"%c",&(Range[i][j]));
			}
			if(Range[i][0]==255){
				break;
			}
			fscanf(fp,"%c",&in);
			fscanf(fp,"%c",&in);
			if(!single||i==select[mode])Range[i][4]=0x60;
			if(!single||i==select[mode])Range[i][5]=0;
			fscanf(fp,"%c",&r);
			lo = r;
			fscanf(fp,"%c",&r);
			lo = lo*256+r;
			fscanf(fp,"%c",&r);
			lo = lo*256+r;
			fscanf(fp,"%c",&r);
			lo = lo*256+r;

			sh = lo - (0x23178 + i*8 + 6); 
			ush = (unsigned short)sh;
			if(!single||i==select[mode])Range[i][6]=(ush-ush%0x100)/0x100;
			if(!single||i==select[mode])Range[i][7]=ush%0x100;

			for(j=0;j<6;j++){
				fscanf(fp,"%c",&in);
			}
			i++;
		}
		if(!single)NumRanges=i;
	}

	fseek(fp,132710,SEEK_SET);
	fscanf(fp,"%c",&in);
	if(in==0x4E){
		ExtendRange=true;
		fscanf(fp,"%c",&in);
		fscanf(fp,"%c",&r);
		RangeOffset = r;
		fscanf(fp,"%c",&r);
		RangeOffset = RangeOffset*256+r;
		fscanf(fp,"%c",&r);
		RangeOffset = RangeOffset*256+r;
		fscanf(fp,"%c",&r);
		RangeOffset = RangeOffset*256+r;
	}
	else ExtendRange=false;

	fseek(fp,143515,SEEK_SET);
	fscanf(fp,"%c",&MaxRange);

	if(ExtendRange){
		fseek(fp,143552,SEEK_SET);
		fscanf(fp,"%c",&in);
		if(in==0x02){
			ExtendArea = false;
			AreaOffset = 0;
		} else {
			ExtendArea = true;
			fscanf(fp,"%c",&in);
			fscanf(fp,"%c",&r);
			AreaOffset = r;
			fscanf(fp,"%c",&r);
			AreaOffset = AreaOffset*256+r;
			fscanf(fp,"%c",&r);
			AreaOffset = AreaOffset*256+r;
			fscanf(fp,"%c",&r);
			AreaOffset = AreaOffset*256+r;
		}
	} else {
		ExtendArea = false;
		AreaOffset = 0;
	}

	fclose(fp);
	sprintf(file,path);
}

void ImportRange(char *path){
	FILE * fp = fopen(path,"rb");
	char in=0;

	for(int i=0;i<64;i++){
		for(int j=0;j<8;j++){
			fscanf(fp,"%c",&(Range[i][j]));
		}
	}

	fscanf(fp,"%c",&MaxRange);

	fclose(fp);
}

void RangeImport(){
	int ret=IDYES;
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
	openFileName.Flags = OFN_LONGNAMES | OFN_PATHMUSTEXIST;
	openFileName.nFileOffset = 0;
	openFileName.nFileExtension = 0;
	openFileName.lpstrDefExt = "sfr";
	openFileName.lCustData = NULL;
	openFileName.lpfnHook = NULL;
	openFileName.lpTemplateName = NULL;

	if(GetOpenFileName(&openFileName)!=0){
		ImportRange(path);
	}
}