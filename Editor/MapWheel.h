if (submode[mode] == 3) {
	if (GET_WHEEL_DELTA_WPARAM(wParam) > 0) {
		if (subselect[mode][11] > 0)subselect[mode][11]--;
	} else {
		subselect[mode][11]++;
	}
}