if (subselect[mode][7] == 1) {

	if (!menu) {
		if (GET_WHEEL_DELTA_WPARAM(wParam) > 0) {
			subselect[mode][8] += 58;
			if (subselect[mode][8] > 0)subselect[mode][8] = 0;
		} else {
			subselect[mode][8] -= 58;
		}
	}
}