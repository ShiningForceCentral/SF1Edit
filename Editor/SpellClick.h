			if(menu){
				switch(menu){
					case 1://range
					case 2://range
					case 3://range
					case 4://range
						if(p.x>=435+(menu-1)%2*200&&p.x<=580+(menu-1)%2*200&&p.y>=45+(menu-1)/2*125&&p.y<=385+(menu-1)/2*125){
							i=(p.y-(45+(menu-1)/2*125))/16;
							Spell[select[mode]][0+(menu-1)*4]=RangeVals[i]+16;
						}
						break;
					case 5://AI
						for(i=0;i<11;i++){
							if(p.x>=483&&p.x<=675&&p.y>=270+20*i&&p.y<=290+20*i){
								switch(i){
									case 0:
										SpellTargeting[select[mode]] = 0x24378 - 0x2409C - 2*select[mode];
										break;
									case 1:
										SpellTargeting[select[mode]] = 0x24386 - 0x2409C - 2*select[mode];
										break;
									case 2:
										SpellTargeting[select[mode]] = 0x244CA - 0x2409C - 2*select[mode];
										break;
									case 3:
										SpellTargeting[select[mode]] = 0x244F0 - 0x2409C - 2*select[mode];
										break;
									case 4:
										SpellTargeting[select[mode]] = 0x24516 - 0x2409C - 2*select[mode];
										break;
									case 5:
										SpellTargeting[select[mode]] = 0x2453E - 0x2409C - 2*select[mode];
										break;
									case 6:
										SpellTargeting[select[mode]] = 0x24544 - 0x2409C - 2*select[mode];
										break;
									case 7:
										SpellTargeting[select[mode]] = 0x2454A - 0x2409C - 2*select[mode];
										break;
									case 8:
										SpellTargeting[select[mode]] = 0x24550 - 0x2409C - 2*select[mode];
										break;
									case 9:
										SpellTargeting[select[mode]] = 0x24556 - 0x2409C - 2*select[mode];
										break;
									case 10:
										SpellTargeting[select[mode]] = 0x2455C - 0x2409C - 2*select[mode];
										break;

								}
							}
						}
						break;
				}
				menu=0;
				return 0;
			}


			for(i=0;i<16+16*ExpandSpells;i++){
				if(p.x>=30&&p.x<=149&&p.y>=i*16+10&&p.y<=i*16+25){
					focus=1;
					select[mode]=i;
				}
			}


			if(p.x>=485&&p.x<=585&&p.y>=270&&p.y<=290){
				menu=5;
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
								if(Pencil)SpellImages[select[mode]][(j+dy)*16+i+dx]=color;
								else SpellImages[select[mode]][(j+dy)*16+i+dx]=0;
							}
						}
					}
				}
			}

			for(i=0;i<4;i++){

				if(p.x>=414+(i%2)*200&&p.x<=434+(i%2)*200&&p.y>=44+(i/2)*141-16&&p.y<=60+(i/2)*141-16){
					menu=i+1;
				}

				for(j=0;j<4;j++){
					if(p.x>=485+(i%2)*200&&p.x<=510+(i%2)*200&&p.y>=45+(i/2)*141-16+16*j&&p.y<=60+(i/2)*141-16+16*j){
						focus=j+2;
						subfocus=i;
					}
				}
			}

			if(p.x>=300&&p.x<=315&&p.y>=11&&p.y<=25){
				if(ExpandSpells){
					SpellNameOffset = 0x26404;
					SpellOffset = 0x26466;
					SpellImagesOffset = 0xCF0EA;
				} else {
					SpellNameOffset = 0x180B40;
					SpellOffset = 0x180C60;
					SpellImagesOffset = 0x180E80;
				}
				ExpandSpells=!ExpandSpells;
			}