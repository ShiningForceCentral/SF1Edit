if (submode[mode] == 0) {
	switch (menu) {
		case 1:
			for (int i = 0; i < 7; i++) {
				if (p.x >= 300 && p.x <= 450 && p.y >= 70 + i * 20 && p.y <= 89 + i * 20) {

					RangeShape = i;

					Range[select[mode]][0] &= 0x0F;
					Range[select[mode]][0] |= 16 * i;

					return true;
				}
			}
			break;
		case 2:
			for (int i = 0; i < (3 + 6 * ExtendRange * ExtendArea); i++) {
				if (p.x >= 300 && p.x <= 450 && p.y >= 90 + i * 20 && p.y <= 109 + i * 20) {

					RangeArea = i;

					switch (RangeArea) {
					case 0:
					case 1:
					case 2:
					case 3:
					case 4:
						Range[select[mode]][2] = RangeArea;
						break;
					case 5:
					case 6:
					case 7:
					case 8:
						Range[select[mode]][2] = RangeArea + 24;
						break;
					}

					return true;
				}
			}
			break;
		case 3:
			for (int i = 0; i < 8; i++) {
				if (p.x >= 300 && p.x <= 450 && p.y >= 110 + i * 20 && p.y <= 129 + i * 20) {

					Range[select[mode]][3] = i;

					return true;
				}
			}
			break;
		case 4:
			for (int i = 0; i < NUM_RANGE_ROUTINES; i++) {
				if (p.x >= 300 && p.x <= 500 && p.y >= 130 + i * 20 && p.y <= 149 + i * 20) {
					RangeRoutine = i;

					long t = RangeRoutineOffsets[i] - 0x23178 - 6 - 8 * select[mode];

					Range[select[mode]][7] = t & 0x00FF;
					Range[select[mode]][6] = (t & 0xFF00) >> 8;
					return true;
				}
			}
			break;
	}

	menu = 0;

	if (p.x >= 4 && p.x <= 24 && p.y >= 10 && p.y <= 30) {
		if (NumRanges < 256)NumRanges++;
		select[mode] = NumRanges - 1;
		subselect[mode][0] = select[mode] - (select[mode] % 30);
		RangeDataOffset = 0x180300;
	}
	if (p.x >= 4 && p.x <= 24 && p.y >= 34 && p.y <= 54) {
		if (NumRanges > 0)NumRanges--;
		if(select[mode] > NumRanges - 1)select[mode] = NumRanges - 1;
		subselect[mode][0] = select[mode] - (select[mode] % 30);
	}

	if (p.x >= 690 && p.x <= 703 && p.y >= 34 && p.y <= 47) {
		RangePreview = true;
	}
	if (p.x >= 690 && p.x <= 703 && p.y >= 54 && p.y <= 67) {
		RangePreview = false;
	}

	if (p.x >= 720 && p.x <= 733 && p.y >= 94 && p.y <= 107) {
		ExtendRange = !ExtendRange;
		if (RangeOffset == 0)RangeOffset = 0x180080;
	}

	if (p.x >= 720 && p.x <= 733 && p.y >= 114 && p.y <= 127) {
		ExtendArea = !ExtendArea;
		if (AreaOffset == 0)AreaOffset = 0x182700;
	}


	for (i = 0; i < 30 && (i + subselect[mode][0] < NumRanges); i++) {
		if (p.x >= 50 && p.x <= 129 && p.y >= i * 16 + 10 && p.y <= i * 16 + 25) {
			select[mode] = i + subselect[mode][0];
		}
	}

	if (NumRanges > 30) {
		if (p.x >= 50 && p.x <= 70 && p.y >= 520 && p.y <= 540) {
			subselect[mode][0] -= 30;
			if (subselect[mode][0] < 0)subselect[mode][0] = NumRanges - NumRanges % 30;

			select[mode] = (select[mode] % 30) + subselect[mode][0];

			if (select[mode] >= NumRanges)select[mode] = NumRanges - 1;
		}
		if (p.x >= 73 && p.x <= 93 && p.y >= 520 && p.y <= 540) {
			subselect[mode][0] += 30;
			if (subselect[mode][0] >= NumRanges)subselect[mode][0] = 0;

			select[mode] = (select[mode] % 30) + subselect[mode][0];

			if (select[mode] >= NumRanges)select[mode] = NumRanges - 1;
		}
	}

	if (p.x >= 300 && p.x <= 360 && p.y >= 32 && p.y <= 51) {
		focus = 1;
	}

	if (p.x >= 300 && p.x <= 360 && p.y >= 52 && p.y <= 71) {
		focus = 2;
	}

	if (p.x >= 710 && p.x <= 760 && p.y >= 72 && p.y <= 91) {
		focus = 10;
	}

	if(ExtendRange)
	if (p.x >= 300 && p.x <= 450 && p.y >= 70 && p.y <= 90) {
		menu = 1;
	}
	if (p.x >= 300 && p.x <= 450 && p.y >= 90 && p.y <= 110) {
		menu = 2;
	}
	if (p.x >= 300 && p.x <= 450 && p.y >= 110 && p.y <= 130) {
		menu = 3;
	}
	if (p.x >= 300 && p.x <= 500 && p.y >= 130 && p.y <= 150) {
		menu = 4;
	}
}


if (submode[mode] == 1) {
	if (menu == 1 && ExtendRange) {
		y = 26 + 16 * submenu;
		if (y + 188 > 540)y = 540 - 188;
		for (i = 0; i < 7; i++) {
			if (p.x >= 207 && p.x <= 270 && p.y >= y + 54 + 16 * i&&p.y <= y + 69 + 16 * i) {
				Range[submenu + 32 * select[mode]][0] &= 0x0F;
				Range[submenu + 32 * select[mode]][0] ^= 16 * i;
				return 0;
			}
		}

		if (p.x >= 179 && p.x <= 329 && p.y >= y&&p.y <= y + 188) {
			return 0;
		}

		menu = 0;
	}
	if (menu == 2 && ExtendRange&&ExtendArea) {
		y = 26 + 16 * submenu;
		if (y + 188 > 540)y = 540 - 188;
		for (i = 0; i < 9; i++) {
			if (p.x >= 337 && p.x <= 400 && p.y >= y + 22 + 16 * i&&p.y <= y + 37 + 16 * i) {
				Range[submenu + 32 * select[mode]][2] = i;
				if (i > 4)Range[submenu + 32 * select[mode]][2] += 24;
				return 0;
			}
		}

		if (p.x >= 309 && p.x <= 459 && p.y >= y&&p.y <= y + 188) {
			return 0;
		}

		menu = 0;
	}

	j = (NumRanges - (NumRanges) % 32) / 32;
	if ((NumRanges) % 32 > 0)j++;
	for (i = 0; i < j; i++) {
		if (p.x >= 50 && p.x <= 149 && p.y >= i * 16 + 10 && p.y <= i * 16 + 25) {
			select[mode] = i;
		}
	}

	for (i = 0; i < 32 && i + 32 * select[mode] < NumRanges; i++) {
		for (j = 0; j < 5; j++) {
			if (p.x >= 200 + 65 * j&&p.x <= 264 + 65 * j&&p.y >= 26 + 16 * i&&p.y <= 41 + 16 * i) {
				focus = j + 1;
				subfocus = i;
			}
		}
		if (ExtendRange&&p.x >= 179 && p.x <= 199 && p.y >= 26 + 16 * i&&p.y <= 46 + 16 * i) {
			menu = 1;
			submenu = i;
		}
		if (ExtendRange&&ExtendArea&&p.x >= 309 && p.x <= 329 && p.y >= 26 + 16 * i&&p.y <= 46 + 16 * i) {
			menu = 2;
			submenu = i;
		}
	}

	if (p.x >= 134 && p.x <= 147 && p.y >= 482 && p.y <= 495) {
		ExtendRange = !ExtendRange;
		if (RangeOffset == 0)RangeOffset = 0x180080;
	}

	if (p.x >= 134 && p.x <= 147 && p.y >= 514 && p.y <= 527) {
		ExtendArea = !ExtendArea;
		if (AreaOffset == 0)AreaOffset = 0x182700;
	}

	if (p.x >= 114 && p.x <= 127 && p.y >= 402 && p.y <= 415) {
		if (RangeDataOffset == 0x23178)RangeDataOffset = 0x180300;
		else RangeDataOffset = 0x23178;
	}

	if (ExtendRange&&p.x >= 94 && p.x <= 170 && p.y >= 496 && p.y <= 512) {
		focus = 9;
	}

	if (RangeDataOffset != 0x23178 && p.x >= 56 && p.x <= 132 && p.y >= 416 && p.y <= 432) {
		focus = 11;
	}

	if (ExtendRange&&p.x >= 94 && p.x <= 170 && p.y >= 528 && p.y <= 544) {
		focus = 12;
	}

	if (RangeDataOffset != 0x23178 && p.x >= 4 && p.x <= 24 && p.y >= 10 && p.y <= 30) {
		if (NumRanges < 256)NumRanges++;
	}
	if (RangeDataOffset != 0x23178 && p.x >= 4 && p.x <= 24 && p.y >= 34 && p.y <= 54) {
		if (NumRanges > 0)NumRanges--;
	}

	if (p.x >= 127 && p.x <= 157 && p.y >= 448 && p.y <= 464) {
		focus = 10;
	}

}