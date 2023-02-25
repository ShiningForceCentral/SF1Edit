				c=wParam;
				switch(focus){
					case 1://name
						if((c>='a'&&c<='z')||(c>='A'&&c<='Z')||(c>='0'&&c<='9')||c==' '){
							if(strlen(Classes[select[mode]])<4){
								sprintf(Classes[select[mode]],"%s%c",Classes[select[mode]],c);
							} else Classes[select[mode]][3]=c;
						}
						if(c==8&&strlen(Classes[select[mode]])>0){
							Classes[select[mode]][strlen(Classes[select[mode]])-1]=0;
						}
						break;
					//case 2:
					//case 3:
					//case 4:
					//case 5:
					case 6:
					case 7:
					case 8:
					//case 9:
						val=c-'0';
						if(val>=0&&val<10){
							i=ClassData[select[mode]][focus-2];
							if(i<100){
								i*=10;
								i+=val;
								ClassData[select[mode]][focus-2]=i;
							}
						}
						if(c==8){
							i=ClassData[select[mode]][focus-2];
							i=i-i%10;
							i/=10;
							ClassData[select[mode]][focus-2]=i;
						}
						break;
					case 12://spell priority
						val=c-'0';
						if(val>=0&&val<10){
							i=Priority[select[mode]];
							if(i<100){
								i*=10;
								i+=val;
								Priority[select[mode]]=i;
							}
						}
						if(c==8){
							i=Priority[select[mode]];
							i=i-i%10;
							i/=10;
							Priority[select[mode]]=i;
						}
						if(Priority[select[mode]]>100)Priority[select[mode]]=100;
						break;
				}