GetCursorPos(&p);
ScreenToClient(hWnd, &p);
p.y -= 40;

if (ignorerelease)ignorerelease = false;
else {
	BSGraphs[subselect[mode][0]]->release(p.x, p.y);
	//propagateBank(BSGraphs[subselect[mode][0]], BSGraphs[subselect[mode][0]]->nodes.head->data, 0);
}
