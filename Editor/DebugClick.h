if (submode[mode] == 0) {
	if (p.x >= 50 && p.x <= 150 && p.y >= 20 && p.y <= 36) {
		focus = 1;
	}
	if (p.x >= 50 && p.x <= 150 && p.y >= 40 && p.y <= 56) {
		focus = 2;
	}

	for (i = 0; i < DPSize; i++) {
		if (p.x >= 160 + 18 * i&&p.x <= 177 + 18 * i&&p.y >= 20 && p.y <= 38) {
			COLORREF c = RGB(DebugPalette[i][0], DebugPalette[i][1], DebugPalette[i][2]);
			chooseColor(c);
			DebugPalette[i][0] = GetRValue(c);
			DebugPalette[i][1] = GetGValue(c);
			DebugPalette[i][2] = GetBValue(c);
		}
	}

	if (DPOffset && DPSize && strlen(file))
	if (p.x >= 20 && p.x <= 120 && p.y >= 60 && p.y <= 90) {
		if (MessageBox(NULL, "Are you sure? Backups are recommended before saving debug palettes, no protection against editing code.", "Confirm", MB_YESNO) == IDYES) {

			fp = fopen(file, "rb+");
			fseek(fp, DPOffset, SEEK_SET);
			writePalette(DebugPalette, DPSize, fp);
			fclose(fp);
			MessageBox(NULL, "Palette Saved", "Note", MB_OK);
		}
	}

}

if (submode[mode] == 1) {
	if (p.x >= 50 && p.x <= 150 && p.y >= 20 && p.y <= 36) {
		focus = 1;
	}

	if (p.x >= 648 && p.x <= 698 && p.y >= 20 && p.y <= 40) {
		focus = 2;
	}
	if (p.x >= 648 && p.x <= 698 && p.y >= 40 && p.y <= 60) {
		focus = 3;
	}

	long len;
	char * data;
	unsigned char l;
	unsigned char c;

	if (DGOffset && DGOffset<romsize && strlen(file)){
		if (p.x >= 20 && p.x <= 120 && p.y >= 60 && p.y <= 90) {

			FILE * fp = fopen(file, "rb");
			if (!fp)return 0;
			PixelDecompressor PD(fp);

			len = PD.GetData(DGOffset, &data);
			DGSize[0] = PD.width;
			DGSize[1] = PD.height;

			for (int i = 0;i<len;i++) {
				c = data[i];
				if (c == 0xFF)DGFX[i] = l;
				else {
					DGFX[i] = c;
					l = c;
				}
			}
			fclose(fp);
		}
	}

	if (DGOffset && DGOffset<romsize && strlen(file)) {
		if (p.x >= 500 && p.x <= 600 && p.y >= 60 && p.y <= 90) {

			FILE * fp = fopen(file, "rb");
			if (!fp)return 0;
			PixelDecompressor PD(fp);

			len = PD.GetData(DGOffset, &data,16,16);
			DGSize[0] = PD.width;
			DGSize[1] = PD.height;

			for (int i = 0; i<len; i++) {
				c = data[i];
				if (c == 0xFF)DGFX[i] = l;
				else {
					DGFX[i] = c;
					l = c;
				}
			}
			fclose(fp);
		}
	}

	if (DGOffset && DGOffset<romsize && strlen(file)) {
		if (p.x >= 620 && p.x <= 720 && p.y >= 60 && p.y <= 90) {

			if (DGSize[0] < 0 || DGSize[0]>32 || DGSize[1] < 0 || DGSize[1]>32)return 0;

			FILE * fp = fopen(file, "rb");
			if (!fp)return 0;
			PixelDecompressor PD(fp);

			len = PD.GetData(DGOffset, &data, DGSize[0], DGSize[1]);
			DGSize[0] = PD.width;
			DGSize[1] = PD.height;

			for (int i = 0; i<len; i++) {
				c = data[i];
				if (c == 0xFF)DGFX[i] = l;
				else {
					DGFX[i] = c;
					l = c;
				}
			}
			fclose(fp);
		}
	}

	if (p.x >= 380 && p.x <= 480 && p.y >= 60 && p.y <= 90) {
		String file = "Debug.bmp";
		FILE * fp = fopen(file, "wb");
		BMPHeader(fp, DGSize[0], DGSize[1]);
		int x;
		for (int y = DGSize[1] - 1;y >= 0;y--) {
			for (x = 0;x<DGSize[0];x++) {
				color = DGFX[x + y*DGSize[0]];
				if (color) {
					fprintf(fp, "%c", DebugPalette[color][2]);
					fprintf(fp, "%c", DebugPalette[color][1]);
					fprintf(fp, "%c", DebugPalette[color][0]);
				} else {
					fprintf(fp, "%c", 99);
					fprintf(fp, "%c", 1);
					fprintf(fp, "%c", 100);
				}
			}
			for (x = 0;x<(4 - (DGSize[0] * 3) % 4) % 4;x++) {
				fprintf(fp, "%c", 0);
			}
		}
		fclose(fp);
		MessageBox(NULL, "Saved to debug.bmp", "Note", MB_OK);
	}

	if (p.x >= 260 && p.x <= 360 && p.y >= 60 && p.y <= 90) {
		String file = "Debug.bmp";
		FILE * fp = fopen(file, "rb");
		unsigned char r;
		unsigned char color[3];
		if (fp) {
			DGSize[0] = 0;
			fseek(fp, 0x12, SEEK_SET);
			fscanf(fp, "%c", &r);
			DGSize[0] += r;
			fscanf(fp, "%c", &r);
			DGSize[0] += r * 256;
			fscanf(fp, "%c", &r);
			DGSize[0] += r * 256 * 256;


			DGSize[1] = 0;
			fseek(fp, 0x16, SEEK_SET);
			fscanf(fp, "%c", &r);
			DGSize[1] += r;
			fscanf(fp, "%c", &r);
			DGSize[1] += r * 256;
			fscanf(fp, "%c", &r);
			DGSize[1] += r * 256 * 256;

			fseek(fp, 0x36, SEEK_SET);

			int x;

			for (int y = DGSize[1] - 1;y >= 0;y--) {
				for (x = 0;x<DGSize[0];x++) {
					fscanf(fp, "%c", &(color[2]));
					fscanf(fp, "%c", &(color[1]));
					fscanf(fp, "%c", &(color[0]));
					DGFX[x + y*DGSize[0]] = FindColor(DebugPalette, color, DPSize, 0);
				}
				for (x = 0;x<(4 - (DGSize[0] * 3) % 4) % 4;x++) {
					fscanf(fp, "%c", &r);
				}
			}
			fclose(fp);
		}
	}
}


