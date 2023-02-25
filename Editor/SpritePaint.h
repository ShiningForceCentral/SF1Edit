
	SelectObject(bmpdc,minus);
	BitBlt(memdc,5,8,20,20,bmpdc,0,0,SRCCOPY);

	sprintf(out,"Map: %d",select[mode]);
	if(focus==1&&cursor)sprintf(out,"%s|",out);
	TextOut(memdc,26,10,out,strlen(out));

	SelectObject(bmpdc,plus);
	BitBlt(memdc,96,8,20,20,bmpdc,0,0,SRCCOPY);

	for(i=0;i<NumSprites[select[mode]];i++){
		sprintf(out,"Sprite %d",i+1);
		TextOut(memdc,120,i*16+26,out,strlen(out));
		for(j=0;j<6;j++){
			if(focus==2+i*6+j&&cursor){
				sprintf(out,"%d|",Sprites[select[mode]][i][j]);
			} else {
				sprintf(out,"%d",Sprites[select[mode]][i][j]);
			}
			TextOut(memdc,240+80*j,i*16+26,out,strlen(out));
		}
	}

	TextOut(memdc,240,10,"X",1);
	TextOut(memdc,320,10,"Y",1);
	TextOut(memdc,400,10,"Dir/Anim",8);
	TextOut(memdc,480,10,"Gfx",3);
	TextOut(memdc,560,10,"Movement",8);
	TextOut(memdc,640,10,"Dialog",6);
