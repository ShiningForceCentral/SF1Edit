if(submode[mode]==0){
			switch(wParam){
				case VK_LEFT:
					select[mode]-=32;
					select[mode]%=63;
					break;
				case VK_RIGHT:
					select[mode]+=32;
					select[mode]%=63;
					break;
				case VK_UP:
					select[mode]-=1;
					select[mode]%=63;
					break;
				case VK_DOWN:
					select[mode]+=1;
					select[mode]%=63;
					break;
				case VK_PRIOR:
					if (NumItems == 128) {
						ItemView -= 64;
						ItemView %= NumItems;
						select[mode] -= 64;
						if (select[mode] < 0)select[mode] += NumItems;
					}
					break;
				case VK_NEXT:
					if (NumItems == 128) {
						ItemView += 64;
						ItemView %= NumItems;
						select[mode] += 64;
						select[mode] %= NumItems;
					}
					break;

			}
			if(select[mode]<0)select[mode]+=63;
			while(ItemView==64&&select[mode]<64)select[mode]+=63;
}

if(submode[mode]==1){
			switch(wParam){
				case VK_ESCAPE:
					submode[mode]=0;
					focus=0;
					break;
			}
}
if(submode[mode]==2){
			switch(wParam){
				case VK_ESCAPE:
					submode[mode]=0;
					focus=0;
					break;
			}
}