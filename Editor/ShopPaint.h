			Rectangle(memdc,140,10+16*(select[mode]%32),140+70,10+16*(select[mode]%32)+16);

			for(i=0;i<12;i++){
				sprintf(out,TownName[i]);
				if(i==6){
					TextOut(memdc,20,i*32+26,out,strlen(out));
				} else {
					TextOut(memdc,20,i*32+10,out,strlen(out));
				}
			}

			for(i=0;i<24;i++){
				if(i<12||i>13){
					sprintf(out,"Shop %d",i%2+1);
				} else {
					if(i==12)sprintf(out,"Shop 3");
					if(i==13)sprintf(out,"Shop 1");
				}
				TextOut(memdc,140,i*16+10,out,strlen(out));
			}


			if(select[mode]>=0&&select[mode]<30){
				k=0;
				for(i=0;i<32;i++){
					if(ShopItems[select[mode]][i]!=-1){
						sprintf(out,"%d",ShopItems[select[mode]][i]);
						if(k==subfocus&&focus==1&&cursor){
							sprintf(out,"%s|",out);
						}
						TextOut(memdc,270,26+16*k,out,strlen(out));
						if(ShopItems[select[mode]][i]!=255){
							if(ShopItems[select[mode]][i]>=128){
								sprintf(out,"(%s, Eq)",ItemName[ShopItems[select[mode]][i]%NumItems]);
							} else {
								sprintf(out,"(%s)",ItemName[ShopItems[select[mode]][i]%NumItems]);
							}
							TextOut(memdc,300,26+16*k,out,strlen(out));
						}
						SelectObject(bmpdc,dots);
						BitBlt(memdc,239,k*16+26,20,20,bmpdc,0,0,SRCCOPY);
						k++;
					}
				}
			}

			TextOut(memdc,270,10,"Items",5);
			TextOut(memdc,470,10,"Shop Type",9);
			TextOut(memdc,500,26,"Weapon",6);
			if(ShopTypes[select[mode]]==0)SelectObject(bmpdc,checkon);
			else SelectObject(bmpdc,checkoff);
			BitBlt(memdc,470,26,13,13,bmpdc,0,0,SRCCOPY);
			TextOut(memdc,500,42,"Item",4);
			if(ShopTypes[select[mode]]==1)SelectObject(bmpdc,checkon);
			else SelectObject(bmpdc,checkoff);
			BitBlt(memdc,470,42,13,13,bmpdc,0,0,SRCCOPY);

			SelectObject(bmpdc,plus);
			BitBlt(memdc,440,10,20,20,bmpdc,0,0,SRCCOPY);
			SelectObject(bmpdc,minus);
			BitBlt(memdc,440,30,20,20,bmpdc,0,0,SRCCOPY);

			if(menu==1){
				r.top=26+16*(submenu);
				r.left=239;
				r.right=709;
				r.bottom=304+16*(submenu);
				FillRect(memdc,&r,(HBRUSH)GetStockObject(WHITE_BRUSH));

				if(NumItems==128){
					TextOut(memdc,400,28+16*submenu,"Extended:",9);
					if(ShopItems[select[mode]][submenu]&0x40){
						SelectObject(bmpdc,checkon);
					} else {
						SelectObject(bmpdc,checkoff);
					}
					BitBlt(memdc,470,28+16*submenu,13,13,bmpdc,0,0,SRCCOPY);
				}

				if(ShopItems[select[mode]][submenu]%64<63)Rectangle(memdc,244+115*(ShopItems[select[mode]][submenu]%64-ShopItems[select[mode]][submenu]%16)/16,45+ShopItems[select[mode]][submenu]%16*16+16*(submenu),244+115*(ShopItems[select[mode]][submenu]%64-ShopItems[select[mode]][submenu]%16)/16+115,45+ShopItems[select[mode]][submenu]%16*16+16+16*(submenu));
				for(j=0;j<4;j++){
					for(i=0;i<16;i++){
						if(j==3&&i==15)sprintf(out,"");
						else 		
							if(NumItems==128 && (ShopItems[select[mode]][submenu] & 0x40)){
								sprintf(out,"%s",ItemName[j*16+i+64]);
							} else {
								sprintf(out,"%s",ItemName[j*16+i]);
							}
						TextOut(memdc,244+115*j,45+16*i+16*(submenu),out,strlen(out));
					}
				}
			}
