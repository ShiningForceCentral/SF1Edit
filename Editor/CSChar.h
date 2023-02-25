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
	if (focus == 34) {
		val = c - '0';
		if (val >= 0 && val<10) {
			i = subselect[mode][10];
			if (i<1000) {
				i *= 10;
				i += val;
				subselect[mode][10] = i;
			}
		}
		if (c == 8) {
			i = subselect[mode][10];
			i = i - i % 10;
			i /= 10;
			subselect[mode][10] = i;
		}
		subselect[mode][10] %= NumChars;
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
	subselect[mode][0] %= NUM_CS;

	CSGraphs[subselect[mode][0]]->w = CSGraphs[u]->w;
	CSGraphs[subselect[mode][0]]->h = CSGraphs[u]->h;
	CSGraphs[subselect[mode][0]]->vx = 0;
	CSGraphs[subselect[mode][0]]->vy = 0;
}

if (focus == 2 && CSGraphs[subselect[mode][0]]->sel) {
	i = subfocus;
	if (i<0)i = (i + 1)*-1;
	val = c - '0';
	if (val >= 0 && val<10) {
		switch (CSGraphs[subselect[mode][0]]->sel->type->argtypes[i]) {
			case ARG_DIR:
			case ARG_IGNORE:
			case ARG_SPECIAL:
			case ARG_BRANCH:
			case ARG_SBRANCH:
				return true;
			case ARG_CHAR:
			case ARG_ITEM:
			case ARG_BYTE:
			case ARG_VOICE:
			case ARG_WORD:
			case ARG_LONG:
			case ARG_MESSAGE:
			case ARG_BANKED:
				lo = CSGraphs[subselect[mode][0]]->sel->args[i];
				break;
			case ARG_ADDSUB:
				CSGraphs[subselect[mode][0]]->sel->args[i] &= 0xF1;
				CSGraphs[subselect[mode][0]]->sel->args[i] |= (val * 2) & 0x0E;
				break;
			case ARG_YESNO:
				lo = CSGraphs[subselect[mode][0]]->sel->args[i];
				if (subfocus >= 0)lo = (lo & 0xFF00) / 0x100;
				else lo = lo & 0xFF;
				break;
		}

		lo *= 10;
		lo += val;

		switch (CSGraphs[subselect[mode][0]]->sel->type->argtypes[i]) {
			case ARG_CHAR:
			case ARG_ITEM:
			case ARG_VOICE:
			case ARG_BYTE:
				CSGraphs[subselect[mode][0]]->sel->args[i] = lo & 0x00FF;
				break;
			case ARG_WORD:
			case ARG_MESSAGE:
			case ARG_BANKED:
				CSGraphs[subselect[mode][0]]->sel->args[i] = lo & 0x0000FFFF;
				break;
			case ARG_LONG:
				CSGraphs[subselect[mode][0]]->sel->args[i] = lo;
				break;
			case ARG_YESNO:
				if (subfocus >= 0) {
					lo = (lo * 0x100) & 0xFF00;
					CSGraphs[subselect[mode][0]]->sel->args[i] &= 0xFF;
					CSGraphs[subselect[mode][0]]->sel->args[i] |= lo;
				} else {
					lo = lo & 0xFF;
					CSGraphs[subselect[mode][0]]->sel->args[i] &= 0xFF00;
					CSGraphs[subselect[mode][0]]->sel->args[i] |= lo;
				}
				break;
		}

	}
	if (c == '-'&&CSGraphs[subselect[mode][0]]->sel->type->argtypes[i] == ARG_ADDSUB) {
		CSGraphs[subselect[mode][0]]->sel->args[i] ^= 0x01;
	}
	if (c == 8) {
		switch (CSGraphs[subselect[mode][0]]->sel->type->argtypes[i]) {
			case ARG_DIR:
			case ARG_IGNORE:
			case ARG_SPECIAL:
			case ARG_BRANCH:
			case ARG_SBRANCH:
				return true;
			case ARG_ADDSUB:
				CSGraphs[subselect[mode][0]]->sel->args[i] &= 0xF1;
				break;
			case ARG_CHAR:
			case ARG_ITEM:
			case ARG_BYTE:
			case ARG_VOICE:
			case ARG_WORD:
			case ARG_LONG:
			case ARG_MESSAGE:
			case ARG_BANKED:
				lo = CSGraphs[subselect[mode][0]]->sel->args[i];
				break;
			case ARG_YESNO:
				lo = CSGraphs[subselect[mode][0]]->sel->args[i];
				if (subfocus >= 0)lo = (lo & 0xFF00) / 0x100;
				else lo = lo & 0xFF;
				break;
		}
		lo = lo - lo % 10;
		lo /= 10;
		switch (CSGraphs[subselect[mode][0]]->sel->type->argtypes[i]) {
			case ARG_CHAR:
			case ARG_ITEM:
			case ARG_BYTE:
			case ARG_VOICE:
			case ARG_WORD:
			case ARG_LONG:
			case ARG_MESSAGE:
			case ARG_BANKED:
				CSGraphs[subselect[mode][0]]->sel->args[i] = lo;
				break;
			case ARG_YESNO:
				if (subfocus >= 0) {
					lo = (lo * 0x100) & 0xFF00;
					CSGraphs[subselect[mode][0]]->sel->args[i] &= 0xFF;
					CSGraphs[subselect[mode][0]]->sel->args[i] |= lo;
				} else {
					lo = lo & 0xFF;
					CSGraphs[subselect[mode][0]]->sel->args[i] &= 0xFF00;
					CSGraphs[subselect[mode][0]]->sel->args[i] |= lo;
				}
				break;
		}
	}

	if (!strcmp(CSGraphs[subselect[mode][0]]->sel->type->name, "Set Message Bank")) {
		//propagateBank(CSGraphs[subselect[mode][0]], CSGraphs[subselect[mode][0]]->sel, CSGraphs[subselect[mode][0]]->sel->args[0]);
	}

}

if (c == 'z') {
	CSGraphs[subselect[mode][0]]->graphzoom *= 2;
	if (CSGraphs[subselect[mode][0]]->graphzoom == 16)CSGraphs[subselect[mode][0]]->graphzoom = 1;
}