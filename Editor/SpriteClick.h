
				if(p.x>=26&&p.x<=95&&p.y>=10&&p.y<=25){
					focus=1;
				}

				if(p.x>=5&&p.x<=25&&p.y>=8&&p.y<=28){
					select[mode]--;
					if(select[mode]<0)select[mode]=53;
				}

				if(p.x>=96&&p.x<=116&&p.y>=8&&p.y<=28){
					select[mode]++;
					if(select[mode]>53)select[mode]=0;
				}


				for(i=0;i<NumSprites[select[mode]];i++){
					for(j=0;j<6;j++){
						if(p.x>=240+80*j&&p.x<310+80*j&&p.y>=i*16+26&&p.y<i*16+42){
							focus=2+i*6+j;
						}
					}
				}