if(submode[mode]==0){
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
			
			Rectangle(memdc,73+190*((select[mode]-ItemView)/32),10+16*((select[mode]-ItemView)%32),73+190*((select[mode]-ItemView)/32)+124,10+16*((select[mode]-ItemView)%32)+16);

			for(i=0;i<32;i++){
				if(i==(select[mode]-ItemView)&&focus==1&&cursor){
					sprintf(out,"%s|",ItemName[i+ItemView]);
					TextOut(memdc,73,i*16+10,out,strlen(out));
				} else {
					TextOut(memdc,73,i*16+10,ItemName[i+ItemView],strlen(ItemName[i+ItemView]));
				}
				sprintf(out,"%d",i+ItemView);
				TextOut(memdc,50,i*16+10,out,strlen(out));
			}
			for(i=32;i<63;i++){
				if(i==(select[mode]-ItemView)&&focus==1&&cursor){
					sprintf(out,"%s|",ItemName[i+ItemView]);
					TextOut(memdc,263,(i-32)*16+10,out,strlen(out));
				} else {
					TextOut(memdc,263,(i-32)*16+10,ItemName[i+ItemView],strlen(ItemName[i+ItemView]));
				}
				sprintf(out,"%d",i+ItemView);
				TextOut(memdc,240,(i-32)*16+10,out,strlen(out));
			}

			/*for(i=0;i<16;i++){
				sprintf(out,"%d",Item[select[mode]][i]);
				TextOut(memdc,360,i*16+10,out,strlen(out));
			}*/

			TextOut(memdc,390,10,"Equippable",10);

			for(i=0;i<32;i++){
				TextOut(memdc,420,i*15+30,Classes[i+subselect[mode][0]],strlen(Classes[i + subselect[mode][0]]));
				if(Item[select[mode]][3 + subselect[mode][0]/2-i/8]&(int)pow(2.0,i%8))SelectObject(bmpdc,checkon);
				else SelectObject(bmpdc,checkoff);
				BitBlt(memdc,397,i*15+31,13,13,bmpdc,0,0,SRCCOPY);
			}

			if (ExtendEquip) {
				SelectObject(bmpdc, uparrow);
				BitBlt(memdc, 405, 520, 20, 20, bmpdc, 0, 0, SRCCOPY);
				SelectObject(bmpdc, downarrow);
				BitBlt(memdc, 428, 520, 20, 20, bmpdc, 0, 0, SRCCOPY);
			}

			TextOut(memdc,500,25,"Attribute:",10);
			i = Item[select[mode]][6];
			if(i==255)i=7;
			TextOut(memdc,612,25,Atts[i],strlen(Atts[i]));

			SelectObject(bmpdc,plus);
			BitBlt(memdc,650,23,20,20,bmpdc,0,0,SRCCOPY);
			SelectObject(bmpdc,minus);
			BitBlt(memdc,675,23,20,20,bmpdc,0,0,SRCCOPY);

			TextOut(memdc,500,40,"Attribute Bonus:",16);
			if(focus==2&&cursor){
				sprintf(out,"%d|",Item[select[mode]][7]);
				TextOut(memdc,612,40,out,strlen(out));
			} else {
				sprintf(out,"%d",Item[select[mode]][7]);
				TextOut(memdc,612,40,out,strlen(out));
			}

			TextOut(memdc,500,55,"Price:",6);

			if(focus==3&&cursor){
				sprintf(out,"%d|",Item[select[mode]][14]*256+Item[select[mode]][15]);
				TextOut(memdc,612,55,out,strlen(out));
			} else {
				sprintf(out,"%d",Item[select[mode]][14]*256+Item[select[mode]][15]);
				TextOut(memdc,612,55,out,strlen(out));
			}

			TextOut(memdc,500,70,"Cursed:",7);
			if(Item[select[mode]][5]&1)SelectObject(bmpdc,checkon);
			else SelectObject(bmpdc,checkoff);
			BitBlt(memdc,612,72,13,13,bmpdc,0,0,SRCCOPY);

			SelectObject(bmpdc,dots);
			BitBlt(memdc,478,84,20,20,bmpdc,0,0,SRCCOPY);

			TextOut(memdc,500,85,"Use Range:",10);

			if(focus==4&&cursor){
				sprintf(out,"%d|",Item[select[mode]][8]);
				TextOut(memdc,612,85,out,strlen(out));
			} else {
				sprintf(out,"%d",Item[select[mode]][8]);
				TextOut(memdc,612,85,out,strlen(out));
			}
			i = Item[select[mode]][8];
			if(i<16||i>63)sprintf(out,"(None)");
			if(i>=16&&i<64)sprintf(out,"(%s)",Ranges[i-16]);
			TextOut(memdc,650,85,out,strlen(out));

			TextOut(memdc,500,100,"Use Effect:",11);

			if(focus==5&&cursor){
				sprintf(out,"%d|",Item[select[mode]][9]);
				TextOut(memdc,612,100,out,strlen(out));
			} else {
				sprintf(out,"%d",Item[select[mode]][9]);
				TextOut(memdc,612,100,out,strlen(out));
			}

			SelectObject(bmpdc,dots);
			BitBlt(memdc,478,114,20,20,bmpdc,0,0,SRCCOPY);

			TextOut(memdc,500,115,"Range:",6);

			if(focus==6&&cursor){
				sprintf(out,"%d|",Item[select[mode]][12]);
				TextOut(memdc,612,115,out,strlen(out));
			} else {
				sprintf(out,"%d",Item[select[mode]][12]);
				TextOut(memdc,612,115,out,strlen(out));
			}
			i = Item[select[mode]][12];
			if(i<16||i>63)sprintf(out,"(None)");
			if(i>=16&&i<64)sprintf(out,"(%s)",Ranges[i-16]);
			TextOut(memdc,650,115,out,strlen(out));

			TextOut(memdc,500,130,"Attack Effect:",14);

			if(focus==9&&cursor){
				sprintf(out,"%d|",Item[select[mode]][13]);
				TextOut(memdc,612,130,out,strlen(out));
			} else {
				sprintf(out,"%d",Item[select[mode]][13]);
				TextOut(memdc,612,130,out,strlen(out));
			}

			if(ItemView==0){
				TextOut(memdc,500,145,"Sell to Deals:",14);
			} else {
				TextOut(memdc,500,145,"Broken:",7);
			}
			if(Item[select[mode]][4]&128)SelectObject(bmpdc,checkon);
			else SelectObject(bmpdc,checkoff);
			BitBlt(memdc,612,147,13,13,bmpdc,0,0,SRCCOPY);


			TextOut(memdc,500,160,"Chance to Crack:",16);
			if(Item[select[mode]][4]&64)SelectObject(bmpdc,checkon);
			else SelectObject(bmpdc,checkoff);
			BitBlt(memdc,612,162,13,13,bmpdc,0,0,SRCCOPY);

			TextOut(memdc,500,175,"Cannot Unequip:",15);
			if(Item[select[mode]][4]&32)SelectObject(bmpdc,checkon);
			else SelectObject(bmpdc,checkoff);
			BitBlt(memdc,612,177,13,13,bmpdc,0,0,SRCCOPY);

			TextOut(memdc,500,190,"Lose After Use:",15);
			if(Item[select[mode]][4]&16)SelectObject(bmpdc,checkon);
			else SelectObject(bmpdc,checkoff);
			BitBlt(memdc,612,192,13,13,bmpdc,0,0,SRCCOPY);

			TextOut(memdc,635,145,"Can't Drop:",11);
			if(Item[select[mode]][4]&8)SelectObject(bmpdc,checkon);
			else SelectObject(bmpdc,checkoff);
			BitBlt(memdc,747,147,13,13,bmpdc,0,0,SRCCOPY);

			TextOut(memdc,635,160,"Usable:",7);
			if(Item[select[mode]][4]&4)SelectObject(bmpdc,checkon);
			else SelectObject(bmpdc,checkoff);
			BitBlt(memdc,747,162,13,13,bmpdc,0,0,SRCCOPY);

			TextOut(memdc,635,175,"Ring:",5);
			if(Item[select[mode]][4]&2)SelectObject(bmpdc,checkon);
			else SelectObject(bmpdc,checkoff);
			BitBlt(memdc,747,177,13,13,bmpdc,0,0,SRCCOPY);

			TextOut(memdc,635,190,"Weapon:",7);
			if(Item[select[mode]][4]&1)SelectObject(bmpdc,checkon);
			else SelectObject(bmpdc,checkoff);
			BitBlt(memdc,747,192,13,13,bmpdc,0,0,SRCCOPY);

			Rectangle(memdc,500,205,624,222);
			TextOut(memdc,542,205,"Outfits",7);

			if(AddArmor){
				TextOut(memdc,635,205,"Armor:",6);
				if(Item[select[mode]][5]&2)SelectObject(bmpdc,checkon);
				else SelectObject(bmpdc,checkoff);
				BitBlt(memdc,747,207,13,13,bmpdc,0,0,SRCCOPY);
			}


			TextOut(memdc,500,242,"Extend Drop Table:",18);
			if(ExtendDrops)SelectObject(bmpdc,checkon);
			else SelectObject(bmpdc,checkoff);
			BitBlt(memdc,628,244,13,13,bmpdc,0,0,SRCCOPY);

			/*TextOut(memdc,500,206,"Regenerate:",11);
			if(Item[select[mode]][10]==8)SelectObject(bmpdc,checkon);
			else SelectObject(bmpdc,checkoff);
			BitBlt(memdc,612,208,13,13,bmpdc,0,0,SRCCOPY);*/

			if(ExtendDrops){

				TextOut(memdc,500,222,"Dropped by Enemies:",19);
				if(ItemDrop[select[mode]])SelectObject(bmpdc,checkon);
				else SelectObject(bmpdc,checkoff);
				BitBlt(memdc,650,224,13,13,bmpdc,0,0,SRCCOPY);

				TextOut(memdc,648,242,"Offset:",7);
				sprintf(out,"%X",ItemDropOffset);
				if(focus==10&&cursor){
					sprintf(out,"%s|",out);
				}
				TextOut(memdc,693,242,out,strlen(out));
			}

			TextOut(memdc,500,268,"Item Type:",10);

			sprintf(out,"%d",ItemType[select[mode]]);
			if(focus==11&&cursor){
				sprintf(out,"%s|",out);
			}
			TextOut(memdc,580,268,out,strlen(out));

			TextOut(memdc,610,268,"Weapon Sprite:",14);

			sprintf(out,"%d",ItemWS[select[mode]]);
			if(focus==12&&cursor){
				sprintf(out,"%s|",out);
			}
			TextOut(memdc,720,268,out,strlen(out));


			TextOut(memdc,500,288,"?:",2);

			sprintf(out,"%d",Item[select[mode]][10]);
			if(focus==13&&cursor){
				sprintf(out,"%s|",out);
			}
			TextOut(memdc,580,288,out,strlen(out));

			TextOut(memdc,610,288,"?:",2);

			sprintf(out,"%d",Item[select[mode]][11]);
			if(focus==14&&cursor){
				sprintf(out,"%s|",out);
			}
			TextOut(memdc,720,288,out,strlen(out));


			/*
			TextOut(memdc,500,268,"Item Name Offset:",17);

			sprintf(out,"%X",ItemNameOffset);
			if(focus==7&&cursor){
				sprintf(out,"%s|",out);
			}
			TextOut(memdc,620,268,out,strlen(out));

			TextOut(memdc,500,284,"Item Data Offset:",17);

			sprintf(out,"%X",ItemOffset);
			if(focus==8&&cursor){
				sprintf(out,"%s|",out);
			}
			TextOut(memdc,620,284,out,strlen(out));
			*/


			for(i=0;i<16;i++){
				for(j=0;j<24;j++){
					for(int dx=0;dx<8;dx++){
						for(int dy=0;dy<8;dy++){
							SetPixel(memdc,575+8*i+dx,310+8*j+dy,RGB(IconPalette[ItemImages[select[mode]][j*16+i]][0],IconPalette[ItemImages[select[mode]][j*16+i]][1],IconPalette[ItemImages[select[mode]][j*16+i]][2]));
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

			for(k=0;k<63;k++){
				for(i=0;i<16;i++){
					for(j=0;j<24;j++){
						SetPixel(memdc,(k/32)*190+30+i-k%2*16,(k%32)*16+j+6,RGB(IconPalette[ItemImages[k+ItemView][j*16+i]][0],IconPalette[ItemImages[k+ItemView][j*16+i]][1],IconPalette[ItemImages[k+ItemView][j*16+i]][2]));
					}
				}
			}
			
			Rectangle(memdc,651,101,783,116);
			TextOut(memdc,658,100,"Out of Battle Uses",18);

			if(NumItems==128){
				SelectObject(bmpdc,uparrow);
				BitBlt(memdc,200,520,20,20,bmpdc,0,0,SRCCOPY);
				SelectObject(bmpdc,downarrow);
				BitBlt(memdc,223,520,20,20,bmpdc,0,0,SRCCOPY);
				SelectObject(bmpdc,checkon);
			} else SelectObject(bmpdc,checkoff);


			TextOut(memdc,280,510,"Extend Items",12);	
			BitBlt(memdc,260,511,13,13,bmpdc,0,0,SRCCOPY);

			switch(menu){
				case 1://range
					r.top=130;
					r.left=479;
					r.right=625;
					r.bottom=487;
					FillRect(memdc,&r,(HBRUSH)GetStockObject(WHITE_BRUSH));
					for(i=0;i<19;i++){
						sprintf(out,"%s",RangeTypes[i]);
						TextOut(memdc,481,132+16*i,out,strlen(out));
					}
					break;
				case 2://use range
					r.top=100;
					r.left=479;
					r.right=625;
					r.bottom=457;
					FillRect(memdc,&r,(HBRUSH)GetStockObject(WHITE_BRUSH));
					for(i=0;i<19;i++){
						sprintf(out,"%s",RangeTypes[i]);
						TextOut(memdc,481,102+16*i,out,strlen(out));
					}
					break;
			}
}

if(submode[mode]==1){
	TextOut(memdc,40,15,"Type",4);
	TextOut(memdc,200,15,"Item #",6);

	for(int i=0;i<NUM_MAPUSES;i++){
		TextOut(memdc,40,40+20*i,MapUseLabels[i],strlen(MapUseLabels[i]));
		sprintf(out,"%d",MapItem[i]);

		if(cursor&&focus==i+1)sprintf(out,"%s|",out);

		TextOut(memdc,200,40+20*i,out,strlen(out));

		if(MapItem[i]<NumItems){
			sprintf(out,"(%s)",ItemName[MapItem[i]]);
			TextOut(memdc,230,40+20*i,out,strlen(out));
		}
	}
	
	Rectangle(memdc,620,524,790,544);
	TextOut(memdc,690,526,"Back",4);
}

if(submode[mode]==2){

	SelectObject(bmpdc,plus);
	BitBlt(memdc,10,13,20,20,bmpdc,0,0,SRCCOPY);

	TextOut(memdc,40,15,"Item #",6);
	TextOut(memdc,220,15,"Character",9);
	TextOut(memdc,400,15,"Map Sprite",10);
	if(BattleOutfits)TextOut(memdc,580,15,"Battle Sprite",13);

	for(int i=0;i<NumOutfits;i++){
		SelectObject(bmpdc,deleteicon);
		BitBlt(memdc,10,40+24*i,20,20,bmpdc,0,0,SRCCOPY);

		sprintf(out,"%d",ItemOutfits[i][1]);
		if(cursor&&focus==i+1)sprintf(out,"%s|",out);
		TextOut(memdc,40,40+24*i,out,strlen(out));

		sprintf(out,"(%s)",ItemName[ItemOutfits[i][1]]);
		TextOut(memdc,66,40+24*i,out,strlen(out));

		sprintf(out,"%d",ItemOutfits[i][0]);
		if(cursor&&focus==i+65)sprintf(out,"%s|",out);
		TextOut(memdc,220,40+24*i,out,strlen(out));

		sprintf(out,"(%s)",CharName[ItemOutfits[i][0]]);
		TextOut(memdc,244,40+24*i,out,strlen(out));

		sprintf(out,"%d",ItemOutfits[i][2]);
		if(cursor&&focus==i+129)sprintf(out,"%s|",out);
		TextOut(memdc,400,40+24*i,out,strlen(out));

		width=MSSize[ItemOutfits[i][2]][0][0];
		height=MSSize[ItemOutfits[i][2]][0][1];

		for(x=0;x<width;x++){
			for(y=0;y<height;y++){
				k = MapSprites[ItemOutfits[i][2]][0][x+y*width];
				if(k<0)k=0;

				SetPixel(memdc,x+430,y+36+24*i,RGB(FMSPalette[k][0],FMSPalette[k][1],FMSPalette[k][2]));
			}
		}

		if(BattleOutfits){
			sprintf(out,"%d",ItemOutfits[i][3]);
			if(cursor&&focus==i+193)sprintf(out,"%s|",out);
			TextOut(memdc,580,40+24*i,out,strlen(out));
		}
	}
	
	Rectangle(memdc,620,524,790,544);
	TextOut(memdc,690,526,"Back",4);

	TextOut(memdc,500,526,"Battle Outfits",14);
	if(BattleOutfits)SelectObject(bmpdc,checkon);
	else SelectObject(bmpdc,checkoff);
	BitBlt(memdc,480,528,13,13,bmpdc,0,0,SRCCOPY);
}