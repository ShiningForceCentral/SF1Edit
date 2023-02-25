c = wParam;

if (submode[mode] == 0) {
	switch (focus) {
	case 1:
		val = c - '0';
		if (val >= 0 && val < 10) {
			i = DPOffset;
			i *= 16;
			i += val;
			DPOffset = i;
		}
		val = c - 'a';
		if (val >= 0 && val < 10) {
			i = DPOffset;
			i *= 16;
			i += val + 10;
			DPOffset = i;
		}
		val = c - 'A';
		if (val >= 0 && val < 10) {
			i = DPOffset;
			i *= 16;
			i += val + 10;
			DPOffset = i;
		}
		if (c == 8) {
			i = DPOffset;
			i = i - i % 16;
			i /= 16;
			DPOffset = i;
		}

		if (strlen(file)) {
			fp = fopen(file, "rb+");
			fseek(fp, DPOffset, SEEK_SET);
			readPalette(DebugPalette, DPSize, fp);
			fclose(fp);
		}
		break;
	case 2:
		val = c - '0';
		if (val >= 0 && val < 10) {
			i = DPSize;
			i *= 10;
			i += val;
			DPSize = i;
		}
		if (c == 8) {
			i = DPSize;
			i = i - i % 10;
			i /= 10;
			DPSize = i;
		}
		if (DPSize > 32)DPSize = 32;
		if (strlen(file)) {
			fp = fopen(file, "rb+");
			fseek(fp, DPOffset, SEEK_SET);
			readPalette(DebugPalette, DPSize, fp);
			fclose(fp);
		}
		break;
	}
}

if (submode[mode] == 1) {
	switch (focus) {
	case 1:
		val = c - '0';
		if (val >= 0 && val < 10) {
			i = DGOffset;
			i *= 16;
			i += val;
			DGOffset = i;
		}
		val = c - 'a';
		if (val >= 0 && val < 10) {
			i = DGOffset;
			i *= 16;
			i += val + 10;
			DGOffset = i;
		}
		val = c - 'A';
		if (val >= 0 && val < 10) {
			i = DGOffset;
			i *= 16;
			i += val + 10;
			DGOffset = i;
		}
		if (c == 8) {
			i = DGOffset;
			i = i - i % 16;
			i /= 16;
			DGOffset = i;
		}
		break;
	case 2:
		val = c - '0';
		if (val >= 0 && val < 10) {
			i = DGSize[0];
			i *= 10;
			i += val;
			DGSize[0] = i;
		}
		if (c == 8) {
			i = DGSize[0];
			i = i - i % 10;
			i /= 10;
			DGSize[0] = i;
		}
		if (DGSize[0] > 32)DGSize[0] = 32;
		break;
	case 3:
		val = c - '0';
		if (val >= 0 && val < 10) {
			i = DGSize[1];
			i *= 10;
			i += val;
			DGSize[1] = i;
		}
		if (c == 8) {
			i = DGSize[1];
			i = i - i % 10;
			i /= 10;
			DGSize[1] = i;
		}
		if (DGSize[1] > 32)DGSize[1] = 32;
		break;
	}
}