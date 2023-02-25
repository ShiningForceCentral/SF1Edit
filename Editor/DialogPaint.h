if (!ScriptsLoaded) {
	if (strlen(file)) {
		Rectangle(memdc, 50, 30, 176, 52);
		TextOut(memdc, 73, 33, "Load Scripts", 14);
	} else {
		TextOut(memdc, 55, 33, "Load a ROM first.", 17);
	}
} else {
	DialogGraphs[subselect[mode][0]]->paint(memdc);
}