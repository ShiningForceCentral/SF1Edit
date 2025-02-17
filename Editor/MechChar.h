			c=wParam;
			switch(focus){
				case 1:
					val=c-'0';
					if(val>=0&&val<10){
						i=Poison;
						if(i<=10){
							i*=10;
							i+=val;
							Poison=i;
						}
					}
					if(c==8){
						i=Poison;
						i=i-i%10;
						i/=10;
						Poison=i;
					}
					if(Poison>100)Poison=100;
					break;
				case 2://offset
					val=c-'0';
					if(c>='a'&&c<='f'){
						val=c-'a'+10;
					}
					if(c>='A'&&c<='F'){
						val=c-'A'+10;
					}
					if(val>=0&&val<16){
						l=PoisonOffset;
						if(l<524288){
							l*=16;
							l+=val;
							PoisonOffset=l;
						}
					}
					if(c==8){
						l=PoisonOffset;
						l=l-l%16;
						l/=16;
						PoisonOffset=l;
					}
					break;
				case 3://base damage
					val=c-'0';
					if(val>=0&&val<10){
						i=DamageBase;
						if(i<=10){
							i*=10;
							i+=val;
							DamageBase=i;
						}
					}
					if(c==8){
						i=DamageBase;
						i=i-i%10;
						i/=10;
						DamageBase=i;
					}
					if(DamageBase>100)DamageBase=100;
					break;
				case 4://spread
					val=c-'0';
					if(val>=0&&val<10){
						i=DamageSpread-1;
						if(i<=10){
							i*=10;
							i+=val;
							DamageSpread=i+1;
						}
					}
					if(c==8){
						i=DamageSpread-1;
						i=i-i%10;
						i/=10;
						DamageSpread=i+1;
					}
					if(DamageSpread>101)DamageSpread=101;
					if(DamageSpread<1)DamageSpread=1;
					break;
				case 5://critical
					val=c-'0';
					if(val>=0&&val<10){
						i=CritMult;
						if(i<=10){
							i*=10;
							i+=val;
							CritMult=i;
						}
					}
					if(c==8){
						i=CritMult;
						i=i-i%10;
						i/=10;
						CritMult=i;
					}
					if(CritMult>100)CritMult=100;
					break;
				case 6://double chance
					val=c-'0';
					if(val>=0&&val<10){
						i=DoubleChance;
						if(i<=10){
							i*=10;
							i+=val;
							DoubleChance=i;
						}
					}
					if(c==8){
						i=DoubleChance;
						i=i-i%10;
						i/=10;
						DoubleChance=i;
					}
					if(DoubleChance>100)DoubleChance=100;
					break;
				case 7://multi falloff
					val=c-'0';
					if(val>=0&&val<10){
						i=MultiFalloff;
						if(i<=10){
							i*=10;
							i+=val;
							MultiFalloff=i;
						}
					}
					if(c==8){
						i=MultiFalloff;
						i=i-i%10;
						i/=10;
						MultiFalloff=i;
					}
					if(MultiFalloff>100)MultiFalloff=100;
					break;
				case 8://break chance
					val=c-'0';
					if(val>=0&&val<10){
						i=BreakChance;
						if(i<=10){
							i*=10;
							i+=val;
							BreakChance=i;
						}
					}
					if(c==8){
						i=BreakChance;
						i=i-i%10;
						i/=10;
						BreakChance=i;
					}
					if(BreakChance>100)BreakChance=100;
					break;
				case 9://unpromoted level cap
					val=c-'0';
					if(val>=0&&val<10){
						i=UnLevelLimit;
						if(i<=12){
							i*=10;
							i+=val;
							UnLevelLimit=i;
						}
					}
					if(c==8){
						i=UnLevelLimit;
						i=i-i%10;
						i/=10;
						UnLevelLimit=i;
					}
					if(UnLevelLimit>127)UnLevelLimit=127;
					break;
				case 10://promoted level cap
					val=c-'0';
					if(val>=0&&val<10){
						i=LevelLimit;
						if(i<=12){
							i*=10;
							i+=val;
							LevelLimit=i;
						}
					}
					if(c==8){
						i=LevelLimit;
						i=i-i%10;
						i/=10;
						LevelLimit=i;
					}
					if(LevelLimit>127)LevelLimit=127;
					break;
				case 11://minimum promotion level
					val=c-'0';
					if(val>=0&&val<10){
						i=ProLevel;
						if(i<=12){
							i*=10;
							i+=val;
							ProLevel=i;
						}
					}
					if(c==8){
						i=ProLevel;
						i=i-i%10;
						i/=10;
						ProLevel=i;
					}
					if(ProLevel>127)ProLevel=127;
					break;
				case 12://base promotion level
					val=c-'0';
					if(val>=0&&val<10){
						i=ProLevelAdd;
						if(i<=12){
							i*=10;
							i+=val;
							ProLevelAdd=i;
						}
					}
					if(c==8){
						i=ProLevelAdd;
						i=i-i%10;
						i/=10;
						ProLevelAdd=i;
					}
					if(ProLevelAdd>127)ProLevelAdd=127;
					break;
				case 13://HP EXP Percent
					val = c - '0';
					if (val >= 0 && val<10) {
						i = HPEXPPercent;
						if (i <= 12) {
							i *= 10;
							i += val;
							HPEXPPercent = i;
						}
					}
					if (c == 8) {
						i = HPEXPPercent;
						i = i - i % 10;
						i /= 10;
						HPEXPPercent = i;
					}
					if (HPEXPPercent>100)HPEXPPercent = 100;
					break;
				case 14://HP EXP Min
					val = c - '0';
					if (val >= 0 && val<10) {
						i = HPEXPMin;
						if (i <= 12) {
							i *= 10;
							i += val;
							HPEXPMin = i;
						}
					}
					if (c == 8) {
						i = HPEXPMin;
						i = i - i % 10;
						i /= 10;
						HPEXPMin = i;
					}
					if (HPEXPMin>100)HPEXPMin = 100;
					break;
				case 15://Promote Stat %
					val = c - '0';
					if (val >= 0 && val<10) {
						i = PromotePercent;
						if (i < 100) {
							i *= 10;
							i += val;
							PromotePercent = i;
						}
					}
					if (c == 8) {
						i = PromotePercent;
						i = i - i % 10;
						i /= 10;
						PromotePercent = i;
					}
					break;
				case 16: { //detox exp
					int val = c - '0';
					if (val >= 0 && val < 10) {
						int i = DetoxEXP;
						if (i <= 12) {  
							i *= 10;
							i += val;
							DetoxEXP = i;
						}
					}
					if (c == 8) { 
						int i = DetoxEXP;
						i = i - i % 10;
						i /= 10;
						DetoxEXP = i;
					}
					if (DetoxEXP > 100) {
						DetoxEXP = 100;  
					}
					break;
				}
				case 18: { //sleep chance
					int val = c - '0';
					if (val >= 0 && val < 10) {
						int newVal = SleepWakeChance * 10 + val;
						if (newVal <= 100)
							SleepWakeChance = newVal;
					}
					else if (c == 8) { 
						SleepWakeChance /= 10;
					}
					break;
				}
			}