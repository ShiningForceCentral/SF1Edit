			if(Pencil){
				SelectObject(bmpdc,pencilon);
				BitBlt(memdc,488,325,20,20,bmpdc,0,0,SRCCOPY);
				SelectObject(bmpdc,eraser);
				BitBlt(memdc,488,350,20,20,bmpdc,0,0,SRCCOPY);
			} else {
				SelectObject(bmpdc,pencil);
				BitBlt(memdc,488,325,20,20,bmpdc,0,0,SRCCOPY);
				SelectObject(bmpdc,eraseron);
				BitBlt(memdc,488,350,20,20,bmpdc,0,0,SRCCOPY);
			}

			switch(size){
			case 1:
				SelectObject(bmpdc,oneon);
				BitBlt(memdc,488,400,20,20,bmpdc,0,0,SRCCOPY);
				SelectObject(bmpdc,two);
				BitBlt(memdc,488,425,20,20,bmpdc,0,0,SRCCOPY);
				SelectObject(bmpdc,four);
				BitBlt(memdc,488,450,20,20,bmpdc,0,0,SRCCOPY);
				break;
			case 2:
				SelectObject(bmpdc,one);
				BitBlt(memdc,488,400,20,20,bmpdc,0,0,SRCCOPY);
				SelectObject(bmpdc,twoon);
				BitBlt(memdc,488,425,20,20,bmpdc,0,0,SRCCOPY);
				SelectObject(bmpdc,four);
				BitBlt(memdc,488,450,20,20,bmpdc,0,0,SRCCOPY);
				break;
			case 4:
				SelectObject(bmpdc,one);
				BitBlt(memdc,488,400,20,20,bmpdc,0,0,SRCCOPY);
				SelectObject(bmpdc,two);
				BitBlt(memdc,488,425,20,20,bmpdc,0,0,SRCCOPY);
				SelectObject(bmpdc,fouron);
				BitBlt(memdc,488,450,20,20,bmpdc,0,0,SRCCOPY);
				break;
			}
			
			Rectangle(memdc,50+160*(select[mode]/32),10+16*(select[mode]%32),50+160*(select[mode]/32)+120,10+16*(select[mode]%32)+16);

			for(i=0;i<16+16*ExpandSpells;i++){
				if(i==select[mode]&&focus==1&&cursor){
					sprintf(out,"%s|",SpellName[i]);
					TextOut(memdc,50,i*16+10,out,strlen(out));
				} else {
					TextOut(memdc,50,i*16+10,SpellName[i],strlen(SpellName[i]));
				}
			}

			TextOut(memdc,400,9,"Level 1:",8);
			TextOut(memdc,600,9,"Level 2:",8);
			TextOut(memdc,400,150,"Level 3:",8);
			TextOut(memdc,600,150,"Level 4:",8);

			for(i=0;i<4;i++){

				SelectObject(bmpdc,dots);
				BitBlt(memdc,414+(i%2)*200,44+(i/2)*141-16,20,20,bmpdc,0,0,SRCCOPY);

				TextOut(memdc,435+(i%2)*200,45+(i/2)*141-16,"Range:",6);

				if(focus==2&&subfocus==i&&cursor){
					sprintf(out,"%d|",Spell[select[mode]][0+4*i]);
					TextOut(memdc,485+(i%2)*200,45+(i/2)*141-16,out,strlen(out));
				} else {
					sprintf(out,"%d",Spell[select[mode]][0+4*i]);
					TextOut(memdc,485+(i%2)*200,45+(i/2)*141-16,out,strlen(out));
				}
				j = Spell[select[mode]][0+4*i];
				if(j<16||j>63)sprintf(out,"(None)");
				if(j>=16&&j<64)sprintf(out,"(%s)",Ranges[j-16]);
				TextOut(memdc,510+(i%2)*200,45+(i/2)*141-16,out,strlen(out));

				TextOut(memdc,435+(i%2)*200,61+(i/2)*141-16,"Effect:",7);
				if(focus==3&&subfocus==i&&cursor){
					sprintf(out,"%d|",Spell[select[mode]][1+4*i]);
					TextOut(memdc,485+(i%2)*200,61+(i/2)*141-16,out,strlen(out));
				} else {
					sprintf(out,"%d",Spell[select[mode]][1+4*i]);
					TextOut(memdc,485+(i%2)*200,61+(i/2)*141-16,out,strlen(out));
				}

				TextOut(memdc,435+(i%2)*200,77+(i/2)*141-16,"MP:",3);
				if(focus==4&&subfocus==i&&cursor){
					sprintf(out,"%d|",Spell[select[mode]][2+4*i]);
					TextOut(memdc,485+(i%2)*200,77+(i/2)*141-16,out,strlen(out));
				} else {
					sprintf(out,"%d",Spell[select[mode]][2+4*i]);
					TextOut(memdc,485+(i%2)*200,77+(i/2)*141-16,out,strlen(out));
				}

				sprintf(out,"%d",Spell[select[mode]][3+4*i]);
				if(focus==5&&subfocus==i&&cursor)sprintf(out,"%s|",out);
				TextOut(memdc,485+(i%2)*200,93+(i/2)*141-16,out,strlen(out));
			}

			TextOut(memdc,400,270,"AI Type:",8);

			switch(SpellTargeting[select[mode]]+0x2409C+2*select[mode]){
				case 0x24378:
					TextOut(memdc,485,270,"Class,Distance,Health",21);
					break;
				case 0x24386:
					TextOut(memdc,485,270,"Class",5);
					break;
				case 0x244CA:
					TextOut(memdc,485,270,"Distance",8);
					break;
				case 0x244F0:
					TextOut(memdc,485,270,"High Health",11);
					break;
				case 0x24516:
					TextOut(memdc,485,270,"Low Health",10);
					break;
				case 0x2453E:
					TextOut(memdc,485,270,"Not Quickened",13);
					break;
				case 0x24544:
					TextOut(memdc,485,270,"Not Boosted",11);
					break;
				case 0x2454A:
					TextOut(memdc,485,270,"Not Shielded",12);
					break;
				case 0x24550:
					TextOut(memdc,485,270,"Not Slowed",10);
					break;
				case 0x24556:
					TextOut(memdc,485,270,"Not Dispelled",13);
					break;
				case 0x2455C:
					TextOut(memdc,485,270,"Not Muddled",11);
					break;
			}
			

			for(i=0;i<16;i++){
				for(j=0;j<24;j++){
					for(int dx=0;dx<8;dx++){
						for(int dy=0;dy<8;dy++){
							SetPixel(memdc,575+8*i+dx,310+8*j+dy,RGB(IconPalette[SpellImages[select[mode]][j*16+i]][0],IconPalette[SpellImages[select[mode]][j*16+i]][1],IconPalette[SpellImages[select[mode]][j*16+i]][2]));
						}
					}
				}
				for(int dx=0;dx<18;dx++){
					for(int dy=0;dy<18;dy++){
						SetPixel(memdc,490+18*i+dx,514+dy,RGB(IconPalette[i][0],IconPalette[i][1],IconPalette[i][2]));
					}
				}
			}

			for(i=0;i<18;i++){
				for(int dy=0;dy<18;dy++){
					SetPixel(memdc,489+i,475+dy,RGB(IconPalette[color][0],IconPalette[color][1],IconPalette[color][2]));
				}
			}

			for(k=0;k<16+16*ExpandSpells;k++){
				for(i=0;i<16;i++){
					for(j=0;j<24;j++){
						SetPixel(memdc,(k/32)*160+30+i-k%2*16,(k%32)*16+j+6,RGB(IconPalette[SpellImages[k][j*16+i]][0],IconPalette[SpellImages[k][j*16+i]][1],IconPalette[SpellImages[k][j*16+i]][2]));
					}
				}
			}

			TextOut(memdc,200,10,"Extend Spells:",14);
			if(ExpandSpells)SelectObject(bmpdc,checkon);
			else SelectObject(bmpdc,checkoff);
			BitBlt(memdc,300,11,13,13,bmpdc,0,0,SRCCOPY);
			if(ExpandSpells){
				TextOut(memdc,200,26,"Names Offset:",13);
				sprintf(out,"%X",SpellNameOffset);
				if(focus==6&&cursor)sprintf(out,"%s|",out);
				TextOut(memdc,295,26,out,strlen(out));
				TextOut(memdc,200,42,"Data Offset:",12);
				sprintf(out,"%X",SpellOffset);
				if(focus==6&&cursor)sprintf(out,"%s|",out);
				TextOut(memdc,295,42,out,strlen(out));
				TextOut(memdc,200,58,"Images Offset:",14);
				sprintf(out,"%X",SpellImagesOffset);
				if(focus==6&&cursor)sprintf(out,"%s|",out);
				TextOut(memdc,295,58,out,strlen(out));
			}

			switch(menu){
				case 1://range
				case 2://range
				case 3://range
				case 4://range
					r.top=45+(menu-1)/2*125;
					r.left=435+(menu-1)%2*200;
					r.right=580+(menu-1)%2*200;
					r.bottom=385+(menu-1)/2*125;
					FillRect(memdc,&r,(HBRUSH)GetStockObject(WHITE_BRUSH));
					for(i=0;i<18;i++){
						sprintf(out,"%s",RangeTypes[i]);
						TextOut(memdc,438+(menu-1)%2*200,45+(menu-1)/2*125+16*i,out,strlen(out));
					}
					break;
				case 5://AI
					r.top=268;
					r.left=483;
					r.right=675;
					r.bottom=492;
					FillRect(memdc,&r,(HBRUSH)GetStockObject(WHITE_BRUSH));

					//TextOut(memdc,438+(menu-1)%2*200,45+(menu-1)/2*125+16*i,out,strlen(out));

					TextOut(memdc,485,270,"Class,Distance,Health",21);

					TextOut(memdc,485,290,"Class",5);

					TextOut(memdc,485,310,"Distance",8);

					TextOut(memdc,485,330,"High Health",11);

					TextOut(memdc,485,350,"Low Health",10);

					TextOut(memdc,485,370,"Not Quickened",13);

					TextOut(memdc,485,390,"Not Boosted",11);

					TextOut(memdc,485,410,"Not Shielded",12);

					TextOut(memdc,485,430,"Not Slowed",10);

					TextOut(memdc,485,450,"Not Dispelled",13);

					TextOut(memdc,485,470,"Not Muddled",11);


					break;
			}
