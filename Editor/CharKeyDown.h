			switch(wParam){
				case VK_DELETE:
					if(mode==1&&(focus==2||focus==3)){
						if(NumLearn[select[mode]]){
							NumLearn[select[mode]]--;
							for(i=subfocus;i<NumLearn[select[mode]];i++){
								Learn[select[mode]][i][0]=Learn[select[mode]][i+1][0];
								Learn[select[mode]][i][1]=Learn[select[mode]][i+1][1];
							}
						}
						focus=0;
					}
					break;
				case VK_UP:
					select[mode] += (EXT_CHARS - 1);
					select[mode] %= EXT_CHARS;
					select[mode] += CharView;

					if (select[mode] >= MAX_CHARS)select[mode] = MAX_CHARS - 1;
					break;
				case VK_DOWN:
					select[mode] += 1;
					select[mode] %= EXT_CHARS;
					select[mode] += CharView;

					if (select[mode] >= MAX_CHARS)select[mode] = MAX_CHARS - 1;
					break;
				case VK_RETURN:
				case VK_ESCAPE:
					menu=0;
					submode[mode]=0;
					break;
			}
			if(select[mode]<0)select[mode]+=30;