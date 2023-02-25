if (submode[mode] == 0) {
	GetCursorPos(&p);
	ScreenToClient(hWnd, &p);
	p.y -= 40;

	if (!menu) {
		PatBlt(memdc, 10, 560, 80, 20, PATCOPY);
		if (p.x >= -238 + dwidth / 2 && p.x <= 789 + dwidth / 2 && p.y >= 36 && p.y <= 499) {
			x = (p.x - (-238 + dwidth / 2));
			y = (p.y - 36);
			sprintf(out, "%d, %d", (x - x % 4) / 4, (y - y % 4) / 4);
			TextOut(memdc, 10, 560, out, strlen(out));
		}
		BitBlt(hdc, 10, 560, 80, 20, memdc, 10, 560, SRCCOPY);
	}
}