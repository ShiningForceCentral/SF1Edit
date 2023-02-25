			BattleDrag=-1;
			if(submode[mode]==0){
				if(menu==1){
					l=submenu;
					if(l>14)l=14;
					if(p.x>=354&&p.x<=374&&p.y>=12+16*l&&p.y<=25+16*l){
						Battle[select[mode]][submenu][1]^=0x80;
						return 0;
					}
					for(i=0;i<16;i++){
						for(j=0;j<4;j++){
							if(p.x>=284+115*j&&p.x<=398+115*j&&p.y>=28+16*i+(l)*16&&p.y<=43+16*i+(l)*16){
								if(j==3&&i==15){
									Battle[select[mode]][submenu][1]=255;
									menu=0;
									return 0;
								}
								Battle[select[mode]][submenu][1]&=0x80;
								Battle[select[mode]][submenu][1]|=i+j*16;
								menu=0;
								return 0;
							}
						}
					}
					menu=0;
				}
				if(menu==2){
					l=submenu;
					if(l>14)l=14;
					if(p.x>=414&&p.x<=434&&p.y>=12+16*l&&p.y<=25+16*l){
						Battle[select[mode]][submenu][2]^=0x80;
						return 0;
					}
					for(i=0;i<16;i++){
						for(j=0;j<4;j++){
							if(p.x>=344+115*j&&p.x<=458+115*j&&p.y>=28+16*i+(l)*16&&p.y<=43+16*i+(l)*16){
								if(j==3&&i==15){
									Battle[select[mode]][submenu][2]=255;
									menu=0;
									return 0;
								}
								Battle[select[mode]][submenu][2]&=0x80;
								Battle[select[mode]][submenu][2]|=i+j*16;
								menu=0;
								return 0;
							}
						}
					}
					menu=0;
				}
				if(menu==3){
					if(!ExpandSpells)
					for(i=0;i<16;i++){
						for(j=0;j<4;j++){
							if(p.x>=404+75*j&&p.x<=478+75*j&&p.y>=28+16*i+(submenu)*16&&p.y<=43+16*i+(submenu)*16){
								Battle[select[mode]][submenu][3]=i+j*64;
								menu=0;
								return 0;
							}
						}
					}
					else
					for(i=0;i<32;i++){
						for(j=0;j<4;j++){
							if(p.x>=404+75*j&&p.x<=478+75*j&&p.y>=28+16*i&&p.y<=43+16*i){
								Battle[select[mode]][submenu][3]=i+j*64;
								menu=0;
								return 0;
							}
						}
					}
					menu=0;
				}
				if(menu==4){
					l=submenu;
					if(l>14)l=14;
					for(i=0;i<16;i++){
						for(j=0;j<5;j++){
							if(p.x>=184+115*j&&p.x<=298+115*j&&p.y>=28+16*i+(l)*16&&p.y<=43+16*i+(l)*16){
								Battle[select[mode]][submenu][0]=i+j*16;
								menu=0;
								return 0;
							}
						}
					}
					menu=0;
				}
				for(i=0;i<NUM_BATTLES;i++){
					if(p.x>=20&&p.x<=90&&p.y>=i*16+10&&p.y<=i*16+25){
						select[mode]=i;
					}
				}
				for(i=0;i<NumEnemies[select[mode]];i++){
					for(j=0;j<8;j++){
						if(p.x>=240+60*j&&p.x<310+60*j&&p.y>=i*16+26&&p.y<i*16+42){
							focus=2+i*8+j;
						}
					}
					if(p.x>=740&&p.x<800&&p.y>=i*16+26&&p.y<i*16+42){
						submode[mode]=1;
						menu=i;
					}

					if(p.x>=219&&p.x<239&&p.y>=i*16+25&&p.y<i*16+45){
						menu=4;
						submenu=i;
					}

					if(p.x>=279&&p.x<299&&p.y>=i*16+25&&p.y<i*16+45){
						menu=1;
						submenu=i;
					}

					if(p.x>=339&&p.x<359&&p.y>=i*16+25&&p.y<i*16+45){
						menu=2;
						submenu=i;
					}
					if(p.x>=399&&p.x<419&&p.y>=i*16+25&&p.y<i*16+45){
						menu=3;
						submenu=i;
					}
				}
			}

			if(submode[mode]==1){
				if(p.x>=160&&p.x<210&&p.y>=5&&p.y<21){
					focus=1;
				}

				for(j=0;j<NumBehaviors[select[mode]][menu];j++){
					if(Behaviors[select[mode]][menu][j][1]==2&&p.x>=85+260*(j%3)&&p.x<155+260*(j%3)&&p.y>=155+170*(j-j%3)/3&&p.y<173+170*(j-j%3)/3){
						submode[mode]=4;
						subselect[mode][1]=j;
						return false;
					}

					if(p.x>=85+260*(j%3)&&p.x<85+260*(j%3)+50&&p.y>=139+170*(j-j%3)/3&&p.y<139+170*(j-j%3)/3+16){
						focus=2;
						subfocus=j;
					}

					if(p.x>=85+260*(j%3)&&p.x<85+260*(j%3)+50&&p.y>=155+170*(j-j%3)/3&&p.y<155+170*(j-j%3)/3+16){
						focus=3;
						subfocus=j;
					}

					if(p.x>=85+260*(j%3)&&p.x<85+260*(j%3)+50&&p.y>=171+170*(j-j%3)/3&&p.y<171+170*(j-j%3)/3+16){
						focus=4;
						subfocus=j;
					}

					for(i=0;i<8;i++){
						if(p.x>=165+(i%2)*90+260*(j%3)&&p.x<165+(i%2)*90+260*(j%3)+20&&p.y>=61+(i-i%2)/2*16+170*(j-j%3)/3&&p.y<61+(i-i%2)/2*16+170*(j-j%3)/3+16){
							Behaviors[select[mode]][menu][j][0]^=(1<<i);
						}
					}

				}
				if(p.x>=200&&p.x<240&&p.y>=0&&p.y<20){
					submode[mode]=2;
					menu=0;
				}
			}
			if(submode[mode]==2){

				if (p.x >= 0 && p.x <= 40 && p.y >= 50 && p.y <= 90) {
					mode = 105;

					BattleMode = 1;
					focus = 0;
					menu = 0;
					BattleSelect = -1;
					return 0;
				}



				if(menu==1||menu==2){
					if(p.x>=dwidth+354&&p.x<=dwidth+374&&p.y>=121&&p.y<=134){
						Battle[select[mode]][BattleSelect][menu]^=0x80;
						return 0;
					}
					if(NumItems==128){
						if(p.x>=dwidth+449&&p.x<=dwidth+469&&p.y>=121&&p.y<=134){
							Battle[select[mode]][BattleSelect][menu]^=0x40;
							return 0;
						}
					}
					for(i=0;i<16;i++){
						for(j=0;j<4;j++){
							if(p.x>=dwidth+284+115*j&&p.x<=dwidth+398+115*j&&p.y>=137+16*i&&p.y<=153+16*i){
								if(j==3&&i==15){
									Battle[select[mode]][BattleSelect][menu]=255;
									menu=0;
									return 0;
								}
								if(NumItems==128){
									Battle[select[mode]][BattleSelect][menu]&=0xC0;
								} else {
									Battle[select[mode]][BattleSelect][menu]&=0x80;
								}
								Battle[select[mode]][BattleSelect][menu]|=i+j*16;
								menu=0;
								return 0;
							}
						}
					}
					menu=0;
				}
				if(menu==3){
					if(!ExpandSpells)
					for(i=0;i<=16;i++){
						for(j=0;j<4;j++){
							if(p.x>=dwidth+404+75*j&&p.x<=dwidth+478+75*j&&p.y>=161+16*i&&p.y<=176+16*i){
								if(i==16)Battle[select[mode]][BattleSelect][3]=255;
								else Battle[select[mode]][BattleSelect][3]=i+j*64;
								menu=0;
								return 0;
							}
						}
					}
					else
					for(i=0;i<=32;i++){
						for(j=0;j<4;j++){
							if(p.x>=dwidth+404+75*j&&p.x<=dwidth+478+75*j&&p.y>=28+16*i-16&&p.y<=43+16*i-16){
								if(i==32)Battle[select[mode]][BattleSelect][3]=255;
								else Battle[select[mode]][BattleSelect][3]=i+j*64;
								menu=0;
								return 0;
							}
						}
					}
					menu=0;
					return 0;
				}
				if(menu==4){
					int q = 16 + 16*(NumMonsters==146);
					for(i=0;i<q;i++){
						for(j=0;j<5;j++){
							if(p.x>=dwidth+184+115*j&&p.x<=dwidth+298+115*j&&p.y>=43+16*i&&p.y<=58+16*i){
								if(i+j*q<NumMonsters)Battle[select[mode]][BattleSelect][0]=i+j*q;
								menu=0;
								return 0;
							}
						}
					}
					menu=0;

				}
				if (menu == 5) {

					for (int i = 0; i < 3; i++) {

						if (p.x >= dwidth + 620 && p.x <= dwidth + 720 && p.y >= 478 + i * 20 && p.y <= 498 + i * 20) {
							Behaviors[select[mode]][BattleSelect][subselect[mode][2]][1] = i;
							return 0;
						}
					}
					menu = 0;
				}

				if (menu == 6) {

					for (int i = 0; i<NUM_SOUNDS / 3; i++) {

						if (p.x >= 50 && p.x <= dwidth + 50 + 200 && p.y >= 28 + i * 14 && p.y <= 28 + (i + 1) * 14) {

							MapHeader[BattleHeaderPos[select[mode]]][0] = i + 1;

						}

						if (p.x >= 50 + 200 && p.x <= 50 + 400 && p.y >= 28 + i * 14 && p.y <= 28 + (i + 1) * 14) {

							MapHeader[BattleHeaderPos[select[mode]]][0] = i + NUM_SOUNDS / 3 + 1;

						}

						if (p.x >= 50 + 400 && p.x <= 50 + 600 && p.y >= 28 + i * 14 && p.y <= 28  + (i + 1) * 14) {

							MapHeader[BattleHeaderPos[select[mode]]][0] = i + 2 * NUM_SOUNDS / 3 + 1;

						}
					}

					menu = 0;
					return 0;
				}

				if (p.x >= 307 && p.x <= 327 && p.y >= 8 && p.y <= 28) {
					menu = 6;
				}

				if(p.x>=55&&p.x<=75&&p.y>=8&&p.y<=28){
					select[mode]--;
					if(select[mode]<0)select[mode]+= NUM_BATTLES;
					ViewX=0;
					ViewY=0;
					BattleSelect=-1;
					BattleDrag=-1;
					BattleEntrance=BattleIndex[select[mode]][3];
					subselect[mode][2] = 0;
				}
				if(p.x>=76&&p.x<=135&&p.y>=10&&p.y<=26){
					focus=1;
				}
				if(p.x>=140&&p.x<=160&&p.y>=8&&p.y<=28){
					select[mode]++;
					select[mode]%= NUM_BATTLES;
					ViewX=0;
					ViewY=0;
					BattleSelect=-1;
					BattleDrag=-1;
					BattleEntrance=BattleIndex[select[mode]][3];
					subselect[mode][2] = 0;
				}
				if(p.x>=176&&p.x<=237&&p.y>=10&&p.y<=26){
					focus=2;
				}
				if(p.x>=238&&p.x<=328&&p.y>=10&&p.y<=26){
					focus=3;
				}
				if(p.x>=328&&p.x<=377&&p.y>=10&&p.y<=26){
					focus=4;
				}
				if(p.x>=378&&p.x<=427&&p.y>=10&&p.y<=26){
					focus=5;
				}
				if(p.x>=428&&p.x<=477&&p.y>=10&&p.y<=26){
					focus=6;
				}
				if(p.x>=478&&p.x<=527&&p.y>=10&&p.y<=26){
					focus=7;
				}
				if(p.x>=300&&p.x<=313&&p.y>=(BMH-10)*48+522&&p.y<=(BMH-10)*48+535){
					DisplayBorder=!DisplayBorder;
				}
				if(p.x>=430&&p.x<=443&&p.y>=(BMH-10)*48+522&&p.y<=(BMH-10)*48+535){
					DisplayGrid=!DisplayGrid;
				}

				if(p.x>=dwidth+540&&p.x<=dwidth+553&&p.y>=32&&p.y<=45){
					BattleMode=0;
					BattleSelect=-1;
					subselect[mode][2] = 0;
				}

				if(p.x>=dwidth+700&&p.x<=dwidth+713&&p.y>=32&&p.y<=45){
					BattleMode=1;
					BattleSelect=-1;
					subselect[mode][2] = 0;
				}

				if(p.x>=dwidth+540&&p.x<=dwidth+553&&p.y>=48&&p.y<=61){
					BattleMode=2;
					BattleSelect=-1;
					subselect[mode][2] = 0;
				}

				if(p.x>=dwidth+700&&p.x<=dwidth+713&&p.y>=48&&p.y<=61){
					BattleMode=3;
					BattleSelect=-1;
					subselect[mode][2] = 0;
				}

				if (p.x >= dwidth + 540 && p.x <= dwidth + 553 && p.y >= 64 && p.y <= 76) {
					BattleMode = 4;
					BattleSelect = -1;
					subselect[mode][2] = 0;
				}

				switch(BattleMode){
				case 0:
					if(p.x>=50&&p.x<50+48*BMW&&p.y>=40&&p.y<=40+48*BMH){
						i = (p.x-50)*MapZoom/48+ViewX-MapHeader[BattleHeaderPos[select[mode]]][3];
						j = (p.y-40)*MapZoom/48+ViewY-MapHeader[BattleHeaderPos[select[mode]]][5];
						for(k=0;k<NumEnemies[select[mode]];k++){
							if(Battle[select[mode]][k][4]==i&&Battle[select[mode]][k][5]==j)BattleDrag=k;
						}

						if(BattleSelect!=-1)
						for(k=0;k<NumBehaviors[select[mode]][BattleSelect];k++){
							if(Behaviors[select[mode]][BattleSelect][k][1]==0){
								if(i==Behaviors[select[mode]][BattleSelect][k][2]&&j==Behaviors[select[mode]][BattleSelect][k][3]){
									BattleDrag=BattleSelect+256*(k+1);
								}
							}

							if(Behaviors[select[mode]][BattleSelect][k][1]==2){
								for(int l=0;l<8;l++){
									if(AIPaths[select[mode]][BattleSelect][k][l][0]==0xFF)break;
									if(i==AIPaths[select[mode]][BattleSelect][k][l][0]&&j==AIPaths[select[mode]][BattleSelect][k][l][1]){
										BattleDrag=BattleSelect+256*(k+1)+32*l;
									}
								}
							}
						}

						if(BattleDrag==-1)BattleSelect=-1;
						else {
							if(BattleSelect!= (BattleDrag & 0x1F))subselect[mode][2] = 0;
							BattleSelect = BattleDrag & 0x1F;
						}
						
					}

					if(p.x>=dwidth+720&&p.x<=dwidth+740&&p.y>=119&&p.y<139){
						RemoveEnemy();
					}

					if (p.x >= dwidth + 720 && p.x <= dwidth + 740 && p.y >= 139 && p.y<159) {
						if (BattleSelect >= 0) {
							Battle[select[mode]][BattleSelect][1] = 255;
						}
					}
					if (p.x >= dwidth + 720 && p.x <= dwidth + 740 && p.y >= 159 && p.y<179) {
						if (BattleSelect >= 0) {
							Battle[select[mode]][BattleSelect][2] = 255;
						}
					}
					if (p.x >= dwidth + 720 && p.x <= dwidth + 740 && p.y >= 179 && p.y<189) {
						if (BattleSelect >= 0) {
							Battle[select[mode]][BattleSelect][3] = 255;
						}
					}

					if(p.x>=dwidth+540&&p.x<=dwidth+560&&p.y>=138&&p.y<158){
						menu=1;
					}
					if(p.x>=dwidth+540&&p.x<=dwidth+560&&p.y>=158&&p.y<178){
						menu=2;
					}
					if(p.x>=dwidth+540&&p.x<=dwidth+560&&p.y>=178&&p.y<198){
						menu=3;
					}
					if(p.x>=dwidth+540&&p.x<=dwidth+560&&p.y>=118&&p.y<138){
						menu=4;
					}
					if(p.x>=dwidth+540&&p.x<=dwidth+600&&p.y>=198&&p.y<218){
						focus=8;
					}
					if(p.x>=dwidth+540&&p.x<=dwidth+600&&p.y>=218&&p.y<238){
						focus=9;
					}
					if(p.x>=dwidth+540&&p.x<=dwidth+640&&p.y>=238&&p.y<258){
						focus=10;
					}
					if(p.x>=dwidth+540&&p.x<=dwidth+640&&p.y>=258&&p.y<278){
						focus=15;
					}

					if (p.x >= dwidth + 540 && p.x <= dwidth + 740 && p.y >= 318 && p.y<338) {
						focus = -1;
					}

					if (p.x >= dwidth + 570 && p.x <= dwidth + 670 && p.y >= 500 && p.y<520) {
						focus = -2;
					}
					if (p.x >= dwidth + 570 && p.x <= dwidth + 670 && p.y >= 520 && p.y<540) {
						focus = -3;
					}


					if (BattleSelect != -1) {
						if (p.x >= dwidth + 560 && p.x <= dwidth + 580 && p.y >= 360 && p.y < 380) {
							subselect[mode][2]--;
							if (subselect[mode][2] < 0)subselect[mode][2] = NumBehaviors[select[mode]][BattleSelect] - 1;
						}

						if (p.x >= dwidth + 695 && p.x <= dwidth + 715 && p.y >= 360 && p.y < 380) {
							subselect[mode][2]++;
							if (subselect[mode][2] >= NumBehaviors[select[mode]][BattleSelect])subselect[mode][2] = 0;
						}

						if (NumBehaviors[select[mode]][BattleSelect]) {

							for (i = 0; i < 8; i++) {
								if (p.x >= dwidth + 600 + (i % 2) * 90 && p.x <= dwidth + 600 + (i % 2) * 90 + 13 && p.y >= 400 + (i - i % 2) / 2 * 16 && p.y < 400 + (i - i % 2) / 2 * 16 + 13) {
									if (Behaviors[select[mode]][BattleSelect][subselect[mode][2]][0] & (1 << i)) {
										Behaviors[select[mode]][BattleSelect][subselect[mode][2]][0] ^= (1 << i);
									} else {
										Behaviors[select[mode]][BattleSelect][subselect[mode][2]][0] |= (1 << i);
									}
								}
							}

							if (p.x >= dwidth + 620 && p.x <= dwidth + 720 && p.y >= 478 && p.y < 498) {
								menu = 5;
							}

							if (Behaviors[select[mode]][BattleSelect][subselect[mode][2]][1] == 2) {
								if (p.x >= dwidth + 756 && p.x <= dwidth + 776 && p.y >= 498 && p.y <= 518) {
									for (int l = 0; l < 8; l++) {
										if (AIPaths[select[mode]][BattleSelect][subselect[mode][2]][l][0] == 0xFF) {
											AIPaths[select[mode]][BattleSelect][subselect[mode][2]][l][0] = 4 + ViewX - MapHeader[BattleHeaderPos[select[mode]]][3];
											AIPaths[select[mode]][BattleSelect][subselect[mode][2]][l][1] = 4 + ViewY - MapHeader[BattleHeaderPos[select[mode]]][5];
											break;
										}
									}
								}
								if (p.x >= dwidth + 756 && p.x <= dwidth + 776 && p.y >= 518 && p.y <= 538) {
									for (int l = 0; l < 8; l++) {
										if (AIPaths[select[mode]][BattleSelect][subselect[mode][2]][l][0] == 0xFF) {
											if (l)AIPaths[select[mode]][BattleSelect][subselect[mode][2]][l - 1][0] = 0xFF;
											break;
										}
									}
								}
							}
						}


						if (p.x >= dwidth + 540 && p.x <= dwidth + 560 && p.y >= 278 && p.y < 298) {
							submode[mode] = 1;
							menu = BattleSelect;
						}
					}
					if(p.x>=dwidth+575&&p.x<=dwidth+595&&p.y>=90&&p.y<110){
						if(NumEnemies[select[mode]]<20){
							
							BattleDrag=-1;
							subselect[mode][2] = 0;
							BattleSelect=NumEnemies[select[mode]];
							Battle[select[mode]][BattleSelect][0]=0;
							Battle[select[mode]][BattleSelect][1]=255;
							Battle[select[mode]][BattleSelect][2]=255;
							Battle[select[mode]][BattleSelect][3]=255;
							Battle[select[mode]][BattleSelect][4]=4+ViewX-MapHeader[BattleHeaderPos[select[mode]]][3];
							Battle[select[mode]][BattleSelect][5]=4+ViewY-MapHeader[BattleHeaderPos[select[mode]]][5];
							Battle[select[mode]][BattleSelect][6]=0;
							Battle[select[mode]][BattleSelect][7]=1;
							NumBehaviors[select[mode]][BattleSelect]=1;
							Behaviors[select[mode]][BattleSelect][0][0] = 254;
							Behaviors[select[mode]][BattleSelect][0][1] = 1;
							Behaviors[select[mode]][BattleSelect][0][2] = 255;
							Behaviors[select[mode]][BattleSelect][0][3] = 255;

							bool overlap;
							int l = 0;

							do {
								overlap = false;
								for (k = 0; k < NumEnemies[select[mode]]; k++) {
									if ((Battle[select[mode]][k][4] == Battle[select[mode]][BattleSelect][4] && Battle[select[mode]][k][5] == Battle[select[mode]][BattleSelect][5]) || (Battle[select[mode]][BattleSelect][4]<0) || (Battle[select[mode]][BattleSelect][5]<0)) {
										overlap = true;
										switch (l) {
										case 0:
											Battle[select[mode]][BattleSelect][4]-=1;
											Battle[select[mode]][BattleSelect][5]-=0;
											break;
										case 1:
										case 9:
										case 10:
										case 11:
											Battle[select[mode]][BattleSelect][4] -= 0;
											Battle[select[mode]][BattleSelect][5] -= 1;
											break;
										case 2:
										case 3:
										case 12:
										case 13:
										case 14:
										case 15:
											Battle[select[mode]][BattleSelect][4] += 1;
											Battle[select[mode]][BattleSelect][5] -= 0;
											break;
										case 4:
										case 5:
										case 16:
										case 17:
										case 18:
										case 19:
											Battle[select[mode]][BattleSelect][4] -= 0;
											Battle[select[mode]][BattleSelect][5] += 1;
											break;
										case 6:
										case 7:
										case 8:
										case 20:
										case 21:
										case 22:
										case 23:
											Battle[select[mode]][BattleSelect][4] -= 1;
											Battle[select[mode]][BattleSelect][5] += 0;
											break;
										default:
											overlap = false;
										}
										l++;
										break;
									}
								}
							} while (overlap);

							NumEnemies[select[mode]]++;
						}
					}
					break;
				case 1:

					if(p.x>=dwidth+673&&p.x<dwidth+775&&p.y>=98&&p.y<120){
						submode[mode]=3;
						subselect[mode][0]=select[mode];
						select[mode]=0;
						return 0;
					}

					if(p.x>=dwidth+560&&p.x<dwidth+640&&p.y>=98&&p.y<118){
						focus=14;
					}
					if(p.x>=dwidth+540&&p.x<=dwidth+560&&p.y>=98&&p.y<118){
						BattleTerrain--;
						if(BattleTerrain<0)BattleTerrain=15;
					}
					if(p.x>=dwidth+640&&p.x<=dwidth+660&&p.y>=98&&p.y<118){
						BattleTerrain++;
						BattleTerrain%=16;
					}

					if(p.x>=50&&p.x<50+48*BMW&&p.y>=40&&p.y<=40+48*BMH){
						i = (p.x-50)*MapZoom/48+ViewX-MapHeader[BattleHeaderPos[select[mode]]][3]-1;
						j = (p.y-40)*MapZoom/48+ViewY-MapHeader[BattleHeaderPos[select[mode]]][5]-1;

						if(BattleTerrain){
							if(!BattleLand[select[mode]][i+(j)*BattleSize[select[mode]][0]]){
								BattleAI[select[mode]][i+(j)*BattleSize[select[mode]][0]]=0;
							}
						}
						
						if (!BattleTerrain) {
							if (BattleLand[select[mode]][i + (j)*BattleSize[select[mode]][0]]) {
								BattleAI[select[mode]][i + (j)*BattleSize[select[mode]][0]] = 255;
							}
						}

						BattleLand[select[mode]][i+(j)*BattleSize[select[mode]][0]]=BattleTerrain;
					}

					for(i=0;i<8;i++){
						if(p.x>=dwidth+575&&p.x<dwidth+650&&p.y>=320+20*i&&p.y<=340+20*i){
							focus=16+i;
						}

						if(p.x>=dwidth+675&&p.x<dwidth+750&&p.y>=320+20*i&&p.y<=340+20*i){
							focus=24+i;
						}
					}

					break;
				case 2:
					if(p.x>=dwidth+560&&p.x<dwidth+640&&p.y>=98&&p.y<118){
						focus=13;
					}
					if(p.x>=50&&p.x<50+48*BMW&&p.y>=40&&p.y<=40+48*BMH){
						i = (p.x-50)*MapZoom/48+ViewX-MapHeader[BattleHeaderPos[select[mode]]][3]-1;
						j = (p.y-40)*MapZoom/48+ViewY-MapHeader[BattleHeaderPos[select[mode]]][5]-1;
						if(BattleLand[select[mode]][i+(j)*BattleSize[select[mode]][0]]){
							BattleAI[select[mode]][i+(j)*BattleSize[select[mode]][0]]=BattleReg;
						}
					}

					if(p.x>=dwidth+540&&p.x<=dwidth+560&&p.y>=98&&p.y<118){
						BattleReg--;
						if(BattleReg<0)BattleReg=6;
					}
					if(p.x>=dwidth+640&&p.x<=dwidth+660&&p.y>=98&&p.y<118){
						BattleReg++;
						BattleReg%=7;
					}
					break;
				case 3:
					if(p.x>=50&&p.x<50+48*BMW&&p.y>=40&&p.y<=40+48*BMH){
						i = (p.x-50)*MapZoom/48+ViewX-MapHeader[BattleHeaderPos[select[mode]]][3];
						j = (p.y-40)*MapZoom/48+ViewY-MapHeader[BattleHeaderPos[select[mode]]][5];
						for(k=0;k<NumBattleStart[select[mode]][BattleEntrance];k++){
							if(BattleStart[select[mode]][BattleEntrance][k][0]==i&&BattleStart[select[mode]][BattleEntrance][k][1]==j)BattleDrag=k;
						}
						if(BattleSelect!=BattleDrag)subselect[mode][2] = 0;
						BattleSelect=BattleDrag;
						
					}
					if(p.x>=dwidth+540&&p.x<=dwidth+560&&p.y>=98&&p.y<118){
						BattleEntrance--;
						if(BattleEntrance<0)BattleEntrance=3;
					}
					if(p.x>=dwidth+560&&p.x<dwidth+640&&p.y>=98&&p.y<118){
						focus=11;
					}
					if(p.x>=dwidth+640&&p.x<=dwidth+660&&p.y>=98&&p.y<118){
						BattleEntrance++;
						BattleEntrance%=4;
					}

					if(p.x>=dwidth+540&&p.x<=dwidth+560&&p.y>=118&&p.y<138){
						if(NumBattleStart[select[mode]][BattleEntrance]>0)NumBattleStart[select[mode]][BattleEntrance]--;
						if(NumBattleStart[select[mode]][BattleEntrance]<0)NumBattleStart[select[mode]][BattleEntrance]=0;
					}
					if(p.x>=dwidth+540&&p.x<dwidth+640&&p.y>=118&&p.y<138){
						focus=12;
					}
					if(p.x>=dwidth+650&&p.x<=dwidth+670&&p.y>=118&&p.y<138){
						NumBattleStart[select[mode]][BattleEntrance]++;
						if(NumBattleStart[select[mode]][BattleEntrance]>12)NumBattleStart[select[mode]][BattleEntrance]=12;
						else {
							BattleStart[select[mode]][BattleEntrance][NumBattleStart[select[mode]][BattleEntrance]-1][0]=4+ViewX-MapHeader[BattleHeaderPos[select[mode]]][3];
							BattleStart[select[mode]][BattleEntrance][NumBattleStart[select[mode]][BattleEntrance]-1][1]=4+ViewY-MapHeader[BattleHeaderPos[select[mode]]][5];

							if (BattleStart[select[mode]][BattleEntrance][NumBattleStart[select[mode]][BattleEntrance] - 1][0] < 0)BattleStart[select[mode]][BattleEntrance][NumBattleStart[select[mode]][BattleEntrance] - 1][0] = 0;
							if (BattleStart[select[mode]][BattleEntrance][NumBattleStart[select[mode]][BattleEntrance] - 1][1] < 0)BattleStart[select[mode]][BattleEntrance][NumBattleStart[select[mode]][BattleEntrance] - 1][1] = 0;

							if (BattleStart[select[mode]][BattleEntrance][NumBattleStart[select[mode]][BattleEntrance] - 1][0] >= BattleSize[select[mode]][0]) {
								if (4 + ViewX < MapHeader[BattleHeaderPos[select[mode]]][3])
									BattleStart[select[mode]][BattleEntrance][NumBattleStart[select[mode]][BattleEntrance] - 1][0] = 1;
								else
									BattleStart[select[mode]][BattleEntrance][NumBattleStart[select[mode]][BattleEntrance] - 1][0] = BattleSize[select[mode]][0];
							}
							if (BattleStart[select[mode]][BattleEntrance][NumBattleStart[select[mode]][BattleEntrance] - 1][1] >= BattleSize[select[mode]][1])BattleStart[select[mode]][BattleEntrance][NumBattleStart[select[mode]][BattleEntrance] - 1][1] = BattleSize[select[mode]][1]-1;

							BattleSelect = NumBattleStart[select[mode]][BattleEntrance] - 1;

							bool overlap;
							int l = 0;

							do {
								overlap = false;
								for (k = 0; k < NumBattleStart[select[mode]][BattleEntrance]-1; k++) {
									if ((BattleStart[select[mode]][BattleEntrance][k][0]== BattleStart[select[mode]][BattleEntrance][NumBattleStart[select[mode]][BattleEntrance]-1][0] && BattleStart[select[mode]][BattleEntrance][k][1] == BattleStart[select[mode]][BattleEntrance][NumBattleStart[select[mode]][BattleEntrance]-1][1]) || (BattleStart[select[mode]][BattleEntrance][NumBattleStart[select[mode]][BattleEntrance]-1][0]<0) || (BattleStart[select[mode]][BattleEntrance][NumBattleStart[select[mode]][BattleEntrance]-1][1]<0)) {
										overlap = true;
										switch (l) {
										case 0:
											BattleStart[select[mode]][BattleEntrance][NumBattleStart[select[mode]][BattleEntrance]-1][0] -= 1;
											BattleStart[select[mode]][BattleEntrance][NumBattleStart[select[mode]][BattleEntrance]-1][1] -= 0;
											break;
										case 1:
										case 9:
										case 10:
										case 11:
											BattleStart[select[mode]][BattleEntrance][NumBattleStart[select[mode]][BattleEntrance]-1][0] -= 0;
											BattleStart[select[mode]][BattleEntrance][NumBattleStart[select[mode]][BattleEntrance]-1][1] -= 1;
											break;
										case 2:
										case 3:
										case 12:
										case 13:
										case 14:
										case 15:
											BattleStart[select[mode]][BattleEntrance][NumBattleStart[select[mode]][BattleEntrance]-1][0] += 1;
											BattleStart[select[mode]][BattleEntrance][NumBattleStart[select[mode]][BattleEntrance]-1][1] -= 0;
											break;
										case 4:
										case 5:
										case 16:
										case 17:
										case 18:
										case 19:
											BattleStart[select[mode]][BattleEntrance][NumBattleStart[select[mode]][BattleEntrance]-1][0] -= 0;
											BattleStart[select[mode]][BattleEntrance][NumBattleStart[select[mode]][BattleEntrance]-1][1] += 1;
											break;
										case 6:
										case 7:
										case 8:
										case 20:
										case 21:
										case 22:
										case 23:
											BattleStart[select[mode]][BattleEntrance][NumBattleStart[select[mode]][BattleEntrance]-1][0] -= 1;
											BattleStart[select[mode]][BattleEntrance][NumBattleStart[select[mode]][BattleEntrance]-1][1] += 0;
											break;
										default:
											overlap = false;
										}
										l++;
										break;
									}
								}
							} while (overlap);
						}
					}
					break;
				case 4:
					if (p.x >= dwidth + 561 && p.x<dwidth + 660 && p.y >= 162 && p.y<182 && BattleExit != 255 && BattleExit != -1) {

						subselect[18][0] = BattleIndex[select[mode]][0]-1;
						submode[18] = 2;


						if (!ScriptsLoaded&&strlen(file)) {
							LoadDialog(file);
							LoadBE(file);
							LoadBExit(file);
						}

						if (ScriptsLoaded) {
							BExitGraphNode * node = BExitGraphs[subselect[18][0]]->findRegion(BattleIndex[select[mode]][1]);

							node = BExitGraphs[subselect[18][0]]->findExit(BattleExit,node,true);

							if (node) {
								if (BExitGraphs[subselect[18][0]]->sel)BExitGraphs[subselect[18][0]]->sel->selected = false;
								node->selected = true;
								node->selout = false;
								BExitGraphs[subselect[18][0]]->sel = node;
								BExitGraphs[subselect[18][0]]->vx = BExitGraphs[subselect[18][0]]->sel->x - BExitGraphs[subselect[18][0]]->w / 2;
								BExitGraphs[subselect[18][0]]->vy = BExitGraphs[subselect[18][0]]->sel->y - BExitGraphs[subselect[18][0]]->h / 2;
							}
						}
						mode = 18;
						menu = 0;
						focus = -1;
						ignorerelease = true;
					}

					if (p.x >= dwidth + 560 && p.x<dwidth + 640 && p.y >= 98 && p.y<118) {
						focus = 13;
					}
					if (p.x >= dwidth + 560 && p.x<dwidth + 640 && p.y >= 118 && p.y<138) {
						focus = 14;
					}

					if (p.x >= dwidth + 584 && p.x<dwidth + 644 && p.y >= 140 && p.y<160) {
						focus = -4;
					}
					if (p.x >= dwidth + 674 && p.x<dwidth + 724 && p.y >= 140 && p.y<160) {
						focus = -5;
					}

					if (p.x >= dwidth + 540 && p.x <= dwidth + 560 && p.y >= 98 && p.y<118) {
						BattleExitSet--;
						if (BattleExitSet<0)BattleExitSet = 2;

						if (BattExits[select[mode]][BattleExitSet] == 255)BattleExitSet = 0;
					}
					if (p.x >= dwidth + 640 && p.x <= dwidth + 660 && p.y >= 98 && p.y<118) {
						BattleExitSet++;
						if (BattleExitSet>2)BattleExitSet = 0;
						if (BattExits[select[mode]][BattleExitSet] == 255)BattleExitSet = 0;
					}

					if (p.x >= dwidth + 540 && p.x <= dwidth + 560 && p.y >= 118 && p.y<138) {
						BattleExit--;
						if (BattleExit==-1)BattleExit = 255;
						if (BattleExit < -1)BattleExit = 127;
						if (BattleExit == 254)BattleExit = 127;
						if (BattleExit == 124)BattleExit = 7;
					}
					if (p.x >= dwidth + 640 && p.x <= dwidth + 660 && p.y >= 118 && p.y<138) {
						BattleExit++;
						if (BattleExit>7)BattleExit = 124;
						if (BattleExit>127)BattleExit = 255;
						if (BattleExit>255)BattleExit = 0;
					}

					if (p.x >= 50 && p.x<50 + 48 * BMW&&p.y >= 40 && p.y <= 40 + 48 * BMH) {
						if (BattleExitSet == 0) {
							i = (p.x - 50)*MapZoom / 48 + ViewX - MapHeader[BattleHeaderPos[select[mode]]][3];
							j = (p.y - 40)*MapZoom / 48 + ViewY - MapHeader[BattleHeaderPos[select[mode]]][5];
						} else {
							i = (p.x - 50)*MapZoom / 48 + ViewX;
							j = (p.y - 40)*MapZoom / 48 + ViewY;
						}

						if (j >= 0 && i < MapSize[MapHeader[BattleHeaderPos[select[mode]]][1]][0]) {
							Exits[BattExits[select[mode]][BattleExitSet]][i + (j)*MapSize[MapHeader[BattleHeaderPos[select[mode]]][1]][0]] = BattleExit;
							if (Exits[BattExits[select[mode]][BattleExitSet]][i + (j)*MapSize[MapHeader[BattleHeaderPos[select[mode]]][1]][0]] == -1)Exits[BattExits[select[mode]][BattleExitSet]][i + (j)*MapSize[MapHeader[BattleHeaderPos[select[mode]]][1]][0]] = 255;
							Exits[128 + BattExits[select[mode]][BattleExitSet]][i + (j)*MapSize[MapHeader[BattleHeaderPos[select[mode]]][1]][0]] = BattleTele;
						}
					}

					break;
				}
					if(p.x>=20&&p.x<=40&&p.y>=(BMH-10)*48+500&&p.y<=(BMH-10)*48+520){
						MapZoom*=2;
						if(MapZoom==8)MapZoom=1;

						if(ViewX>=MapSize[MapHeader[BattleHeaderPos[select[mode]]][1]][0]-10*MapZoom)ViewX=MapSize[MapHeader[BattleHeaderPos[select[mode]]][1]][0]-10*MapZoom;
						if(ViewY>=MapSize[MapHeader[BattleHeaderPos[select[mode]]][1]][1]-10*MapZoom)ViewY=MapSize[MapHeader[BattleHeaderPos[select[mode]]][1]][1]-10*MapZoom;

						if(ViewX<0)ViewX=0;
						if(ViewY<0)ViewY=0;
					}
			}

			if(submode[mode]==3){
				if(subselect[mode][0]!=-1){
					if(p.x>=673&&p.x<=775&&p.y>=520&&p.y<=540){
						submode[mode]=2;
						select[mode]=subselect[mode][0];
						subselect[mode][0]=-1;
						return 0;
					}
				}

				j=(125-(125)%30)/30;
				if((125)%30>0)j++;
				for(i=0;i<j;i++){
					if(p.x>=50&&p.x<=149&&p.y>=i*16+10&&p.y<=i*16+25){
						select[mode]=i;
					}
				}

				for(i=0;i<16;i++){
					if(p.x>=50&&p.x<=149&&p.y>=(7+i)*16+10&&p.y<=(7+i)*16+25){
						select[mode]=i+7;
					}
				}

				if(select[mode]<7){
					for(i=0;i<NUM_BATTLES;i++){
						for(j=0;j<4;j++){
							if(p.x>=240+95*j&&p.x<=334+95*j&&p.y>=26+16*i&&p.y<=41+16*i){
								focus=j+1;
								subfocus=i;
							}
						}
					}
				} else {
					for(j=0;j<8;j++){
						if(p.x>=304+55*j&&p.x<=359+55*j&&p.y>=58&&p.y<=74){
							focus=j+1;
						}
						if(p.x>=304+55*j&&p.x<=359+55*j&&p.y>=90&&p.y<=106){
							focus=j+9;
						}
					}
				}
			}

			if(submode[mode]==4){
				if(p.x>=620&&p.x<=790&&p.y>=524&&p.y<=544){
					submode[mode]=1;
					focus=0;
					return true;
				}

				i = select[mode];
				j = menu;
				k = subselect[mode][1];

				if(p.x>=18&&p.x<=38&&p.y>=30&&p.y<=50){
					for(int l=0;l<8;l++){
						if(AIPaths[i][j][k][l][0]==0xFF){
							AIPaths[i][j][k][l][0] = 0;
							AIPaths[i][j][k][l][1] = 0;
							return false;
						}
					}
				}

				for(int l=0;l<8;l++){
					if(AIPaths[i][j][k][l][0]==0xFF)break;
					
					if(p.x>=18&&p.x<=38&&p.y>=50+20*l&&p.y<=70+20*l){
						for(int l2=l;l2<7;l2++){
							AIPaths[i][j][k][l2][0] = AIPaths[i][j][k][l2+1][0];
							AIPaths[i][j][k][l2][1] = AIPaths[i][j][k][l2+1][1];
						}
						AIPaths[i][j][k][7][0] = 0xFF;
						AIPaths[i][j][k][7][1] = 0xFF;
						return false;
					}

					if(p.x>=80&&p.x<=110&&p.y>=50+20*l&&p.y<=70+20*l){
						focus = 2*l+1;
					}
					if(p.x>=110&&p.x<=140&&p.y>=50+20*l&&p.y<=70+20*l){
						focus = 2*l+2;
					}
				}
			}

			GetClientRect(hWnd,&r);

