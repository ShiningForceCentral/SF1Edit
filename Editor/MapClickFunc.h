void MapClick(POINT p){
	int x,y;
	if(!DisplayEvent){

		if(!DisplaySprites){
			if (!DisplayHQ) {
				if (!DisplaySpecial) {
					if (p.x >= 50 && p.x <= 530 + 60 * (MMW - 8) && p.y >= 40 && p.y <= 520 + 60 * (MMH - 8)) {
						x = (p.x - 50)*MapZoom / 60;
						y = (p.y - 40)*MapZoom / 60;
						if (!SecondLayer) {
							MapData[select[mode]][x + ViewX + (y + ViewY)*MapSize[select[mode]][0]] = subselect[mode][0];
							MapWalk[select[mode]][x + ViewX + (y + ViewY)*MapSize[select[mode]][0]] = Walkable;
						} else {
							MapData2[select[mode]][x + ViewX + (y + ViewY)*MapSize[select[mode]][0]] = subselect[mode][0];
							MapGroup[select[mode]][x + ViewX + (y + ViewY)*MapSize[select[mode]][0]] = subselect[mode][1];
						}
						MapChanged = true;
					}
				} else {
					if (p.x >= 50 && p.x <= 530 + 60 * (MMW - 8) && p.y >= 40 && p.y <= 520 + 60 * (MMH - 8)) {
						x = (p.x - 50)*MapZoom / 60 + ViewX;
						y = (p.y - 40)*MapZoom / 60 + ViewY;

						if (x >= MapSize[select[mode]][0])x = MapSize[select[mode]][0]-1;
						if (y >= MapSize[select[mode]][1])y = MapSize[select[mode]][1]-1;

						if (x >= 0 && y >= 0) {
							MapSpecialTiles[select[mode]][subselect[mode][13]][0] = x;
							MapSpecialTiles[select[mode]][subselect[mode][13]][1] = y;
							MapSpecialTiles[select[mode]][subselect[mode][13]][2] = MapSpecialTiles[select[mode]][subselect[mode][13]][2] & 0x18;
							MapChanged = true;
						}
					}

				}
			} else {
				if (p.x >= 50 && p.x <= 530 + 60 * (MMW - 8) && p.y >= 40 && p.y <= 520 + 60 * (MMH - 8)) {
					x = (p.x - 50)*MapZoom / 60;
					y = (p.y - 40)*MapZoom / 60;

					MapSelect = -1;

					for (int i = 0; i<NumHQPos; i++) {

						if (x == HQPos[i][1] - ViewX && y == HQPos[i][2] - ViewY) {
							MapSelect = i;
						}
					}
				}
			}
		} else {
			if(p.x>=50&&p.x<=530+60*(MMW-8)&&p.y>=40&&p.y<=520+60*(MMH-8)){
				x=(p.x-50)*MapZoom/60;
				y=(p.y-40)*MapZoom/60;

				MapSelect = -1;

				for(int i=0;i<NumSprites[subselect[mode][12]];i++){

					if(x == Sprites[subselect[mode][12]][i][0]-ViewX && y == (Sprites[subselect[mode][12]][i][1]&0x7F)-ViewY){
						MapSelect = i;
					}
				}
			}

		}

	} else {
		if(p.x>=50&&p.x<=530+60*(MMW-8)&&p.y>=40&&p.y<=520+60*(MMH-8)){
			x=(p.x-50)*MapZoom/60;
			y=(p.y-40)*MapZoom/60;

			MapEvent[select[mode]][x+ViewX+(y+ViewY)*MapSize[select[mode]][0]]=subselect[mode][3];

			if(subselect[mode][3]==20){
				MapFlag[select[mode]][x+ViewX+(y+ViewY)*MapSize[select[mode]][0]]|=1;
			} else {
				MapFlag[select[mode]][x+ViewX+(y+ViewY)*MapSize[select[mode]][0]]|=1;
				MapFlag[select[mode]][x+ViewX+(y+ViewY)*MapSize[select[mode]][0]]^=1;
			}

			
			if(subselect[mode][3]==12||subselect[mode][3]==16||subselect[mode][3]==104){
				if(FindTele(subselect[mode][3],x+ViewX,y+ViewY,select[mode],false)!=1024){
					SetTele(subselect[mode][3],x+ViewX,y+ViewY,select[mode],subselect[mode][5],subselect[mode][6],subselect[mode][4],subselect[mode][7]);
				} else {
					AddTele(subselect[mode][3],x+ViewX,y+ViewY,select[mode],subselect[mode][7],subselect[mode][5],subselect[mode][6],subselect[mode][4],subselect[mode][7]);
				}
				/*MapTele[select[mode]][x+ViewX+(y+ViewY)*MapSize[select[mode]][0]][0]=subselect[mode][4];
				MapTele[select[mode]][x+ViewX+(y+ViewY)*MapSize[select[mode]][0]][1]=subselect[mode][5]+subselect[mode][6]*MapSize[subselect[mode][4]][0];
				MapTele[select[mode]][x+ViewX+(y+ViewY)*MapSize[select[mode]][0]][2]=subselect[mode][7];
				MapTele[subselect[mode][4]][subselect[mode][5]+subselect[mode][6]*MapSize[subselect[mode][4]][0]][0]=select[mode];
				MapTele[subselect[mode][4]][subselect[mode][5]+subselect[mode][6]*MapSize[subselect[mode][4]][0]][1]=x+ViewX+(y+ViewY)*MapSize[select[mode]][0];
				MapTele[subselect[mode][4]][subselect[mode][5]+subselect[mode][6]*MapSize[subselect[mode][4]][0]][2]=subselect[mode][7];*/
			} else {
				ClearTele(subselect[mode][3],x+ViewX,y+ViewY,select[mode]);
			}

			if(subselect[mode][3]==112){
				MapChest[select[mode]][x+ViewX+(y+ViewY)*MapSize[select[mode]][0]]=subselect[mode][8];
				MapGold[select[mode]][x+ViewX+(y+ViewY)*MapSize[select[mode]][0]]=subselect[mode][9];
			} else {
				MapChest[select[mode]][x+ViewX+(y+ViewY)*MapSize[select[mode]][0]]=-1;
				MapGold[select[mode]][x+ViewX+(y+ViewY)*MapSize[select[mode]][0]]=0;
			}
			if(subselect[mode][3]==100){
				MapRead[select[mode]][x+ViewX+(y+ViewY)*MapSize[select[mode]][0]]=subselect[mode][10];
			} else {
				MapRead[select[mode]][x+ViewX+(y+ViewY)*MapSize[select[mode]][0]]=-1;
			}


			MapChanged = true;
		}
	}
}

void MapDrag(POINT p){
	if(MapSelect!=-1){
		int x=(p.x-50)*MapZoom/60;
		int y=(p.y-40)*MapZoom/60;

		if(x>=0&&y>=0&&x<MMW*MapZoom&&y<MMH*MapZoom){
			if (!DisplayHQ) {
				Sprites[subselect[mode][12]][MapSelect][0] = x + ViewX;
				Sprites[subselect[mode][12]][MapSelect][1] = (Sprites[subselect[mode][12]][MapSelect][1] & 0x80) + y + ViewY;
			} else {
				HQPos[MapSelect][1] = x + ViewX;
				HQPos[MapSelect][2] = y + ViewY;
			}
		}
	}

}