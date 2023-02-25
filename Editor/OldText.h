struct Compressor{
	
	int StringNumber;
	unsigned char StringLength;
	unsigned long TreeOffset;
	unsigned long TreePointer;
	unsigned long DataPointer;
	unsigned long ScriptPointer;

	unsigned int TreeLength;
	unsigned int SymbolOffset;
	unsigned char Node;

	unsigned int Tree;
	unsigned int Length;
	unsigned int Symbol;

	FILE * file;
	char String[1024];
	char Result[1024];
	unsigned char Search;
	bool Start;

	unsigned char Pos;
	unsigned char temp[32];
	char tempc[32];
	unsigned long templ;
	unsigned long templ2;
	unsigned int StrLen;

	Compressor(FILE * fp){
		file=fp;
	}

	unsigned int PutString(char * text){
		sprintf(String,text);
		Pos=0;

		Tree = 0xC0;
		Length = 0;
		Symbol = 0;

		StrLen = strlen(String);

		Result[0]=0;

		bool Quote=false;

		for(unsigned int i=0;i<StrLen;i++){

			//check decoder flag?

			if(String[i]=='['||String[i]==0xC3){
				unsigned char j=1;
				while(String[i+j]!=']'){
					tempc[j-1]=String[i+j];
					j++;
				}
				tempc[j-1]=0;
				if(!strcmp(tempc,"Dict")){
					i+=5;
					String[i]=0xC1;
				}
				if(!strcmp(tempc,"Line")){
					i+=5;
					String[i]=0xC2;
				}
				if(!strcmp(tempc,"Delay2")){
					i+=7;
					String[i]=0xC4;
				}
				if(!strcmp(tempc,"Num")){
					i+=4;
					String[i]=0xC5;
				}
				if(!strcmp(tempc,"Name")){
					i+=5;
					String[i]=0xC6;
				}
				if(!strcmp(tempc,"Hero")){
					i+=5;
					String[i]=0xC8;
				}
				if(!strcmp(tempc,"Item")){
					i+=5;
					String[i]=0xCA;
				}
				if(!strcmp(tempc,"Spell")){
					i+=6;
					String[i]=0xCB;
				}
				if(!strcmp(tempc,"Wait2")){
					i+=6;
					String[i]=0xCD;
				}
				if(!strcmp(tempc,"Delay1")){
					i+=7;
					String[i]=0xCF;
				}
				if(!strcmp(tempc,"Class")){
					i+=6;
					String[i]=0xD2;
				}
			} else {
				sprintf(tempc,"%c",String[i]);

				String[i] = strstr(Symbols,tempc) - Symbols;

				if(tempc[0]=='"'){
					Quote=!Quote;
					//if(Quote)String[i]++;
					String[i]++;
				}
			}
			
			templ2 = Encode(String[i]);

			for(unsigned char b=0;b<templ2;b++){
				Result[Pos]*=2;
				if(templ&(1<<((templ2-b)-1)))Result[Pos]++;
				Length++;
				if(Length==8){
					Length=0;
					Pos++;
					Result[Pos]=0;
				}
			}


			Tree = String[i];
			Tree = Tree % 0x100;
		}

		templ2 = Encode(0xC0);

		for(unsigned char b=0;b<templ2;b++){
			Result[Pos]*=2;
			if(templ&(1<<((templ2-b)-1)))Result[Pos]++;
			Length++;
			if(Length==8){
				Length=0;
				Pos++;
				Result[Pos]=0;
			}
		}

		if(Length>0){
			Result[Pos]=Result[Pos]<<(8-Length);
			Pos++;
		}

		Result[Pos]=0;

		//fprintf(file,"%c",Pos);
		//fprintf(file,Result);

		return Pos;
	}

	unsigned long Encode(char c){
		unsigned char i;
		unsigned int BitLength;
		unsigned long Bits;

		Search = c;

		//fseek(file,0x13000C+Tree*2,SEEK_SET);
		fseek(file,0x1E892+Tree*2,SEEK_SET);
		TreeOffset = readword();

		//TreePointer = 0x1301B4 + TreeOffset;
		TreePointer = 0x1EA3A + TreeOffset;
		DataPointer = TreePointer;

		TreeLength = 0;
		SymbolOffset = 0;
		BitLength = 0;

		Start=false;

		Bits = FindSymbol(Bits,BitLength);

		if(!(Bits&(1<<(BitLength-1))))BitLength--;

		templ=Bits;

		return BitLength;
	}

	long FindSymbol(unsigned long Bits,unsigned int &BitLength){
		//check left branch
		if(TreeLength==0){
			TreeLength = 7;
			fseek(file,DataPointer,SEEK_SET);
			fscanf(file,"%c",&Node);
			DataPointer++;
		} else {
			TreeLength--;
		}
		temp[0]=Node;
		Node*=2;
		/*if(!Start){
			temp[0]=Node;
			Node*=2;
			Start=true;
		}*/
		if(temp[0]<128){//node is not a leaf, continue
			templ=FindSymbol(Bits,BitLength);
			if(templ!=0xFEDCBA98){
				BitLength++;
				return templ;
			}

		} else {//node is a leaf
			fseek(file,TreePointer+SymbolOffset-1,SEEK_SET);
			fscanf(file,"%c",&(temp[0]));

			if(temp[0]==Search){//found symbol
				BitLength++;
				return 0;
			} else {//not a match
				SymbolOffset--;
			}
		}
		//check right branch
		if(TreeLength==0){
			TreeLength = 7;
			fseek(file,DataPointer,SEEK_SET);
			fscanf(file,"%c",&Node);
			DataPointer++;
		} else {
			TreeLength--;
		}
		temp[0]=Node;
		Node*=2;
		if(temp[0]<128){//node is not a leaf, continue
			
			templ=FindSymbol(Bits,BitLength);
			if(templ!=0xFEDCBA98){
				return templ|(1<<BitLength++);
			}

		} else {//node is a leaf
			fseek(file,TreePointer+SymbolOffset-1,SEEK_SET);
			fscanf(file,"%c",&(temp[0]));

			if(temp[0]==Search){//found symbol
				BitLength++;
				return 1;
			} else {//not a match
				SymbolOffset--;
			}
		}
		return 0xFEDCBA98;
	}

	unsigned long readlong(){
		unsigned long t;
		fscanf(file,"%c%c%c%c",&(temp[0]),&(temp[1]),&(temp[2]),&(temp[3]));
		t=temp[0];
		t*=256;
		t+=temp[1];
		t*=256;
		t+=temp[2];
		t*=256;
		t+=temp[3];
		return t;
	}

	unsigned long readword(){
		unsigned long t;
		fscanf(file,"%c%c",&(temp[0]),&(temp[1]));
		t=temp[0];
		t*=256;
		t+=temp[1];
		return t;
	}

};

void SaveText(){
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
		unsigned char l;
		unsigned long pos,ppos;

		Compressor Com(fp);

		char test[32];


		TextOffset = 0x200000;//Option to choose?

		if(TextOffset>romsize-1){
			MessageBox(NULL,"Rom is too small, expand rom.","Error",MB_OK);
			fclose(fp);
			return;
		}

		pos = TextOffset;
		ppos = 0x13E906;

		for(unsigned int i=0;i<NUM_TEXT;i++){
			if(i%23==0){
				PatBlt(memdc, 0, 0, maxx, maxy, PATCOPY);
				sprintf(test,"Compressing: %d%%",(int)(100*i/NUM_TEXT));
				TextOut(memdc, 300, 250, test,strlen(test));
				BitBlt(hdc,0,0,maxx,maxy,memdc,0,0,SRCCOPY);
			}
			if(i%256==0){
				fseek(fp,ppos,SEEK_SET);
				fprintf(fp,"%c",(pos&0xFF000000)/0x1000000);
				fprintf(fp,"%c",(pos&0x00FF0000)/0x10000);
				fprintf(fp,"%c",(pos&0x0000FF00)/0x100);
				fprintf(fp,"%c",(pos&0x000000FF));
				ppos+=4;
			}
			l=Com.PutString(Text[i]);
			fseek(fp,pos,SEEK_SET);
			fprintf(fp,"%c",l+1);
			for(unsigned int p=0;p<l;p++){
				fprintf(fp,"%c",Com.Result[p]);
			}
			pos+=l+1;
		}
		fclose(fp);
		
		//MessageBox(NULL,"Text Saved","Note",MB_OK);
	}
}

void ExportText(char*path){
	FILE * fp = fopen(path,"wb");



	fclose(fp);
	MessageBox(NULL,"Text Exported","Note",MB_OK);
}

void TextExport(){
	OPENFILENAME openFileName;
	char path[256];
	path[0] = '\0';  
	memset( &openFileName, 0, sizeof(openFileName) );
	openFileName.lStructSize = sizeof(openFileName);
	openFileName.hwndOwner = NULL;
	openFileName.hInstance = NULL;
	openFileName.lpstrFilter = "Shining Force Text(*.sftx)\0*.sftxt\0";
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
	openFileName.lpstrDefExt = "sftx";
	openFileName.lCustData = NULL;
	openFileName.lpfnHook = NULL;
	openFileName.lpTemplateName = NULL;

	if(GetSaveFileName(&openFileName)!=0){
		ExportText(path);
	}
}
