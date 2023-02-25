unsigned char IconPalette[16][3];
unsigned char FMSPalette[16][3];
unsigned char EMSPalette[16][3];
unsigned char ESPalette[80][4][16][3];
unsigned char NumESPalette[80];
unsigned char ISPalette[128][4][3];
unsigned char TSPalette[27][16][3];
unsigned char FSPalette[80][8][16][3];
unsigned char NumFSPalette[80];
unsigned char BGPalette[78][4][16][3];
unsigned char NumBGPalette[78];

int NumGFX[];

bool GFXPaletteEdit = false;

double round(double d){
	return floor(d+0.5);
}

unsigned char GenToRGB(unsigned char c) {
	return round(c * 255 / 14.0);
}

unsigned char RGBToGen(unsigned char c) {
	return (unsigned char)round(((int)c) * 14 / 255.0);
}

void readPalette(unsigned char data[][3],int size,FILE * fp){
	int i;
	unsigned int in=0;
	for(i=0; i<size; i++){
		fscanf(fp,"%c",&in);
		data[i][2]=round(in*255/14.0);
		fscanf(fp,"%c",&in);
		data[i][0]=round((in%16)*255/14.0);
		in-=in%16;
		in/=16;
		data[i][1]=round(in*255/14.0);
	}
	in=-1;
	for(i=1;i<size;i++){
		for(int j=0;j<i;j++){
			if(data[i][0]==data[j][0]&&data[i][1]==data[j][1]&&data[i][2]==data[j][2]){
				if(data[i][0]<248)data[i][0]++;
				else data[i][0]--;
				if(data[i][1]<248)data[i][1]++;
				else data[i][1]--;
				if(data[i][2]<248)data[i][2]++;
				else data[i][2]--;
				i--;
			}
		}
	}
}

void writePalette(unsigned char data[][3],int size,FILE * fp){
	unsigned int in=0;
	unsigned char a, b;
	for(int i=0; i<size; i++){
		a = (unsigned char)round(((int)data[i][2]) * 14 / 255.0);
		if (a % 2)a--;
		fprintf(fp,"%c",a);

		a = (unsigned char)round(((int)data[i][1]) * 14 / 255.0);
		if (a % 2)a--;
		b = (unsigned char)round(((int)data[i][0]) * 14 / 255.0);
		if (a % 2)a--;

		fprintf(fp,"%c",a*16+b);
	}
}

void chooseColor(COLORREF &c){
	CHOOSECOLOR cc;                 // common dialog box structure 
	static COLORREF acrCustClr[16]; // array of custom colors 

	// Initialize CHOOSECOLOR 
	ZeroMemory(&cc, sizeof(cc));
	cc.lStructSize = sizeof(cc);
	cc.hwndOwner = hwnd;
	cc.lpCustColors = (LPDWORD) acrCustClr;
	cc.rgbResult = c;
	cc.Flags = CC_FULLOPEN | CC_RGBINIT;
 
	unsigned char r,g,b;

	if (ChooseColor(&cc)==TRUE) 
	{
		c = cc.rgbResult; 

		r = (unsigned char)round(((int)GetRValue(c)) * 14 / 255.0);
		if (r % 2)r--;
		g = (unsigned char)round(((int)GetGValue(c)) * 14 / 255.0);
		if (g % 2)g--;
		b = (unsigned char)round(((int)GetBValue(c)) * 14 / 255.0);
		if (b % 2)b--;

		r = round(r * 255 / 14.0);
		g = round(g * 255 / 14.0);
		b = round(b * 255 / 14.0);

		c = RGB(r, g, b);
	}
}

unsigned char reduceColor(unsigned char c) {
	c = (unsigned char)round((int)(c) * 14 / 255.0);
	if (c % 2)c--;

	c = round(c * 255 / 14.0);
	return c;
}

void reducePalette(unsigned char pal[][3]) {
	for (int i = 0; i < 16; i++) {
		pal[i][0] = reduceColor(pal[i][0]);
		pal[i][1] = reduceColor(pal[i][1]);
		pal[i][2] = reduceColor(pal[i][2]);
	}
}

void LoadPalette(char *path){
	unsigned char r;
	unsigned int in=0;
	int o,o2;

	unsigned int pal[2];
	unsigned int frame[16];

	FILE * fp = fopen(path,"rb");

	fseek(fp,14732,SEEK_SET);
	readPalette(IconPalette,16,fp);
	
	fseek(fp,39438,SEEK_SET);
	readPalette(FMSPalette,16,fp);
	readPalette(EMSPalette,16,fp);

	//fseek(fp, 0xC57C4, SEEK_SET);
	//readPalette(TitlePalette, 16, fp);

	fseek(fp,0x100000,SEEK_SET);
	fscanf(fp,"%c",&r);
	o = r;
	fscanf(fp,"%c",&r);
	o = o*256+r;
	fscanf(fp,"%c",&r);
	o = o*256+r;
	fscanf(fp,"%c",&r);
	o = o*256+r;

	int s;
	for(s=0;s<NumGFX[1];s++){

		fseek(fp,o,SEEK_SET);
		fscanf(fp,"%c",&r);
		o2 = r;
		fscanf(fp,"%c",&r);
		o2 = o2*256+r;
		fscanf(fp,"%c",&r);
		o2 = o2*256+r;
		fscanf(fp,"%c",&r);
		o2 = o2*256+r;
		o+=4;

		if (ExpandedGraphics)o2 += 0x200000;

		fseek(fp,o2,SEEK_SET);
		for(int i=0;i<2;i++){
			fscanf(fp,"%c",&r);
			pal[i]=r;
			fscanf(fp,"%c",&r);
			pal[i]=pal[i]*256+r;
		}

		frame[0]=0;
		fscanf(fp,"%c",&r);
		frame[0]=r;
		fscanf(fp,"%c",&r);
		frame[0]=frame[0]*256+r;

		NumESPalette[s]=(frame[0]-pal[1])/32;

		fseek(fp,o2+pal[1]+2,SEEK_SET);
		for(int p=0;p<NumESPalette[s];p++){
			readPalette(ESPalette[s][p],16,fp);
		}
	}
/*	for(int i=0;i<42;i++){
		fseek(fp,o,SEEK_SET);
		fscanf(fp,"%c",&r);
		o2 = r;
		fscanf(fp,"%c",&r);
		o2 = o2*256+r;
		fscanf(fp,"%c",&r);
		o2 = o2*256+r;
		fscanf(fp,"%c",&r);
		o2 = o2*256+r;
		fseek(fp,o2+2,SEEK_SET);
		fscanf(fp,"%c",&r);
		in = r*256;
		fscanf(fp,"%c",&r);
		in+=r;
		fscanf(fp,"%c",&r);
		fscanf(fp,"%c",&r);
		r=r-r%32;
		//numBSP[i]=r/32;
		numBSP[i]=2;
		fseek(fp,o2+in+2,SEEK_SET);
		for(int j=0;j<numBSP[i];j++){
			readPalette(BSPalette[i][j],16,fp);
		}
		o+=4;
	}*/

	fseek(fp, 0x14400C, SEEK_SET);
	fscanf(fp, "%c", &r);
	o = r;
	fscanf(fp, "%c", &r);
	o = o * 256 + r;
	fscanf(fp, "%c", &r);
	o = o * 256 + r;
	fscanf(fp, "%c", &r);
	o = o * 256 + r;

	fseek(fp, o,SEEK_SET);
	int i;
	if (NumItems == 128) {
		for (i = 0; i < 128; i++) {
			readPalette(ISPalette[i], 4, fp);
		}
	} else {
		for (i = 0; i < 63; i++) {
			readPalette(ISPalette[i], 4, fp);
		}
	}

	fseek(fp,0xB94CA,SEEK_SET);
	for(i=0;i<27;i++){
		readPalette(TSPalette[i]+1,15,fp);
		TSPalette[i][0][0]=0xFF;
		TSPalette[i][0][1]=0xFF;
		TSPalette[i][0][2]=0xFF;
	}

	fseek(fp,0x144000,SEEK_SET);
	fscanf(fp,"%c",&r);
	o = r;
	fscanf(fp,"%c",&r);
	o = o*256+r;
	fscanf(fp,"%c",&r);
	o = o*256+r;
	fscanf(fp,"%c",&r);
	o = o*256+r;

	for(s=0;s<NumGFX[0];s++){
		fseek(fp,o,SEEK_SET);
		fscanf(fp,"%c",&r);
		o2 = r;
		fscanf(fp,"%c",&r);
		o2 = o2*256+r;
		fscanf(fp,"%c",&r);
		o2 = o2*256+r;
		fscanf(fp,"%c",&r);
		o2 = o2*256+r;
		o+=4;

		if (ExpandedGraphics)o2 += 0x100000;

		fseek(fp,o2,SEEK_SET);
		for(int i=0;i<2;i++){
			fscanf(fp,"%c",&r);
			pal[i]=r;
			fscanf(fp,"%c",&r);
			pal[i]=pal[i]*256+r;
		}

		frame[0]=0;
		fscanf(fp,"%c",&r);
		frame[0]=r;
		fscanf(fp,"%c",&r);
		frame[0]=frame[0]*256+r;

		NumFSPalette[s]=(frame[0]-pal[1])/32;

		fseek(fp,o2+pal[1]+2,SEEK_SET);
		for(int p=0;p<NumFSPalette[s];p++){
			readPalette(FSPalette[s][p],16,fp);
		}
	}

	fseek(fp, 0xCC000, SEEK_SET);
	fscanf(fp, "%c", &r);
	o = r;
	fscanf(fp, "%c", &r);
	o = o * 256 + r;
	fscanf(fp, "%c", &r);
	o = o * 256 + r;
	fscanf(fp, "%c", &r);
	o = o * 256 + r;

	bool etemp;

	for (s = 0; s < NumGFX[3]; s++) {

		fseek(fp, o, SEEK_SET);
		fscanf(fp, "%c", &r);
		o2 = r;
		fscanf(fp, "%c", &r);
		o2 = o2 * 256 + r;
		fscanf(fp, "%c", &r);
		o2 = o2 * 256 + r;
		fscanf(fp, "%c", &r);
		o2 = o2 * 256 + r;
		o += 4;

		if (!s) {
			if (o2 == 0x3B0000)etemp = true;
			else etemp = false;
		}

		if (etemp)o2 += 0x200000;

		fseek(fp, o2, SEEK_SET);
		readPalette(BGPalette[s][0], 16, fp);
	}
				


	fclose(fp);
	sprintf(file,path);
}

void ImportPalette(char *path){
	FILE * fp = fopen(path,"rb");

	readPalette(IconPalette,16,fp);
	
	readPalette(FMSPalette,16,fp);
	readPalette(EMSPalette,16,fp);

	int i;
	for(i=0;i<50;i++){
		for(int j=0;j<NumESPalette[i];j++){
			readPalette(ESPalette[i][j],16,fp);
		}
	}

	for(i=0;i<63;i++){
		readPalette(ISPalette[i],4,fp);
	}

	for(i=0;i<24;i++){
		readPalette(TSPalette[i],15,fp);
	}

	fclose(fp);
}

void PaletteImport(){
	int ret=IDYES;
	OPENFILENAME openFileName;
	char path[256];
	path[0] = '\0';    
	memset( &openFileName, 0, sizeof(openFileName) );
	openFileName.lStructSize = sizeof(openFileName);
	openFileName.hwndOwner = NULL;
	openFileName.hInstance = NULL;
	openFileName.lpstrFilter = "Shining Force Palettes(*.sfp)\0*.sfp\0";
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
	openFileName.lpstrDefExt = "sfp";
	openFileName.lCustData = NULL;
	openFileName.lpfnHook = NULL;
	openFileName.lpTemplateName = NULL;

	if(GetOpenFileName(&openFileName)!=0){
		ImportPalette(path);
	}
}
