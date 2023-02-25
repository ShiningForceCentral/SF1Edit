if (GET_WHEEL_DELTA_WPARAM(wParam) > 0) del = 16;
else del = -16;

BExitGraph * bex;
bex = BExitGraphs[subselect[mode][0]];


if (GetKeyState(VK_SHIFT) & 0x80 || GetKeyState(VK_LSHIFT) & 0x80 || GetKeyState(VK_RSHIFT) & 0x80) {
	bex->vx -= (del)*bex->graphzoom;
} else {
	bex->vy -= (del)*bex->graphzoom;
}
if (bex->vx <= -bex->w)bex->vx = -bex->w + 1;
if (bex->vy <= -bex->h)bex->vy = -bex->h + 1;

InvalidateRect(hwnd, NULL, 0);
