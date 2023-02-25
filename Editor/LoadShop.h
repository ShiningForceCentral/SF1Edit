int ShopItems[24][64];
unsigned char ShopTypes[24];

long ShopOffset;
bool ExtendShops;

char TownName[12][16] = {"Guardiana","Alterone","Rindo","Manarina","Bustoke","Pao","Urbantol","Waral","Rudo","Dragonia","Prompt","Runefaust"};

void LoadShop(char *path, bool single=false){

	unsigned char r,j,c;
	FILE * fp = fopen(path,"rb");

	fseek(fp,0x16F24,SEEK_SET);
	fscanf(fp,"%c",&r);
	if(r==0x4E){
		ExtendShops=true;
		ShopOffset=0x1C0266;
	} else {
		ExtendShops=false;
		ShopOffset=0x16F92;
	}


	fseek(fp,ShopOffset,SEEK_SET);

	if(!single){
		memset(ShopItems,-1,24*64*sizeof(int));
	} else {
		memset(ShopItems[select[mode]],-1,64*sizeof(int));
	}

	for(int i=0; i<12; i++){
		if(single&&i*2!=select[mode]){
			fscanf(fp,"%c",&c);
		} else {
			fscanf(fp,"%c",&(ShopTypes[i*2]));
		}
		fscanf(fp,"%c",&r);
		j=0;
		while(r!=255){
			if(!single||i*2==select[mode])ShopItems[i*2][j]=r;
			fscanf(fp,"%c",&r);
			j++;
		}
		if(single&&i*2+1!=select[mode]){
			fscanf(fp,"%c",&c);
		} else {
			fscanf(fp,"%c",&(ShopTypes[i*2+1]));
		}
		fscanf(fp,"%c",&r);
		j=0;
		while(r!=255){
			if(!single||i*2+1==select[mode])ShopItems[i*2+1][j]=r;
			fscanf(fp,"%c",&r);
			j++;
		}
	}

	fclose(fp);
	sprintf(file,path);
}

void ImportShop(char *path){
	unsigned char r,j;
	FILE * fp = fopen(path,"rb");

	memset(ShopItems,-1,24*64*sizeof(int));

	for(int i=0; i<12; i++){
		fscanf(fp,"%c",&(ShopTypes[i*2]));
		fscanf(fp,"%c",&r);
		j=0;
		while(r!=255){
			ShopItems[i*2][j]=r;
			fscanf(fp,"%c",&r);
			j++;
		}
		fscanf(fp,"%c",&(ShopTypes[i*2+1]));
		fscanf(fp,"%c",&r);
		j=0;
		while(r!=255){
			ShopItems[i*2+1][j]=r;
			fscanf(fp,"%c",&r);
			j++;
		}
	}

	fclose(fp);
}

void ShopImport(){
	int ret=IDYES;
	OPENFILENAME openFileName;
	char path[256];
	path[0] = '\0';    
	memset( &openFileName, 0, sizeof(openFileName) );
	openFileName.lStructSize = sizeof(openFileName);
	openFileName.hwndOwner = NULL;
	openFileName.hInstance = NULL;
	openFileName.lpstrFilter = "Shining Force Shops(*.sfsh)\0*.sfsh\0";
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
	openFileName.lpstrDefExt = "sfb";
	openFileName.lCustData = NULL;
	openFileName.lpfnHook = NULL;
	openFileName.lpTemplateName = NULL;

	if(GetOpenFileName(&openFileName)!=0){
		ImportShop(path);
	}
}

