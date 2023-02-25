GetCursorPos(&p);
ScreenToClient(hWnd, &p);
p.y -= 40;

if (wParam &	MK_LBUTTON) {
	WCGraphs[subselect[mode][0]]->move(p.x, p.y);
}