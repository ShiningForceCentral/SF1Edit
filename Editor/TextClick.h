if(submode[mode]==0){

	if(p.x>=620&&p.x<=790&&p.y>=524&&p.y<=544){
		submode[mode]=1;
		focus=0;
		subfocus=-1;
		menu=0;
		return true;
	}

	if (TextLoaded&&menu == 1) {

		if (p.x >= 140 && p.x <= 160 && p.y >= 522 && p.y<542) {
			Find();
			return true;
		}

		if (p.x >= 160 && p.x <= 360 && p.y >= 522 && p.y<542) {

		} else {
			menu = 0;
		}
	}

	if(TextLoaded&&!menu){
		if(p.x>=50&&p.x<=70&&p.y>=522&&p.y<=542){
			subselect[mode][0]+=32;
			if(subselect[mode][0]>NUM_TEXT-1)subselect[mode][0]-=NUM_TEXT;
			subfocus=strlen(Text[(subselect[mode][0]+focus)%NUM_TEXT]);
		}
		if(p.x>=80&&p.x<=100&&p.y>=522&&p.y<=542){
			subselect[mode][0]-=32;
			if(subselect[mode][0]<0)subselect[mode][0]+=NUM_TEXT;
			subfocus=strlen(Text[(subselect[mode][0]+focus)%NUM_TEXT]);
		}

		if(p.x>=140&&p.x<=160&&p.y>=522&&p.y<542){
			if(menu!=1)menu=1;
			else Find();
			subfocus=-1;
			return true;
		}
		if (p.x >= 160 && p.x <= 360 && p.y >= 522 && p.y<542) {
			if (menu != 1)menu = 1;
			return true;
		}
		if(p.x>=110&&p.x<=130&&p.y>=522&&p.y<542){
			menu=2;
			return true;
		}
		for(i=0;i<32;i++){
			if(p.x>=50&&p.x<=800&&p.y>=i*16+6&&p.y<i*16+22){
				if (focus != i) 
					subfocus = -1;
				else subfocus = lastsubfocus;
					//subfocus=strlen(Text[(subselect[mode][0]+i)%NUM_TEXT]);

				if (subfocus > -1) {
					if (subfocus > 0)strncpy(out, Text[(subselect[mode][0] + i) % NUM_TEXT], subfocus);
					out[subfocus] = 0;
					if (cursor)
						sprintf(out, "%s|%s", out, Text[(subselect[mode][0] + i) % NUM_TEXT] + subfocus);
					else
						sprintf(out, "%s %s", out, Text[(subselect[mode][0] + i) % NUM_TEXT] + subfocus);

					strncpy(temp, out, subfocus + 1);
					temp[subfocus + 1] = 0;
				} else {
					temp[0] = 0;
					sprintf(out, "%s", Text[(subselect[mode][0] + i) % NUM_TEXT]);
				}

				j = 0;


				SetRect(&r, 0, 0, 0, 0);
				DrawText(memdc, temp, strlen(temp), &r, DT_CALCRECT);
				while (r.right>650) {
					j++;

					strncpy(temp, out + j, subfocus + 1 - j);

					

					temp[subfocus + 1 - j] = 0;
					SetRect(&r, 0, 0, 0, 0);
					DrawText(memdc, temp, strlen(temp), &r, DT_CALCRECT);
				}
				sprintf(out, out + j);
				int j2 = j;

				j = -1;
				do{
					if (out[j] == '[')while (out[j] != ']')j++;
					j++;
					
					strncpy(temp, out, j + 1);
					temp[j + 1] = 0;
					SetRect(&r, 0, 0, 0, 0);
					DrawText(memdc, temp, strlen(temp), &r, DT_CALCRECT);

				} while (r.right+50 < p.x && j < strlen(Text[(subselect[mode][0] + i) % NUM_TEXT]));

				focus = i;
				subfocus = j+j2;

				//TextOut(memdc,50,i*16+10,Text[(subselect[mode][0]+i)%NUM_TEXT],strlen(Text[(subselect[mode][0]+i)%NUM_TEXT]));
			}
		}

		if(p.x>=450&&p.x<=520&&p.y>=522&&p.y<542){
			focus=32;
		}
		if (p.x >= 532 && p.x <= 602 && p.y >= 522 && p.y<542) {
			focus = 33;
		}
	}

	if(!TextLoaded&&strlen(file)){
		if(p.x>=50&&p.x<=176&&p.y>=30&&p.y<=52){
			LoadText(file,true);
		}
	}

	if(TextLoaded&&menu==2){
		if(p.x>220||p.x<110||p.y<302||p.y>522){
			menu=0;
			focus=lastfocus;
			subfocus=lastsubfocus;
		}
		if(lastsubfocus>-1&&lastfocus>-1)
		for(i=0;i<11;i++){
			if(p.x>= 110 &&p.x<=220&&p.y>=i*16+304&&p.y<i*16+320){
				sprintf(out,"");
				if(lastsubfocus>0)strncpy(out,Text[(subselect[mode][0]+lastfocus)%NUM_TEXT],lastsubfocus);
				out[lastsubfocus]=0;
				switch(i){
				case 0:
					sprintf(out,"%s%s%s",out,"[Line]",Text[(subselect[mode][0]+lastfocus)%NUM_TEXT]+lastsubfocus);
					lastsubfocus+=6;
					break;
				case 1:
					sprintf(out,"%s%s%s",out,"[Hero]",Text[(subselect[mode][0]+lastfocus)%NUM_TEXT]+lastsubfocus);
					lastsubfocus+=6;
					break;
				case 2:
					sprintf(out,"%s%s%s",out,"[Delay1]",Text[(subselect[mode][0]+lastfocus)%NUM_TEXT]+lastsubfocus);
					lastsubfocus+=8;
					break;
				case 3:
					sprintf(out,"%s%s%s",out,"[Delay2]",Text[(subselect[mode][0]+lastfocus)%NUM_TEXT]+lastsubfocus);
					lastsubfocus+=8;
					break;
				case 4:
					sprintf(out,"%s%s%s",out,"[Wait2]",Text[(subselect[mode][0]+lastfocus)%NUM_TEXT]+lastsubfocus);
					lastsubfocus+=7;
					break;
				case 5:
					sprintf(out,"%s%s%s",out,"[Num]",Text[(subselect[mode][0]+lastfocus)%NUM_TEXT]+lastsubfocus);
					lastsubfocus+=5;
					break;
				case 6:
					sprintf(out,"%s%s%s",out,"[Name]",Text[(subselect[mode][0]+lastfocus)%NUM_TEXT]+lastsubfocus);
					lastsubfocus+=6;
					break;
				case 7:
					sprintf(out,"%s%s%s",out,"[Item]",Text[(subselect[mode][0]+lastfocus)%NUM_TEXT]+lastsubfocus);
					lastsubfocus+=6;
					break;
				case 8:
					sprintf(out,"%s%s%s",out,"[Spell]",Text[(subselect[mode][0]+lastfocus)%NUM_TEXT]+lastsubfocus);
					lastsubfocus+=6;
					break;
				case 9:
					sprintf(out,"%s%s%s",out,"[Class]",Text[(subselect[mode][0]+lastfocus)%NUM_TEXT]+lastsubfocus);
					lastsubfocus+=6;
					break;
				case 10:
					sprintf(out,"%s%s%s",out,"[Dict]",Text[(subselect[mode][0]+lastfocus)%NUM_TEXT]+lastsubfocus);
					lastsubfocus+=6;
					break;
				}
				sprintf(Text[(subselect[mode][0]+lastfocus)%NUM_TEXT],"%s",out);
			}
		}
	}
}

if(submode[mode]==1){

	if(p.x>=620&&p.x<=790&&p.y>=524&&p.y<=544){
		submode[mode]=0;
		focus=0;
		return true;
	}

	for(int i=0;i<NUM_SPECIAL;i++){
		if (i == 3 && !ShowCrit)continue;
		if(p.x>=200&&p.x<=270&&p.y>=40+20*i&&p.y<=60+20*i){
			focus=i+1;
		}



		if(p.x>=280&&p.x<=400&&p.y>=40+20*i&&p.y<=60+20*i){
			sprintf(Text[SpecialMessages[i]],"%s",MessagesDefaults[i]);
			submode[mode]=0;
			focus=0;
			subselect[mode][0] = SpecialMessages[i];
			return true;
		}

	}

	if (p.x >= 200 && p.x <= 270 && p.y >= 40 + 20 * (NUM_SPECIAL + 1) && p.y <= 60 + 20 * (NUM_SPECIAL + 1)) {
		focus = 256;
	}

	if(NumChars==MAX_CHARS)
	if (p.x >= 280 && p.x <= 400 && p.y >= 40 + 20 * (NUM_SPECIAL + 1) &&p.y <= 60 + 20 * (NUM_SPECIAL + 1)) {

		if (SpecialMessages[255] + 49*3 > 4096) {
			MessageBox(NULL, "Starting number is too high, need room for 150 messages.", "Error", MB_OK);
			return true;
		}

		if (SpecialMessages[255] >= 261 && SpecialMessages[255] - 261 < 29 * 3) {
			MessageBox(NULL, "Message ranges can't overlap. Change the message number to where you want to copy the messages to.", "Error", MB_OK);
			return true;
		}

		if (SpecialMessages[255] < 261 && 261 - SpecialMessages[255] < 49 * 3) {
			MessageBox(NULL, "Message ranges can't overlap. Change the message number to where you want to copy the messages to.", "Error", MB_OK);
			return true;
		}

		if (MessageBox(NULL,"This will overwrite a large number of messages (150) starting from the chosen number. Continue?","Warning",MB_YESNO) == IDYES) {
			for (int i = 0;i < 29;i++) {
				sprintf(Text[SpecialMessages[255] + i], Text[261 + i]);
				sprintf(Text[SpecialMessages[255] + 49 + i], Text[290 + i]);
				sprintf(Text[SpecialMessages[255] + 49 * 2 + i], Text[319 + i]);
			}
			for (int i = 29; i < 49; i++) {
				sprintf(Text[SpecialMessages[255] + i], "0");
				sprintf(Text[SpecialMessages[255] + 49 + i], "0");
				sprintf(Text[SpecialMessages[255] + 49 * 2 + i], "0");
			}
		}
		return true;
	}

}