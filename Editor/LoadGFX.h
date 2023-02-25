COLORREF colorList[8] = { RGB(255,0,0), RGB(0,255,0), RGB(0,0,255), RGB(255,255,0), RGB(255,0,255), RGB(0,255,255), RGB(255,255,255), RGB(0,0,0) };

unsigned long GFXSpace[32];

unsigned char ForceSprites[80][8][12288];
unsigned int FSSize[80][8][2];
unsigned char NumFSFrame[80];

unsigned long FSBankOffset;

unsigned char EnemySprites[80][8][12288];
unsigned int ESSize[80][8][2];
unsigned char NumESFrame[80];

unsigned long ESBankOffset;

unsigned char WeaponSprites[64][6][12288];
unsigned int WSSize[64][6][2];
unsigned char NumWS;
unsigned char WSRepeat[64];

unsigned long WSBankOffset;

unsigned char Backgrounds[78][12288];
unsigned int BGSize[78][2];

unsigned long BGBankOffset;
bool BGExpand;

unsigned char Platforms[11][12288];
unsigned char PFPalette[11][16][3];
unsigned int PFSize[11][2];

unsigned long PFBankOffset;

unsigned char MenuIcons[9][12288];
unsigned int MISize[9][2];

unsigned long MIBankOffset;




unsigned char Portraits[128][12288];
unsigned char POPalette[128][16][3];
unsigned int POSize[128][2];
unsigned char POData[128][128];
bool POExpand;

unsigned long POBankOffset;

unsigned char MapSprites[256][3][12288];
//unsigned char MPalette[52][16][3];
unsigned int MSSize[256][3][2];
unsigned char NumMSFrame = 3;
unsigned char MSTextSound[256];
bool MSPalette[256];

unsigned long MSBankOffset;
unsigned long MSSoundOffset;

unsigned char Tilesets[33][17000];
unsigned int TSSize[33][2];
//unsigned char TSPalette[32][4][4][3];
unsigned char TSPalNums[33] = { 0,12,17,0,23,26,0,0,4,0,0,2,1,6,10,0,12,12,15,15,0,0,2,0,0,0,21,2,8,22,23,25,26 };

unsigned long TSBankOffset;

unsigned char Effects[19][17000];
unsigned int EFSize[19][2];
unsigned char EFPalette[19][16][3];

unsigned long EFBankOffset;
unsigned long EFPalOffset[19] = { 0x126B9E,0x1269C6,0x126A6C,0,0x126C8E,0x126DEA,0x126E78,0x126EF0,0x1270F4,0x126FFE,0x126FD0,0x127092,0x127182,0x126C26,0xB973E,0xB973E,0xB973E,0xC18AE,0xC18AE };

unsigned char TempGfx[65536];


unsigned char CutsceneGFX[64][20000];
unsigned int CSSize[64][2];

unsigned long CSGFXPointer[] = { 0xC005C, 0xC0000, 0xC0004, 0xC0008, 0xC000C, 0xC0010, 0xC001C, 0xC0014, 0xC0028, 0xC002C, 0xC0034, 0xC003C, 0xC0040, 0xC0048, 0xC004C, 0xC0050, 0xC0054, 0xC0068, 0xC006C, 0xC0070, 0xC0074, 0xC0078, 0xC007C, 0xC0080, 0xC0084 };
unsigned long CSPalOffset[] =  { 0xC57C4, 0xC15DE, 0,       0,       0,       0xC161E, 0,       0xC15FE, 0xC18AE, 0xC192E, 0xC2E50, 0xC331A, 0,       0xC3F2E, 0,       0,       0,       0xC7084, 0,       0,       0,       0,       0,       0,       0       };

unsigned char CSPalette[64][16][3];


int NumGFX[] = { 35,50,15,78,11,25,52,160,33,19 };

int SplashLayout[256] = {
	0,13,6,0,3,0,2,4,0,0,0,0,0,0,0,0,
	0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,
	0,3,0,0,0,0,0,0,0,0,0,0,0,0,3,0,
	0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,
	0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,
	0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,
	0,0,0,0,1,0,0,0,0,8,1,0,0,3,0,0,
	0,0,0,0,0,0,0,0,5,0,0,0,0,0,0,0,
	0,0,18,0,2,2,6,0,0,0,0,1,0,0,0,6,
	0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,
	0,0,1,5,0,0,0,0,0,0,1,0,0,5,0,0,
	0,0,0,0,1,0,0,0,4,0,0,0,0,0,0,1,
	0,6,0,0,0,0,0,0,0,0,0,1,0,5,3,0,
	0,0,0,0,0,3,0,0,0,0,0,0,0,1,0,0,
	0,3,0,0,0,0,0,0,0,3,0,-9 * 16 - 3,0,-255,-255,-255,
	-255,-255,-255,-255,-255,-255,-255,-255,-255,-255,-255,-255,-255,-255,-255,-255
};

bool GraphicsLoaded = false;
bool AnimGrid = false;
bool AnimBorder = false;
bool GFXBG = true;

unsigned long diff;

void DrawChunk(HDC target, int tx, int ty, unsigned char gfx[17000], unsigned char pal[16][3], int sizex, int sizey, int ox, int oy, int w, int h, int zoom = 1, bool flipx = false, bool flipy = false) {
	int qx = 0;
	int qy = 0;

	for (int vx = 0; vx < sizex; vx++) {
		for (int vy = 0; vy < sizey; vy++) {
			for (int x = 0; x < 8; x++) {
				for (int y = 0; y < 8; y++) {
					for (int dx = 0; dx < zoom; dx++) {
						for (int dy = 0; dy < zoom; dy++) {
							int k = gfx[8 * qx + ox + x + (8 * qy + oy + y)*w];
							if (k < 0)k = 0;

							if (AnimBorder)
								if ((!vx && !x) || (vx == sizex - 1 && x == 7) || (!vy && !y) || (vy == sizey - 1 && y == 7))k = 1;

							if (k) {
								if (!flipx) {
									if (!flipy)SetPixel(target, tx + zoom * (8 * vx + x) + dx, ty + zoom * (8 * vy + y) + dy, RGB(pal[k][0], pal[k][1], pal[k][2]));
									else       SetPixel(target, tx + zoom * (8 * vx + x) + dx, ty + zoom * (sizey * 8 - (8 * vy + y)) + dy, RGB(pal[k][0], pal[k][1], pal[k][2]));
								} else {
									if (!flipy)SetPixel(target, tx + zoom * (sizex * 8 - (8 * vx + x)) + dx, ty + zoom * (8 * vy + y) + dy, RGB(pal[k][0], pal[k][1], pal[k][2]));
									else       SetPixel(target, tx + zoom * (sizex * 8 - (8 * vx + x)) + dx, ty + zoom * (sizey * 8 - (8 * vy + y)) + dy, RGB(pal[k][0], pal[k][1], pal[k][2]));
								}
							}
						}
					}
				}
			}

			qy++;
			if ((oy + 8 * qy) % 32 == 0 || (oy + 8 * qy > h)) {
				qy -= 4;
				qx++;
				if ((ox + 8 * qx) % 32 == 0 || (ox + 8 * qx > w)) {
					qy += 4;
					qx -= 4;

					if (oy + 8 * qy > h) {
						qy -= h / 8;
						qx += 4;
					}
				}
			}

		}

	}

}

void DrawChunkSource(HDC target, int tx, int ty, COLORREF color, int sizex, int sizey, int ox, int oy, int w, int h, int zoom = 1) {
	int qx = 0;
	int qy = 0;

	for (int vx = 0; vx < sizex; vx++) {
		for (int vy = 0; vy < sizey; vy++) {
			for (int x = 0; x < 8; x++) {
				for (int y = 0; y < 8; y++) {
					for (int dx = 0; dx < zoom; dx++) {
						for (int dy = 0; dy < zoom; dy++) {
							//if ((!vx && !x) || (vx == sizex - 1 && x == 7) || (!vy && !y) || (vy == sizey - 1 && y == 7))
							if ((!y && !vy) || (y == 7 && vy == sizey - 1) || !x || x == 7 || (x % 2 == 0 && (!y && (qy + oy / 8) % 4 == 0)) || (x % 2 == 1 && (y == 7 && (qy + oy / 8) % 4 == 3))) {

								SetPixel(target, tx + zoom * (8 * qx + ox + x) + dx, ty + zoom * (8 * qy + oy + y) + dy, color);
							}
						}
					}
				}
			}

			qy++;
			if ((oy + 8 * qy) % 32 == 0 || (oy + 8 * qy > h)) {
				qy -= 4;
				qx++;
				if ((ox + 8 * qx) % 32 == 0 || (ox + 8 * qx > w)) {
					qy += 4;
					qx -= 4;

					if (oy + 8 * qy > h) {
						qy -= h / 8;
						qx += 4;
					}
				}
			}

		}

	}

}

void PixelToTileset(POINT &p) {

	p.x /= 4;
	p.y /= 4;

	int x, y;
	int dx, dy;
	int bx, by;
	int cx, cy;

	dx = p.x % 8;
	dy = p.y % 8;

	x = (p.x - dx) / 8;
	y = (p.y - dy) / 8;

	bx = y % 4;
	by = (y - bx) / 4;

	cx = x % 4;
	cy = (x - cx) / 4;

	p.x = 32 * cx + 8 * bx + dx;
	p.y = 32 * cy + 8 * by + dy;

	p.x *= 4;
	p.y *= 4;
}

void TilesetToPixel(POINT &p) {

	int dx, dy;

	p.x /= 4;
	p.y /= 4;

	dx = p.x % 8;
	dy = p.y % 8;

	int i, j;
	int x = -1, y = -1;

	for (i = 0; i<4 && x == -1; i++) {
		for (j = 0; j<4 && x == -1; j++) {
			if (p.x >= i * 32 && p.x<(i + 1) * 32 && p.y >= j * 32 && p.y<(j + 1) * 32) {
				x = j * 4 + i;
			}
		}
	}
	for (i = 0; i<4 && y == -1; i++) {
		for (j = 0; j<4 && y == -1; j++) {
			if (p.x >= i * 8 + 32 * (x % 4) && p.x<(i + 1) * 8 + 32 * (x % 4) && p.y >= j * 8 + 8 * (x - x % 4) && p.y<(j + 1) * 8 + 8 * (x - x % 4)) {
				y = j * 4 + i;
			}
		}
	}

	p.x = 8 * x + dx;
	p.y = 8 * y + dy;

	p.x *= 4;
	p.y *= 4;
}

int CtoN(int x, int y) {
	return 32 * (x - x % 4) / 4 + 16 * (y - y % 4) / 4 + 4 * (x % 4) + y % 4;
}

int NtoX(int n) {
	return (n - n % 4) / 4 - 4 * (n - n % 16) / 16 + 4 * (n - n % 32) / 32;
}

int NtoY(int n) {
	return n - 4 * (n - n % 4) / 4 + 4 * (n - n % 16) / 16 - 8 * (n - n % 32) / 32;
}

void resetMSPalettes() {
	for (int i = 0; i < 60; i++) {
		MSPalette[i] = false;
	}
	for (int i = 60; i < 70; i++) {
		MSPalette[i] = true;
	}
	MSPalette[70] = false;
	for (int i = 71; i < 89; i++) {
		MSPalette[i] = true;
	}
	MSPalette[89] = false;
	MSPalette[90] = true;
	MSPalette[91] = true;
	MSPalette[92] = true;
	MSPalette[93] = false;
	MSPalette[94] = true;
	MSPalette[95] = false;
	MSPalette[96] = true;
	MSPalette[97] = false;
	MSPalette[98] = true;
	MSPalette[99] = true;
	MSPalette[100] = false;
	for (int i = 101; i < 120; i++) {
		MSPalette[i] = true;
	}
	for (int i = 121; i < 160; i++) {
		MSPalette[i] = false;
	}
}

int findWSPalette(int w) {
	if (w == 14)w = 15;
	for (int i = 0; i<NumItems; i++) {
		if (ItemWS[i] == w) {
			for (int j = 0; j<4; j++) {
				if (ISPalette[i % 64][j][0] - j)return i % 64;
				if (ISPalette[i % 64][j][1] - j)return i % 64;
				if (ISPalette[i % 64][j][2] - j)return i % 64;
			}
		}
	}
	return 0;
}

void LoadGFX(char *path, bool single = false) {
	if (!GraphicsLoaded&&single)return;

	resetMSPalettes();

	for (int i = 0; i < 32; i++) {
		GFXSpace[i] = 0;
	}

	unsigned char r;
	unsigned int in = 0;
	FILE * fp = fopen(path, "rb");

	SetCursor(LoadCursor(0, IDC_WAIT));

	fseek(fp, 0x98FA, SEEK_SET);
	fscanf(fp, "%c", &in);
	if (in == 0x4E) {
		ChooseMSPal = true;
	} else {
		ChooseMSPal = false;
	}

	PixelDecompressor PD(fp);

	fseek(fp, 0x144000, SEEK_SET);
	fscanf(fp, "%c", &r);
	FSBankOffset = r;
	fscanf(fp, "%c", &r);
	FSBankOffset = FSBankOffset * 256 + r;
	fscanf(fp, "%c", &r);
	FSBankOffset = FSBankOffset * 256 + r;
	fscanf(fp, "%c", &r);
	FSBankOffset = FSBankOffset * 256 + r;

	if (!single)
		if (FSBankOffset>0x180000) {
			fseek(fp, 0x23FFFF, SEEK_SET);
			fscanf(fp, "%c", &r);
			if (r != 0 && r != 255)NumGFX[0] = r;
			else NumGFX[0] = 35;
		} else {
			NumGFX[0] = 35;
		}

	fseek(fp, 0x100000, SEEK_SET);
	fscanf(fp, "%c", &r);
	ESBankOffset = r;
	fscanf(fp, "%c", &r);
	ESBankOffset = ESBankOffset * 256 + r;
	fscanf(fp, "%c", &r);
	ESBankOffset = ESBankOffset * 256 + r;
	fscanf(fp, "%c", &r);
	ESBankOffset = ESBankOffset * 256 + r;

	if (!single)
		if (ESBankOffset>0x180000) {
			fseek(fp, 0x23FCFF, SEEK_SET);
			fscanf(fp, "%c", &r);
			if (r != 0 && r != 255)NumGFX[1] = r;
			else NumGFX[1] = 50;
		} else {
			NumGFX[1] = 50;
		}


	fseek(fp, 0x144008, SEEK_SET);
	fscanf(fp, "%c", &r);
	WSBankOffset = r;
	fscanf(fp, "%c", &r);
	WSBankOffset = WSBankOffset * 256 + r;
	fscanf(fp, "%c", &r);
	WSBankOffset = WSBankOffset * 256 + r;
	fscanf(fp, "%c", &r);
	WSBankOffset = WSBankOffset * 256 + r;

	fseek(fp, 0xCC000, SEEK_SET);
	fscanf(fp, "%c", &r);
	BGBankOffset = r;
	fscanf(fp, "%c", &r);
	BGBankOffset = BGBankOffset * 256 + r;
	fscanf(fp, "%c", &r);
	BGBankOffset = BGBankOffset * 256 + r;
	fscanf(fp, "%c", &r);
	BGBankOffset = BGBankOffset * 256 + r;

	fseek(fp, 0x144010, SEEK_SET);
	fscanf(fp, "%c", &r);
	PFBankOffset = r;
	fscanf(fp, "%c", &r);
	PFBankOffset = PFBankOffset * 256 + r;
	fscanf(fp, "%c", &r);
	PFBankOffset = PFBankOffset * 256 + r;
	fscanf(fp, "%c", &r);
	PFBankOffset = PFBankOffset * 256 + r;

	fseek(fp, 0xBE6C, SEEK_SET);
	fscanf(fp, "%c", &r);
	MIBankOffset = r;
	fscanf(fp, "%c", &r);
	MIBankOffset = MIBankOffset * 256 + r;
	fscanf(fp, "%c", &r);
	MIBankOffset = MIBankOffset * 256 + r;
	fscanf(fp, "%c", &r);
	MIBankOffset = MIBankOffset * 256 + r;

	fseek(fp, 0x2C004, SEEK_SET);
	fscanf(fp, "%c", &r);
	POBankOffset = r;
	fscanf(fp, "%c", &r);
	POBankOffset = POBankOffset * 256 + r;
	fscanf(fp, "%c", &r);
	POBankOffset = POBankOffset * 256 + r;
	fscanf(fp, "%c", &r);
	POBankOffset = POBankOffset * 256 + r;

	if (!single)
		if (POBankOffset>0x1E0000) {
			fseek(fp, 0x23ECFF, SEEK_SET);
			fscanf(fp, "%c", &r);
			if (r != 0 && r != 255)NumGFX[6] = r;
			else NumGFX[6] = 52;
		} else {
			NumGFX[6] = 52;
		}

	fseek(fp, 0x38000, SEEK_SET);
	fscanf(fp, "%c", &r);
	MSBankOffset = r;
	fscanf(fp, "%c", &r);
	MSBankOffset = MSBankOffset * 256 + r;
	fscanf(fp, "%c", &r);
	MSBankOffset = MSBankOffset * 256 + r;
	fscanf(fp, "%c", &r);
	MSBankOffset = MSBankOffset * 256 + r;

	if (!single)
		if (MSBankOffset>0x1E0000) {
			fseek(fp, 0x23EFFF, SEEK_SET);
			fscanf(fp, "%c", &r);
			if (r != 0 && r != 255)NumGFX[7] = r;
			else NumGFX[7] = 160;
		} else {
			NumGFX[7] = 160;
		}

	fseek(fp, 0x17F6C, SEEK_SET);
	fscanf(fp, "%c", &in);
	if (in == 0x4E) {
		MSSoundOffset = 0x1A9D80;
	} else {
		MSSoundOffset = 0x17BBC;
	}
	fseek(fp, MSSoundOffset, SEEK_SET);
	for (int s = 0; s < NumGFX[7]; s++) {
		fscanf(fp, "%c", &MSTextSound[s]);
	}

	if (ChooseMSPal) {
		char b = 0;
		fseek(fp, 0x23EF60, SEEK_SET);
		for (int s = 0; s < NumGFX[7]; s++) {
			if (!(s % 8)) {
				fscanf(fp, "%c", &b);
			}
			MSPalette[s] = (b & 0x80);
			b = b << 1;

		}
	}


	fseek(fp, 0x5800C, SEEK_SET);
	fscanf(fp, "%c", &r);
	TSBankOffset = r;
	fscanf(fp, "%c", &r);
	TSBankOffset = TSBankOffset * 256 + r;
	fscanf(fp, "%c", &r);
	TSBankOffset = TSBankOffset * 256 + r;
	fscanf(fp, "%c", &r);
	TSBankOffset = TSBankOffset * 256 + r;

	EFBankOffset = 0x124030;

	char * data;
	unsigned char c, l;
	char t;
	int len;
	long o = FSBankOffset;
	long o2, o3;

	unsigned int pal[2];
	unsigned int frame[16];

	int s, i;

	//loads the yes/no choice menu icons
	/*			len = PD.GetData(0x57EA,&data);

	long tee = ftell(fp);

	for(i=0;i<len;i++){
	c=data[i];
	if(c==0xFF)TempGfx[i]=l;
	else {
	TempGfx[i]=c;
	l=c;
	}
	}
	//delete data;
	*/

	ExpandedGraphics = false;

	o = FSBankOffset;

	if (!single || submode[mode] == 0)
		for (s = 0; s<NumGFX[0]; s++) {

			fseek(fp, o, SEEK_SET);
			fscanf(fp, "%c", &r);
			o2 = r;
			fscanf(fp, "%c", &r);
			o2 = o2 * 256 + r;
			fscanf(fp, "%c", &r);
			o2 = o2 * 256 + r;
			fscanf(fp, "%c", &r);
			o2 = o2 * 256 + r;
			o += 4;

			if (!s && o2 == 0x300000)
				ExpandedGraphics = true;

			if (ExpandedGraphics)o2 += 0x100000;

			if (!single || s == subselect[mode][submode[mode]]) {

				fseek(fp, o2, SEEK_SET);
				for (i = 0; i<2; i++) {
					fscanf(fp, "%c", &r);
					pal[i] = r;
					fscanf(fp, "%c", &r);
					pal[i] = pal[i] * 256 + r;
				}

				frame[0] = 0;
				fscanf(fp, "%c", &r);
				frame[0] = r;
				fscanf(fp, "%c", &r);
				frame[0] = frame[0] * 256 + r;

				NumFSPalette[s] = (frame[0] - pal[1]) / 32;
				NumFSFrame[s] = pal[1] / 2 - 1;

				for (i = 1; i<NumFSFrame[s]; i++) {
					frame[i] = 0;
					fscanf(fp, "%c", &r);
					frame[i] = r;
					fscanf(fp, "%c", &r);
					frame[i] = frame[i] * 256 + r;
				}


				fseek(fp, o2 + pal[1] + 2, SEEK_SET);
				for (int p = 0; p<NumFSPalette[s]; p++) {
					//readPalette(FSPalette[s][p],16,fp);
				}

				for (int f = 0; f<NumFSFrame[s]; f++) {
					len = PD.GetData(o2 + frame[f] + 2, &data);
					FSSize[s][f][0] = PD.width;
					FSSize[s][f][1] = PD.height;

					for (i = 0; i<len; i++) {
						c = data[i];
						if (c == 0xFF)ForceSprites[s][f][i] = l;
						else {
							ForceSprites[s][f][i] = c;
							l = c;
						}
					}
					//delete data;
				}
			}
		}

	o = ESBankOffset;
	if (!single || submode[mode] == 1)
		for (s = 0; s<NumGFX[1]; s++) {

			fseek(fp, o, SEEK_SET);
			fscanf(fp, "%c", &r);
			o2 = r;
			fscanf(fp, "%c", &r);
			o2 = o2 * 256 + r;
			fscanf(fp, "%c", &r);
			o2 = o2 * 256 + r;
			fscanf(fp, "%c", &r);
			o2 = o2 * 256 + r;
			o += 4;

			if (ExpandedGraphics)o2 += 0x200000;

			if (!single || s == subselect[mode][submode[mode]]) {
				fseek(fp, o2, SEEK_SET);
				for (i = 0; i<2; i++) {
					fscanf(fp, "%c", &r);
					pal[i] = r;
					fscanf(fp, "%c", &r);
					pal[i] = pal[i] * 256 + r;
				}

				frame[0] = 0;
				fscanf(fp, "%c", &r);
				frame[0] = r;
				fscanf(fp, "%c", &r);
				frame[0] = frame[0] * 256 + r;

				NumESPalette[s] = (frame[0] - pal[1]) / 32;
				NumESFrame[s] = pal[1] / 2 - 1;

				for (i = 1; i<NumESFrame[s]; i++) {
					frame[i] = 0;
					fscanf(fp, "%c", &r);
					frame[i] = r;
					fscanf(fp, "%c", &r);
					frame[i] = frame[i] * 256 + r;
				}


				fseek(fp, o2 + pal[1] + 2, SEEK_SET);
				for (int p = 0; p<NumESPalette[s]; p++) {
					//readPalette(ESPalette[s][p],16,fp);
				}

				for (int f = 0; f<NumESFrame[s]; f++) {
					len = PD.GetData(o2 + frame[f] + 2, &data);
					//len = PD.GetData(0x200000,&data);
					ESSize[s][f][0] = PD.width;
					ESSize[s][f][1] = PD.height;

					for (i = 0; i<len; i++) {
						c = data[i];
						if (c == 0xFF)EnemySprites[s][f][i] = l;
						else {
							EnemySprites[s][f][i] = c;
							l = c;
						}
					}
					//delete data;
				}
			}
		}

	o = WSBankOffset;
	o2 = 0;
	o3 = 0;
	t = -1;

	if (!single) {
		if (WSBankOffset == 0x23EBD0 || WSBankOffset == 0x1E7000) {
			fseek(fp, 0x23EBCF, SEEK_SET);
			fscanf(fp, "%c", &r);
			if (r != 0 && r != 255)NumGFX[2] = r;
			else NumGFX[2] = 15;
		} else NumGFX[2] = 15;
	} else NumGFX[2] = 15;

	if (!single || submode[mode] == 2)
		for (s = 0; s<31 + (NumGFX[2] - 15); s++) {
			o3 = o2;

			if (t >= 0)WSRepeat[t] = 0;
			s--;

			while (o3 == o2) {
				fseek(fp, o, SEEK_SET);
				fscanf(fp, "%c", &r);
				o2 = r;
				fscanf(fp, "%c", &r);
				o2 = o2 * 256 + r;
				fscanf(fp, "%c", &r);
				o2 = o2 * 256 + r;
				fscanf(fp, "%c", &r);
				o2 = o2 * 256 + r;
				o += 4;
				if (t >= 0)WSRepeat[t]++;
				s++;
			}

			t++;

			if(s<31 + (NumGFX[2] - 15))
			if (!single || s == subselect[mode][submode[mode]]) {

				fseek(fp, o2, SEEK_SET);

				for (int f = 0; f<1; f++) {
					len = PD.GetData(o2, &data);
					WSSize[t][f][0] = PD.width;
					WSSize[t][f][1] = PD.height;

					for (int i = 0; i<len; i++) {
						c = data[i];
						if (c == 0xFF)WeaponSprites[t][f][i] = l;
						else {
							WeaponSprites[t][f][i] = c;
							l = c;
						}
					}
					//delete data;
				}
			}
		}

	o = BGBankOffset;



	if (!single || submode[mode] == 3)
		for (s = 0; s<78; s++) {


			fseek(fp, o, SEEK_SET);
			fscanf(fp, "%c", &r);
			o2 = r;
			fscanf(fp, "%c", &r);
			o2 = o2 * 256 + r;
			fscanf(fp, "%c", &r);
			o2 = o2 * 256 + r;
			fscanf(fp, "%c", &r);
			o2 = o2 * 256 + r;
			o += 4;

			if (!s) {
				if (o2 == 0x3B0000)BGExpand = true;
				else BGExpand = false;
			}

			if (BGExpand)o2 += 0x200000;

			if (!single || s == subselect[mode][submode[mode]]) {

				NumBGPalette[s] = 1;

				fseek(fp, o2, SEEK_SET);
				for (int p = 0; p<NumBGPalette[s]; p++) {
					//readPalette(BGPalette[s][p],16,fp);
				}

				if (s % 2 == 0)len = PD.GetData(o2 + 32, &data);
				else len = PD.GetData(o2, &data);
				BGSize[s][0] = PD.width;
				BGSize[s][1] = PD.height;

				for (int i = 0; i<len; i++) {
					c = data[i];
					if (c == 0xFF)Backgrounds[s][i] = l;
					else {
						Backgrounds[s][i] = c;
						l = c;
					}
				}
				//delete data;
			}
		}

	o = PFBankOffset;

	if (!single || submode[mode] == 4)
		for (s = 0; s<11; s++) {

			fseek(fp, o, SEEK_SET);
			fscanf(fp, "%c", &r);
			o2 = r;
			fscanf(fp, "%c", &r);
			o2 = o2 * 256 + r;
			fscanf(fp, "%c", &r);
			o2 = o2 * 256 + r;
			fscanf(fp, "%c", &r);
			o2 = o2 * 256 + r;
			o += 4;

			if (!single || s == subselect[mode][submode[mode]]) {

				fseek(fp, o2, SEEK_SET);
				readPalette(PFPalette[s] + 2, 4, fp);
				PFPalette[s][0][0] = 224;
				PFPalette[s][0][1] = 224;
				PFPalette[s][0][2] = 224;
				PFPalette[s][1][0] = 0;
				PFPalette[s][1][1] = 0;
				PFPalette[s][1][2] = 0;

				for (int f = 0; f<1; f++) {
					len = PD.GetData(o2 + 8, &data);
					PFSize[s][0] = PD.width;
					PFSize[s][1] = PD.height;

					for (int i = 0; i<len; i++) {
						c = data[i];
						if (c == 0x0E)c = 1;
						if (c == 0xFF)Platforms[s][i] = l;
						else {
							Platforms[s][i] = c;
							l = c;
						}
					}
					//delete data;
				}
			}
		}

	o = POBankOffset;

	if (!single || submode[mode] == 6)
		for (s = 0; s<NumGFX[6]; s++) {

			fseek(fp, o, SEEK_SET);
			fscanf(fp, "%c", &r);
			o2 = r;
			fscanf(fp, "%c", &r);
			o2 = o2 * 256 + r;
			fscanf(fp, "%c", &r);
			o2 = o2 * 256 + r;
			fscanf(fp, "%c", &r);
			o2 = o2 * 256 + r;
			o += 4;

			if (!s) {
				if (o2 == 0x3C0000)POExpand = true;
				else POExpand = false;
			}

			if (POExpand)o2 += 0x100000;

			if (!single || s == subselect[mode][submode[mode]]) {
				l = 0;
				fseek(fp, o2, SEEK_SET);
				//facial animation tile data
				fscanf(fp, "%c", &(POData[s][l++]));
				fscanf(fp, "%c", &(POData[s][l++]));
				t = l;
				for (i = 0; i<POData[s][t - 2] * 256 + POData[s][t - 1]; i++) {
					fscanf(fp, "%c", &(POData[s][l++]));
					fscanf(fp, "%c", &(POData[s][l++]));
					fscanf(fp, "%c", &(POData[s][l++]));
					fscanf(fp, "%c", &(POData[s][l++]));
				}
				fscanf(fp, "%c", &(POData[s][l++]));
				fscanf(fp, "%c", &(POData[s][l++]));
				t = l;
				for (i = 0; i<POData[s][t - 2] * 256 + POData[s][t - 1]; i++) {
					fscanf(fp, "%c", &(POData[s][l++]));
					fscanf(fp, "%c", &(POData[s][l++]));
					fscanf(fp, "%c", &(POData[s][l++]));
					fscanf(fp, "%c", &(POData[s][l++]));
				}
				POData[s][l] = 0xFF;

				//fseek(fp,o2+28,SEEK_SET);
				readPalette(POPalette[s], 16, fp);

				for (int f = 0; f<1; f++) {
					len = PD.GetData(o2 + l + 32, &data);
					POSize[s][0] = PD.width;
					POSize[s][1] = PD.height;

					for (i = 0; i<len; i++) {
						c = data[i];
						if (c == 0xFF)Portraits[s][i] = l;
						else {
							Portraits[s][i] = c;
							l = c;
						}
					}
					//delete data;
				}
			}
		}

	o = MSBankOffset;

	if (!single || submode[mode] == 7)
		for (s = 0; s<3 * NumGFX[7]; s++) {

			fseek(fp, o, SEEK_SET);
			fscanf(fp, "%c", &r);
			o2 = r;
			fscanf(fp, "%c", &r);
			o2 = o2 * 256 + r;
			fscanf(fp, "%c", &r);
			o2 = o2 * 256 + r;
			fscanf(fp, "%c", &r);
			o2 = o2 * 256 + r;
			o += 4;

			if (!single || s == subselect[mode][submode[mode]]) {
				fseek(fp, o2, SEEK_SET);


				int f = (s - s%NumGFX[7]) / NumGFX[7];

				len = PD.GetData(o2, &data, 6, 3);
				MSSize[s%NumGFX[7]][f][0] = PD.width;
				MSSize[s%NumGFX[7]][f][1] = PD.height;

				for (int i = 0; i<len; i++) {
					c = data[i];
					if (c == 0xFF)MapSprites[s%NumGFX[7]][f][i] = l;
					else {
						MapSprites[s%NumGFX[7]][f][i] = c;
						l = c;
					}
				}
				//delete data;
			}

		}

	o = TSBankOffset;

	if (!single || submode[mode] == 8)
		for (s = 0; s<33; s++) {
			if (s == 6)o += 24;
			fseek(fp, o, SEEK_SET);
			fscanf(fp, "%c", &r);
			o2 = r;
			fscanf(fp, "%c", &r);
			o2 = o2 * 256 + r;
			fscanf(fp, "%c", &r);
			o2 = o2 * 256 + r;
			fscanf(fp, "%c", &r);
			o2 = o2 * 256 + r;
			o += 4;

			if (!single || s == subselect[mode][submode[mode]]) {
				fseek(fp, o2, SEEK_SET);

				for (int f = 0; f<1; f++) {
					len = PD.GetData(o2, &data);
					TSSize[s][0] = PD.width;
					TSSize[s][1] = PD.height;

					for (int i = 0; i<len; i++) {
						c = data[i];
						if (c == 0xFF)Tilesets[s][i] = l;
						else {
							Tilesets[s][i] = c;
							l = c;
						}
					}
					//delete data;
				}
			}
		}

	o = EFBankOffset;

	if (!single || submode[mode] == 9)
		for (s = 0; s<19; s++) {

			if (!single || s == subselect[mode][submode[mode]]) {
				fseek(fp, EFPalOffset[s], SEEK_SET);
				if (s == 3) {
					fseek(fp, 0x126D9C, SEEK_SET);
					readPalette(EFPalette[s] + 6, 1, fp);
					fseek(fp, 0x126D72, SEEK_SET);
					readPalette(EFPalette[s] + 7, 1, fp);
					fseek(fp, 0x126D7A, SEEK_SET);
					readPalette(EFPalette[s] + 8, 1, fp);
					EFPalette[s][0][0] = 0xFF;
					EFPalette[s][0][1] = 0xFF;
					EFPalette[s][0][2] = 0xFF;
				} else if (s<14) {
					readPalette(EFPalette[s] + 6, 5, fp);
					EFPalette[s][0][0] = 0xFF;
					EFPalette[s][0][1] = 0xFF;
					EFPalette[s][0][2] = 0xFF;
					EFPalette[s][1][0] = 0;
					EFPalette[s][1][1] = 0;
					EFPalette[s][1][2] = 0;
				} else {
					readPalette(EFPalette[s], 16, fp);
				}
			}


			fseek(fp, o, SEEK_SET);
			fscanf(fp, "%c", &r);
			o2 = r;

			fscanf(fp, "%c", &r);
			o2 = o2 * 256 + r;
			fscanf(fp, "%c", &r);
			o2 = o2 * 256 + r;
			fscanf(fp, "%c", &r);
			o2 = o2 * 256 + r;
			o += 4;

			if (!single || s == subselect[mode][submode[mode]]) {
				fseek(fp, o2, SEEK_SET);

				for (int f = 0; f<1; f++) {
					len = PD.GetData(o2, &data);
					EFSize[s][0] = PD.width;
					EFSize[s][1] = PD.height;

					for (int i = 0; i<len; i++) {
						c = data[i];
						if (c == 0xFF)Effects[s][i] = l;
						else {
							Effects[s][i] = c;
							l = c;
						}
					}
					//delete data;
				}
			}
		}

	o = MIBankOffset;


	//o = 0xBC004;//
	//o = 0xB97F4;//



	if (!single)
		for (s = 0; s<NumGFX[5]; s++) {
			
			o = CSPalOffset[s];
			if (o) {
				fseek(fp, o, SEEK_SET);
				readPalette(CSPalette[s], 16, fp);
			}

			o = CSGFXPointer[s];

			fseek(fp, o, SEEK_SET);
			fscanf(fp, "%c", &r);
			o2 = r;
			fscanf(fp, "%c", &r);
			o2 = o2 * 256 + r;
			fscanf(fp, "%c", &r);
			o2 = o2 * 256 + r;
			fscanf(fp, "%c", &r);
			o2 = o2 * 256 + r;
			o += 4;

			fseek(fp, o2, SEEK_SET);


				len = PD.GetData(o2, &data);
				CSSize[s][0] = PD.width;
				CSSize[s][1] = PD.height;

				for (int i = 0; i<len; i++) {
					c = data[i];
					if (c == 0xFF)CutsceneGFX[s][i] = l;
					else {
						CutsceneGFX[s][i] = c;
						l = c;
					}
				}
				//delete data;
	
		}

	fclose(fp);
	sprintf(file, path);

	GraphicsLoaded = true;
	SetCursor(LoadCursor(0, IDC_ARROW));
	InvalidateRect(hwnd, NULL, false);
}

unsigned char FindColor(unsigned char palette[16][3], unsigned char color[3], int colors = 16, int start = 0) {
	diff = 255 * 255 * 3 + 1;
	unsigned long d;
	unsigned int t;
	unsigned char match;
	if (color[0] == 100 && color[1] == 1 && color[2] == 99)
		return 0;
	for (int i = colors - 1; i >= start; i--) {
		d = 0;
		t = abs(color[0] - palette[i][0]);
		d += t*t;
		t = abs(color[1] - palette[i][1]);
		d += t*t;
		t = abs(color[2] - palette[i][2]);
		d += t*t;
		//if(!d)return i;
		if (d<diff) {
			diff = d;
			match = i;
		} else if (d == diff&&i) {
			diff = d;
			match = i;
		}
	}
	return match;
}

unsigned char FindWSColor(unsigned char palette[4][3], unsigned char color[3], int colors = 4, int start = 0) {
	diff = 255 * 255 * 3 + 1;
	unsigned long d;
	unsigned int t;
	unsigned char match;
	if (color[0] == 100 && color[1] == 1 && color[2] == 99)
		return 0;
	for (int i = colors - 1; i >= start; i--) {
		d = 0;
		t = abs(color[0] - palette[i][0]);
		d += t*t;
		t = abs(color[1] - palette[i][1]);
		d += t*t;
		t = abs(color[2] - palette[i][2]);
		d += t*t;
		//if(!d)return i;
		if (d<diff) {
			diff = d;
			match = i;
		} else if (d == diff&&i) {
			diff = d;
			match = i;
		}
	}


	d = 0;
	t = abs(color[0] - 0);
	d += t*t;
	t = abs(color[1] - 0);
	d += t*t;
	t = abs(color[2] - 0);
	d += t*t;
	if (d <= diff) {
		return 14;
	}

	d = 0;
	t = abs(color[0] - 255);
	d += t*t;
	t = abs(color[1] - 255);
	d += t*t;
	t = abs(color[2] - 255);
	d += t*t;
	if (d<diff) {
		return 1;
	}

	switch (match) {
		case 0:
			return 11;
		case 1:
			return 12;
		case 2:
			return 13;
		case 3:
			return 15;
	}

	return match;
}

void ImportGFX() {
	int j;
	unsigned char r;
	FILE * fp;// = fopen(path,"rb");

	String file;
	char tempc[32];

	int l;
	POINT p;

	unsigned char color[3];

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

	SetCursor(LoadCursor(0, IDC_WAIT));

	int s;

	for (s = 0; s<NumItems; s++) {
		file = path;
		file += "\\Icons\\Items\\";
		file += itoa(s, tempc, 10);
		file += ".bmp";
		fp = fopen(file, "rb");
		if (fp) {
			fseek(fp, 0x36, SEEK_SET);

			int x;
			for (int y = 23; y >= 0; y--) {
				for (x = 0; x<16; x++) {
					fscanf(fp, "%c", &(color[2]));
					fscanf(fp, "%c", &(color[1]));
					fscanf(fp, "%c", &(color[0]));
					ItemImages[s][x + y * 16] = FindColor(IconPalette, color);
				}
				for (x = 0; x<(4 - (16 * 3) % 4) % 4; x++) {
					fscanf(fp, "%c", &r);
				}
			}
			fclose(fp);
		}
	}

	for (s = 0; s<16 + 16 * ExpandSpells; s++) {
		file = path;
		file += "\\Icons\\Spells\\";
		file += itoa(s, tempc, 10);
		file += ".bmp";
		fp = fopen(file, "rb");
		if (fp) {
			fseek(fp, 0x36, SEEK_SET);

			int x;
			for (int y = 23; y >= 0; y--) {
				for (x = 0; x<16; x++) {
					fscanf(fp, "%c", &(color[2]));
					fscanf(fp, "%c", &(color[1]));
					fscanf(fp, "%c", &(color[0]));
					SpellImages[s][x + y * 16] = FindColor(IconPalette, color);
				}
				for (x = 0; x<(4 - (16 * 3) % 4) % 4; x++) {
					fscanf(fp, "%c", &r);
				}
			}
			fclose(fp);
		}
	}




	for (s = 0; s<NumGFX[0]; s++) {
		for (int i = 0; i<6; i++) {
			file = path;
			file += "\\Battle\\Force\\";
			file += itoa(s, tempc, 10);
			file += "_";
			file += itoa(i, tempc, 10);
			file += ".bmp";
			fp = fopen(file, "rb");
			if (fp) {
				FSSize[s][i][0] = 0;
				fseek(fp, 0x12, SEEK_SET);
				fscanf(fp, "%c", &r);
				FSSize[s][i][0] += r;
				fscanf(fp, "%c", &r);
				FSSize[s][i][0] += r * 256;
				fscanf(fp, "%c", &r);
				FSSize[s][i][0] += r * 256 * 256;


				FSSize[s][i][1] = 0;
				fseek(fp, 0x16, SEEK_SET);
				fscanf(fp, "%c", &r);
				FSSize[s][i][1] += r;
				fscanf(fp, "%c", &r);
				FSSize[s][i][1] += r * 256;
				fscanf(fp, "%c", &r);
				FSSize[s][i][1] += r * 256 * 256;

				fseek(fp, 0x36, SEEK_SET);

				int x;
				for (int y = FSSize[s][i][1] - 1; y >= 0; y--) {
					for (x = 0; x<FSSize[s][i][0]; x++) {
						fscanf(fp, "%c", &(color[2]));
						fscanf(fp, "%c", &(color[1]));
						fscanf(fp, "%c", &(color[0]));
						ForceSprites[s][i][x + y*FSSize[s][i][0]] = FindColor(FSPalette[s][0], color);
					}
					for (x = 0; x<(4 - (FSSize[s][i][0] * 3) % 4) % 4; x++) {
						fscanf(fp, "%c", &r);
					}
				}
				fclose(fp);
			}
		}
	}

	for (s = 0; s<NumGFX[1]; s++) {
		for (int i = 0; i<6; i++) {
			file = path;
			file += "\\Battle\\Enemies\\";
			file += itoa(s, tempc, 10);
			file += "_";
			file += itoa(i, tempc, 10);
			file += ".bmp";
			fp = fopen(file, "rb");
			if (fp) {
				ESSize[s][i][0] = 0;
				fseek(fp, 0x12, SEEK_SET);
				fscanf(fp, "%c", &r);
				ESSize[s][i][0] += r;
				fscanf(fp, "%c", &r);
				ESSize[s][i][0] += r * 256;
				fscanf(fp, "%c", &r);
				ESSize[s][i][0] += r * 256 * 256;


				ESSize[s][i][1] = 0;
				fseek(fp, 0x16, SEEK_SET);
				fscanf(fp, "%c", &r);
				ESSize[s][i][1] += r;
				fscanf(fp, "%c", &r);
				ESSize[s][i][1] += r * 256;
				fscanf(fp, "%c", &r);
				ESSize[s][i][1] += r * 256 * 256;

				fseek(fp, 0x36, SEEK_SET);

				int x;

				for (int y = ESSize[s][i][1] - 1; y >= 0; y--) {
					for (x = 0; x<ESSize[s][i][0]; x++) {
						fscanf(fp, "%c", &(color[2]));
						fscanf(fp, "%c", &(color[1]));
						fscanf(fp, "%c", &(color[0]));
						EnemySprites[s][i][x + y*ESSize[s][i][0]] = FindColor(ESPalette[s][0], color);
					}
					for (x = 0; x<(4 - (ESSize[s][i][0] * 3) % 4) % 4; x++) {
						fscanf(fp, "%c", &r);
					}
				}
				fclose(fp);
			}
		}
	}

	for (s = 0; s<NumGFX[2]; s++) {
		if (s == 3)
			s = s;
		l = findWSPalette(s);
		for (int i = 0; i<1; i++) {
			file = path;
			file += "\\Battle\\Weapons\\";
			file += itoa(s, tempc, 10);
			file += ".bmp";
			fp = fopen(file, "rb");
			if (fp) {
				WSSize[s][i][0] = 0;
				fseek(fp, 0x12, SEEK_SET);
				fscanf(fp, "%c", &r);
				WSSize[s][i][0] += r;
				fscanf(fp, "%c", &r);
				WSSize[s][i][0] += r * 256;
				fscanf(fp, "%c", &r);
				WSSize[s][i][0] += r * 256 * 256;


				WSSize[s][i][1] = 0;
				fseek(fp, 0x16, SEEK_SET);
				fscanf(fp, "%c", &r);
				WSSize[s][i][1] += r;
				fscanf(fp, "%c", &r);
				WSSize[s][i][1] += r * 256;
				fscanf(fp, "%c", &r);
				WSSize[s][i][1] += r * 256 * 256;

				fseek(fp, 0x36, SEEK_SET);

				int x;

				for (int y = WSSize[s][i][1] - 1; y >= 0; y--) {
					for (x = 0; x<WSSize[s][i][0]; x++) {
						fscanf(fp, "%c", &(color[2]));
						fscanf(fp, "%c", &(color[1]));
						fscanf(fp, "%c", &(color[0]));
						WeaponSprites[s][i][x + y*WSSize[s][i][0]] = FindWSColor(ISPalette[l], color);
					}
					for (x = 0; x<(4 - (WSSize[s][i][0] * 3) % 4) % 4; x++) {
						fscanf(fp, "%c", &r);
					}
				}
				fclose(fp);
			}
		}
	}

	for (s = 0; s<NumGFX[3]; s++) {
		for (int i = 0; i<6; i++) {
			file = path;
			file += "\\Battle\\Backgrounds\\";
			file += itoa(s, tempc, 10);
			file += ".bmp";
			fp = fopen(file, "rb");
			if (fp) {
				BGSize[s][0] = 0;
				fseek(fp, 0x12, SEEK_SET);
				fscanf(fp, "%c", &r);
				BGSize[s][0] += r;
				fscanf(fp, "%c", &r);
				BGSize[s][0] += r * 256;
				fscanf(fp, "%c", &r);
				BGSize[s][0] += r * 256 * 256;


				BGSize[s][1] = 0;
				fseek(fp, 0x16, SEEK_SET);
				fscanf(fp, "%c", &r);
				BGSize[s][1] += r;
				fscanf(fp, "%c", &r);
				BGSize[s][1] += r * 256;
				fscanf(fp, "%c", &r);
				BGSize[s][1] += r * 256 * 256;

				fseek(fp, 0x36, SEEK_SET);

				int x;

				for (int y = BGSize[s][1] - 1; y >= 0; y--) {
					for (x = 0; x<BGSize[s][0]; x++) {
						fscanf(fp, "%c", &(color[2]));
						fscanf(fp, "%c", &(color[1]));
						fscanf(fp, "%c", &(color[0]));
						Backgrounds[s][x + y*BGSize[s][0]] = FindColor(BGPalette[s - s % 2][0], color);
					}
					for (x = 0; x<(4 - (BGSize[s][0] * 3) % 4) % 4; x++) {
						fscanf(fp, "%c", &r);
					}
				}
				fclose(fp);
			}
		}
	}

	for (s = 0; s<NumGFX[4]; s++) {
		file = path;
		file += "\\Battle\\Platforms\\";
		file += itoa(s, tempc, 10);
		file += ".bmp";
		fp = fopen(file, "rb");
		if (fp) {
			PFSize[s][0] = 0;
			fseek(fp, 0x12, SEEK_SET);
			fscanf(fp, "%c", &r);
			PFSize[s][0] += r;
			fscanf(fp, "%c", &r);
			PFSize[s][0] += r * 256;
			fscanf(fp, "%c", &r);
			PFSize[s][0] += r * 256 * 256;


			PFSize[s][1] = 0;
			fseek(fp, 0x16, SEEK_SET);
			fscanf(fp, "%c", &r);
			PFSize[s][1] += r;
			fscanf(fp, "%c", &r);
			PFSize[s][1] += r * 256;
			fscanf(fp, "%c", &r);
			PFSize[s][1] += r * 256 * 256;

			fseek(fp, 0x36, SEEK_SET);

			int x;

			for (int y = PFSize[s][1] - 1; y >= 0; y--) {
				for (x = 0; x<PFSize[s][0]; x++) {
					fscanf(fp, "%c", &(color[2]));
					fscanf(fp, "%c", &(color[1]));
					fscanf(fp, "%c", &(color[0]));
					Platforms[s][x + y*PFSize[s][0]] = FindColor(PFPalette[s], color, 6);
				}
				for (x = 0; x<(4 - (PFSize[s][0] * 3) % 4) % 4; x++) {
					fscanf(fp, "%c", &r);
				}
			}
			fclose(fp);
		}
	}

	for (s = 0; s<NumGFX[6]; s++) {
		file = path;
		file += "\\Portraits\\";
		file += itoa(s, tempc, 10);
		file += ".bmp";
		fp = fopen(file, "rb");
		if (fp) {
			POSize[s][0] = 0;
			fseek(fp, 0x12, SEEK_SET);
			fscanf(fp, "%c", &r);
			POSize[s][0] += r;
			fscanf(fp, "%c", &r);
			POSize[s][0] += r * 256;
			fscanf(fp, "%c", &r);
			POSize[s][0] += r * 256 * 256;


			POSize[s][1] = 0;
			fseek(fp, 0x16, SEEK_SET);
			fscanf(fp, "%c", &r);
			POSize[s][1] += r;
			fscanf(fp, "%c", &r);
			POSize[s][1] += r * 256;
			fscanf(fp, "%c", &r);
			POSize[s][1] += r * 256 * 256;

			fseek(fp, 0x36, SEEK_SET);

			int x;

			for (int y = POSize[s][1] - 1; y >= 0; y--) {
				for (x = 0; x<POSize[s][0]; x++) {
					fscanf(fp, "%c", &(color[2]));
					fscanf(fp, "%c", &(color[1]));
					fscanf(fp, "%c", &(color[0]));
					Portraits[s][x + y*POSize[s][0]] = FindColor(POPalette[s], color);
				}
				for (x = 0; x<(4 - (POSize[s][0] * 3) % 4) % 4; x++) {
					fscanf(fp, "%c", &r);
				}
			}
			fclose(fp);
		}
	}

	for (s = 0; s<NumGFX[7]; s++) {
		for (int i = 0; i<3; i++) {
			file = path;
			file += "\\Map\\Sprites\\";
			file += itoa(s, tempc, 10);
			file += "_";
			file += itoa(i, tempc, 10);
			file += ".bmp";
			fp = fopen(file, "rb");
			if (fp) {
				MSSize[s][i][0] = 0;
				fseek(fp, 0x12, SEEK_SET);
				fscanf(fp, "%c", &r);
				MSSize[s][i][0] += r;
				fscanf(fp, "%c", &r);
				MSSize[s][i][0] += r * 256;
				fscanf(fp, "%c", &r);
				MSSize[s][i][0] += r * 256 * 256;


				MSSize[s][i][1] = 0;
				fseek(fp, 0x16, SEEK_SET);
				fscanf(fp, "%c", &r);
				MSSize[s][i][1] += r;
				fscanf(fp, "%c", &r);
				MSSize[s][i][1] += r * 256;
				fscanf(fp, "%c", &r);
				MSSize[s][i][1] += r * 256 * 256;

				fseek(fp, 0x36, SEEK_SET);

				int x;

				for (int y = MSSize[s][i][1] - 1; y >= 0; y--) {
					for (x = 0; x<MSSize[s][i][0]; x++) {
						fscanf(fp, "%c", &(color[2]));
						fscanf(fp, "%c", &(color[1]));
						fscanf(fp, "%c", &(color[0]));
						if (!MSPalette[s])
							MapSprites[s][i][x + y*MSSize[s][i][0]] = FindColor(FMSPalette, color);
						else
							MapSprites[s][i][x + y*MSSize[s][i][0]] = FindColor(EMSPalette, color);
					}
					for (x = 0; x<(4 - (MSSize[s][i][0] * 3) % 4) % 4; x++) {
						fscanf(fp, "%c", &r);
					}
				}
				fclose(fp);
			}
		}
	}

	for (s = 0; s<NumGFX[6]; s++) {
		file = path;
		file += "\\Map\\Tilesets\\";
		file += itoa(s, tempc, 10);
		file += ".bmp";
		fp = fopen(file, "rb");
		if (fp) {
			TSSize[s][0] = 0;
			fseek(fp, 0x12, SEEK_SET);
			fscanf(fp, "%c", &r);
			TSSize[s][0] += r;
			fscanf(fp, "%c", &r);
			TSSize[s][0] += r * 256;
			fscanf(fp, "%c", &r);
			TSSize[s][0] += r * 256 * 256;


			TSSize[s][1] = 0;
			fseek(fp, 0x16, SEEK_SET);
			fscanf(fp, "%c", &r);
			TSSize[s][1] += r;
			fscanf(fp, "%c", &r);
			TSSize[s][1] += r * 256;
			fscanf(fp, "%c", &r);
			TSSize[s][1] += r * 256 * 256;

			fseek(fp, 0x36, SEEK_SET);

			int x;

			for (int y = TSSize[s][1] - 1; y >= 0; y--) {
				for (x = 0; x<TSSize[s][0]; x++) {
					fscanf(fp, "%c", &(color[2]));
					fscanf(fp, "%c", &(color[1]));
					fscanf(fp, "%c", &(color[0]));
					p.x = x * 4;
					p.y = y * 4;
					TilesetToPixel(p);
					Tilesets[s][p.x / 4 + (p.y / 4)*TSSize[s][0]] = FindColor(TSPalette[TSPalNums[s]], color);
				}
				for (x = 0; x<(4 - (TSSize[s][0] * 3) % 4) % 4; x++) {
					fscanf(fp, "%c", &r);
				}
			}
			fclose(fp);
		}
	}

	for (s = 0; s<NumGFX[9]; s++) {
		file = path;
		file += "\\Animations\\";
		file += itoa(s, tempc, 10);
		file += ".bmp";
		fp = fopen(file, "rb");
		if (fp) {
			EFSize[s][0] = 0;
			fseek(fp, 0x12, SEEK_SET);
			fscanf(fp, "%c", &r);
			EFSize[s][0] += r;
			fscanf(fp, "%c", &r);
			EFSize[s][0] += r * 256;
			fscanf(fp, "%c", &r);
			EFSize[s][0] += r * 256 * 256;


			EFSize[s][1] = 0;
			fseek(fp, 0x16, SEEK_SET);
			fscanf(fp, "%c", &r);
			EFSize[s][1] += r;
			fscanf(fp, "%c", &r);
			EFSize[s][1] += r * 256;
			fscanf(fp, "%c", &r);
			EFSize[s][1] += r * 256 * 256;

			fseek(fp, 0x36, SEEK_SET);

			if (s == 3) {
				j = 9;
			} else if (s<14) {
				j = 11;
			} else {
				j = 16;
			}

			int x;

			for (int y = EFSize[s][1] - 1; y >= 0; y--) {
				for (x = 0; x<EFSize[s][0]; x++) {
					fscanf(fp, "%c", &(color[2]));
					fscanf(fp, "%c", &(color[1]));
					fscanf(fp, "%c", &(color[0]));
					Effects[s][x + y*EFSize[s][0]] = FindColor(EFPalette[s], color, j, 6);
				}
				for (x = 0; x<(4 - (EFSize[s][0] * 3) % 4) % 4; x++) {
					fscanf(fp, "%c", &r);
				}
			}
			fclose(fp);
		}
	}

	int i, k, vx, vy, x, y;

	for (s = 0; s<NumGFX[5]; s++) {
		file = path;
		file += "\\Screens\\";
		file += itoa(s, tempc, 10);
		file += ".bmp";
		fp = fopen(file, "rb");
		if (fp) {
			CSSize[s][0] = 0;
			fseek(fp, 0x12, SEEK_SET);
			fscanf(fp, "%c", &r);
			CSSize[s][0] += r;
			fscanf(fp, "%c", &r);
			CSSize[s][0] += r * 256;
			fscanf(fp, "%c", &r);
			CSSize[s][0] += r * 256 * 256;


			CSSize[s][1] = 0;
			fseek(fp, 0x16, SEEK_SET);
			fscanf(fp, "%c", &r);
			CSSize[s][1] += r;
			fscanf(fp, "%c", &r);
			CSSize[s][1] += r * 256;
			fscanf(fp, "%c", &r);
			CSSize[s][1] += r * 256 * 256;

			fseek(fp, 0x36, SEEK_SET);

			
			

			if (s == 0) {
				int x;
				for (i = 0; i < 256 * 256; i++)TempGfx[i] = 255;

				for (int y = CSSize[s][1] - 1; y >= 0; y--) {
					for (x = 0; x<CSSize[s][0]; x++) {
						fscanf(fp, "%c", &(color[2]));
						fscanf(fp, "%c", &(color[1]));
						fscanf(fp, "%c", &(color[0]));
						TempGfx[x + y*CSSize[s][0]] = FindColor(CSPalette[s], color);
					}
					for (x = 0; x<(4 - (CSSize[s][0] * 3) % 4) % 4; x++) {
						fscanf(fp, "%c", &r);
					}
				}

				CSSize[s][0] = 128;
				CSSize[s][1] = 128;

				int width = CSSize[s][0];
				int height = CSSize[s][1];

				int qx = -1;
				int qy = 0;

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
								k = TempGfx[qx * 8 + x % 8 + (qy * 8 + y % 8) * 256];
								if (k < 0)k = 0;


								CutsceneGFX[s][p.x / 4 + p.y / 4 * width] = k;
						}

					}
				}



			} else {
				int x;

				int pl = s;
				while (pl>0 && CSPalOffset[pl] == 0)pl--;

				for (int y = CSSize[s][1] - 1; y >= 0; y--) {
					for (x = 0; x<CSSize[s][0]; x++) {
						fscanf(fp, "%c", &(color[2]));
						fscanf(fp, "%c", &(color[1]));
						fscanf(fp, "%c", &(color[0]));

						CutsceneGFX[s][x + y*CSSize[s][0]] = FindColor(CSPalette[pl], color);
					}
					for (x = 0; x<(4 - (CSSize[s][0] * 3) % 4) % 4; x++) {
						fscanf(fp, "%c", &r);
					}
				}
			}
			
			fclose(fp);
		}
	}



	SetCursor(LoadCursor(0, IDC_ARROW));

	MessageBox(NULL, "Graphics Imported", "Note", MB_OK);


	GraphicsLoaded = true;
}

void GFXImport() {
	ImportGFX();
}

void FromClipboard(unsigned char * data, unsigned int size[2], unsigned char pal[16][3], bool tileset, bool weapon, bool resize, bool recolor) {
	UINT format = 0;

	int ci = 0;

	if (recolor) {
		for (int i = 0; i < 16; i++) {
			if ((pal[i][0] != 100 || pal[i][1] != 1 || pal[i][2] != 99) && i + 1 > ci)ci = i + 1;
			else break;
		}
	}

	if (!IsClipboardFormatAvailable(CF_BITMAP))return;

	if (!OpenClipboard(hwnd))
		return;

	/*for (;;) {
	format = EnumClipboardFormats(format);
	if (!format) {
	CloseClipboard();
	return;
	}
	if (format == CF_BITMAP)break;
	}*/



	clip = (HBITMAP)GetClipboardData(CF_BITMAP);


	if (!clip) {
		CloseClipboard();
		return;
	}


	HBITMAP old = (HBITMAP)SelectObject(clipdc, clip);

	int x, y;

	POINT p;

	BITMAP bm;
	GetObject(clip, sizeof(bm), &bm);

	if (bm.bmWidth != size[0] || bm.bmHeight != size[1]) {
		char out[512];

		if (!resize) {
			sprintf(out, "Image sizes do not match.\r\nExpected %d x %d\r\nReceived %d x %d", size[0], size[1], bm.bmWidth, bm.bmHeight);
			MessageBox(hwnd, out, "Note", MB_OK);
			CloseClipboard();
			return;
		} else {
			if (bm.bmWidth % 8 || bm.bmHeight % 8) {
				sprintf(out, "Image size must be a multiple of 8 pixels.");
				MessageBox(hwnd, out, "Note", MB_OK);
				CloseClipboard();
				return;
			} else {
				size[0] = bm.bmWidth;
				size[1] = bm.bmHeight;
			}
		}
	}

	unsigned char color[3];

	for (x = 0; x<size[0]; x++) {
		for (y = 0; y<size[1]; y++) {
			COLORREF c = GetPixel(clipdc, x, y);
			color[0] = GetRValue(c);
			color[1] = GetGValue(c);
			color[2] = GetBValue(c);

			if (tileset) {
				p.x = x * 4;
				p.y = y * 4;
				TilesetToPixel(p);
				p.x /= 4;
				p.y /= 4;
			} else {
				p.x = x;
				p.y = y;
			}

			if (weapon)data[p.x + p.y*size[0]] = FindWSColor(pal, color);
			else data[p.x + p.y*size[0]] = FindColor(pal, color);

			if (recolor && diff > 0 && ci < 16 && (ci<4 || !weapon) && (color[0] != 100 || color[1] != 1 || color[2] != 99)) {
				int tci = ci;

				if (weapon) {
					switch (ci) {
						case 0:
							tci = 11;
							break;
						case 1:
							tci = 12;
							break;
						case 2:
							tci = 13;
							break;
						case 3:
							tci = 15;
							break;
					}
				}

				pal[ci][0] = color[0];
				pal[ci][1] = color[1];
				pal[ci][2] = color[2];
				data[p.x + p.y*size[0]] = tci;
				ci++;
				while ((pal[ci][0] != 100 || pal[ci][1] != 1 || pal[ci][2] != 99) && ci < 15)ci++;
			}
		}
	}
	CloseClipboard();
	InvalidateRect(hwnd, NULL, true);

	SelectObject(clipdc, old);
}

void PasteSelected(bool recolor = false) {
	int m = subselect[mode][submode[mode]];
	int frame = subselect[mode][submode[mode] + 32];
	int l = subselect[mode][submode[mode] + 64];

	int pl;

	switch (submode[mode]) {
		case 0:

			if (recolor) {
				FSPalette[m][l][0][0] = 128;
				FSPalette[m][l][0][1] = 128;
				FSPalette[m][l][0][2] = 128;
				FSPalette[m][l][1][0] = 255;
				FSPalette[m][l][1][1] = 255;
				FSPalette[m][l][1][2] = 255;

				for (int i = 2; i < 16; i++) {
					if (i < 10 || i>14) {
						FSPalette[m][l][i][0] = 100;
						FSPalette[m][l][i][1] = 1;
						FSPalette[m][l][i][2] = 99;
					}
				}
			}

			FromClipboard(ForceSprites[m][frame], FSSize[m][frame], FSPalette[m][l], false, false, false, recolor);
			break;
		case 1:
			if (recolor) {
				ESPalette[m][l][0][0] = 128;
				ESPalette[m][l][0][1] = 128;
				ESPalette[m][l][0][2] = 128;
				ESPalette[m][l][1][0] = 255;
				ESPalette[m][l][1][1] = 255;
				ESPalette[m][l][1][2] = 255;

				for (int i = 2; i < 16; i++) {
					if (i < 10 || i>14) {
						ESPalette[m][l][i][0] = 100;
						ESPalette[m][l][i][1] = 1;
						ESPalette[m][l][i][2] = 99;
					}
				}
			}

			FromClipboard(EnemySprites[m][frame], ESSize[m][frame], ESPalette[m][l], false, false, false, recolor);
			break;
		case 2:
			if (recolor) {
				for (int i = 0; i < 4; i++) {
					ISPalette[l][i][0] = 100;
					ISPalette[l][i][1] = 1;
					ISPalette[l][i][2] = 99;
				}
			}

			FromClipboard(WeaponSprites[m][frame], WSSize[m][frame], ISPalette[l], false, true, false, recolor);
			break;
		case 3:
			if (recolor) {
				for (int i = 0; i < 16; i++) {
					BGPalette[m - m % 2][l][i][0] = 100;
					BGPalette[m - m % 2][l][i][1] = 1;
					BGPalette[m - m % 2][l][i][2] = 99;
				}
			}

			FromClipboard(Backgrounds[m], BGSize[m], BGPalette[m - m % 2][l], false, false, false, recolor);
			break;
		case 4:
			if (recolor) {
				PFPalette[m][0][0] = 255;
				PFPalette[m][0][1] = 255;
				PFPalette[m][0][2] = 255;
				PFPalette[m][1][0] = 0;
				PFPalette[m][1][1] = 0;
				PFPalette[m][1][2] = 0;
				for (int i = 2; i < 6; i++) {
					PFPalette[m][i][0] = 100;
					PFPalette[m][i][1] = 1;
					PFPalette[m][i][2] = 99;
				}
			}

			FromClipboard(Platforms[m], PFSize[m], PFPalette[m], false, false, false, recolor);
			break;
		case 5:
			if(!m)MessageBox(hwnd, "Clipboard not currently available for this graphics type.", "Note", MB_OK);
			else {

				pl = m;
				while (pl>0 && CSPalOffset[pl] == 0)pl--;


				if (recolor) {
					for (int i = 0; i < 16; i++) {
						CSPalette[pl][i][0] = 100;
						CSPalette[pl][i][1] = 1;
						CSPalette[pl][i][2] = 99;
					}
				}


				FromClipboard(CutsceneGFX[m], CSSize[m], CSPalette[pl], false, false, false, true);
			}
			break;
		case 6:
			if (recolor) {
				POPalette[m][0][0] = 0;
				POPalette[m][0][1] = 0;
				POPalette[m][0][2] = 0;
				for (int i = 1; i < 16; i++) {
					POPalette[m][i][0] = 100;
					POPalette[m][i][1] = 1;
					POPalette[m][i][2] = 99;
				}
			}

			FromClipboard(Portraits[m], POSize[m], POPalette[m], false, false, false, true);
			break;
		case 7:
			if (MSPalette[m])FromClipboard(MapSprites[m][frame], MSSize[m][frame], EMSPalette);
			else FromClipboard(MapSprites[m][frame], MSSize[m][frame], FMSPalette);
			break;
		case 8:
			if (recolor) {
				TSPalette[TSPalNums[m]][0][0] = 0;
				TSPalette[TSPalNums[m]][0][1] = 0;
				TSPalette[TSPalNums[m]][0][2] = 0;
				for (int i = 1; i < 16; i++) {
					TSPalette[TSPalNums[m]][i][0] = 100;
					TSPalette[TSPalNums[m]][i][1] = 1;
					TSPalette[TSPalNums[m]][i][2] = 99;
				}
			}

			FromClipboard(Tilesets[m], TSSize[m], TSPalette[TSPalNums[m]], true, false, false, true);
			break;
		case 9:
			FromClipboard(Effects[m], EFSize[m], EFPalette[m]);
			break;
	}
}