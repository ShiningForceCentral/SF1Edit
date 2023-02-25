if (GET_WHEEL_DELTA_WPARAM(wParam) > 0) del = 16;
else del = -16;

BSGraph * bs;
bs = BSGraphs[subselect[mode][0]];


if (GetKeyState(VK_SHIFT) & 0x80 || GetKeyState(VK_LSHIFT) & 0x80 || GetKeyState(VK_RSHIFT) & 0x80) {
	bs->vx -= (del)*bs->graphzoom;
} else {
	bs->vy -= (del)*bs->graphzoom;
}
if (bs->vx <= -bs->w)bs->vx = -bs->w + 1;
if (bs->vy <= -bs->h)bs->vy = -bs->h + 1;

InvalidateRect(hwnd, NULL, 0);
