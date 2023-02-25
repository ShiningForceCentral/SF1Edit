		if(submode[mode]==0){	
			switch(wParam){
				case VK_UP:
					select[mode]-=1;
					select[mode]%=30;
					focus=1;
					break;
				case VK_DOWN:
					select[mode]+=1;
					select[mode]%=30;
					focus=1;
					break;
				case VK_ESCAPE:
					menu=0;
					break;
			}
		}
		if(submode[mode]==2){
			switch(wParam){
				case VK_HOME:
					switch (BattleMode) {
						case 0:
							if (BattleSelect != -1)BattleSelect--;
							if (BattleSelect < 0)BattleSelect = NumEnemies[select[mode]] - 1;
							break;
						case 1:
							BattleTerrain--;
							if (BattleTerrain<0)BattleTerrain = 15;
							break;
						case 2:
							BattleReg--;
							if (BattleReg<0)BattleReg = 6;
							break;
						case 3:
							BattleEntrance--;
							if (BattleEntrance<0)BattleEntrance = 3;
							break;
						case 4:
							BattleExitSet--;
							if (BattleExitSet<0)BattleExitSet = 2;

							if (BattExits[select[mode]][BattleExitSet] == 255)BattleExitSet = 0;
							break;
					}
					break;
				case VK_END:
					switch (BattleMode) {
						case 0:
							BattleSelect++;
							if (BattleSelect > NumEnemies[select[mode]] - 1)BattleSelect = 0;
							break;
						case 1:
							BattleTerrain++;
							BattleTerrain %= 16;
							break;
						case 2:
							BattleReg++;
							BattleReg %= 7;
							break;
						case 3:
							BattleEntrance++;
							BattleEntrance %= 4;
							break;
						case 4:
							BattleExitSet++;
							if (BattleExitSet>2)BattleExitSet = 0;
							if (BattExits[select[mode]][BattleExitSet] == 255)BattleExitSet = 0;
							break;
					}
					break;
				case VK_NEXT:
					select[mode]-=1;
					select[mode]%=30;
					BattleEntrance=BattleIndex[select[mode]][3];
					ViewX=0;
					ViewY=0;
					BattleSelect=-1;
					BattleDrag=-1;
					focus=1;
					break;
				case VK_PRIOR:
					select[mode]+=1;
					select[mode]%=30;
					BattleEntrance=BattleIndex[select[mode]][3];
					ViewX=0;
					ViewY=0;
					BattleSelect=-1;
					BattleDrag=-1;
					focus=1;
					break;
				case VK_UP:
					if(ViewY>0)ViewY-=1;
					break;
				case VK_LEFT:
					if(ViewX>0)ViewX-=1;
					break;
				case VK_DOWN:
					if(ViewY<MapSize[MapHeader[BattleHeaderPos[select[mode]]][1]][1]-10)ViewY+=1;
					break;
				case VK_RIGHT:
					if(ViewX<MapSize[MapHeader[BattleHeaderPos[select[mode]]][1]][0]-10)ViewX+=1;
					break;
				case VK_DELETE:
					if(BattleMode==0){
						RemoveEnemy();
					}
					break;
			}
		}

		if(submode[mode]==3){	
			switch(wParam){
				case VK_UP:
					select[mode]-=1;
					select[mode]%=23;
					if(select[mode]==6)select[mode]=4;
					break;
				case VK_DOWN:
					select[mode]+=1;
					select[mode]%=23;
					if(select[mode]==5)select[mode]=7;
					break;
				case VK_ESCAPE:
					if(subselect[mode][0]!=-1){
						submode[mode]=2;
						select[mode]=subselect[mode][0];
						subselect[mode][0]=-1;
					}
					break;
			}
			if(select[mode]<0)select[mode]+=23;
		}

			if(select[mode]<0)select[mode]+=30;
			if(submode[mode]==1&&(wParam==VK_ESCAPE||wParam==VK_RETURN)){
				submode[mode]=2;
				menu=0;
			}
			
		if(submode[mode]==4){	
			switch(wParam){
				case VK_ESCAPE:
					submode[mode]=1;
					break;
			}
		}