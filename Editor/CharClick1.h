if(submode[mode]==0){
				if(menu){
					switch(menu){
						case 1:
							if(p.x>=455&&p.x<=570&&p.y>=41&&p.y<=41+15*32){
								i=(p.y-41)/15;
								Char[select[mode]][0]=i;
							}
							if (NumClasses == 64)
							if (p.x >= 570 && p.x <= 570+114 && p.y >= 41 && p.y <= 41 + 15 * 32) {
								i = (p.y - 41) / 15;
								Char[select[mode]][0] = i + 32;
							}
							break;
						case 2:
							if(p.x>=377&&p.x<=397&&p.y>=20+16*submenu&&p.y<=33+16*submenu){
								Char[select[mode]][16+submenu]^=0x80;
								return 0;
							}
							if(NumItems==128)
							if(p.x>=470&&p.x<=483&&p.y>=20+16*submenu&&p.y<=33+16*submenu){
								Char[select[mode]][16+submenu]^=0x40;
								return 0;
							}
							for(i=0;i<16;i++){
								for(j=0;j<4;j++){
									if(p.x>=307+115*j&&p.x<=421+115*j&&p.y>=36+16*i+(submenu)*16&&p.y<=51+16*i+(submenu)*16){
										if(NumItems==128)Char[select[mode]][16+submenu]&=0xC0;
										else Char[select[mode]][16+submenu]&=0x80;
										Char[select[mode]][16+submenu]|=i+j*16;

										if (Char[select[mode]][16 + submenu] == 63 || Char[select[mode]][16 + submenu] == 127 || Char[select[mode]][16 + submenu] == 191)Char[select[mode]][16 + submenu] = 255;

										menu=0;
										return 0;
									}
								}
							}
							break;
						case 3:
							for(i=0;i<16;i++){
								for(j=0;j<4;j++){
									if(p.x>=307+75*j&&p.x<=381+75*j&&p.y>=84+16*i+(submenu)*16&&p.y<=99+16*i+(submenu)*16){
										Char[select[mode]][20+submenu]=i+j*64;
										menu=0;
										return 0;
									}
								}
							}
							break;
					}
					menu=0;
					return 0;
				}

				if (p.x >= 640 && p.x <= 660 && p.y >= 425 && p.y < 445) {
					submode[16] = 0;
					subselect[16][submode[16]] = BattleSprite[select[mode]][0];

					subselect[16][submode[16] + 64] = BattleSprite[select[mode]][1];

					mode = 16;
				}

				if (p.x >= 640 && p.x <= 660 && p.y >= 445 && p.y < 465) {
					subselect[14][1] = BattleSprite[select[mode]][0];
					mode = 14;
				}

				if (select[mode] != 0) {
					if (p.x >= 740 && p.x <= 760 && p.y >= 136 && p.y < 156) {
						mode = 15;
						subselect[mode][0] = SpecialMessages[255] + select[0] - 1;
						submode[mode] = 0;
					}
					if (p.x >= 740 && p.x <= 760 && p.y >= 156 && p.y < 176) {
						mode = 15;
						subselect[mode][0] = SpecialMessages[255] + select[0] + (NumChars - 1) - 1;
						submode[mode] = 0;
					}
					if (p.x >= 740 && p.x <= 760 && p.y >= 176 && p.y < 196) {
						mode = 15;
						subselect[mode][0] = SpecialMessages[255] + select[0] + 2*(NumChars - 1) - 1;
						submode[mode] = 0;
					}
				}

				if (p.x >= 640 && p.x <= 660 && p.y >= 465 && p.y < 485) {
					submode[16] = 6;
					subselect[16][submode[16]] = CharPortrait[select[mode]];
					mode = 16;
				}

				if (p.x >= 640 && p.x <= 660 && p.y >= 485 && p.y < 505) {
					submode[16] = 7;
					subselect[16][submode[16]] = CharMapSprite[select[mode]];
					mode = 16;
				}

				if(p.x>=220&&p.x<=460&&p.y>=500&&p.y<=520){
					submode[mode]=1;
					return 0;
				}

				int q;
				q = 31;
				if (CharView + q > NumChars) q = NumChars - CharView;

				for(i=0;i<q;i++){
					if(p.x>=30&&p.x<=149&&p.y>=i*16+10&&p.y<=i*16+25){
						focus=1;
						select[mode]=i + CharView;
					}
				}

				if(p.x>=473&&p.x<=493&&p.y>=24&&p.y<=44){
					menu=1;
				}

				for(i=0;i<4;i++){
					if(p.x>=592&&p.x<=611&&p.y>=244+i*20&&p.y<=263+i*20){
						menu=2;
						submenu=i;
					}
					if (p.x >= 572 && p.x <= 591 && p.y >= 244 + i * 20 && p.y <= 263 + i * 20) {
						Char[select[mode]][16 + i] = 255;
					}
				}

				for(i=0;i<4;i++){
					if(p.x>=592&&p.x<=611&&p.y>=324+i*20&&p.y<=343+i*20){
						menu=3;
						submenu=i;
					}
					if (p.x >= 572 && p.x <= 591 && p.y >= 324 + i * 20 && p.y <= 343 + i * 20) {
						Char[select[mode]][20 + i] = 255;
					}
				}

				if (p.x >= 582 && p.x <= 620 && p.y >= 25 && p.y <= 245) {
					focus = (p.y - 25) / 20 + 2;
				}
				if (p.x >= 612 && p.x <= 650 && p.y >= 245 && p.y <= 405) {
					focus = (p.y - 25) / 20 + 2;
				}

				if(romsize>=0x200000)
				if (p.x >= 707 && p.x <= 740 && p.y >= 45 && p.y <= 65) {
					focus = 42;
				}


				for(i=0;i<6;i++){
					if(p.x>=212&&p.x<=250&&p.y>=110+70*i&&p.y<=130+70*i)focus=21+i;
					if(p.x>=342&&p.x<=380&&p.y>=110+70*i&&p.y<=130+70*i)focus=27+i;

					for(int j=0;j<4;j++){
						if(p.x>=260+30*(j%2)&&p.x<=280+30*(j%2)&&p.y>=90+70*i+30*(j/2)&&p.y<=110+70*i+30*(j/2)){
							Stats[select[mode]][i]=Stats[select[mode]][i]%64+j*64;
						}
						if(p.x>=390+30*(j%2)&&p.x<=410+30*(j%2)&&p.y>=90+70*i+30*(j/2)&&p.y<=110+70*i+30*(j/2)){
							Stats[select[mode]][i+6]=Stats[select[mode]][i+6]%64+j*64;
						}
					}
				}

				/* Battle sprite selection */
				if(p.x>=612&&p.x<=650&&p.y>=425&&p.y<=444){
					focus=40;
				}
				if (p.x >= 562 && p.x <= 590 && p.y >= 425 && p.y <= 444) {
					focus = 34;
				}

				/* Battle palette selection */
				if(p.x>=612&&p.x<=650&&p.y>=445&&p.y<=464){
					focus = 41;
				}
				if (p.x >= 562 && p.x <= 590 && p.y >= 445 && p.y <= 464) {
					focus = 35;
				}

				/* Portrait selection */
				if (p.x >= 562 && p.x <= 590 && p.y >= 465 && p.y <= 484) {
					focus = 36;
				}
				if (p.x >= 612 && p.x <= 650 && p.y >= 465 && p.y <= 484) {
					focus = 38;
				}

				/* Map sprite selection */
				if (p.x >= 612 && p.x <= 650 && p.y >= 485 && p.y <= 504) {
					focus = 39;
				}
				if (p.x >= 562 && p.x <= 590 && p.y >= 485 && p.y <= 504) {
					focus = 37;
				}

				/* Arrows */
				if (NumChars == MAX_CHARS) {
					if (p.x >= 20 && p.x <= 40 && p.y >= 520 && p.y <= 540) {
						CharView += 31;
						CharView %= 62;
						select[mode] += 31;
						select[mode] %= 62;
						if (select[mode] > NumChars - 1) select[mode] = NumChars - 1;
					}
					if (p.x >= 43 && p.x <= 63 && p.y >= 520 && p.y <= 540) {
						CharView += 31;
						CharView %= 62;
						select[mode] += 31;
						select[mode] %= 62;
						if (select[mode] > NumChars - 1) select[mode] = NumChars - 1;
					}
				}

				SelectObject(bmpdc, uparrow);
				BitBlt(memdc, 20, 520, 20, 20, bmpdc, 0, 0, SRCCOPY);
				SelectObject(bmpdc, downarrow);
				BitBlt(memdc, 43, 520, 20, 20, bmpdc, 0, 0, SRCCOPY);

				if (p.x >= 492 && p.x <= 505 && p.y >= 513 && p.y <= 526) {
					if (NumChars == MAX_CHARS) {
						NumChars = MIN_CHARS;
						CharView = 0;
						select[mode] %= 31;
					} else {
						NumChars = MAX_CHARS;
						MessageBox(NULL, "To fully enable extended characters, remember to use 'Assign Messages' in the text editor to move the HQ messages and copy the old ones.\r\n\r\nAlso note that old save states will not work after extending the number of characters!", "Note", MB_OK);

						for (int i = 29; i < 50; i++) {
							if (!Char[i][1]) {
								Char[i][1] = 1;
								Char[i][16] = 255;
								Char[i][17] = 255;
								Char[i][18] = 255;
								Char[i][19] = 255;
								Char[i][20] = 255;
								Char[i][21] = 255;
								Char[i][22] = 255;
								Char[i][23] = 255;
							}
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

	for(int j=0;j<4;j++){
		if(p.x>=90+30*(j)&&p.x<=110+30*(j)&&p.y>=30&&p.y<=50){
			subselect[mode][0]=j;
		}
	}
	for(int j=1;j<20;j++){
		if(p.x>=140&&p.x<=200&&p.y>=70+20*j&&p.y<=90+20*j){
			focus=j;
		}
	}
}