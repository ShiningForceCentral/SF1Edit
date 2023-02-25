if (submode[mode] == 0) {
	sprintf(out, "Offset: %X", DPOffset);
	if (focus == 1 && cursor)sprintf(out, "%s|", out);
	TextOut(memdc, 20, 20, out, strlen(out));

	sprintf(out, "Size: %d", DPSize);
	if (focus == 2 && cursor)sprintf(out, "%s|", out);
	TextOut(memdc, 20, 40, out, strlen(out));

	if (DPOffset && DPSize) {
		for (i = 0; i < DPSize; i++) {
			for (int dx = 0; dx < 18; dx++) {
				for (int dy = 0; dy < 18; dy++) {
					SetPixel(memdc, 160 + 18 * i + dx, 20 + dy, RGB(DebugPalette[i][0], DebugPalette[i][1], DebugPalette[i][2]));
				}
			}
		}
	}

	Rectangle(memdc, 20, 60, 120, 90);
	TextOut(memdc, 52, 66, "Save", 4);
}

if (submode[mode] == 1) {
	sprintf(out, "Offset: %X", DGOffset);
	if (focus == 1 && cursor)sprintf(out, "%s|", out);
	TextOut(memdc, 20, 20, out, strlen(out));

	Rectangle(memdc, 20, 60, 120, 90);
	TextOut(memdc, 52, 66, "Load", 4);

	Rectangle(memdc, 140, 60, 240, 90);
	TextOut(memdc, 172, 66, "Save", 4);

	Rectangle(memdc, 260, 60, 360, 90);
	TextOut(memdc, 288, 66, "Import", 6);

	Rectangle(memdc, 380, 60, 480, 90);
	TextOut(memdc, 408, 66, "Export", 6);

	Rectangle(memdc, 500, 60, 600, 90);
	TextOut(memdc, 528, 66, "Load 2", 6);

	Rectangle(memdc, 620, 60, 720, 90);
	TextOut(memdc, 648, 66, "Load 3", 6);

	sprintf(out, "W: %d", DGSize[0]);
	if (focus == 2 && cursor)sprintf(out, "%s|", out);
	TextOut(memdc, 648, 20,out, strlen(out));

	sprintf(out, "H: %d", DGSize[1]);
	if (focus == 3 && cursor)sprintf(out, "%s|", out);
	TextOut(memdc, 648, 40, out, strlen(out));

	if (DPOffset && DPSize) {
		for (i = 0; i < DPSize; i++) {
			for (int dx = 0; dx < 18; dx++) {
				for (int dy = 0; dy < 18; dy++) {
					SetPixel(memdc, 160 + 18 * i + dx, 20 + dy, RGB(DebugPalette[i][0], DebugPalette[i][1], DebugPalette[i][2]));
				}
			}
		}
	}

	if (DGOffset && DGSize[0]) {
		int width = DGSize[0];
		int height = DGSize[1];

		for (int x = 0;x < width;x++) {
			for (int y = 0;y < height;y++) {
				for (i = 0;i < 4;i++) {
					for (j = 0;j < 4;j++) {
						k = DGFX[x + y*width];
						if (k < 0)k = 0;
						if(k<DPSize)SetPixel(memdc, x * 4 + i + 82, y * 4 + j + 97, RGB(DebugPalette[k][0], DebugPalette[k][1], DebugPalette[k][2]));
					}
				}
			}
		}
	}
}