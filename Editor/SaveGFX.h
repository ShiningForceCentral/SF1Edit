void SaveGFX() {
	if (!GraphicsLoaded)return;
	if (!strlen(file)) {
		int ret = IDYES;
		OPENFILENAME openFileName;
		char path[256];
		path[0] = '\0';
		memset(&openFileName, 0, sizeof(openFileName));
		openFileName.lStructSize = sizeof(openFileName);
		openFileName.hwndOwner = NULL;
		openFileName.hInstance = NULL;
		openFileName.lpstrFilter = "Genesis ROM(*.bin)\0*.bin\0";
		openFileName.lpstrCustomFilter = NULL;
		openFileName.nMaxCustFilter = 0;
		openFileName.nFilterIndex = 0;
		openFileName.lpstrFile = path;
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

		if (GetOpenFileName(&openFileName) != 0) {
			sprintf(file, path);
		}
	}


	if (strlen(file)) {
		int s;

		unsigned int len;
		unsigned long o, o2, d;



		FILE * fp = fopen(file, "rb+");

		if (0x400000>romsize) {
			MessageBox(NULL, "Rom is too small, expand rom.", "Error", MB_OK);
			fclose(fp);
			return;
		}

		if (ExpandedGraphics && 0x600000>romsize) {
			MessageBox(NULL, "Rom is too small, expand rom.", "Error", MB_OK);
			fclose(fp);
			return;
		}

		fseek(fp, 0xE1A6, SEEK_SET);
		fprintf(fp, "%c", 0x04);
		fprintf(fp, "%c", 0x00);

		if (ChooseMSPal) {
			fseek(fp, 0x10136, SEEK_SET);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0xB9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x23);
			fprintf(fp, "%c", 0xEF);
			fprintf(fp, "%c", 0x00);

			fseek(fp, 0x98FA, SEEK_SET);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0xB9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x23);
			fprintf(fp, "%c", 0xEF);
			fprintf(fp, "%c", 0x20);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0x71);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0x71);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0x71);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0x71);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0x71);

			fseek(fp, 0x9ADE, SEEK_SET);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0xB9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x23);
			fprintf(fp, "%c", 0xEF);
			fprintf(fp, "%c", 0x20);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0x71);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0x71);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0x71);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0x71);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0x71);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0x71);

			fseek(fp, 0x8948, SEEK_SET);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0xB9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x23);
			fprintf(fp, "%c", 0xEF);
			fprintf(fp, "%c", 0x20);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0x71);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0x71);

			fseek(fp, 0x8964, SEEK_SET);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0x71);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0x71);

			fseek(fp, 0x23EF20, SEEK_SET);
			fprintf(fp, "%c", 0x48);
			fprintf(fp, "%c", 0xE7);
			fprintf(fp, "%c", 0x60);
			fprintf(fp, "%c", 0x40);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0xB9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x02);
			fprintf(fp, "%c", 0x03);
			fprintf(fp, "%c", 0x08);
			fprintf(fp, "%c", 0x43);
			fprintf(fp, "%c", 0xFA);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x34);
			fprintf(fp, "%c", 0x42);
			fprintf(fp, "%c", 0x42);
			fprintf(fp, "%c", 0x14);
			fprintf(fp, "%c", 0x01);
			fprintf(fp, "%c", 0xE6);
			fprintf(fp, "%c", 0x4A);
			fprintf(fp, "%c", 0xD2);
			fprintf(fp, "%c", 0xC2);
			fprintf(fp, "%c", 0x74);
			fprintf(fp, "%c", 0x07);
			fprintf(fp, "%c", 0x02);
			fprintf(fp, "%c", 0x01);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x07);
			fprintf(fp, "%c", 0x94);
			fprintf(fp, "%c", 0x01);
			fprintf(fp, "%c", 0x12);
			fprintf(fp, "%c", 0x11);
			fprintf(fp, "%c", 0xE4);
			fprintf(fp, "%c", 0x69);

			fprintf(fp, "%c", 0xC0);
			fprintf(fp, "%c", 0xFC);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x12);
			fprintf(fp, "%c", 0x06);
			fprintf(fp, "%c", 0x40);
			fprintf(fp, "%c", 0x61);
			fprintf(fp, "%c", 0x00);

			fprintf(fp, "%c", 0x08);
			fprintf(fp, "%c", 0x01);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x66);
			fprintf(fp, "%c", 0x04);
			fprintf(fp, "%c", 0x04);
			fprintf(fp, "%c", 0x40);
			fprintf(fp, "%c", 0x20);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x4C);
			fprintf(fp, "%c", 0xDF);
			fprintf(fp, "%c", 0x02);
			fprintf(fp, "%c", 0x06);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0x75);

			fseek(fp, 0x23EF00, SEEK_SET);
			fprintf(fp, "%c", 0x1E);
			fprintf(fp, "%c", 0x18);
			fprintf(fp, "%c", 0x08);
			fprintf(fp, "%c", 0x39);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x07);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x23);
			fprintf(fp, "%c", 0xEF);
			fprintf(fp, "%c", 0x60);
			fprintf(fp, "%c", 0x66);
			fprintf(fp, "%c", 0x06);

			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x07);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0xC0);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0x75);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x07);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0xE0);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0x75);

			fseek(fp, 0x11C9C, SEEK_SET);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0xB9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x23);
			fprintf(fp, "%c", 0xEC);
			fprintf(fp, "%c", 0x80);

			fseek(fp, 0x23EC80, SEEK_SET);
			fprintf(fp, "%c", 0xE6);
			fprintf(fp, "%c", 0x08);
			fprintf(fp, "%c", 0x48);
			fprintf(fp, "%c", 0xE7);
			fprintf(fp, "%c", 0x60);
			fprintf(fp, "%c", 0x40);

			fprintf(fp, "%c", 0x12);
			fprintf(fp, "%c", 0x10);

			fprintf(fp, "%c", 0x43);
			fprintf(fp, "%c", 0xFA);
			fprintf(fp, "%c", 0x02);
			fprintf(fp, "%c", 0xD6);
			fprintf(fp, "%c", 0x42);
			fprintf(fp, "%c", 0x42);
			fprintf(fp, "%c", 0x14);
			fprintf(fp, "%c", 0x01);
			fprintf(fp, "%c", 0xE6);
			fprintf(fp, "%c", 0x4A);
			fprintf(fp, "%c", 0xD2);
			fprintf(fp, "%c", 0xC2);
			fprintf(fp, "%c", 0x74);
			fprintf(fp, "%c", 0x07);
			fprintf(fp, "%c", 0x02);
			fprintf(fp, "%c", 0x01);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x07);
			fprintf(fp, "%c", 0x94);
			fprintf(fp, "%c", 0x01);
			fprintf(fp, "%c", 0x12);
			fprintf(fp, "%c", 0x11);
			fprintf(fp, "%c", 0xE4);
			fprintf(fp, "%c", 0x69);

			fprintf(fp, "%c", 0x08);
			fprintf(fp, "%c", 0x01);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x66);
			fprintf(fp, "%c", 0x06);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0xC0);
			fprintf(fp, "%c", 0x60);
			fprintf(fp, "%c", 0x04);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0xE0);
			fprintf(fp, "%c", 0x4C);
			fprintf(fp, "%c", 0xDF);
			fprintf(fp, "%c", 0x02);
			fprintf(fp, "%c", 0x06);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0x75);


		} else {
			fseek(fp, 0x10136, SEEK_SET);
			fprintf(fp, "%c", 0x1E);
			fprintf(fp, "%c", 0x18);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x07);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0xC0);

			fseek(fp, 0x98FA, SEEK_SET);
			fprintf(fp, "%c", 0xC0);
			fprintf(fp, "%c", 0xFC);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x12);
			fprintf(fp, "%c", 0x06);
			fprintf(fp, "%c", 0x40);
			fprintf(fp, "%c", 0x61);
			fprintf(fp, "%c", 0x00);

			fprintf(fp, "%c", 0x4A);
			fprintf(fp, "%c", 0x10);
			fprintf(fp, "%c", 0x6D);
			fprintf(fp, "%c", 0x04);
			fprintf(fp, "%c", 0x04);
			fprintf(fp, "%c", 0x40);
			fprintf(fp, "%c", 0x20);
			fprintf(fp, "%c", 0x00);

			fseek(fp, 0x9ADE, SEEK_SET);
			fprintf(fp, "%c", 0xC0);
			fprintf(fp, "%c", 0xFC);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x12);
			fprintf(fp, "%c", 0x06);
			fprintf(fp, "%c", 0x40);
			fprintf(fp, "%c", 0x61);
			fprintf(fp, "%c", 0x00);

			fprintf(fp, "%c", 0x0C);
			fprintf(fp, "%c", 0x10);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0xFF);
			fprintf(fp, "%c", 0x6D);
			fprintf(fp, "%c", 0x04);
			fprintf(fp, "%c", 0x04);
			fprintf(fp, "%c", 0x40);
			fprintf(fp, "%c", 0x20);
			fprintf(fp, "%c", 0x00);

			fseek(fp, 0x8948, SEEK_SET);
			fprintf(fp, "%c", 0xE7);
			fprintf(fp, "%c", 0x48);
			fprintf(fp, "%c", 0xD0);
			fprintf(fp, "%c", 0x47);
			fprintf(fp, "%c", 0xD0);
			fprintf(fp, "%c", 0x40);
			fprintf(fp, "%c", 0x06);
			fprintf(fp, "%c", 0x40);
			fprintf(fp, "%c", 0x41);
			fprintf(fp, "%c", 0x00);

			fseek(fp, 0x8964, SEEK_SET);
			fprintf(fp, "%c", 0x06);
			fprintf(fp, "%c", 0x40);
			fprintf(fp, "%c", 0x20);
			fprintf(fp, "%c", 0x00);

			fseek(fp, 0x11C9C, SEEK_SET);
			fprintf(fp, "%c", 0xE6);
			fprintf(fp, "%c", 0x08);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x40);
		}

		fseek(fp, 0x23FFFF, SEEK_SET);
		fprintf(fp, "%c", NumGFX[0]);
		fseek(fp, 0x23FCFF, SEEK_SET);
		fprintf(fp, "%c", NumGFX[1]);
		fseek(fp, 0x23EFFF, SEEK_SET);
		fprintf(fp, "%c", NumGFX[7]);
		fseek(fp, 0x23ECFF, SEEK_SET);
		fprintf(fp, "%c", NumGFX[6]);

		fseek(fp, 0x1FFF50, SEEK_SET);
		fprintf(fp, "%c", 0x13);
		fprintf(fp, "%c", 0xFC);
		fprintf(fp, "%c", 0x00);
		fprintf(fp, "%c", 0x00);
		fprintf(fp, "%c", 0x00);
		fprintf(fp, "%c", 0xA1);
		fprintf(fp, "%c", 0x30);
		fprintf(fp, "%c", 0xF1);
		fprintf(fp, "%c", 0x20);
		fprintf(fp, "%c", 0x79);
		fprintf(fp, "%c", 0x00);
		fprintf(fp, "%c", 0x14);
		fprintf(fp, "%c", 0x40);
		fprintf(fp, "%c", 0x00);

		if (ExpandedGraphics) {
			fprintf(fp, "%c", 0x13);
			fprintf(fp, "%c", 0xFC);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x08);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0xA1);
			fprintf(fp, "%c", 0x30);
			fprintf(fp, "%c", 0xFD);
			fprintf(fp, "%c", 0x13);
			fprintf(fp, "%c", 0xFC);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x09);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0xA1);
			fprintf(fp, "%c", 0x30);
			fprintf(fp, "%c", 0xFF);
		}

		fprintf(fp, "%c", 0x4E);
		fprintf(fp, "%c", 0x75);

		fseek(fp, 0x1FFF70, SEEK_SET);
		fprintf(fp, "%c", 0x13);
		fprintf(fp, "%c", 0xFC);
		fprintf(fp, "%c", 0x00);
		fprintf(fp, "%c", 0x01);
		fprintf(fp, "%c", 0x00);
		fprintf(fp, "%c", 0xA1);
		fprintf(fp, "%c", 0x30);
		fprintf(fp, "%c", 0xF1);
		fprintf(fp, "%c", 0x41);
		fprintf(fp, "%c", 0xF9);
		fprintf(fp, "%c", 0x00);
		fprintf(fp, "%c", 0xFF);
		fprintf(fp, "%c", 0x30);
		fprintf(fp, "%c", 0x00);

		if (ExpandedGraphics) {
			fprintf(fp, "%c", 0x13);
			fprintf(fp, "%c", 0xFC);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x06);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0xA1);
			fprintf(fp, "%c", 0x30);
			fprintf(fp, "%c", 0xFD);
			fprintf(fp, "%c", 0x13);
			fprintf(fp, "%c", 0xFC);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x07);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0xA1);
			fprintf(fp, "%c", 0x30);
			fprintf(fp, "%c", 0xFF);
		}

		fprintf(fp, "%c", 0x4E);
		fprintf(fp, "%c", 0x75);



		if (ExpandedGraphics) {


			fseek(fp, 0x1262A8, SEEK_SET);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0xB9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x1F);
			fprintf(fp, "%c", 0xFE);
			fprintf(fp, "%c", 0x60);

			fseek(fp, 0x126284, SEEK_SET);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0xB9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x1F);
			fprintf(fp, "%c", 0xFE);
			fprintf(fp, "%c", 0x60);


			fseek(fp, 0x1FFE60, SEEK_SET);
			fprintf(fp, "%c", 0x20);
			fprintf(fp, "%c", 0x79);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x10);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x00);

			fprintf(fp, "%c", 0x13);
			fprintf(fp, "%c", 0xFC);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x0A);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0xA1);
			fprintf(fp, "%c", 0x30);
			fprintf(fp, "%c", 0xFD);
			fprintf(fp, "%c", 0x13);
			fprintf(fp, "%c", 0xFC);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x0B);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0xA1);
			fprintf(fp, "%c", 0x30);
			fprintf(fp, "%c", 0xFF);

			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0x75);

			fseek(fp, 0x1262C6, SEEK_SET);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0xB9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x1F);
			fprintf(fp, "%c", 0xFE);
			fprintf(fp, "%c", 0x80);

			fseek(fp, 0x1FFE80, SEEK_SET);
			fprintf(fp, "%c", 0x41);
			fprintf(fp, "%c", 0xF9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0xFF);
			fprintf(fp, "%c", 0x30);
			fprintf(fp, "%c", 0x00);


			fprintf(fp, "%c", 0x13);
			fprintf(fp, "%c", 0xFC);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x06);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0xA1);
			fprintf(fp, "%c", 0x30);
			fprintf(fp, "%c", 0xFD);
			fprintf(fp, "%c", 0x13);
			fprintf(fp, "%c", 0xFC);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x07);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0xA1);
			fprintf(fp, "%c", 0x30);
			fprintf(fp, "%c", 0xFF);

			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0x75);




			fseek(fp, 0x1262A2, SEEK_SET);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0xF9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x1F);
			fprintf(fp, "%c", 0xFE);
			fprintf(fp, "%c", 0xA0);

			fseek(fp, 0x1FFEA0, SEEK_SET);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0xB9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x02);
			fprintf(fp, "%c", 0xBC);


			fprintf(fp, "%c", 0x13);
			fprintf(fp, "%c", 0xFC);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x06);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0xA1);
			fprintf(fp, "%c", 0x30);
			fprintf(fp, "%c", 0xFD);
			fprintf(fp, "%c", 0x13);
			fprintf(fp, "%c", 0xFC);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x07);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0xA1);
			fprintf(fp, "%c", 0x30);
			fprintf(fp, "%c", 0xFF);

			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0x75);

			fseek(fp, 0x126380, SEEK_SET);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0xB9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x1F);
			fprintf(fp, "%c", 0xFE);
			fprintf(fp, "%c", 0xC0);

			fseek(fp, 0x1FFEC0, SEEK_SET);
			fprintf(fp, "%c", 0x20);
			fprintf(fp, "%c", 0x79);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x14);
			fprintf(fp, "%c", 0x40);
			fprintf(fp, "%c", 0x10);

			fprintf(fp, "%c", 0x13);
			fprintf(fp, "%c", 0xFC);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x06);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0xA1);
			fprintf(fp, "%c", 0x30);
			fprintf(fp, "%c", 0xFD);
			fprintf(fp, "%c", 0x13);
			fprintf(fp, "%c", 0xFC);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x07);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0xA1);
			fprintf(fp, "%c", 0x30);
			fprintf(fp, "%c", 0xFF);


			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0x75);






			fseek(fp, 0x126390, SEEK_SET);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0xB9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x1F);
			fprintf(fp, "%c", 0xFE);
			fprintf(fp, "%c", 0xE0);

			fseek(fp, 0x1FFEE0, SEEK_SET);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0xB9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x02);
			fprintf(fp, "%c", 0xEC);


			fprintf(fp, "%c", 0x13);
			fprintf(fp, "%c", 0xFC);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x06);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0xA1);
			fprintf(fp, "%c", 0x30);
			fprintf(fp, "%c", 0xFD);
			fprintf(fp, "%c", 0x13);
			fprintf(fp, "%c", 0xFC);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x07);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0xA1);
			fprintf(fp, "%c", 0x30);
			fprintf(fp, "%c", 0xFF);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0x75);






			fseek(fp, 0x1263A8, SEEK_SET);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0xB9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x1F);
			fprintf(fp, "%c", 0xFD);
			fprintf(fp, "%c", 0x80);


			fseek(fp, 0x1FFD80, SEEK_SET);
			fprintf(fp, "%c", 0x20);
			fprintf(fp, "%c", 0x79);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x0C);
			fprintf(fp, "%c", 0xC0);
			fprintf(fp, "%c", 0x00);

			fprintf(fp, "%c", 0x13);
			fprintf(fp, "%c", 0xFC);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x0A);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0xA1);
			fprintf(fp, "%c", 0x30);
			fprintf(fp, "%c", 0xFD);
			fprintf(fp, "%c", 0x13);
			fprintf(fp, "%c", 0xFC);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x0B);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0xA1);
			fprintf(fp, "%c", 0x30);
			fprintf(fp, "%c", 0xFF);

			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0x75);


			fseek(fp, 0x1262CE, SEEK_SET);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0xB9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x1F);
			fprintf(fp, "%c", 0xFD);
			fprintf(fp, "%c", 0xA0);


			fseek(fp, 0x1FFDA0, SEEK_SET);
			fprintf(fp, "%c", 0x20);
			fprintf(fp, "%c", 0x79);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x14);
			fprintf(fp, "%c", 0x40);
			fprintf(fp, "%c", 0x00);

			fprintf(fp, "%c", 0x13);
			fprintf(fp, "%c", 0xFC);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x08);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0xA1);
			fprintf(fp, "%c", 0x30);
			fprintf(fp, "%c", 0xFD);
			fprintf(fp, "%c", 0x13);
			fprintf(fp, "%c", 0xFC);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x09);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0xA1);
			fprintf(fp, "%c", 0x30);
			fprintf(fp, "%c", 0xFF);

			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0x75);


			fseek(fp, 0x126306, SEEK_SET);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0xF9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x1F);
			fprintf(fp, "%c", 0xFD);
			fprintf(fp, "%c", 0xC0);


			fseek(fp, 0x1FFDC0, SEEK_SET);
			fprintf(fp, "%c", 0x42);
			fprintf(fp, "%c", 0x59);
			fprintf(fp, "%c", 0x32);
			fprintf(fp, "%c", 0xD8);


			fprintf(fp, "%c", 0x13);
			fprintf(fp, "%c", 0xFC);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x06);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0xA1);
			fprintf(fp, "%c", 0x30);
			fprintf(fp, "%c", 0xFD);
			fprintf(fp, "%c", 0x13);
			fprintf(fp, "%c", 0xFC);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x07);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0xA1);
			fprintf(fp, "%c", 0x30);
			fprintf(fp, "%c", 0xFF);

			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0x75);




			fseek(fp, 0x9872, SEEK_SET);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0xB9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x1F);
			fprintf(fp, "%c", 0xFD);
			fprintf(fp, "%c", 0xE0);


			fseek(fp, 0x1FFDE0, SEEK_SET);
			fprintf(fp, "%c", 0x20);
			fprintf(fp, "%c", 0x79);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x03);
			fprintf(fp, "%c", 0x80);
			fprintf(fp, "%c", 0x00);

			fprintf(fp, "%c", 0x13);
			fprintf(fp, "%c", 0xFC);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x06);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0xA1);
			fprintf(fp, "%c", 0x30);
			fprintf(fp, "%c", 0xFD);
			fprintf(fp, "%c", 0x13);
			fprintf(fp, "%c", 0xFC);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x07);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0xA1);
			fprintf(fp, "%c", 0x30);
			fprintf(fp, "%c", 0xFF);

			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0x75);


			fseek(fp, 0x37F6, SEEK_SET);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0xB9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x1F);
			fprintf(fp, "%c", 0xFE);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0x71);

			fseek(fp, 0x1FFE00, SEEK_SET);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0xB9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x30);
			fprintf(fp, "%c", 0x54);
			fprintf(fp, "%c", 0x30);
			fprintf(fp, "%c", 0x38);
			fprintf(fp, "%c", 0xC0);
			fprintf(fp, "%c", 0xB8);

			fprintf(fp, "%c", 0x13);
			fprintf(fp, "%c", 0xFC);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x01);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0xA1);
			fprintf(fp, "%c", 0x30);
			fprintf(fp, "%c", 0xF1);

			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0x75);




			fseek(fp, 0x12633E, SEEK_SET);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0xB9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x1F);
			fprintf(fp, "%c", 0xFB);
			fprintf(fp, "%c", 0x80);


			fseek(fp, 0x1FFB80, SEEK_SET);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0xB9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x02);
			fprintf(fp, "%c", 0xEC);

			fprintf(fp, "%c", 0x13);
			fprintf(fp, "%c", 0xFC);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x06);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0xA1);
			fprintf(fp, "%c", 0x30);
			fprintf(fp, "%c", 0xFD);
			fprintf(fp, "%c", 0x13);
			fprintf(fp, "%c", 0xFC);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x07);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0xA1);
			fprintf(fp, "%c", 0x30);
			fprintf(fp, "%c", 0xFF);

			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0x75);



			fseek(fp, 0x126486, SEEK_SET);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0xF9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x1F);
			fprintf(fp, "%c", 0xFA);
			fprintf(fp, "%c", 0x00);

			fseek(fp, 0x1FFA00, SEEK_SET);
			fprintf(fp, "%c", 0x4A);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x6B);
			fprintf(fp, "%c", 0x16);


			fprintf(fp, "%c", 0x13);
			fprintf(fp, "%c", 0xFC);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x06);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0xA1);
			fprintf(fp, "%c", 0x30);
			fprintf(fp, "%c", 0xFD);

			fprintf(fp, "%c", 0x13);
			fprintf(fp, "%c", 0xFC);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x07);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0xA1);
			fprintf(fp, "%c", 0x30);
			fprintf(fp, "%c", 0xFF);

			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0xF9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x12);
			fprintf(fp, "%c", 0x64);
			fprintf(fp, "%c", 0x8C);

			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0x75);




			fseek(fp, 0xE156, SEEK_SET);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0xB9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x1F);
			fprintf(fp, "%c", 0xFE);
			fprintf(fp, "%c", 0x20);

			fseek(fp, 0x1FFE20, SEEK_SET);
			fprintf(fp, "%c", 0x20);
			fprintf(fp, "%c", 0x79);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x02);
			fprintf(fp, "%c", 0xC0);
			fprintf(fp, "%c", 0x04);


			fprintf(fp, "%c", 0x13);
			fprintf(fp, "%c", 0xFC);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x08);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0xA1);
			fprintf(fp, "%c", 0x30);
			fprintf(fp, "%c", 0xFD);
			fprintf(fp, "%c", 0x13);
			fprintf(fp, "%c", 0xFC);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x09);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0xA1);
			fprintf(fp, "%c", 0x30);
			fprintf(fp, "%c", 0xFF);

			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0x75);



			fseek(fp, 0xE1A8, SEEK_SET);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0xB9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x1F);
			fprintf(fp, "%c", 0xFF);
			fprintf(fp, "%c", 0x00);

			fseek(fp, 0x1FFF00, SEEK_SET);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0xB9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x02);
			fprintf(fp, "%c", 0x98);


			fprintf(fp, "%c", 0x13);
			fprintf(fp, "%c", 0xFC);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x06);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0xA1);
			fprintf(fp, "%c", 0x30);
			fprintf(fp, "%c", 0xFD);
			fprintf(fp, "%c", 0x13);
			fprintf(fp, "%c", 0xFC);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x07);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0xA1);
			fprintf(fp, "%c", 0x30);
			fprintf(fp, "%c", 0xFF);

			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0x75);



			fseek(fp, 0x1263E2, SEEK_SET);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0xF9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x1F);
			fprintf(fp, "%c", 0xFF);
			fprintf(fp, "%c", 0x20);


			fseek(fp, 0x1FFF20, SEEK_SET);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0xB9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x02);
			fprintf(fp, "%c", 0xEC);

			/*fprintf(fp, "%c", 0x13);
			fprintf(fp, "%c", 0xFC);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x06);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0xA1);
			fprintf(fp, "%c", 0x30);
			fprintf(fp, "%c", 0xFD);
			fprintf(fp, "%c", 0x13);
			fprintf(fp, "%c", 0xFC);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x07);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0xA1);
			fprintf(fp, "%c", 0x30);
			fprintf(fp, "%c", 0xFF);*/

			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0x75);

		} else {
			fseek(fp, 0x1263E2, SEEK_SET);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0xF9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x02);
			fprintf(fp, "%c", 0xEC);

			fseek(fp, 0xE156, SEEK_SET);
			fprintf(fp, "%c", 0x20);
			fprintf(fp, "%c", 0x79);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x02);
			fprintf(fp, "%c", 0xC0);
			fprintf(fp, "%c", 0x04);

			fseek(fp, 0x126486, SEEK_SET);
			fprintf(fp, "%c", 0x4A);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x6B);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x02);
			fprintf(fp, "%c", 0x34);

			fseek(fp, 0x12633E, SEEK_SET);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0xB9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x02);
			fprintf(fp, "%c", 0xEC);

			fseek(fp, 0x37F6, SEEK_SET);
			fprintf(fp, "%c", 0x61);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0xF8);
			fprintf(fp, "%c", 0x5C);
			fprintf(fp, "%c", 0x30);
			fprintf(fp, "%c", 0x38);
			fprintf(fp, "%c", 0xC0);
			fprintf(fp, "%c", 0xB8);


			fseek(fp, 0x9872, SEEK_SET);
			fprintf(fp, "%c", 0x20);
			fprintf(fp, "%c", 0x79);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x03);
			fprintf(fp, "%c", 0x80);
			fprintf(fp, "%c", 0x00);

			fseek(fp, 0x126306, SEEK_SET);
			fprintf(fp, "%c", 0x42);
			fprintf(fp, "%c", 0x59);
			fprintf(fp, "%c", 0x32);
			fprintf(fp, "%c", 0xD8);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0x75);

			fseek(fp, 0x1262CE, SEEK_SET);
			fprintf(fp, "%c", 0x20);
			fprintf(fp, "%c", 0x79);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x14);
			fprintf(fp, "%c", 0x40);
			fprintf(fp, "%c", 0x00);

			fseek(fp, 0x1262A8, SEEK_SET);
			fprintf(fp, "%c", 0x20);
			fprintf(fp, "%c", 0x79);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x10);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x00);

			fseek(fp, 0x126284, SEEK_SET);
			fprintf(fp, "%c", 0x20);
			fprintf(fp, "%c", 0x79);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x10);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x00);


			fseek(fp, 0x1262C6, SEEK_SET);
			fprintf(fp, "%c", 0x41);
			fprintf(fp, "%c", 0xF9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0xFF);
			fprintf(fp, "%c", 0x30);
			fprintf(fp, "%c", 0x00);

			fseek(fp, 0x1262A2, SEEK_SET);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0xF9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x02);
			fprintf(fp, "%c", 0xBC);

			fseek(fp, 0x126380, SEEK_SET);
			fprintf(fp, "%c", 0x20);
			fprintf(fp, "%c", 0x79);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x14);
			fprintf(fp, "%c", 0x40);
			fprintf(fp, "%c", 0x10);

			fseek(fp, 0x126390, SEEK_SET);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0xB9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x02);
			fprintf(fp, "%c", 0xEC);


			fseek(fp, 0x1263A8, SEEK_SET);
			fprintf(fp, "%c", 0x20);
			fprintf(fp, "%c", 0x79);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x0C);
			fprintf(fp, "%c", 0xC0);
			fprintf(fp, "%c", 0x00);
		}







		fseek(fp, 0x126326, SEEK_SET);
		fprintf(fp, "%c", 0x4E);
		fprintf(fp, "%c", 0xB9);
		fprintf(fp, "%c", 0x00);
		fprintf(fp, "%c", 0x1F);
		fprintf(fp, "%c", 0xFF);
		fprintf(fp, "%c", 0x50);
		fseek(fp, 0x12635E, SEEK_SET);
		fprintf(fp, "%c", 0x4E);
		fprintf(fp, "%c", 0xB9);
		fprintf(fp, "%c", 0x00);
		fprintf(fp, "%c", 0x1F);
		fprintf(fp, "%c", 0xFF);
		fprintf(fp, "%c", 0x70);


		PixelCompressor PC(fp);

		if (ExpandedGraphics)o2 = 0x400000;
		else o2 = 0x240000;

		//FSBankOffset = 0x23FE60;
		FSBankOffset = 0x1E4000;

		fseek(fp, 0x144000, SEEK_SET);
		fprintf(fp, "%c", (FSBankOffset & 0xFF000000) / 0x1000000);
		fprintf(fp, "%c", (FSBankOffset & 0x00FF0000) / 0x10000);
		fprintf(fp, "%c", (FSBankOffset & 0x0000FF00) / 0x100);
		fprintf(fp, "%c", (FSBankOffset & 0x000000FF));

		o = FSBankOffset;

		for (s = 0; s<NumGFX[0]; s++) {

			if (ExpandedGraphics)o2 -= 0x100000;

			fseek(fp, o, SEEK_SET);
			fprintf(fp, "%c", (o2 & 0xFF000000) / 0x1000000);
			fprintf(fp, "%c", (o2 & 0x00FF0000) / 0x10000);
			fprintf(fp, "%c", (o2 & 0x0000FF00) / 0x100);
			fprintf(fp, "%c", (o2 & 0x000000FF));
			o += 4;

			if (ExpandedGraphics)o2 += 0x100000;

			fseek(fp, o2, SEEK_SET);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x0A);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", NumFSFrame[s] * 2 + 2);

			d = NumFSFrame[s] * 2 + 4 + NumFSPalette[s] * 32;

			for (int i = 0; i<NumFSFrame[s]; i++) {
				fseek(fp, o2 + 4 + 2 * i, SEEK_SET);
				fprintf(fp, "%c", ((d - 2) & 0xFF00) / 0x100);
				fprintf(fp, "%c", ((d - 2) & 0x00FF));
				fseek(fp, o2 + d, SEEK_SET);
				len = PC.PutData(FSSize[s][i][0], FSSize[s][i][0] * FSSize[s][i][1], ForceSprites[s][i]);
				d += len;
				if (d % 2)d++;
			}


			fseek(fp, o2 + NumFSFrame[s] * 2 + 4, SEEK_SET);
			for (int p = 0; p<NumFSPalette[s]; p++) {
				writePalette(FSPalette[s][p], 16, fp);
			}
			o2 += d;
		}

		GFXSpace[0] = o2 - 0x400000;

		if (o2 % 4)o2 += 4 - (o2 % 4);


		if (ExpandedGraphics)o2 = 0x500000;

		//ESBankOffset = 0x23FD00;
		ESBankOffset = 0x1E5000;

		o = ESBankOffset;

		fseek(fp, 0x100000, SEEK_SET);
		fprintf(fp, "%c", (ESBankOffset & 0xFF000000) / 0x1000000);
		fprintf(fp, "%c", (ESBankOffset & 0x00FF0000) / 0x10000);
		fprintf(fp, "%c", (ESBankOffset & 0x0000FF00) / 0x100);
		fprintf(fp, "%c", (ESBankOffset & 0x000000FF));

		for (s = 0; s<NumGFX[1]; s++) {

			if (ExpandedGraphics)o2 -= 0x200000;

			fseek(fp, o, SEEK_SET);
			fprintf(fp, "%c", (o2 & 0xFF000000) / 0x1000000);
			fprintf(fp, "%c", (o2 & 0x00FF0000) / 0x10000);
			fprintf(fp, "%c", (o2 & 0x0000FF00) / 0x100);
			fprintf(fp, "%c", (o2 & 0x000000FF));
			o += 4;

			if (ExpandedGraphics)o2 += 0x200000;

			fseek(fp, o2, SEEK_SET);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x0A);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", NumESFrame[s] * 2 + 2);

			d = NumESFrame[s] * 2 + 4 + NumESPalette[s] * 32;

			for (int i = 0; i<NumESFrame[s]; i++) {
				fseek(fp, o2 + 4 + 2 * i, SEEK_SET);
				fprintf(fp, "%c", ((d - 2) & 0xFF00) / 0x100);
				fprintf(fp, "%c", ((d - 2) & 0x00FF));
				fseek(fp, o2 + d, SEEK_SET);
				len = PC.PutData(ESSize[s][i][0], ESSize[s][i][0] * ESSize[s][i][1], EnemySprites[s][i]);
				d += len;
				if (d % 2)d++;
			}


			fseek(fp, o2 + NumESFrame[s] * 2 + 4, SEEK_SET);
			for (int p = 0; p<NumESPalette[s]; p++) {
				writePalette(ESPalette[s][p], 16, fp);
			}
			o2 += d;
		}

		GFXSpace[1] = o2 - 0x500000;

		if (o2 % 4)o2 += 4 - (o2 % 4);

		if (ExpandedGraphics)o2 = 0x4C0000;
		POBankOffset = 0x1E8000;

		o = POBankOffset;

		fseek(fp, 0x2C004, SEEK_SET);
		fprintf(fp, "%c", (POBankOffset & 0xFF000000) / 0x1000000);
		fprintf(fp, "%c", (POBankOffset & 0x00FF0000) / 0x10000);
		fprintf(fp, "%c", (POBankOffset & 0x0000FF00) / 0x100);
		fprintf(fp, "%c", (POBankOffset & 0x000000FF));

		for (s = 0; s<NumGFX[6]; s++) {

			if (ExpandedGraphics)o2 -= 0x100000;

			fseek(fp, o, SEEK_SET);
			fprintf(fp, "%c", (o2 & 0xFF000000) / 0x1000000);
			fprintf(fp, "%c", (o2 & 0x00FF0000) / 0x10000);
			fprintf(fp, "%c", (o2 & 0x0000FF00) / 0x100);
			fprintf(fp, "%c", (o2 & 0x000000FF));
			o += 4;

			if (ExpandedGraphics)o2 += 0x100000;

			d = 0;

			fseek(fp, o2, SEEK_SET);

			int t = POData[s][d] * 256 + POData[s][d + 1];
			fprintf(fp, "%c", POData[s][d]);
			fprintf(fp, "%c", POData[s][d + 1]);
			d += 2;
			for (int q = 0; q<4 * t; q++) {
				fprintf(fp, "%c", POData[s][d]);
				d++;
			}
			t = POData[s][d] * 256 + POData[s][d + 1];
			fprintf(fp, "%c", POData[s][d]);
			fprintf(fp, "%c", POData[s][d + 1]);
			d += 2;
			for (int q = 0; q<4 * t; q++) {
				fprintf(fp, "%c", POData[s][d]);
				d++;
			}

			writePalette(POPalette[s], 16, fp);
			d += 32;

			fseek(fp, o2 + d, SEEK_SET);
			len = PC.PutData(POSize[s][0], POSize[s][0] * POSize[s][1], Portraits[s]);
			d += len;
			if (d % 2)d++;


			o2 += d;
		}

		GFXSpace[6] = o2 - 0x4C0000;

		if (o2 % 4)o2 += 4 - (o2 % 4);

		if (ExpandedGraphics)o2 = 0x5B0000;
		o = BGBankOffset;

		for (s = 0; s<NumGFX[3]; s++) {

			fseek(fp, o, SEEK_SET);

			if (ExpandedGraphics)o2 -= 0x200000;

			fprintf(fp, "%c", (o2 & 0xFF000000) / 0x1000000);
			fprintf(fp, "%c", (o2 & 0x00FF0000) / 0x10000);
			fprintf(fp, "%c", (o2 & 0x0000FF00) / 0x100);
			fprintf(fp, "%c", (o2 & 0x000000FF));

			if (ExpandedGraphics)o2 += 0x200000;

			o += 4;

			d = 0;

			if (s % 2 == 0) {
				fseek(fp, o2, SEEK_SET);
				for (int p = 0; p<NumBGPalette[s]; p++) {
					writePalette(BGPalette[s][p], 16, fp);
					d += 32;
				}
			}

			fseek(fp, o2 + d, SEEK_SET);
			len = PC.PutData(BGSize[s][0], BGSize[s][0] * BGSize[s][1], Backgrounds[s]);
			d += len;
			if (d % 2)d++;


			o2 += d;
		}

		GFXSpace[3] = o2 - 0x5B0000;

		if (o2 % 4)o2 += 4 - (o2 % 4);

		if (ExpandedGraphics)o2 = 0x300000;
		WSBankOffset = 0x1E7000;

		fseek(fp, 0x23EBCF, SEEK_SET);
		fprintf(fp, "%c", NumGFX[2]);

		fseek(fp, 0x144008, SEEK_SET);
		fprintf(fp, "%c", (WSBankOffset & 0xFF000000) / 0x1000000);
		fprintf(fp, "%c", (WSBankOffset & 0x00FF0000) / 0x10000);
		fprintf(fp, "%c", (WSBankOffset & 0x0000FF00) / 0x100);
		fprintf(fp, "%c", (WSBankOffset & 0x000000FF));

		o = WSBankOffset;

		for (s = 0; s<NumGFX[2]; s++) {
			for (int i = 0; i<WSRepeat[s]; i++) {
				fseek(fp, o, SEEK_SET);
				fprintf(fp, "%c", (o2 & 0xFF000000) / 0x1000000);
				fprintf(fp, "%c", (o2 & 0x00FF0000) / 0x10000);
				fprintf(fp, "%c", (o2 & 0x0000FF00) / 0x100);
				fprintf(fp, "%c", (o2 & 0x000000FF));
				o += 4;
			}

			fseek(fp, o2, SEEK_SET);
			len = PC.PutData(WSSize[s][0][0], WSSize[s][0][0] * WSSize[s][0][1], WeaponSprites[s][0]);
			d += len;
			if (d % 2)d++;

			o2 += d;
		}


		if (o2 % 4)o2 += 4 - (o2 % 4);


		

		

		MSBankOffset = 0x1E9000;

		fseek(fp, 0x38000, SEEK_SET);
		fprintf(fp, "%c", (MSBankOffset & 0xFF000000) / 0x1000000);
		fprintf(fp, "%c", (MSBankOffset & 0x00FF0000) / 0x10000);
		fprintf(fp, "%c", (MSBankOffset & 0x0000FF00) / 0x100);
		fprintf(fp, "%c", (MSBankOffset & 0x000000FF));
		fprintf(fp, "%c", ((MSBankOffset + 4 * NumGFX[7]) & 0xFF000000) / 0x1000000);
		fprintf(fp, "%c", ((MSBankOffset + 4 * NumGFX[7]) & 0x00FF0000) / 0x10000);
		fprintf(fp, "%c", ((MSBankOffset + 4 * NumGFX[7]) & 0x0000FF00) / 0x100);
		fprintf(fp, "%c", ((MSBankOffset + 4 * NumGFX[7]) & 0x000000FF));
		fprintf(fp, "%c", ((MSBankOffset + 8 * NumGFX[7]) & 0xFF000000) / 0x1000000);
		fprintf(fp, "%c", ((MSBankOffset + 8 * NumGFX[7]) & 0x00FF0000) / 0x10000);
		fprintf(fp, "%c", ((MSBankOffset + 8 * NumGFX[7]) & 0x0000FF00) / 0x100);
		fprintf(fp, "%c", ((MSBankOffset + 8 * NumGFX[7]) & 0x000000FF));


		o = MSBankOffset;

		for (int i = 0; i<NumMSFrame; i++) {
			for (s = 0; s<NumGFX[7]; s++) {

				fseek(fp, o, SEEK_SET);
				fprintf(fp, "%c", (o2 & 0xFF000000) / 0x1000000);
				fprintf(fp, "%c", (o2 & 0x00FF0000) / 0x10000);
				fprintf(fp, "%c", (o2 & 0x0000FF00) / 0x100);
				fprintf(fp, "%c", (o2 & 0x000000FF));
				o += 4;

				d = 0;


				fseek(fp, o2, SEEK_SET);
				len = PC.PutData(MSSize[s][i][0], MSSize[s][i][0] * MSSize[s][i][1], MapSprites[s][i], false);
				d += len;
				if (d % 2)d++;

				o2 += d;
			}
		}

		if (ChooseMSPal) {
			char b = 0;
			fseek(fp, 0x23EF60, SEEK_SET);
			for (s = 0; s < NumGFX[7]; s++) {
				if (s && !(s % 8)) {
					fprintf(fp, "%c", b);
					b = 0;
				}
				b = b << 1;
				if (MSPalette[s])b++;

			}
			if (7 - (s - 1) % 8)b = b << (7 - (s - 1) % 8);
			fprintf(fp, "%c", b);
		}

		if (NumGFX[7] > 160) {
			MSSoundOffset = 0x1A9D80;
		}

		fseek(fp, 0x1001C, SEEK_SET);
		fprintf(fp, "%c", (MSSoundOffset & 0xFF000000) / 0x1000000);
		fprintf(fp, "%c", (MSSoundOffset & 0x00FF0000) / 0x10000);
		fprintf(fp, "%c", (MSSoundOffset & 0x0000FF00) / 0x100);
		fprintf(fp, "%c", (MSSoundOffset & 0x000000FF));

		fseek(fp, MSSoundOffset, SEEK_SET);
		for (s = 0; s < NumGFX[7]; s++) {
			fprintf(fp, "%c", MSTextSound[s]);
		}

		if (MSSoundOffset == 0x1A9D80) {
			fseek(fp, 0x17F6C, SEEK_SET);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0xB9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x1A);
			fprintf(fp, "%c", 0x9D);
			fprintf(fp, "%c", 0x70);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0x71);

			fseek(fp, 0x1A9D70, SEEK_SET);
			fprintf(fp, "%c", 0x41);
			fprintf(fp, "%c", 0xF9);
			fprintf(fp, "%c", 0x00);
			fprintf(fp, "%c", 0x1A);
			fprintf(fp, "%c", 0x9D);
			fprintf(fp, "%c", 0x80);

			fprintf(fp, "%c", 0x12);
			fprintf(fp, "%c", 0x30);
			fprintf(fp, "%c", 0x10);
			fprintf(fp, "%c", 0x00);

			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0x75);
		} else {
			fseek(fp, 0x17F6C, SEEK_SET);
			fprintf(fp, "%c", 0x41);
			fprintf(fp, "%c", 0xFA);
			fprintf(fp, "%c", 0xFC);
			fprintf(fp, "%c", 0x4E);
			fprintf(fp, "%c", 0x12);
			fprintf(fp, "%c", 0x30);
			fprintf(fp, "%c", 0x10);
			fprintf(fp, "%c", 0x00);
		}

		if (o2 % 4)o2 += 4 - (o2 % 4);
		o = TSBankOffset;

		for (s = 0; s<NumGFX[8]; s++) {
			if (s == 6)o += 24;
			fseek(fp, o, SEEK_SET);
			fprintf(fp, "%c", (o2 & 0xFF000000) / 0x1000000);
			fprintf(fp, "%c", (o2 & 0x00FF0000) / 0x10000);
			fprintf(fp, "%c", (o2 & 0x0000FF00) / 0x100);
			fprintf(fp, "%c", (o2 & 0x000000FF));
			o += 4;

			d = 0;

			fseek(fp, o2, SEEK_SET);

			fseek(fp, o2, SEEK_SET);
			len = PC.PutData(TSSize[s][0], TSSize[s][0] * TSSize[s][1], Tilesets[s]);
			d += len;
			if (d % 2)d++;


			o2 += d;
		}

		if (o2 % 4)o2 += 4 - (o2 % 4);
		o = EFBankOffset;

		for (s = 0; s<NumGFX[9]; s++) {

			fseek(fp, o, SEEK_SET);
			fprintf(fp, "%c", (o2 & 0xFF000000) / 0x1000000);
			fprintf(fp, "%c", (o2 & 0x00FF0000) / 0x10000);
			fprintf(fp, "%c", (o2 & 0x0000FF00) / 0x100);
			fprintf(fp, "%c", (o2 & 0x000000FF));
			o += 4;

			d = 0;

			fseek(fp, o2, SEEK_SET);
			len = PC.PutData(EFSize[s][0], EFSize[s][0] * EFSize[s][1], Effects[s]);
			d += len;
			if (d % 2)d++;


			o2 += d;
		}

		if (o2 % 4)o2 += 4 - (o2 % 4);
		o = PFBankOffset;

		for (s = 0; s<NumGFX[4]; s++) {


			fseek(fp, o, SEEK_SET);
			fprintf(fp, "%c", (o2 & 0xFF000000) / 0x1000000);
			fprintf(fp, "%c", (o2 & 0x00FF0000) / 0x10000);
			fprintf(fp, "%c", (o2 & 0x0000FF00) / 0x100);
			fprintf(fp, "%c", (o2 & 0x000000FF));
			o += 4;


			d = 0;

			fseek(fp, o2, SEEK_SET);

			writePalette(PFPalette[s] + 2, 4, fp);
			d += 8;

			fseek(fp, o2 + d, SEEK_SET);
			len = PC.PutData(PFSize[s][0], PFSize[s][0] * PFSize[s][1], Platforms[s], true, 0, 0xE);
			d += len;
			if (d % 2)d++;


			o2 += d;
		}

		if (ExpandedGraphics)GFXSpace[31] = o2 - 0x300000;
		else GFXSpace[31] = o2 - 0x240000;

		o2 = 0x580B8;
	
		for (s = 0; s<NumGFX[5]; s++) {

			o = CSPalOffset[s];
			if (o) {
				fseek(fp, o, SEEK_SET);
				writePalette(CSPalette[s], 16, fp);
			}

			o = CSGFXPointer[s];
			fseek(fp, o, SEEK_SET);
			fprintf(fp, "%c", (o2 & 0xFF000000) / 0x1000000);
			fprintf(fp, "%c", (o2 & 0x00FF0000) / 0x10000);
			fprintf(fp, "%c", (o2 & 0x0000FF00) / 0x100);
			fprintf(fp, "%c", (o2 & 0x000000FF));
			o += 4;

			o = ftell(fp);

			d = 0;

			fseek(fp, o2, SEEK_SET);

			len = PC.PutData(CSSize[s][0], CSSize[s][0] * CSSize[s][1], CutsceneGFX[s]);
			d += len;
			if (d % 2)d++;


			o2 += d;
		}


		InvalidateRect(hwnd, NULL, false);

		fclose(fp);

		if (GFXPaletteEdit) {
			SavePalette();
		}
		MessageBox(NULL, "Graphics Saved", "Note", MB_OK);
	}
}

void BMPHeader(FILE * fp, int w, int h) {
	long row = w * 3;
	row += (4 - row % 4) % 4;
	long size = row*h;
	fprintf(fp, "BM");
	long totalsize = size + 54;
	fprintf(fp, "%c", totalsize % 256);
	totalsize -= totalsize % 256;
	totalsize /= 256;
	fprintf(fp, "%c", totalsize % 256);
	totalsize -= totalsize % 256;
	totalsize /= 256;
	fprintf(fp, "%c", totalsize % 256);
	totalsize -= totalsize % 256;
	totalsize /= 256;
	fprintf(fp, "%c", totalsize % 256);
	fprintf(fp, "%c", 0);
	fprintf(fp, "%c", 0);
	fprintf(fp, "%c", 0);
	fprintf(fp, "%c", 0);
	fprintf(fp, "%c", 54);
	fprintf(fp, "%c", 0);
	fprintf(fp, "%c", 0);
	fprintf(fp, "%c", 0);
	fprintf(fp, "%c", 40);
	fprintf(fp, "%c", 0);
	fprintf(fp, "%c", 0);
	fprintf(fp, "%c", 0);
	fprintf(fp, "%c", w % 256);
	w -= w % 256;
	w /= 256;
	fprintf(fp, "%c", w % 256);
	w -= w % 256;
	w /= 256;
	fprintf(fp, "%c", w % 256);
	w -= w % 256;
	w /= 256;
	fprintf(fp, "%c", w % 256);
	fprintf(fp, "%c", h % 256);
	h -= h % 256;
	h /= 256;
	fprintf(fp, "%c", h % 256);
	h -= h % 256;
	h /= 256;
	fprintf(fp, "%c", h % 256);
	h -= h % 256;
	h /= 256;
	fprintf(fp, "%c", h % 256);
	fprintf(fp, "%c", 1);
	fprintf(fp, "%c", 0);
	fprintf(fp, "%c", 24);
	fprintf(fp, "%c", 0);
	fprintf(fp, "%c", 0);
	fprintf(fp, "%c", 0);
	fprintf(fp, "%c", 0);
	fprintf(fp, "%c", 0);
	fprintf(fp, "%c", size % 256);
	size -= size % 256;
	size /= 256;
	fprintf(fp, "%c", size % 256);
	size -= size % 256;
	size /= 256;
	fprintf(fp, "%c", size % 256);
	size -= size % 256;
	size /= 256;
	fprintf(fp, "%c", size % 256);
	fprintf(fp, "%c", 19);
	fprintf(fp, "%c", 11);
	fprintf(fp, "%c", 0);
	fprintf(fp, "%c", 0);
	fprintf(fp, "%c", 19);
	fprintf(fp, "%c", 11);
	fprintf(fp, "%c", 0);
	fprintf(fp, "%c", 0);
	fprintf(fp, "%c", 0);
	fprintf(fp, "%c", 0);
	fprintf(fp, "%c", 0);
	fprintf(fp, "%c", 0);
	fprintf(fp, "%c", 0);
	fprintf(fp, "%c", 0);
	fprintf(fp, "%c", 0);
	fprintf(fp, "%c", 0);
}

void ExportGFX() {
	FILE * fp;

	int color;
	int l;
	int s;

	char tempc[32];

	char path[256];
	path[0] = '\0';

	ITEMIDLIST*            pItem;
	BROWSEINFO            bi;
	LPSTR                  szBuffer;

	LPMALLOC ppMalloc;
	SHGetMalloc(&ppMalloc);

	szBuffer = (LPSTR)ppMalloc->Alloc(MAX_PATH);

	PIDLIST_ABSOLUTE pIdL = NULL;
	SFGAOF out;

	wchar_t wdir[512];
	memset(wdir, 0, 512 * sizeof(wchar_t));
	MultiByteToWideChar(CP_ACP, 0, EditorDirectory, -1, wdir, strlen(EditorDirectory));

	SHParseDisplayName(wdir, NULL, &pIdL, SFGAO_FILESYSTEM, &out);

	bi.hwndOwner = NULL;
	bi.pidlRoot = pIdL;
	bi.pszDisplayName = szBuffer;
	bi.lpszTitle = "Select folder";
	bi.lpfn = NULL;
	bi.lParam = (LPARAM)EditorDirectory;
	bi.ulFlags = BIF_USENEWUI | BIF_NEWDIALOGSTYLE;

	pItem = SHBrowseForFolder(&bi);

	if (pItem) {
		SHGetPathFromIDList(pItem, szBuffer);
		sprintf(path, szBuffer);
		ppMalloc->Free(pItem);
		ppMalloc->Free(szBuffer);
	} else {
		ppMalloc->Free(pItem);
		ppMalloc->Free(szBuffer);
		return;
	}


	String file, dir;

	POINT p;

	SetCursor(LoadCursor(0, IDC_WAIT));

	file = path;
	file += "\\Battle";
	mkdir(file);

	file = path;
	file += "\\Battle\\Force";
	mkdir(file);

	file = path;
	file += "\\Battle\\Enemies";
	mkdir(file);

	file = path;
	file += "\\Battle\\Backgrounds";
	mkdir(file);

	file = path;
	file += "\\Battle\\Platforms";
	mkdir(file);

	file = path;
	file += "\\Battle\\Weapons";
	mkdir(file);

	file = path;
	file += "\\Portraits";
	mkdir(file);

	file = path;
	file += "\\Map";
	mkdir(file);

	file = path;
	file += "\\Map\\Sprites";
	mkdir(file);

	file = path;
	file += "\\Map\\Tilesets";
	mkdir(file);

	file = path;
	file += "\\Animations";
	mkdir(file);

	file = path;
	file += "\\Icons";
	mkdir(file);

	file = path;
	file += "\\Icons\\Items";
	mkdir(file);

	file = path;
	file += "\\Icons\\Spells";
	mkdir(file);

	file = path;
	file += "\\Screens";
	mkdir(file);

	for (s = 0; s < NumItems; s++) {

		file = path;
		file += "\\Icons\\Items\\";
		file += itoa(s, tempc, 10);
		file += ".bmp";
		fp = fopen(file, "wb");
		BMPHeader(fp, 16, 24);

		for (int j = 23; j >= 0; j--) {
			for (int i = 0; i < 16; i++) {
				color = ItemImages[s][j * 16 + i];
				if (color) {
					fprintf(fp, "%c", IconPalette[color][2]);
					fprintf(fp, "%c", IconPalette[color][1]);
					fprintf(fp, "%c", IconPalette[color][0]);
				} else {
					fprintf(fp, "%c", 99);
					fprintf(fp, "%c", 1);
					fprintf(fp, "%c", 100);
				}
			}
		}
		fclose(fp);
	}

	for (s = 0; s < 16 + 16 * ExpandSpells; s++) {

		file = path;
		file += "\\Icons\\Spells\\";
		file += itoa(s, tempc, 10);
		file += ".bmp";
		fp = fopen(file, "wb");
		BMPHeader(fp, 16, 24);

		for (int j = 23; j >= 0; j--) {
			for (int i = 0; i < 16; i++) {
				color = SpellImages[s][j * 16 + i];
				if (color) {
					fprintf(fp, "%c", IconPalette[color][2]);
					fprintf(fp, "%c", IconPalette[color][1]);
					fprintf(fp, "%c", IconPalette[color][0]);
				} else {
					fprintf(fp, "%c", 99);
					fprintf(fp, "%c", 1);
					fprintf(fp, "%c", 100);
				}
			}
		}
		fclose(fp);
	}

	for (s = 0; s<NumGFX[0]; s++) {
		for (int i = 0; i<NumFSFrame[s]; i++) {
			file = path;
			file += "\\Battle\\Force\\";
			file += itoa(s, tempc, 10);
			file += "_";
			file += itoa(i, tempc, 10);
			file += ".bmp";
			fp = fopen(file, "wb");
			BMPHeader(fp, FSSize[s][i][0], FSSize[s][i][1]);

			int x;

			for (int y = FSSize[s][i][1] - 1; y >= 0; y--) {
				for (x = 0; x<FSSize[s][i][0]; x++) {
					color = ForceSprites[s][i][x + y*FSSize[s][i][0]];
					if (color) {
						fprintf(fp, "%c", FSPalette[s][0][color][2]);
						fprintf(fp, "%c", FSPalette[s][0][color][1]);
						fprintf(fp, "%c", FSPalette[s][0][color][0]);
					} else {
						fprintf(fp, "%c", 99);
						fprintf(fp, "%c", 1);
						fprintf(fp, "%c", 100);
					}
				}
				for (x = 0; x<(4 - (FSSize[s][i][0] * 3) % 4) % 4; x++) {
					fprintf(fp, "%c", 0);
				}
			}
			fclose(fp);
		}
	}

	for (s = 0; s<NumGFX[1]; s++) {
		for (int i = 0; i<NumESFrame[s]; i++) {
			file = path;
			file += "\\Battle\\Enemies\\";
			file += itoa(s, tempc, 10);
			file += "_";
			file += itoa(i, tempc, 10);
			file += ".bmp";
			fp = fopen(file, "wb");
			BMPHeader(fp, ESSize[s][i][0], ESSize[s][i][1]);

			int x;

			for (int y = ESSize[s][i][1] - 1; y >= 0; y--) {
				for (x = 0; x<ESSize[s][i][0]; x++) {
					color = EnemySprites[s][i][x + y*ESSize[s][i][0]];
					if (color) {
						fprintf(fp, "%c", ESPalette[s][0][color][2]);
						fprintf(fp, "%c", ESPalette[s][0][color][1]);
						fprintf(fp, "%c", ESPalette[s][0][color][0]);
					} else {
						fprintf(fp, "%c", 99);
						fprintf(fp, "%c", 1);
						fprintf(fp, "%c", 100);
					}
				}
				for (x = 0; x<(4 - (ESSize[s][i][0] * 3) % 4) % 4; x++) {
					fprintf(fp, "%c", 0);
				}
			}
			fclose(fp);
		}
	}

	for (s = 0; s<NumGFX[2]; s++) {
		for (int i = 0; i<1; i++) {
			file = path;
			file += "\\Battle\\Weapons\\";
			file += itoa(s, tempc, 10);
			file += ".bmp";
			fp = fopen(file, "wb");
			BMPHeader(fp, WSSize[s][i][0], WSSize[s][i][1]);
			l = findWSPalette(s);

			int x;

			for (int y = WSSize[s][i][1] - 1; y >= 0; y--) {
				for (x = 0; x<WSSize[s][i][0]; x++) {
					color = WeaponSprites[s][i][x + y*WSSize[s][i][0]];

					switch (color) {
						case 15:
							color = 3;
							break;
						case 14:
							fprintf(fp, "%c", 0);
							fprintf(fp, "%c", 0);
							fprintf(fp, "%c", 0);
							color = -1;
							break;
						case 13:
							color = 2;
							break;
						case 12:
							color = 1;
							break;
						case 11:
							color = 0;
							fprintf(fp, "%c", ISPalette[l][color][2]);
							fprintf(fp, "%c", ISPalette[l][color][1]);
							fprintf(fp, "%c", ISPalette[l][color][0]);
							color = -1;
							break;
						case 1:
							fprintf(fp, "%c", 255);
							fprintf(fp, "%c", 255);
							fprintf(fp, "%c", 255);
							color = -1;
							break;
					}

					if (color) {
						if (color>0) {
							fprintf(fp, "%c", ISPalette[l][color][2]);
							fprintf(fp, "%c", ISPalette[l][color][1]);
							fprintf(fp, "%c", ISPalette[l][color][0]);
						}
					} else {
						fprintf(fp, "%c", 99);
						fprintf(fp, "%c", 1);
						fprintf(fp, "%c", 100);
					}
				}
				for (x = 0; x<(4 - (WSSize[s][i][0] * 3) % 4) % 4; x++) {
					fprintf(fp, "%c", 0);
				}
			}
			fclose(fp);
		}
	}

	for (s = 0; s<NumGFX[3]; s++) {
		file = path;
		file += "\\Battle\\Backgrounds\\";
		file += itoa(s, tempc, 10);
		file += ".bmp";
		fp = fopen(file, "wb");
		BMPHeader(fp, BGSize[s][0], BGSize[s][1]);

		int x;
		for (int y = BGSize[s][1] - 1; y >= 0; y--) {
			for (x = 0; x<BGSize[s][0]; x++) {
				color = Backgrounds[s][x + y*BGSize[s][0]];
				if (color) {
					fprintf(fp, "%c", BGPalette[s - s % 2][0][color][2]);
					fprintf(fp, "%c", BGPalette[s - s % 2][0][color][1]);
					fprintf(fp, "%c", BGPalette[s - s % 2][0][color][0]);
				} else {
					fprintf(fp, "%c", 99);
					fprintf(fp, "%c", 1);
					fprintf(fp, "%c", 100);
				}
			}
			for (x = 0; x<(4 - (BGSize[s][0] * 3) % 4) % 4; x++) {
				fprintf(fp, "%c", 0);
			}
		}
		fclose(fp);
	}

	for (s = 0; s<NumGFX[4]; s++) {
		file = path;
		file += "\\Battle\\Platforms\\";
		file += itoa(s, tempc, 10);
		file += ".bmp";
		fp = fopen(file, "wb");
		BMPHeader(fp, PFSize[s][0], PFSize[s][1]);

		int x;
		for (int y = PFSize[s][1] - 1; y >= 0; y--) {
			for (x = 0; x<PFSize[s][0]; x++) {
				color = Platforms[s][x + y*PFSize[s][0]];
				if (color) {
					fprintf(fp, "%c", PFPalette[s][color][2]);
					fprintf(fp, "%c", PFPalette[s][color][1]);
					fprintf(fp, "%c", PFPalette[s][color][0]);
				} else {
					fprintf(fp, "%c", 99);
					fprintf(fp, "%c", 1);
					fprintf(fp, "%c", 100);
				}
			}
			for (x = 0; x<(4 - (PFSize[s][0] * 3) % 4) % 4; x++) {
				fprintf(fp, "%c", 0);
			}
		}
		fclose(fp);
	}

	for (s = 0; s<NumGFX[6]; s++) {
		file = path;
		file += "\\Portraits\\";
		file += itoa(s, tempc, 10);
		file += ".bmp";
		fp = fopen(file, "wb");
		BMPHeader(fp, POSize[s][0], POSize[s][1]);

		int x;
		for (int y = POSize[s][1] - 1; y >= 0; y--) {
			for (x = 0; x<POSize[s][0]; x++) {
				color = Portraits[s][x + y*POSize[s][0]];
				if (color) {
					fprintf(fp, "%c", POPalette[s][color][2]);
					fprintf(fp, "%c", POPalette[s][color][1]);
					fprintf(fp, "%c", POPalette[s][color][0]);
				} else {
					fprintf(fp, "%c", 99);
					fprintf(fp, "%c", 1);
					fprintf(fp, "%c", 100);
				}
			}
			for (x = 0; x<(4 - (POSize[s][0] * 3) % 4) % 4; x++) {
				fprintf(fp, "%c", 0);
			}
		}
		fclose(fp);
	}

	for (s = 0; s<NumGFX[7]; s++) {
		for (int i = 0; i<NumMSFrame; i++) {
			file = path;
			file += "\\Map\\Sprites\\";
			file += itoa(s, tempc, 10);
			file += "_";
			file += itoa(i, tempc, 10);
			file += ".bmp";
			fp = fopen(file, "wb");
			BMPHeader(fp, MSSize[s][i][0], MSSize[s][i][1]);

			int x;
			for (int y = MSSize[s][i][1] - 1; y >= 0; y--) {
				for (x = 0; x<MSSize[s][i][0]; x++) {
					color = MapSprites[s][i][x + y*MSSize[s][i][0]];
					if (color) {
						//if (ChooseMSPal && MSPalette[s]) {
						if (MSPalette[s]) {
							fprintf(fp, "%c", EMSPalette[color][2]);
							fprintf(fp, "%c", EMSPalette[color][1]);
							fprintf(fp, "%c", EMSPalette[color][0]);
						} else {
							fprintf(fp, "%c", FMSPalette[color][2]);
							fprintf(fp, "%c", FMSPalette[color][1]);
							fprintf(fp, "%c", FMSPalette[color][0]);
						}
					} else {
						fprintf(fp, "%c", 99);
						fprintf(fp, "%c", 1);
						fprintf(fp, "%c", 100);
					}
				}
				for (x = 0; x<(4 - (MSSize[s][i][0] * 3) % 4) % 4; x++) {
					fprintf(fp, "%c", 0);
				}
			}
			fclose(fp);
		}
	}

	for (s = 0; s<NumGFX[8]; s++) {
		file = path;
		file += "\\Map\\Tilesets\\";
		file += itoa(s, tempc, 10);
		file += ".bmp";
		fp = fopen(file, "wb");
		BMPHeader(fp, TSSize[s][0], TSSize[s][1]);

		int x;

		for (int y = TSSize[s][1] - 1; y >= 0; y--) {
			for (x = 0; x<TSSize[s][0]; x++) {
				p.x = x * 4;
				p.y = y * 4;
				TilesetToPixel(p);
				color = Tilesets[s][p.x / 4 + p.y / 4 * TSSize[s][0]];
				if (color) {
					fprintf(fp, "%c", TSPalette[TSPalNums[s]][color][2]);
					fprintf(fp, "%c", TSPalette[TSPalNums[s]][color][1]);
					fprintf(fp, "%c", TSPalette[TSPalNums[s]][color][0]);
				} else {
					fprintf(fp, "%c", 99);
					fprintf(fp, "%c", 1);
					fprintf(fp, "%c", 100);
				}
			}
			for (x = 0; x<(4 - (TSSize[s][0] * 3) % 4) % 4; x++) {
				fprintf(fp, "%c", 0);
			}
		}
		fclose(fp);
	}

	for (s = 0; s<NumGFX[9]; s++) {
		file = path;
		file += "\\Animations\\";
		file += itoa(s, tempc, 10);
		file += ".bmp";
		fp = fopen(file, "wb");
		BMPHeader(fp, EFSize[s][0], EFSize[s][1]);
		int x;
		for (int y = EFSize[s][1] - 1; y >= 0; y--) {
			for (x = 0; x<EFSize[s][0]; x++) {
				color = Effects[s][x + y*EFSize[s][0]];
				if (color) {
					fprintf(fp, "%c", EFPalette[s][color][2]);
					fprintf(fp, "%c", EFPalette[s][color][1]);
					fprintf(fp, "%c", EFPalette[s][color][0]);
				} else {
					fprintf(fp, "%c", 99);
					fprintf(fp, "%c", 1);
					fprintf(fp, "%c", 100);
				}
			}
			for (x = 0; x<(4 - (EFSize[s][0] * 3) % 4) % 4; x++) {
				fprintf(fp, "%c", 0);
			}
		}
		fclose(fp);
	}


	int i, k, vx, vy, x, y;

	for (s = 0; s<NumGFX[5]; s++) {
		file = path;
		file += "\\Screens\\";
		file += itoa(s, tempc, 10);
		file += ".bmp";
		fp = fopen(file, "wb");


		




		int width = CSSize[s][0];
		int height = CSSize[s][1];


		if (s == 0) {
			BMPHeader(fp, 256, 96);
			int qx = -1;
			int qy = 0;

			for (i = 0; i < 256 * 256; i++)TempGfx[i] = 255;

			for (vy = 0; vy < height / 8; vy++) {
				for (x = 0; x < width; x++) {
					for (y = 0; y < 8; y++) {

						vx = (x - x % 8) / 8;

						if (SplashLayout[vx + 16 * vy] == -255)continue;

						if (!(x % 8) && !(y % 8))
							if (SplashLayout[vx + 16 * vy] < 0) {
								for (l = 1; l < -1 * SplashLayout[vx + 16 * vy]; l++) {
									qx--;
									if (qx == 15) {
										qx = 31;
										qy--;
									}
								}
							} else
								for (l = 0; l <= SplashLayout[vx + 16 * vy]; l++) {
									qx++;
									if (qx == 16) {
										qx = 0;
										qy++;
										if (qy == 12) {
											qy = 0;
											qx = 16;
										}
									}
									if (qx == 32) {
										qx = 16;
										qy++;
									}
								}


							POINT p;
							p.x = x * 4;
							p.y = (8 * vy + y) * 4;
							TilesetToPixel(p);
							k = CutsceneGFX[s][p.x / 4 + p.y / 4 * width];
							if (k < 0)k = 0;


							TempGfx[qx * 8 + x % 8 + (qy * 8 + y % 8) * 256] = k;
					}

				}
			}



			int x;
			for (int y = 95; y >= 0; y--) {
				for (x = 0; x < 256; x++) {
					color = TempGfx[x + y * 256];
					if (color == 255) {
						if ((x + y) % 2) {
							fprintf(fp, "%c", 0);
							fprintf(fp, "%c", 1);
							fprintf(fp, "%c", 2);
						} else {
							fprintf(fp, "%c", 255);
							fprintf(fp, "%c", 254);
							fprintf(fp, "%c", 253);
						}
					} else {
						if (color) {
							fprintf(fp, "%c", CSPalette[0][color][2]);
							fprintf(fp, "%c", CSPalette[0][color][1]);
							fprintf(fp, "%c", CSPalette[0][color][0]);
						} else {
							fprintf(fp, "%c", 99);
							fprintf(fp, "%c", 1);
							fprintf(fp, "%c", 100);
						}
					}
				}
				for (x = 0; x < (4 - (256 * 3) % 4) % 4; x++) {
					fprintf(fp, "%c", 0);
				}
			}
		} else {
			BMPHeader(fp, CSSize[s][0], CSSize[s][1]);
			int x;
			int pl = s;
			while (pl>0 && CSPalOffset[pl] == 0)pl--;

			for (int y = CSSize[s][1] - 1; y >= 0; y--) {
				for (x = 0; x<CSSize[s][0]; x++) {
					color = CutsceneGFX[s][x + y*CSSize[s][0]];
					if (color) {
						fprintf(fp, "%c",CSPalette[pl][color][2]);
						fprintf(fp, "%c",CSPalette[pl][color][1]);
						fprintf(fp, "%c",CSPalette[pl][color][0]);
					} else {
						fprintf(fp, "%c", 99);
						fprintf(fp, "%c", 1);
						fprintf(fp, "%c", 100);
					}
				}
				for (x = 0; x<(4 - (CSSize[s][0] * 3) % 4) % 4; x++) {
					fprintf(fp, "%c", 0);
				}
			}
		}
		fclose(fp);
	}

	SetCursor(LoadCursor(0, IDC_ARROW));

	MessageBox(NULL, "Graphics Exported.", "Note", MB_OK);
}

void GFXExport() {
	ExportGFX();
}

void ToClipboard(unsigned char * data, unsigned int size[2], unsigned char pal[16][3], bool tileset, bool weapon) {
	clip = CreateCompatibleBitmap(hdc, size[0], size[1]);
	HBITMAP old = (HBITMAP)SelectObject(clipdc, clip);

	int x, y;

	POINT p;

	for (x = 0; x<size[0]; x++) {
		for (y = 0; y < size[1]; y++) {
			color = data[x + y*size[0]];

			if (weapon) {
				switch (color) {
					case 15:
						color = 3;
						break;
					case 14:
						color = -1;
						break;
					case 13:
						color = 2;
						break;
					case 12:
						color = 1;
						break;
					case 11:
						color = -3;
						break;
					case 1:
						color = -2;
						break;
				}
			}

			if (tileset) {
				p.x = x * 4;
				p.y = y * 4;
				PixelToTileset(p);
				p.x /= 4;
				p.y /= 4;
			} else {
				p.x = x;
				p.y = y;
			}

			if (color) {
				switch (color) {
					case -1:
						SetPixel(clipdc, p.x, p.y, RGB(0, 0, 0));
						break;
					case -2:
						SetPixel(clipdc, p.x, p.y, RGB(255, 255, 255));
						break;
					case -3:
						SetPixel(clipdc, p.x, p.y, RGB(pal[0][0], pal[0][1], pal[0][2]));
						break;
					default:
						SetPixel(clipdc, p.x, p.y, RGB(pal[color][0], pal[color][1], pal[color][2]));
						break;
				}

			} else {
				SetPixel(clipdc, p.x, p.y, RGB(100, 1, 99));
			}
		}
	}

	if (!OpenClipboard(hwnd))
		return;
	//EmptyClipboard();

	SetClipboardData(CF_BITMAP, clip);

	CloseClipboard();

	SelectObject(clipdc, old);

	MessageBox(hwnd, "Copied to clipboard.", "Note", MB_OK);
}

void CopySelected() {
	int m = subselect[mode][submode[mode]];
	int frame = subselect[mode][submode[mode] + 32];
	int l = subselect[mode][submode[mode] + 64];
	int pl;

	switch (submode[mode]) {
		case 0:
			ToClipboard(ForceSprites[m][frame], FSSize[m][frame], FSPalette[m][l]);
			break;
		case 1:
			ToClipboard(EnemySprites[m][frame], ESSize[m][frame], ESPalette[m][l]);
			break;
		case 2:
			ToClipboard(WeaponSprites[m][frame], WSSize[m][frame], ISPalette[l], false, true);
			break;
		case 3:
			ToClipboard(Backgrounds[m], BGSize[m], BGPalette[m - m % 2][l]);
			break;
		case 4:
			ToClipboard(Platforms[m], PFSize[m], PFPalette[m]);
			break;
		case 5:
			if(m==0)MessageBox(hwnd, "Clipboard not currently available for this graphics type.", "Note", MB_OK);
			else {
				pl = m;
				while (pl>0 && CSPalOffset[pl] == 0)pl--;
				ToClipboard(CutsceneGFX[m], CSSize[m], CSPalette[pl]);
			}
			break;
		case 6:
			ToClipboard(Portraits[m], POSize[m], POPalette[m]);
			break;
		case 7:
			if (MSPalette[m])ToClipboard(MapSprites[m][frame], MSSize[m][frame], EMSPalette);
			else ToClipboard(MapSprites[m][frame], MSSize[m][frame], FMSPalette);
			break;
		case 8:
			ToClipboard(Tilesets[m], TSSize[m], TSPalette[TSPalNums[m]], true);
			break;
		case 9:
			ToClipboard(Effects[m], EFSize[m], EFPalette[m]);
			break;
	}
}