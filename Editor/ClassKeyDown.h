			if(submode[mode]==0){
				switch(wParam){
					case VK_UP:
						select[mode]-=1;
						select[mode] -= subselect[mode][0];
						select[mode]%=32;
						if (select[mode] < 0)select[mode] += 32;
						select[mode] += subselect[mode][0];
						break;
					case VK_DOWN:
						select[mode]+=1;
						select[mode] -= subselect[mode][0];
						select[mode] %= 32;
						select[mode] += subselect[mode][0];
						break;
					case VK_PRIOR:
					case VK_NEXT:
						if (NumClasses == 64) {
							if (!subselect[mode][0]) {
								subselect[mode][0] = 32;
								select[mode] += 32;
							} else {
								subselect[mode][0] = 0;
								select[mode] -= 32;
							}
						}
						break;
				}
				if(select[mode]<0)select[mode]+=32;
			}
			if(submode[mode]==1){
				switch(wParam){
					case VK_LEFT:
						select[mode]-=37;
						select[mode]-=NumClasses;
						select[mode]%=NumMonsters;
						select[mode]+= NumClasses;
						break;
					case VK_RIGHT:
						select[mode]+=37;
						select[mode]-= NumClasses;
						select[mode]%=NumMonsters;
						select[mode]+= NumClasses;
						break;
					case VK_UP:
						select[mode]-=1;
						select[mode]-= NumClasses;
						select[mode]%=NumMonsters;
						select[mode]+= NumClasses;
						break;
					case VK_DOWN:
						select[mode]+=1;
						select[mode]-= NumClasses;
						select[mode]%=NumMonsters;
						select[mode]+= NumClasses;
						break;
					case VK_PRIOR:
					case VK_NEXT:
							MonsterView += 73;
							MonsterView %= NumMonsters;
							select[mode] += 73;
							select[mode] -= NumClasses;
							select[mode] %= NumMonsters;
							select[mode] += NumClasses;
						break;
				}
				if(select[mode]<NumClasses)select[mode]+=NumMonsters;

				select[mode] = (select[mode]- NumClasses) % 73 + MonsterView+ NumClasses;
			}