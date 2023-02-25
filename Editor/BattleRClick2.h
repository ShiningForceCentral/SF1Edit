if (BattleMode == 1) {
	if (p.x >= 50 && p.x < 50 + 48 * BMW&&p.y >= 40 && p.y <= 40 + 48 * BMH) {
		i = (p.x - 50)*MapZoom / 48 + ViewX - 1;
		j = (p.y - 40)*MapZoom / 48 + ViewY - 1;
		BattleTerrain = NonBattleLand[select[mode]][i + (j)*NonBattleSize[select[mode]][0]];
	}
}