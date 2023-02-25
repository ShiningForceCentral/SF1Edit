if (ScriptsLoaded) {
	if (p.x >= 76 && p.x <= 145 && p.y >= 10 && p.y <= 25) {
		focus = 1;
	}

	if (p.x >= 550 && p.x <= 700 && p.y >= 10 && p.y <= 25) {
		focus = 4;
	}

	if (p.x >= 55 && p.x <= 75 && p.y >= 8 && p.y <= 28) {
		u = subselect[mode][0];
		subselect[mode][0]--;
		if (subselect[mode][0] < 0)subselect[mode][0] = NUM_WC - 1;
		WCGraphs[subselect[mode][0]]->w = WCGraphs[u]->w;
		WCGraphs[subselect[mode][0]]->h = WCGraphs[u]->h;
		WCGraphs[subselect[mode][0]]->buildList();
		//WCGraphs[subselect[mode][0]]->vx = 0;
		//WCGraphs[subselect[mode][0]]->vy = 0;
	}

	if (p.x >= 146 && p.x <= 166 && p.y >= 8 && p.y <= 28) {
		u = subselect[mode][0];
		subselect[mode][0]++;
		if (subselect[mode][0] > NUM_WC - 1)subselect[mode][0] = 0;
		WCGraphs[subselect[mode][0]]->w = WCGraphs[u]->w;
		WCGraphs[subselect[mode][0]]->h = WCGraphs[u]->h;
		WCGraphs[subselect[mode][0]]->buildList();
		//WCGraphs[subselect[mode][0]]->vx = 0;
		//WCGraphs[subselect[mode][0]]->vy = 0;
	}

	WCGraphs[subselect[mode][0]]->click(p.x, p.y);
}