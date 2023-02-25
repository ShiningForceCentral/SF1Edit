if (GET_WHEEL_DELTA_WPARAM(wParam) > 0) del = 16;
else del = -16;

WCGraph * wc;
wc = WCGraphs[subselect[mode][0]];


if (GetKeyState(VK_SHIFT) & 0x80 || GetKeyState(VK_LSHIFT) & 0x80 || GetKeyState(VK_RSHIFT) & 0x80) {
	wc->vx -= (del)*wc->graphzoom;
} else {
	wc->vy -= (del)*wc->graphzoom;
}
if (wc->vx <= -wc->w)wc->vx = -wc->w + 1;
if (wc->vy <= -wc->h)wc->vy = -wc->h + 1;

InvalidateRect(hwnd, NULL, 0);
