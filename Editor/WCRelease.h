GetCursorPos(&p);
ScreenToClient(hWnd, &p);
p.y -= 40;

if (ignorerelease)ignorerelease = false;
else {
	WCGraphs[subselect[mode][0]]->release(p.x, p.y);
	//propagateBank(WCGraphs[subselect[mode][0]], WCGraphs[subselect[mode][0]]->nodes.head->data, 0);
}
