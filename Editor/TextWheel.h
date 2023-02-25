if (TextLoaded && !menu) {
	if (GET_WHEEL_DELTA_WPARAM(wParam) > 0) {
		subselect[mode][0] -= 1;
		if (subselect[mode][0] < 0)subselect[mode][0] += NUM_TEXT;
		if (focus < 31)focus++;
		else subfocus = strlen(Text[(subselect[mode][0] + focus) % NUM_TEXT]);
	}
	else {
		subselect[mode][0] += 1;
		if (subselect[mode][0] > NUM_TEXT - 1)subselect[mode][0] -= NUM_TEXT;
		if (focus > 0)focus--;
		else subfocus = strlen(Text[(subselect[mode][0] + focus) % NUM_TEXT]);
	}
}