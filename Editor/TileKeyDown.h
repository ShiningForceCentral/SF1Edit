			switch(wParam){
					break;
				case VK_UP:
				case VK_LEFT:
					select[mode]-=1;
					select[mode]%=8713;
					focus=1;
					break;
				case VK_DOWN:
				case VK_RIGHT:
					select[mode]+=1;
					select[mode]%=8713;
					focus=1;
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
			}
			if(select[mode]<0)select[mode]+=8713;