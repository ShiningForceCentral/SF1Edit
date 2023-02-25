char WSAnim[256][32][8];
char EAnim[256][32][4];


unsigned long WSAnimBank;
unsigned long WSAnimOffset[256];
int NumAnim;

unsigned long EAnimBank;
unsigned long EAnimOffset[256];
int NumEAnim;

unsigned long AnimSetBank;
int NumAnimSet;
unsigned long EAnimSetBank;
int NumEAnimSet;



unsigned char AnimSets[256][256];
unsigned char EAnimSets[256][256];

unsigned char EndingForce[12][3];
unsigned char EndingScenes[15][4];

#include "LoadSpellAnim.h"

void getAnimValues(int anim){
	int j=1;

	for(int i=0;i<NumAnimSet;i++){
		j=1;
		while(AnimSets[i][j]!=0xFF){
			if(AnimSets[i][j+1]==anim&&AnimSets[i][j]<128){
				subselect[17][1]=i;
				subselect[17][2]=AnimSets[i][j];
				if (subselect[17][2]>14)subselect[17][2] = 14;
				return;
			}
			j+=3;
		}
		j=1;
		while(AnimSets[i][j]!=0xFF){
			if(AnimSets[i][j+1]==anim){
				subselect[17][1]=i;
				subselect[17][2]=AnimSets[i][j];
				if (subselect[17][2]>14)subselect[17][2] = 14;
				return;
			}
			j+=3;
		}
	}

}

void getEAnimValues(int anim) {
	int j = 1;

	for (int i = 0; i<NumEAnimSet; i++) {
		j = 1;
		while (EAnimSets[i][j] != 0xFF) {
			if (EAnimSets[i][j + 1] == anim&&EAnimSets[i][j]<128) {
				subselect[17][1] = i;
				subselect[17][2] = EAnimSets[i][j];
				return;
			}
			j += 3;
		}
		j = 1;
		while (EAnimSets[i][j] != 0xFF) {
			if (EAnimSets[i][j + 1] == anim) {
				subselect[17][1] = i;
				subselect[17][2] = EAnimSets[i][j];
				return;
			}
			j += 3;
		}
	}
}

void LoadAnim(char *path,bool single=false){
	if(!GraphicsLoaded&&single)return;
	unsigned char r;

	initPals();
	initScriptComponents();

	FILE * fp = fopen(path,"rb");

	fseek(fp, 0x26EE4, SEEK_SET);
	for (int i = 0; i < 12; i++) {
		fscanf(fp, "%c", &(EndingForce[i][0]));
		fscanf(fp, "%c", &(EndingForce[i][1]));
		fscanf(fp, "%c", &(EndingForce[i][2]));
	}

	fseek(fp, 0x26F0A, SEEK_SET);
	for (int i = 0; i < 15; i++) {
		fscanf(fp, "%c", &(EndingScenes[i][0]));
		fscanf(fp, "%c", &(EndingScenes[i][1]));
		fscanf(fp, "%c", &(EndingScenes[i][2]));
		fscanf(fp, "%c", &(EndingScenes[i][3]));
	}

	fseek(fp,0x144004,SEEK_SET);
	fscanf(fp,"%c",&r);
	WSAnimBank = r;
	fscanf(fp,"%c",&r);
	WSAnimBank = WSAnimBank*256+r;
	fscanf(fp,"%c",&r);
	WSAnimBank = WSAnimBank*256+r;
	fscanf(fp,"%c",&r);
	WSAnimBank = WSAnimBank*256+r;

	if (WSAnimBank == 0x161A66) {
		NumAnim = 59;
	} else {
		fseek(fp, 0x43FFF, SEEK_SET);
		fscanf(fp, "%c", &r);
		NumAnim = r;
	}

	fseek(fp,WSAnimBank,SEEK_SET);
	int i;
	for(i=0;i<NumAnim;i++){
		fscanf(fp,"%c",&r);
		WSAnimOffset[i] = r;
		fscanf(fp,"%c",&r);
		WSAnimOffset[i] = WSAnimOffset[i]*256+r;
		fscanf(fp,"%c",&r);
		WSAnimOffset[i] = WSAnimOffset[i]*256+r;
		fscanf(fp,"%c",&r);
		WSAnimOffset[i] = WSAnimOffset[i]*256+r;
	}

	int l;
	if(!single||submode[mode]==0)
	for(i=0;i<NumAnim;i++){
		fseek(fp,WSAnimOffset[i],SEEK_SET);
		fscanf(fp,"%c",&r);
		l = r+1;
		fseek(fp,WSAnimOffset[i],SEEK_SET);
		for(int f=0;f<l;f++){
			for(int j=0;j<8;j++){
				fscanf(fp,"%c",&r);
				if(single&&i!=select[mode])continue;
				WSAnim[i][f][j] = r;
			}
		}
	}

	fseek(fp,0x203D8,SEEK_SET);
	fscanf(fp,"%c",&r);
	AnimSetBank = r;
	fscanf(fp,"%c",&r);
	AnimSetBank = AnimSetBank*256+r;
	fscanf(fp,"%c",&r);
	AnimSetBank = AnimSetBank*256+r;
	fscanf(fp,"%c",&r);
	AnimSetBank = AnimSetBank*256+r;

	long o = AnimSetBank;
	long o2;

	if(!single||submode[mode]==1)
	if(AnimSetBank==0x26666){
		NumAnimSet = 35;
	} else {
		fseek(fp,o-1,SEEK_SET);
		fscanf(fp,"%c",&r);
		NumAnimSet = r;
	}

	if(!single||submode[mode]==1)
	for(i=0;i<NumAnimSet;i++){
		o2 = AnimSetBank;
		fseek(fp,o,SEEK_SET);
		fscanf(fp,"%c",&r);
		if(r!=0xFF){
			o2+=256*r;
			fscanf(fp,"%c",&r);
			o2+=r;
			o+=2;
			fseek(fp,o2,SEEK_SET);
			fscanf(fp,"%c",&r);
			o2++;
			AnimSets[i][0]=r;
			int j=1;
			while(true){
				fscanf(fp,"%c",&r);
				o2++;
				AnimSets[i][j++]=r;
				if(r==0xFF)break;
				fscanf(fp,"%c",&r);
				o2++;
				AnimSets[i][j++]=r;
				fscanf(fp,"%c",&r);
				o2++;
				AnimSets[i][j++]=r;
			}
			AnimSets[i][j++]=0xFF;
			AnimSets[i][j++]=0xFF;
		} else {
			for(int q=0;q<256;q++)AnimSets[i][q] = 0xFF;
			o+=2;
		}
	}

	if (NumAnimSet < NumGFX[0]) {
		for (i = NumAnimSet; i < NumGFX[0]; i++)AnimSets[i][1] = 0xFF;
		NumAnimSet = NumGFX[0];
	}


	fseek(fp, 0x100004, SEEK_SET);
	fscanf(fp, "%c", &r);
	EAnimBank = r;
	fscanf(fp, "%c", &r);
	EAnimBank = EAnimBank * 256 + r;
	fscanf(fp, "%c", &r);
	EAnimBank = EAnimBank * 256 + r;
	fscanf(fp, "%c", &r);
	EAnimBank = EAnimBank * 256 + r;

	if (EAnimBank == 0x122252) {
		NumEAnim = 71;
	} else {
		fseek(fp, 0x47FFF, SEEK_SET);
		fscanf(fp, "%c", &r);
		NumEAnim = r;
	}

	fseek(fp, EAnimBank, SEEK_SET);
	for (i = 0;i<NumEAnim;i++) {
		fscanf(fp, "%c", &r);
		EAnimOffset[i] = r;
		fscanf(fp, "%c", &r);
		EAnimOffset[i] = EAnimOffset[i] * 256 + r;
		fscanf(fp, "%c", &r);
		EAnimOffset[i] = EAnimOffset[i] * 256 + r;
		fscanf(fp, "%c", &r);
		EAnimOffset[i] = EAnimOffset[i] * 256 + r;
	}

	if (!single || submode[mode] == 0)
		for (i = 0;i<NumEAnim;i++) {
			fseek(fp, EAnimOffset[i], SEEK_SET);
			fscanf(fp, "%c", &r);
			l = r + 1;
			fseek(fp, EAnimOffset[i], SEEK_SET);
			for (int f = 0;f<l;f++) {
				for (int j = 0;j<4;j++) {
					fscanf(fp, "%c", &r);
					if (single&&i != select[mode])continue;
					EAnim[i][f][j] = r;
				}
			}
		}

	fseek(fp, 0x203DC, SEEK_SET);
	fscanf(fp, "%c", &r);
	EAnimSetBank = r;
	fscanf(fp, "%c", &r);
	EAnimSetBank = EAnimSetBank * 256 + r;
	fscanf(fp, "%c", &r);
	EAnimSetBank = EAnimSetBank * 256 + r;
	fscanf(fp, "%c", &r);
	EAnimSetBank = EAnimSetBank * 256 + r;

	o = EAnimSetBank;

	if (!single || submode[mode] == 3)
		if (EAnimSetBank == 0x2688E) {
			NumEAnimSet = 42;
		} else {
			fseek(fp, o - 1, SEEK_SET);
			fscanf(fp, "%c", &r);
			NumEAnimSet = r;
		}
	if (!single || submode[mode] == 3)
		for (i = 0;i<NumEAnimSet;i++) {
			o2 = EAnimSetBank;
			fseek(fp, o, SEEK_SET);
			fscanf(fp, "%c", &r);
			if (r != 0xFF) {
				o2 += 256 * r;
				fscanf(fp, "%c", &r);
				o2 += r;
				o += 2;
				fseek(fp, o2, SEEK_SET);
				fscanf(fp, "%c", &r);
				o2++;
				EAnimSets[i][0] = r;
				int j = 1;
				while (true) {
					fscanf(fp, "%c", &r);
					o2++;
					EAnimSets[i][j++] = r;
					if (r == 0xFF)break;
					fscanf(fp, "%c", &r);
					o2++;
					EAnimSets[i][j++] = r;
					fscanf(fp, "%c", &r);
					o2++;
					EAnimSets[i][j++] = r;
				}
				EAnimSets[i][j++] = 0xFF;
				EAnimSets[i][j++] = 0xFF;
			} else {
				for (int q = 0; q<256; q++)EAnimSets[i][q] = 0xFF;
				o += 2;
			}
		}

	if (NumEAnimSet < NumGFX[1]) {
		for (i = NumEAnimSet; i < NumGFX[1]; i++)EAnimSets[i][1] = 0xFF;
		NumEAnimSet = NumGFX[1];
	}


	if(!single)getAnimValues(0);

	fclose(fp);
}