if (submode[mode] == 0) {
	switch (wParam) {
		case VK_PRIOR:
			if (NumRanges > 30) {
				subselect[mode][0] -= 30;
				if (subselect[mode][0] < 0)subselect[mode][0] = NumRanges - NumRanges % 30;

				select[mode] = (select[mode] % 30) + subselect[mode][0];

				if (select[mode] >= NumRanges)select[mode] = NumRanges - 1;
			}
			break;
		case VK_NEXT:
			if (NumRanges > 30) {
				subselect[mode][0] += 30;
				if (subselect[mode][0] >= NumRanges)subselect[mode][0] = 0;

				select[mode] = (select[mode] % 30) + subselect[mode][0];

				if (select[mode] >= NumRanges)select[mode] = NumRanges - 1;
			}
			break;

		case VK_ESCAPE:
			menu = 0;
			break;
		case VK_UP:
			if (menu)return 0;
			focus = 0;
			select[mode] -= 1;
			if (select[mode] < subselect[mode][0])select[mode] += 30;
			if (select[mode] >= NumRanges)select[mode] = NumRanges - 1;
			break;
		case VK_DOWN:
			if (menu)return 0;
			focus = 0;
			select[mode] += 1;

			if (select[mode] >= subselect[mode][0] + 30 || select[mode] >= NumRanges)select[mode] = subselect[mode][0];

			break;
	}

}

if (submode[mode] == 1) {
	switch (wParam) {
	case VK_LEFT:
		select[mode] -= 1;
		break;
	case VK_RIGHT:
		select[mode] += 1;
		break;
	case VK_UP:
		select[mode] -= 1;
		break;
	case VK_DOWN:
		select[mode] += 1;
		break;
	case VK_ESCAPE:
	case VK_RETURN:
		menu = 0;
		break;
	}
	j = (NumRanges - (NumRanges) % 32) / 32;
	if ((NumRanges) % 32 > 0)j++;
	if (j > 0)select[mode] %= j;
	else select[mode] = 0;
	if (select[mode] < 0)select[mode] += j;
}