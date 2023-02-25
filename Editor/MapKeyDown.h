		if(submode[mode]==0){
			switch(wParam){
				case VK_UP:
				case VK_LEFT:
					select[mode]-=1;
					select[mode]%=54;
					focus=1;
					break;
				case VK_DOWN:
				case VK_RIGHT:
					select[mode]+=1;
					select[mode]%=54;
					focus=1;
					break;
			}
			if(select[mode]<0)select[mode]+=54;
		}

		if(submode[mode]==1){
			switch(wParam){
				case VK_UP:
				case VK_LEFT:
					select[mode]-=1;
					select[mode]%=8;
					focus=1;
					break;
				case VK_DOWN:
				case VK_RIGHT:
					select[mode]+=1;
					select[mode]%=8;
					focus=1;
					break;
			}
			if(select[mode]<0)select[mode]+=8;
		}

		if(submode[mode]==2){
			switch(wParam){
				case VK_SUBTRACT:
					select[mode]--;
					if (select[mode]<0)select[mode] = NUM_MAPS - 1;
					curtiles = MapGraphics[select[mode]][0];
					curtiles2 = MapGraphics[select[mode]][1];
					if (ViewX >= MapSize[select[mode]][0] - 8 * MapZoom)ViewX = MapSize[select[mode]][0] - 8 * MapZoom;
					if (ViewY >= MapSize[select[mode]][1] - 8 * MapZoom)ViewY = MapSize[select[mode]][1] - 8 * MapZoom;

					if (ViewX<0)ViewX = 0;
					if (ViewY<0)ViewY = 0;

					if (MapSpriteSet[select[mode]] != 0xFF) subselect[mode][12] = MapSpriteSet[select[mode]];
					break;

				case VK_ADD:
					select[mode]++;
					if (select[mode]>NUM_MAPS - 1)select[mode] = 0;
					curtiles = MapGraphics[select[mode]][0];
					curtiles2 = MapGraphics[select[mode]][1];
					if (ViewX >= MapSize[select[mode]][0] - 8 * MapZoom)ViewX = MapSize[select[mode]][0] - 8 * MapZoom;
					if (ViewY >= MapSize[select[mode]][1] - 8 * MapZoom)ViewY = MapSize[select[mode]][1] - 8 * MapZoom;

					if (ViewX<0)ViewX = 0;
					if (ViewY<0)ViewY = 0;

					if (MapSpriteSet[select[mode]] != 0xFF) subselect[mode][12] = MapSpriteSet[select[mode]];
					break;

				case VK_UP:
					if(ViewY>0)ViewY-=1;
					break;
				case VK_LEFT:
					if(ViewX>0)ViewX-=1;
					break;
				case VK_DOWN:
					if(ViewY<MapSize[select[mode]][1]-8*MapZoom)ViewY+=1;
					break;
				case VK_RIGHT:
					if(ViewX<MapSize[select[mode]][0]-8*MapZoom)ViewX+=1;
					break;
				case VK_HOME:
					curtiles--;
					if(curtiles<0)curtiles=23;
					break;
				case VK_END:
					curtiles++;
					if(curtiles>23)curtiles=0;
					break;
				case VK_PRIOR:
					curtiles2--;
					if(curtiles2<0)curtiles2=23;
					break;
				case VK_NEXT:
					curtiles2++;
					if(curtiles2>23)curtiles2=0;
					break;
				case VK_DELETE:

					if(MapSelect!=255&&NumSprites[subselect[mode][12]]>0){
						NumSprites[subselect[mode][12]]--;
						
						if(MapSelect!=NumSprites[subselect[mode][12]]){

							Sprites[subselect[mode][12]][MapSelect][0]=Sprites[subselect[mode][12]][NumSprites[subselect[mode][12]]][0];
							Sprites[subselect[mode][12]][MapSelect][1]=Sprites[subselect[mode][12]][NumSprites[subselect[mode][12]]][1];

							Sprites[subselect[mode][12]][MapSelect][2]=Sprites[subselect[mode][12]][NumSprites[subselect[mode][12]]][2];
							Sprites[subselect[mode][12]][MapSelect][3]=Sprites[subselect[mode][12]][NumSprites[subselect[mode][12]]][3];
							Sprites[subselect[mode][12]][MapSelect][4]=Sprites[subselect[mode][12]][NumSprites[subselect[mode][12]]][4];
							Sprites[subselect[mode][12]][MapSelect][5]=Sprites[subselect[mode][12]][NumSprites[subselect[mode][12]]][5];
						
						}
						MapSelect=255;
					}

					break;
			}
			if(select[mode]<0)select[mode]+=NUM_MAPS;
		}

		if(submode[mode]==3){
			switch(wParam){
				case VK_ESCAPE:
					menu=0;
					break;
				case VK_DOWN:
					subselect[mode][11]++;
					break;
				case VK_UP:
					if(subselect[mode][11]>0)subselect[mode][11]--;
					break;
			}
		}
