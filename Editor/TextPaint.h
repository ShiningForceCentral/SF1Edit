if(submode[mode]==0){
	if(!TextLoaded){
		if(strlen(file)){
			Rectangle(memdc,50,30,176,52);
			TextOut(memdc,55,33,"Decompress Text",15);
		} else {
			TextOut(memdc,55,33,"Load a ROM first.",17);
		}
	} else {
		for(i=0;i<32 && i<NUM_TEXT;i++){

			if (focus == i) {
				HBRUSH tb = (HBRUSH)SelectObject(memdc, CreateSolidBrush(RGB(170, 170, 170)));

				Rectangle(memdc, 0, i * 16 + 6, maxx, i * 16 + 22);

				DeleteObject(SelectObject(memdc, tb));
			} else 
				if (i % 2) {
					HPEN tp = (HPEN)SelectObject(memdc, GetStockObject(NULL_PEN));
					HBRUSH tb = (HBRUSH)SelectObject(memdc, CreateSolidBrush(RGB(140, 140, 140)));

					Rectangle(memdc, 0, i * 16 + 6, maxx, i * 16 + 22);

					SelectObject(memdc, tp);
					DeleteObject(SelectObject(memdc, tb));
				}

			if(focus==i&&subfocus>-1){
				sprintf(out,"");
				if(subfocus>0)strncpy(out,Text[(subselect[mode][0]+i)%NUM_TEXT],subfocus);
				out[subfocus]=0;
				if(cursor)
					sprintf(out,"%s|%s",out,Text[(subselect[mode][0]+i)%NUM_TEXT]+subfocus);
				else
					sprintf(out,"%s %s",out,Text[(subselect[mode][0]+i)%NUM_TEXT]+subfocus);
				j=0;
				strncpy(temp,out,subfocus+1);
				temp[subfocus+1]=0;
				SetRect(&r,0,0,0,0);
				DrawText(memdc,temp,strlen(temp),&r,DT_CALCRECT);
				while(r.right>650){
					j++;
					strncpy(temp,out+j,subfocus+1-j);
					temp[subfocus+1-j]=0;
					SetRect(&r,0,0,0,0);
					DrawText(memdc,temp,strlen(temp),&r,DT_CALCRECT);
				}
				sprintf(out,out+j);
				TextOutHighlight(memdc,50,i*16+6,out,strlen(out),'[',']',RGB(0,0,0),RGB(225, 225, 225));
			} else {
				TextOutHighlight(memdc,50,i*16+6,Text[(subselect[mode][0]+i)%NUM_TEXT],strlen(Text[(subselect[mode][0]+i)%NUM_TEXT]), '[', ']', RGB(0, 0, 0), RGB(225, 225, 225));
			}

			sprintf(out, "%d", (subselect[mode][0] + i) % NUM_TEXT);
			TextOut(memdc, 4, i * 16 + 6, out, strlen(out));

			

		}

		SelectObject(bmpdc, downarrow);
		BitBlt(memdc,50, 522,20,20,bmpdc,0,0,SRCCOPY);

		SelectObject(bmpdc, uparrow);
		BitBlt(memdc,80, 522,20,20,bmpdc,0,0,SRCCOPY);

		SelectObject(bmpdc,special);
		BitBlt(memdc,110, 522,20,20,bmpdc,0,0,SRCCOPY);

		SelectObject(bmpdc, search);
		BitBlt(memdc, 140, 522, 20, 20, bmpdc, 0, 0, SRCCOPY);


		r.top = 522;
		r.left = 160;
		r.right = 360;
		r.bottom = 542;
		FillRect(memdc, &r, (HBRUSH)GetStockObject(WHITE_BRUSH));

		//TextOut(memdc, 40, 72, "Search", 6);

		if (menu == 1 && cursor) {
			sprintf(out, "%s|", searchtext);
			TextOut(memdc, 162, 522, out, strlen(out));
		}
		else {
			TextOut(memdc, 162, 522, searchtext, strlen(searchtext));
		}


		TextOut(memdc, 370, 522, "Goto Line:", 10);

		r.top = 522;
		r.left = 450;
		r.right = 520;
		r.bottom = 542;
		FillRect(memdc, &r, (HBRUSH)GetStockObject(WHITE_BRUSH));

		if(focus<32){
			sprintf(out,"%d",(subselect[mode][0]+focus) % NUM_TEXT);
		} else {
			sprintf(out,"%d",subselect[mode][0]);
			if(cursor&&focus==32)sprintf(out,"%s|",out);
		}

		TextOut(memdc,452,522,out,strlen(out));


		TextOut(memdc, 523, 522, "/", 1);

		r.top = 522;
		r.left = 532;
		r.right = 602;
		r.bottom = 542;
		FillRect(memdc, &r, (HBRUSH)GetStockObject(WHITE_BRUSH));


		sprintf(out, "%d", NUM_TEXT);
		if (cursor&&focus == 33)sprintf(out, "%s|", out);

		TextOut(memdc, 534, 522, out, strlen(out));

	}

	Rectangle(memdc,620,524,790,544);
	TextOut(memdc,648,526,"Assign Messages",15);

	if(menu==2){
		r.top=302;
		r.left=110;
		r.right=220;
		r.bottom=522;
		FillRect(memdc,&r,(HBRUSH)GetStockObject(WHITE_BRUSH));
		TextOut(memdc,113,304,"[Line]",6);
		TextOut(memdc,113,304+16*1,"[Hero]",6);
		TextOut(memdc,113,304+16*2,"[Delay1]",8);
		TextOut(memdc,113,304+16*3,"[Delay2]",8);
		TextOut(memdc,113,304+16*4,"[Wait2]",7);
		TextOut(memdc,113,304+16*5,"[Num]",5);
		TextOut(memdc,113,304+16*6,"[Name]",6);
		TextOut(memdc,113,304+16*7,"[Item]",6);
		TextOut(memdc,113,304+16*8,"[Spell]",7);
		TextOut(memdc,113,304+16*9,"[Class]",7);
		TextOut(memdc,113,304+16*10,"[Dict]",6);

	}
}

if(submode[mode]==1){
	TextOut(memdc,40,15,"Name",4);
	TextOut(memdc,200,15,"Message #",9);

	for(int i=0;i<NUM_SPECIAL;i++){
		if (i == 3 && !ShowCrit)continue;
		TextOut(memdc,40,40+20*i,MessagesLabels[i],strlen(MessagesLabels[i]));
		sprintf(out,"%d",SpecialMessages[i]);

		if(cursor&&focus==1+i)sprintf(out,"%s|",out);

		TextOut(memdc,200,40+20*i,out,strlen(out));

		Rectangle(memdc,280,40+20*i,400,58+20*i);
		TextOut(memdc,283,40+20*i,"Default Message",15);
	}

	if (NumChars == MAX_CHARS) {
		TextOut(memdc, 40, 40 + 20 * (NUM_SPECIAL+1), "HQ Messages", 11);
		sprintf(out, "%d", SpecialMessages[255]);

		if (cursor&&focus == 256)sprintf(out, "%s|", out);

		TextOut(memdc, 200, 40 + 20 * (NUM_SPECIAL + 1), out, strlen(out));

		Rectangle(memdc, 280, 40 + 20 * (NUM_SPECIAL + 1), 400, 58 + 20 * (NUM_SPECIAL + 1));
		TextOut(memdc, 287, 40 + 20 * (NUM_SPECIAL + 1), "Copy Messages", 13);
	}

	
	Rectangle(memdc,620,524,790,544);
	TextOut(memdc,690,526,"Back",4);
}