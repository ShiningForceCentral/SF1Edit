if (GET_WHEEL_DELTA_WPARAM(wParam) > 0) del = 16;
else del = -16;

DialogGraph * dg;
dg = DialogGraphs[subselect[mode][0]];


if (GetKeyState(VK_SHIFT) & 0x80 || GetKeyState(VK_LSHIFT) & 0x80 || GetKeyState(VK_RSHIFT) & 0x80) {
	dg->vx -= (del)*dg->graphzoom;
} else {
	dg->vy -= (del)*dg->graphzoom;
}
if (dg->vx <= -dg->w)dg->vx = -dg->w + 1;
if (dg->vy <= -dg->h)dg->vy = -dg->h + 1;

InvalidateRect(hwnd, NULL, 0);
