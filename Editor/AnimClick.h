if (GraphicsLoaded) {
	if (p.x >= 0 && p.x <= 40 && p.y >= 35 && p.y < 75) {
		submode[mode] = 0;
		select[mode] = 0;
		subselect[mode][1] = 0;
	}
	if (p.x >= 0 && p.x <= 40 && p.y >= 75 && p.y < 115) {
		submode[mode] = 1;
		select[mode] = 0;
		subselect[mode][1] = 0;
	}
	if (p.x >= 0 && p.x <= 40 && p.y >= 115 && p.y < 155) {
		submode[mode] = 2;
		select[mode] = 0;
		subselect[mode][1] = 0;
	}
	if (p.x >= 0 && p.x <= 40 && p.y >= 155 && p.y < 195) {
		submode[mode] = 3;
		select[mode] = 0;
		subselect[mode][1] = 0;
	}
	if (p.x >= 0 && p.x <= 40 && p.y >= 195 && p.y < 235) {
		submode[mode] = 4;
		select[mode] = 0;
		subselect[mode][1] = 0;
	}
	if (p.x >= 0 && p.x <= 40 && p.y >= 235 && p.y < 275) {
		submode[mode] = 5;
		select[mode] = 0;
		subselect[mode][1] = 0;
	}
}

if(submode[mode]==0){
	if(!GraphicsLoaded&&strlen(file)){
		if(p.x>=50&&p.x<=176&&p.y>=30&&p.y<=52){
			LoadGFX(file);
		}
	}

	if(GraphicsLoaded){
		if(p.x>=55&&p.x<=75&&p.y>=8&&p.y<=28){
			select[mode]--;
			if(select[mode]<0)select[mode]=NumAnim-1;
			subselect[mode][0]=0;
			getAnimValues(select[mode]);
		}

		if(p.x>=171&&p.x<=191&&p.y>=8&&p.y<=28){
			select[mode]++;
			if(select[mode]>NumAnim - 1)select[mode]=0;
			subselect[mode][0]=0;
			getAnimValues(select[mode]);
		}

		if(p.x>=201&&p.x<=221&&p.y>=8&&p.y<=28){
			subselect[mode][0]--;
			if(subselect[mode][0]<0)subselect[mode][0]=WSAnim[select[mode]][0][0];
		}

		if(p.x>=292&&p.x<=312&&p.y>=8&&p.y<=28){
			subselect[mode][0]++;
			if(subselect[mode][0]>WSAnim[select[mode]][0][0])subselect[mode][0]=0;
		}

		if(p.x>=dwidth+645&&p.x<=dwidth+665&&p.y>=80&&p.y<=100){
			subselect[mode][1]--;
			if(subselect[mode][1]<0)subselect[mode][1]=NumGFX[0]-1;
		}

		if(p.x>=dwidth+761&&p.x<=dwidth+781&&p.y>=80&&p.y<=100){
			subselect[mode][1]++;
			if(subselect[mode][1]>NumGFX[0]-1)subselect[mode][1]=0;
		}

		if(p.x>=dwidth+645&&p.x<=dwidth+665&&p.y>=100&&p.y<=120){
			subselect[mode][2]--;
			if(subselect[mode][2]<0)subselect[mode][2]=130;
			if (subselect[mode][2] == 127)subselect[mode][2] = NumGFX[2] - 1;
		}

		if(p.x>=dwidth+761&&p.x<=dwidth+781&&p.y>=100&&p.y<=120){
			subselect[mode][2]++;
			if(subselect[mode][2]>NumGFX[2]-1 && subselect[mode][2]<127)subselect[mode][2]=128;
			if(subselect[mode][2] == 131)subselect[mode][2] = 0;
		}

		if (p.x >= 330 && p.x <= 434 && p.y >= 3 && p.y <= 33) {
			if (NumAnim < 256) {
				select[mode] = NumAnim;
				NumAnim++;
				WSAnim[select[mode]][0][0] = 0;
				WSAnim[select[mode]][0][1] = -1;
				WSAnim[select[mode]][0][2] = 1;
				WSAnim[select[mode]][0][3] = 0;

				for (int q = 4;q < 256;q++) {
					WSAnim[select[mode]][0][q] = 0;
				}
				getAnimValues(select[mode]);
			}
		}

		if (p.x >= 454 && p.x <= 558 && p.y >= 3 && p.y <= 33) {
			if (NumAnim) {
				NumAnim--;
				select[mode] = NumAnim-1;
				getAnimValues(select[mode]);
			}
		}


		if(p.x>=76&&p.x<=168&&p.y>=10&&p.y<=30){
			focus=1;
		}

		if(p.x>=222&&p.x<=291&&p.y>=10&&p.y<=30){
			focus=2;
		}

		if(p.x>=60&&p.x<=160&&p.y>=40&&p.y<=60){
			focus=3;
		}

		if(p.x>=60&&p.x<=160&&p.y>=60&&p.y<=80){
			focus=4;
		}

		if(p.x>=60&&p.x<=160&&p.y>=80&&p.y<=100){
			focus=5;
		}

		if(p.x>=60&&p.x<=160&&p.y>=100&&p.y<=120){
			focus=6;
		}

		if(p.x>=60&&p.x<=160&&p.y>=140&&p.y<=160){
			focus=7;
		}

		if(p.x>=60&&p.x<=160&&p.y>=220&&p.y<=240){
			focus=8;
		}

		if(p.x>=60&&p.x<=160&&p.y>=240&&p.y<=260){
			focus=9;
		}

		if(p.x>=60&&p.x<=160&&p.y>=260&&p.y<=280){
			focus=10;
		}

		if(p.x>=60&&p.x<=73&&p.y>=280&&p.y<=293){
			WSAnim[select[mode]][subselect[mode][0]][4]^=0x10;
		}

		if(p.x>=60&&p.x<=73&&p.y>=300&&p.y<=313){
			WSAnim[select[mode]][subselect[mode][0]][4]^=0x20;
		}

		if(subselect[mode][0]){

			if(p.x>=60&&p.x<=160&&p.y>=380&&p.y<=400){
				focus=11;
			}

			if(p.x>=60&&p.x<=160&&p.y>=400&&p.y<=420){
				focus=12;
			}

			if(p.x>=60&&p.x<=160&&p.y>=420&&p.y<=440){
				focus=13;
			}

			if(p.x>=60&&p.x<=73&&p.y>=440&&p.y<=453){
				WSAnim[select[mode]][subselect[mode][0]][0]^=0x10;
			}

			if(p.x>=60&&p.x<=73&&p.y>=460&&p.y<=473){
			//	WSAnim[select[mode]][subselect[mode][0]][0]^=0x20;
			}

		}

		if (p.x >= 200 && p.x <= 213 && p.y >= 522 && p.y <= 535) {
			AnimBorder = !AnimBorder;
		}

		if(p.x>=dwidth+666&&p.x<=dwidth+760&&p.y>=80&&p.y<=100){
			focus=14;
		}

		if(p.x>=dwidth+666&&p.x<=dwidth+760&&p.y>=100&&p.y<=120){
			focus=15;
		}
	}
}

if(submode[mode]==1){

		if(p.x>=55&&p.x<=75&&p.y>=8&&p.y<=28){
			select[mode]--;
			if(select[mode]<0)select[mode]=NumAnimSet-1;
			subselect[mode][0]=0;
		}

		if (p.x >= 76 && p.x <= 170 && p.y >= 8 && p.y <= 28) {
			focus = 1;
		}

		if(p.x>=171&&p.x<=191&&p.y>=8&&p.y<=28){
			select[mode]++;
			if(select[mode]>NumAnimSet-1)select[mode]=0;
			subselect[mode][0]=0;
		}

	j=1;

	while(AnimSets[select[mode]][j]!=0xFF){
		j++;

		if(p.x>=200&&p.x<=299&&p.y>=60+18*((j+1)/3)&&p.y<=77+18*((j+1)/3)){
			focus=3+(j+1)/3;
			subfocus=0;
		}

		if(p.x>=300&&p.x<=399&&p.y>=60+18*((j+1)/3)&&p.y<=77+18*((j+1)/3)){
			focus=3+(j+1)/3;
			subfocus=1;
		}

		if(p.x>=400&&p.x<=499&&p.y>=60+18*((j+1)/3)&&p.y<=77+18*((j+1)/3)){
			focus=3+(j+1)/3;
			subfocus=2;
		}

		j+=2;
	}

	if(j<73){
		if(p.x>=60&&p.x<=160&&p.y>=80&&p.y<=110){
			AnimSets[select[mode]][j]=0;
			AnimSets[select[mode]][j+1]=0;
			AnimSets[select[mode]][j+2]=0;
			AnimSets[select[mode]][j+3]=0xFF;
			AnimSets[select[mode]][j+4]=0xFF;
		}
	}

	if(j>1){
		if(p.x>=60&&p.x<=160&&p.y>=120&&p.y<=150){
			AnimSets[select[mode]][j-3]=0xFF;
			AnimSets[select[mode]][j-2]=0xFF;
		}
	}
}

if (submode[mode] == 2) {
	if (!GraphicsLoaded&&strlen(file)) {
		if (p.x >= 50 && p.x <= 176 && p.y >= 30 && p.y <= 52) {
			LoadGFX(file);
		}
	}

	if (GraphicsLoaded) {
		if (p.x >= 55 && p.x <= 75 && p.y >= 8 && p.y <= 28) {
			select[mode]--;
			if (select[mode]<0)select[mode] = NumEAnim-1;
			subselect[mode][0] = 0;
			getEAnimValues(select[mode]);
		}

		if (p.x >= 171 && p.x <= 191 && p.y >= 8 && p.y <= 28) {
			select[mode]++;
			if (select[mode]>NumEAnim - 1)select[mode] = 0;
			subselect[mode][0] = 0;
			getEAnimValues(select[mode]);
		}

		if (p.x >= 201 && p.x <= 221 && p.y >= 8 && p.y <= 28) {
			subselect[mode][0]--;
			if (subselect[mode][0]<0)subselect[mode][0] = EAnim[select[mode]][0][0];
		}

		if (p.x >= 292 && p.x <= 312 && p.y >= 8 && p.y <= 28) {
			subselect[mode][0]++;
			if (subselect[mode][0]>EAnim[select[mode]][0][0])subselect[mode][0] = 0;
		}

		if (p.x >= dwidth + 645 && p.x <= dwidth + 665 && p.y >= 80 && p.y <= 100) {
			subselect[mode][1]--;
			if (subselect[mode][1]<0)subselect[mode][1] = NumGFX[1] - 1;
		}

		if (p.x >= dwidth + 761 && p.x <= dwidth + 781 && p.y >= 80 && p.y <= 100) {
			subselect[mode][1]++;
			if (subselect[mode][1]>NumGFX[1] - 1)subselect[mode][1] = 0;
		}

		if (p.x >= 330 && p.x <= 434 && p.y >= 3 && p.y <= 33) {
			if (NumEAnim < 256) {
				select[mode] = NumEAnim;
				NumEAnim++;
				EAnim[select[mode]][0][0] = 0;
				EAnim[select[mode]][0][1] = -1;
				EAnim[select[mode]][0][2] = 1;
				EAnim[select[mode]][0][3] = 0;

				for (int q = 4;q < 256;q++) {
					EAnim[select[mode]][0][q] = 0;
				}
				getEAnimValues(select[mode]);
			}
		}

		if (p.x >= 454 && p.x <= 558 && p.y >= 3 && p.y <= 33) {
			if (NumEAnim) {
				NumEAnim--;
				select[mode] = NumEAnim - 1;
				getEAnimValues(select[mode]);
			}
		}

		if (p.x >= 76 && p.x <= 168 && p.y >= 10 && p.y <= 30) {
			focus = 1;
		}

		if (p.x >= 222 && p.x <= 291 && p.y >= 10 && p.y <= 30) {
			focus = 2;
		}

		if (p.x >= 60 && p.x <= 160 && p.y >= 40 && p.y <= 60) {
			focus=3;
		}

		if (p.x >= 60 && p.x <= 160 && p.y >= 60 && p.y <= 80) {
			focus = 4;
		}

		if (p.x >= 60 && p.x <= 160 && p.y >= 80 && p.y <= 100) {
			focus = 5;
		}

		if (p.x >= 60 && p.x <= 160 && p.y >= 100 && p.y <= 120) {
			focus = 6;
		}

		if (p.x >= 60 && p.x <= 160 && p.y >= 140 && p.y <= 160) {
			focus = 7;
		}

		if (subselect[mode][0]) {

			if (p.x >= 60 && p.x <= 160 && p.y >= 380 && p.y <= 400) {
				focus = 11;
			}

			if (p.x >= 60 && p.x <= 160 && p.y >= 400 && p.y <= 420) {
				focus = 12;
			}

			if (p.x >= 60 && p.x <= 160 && p.y >= 420 && p.y <= 440) {
				focus = 13;
			}

			if (p.x >= 60 && p.x <= 73 && p.y >= 440 && p.y <= 453) {
				EAnim[select[mode]][subselect[mode][0]][0] ^= 0x10;
			}

			if (p.x >= 60 && p.x <= 73 && p.y >= 460 && p.y <= 473) {
				//	WSAnim[select[mode]][subselect[mode][0]][0]^=0x20;
			}

		}

		if (p.x >= 200 && p.x <= 213 && p.y >= 522 && p.y <= 535) {
			AnimBorder = !AnimBorder;
		}

		if (p.x >= dwidth + 666 && p.x <= dwidth + 760 && p.y >= 80 && p.y <= 100) {
			focus = 14;
		}

	}
}

if (submode[mode] == 3) {

	if (p.x >= 55 && p.x <= 75 && p.y >= 8 && p.y <= 28) {
		select[mode]--;
		if (select[mode]<0)select[mode] = NumEAnimSet - 1;
		subselect[mode][0] = 0;
	}

	if (p.x >= 76 && p.x <= 170 && p.y >= 8 && p.y <= 28) {
		focus = 1;
	}

	if (p.x >= 171 && p.x <= 191 && p.y >= 8 && p.y <= 28) {
		select[mode]++;
		if (select[mode]>NumEAnimSet - 1)select[mode] = 0;
		subselect[mode][0] = 0;
	}

	j = 1;

	while (EAnimSets[select[mode]][j] != 0xFF) {
		j++;

		if (p.x >= 200 && p.x <= 299 && p.y >= 60 + 18 * ((j + 1) / 3) && p.y <= 77 + 18 * ((j + 1) / 3)) {
			focus = 3 + (j + 1) / 3;
			subfocus = 0;
		}

		if (p.x >= 300 && p.x <= 399 && p.y >= 60 + 18 * ((j + 1) / 3) && p.y <= 77 + 18 * ((j + 1) / 3)) {
			focus = 3 + (j + 1) / 3;
			subfocus = 1;
		}

		if (p.x >= 400 && p.x <= 499 && p.y >= 60 + 18 * ((j + 1) / 3) && p.y <= 77 + 18 * ((j + 1) / 3)) {
			focus = 3 + (j + 1) / 3;
			subfocus = 2;
		}

		j += 2;
	}

	if (j<73) {
		if (p.x >= 60 && p.x <= 160 && p.y >= 80 && p.y <= 110) {
			EAnimSets[select[mode]][j] = 0;
			EAnimSets[select[mode]][j + 1] = 0;
			EAnimSets[select[mode]][j + 2] = 0;
			EAnimSets[select[mode]][j + 3] = 0xFF;
			EAnimSets[select[mode]][j + 4] = 0xFF;
		}
	}

	if (j>1) {
		if (p.x >= 60 && p.x <= 160 && p.y >= 120 && p.y <= 150) {
			EAnimSets[select[mode]][j - 3] = 0xFF;
			EAnimSets[select[mode]][j - 2] = 0xFF;
		}
	}
}

if (submode[mode] == 4) {
#include "SpellAnimClick.h"
}

if (submode[mode] == 5) {
	if (p.x >= 55 && p.x <= 75 && p.y >= 8 && p.y <= 28) {
		select[mode]--;
		if (select[mode]<0)select[mode] = 11;
	}

	if (p.x >= 171 && p.x <= 191 && p.y >= 8 && p.y <= 28) {
		select[mode]++;
		if (select[mode]>11)select[mode] = 0;
	}

	if (p.x >= 201 && p.x <= 221 && p.y >= 8 && p.y <= 28) {
		subselect[mode][0]--;
		if (subselect[mode][0]<0)subselect[mode][0] = 14;
	}

	if (p.x >= 292 && p.x <= 312 && p.y >= 8 && p.y <= 28) {
		subselect[mode][0]++;
		if (subselect[mode][0]>14)subselect[mode][0] = 0;
	}

	if (p.x >= 76 && p.x <= 168 && p.y >= 10 && p.y <= 30) {
		focus = 1;
	}

	if (p.x >= 222 && p.x <= 291 && p.y >= 10 && p.y <= 30) {
		focus = 2;
	}

	if (p.x >= 76 && p.x <= 168 && p.y >= 50 && p.y <= 70) {
		focus = 3;
	}

	if (p.x >= 76 && p.x <= 168 && p.y >= 70 && p.y <= 90) {
		focus = 4;
	}

	if (p.x >= 76 && p.x <= 168 && p.y >= 90 && p.y <= 110) {
		focus = 5;
	}

	if (p.x >= 222 && p.x <= 352 && p.y >= 50 && p.y <= 70) {
		focus = 6;
	}

	if (p.x >= 222 && p.x <= 322 && p.y >= 70 && p.y <= 90) {
		focus = 7;
	}

	if (p.x >= 222 && p.x <= 322 && p.y >= 90 && p.y <= 110) {
		focus = 8;
	}

	if (p.x >= 222 && p.x <= 322 && p.y >= 110 && p.y <= 130) {
		focus = 9;
	}
}