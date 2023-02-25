#include "SaveSpellAnim.h"

void SaveAnim(){
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

	unsigned long o, o2;

	int i;
	if(strlen(file)){
		FILE * fp = fopen(file,"rb+");

		if (MSBankOffset == 0x39928) {
			MessageBox(NULL, "Graphics must first be saved before saving animations.", "Error", MB_OK);
			fclose(fp);
			return;
		}

		fseek(fp, 0x26EE4, SEEK_SET);
		for (int i = 0; i < 12; i++) {
			fprintf(fp, "%c", (EndingForce[i][0]));
			fprintf(fp, "%c", (EndingForce[i][1]));
			fprintf(fp, "%c", (EndingForce[i][2]));
		}

		fseek(fp, 0x26F0A, SEEK_SET);
		for (int i = 0; i < 15; i++) {
			fprintf(fp, "%c", (EndingScenes[i][0]));
			fprintf(fp, "%c", (EndingScenes[i][1]));
			fprintf(fp, "%c", (EndingScenes[i][2]));
			fprintf(fp, "%c", (EndingScenes[i][3]));
		}

		WSAnimBank = 0x40000;

		fseek(fp, 0x144004, SEEK_SET);
		fprintf(fp, "%c", (WSAnimBank & 0xFF000000) / 0x1000000);
		fprintf(fp, "%c", (WSAnimBank & 0x00FF0000) / 0x10000);
		fprintf(fp, "%c", (WSAnimBank & 0x0000FF00) / 0x100);
		fprintf(fp, "%c", (WSAnimBank & 0x000000FF));

		o = WSAnimBank;
		o2 = 0x40400;

		for(i=0;i<NumAnim;i++){
			fseek(fp, o, SEEK_SET);
			fprintf(fp, "%c", (o2 & 0xFF000000) / 0x1000000);
			fprintf(fp, "%c", (o2 & 0x00FF0000) / 0x10000);
			fprintf(fp, "%c", (o2 & 0x0000FF00) / 0x100);
			fprintf(fp, "%c", (o2 & 0x000000FF));

			o += 4;

			fseek(fp,o2,SEEK_SET);
			for(int f=0;f<WSAnim[i][0][0]+1;f++){
				for(int j=0;j<8;j++){
					fprintf(fp,"%c",WSAnim[i][f][j]);
					o2++;
				}
			}
		}

		fseek(fp, 0x43FFF, SEEK_SET);
		fprintf(fp, "%c", NumAnim);


		EAnimBank = 0x44000;

		fseek(fp, 0x100004, SEEK_SET);
		fprintf(fp, "%c", (EAnimBank & 0xFF000000) / 0x1000000);
		fprintf(fp, "%c", (EAnimBank & 0x00FF0000) / 0x10000);
		fprintf(fp, "%c", (EAnimBank & 0x0000FF00) / 0x100);
		fprintf(fp, "%c", (EAnimBank & 0x000000FF));

		o = EAnimBank;
		o2 = 0x44400;

		for (i = 0; i<NumEAnim; i++) {

			fseek(fp, o, SEEK_SET);
			fprintf(fp, "%c", (o2 & 0xFF000000) / 0x1000000);
			fprintf(fp, "%c", (o2 & 0x00FF0000) / 0x10000);
			fprintf(fp, "%c", (o2 & 0x0000FF00) / 0x100);
			fprintf(fp, "%c", (o2 & 0x000000FF));

			o += 4;

			fseek(fp, o2, SEEK_SET);
			for (int f = 0; f<EAnim[i][0][0] + 1; f++) {
				for (int j = 0; j<4; j++) {
					fprintf(fp, "%c", EAnim[i][f][j]);
					o2++;
				}
			}
		}

		fseek(fp, 0x47FFF, SEEK_SET);
		fprintf(fp, "%c", NumEAnim);

		if(0x200000>romsize){
			MessageBox(NULL,"Rom is too small, expand rom to save.","Error",MB_OK);
			fclose(fp);
			return;
		}

		AnimSetBank = 0x1C3560;

		fseek(fp,0x203D8,SEEK_SET);
		fprintf(fp,"%c",(AnimSetBank&0xFF000000)/0x1000000);
		fprintf(fp,"%c",(AnimSetBank&0x00FF0000)/0x10000);
		fprintf(fp,"%c",(AnimSetBank&0x0000FF00)/0x100);
		fprintf(fp,"%c",(AnimSetBank&0x000000FF));

		long o = AnimSetBank;
		long o2;


		fseek(fp,o-1,SEEK_SET);
		fprintf(fp,"%c",NumAnimSet);

		o2 = AnimSetBank+2*NumAnimSet;

		for(i=0;i<NumAnimSet;i++){
			fseek(fp,o,SEEK_SET);

			if(AnimSets[i][1]==0xFF){
				o+=2;
				fprintf(fp,"%c",0xFF);
				fprintf(fp,"%c",0xFF);
			} else {
				fprintf(fp,"%c",((o2-AnimSetBank)&0xFF00)/0x100);
				fprintf(fp,"%c",((o2-AnimSetBank)&0xFF));

				o+=2;
				fseek(fp,o2,SEEK_SET);
				fprintf(fp,"%c",AnimSets[i][0]);

				int j=1;
				while(AnimSets[i][j]!=0xFF){
					fprintf(fp,"%c",AnimSets[i][j++]);
					fprintf(fp,"%c",AnimSets[i][j++]);
					fprintf(fp,"%c",AnimSets[i][j++]);
				}
				fprintf(fp,"%c",0xFF);
				o2=ftell(fp);
			} 
		}


		EAnimSetBank = 0x1C2B00;

		fseek(fp, 0x203DC, SEEK_SET);
		fprintf(fp, "%c", (EAnimSetBank & 0xFF000000) / 0x1000000);
		fprintf(fp, "%c", (EAnimSetBank & 0x00FF0000) / 0x10000);
		fprintf(fp, "%c", (EAnimSetBank & 0x0000FF00) / 0x100);
		fprintf(fp, "%c", (EAnimSetBank & 0x000000FF));

		o = EAnimSetBank;


		fseek(fp, o - 1, SEEK_SET);
		fprintf(fp, "%c", NumEAnimSet);

		o2 = EAnimSetBank + 2 * NumEAnimSet;

		for (i = 0; i<NumEAnimSet; i++) {
			fseek(fp, o, SEEK_SET);

			if (EAnimSets[i][1] == 0xFF) {
				o += 2;
				fprintf(fp, "%c", 0xFF);
				fprintf(fp, "%c", 0xFF);
			} else {
				fprintf(fp, "%c", ((o2 - EAnimSetBank) & 0xFF00) / 0x100);
				fprintf(fp, "%c", ((o2 - EAnimSetBank) & 0xFF));

				o += 2;
				fseek(fp, o2, SEEK_SET);
				fprintf(fp, "%c", EAnimSets[i][0]);

				int j = 1;
				while (EAnimSets[i][j] != 0xFF) {
					fprintf(fp, "%c", EAnimSets[i][j++]);
					fprintf(fp, "%c", EAnimSets[i][j++]);
					fprintf(fp, "%c", EAnimSets[i][j++]);
				}
				fprintf(fp, "%c", 0xFF);
				o2 = ftell(fp);
			}
		}

		//SaveSpellAnim(fp);//*******


		fclose(fp);
		MessageBox(NULL,"Animation Saved","Note",MB_OK);
	}
}