			switch(wParam){
				case VK_LEFT:
					select[mode]-=1;
					select[mode]%=80;
					break;
				case VK_RIGHT:
					select[mode]+=1;
					select[mode]%=80;
					break;
				case VK_UP:
					select[mode]-=8;
					select[mode]%=80;
					break;
				case VK_DOWN:
					select[mode]+=8;
					select[mode]%=80;
					break;
			}
			if(select[mode]<0)select[mode]+=80;