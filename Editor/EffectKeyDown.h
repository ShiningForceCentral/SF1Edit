if (submode[mode] == 0) {
	switch (wParam) {
	case VK_PRIOR:

		if (NumEffects > 30) {
			subselect[mode][0] -= 30;
			if (subselect[mode][0] < 0)subselect[mode][0] = NumEffects - NumEffects % 30;

			select[mode] = (select[mode] % 30) + subselect[mode][0];

			if (select[mode] >= NumEffects)select[mode] = NumEffects - 1;
		}
		break;
	case VK_NEXT:
		if (NumEffects > 30) {
				subselect[mode][0] += 30;
				if (subselect[mode][0] >= NumEffects)subselect[mode][0] = 0;

				select[mode] = (select[mode] % 30) + subselect[mode][0];

				if (select[mode] >= NumEffects)select[mode] = NumEffects - 1;
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
		if (select[mode] >= NumEffects)select[mode] = NumEffects - 1;
		break;
	case VK_DOWN:
		if (menu)return 0;
		focus = 0;
		select[mode] += 1;

		if (select[mode] >= subselect[mode][0]+30 || select[mode] >= NumEffects)select[mode] = subselect[mode][0];

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
	}
	j = (NumEffects - (NumEffects) % 30) / 30;
	if ((NumEffects) % 30 > 0)j++;
	if (j > 0)select[mode] %= j;
	else select[mode] = 0;
	if (select[mode] < 0)select[mode] += j;
}