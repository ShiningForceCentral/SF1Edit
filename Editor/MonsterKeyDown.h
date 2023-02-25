			switch(wParam){
				case VK_LEFT:
					select[mode]-=37;
					select[mode]+=73;
					select[mode]%=73;
					select[mode]+=MonsterView;
					break;
				case VK_RIGHT:
					select[mode]+=37;
					select[mode]%=73;
					select[mode]+=MonsterView;
					break;
				case VK_UP:
					select[mode]-=1;
					select[mode]+=73;
					select[mode]%=73;
					select[mode]+=MonsterView;
					break;
				case VK_DOWN:
					select[mode]+=1;
					select[mode]%=73;
					select[mode]+=MonsterView;
					break;
				case VK_PRIOR:
					if (NumMonsters == 146) {
						MonsterView -= 73;
						if (MonsterView < 0)MonsterView += NumMonsters;
						select[mode] -= 73;
						if (select[mode] < 0)select[mode] += NumMonsters;
					}
					break;
				case VK_NEXT:
					if (NumMonsters == 146) {
						MonsterView += 73;
						MonsterView %= NumMonsters;
						select[mode] += 73;
						select[mode] %= NumMonsters;
					}
					break;

			}
			if(select[mode]<MonsterView-73)select[mode]+=73;