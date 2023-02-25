struct StringSaver{

	char Result[1024];

	unsigned int PutString(char * text){
		char String[1024];
		sprintf(String,text);
		unsigned int Pos=0;
		char tempc[32];

		unsigned int StrLen = strlen(String);

		Result[0]=0;

		bool Quote=false;

		for(unsigned int i=0;i<StrLen;i++){


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
			
			Result[Pos++] = String[i];
		}

		Result[Pos++] = 0xC0;


		Result[Pos]=0;

		return Pos;
	}
};

void SaveText(){
	if (!TextLoaded) return;
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
		unsigned int l,t,n;
		unsigned long pos,ppos;

		StringSaver SS;

		char test[32];


		TextOffset = 0x200000;//Option to choose?

		if(TextOffset>romsize-1){
			MessageBox(NULL,"Rom is too small, expand rom.","Error",MB_OK);
			fclose(fp);
			return;
		}
		 
		fseek(fp, 0x6C50, SEEK_SET);
		fprintf(fp, "%c", (SpecialMessages[255] & 0xFF00) / 0x100);
		fprintf(fp, "%c", (SpecialMessages[255] & 0x00FF));

		fseek(fp,0x1A5514,SEEK_SET);
		fprintf(fp,"%c",(SpecialMessages[0]&0xFF00)/0x100);
		fprintf(fp,"%c",(SpecialMessages[0]&0x00FF));

		
		fseek(fp, 0x1C3128, SEEK_SET);
		fprintf(fp, "%c", (SpecialMessages[1] & 0xFF00) / 0x100);
		fprintf(fp, "%c", (SpecialMessages[1] & 0x00FF));
		
		
		fseek(fp, 0x1C31A8, SEEK_SET);
		fprintf(fp, "%c", (SpecialMessages[1] & 0xFF00) / 0x100);
		fprintf(fp, "%c", (SpecialMessages[1] & 0x00FF));
		

		pos = TextOffset;
		ppos = 0x13E906;

		fseek(fp, 0x13E950, SEEK_SET);

		fprintf(fp, "%c", (NUM_TEXT & 0xFF00) / 0x100);
		fprintf(fp, "%c", (NUM_TEXT & 0x00FF));

		for(unsigned int i=0;i<NUM_TEXT;i++){
			if(i%23==0){
				PatBlt(memdc, 0, 0, maxx, maxy, PATCOPY);
				sprintf(test,"Saving: %d%%",(int)(100*i/NUM_TEXT));
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
			if (!strlen(Text[i]))sprintf(Text[i], "0");
			l=SS.PutString(Text[i]);
			fseek(fp,pos,SEEK_SET);
			t=l+1;
			n=0;
			while(t>=255){
				t-=255;
				fprintf(fp,"%c",0xFF);
				n++;
			}
			fprintf(fp,"%c",t);
			for(unsigned int p=0;p<l;p++){
				fprintf(fp,"%c",SS.Result[p]);
			}
			pos+=l+1+n;
		}

		fseek(fp,0x2140,SEEK_SET);
		fprintf(fp,"%c",0x4E);
		fprintf(fp,"%c",0xB9);
		fprintf(fp,"%c",0x00);
		fprintf(fp,"%c",0x1F);
		fprintf(fp,"%c",0xFF);
		fprintf(fp,"%c",0xC0);
		fseek(fp,0x215C,SEEK_SET);
		fprintf(fp,"%c",0x4E);
		fprintf(fp,"%c",0xB9);
		fprintf(fp,"%c",0x00);
		fprintf(fp,"%c",0x1F);
		fprintf(fp,"%c",0xFF);
		fprintf(fp,"%c",0xEC);
		fseek(fp,0x2112,SEEK_SET);
		fprintf(fp,"%c",0x4E);
		fprintf(fp,"%c",0xB9);
		fprintf(fp,"%c",0x00);
		fprintf(fp,"%c",0x1F);
		fprintf(fp, "%c", 0xFF);
		fprintf(fp, "%c", 0x9C);//////

		fseek(fp, 0x1FFF9C, SEEK_SET);////
		fprintf(fp,"%c",0x13);
		fprintf(fp,"%c",0xFC);
		fprintf(fp,"%c",0x00);
		fprintf(fp,"%c",0x00);
		fprintf(fp,"%c",0x00);
		fprintf(fp,"%c",0xA1);
		fprintf(fp,"%c",0x30);
		fprintf(fp,"%c",0xF1);

		fprintf(fp,"%c",0x13);
		fprintf(fp,"%c",0xD8);
		fprintf(fp,"%c",0x00);
		fprintf(fp,"%c",0xFF);
		fprintf(fp,"%c",0xF8);
		fprintf(fp,"%c",0x05);

		fprintf(fp,"%c",0x0C);
		fprintf(fp,"%c",0x39);
		fprintf(fp,"%c",0x00);
		fprintf(fp,"%c",0xFF);
		fprintf(fp,"%c",0x00);
		fprintf(fp,"%c",0xFF);
		fprintf(fp,"%c",0xF8);
		fprintf(fp,"%c",0x05);
		fprintf(fp,"%c",0x66);
		fprintf(fp,"%c",0x02);

		fprintf(fp,"%c",0x10);
		fprintf(fp,"%c",0x18);

		fprintf(fp,"%c",0x13);
		fprintf(fp,"%c",0xFC);
		fprintf(fp,"%c",0x00);
		fprintf(fp,"%c",0x01);
		fprintf(fp,"%c",0x00);
		fprintf(fp,"%c",0xA1);
		fprintf(fp,"%c",0x30);
		fprintf(fp,"%c",0xF1);
		fprintf(fp,"%c",0x4E);
		fprintf(fp,"%c",0x75);

	
			fseek(fp, 0x1FFFC0, SEEK_SET);
			fprintf(fp, "%c", 0x13);
			fprintf(fp, "%c", 0xFC);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0xA1);
			fprintf(fp, "%c", 0x30);
			fprintf(fp, "%c", 0xF1);

		
		fprintf(fp,"%c",0x7E);
		fprintf(fp,"%c",0x00);
		fprintf(fp,"%c",0x1E);
		fprintf(fp,"%c",0x10);

		fprintf(fp,"%c",0x0C);
		fprintf(fp,"%c",0x07);
		fprintf(fp,"%c",0x00);
		fprintf(fp,"%c",0xFF);
		fprintf(fp,"%c",0x66);
		fprintf(fp,"%c",0x0E);

		fprintf(fp,"%c",0x52);
		fprintf(fp,"%c",0x48);
		fprintf(fp,"%c",0x1E);
		fprintf(fp,"%c",0x10);
		fprintf(fp,"%c",0xD1);
		fprintf(fp,"%c",0xC7);
		fprintf(fp,"%c",0xD1);
		fprintf(fp,"%c",0xFC);
		fprintf(fp,"%c",0x00);
		fprintf(fp,"%c",0x00);
		fprintf(fp,"%c",0x00);
		fprintf(fp,"%c",0xFF);


		fprintf(fp,"%c",0x60);
		fprintf(fp,"%c",0x02);

		fprintf(fp,"%c",0xD1);
		fprintf(fp,"%c",0xC7);

		fprintf(fp,"%c",0x13);
		fprintf(fp,"%c",0xFC);
		fprintf(fp,"%c",0x00);
		fprintf(fp,"%c",0x01);
		fprintf(fp,"%c",0x00);
		fprintf(fp,"%c",0xA1);
		fprintf(fp,"%c",0x30);
		fprintf(fp,"%c",0xF1);
		fprintf(fp,"%c",0x4E);
		fprintf(fp,"%c",0x75);
		fprintf(fp,"%c",0x13);
		fprintf(fp,"%c",0xFC);
		fprintf(fp,"%c",0x00);
		fprintf(fp,"%c",0x00);
		fprintf(fp,"%c",0x00);
		fprintf(fp,"%c",0xA1);
		fprintf(fp,"%c",0x30);
		fprintf(fp,"%c",0xF1);
		fprintf(fp,"%c",0x10);
		fprintf(fp,"%c",0x18);
		fprintf(fp,"%c",0x13);
		fprintf(fp,"%c",0xFC);
		fprintf(fp,"%c",0x00);
		fprintf(fp,"%c",0x01);
		fprintf(fp,"%c",0x00);
		fprintf(fp,"%c",0xA1);
		fprintf(fp,"%c",0x30);
		fprintf(fp,"%c",0xF1);
		fprintf(fp,"%c",0x4E);
		fprintf(fp,"%c",0x75);
		fclose(fp);
		
		//MessageBox(NULL,"Text Saved","Note",MB_OK);
	}
}

void ExportText(char*path){
	FILE * fp = fopen(path,"wb");

	for(int i=0;i<NUM_TEXT;i++){
		fprintf(fp,"%s\r\n",Text[i]);
	}

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
	openFileName.lpstrFilter = "Text File(*.txt)\0*.txt\0";
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
	openFileName.lpstrDefExt = "txt";
	openFileName.lCustData = NULL;
	openFileName.lpfnHook = NULL;
	openFileName.lpTemplateName = NULL;

	if(GetSaveFileName(&openFileName)!=0){
		ExportText(path);
	}
}
