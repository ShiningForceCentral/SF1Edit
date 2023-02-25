switch (subselect[mode][7]) {
case 2:
	for (i = 0; i<5; i++) {
		if (p.x >= 90 + 18 * i&&p.x <= 108 + 18 * i&&p.y >= 40 && p.y<59) {
			COLORREF c = RGB(SpellAnimPal[select[mode]][i+6][0], SpellAnimPal[select[mode]][i + 6][1], SpellAnimPal[select[mode]][i + 6][2]);
			chooseColor(c);
			GFXPaletteEdit = true;
			SpellAnimPal[select[mode]][i + 6][0] = GetRValue(c);
			SpellAnimPal[select[mode]][i + 6][1] = GetGValue(c);
			SpellAnimPal[select[mode]][i + 6][2] = GetBValue(c);
			InvalidateRect(hWnd, NULL, 0);
		}
	}
	break;

}