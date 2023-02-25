			c=wParam;
			switch(focus){
				case 1://name
					if((c>='a'&&c<='z')||(c>='A'&&c<='Z')||(c>='0'&&c<='9')||c==' '){
						if(!ExpandSpells&&totalLength(SpellName,63)>=103){
							MessageBox(NULL,"You are at the maximum length for spell names.\nEither use extended spells or shorten another spell name.","Error",MB_OK);
							return false;
						}
						if(strlen(SpellName[select[mode]])<6){
							sprintf(SpellName[select[mode]],"%s%c",SpellName[select[mode]],c);
						} else SpellName[select[mode]][5]=c;
					}
					if(c==8&&strlen(SpellName[select[mode]])>0){
						SpellName[select[mode]][strlen(SpellName[select[mode]])-1]=0;
					}
					break;
				case 2://range
					val=c-'0';
					if(val>=0&&val<10){
						i=Spell[select[mode]][0+4*subfocus];
						if(i<100){
							i*=10;
							i+=val;
							Spell[select[mode]][0+4*subfocus]=i;
						}
					}
					if(c==8){
						i=Spell[select[mode]][0+4*subfocus];
						i=i-i%10;
						i/=10;
						Spell[select[mode]][0+4*subfocus]=i;
					}
					break;
				case 3://effect
					val=c-'0';
					if(val>=0&&val<10){
						i=Spell[select[mode]][1+4*subfocus];
						if(i<100){
							i*=10;
							i+=val;
							Spell[select[mode]][1+4*subfocus]=i;
						}
					}
					if(c==8){
						i=Spell[select[mode]][1+4*subfocus];
						i=i-i%10;
						i/=10;
						Spell[select[mode]][1+4*subfocus]=i;
					}
					break;
				case 4://MP
					val=c-'0';
					if(val>=0&&val<10){
						i=Spell[select[mode]][2+4*subfocus];
						if(i<100){
							i*=10;
							i+=val;
							Spell[select[mode]][2+4*subfocus]=i;
						}
					}
					if(c==8){
						i=Spell[select[mode]][2+4*subfocus];
						i=i-i%10;
						i/=10;
						Spell[select[mode]][2+4*subfocus]=i;
					}
					break;
				case 5://?
					val=c-'0';
					if(val>=0&&val<10){
						i=Spell[select[mode]][3+4*subfocus];
						if(i<100){
							i*=10;
							i+=val;
							Spell[select[mode]][3+4*subfocus]=i;
						}
					}
					if(c==8){
						i=Spell[select[mode]][3+4*subfocus];
						i=i-i%10;
						i/=10;
						Spell[select[mode]][3+4*subfocus]=i;
					}
					break;

			}