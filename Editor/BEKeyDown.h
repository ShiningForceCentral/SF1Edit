switch(wParam){
	case VK_DELETE:
		BEGraphs[subselect[mode][0]]->remove();
		break;
	case VK_ESCAPE:
		menu=0;
		searchstart = -1;
		break;
	default:
		BEGraphs[subselect[mode][0]]->keydown(wParam);
		break;
}