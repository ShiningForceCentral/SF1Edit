			if(submode[mode]==2){
				GetCursorPos(&p);
				ScreenToClient(hWnd,&p);
				p.y-=40;

				if(MapDragging){
					if(p.x - MapDragPos[0] >= 60/MapZoom){
						if(ViewX>0){
							ViewX--;
							MapDragPos[0]+=60/MapZoom;
							InvalidateRect(hWnd,NULL,0);
						}
					}
					if(p.x - MapDragPos[0] <= -60/MapZoom){
						if(ViewX<MapSize[select[mode]][0]-8*MapZoom){
							ViewX++;
							MapDragPos[0]-=60/MapZoom;
							InvalidateRect(hWnd,NULL,0);
						}
					}

					if(p.y - MapDragPos[1] >= 60/MapZoom){
						if(ViewY>0){
							ViewY--;
							MapDragPos[1]+=60/MapZoom;
							InvalidateRect(hWnd,NULL,0);
						}
					}
					if(p.y - MapDragPos[1] <= -60/MapZoom){
						if(ViewY<MapSize[select[mode]][1]-8*MapZoom){
							ViewY++;
							MapDragPos[1]-=60/MapZoom;
							InvalidateRect(hWnd,NULL,0);
						}
					}
				}

				PatBlt(memdc,50,560+60*(MMH-8),150,20,PATCOPY);
				if(p.x>=50&&p.x<=50+60*MMW&&p.y>=40&&p.y<=40+60*MMH){
					x=(p.x-50)*MapZoom/60;
					y=(p.y-40)*MapZoom/60;
					x+=ViewX;
					y+=ViewY;
					sprintf(out,"%d, %d",x,y);
					TextOut(memdc,50,560+60*(MMH-8),out,strlen(out));
				}
				BitBlt(hdc,50,560+60*(MMH-8),150,20,memdc,50,560+60*(MMH-8),SRCCOPY);

				if(wParam & MK_LBUTTON && ldown){
					if(DisplaySprites || DisplayHQ)MapDrag(p);
					else MapClick(p);
					InvalidateRect(hWnd,NULL,0);
				}
			}