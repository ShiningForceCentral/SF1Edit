void SaveMap(){
	if(!strlen(file)){
		int ret=IDYES;
		OPENFILENAME openFileName;
		char path[256];
		path[0] = '\0';    
		memset( &openFileName, 0, sizeof(openFileName) );
		openFileName.lStructSize = sizeof(openFileName);
		openFileName.hwndOwner = NULL;
		openFileName.hInstance = NULL;
		openFileName.lpstrFilter = "Genesis ROM(*.bin)\0*.bin\0";
		openFileName.lpstrCustomFilter = NULL;
		openFileName.nMaxCustFilter = 0;
		openFileName.nFilterIndex = 0;
		openFileName.lpstrFile =  path;
		openFileName.nMaxFile = 256;
		openFileName.lpstrFileTitle = NULL;
		openFileName.nMaxFileTitle = 0;
		openFileName.lpstrInitialDir = ".";
		openFileName.lpstrTitle = NULL;
		openFileName.Flags = OFN_LONGNAMES | OFN_PATHMUSTEXIST;
		openFileName.nFileOffset = 0;
		openFileName.nFileExtension = 0;
		openFileName.lpstrDefExt = "bin";
		openFileName.lCustData = NULL;
		openFileName.lpfnHook = NULL;
		openFileName.lpTemplateName = NULL;

		if(GetOpenFileName(&openFileName)!=0){
			sprintf(file,path);
		}
	}

	int i;
	
	if(strlen(file)){


		FILE * fp = fopen(file,"rb+");

		if(0x1E0000>romsize){
			MessageBox(NULL,"Rom is too small, expand rom to save map changes.","Error",MB_OK);
			fclose(fp);
			return;
		}

		if (NumChars == 30) {
			fseek(fp, 0x23A6D, SEEK_SET);
			fprintf(fp, "%c", NovaSprite);
		}

		fseek(fp, 0x68C1, SEEK_SET);
		fprintf(fp, "%c", BlueFlameSprite);

		long o;

		o = 0x1EA000;

		for (int j = 0; j < 5; j++) {
			fseek(fp, MapSpecialBankOffset + 4 * j, SEEK_SET);
			
			fprintf(fp, "%c", ((o) & 0xFF000000) / 0x1000000);
			fprintf(fp, "%c", ((o) & 0x00FF0000) / 0x10000);
			fprintf(fp, "%c", ((o) & 0x0000FF00) / 0x100);
			fprintf(fp, "%c", ((o) & 0x000000FF));

			fseek(fp, o, SEEK_SET);

			for (int i = 0; i < NUM_MAPS;i++) {

				if (MapSpecialTiles[i][j][0] != 0xFF) {

					fprintf(fp, "%c", i);

					fprintf(fp, "%c", MapSpecialTiles[i][j][0]);
					fprintf(fp, "%c", MapSpecialTiles[i][j][1]);
					fprintf(fp, "%c", MapSpecialTiles[i][j][2]);

					o += 4;
				}
			}

			if(j<3)fprintf(fp, "%c", 0xFF);
			else fprintf(fp, "%c", 0xFE);
			fprintf(fp, "%c", 0xFF);
			o += 2;
		}





			
			
		o = 0x1C0500;

		fseek(fp, 0x80010, SEEK_SET);

		for (i = 0; i<54; i++) {
			SpriteOffsets[i] = o;
			fprintf(fp, "%c", ((o) & 0xFF000000) / 0x1000000);
			fprintf(fp, "%c", ((o) & 0x00FF0000) / 0x10000);
			fprintf(fp, "%c", ((o) & 0x0000FF00) / 0x100);
			fprintf(fp, "%c", ((o) & 0x000000FF));
			o += 6 * NumSprites[i] + 2;
		}

		for (i = 0; i < 54; i++) {

			CountMapSprites();

			if (UniSprites[i] > 12) {
				select[mode] = i;
				submode[mode] = 0;
				MessageBox(NULL, "Cannot have more than 12 unique sprite graphics.", "Error", MB_OK);
				fclose(fp);
				return;
			}
		}

		for (i = 0; i<54; i++) {
			fseek(fp, SpriteOffsets[i], SEEK_SET);
			for (int j = 0; j<NumSprites[i]; j++) {
				for (int k = 0; k<6; k++) {
					fprintf(fp, "%c", Sprites[i][j][k]);
				}
			}
			fprintf(fp, "%c", 255);
			fprintf(fp, "%c", 255);
		}
		
		//HQPosOffset = 0x1E1000;//

		//fseek(fp, 0x1E0FFF, SEEK_SET);
		//fprintf(fp, "%c", NumHQPos);

		//fseek(fp, 0x67E1, SEEK_SET);
		//fprintf(fp, "%c", NumHQPos);

		/*fseek(fp, HQPosOffset, SEEK_SET);
		for (i = 0; i < NumHQPos; i++) {
			for (int j = 0; j < 3; j++) {
				fprintf(fp, "%c", HQPos[i][j]);
			}
		}

		fprintf(fp, "%c", 0xFF);
		fprintf(fp, "%c", 0xFF);
		fprintf(fp, "%c", 0xFF);

		fseek(fp, 0x67CE, SEEK_SET);
		fprintf(fp, "%c", 0x4E);
		fprintf(fp, "%c", 0xB9);
		fprintf(fp, "%c", 0x00);
		fprintf(fp, "%c", 0x1E);
		fprintf(fp, "%c", 0x0F);
		fprintf(fp, "%c", 0xF0);

		fseek(fp, 0x1E0FF0, SEEK_SET);
		fprintf(fp, "%c", 0x70);
		fprintf(fp, "%c", 0x01);
		fprintf(fp, "%c", 0x43);
		fprintf(fp, "%c", 0xF9);
		fprintf(fp, "%c", 0x00);
		fprintf(fp, "%c", 0x1E);
		fprintf(fp, "%c", 0x10);
		fprintf(fp, "%c", 0x00);
		fprintf(fp, "%c", 0x4E);
		fprintf(fp, "%c", 0x75);
		*/

		for(i=0;i<NUM_MAPS+1;i++){
			if(i==11||i==17||i==38){
				fseek(fp,0x8FBE+8*MapMusic[i][2],SEEK_SET);
				fprintf(fp,"%c",MapMusic[i][0]);
			}
		}

		fseek(fp,0x1D37E,SEEK_SET);
		for(i=0;i<NUM_MAPS;i++){
			if(MapMusic[i][1]==1){
				fprintf(fp,"%c",i);
				fprintf(fp,"%c",MapMusic[i][0]);
			}
		}

		

		fseek(fp,120462,SEEK_SET);

		for(i=0; i<8; i++){
			for(int j=0; j<32; j++){
				for(int k=0; k<4; k++){
					fprintf(fp,"%c",Chests[i][31-j][k]);
				}
			}
		}

		unsigned long temp,offset;
		unsigned char in,r;
		unsigned int c;

		offset = 0x1AB000;

		for(i=0; i<172; i++){
			fseek(fp,0x80EFE+4*i,SEEK_SET);

			temp=offset;
			fprintf(fp,"%c",((temp)&0xFF000000)/0x1000000);
			fprintf(fp,"%c",((temp)&0x00FF0000)/0x10000);
			fprintf(fp,"%c",((temp)&0x0000FF00)/0x100);
			fprintf(fp,"%c",((temp)&0x000000FF));

			r=0;
			in=0;
			c=0;
			fseek(fp,temp,SEEK_SET);
			while( (i==171&&in!=0x09&&in!=0x19&&in!=0x0E)||(i<171&&c<SpriteScrLen[i]) ){
			//while(in!=0x09&&in!=0x19&&in!=0x0E){
				in=SpriteScripts[i][r];
				c++;
				fprintf(fp,"%c",SpriteScripts[i][r++]);
				switch(in){
					case 24:
						fprintf(fp,"%c",SpriteScripts[i][r++]);
						c++;
					case 15:
					case 17:
					case 18:
					case 20:
					case 21:
					case 22:
						fprintf(fp,"%c",SpriteScripts[i][r++]);
						c++;
					case 8:
					case 12:
					case 13:
					case 14:
					case 16:
					case 19:
						fprintf(fp,"%c",SpriteScripts[i][r++]);
						c++;
						break;

				}
			}
			offset+=r;
		}


		fseek(fp,0x1A7400,SEEK_SET);
		for(i=0; i<NUM_MAPS; i++){
			fprintf(fp,"%c",MapGraphics[i][0]);
			fprintf(fp,"%c",MapGraphics[i][1]);
		}

		//MessageBox(NULL,"Map saving currently disabled.","Error",MB_OK);
		//fclose(fp);
		//return;

		BPCompressor BPC(fp,false);
		SBCompressor SBC(fp,false);
		ULCompressor ULC(fp);

		offset=MapsOffset;

		for(i=0; i<NUM_MAPS; i++){
			//820CC
			fseek(fp,0x820CC+32*i,SEEK_SET);

			temp = MapTileset[i][0]*18+0x8264C;

			fprintf(fp,"%c",((temp)&0xFF000000)/0x1000000);
			fprintf(fp,"%c",((temp)&0x00FF0000)/0x10000);
			fprintf(fp,"%c",((temp)&0x0000FF00)/0x100);
			fprintf(fp,"%c",((temp)&0x000000FF));

			temp = MapTileset[i][1]*18+0x8264C;

			fprintf(fp,"%c",((temp)&0xFF000000)/0x1000000);
			fprintf(fp,"%c",((temp)&0x00FF0000)/0x10000);
			fprintf(fp,"%c",((temp)&0x0000FF00)/0x100);
			fprintf(fp,"%c",((temp)&0x000000FF));

			temp = MapTileset[i][2]*18+0x8264C;

			fprintf(fp,"%c",((temp)&0xFF000000)/0x1000000);
			fprintf(fp,"%c",((temp)&0x00FF0000)/0x10000);
			fprintf(fp,"%c",((temp)&0x0000FF00)/0x100);
			fprintf(fp,"%c",((temp)&0x000000FF));

			temp = MapTileset[i][3]*18+0x8264C;

			fprintf(fp,"%c",((temp)&0xFF000000)/0x1000000);
			fprintf(fp,"%c",((temp)&0x00FF0000)/0x10000);
			fprintf(fp,"%c",((temp)&0x0000FF00)/0x100);
			fprintf(fp,"%c",((temp)&0x000000FF));

			if(offset%2)offset++;

			temp = offset;

			fprintf(fp,"%c",((temp)&0xFF000000)/0x1000000);
			fprintf(fp,"%c",((temp)&0x00FF0000)/0x10000);
			fprintf(fp,"%c",((temp)&0x0000FF00)/0x100);
			fprintf(fp,"%c",((temp)&0x000000FF));


			temp = MapPalOffsets[i];

			fprintf(fp, "%c", ((temp) & 0xFF000000) / 0x1000000);
			fprintf(fp, "%c", ((temp) & 0x00FF0000) / 0x10000);
			fprintf(fp, "%c", ((temp) & 0x0000FF00) / 0x100);
			fprintf(fp, "%c", ((temp) & 0x000000FF));

			temp = MapGfxOffsets[i];

			fprintf(fp, "%c", ((temp) & 0xFF000000) / 0x1000000);
			fprintf(fp, "%c", ((temp) & 0x00FF0000) / 0x10000);
			fprintf(fp, "%c", ((temp) & 0x0000FF00) / 0x100);
			fprintf(fp, "%c", ((temp) & 0x000000FF));

			fseek(fp,offset,SEEK_SET);
			offset+=2;

			fprintf(fp,"%c",MapSize[i][0]);
			fprintf(fp,"%c",MapSize[i][1]);

			offset+=BPC.PutData(MapSize[i][0],MapSize[i][0]*MapSize[i][1],MapData[i]);
			offset+=SBC.PutData(MapSize[i][0],MapSize[i][0]*MapSize[i][1],MapWalk[i],BPC.Barrel,BPC.Length);
			offset+=ULC.PutData(MapSize[i][0],MapSize[i][0]*MapSize[i][1],MapFlag[i],MapFlag2[i],MapEvent[i],MapGroup[i],MapData2[i],SBC.Barrel,SBC.Length);

		}

		fseek(fp,0x12D31,SEEK_SET);
		fprintf(fp,"%c",0xA6);//fix for some hardcoded event based tele switches

		fseek(fp,0x12C62,SEEK_SET);

		if(TeleOffset == 0x12D8A)TeleOffset = 0x1A5880;

		fprintf(fp,"%c",0x4E);
		fprintf(fp,"%c",0xB9);
		fprintf(fp,"%c",((TeleOffset)&0xFF000000)/0x1000000);
		fprintf(fp,"%c",((TeleOffset)&0x00FF0000)/0x10000);
		fprintf(fp,"%c",((TeleOffset)&0x0000FF00)/0x100);
		fprintf(fp,"%c",((TeleOffset)&0x000000FF));
		fseek(fp,TeleOffset,SEEK_SET);
		fprintf(fp,"%c",0x42);
		fprintf(fp,"%c",0x47);
		fprintf(fp,"%c",0x41);
		fprintf(fp,"%c",0xF9);
		fprintf(fp,"%c",((TeleOffset+10)&0xFF000000)/0x1000000);
		fprintf(fp,"%c",((TeleOffset+10)&0x00FF0000)/0x10000);
		fprintf(fp,"%c",((TeleOffset+10)&0x0000FF00)/0x100);
		fprintf(fp,"%c",((TeleOffset+10)&0x000000FF));
		fprintf(fp,"%c",0x4E);
		fprintf(fp,"%c",0x75);
		

		for(int j=0;j<1024;j++){
			if(MapTele[j][0]!=-1){
				for(i=0;i<8;i++){
					fprintf(fp,"%c",MapTele[j][i]);
				}
			}
		}
		/*for(i=0;i<NUM_MAPS;i++){
			for(int j=0;j<4096;j++){
				if(MapTele[i][j][0]!=-1)
				if(MapTele[i][j][0]*4096+MapTele[i][j][1]>=i*4096+j){
					fprintf(fp,"%c",i);
					fprintf(fp,"%c",j%MapSize[i][0]);
					fprintf(fp,"%c",(j-j%MapSize[i][0])/MapSize[i][0]);
					fprintf(fp,"%c",MapTele[i][j][2]);
					fprintf(fp,"%c",MapTele[i][j][0]);
					fprintf(fp,"%c",MapTele[i][j][1]%MapSize[MapTele[i][j][0]][0]);
					fprintf(fp,"%c",(MapTele[i][j][1]-MapTele[i][j][1]%MapSize[MapTele[i][j][0]][0])/MapSize[MapTele[i][j][0]][0]);
					fprintf(fp,"%c",MapTele[MapTele[i][j][0]][MapTele[i][j][1]][2]);
				}
			}
		}*/

		fseek(fp,0x1A6300,SEEK_SET);
		for(i=0;i<NUM_MAPS;i++){
			if(MapSize[i][0])
			for(int j=0;j<4096;j++){
				if(MapChest[i][j]!=0xFF){
					fprintf(fp,"%c",i);
					fprintf(fp,"%c",j%MapSize[i][0]);
					fprintf(fp,"%c",(j-j%MapSize[i][0])/MapSize[i][0]);
					fprintf(fp,"%c",MapChest[i][j]+(MapGold[i][j]-MapGold[i][j]%256)/256);
					fprintf(fp,"%c",MapGold[i][j]%256);
				}
			}
		}
		fseek(fp,0x138BC,SEEK_SET);
		fprintf(fp,"%c",0x4E);
		fprintf(fp,"%c",0xB9);
		fprintf(fp,"%c",0x00);
		fprintf(fp,"%c",0x1A);
		fprintf(fp,"%c",0x67);
		fprintf(fp,"%c",0x00);
		fprintf(fp,"%c",0x4E);
		fprintf(fp,"%c",0x71);
		fseek(fp,0x13918,SEEK_SET);
		fprintf(fp,"%c",0x4E);
		fprintf(fp,"%c",0x71);
		fprintf(fp,"%c",0x4E);
		fprintf(fp,"%c",0x71);
		fprintf(fp,"%c",0x4E);
		fprintf(fp,"%c",0x71);
		fprintf(fp,"%c",0x02);
		fprintf(fp,"%c",0x01);
		fprintf(fp,"%c",0x00);
		fprintf(fp,"%c",0x7F);
		fprintf(fp,"%c",0xE1);
		fprintf(fp,"%c",0x59);
		fprintf(fp,"%c",0x12);
		fprintf(fp,"%c",0x30);
		fprintf(fp,"%c",0x60);
		fprintf(fp,"%c",0x04);
		fseek(fp,0x1A6700,SEEK_SET);
		for(i=0;i<chestsize;i++){
			fprintf(fp,"%c",chestasm[i]);
		}


		if(DialogHeaderOffset == 0x1C3D00){
			fseek(fp,0x17CE8,SEEK_SET);		
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0xB9);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x1A);
			fprintf(fp,"%c",0x68);
			fprintf(fp,"%c",0x00);

			fprintf(fp,"%c",0x41);
			fprintf(fp,"%c",0xF9);
			fprintf(fp,"%c",((DialogHeaderOffset)&0xFF000000)/0x1000000);
			fprintf(fp,"%c",((DialogHeaderOffset)&0x00FF0000)/0x10000);
			fprintf(fp,"%c",((DialogHeaderOffset)&0x0000FF00)/0x100);
			fprintf(fp,"%c",((DialogHeaderOffset)&0x000000FF));
		} else {
			fseek(fp,0x17CEC,SEEK_SET);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0x71);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0xB9);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x1A);
			fprintf(fp,"%c",0x68);
			fprintf(fp,"%c",0x00);
			fseek(fp,0x17CF4,SEEK_SET);	
		}


		if(DialogHeaderOffset == 0x1C3D00){
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0x71);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0x71);
		} else {
			fprintf(fp,"%c",0x41);
			fprintf(fp,"%c",0xFA);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x6C);
		}
		//old NOP spot
		fprintf(fp,"%c",0x4B);
		fprintf(fp,"%c",0xFA);
		fprintf(fp,"%c",0x01);
		fprintf(fp,"%c",0x74);
		fprintf(fp,"%c",0x10);
		fprintf(fp,"%c",0x38);
		fprintf(fp,"%c",0xF8);
		fprintf(fp,"%c",0x08);
		fprintf(fp,"%c",0x7E);
		fprintf(fp,"%c",0x22);
		fprintf(fp,"%c",0x59);
		fprintf(fp,"%c",0x88);
		fprintf(fp,"%c",0x58);
		fprintf(fp,"%c",0x88);
		fprintf(fp,"%c",0xB0);
		fprintf(fp,"%c",0x58);
		fprintf(fp,"%c",0x57);
		fprintf(fp,"%c",0xCF);
		fprintf(fp,"%c",0xFF);
		fprintf(fp,"%c",0xFA);
		fprintf(fp,"%c",0x0C);
		fprintf(fp,"%c",0x01);
		fprintf(fp,"%c",0x00);
		fprintf(fp,"%c",0xFD);
		fprintf(fp,"%c",0x67);
		fprintf(fp,"%c",0x1A);
		fprintf(fp,"%c",0x0C);
		fprintf(fp,"%c",0x01);
		fprintf(fp,"%c",0x00);
		fprintf(fp,"%c",0xFC);
		fprintf(fp,"%c",0x67);
		fprintf(fp,"%c",0x14);
		fprintf(fp,"%c",0x48);
		fprintf(fp,"%c",0x82);
		fprintf(fp,"%c",0x0C);
		fprintf(fp,"%c",0x01);
		fprintf(fp,"%c",0x00);
		fprintf(fp,"%c",0xFF);
		fprintf(fp,"%c",0x67);
		fprintf(fp,"%c",0x0C);
		fprintf(fp,"%c",0x0C);
		fprintf(fp,"%c",0x01);
		fprintf(fp,"%c",0x00);
		fprintf(fp,"%c",0xFE);
		fprintf(fp,"%c",0x67);
		fprintf(fp,"%c",0x06);
		fprintf(fp,"%c",0x10);
		fprintf(fp,"%c",0x03);
		fprintf(fp,"%c",0x61);
		fprintf(fp,"%c",0x00);
		fprintf(fp,"%c",0x02);
		fprintf(fp,"%c",0x3A);
		fprintf(fp,"%c",0x4E);
		fprintf(fp,"%c",0xB9);
		fprintf(fp,"%c",0x00);
		fprintf(fp,"%c",0x1A);
		fprintf(fp,"%c",0x67);
		fprintf(fp,"%c",0xE4);

		fseek(fp,0x1A67E4,SEEK_SET);
		for(i=0;i<readsize;i++){
			fprintf(fp,"%c",readasm[i]);
		}

		fseek(fp,0x1A6890,SEEK_SET);
		for(i=0;i<NUM_MAPS;i++){
			if(MapSize[i][0])
			for(int j=0;j<4096;j++){
				if(MapRead[i][j]!=-1){
					fprintf(fp,"%c",i);
					fprintf(fp,"%c",j%MapSize[i][0]);
					fprintf(fp,"%c",(j-j%MapSize[i][0])/MapSize[i][0]);
					fprintf(fp,"%c",(MapRead[i][j]-MapRead[i][j]%256)/256);
					fprintf(fp,"%c",MapRead[i][j]%256);
				}
			}
		}

		fclose(fp);
		MessageBox(NULL,"Maps Saved","Note",MB_OK);
	}
}

void ExportMap(char*path){
	FILE * fp = fopen(path,"wb");

	int i;
	for(i=0; i<54; i++){
		for(int j=0; j<NumSprites[i]; j++){
			for(int k=0;k<6;k++){
				fprintf(fp,"%c",Sprites[i][j][k]);
			}
		}
		fprintf(fp,"%c",255);
		fprintf(fp,"%c",255);
	}

	for(i=0; i<8; i++){
		for(int j=0; j<32; j++){
			for(int k=0; k<4; k++){
				fprintf(fp,"%c",Chests[i][31-j][k]);
			}
		}
	}

	fclose(fp);
	MessageBox(NULL,"Maps Exported","Note",MB_OK);
}

void MapExport(){
	OPENFILENAME openFileName;
	char path[256];
	path[0] = '\0';  
	memset( &openFileName, 0, sizeof(openFileName) );
	openFileName.lStructSize = sizeof(openFileName);
	openFileName.hwndOwner = NULL;
	openFileName.hInstance = NULL;
	openFileName.lpstrFilter = "Shining Force Maps(*.sfma)\0*.sfma\0";
	openFileName.lpstrCustomFilter = NULL;
	openFileName.nMaxCustFilter = 0;
	openFileName.nFilterIndex = 0;
	openFileName.lpstrFile =  path;
	openFileName.nMaxFile = 256;
	openFileName.lpstrFileTitle = NULL;
	openFileName.nMaxFileTitle = 0;
	openFileName.lpstrInitialDir = ".";
	openFileName.lpstrTitle = NULL;
	openFileName.Flags = OFN_OVERWRITEPROMPT | OFN_LONGNAMES | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY;
	openFileName.nFileOffset = 0;
	openFileName.nFileExtension = 0;
	openFileName.lpstrDefExt = "sfna";
	openFileName.lCustData = NULL;
	openFileName.lpfnHook = NULL;
	openFileName.lpTemplateName = NULL;

	if(GetSaveFileName(&openFileName)!=0){
		ExportMap(path);
	}
}