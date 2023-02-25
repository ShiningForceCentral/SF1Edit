		if(wParam &	MK_LBUTTON){
			GetCursorPos(&p);
			ScreenToClient(hWnd,&p);
			p.y-=40;
			switch(submode[mode]){
				case 0:
					if(p.x>=82&&p.x<82+FSSize[subselect[mode][submode[mode]]][subselect[mode][submode[mode]+32]][0]*4&&p.y>=67&&p.y<67+FSSize[subselect[mode][submode[mode]]][subselect[mode][submode[mode]+32]][1]*4){
						if(!Pencil){
							dx=color;
							color=0;
						}
						for(u=0;u<size&&x+u<FSSize[subselect[mode][submode[mode]]][subselect[mode][submode[mode]+32]][0];u++){
							for(v=0;v<size&&y+v<FSSize[subselect[mode][submode[mode]]][subselect[mode][submode[mode]+32]][1];v++){
								ForceSprites[subselect[mode][submode[mode]]][subselect[mode][submode[mode]+32]][(p.x-82)/4+u+((p.y-67)/4+v)*FSSize[subselect[mode][submode[mode]]][subselect[mode][submode[mode]+32]][0]]=color;
								x=(p.x-82)/4+u;
								y=(p.y-67)/4+10+v;
								l = subselect[mode][submode[mode]+64];

								for(i=0;i<4;i++){
									for(j=0;j<4;j++){
										SetPixel(hdc,x*4+i+82,y*4+j+67,RGB(FSPalette[subselect[mode][submode[mode]]][l][color][0],FSPalette[subselect[mode][submode[mode]]][l][color][1],FSPalette[subselect[mode][submode[mode]]][l][color][2]));
									}
								}
							}
						}
						if(!Pencil){
							color=dx;
						}
					}
					break;
				case 1:
					if(p.x>=82&&p.x<82+ESSize[subselect[mode][submode[mode]]][subselect[mode][submode[mode]+32]][0]*4&&p.y>=67&&p.y<67+ESSize[subselect[mode][submode[mode]]][subselect[mode][submode[mode]+32]][1]*4){
						if(!Pencil){
							dx=color;
							color=0;
						}
						for(u=0;u<size&&x+u<ESSize[subselect[mode][submode[mode]]][subselect[mode][submode[mode]+32]][0];u++){
							for(v=0;v<size&&y+v<ESSize[subselect[mode][submode[mode]]][subselect[mode][submode[mode]+32]][1];v++){
								EnemySprites[subselect[mode][submode[mode]]][subselect[mode][submode[mode]+32]][(p.x-82)/4+u+((p.y-67)/4+v)*ESSize[subselect[mode][submode[mode]]][subselect[mode][submode[mode]+32]][0]]=color;
								x=(p.x-82)/4+u;
								y=(p.y-67)/4+10+v;
								l = subselect[mode][submode[mode]+64];

								for(i=0;i<4;i++){
									for(j=0;j<4;j++){
										SetPixel(hdc,x*4+i+82,y*4+j+67,RGB(ESPalette[subselect[mode][submode[mode]]][l][color][0],ESPalette[subselect[mode][submode[mode]]][l][color][1],ESPalette[subselect[mode][submode[mode]]][l][color][2]));
									}
								}
							}
						}
						if(!Pencil){
							color=dx;
						}
					}
					break;
				case 3:
					if(p.x>=82&&p.x<82+BGSize[subselect[mode][submode[mode]]][0]*4&&p.y>=67&&p.y<67+BGSize[subselect[mode][submode[mode]]][1]*4){
						if(!Pencil){
							dx=color;
							color=0;
						}
						for(u=0;u<size&&x+u<BGSize[subselect[mode][submode[mode]]][0];u++){
							for(v=0;v<size&&y+v<BGSize[subselect[mode][submode[mode]]][1];v++){
								Backgrounds[subselect[mode][submode[mode]]][(p.x-82)/4+u+((p.y-67)/4+v)*BGSize[subselect[mode][submode[mode]]][0]]=color;
								x=(p.x-82)/4+u;
								y=(p.y-67)/4+10+v;
								l = subselect[mode][submode[mode]+64];

								for(i=0;i<4;i++){
									for(j=0;j<4;j++){
										SetPixel(hdc,x*4+i+82,y*4+j+67,RGB(BGPalette[subselect[mode][submode[mode]]][l][color][0],BGPalette[subselect[mode][submode[mode]]][l][color][1],BGPalette[subselect[mode][submode[mode]]][l][color][2]));
									}
								}
							}
						}
						if(!Pencil){
							color=dx;
						}
					}
					break;
				case 4:
					if(p.x>=82&&p.x<82+PFSize[subselect[mode][submode[mode]]][0]*4&&p.y>=67&&p.y<67+PFSize[subselect[mode][submode[mode]]][1]*4){
						if(!Pencil){
							dx=color;
							color=0;
						}
						for(u=0;u<size&&x+u<PFSize[subselect[mode][submode[mode]]][0];u++){
							for(v=0;v<size&&y+v<PFSize[subselect[mode][submode[mode]]][1];v++){
								Platforms[subselect[mode][submode[mode]]][(p.x-82)/4+u+((p.y-67)/4+v)*PFSize[subselect[mode][submode[mode]]][0]]=color;
								x=(p.x-82)/4+u;
								y=(p.y-67)/4+10+v;
								l = subselect[mode][submode[mode]+64];

								for(i=0;i<4;i++){
									for(j=0;j<4;j++){
										SetPixel(hdc,x*4+i+82,y*4+j+67,RGB(PFPalette[subselect[mode][submode[mode]]][color][0],PFPalette[subselect[mode][submode[mode]]][color][1],PFPalette[subselect[mode][submode[mode]]][color][2]));
									}
								}
							}
						}
						if(!Pencil){
							color=dx;
						}

					}
					break;
				case 6:
					if(p.x>=82&&p.x<82+POSize[subselect[mode][submode[mode]]][0]*4&&p.y>=67&&p.y<67+POSize[subselect[mode][submode[mode]]][1]*4){
						if(!Pencil){
							dx=color;
							color=0;
						}
						for(u=0;u<size&&x+u<POSize[subselect[mode][submode[mode]]][0];u++){
							for(v=0;v<size&&y+v<POSize[subselect[mode][submode[mode]]][1];v++){
								Portraits[subselect[mode][submode[mode]]][(p.x-82)/4+u+((p.y-67)/4+v)*POSize[subselect[mode][submode[mode]]][0]]=color;
								x=(p.x-82)/4+u;
								y=(p.y-67)/4+10+v;
								l = subselect[mode][submode[mode]+64];

								for(i=0;i<4;i++){
									for(j=0;j<4;j++){
										SetPixel(hdc,x*4+i+82,y*4+j+67,RGB(POPalette[subselect[mode][submode[mode]]][color][0],POPalette[subselect[mode][submode[mode]]][color][1],POPalette[subselect[mode][submode[mode]]][color][2]));
									}
								}
							}
						}
						if(!Pencil){
							color=dx;
						}

					}
					break;
				case 7:
					if(p.x>=82&&p.x<82+MSSize[subselect[mode][submode[mode]]][subselect[mode][submode[mode]+32]][0]*4&&p.y>=67&&p.y<67+MSSize[subselect[mode][submode[mode]]][subselect[mode][submode[mode]+32]][1]*4){
						if(!Pencil){
							dx=color;
							color=0;
						}
						for(u=0;u<size&&x+u<MSSize[subselect[mode][submode[mode]]][subselect[mode][submode[mode]+32]][0];u++){
							for(v=0;v<size&&y+v<MSSize[subselect[mode][submode[mode]]][subselect[mode][submode[mode]+32]][1];v++){
								MapSprites[subselect[mode][submode[mode]]][subselect[mode][submode[mode]+32]][(p.x-82)/4+u+((p.y-67)/4+v)*MSSize[subselect[mode][submode[mode]]][subselect[mode][submode[mode]+32]][0]]=color;
								x=(p.x-82)/4+u;
								y=(p.y-67)/4+10+v;
								l = subselect[mode][submode[mode]+64];

								for(i=0;i<4;i++){
									for(j=0;j<4;j++){
										if (MSPalette[subselect[mode][submode[mode]]])SetPixel(hdc,x*4+i+82,y*4+j+67,RGB(EMSPalette[color][0],EMSPalette[color][1],EMSPalette[color][2]));
										else SetPixel(hdc, x * 4 + i + 82, y * 4 + j + 67, RGB(FMSPalette[color][0], FMSPalette[color][1], FMSPalette[color][2]));
									}
								}
							}
						}
						if(!Pencil){
							color=dx;
						}

					}
					break;
			case 8:
				if(p.x>=82&&p.x<82+TSSize[subselect[mode][submode[mode]]][0]*4&&p.y>=67&&p.y<67+TSSize[subselect[mode][submode[mode]]][1]*4){
					if(!Pencil){
						dx=color;
						color=0;
					}
					for(u=0;u<size&&x+u<TSSize[subselect[mode][submode[mode]]][0];u++){
						for(v=0;v<size&&y+v<TSSize[subselect[mode][submode[mode]]][1];v++){
							p2.x=p.x-82;
							p2.y=p.y-67;
							TilesetToPixel(p2);
							Tilesets[subselect[mode][submode[mode]]][(p2.x)/4+u+((p2.y)/4+v)*TSSize[subselect[mode][submode[mode]]][0]]=color;
							x=(p.x-82)/4+u;
							y=(p.y-67)/4+10+v;
							l = subselect[mode][submode[mode]+64];

							for(i=0;i<4;i++){
								for(j=0;j<4;j++){
									SetPixel(hdc,x*4+i+82,y*4+j+67,RGB(TSPalette[TSPalNums[subselect[mode][submode[mode]]]][color][0],TSPalette[TSPalNums[subselect[mode][submode[mode]]]][color][1],TSPalette[TSPalNums[subselect[mode][submode[mode]]]][color][2]));
								}
							}
						}
					}
					if(!Pencil){
						color=dx;
					}

				}
				break;
				case 9:
					if(p.x>=82&&p.x<82+EFSize[subselect[mode][submode[mode]]][0]*4&&p.y>=67&&p.y<67+EFSize[subselect[mode][submode[mode]]][1]*4){
						if(!Pencil){
							dx=color;
							color=0;
						}
						for(u=0;u<size&&x+u<EFSize[subselect[mode][submode[mode]]][0];u++){
							for(v=0;v<size&&y+v<EFSize[subselect[mode][submode[mode]]][1];v++){
								Effects[subselect[mode][submode[mode]]][(p.x-82)/4+u+((p.y-67)/4+v)*EFSize[subselect[mode][submode[mode]]][0]]=color;
								x=(p.x-82)/4+u;
								y=(p.y-67)/4+10+v;
								l = subselect[mode][submode[mode]+64];

								for(i=0;i<4;i++){
									for(j=0;j<4;j++){
										SetPixel(hdc,x*4+i+82,y*4+j+67,RGB(EFPalette[subselect[mode][submode[mode]]][color][0],EFPalette[subselect[mode][submode[mode]]][color][1],EFPalette[subselect[mode][submode[mode]]][color][2]));
									}
								}
							}
						}
						if(!Pencil){
							color=dx;
						}

					}
					break;
			}

		}

		if (submode[mode] == 6 && subselect[mode][submode[mode] + 96]) {
			GetCursorPos(&p);
			ScreenToClient(hWnd, &p);
			p.y -= 40;
			PatBlt(memdc, 82, 67+32*8, 150, 20, PATCOPY);
			if (p.x >= 82 && p.x <= 82+32*8 && p.y >= 67 && p.y <= 67+32*8) {
				x = (p.x - 82) / 32;
				y = (p.y - 67) / 32;
				x += ViewX;
				y += ViewY;
				sprintf(out, "%d, %d", x, y);
				TextOut(memdc, 82, 67+32*8, out, strlen(out));
			}
			BitBlt(hdc, 82, 67 + 32 * 8 + 40, 150, 20, memdc, 82, 67 + 32 * 8, SRCCOPY);
		}