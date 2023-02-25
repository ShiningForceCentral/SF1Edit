
	SelectObject(bmpdc,minus);
	BitBlt(memdc,100,58,20,20,bmpdc,0,0,SRCCOPY);

	sprintf(out,"Tile: %d",select[mode]);
	if(focus==1&&cursor)sprintf(out,"%s|",out);
	TextOut(memdc,121,60,out,strlen(out));

	SelectObject(bmpdc,plus);
	BitBlt(memdc,191,58,20,20,bmpdc,0,0,SRCCOPY);

	TextOut(memdc,300,34,"Subtiles",8);
	TextOut(memdc,575,34,"Palette",7);
	TextOut(memdc,300,293,"Above Sprites",13);
	TextOut(memdc,575,293,"Flip X,Y",8);

	for(i=0;i<3;i++){
		for(j=0;j<3;j++){
			k = (Tiles[select[mode]][i*2+j*6]&0x07)*256;
			k += Tiles[select[mode]][i*2+j*6+1];
			k -= 0x3BE;

			//sprintf(out,"%d",Tiles[select[mode]][i*2+j*6+1]);
			//TextOut(memdc,300+i*75,50+j*75,out,strlen(out));
			//sprintf(out,"%d",Tiles[select[mode]][i*2+j*6]&0x07);
			
			sprintf(out,"%d",k);
			if(focus==2&&subfocus==j*3+i&&cursor)sprintf(out,"%s|",out);
			TextOut(memdc,300+i*75,66+j*75,out,strlen(out));

			if(k>255){
				SelectObject(bmpdc,tileset[curtiles2]);
				k-=256;
			} else SelectObject(bmpdc,tileset[curtiles]);
			x = (k%16)*8;
			y = (k-k%16)/2;
			if(Tiles[select[mode]][i*2+j*6]&0x08){
				x+=7;
				dx=-1;
			} else dx=1;
			if(Tiles[select[mode]][i*2+j*6]&0x10){
				y+=7;
				dy=-1;
			} else dy=1;
			StretchBlt(memdc,140+i*8,120+j*8,8,8,bmpdc,x,y,8*dx,8*dy,SRCCOPY);
			StretchBlt(memdc,55+i*64,170+j*64,64,64,bmpdc,x,y,8*dx,8*dy,SRCCOPY);

			
			sprintf(out,"%d",(Tiles[select[mode]][i*2+j*6]&0x60)/0x20);
			if(focus==3&&subfocus==j*3+i&&cursor)sprintf(out,"%s|",out);
			TextOut(memdc,575+i*75,66+j*75,out,strlen(out));

			if(Tiles[select[mode]][i*2+j*6]&0x80)SelectObject(bmpdc,checkon);
			else SelectObject(bmpdc,checkoff);
			BitBlt(memdc,300+i*75,325+j*75,13,13,bmpdc,0,0,SRCCOPY);

			if(Tiles[select[mode]][i*2+j*6]&0x08)SelectObject(bmpdc,checkon);
			else SelectObject(bmpdc,checkoff);
			BitBlt(memdc,575+i*75,325+j*75,13,13,bmpdc,0,0,SRCCOPY);
			if(Tiles[select[mode]][i*2+j*6]&0x10)SelectObject(bmpdc,checkon);
			else SelectObject(bmpdc,checkoff);
			BitBlt(memdc,595+i*75,325+j*75,13,13,bmpdc,0,0,SRCCOPY);

		}
	}

