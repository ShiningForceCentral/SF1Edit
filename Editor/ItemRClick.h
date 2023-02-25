if(submode[mode]==0){
	for(i=0;i<16;i++){
		for(j=0;j<24;j++){
			if(p.x>=575+8*i&&p.x<583+8*i&&p.y>=310+8*j&&p.y<318+8*j){
				for(int dx=0;dx<size&&i+dx<16;dx++){
					for(int dy=0;dy<size&&j+dy<24;dy++){
						color=ItemImages[select[mode]][(j+dy)*16+i+dx];
					}
				}
			}
		}
	}
}