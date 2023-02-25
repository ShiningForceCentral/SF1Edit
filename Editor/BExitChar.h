c = wParam;

if (menu == 2) {
	if (focus == 32) {
		val = c - '0';
		if (val >= 0 && val<10) {
			i = subselect[mode][8];
			if (i<1000) {
				i *= 10;
				i += val;
				subselect[mode][8] = i;
			}
		}
		if (c == 8) {
			i = subselect[mode][8];
			i = i - i % 10;
			i /= 10;
			subselect[mode][8] = i;
		}
		subselect[mode][8] %= NUM_TEXT;
	}
	if (focus == 33) {
		val = c - '0';
		if (val >= 0 && val<10) {
			i = subselect[mode][9];
			if (i<1000) {
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
		subselect[mode][9] %= 2048;
	}
}

if (focus == 1) {
	val = c - '0';
	if (val >= 0 && val<10) {
		i = subselect[mode][0];
		if (i<10) {
			i *= 10;
			i += val;
			subselect[mode][0] = i;
		}
	}
	if (c == 8) {
		i = subselect[mode][0];
		i = i - i % 10;
		i /= 10;
		subselect[mode][0] = i;
	}
	subselect[mode][0] %= NUM_BEXIT;

	BExitGraphs[subselect[mode][0]]->w = BExitGraphs[u]->w;
	BExitGraphs[subselect[mode][0]]->h = BExitGraphs[u]->h;
	BExitGraphs[subselect[mode][0]]->vx = 0;
	BExitGraphs[subselect[mode][0]]->vy = 0;
}

if (focus == 2 && BExitGraphs[subselect[mode][0]]->sel) {
	i = subfocus;
	if (i<0)i = (i + 1)*-1;
	val = c - '0';
	if (val >= 0 && val<10) {
		switch (BExitGraphs[subselect[mode][0]]->sel->type->argtypes[i]) {
		case ARG_DIR:
		case ARG_IGNORE:
		case ARG_SPECIAL:
		case ARG_BRANCH:
		case ARG_SBRANCH:
			return true;
		case ARG_BYTE:
		case ARG_WORD:
		case ARG_LONG:
		case ARG_MESSAGE:
		case ARG_BANKED:
			lo = BExitGraphs[subselect[mode][0]]->sel->args[i];
			break;
		case ARG_ADDSUB:
			BExitGraphs[subselect[mode][0]]->sel->args[i] &= 0xF1;
			BExitGraphs[subselect[mode][0]]->sel->args[i] |= (val * 2) & 0x0E;
			break;
		case ARG_YESNO:
			lo = BExitGraphs[subselect[mode][0]]->sel->args[i];
			if (subfocus >= 0)lo = (lo & 0xFF00) / 0x100;
			else lo = lo & 0xFF;
			break;
		}

		lo *= 10;
		lo += val;

		switch (BExitGraphs[subselect[mode][0]]->sel->type->argtypes[i]) {
		case ARG_BYTE:
			BExitGraphs[subselect[mode][0]]->sel->args[i] = lo & 0x00FF;
			break;
		case ARG_WORD:
		case ARG_MESSAGE:
		case ARG_BANKED:
			BExitGraphs[subselect[mode][0]]->sel->args[i] = lo & 0x0000FFFF;
			break;
		case ARG_LONG:
			BExitGraphs[subselect[mode][0]]->sel->args[i] = lo;
			break;
		case ARG_YESNO:
			if (subfocus >= 0) {
				lo = (lo * 0x100) & 0xFF00;
				BExitGraphs[subselect[mode][0]]->sel->args[i] &= 0xFF;
				BExitGraphs[subselect[mode][0]]->sel->args[i] |= lo;
			} else {
				lo = lo & 0xFF;
				BExitGraphs[subselect[mode][0]]->sel->args[i] &= 0xFF00;
				BExitGraphs[subselect[mode][0]]->sel->args[i] |= lo;
			}
			break;
		}

	}
	if (c == '-'&&BExitGraphs[subselect[mode][0]]->sel->type->argtypes[i] == ARG_ADDSUB) {
		BExitGraphs[subselect[mode][0]]->sel->args[i] ^= 0x01;
	}
	if (c == 8) {
		switch (BExitGraphs[subselect[mode][0]]->sel->type->argtypes[i]) {
		case ARG_DIR:
		case ARG_IGNORE:
		case ARG_SPECIAL:
		case ARG_BRANCH:
		case ARG_SBRANCH:
			return true;
		case ARG_ADDSUB:
			BExitGraphs[subselect[mode][0]]->sel->args[i] &= 0xF1;
			break;
		case ARG_BYTE:
			lo = BExitGraphs[subselect[mode][0]]->sel->args[i] & 0xFF;
			break;
		case ARG_WORD:
		case ARG_LONG:
		case ARG_MESSAGE:
		case ARG_BANKED:
			lo = BExitGraphs[subselect[mode][0]]->sel->args[i];
			break;
		case ARG_YESNO:
			lo = BExitGraphs[subselect[mode][0]]->sel->args[i];
			if (subfocus >= 0)lo = (lo & 0xFF00) / 0x100;
			else lo = lo & 0xFF;
			break;
		}
		lo = lo - lo % 10;
		lo /= 10;
		switch (BExitGraphs[subselect[mode][0]]->sel->type->argtypes[i]) {
		case ARG_BYTE:
		case ARG_WORD:
		case ARG_LONG:
		case ARG_MESSAGE:
		case ARG_BANKED:
			BExitGraphs[subselect[mode][0]]->sel->args[i] = lo;
			break;
		case ARG_YESNO:
			if (subfocus >= 0) {
				lo = (lo * 0x100) & 0xFF00;
				BExitGraphs[subselect[mode][0]]->sel->args[i] &= 0xFF;
				BExitGraphs[subselect[mode][0]]->sel->args[i] |= lo;
			} else {
				lo = lo & 0xFF;
				BExitGraphs[subselect[mode][0]]->sel->args[i] &= 0xFF00;
				BExitGraphs[subselect[mode][0]]->sel->args[i] |= lo;
			}
			break;
		}
	}
}

if (c == 'z') {
	BExitGraphs[subselect[mode][0]]->graphzoom *= 2;
	if (BExitGraphs[subselect[mode][0]]->graphzoom == 16)BExitGraphs[subselect[mode][0]]->graphzoom = 1;
}