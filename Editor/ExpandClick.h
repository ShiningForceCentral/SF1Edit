	for(i=0;i<10;i++){
		if(p.x>=278+150*(i%2)&&p.x<=293+150*(i%2)&&p.y>=76+(i-(i%2))*8&&p.y<=89+(i-(i%2))*8){
			sizesel=i;
		}
	}

	if(p.x>=352&&p.x<=410&&p.y>=162&&p.y<=190){
		if(1572864+524288*sizesel>romsize){
			if(!strlen(file)){
				MessageBox(NULL,"No ROM opened.","Error",MB_OK);
				return 0;
			}

			if (1572864 + 524288 * sizesel > 0x400000) {
				if (MessageBox(NULL, "Not all emulators are able to support sizes above 4MB. Continue?", "Note", MB_YESNO) != IDYES) {
					return 0;
				} else {
					MessageBox(NULL, "To make use of the space above 4MB, enable Expanded Graphics in the graphics section.", "Note", MB_OK);
				}
			}
			fp=fopen(file,"a");
			while(romsize<1572864+524288*sizesel){
				romsize++;
				fprintf(fp,"%c",255);
			}



			fclose(fp);
			fp = fopen(file,"rb+");

			fseek(fp,420,SEEK_SET);
			fprintf(fp,"%c",((romsize-1)&0xFF000000)/0x1000000);
			fprintf(fp,"%c",((romsize-1)&0x00FF0000)/0x10000);
			fprintf(fp,"%c",((romsize-1)&0x0000FF00)/0x100);
			fprintf(fp,"%c",((romsize-1)&0x000000FF));
			fseek(fp,1146,SEEK_SET);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0xB9);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x17);
			fprintf(fp,"%c",0xFF);
			fprintf(fp,"%c",0x70);
			fseek(fp,1572720,SEEK_SET);
			fprintf(fp,"%c",0x13);
			fprintf(fp,"%c",0xFC);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x01);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0xA1);
			fprintf(fp,"%c",0x30);
			fprintf(fp,"%c",0xF1);
			fprintf(fp,"%c",0x4A);
			fprintf(fp,"%c",0xB9);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0xA1);
			fprintf(fp,"%c",0x00);
			fprintf(fp,"%c",0x08);
			fprintf(fp,"%c",0x4E);
			fprintf(fp,"%c",0x75);
			fclose(fp);
			MessageBox(NULL,"ROM Expanded.","Note",MB_OK);
			return 0;
		}
		if(1572864+524288*sizesel<romsize){
			if(MessageBox(NULL,"Selected size is smaller than current size. Data may be lost. Continue?","Note",MB_YESNO)==IDYES){
			   i=_sopen(file, _O_RDWR, _SH_DENYNO);
			   if(i>-1)			   {
				  if( _chsize( i, 1572864+524288*sizesel ) == 0 ){
					 fp = fopen(file,"rb+");
					 romsize = 1572864 + 524288 * sizesel;
					 fseek(fp,420,SEEK_SET);
					 fprintf(fp,"%c",((romsize-1)&0xFF000000)/0x1000000);
					 fprintf(fp,"%c",((romsize-1)&0x00FF0000)/0x10000);
					 fprintf(fp,"%c",((romsize-1)&0x0000FF00)/0x100);
					 fprintf(fp,"%c",((romsize-1)&0x000000FF));
					 fseek(fp,1146,SEEK_SET);
					 fprintf(fp,"%c",0x4E);
					 fprintf(fp,"%c",0xB9);
					 fprintf(fp,"%c",0x00);
					 fprintf(fp,"%c",0x17);
					 fprintf(fp,"%c",0xFF);
					 fprintf(fp,"%c",0x70);
					 fseek(fp,1572720,SEEK_SET);
					 fprintf(fp,"%c",0x13);
					 fprintf(fp,"%c",0xFC);
					 fprintf(fp,"%c",0x00);
					 fprintf(fp,"%c",0x01);
					 fprintf(fp,"%c",0x00);
					 fprintf(fp,"%c",0xA1);
					 fprintf(fp,"%c",0x30);
					 fprintf(fp,"%c",0xF1);
					 fprintf(fp,"%c",0x4A);
					 fprintf(fp,"%c",0xB9);
					 fprintf(fp,"%c",0x00);
					 fprintf(fp,"%c",0xA1);
					 fprintf(fp,"%c",0x00);
					 fprintf(fp,"%c",0x08);
					 fprintf(fp,"%c",0x4E);
					 fprintf(fp,"%c",0x75);
					 fclose(fp);

					 MessageBox(NULL,"ROM Expanded.","Note",MB_OK);
				  }
				  else
					 MessageBox(NULL,"ROM Expansion failed.","Error",MB_OK);
				  _close( i );
			   }
			}
		}
	}
