			if(menu){
				switch(menu){
					case 1:
						if(p.x>=455&&p.x<=570&&p.y>=41&&p.y<=41+15*32){
							i=(p.y-41)/15;
							Monster[select[mode]][0]=i;
						}
						break;
				}
				menu=0;
				return 0;
			}


			if (p.x >= 640 && p.x <= 660 && p.y >= 225 && p.y < 245) {
				submode[16] = 7;
				subselect[16][submode[16]] = Monster[select[mode]][12];

				mode = 16;
			}

			if (p.x >= 640 && p.x <= 660 && p.y >= 245 && p.y < 265) {
				submode[16] = 1;
				subselect[16][submode[16]] = Monster[select[mode]][13];

				subselect[16][submode[16] + 64] = Monster[select[mode]][14];

				mode = 16;

			}

			if (p.x >= 640 && p.x <= 660 && p.y >= 265 && p.y < 285) {
				select[14] = Monster[select[mode]][13];
				mode = 14;
			}

			for(i=0;i<37;i++){
				if(p.x>=30&&p.x<=149&&p.y>=i*14+5&&p.y<=i*14+20){
					focus=1;
					select[mode]=i+MonsterView;
				}
			}

			for(i=37;i<73;i++){
				if(p.x>=180&&p.x<=299&&p.y>=(i-37)*14+5&&p.y<=(i-37)*14+20){
					focus=1;
					select[mode]=i+MonsterView;
				}
			}

			if(p.x>=453&&p.x<=473&&p.y>=24&&p.y<=44){
				menu=1;
			}

			if(p.x>=612&&p.x<=650&&p.y>=25&&p.y<=365){
				focus=(p.y-25)/20+2;
			}

			if(p.x>=452&&p.x<=465&&p.y>=501&&p.y<=514){
				if(AddCritical){
					if(NumMonsters==146)return 0;
					AddCritical=false;
					if(NumMonsters==73)MonsterDataOffset = 0x2751C;
				} else {
					AddCritical=true;
					MonsterDataOffset = 0x1BF320;
				}
			}

			if(NumMonsters==146){
				if(p.x>=200&&p.x<=220&&p.y>=520&&p.y<=540){
					MonsterView -= 73;
					if(MonsterView<0)MonsterView+=NumMonsters;
					select[mode]-=73;
					if(select[mode]<0)select[mode]+=NumMonsters;
				}
				if(p.x>=223&&p.x<=243&&p.y>=520&&p.y<=540){
					MonsterView += 73;
					MonsterView%=NumMonsters;
					select[mode]+=73;
					select[mode]%=NumMonsters;
				}
			}

			if(p.x>=452&&p.x<=465&&p.y>=517&&p.y<=530){
				if(NumMonsters==146){
					if(totalLength(MonsterName,73)>618){
						MessageBox(NULL,"You are over the limit for monster names. Shorten the monster names if you aren't going to use extended monsters.","Error",MB_OK);
						return false;
					}
					NumMonsters=73;

					MonsterView=0;

					if(!AddCritical){
						MonsterDataOffset = 0x2751C;
					} else {
						MonsterDataOffset = 0x1BF320;
					}

					int temp = MonsterNameOffset - ClassNamesOffset;
					ClassNamesOffset = 0x25D6C;
					ClassOffset=0x260BC;
					MonsterNameOffset = ClassNamesOffset+temp;
				} else {
					AddCritical=true;
					NumMonsters=146;
					MonsterDataOffset = 0x1BF320;

					int temp = MonsterNameOffset - ClassNamesOffset;
					ClassNamesOffset = 0x1DC000;
					ClassOffset=0x1E2000;
					MonsterNameOffset = ClassNamesOffset+temp;
				}
			}