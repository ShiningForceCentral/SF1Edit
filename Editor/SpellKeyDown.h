			switch(wParam){
					break;
				case VK_UP:
					select[mode]-=1;
					select[mode]%=16+16*ExpandSpells;
					break;
				case VK_DOWN:
					select[mode]+=1;
					select[mode]%=16+16*ExpandSpells;
					break;
			}
			if(select[mode]<0)select[mode]+=16+16*ExpandSpells;