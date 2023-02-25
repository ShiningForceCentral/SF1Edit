			c=wParam;
			switch(focus){
				case 1://name
					if((c>='a'&&c<='z')||(c>='A'&&c<='Z')||(c>='0'&&c<='9')||c==' '){
						if(NumMonsters==73&&totalLength(MonsterName,73)>=618){
							MessageBox(NULL,"You are at the maximum length for monster names.","Error",MB_OK);
							return false;
						}
						if(strlen(MonsterName[select[mode]])<16){
							sprintf(MonsterName[select[mode]],"%s%c",MonsterName[select[mode]],c);
						} else MonsterName[select[mode]][9]=c;
					}
					if(c==8&&strlen(MonsterName[select[mode]])>0){
						MonsterName[select[mode]][strlen(MonsterName[select[mode]])-1]=0;
					}
					break;
				case 2://Coins
					val=c-'0';
					if(val>=0&&val<10){
						i=Monster[select[mode]][0]*256+Monster[select[mode]][1];
						if(i<10000){
							i*=10;
							i+=val;
							Monster[select[mode]][1]=i%256;
							Monster[select[mode]][0]=(i-Monster[select[mode]][1])/256;
						}
					}
					if(c==8){
						i=Monster[select[mode]][0]*256+Monster[select[mode]][1];
						i=i-i%10;
						i/=10;
						Monster[select[mode]][1]=i%256;
						Monster[select[mode]][0]=(i-Monster[select[mode]][1])/256;
					}
					break;
				case 3://MonsterName
				case 4://Level
				case 5://Attack
				case 6://Defense
				case 7://Agility
				case 8://Move
					val=c-'0';
					if(val>=0&&val<10){
						i=Monster[select[mode]][focus-1];
						if(i<100){
							i*=10;
							i+=val;
							Monster[select[mode]][focus-1]=i;
						}
					}
					if(c==8){
						i=Monster[select[mode]][focus-1];
						i=i-i%10;
						i/=10;
						Monster[select[mode]][focus-1]=i;
					}
					break;
				case 10://MP
				case 11://Status
				case 12://Map Sprite
				case 13://Battle Sprite
				case 14://Battle Palette
				case 15://Portrait
				case 16://Critical
					val=c-'0';
					if(val>=0&&val<10){
						i=Monster[select[mode]][focus];
						if(i<100){
							i*=10;
							i+=val;
							Monster[select[mode]][focus]=i;
						}
					}
					if(c==8){
						i=Monster[select[mode]][focus];
						i=i-i%10;
						i/=10;
						Monster[select[mode]][focus]=i;
					}
					break;
				case 9://HP
					val=c-'0';
					if(val>=0&&val<10){
						i=Monster[select[mode]][8]*256+Monster[select[mode]][9];
						if(i<10000){
							i*=10;
							i+=val;
							Monster[select[mode]][9]=i%256;
							Monster[select[mode]][8]=(i-Monster[select[mode]][9])/256;
						}
					}
					if(c==8){
						i=Monster[select[mode]][8]*256+Monster[select[mode]][9];
						i=i-i%10;
						i/=10;
						Monster[select[mode]][9]=i%256;
						Monster[select[mode]][8]=(i-Monster[select[mode]][9])/256;
					}
					break;
			}