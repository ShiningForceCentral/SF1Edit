
			if(p.x>=63&&p.x<=103&&p.y>=10&&p.y<=26){
				focus=1;
			}

			if(p.x>=148&&p.x<=208&&p.y>=58&&p.y<=74&&PoisonOffset!=0x20244){
				focus=2;
			}

			if(p.x>=115&&p.x<=155&&p.y>=106&&p.y<=121){
				focus=3;
			}
			if(p.x>=115&&p.x<=155&&p.y>=122&&p.y<=137){
				focus=4;
			}
			if(p.x>=115&&p.x<=155&&p.y>=138&&p.y<=155){
				focus=5;
			}
			if(p.x>=120&&p.x<=160&&p.y>=236&&p.y<=252){
				focus=6;
			}
			if(p.x>=120&&p.x<=160&&p.y>=268&&p.y<=284){
				focus=7;
			}

			if(p.x>=138&&p.x<=178&&p.y>=298&&p.y<=314){
				focus=8;
			}

			if(p.x>=110&&p.x<=160&&p.y>=374&&p.y<=390){
				focus=9;
			}
			if(p.x>=110&&p.x<=160&&p.y>=390&&p.y<=406){
				focus=10;
			}
			if(p.x>=250&&p.x<=300&&p.y>=374&&p.y<=390){
				focus=11;
			}

			if(p.x>=250&&p.x<=300&&p.y>=390&&p.y<=406){
				focus=12;
			}

			if (p.x >= 430 && p.x <= 480 && p.y >= 110 && p.y <= 130) {
				focus = 13;
			}
			if (p.x >= 430 && p.x <= 480 && p.y >= 130 && p.y <= 150) {
				focus = 14;
			}

			if (p.x >= 210 && p.x <= 250 && p.y >= 410 && p.y <= 426) {
				focus = 15;
			}


			if(p.x>=20&&p.x<=33&&p.y>=26&&p.y<=39){
				PoisonOffset=0x20244;
			}

			if(p.x>=20&&p.x<=33&&p.y>=42&&p.y<=55&&PoisonOffset==0x20244){
				PoisonOffset=0x180000;
			}

			if(p.x>=130&&p.x<=143&&p.y>=172&&p.y<=185){
				RemoveMarks=!RemoveMarks;
			}

			if (p.x >= 397 && p.x <= 410 && p.y >= 300 && p.y <= 313) {
				FixMuddle = !FixMuddle;
			}

			if(p.x>=414&&p.x<=427&&p.y>=12&&p.y<=25){
				FixLE=!FixLE;
			}

			if(p.x>=468&&p.x<=481&&p.y>=32&&p.y<=45){
				ItemPassing=!ItemPassing;
			}

			if (p.x >= 558 && p.x <= 571 && p.y >= 32 && p.y <= 45) {
				ItemPassingBattle = !ItemPassingBattle;
			}

			if(p.x>=404&&p.x<=417&&p.y>=52&&p.y<=65){
				EXPOverflow=!EXPOverflow;
			}

			if(p.x>=417&&p.x<=430&&p.y>=72&&p.y<=85){
				AddArmor=!AddArmor;
			}

			if(p.x>=417&&p.x<=430&&p.y>=92&&p.y<=105){
				HealAI=!HealAI;
			}

			if(p.x>=315&&p.x<=328&&p.y>=172&&p.y<=185){
				DisplayCrit=!DisplayCrit;
			}

			if(p.x>=130&&p.x<=143&&p.y>=192&&p.y<=205){
				RemoveCaps=!RemoveCaps;
			}

			if(p.x>=130&&p.x<=143&&p.y>=254&&p.y<=270){
				MultiAttacks=!MultiAttacks;
			}

			if (p.x >= 338 && p.x <= 351 && p.y >= 222 && p.y <= 235) {
				FixDoubles = !FixDoubles;
			}

			if(p.x>=102&&p.x<=115&&p.y>=330&&p.y<=346){
				DisallowRevive=!DisallowRevive;
			}

			if(p.x>=115&&p.x<=128&&p.y>=431&&p.y<=444){
				JogurtLevels=!JogurtLevels;
			}

			if (p.x >= 265 && p.x <= 278 && p.y >= 431 && p.y <= 444) {
				ShowCrit = !ShowCrit;
			}
			BitBlt(memdc, 265, 431, 13, 13, bmpdc, 0, 0, SRCCOPY);

			if(p.x>=172&&p.x<=185&&p.y>=472&&p.y<=485){
				ExtendStatItems=!ExtendStatItems;

				if (ExtendStatItems)NUM_STAT_UPS++;
				else NUM_STAT_UPS--;
			}
			if (p.x >= 172 && p.x <= 185 && p.y >= 492 && p.y <= 505) {
				AddMPEffect = !AddMPEffect;

				if(AddMPEffect)NUM_EFFECT_ROUTINE++;
				else NUM_EFFECT_ROUTINE--;
			}
			if (p.x >= 430 && p.x <= 480 && p.y >= 150 && p.y <= 170) {
				focus = 16;
			}
			if (p.x >= 430 && p.x <= 480 && p.y >= 170 && p.y <= 190) {
				focus = 18;
			}