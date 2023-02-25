			c=wParam;
			if(submode[mode]==0){
				if(focus==32&&TextLoaded){
					val=c-'0';
					if(val>=0&&val<10){
						i=subselect[mode][0];
						if(i<1000){
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
					subselect[mode][0]%=NUM_TEXT;
				}
				if (focus == 33 && TextLoaded) {
					val = c - '0';
					if (val >= 0 && val<10) {
						i = NUM_TEXT;
						if (i<1000) {
							i *= 10;
							i += val;
							NUM_TEXT = i;
						}
					}
					if (c == 8) {
						i = NUM_TEXT;
						i = i - i % 10;
						i /= 10;
						NUM_TEXT = i;
					}
					if (NUM_TEXT > 4096)NUM_TEXT = 4096;
					if (subselect[mode][0] >= NUM_TEXT)subselect[mode][0] = 0;
				}
				if(focus>=0&&focus<32&&TextLoaded&&subfocus>-1&&!menu){
					if((c>='a'&&c<='z')||(c>='A'&&c<='Z')||(c>='0'&&c<='9')||c==' '||c=='_'||c=='-'||c=='.'||c==','||c=='!'||c=='('||c==')'||c=='#'||c=='%'||c=='&'||c=='+'||c=='/'||c==':'||c=='?'||c=='\''){
						if(strlen(Text[(subselect[mode][0]+focus)%NUM_TEXT])<1024){

							sprintf(out,"");
							if(subfocus>0)strncpy(out,Text[(subselect[mode][0]+focus)% NUM_TEXT],subfocus);
							out[subfocus]=0;
							sprintf(out,"%s%c%s",out,c,Text[(subselect[mode][0]+focus)% NUM_TEXT]+subfocus);

							sprintf(Text[(subselect[mode][0]+focus)% NUM_TEXT],"%s",out);

							subfocus++;
						}
					}

					if (c == '[' || c == ']') {
						menu = 2;
						lastfocus = focus;
						lastsubfocus = subfocus;
					}

					if(c=='~'){
						if(strlen(Text[(subselect[mode][0]+focus)% NUM_TEXT])<1024){

							sprintf(out,"");
							if(subfocus>0)strncpy(out,Text[(subselect[mode][0]+focus)% NUM_TEXT],subfocus);
							out[subfocus]=0;
							sprintf(out,"%s%c%s",out,0xC3,Text[(subselect[mode][0]+focus)% NUM_TEXT]+subfocus);

							sprintf(Text[(subselect[mode][0]+focus)% NUM_TEXT],"%s",out);

							subfocus++;
						}
					}

					if(c==8&&strlen(Text[(subselect[mode][0]+focus)% NUM_TEXT])>0&&subfocus>0){
						sprintf(out,"");
						i=subfocus-1;
						j=1;
						if(Text[(subselect[mode][0]+focus)% NUM_TEXT][i]==']'){
							while(Text[(subselect[mode][0]+focus)% NUM_TEXT][i]!='['){
								i--;
								j++;
							}
						}
						strncpy(out,Text[(subselect[mode][0]+focus)% NUM_TEXT],i);
						out[i]=0;
						sprintf(out,"%s%s",out,Text[(subselect[mode][0]+focus)% NUM_TEXT]+subfocus);

						sprintf(Text[(subselect[mode][0]+focus)% NUM_TEXT],"%s",out);

						subfocus-=j;;
					}
				}
				if(TextLoaded&&menu==1){
					if((c>='a'&&c<='z')||(c>='A'&&c<='Z')||(c>='0'&&c<='9')||c==' ' || c == ' ' || c == '_' || c == '-' || c == '.' || c == ',' || c == '!' || c == '(' || c == ')' || c == '#' || c == '%' || c == '&' || c == '+' || c == '/' || c == ':' || c == '?' || c == '\''){
						if(strlen(searchtext)<20){
							sprintf(searchtext,"%s%c",searchtext,c);
						} else searchtext[19]=c;
					}
					if(c==8&&strlen(searchtext)>0){
						searchtext[strlen(searchtext)-1]=0;
					}
				}
			}

			if(submode[mode]==1){
				val=c-'0';
				if(focus>0){
					if(val>=0&&val<10){
						i=SpecialMessages[focus-1];
						if(i<1000){
							i*=10;
							i+=val;
							SpecialMessages[focus-1]=i;
						}
					}
					if(c==8){
						i=SpecialMessages[focus-1];
						i=i-i%10;
						i/=10;
						SpecialMessages[focus-1]=i;
					}
				}
			}