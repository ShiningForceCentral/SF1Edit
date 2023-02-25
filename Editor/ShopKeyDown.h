			switch(wParam){
				case VK_ESCAPE:
				case VK_RETURN:
					menu=0;
					break;
				case VK_UP:
					select[mode]-=1;
					select[mode]%=24;
					break;
				case VK_DOWN:
					select[mode]+=1;
					select[mode]%=24;
					break;
			}
			if(select[mode]<0)select[mode]+=24;
