if (ScriptsLoaded) {
	if (p.x >= 76 && p.x <= 145 && p.y >= 10 && p.y <= 25) {
		focus = 1;
	}

	if (p.x >= 55 && p.x <= 75 && p.y >= 8 && p.y <= 28) {
		u = subselect[mode][0];
		subselect[mode][0]--;
		if (subselect[mode][0] < 0)subselect[mode][0] = NUM_CS - 1;
		CSGraphs[subselect[mode][0]]->w = CSGraphs[u]->w;
		CSGraphs[subselect[mode][0]]->h = CSGraphs[u]->h;
		CSGraphs[subselect[mode][0]]->buildList();
		//CSGraphs[subselect[mode][0]]->vx = 0;
		//CSGraphs[subselect[mode][0]]->vy = 0;
	}

	if (p.x >= 146 && p.x <= 166 && p.y >= 8 && p.y <= 28) {
		u = subselect[mode][0];
		subselect[mode][0]++;
		if (subselect[mode][0] > NUM_CS - 1)subselect[mode][0] = 0;
		CSGraphs[subselect[mode][0]]->w = CSGraphs[u]->w;
		CSGraphs[subselect[mode][0]]->h = CSGraphs[u]->h;
		CSGraphs[subselect[mode][0]]->buildList();
		//CSGraphs[subselect[mode][0]]->vx = 0;
		//CSGraphs[subselect[mode][0]]->vy = 0;
	}

	CSGraphs[subselect[mode][0]]->click(p.x, p.y);
}