			c=wParam;
			if(focus==1){
				val=c-'0';
				if(val>=0&&val<10){
					i=select[mode];
					if(i<10){
						i*=10;
						i+=val;
						select[mode]=i;
					}
				}
				if(c==8){
					i=select[mode];
					i=i-i%10;
					i/=10;
					select[mode]=i;
				}
				select[mode]%=54;
			}
			if(focus>1&&focus<2+NumSprites[select[mode]]*6){
				val=c-'0';
				if(val>=0&&val<10){
					i=Sprites[select[mode]][((focus-2)-(focus-2)%6)/6][(focus-2)%6];
					if(i<100){
						i*=10;
						i+=val;
						Sprites[select[mode]][((focus-2)-(focus-2)%6)/6][(focus-2)%6]=i;
					}
				}
				if(c==8){
					i=Sprites[select[mode]][((focus-2)-(focus-2)%6)/6][(focus-2)%6];
					i=i-i%10;
					i/=10;
					Sprites[select[mode]][((focus-2)-(focus-2)%6)/6][(focus-2)%6]=i;
				}
			}
