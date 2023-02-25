if (submode[mode] == 0) {
	c = wParam;

	int t;

	switch (focus) {
		case 1:
			val = c - '0';

			if (val >= 0 && val < 10) {
				l = Range[select[mode]][1];
				if (l < 15) {
					l *= 10;
					l += val;
					Range[select[mode]][1] = l;
				}
			}
			if (c == 8) {
				l = Range[select[mode]][1];
				l = l - l % 10;
				l /= 10;
				Range[select[mode]][1] = l;
			}
			if (Range[select[mode]][1] > 15)Range[select[mode]][1] = 15;
			break;
		case 2:
			val = c - '0';

			t = Range[select[mode]][0] & 0xF0;
			Range[select[mode]][0] &= 0x0F;

			if (val >= 0 && val < 10) {
				l = Range[select[mode]][0];
				if (l < 15) {
					l *= 10;
					l += val;
					Range[select[mode]][0] = l;
				}
			}
			if (c == 8) {
				l = Range[select[mode]][0];
				l = l - l % 10;
				l /= 10;
				Range[select[mode]][0] = l;
			}
			if (Range[select[mode]][0] > 15)Range[select[mode]][0] = 15;
			Range[select[mode]][0] |= t;
			break;
		case 10:
				val = c - '0';
				if (val >= 0 && val < 10) {
					i = MaxRange;
					if (i < 10) {
						i *= 10;
						i += val;
						MaxRange = i;
					}
				}
				if (c == 8) {
					i = MaxRange;
					i = i - i % 10;
					i /= 10;
					MaxRange = i;
				}
				MaxRange &= 0x0F;
			break;
	}
}

if (submode[mode] == 1) {
	c = wParam;
	if (menu == 1 && ExtendRange) {
		val = c - '0';
		if (val >= 0 && val < 10) {
			i = Range[submenu + 32 * select[mode]][0] & 0x0F;
			if (i < 100) {
				i *= 10;
				i += val;
				Range[submenu + 32 * select[mode]][0] &= 0xF0;
				Range[submenu + 32 * select[mode]][0] |= i & 0x0F;
			}
		}
		if (c == 8) {
			i = Range[submenu + 32 * select[mode]][0] & 0x0F;
			i = i - i % 10;
			i /= 10;
			Range[submenu + 32 * select[mode]][0] &= 0xF0;
			Range[submenu + 32 * select[mode]][0] |= i & 0x0F;
		}
		return 0;
	}
	if (focus > 0 && focus < 5 && subfocus + 32 * select[mode] < NumRanges) {
		val = c - '0';
		if (val >= 0 && val < 10) {
			i = Range[subfocus + 32 * select[mode]][focus - 1];
			if (i < 100) {
				i *= 10;
				i += val;
				Range[subfocus + 32 * select[mode]][focus - 1] = i;
			}
		}
		if (c == 8) {
			i = Range[subfocus + 32 * select[mode]][focus - 1];
			i = i - i % 10;
			i /= 10;
			Range[subfocus + 32 * select[mode]][focus - 1] = i;
		}
	}
	if (focus == 5) {
		val = c - '0';
		if (c >= 'a'&&c <= 'f') {
			val = c - 'a' + 10;
		}
		if (c >= 'A'&&c <= 'F') {
			val = c - 'A' + 10;
		}
		if (val >= 0 && val < 16) {
			l = Range[subfocus + 32 * select[mode]][6] * 256 + Range[subfocus + 32 * select[mode]][7];
			if (l < 6553) {
				l *= 16;
				l += val;
				Range[subfocus + 32 * select[mode]][6] = (l - l % 0x100) / 0x100;
				Range[subfocus + 32 * select[mode]][7] = l % 0x100;
			}
		}
		if (c == 8) {
			l = Range[subfocus + 32 * select[mode]][6] * 256 + Range[subfocus + 32 * select[mode]][7];
			l = l - l % 16;
			l /= 16;
			Range[subfocus + 32 * select[mode]][6] = (l - l % 0x100) / 0x100;
			Range[subfocus + 32 * select[mode]][7] = l % 0x100;
		}
	}
	if (focus == 9) {
		val = c - '0';
		if (c >= 'a'&&c <= 'f') {
			val = c - 'a' + 10;
		}
		if (c >= 'A'&&c <= 'F') {
			val = c - 'A' + 10;
		}
		if (val >= 0 && val < 16) {
			l = RangeOffset;
			if (l < 524288) {
				l *= 16;
				l += val;
				RangeOffset = l;
			}
		}
		if (c == 8) {
			l = RangeOffset;
			l = l - l % 16;
			l /= 16;
			RangeOffset = l;
		}
	}
	if (focus == 10) {
		val = c - '0';
		if (val >= 0 && val < 10) {
			i = MaxRange;
			if (i < 10) {
				i *= 10;
				i += val;
				MaxRange = i;
			}
		}
		if (c == 8) {
			i = MaxRange;
			i = i - i % 10;
			i /= 10;
			MaxRange = i;
		}
		MaxRange &= 0x0F;
	}
	if (focus == 11) {
		val = c - '0';
		if (c >= 'a'&&c <= 'f') {
			val = c - 'a' + 10;
		}
		if (c >= 'A'&&c <= 'F') {
			val = c - 'A' + 10;
		}
		if (val >= 0 && val < 16) {
			l = RangeDataOffset;
			if (l < 524288) {
				l *= 16;
				l += val;
				RangeDataOffset = l;
			}
		}
		if (c == 8) {
			l = RangeDataOffset;
			l = l - l % 16;
			l /= 16;
			RangeDataOffset = l;
		}
	}
	if (focus == 12) {
		val = c - '0';
		if (c >= 'a'&&c <= 'f') {
			val = c - 'a' + 10;
		}
		if (c >= 'A'&&c <= 'F') {
			val = c - 'A' + 10;
		}
		if (val >= 0 && val < 16) {
			l = AreaOffset;
			if (l < 524288) {
				l *= 16;
				l += val;
				AreaOffset = l;
			}
		}
		if (c == 8) {
			l = AreaOffset;
			l = l - l % 16;
			l /= 16;
			AreaOffset = l;
		}
	}
}