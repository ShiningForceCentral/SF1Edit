if(submode[mode]==0){
	if(TextLoaded&&!menu)
	switch(wParam){
		case VK_LEFT:
			if(subfocus>0)subfocus--;

			if (Text[(subselect[mode][0] + focus) % NUM_TEXT][subfocus] == ']') {
				while (Text[(subselect[mode][0] + focus) % NUM_TEXT][subfocus] != '[')subfocus--;
			}

			break;
		case VK_RIGHT:
			if(subfocus>-1&&subfocus<strlen(Text[(subselect[mode][0]+focus)%NUM_TEXT]))subfocus++;

			if (Text[(subselect[mode][0] + focus) % NUM_TEXT][subfocus-1] == '[') {
				while (Text[(subselect[mode][0] + focus) % NUM_TEXT][subfocus-1] != ']')subfocus++;
			}
			break;
		case VK_HOME:
			if(subfocus>-1)subfocus=0;
			break;
		case VK_END:
			if(subfocus>-1)subfocus=strlen(Text[(subselect[mode][0]+focus)%NUM_TEXT]);
			break;
		case VK_UP:
			if(focus>0){
				focus--;
				subfocus=strlen(Text[(subselect[mode][0]+focus)%NUM_TEXT]);
			}
			break;
		case VK_DOWN:
			if(focus<31){
				focus++;
				subfocus=strlen(Text[(subselect[mode][0]+focus)%NUM_TEXT]);
			}
			break;
		case VK_DELETE:
			if(focus>=0&&focus<32&&TextLoaded&&subfocus>-1&&subfocus<strlen(Text[(subselect[mode][0]+focus)%NUM_TEXT])){
				sprintf(out,"");
				if(subfocus>0)strncpy(out,Text[(subselect[mode][0]+focus)%NUM_TEXT],subfocus);
				out[subfocus]=0;
				i=1;
				if(Text[(subselect[mode][0]+focus)%NUM_TEXT][subfocus]=='['){
					while(Text[(subselect[mode][0]+focus)%NUM_TEXT][subfocus+i]!=']')i++;
					i++;
				}
				sprintf(out,"%s%s",out,Text[(subselect[mode][0]+focus)%NUM_TEXT]+subfocus+i);

				sprintf(Text[(subselect[mode][0]+focus)%NUM_TEXT],"%s",out);
			}
			break;
		case VK_NEXT:
			subselect[mode][0]+=32;
			if(subselect[mode][0]>NUM_TEXT-1)subselect[mode][0]-=NUM_TEXT;
			subfocus=strlen(Text[(subselect[mode][0]+focus)%NUM_TEXT]);
			break;
		case VK_PRIOR:
			subselect[mode][0]-=32;
			if(subselect[mode][0]<0)subselect[mode][0]+=NUM_TEXT;
			subfocus=strlen(Text[(subselect[mode][0]+focus)%NUM_TEXT]);
			break;
		case VK_F3:
			Find();
			break;
	}
	if(TextLoaded&&menu==1)
	switch(wParam){
		case VK_ESCAPE:
			menu=0;
			break;
		case VK_RETURN:
			Find();
			break;
		case VK_F3:
			Find();
			break;
	}
	if(TextLoaded&&menu==2)
	switch(wParam){
		case VK_ESCAPE:
		case VK_RETURN:
			menu=0;
			focus=lastfocus;
			subfocus=lastsubfocus;
			break;
	}
}

if(submode[mode]==1){
	switch(wParam){
		case VK_ESCAPE:
			focus=0;
			submode[mode]=0;
			break;
	}
}