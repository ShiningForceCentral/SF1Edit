switch (wParam) {
	case VK_DELETE:
		BSGraphs[subselect[mode][0]]->remove();
		break;
	case VK_ESCAPE:
		menu = 0;
		searchstart = -1;
		break;
	default:
		BSGraphs[subselect[mode][0]]->keydown(wParam);
		break;
}