GetCursorPos(&p);
ScreenToClient(hWnd, &p);
p.y -= 40;

if (ignorerelease)ignorerelease = false;
else BExitGraphs[subselect[mode][0]]->release(p.x, p.y);
