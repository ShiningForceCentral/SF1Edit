
	c=wParam;

if(submode[mode]==0){
	if(focus==1){
		val=c-'0';
		if(val>=0&&val<10){
			i=select[mode];
			if(i<10){
				i*=10;
				i+=val;
				select[mode]=i;
			}
		}
		if(c==8){
			i = select[mode];
			i=i-i%10;
			i/=10;
			select[mode]=i;
		}
		select[mode]%= NumAnim;
		getAnimValues(select[mode]);
	}
	if(focus==2){
		val=c-'0';
		if(val>=0&&val<10){
			i=subselect[mode][0];
			if(i<100){
				i*=10;
				i+=val;
				subselect[mode][0]=i;
			}
		}
		if(c==8){
			i=subselect[mode][0];
			i=i-i%10;
			i/=10;
			subselect[mode][0]=i;
		}
		subselect[mode][0]%=WSAnim[select[mode]][0][0]+1;
	}

	if (focus == 3) {
		val = c - '0';
		if (val >= 0 && val<10) {
			i = WSAnim[select[mode]][0][0];
			if (i<100) {
				if (i!=0xFF) {
					i++;
					i *= 10;
					i += val;
					i--;
				} else {
					i = val - 1;
				}
				WSAnim[select[mode]][0][0] = i;
			}
		}
		if (c == 8) {
			if (WSAnim[select[mode]][0][0] >=9 && WSAnim[select[mode]][0][0] != -1) {
				i = WSAnim[select[mode]][0][0];
				i++;
				i = i - i % 10;
				i /= 10;
				i--;
			} else if (i != 0xFF) {
				i = 0xFF;
			} else i = 0;
			WSAnim[select[mode]][0][0] = i;
		}
		if (WSAnim[select[mode]][0][0]>31 && WSAnim[select[mode]][0][0]!=0xFF)WSAnim[select[mode]][0][0] = 31;
		if (WSAnim[select[mode]][0][0]<0 && WSAnim[select[mode]][0][0] != -1)WSAnim[select[mode]][0][0] = 0;
	}

	if(focus==4){
		val=c-'0';
		if(val>=0&&val<10){
			i=WSAnim[select[mode]][0][2];
			if(i<100){
				i*=10;
				if(i<0||editneg)i-=val;
				else i+=val;
				WSAnim[select[mode]][0][2]=i;
			}
		}
		if(c==8){
			i=WSAnim[select[mode]][0][2];
			i=i-i%10;
			i/=10;
			WSAnim[select[mode]][0][2]=i;
		}
		if(c=='-'){
			if(WSAnim[select[mode]][0][2]){
				WSAnim[select[mode]][0][2]*=-1;
			} else {
				editneg=true;
			}
		}
	}
	if(focus==5){
		val=c-'0';
		if(val>=0&&val<10){
			i=WSAnim[select[mode]][0][1];
			if(i<100){
				i*=10;
				if(i<0||editneg)i-=val;
				else i+=val;
				WSAnim[select[mode]][0][1]=i;
			}
		}
		if(c==8){
			i=WSAnim[select[mode]][0][1];
			i=i-i%10;
			i/=10;
			WSAnim[select[mode]][0][1]=i;
		}
		if(c=='-'){
			if(WSAnim[select[mode]][0][1]){
				WSAnim[select[mode]][0][1]*=-1;
			} else {
				editneg=true;
			}
		}
	}
	if(focus==6){
		val=c-'0';
		if(val>=0&&val<10){
			i=WSAnim[select[mode]][0][3];
			if(i<100){
				i*=10;
				if(i<0||editneg)i-=val;
				else i+=val;
				WSAnim[select[mode]][0][3]=i;
			}
		}
		if(c==8){
			i=WSAnim[select[mode]][0][3];
			i=i-i%10;
			i/=10;
			WSAnim[select[mode]][0][3]=i;
		}
		if(c=='-'){
			if(WSAnim[select[mode]][0][3]){
				WSAnim[select[mode]][0][3]*=-1;
			} else {
				editneg=true;
			}
		}
	}
	if(focus==7){
		val=c-'0';
		if(val>=0&&val<10){
			i=WSAnim[select[mode]][subselect[mode][0]][1];
			if(i<100){
				i*=10;
				if(i<0||editneg)i-=val;
				else i+=val;
				WSAnim[select[mode]][subselect[mode][0]][1]=i;
			}
		}
		if(c==8){
			i=WSAnim[select[mode]][subselect[mode][0]][1];
			i=i-i%10;
			i/=10;
			WSAnim[select[mode]][subselect[mode][0]][1]=i;
		}
		if(c=='-'){
			if(WSAnim[select[mode]][subselect[mode][0]][1]){
				WSAnim[select[mode]][subselect[mode][0]][1]*=-1;
			} else {
				editneg=true;
			}
		}
	}
	if(focus==8){
		val=c-'0';
		if(val>=0&&val<10){
			i=WSAnim[select[mode]][subselect[mode][0]][4]&0x0F;
			if(i<100){
				i*=10;
				i+=val;
				i&=0x03;
				WSAnim[select[mode]][subselect[mode][0]][4]&=0xF0;
				WSAnim[select[mode]][subselect[mode][0]][4]+=i;
			}
		}
		if(c==8){
			i=WSAnim[select[mode]][subselect[mode][0]][4]&0x0F;
			i=i-i%10;
			i/=10;
			WSAnim[select[mode]][subselect[mode][0]][4]&=0xF0;
			WSAnim[select[mode]][subselect[mode][0]][4]+=i;
		}
	}
	if(focus==9){
		val=c-'0';
		if(val>=0&&val<10){
			i=WSAnim[select[mode]][subselect[mode][0]][6];
			if(i<100){
				i*=10;
				if(i<0||editneg)i-=val;
				else i+=val;
				WSAnim[select[mode]][subselect[mode][0]][6]=i;
			}
		}
		if(c==8){
			i=WSAnim[select[mode]][subselect[mode][0]][6];
			i=i-i%10;
			i/=10;
			WSAnim[select[mode]][subselect[mode][0]][6]=i;
		}
		if(c=='-'){
			if(WSAnim[select[mode]][subselect[mode][0]][6]){
				WSAnim[select[mode]][subselect[mode][0]][6]*=-1;
			} else {
				editneg=true;
			}
		}
	}
	if(focus==10){
		val=c-'0';
		if(val>=0&&val<10){
			i=WSAnim[select[mode]][subselect[mode][0]][7];
			if(i<100){
				i*=10;
				if(i<0||editneg)i-=val;
				else i+=val;
				WSAnim[select[mode]][subselect[mode][0]][7]=i;
			}
		}
		if(c==8){
			i=WSAnim[select[mode]][subselect[mode][0]][7];
			i=i-i%10;
			i/=10;
			WSAnim[select[mode]][subselect[mode][0]][7]=i;
		}
		if(c=='-'){
			if(WSAnim[select[mode]][subselect[mode][0]][7]){
				WSAnim[select[mode]][subselect[mode][0]][7]*=-1;
			} else {
				editneg=true;
			}
		}
	}


	if(focus==11){
		val=c-'0';
		if(val>=0&&val<10){
			i=WSAnim[select[mode]][subselect[mode][0]][0]&0x0F;
			if(i<100){
				i*=10;
				i+=val;
				i&=0x0F;
				WSAnim[select[mode]][subselect[mode][0]][0]&=0xF0;
				WSAnim[select[mode]][subselect[mode][0]][0]+=i;
			}
		}
		if(c==8){
			i=WSAnim[select[mode]][subselect[mode][0]][0]&0x0F;
			i=i-i%10;
			i/=10;
			WSAnim[select[mode]][subselect[mode][0]][0]&=0xF0;
			WSAnim[select[mode]][subselect[mode][0]][0]+=i;
		}
	}
	if(focus==12){
		val=c-'0';
		if(val>=0&&val<10){
			i=WSAnim[select[mode]][subselect[mode][0]][2];
			if(i<100){
				i*=10;
				if(i<0||editneg)i-=val;
				else i+=val;
				WSAnim[select[mode]][subselect[mode][0]][2]=i;
			}
		}
		if(c==8){
			i=WSAnim[select[mode]][subselect[mode][0]][2];
			i=i-i%10;
			i/=10;
			WSAnim[select[mode]][subselect[mode][0]][2]=i;
		}
		if(c=='-'){
			if(WSAnim[select[mode]][subselect[mode][0]][2]){
				WSAnim[select[mode]][subselect[mode][0]][2]*=-1;
			} else {
				editneg=true;
			}
		}
	}
	if(focus==13){
		val=c-'0';
		if(val>=0&&val<10){
			i=WSAnim[select[mode]][subselect[mode][0]][3];
			if(i<100){
				i*=10;
				if(i<0||editneg)i-=val;
				else i+=val;
				WSAnim[select[mode]][subselect[mode][0]][3]=i;
			}
		}
		if(c==8){
			i=WSAnim[select[mode]][subselect[mode][0]][3];
			i=i-i%10;
			i/=10;
			WSAnim[select[mode]][subselect[mode][0]][3]=i;
		}
		if(c=='-'){
			if(WSAnim[select[mode]][subselect[mode][0]][3]){
				WSAnim[select[mode]][subselect[mode][0]][3]*=-1;
			} else {
				editneg=true;
			}
		}
	}


	if(focus==14){
		val=c-'0';
		if(val>=0&&val<10){
			i=subselect[mode][1];
			if(i<10){
				i*=10;
				i+=val;
				subselect[mode][1]=i;
			}
		}
		if(c==8){
			i=subselect[mode][1];
			i=i-i%10;
			i/=10;
			subselect[mode][1]=i;
		}
		subselect[mode][1]%=35;
	}
	if(focus==15){
		val=c-'0';
		if(val>=0&&val<100){
			i=subselect[mode][2];
			if(i<10){
				i*=10;
				i+=val;
				subselect[mode][2]=i;
			}
		}
		if(c==8){
			i=subselect[mode][2];
			i=i-i%10;
			i/=10;
			subselect[mode][2]=i;
		}
		if (subselect[mode][2] > 130)subselect[mode][2] = 130;
		if (subselect[mode][2] > NumGFX[2]-1 && subselect[mode][2] < 128)subselect[mode][2] = NumGFX[2] - 1;
	}
}

if(submode[mode]==1){
	if (focus == 1) {
		val = c - '0';
		if (val >= 0 && val<10) {
			i = select[mode];
			if (i<10) {
				i *= 10;
				i += val;
				select[mode] = i;
			}
		}
		if (c == 8) {
			i = select[mode];
			i = i - i % 10;
			i /= 10;
			select[mode] = i;
		}
		select[mode] %= NumAnimSet;
	}
	if(focus>3){
		val=c-'0';
		if(val>=0&&val<10){
			i=AnimSets[select[mode]][3*(focus-3)-2+subfocus];
			if(i<100){
				i*=10;
				i+=val;
				AnimSets[select[mode]][3*(focus-3)-2+subfocus]=i;
			}
		}
		if(c==8){
			i=AnimSets[select[mode]][3*(focus-3)-2+subfocus];
			i=i-i%10;
			i/=10;
			AnimSets[select[mode]][3*(focus-3)-2+subfocus]=i;
		}
	}
}

if (submode[mode] == 2) {
	if (focus == 1) {
		val = c - '0';
		if (val >= 0 && val<10) {
			i = select[mode];
			if (i<10) {
				i *= 10;
				i += val;
				select[mode] = i;
			}
		}
		if (c == 8) {
			i = select[mode];
			i = i - i % 10;
			i /= 10;
			select[mode] = i;
		}
		select[mode] %= NumEAnim;
		getEAnimValues(select[mode]);
	}
	if (focus == 2) {
		val = c - '0';
		if (val >= 0 && val<10) {
			i = subselect[mode][0];
			if (i<100) {
				i *= 10;
				i += val;
				subselect[mode][0] = i;
			}
		}
		if (c == 8) {
			i = subselect[mode][0];
			i = i - i % 10;
			i /= 10;
			subselect[mode][0] = i;
		}
		subselect[mode][0] %= EAnim[select[mode]][0][0] + 1;
	}

	if (focus == 3) {
		val = c - '0';
		if (val >= 0 && val<10) {
			i = EAnim[select[mode]][0][0];
			if (i<100) {
				i++;
				i *= 10;
				i += val;
				i--;
				EAnim[select[mode]][0][0] = i;
			}
		}
		if (c == 8) {
			i = EAnim[select[mode]][0][0];
			i++;
			i = i - i % 10;
			i /= 10;
			i--;
			EAnim[select[mode]][0][0] = i;
		}
		if(EAnim[select[mode]][0][0]>31)EAnim[select[mode]][0][0] = 31;
	}

	if (focus == 4) {
		val = c - '0';
		if (val >= 0 && val<10) {
			i = EAnim[select[mode]][0][2];
			if (i<100) {
				i *= 10;
				if (i<0 || editneg)i -= val;
				else i += val;
				EAnim[select[mode]][0][2] = i;
			}
		}
		if (c == 8) {
			i = EAnim[select[mode]][0][2];
			i = i - i % 10;
			i /= 10;
			EAnim[select[mode]][0][2] = i;
		}
		if (c == '-') {
			if (EAnim[select[mode]][0][2]) {
				EAnim[select[mode]][0][2] *= -1;
			} else {
				editneg = true;
			}
		}
	}
	if (focus == 5) {
		val = c - '0';
		if (val >= 0 && val<10) {
			i = EAnim[select[mode]][0][1];
			if (i<100) {
				i *= 10;
				if (i<0 || editneg)i -= val;
				else i += val;
				EAnim[select[mode]][0][1] = i;
			}
		}
		if (c == 8) {
			i = EAnim[select[mode]][0][1];
			i = i - i % 10;
			i /= 10;
			EAnim[select[mode]][0][1] = i;
		}
		if (c == '-') {
			if (EAnim[select[mode]][0][1]) {
				EAnim[select[mode]][0][1] *= -1;
			} else {
				editneg = true;
			}
		}
	}
	if (focus == 6) {
		val = c - '0';
		if (val >= 0 && val<10) {
			i = EAnim[select[mode]][0][3];
			if (i<100) {
				i *= 10;
				if (i<0 || editneg)i -= val;
				else i += val;
				EAnim[select[mode]][0][3] = i;
			}
		}
		if (c == 8) {
			i = EAnim[select[mode]][0][3];
			i = i - i % 10;
			i /= 10;
			EAnim[select[mode]][0][3] = i;
		}
		if (c == '-') {
			if (EAnim[select[mode]][0][3]) {
				EAnim[select[mode]][0][3] *= -1;
			} else {
				editneg = true;
			}
		}
	}
	if (focus == 7) {
		val = c - '0';
		if (val >= 0 && val<10) {
			i = EAnim[select[mode]][subselect[mode][0]][1];
			if (i<100) {
				i *= 10;
				if (i<0 || editneg)i -= val;
				else i += val;
				EAnim[select[mode]][subselect[mode][0]][1] = i;
			}
		}
		if (c == 8) {
			i = EAnim[select[mode]][subselect[mode][0]][1];
			i = i - i % 10;
			i /= 10;
			EAnim[select[mode]][subselect[mode][0]][1] = i;
		}
		if (c == '-') {
			if (EAnim[select[mode]][subselect[mode][0]][1]) {
				EAnim[select[mode]][subselect[mode][0]][1] *= -1;
			} else {
				editneg = true;
			}
		}
	}


	if (focus == 11) {
		val = c - '0';
		if (val >= 0 && val<10) {
			i = EAnim[select[mode]][subselect[mode][0]][0] & 0x0F;
			if (i<100) {
				i *= 10;
				i += val;
				i &= 0x0F;
				EAnim[select[mode]][subselect[mode][0]][0] &= 0xF0;
				EAnim[select[mode]][subselect[mode][0]][0] += i;
			}
		}
		if (c == 8) {
			i = EAnim[select[mode]][subselect[mode][0]][0] & 0x0F;
			i = i - i % 10;
			i /= 10;
			EAnim[select[mode]][subselect[mode][0]][0] &= 0xF0;
			EAnim[select[mode]][subselect[mode][0]][0] += i;
		}
	}
	if (focus == 12) {
		val = c - '0';
		if (val >= 0 && val<10) {
			i = EAnim[select[mode]][subselect[mode][0]][2];
			if (i<100) {
				i *= 10;
				if (i<0 || editneg)i -= val;
				else i += val;
				EAnim[select[mode]][subselect[mode][0]][2] = i;
			}
		}
		if (c == 8) {
			i = EAnim[select[mode]][subselect[mode][0]][2];
			i = i - i % 10;
			i /= 10;
			EAnim[select[mode]][subselect[mode][0]][2] = i;
		}
		if (c == '-') {
			if (EAnim[select[mode]][subselect[mode][0]][2]) {
				EAnim[select[mode]][subselect[mode][0]][2] *= -1;
			} else {
				editneg = true;
			}
		}
	}
	if (focus == 13) {
		val = c - '0';
		if (val >= 0 && val<10) {
			i = EAnim[select[mode]][subselect[mode][0]][3];
			if (i<100) {
				i *= 10;
				if (i<0 || editneg)i -= val;
				else i += val;
				EAnim[select[mode]][subselect[mode][0]][3] = i;
			}
		}
		if (c == 8) {
			i = EAnim[select[mode]][subselect[mode][0]][3];
			i = i - i % 10;
			i /= 10;
			EAnim[select[mode]][subselect[mode][0]][3] = i;
		}
		if (c == '-') {
			if (EAnim[select[mode]][subselect[mode][0]][3]) {
				EAnim[select[mode]][subselect[mode][0]][3] *= -1;
			} else {
				editneg = true;
			}
		}
	}


	if (focus == 14) {
		val = c - '0';
		if (val >= 0 && val<10) {
			i = subselect[mode][1];
			if (i<10) {
				i *= 10;
				i += val;
				subselect[mode][1] = i;
			}
		}
		if (c == 8) {
			i = subselect[mode][1];
			i = i - i % 10;
			i /= 10;
			subselect[mode][1] = i;
		}
		subselect[mode][1] %= 35;
	}
}

if (submode[mode] == 3) {
	if (focus == 1) {
		val = c - '0';
		if (val >= 0 && val<10) {
			i = select[mode];
			if (i<10) {
				i *= 10;
				i += val;
				select[mode] = i;
			}
		}
		if (c == 8) {
			i = select[mode];
			i = i - i % 10;
			i /= 10;
			select[mode] = i;
		}
		select[mode] %= NumEAnimSet;
	}
	if (focus>3) {
		val = c - '0';
		if (val >= 0 && val<10) {
			i = EAnimSets[select[mode]][3 * (focus - 3) - 2 + subfocus];
			if (i<100) {
				i *= 10;
				i += val;
				EAnimSets[select[mode]][3 * (focus - 3) - 2 + subfocus] = i;
			}
		}
		if (c == 8) {
			i = EAnimSets[select[mode]][3 * (focus - 3) - 2 + subfocus];
			i = i - i % 10;
			i /= 10;
			EAnimSets[select[mode]][3 * (focus - 3) - 2 + subfocus] = i;
		}
	}
}

if (submode[mode] == 4) {
#include "SpellAnimChar.h"
}


if (submode[mode] == 5) {
	if (focus == 1) {
		val = c - '0';
		if (val >= 0 && val < 10) {
			i = select[mode];
			if (i < 10) {
				i *= 10;
				i += val;
				select[mode] = i;
			}
		}
		if (c == 8) {
			i = select[mode];
			i = i - i % 10;
			i /= 10;
			select[mode] = i;
		}
		select[mode] %= 12;
	}
	if (focus == 2) {
		val = c - '0';
		if (val >= 0 && val < 10) {
			i = subselect[mode][0];
			if (i < 100) {
				i *= 10;
				i += val;
				subselect[mode][0] = i;
			}
		}
		if (c == 8) {
			i = subselect[mode][0];
			i = i - i % 10;
			i /= 10;
			subselect[mode][0] = i;
		}
		subselect[mode][0] %= 15;
	}
	if (focus == 3 || focus==4 || focus==5) {
		val = c - '0';
		if (val >= 0 && val < 10) {
			i = EndingForce[select[mode]][focus - 3];
			if (i < 100) {
				i *= 10;
				i += val;
				EndingForce[select[mode]][focus-3] = i;
			}
		}
		if (c == 8) {
			i = EndingForce[select[mode]][focus - 3];
			i = i - i % 10;
			i /= 10;
			EndingForce[select[mode]][focus - 3] = i;
		}
	}

	if (focus == 6 || focus == 7 || focus == 8 || focus == 9) {
		val = c - '0';
		if (val >= 0 && val < 10) {
			i = EndingScenes[subselect[mode][0]][focus - 6];
			if (i < 100) {
				i *= 10;
				i += val;
				EndingScenes[subselect[mode][0]][focus - 6] = i;
			}
		}
		if (c == 8) {
			i = EndingScenes[subselect[mode][0]][focus - 6];
			i = i - i % 10;
			i /= 10;
			EndingScenes[subselect[mode][0]][focus - 6] = i;
		}
	}



	
}