#include "SpellAnimScript.h"

unsigned char TempBGPalette[16][3];
unsigned char TempBGPalette2[16][3];
unsigned char TempPFPalette[16][3];
unsigned char TempFSPalette[16][3];
unsigned char TempESPalette[16][3];

bool TempPalReady = false;
bool DrawBG2 = true;

unsigned char FlickerColor[32][3];

//unsigned char AnimEffectGFX[32];
unsigned char NumAnimGFX[32];
char AnimGFX[32][64][5];
unsigned char PaletteScript[32][64][4];
unsigned char PSLen[32];

unsigned char SpellAnimGFX[32][17000];
unsigned int SAGFXSize[32][2];
unsigned char SpellAnimPal[32][5][3];
ScriptContainer SpellAnimScript[32];

unsigned char NumSpellAnim = 0;

char PaletteActions[][24] = { "Load Color", "Save Color", "Filter", "Increase/Decrease", "Cap Value", 
	"Mix Color", "Set Color", "Clear Value","Add Value","Reduce","Duplicate","Multiply/Divide" };

int SpellFrame = -1;
int LastFrame = -1;

POINT NtoXY(int n, int h) {
	POINT r;

	int s = (h * 4);
	int c = (n - n%s) / s;
	n -= c*s;

	int b = (n - n % 16) / 16;
	n -= b * 16;

	r.y = b*4 + n%4;
	

	r.x = c*4 + (n - n % 4) / 4;
	return r;
}

int XYtoN(int x, int y, int h) {
	int s = (h * 4);
	int c = (x - x % 4) / 4;
	int b = (y - y % 4) / 4;

	x -= 4 * c;
	y -= 4 * b;


	return c*s + b * 16 + x * 4 + y;
}

void initPals() {
	ScriptFunction * sf;
	ScriptLine * sl;
	ScriptItem * si;

	sf = new ScriptFunction("Initialize");//
	sl = new ScriptLine();
	sf->lines.append(sl);
	si = new ScriptItem(0, "X");
	sl->items.append(si);
	si = new ScriptItem(0, "=");
	sl->items.append(si);
	si = new ScriptItem(0, "X");
	sl->items.append(si);
	si = new ScriptItem(0, "+");
	sl->items.append(si);
	si = new ScriptItem(0, "1");
	sl->items.append(si);

	SpellAnimScript[0].functions.append(sf);//

	sf = new ScriptFunction("FrameRoutine");//
	SpellAnimScript[0].functions.append(sf);//

	for (int i = 0; i < 32; i++) {
		FlickerColor[i][0] = 0;
		FlickerColor[i][1] = 0;
		FlickerColor[i][2] = 0;
	}

	FlickerColor[0][0] = 222;

	NumSpellAnim = 1;

	NumAnimGFX[0] = 12;
	//AnimEffectGFX[0] = 2;
	
	for (int i = 0;i < 17000;i++) {
		SpellAnimGFX[0][i] = Effects[2][i];
	}

	for (int i = 0;i < 16;i++) {
		SpellAnimPal[0][i + 6][0] = 100;
		SpellAnimPal[0][i + 6][1] = 1;
		SpellAnimPal[0][i + 6][2] = 99;
	}

	for (int i = 0;i < 5;i++) {
		SpellAnimPal[0][i + 6][0] = EFPalette[2][i + 6][0];
		SpellAnimPal[0][i + 6][1] = EFPalette[2][i + 6][1];
		SpellAnimPal[0][i + 6][2] = EFPalette[2][i + 6][2];
	}
	SpellAnimPal[0][0][0] = 128;
	SpellAnimPal[0][0][1] = 128;
	SpellAnimPal[0][0][2] = 128;
	SpellAnimPal[0][1][0] = 255;
	SpellAnimPal[0][1][1] = 255;
	SpellAnimPal[0][1][2] = 255;

	SAGFXSize[0][0] = EFSize[2][0];
	SAGFXSize[0][1] = EFSize[2][1];

	AnimGFX[0][0][0] = 0xF0;
	AnimGFX[0][0][1] = 0xC0;
	AnimGFX[0][0][2] = 0x60;
	AnimGFX[0][0][3] = 0x0F;
	AnimGFX[0][0][4] = 0x00;

	AnimGFX[0][1][0] = 0xF0;
	AnimGFX[0][1][1] = 0xE0;
	AnimGFX[0][1][2] = 0x70;
	AnimGFX[0][1][3] = 0x0F;
	AnimGFX[0][1][4] = 0x00;

	AnimGFX[0][2][0] = 0xF0;
	AnimGFX[0][2][1] = 0xC0;
	AnimGFX[0][2][2] = 0x60;
	AnimGFX[0][2][3] = 0x0F;
	AnimGFX[0][2][4] = 0x01;

	AnimGFX[0][3][0] = 0xF0;
	AnimGFX[0][3][1] = 0xE0;
	AnimGFX[0][3][2] = 0x70;
	AnimGFX[0][3][3] = 0x0F;
	AnimGFX[0][3][4] = 0x01;

	AnimGFX[0][4][0] = 0xF4;
	AnimGFX[0][4][1] = 0xD0;
	AnimGFX[0][4][2] = 0x9A;
	AnimGFX[0][4][3] = 0x0A;
	AnimGFX[0][4][4] = 0x00;

	AnimGFX[0][5][0] = 0xF4;
	AnimGFX[0][5][1] = 0xE8;
	AnimGFX[0][5][2] = 0xA3;
	AnimGFX[0][5][3] = 0x0A;
	AnimGFX[0][5][4] = 0x00;

	AnimGFX[0][6][0] = 0xF4;
	AnimGFX[0][6][1] = 0xD0;
	AnimGFX[0][6][2] = 0x9A;
	AnimGFX[0][6][3] = 0x0A;
	AnimGFX[0][6][4] = 0x01;

	AnimGFX[0][7][0] = 0xF4;
	AnimGFX[0][7][1] = 0xE8;
	AnimGFX[0][7][2] = 0xA3;
	AnimGFX[0][7][3] = 0x0A;
	AnimGFX[0][7][4] = 0x01;

	AnimGFX[0][8][0] = 0xF8;
	AnimGFX[0][8][1] = 0xE0;
	AnimGFX[0][8][2] = 0xAC;
	AnimGFX[0][8][3] = 0x05;
	AnimGFX[0][8][4] = 0x00;

	AnimGFX[0][9][0] = 0xF8;
	AnimGFX[0][9][1] = 0xF0;
	AnimGFX[0][9][2] = 0xB0;
	AnimGFX[0][9][3] = 0x05;
	AnimGFX[0][9][4] = 0x00;

	AnimGFX[0][10][0] = 0xF8;
	AnimGFX[0][10][1] = 0xE0;
	AnimGFX[0][10][2] = 0xAC;
	AnimGFX[0][10][3] = 0x05;
	AnimGFX[0][10][4] = 0x01;

	AnimGFX[0][11][0] = 0xF8;
	AnimGFX[0][11][1] = 0xF0;
	AnimGFX[0][11][2] = 0xB0;
	AnimGFX[0][11][3] = 0x05;
	AnimGFX[0][11][4] = 0x01;

	PSLen[0] = 0;
	memset(PaletteScript, 0, 64 * 32 * 4);

	PaletteScript[0][0][0] = 0;
	PaletteScript[0][1][0] = 2;
	PaletteScript[0][1][1] = 0xE;
	PaletteScript[0][2][0] = 3;
	PaletteScript[0][2][1] = 1;
	PaletteScript[0][3][0] = 4;
	PaletteScript[0][3][1] = 1;
	PaletteScript[0][4][0] = 3;
	PaletteScript[0][4][1] = 0;
	PaletteScript[0][4][2] = 1;
	PaletteScript[0][5][0] = 6;
	PaletteScript[0][5][1] = 1;
	PSLen[0] = 6;
}

void redPals(int bg, int bg2, int pf, int fs, int es) {
	TempPalReady = true;
	for (int i = 0; i < 16; i++) {

		TempBGPalette[i][0] = BGPalette[bg * 2][0][i][0] * 2;
		if (BGPalette[bg * 2][0][i][0] > 127)TempBGPalette[i][0] = 255;
		TempBGPalette[i][0] = reduceColor(TempBGPalette[i][0]);
		TempBGPalette[i][1] = reduceColor(BGPalette[bg * 2][0][i][1] / 2);
		TempBGPalette[i][2] = reduceColor(BGPalette[bg * 2][0][i][2] / 2);

		TempBGPalette2[i][0] = BGPalette[bg2 * 2][0][i][0] * 2;
		if (BGPalette[bg2 * 2][0][i][0] > 127)TempBGPalette2[i][0] = 255;
		TempBGPalette2[i][0] = reduceColor(TempBGPalette2[i][0]);
		TempBGPalette2[i][1] = reduceColor(BGPalette[bg2 * 2][0][i][1] / 2);
		TempBGPalette2[i][2] = reduceColor(BGPalette[bg2 * 2][0][i][2] / 2);

		TempPFPalette[i][0] = PFPalette[pf][i][0] * 2;
		if (PFPalette[pf][i][0] > 127)TempPFPalette[i][0] = 255;
		TempPFPalette[i][0] = reduceColor(TempPFPalette[i][0]);
		TempPFPalette[i][1] = reduceColor(PFPalette[pf][i][1] / 2);
		TempPFPalette[i][2] = reduceColor(PFPalette[pf][i][2] / 2);

		TempESPalette[i][0] = ESPalette[es][0][i][0] * 2;
		if (ESPalette[es][0][i][0] > 127)TempESPalette[i][0] = 255;
		TempESPalette[i][0] = reduceColor(TempESPalette[i][0]);
		TempESPalette[i][1] = reduceColor(ESPalette[es][0][i][1] / 2);
		TempESPalette[i][2] = reduceColor(ESPalette[es][0][i][2] / 2);

		TempFSPalette[i][0] = FSPalette[fs][0][i][0] * 2;
		if (FSPalette[fs][0][i][0] > 127)TempFSPalette[i][0] = 255;
		TempFSPalette[i][0] = reduceColor(TempFSPalette[i][0]);
		TempFSPalette[i][1] = reduceColor(FSPalette[fs][0][i][1] / 2);
		TempFSPalette[i][2] = reduceColor(FSPalette[fs][0][i][2] / 2);

	}
}

void restorePals(int bg, int bg2, int pf, int fs, int es) {
	TempPalReady = true;
	for (int i = 0; i < 16; i++) {

		TempBGPalette[i][0] = BGPalette[bg * 2][0][i][0];
		TempBGPalette[i][1] = BGPalette[bg * 2][0][i][1];
		TempBGPalette[i][2] = BGPalette[bg * 2][0][i][2];

		TempBGPalette2[i][0] = BGPalette[bg2 * 2][0][i][0];
		TempBGPalette2[i][1] = BGPalette[bg2 * 2][0][i][1];
		TempBGPalette2[i][2] = BGPalette[bg2 * 2][0][i][2];

		TempPFPalette[i][0] = PFPalette[pf][i][0];
		TempPFPalette[i][1] = PFPalette[pf][i][1];
		TempPFPalette[i][2] = PFPalette[pf][i][2];

		TempESPalette[i][0] = ESPalette[es][0][i][0];
		TempESPalette[i][1] = ESPalette[es][0][i][1];
		TempESPalette[i][2] = ESPalette[es][0][i][2];

		TempFSPalette[i][0] = FSPalette[fs][0][i][0];
		TempFSPalette[i][1] = FSPalette[fs][0][i][1];
		TempFSPalette[i][2] = FSPalette[fs][0][i][2];

	}
}

int tps;



void PaletteStep(unsigned char pal[][3], int index, int action, int arg=0, int arg2=0, int arg3=0) {
	int a = 0;
	int b = 0;

	switch (action) {
		case 0://load

			tps = RGBToGen(pal[index][2]) * 256 + RGBToGen(pal[index][1]) * 16 + RGBToGen(pal[index][0]);

			break;
		case 1://save

			pal[index][2] = GenToRGB((tps & 0xE00) / 256);
			pal[index][1] = GenToRGB((tps & 0x0E0) / 16);
			pal[index][0] = GenToRGB((tps & 0x00E));

			break;
		case 2://filter

			tps &= arg3 * 256 + arg2 * 16 + arg;

			break;
		case 3://shift

			if (arg2) {
				a = RGBToGen(pal[index][2]) * 256 + RGBToGen(pal[index][1]) * 16 + RGBToGen(pal[index][0]);

				if (arg)a = a << 1;
				else a = a >> 1;

				pal[index][2] = GenToRGB((a & 0xE00) / 256);
				pal[index][1] = GenToRGB((a & 0x0E0) / 16);
				pal[index][0] = GenToRGB((a & 0x00E));
			} else {
				if (arg)tps = tps << 1;
				else tps = tps >> 1;
			}
			break;
		case 4://cap

			if (!arg2) {
				if (arg) {
					if (tps & 0x1000)tps |= 0x0E00;
					if (tps & 0x0100)tps |= 0x00E0;
					if (tps & 0x0010)tps |= 0x000E;
					tps &= 0xEEE;
				} else {
					tps &= 0x666;
				}
			} else {
				a = RGBToGen(pal[index][2]) * 256 + RGBToGen(pal[index][1]) * 16 + RGBToGen(pal[index][0]);

				if (arg) {
					if (a & 0x1000)a |= 0x0E00;
					if (a & 0x0100)a |= 0x00E0;
					if (a & 0x0010)a |= 0x000E;
					a &= 0xEEE;
				} else {
					a &= 0x666;
				}
				
				pal[index][2] = GenToRGB((a & 0xE00) / 256);
				pal[index][1] = GenToRGB((a & 0x0E0) / 16);
				pal[index][0] = GenToRGB((a & 0x00E));
			}

			
			break;
		case 5://mix

			a = RGBToGen(pal[index][2]) * 256 + RGBToGen(pal[index][1]) * 16 + RGBToGen(pal[index][0]);
			a |= tps;


			pal[index][2] = GenToRGB((a & 0xE00) / 256);
			pal[index][1] = GenToRGB((a & 0x0E0) / 16);
			pal[index][0] = GenToRGB((a & 0x00E));

			break;
		case 6://set

			a = RGBToGen(pal[index][2]) * 256 + RGBToGen(pal[index][1]) * 16 + RGBToGen(pal[index][0]);

			b = 14 * 256 * arg3 + 14 * 16 * arg2 + 14 * arg;
			b = 0xEEE - b;

			a &= b;

			b = 0xEEE - b;

			a |= (tps & b);

			pal[index][2] = GenToRGB((a & 0xE00) / 256);
			pal[index][1] = GenToRGB((a & 0x0E0) / 16);
			pal[index][0] = GenToRGB((a & 0x00E));


			break;
		case 7://clear
			tps = 0;
			break;
		case 8://add
			if(arg)tps += RGBToGen(pal[index][0]);
			if(arg2)tps += RGBToGen(pal[index][1]);
			if(arg3)tps += RGBToGen(pal[index][2]);
			break;
		case 9://reduce
			switch (arg) {
				case 0:
					tps &= 0x000E;
					break;
				case 1:
					tps &= 0x00E0;
					tps /= 16;
					break;
				case 2:
					tps &= 0x0E00;
					tps /= 256;
					break;
			}
			break;
		case 10://duplicate
			tps &= 0x000E;
			tps += (tps * 16) + (tps * 256);
			break;
		case 11://mul/div
			if (arg) {
				tps /= arg2;
			} else {
				tps *= arg2;
			}
			tps &= 0xFFFF;
			break;
	}
}

void runPaletteScript(unsigned char script[][4],int len) {
	for (int j = 0; j < 16; j++) {
		for (int i = 0; i < len; i++) {
			PaletteStep(TempBGPalette,  j, script[i][0], script[i][1], script[i][2], script[i][3]);
		}
	}
	reducePalette(TempBGPalette);

	for (int j = 0; j < 16; j++) {
		for (int i = 0; i < len; i++) {
			PaletteStep(TempBGPalette2, j, script[i][0], script[i][1], script[i][2], script[i][3]);
		}
	}
	reducePalette(TempBGPalette2);

	for (int j = 0; j < 16; j++) {
		for (int i = 0; i < len; i++) {
			PaletteStep(TempPFPalette, j, script[i][0], script[i][1], script[i][2], script[i][3]);
		}
	}
	reducePalette(TempPFPalette);

	for (int j = 0; j < 16; j++) {
		for (int i = 0; i < len; i++) {
			PaletteStep(TempESPalette, j, script[i][0], script[i][1], script[i][2], script[i][3]);
		}
	}
	reducePalette(TempESPalette);

	for (int j = 0; j < 16; j++) {
		for (int i = 0; i < len; i++) {
			PaletteStep(TempFSPalette, j, script[i][0], script[i][1], script[i][2], script[i][3]);
		}
	}
	reducePalette(TempFSPalette);
}

void PasteSelectedAnim() {
	int m = select[mode];

	switch (subselect[mode][7]) {
	case 2:

		SpellAnimPal[m][0][0] = 128;
		SpellAnimPal[m][0][1] = 128;
		SpellAnimPal[m][0][2] = 128;
		SpellAnimPal[m][1][0] = 255;
		SpellAnimPal[m][1][1] = 255;
		SpellAnimPal[m][1][2] = 255;

		for (int i = 2;i < 6;i++) {
			SpellAnimPal[m][i][0] = 127;
			SpellAnimPal[m][i][1] = 128;
			SpellAnimPal[m][i][2] = 129;
		}
		for (int i = 6;i < 16;i++) {
			SpellAnimPal[m][i][0] = 100;
			SpellAnimPal[m][i][1] = 1;
			SpellAnimPal[m][i][2] = 99;
		}

		FromClipboard(SpellAnimGFX[m], SAGFXSize[m], SpellAnimPal[m], false, false, true, true);





		break;
	}
}