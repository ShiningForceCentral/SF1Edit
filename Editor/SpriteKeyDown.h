			switch(wParam){
					break;
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