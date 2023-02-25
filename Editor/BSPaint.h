if (!ScriptsLoaded) {
	if (strlen(file)) {

	} else {
		TextOut(memdc, 55, 33, "Load a ROM first.", 17);
	}
} else {
	BSGraphs[subselect[mode][0]]->paint(memdc);
}
