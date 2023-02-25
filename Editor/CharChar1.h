c=wParam;
if(submode[mode]==0){
				switch(focus){
					case 1://name
						if((c>='a'&&c<='z')||(c>='A'&&c<='Z')||(c>='0'&&c<='9')||c==' '){
							if(strlen(CharName[select[mode]])<10){
								sprintf(CharName[select[mode]],"%s%c",CharName[select[mode]],c);
							} else CharName[select[mode]][9]=c;
						}
						if(c==8&&strlen(CharName[select[mode]])>0){
							CharName[select[mode]][strlen(CharName[select[mode]])-1]=0;
						}
						break;
					case 2://Class
						val=c-'0';
						if(val>=0&&val<10){
							i=Char[select[mode]][0];
							if(i<100){
								i*=10;
								i+=val;
								Char[select[mode]][0]=i;
							}
						}
						if(c==8){
							i=Char[select[mode]][0];
							i=i-i%10;
							i/=10;
							Char[select[mode]][0]=i;
						}
						Char[select[mode]][0]%=32;
						break;
					case 3://Level
						val=c-'0';
						if(val>=0&&val<10){
							i=Char[select[mode]][1];
							if(i<100){
								i*=10;
								i+=val;
								Char[select[mode]][1]=i;
							}
						}
						if(c==8){
							i=Char[select[mode]][1];
							i=i-i%10;
							i/=10;
							Char[select[mode]][1]=i;
						}
						Char[select[mode]][1]%=100;
						break;
					case 4://Attack
					case 5://Defense
					case 6://Agility
					case 7://Move
					case 8://Deadly Attack Rate
						val=c-'0';
						if(val>=0&&val<10){
							i=Char[select[mode]][focus-2];
							if(i<100){
								i*=10;
								i+=val;
								Char[select[mode]][focus-2]=i;
							}
						}
						if(c==8){
							i=Char[select[mode]][focus-2];
							i=i-i%10;
							i/=10;
							Char[select[mode]][focus-2]=i;
						}
						break;
					case 13://Item 1
					case 14://Item 2
					case 15://Item 3
					case 16://Item 4
					case 17://Spell 1
					case 18://Spell 2
					case 19://Spell 3
					case 20://Spell 4
						val=c-'0';
						if(val>=0&&val<10){
							i=Char[select[mode]][focus+3];
							if(i<100){
								i*=10;
								i+=val;
								Char[select[mode]][focus+3]=i;
							}
						}
						if(c==8){
							i=Char[select[mode]][focus+3];
							i=i-i%10;
							i/=10;
							Char[select[mode]][focus+3]=i;
						}
						break;
					case 9://HP
					case 10://Max HP
						val=c-'0';
						if(val>=0&&val<10){
							i=Char[select[mode]][focus-1+(focus-9)]*256+Char[select[mode]][focus+(focus-9)];
							if(i<10000){
								i*=10;
								i+=val;
								Char[select[mode]][focus+(focus-9)]=i%256;
								Char[select[mode]][focus-1+(focus-9)]=(i-Char[select[mode]][focus+(focus-9)])/256;
							}
						}
						if(c==8){
							i=Char[select[mode]][focus-1+(focus-9)]*256+Char[select[mode]][focus+(focus-9)];
							i=i-i%10;
							i/=10;
							Char[select[mode]][focus+(focus-9)]=i%256;
							Char[select[mode]][focus-1+(focus-9)]=(i-Char[select[mode]][focus+(focus-9)])/256;
						}
						break;
					case 11://MP
					case 12://Max MP
						val=c-'0';
						if(val>=0&&val<10){
							i=Char[select[mode]][focus+1];
							if(i<100){
								i*=10;
								i+=val;
								Char[select[mode]][focus+1]=i;
							}
						}
						if(c==8){
							i=Char[select[mode]][focus+1];
							i=i-i%10;
							i/=10;
							Char[select[mode]][focus+1]=i;
						}
						break;
					case 21://stat growth
					case 22:
					case 23:
					case 24:
					case 25:
					case 26:
					case 27://promoted stat growth
					case 28:
					case 29:
					case 30:
					case 31:
					case 32:
						val=c-'0';
						if(val>=0&&val<10){
							i=Stats[select[mode]][focus-21]%64;
							if(i<100){
								i*=10;
								i+=val;
								Stats[select[mode]][focus-21]=i%64+Stats[select[mode]][focus-21]-Stats[select[mode]][focus-21]%64;
							}
						}
						if(c==8){
							i=Stats[select[mode]][focus-21]%64;
							i=i-i%10;
							i/=10;
							Stats[select[mode]][focus-21]=i%64+Stats[select[mode]][focus-21]-Stats[select[mode]][focus-21]%64;
						}
						break;
					case 33://offset
						val=c-'0';
						if(c>='a'&&c<='f'){
							val=c-'a'+10;
						}
						if(c>='A'&&c<='F'){
							val=c-'A'+10;
						}
						if(val>=0&&val<16){
							l=CharOffset;
							if(l<524288){
								l*=16;
								l+=val;
								CharOffset=l;
							}
						}
						if(c==8){
							l=CharOffset;
							l=l-l%16;
							l/=16;
							CharOffset=l;
						}
						break;
					case 34://Battle Sprite
					case 35://Battle Palette
						val=c-'0';
						if(val>=0&&val<10){
							i=BattleSprite[select[mode]][focus-34];
							if(i<100){
								i*=10;
								i+=val;
								BattleSprite[select[mode]][focus-34]=i;
							}
						}
						if(c==8){
							i=BattleSprite[select[mode]][focus-34];
							i=i-i%10;
							i/=10;
							BattleSprite[select[mode]][focus-34]=i;
						}
						break;
					case 36://portrait
						val = c - '0';
						if (val >= 0 && val<10) {
							i = CharPortrait[select[mode]];
							if (i<100) {
								i *= 10;
								i += val;
								CharPortrait[select[mode]] = i;
							}
						}
						if (c == 8) {
							i = CharPortrait[select[mode]];
							i = i - i % 10;
							i /= 10;
							CharPortrait[select[mode]] = i;
						}
						if (CharPortrait[select[mode]] > NumGFX[6]-1)CharPortrait[select[mode]] = NumGFX[6]-1;
						break;
					case 37://map sprite
						val = c - '0';
						if (val >= 0 && val<10) {
							i = CharMapSprite[select[mode]];
							if (i<100) {
								i *= 10;
								i += val;
								CharMapSprite[select[mode]] = i;
							}
						}
						if (c == 8) {
							i = CharMapSprite[select[mode]];
							i = i - i % 10;
							i /= 10;
							CharMapSprite[select[mode]] = i;
						}
						if (CharMapSprite[select[mode]] > NumGFX[7] - 1)CharMapSprite[select[mode]] = NumGFX[7] - 1;
						break;
					case 38://portrait2
						val = c - '0';
						if (val >= 0 && val<10) {
							i = CharPortrait2[select[mode]];
							if (i<100) {
								i *= 10;
								i += val;
								CharPortrait2[select[mode]] = i;
							}
						}
						if (c == 8) {
							i = CharPortrait2[select[mode]];
							i = i - i % 10;
							i /= 10;
							CharPortrait2[select[mode]] = i;
						}
						if (CharPortrait2[select[mode]] > NumGFX[6] - 1)CharPortrait2[select[mode]] = NumGFX[6] - 1;
						break;
					case 39://map sprite 2
						val = c - '0';
						if (val >= 0 && val<10) {
							i = CharMapSprite2[select[mode]];
							if (i<100) {
								i *= 10;
								i += val;
								CharMapSprite2[select[mode]] = i;
							}
						}
						if (c == 8) {
							i = CharMapSprite2[select[mode]];
							i = i - i % 10;
							i /= 10;
							CharMapSprite2[select[mode]] = i;
						}
						if (CharMapSprite2[select[mode]] > NumGFX[7] - 1)CharMapSprite2[select[mode]] = NumGFX[7] - 1;
						break;
					case 40://Battle Sprite 2
					case 41://Battle Palette 2
						val = c - '0';
						if (val >= 0 && val<10) {
							i = BattleSprite2[select[mode]][focus - 40];
							if (i<100) {
								i *= 10;
								i += val;
								BattleSprite2[select[mode]][focus - 40] = i;
							}
						}
						if (c == 8) {
							i = BattleSprite2[select[mode]][focus - 40];
							i = i - i % 10;
							i /= 10;
							BattleSprite2[select[mode]][focus - 40] = i;
						}
						break;
					case 42:
						if (romsize >= 0x200000) {
							val = c - '0';
							if (val >= 0 && val<10) {
								i = CharPromotedAt[select[mode]];
								if (i<100) {
									i *= 10;
									i += val;

									if (i >= 100)i = 99;

									CharPromotedAt[select[mode]] = i;
								}
							}
							if (c == 8) {
								i = CharPromotedAt[select[mode]];
								i = i - i % 10;
								i /= 10;
								CharPromotedAt[select[mode]] = i;
							}
						}
						break;
				}
}

if(submode[mode]==1){
	if(focus){
		ChangeCurves=true;
		val=c-'0';
		if(val>=0&&val<10){
			i=Curves[subselect[mode][0]][focus];
			if(i==255)i=0;
			if(i<100){
				i*=10;
				i+=val;
				Curves[subselect[mode][0]][focus]=i;
			}
		}
		if(c==8){
			i=Curves[subselect[mode][0]][focus];
			if(i==0)
				i=255;
			else if(i==255)
				i=0;
			else {
				i=i-i%10;
				i/=10;
			}
			Curves[subselect[mode][0]][focus]=i;
		}
		if(Curves[subselect[mode][0]][focus]!=255&&Curves[subselect[mode][0]][focus]>100)Curves[subselect[mode][0]][focus]=100;
	}
}