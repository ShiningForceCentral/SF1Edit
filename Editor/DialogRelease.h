GetCursorPos(&p);
ScreenToClient(hWnd,&p);
p.y-=40;

if(ignorerelease)ignorerelease=false;
else {
	DialogGraphs[subselect[mode][0]]->release(p.x, p.y);
	propagateBank(DialogGraphs[subselect[mode][0]], DialogGraphs[subselect[mode][0]]->nodes.head->data, 0);
}
