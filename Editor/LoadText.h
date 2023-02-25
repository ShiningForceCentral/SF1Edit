char Symbols[]=" 0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz_-.,!?\"\"'()#%&+/:";

unsigned int SpecialMessages[256];
char MessagesLabels[][32] = {"Max MP Increase", "Pass Item", "MP Refill", "Crit Increase"};
char MessagesDefaults[][256] = {"[Name]'s maximum MP[Line]increases by [Num].[Wait2]","[Hero] passes it[Line]to [Name]![Wait2]","[Name] regains [Num] magic[Line]points.","Critical rate[Line]increases by [Num].[Wait2]"};
unsigned int NUM_SPECIAL = 4;

unsigned int NUM_TEXT = 2231;

char Text[4096][1024];
bool TextLoaded = false;
unsigned long TextOffset;

char* stristr(const char* haystack, const char* needle) {
	do {
		const char* h = haystack;
		const char* n = needle;
		while (tolower((unsigned char)*h) == tolower((unsigned char)*n) && *n) {
			h++;
			n++;
		}
		if (*n == 0) {
			return (char *)haystack;
		}
	} while (*haystack++);
	return 0;
}

char * removeTags(char * text){
	replace(text,"[Line]"," ");
	replace(text,"[Wait]"," ");
	replace(text,"[Wait2]"," ");
	return text;
}

void InitText(){
	for(int i=0;i<4096;i++){
		sprintf(Text[i],"");
	}
	TextLoaded = false;
}

void TextOutHighlight(HDC hdc, int x, int y, char * s, int l, char b, char e, COLORREF c1, COLORREF c2) {
	RECT r;
	SetRect(&r, 0, 0, 0, 0);

	int a = 0;
	int p = 0;
	char * buf = new char[l];

	bool in = false;

	int left=x;

	while(a<l){
		while (a + p < l && ((!in && s[a + p] != b) || (in && s[a + p] != e))) {
			buf[p] = s[a + p];
			p++;
		}
		if (in && s[a + p] == e) {
			buf[p] = s[a + p];
			p++;
		}
		SetRect(&r, 0, 0, 0, 0);
		DrawText(hdc, buf, p, &r, DT_CALCRECT);
		if (in)SetTextColor(hdc,c2);
		else SetTextColor(hdc, c1);
		TextOut(hdc, left, y, buf, p);
		if (!in && s[a + p] == b)in = true;
		else if (in && s[a + p-1] == e)in = false;
		left += r.right;
		a += p;
		p = 0;
		buf[0] = 0;
	}

	SetTextColor(hdc,c1);
	delete buf;
}

struct Decompressor{
	
	int StringNumber;
	unsigned char StringLength;
	unsigned long TreeOffset;
	unsigned long TreePointer;
	unsigned long DataPointer;
	unsigned long ScriptPointer;

	unsigned int Tree;
	unsigned int Length;
	unsigned int Symbol;

	FILE * file;
	char Result[1024];
	unsigned int Pos;
	unsigned char temp[32];
	unsigned long templ;

	Decompressor(FILE * fp){
		file=fp;
	}

	char * GetString(int String){
		StringNumber = String;
		ScriptPointer = GetStringOffset();
		fseek(file,ScriptPointer,SEEK_SET);
		fscanf(file,"%c",&StringLength);
		ScriptPointer++;
		sprintf(Result,"");
		if(StringLength==1) return Result;//is this the correct behavior?
		Pos=0;

		Tree = 0xC0;//FFF809
		Length = 0;//FFF8DC
		Symbol = 0;//FFF8DA

		while(1){

			//check decoder flag?

			
			temp[0] = Decode();

			Tree = temp[0];

			if(temp[0]==0xC0){
				Result[Pos]=0;
				return Result;
			}
			if(temp[0]>0xC0){
				switch(temp[0]){
				case 0xC1:
					sprintf(Result+Pos,"[Dict]");
					Pos+=6;
					break;
				case 0xC2:
					sprintf(Result+Pos,"[Line]");
					Pos+=6;
					break;
				case 0xC4:
					sprintf(Result+Pos,"[Delay2]");
					Pos+=8;
					break;
				case 0xC5:
					sprintf(Result+Pos,"[Num]");
					Pos+=5;
					break;
				case 0xC6:
					sprintf(Result+Pos,"[Name]");
					Pos+=6;
					break;
				case 0xC8:
					sprintf(Result+Pos,"[Hero]");
					Pos+=6;
					break;
				case 0xCA:
					sprintf(Result+Pos,"[Item]");
					Pos+=6;
					break;
				case 0xCB:
					sprintf(Result+Pos,"[Spell]");
					Pos+=7;
					break;
				case 0xCD:
					sprintf(Result+Pos,"[Wait2]");
					Pos+=7;
					break;
				case 0xCF:
					sprintf(Result+Pos,"[Delay1]");
					Pos+=8;
					break;
				case 0xD2:
					sprintf(Result+Pos,"[Class]");
					Pos+=7;
					break;
				default:
					temp[0]=temp[0];
					break;
				}
			} else {
				Result[Pos]=Symbols[temp[0]];
				Pos++;
			}

			//do an FFEA check?
		}
	}

	unsigned char Decode(){
		unsigned int TreeLength;
		unsigned int SymbolOffset;
		unsigned char Node;

		unsigned char i;

		//fseek(file,0x13000C+Tree*2,SEEK_SET);
		fseek(file,0x1E892+Tree*2,SEEK_SET);
		TreeOffset = readword();

		//TreePointer = 0x1301B4 + TreeOffset;
		TreePointer = 0x1EA3A + TreeOffset;
		DataPointer = TreePointer;

		TreeLength = 0;
		SymbolOffset = 0;

		while(1){
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

				if(Length==0){
					Length = 7;
					fseek(file,ScriptPointer,SEEK_SET);
					fscanf(file,"%c",&Symbol);
					ScriptPointer++;
				} else {
					Length--;
				}
				temp[0]=Symbol;
				Symbol*=2;
				if(temp[0]>127){//if 1, need to go right, skip all symbols from left branch
					i=1;
					while(i>0){
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
						if(temp[0]<128){//another branch, need to continue skipping
							i++;
						} else {//found a leaf, skip it in symbol list and done skipping
							SymbolOffset--;
							i--;
						}
					}
				}
			} else {//node is a leaf, we are done
				fseek(file,TreePointer+SymbolOffset-1,SEEK_SET);
				fscanf(file,"%c",&(temp[0]));
				return temp[0];
			}
		}
	}

	unsigned long GetStringOffset(){
		unsigned long bank = StringNumber>>6;
		bank&=0xFFFFFFFC;

		fseek(file,0x130000,SEEK_SET);
		unsigned long bankpointer = readlong();
		fseek(file,bankpointer+bank,SEEK_SET);
		bankpointer=readlong();

		while(StringNumber%256!=0){

			fseek(file,bankpointer,SEEK_SET);
			fscanf(file,"%c",&(temp[0]));
			bankpointer+=temp[0];
			StringNumber--;
		}
		return bankpointer;
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

struct StringLoader{
	
	int StringNumber;
	unsigned char StringLength;
	unsigned long ScriptPointer;

	unsigned int Symbol;

	FILE * file;
	char Result[1024];
	unsigned int Pos;
	unsigned char temp[32];
	unsigned long templ;

	unsigned long bankpointer;
	unsigned long banks[32];

	StringLoader(FILE * fp){
		file=fp;
		fseek(file, 0x130000, SEEK_SET);
		bankpointer = readlong();
		for (int i = 0;i < 32;i++) {
			banks[i] = 0;
		}
	}

	char * GetString(int String){
		if (String != -1) {
			StringNumber = String;
			ScriptPointer = GetStringOffset();
			fseek(file, ScriptPointer, SEEK_SET);
		} else StringNumber++;
		StringLength=0;
		do{
			fscanf(file,"%c",&(temp[0]));
			StringLength+=temp[0];
			ScriptPointer++;
		} while(temp[0]==0xFF);
		sprintf(Result,"");
		if(StringLength==1) return Result;//is this the correct behavior?
		Pos=0;

		Symbol = 0;

		while(1){

			//check decoder flag?

			
			temp[0] = Decode();

			if(temp[0]==0xC0){
				Result[Pos]=0;
				return Result;
			}
			if(temp[0]>0xC0){
				switch(temp[0]){
				case 0xC1:
					sprintf(Result+Pos,"[Dict]");
					Pos+=6;
					break;
				case 0xC2:
					sprintf(Result+Pos,"[Line]");
					Pos+=6;
					break;
				case 0xC4:
					sprintf(Result+Pos,"[Delay2]");
					Pos+=8;
					break;
				case 0xC5:
					sprintf(Result+Pos,"[Num]");
					Pos+=5;
					break;
				case 0xC6:
					sprintf(Result+Pos,"[Name]");
					Pos+=6;
					break;
				case 0xC8:
					sprintf(Result+Pos,"[Hero]");
					Pos+=6;
					break;
				case 0xCA:
					sprintf(Result+Pos,"[Item]");
					Pos+=6;
					break;
				case 0xCB:
					sprintf(Result+Pos,"[Spell]");
					Pos+=7;
					break;
				case 0xCD:
					sprintf(Result+Pos,"[Wait2]");
					Pos+=7;
					break;
				case 0xCF:
					sprintf(Result+Pos,"[Delay1]");
					Pos+=8;
					break;
				case 0xD2:
					sprintf(Result+Pos,"[Class]");
					Pos+=7;
					break;
				default:
					temp[0]=temp[0];
					break;
				}
			} else {
				Result[Pos]=Symbols[temp[0]];
				Pos++;
			}

			//do an FFEA check?
		}
	}

	unsigned long GetStringOffset(){
		unsigned long bank = StringNumber>>6;
		unsigned char c=-1;
		bank&=0xFFFFFFFC;

		unsigned long pointer;

		if (banks[bank] == 0) {
			fseek(file, bankpointer + bank, SEEK_SET);
			pointer = readlong();
			banks[bank] = pointer;
		} else {
			pointer = banks[bank];
		}

		while(StringNumber%256!=0){
			c=-1;
			fseek(file, pointer,SEEK_SET);
			do{
			fscanf(file,"%c",&(temp[0]));
			pointer +=temp[0];
			c++;
			} while(temp[0]==0xFF);
			pointer +=c;
			StringNumber--;
		}
		return pointer;
	}

	unsigned char Decode(){
		fscanf(file,"%c",&Symbol);
		return Symbol;
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
};

void LoadText(char *path, bool decomp=false, bool single=false){
	if(single&&!TextLoaded)return;
	char r[32];
	unsigned char c;
	unsigned int in=0;
	FILE * fp = fopen(path,"rb");


	fseek(fp, 0x248E0, SEEK_SET);
	fscanf(fp, "%c", &in);

	if (in != 0x4E) {
		SpecialMessages[3] = 751;
	} else {
		fseek(fp, 0x1E3014, SEEK_SET);
		fscanf(fp, "%c", &in);
		SpecialMessages[3] = in;
		fscanf(fp, "%c", &in);
		SpecialMessages[3] = SpecialMessages[3] * 256 + in;
	}

	fseek(fp, 0x6C50, SEEK_SET);
	fscanf(fp, "%c", &in);
	SpecialMessages[255] = in;
	fscanf(fp, "%c", &in);
	SpecialMessages[255] = SpecialMessages[255] * 256 + in;



	fseek(fp,0x13E906,SEEK_SET);
	fscanf(fp,"%c",&c);
	TextOffset = c;
	fscanf(fp,"%c",&c);
	TextOffset = TextOffset*256+c;
	fscanf(fp,"%c",&c);
	TextOffset = TextOffset*256+c;
	fscanf(fp,"%c",&c);
	TextOffset = TextOffset*256+c;

	fseek(fp, 0x13E950, SEEK_SET);
	fscanf(fp, "%c", &c);
	if (c == 0xFF || c==-1) {
		NUM_TEXT = 2231;
	} else {
		NUM_TEXT = c;
		fscanf(fp, "%c", &c);
		NUM_TEXT = NUM_TEXT * 256 + c;
	}

	//fseek(fp,132016,SEEK_SET);
	//fscanf(fp,"%c",&r);
	
	Decompressor Dec(fp);
	StringLoader SL(fp);

	fseek(fp,0x215F,SEEK_SET);
	fscanf(fp,"%c",&r);

	if(r[0]==1&&decomp){

		for(int i=0;i<NUM_TEXT;i++){
			if(!single||i==(subselect[mode][0]+focus)%NUM_TEXT)sprintf(Text[i],Dec.GetString(i));
			if(i%23==0){
				//PatBlt(memdc, 75, 92, 250, 32, PATCOPY);
				PatBlt(memdc, 0, 0, maxx, maxy, PATCOPY);
				sprintf(r,"Decompressing: %d%%",(int)(100*i/NUM_TEXT));
				TextOut(memdc, 75, 92, r,strlen(r));
				//BitBlt(hdc,75,92,250,32,memdc,75,92,SRCCOPY);
				BitBlt(hdc,0,40,maxx,maxy-40,memdc,0,40,SRCCOPY);
			}

		}
		TextLoaded = true;
	} else {
		if(!single)InitText();
		else sprintf(Text[select[mode]],"");
	}

	if(r[0]==0x1F){
		for(int i=0;i<NUM_TEXT;i++){
			if(!single||i==(subselect[mode][0]+focus)%NUM_TEXT)
				if(!i)sprintf(Text[i],SL.GetString(i));
				else sprintf(Text[i], SL.GetString(-1));
		}
		TextLoaded = true;
	}

	fclose(fp);
}

void ImportText(char *path){
	unsigned char r;
	FILE * fp = fopen(path,"rb");

	for(int i=0;i<NUM_TEXT && !feof(fp);i++){
		fscanf(fp,"%[^\r\n]",&(Text[i]));
		fscanf(fp,"%c",&r);
		if(r==0xD)fscanf(fp,"%c",&r);
	}

	fclose(fp);
	TextLoaded = true;
}

void TextImport(){
	int ret=IDYES;
	OPENFILENAME openFileName;
	char path[256];
	path[0] = '\0';    
	memset( &openFileName, 0, sizeof(openFileName) );
	openFileName.lStructSize = sizeof(openFileName);
	openFileName.hwndOwner = NULL;
	openFileName.hInstance = NULL;
	openFileName.lpstrFilter = "Text Files(*.txt)\0*.txt\0";
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
	openFileName.lpstrDefExt = "txt";
	openFileName.lCustData = NULL;
	openFileName.lpfnHook = NULL;
	openFileName.lpTemplateName = NULL;

	if(GetOpenFileName(&openFileName)!=0){
		ImportText(path);
	}
}

void Find(){
	if(strlen(searchtext)<1)return;
	for(int i=1;i<NUM_TEXT-1;i++){
		if(stristr(Text[(subselect[mode][0]+focus+i)%NUM_TEXT],searchtext)){
			subselect[mode][0]=(subselect[mode][0]+focus+i)%NUM_TEXT;
			if(!menu){
				focus=0;
				subfocus=strlen(Text[(subselect[mode][0]+focus)%NUM_TEXT]);
			}
			return;
		}
	}
	MessageBox(NULL,"String not found!","Note",MB_OK);
}