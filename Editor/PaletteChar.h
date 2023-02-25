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
		select[mode]%=50;
	}
	if(focus==2){
		val=c-'0';
		if(val>=0&&val<10){
			i=submode[mode];
			if(i<10 || (val<100 && NumItems == 128)){
				i*=10;
				i+=val;
				submode[mode]=i;
			}
		}
		if(c==8){
			i=submode[mode];
			i=i-i%10;
			i/=10;
			submode[mode]=i;
		}
		if (NumItems == 128) {
			submode[mode] %= 128;
		} else {
			submode[mode] %= 63;
		}
	}
	if(focus==3){
		val=c-'0';
		if(val>=0&&val<10){
			i=subselect[mode][focus-3];
			if(i<10){
				i*=10;
				i+=val;
				subselect[mode][focus-3]=i;
			}
		}
		if(c==8){
			i=subselect[mode][focus-3];
			i=i-i%10;
			i/=10;
			subselect[mode][focus-3]=i;
		}
		subselect[mode][focus-3]%=27;
	}
	if(focus==4){
		val=c-'0';
		if(val>=0&&val<10){
			i=subselect[mode][focus-3];
			if(i<10){
				i*=10;
				i+=val;
				subselect[mode][focus-3]=i;
			}
		}
		if(c==8){
			i=subselect[mode][focus-3];
			i=i-i%10;
			i/=10;
			subselect[mode][focus-3]=i;
		}
		subselect[mode][focus-3]%=NumGFX[0];
	}
	if (focus == 5) {
		val = c - '0';
		if (val >= 0 && val<10) {
			i = subselect[mode][focus - 3];
			if (i<10) {
				i *= 10;
				i += val;
				subselect[mode][focus - 3] = i;
			}
		}
		if (c == 8) {
			i = subselect[mode][focus - 3];
			i = i - i % 10;
			i /= 10;
			subselect[mode][focus - 3] = i;
		}
		subselect[mode][focus - 3] %= NumGFX[3];
	}