if (submode[mode] == 0) {
	switch (menu) {
		case 1:
			for (int i = 0; i < NUM_EFFECT_ROUTINE; i++) {
				if (p.x >= 400 && p.x <= 650 && p.y >= 50+i*20 && p.y <= 69+i*20) {

					Effect[select[mode]][7] = EffectRoutineOffset[i] & 0x00FF;
					Effect[select[mode]][6] = (EffectRoutineOffset[i] & 0xFF00) >> 8;
					return true;
				}
			}
			break;
		case 2:
			for (int i = 0; i < 5; i++) {
				if (p.x >= 400 && p.x <= 550 && p.y >= 70 + i * 20 && p.y <= 89 + i * 20) {

					switch (i) {
						case 0:
							Effect[select[mode]][0] = 0;
							break;
						case 1:
							Effect[select[mode]][0] = 128;
							break;
						case 2:
							Effect[select[mode]][0] = 129;
							break;
						case 3:
							Effect[select[mode]][0] = 255;
							break;
					}

					return true;
				}
			}
			break;
		case 3:
			for (int i = 0; i < 8; i++) {
				if (p.x >= 400 && p.x <= 550 && p.y >= 110+i*20 && p.y <= 129+i*20) {

					Effect[select[mode]][2] &= 0xF8;
					Effect[select[mode]][2] |= i;

					return true;
				}
			}
			break;
		case 4:
			for (int i = 0; i < 3; i++) {
				if (p.x >= 400 && p.x <= 550 && p.y >= 130 + i * 20 && p.y <= 149 + i * 20) {

					Effect[select[mode]][2] &= 0x07;
					Effect[select[mode]][2] |= (i << 3);

					return true;
				}
			}
			break;
		case 5:
			for (int i = 0; i < 10; i++) {
				if (p.x >= 400 && p.x <= 650 && p.y >= 90 + i * 20 && p.y <= 109 + i * 20) {

					Effect[select[mode]][2] = i;
					return true;
				}
			}
			break;
		case 6:
			for (int i = 0; i < NUM_STAT_UPS; i++) {
				if (p.x >= 400 && p.x <= 650 && p.y >= 90 + i * 20 && p.y <= 109 + i * 20) {

					Effect[select[mode]][2] = i;
					return true;
				}
			}
			break;
	}

	menu = 0;

	for (i = 0;i < 30 && (i + subselect[mode][0] < NumEffects);i++) {
		if (p.x >= 50 && p.x <= 129 && p.y >= i * 16 + 10 && p.y <= i * 16 + 25) {
			select[mode] = i + subselect[mode][0];
		}
	}

	if (NumEffects > 30) {
		if (p.x >= 50 && p.x <= 70 && p.y >= 520 && p.y <= 540) {
			subselect[mode][0] -= 30;
			if (subselect[mode][0] < 0)subselect[mode][0] = NumEffects - NumEffects % 30;

			if (subselect[mode][0] >= NumEffects)subselect[mode][0] = NumEffects - 30;

			select[mode] = (select[mode] % 30) + subselect[mode][0];

			if (select[mode] >= NumEffects)select[mode] = NumEffects - 1;
		}
		if (p.x >= 73 && p.x <= 93 && p.y >= 520 && p.y <= 540) {
			subselect[mode][0] += 30;
			if (subselect[mode][0] >= NumEffects)subselect[mode][0] = 0;

			select[mode] = (select[mode] % 30) + subselect[mode][0];

			if (select[mode] >= NumEffects)select[mode] = NumEffects - 1;
		}
	}

	if (p.x >= 4 && p.x <= 24 && p.y >= 10 && p.y <= 30) {
		if (NumEffects < 256) {
			NumEffects++;
			select[mode] = NumEffects - 1;
			subselect[mode][0] = select[mode] - (select[mode] % 30);
		}
		EffectOffset = 0x1AA120;
	}
	if (p.x >= 4 && p.x <= 24 && p.y >= 34 && p.y <= 54) {
		if (NumEffects > 0) {
			NumEffects--;
			if(select[mode]>=NumEffects)select[mode] = NumEffects - 1;
		}
		EffectOffset = 0x1AA120;
	}
	
	if (p.x >= 400 && p.x <= 650 && p.y >= 48 && p.y < 68) {
		menu = 1;
	}
	if (p.x >= 400 && p.x <= 550 && p.y >= 68 && p.y < 88) {
		menu = 2;
	}

	if (p.x >= 400 && p.x <= 550 && p.y >= 88 && p.y < 108) {
		switch (EffectAction) {
			case 0:
			case 3:
			case 5:
			case 6:
			case 11:
			case 12:
				focus=1;
				break;
			case 7:
				menu = 5;
				break;
			case 10:
				menu = 6;
				break;
		}
		break;
	}

	if (p.x >= 400 && p.x <= 550 && p.y >= 108 && p.y < 128) {
		switch (EffectAction) {
			case 3:
			case 5:
			case 6:
			case 12:
				menu = 3;
				break;
			case 7:
				if (p.x < 415) {
					if (Effect[select[mode]][3])Effect[select[mode]][3] = 0;
					else Effect[select[mode]][3] = 1;
				}
				break;
		}
		break;
	}
	if (p.x >= 400 && p.x <= 550 && p.y >= 128 && p.y < 148) {
		switch (EffectAction) {
			case 5:
			case 6:
			case 12:
				menu = 4;
				break;
		}
		break;
	}

	if (p.x >= 400 && p.x <= 550 && p.y >= 170 && p.y < 190) {
		focus = 2;
	}

	if (EffectType == 1 || EffectType == 2) {
		if (p.x >= 400 && p.x <= 550 && p.y >= 150 && p.y < 170) {
			focus = 3;
		}
	}
}

if (submode[mode] == 1) {
	j = (NumEffects - (NumEffects) % 30) / 30;
	if ((NumEffects) % 30 > 0)j++;
	for (i = 0;i < j;i++) {
		if (p.x >= 50 && p.x <= 149 && p.y >= i * 16 + 10 && p.y <= i * 16 + 25) {
			select[mode] = i;
		}
	}

	for (i = 0;i < 30;i++) {
		for (j = 0;j < 8;j++) {
			if (p.x >= 200 + 65 * j&&p.x <= 264 + 65 * j&&p.y >= 26 + 16 * i&&p.y <= 41 + 16 * i) {
				focus = j + 1;
				subfocus = i;
			}
		}
	}

	if (p.x >= 4 && p.x <= 24 && p.y >= 10 && p.y <= 30) {
		if (NumEffects < 256)NumEffects++;
		EffectOffset = 0x1AA120;
	}
	if (p.x >= 4 && p.x <= 24 && p.y >= 34 && p.y <= 54) {
		if (NumEffects > 0)NumEffects--;
		EffectOffset = 0x1AA120;
	}
}