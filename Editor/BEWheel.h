if (GET_WHEEL_DELTA_WPARAM(wParam) > 0) del = 16;
else del = -16;

BEGraph * be;
be = BEGraphs[subselect[mode][0]];


if (GetKeyState(VK_SHIFT) & 0x80 || GetKeyState(VK_LSHIFT) & 0x80 || GetKeyState(VK_RSHIFT) & 0x80) {
	be->vx -= (del)*be->graphzoom;
} else {
	be->vy -= (del)*be->graphzoom;
}
if (be->vx <= -be->w)be->vx = -be->w + 1;
if (be->vy <= -be->h)be->vy = -be->h + 1;

InvalidateRect(hwnd, NULL, 0);
