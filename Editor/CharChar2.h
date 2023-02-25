				c=wParam;
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
					case 2://level
						val=c-'0';

						if(val>=0&&val<10){
							j=Learn[select[mode]][subfocus][0];
							if(j<100){
								j*=10;
								j+=val;
								if(j>119)j=119;
								Learn[select[mode]][subfocus][0]=j;
							}
						}
						if(c==8){
							j=Learn[select[mode]][subfocus][0];
							if(j==0){
								NumLearn[select[mode]]--;
								for(i=subfocus;i<NumLearn[select[mode]];i++){
									Learn[select[mode]][i][0]=Learn[select[mode]][i+1][0];
									Learn[select[mode]][i][1]=Learn[select[mode]][i+1][1];
								}
								focus=0;
								return 0;
							}
							j=j-j%10;
							j/=10;
							Learn[select[mode]][subfocus][0]=j;
						}
						break;
					case 3://spell
						val=c-'0';

						if(val>=0&&val<10){
							l=Learn[select[mode]][subfocus][1];
							if(l<100){
								l*=10;
								l+=val;
								Learn[select[mode]][subfocus][1]=l;
							}
						}
						if(c==8){
							l=Learn[select[mode]][subfocus][1];
							if(l==0){
								NumLearn[select[mode]]--;
								for(i=subfocus;i<NumLearn[select[mode]];i++){
									Learn[select[mode]][i][0]=Learn[select[mode]][i+1][0];
									Learn[select[mode]][i][1]=Learn[select[mode]][i+1][1];
								}
								focus=0;
								return 0;
							}
							l=l-l%10;
							l/=10;
							Learn[select[mode]][subfocus][1]=l;
						}
						break;
					case 4://offset
						val=c-'0';
						if(c>='a'&&c<='f'){
							val=c-'a'+10;
						}
						if(c>='A'&&c<='F'){
							val=c-'A'+10;
						}
						if(val>=0&&val<16){
							l=LearnOffset;
							if(l<524288){
								l*=16;
								l+=val;
								LearnOffset=l;
							}
						}
						if(c==8){
							l=LearnOffset;
							l=l-l%16;
							l/=16;
							LearnOffset=l;
						}
						break;
				}