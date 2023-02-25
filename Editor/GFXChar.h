	c=wParam;

	if(focus==1){
		val=c-'0';
		if(val>=0&&val<10){
			i=subselect[mode][submode[mode]];
			if(i<100){
				i*=10;
				i+=val;
				subselect[mode][submode[mode]]=i;
			}
		}
		if(c==8){
			i=subselect[mode][submode[mode]];
			i=i-i%10;
			i/=10;
			subselect[mode][submode[mode]]=i;
		}
		subselect[mode][submode[mode]]%=NumGFX[submode[mode]];
		subselect[mode][submode[mode]+32]=0;
		subselect[mode][submode[mode]+64]=0;
		if(submode[mode]==2)subselect[mode][submode[mode]+64]=findWSPalette(subselect[mode][submode[mode]]);
	}
	if(focus==2){
		val=c-'0';
		if(val>=0&&val<10){
			i=subselect[mode][submode[mode]+32];
			if(i<10){
				i*=10;
				i+=val;
				subselect[mode][submode[mode]+32]=i;
			}
		}
		if(c==8){
			i=subselect[mode][submode[mode]+32];
			i=i-i%10;
			i/=10;
			subselect[mode][submode[mode]+32]=i;
		}
		subselect[mode][submode[mode]+32]%=NumFSFrame[subselect[mode][submode[mode]]];
	}
	if(focus==3){
		val=c-'0';
		if(val>=0&&val<10){
			i=subselect[mode][submode[mode]+64];
			if(i<10){
				i*=10;
				i+=val;
				subselect[mode][submode[mode]+64]=i;
			}
		}
		if(c==8){
			i=subselect[mode][submode[mode]+64];
			i=i-i%10;
			i/=10;
			subselect[mode][submode[mode]+64]=i;
		}
		switch(submode[mode]){
			case 0:
				subselect[mode][submode[mode]+64]%=NumFSPalette[subselect[mode][submode[mode]]];
				break;
			case 1:
				subselect[mode][submode[mode]+64]%=NumESPalette[subselect[mode][submode[mode]]];
				break;
			case 2:
				subselect[mode][submode[mode]+64]%=NumItems;
				break;
		}
	}

	if (subselect[mode][submode[mode] + 96]) {
		int dx, dy, sx, sy;

		l = 0;
		int t = POData[subselect[mode][submode[mode]]][l++] * 256;
		t += POData[subselect[mode][submode[mode]]][l++];
		for (i = 0;i < t;i++) {
			if (i == subselect[mode][submode[mode] + 128]) {
				dx = POData[subselect[mode][submode[mode]]][l++];
				dy = POData[subselect[mode][submode[mode]]][l++];
				sx = POData[subselect[mode][submode[mode]]][l++];
				sy = POData[subselect[mode][submode[mode]]][l++];

				sx = NtoX(sy);
				sy = NtoY(sy);
			} else {
				l += 4;
			}
		}
		if (subselect[mode][submode[mode] + 96] == 2) {
			t = POData[subselect[mode][submode[mode]]][l++] * 256;
			t += POData[subselect[mode][submode[mode]]][l++];
			for (i = 0;i < t;i++) {
				if (i == subselect[mode][submode[mode] + 128]) {
					dx = POData[subselect[mode][submode[mode]]][l++];
					dy = POData[subselect[mode][submode[mode]]][l++];
					sx = POData[subselect[mode][submode[mode]]][l++];
					sy = POData[subselect[mode][submode[mode]]][l++];

					sx = NtoX(sy);
					sy = NtoY(sy);
				} else {
					l += 4;
				}
			}
		}

		if (focus == 4) {
			val = c - '0';
			if (val >= 0 && val < 10) {
				i = sx;
				if (i < 10) {
					i *= 10;
					i += val;
					sx = i;
				}
			}
			if (c == 8) {
				i = sx;
				i = i - i % 10;
				i /= 10;
				sx = i;
			}
			sx %= 8;
		}

		if (focus == 5) {
			val = c - '0';
			if (val >= 0 && val < 10) {
				i = sy;
				if (i < 10) {
					i *= 10;
					i += val;
					sy = i;
				}
			}
			if (c == 8) {
				i = sy;
				i = i - i % 10;
				i /= 10;
				sy = i;
			}
			sy %= 8;
		}

		if (focus == 6) {
			val = c - '0';
			if (val >= 0 && val < 10) {
				i = dx;
				if (i < 10) {
					i *= 10;
					i += val;
					dx = i;
				}
			}
			if (c == 8) {
				i = dx;
				i = i - i % 10;
				i /= 10;
				dx = i;
			}
			dx %= 8;
		}

		if (focus == 7) {
			val = c - '0';
			if (val >= 0 && val < 10) {
				i = dy;
				if (i < 10) {
					i *= 10;
					i += val;
					dy = i;
				}
			}
			if (c == 8) {
				i = dy;
				i = i - i % 10;
				i /= 10;
				dy = i;
			}
			dy %= 8;
		}
		l = 0;
		t = POData[subselect[mode][submode[mode]]][l++] * 256;
		t += POData[subselect[mode][submode[mode]]][l++];
		for (i = 0;i < t;i++) {
			if (i == subselect[mode][submode[mode] + 128] && subselect[mode][submode[mode] + 96] == 1) {
				POData[subselect[mode][submode[mode]]][l++] = dx;
				POData[subselect[mode][submode[mode]]][l++] = dy;
				POData[subselect[mode][submode[mode]]][l++] = 0;
				POData[subselect[mode][submode[mode]]][l++] = CtoN(sx,sy);
			} else {
				l += 4;
			}
		}
		if (subselect[mode][submode[mode] + 96] == 2) {
			t = POData[subselect[mode][submode[mode]]][l++] * 256;
			t += POData[subselect[mode][submode[mode]]][l++];
			for (i = 0;i < t;i++) {
				if (i == subselect[mode][submode[mode] + 128]) {
					POData[subselect[mode][submode[mode]]][l++] = dx;
					POData[subselect[mode][submode[mode]]][l++] = dy;
					POData[subselect[mode][submode[mode]]][l++] = 0;
					POData[subselect[mode][submode[mode]]][l++] = CtoN(sx, sy);
				} else {
					l += 4;
				}
			}
		}
	}

	if (focus == 8) {
		val = c - '0';
		if (val >= 0 && val < 10) {
			i = MSTextSound[subselect[mode][submode[mode]]];
			if (i < 100) {
				i *= 10;
				i += val;
				MSTextSound[subselect[mode][submode[mode]]] = i;
			}
		}
		if (c == 8) {
			i = MSTextSound[subselect[mode][submode[mode]]];
			i = i - i % 10;
			i /= 10;
			MSTextSound[subselect[mode][submode[mode]]] = i;
		}
	}