void writePaletteStep(FILE * fp, int action, int arg = 0, int arg2 = 0, int arg3 = 0) {
	int a = 0;
	int b = 0;

	switch (action) {
	case 0://load

		//30 10  MOVE.W    (A0),D0
		fprintf(fp, "%c", 0x30);
		fprintf(fp, "%c", 0x10);

		break;
	case 1://save

		//30 80  MOVE.W    D0,(A0)
		fprintf(fp, "%c", 0x30);
		fprintf(fp, "%c", 0x80);

		break;
	case 2://filter

		a = 0x0100 * arg3 + 0x0010 * arg2 + arg;

		//02 40  AND.W     #$000E,D0
		fprintf(fp, "%c", 0x02);
		fprintf(fp, "%c", 0x40);
		fprintf(fp, "%c", (a & 0xFF00)/0x100);
		fprintf(fp, "%c", a & 0xFF);

		break;
	case 3://shift

		if (arg2) {
			if (arg) {
				//E3 D0  LSL.W     #1, (A0)
				fprintf(fp, "%c", 0xE3);
				fprintf(fp, "%c", 0xD0);
			} else {
				//E2 D0  LSR.W     #1, (A0)
				fprintf(fp, "%c", 0xE2);
				fprintf(fp, "%c", 0xD0);
			}
		} else {
			if (arg) {
				//E3 48  LSL.W     #1, D0
				fprintf(fp, "%c", 0xE3);
				fprintf(fp, "%c", 0x48);
			} else {
				//E2 48  LSR.W     #1, D0
				fprintf(fp, "%c", 0xE2);
				fprintf(fp, "%c", 0x48);
			}
		}
		break;
	case 4://cap
		
		if (!arg2) {
			if (arg) {
				//08 00 00 0C  BTST    #$C,D0
				fprintf(fp, "%c", 0x08);
				fprintf(fp, "%c", 0x00);
				fprintf(fp, "%c", 0x00);
				fprintf(fp, "%c", 0x0C);
				//67 04		   BEQ	   #$04
				fprintf(fp, "%c", 0x67);
				fprintf(fp, "%c", 0x04);
				//00 40 0E 00  ORI.W   #$0E00,D0
				fprintf(fp, "%c", 0x00);
				fprintf(fp, "%c", 0x40);
				fprintf(fp, "%c", 0x0E);
				fprintf(fp, "%c", 0x00);

				//08 00 00 08  BTST    #$8,D0
				fprintf(fp, "%c", 0x08);
				fprintf(fp, "%c", 0x00);
				fprintf(fp, "%c", 0x00);
				fprintf(fp, "%c", 0x08);
				//67 04		   BEQ	   #$04
				fprintf(fp, "%c", 0x67);
				fprintf(fp, "%c", 0x04);
				//00 40 00 E0  ORI.W   #$00E0,D0
				fprintf(fp, "%c", 0x00);
				fprintf(fp, "%c", 0x40);
				fprintf(fp, "%c", 0x00);
				fprintf(fp, "%c", 0xE0);

				//08 00 00 04  BTST    #$4,D0
				fprintf(fp, "%c", 0x08);
				fprintf(fp, "%c", 0x00);
				fprintf(fp, "%c", 0x00);
				fprintf(fp, "%c", 0x04);
				//67 04		   BEQ	   #$04
				fprintf(fp, "%c", 0x67);
				fprintf(fp, "%c", 0x04);
				//00 40 00 0E  ORI.W   #$000E,D0
				fprintf(fp, "%c", 0x00);
				fprintf(fp, "%c", 0x40);
				fprintf(fp, "%c", 0x00);
				fprintf(fp, "%c", 0x0E);

				//02 40  AND.W     #$0EEE,D0
				fprintf(fp, "%c", 0x02);
				fprintf(fp, "%c", 0x40);
				fprintf(fp, "%c", 0x0E);
				fprintf(fp, "%c", 0xEE);
			} else {
				//02 40  AND.W     #$0666,D0
				fprintf(fp, "%c", 0x02);
				fprintf(fp, "%c", 0x40);
				fprintf(fp, "%c", 0x06);
				fprintf(fp, "%c", 0x66);
			}
		} else {
			if (arg) {
				//08 10 00 0C  BTST    #$C,(A0)
				fprintf(fp, "%c", 0x08);
				fprintf(fp, "%c", 0x10);
				fprintf(fp, "%c", 0x00);
				fprintf(fp, "%c", 0x0C);
				//67 04		   BEQ	   #$04
				fprintf(fp, "%c", 0x67);
				fprintf(fp, "%c", 0x04);
				//00 50 0E 00  ORI.W   #$0E00,(A0)
				fprintf(fp, "%c", 0x00);
				fprintf(fp, "%c", 0x50);
				fprintf(fp, "%c", 0x0E);
				fprintf(fp, "%c", 0x00);

				//08 10 00 08  BTST    #$8,(A0)
				fprintf(fp, "%c", 0x08);
				fprintf(fp, "%c", 0x10);
				fprintf(fp, "%c", 0x00);
				fprintf(fp, "%c", 0x08);
				//67 04		   BEQ	   #$04
				fprintf(fp, "%c", 0x67);
				fprintf(fp, "%c", 0x04);
				//00 50 00 E0  ORI.W   #$00E0,(A0)
				fprintf(fp, "%c", 0x00);
				fprintf(fp, "%c", 0x50);
				fprintf(fp, "%c", 0x00);
				fprintf(fp, "%c", 0xE0);

				//08 10 00 04  BTST    #$4,(A0)
				fprintf(fp, "%c", 0x08);
				fprintf(fp, "%c", 0x10);
				fprintf(fp, "%c", 0x00);
				fprintf(fp, "%c", 0x04);
				//67 04		   BEQ	   #$04
				fprintf(fp, "%c", 0x67);
				fprintf(fp, "%c", 0x04);
				//00 50 00 0E  ORI.W   #$000E,(A0)
				fprintf(fp, "%c", 0x00);
				fprintf(fp, "%c", 0x50);
				fprintf(fp, "%c", 0x00);
				fprintf(fp, "%c", 0x0E);

				//02 50  AND.W     #$0EEE,(A0)
				fprintf(fp, "%c", 0x02);
				fprintf(fp, "%c", 0x50);
				fprintf(fp, "%c", 0x0E);
				fprintf(fp, "%c", 0xEE);
			} else {
				//02 50  AND.W     #$0666,(A0)
				fprintf(fp, "%c", 0x02);
				fprintf(fp, "%c", 0x50);
				fprintf(fp, "%c", 0x06);
				fprintf(fp, "%c", 0x66);
			}
		}


		break;
	case 5://mix

		//81 50 OR.W	D0,(A0)
		fprintf(fp, "%c", 0x81);
		fprintf(fp, "%c", 0x50);

		break;
	case 6://set


		b = 14 * 256 * arg3 + 14 * 16 * arg2 + 14 * arg;
		b = 0xEEE - b;

		//02 50  AND.W     #$0EEE,(A0)
		fprintf(fp, "%c", 0x02);
		fprintf(fp, "%c", 0x50);
		fprintf(fp, "%c", (b & 0xFF00) / 0x100);
		fprintf(fp, "%c", b & 0xFF);

		b = 0xEEE - b;

		//32 00 MOVE.W     D0,D1
		fprintf(fp, "%c", 0x32);
		fprintf(fp, "%c", 0x00);


		//02 41  AND.W     #$0666,D1
		fprintf(fp, "%c", 0x02);
		fprintf(fp, "%c", 0x41);
		fprintf(fp, "%c", (b & 0xFF00) / 0x100);
		fprintf(fp, "%c", b & 0xFF);

		//81 50 OR.W	D1,(A0)
		fprintf(fp, "%c", 0x81);
		fprintf(fp, "%c", 0x50);


		break;
	case 7://clear
		//42 40  CLR.W   D0
		fprintf(fp, "%c", 0x42);
		fprintf(fp, "%c", 0x40);
		break;
	case 8://add
		b = 0;
		if (arg) {
			//32 10  MOVE.W    (A0),D1
			fprintf(fp, "%c", 0x32);
			fprintf(fp, "%c", 0x10);

			//02 41  AND.W     #$0666,D1
			fprintf(fp, "%c", 0x02);
			fprintf(fp, "%c", 0x41);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x0E);

			//D0 41  ADD.W   D1,D0 
			fprintf(fp, "%c", 0xD0);
			fprintf(fp, "%c", 0x41);
		}
		if (arg2) {
			//32 10  MOVE.W    (A0),D1
			fprintf(fp, "%c", 0x32);
			fprintf(fp, "%c", 0x10);

			//02 41  AND.W     #$0666,D1
			fprintf(fp, "%c", 0x02);
			fprintf(fp, "%c", 0x41);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0xE0);

			//E8 49  LSR.W     #4, D1
			fprintf(fp, "%c", 0xE8);
			fprintf(fp, "%c", 0x49);

			//D0 41  ADD.W   D1,D0 
			fprintf(fp, "%c", 0xD0);
			fprintf(fp, "%c", 0x41);
		}
		if (arg3) {
			//32 10  MOVE.W    (A0),D1
			fprintf(fp, "%c", 0x32);
			fprintf(fp, "%c", 0x10);

			//02 41  AND.W     #$0666,D1
			fprintf(fp, "%c", 0x02);
			fprintf(fp, "%c", 0x41);
			fprintf(fp, "%c", 0x0E);
			fprintf(fp, "%c", 0x00);

			//E0 49  LSR.W     #8, D1
			fprintf(fp, "%c", 0xE0);
			fprintf(fp, "%c", 0x49);

			//D0 41  ADD.W   D1,D0 
			fprintf(fp, "%c", 0xD0);
			fprintf(fp, "%c", 0x41);
		}
		break;
	case 9://reduce
		switch (arg) {
		case 0:
			//02 40  AND.W     #$0666,D0
			fprintf(fp, "%c", 0x02);
			fprintf(fp, "%c", 0x40);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x0E);
			break;
		case 1:
			//02 40  AND.W     #$0666,D0
			fprintf(fp, "%c", 0x02);
			fprintf(fp, "%c", 0x40);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0xE0);
			//E8 48  LSR.W     #4, D0
			fprintf(fp, "%c", 0xE2);
			fprintf(fp, "%c", 0x48);
			break;
		case 2:
			//02 40  AND.W     #$0666,D0
			fprintf(fp, "%c", 0x02);
			fprintf(fp, "%c", 0x40);
			fprintf(fp, "%c", 0x0E);
			fprintf(fp, "%c", 0x00);
			//E0 48  LSR.W     #8, D0
			fprintf(fp, "%c", 0xE2);
			fprintf(fp, "%c", 0x48);
			break;
		}
		break;
	case 10://duplicate
		//02 40  AND.W     #$0666,D0
		fprintf(fp, "%c", 0x02);
		fprintf(fp, "%c", 0x40);
		fprintf(fp, "%c", 0x00);
		fprintf(fp, "%c", 0x0E);

		//32 00 MOVE.W     D0,D1
		fprintf(fp, "%c", 0x32);
		fprintf(fp, "%c", 0x00);

		//E8 49  LSR.W     #4, D1
		fprintf(fp, "%c", 0xE8);
		fprintf(fp, "%c", 0x49);

		//D0 41  ADD.W   D1,D0 
		fprintf(fp, "%c", 0xD0);
		fprintf(fp, "%c", 0x41);

		//E8 49  LSR.W     #4, D1
		fprintf(fp, "%c", 0xE8);
		fprintf(fp, "%c", 0x49);

		//D0 41  ADD.W   D1,D0 
		fprintf(fp, "%c", 0xD0);
		fprintf(fp, "%c", 0x41);

		break;
	case 11://mul/div
		if (arg) {
			//81 FC  DIVS.W  #$0064,D0
			fprintf(fp, "%c", 0x81);
			fprintf(fp, "%c", 0xFC);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", arg2);
		} else {
			//C0 FC  MULU.W  #$0012, D0
			fprintf(fp, "%c", 0xC0);
			fprintf(fp, "%c", 0xFC);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", arg2);
		}
		break;
	}
}

void writePaletteScript(FILE * fp, unsigned char script[][4], int len) {
	for (int i = 0; i < len; i++) {
		writePaletteStep(fp, script[i][0], script[i][1], script[i][2], script[i][3]);
	}
}

void SaveSpellAnim(FILE * fp) {
	PixelCompressor PC(fp);

	fseek(fp, 0x12648C, SEEK_SET);
	fprintf(fp, "%c", 0x4E);
	fprintf(fp, "%c", 0xF9);
	fprintf(fp, "%c", 0x00);
	fprintf(fp, "%c", 0x05);
	fprintf(fp, "%c", 0x00);
	fprintf(fp, "%c", 0x00);
	fprintf(fp, "%c", 0x4E);
	fprintf(fp, "%c", 0x71);

	fseek(fp, 0x50000, SEEK_SET);
	fprintf(fp, "%c", 0x0C);
	fprintf(fp, "%c", 0x00);
	fprintf(fp, "%c", 0x00);
	fprintf(fp, "%c", 0x4C);
	fprintf(fp, "%c", 0x6C);
	fprintf(fp, "%c", 0x14);
	fprintf(fp, "%c", 0x3E);
	fprintf(fp, "%c", 0x00);
	fprintf(fp, "%c", 0xDE);
	fprintf(fp, "%c", 0x47);
	fprintf(fp, "%c", 0x41);
	fprintf(fp, "%c", 0xF9);
	fprintf(fp, "%c", 0x00);
	fprintf(fp, "%c", 0x12);
	fprintf(fp, "%c", 0x64);
	fprintf(fp, "%c", 0x98);
	fprintf(fp, "%c", 0xD0);
	fprintf(fp, "%c", 0xC7);
	fprintf(fp, "%c", 0x3E);
	fprintf(fp, "%c", 0x10);

	fprintf(fp, "%c", 0x4E);
	fprintf(fp, "%c", 0xF9);
	fprintf(fp, "%c", 0x00);
	fprintf(fp, "%c", 0x12);
	fprintf(fp, "%c", 0x64);
	fprintf(fp, "%c", 0x94);

	fprintf(fp, "%c", 0x04);
	fprintf(fp, "%c", 0x00);
	fprintf(fp, "%c", 0x00);
	fprintf(fp, "%c", 0x4C);
	fprintf(fp, "%c", 0x3E);
	fprintf(fp, "%c", 0x00);
	fprintf(fp, "%c", 0xDE);
	fprintf(fp, "%c", 0x47);
	fprintf(fp, "%c", 0x3E);
	fprintf(fp, "%c", 0x3B);
	fprintf(fp, "%c", 0x70);
	fprintf(fp, "%c", 0x06);
	fprintf(fp, "%c", 0x4E);
	fprintf(fp, "%c", 0xFB);
	fprintf(fp, "%c", 0x70);
	fprintf(fp, "%c", 0x02);

	fseek(fp, 0x12724A, SEEK_SET);
	fprintf(fp, "%c", 0x4E);
	fprintf(fp, "%c", 0xF9);
	fprintf(fp, "%c", 0x00);
	fprintf(fp, "%c", 0x06);
	fprintf(fp, "%c", 0x00);
	fprintf(fp, "%c", 0x00);
	fprintf(fp, "%c", 0x4E);
	fprintf(fp, "%c", 0x71);
	fprintf(fp, "%c", 0x4E);
	fprintf(fp, "%c", 0x71);

	fseek(fp, 0x60000, SEEK_SET);
	fprintf(fp, "%c", 0x1E);
	fprintf(fp, "%c", 0x38);
	fprintf(fp, "%c", 0xB5);
	fprintf(fp, "%c", 0xBF);
	fprintf(fp, "%c", 0x0C);
	fprintf(fp, "%c", 0x07);
	fprintf(fp, "%c", 0x00);
	fprintf(fp, "%c", 0x15);
	fprintf(fp, "%c", 0x6C);
	fprintf(fp, "%c", 0x12);
	fprintf(fp, "%c", 0xDE);
	fprintf(fp, "%c", 0x47);
	fprintf(fp, "%c", 0x41);
	fprintf(fp, "%c", 0xF9);
	fprintf(fp, "%c", 0x00);
	fprintf(fp, "%c", 0x12);
	fprintf(fp, "%c", 0x72);
	fprintf(fp, "%c", 0x58);
	fprintf(fp, "%c", 0xD0);
	fprintf(fp, "%c", 0xC7);
	fprintf(fp, "%c", 0x3E);
	fprintf(fp, "%c", 0x10);

	fprintf(fp, "%c", 0x4E);
	fprintf(fp, "%c", 0xF9);
	fprintf(fp, "%c", 0x00);
	fprintf(fp, "%c", 0x12);
	fprintf(fp, "%c", 0x72);
	fprintf(fp, "%c", 0x54);

	fprintf(fp, "%c", 0x04);
	fprintf(fp, "%c", 0x07);
	fprintf(fp, "%c", 0x00);
	fprintf(fp, "%c", 0x15);
	fprintf(fp, "%c", 0xDE);
	fprintf(fp, "%c", 0x47);
	fprintf(fp, "%c", 0x3E);
	fprintf(fp, "%c", 0x3B);
	fprintf(fp, "%c", 0x70);
	fprintf(fp, "%c", 0x06);
	fprintf(fp, "%c", 0x4E);
	fprintf(fp, "%c", 0xFB);
	fprintf(fp, "%c", 0x70);
	fprintf(fp, "%c", 0x02);

	long o, o2, o3, o4, o5, o6, ot, ot2, d, lp;

	lp = 0x4FF00;//loop

	o  = 0x5002A;//main routine offsets
	o2 = 0x50100;//main routines

	o3 = 0x6002A;//frame routine offsets
	o4 = 0x60100;//frame routines

	o5 = 0x400000;//palettes
	o6 = 0x401000;//graphics


	fseek(fp, lp, SEEK_SET);

	//loop routine
	fprintf(fp, "%c", 0x4E);
	fprintf(fp, "%c", 0x40);
	fprintf(fp, "%c", 0x00);
	fprintf(fp, "%c", 0x4D);
	fprintf(fp, "%c", 0x7E);
	fprintf(fp, "%c", 0x04);

	fprintf(fp, "%c", 0x33);
	fprintf(fp, "%c", 0xC4);
	fprintf(fp, "%c", 0x00);
	fprintf(fp, "%c", 0xFF);
	fprintf(fp, "%c", 0x00);
	fprintf(fp, "%c", 0x00);

	fprintf(fp, "%c", 0x70);
	fprintf(fp, "%c", 0x05);
	fprintf(fp, "%c", 0x4E);
	fprintf(fp, "%c", 0xB9);
	fprintf(fp, "%c", 0x00);
	fprintf(fp, "%c", 0x00);
	fprintf(fp, "%c", 0x02);
	fprintf(fp, "%c", 0x44);

	fprintf(fp, "%c", 0x42);
	fprintf(fp, "%c", 0x79);
	fprintf(fp, "%c", 0x00);
	fprintf(fp, "%c", 0xFF);
	fprintf(fp, "%c", 0x00);
	fprintf(fp, "%c", 0x00);

	fprintf(fp, "%c", 0x4E);
	fprintf(fp, "%c", 0xB9);
	fprintf(fp, "%c", 0x00);
	fprintf(fp, "%c", 0x00);
	fprintf(fp, "%c", 0x02);
	fprintf(fp, "%c", 0x24);

	fprintf(fp, "%c", 0x70);
	fprintf(fp, "%c", 0x05);
	fprintf(fp, "%c", 0x4E);
	fprintf(fp, "%c", 0xB9);
	fprintf(fp, "%c", 0x00);
	fprintf(fp, "%c", 0x00);
	fprintf(fp, "%c", 0x02);
	fprintf(fp, "%c", 0x44);

	fprintf(fp, "%c", 0x51);
	fprintf(fp, "%c", 0xCF);
	fprintf(fp, "%c", 0xFF);
	fprintf(fp, "%c", 0xDC);
	fprintf(fp, "%c", 0x4E);
	fprintf(fp, "%c", 0x75);

	for (int i = 0; i < NumSpellAnim; i++) {
		fseek(fp, o2, SEEK_SET);

		//palette routine
		ot = ftell(fp);
		fprintf(fp, "%c", 0x4E);
		fprintf(fp, "%c", 0xB9);
		fprintf(fp, "%c", 0x00);
		fprintf(fp, "%c", 0x12);
		fprintf(fp, "%c", 0x67);
		fprintf(fp, "%c", 0x8E);

		fprintf(fp, "%c", 0x48);
		fprintf(fp, "%c", 0xE7);
		fprintf(fp, "%c", 0xC0);
		fprintf(fp, "%c", 0x80);

		fprintf(fp, "%c", 0x41);
		fprintf(fp, "%c", 0xF9);
		fprintf(fp, "%c", 0x00);
		fprintf(fp, "%c", 0xFF);
		fprintf(fp, "%c", 0x00);
		fprintf(fp, "%c", 0x00);

		fprintf(fp, "%c", 0x7E);
		fprintf(fp, "%c", 0x3F);
		ot2 = ftell(fp);

		writePaletteScript(fp, PaletteScript[i], PSLen[i]);

		fprintf(fp, "%c", 0xD0);
		fprintf(fp, "%c", 0xFC);
		fprintf(fp, "%c", 0x00);
		fprintf(fp, "%c", 0x02);

		d = ftell(fp) - ot2 + 2;
		d = 0x10000 - d;

		fprintf(fp, "%c", 0x51);
		fprintf(fp, "%c", 0xCF);
		fprintf(fp, "%c", (d & 0xFF00) / 0x100);
		fprintf(fp, "%c", d & 0xFF);
		fprintf(fp, "%c", 0x4C);
		fprintf(fp, "%c", 0xDF);
		fprintf(fp, "%c", 0x01);
		fprintf(fp, "%c", 0x03);
		fprintf(fp, "%c", 0x4E);
		fprintf(fp, "%c", 0x75);

		ot2 = ftell(fp);
		//init routine
		fprintf(fp, "%c", 0x3F);
		fprintf(fp, "%c", 0x03);
		fprintf(fp, "%c", 0x4E);
		fprintf(fp, "%c", 0xB9);
		fprintf(fp, "%c", (ot & 0xFF000000) / 0x1000000);
		fprintf(fp, "%c", (ot & 0x00FF0000) / 0x10000);
		fprintf(fp, "%c", (ot & 0x0000FF00) / 0x100);
		fprintf(fp, "%c", (ot & 0x000000FF));

		fprintf(fp, "%c", 0x13);
		fprintf(fp, "%c", 0xFC);
		fprintf(fp, "%c", 0x00);
		fprintf(fp, "%c", 0x08);
		fprintf(fp, "%c", 0x00);
		fprintf(fp, "%c", 0xA1);
		fprintf(fp, "%c", 0x30);
		fprintf(fp, "%c", 0xFF);

		fprintf(fp, "%c", 0x41);
		fprintf(fp, "%c", 0xF9);
		fprintf(fp, "%c", (o5 & 0xFF000000) / 0x1000000);
		fprintf(fp, "%c", (o5 & 0x00FF0000) / 0x10000);
		fprintf(fp, "%c", (o5 & 0x0000FF00) / 0x100);
		fprintf(fp, "%c", (o5 & 0x000000FF));
		fprintf(fp, "%c", 0x43);
		fprintf(fp, "%c", 0xF9);
		fprintf(fp, "%c", 0x00);
		fprintf(fp, "%c", 0xFF);
		fprintf(fp, "%c", 0x00);
		fprintf(fp, "%c", 0x2C);
		fprintf(fp, "%c", 0x22);
		fprintf(fp, "%c", 0xD8);
		fprintf(fp, "%c", 0x22);
		fprintf(fp, "%c", 0xD8);
		fprintf(fp, "%c", 0x32);
		fprintf(fp, "%c", 0xD8);
		fprintf(fp, "%c", 0x4E);
		fprintf(fp, "%c", 0xB9);
		fprintf(fp, "%c", 0x00);
		fprintf(fp, "%c", 0x00);
		fprintf(fp, "%c", 0x02);
		fprintf(fp, "%c", 0x24);

		fprintf(fp, "%c", 0x41);
		fprintf(fp, "%c", 0xF9);
		fprintf(fp, "%c", (o6 & 0xFF000000) / 0x1000000);
		fprintf(fp, "%c", (o6 & 0x00FF0000) / 0x10000);
		fprintf(fp, "%c", (o6 & 0x0000FF00) / 0x100);
		fprintf(fp, "%c", (o6 & 0x000000FF));

		fprintf(fp, "%c", 0x30);
		fprintf(fp, "%c", 0x3C);
		fprintf(fp, "%c", 0xB8);
		fprintf(fp, "%c", 0x00);
		fprintf(fp, "%c", 0x32);
		fprintf(fp, "%c", 0x40);
		fprintf(fp, "%c", 0x30);
		fprintf(fp, "%c", 0x3C);
		fprintf(fp, "%c", 0x0C);
		fprintf(fp, "%c", 0x00);
		fprintf(fp, "%c", 0x72);
		fprintf(fp, "%c", 0x02);
		fprintf(fp, "%c", 0x4E);
		fprintf(fp, "%c", 0xB9);
		fprintf(fp, "%c", 0x00);
		fprintf(fp, "%c", 0x00);
		fprintf(fp, "%c", 0x02);
		fprintf(fp, "%c", 0x98);
		fprintf(fp, "%c", 0x4E);
		fprintf(fp, "%c", 0xB9);
		fprintf(fp, "%c", 0x00);
		fprintf(fp, "%c", 0x00);
		fprintf(fp, "%c", 0x02);
		fprintf(fp, "%c", 0x64);

		fprintf(fp, "%c", 0x13);
		fprintf(fp, "%c", 0xFC);
		fprintf(fp, "%c", 0x00);
		fprintf(fp, "%c", 0x07);
		fprintf(fp, "%c", 0x00);
		fprintf(fp, "%c", 0xA1);
		fprintf(fp, "%c", 0x30);
		fprintf(fp, "%c", 0xFF);

		fprintf(fp, "%c", 0x36);
		fprintf(fp, "%c", 0x1F);
		fprintf(fp, "%c", 0x4E);
		fprintf(fp, "%c", 0x75);

		o2 = ftell(fp);
		fseek(fp, o, SEEK_SET);
		for (int j = 0; j < 8; j++) {
			fprintf(fp, "%c", ((o2 + j * 4 - 0x5002A) & 0xFF00) / 0x100);
			fprintf(fp, "%c", ((o2 + j * 4 - 0x5002A) & 0xFF));
			o += 2;
		}

		fseek(fp, o2, SEEK_SET);

		//wrappers
		for (int j = 0;j < 4;j++) {
			fprintf(fp, "%c", 0x76);
			fprintf(fp, "%c", j+1);
			fprintf(fp, "%c", 0x60);
			fprintf(fp, "%c", 26 - 8 * j);
			fprintf(fp, "%c", 0x76);
			fprintf(fp, "%c", 128 + j+1);
			if (j < 3) {
				fprintf(fp, "%c", 0x60);
				fprintf(fp, "%c", 22 - 8 * j);
			}
		}


		//write main routine
		fprintf(fp, "%c", 0x4E);
		fprintf(fp, "%c", 0xB9);
		fprintf(fp, "%c", (ot2 & 0xFF000000) / 0x1000000);
		fprintf(fp, "%c", (ot2 & 0x00FF0000) / 0x10000);
		fprintf(fp, "%c", (ot2 & 0x0000FF00) / 0x100);
		fprintf(fp, "%c", (ot2 & 0x000000FF));
		fprintf(fp, "%c", 0x4E);
		fprintf(fp, "%c", 0xB9);
		fprintf(fp, "%c", 0x00);
		fprintf(fp, "%c", 0x12);
		fprintf(fp, "%c", 0x6A);
		fprintf(fp, "%c", 0xD6);

		fprintf(fp, "%c", 0x11);
		fprintf(fp, "%c", 0xC3);
		fprintf(fp, "%c", 0xB5);
		fprintf(fp, "%c", 0xBE);
		fprintf(fp, "%c", 0x74);
		fprintf(fp, "%c", 0x15);
		fprintf(fp, "%c", 0x11);
		fprintf(fp, "%c", 0xC2);
		fprintf(fp, "%c", 0xB5);
		fprintf(fp, "%c", 0xBF);
		fprintf(fp, "%c", 0x42);
		fprintf(fp, "%c", 0x38);
		fprintf(fp, "%c", 0xB5);
		fprintf(fp, "%c", 0xBD);
		fprintf(fp, "%c", 0x11);
		fprintf(fp, "%c", 0xFC);
		fprintf(fp, "%c", 0x00);
		fprintf(fp, "%c", 0x01);
		fprintf(fp, "%c", 0xB5);
		fprintf(fp, "%c", 0xBC);

		//starting graphics here ****


		d = RGBToGen(FlickerColor[i][2]) * 256 + RGBToGen(FlickerColor[i][1]) * 16 + RGBToGen(FlickerColor[i][0]);
		fprintf(fp, "%c", 0x38);
		fprintf(fp, "%c", 0x3C);
		fprintf(fp, "%c", (d & 0xFF00) / 0x100);
		fprintf(fp, "%c", d & 0xFF);
		fprintf(fp, "%c", 0x4E);
		fprintf(fp, "%c", 0xF9);
		fprintf(fp, "%c", (lp & 0xFF000000) / 0x1000000);
		fprintf(fp, "%c", (lp & 0x00FF0000) / 0x10000);
		fprintf(fp, "%c", (lp & 0x0000FF00) / 0x100);
		fprintf(fp, "%c", (lp & 0x000000FF));

		o2 = ftell(fp);


		fseek(fp, o3, SEEK_SET);
		fprintf(fp, "%c", ((o4 - 0x6002A) & 0xFF00) / 0x100);
		fprintf(fp, "%c", ((o4 - 0x6002A) & 0xFF));
		o3 += 2;

		fseek(fp, o4, SEEK_SET);
		//write frame routine

		//just end for now****

		fprintf(fp, "%c", 0x0C);
		fprintf(fp, "%c", 0x38);
		fprintf(fp, "%c", 0x00);
		fprintf(fp, "%c", 0xFF);
		fprintf(fp, "%c", 0xB5);
		fprintf(fp, "%c", 0xBD);
		fprintf(fp, "%c", 0x66);
		fprintf(fp, "%c", 0x0A);

		fprintf(fp, "%c", 0x42);
		fprintf(fp, "%c", 0x38);
		fprintf(fp, "%c", 0xB5);
		fprintf(fp, "%c", 0xBC);
		fprintf(fp, "%c", 0x4E);
		fprintf(fp, "%c", 0xB9);
		fprintf(fp, "%c", 0x00);
		fprintf(fp, "%c", 0x12);
		fprintf(fp, "%c", 0x69);
		fprintf(fp, "%c", 0x82);

		fprintf(fp, "%c", 0x4E);
		fprintf(fp, "%c", 0xB9);
		fprintf(fp, "%c", 0x00);
		fprintf(fp, "%c", 0x00);
		fprintf(fp, "%c", 0x02);
		fprintf(fp, "%c", 0x24);
		fprintf(fp, "%c", 0x4E);
		fprintf(fp, "%c", 0xB9);
		fprintf(fp, "%c", 0x00);
		fprintf(fp, "%c", 0x12);
		fprintf(fp, "%c", 0x83);
		fprintf(fp, "%c", 0xE2);
		fprintf(fp, "%c", 0x4E);
		fprintf(fp, "%c", 0x75);

		o4 = ftell(fp);

		fseek(fp, o5, SEEK_SET);
		writePalette(SpellAnimPal[i], 5, fp);
		for (int j = 0;j < NumAnimGFX[i];j++) {
			for (int k = 0;k < 5;k++) {
				fprintf(fp, "%c", AnimGFX[i][j][k]);
			}
		}
		o5 = ftell(fp);

		fseek(fp, o6, SEEK_SET);
		PC.PutData(SAGFXSize[i][0], SAGFXSize[i][0] * SAGFXSize[i][1], SpellAnimGFX[i]);
		o6 = ftell(fp);
	}
}


void CopySelectedAnim() {
	int m = select[mode];

	switch (subselect[mode][7]) {
	case 2:
		ToClipboard(SpellAnimGFX[m], SAGFXSize[m], SpellAnimPal[m], false, false);
		break;
	}
}