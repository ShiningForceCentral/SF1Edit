switch(wParam){
	case VK_DELETE:
		DialogGraphs[subselect[mode][0]]->remove();
		break;
	case VK_ESCAPE:
		menu=0;
		searchstart = -1;
		break;
	default:
		DialogGraphs[subselect[mode][0]]->keydown(wParam);
		break;
}