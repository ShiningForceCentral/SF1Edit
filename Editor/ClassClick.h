				switch(menu){
					case 1:
						if(p.x>=279&&p.x<=424&&p.y>=130&&p.y<=486){
							i=(p.y-130)/16;
							ClassData[select[mode]][5]=RangeVals[i]+16;
						}
						menu=0;
						return 0;
					case 2:
						for (i = 0;i < 7;i++) {
							if (p.x >= 515 && p.x <= 615 && p.y >= 182 + i * 20 && p.y <= 202 + i * 20) {
								ClassData[select[mode]][0] = i + 1;
								return 0;
							}
						}

						menu = 0;
						return 0;
					case 3:
						for (i = 0; i < 15; i++) {
							if (p.x >= 515 && p.x <= 639 && p.y >= 202 + i * 20 && p.y <= 222 + i * 20) {
								ClassAction = i;


								switch (ClassAction) {
								case 0:
									ClassData[select[mode]][1] = 255;
									break;
								case 1:
									ClassData[select[mode]][1] = 128;
									break;
								case 2:
									ClassData[select[mode]][1] = 130;
									break;
								case 3:
								case 4:
								case 5:
								case 6:
								case 7:
								case 8:
								case 9:
								case 10:
								case 11:
								case 12:
								case 13:
									ClassData[select[mode]][1] = ClassAction - 3;
									break;
								case 14:
									ClassData[select[mode]][1] = 131;
									break;
								}


								return 0;
							}
						}

						menu = 0;
						return 0;
					case 4:
						for (i = 0; i < 4; i++) {
							if (p.x >= 515 && p.x <= 639 && p.y >= 222 + i * 20 && p.y <= 242 + i * 20) {
								ActionChance = i;

								ClassData[select[mode]][4] &= 0xCF;
								ClassData[select[mode]][4] |= (ActionChance * 16);

								return 0;
							}
						}

						menu = 0;
						return 0;
					case 5:
						for (i = 0; i < 10; i++) {
							if (p.x >= 515 && p.x <= 639 && p.y >= 322 + i * 20 && p.y <= 342 + i * 20) {
								ClassSpecial = i;

								if (ClassSpecial == 0)ClassData[select[mode]][7]=255;
								else ClassData[select[mode]][7] = ClassSpecial-1;
									
								return 0;
							}
						}

						menu = 0;
						return 0;
					case 6:
						for (i = 0; i < 4; i++) {
							if (p.x >= 515 && p.x <= 639 && p.y >= 342 + i * 20 && p.y <= 362 + i * 20) {
								SpecialChance = i;

								ClassData[select[mode]][4] &= 0xFC;
								ClassData[select[mode]][4] |= (SpecialChance);

								return 0;
							}
						}

						menu = 0;
						return 0;
					case 7:
						for (i = 0; i < 4; i++) {
							if (p.x >= 515 && p.x <= 639 && p.y >= 422 + i * 20 && p.y <= 442 + i * 20) {

								ClassData[select[mode]][4] &= 0xF3;
								ClassData[select[mode]][4] |= (i*4);

								return 0;
							}
						}

						menu = 0;
						return 0;
					case 8:
						if (p.x >= 400 && p.x <= 515 && p.y >= 26 && p.y <= 40) {
							ClassPromote[select[mode]] = 0xFF;
						}

						if (p.x >= 400 && p.x <= 515 && p.y >= 41 && p.y <= 41 + 15 * 32) {
							i = (p.y - 41) / 15;
							ClassPromote[select[mode]] = i;
						}
						if (p.x >= 515 && p.x <= 630 && p.y >= 41 && p.y <= 41 + 15 * 32) {
							i = (p.y - 41) / 15;
							ClassPromote[select[mode]] = i + 32;
						}

						menu = 0;
						return 0;
				}

				if(p.x>=0&&p.x<=40&&p.y>=10&&p.y<=49){
					if(submode[mode]==1){
						submode[mode]=0;
						select[mode]-=32;
						select[mode]%=32;
					}
				}
				if(p.x>=0&&p.x<=40&&p.y>=50&&p.y<=99){
					if(submode[mode]==0){
						submode[mode]=1;
						select[mode]+=32;
					}
				}

				if(submode[mode]==0){
					for(i=0;i<32;i++){
						if(p.x>=30&&p.x<=149&&p.y>=i*16+10&&p.y<=i*16+25){
							focus=1;
							select[mode]=i+subselect[mode][0];
						}
					}

					if (NumClasses == 64) {
						if (p.x >= 200 && p.x <= 220 && p.y >= 520 && p.y <= 540) {
							select[mode] -= subselect[mode][0];
							subselect[mode][0] = 32 - subselect[mode][0];
							select[mode] += subselect[mode][0];
						}
						if (p.x >= 223 && p.x <= 243 && p.y >= 520 && p.y <= 540) {
							select[mode] -= subselect[mode][0];
							subselect[mode][0] = 32 - subselect[mode][0];
							select[mode] += subselect[mode][0];
						}
						if (p.x >= 380 && p.x <= 400 && p.y >= 461 && p.y <= 481) {
							menu = 8;
						}
					}

				}

				if(submode[mode]==1){
					for(i=0;i<37;i++){
						if(p.x>=30&&p.x<=149&&p.y>=i*14+5&&p.y<=i*14+20){
							focus=1;
							select[mode]=i+NumClasses+MonsterView;
						}
					}

					for(i=37;i<73;i++){
						if(p.x>=180&&p.x<=299&&p.y>=(i-37)*14+5&&p.y<=(i-37)*14+20){
							focus=1;
							select[mode]=i+ NumClasses +MonsterView;
						}
					}

					if(NumMonsters==146){
						if(p.x>=200&&p.x<=220&&p.y>=520&&p.y<=540){
							MonsterView -= 73;
							if(MonsterView<0)MonsterView+=NumMonsters;
							select[mode]-=73;
							select[mode] -= NumClasses;
							select[mode] %= NumMonsters;
							select[mode] += NumClasses;
						}
						if(p.x>=223&&p.x<=243&&p.y>=520&&p.y<=540){
							MonsterView += 73;
							MonsterView%=NumMonsters;
							select[mode]+=73;
							select[mode] -= NumClasses;
							select[mode] %= NumMonsters;
							select[mode] += NumClasses;
						}
					}
				}

				

				if (p.x >= 515 && p.x <= 615 && p.y >= 182 &&p.y <= 202) {
					menu = 2;
				}
				if (p.x >= 515 && p.x <= 639 && p.y >= 202 && p.y <= 222) {
					menu = 3;
				}
				if (p.x >= 515 && p.x <= 615 && p.y >= 222 && p.y <= 242) {
					menu = 4;
				}
				if (p.x >= 515 && p.x <= 647 && p.y >= 322 && p.y <= 342) {
					menu = 5;
				}
				if (p.x >= 515 && p.x <= 615 && p.y >= 342 && p.y <= 362) {
					menu = 6;
				}
				if(FixDoubles)
				if (p.x >= 515 && p.x <= 615 && p.y >= 422 && p.y <= 442) {
					menu = 7;
				}

				for(i=5;i<7;i++){
					if(p.x>=515&&p.x<=545&&p.y>=186+16*i&&p.y<=201+16*i)focus=2+i;
				}

				if(submode[mode]==0)
				if(p.x>=535&&p.x<=585&&p.y>=382&&p.y<=397)focus=12;

				if(p.x>=380&&p.x<=400&&p.y>=265&&p.y<=285){
					menu=1;
				}

				for(i=0;i<4;i++){
					if(p.x>=480+50*i&&p.x<=520+50*i&&p.y>=42&&p.y<=57){
						ClassData[select[mode]][2]&=0x3F;
						ClassData[select[mode]][2]|=i*64;
					}
				}

				for(i=0;i<4;i++){
					if(p.x>=480+50*i&&p.x<=520+50*i&&p.y>=58&&p.y<=73){
						ClassData[select[mode]][2]&=0xCF;
						ClassData[select[mode]][2]|=i*16;
					}
				}

				for(i=0;i<4;i++){
					if(p.x>=480+50*i&&p.x<=520+50*i&&p.y>=74&&p.y<=89){
						ClassData[select[mode]][2]&=0xF3;
						ClassData[select[mode]][2]|=i*4;
					}
				}

				for(i=0;i<4;i++){
					if(p.x>=480+50*i&&p.x<=520+50*i&&p.y>=90&&p.y<=105){
						ClassData[select[mode]][2]&=0xFC;
						ClassData[select[mode]][2]|=i;
					}
				}

				for(i=0;i<4;i++){
					if(p.x>=480+50*i&&p.x<=520+50*i&&p.y>=106&&p.y<=121){
						ClassData[select[mode]][3]&=0x3F;
						ClassData[select[mode]][3]|=i*64;
					}
				}

				for(i=0;i<4;i++){
					if(p.x>=480+50*i&&p.x<=520+50*i&&p.y>=122&&p.y<=137){
						ClassData[select[mode]][3]&=0xCF;
						ClassData[select[mode]][3]|=i*16;
					}
				}

				for(i=0;i<4;i++){
					if(p.x>=480+50*i&&p.x<=520+50*i&&p.y>=138&&p.y<=153){
						ClassData[select[mode]][3]&=0xF3;
						ClassData[select[mode]][3]|=i*4;
					}
				}

				for(i=0;i<4;i++){
					if(p.x>=480+50*i&&p.x<=520+50*i&&p.y>=154&&p.y<=169){
						ClassData[select[mode]][3]&=0xFC;
						ClassData[select[mode]][3]|=i;
					}
				}

				for(i=7;i>=6;i--){
					if(p.x>=740&&p.x<=755&&p.y>=188+16*(7-i)&&p.y<=203+16*(7-i)){
						ClassData[select[mode]][4]^=(1<<i);
					}
				}

				if (p.x >= 400 && p.x <= 413 && p.y >= 513 && p.y <= 526) {
					if (NumClasses == 32) {
						NumClasses = 64;
						ExtendEquip = true;

						for (i = 0;i < NumMonsters;i++) {
							Monster[i][2]+=32;
						}

						for (i = 209; i >= 64; i--) {
							for (j = 0;j < 8;j++) {
								ClassData[i][j] = ClassData[i - 32][j];
							}
						}
						for (i = 32; i < 64; i++) {
							for (j = 0;j < 8;j++) {
								ClassData[i][j] = 0;
							}
						}

						if (submode[mode] == 1) {
							select[mode] += 32;
						}

					} else {
						NumClasses = 32;
						ExtendEquip = false;

						for (i = 0;i < NumMonsters;i++) {
							Monster[i][2] -= 32;
						}

						for (i = 32; i < 210-32; i++) {
							for (j = 0;j < 8;j++) {
								ClassData[i][j] = ClassData[i + 32][j];
							}
						}

						if (submode[mode] == 0) {
							select[mode] %= 32;
						}
						if (submode[mode] == 1) {
							select[mode] -= 32;
						}
					}
				}

				if (submode[mode] == 0) {
					int healerX = 600;  // same x coordinate as in ClassPaint.h
					int healerY = 440;
					int lineHeight = 20;

					// Click Checks
					if (p.x >= healerX + 130 && p.x <= healerX + 210) {
						if (p.y >= healerY && p.y < healerY + lineHeight) {
							// Healer Class 1 clicked
							HealerClasses[0] = (HealerClasses[0] + 1) % NumClasses;
							return 0;
						}
						else if (p.y >= healerY + lineHeight && p.y < healerY + 2 * lineHeight) {
							// Healer Class 2 clicked
							HealerClasses[1] = (HealerClasses[1] + 1) % NumClasses;
							return 0;
						}
						else if (p.y >= healerY + 2 * lineHeight && p.y < healerY + 3 * lineHeight) {
							// Healer Class 3 clicked
							HealerClasses[2] = (HealerClasses[2] + 1) % NumClasses;
							return 0;
						}
						else if (p.y >= healerY + 3 * lineHeight && p.y < healerY + 4 * lineHeight) {
							// Healer Class 4 clicked
							HealerClasses[3] = (HealerClasses[3] + 1) % NumClasses;
							return 0;
						}
					}
				}