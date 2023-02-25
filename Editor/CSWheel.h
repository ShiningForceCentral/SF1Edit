if (GET_WHEEL_DELTA_WPARAM(wParam) > 0) del = 16;
else del = -16;

CSGraph * cs;
cs = CSGraphs[subselect[mode][0]];


if (GetKeyState(VK_SHIFT) & 0x80 || GetKeyState(VK_LSHIFT) & 0x80 || GetKeyState(VK_RSHIFT) & 0x80) {
	cs->vx -= (del)*cs->graphzoom;
} else {
	cs->vy -= (del)*cs->graphzoom;
}
if (cs->vx <= -cs->w)cs->vx = -cs->w + 1;
if (cs->vy <= -cs->h)cs->vy = -cs->h + 1;

InvalidateRect(hwnd, NULL, 0);
