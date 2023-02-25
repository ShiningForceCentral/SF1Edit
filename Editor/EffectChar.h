if (submode[mode] == 0) {
	switch (focus) {
		case 1:
			c = wParam;
			if (NumEffects) {
				val = c - '0';
				if (val >= 0 && val < 10) {
					i = Effect[select[mode]][3];
					if (i < 100) {
						i *= 10;
						i += val;
						Effect[select[mode]][3] = i;
					}
				}
				if (c == 8) {
					i = Effect[select[mode]][3];
					i = i - i % 10;
					i /= 10;
					Effect[select[mode]][3] = i;
				}
			}
			break;
		case 2:
			c = wParam;
			if (NumEffects) {
				val = c - '0';
				if (val >= 0 && val < 10) {
					i = Effect[select[mode]][4];
					if (i < 100) {
						i *= 10;
						i += val;
						Effect[select[mode]][4] = i;
					}
				}
				if (c == 8) {
					i = Effect[select[mode]][4];
					i = i - i % 10;
					i /= 10;
					Effect[select[mode]][4] = i;
				}
			}
			break;
		case 3:
			c = wParam;
			if (NumEffects) {
				val = c - '0';
				if (val >= 0 && val < 10) {
					i = Effect[select[mode]][1];
					if (i < 100) {
						i *= 10;
						i += val;
						Effect[select[mode]][1] = i;
					}
				}
				if (c == 8) {
					i = Effect[select[mode]][1];
					i = i - i % 10;
					i /= 10;
					Effect[select[mode]][1] = i;
				}
			}
			break;
	}
}

if (submode[mode] == 1) {
	c = wParam;
	if (focus > 0 && subfocus + 30 * select[mode] < NumEffects) {
		val = c - '0';
		if (val >= 0 && val < 10) {
			i = Effect[subfocus + 30 * select[mode]][focus - 1];
			if (i < 100) {
				i *= 10;
				i += val;
				Effect[subfocus + 30 * select[mode]][focus - 1] = i;
			}
		}
		if (c == 8) {
			i = Effect[subfocus + 30 * select[mode]][focus - 1];
			i = i - i % 10;
			i /= 10;
			Effect[subfocus + 30 * select[mode]][focus - 1] = i;
		}
	}
}