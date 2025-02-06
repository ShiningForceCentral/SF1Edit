if(submode[mode]==0){
			if(menu){
				switch(menu){
					case 1:
						if(p.x>=479&&p.x<=624&&p.y>=130&&p.y<=486){
							i=(p.y-130)/16;
							Item[select[mode]][12]=RangeVals[i]+16;
						}
						break;
					case 2:
						if(p.x>=479&&p.x<=624&&p.y>=100&&p.y<=456){
							i=(p.y-100)/16;
							Item[select[mode]][8]=RangeVals[i]+16;
						}
						break;
				}
				menu=0;
				return 0;
			}

			if(p.x>=651&&p.x<=783&&p.y>=101&&p.y<=116){
				submode[mode]=1;
				focus=0;
				return true;
			}

			if(p.x>=500&&p.x<=624&&p.y>=205&&p.y<=222){
				submode[mode]=2;
				focus=0;
				return true;
			}


			if (ExtendEquip) {
				if (p.x >= 405 && p.x <= 448 && p.y >= 520 && p.y <= 540) {
					subselect[mode][0] = 32 - subselect[mode][0];
				}
			}


			for(i=0;i<32;i++){
				if(p.x>=397&&p.x<=410&&p.y>=i*15+31&&p.y<=i*15+44){
					if(Item[select[mode]][3 + subselect[mode][0] / 2 -i/8]&(int)pow(2.0,i%8)){
						Item[select[mode]][3 + subselect[mode][0] / 2 -i/8]-=(int)pow(2.0,i%8);
					} else {
						Item[select[mode]][3 + subselect[mode][0] / 2 -i/8]+=(int)pow(2.0,i%8);
					}
				}
			}
			for(i=0;i<32;i++){
				if(p.x>=30&&p.x<=209&&p.y>=i*16+10&&p.y<=i*16+25){
					focus=1;
					select[mode]=i+ItemView;
				}
			}
			for(i=32;i<63;i++){
				if(p.x>=210&&p.x<=379&&p.y>=(i-32)*16+10&&p.y<=(i-32)*16+25){
					focus=1;
					select[mode]=i+ItemView;
				}
			}

			if(p.x>=675&&p.x<=695&&p.y>=23&&p.y<=43){
				Item[select[mode]][6]++;
				if(Item[select[mode]][6]==7)Item[select[mode]][6]=255;
			}
			if(p.x>=700&&p.x<=725&&p.y>=23&&p.y<=43){
				Item[select[mode]][6]--;
				if(Item[select[mode]][6]==254)Item[select[mode]][6]=6;
			}

			if(p.x>=612&&p.x<=625&&p.y>=72&&p.y<=85){
				Item[select[mode]][5]^=0x01;
			}

			if(p.x>=612&&p.x<=625&&p.y>=147&&p.y<=160){
				if(Item[select[mode]][4]&128){
					Item[select[mode]][4]&=127;
				} else {
					Item[select[mode]][4]|=128;
				}
			}

			if(p.x>=612&&p.x<=625&&p.y>=162&&p.y<=175){
				if(Item[select[mode]][4]&64){
					Item[select[mode]][4]&=191;
				} else {
					Item[select[mode]][4]|=64;
				}
			}

			if(p.x>=612&&p.x<=625&&p.y>=177&&p.y<=190){
				if(Item[select[mode]][4]&32){
					Item[select[mode]][4]&=223;
				} else {
					Item[select[mode]][4]|=32;
				}
			}

			if(p.x>=612&&p.x<=625&&p.y>=192&&p.y<=205){
				if(Item[select[mode]][4]&16){
					Item[select[mode]][4]&=239;
				} else {
					Item[select[mode]][4]|=16;
				}
			}

			/*if(p.x>=612&&p.x<=625&&p.y>=206&&p.y<=222){
				if(Item[select[mode]][10]==8){
					Item[select[mode]][10]=255;
					Item[select[mode]][11]=0;
				} else {
					Item[select[mode]][10]=8;
					Item[select[mode]][11]=5;
				}
			}*/

			if(p.x>=737&&p.x<=760&&p.y>=147&&p.y<=160){
				if(Item[select[mode]][4]&8){
					Item[select[mode]][4]&=247;
				} else {
					Item[select[mode]][4]|=8;
				}
			}

			if(p.x>=737&&p.x<=760&&p.y>=162&&p.y<=175){
				if(Item[select[mode]][4]&4){
					Item[select[mode]][4]&=251;
				} else {
					Item[select[mode]][4]|=4;
				}
			}

			if(p.x>=737&&p.x<=760&&p.y>=177&&p.y<=190){
				if(Item[select[mode]][4]&2){
					Item[select[mode]][4]&=253;
				} else {
					Item[select[mode]][4]|=2;
				}
			}

			if(p.x>=737&&p.x<=760&&p.y>=192&&p.y<=205){
				if(Item[select[mode]][4]&1){
					Item[select[mode]][4]&=254;
				} else {
					Item[select[mode]][4]|=1;
				}
			}

			if(AddArmor){
				if(p.x>=737&&p.x<=760&&p.y>=205&&p.y<=218){
					Item[select[mode]][5]^=2;
				}
			}


			if(p.x>=488&&p.x<=508&&p.y>=325&&p.y<=345){
				Pencil=true;
			}
			if(p.x>=488&&p.x<=508&&p.y>=350&&p.y<=370){
				Pencil=false;
			}
			if(p.x>=488&&p.x<=508&&p.y>=400&&p.y<=420){
				size=1;
			}
			if(p.x>=488&&p.x<=508&&p.y>=425&&p.y<=445){
				size=2;
			}
			if(p.x>=488&&p.x<=508&&p.y>=450&&p.y<=470){
				size=4;
			}

			for(i=0;i<16;i++){
				if(p.x>=490+18*i&&p.x<508+18*i&&p.y>=514&&p.y<=532){
					color=i;
				}
			}

			for(i=0;i<16;i++){
				for(j=0;j<24;j++){
					if(p.x>=575+8*i&&p.x<583+8*i&&p.y>=310+8*j&&p.y<318+8*j){
						for(int dx=0;dx<size&&i+dx<16;dx++){
							for(int dy=0;dy<size&&j+dy<24;dy++){
								if(Pencil)ItemImages[select[mode]][(j+dy)*16+i+dx]=color;
								else ItemImages[select[mode]][(j+dy)*16+i+dx]=0;
							}
						}
					}
				}
			}


			if(p.x>=628&&p.x<=641&&p.y>=242&&p.y<=257){
				ExtendDrops=!ExtendDrops;
				if(!ExtendDrops){
					ItemDropOffset=0x2303A;
				} else {
					ItemDropOffset=0x1826A0;
				}
			}

			if(NumItems==128){
				if(p.x>=200&&p.x<=220&&p.y>=520&&p.y<=540){
					ItemView -= 64;
					ItemView%=NumItems;
					select[mode]-=64;
					if(select[mode]<0)select[mode]+=NumItems;
				}
				if(p.x>=223&&p.x<=243&&p.y>=520&&p.y<=540){
					ItemView += 64;
					ItemView%=NumItems;
					select[mode]+=64;
					select[mode]%=NumItems;
				}
			}

			if(p.x>=260&&p.x<=276&&p.y>=511&&p.y<=524){
				if(NumItems==128){
					if(totalLength(ItemName,63)>663){
						MessageBox(NULL,"You are over the limit for item names. Shorten the item names if you aren't going to use extended items.","Error",MB_OK);
						return false;
					}
					NumItems=64;

					ItemView=0;
					ItemNameOffset = 0x25640;
					ItemOffset = 0x25916;
					ItemIconOffset = 0xCFCEA;
					ItemTypeOffset = 0x25D2C;

				} else {
					NumItems=128;
					ItemNameOffset = 0x1AC800;
					ItemOffset = 0x1AD000;
					ItemIconOffset = 0x1B7000;
					ItemTypeOffset = 0x1AD800;
					ItemWSOffset = 0x1AD880;
					sprintf(ItemName[64],"DO NOT USE");
				}
			}

			if(p.x>=478&&p.x<=498&&p.y>=120&&p.y<=130){
				menu=1;
			}

			if(p.x>=478&&p.x<=498&&p.y>=90&&p.y<=100){
				menu=2;
			}
			
			if(p.x>=612&&p.x<=675&&p.y>=45&&p.y<=60){
				focus=2;
			}

			if(p.x>=612&&p.x<=675&&p.y>=60&&p.y<=75){
				focus=3;
			}

			if(p.x>=612&&p.x<=675&&p.y>=90&&p.y<=105){
				focus=4;
			}

			if(p.x>=612&&p.x<=675&&p.y>=105&&p.y<=120){
				focus=5;
			}

			if(p.x>=612&&p.x<=675&&p.y>=120&&p.y<=135){
				focus=6;
			}

			if(p.x>=612&&p.x<=675&&p.y>=135&&p.y<=150){
				focus=9;
			}
/*
			if(p.x>=620&&p.x<=675&&p.y>=150&&p.y<=165){
				focus=7;
			}

			if(p.x>=620&&p.x<=675&&p.y>=165&&p.y<=180){
				focus=8;
			}
*/
			if(ExtendDrops&&p.x>=693&&p.x<=760&&p.y>=242&&p.y<=258){
				focus=10;
			}

			if(p.x>=580&&p.x<=610&&p.y>=268&&p.y<=288){
				focus=11;
			}

			if(p.x>=720&&p.x<=750&&p.y>=268&&p.y<=288){
				focus=12;
			}

			if(p.x>=580&&p.x<=610&&p.y>=288&&p.y<=308){
				focus=13;
			}

			if(p.x>=720&&p.x<=750&&p.y>=288&&p.y<=308){
				focus=14;
			}

			if(ExtendDrops&&p.x>=650&&p.x<=663&&p.y>=222&&p.y<=235){
				ItemDrop[select[mode]]=!ItemDrop[select[mode]];
			}
}

if(submode[mode]==1){
	if(p.x>=620&&p.x<=790&&p.y>=524&&p.y<=544){
		submode[mode]=0;
		focus=0;
		return true;
	}

	for(int i=0;i<NUM_MAPUSES;i++){
		if(p.x>=200&&p.x<=270&&p.y>=40+20*i&&p.y<=60+20*i){
			focus=i+1;
		}
	}
}

if(submode[mode]==2){
	if(p.x>=620&&p.x<=790&&p.y>=524&&p.y<=544){
		submode[mode]=0;
		focus=0;
		return true;
	}

	if(p.x>=480&&p.x<=500&&p.y>=528&&p.y<=548){
		BattleOutfits = !BattleOutfits;
	}

	if(p.x>=10&&p.x<=30&&p.y>=13&&p.y<=33){
		if(NumOutfits<20){
			ItemOutfits[NumOutfits][0]=0;
			ItemOutfits[NumOutfits][1]=0;
			ItemOutfits[NumOutfits][2]=0;
			ItemOutfits[NumOutfits][3]=0;
			NumOutfits++;
		}
		return true;
	}

	for(int i=0;i<NumOutfits;i++){
		if(p.x>=40&&p.x<=110&&p.y>=40+24*i&&p.y<=60+24*i){
			focus=i+1;
		}
		if(p.x>=220&&p.x<=290&&p.y>=40+24*i&&p.y<=60+24*i){
			focus=i+65;
		}
		if(p.x>=400&&p.x<=470&&p.y>=40+24*i&&p.y<=60+24*i){
			focus=i+129;
		}

		if(p.x>=580&&p.x<=650&&p.y>=40+24*i&&p.y<=60+24*i){
			focus=i+193;
		}

		if(p.x>=10&&p.x<=30&&p.y>=40+24*i&&p.y<=60+24*i){
			for(j=i;j<NumOutfits-1;j++){
				ItemOutfits[j][0] = ItemOutfits[j+1][0];
				ItemOutfits[j][1] = ItemOutfits[j+1][1];
				ItemOutfits[j][2] = ItemOutfits[j+1][2];
				ItemOutfits[j][3] = ItemOutfits[j+1][3];
			}
			NumOutfits--;
		}
	}
}