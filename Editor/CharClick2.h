				if(menu>0){
					for(i=0;i<16+16*ExpandSpells;i++){
						for(j=0;j<4;j++){
							if(!ExpandSpells){
								if(p.x>=345+75*j&&p.x<=419+75*j&&p.y>=44+16*i+(menu-1)*16&&p.y<=59+16*i+(menu-1)*16){
									Learn[select[mode]][menu-1][1]=i+j*64;
									menu=0;
									return 0;
								}
							} else {
								if(p.x>=345+75*j&&p.x<=419+75*j&&p.y>=44+15*i&&p.y<=59+15*i){
									Learn[select[mode]][menu-1][1]=i+j*64;
									menu=0;
									return 0;
								}
							}
						}
					}
					menu=0;
				}

				int q;
				q = 30;
				if (CharView + q > NumChars) q = NumChars - CharView;

				for (i = 0; i<q; i++) {
					if (p.x >= 30 && p.x <= 149 && p.y >= i * 16 + 10 && p.y <= i * 16 + 25) {
						focus = 1;
						select[mode] = i + CharView;
					}
				}

				for(i=0;i<q;i++){

					if (NumLearn[select[mode]]>i && p.x >= 270 && p.x <= 289 && p.y >= i * 16 + 42 && p.y <= i * 16 + 57) {
						NumLearn[select[mode]]--;
						for (int j = i; j < NumLearn[select[mode]]; j++) {
							Learn[select[mode]][j][0] = Learn[select[mode]][j + 1][0];
							Learn[select[mode]][j][1] = Learn[select[mode]][j + 1][1];
						}
					}

					if(p.x>=290&&p.x<=339&&p.y>=i*16+42&&p.y<=i*16+57){
						focus=2;
						subfocus=i;
					}
					if(p.x>=340&&p.x<=360&&p.y>=i*16+42&&p.y<=i*16+57){
						menu=i+1;
					}
					if(p.x>=365&&p.x<=435&&p.y>=i*16+42&&p.y<=i*16+57){
						focus=3;
						subfocus=i;
					}
				}


				if (NumChars == MAX_CHARS) {
					if (p.x >= 20 && p.x <= 40 && p.y >= 520 && p.y <= 540) {
						CharView += 30;
						CharView %= 60;
						select[mode] += 30;
						select[mode] %= 60;
					}
					if (p.x >= 43 && p.x <= 63 && p.y >= 520 && p.y <= 540) {
						CharView += 30;
						CharView %= 60;
						select[mode] += 30;
						select[mode] %= 60;
					}
				}


				if(p.x>=260&&p.x<=280&&p.y>=14&&p.y<=34&&((select[mode]>=0&&select[mode]<30)||NumChars>30)){
					NumLearn[select[mode]]++;
					focus=2;
					subfocus=NumLearn[select[mode]]-1;
					Learn[select[mode]][subfocus][0]=0;
					Learn[select[mode]][subfocus][1]=0;
					LearnAdded=true;
				}
				if(p.x>=535&&p.x<=600&&p.y>=10&&p.y<=26){
					focus=4;
				}
