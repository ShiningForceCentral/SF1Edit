switch (subselect[mode][7]) {
	case 0:
		if (focus == 1) {
			val = c - '0';
			if (val >= 0 && val<10) {
				i = subselect[mode][1];
				if (i<100) {
					i *= 10;
					i += val;
					subselect[mode][1] = i;
				}
			}
			if (c == 8) {
				i = subselect[mode][1];
				i = i - i % 10;
				i /= 10;
				subselect[mode][1] = i;
			}
			subselect[mode][1] %= NumGFX[0];
			TempPalReady = false;
		}
		if (focus == 2) {
			val = c - '0';
			if (val >= 0 && val<10) {
				i = subselect[mode][3];
				if (i<100) {
					i *= 10;
					i += val;
					subselect[mode][3] = i;
				}
			}
			if (c == 8) {
				i = subselect[mode][3];
				i = i - i % 10;
				i /= 10;
				subselect[mode][3] = i;
			}
			subselect[mode][3] %= NumGFX[1];
			TempPalReady = false;
		}
		if (focus == 3) {
			val = c - '0';
			if (val >= 0 && val<10) {
				i = subselect[mode][4];
				if (i<100) {
					i *= 10;
					i += val;
					subselect[mode][4] = i;
				}
			}
			if (c == 8) {
				i = subselect[mode][4];
				i = i - i % 10;
				i /= 10;
				subselect[mode][4] = i;
			}
			subselect[mode][4] %= NumGFX[4];
			TempPalReady = false;
		}
		if (focus == 4) {
			val = c - '0';
			if (val >= 0 && val<10) {
				i = subselect[mode][5];
				if (i<100) {
					i *= 10;
					i += val;
					subselect[mode][5] = i;
				}
			}
			if (c == 8) {
				i = subselect[mode][5];
				i = i - i % 10;
				i /= 10;
				subselect[mode][5] = i;
			}
			subselect[mode][5] %= (NumGFX[3]) / 2;
			TempPalReady = false;
		}
		if (focus == 5) {
			val = c - '0';
			if (val >= 0 && val<10) {
				i = subselect[mode][6];
				if (i<100) {
					i *= 10;
					i += val;
					subselect[mode][6] = i;
				}
			}
			if (c == 8) {
				i = subselect[mode][6];
				i = i - i % 10;
				i /= 10;
				subselect[mode][6] = i;
			}
			subselect[mode][6] %= (NumGFX[3]) / 2;
			TempPalReady = false;
		}
		break;
	case 1:
		if (focus == 1) {
			val = c - '0';
			if (val >= 0 && val<10) {
				i = PaletteScript[select[mode]][subfocus][2];
				if (i<100) {
					i *= 10;
					i += val;
					PaletteScript[select[mode]][subfocus][2] = i;
				}
			}
			if (c == 8) {
				i = PaletteScript[select[mode]][subfocus][2];
				i = i - i % 10;
				i /= 10;
				PaletteScript[select[mode]][subfocus][2] = i;
			}
			TempPalReady = false;
		}
		break;
	case 2:
		if (focus == 1) {
			val = c - '0';
			if (val >= 0 && val<10) {
				i = subselect[mode][9];
				if (i<100) {
					i *= 10;
					i += val;
					subselect[mode][9] = i;
				}
			}
			if (c == 8) {
				i = subselect[mode][9];
				i = i - i % 10;
				i /= 10;
				subselect[mode][9] = i;
			}
			subselect[mode][9] %= NumAnimGFX[select[mode]];
		}
		if (focus == 2) {
			val = c - '0';
			if (val >= 0 && val<10) {
				i = AnimGFX[select[mode]][subselect[mode][9]][0];
				if (i<100) {
					i *= 10;
					if (i<0 || editneg)i -= val;
					else i += val;
					AnimGFX[select[mode]][subselect[mode][9]][0] = i;
				}
			}
			if (c == 8) {
				i = AnimGFX[select[mode]][subselect[mode][9]][0];
				i = i - i % 10;
				i /= 10;
				AnimGFX[select[mode]][subselect[mode][9]][0] = i;
			}
			if (c == '-') {
				if (AnimGFX[select[mode]][subselect[mode][9]][0]) {
					AnimGFX[select[mode]][subselect[mode][9]][0] *= -1;
				} else {
					editneg = true;
				}
			}
		}
		if (focus == 3) {
			val = c - '0';
			if (val >= 0 && val<10) {
				i = AnimGFX[select[mode]][subselect[mode][9]][1];
				if (i<100) {
					i *= 10;
					if (i<0 || editneg)i -= val;
					else i += val;
					AnimGFX[select[mode]][subselect[mode][9]][1] = i;
				}
			}
			if (c == 8) {
				i = AnimGFX[select[mode]][subselect[mode][9]][1];
				i = i - i % 10;
				i /= 10;
				AnimGFX[select[mode]][subselect[mode][9]][1] = i;
			}
			if (c == '-') {
				if (AnimGFX[select[mode]][subselect[mode][9]][1]) {
					AnimGFX[select[mode]][subselect[mode][9]][1] *= -1;
				} else {
					editneg = true;
				}
			}
		}
		if (focus == 4) {
			val = c - '0';
			if (val >= 0 && val<10) {
				i = (unsigned char)AnimGFX[select[mode]][subselect[mode][9]][2];
				if (i<100) {
					i *= 10;
					i += val;
					AnimGFX[select[mode]][subselect[mode][9]][2] = i;
				}
			}
			if (c == 8) {
				i = (unsigned char)AnimGFX[select[mode]][subselect[mode][9]][2];
				i = i - i % 10;
				i /= 10;
				AnimGFX[select[mode]][subselect[mode][9]][2] = i;
			}
		}

		if (focus == 5) {
			val = c - '0';
			if (val > 0 && val<5) {
				AnimGFX[select[mode]][subselect[mode][9]][3] &=0xFC;
				AnimGFX[select[mode]][subselect[mode][9]][3] |= val-1;
			}
		}
		if (focus == 6) {
			val = c - '0';
			if (val > 0 && val<5) {
				AnimGFX[select[mode]][subselect[mode][9]][3] &= 0xF3;
				AnimGFX[select[mode]][subselect[mode][9]][3] |= (val-1)*4;
			}
		}

		break;
}
