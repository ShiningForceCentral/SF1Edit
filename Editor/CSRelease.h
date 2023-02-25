GetCursorPos(&p);
ScreenToClient(hWnd, &p);
p.y -= 40;

if (ignorerelease)ignorerelease = false;
else {
	CSGraphs[subselect[mode][0]]->release(p.x, p.y);
	//propagateBank(CSGraphs[subselect[mode][0]], CSGraphs[subselect[mode][0]]->nodes.head->data, 0);
}
