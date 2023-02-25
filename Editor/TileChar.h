	c=wParam;
	if(focus==1){
		val=c-'0';
		if(val>=0&&val<10){
			i=select[mode];
			if(i<1000){
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
		select[mode]%=NUM_TILE;
	}

	if(focus==2){
		val=c-'0';
		if(val>=0&&val<10){
			k = (Tiles[select[mode]][subfocus*2]&0x07)*256;
			k += Tiles[select[mode]][subfocus*2+1];
			k -= 0x3BE;
			if(k<1000){
				k*=10;
				k+=val;
				k += 0x3BE;
				Tiles[select[mode]][subfocus*2+1]=k%256;
				k = k-(k%256);
				k = k/256;
				k&=7;
				Tiles[select[mode]][subfocus*2]&=0xF8;
				Tiles[select[mode]][subfocus*2]|=k;
			}
		}
		if(c==8){
			k = (Tiles[select[mode]][subfocus*2]&0x07)*256;
			k += Tiles[select[mode]][subfocus*2+1];
			k -= 0x3BE;
			k=k-k%10;
			k/=10;
			k += 0x3BE;
			Tiles[select[mode]][subfocus*2+1]=k%256;
			k = k-(k%256);
			k = k/256;
			k&=7;
			Tiles[select[mode]][subfocus*2]&=0xF8;
			Tiles[select[mode]][subfocus*2]|=k;
		}
	}

	if(focus==3){
		val=c-'0';
		if(val>=0&&val<10){
			k = Tiles[select[mode]][subfocus*2]&0x60;
			k /= 0x20;
			if(k==0){
				k*=10;
				k+=val;
				k&=3;
				k*=0x20;
				
				Tiles[select[mode]][subfocus*2]&=0x9F;
				Tiles[select[mode]][subfocus*2]|=k;
			}
		}
		if(c==8){
			Tiles[select[mode]][subfocus*2]&=0x9F;
		}
	}
