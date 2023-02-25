
				if(p.x>=121&&p.x<=190&&p.y>=60&&p.y<=75){
					focus=1;
				}

				if(p.x>=100&&p.x<=120&&p.y>=58&&p.y<=78){
					select[mode]--;
					if(select[mode]<0)select[mode]=NUM_TILE-1;
				}

				if(p.x>=191&&p.x<=201&&p.y>=58&&p.y<=78){
					select[mode]++;
					if(select[mode]>NUM_TILE-1)select[mode]=0;
				}

				for(i=0;i<3;i++){
					for(j=0;j<3;j++){

						if(p.x>=300+i*75&&p.x<=350+i*75&&p.y>=66+j*75&&p.y<=82+j*75){
							focus=2;
							subfocus=j*3+i;
						}

						if(p.x>=575+i*75&&p.x<=625+i*75&&p.y>=66+j*75&&p.y<=82+j*75){
							focus=3;
							subfocus=j*3+i;
						}

						if(p.x>=300+i*75&&p.x<=320+i*75&&p.y>=325+j*75&&p.y<=345+j*75){
							Tiles[select[mode]][i*2+j*6]^=0x80;
						}

						if(p.x>=575+i*75&&p.x<=594+i*75&&p.y>=325+j*75&&p.y<=345+j*75){
							Tiles[select[mode]][i*2+j*6]^=0x08;
						}
						if(p.x>=595+i*75&&p.x<=614+i*75&&p.y>=325+j*75&&p.y<=345+j*75){
							Tiles[select[mode]][i*2+j*6]^=0x10;
						}

					}
				}