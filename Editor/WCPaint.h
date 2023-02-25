if (!ScriptsLoaded) {
	if (strlen(file)) {

	} else {
		TextOut(memdc, 55, 33, "Load a ROM first.", 17);
	}
} else {

	sprintf(out, "Sprite Override: %d", WCSprites[subselect[mode][0]]);
	if (focus == 4 && cursor)sprintf(out, "%s|", out);
	TextOut(memdc, 550, 10, out, strlen(out));


	width = MSSize[0][0][0];
	height = MSSize[0][0][1];

	for (x = 0; x < width / 2; x++) {
		for (y = 0; y < height; y++) {
			k = MapSprites[WCSprites[subselect[mode][0]]][0][x + 24 * cursor + y*width];
			if (k < 0)k = 0;
			if (k) {

				if (MSPalette[WCSprites[subselect[mode][0]]])
					SetPixel(memdc, x + 700, y + 10, RGB(EMSPalette[k][0], EMSPalette[k][1], EMSPalette[k][2]));
				else
					SetPixel(memdc, x + 700, y + 10, RGB(FMSPalette[k][0], FMSPalette[k][1], FMSPalette[k][2]));
			}
		}
	}


	WCGraphs[subselect[mode][0]]->paint(memdc);
}
