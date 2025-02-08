				if(submode[mode]==0){
					SelectObject(bmpdc,charaon);
				} else {
					SelectObject(bmpdc,chara);
				}
				BitBlt(memdc,0,10,40,40,bmpdc,0,0,SRCCOPY);
				if(submode[mode]==1){
					SelectObject(bmpdc,monsteron);
				} else {
					SelectObject(bmpdc,monster);
				}
				BitBlt(memdc,0,50,40,40,bmpdc,0,0,SRCCOPY);

				if(submode[mode]==0){
					Rectangle(memdc,50,10+16*(select[mode]%32),50+120,10+16*(select[mode]%32)+16);

					for(i=0;i<32;i++){
						if(i==select[mode]&&focus==1&&cursor){
							sprintf(out,"%s|",Classes[i + subselect[mode][0]]);
							TextOut(memdc,50,i*16+10,out,strlen(out));
						} else {
							TextOut(memdc,50,i*16+10,Classes[i + subselect[mode][0]],strlen(Classes[i + subselect[mode][0]]));
						}
					}

					if (NumClasses == 64) {
						SelectObject(bmpdc, uparrow);
						BitBlt(memdc, 200, 520, 20, 20, bmpdc, 0, 0, SRCCOPY);
						SelectObject(bmpdc, downarrow);
						BitBlt(memdc, 223, 520, 20, 20, bmpdc, 0, 0, SRCCOPY);
						SelectObject(bmpdc, checkon);
					}
				} else {
					Rectangle(memdc,50+150*((select[mode]-NumClasses)%73/37),5+14*((select[mode]- NumClasses)%73%37),50+150*((select[mode]- NumClasses)%73/37)+120,5+14*((select[mode]- NumClasses)%73%37)+16);

					for(i=0;i<37;i++){
						TextOut(memdc,50,i*14+5,MonsterName[i+MonsterView],strlen(MonsterName[i+MonsterView]));
					}
					for(i=37;i<73;i++){
						TextOut(memdc,200,(i-37)*14+5,MonsterName[i+MonsterView],strlen(MonsterName[i+MonsterView]));
					}

					if(NumMonsters==146){
						SelectObject(bmpdc,uparrow);
						BitBlt(memdc,200,520,20,20,bmpdc,0,0,SRCCOPY);
						SelectObject(bmpdc,downarrow);
						BitBlt(memdc,223,520,20,20,bmpdc,0,0,SRCCOPY);
						SelectObject(bmpdc,checkon);
					}
				}
				TextOut(memdc,400,184,"Movement Type:",14);
				TextOut(memdc,400,204,"Action Type:",12);
				TextOut(memdc,400,224,"Action Chance:", 14);

				SelectObject(bmpdc,dots);
				BitBlt(memdc,380,265,20,20,bmpdc,0,0,SRCCOPY);
				TextOut(memdc,400,266,"Unarmed Range:",14);
				TextOut(memdc,400,282,"Unarmed Attack:",15);
				TextOut(memdc,400,324,"Special Attack:",15);
				TextOut(memdc,400,344,"Special Chance:", 15);



				if (NumClasses == 64) {

					if (submode[mode] == 0) {
						SelectObject(bmpdc, dots);
						BitBlt(memdc, 380, 461, 20, 20, bmpdc, 0, 0, SRCCOPY);
						TextOut(memdc, 400, 462, "Promoted Class:", 15);

						if (ClassPromote[select[mode]] == 0xFF) {
							TextOut(memdc, 535, 462, "None", 4);
						} else {
							TextOut(memdc, 535, 462, Classes[ClassPromote[select[mode]]], strlen(Classes[ClassPromote[select[mode]]]));
						}
					}


					SelectObject(bmpdc, checkon);
				} else SelectObject(bmpdc, checkoff);

				TextOut(memdc, 423, 512, "Extend Classes", 14);
				BitBlt(memdc, 400, 513, 13, 13, bmpdc, 0, 0, SRCCOPY);



				HBRUSH tb;
				tb = (HBRUSH)SelectObject(memdc, CreateSolidBrush(RGB(180, 180, 180)));
				RoundRect(memdc, 515, 182, 615, 202, 10, 10);
				RoundRect(memdc, 515, 202, 639, 222, 10, 10);
				RoundRect(memdc, 515, 222, 615, 242, 10, 10);

				RoundRect(memdc, 515, 322, 647, 342, 10, 10);
				RoundRect(memdc, 515, 342, 615, 362, 10, 10);
				if (FixDoubles)RoundRect(memdc, 515, 422, 615, 442, 10, 10);

				DeleteObject(SelectObject(memdc, tb));

				if (ClassData[select[mode]][0] > 0 && ClassData[select[mode]][0] < 8) {
					sprintf(out, "%s", ClassMovements[ClassData[select[mode]][0]] );
					TextOut(memdc, 521, 184, out, strlen(out));
				}



				ClassAction = 255;

				switch (ClassData[select[mode]][1]) {
					case 255:
						ClassAction = 0;
						break;
					case 128:
						ClassAction = 1;
						break;
					case 130:
						ClassAction = 2;
						break;
					case 0:
					case 1:
					case 2:
					case 3:
					case 4:
					case 5:
					case 6:
					case 7:
					case 8:
					case 9:
					case 10:
						ClassAction = ClassData[select[mode]][1] +3;
						break;
					case 131:
						ClassAction = 14;
						break;
				}

				if (ClassAction != 255) {
					sprintf(out, "%s", ClassActions[ClassAction]);
					TextOut(memdc, 521, 204, out, strlen(out));
				}

				ActionChance = (ClassData[select[mode]][4] & 0x30) / 16;

				sprintf(out, "%s", ActionChances[ActionChance]);
				TextOut(memdc, 521, 224, out, strlen(out));

				SpecialChance = (ClassData[select[mode]][4] & 0x03);

				sprintf(out, "%s", SpecialChances[SpecialChance]);
				TextOut(memdc, 521, 344, out, strlen(out));

				for (i = 5; i<7; i++) {
					sprintf(out, "%d", ClassData[select[mode]][i]);
					if (focus == 2 + i&&cursor) {
						sprintf(out, "%s|", out);
					}
					TextOut(memdc, 515, i * 16 + 186, out, strlen(out));
				}
				if (ClassData[select[mode]][7] == 255)ClassSpecial = 0;
				else ClassSpecial = ClassData[select[mode]][7] + 1;
				

				if (ClassSpecial < 10) {
					sprintf(out, "%s", SpecialAttacks[ClassSpecial]);
					TextOut(memdc, 521, 324, out, strlen(out));
				}

				if(submode[mode]==0){
					TextOut(memdc,400,382,"AI Target Priority:",19);

					sprintf(out,"%d",Priority0[select[mode]]);
					if(focus==12&&cursor){
						sprintf(out,"%s|",out);
					}
					TextOut(memdc,535,382,out,strlen(out));
				}

				if (FixDoubles) {
					TextOut(memdc, 400, 424, "Double Attacks:", 15);

					int q = (ClassData[select[mode]][4] & 0x0C) / 4;

					sprintf(out, "%s", DoubleChances[q]);
					TextOut(memdc, 521, 424, out, strlen(out));
				}

				TextOut(memdc,646,186,"Regenerate:",11);
				TextOut(memdc,646,202,"Undefined:",10);
				//TextOut(memdc,646,218,"?:",2);
				//TextOut(memdc,646,234,"?:",2);
				//TextOut(memdc,646,250,"?:",2);
				//TextOut(memdc,646,266,"?:",2);
				//TextOut(memdc,646,282,"Special Attack:",15);
				//TextOut(memdc,646,298,"?:",2);

				for(i=7;i>=6;i--){
					if(ClassData[select[mode]][4]&(1<<i))SelectObject(bmpdc,checkon);
					else SelectObject(bmpdc,checkoff);
					BitBlt(memdc,740,188+16*(7-i),13,13,bmpdc,0,0,SRCCOPY);
				}
				
				TextOut(memdc,540,8,"RESISTANCES",11);
				TextOut(memdc,480,26,"Base",4);
				TextOut(memdc,530,26,"25%",3);
				TextOut(memdc,580,26,"50%",3);
				TextOut(memdc,630,26,"25% Weakness",12);
				TextOut(memdc,380,42,"Evasion",7);
				TextOut(memdc,380,58,"Undefined",9);
				TextOut(memdc,380,74,"Chaos Breaker",13);
				TextOut(memdc,380,90,"Anti-Air",8);
				TextOut(memdc,380,106,"Sleep/Desoul",12);
				TextOut(memdc,380,122,"Bolt",4);
				TextOut(memdc,380,138,"Freeze",6);
				TextOut(memdc,380,154,"Blaze/Status",12);

				if((ClassData[select[mode]][2]&0xC0)/0x40==0)SelectObject(bmpdc,checkon);
				else SelectObject(bmpdc,checkoff);
				BitBlt(memdc,480,42,13,13,bmpdc,0,0,SRCCOPY);
				if((ClassData[select[mode]][2]&0x30)/0x10==0)SelectObject(bmpdc,checkon);
				else SelectObject(bmpdc,checkoff);
				BitBlt(memdc,480,58,13,13,bmpdc,0,0,SRCCOPY);
				if((ClassData[select[mode]][2]&0x0C)/0x04==0)SelectObject(bmpdc,checkon);
				else SelectObject(bmpdc,checkoff);
				BitBlt(memdc,480,74,13,13,bmpdc,0,0,SRCCOPY);
				if((ClassData[select[mode]][2]&0x03)==0)SelectObject(bmpdc,checkon);
				else SelectObject(bmpdc,checkoff);
				BitBlt(memdc,480,90,13,13,bmpdc,0,0,SRCCOPY);

				if((ClassData[select[mode]][2]&0xC0)/0x40==1)SelectObject(bmpdc,checkon);
				else SelectObject(bmpdc,checkoff);
				BitBlt(memdc,530,42,13,13,bmpdc,0,0,SRCCOPY);
				if((ClassData[select[mode]][2]&0x30)/0x10==1)SelectObject(bmpdc,checkon);
				else SelectObject(bmpdc,checkoff);
				BitBlt(memdc,530,58,13,13,bmpdc,0,0,SRCCOPY);
				if((ClassData[select[mode]][2]&0x0C)/0x04==1)SelectObject(bmpdc,checkon);
				else SelectObject(bmpdc,checkoff);
				BitBlt(memdc,530,74,13,13,bmpdc,0,0,SRCCOPY);
				if((ClassData[select[mode]][2]&0x03)==1)SelectObject(bmpdc,checkon);
				else SelectObject(bmpdc,checkoff);
				BitBlt(memdc,530,90,13,13,bmpdc,0,0,SRCCOPY);

				if((ClassData[select[mode]][2]&0xC0)/0x40==2)SelectObject(bmpdc,checkon);
				else SelectObject(bmpdc,checkoff);
				BitBlt(memdc,580,42,13,13,bmpdc,0,0,SRCCOPY);
				if((ClassData[select[mode]][2]&0x30)/0x10==2)SelectObject(bmpdc,checkon);
				else SelectObject(bmpdc,checkoff);
				BitBlt(memdc,580,58,13,13,bmpdc,0,0,SRCCOPY);
				if((ClassData[select[mode]][2]&0x0C)/0x04==2)SelectObject(bmpdc,checkon);
				else SelectObject(bmpdc,checkoff);
				BitBlt(memdc,580,74,13,13,bmpdc,0,0,SRCCOPY);
				if((ClassData[select[mode]][2]&0x03)==2)SelectObject(bmpdc,checkon);
				else SelectObject(bmpdc,checkoff);
				BitBlt(memdc,580,90,13,13,bmpdc,0,0,SRCCOPY);

				if((ClassData[select[mode]][2]&0xC0)/0x40==3)SelectObject(bmpdc,checkon);
				else SelectObject(bmpdc,checkoff);
				BitBlt(memdc,630,42,13,13,bmpdc,0,0,SRCCOPY);
				if((ClassData[select[mode]][2]&0x30)/0x10==3)SelectObject(bmpdc,checkon);
				else SelectObject(bmpdc,checkoff);
				BitBlt(memdc,630,58,13,13,bmpdc,0,0,SRCCOPY);
				if((ClassData[select[mode]][2]&0x0C)/0x04==3)SelectObject(bmpdc,checkon);
				else SelectObject(bmpdc,checkoff);
				BitBlt(memdc,630,74,13,13,bmpdc,0,0,SRCCOPY);
				if((ClassData[select[mode]][2]&0x03)==3)SelectObject(bmpdc,checkon);
				else SelectObject(bmpdc,checkoff);
				BitBlt(memdc,630,90,13,13,bmpdc,0,0,SRCCOPY);

				if((ClassData[select[mode]][3]&0xC0)/0x40==0)SelectObject(bmpdc,checkon);
				else SelectObject(bmpdc,checkoff);
				BitBlt(memdc,480,106,13,13,bmpdc,0,0,SRCCOPY);
				if((ClassData[select[mode]][3]&0x30)/0x10==0)SelectObject(bmpdc,checkon);
				else SelectObject(bmpdc,checkoff);
				BitBlt(memdc,480,122,13,13,bmpdc,0,0,SRCCOPY);
				if((ClassData[select[mode]][3]&0x0C)/0x04==0)SelectObject(bmpdc,checkon);
				else SelectObject(bmpdc,checkoff);
				BitBlt(memdc,480,138,13,13,bmpdc,0,0,SRCCOPY);
				if((ClassData[select[mode]][3]&0x03)==0)SelectObject(bmpdc,checkon);
				else SelectObject(bmpdc,checkoff);
				BitBlt(memdc,480,154,13,13,bmpdc,0,0,SRCCOPY);

				if((ClassData[select[mode]][3]&0xC0)/0x40==1)SelectObject(bmpdc,checkon);
				else SelectObject(bmpdc,checkoff);
				BitBlt(memdc,530,106,13,13,bmpdc,0,0,SRCCOPY);
				if((ClassData[select[mode]][3]&0x30)/0x10==1)SelectObject(bmpdc,checkon);
				else SelectObject(bmpdc,checkoff);
				BitBlt(memdc,530,122,13,13,bmpdc,0,0,SRCCOPY);
				if((ClassData[select[mode]][3]&0x0C)/0x04==1)SelectObject(bmpdc,checkon);
				else SelectObject(bmpdc,checkoff);
				BitBlt(memdc,530,138,13,13,bmpdc,0,0,SRCCOPY);
				if((ClassData[select[mode]][3]&0x03)==1)SelectObject(bmpdc,checkon);
				else SelectObject(bmpdc,checkoff);
				BitBlt(memdc,530,154,13,13,bmpdc,0,0,SRCCOPY);

				if((ClassData[select[mode]][3]&0xC0)/0x40==2)SelectObject(bmpdc,checkon);
				else SelectObject(bmpdc,checkoff);
				BitBlt(memdc,580,106,13,13,bmpdc,0,0,SRCCOPY);
				if((ClassData[select[mode]][3]&0x30)/0x10==2)SelectObject(bmpdc,checkon);
				else SelectObject(bmpdc,checkoff);
				BitBlt(memdc,580,122,13,13,bmpdc,0,0,SRCCOPY);
				if((ClassData[select[mode]][3]&0x0C)/0x04==2)SelectObject(bmpdc,checkon);
				else SelectObject(bmpdc,checkoff);
				BitBlt(memdc,580,138,13,13,bmpdc,0,0,SRCCOPY);
				if((ClassData[select[mode]][3]&0x03)==2)SelectObject(bmpdc,checkon);
				else SelectObject(bmpdc,checkoff);
				BitBlt(memdc,580,154,13,13,bmpdc,0,0,SRCCOPY);

				if((ClassData[select[mode]][3]&0xC0)/0x40==3)SelectObject(bmpdc,checkon);
				else SelectObject(bmpdc,checkoff);
				BitBlt(memdc,630,106,13,13,bmpdc,0,0,SRCCOPY);
				if((ClassData[select[mode]][3]&0x30)/0x10==3)SelectObject(bmpdc,checkon);
				else SelectObject(bmpdc,checkoff);
				BitBlt(memdc,630,122,13,13,bmpdc,0,0,SRCCOPY);
				if((ClassData[select[mode]][3]&0x0C)/0x04==3)SelectObject(bmpdc,checkon);
				else SelectObject(bmpdc,checkoff);
				BitBlt(memdc,630,138,13,13,bmpdc,0,0,SRCCOPY);
				if((ClassData[select[mode]][3]&0x03)==3)SelectObject(bmpdc,checkon);
				else SelectObject(bmpdc,checkoff);
				BitBlt(memdc,630,154,13,13,bmpdc,0,0,SRCCOPY);

				switch(menu){
					case 1:
						r.top=130;
						r.left=279;
						r.right=425;
						r.bottom=487;
						FillRect(memdc,&r,(HBRUSH)GetStockObject(WHITE_BRUSH));
						for(i=0;i<19;i++){
							sprintf(out,"%s",RangeTypes[i]);
							TextOut(memdc,281,132+16*i,out,strlen(out));
						}
						break;
					case 2:
						tb = (HBRUSH)SelectObject(memdc, CreateSolidBrush(RGB(180, 180, 180)));
						RoundRect(memdc, 515, 182, 615, 182 + 7 * 20, 10, 10);
						DeleteObject(SelectObject(memdc, tb));

						for (int i = 0; i < 7; i++) {
							if (ClassData[select[mode]][0] == i+1) {
								RoundRect(memdc, 515, 182 + i * 20, 615, 202 + i * 20, 10, 10);
							}
							TextOut(memdc, 521, 184 + 20 * i, ClassMovements[i+1], strlen(ClassMovements[i+1]));
						}
						break;
					case 3:
						tb = (HBRUSH)SelectObject(memdc, CreateSolidBrush(RGB(180, 180, 180)));
						RoundRect(memdc, 515, 202, 639, 202 + 15 * 20, 10, 10);
						DeleteObject(SelectObject(memdc, tb));

						for (int i = 0; i < 15; i++) {
							if (ClassAction == i) {
								RoundRect(memdc, 515, 202 + i * 20, 639, 222 + i * 20, 10, 10);
							}
							TextOut(memdc, 521, 204 + 20 * i, ClassActions[i], strlen(ClassActions[i]));
						}
						break;
					case 4:
						tb = (HBRUSH)SelectObject(memdc, CreateSolidBrush(RGB(180, 180, 180)));
						RoundRect(memdc, 515, 222, 639, 222 + 4 * 20, 10, 10);
						DeleteObject(SelectObject(memdc, tb));

						for (int i = 0; i < 4; i++) {
							if (ActionChance == i) {
								RoundRect(memdc, 515, 222 + i * 20, 639, 242 + i * 20, 10, 10);
							}
							TextOut(memdc, 521, 224 + 20 * i, ActionChances[i], strlen(ActionChances[i]));
						}
						break;
					case 5:
						tb = (HBRUSH)SelectObject(memdc, CreateSolidBrush(RGB(180, 180, 180)));
						RoundRect(memdc, 515, 322, 647, 322 + 10 * 20, 10, 10);
						DeleteObject(SelectObject(memdc, tb));

						for (int i = 0; i < 10; i++) {
							if (ClassSpecial == i) {
								RoundRect(memdc, 515, 322 + i * 20, 647, 342 + i * 20, 10, 10);
							}
							TextOut(memdc, 521, 324 + 20 * i, SpecialAttacks[i], strlen(SpecialAttacks[i]));
						}
						break;
					case 6:
						tb = (HBRUSH)SelectObject(memdc, CreateSolidBrush(RGB(180, 180, 180)));
						RoundRect(memdc, 515, 342, 615, 342 + 4 * 20, 10, 10);
						DeleteObject(SelectObject(memdc, tb));

						for (int i = 0; i < 4; i++) {
							if (SpecialChance == i) {
								RoundRect(memdc, 515, 342 + i * 20, 615, 362 + i * 20, 10, 10);
							}
							TextOut(memdc, 521, 344 + 20 * i, SpecialChances[i], strlen(SpecialChances[i]));
						}
						break;
					case 7:
						tb = (HBRUSH)SelectObject(memdc, CreateSolidBrush(RGB(180, 180, 180)));
						RoundRect(memdc, 515, 422, 615, 422 + 4 * 20, 10, 10);
						DeleteObject(SelectObject(memdc, tb));

						for (int i = 0; i < 4; i++) {
							if ((ClassData[select[mode]][4] & 0x0C) == i*4) {
								RoundRect(memdc, 515, 422 + i * 20, 615, 442 + i * 20, 10, 10);
							}
							TextOut(memdc, 521, 424 + 20 * i, DoubleChances[i], strlen(DoubleChances[i]));
						}
						break;
					case 8://class
						r.top = 21;
						r.left = 400;
						r.right = 628;
						r.bottom = 530;
						FillRect(memdc, &r, (HBRUSH)GetStockObject(WHITE_BRUSH));

						TextOut(memdc, 402, 26, "(None)", 6);

						for (i = 0; i<32; i++) {
							sprintf(out, "%s", Classes[i]);
							TextOut(memdc, 402, 43 + 15 * i, out, strlen(out));

							sprintf(out, "%s", Classes[i + 32]);
							TextOut(memdc, 402 + 114, 43 + 15 * i, out, strlen(out));
						}
						break;
				}