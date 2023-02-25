int ClassRandBonus[18][12] = {
	{2,1,0,1,0,0,4,0,4,2,2,0},
	{0,0,2,2,0,0,3,0,3,0,0,0},
	{4,3,-1,0,0,0,0,0,0,0,0,0},
	{3,4,-2,-2,0,0,-1,0,-1,0,0,-1},
	{-1,-1,1,0,0,0,-1,0,-1,5,5,0},
	{7,-1,1,0,0,0,1,0,1,4,4,-1},
	{0,0,0,0,0,0,2,0,2,6,6,0},
	{0,0,1,0,0,0,0,0,0,0,0,0},
	{2,0,0,2,0,0,0,0,0,0,0,0},
	{1,0,3,2,0,0,0,0,0,0,0,0},
	{1,0,1,1,0,0,-1,0,-1,0,0,0},
	{3,2,0,0,0,0,3,0,3,0,0,-1},
	{2,4,0,-2,0,0,7,0,7,0,0,-2},
	{8,2,1,1,0,0,0,0,0,0,0,-2},
	{4,4,0,0,4,0,2,0,2,0,0,-3},
	{3,3,3,2,2,0,3,0,3,4,4,-4},
	{0,0,0,2,0,0,0,0,0,0,0,0},
	{2,4,4,-1,1,0,4,0,4,6,6,-3}
};

int ClassRandCurve[18][12] = {
	{3,2,0,9,2,3,3,14,8,13,4,5},
	{5,2,5,14,0,1,0,11,14,14,0,3},
	{3,5,0,2,0,3,6,17,8,10,0,5},
	{1,5,0,1,0,1,0,20,7,9,0,3},
	{0,0,4,0,19,0,0,5,13,9,14,0},
	{15,2,0,5,2,3,9,6,10,11,9,17},
	{0,0,0,1,11,1,0,5,10,10,9,3},
	{0,0,0,3,0,3,0,6,11,10,0,6},
	{1,0,0,1,0,0,0,4,10,9,0,0},
	{1,0,3,4,0,0,0,7,12,11,0,1},
	{0,0,0,4,0,0,0,7,11,10,0,0},
	{20,6,0,4,0,3,9,13,9,19,0,-1},
	{9,5,1,4,0,1,12,19,9,12,0,0},
	{12,3,2,2,0,3,26,9,11,13,0,5},
	{16,38,14,31,0,14,16,38,14,31,0,14},
	{5,17,16,16,10,5,5,17,16,16,10,5},
	{0,0,0,0,0,0,0,0,0,0,0,0},
	{20,33,22,30,20,0,20,33,22,30,20,0}
};

int CharOldLevel[30] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

int ClassRandWeap[18][4] = {
	{ 29, 30, 29, 30 },
	{ 40, 41, 45, 46 },
	{ 29, 30, 48, 49 },
	{ 40, 41, 45, 46 },
	{ 53, 56, 53, 56 },
	{ 255, 255, 255, 255 },
	{ 53, 56, 53, 56 },
	{ 59, 60, 59, 60 },
	{ 59, 60, 59, 60 },
	{ 29, 30, 29, 30 },
	{ 40, 41, 45, 46 },
	{ 255, 255, 255, 255 },
	{ 255, 255, 255, 255 },
	{ 255, 255, 255, 255 },
	{ 29, 30, 29, 30 },
	{ 29, 30, 29, 30 },
	{ 255, 255, 255, 255 },
	{ 255, 255, 255, 255 }
};

int ClassRandSB[18][2] = {
	{ -1, 2 },
	{ -1, -1 },
	{ -1, -1 },
	{ -1, -1 },
	{ 4, 1 },
	{ 0, 1 },
	{ 3, 1 },
	{ -1, -1 },
	{ -1, -1 },
	{ -1, -1 },
	{ -1, -1 },
	{ -1, -1 },
	{ -1, -1 },
	{ -1, -1 },
	{ -1, -1 },
	{ 1, -1 },
	{ -1, -1 },
	{ 0, 1 }
};

int RandItem[20] = {255,255,255,0,0,1,1,2,2,3,4,5,6,7,8,9,10,11,12,13};

int RandSpellStatus[] = {2,3,4,5,6,7,8,15};
int RandSpellMix[] = {0,1,9,10,11,12};
int RandSpellHelp[] = {2,5,0,1};
int RandSpellHarm[] = {9,10,11,12};

void Randomize(){
	for(int i=0;i<30;i++){
		if(CharOldLevel[i]){
			Char[i][1] = CharOldLevel[i];
		}

		CharOldLevel[i] = Char[i][1];
		// att/def/agi d6+3
		Char[i][2]=random(1,6)+3;
		Char[i][3]=random(1,6)+3;
		Char[i][4]=random(1,6)+3;
		// mov d6+2
		Char[i][5]=random(1,6)+2;
		// cri d6
		Char[i][6]=random(1,6);


		//hp 1d12+2 min 7
		Char[i][8]=0;
		Char[i][9]=random(1,12)+2;
		if(Char[i][9]<7)Char[i][9]=7;
		Char[i][10]=0;
		Char[i][11]=Char[i][9];

		//mp d8+4
		Char[i][12]=random(1,8)+4;
		Char[i][13]=Char[i][12];

		//stat growth d10+5 (crit 1)
		for(int j=0;j<5;j++){
			Stats[i][j] = random(1,10)+5 + random(0,3)*64;
		}
		Stats[i][5] = 1 + random(0,3)*64;
		//promoted stat growth d20+10 (crit d6+2)
		for(int j=0;j<5;j++){
			Stats[i][j+6] = random(1,20)+10 + random(0,3)*64;
		}
		Stats[i][5+6] = random(1,6)+2 + random(0,3)*64;

		//class
		Char[i][0]=random(0,17);

		for(int j=0;j<12;j++){
			int k=2;
			if(j>4)k++;
			if(j<11)Char[i][j+k]+=ClassRandBonus[Char[i][0]][j];
			else {
				Char[i][1]+=ClassRandBonus[Char[i][0]][j];
				if(Char[i][1]>128)Char[i][1]=1;
			}
			Stats[i][j]+=ClassRandCurve[Char[i][0]][j];
		}

		//weapon
		Char[i][16] = ClassRandWeap[Char[i][0]][random(0,3)];
		if(Char[i][16]!=255)Char[i][16]+=128;

		//items
		for(int j=0;j<3;j++){
			Char[i][17+j] = RandItem[random(1,20)];
		}

		//spells
		NumLearn[i] = 0;

		//egress for hero
		if(i==0){
			Learn[i][NumLearn[i]][0] = 0;
			Learn[i][NumLearn[i]][1] = 13;
			NumLearn[i]++;
		}

		char s = random(0,3);
		unsigned char l = 0;
		bool have = false;
		for(int j=0;j<s;j++){
			do{
				switch(random(1,3)){
					case 1:
						l = RandSpellStatus[random(0,7)];
						break;
					case 2:
						l = RandSpellMix[random(0,5)];
						break;
				}
				have = false;
				for(int k=0;k<NumLearn[i];k++){
					if(Learn[i][k][1]==l)have = true;
				}
			} while(have);
			
			char m = random(1,6)+j;
			char n = random(1,4);

			if(ClassRandSB[Char[i][0]][0]==-1 && n<4 && j<ClassRandSB[Char[i][0]][1])
				n++;

			if(Char[i][0]==17)n=4;

			for(int k=0;k<n;k++){
				Learn[i][NumLearn[i]][0] = m;
				Learn[i][NumLearn[i]][1] = l + 64*k;
				NumLearn[i]++;
				m+=(1<<k) + 3 + random(1,10);
			}

		}

		if(ClassRandSB[Char[i][0]][0]!=-1){
			do{
				switch(ClassRandSB[Char[i][0]][0]){
					case 0:
						switch(random(1,3)){
							case 1:
								l = RandSpellStatus[random(0,7)];
								break;
							case 2:
								l = RandSpellMix[random(0,5)];
								break;
						}
						break;
					case 1:
						l = RandSpellStatus[random(0,7)];
						break;
					case 2:
						l = RandSpellMix[random(0,5)];
						break;
					case 3:
						l = RandSpellHelp[random(0,3)];
						break;
					case 4:
						l = RandSpellHarm[random(0,3)];
						break;
				}
				have = false;
				for(int k=0;k<NumLearn[i];k++){
					if(Learn[i][k][1]==l)have = true;
				}
			} while(have);
			
			char m = random(1,6)+3;
			char n = random(1,4);

			if(ClassRandSB[Char[i][0]][1]>-1)
				n+=ClassRandSB[Char[i][0]][1];

			if(n>4)n=4;

			for(int k=0;k<n;k++){
				Learn[i][NumLearn[i]][0] = m;
				Learn[i][NumLearn[i]][1] = l + 64*k;
				NumLearn[i]++;
				m+=(1<<k) + 3 + random(1,10);
			}

		}

		//sort learned
		for(int x=0;x<NumLearn[i];x++){
			for(int y=x+1;y<NumLearn[i];y++){
				if(Learn[i][y][0]<Learn[i][x][0]){
					unsigned char j = Learn[i][x][0];
					Learn[i][x][0] = Learn[i][y][0];
					Learn[i][y][0] = j;
					j = Learn[i][x][1];
					Learn[i][x][1] = Learn[i][y][1];
					Learn[i][y][1] = j;
					y=x;
				}
			}
		}

		if(Char[i][0]>15)Char[i][0]+=14;
	}
}