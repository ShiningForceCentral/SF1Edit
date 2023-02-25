			x=8;
			y=12;
			SelectObject(bmpdc,left);
			BitBlt(memdc,0,0,29,37,bmpdc,0,0,SRCCOPY);
			StretchBlt(memdc,793,0,-29,37,bmpdc,0,0,29,37,SRCCOPY);
			SelectObject(bmpdc,left2);
			BitBlt(memdc,21,88,29,344,bmpdc,0,0,SRCCOPY);
			StretchBlt(memdc,306,88,29,344,bmpdc,29,0,-29,344,SRCCOPY);
			BitBlt(memdc,391,88,29,344,bmpdc,0,0,SRCCOPY);
			StretchBlt(memdc,740,88,29,344,bmpdc,29,0,-29,344,SRCCOPY);
			SelectObject(bmpdc,mid);
			StretchBlt(memdc,29,0,742,37,bmpdc,0,0,14,37,SRCCOPY);
			StretchBlt(memdc,50,88,256,37,bmpdc,0,0,14,37,SRCCOPY);
			StretchBlt(memdc,50,395,256,37,bmpdc,0,0,14,37,SRCCOPY);
			StretchBlt(memdc,420,88,320,37,bmpdc,0,0,14,37,SRCCOPY);
			StretchBlt(memdc,420,395,320,37,bmpdc,0,0,14,37,SRCCOPY);
			for(i=0;i<80;i++){
				for(j=1;j<32;j++){
					for(k=0;k<8;k++){
						l=Font[i][j]/pow(2.0,k);
						l%=2;
						if(l){
							SetPixel(memdc,x+8-k+8*((j-1)%2),y+(j-1)/2,RGB(255,255,255));
							SetPixel(tmpdc,7+(i%8)*16-k+8*((j-1)%2),(i/8)*16+(j-1)/2,RGB(255,255,255));
						} else {
							SetPixel(memdc,x+8-k+8*((j-1)%2),y+(j-1)/2,RGB(0,36,132));
							SetPixel(tmpdc,7+(i%8)*16-k+8*((j-1)%2),(i/8)*16+(j-1)/2,RGB(0,36,132));
						}
						if(8-k+8*((j-1)%2)==Font[i][0]&&showlen){
							SetPixel(tmpdc,7+(i%8)*16-k+8*((j-1)%2),(i/8)*16+(j-1)/2,RGB(255,0,0));
						}
					}
				}
				x+=Font[i][0];
			}
			StretchBlt(memdc,50,100,256,320,tmpdc,0,0,16*8,16*10,SRCCOPY);
			StretchBlt(memdc,420,100,320,320,tmpdc,16*(select[mode]%8),16*(select[mode]/8),16,16,SRCCOPY);
			for(x=0;x<32;x++){
				SetPixel(memdc,50+(select[mode]%8)*32+x,100+(select[mode]/8)*32,RGB(255,0,0));
				SetPixel(memdc,50+(select[mode]%8)*32+x,100+(select[mode]/8+1)*32-1,RGB(255,0,0));
			}
			for(x=0;x<32;x++){
				SetPixel(memdc,50+(select[mode]%8)*32,100+(select[mode]/8)*32+x,RGB(255,0,0));
				SetPixel(memdc,50+(select[mode]%8+1)*32-1,100+(select[mode]/8)*32+x,RGB(255,0,0));
			}
			sprintf(out,"Character width: %d",Font[select[mode]][0]);
			if(showlen)SelectObject(bmpdc,checkon);
			else SelectObject(bmpdc,checkoff);
			BitBlt(memdc,410,441,13,13,bmpdc,0,0,SRCCOPY);
			TextOut(memdc,440,440,out,strlen(out));

			if(Pencil){
				SelectObject(bmpdc,pencilon);
				BitBlt(memdc,352,150,20,20,bmpdc,0,0,SRCCOPY);
				SelectObject(bmpdc,eraser);
				BitBlt(memdc,352,175,20,20,bmpdc,0,0,SRCCOPY);
			} else {
				SelectObject(bmpdc,pencil);
				BitBlt(memdc,352,150,20,20,bmpdc,0,0,SRCCOPY);
				SelectObject(bmpdc,eraseron);
				BitBlt(memdc,352,175,20,20,bmpdc,0,0,SRCCOPY);
			}

			switch(size){
			case 1:
				SelectObject(bmpdc,oneon);
				BitBlt(memdc,352,225,20,20,bmpdc,0,0,SRCCOPY);
				SelectObject(bmpdc,two);
				BitBlt(memdc,352,250,20,20,bmpdc,0,0,SRCCOPY);
				SelectObject(bmpdc,four);
				BitBlt(memdc,352,275,20,20,bmpdc,0,0,SRCCOPY);
				break;
			case 2:
				SelectObject(bmpdc,one);
				BitBlt(memdc,352,225,20,20,bmpdc,0,0,SRCCOPY);
				SelectObject(bmpdc,twoon);
				BitBlt(memdc,352,250,20,20,bmpdc,0,0,SRCCOPY);
				SelectObject(bmpdc,four);
				BitBlt(memdc,352,275,20,20,bmpdc,0,0,SRCCOPY);
				break;
			case 4:
				SelectObject(bmpdc,one);
				BitBlt(memdc,352,225,20,20,bmpdc,0,0,SRCCOPY);
				SelectObject(bmpdc,two);
				BitBlt(memdc,352,250,20,20,bmpdc,0,0,SRCCOPY);
				SelectObject(bmpdc,fouron);
				BitBlt(memdc,352,275,20,20,bmpdc,0,0,SRCCOPY);
				break;
			}

			SelectObject(bmpdc,plus);
			BitBlt(memdc,352,325,20,20,bmpdc,0,0,SRCCOPY);
			SelectObject(bmpdc,minus);
			BitBlt(memdc,352,350,20,20,bmpdc,0,0,SRCCOPY);