			if(menu==1){

				if(NumItems==128)
				if(p.x>=470&&p.x<=483&&p.y>=28+16*submenu&&p.y<=41+16*submenu){
					ShopItems[select[mode]][submenu]^=0x40;
					return 0;
				}

				for(i=0;i<16;i++){
					for(j=0;j<4;j++){
						if(p.x>=244+115*j&&p.x<=358+115*j&&p.y>=45+16*i+(submenu)*16&&p.y<=60+16*i+(submenu)*16){
							if(j==3&&i==15){
								return 0;
							}
							if(NumItems==128){
								ShopItems[select[mode]][submenu]&=0x40;
								ShopItems[select[mode]][submenu]|=i+j*16;
							} else {
								ShopItems[select[mode]][submenu]=i+j*16;
							}
							menu=0;
							return 0;
						}
					}
				}
				menu=0;
			}

			for(i=0;i<30;i++){
				if(p.x>=140&&p.x<=200&&p.y>=i*16+10&&p.y<=i*16+25){
					select[mode]=i;
				}
			}

			for(i=0;i<32;i++){
				if(p.x>=270&&p.x<=300&&p.y>=i*16+26&&p.y<=i*16+41){
					focus=1;
					subfocus=i;
				}
			}

			if(p.x>=470&&p.x<=484&&p.y>=26&&p.y<=40){
				ShopTypes[select[mode]]=0;
			}

			if(p.x>=440&&p.x<=460&&p.y>=10&&p.y<30){
				ShopOffset=0x1C0266;
				for(j=0;j<32;j++){
					if(ShopItems[select[mode]][j]==-1)break;
				}
				if(j<32)ShopItems[select[mode]][j]=0;
			}
			if(p.x>=440&&p.x<=460&&p.y>=30&&p.y<50){
				for(j=0;j<32;j++){
					if(ShopItems[select[mode]][j]==-1)break;
				}
				if(j>0)ShopItems[select[mode]][j-1]=-1;
			}

			if(p.x>=470&&p.x<=484&&p.y>=42&&p.y<=56){
				ShopTypes[select[mode]]=1;
			}

			for(i=0;i<32;i++){
				if(ShopItems[select[mode]][i]!=-1){
					if(p.x>=239&&p.x<=259&&p.y>=i*16+26&&p.y<=i*16+46){
						menu=1;
						submenu=i;
					}
				}
			}