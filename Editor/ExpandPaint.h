	TextOut(memdc,350,50,"Rom Size",8);
	d = 1.5;
	for(i=0;i<10;i++){
		sprintf(out,"%.1f MB",d);
		TextOut(memdc,295+150*(i%2),75+(i-(i%2))*8,out,strlen(out));
		d+=0.5;
		if(sizesel==i)SelectObject(bmpdc,checkon);
		else SelectObject(bmpdc,checkoff);
		BitBlt(memdc,278+150*(i%2),76+(i-(i%2))*8,13,13,bmpdc,0,0,SRCCOPY);
	}
	Rectangle(memdc,352,162,410,190);
	TextOut(memdc,357,169,"Expand",6);