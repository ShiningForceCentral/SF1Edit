#pragma warning( disable : 4477) 


#include "stdafx.h"
#include <shlobj.h> 

#include "resource.h"
#include "stdio.h"
//#include "iomanip.h"
#include "commdlg.h"
#include "math.h"
#include "io.h"
#include "Shellapi.h"
#include "Fcntl.h"
#include "Share.h"
#include "time.h"
#include <direct.h>

char version[] = "3.4.4";

char ScriptTitles[][32] = { "Dialogue Scripts", "Battle End Scripts", "Map/Battle Exit Scripts", "Chapter Start Scripts", "Battle Start Scripts", "World Cutscenes" };

#include "lists.h"

#define random(min, max) ((rand()%(int)(((max) + 1)-(min)))+ (min))

char *replace(char *s, const char *find, const char *replace){
	int i = 0;
	int j = 0;

	while (j<strlen(s)) {
		if (strstr(s+j, find) == s+j){
			strncpy(&s[i], replace,strlen(replace));
			i += strlen(replace);
			j += strlen(find);
		} else {
			s[i] = s[j];
			i++;
			j++;
		}
	}
	s[i] = '\0';

	return s;
}

int totalLength(char list[128][24], int num){
	int len=0;
	for(int i=0;i<num;i++){
		len+=strlen(list[i]);
	}
	return len;
}

int totalLength(char list[73][20], int num){
	int len=0;
	for(int i=0;i<num;i++){
		len+=strlen(list[i]);
	}
	return len;
}


HINSTANCE hInst;
HWND hwnd;
HDC hdc,memdc,bmpdc,tmpdc;
HBITMAP hbit,bbit,tbit;

HDC gdc;
HBITMAP gbit;
HPEN border,selborder,grid;
HBRUSH node,selnode,bgbr;
HBITMAP clip;
HDC clipdc;

void toClipboard(char * text) {
	if (!text || !strlen(text))return;


	if (!OpenClipboard(hwnd))return;
	EmptyClipboard();

	HGLOBAL hglbCopy;
	LPTSTR  lptstrCopy;

	hglbCopy = GlobalAlloc(GMEM_MOVEABLE, (strlen(text) + 1) * sizeof(TCHAR));
	if (hglbCopy == NULL) {
		CloseClipboard();
		return;
	}


	lptstrCopy = (LPTSTR)GlobalLock(hglbCopy);

	memcpy(lptstrCopy, text,
		strlen(text) * sizeof(TCHAR));
	lptstrCopy[strlen(text)] = (TCHAR)0;   

	GlobalUnlock(hglbCopy);

	
	SetClipboardData(CF_TEXT, hglbCopy);
	CloseClipboard();
}

void fromClipboard(char * text, int lim=256) {
	HGLOBAL   hglb;
	LPTSTR    lptstr;

	if (!IsClipboardFormatAvailable(CF_TEXT))
		return;

	if (!OpenClipboard(hwnd))
		return;

	hglb = GetClipboardData(CF_TEXT);
	if (hglb != NULL) {
		lptstr = (LPTSTR)GlobalLock(hglb);
		if (lptstr != NULL) {
			strncpy(text, lptstr, lim);
			text[lim-1] = 0;
			//sprintf(text, lptstr);

			GlobalUnlock(hglb);
		}
	}

	CloseClipboard();
}

HBITMAP left,left2,mid,checkon,checkoff,pencil,pencilon,eraser,eraseron,zoom,uparrow,downarrow;
HBITMAP one,oneon,two,twoon,four,fouron,plus,minus,dots,next,prev,search,special,deleteicon,down;
HBITMAP rate[4],rateon[4];
HBITMAP chara,charaon,magic,magicon,item,itemon,monster,monsteron,spell,spellon,font,fonton,port,porton, anim, animon;
HBITMAP battle,battleon,shop,shopon,map,mapon,classi,classon,tile,tileon,chest,cheston,bg,bgon,sprite,spriteon,highlight;
HBITMAP mech,mechon,effect,effecton,range,rangeon,palette,paletteon,text,texton, gfx, gfxon, plat, platon, script, scripton, list, liston;
HBITMAP moveleft, moveup, moveright, movedown, moveadd;
HBITMAP areas;
HRSRC	asmtemp;
char*	rangeasm;
int		rangesize;
char*	areaasm;
int		areasize;
char*	chestasm;
int		chestsize;
char*	readasm;
int		readsize;

HBITMAP tileset[32];
int select[256];

int mode=0;
int submode[256];
int copysource[256][32];
int subselect[256][256];
long romsize=0;
int sizesel=-1;
void DrawToolbar();
void GetSize(char *);


bool Pencil=true;
bool cursor=true;
bool showlen=false;
int mainframe = 0;
int subframe = 0;
int color=0;
int menu=0;
int submenu=0;
int size=1;
char file[256];
char filepath[256];
char recentfile[5][256];
char inipath[256];
char searchtext[32];
int maxx=GetSystemMetrics(SM_CXSCREEN);
int maxy=GetSystemMetrics(SM_CYSCREEN);
int dwidth=0;
int dheight=0;
int bwidth=0;
int bheight=0;
int focus=0;
int lastfocus=0;
bool editneg=false;
int subfocus=-1;
int lastsubfocus=-1;
int curtiles=0;
int curtiles2=3;

char EditorDirectory[512];

bool ignoremouse = false;
bool ignorerelease = false;
bool ldown = false;

int searchtype=-1;
int searchstart=-1;
bool searchmet;
bool searchmulti = false;

BITMAPINFOHEADER bi;

char Atts[8][10] = {"ATT","DEF","AGI","MOVE","ATT/CRIT","ATT/DEF","YGRT","NONE"};
char Ranges[48][16] = {"1","2-3","2","1-2","1A","1-2A","1-3A","1A","1-3A Area 5","1-3A Area 14","1-3A Area 14","Party","1A","1A","1A","1-2","1-3A","1-2","1-2A","1-2","1-2","1-2 Area 5","1-2 Area 5","1-2","1-2","1-2 Area 5","2-3 Area 5","2-3","1-2 Area 5","1-3 Area 14","1-3 Area 14","1-3","1-2","1-2 Area 5","Egress","Nothing","1-2","1","Laser Eye","1-2","1-3 Area 5","1-3 Area 14","1-2","1A","1A","Level Party","1-2A Area 5","1-2 Area 5"};
char RangeTypes[19][16] = {"None","1","2","1-2","1-3","2-3","1-2 Area 5","2-3 Area 5","1-3 Area 14","1A","1-2A","1-3A","1-2A Area 5","1-3A Area 5","1-3A Area 14","Party","Egress","Laser Eye","Level Party"};
int RangeVals[19] = {239,0,2,3,31,1,21,26,29,4,5,6,46,8,9,11,34,38,45};

bool ExpandedGraphics = false;

#include "loadtext.h"
#include "savetext.h"

#include "LinkedList.h"
#include "Pair.h"
#include "String.h"
#include "ScriptBuilder.h"

#include "BytePair.h" 
#include "SingleBit.h" 
#include "UpperLevel.h" 
#include "Pixel.h" 

unsigned char NumItems = 64;
long EffectOffset;

bool ScriptsLoaded = false;

#define NUM_DIALOG	35
#define NUM_BE		30
#define NUM_BEXIT	8
#define NUM_CS	8
#define NUM_BS	30
#define NUM_WC	5

void FromClipboard(unsigned char * data, unsigned int size[2], unsigned char pal[16][3], bool tileset = false, bool weapon = false, bool resize=false, bool recolor=false);
void ToClipboard(unsigned char * data, unsigned int size[2], unsigned char pal[16][3], bool tileset = false, bool weapon = false);

#include "AdvancedNodes.h"
#include "loadpalettes.h"
#include "savepalette.h"
#include "loadspell.h"
#include "savespell.h"
#include "loaditem.h"
#include "saveitem.h"
#include "loadbattle.h"
#include "savebattle.h"
#include "loadfont.h"
#include "savefont.h"
#include "loadshop.h"
#include "saveshop.h"
#include "loadmonster.h"
#include "savemonster.h"
#include "loadmap.h"
#include "savemap.h"
#include "mapclickfunc.h"
#include "loadclass.h"
#include "saveclass.h"
#include "loadtile.h"
#include "savetile.h"
#include "loadmech.h"
#include "savemech.h"
#include "loadeffect.h"
#include "saveeffect.h"
#include "loadrange.h"
#include "saverange.h"
#include "loadgfx.h"
#include "savegfx.h"
#include "loadchar.h"
#include "savechar.h"
#include "DialogGraph.h"
#include "BEGraph.h"
#include "BExitGraph.h"
#include "CSGraph.h"
#include "BSGraph.h"
#include "WCGraph.h"
#include "LoadDialog.h"
#include "LoadBattleEnd.h"
#include "LoadBExit.h"
#include "LoadCS.h"
#include "LoadBS.h"
#include "LoadWC.h"
#include "SaveDialog.h"
#include "SaveBattleEnd.h"
#include "SaveBExit.h"
#include "SaveCS.h"
#include "SaveBS.h"
#include "SaveWC.h"
#include "loadanim.h"
#include "saveanim.h"

#include "loaddebug.h"

#include "Randomizer.h"





int findMenuItem(HMENU menu, char * text) {
	int nCnt = GetMenuItemCount(menu);
	char label[256];

	for (int i = 0; i < nCnt; i++) {
		GetMenuString(menu, i,label,256, MF_BYPOSITION);
		if (!strcmp(text,label))return i;
	} 

	return -1;
}

void updateMenuRecent() {
	HMENU menu = GetMenu(hwnd);
	if (!menu)return;

	//file menu
	menu = GetSubMenu(menu, 0);
	if (!menu)return;

	int recentPos = findMenuItem(menu, "Recent Files");
	if (recentPos == -1)return;


	menu = GetSubMenu(menu, recentPos);
	if (!menu)return;

	for (int i = 0;i < 5;i++) {
		ModifyMenu(menu, i,MF_STRING | MF_BYPOSITION, IDM_RECENT_FILE1 + i, recentfile[i]);
	}
}

void addRecentFile(char * path) {
	bool match = false;
	for (int i = 0;i < 5;i++) {
		if (!strcmp(path, recentfile[i])) {
			for (int j = i;j >= 1;j--) {
				sprintf(recentfile[j], recentfile[j - 1]);
			}
			sprintf(recentfile[0], path);
			match = true;
			break;
		}
	}
	if (!match) {
		for (int j = 4;j >= 1;j--) {
			sprintf(recentfile[j], recentfile[j - 1]);
		}
		sprintf(recentfile[0], path);
	}

	updateMenuRecent();

	WritePrivateProfileString("recent", "file1", recentfile[0], inipath);
	WritePrivateProfileString("recent", "file2", recentfile[1], inipath);
	WritePrivateProfileString("recent", "file3", recentfile[2], inipath);
	WritePrivateProfileString("recent", "file4", recentfile[3], inipath);
	WritePrivateProfileString("recent", "file5", recentfile[4], inipath);
}

void init(){
	memset(select,0,256*sizeof(int));
	memset(submode,0,256*sizeof(int));
	memset(subselect,0,256*256*sizeof(int));

	GetCurrentDirectory(512, EditorDirectory);
	sprintf(inipath, "%s\\SF1Edit.ini", EditorDirectory);

	char temp[256];

	GetPrivateProfileString("settings", "showbg", "", temp, 256, inipath);
	if (!strcmp(temp, "0"))GFXBG = false;

	submode[8] = 2;

	subselect[17][6] = 17;

	int i;
	for(i=0;i<8713;i++){
		for(int j=0;j<18;j++){
			if(j%2==0)Tiles[i][j]=3;
			else Tiles[i][j]=0xBE;
		}
	}

	for(i=0;i<172;i++){
		for(int j=0;j<64;j++){
			SpriteScripts[i][j]=0x19;
		}
	}

	for(i=0;i<256;i++){
		for(int j=0;j<32;j++){
			copysource[i][j]=-1;
		}
	}

	for(i=0;i<80;i++){
		AnimSets[i][0]=0;
		AnimSets[i][1]=0xFF;
		AnimSets[i][2]=0xFF;
	}

	initDialog();
	initBE();
	initBExit();
	initCS();
	initBS();
	initWC();

	left=(HBITMAP)LoadImage(hInst,MAKEINTRESOURCE(LEFT),IMAGE_BITMAP,0,0,LR_DEFAULTSIZE);
	left2=(HBITMAP)LoadImage(hInst,MAKEINTRESOURCE(LEFT2),IMAGE_BITMAP,0,0,LR_DEFAULTSIZE);
	mid=(HBITMAP)LoadImage(hInst,MAKEINTRESOURCE(MID),IMAGE_BITMAP,0,0,LR_DEFAULTSIZE);
	checkon=(HBITMAP)LoadImage(hInst,MAKEINTRESOURCE(CHECKON),IMAGE_BITMAP,0,0,LR_DEFAULTSIZE);
	checkoff=(HBITMAP)LoadImage(hInst,MAKEINTRESOURCE(CHECKOFF),IMAGE_BITMAP,0,0,LR_DEFAULTSIZE);
	pencilon=(HBITMAP)LoadImage(hInst,MAKEINTRESOURCE(PENCILON),IMAGE_BITMAP,0,0,LR_DEFAULTSIZE);
	pencil=(HBITMAP)LoadImage(hInst,MAKEINTRESOURCE(PENCIL),IMAGE_BITMAP,0,0,LR_DEFAULTSIZE);
	eraseron=(HBITMAP)LoadImage(hInst,MAKEINTRESOURCE(ERASERON),IMAGE_BITMAP,0,0,LR_DEFAULTSIZE);
	eraser=(HBITMAP)LoadImage(hInst,MAKEINTRESOURCE(ERASER),IMAGE_BITMAP,0,0,LR_DEFAULTSIZE);
	oneon=(HBITMAP)LoadImage(hInst,MAKEINTRESOURCE(ONEON),IMAGE_BITMAP,0,0,LR_DEFAULTSIZE);
	one=(HBITMAP)LoadImage(hInst,MAKEINTRESOURCE(ONE),IMAGE_BITMAP,0,0,LR_DEFAULTSIZE);
	twoon=(HBITMAP)LoadImage(hInst,MAKEINTRESOURCE(TWOON),IMAGE_BITMAP,0,0,LR_DEFAULTSIZE);
	two=(HBITMAP)LoadImage(hInst,MAKEINTRESOURCE(TWO),IMAGE_BITMAP,0,0,LR_DEFAULTSIZE);
	fouron=(HBITMAP)LoadImage(hInst,MAKEINTRESOURCE(FOURON),IMAGE_BITMAP,0,0,LR_DEFAULTSIZE);
	four=(HBITMAP)LoadImage(hInst,MAKEINTRESOURCE(FOUR),IMAGE_BITMAP,0,0,LR_DEFAULTSIZE);
	plus=(HBITMAP)LoadImage(hInst,MAKEINTRESOURCE(PLUS),IMAGE_BITMAP,0,0,LR_DEFAULTSIZE);
	minus=(HBITMAP)LoadImage(hInst,MAKEINTRESOURCE(MINUS),IMAGE_BITMAP,0,0,LR_DEFAULTSIZE);
	dots=(HBITMAP)LoadImage(hInst,MAKEINTRESOURCE(DOTS),IMAGE_BITMAP,0,0,LR_DEFAULTSIZE);
	next=(HBITMAP)LoadImage(hInst,MAKEINTRESOURCE(NEXT),IMAGE_BITMAP,0,0,LR_DEFAULTSIZE);
	prev=(HBITMAP)LoadImage(hInst,MAKEINTRESOURCE(PREV),IMAGE_BITMAP,0,0,LR_DEFAULTSIZE);
	rate[0]=(HBITMAP)LoadImage(hInst,MAKEINTRESOURCE(RATE),IMAGE_BITMAP,0,0,LR_DEFAULTSIZE);
	rate[1]=(HBITMAP)LoadImage(hInst,MAKEINTRESOURCE(RATE2),IMAGE_BITMAP,0,0,LR_DEFAULTSIZE);
	rate[3]=(HBITMAP)LoadImage(hInst,MAKEINTRESOURCE(RATE3),IMAGE_BITMAP,0,0,LR_DEFAULTSIZE);
	rate[2]=(HBITMAP)LoadImage(hInst,MAKEINTRESOURCE(RATE4),IMAGE_BITMAP,0,0,LR_DEFAULTSIZE);
	rateon[0]=(HBITMAP)LoadImage(hInst,MAKEINTRESOURCE(RATEON),IMAGE_BITMAP,0,0,LR_DEFAULTSIZE);
	rateon[1]=(HBITMAP)LoadImage(hInst,MAKEINTRESOURCE(RATE2ON),IMAGE_BITMAP,0,0,LR_DEFAULTSIZE);
	rateon[3]=(HBITMAP)LoadImage(hInst,MAKEINTRESOURCE(RATE3ON),IMAGE_BITMAP,0,0,LR_DEFAULTSIZE);
	rateon[2]=(HBITMAP)LoadImage(hInst,MAKEINTRESOURCE(RATE4ON),IMAGE_BITMAP,0,0,LR_DEFAULTSIZE);
	chara=(HBITMAP)LoadImage(hInst,MAKEINTRESOURCE(CHARA),IMAGE_BITMAP,0,0,LR_DEFAULTSIZE);
	charaon=(HBITMAP)LoadImage(hInst,MAKEINTRESOURCE(CHARAON),IMAGE_BITMAP,0,0,LR_DEFAULTSIZE);
	magic=(HBITMAP)LoadImage(hInst,MAKEINTRESOURCE(MAGIC),IMAGE_BITMAP,0,0,LR_DEFAULTSIZE);
	magicon=(HBITMAP)LoadImage(hInst,MAKEINTRESOURCE(MAGICON),IMAGE_BITMAP,0,0,LR_DEFAULTSIZE);
	item=(HBITMAP)LoadImage(hInst,MAKEINTRESOURCE(ITEM),IMAGE_BITMAP,0,0,LR_DEFAULTSIZE);
	itemon=(HBITMAP)LoadImage(hInst,MAKEINTRESOURCE(ITEMON),IMAGE_BITMAP,0,0,LR_DEFAULTSIZE);
	monster=(HBITMAP)LoadImage(hInst,MAKEINTRESOURCE(MONSTER),IMAGE_BITMAP,0,0,LR_DEFAULTSIZE);
	monsteron=(HBITMAP)LoadImage(hInst,MAKEINTRESOURCE(MONSTERON),IMAGE_BITMAP,0,0,LR_DEFAULTSIZE);
	spell=(HBITMAP)LoadImage(hInst,MAKEINTRESOURCE(SPELL),IMAGE_BITMAP,0,0,LR_DEFAULTSIZE);
	spellon=(HBITMAP)LoadImage(hInst,MAKEINTRESOURCE(SPELLON),IMAGE_BITMAP,0,0,LR_DEFAULTSIZE);
	list = (HBITMAP)LoadImage(hInst, MAKEINTRESOURCE(LIST), IMAGE_BITMAP, 0, 0, LR_DEFAULTSIZE);
	liston = (HBITMAP)LoadImage(hInst, MAKEINTRESOURCE(LISTON), IMAGE_BITMAP, 0, 0, LR_DEFAULTSIZE);
	font=(HBITMAP)LoadImage(hInst,MAKEINTRESOURCE(FONT),IMAGE_BITMAP,0,0,LR_DEFAULTSIZE);
	fonton=(HBITMAP)LoadImage(hInst,MAKEINTRESOURCE(FONTON),IMAGE_BITMAP,0,0,LR_DEFAULTSIZE);
	battle=(HBITMAP)LoadImage(hInst,MAKEINTRESOURCE(BATTLE),IMAGE_BITMAP,0,0,LR_DEFAULTSIZE);
	battleon=(HBITMAP)LoadImage(hInst,MAKEINTRESOURCE(BATTLEON),IMAGE_BITMAP,0,0,LR_DEFAULTSIZE);
	shop=(HBITMAP)LoadImage(hInst,MAKEINTRESOURCE(SHOP),IMAGE_BITMAP,0,0,LR_DEFAULTSIZE);
	shopon=(HBITMAP)LoadImage(hInst,MAKEINTRESOURCE(SHOPON),IMAGE_BITMAP,0,0,LR_DEFAULTSIZE);
	map=(HBITMAP)LoadImage(hInst,MAKEINTRESOURCE(MAP),IMAGE_BITMAP,0,0,LR_DEFAULTSIZE);
	mapon=(HBITMAP)LoadImage(hInst,MAKEINTRESOURCE(MAPON),IMAGE_BITMAP,0,0,LR_DEFAULTSIZE);
	highlight=(HBITMAP)LoadImage(hInst,MAKEINTRESOURCE(HIGHLIGHT),IMAGE_BITMAP,0,0,LR_DEFAULTSIZE);
	classi=(HBITMAP)LoadImage(hInst,MAKEINTRESOURCE(CLASSI),IMAGE_BITMAP,0,0,LR_DEFAULTSIZE);
	classon=(HBITMAP)LoadImage(hInst,MAKEINTRESOURCE(CLASSON),IMAGE_BITMAP,0,0,LR_DEFAULTSIZE);
	tile=(HBITMAP)LoadImage(hInst,MAKEINTRESOURCE(TILE),IMAGE_BITMAP,0,0,LR_DEFAULTSIZE);
	tileon=(HBITMAP)LoadImage(hInst,MAKEINTRESOURCE(TILEON),IMAGE_BITMAP,0,0,LR_DEFAULTSIZE);
	chest=(HBITMAP)LoadImage(hInst,MAKEINTRESOURCE(CHEST),IMAGE_BITMAP,0,0,LR_DEFAULTSIZE);
	cheston=(HBITMAP)LoadImage(hInst,MAKEINTRESOURCE(CHESTON),IMAGE_BITMAP,0,0,LR_DEFAULTSIZE);
	mech=(HBITMAP)LoadImage(hInst,MAKEINTRESOURCE(MECH),IMAGE_BITMAP,0,0,LR_DEFAULTSIZE);
	mechon=(HBITMAP)LoadImage(hInst,MAKEINTRESOURCE(MECHON),IMAGE_BITMAP,0,0,LR_DEFAULTSIZE);
	effect=(HBITMAP)LoadImage(hInst,MAKEINTRESOURCE(EFFECT),IMAGE_BITMAP,0,0,LR_DEFAULTSIZE);
	effecton=(HBITMAP)LoadImage(hInst,MAKEINTRESOURCE(EFFECTON),IMAGE_BITMAP,0,0,LR_DEFAULTSIZE);
	range=(HBITMAP)LoadImage(hInst,MAKEINTRESOURCE(RANGE),IMAGE_BITMAP,0,0,LR_DEFAULTSIZE);
	rangeon=(HBITMAP)LoadImage(hInst,MAKEINTRESOURCE(RANGEON),IMAGE_BITMAP,0,0,LR_DEFAULTSIZE);
	palette=(HBITMAP)LoadImage(hInst,MAKEINTRESOURCE(PALETTE),IMAGE_BITMAP,0,0,LR_DEFAULTSIZE);
	paletteon=(HBITMAP)LoadImage(hInst,MAKEINTRESOURCE(PALETTEON),IMAGE_BITMAP,0,0,LR_DEFAULTSIZE);
	text=(HBITMAP)LoadImage(hInst,MAKEINTRESOURCE(TEXTIMG),IMAGE_BITMAP,0,0,LR_DEFAULTSIZE);
	texton=(HBITMAP)LoadImage(hInst,MAKEINTRESOURCE(TEXTON),IMAGE_BITMAP,0,0,LR_DEFAULTSIZE);
	gfx=(HBITMAP)LoadImage(hInst,MAKEINTRESOURCE(GFX),IMAGE_BITMAP,0,0,LR_DEFAULTSIZE);
	gfxon=(HBITMAP)LoadImage(hInst,MAKEINTRESOURCE(GFXON),IMAGE_BITMAP,0,0,LR_DEFAULTSIZE);
	bg=(HBITMAP)LoadImage(hInst,MAKEINTRESOURCE(BG),IMAGE_BITMAP,0,0,LR_DEFAULTSIZE);
	bgon=(HBITMAP)LoadImage(hInst,MAKEINTRESOURCE(BGON),IMAGE_BITMAP,0,0,LR_DEFAULTSIZE);
	plat=(HBITMAP)LoadImage(hInst,MAKEINTRESOURCE(PLAT),IMAGE_BITMAP,0,0,LR_DEFAULTSIZE);
	platon=(HBITMAP)LoadImage(hInst,MAKEINTRESOURCE(PLATON),IMAGE_BITMAP,0,0,LR_DEFAULTSIZE);
	port=(HBITMAP)LoadImage(hInst,MAKEINTRESOURCE(PORTRAIT),IMAGE_BITMAP,0,0,LR_DEFAULTSIZE);
	porton=(HBITMAP)LoadImage(hInst,MAKEINTRESOURCE(PORTRAITON),IMAGE_BITMAP,0,0,LR_DEFAULTSIZE);
	sprite=(HBITMAP)LoadImage(hInst,MAKEINTRESOURCE(SPRITE),IMAGE_BITMAP,0,0,LR_DEFAULTSIZE);
	spriteon=(HBITMAP)LoadImage(hInst,MAKEINTRESOURCE(SPRITEON),IMAGE_BITMAP,0,0,LR_DEFAULTSIZE);
	script=(HBITMAP)LoadImage(hInst,MAKEINTRESOURCE(SCRIPT),IMAGE_BITMAP,0,0,LR_DEFAULTSIZE);
	scripton=(HBITMAP)LoadImage(hInst,MAKEINTRESOURCE(SCRIPTON),IMAGE_BITMAP,0,0,LR_DEFAULTSIZE);
	anim=(HBITMAP)LoadImage(hInst,MAKEINTRESOURCE(ANIM),IMAGE_BITMAP,0,0,LR_DEFAULTSIZE);
	animon=(HBITMAP)LoadImage(hInst,MAKEINTRESOURCE(ANIMON),IMAGE_BITMAP,0,0,LR_DEFAULTSIZE);
	search=(HBITMAP)LoadImage(hInst,MAKEINTRESOURCE(SEARCH),IMAGE_BITMAP,0,0,LR_DEFAULTSIZE);
	special=(HBITMAP)LoadImage(hInst,MAKEINTRESOURCE(SPECIAL),IMAGE_BITMAP,0,0,LR_DEFAULTSIZE);
	deleteicon=(HBITMAP)LoadImage(hInst,MAKEINTRESOURCE(DELETEICON),IMAGE_BITMAP,0,0,LR_DEFAULTSIZE);
	zoom=(HBITMAP)LoadImage(hInst,MAKEINTRESOURCE(ZOOM),IMAGE_BITMAP,0,0,LR_DEFAULTSIZE);
	down=(HBITMAP)LoadImage(hInst,MAKEINTRESOURCE(DOWN),IMAGE_BITMAP,0,0,LR_DEFAULTSIZE);
	downarrow=(HBITMAP)LoadImage(hInst,MAKEINTRESOURCE(DOWNARROW),IMAGE_BITMAP,0,0,LR_DEFAULTSIZE);
	uparrow=(HBITMAP)LoadImage(hInst,MAKEINTRESOURCE(UPARROW),IMAGE_BITMAP,0,0,LR_DEFAULTSIZE);
	areas = (HBITMAP)LoadImage(hInst, MAKEINTRESOURCE(AREAS), IMAGE_BITMAP, 0, 0, LR_DEFAULTSIZE);
	moveleft = (HBITMAP)LoadImage(hInst, MAKEINTRESOURCE(MOVELEFT), IMAGE_BITMAP, 0, 0, LR_DEFAULTSIZE);
	moveup = (HBITMAP)LoadImage(hInst, MAKEINTRESOURCE(MOVEUP), IMAGE_BITMAP, 0, 0, LR_DEFAULTSIZE);
	moveright = (HBITMAP)LoadImage(hInst, MAKEINTRESOURCE(MOVERIGHT), IMAGE_BITMAP, 0, 0, LR_DEFAULTSIZE);
	movedown = (HBITMAP)LoadImage(hInst, MAKEINTRESOURCE(MOVEDOWN), IMAGE_BITMAP, 0, 0, LR_DEFAULTSIZE);
	moveadd = (HBITMAP)LoadImage(hInst, MAKEINTRESOURCE(MOVEADD), IMAGE_BITMAP, 0, 0, LR_DEFAULTSIZE);

	asmtemp = FindResource(hInst,MAKEINTRESOURCE(RANGEASM),RT_RCDATA); 
	rangeasm = (char*)LockResource(LoadResource(hInst,asmtemp));
	rangesize = SizeofResource(hInst,asmtemp);
	asmtemp = FindResource(hInst,MAKEINTRESOURCE(AREAASM),RT_RCDATA); 
	areaasm = (char*)LockResource(LoadResource(hInst,asmtemp));
	areasize = SizeofResource(hInst,asmtemp);
	asmtemp = FindResource(hInst,MAKEINTRESOURCE(IDR_DATA1),RT_RCDATA); 
	chestasm = (char*)LockResource(LoadResource(hInst,asmtemp));
	chestsize = SizeofResource(hInst,asmtemp);
	asmtemp = FindResource(hInst,MAKEINTRESOURCE(IDR_DATA2),RT_RCDATA); 
	readasm = (char*)LockResource(LoadResource(hInst,asmtemp));
	readsize = SizeofResource(hInst,asmtemp);

	tileset[0]=(HBITMAP)LoadImage(hInst,MAKEINTRESOURCE(TILESET1),IMAGE_BITMAP,0,0,LR_DEFAULTSIZE);
	tileset[1]=(HBITMAP)LoadImage(hInst,MAKEINTRESOURCE(TILESET2),IMAGE_BITMAP,0,0,LR_DEFAULTSIZE);
	tileset[2]=(HBITMAP)LoadImage(hInst,MAKEINTRESOURCE(TILESET3),IMAGE_BITMAP,0,0,LR_DEFAULTSIZE);
	tileset[3]=(HBITMAP)LoadImage(hInst,MAKEINTRESOURCE(TILESET4),IMAGE_BITMAP,0,0,LR_DEFAULTSIZE);
	tileset[4]=(HBITMAP)LoadImage(hInst,MAKEINTRESOURCE(TILESET5),IMAGE_BITMAP,0,0,LR_DEFAULTSIZE);
	tileset[5]=(HBITMAP)LoadImage(hInst,MAKEINTRESOURCE(TILESET6),IMAGE_BITMAP,0,0,LR_DEFAULTSIZE);
	tileset[6]=(HBITMAP)LoadImage(hInst,MAKEINTRESOURCE(TILESET7),IMAGE_BITMAP,0,0,LR_DEFAULTSIZE);
	tileset[7]=(HBITMAP)LoadImage(hInst,MAKEINTRESOURCE(TILESET8),IMAGE_BITMAP,0,0,LR_DEFAULTSIZE);
	tileset[8]=(HBITMAP)LoadImage(hInst,MAKEINTRESOURCE(TILESET9),IMAGE_BITMAP,0,0,LR_DEFAULTSIZE);
	tileset[9]=(HBITMAP)LoadImage(hInst,MAKEINTRESOURCE(TILESET10),IMAGE_BITMAP,0,0,LR_DEFAULTSIZE);
	tileset[10]=(HBITMAP)LoadImage(hInst,MAKEINTRESOURCE(TILESET11),IMAGE_BITMAP,0,0,LR_DEFAULTSIZE);
	tileset[11]=(HBITMAP)LoadImage(hInst,MAKEINTRESOURCE(TILESET12),IMAGE_BITMAP,0,0,LR_DEFAULTSIZE);
	tileset[12]=(HBITMAP)LoadImage(hInst,MAKEINTRESOURCE(TILESET13),IMAGE_BITMAP,0,0,LR_DEFAULTSIZE);
	tileset[13]=(HBITMAP)LoadImage(hInst,MAKEINTRESOURCE(TILESET14),IMAGE_BITMAP,0,0,LR_DEFAULTSIZE);
	tileset[14]=(HBITMAP)LoadImage(hInst,MAKEINTRESOURCE(TILESET15),IMAGE_BITMAP,0,0,LR_DEFAULTSIZE);
	tileset[15]=(HBITMAP)LoadImage(hInst,MAKEINTRESOURCE(TILESET16),IMAGE_BITMAP,0,0,LR_DEFAULTSIZE);
	tileset[16]=(HBITMAP)LoadImage(hInst,MAKEINTRESOURCE(TILESET17),IMAGE_BITMAP,0,0,LR_DEFAULTSIZE);
	tileset[17]=(HBITMAP)LoadImage(hInst,MAKEINTRESOURCE(TILESET18),IMAGE_BITMAP,0,0,LR_DEFAULTSIZE);
	tileset[18]=(HBITMAP)LoadImage(hInst,MAKEINTRESOURCE(TILESET19),IMAGE_BITMAP,0,0,LR_DEFAULTSIZE);
	tileset[19]=(HBITMAP)LoadImage(hInst,MAKEINTRESOURCE(TILESET20),IMAGE_BITMAP,0,0,LR_DEFAULTSIZE);
	tileset[20]=(HBITMAP)LoadImage(hInst,MAKEINTRESOURCE(TILESET21),IMAGE_BITMAP,0,0,LR_DEFAULTSIZE);
	tileset[21]=(HBITMAP)LoadImage(hInst,MAKEINTRESOURCE(TILESET22),IMAGE_BITMAP,0,0,LR_DEFAULTSIZE);
	tileset[22]=(HBITMAP)LoadImage(hInst,MAKEINTRESOURCE(TILESET23),IMAGE_BITMAP,0,0,LR_DEFAULTSIZE);
	tileset[23]=(HBITMAP)LoadImage(hInst,MAKEINTRESOURCE(TILESET24),IMAGE_BITMAP,0,0,LR_DEFAULTSIZE);
	tileset[24]=(HBITMAP)LoadImage(hInst,MAKEINTRESOURCE(TILESET25),IMAGE_BITMAP,0,0,LR_DEFAULTSIZE);
	tileset[25]=(HBITMAP)LoadImage(hInst,MAKEINTRESOURCE(TILESET26),IMAGE_BITMAP,0,0,LR_DEFAULTSIZE);
	tileset[26]=(HBITMAP)LoadImage(hInst,MAKEINTRESOURCE(TILESET27),IMAGE_BITMAP,0,0,LR_DEFAULTSIZE);
	tileset[27]=(HBITMAP)LoadImage(hInst,MAKEINTRESOURCE(TILESET28),IMAGE_BITMAP,0,0,LR_DEFAULTSIZE);
	tileset[28]=(HBITMAP)LoadImage(hInst,MAKEINTRESOURCE(TILESET29),IMAGE_BITMAP,0,0,LR_DEFAULTSIZE);
	tileset[29]=(HBITMAP)LoadImage(hInst,MAKEINTRESOURCE(TILESET30),IMAGE_BITMAP,0,0,LR_DEFAULTSIZE);
	tileset[30]=(HBITMAP)LoadImage(hInst,MAKEINTRESOURCE(TILESET31),IMAGE_BITMAP,0,0,LR_DEFAULTSIZE);
	tileset[31]=(HBITMAP)LoadImage(hInst,MAKEINTRESOURCE(TILESET32),IMAGE_BITMAP,0,0,LR_DEFAULTSIZE);

	sprintf(file,"");
	sprintf(filepath, "");
	bi.biSize        = sizeof(BITMAPINFOHEADER);
	bi.biWidth       = 800;
	bi.biHeight      = 640;
	bi.biPlanes      = 1;
	bi.biBitCount    = 24;
	bi.biCompression = BI_RGB;
}

ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
	MSG msg;
	HACCEL hAccelTable;

	MyRegisterClass(hInstance);

	srand(time(0));

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow)) 
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, (LPCTSTR)IDC_FONTEDIT);

	GetPrivateProfileString("recent", "file1", "", recentfile[0], 256, inipath);
	GetPrivateProfileString("recent", "file2", "", recentfile[1], 256, inipath);
	GetPrivateProfileString("recent", "file3", "", recentfile[2], 256, inipath);
	GetPrivateProfileString("recent", "file4", "", recentfile[3], 256, inipath);
	GetPrivateProfileString("recent", "file5", "", recentfile[4], 256, inipath);

	updateMenuRecent();

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0)) 
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) 
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage is only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX); 

	wcex.style			= CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS ;
	wcex.lpfnWndProc	= (WNDPROC)WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, (LPCTSTR)IDI_FONTEDIT);
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= (LPCSTR)IDC_FONTEDIT;
	wcex.lpszClassName	= "Window";
	wcex.hIconSm		= LoadIcon(wcex.hInstance, (LPCTSTR)IDI_SMALL);

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HANDLE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable

   char tmp[32];
   sprintf(tmp, "Shining Force Editor v%s", version);

   hWnd = CreateWindow("Window", tmp, WS_OVERLAPPEDWINDOW,
      (maxx-800)/2, (maxy-640)/2, 800, 640, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }
   hwnd = hWnd;
   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

void Import(){
	switch(mode){
		case 0:
		case 1:
			CharImport();
			break;
		case 2:
			ItemImport();
			break;
		case 3:
			MonsterImport();
			break;
		case 4:
			SpellImport();
			break;
		case 5:
			BattleImport();
			break;
		case 6:
			FontImport();
			break;
		case 7:
			ShopImport();
			break;
		case 8:
			MapImport();
			break;
		case 9:
			ClassImport();
			break;
		case 10:
			TileImport();
			break;
		case 11:
			MechImport();
			break;
		case 12:
			EffectImport();
			break;
		case 13:
			RangeImport();
			break;
		case 14:
			PaletteImport();
			break;
		case 15:
			TextImport();
			break;
		case 16:
			if(GraphicsLoaded)GFXImport();
			break;
	}
}

void Export(){
	switch(mode){
		case 0:
		case 1:
			CharExport();
			break;
		case 2:
			ItemExport();
			break;
		case 3:
			MonsterExport();
			break;
		case 4:
			SpellExport();
			break;
		case 5:
			BattleExport();
			break;
		case 6:
			FontExport();
			break;
		case 7:
			ShopExport();
			break;
		case 8:
			MapExport();
			break;
		case 9:
			ClassExport();
			break;
		case 10:
			TileExport();
			break;
		case 11:
			MechExport();
			break;
		case 12:
			EffectExport();
			break;
		case 13:
			RangeExport();
			break;
		case 14:
			PaletteExport();
			break;
		case 15:
			if(TextLoaded)TextExport();
			break;
		case 16:
			if(GraphicsLoaded)GFXExport();
			break;
	}
}

void OpenFile(char * in, bool load) {
	char path[256];
	sprintf(path, in);
	sprintf(filepath, path);

	addRecentFile(path);

	char title[512];

	int f = -1;
	for (int i = 0;i < strlen(filepath);i++) {
		if (filepath[i] == '\\')f = i;
	}
	filepath[f + 1] = 0;
	if (load) {
		GraphicsLoaded = false;
		ScriptsLoaded = false;

		GetSize(path);
		if (!romsize) {
			MessageBox(NULL, "File could not be opened.", "Error", MB_OK);
			return;
		}

		LoadMech(path);

		LoadGFX(path);
		LoadChar(path);
		LoadClass(path);
		LoadItem(path);
		LoadSpell(path);
		LoadFont(path);
		LoadShop(path);
		LoadMap(path);
		LoadBattle(path);

		LoadDialog(file);
		LoadBE(file);
		LoadBExit(file);
		LoadCS(file);
		LoadBS(file);
		LoadWC(file);

		LoadMonster(path);
		LoadTile(path);

		LoadEffect(path);
		LoadRange(path);
		LoadPalette(path);
		LoadText(path);
		LoadAnim(path);

	} else {
		GetSize(path);

		sprintf(file, path);
	}
	sprintf(title, "Shining Force Editor v%s - %s", version, path);
	SetWindowText(hwnd, title);
}

void Open(bool load=true){
	int ret=IDYES;
	OPENFILENAME openFileName;
	char path[512];
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
	if(!load)openFileName.lpstrTitle = "Change File";
	else openFileName.lpstrTitle = NULL;
	openFileName.Flags = OFN_LONGNAMES | OFN_PATHMUSTEXIST;
	openFileName.nFileOffset = 0;
	openFileName.nFileExtension = 0;
	openFileName.lpstrDefExt = "map";
	openFileName.lCustData = NULL;
	openFileName.lpfnHook = NULL;
	openFileName.lpTemplateName = NULL;



	menu=0;

	ignoremouse = true;

	if(GetOpenFileName(&openFileName)!=0){
		OpenFile(path, load);
	}
	ignoremouse = false;
}

void Save(){
	switch(mode){
	case 0:
	case 1:
		SaveChar();
		break;
	case 2:
		SaveItem();
		break;
	case 3:
		SaveClass();
		SaveMonster();
		break;
	case 4:
		SaveSpell();
		break;
	case 105:
	case 5:
		SaveBattle();
		break;
	case 6:
		SaveFont();
		break;
	case 7:
		SaveShop();
		break;
	case 8:
		SaveMap();
		break;
	case 9:
		SaveClass();
		SaveMonster();
		break;
	case 10:
		SaveTile();
		break;
	case 11:
		SaveMech();
		break;
	case 12:
		SaveEffect();
		break;
	case 13:
		SaveRange();
		break;
	case 14:
		SavePalette();
		break;
	case 15:
		SaveText();
		break;
	case 16:
		SaveGFX();
		break;
	case 17:
		SaveAnim();
		break;
	case 18:
		switch(submode[mode]){
			case 0:
				SaveDialog();
				break;
			case 1:
				SaveBE();
				break;
			case 2:
				SaveBExit();
				break;
			case 3:
				SaveCS();
				break;
			case 4:
				SaveBS();
				break;
			case 5:
				SaveWC();
				break;
		}
		break;
	}
}

void OpenSingle(){
	switch(mode){
	case 0:
	case 1:
		LoadChar(file,true);
		break;
	case 2:
		LoadItem(file,true);
		break;
	case 3:
		LoadMonster(file,true);
		break;
	case 4:
		LoadSpell(file,true);
		break;
	case 105:
	case 5:
		LoadBattle(file,true);
		break;
	case 6:
		LoadFont(file,true);
		break;
	case 7:
		LoadShop(file,true);
		break;
	case 8:
		LoadMap(file,true);
		break;
	case 9:
		LoadClass(file,true);
		break;
	case 10:
		LoadTile(file,true);
		break;
	case 11:
		MessageBox(NULL,"Not applicable for this editor.","Note",MB_OK);
		break;
	case 12:
		LoadEffect(file,true);
		break;
	case 13:
		LoadRange(file,true);
		break;
	case 14:
		MessageBox(NULL,"Not applicable for this editor.","Note",MB_OK);
		break;
	case 15:
		LoadText(file,true,true);
		break;
	case 16:
		LoadGFX(file,true);
		break;
	case 17:
		LoadAnim(file,true);
		break;
	case 18:
		switch(submode[mode]){
			case 0:
				LoadDialog(file,true);
				break;
			case 1:
				LoadBE(file,true);
				break;
			case 2:
				LoadBExit(file, true);
				break;
		}
		break;
	}
}

//
//  FUNCTION: WndProc(HWND, unsigned, WORD, LONG)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	int i,j,k,l,m,x,y,dx,dy,u,v,w,s,del;
	x=y=dx=dy=u=v=w=s=0;
	char out[1024];
	char temp[1024];
	char c;
	double d;
	long lo;
	short sh;
	unsigned char val;
	unsigned char width,height;
	POINT p,p2;
	RECT r;
	FILE * fp;
	HBRUSH brush;
	HPEN pen;
	switch (message) 
	{
		case WM_CLOSE:
			if (MessageBox(hWnd, "Are you sure you want to quit? Unsaved sections will be lost.", "Confirm", MB_YESNO) == IDNO)return 0;
			return DefWindowProc(hWnd, message, wParam, lParam);
		case WM_CREATE:
			hwnd = hWnd;
			hdc=GetDC(hWnd);
			memdc=CreateCompatibleDC(hdc);
			bmpdc=CreateCompatibleDC(hdc);
			tmpdc=CreateCompatibleDC(hdc);
			clipdc=CreateCompatibleDC(hdc);
			hbit=CreateCompatibleBitmap(hdc,maxx,maxy);
			bbit=CreateCompatibleBitmap(hdc,maxx,maxy);
			tbit=CreateCompatibleBitmap(hdc,maxx,maxy);
			SelectObject(memdc,hbit);
			SelectObject(bmpdc,bbit);
			SelectObject(tmpdc,tbit);
			SelectObject(memdc,CreateSolidBrush(RGB(128,128,128)));
			SelectObject(tmpdc,CreateSolidBrush(RGB(0,36,132)));
			SetBkMode(memdc, TRANSPARENT);

			gdc=CreateCompatibleDC(hdc);
			gbit=CreateCompatibleBitmap(hdc,GRAPHSIZE,GRAPHSIZE);
			while (!gbit && GRAPHSIZE > 1024) {
				GRAPHSIZE /= 2;
				gbit = CreateCompatibleBitmap(hdc, GRAPHSIZE, GRAPHSIZE);
			}
			SelectObject(gdc,gbit);
			SetBkMode(gdc, TRANSPARENT);
			bgbr = CreateSolidBrush(RGB(160,160,160));
			SelectObject(gdc,bgbr);
			border = CreatePen(PS_SOLID,2,RGB(60,60,60));
			selborder = CreatePen(PS_SOLID,2,RGB(80,80,220));
			SelectObject(gdc,border);

			grid = CreatePen(PS_SOLID,1,RGB(100,100,100));
			node = CreateSolidBrush(RGB(180,180,180));
			selnode = CreateSolidBrush(RGB(180,180,220));

			init();

			SetTimer(hWnd,0,40,NULL);
			break;
		case WM_GETMINMAXINFO:
			LPMINMAXINFO pMMI;
			pMMI = (LPMINMAXINFO)lParam;
			pMMI->ptMaxTrackSize.x = maxx;
			pMMI->ptMaxTrackSize.y = maxy;
			pMMI->ptMaxSize.x = maxx;
			pMMI->ptMaxSize.y = maxy;
			pMMI->ptMinTrackSize.x = 800;
			pMMI->ptMinTrackSize.y = 640;
			break;
		case WM_SIZE:
			u = LOWORD(lParam); 
			v = HIWORD(lParam);

			if(bwidth){
				dwidth = u - bwidth;
				dheight = v - bheight;
			} else {
				bwidth = u;
				bheight = v;
			}

			break;
		case WM_TIMER:
			if(mode!=16 && ((subframe % 6)==0 || mode==17))InvalidateRect(hWnd,NULL,0);

			if (subframe % 6 == 0) {
				mainframe++;
				if (mainframe % 2)cursor = !cursor;
				if (mainframe == 256)mainframe = 0;
			}

			subframe++;
			if (subframe == 1536)subframe = 0;
			

			

			break;
		case WM_COMMAND:
			wmId    = LOWORD(wParam); 
			wmEvent = HIWORD(wParam); 
			// Parse the menu selections:
			switch (wmId)
			{
				case IDM_RANDOM:
					if(MessageBox(NULL, "Are you sure you want to randomize character data?", "Confirm", MB_YESNO)==IDYES){
						Randomize();
						MessageBox(NULL, "Data randomized. Save in both Character and Spells Learned editors to commit changes.", "Note", MB_OK);
					}
					break;
				case IDM_OPEN:
					Open();
					InvalidateRect(hWnd,NULL,0);
					break;
				case IDM_RECENT_FILE1:
					if (strlen(recentfile[0]))OpenFile(recentfile[0], true);
					break;
				case IDM_RECENT_FILE2:
					if (strlen(recentfile[1]))OpenFile(recentfile[1], true);
					break;
				case IDM_RECENT_FILE3:
					if (strlen(recentfile[2]))OpenFile(recentfile[2], true);
					break;
				case IDM_RECENT_FILE4:
					if (strlen(recentfile[3]))OpenFile(recentfile[3], true);
					break;
				case IDM_RECENT_FILE5:
					if (strlen(recentfile[4]))OpenFile(recentfile[4], true);
					break;

				case IDM_CHANGE:
					Open(false);
					InvalidateRect(hWnd,NULL,0);
					break;
				case IDM_EXIT:
				   DestroyWindow(hWnd);
				   break;
				case IDM_SAVE:
					Save();
					break;
				case IDM_LOADCUR:
					OpenSingle();
					break;
				case IDM_IMPORT:
					Import();
					InvalidateRect(hWnd,NULL,0);
					break;
				case IDM_EXPAND:
					mode=-1;
					InvalidateRect(hWnd,NULL,0);
					break;
				case IDM_EXPORT:
					Export();
					break;
				case IDM_FOLDER:
					if (!strlen(file))return 0;
					ShellExecute(NULL, "open", filepath, NULL, NULL, SW_SHOWDEFAULT);
					break;
				case IDM_TOCLIPBOARD:
					if (mode == 2) {
						CopySelectedItem();
					}
					if (mode == 4) {
						CopySelectedSpell();
					}
					if (mode == 16) {
						CopySelected();
					}
					if (mode == 17) {
						CopySelectedAnim();
					}
					break;
				case IDM_FROMCLIPBOARD:
					if (mode == 2) {
						PasteSelectedItem();
					}
					if (mode == 4) {
						PasteSelectedSpell();
					}
					if (mode == 16) {
						PasteSelected();
					}
					if (mode == 17) {
						PasteSelectedAnim();
					}

					break;
				case IDM_FROMCLIPBOARD_PAL:
					if (mode == 16) {
						PasteSelected(true);
					}
					break;
				case IDM_COPY:
					switch(mode){
						case 12:
							copysource[mode][submode[mode]] = subfocus + 30*select[mode];
							break;
						case 13:
							copysource[mode][submode[mode]] = subfocus + 32*select[mode];
							break;
						case 15:
							copysource[mode][submode[mode]] = (subselect[mode][0]+focus)%NUM_TEXT;
							break;
						case 16:
							copysource[mode][submode[mode]] = subselect[mode][submode[mode]]*256+subselect[mode][submode[mode]+32];
							break;


						case 18:
							switch (submode[mode]) {
								case 0:
									DialogGraphs[subselect[mode][0]]->copy();
									break;
								case 1:
									BEGraphs[subselect[mode][0]]->copy();
									break;
								case 2:
									BExitGraphs[subselect[mode][0]]->copy();
									break;
								case 3:
									CSGraphs[subselect[mode][0]]->copy();
									break;
								case 4:
									BSGraphs[subselect[mode][0]]->copy();
									break;
								case 5:
									WCGraphs[subselect[mode][0]]->copy();
									break;
							}
							break;

						default:
							copysource[mode][submode[mode]] = select[mode];
							break;
					}
					break;

				case IDM_PASTE:
					if(copysource[mode][submode[mode]]>=0 || mode==18)
					switch(mode){
						case 0:
							for(i=0;i<30;i++){
								Char[select[mode]][i] = Char[copysource[mode][submode[mode]]][i];
							}
							for(i=0;i<12;i++){
								Stats[select[mode]][i] = Stats[copysource[mode][submode[mode]]][i];
							}
							sprintf(CharName[select[mode]],"%s",CharName[copysource[mode][submode[mode]]]);

							CharMapSprite[select[mode]] = CharMapSprite[copysource[mode][submode[mode]]];
							CharPortrait[select[mode]] = CharPortrait[copysource[mode][submode[mode]]];
							CharPortrait2[select[mode]] = CharPortrait2[copysource[mode][submode[mode]]];
							BattleSprite[select[mode]][0] = BattleSprite[copysource[mode][submode[mode]]][0];
							BattleSprite[select[mode]][1] = BattleSprite[copysource[mode][submode[mode]]][1];

							break;
						case 1:
							for(i=0;i<120;i++){
								Learn[select[mode]][i][0] = Learn[copysource[mode][submode[mode]]][i][0];
								Learn[select[mode]][i][1] = Learn[copysource[mode][submode[mode]]][i][1];
							}
							NumLearn[select[mode]] = NumLearn[copysource[mode][submode[mode]]];
							LearnAdded=true;
							break;
						case 2:
							for(i=0;i<16;i++){
								Item[select[mode]][i] = Item[copysource[mode][submode[mode]]][i];
							}
							for(i=0;i<384;i++){
								ItemImages[select[mode]][i] = ItemImages[copysource[mode][submode[mode]]][i];
							}
							sprintf(ItemName[select[mode]],"%s",ItemName[copysource[mode][submode[mode]]]);
							ItemWS[select[mode]] = ItemWS[copysource[mode][submode[mode]]];
							ItemType[select[mode]] = ItemType[copysource[mode][submode[mode]]];
							break;
						case 3:
							for(i=0;i<17;i++){
								Monster[select[mode]][i] = Monster[copysource[mode][submode[mode]]][i];
							}
							sprintf(MonsterName[select[mode]],"%s",MonsterName[copysource[mode][submode[mode]]]);
							break;
						case 4:
							for(i=0;i<32;i++){
								Spell[select[mode]][i] = Spell[copysource[mode][submode[mode]]][i];
							}
							for(i=0;i<384;i++){
								SpellImages[select[mode]][i] = SpellImages[copysource[mode][submode[mode]]][i];
							}
							sprintf(SpellName[select[mode]],"%s",SpellName[copysource[mode][submode[mode]]]);
							break;
						case 9:
							for(i=0;i<8;i++){
								ClassData[select[mode]][i] = ClassData[copysource[mode][submode[mode]]][i];
							}
							if(submode[mode]==0)
								sprintf(Classes[select[mode]],"%s",Classes[copysource[mode][submode[mode]]]);
							break;
						case 10:
							for(i=0;i<18;i++){
								Tiles[select[mode]][i] = Tiles[copysource[mode][submode[mode]]][i];
							}
							break;
						case 12:
							for(i=0;i<8;i++){
								Effect[subfocus + 30*select[mode]][i] = Effect[copysource[mode][submode[mode]]][i];
							}
							break;
						case 13:
							for(i=0;i<8;i++){
								Range[subfocus + 32*select[mode]][i] = Range[copysource[mode][submode[mode]]][i];
							}
							j = Range[subfocus + 32*select[mode]][6]*256 + Range[subfocus + 32*select[mode]][7];

							j-=8*( (subfocus + 32*select[mode]) - copysource[mode][submode[mode]]);

							Range[subfocus + 32*select[mode]][6] = (j&0xFF00)/0x100;
							Range[subfocus + 32*select[mode]][7] = (j&0xFF);
							break;
						case 15:
							sprintf(Text[(subselect[mode][0]+focus)%NUM_TEXT],"%s",Text[copysource[mode][submode[mode]]]);
							break;
						case 16:
							k = copysource[mode][submode[mode]]%256;
							l = (copysource[mode][submode[mode]]-k)/256;
							switch(submode[mode]){
								case 0:
									for(i=0;i<12288;i++){
										ForceSprites[subselect[mode][submode[mode]]][subselect[mode][submode[mode]+32]][i] = ForceSprites[l][k][i];
									}
									break;
								case 1:
									for(i=0;i<12288;i++){
										EnemySprites[subselect[mode][submode[mode]]][subselect[mode][submode[mode]+32]][i] = EnemySprites[l][k][i];
									}
									break;
								case 2:
									for(i=0;i<12288;i++){
										WeaponSprites[subselect[mode][submode[mode]]][subselect[mode][submode[mode]+32]][i] = WeaponSprites[l][k][i];
									}
									break;
								case 3:
									for(i=0;i<12288;i++){
										Backgrounds[subselect[mode][submode[mode]]][i] = Backgrounds[l][i];
									}
									break;
								case 4:
									for(i=0;i<12288;i++){
										Platforms[subselect[mode][submode[mode]]][i] = Platforms[l][i];
									}
									break;
								case 6:
									for(i=0;i<12288;i++){
										Portraits[subselect[mode][submode[mode]]][i] = Portraits[l][i];
									}
									break;
								case 7:
									for(i=0;i<12288;i++){
										MapSprites[subselect[mode][submode[mode]]][subselect[mode][submode[mode]+32]][i] = MapSprites[l][k][i];
									}
									break;
								case 8:
									for(i=0;i<17000;i++){
										Tilesets[subselect[mode][submode[mode]]][i] = Tilesets[l][i];
									}
									break;
								case 9:
									for(i=0;i<17000;i++){
										Effects[subselect[mode][submode[mode]]][i] = Effects[l][i];
									}
									break;
							}
							InvalidateRect(hwnd,NULL,0);
							break;
						case 18:
							switch (submode[mode]) {
								case 0:
									DialogGraphs[subselect[mode][0]]->paste();
									break;
								case 1:
									BEGraphs[subselect[mode][0]]->paste();
									break;
								case 2:
									BExitGraphs[subselect[mode][0]]->paste();
									break;
								case 3:
									CSGraphs[subselect[mode][0]]->paste();
									break;
								case 4:
									BSGraphs[subselect[mode][0]]->paste();
									break;
								case 5:
									WCGraphs[subselect[mode][0]]->paste();
									break;
							}
							break;
					}
					break;

				case IDM_HELP:
					//GetCurrentDirectory(512,temp);
					sprintf(temp,"%s\\help\\help.html",EditorDirectory);
					if ((int)ShellExecute(NULL, "open", temp, NULL, NULL, SW_SHOWNORMAL) < 32) {
						//GetCurrentDirectory(512, temp);
						sprintf(temp, "%s\\help.html", EditorDirectory);
						if ((int)ShellExecute(NULL, "open", temp, NULL, NULL, SW_SHOWNORMAL) < 32) {
							GetCurrentDirectory(512, temp);
							sprintf(temp, "%s\\help\\help.html", EditorDirectory);
							if ((int)ShellExecute(NULL, "open", temp, NULL, NULL, SW_SHOWNORMAL) < 32) {
								GetCurrentDirectory(512, temp);
								sprintf(temp, "%s\\help.html", EditorDirectory);
								if ((int)ShellExecute(NULL, "open", temp, NULL, NULL, SW_SHOWNORMAL) < 32) {
									MessageBox(NULL, "Could not find help file.", "Error", MB_OK);
								}
							}
						}
					}
					break;
				case ID_MODE_CHAR:
					mode=0;
					focus=0;
					menu=0;
					break;
				case ID_MODE_LEARN:
					mode=1;
					focus=0;
					menu=0;
					break;
				case ID_MODE_ITEM:
					mode=2;
					focus=0;
					menu=0;
					break;
				case ID_MODE_ENEMY:
					mode=3;
					focus=0;
					menu=0;
					break;
				case ID_MODE_SPELL:
					mode=4;
					focus=0;
					menu=0;
					break;
				case ID_MODE_BATTLE:
					mode=5;

					if(!GraphicsLoaded&&strlen(file))LoadGFX(file);
					if(GraphicsLoaded)submode[mode]=2;
					else submode[mode]=0;
					if(subselect[mode][0]!=-1)select[mode]=subselect[mode][0];
					subselect[mode][0]=-1;

					focus=0;
					menu=0;
					BattleSelect = -1;
					break;
				case ID_MODE_OBATTLE:
					mode = 105;

					if (!GraphicsLoaded&&strlen(file))LoadGFX(file);

					BattleMode = 1;
					focus = 0;
					menu = 0;
					BattleSelect = -1;
					break;
				case ID_MODE_TBATTLE:
					mode=5;

					submode[mode]=0;
					if(subselect[mode][0]!=-1)select[mode]=subselect[mode][0];
					subselect[mode][0]=-1;

					focus=0;
					menu=0;
					break;
				case ID_MODE_TERRAIN:
					if(mode==5&&submode[mode]<3)subselect[mode][0]=select[mode];
					else subselect[5][0]=-1;
					mode=5;

					submode[mode]=3;
					

					focus=0;
					menu=0;

					select[mode]=0;
					break;
				case ID_MODE_FONT:
					mode=6;
					focus=0;
					menu=0;
					break;
				case ID_MODE_SHOP:
					mode=7;
					focus=0;
					menu=0;
					break;
				case ID_MODE_SPRITE:
					mode=8;
					submode[mode]=0;
					focus=0;
					menu=0;
					break;
				case ID_MODE_CHEST:
					mode=8;
					submode[mode]=1;
					focus=0;
					menu=0;
					break;
				case ID_MODE_MAP:
					mode=8;
					submode[mode]=2;
					focus=0;
					menu=0;
					break;
				case ID_MODE_SCRIPT:
					mode=8;
					submode[mode]=3;
					if (LastNPCScript != -1)select[mode] = LastNPCScript;
					else select[mode] = 0;

					focus=0;
					menu=0;
					break;
				case ID_MODE_CLASSF:
					mode=9;
					submode[mode]=0;
					focus=0;
					menu=0;
					break;
				case ID_MODE_CLASSE:
					mode=9;
					submode[mode]=1;
					focus=0;
					menu=0;
					break;
				case ID_MODE_TILE:
					mode=10;
					focus=0;
					menu=0;
					break;
				case ID_MODE_MECH:
					mode=11;
					focus=0;
					menu=0;
					break;
				case ID_MODE_EFFECT:
					mode=12;
					submode[mode] = 0;
					focus=0;
					menu=0;
					break;
				case ID_MODE_EFFECTOLD:
					mode = 12;
					focus = 0;
					menu = 0;
					submode[mode] = 1;
					select[mode] = 0;
					break;
				case ID_MODE_RANGE:
					mode=13;
					submode[mode] = 0;
					focus=0;
					menu=0;
					break;
				case ID_MODE_RANGEOLD:
					mode = 13;
					submode[mode] = 1;
					select[mode] = 0;
					focus = 0;
					menu = 0;
					break;
				case ID_MODE_PALETTE:
					mode=14;
					focus=0;
					menu=0;
					break;
				case ID_MODE_TEXT:
					mode=15;
					submode[mode]=0;
					focus=0;
					menu=0;
					break;
				case ID_MODE_ASSIGN:
					mode=15;
					submode[mode]=1;
					focus=0;
					menu=0;
					break;
				case ID_MODE_GFX:
					mode=16;
					focus=0;
					menu=0;
					InvalidateRect(hWnd, NULL, 0);
					break;
				case ID_MODE_ANIM:
					mode=17;
					if (submode[mode] != 0) {
						select[mode] = 0;
						subselect[mode][1] = 0;
					}
					submode[mode]=0;
					focus=0;
					menu=0;
					break;
				case ID_MODE_ANIMSET:
					mode=17;
					if (submode[mode] != 1) {
						select[mode] = 0;
						subselect[mode][1] = 0;
					}
					submode[mode] = 1;
					focus=0;
					menu=0;
					break;
				case ID_MODE_EANIM:
					mode = 17;
					if (submode[mode] != 2) {
						select[mode] = 0;
						subselect[mode][1] = 0;
					}
					submode[mode] = 2;
					focus = 0;
					menu = 0;
					break;
				case ID_MODE_EANIMSET:
					mode = 17;
					if (submode[mode] != 3) {
						select[mode] = 0;
						subselect[mode][1] = 0;
					}
					submode[mode] = 3;
					focus = 0;
					menu = 0;
					break;
				case ID_MODE_DIALOG:
					if(!TextLoaded&&strlen(file)){
						LoadText(file,true);
					}

					if (!ScriptsLoaded&&strlen(file)) {
						LoadDialog(file);
						LoadBE(file);
						LoadBExit(file);
					}

					mode=18;
					focus=0;
					menu=0;
					submode[mode]=0;
					subselect[mode][0] = 0;
					break;
				case ID_MODE_BATTLEEND:
					if(!TextLoaded&&strlen(file)){
						LoadText(file,true);
					}

					if (!ScriptsLoaded&&strlen(file)) {
						LoadDialog(file);
						LoadBE(file);
						LoadBExit(file);
					}

					mode=18;
					focus=0;
					menu=0;
					submode[mode]=1;
					subselect[mode][0] = 0;
					break;
				case ID_MODE_BATTLEEXIT:
					if (!TextLoaded&&strlen(file)) {
						LoadText(file, true);
					}

					if (!ScriptsLoaded&&strlen(file)) {
						LoadDialog(file);
						LoadBE(file);
						LoadBExit(file);
					}

					mode = 18;
					focus = 0;
					menu = 0;
					submode[mode] = 2;
					subselect[mode][0] = 0;
					break;
				case ID_MODE_CHAPTERSTART:
					if (!TextLoaded&&strlen(file)) {
						LoadText(file, true);
					}

					mode = 18;
					focus = 0;
					menu = 0;
					submode[mode] = 3;
					subselect[mode][0] = 0;
					break;
				case ID_MODE_BATTLESTART:
					if (!TextLoaded&&strlen(file)) {
						LoadText(file, true);
					}

					mode = 18;
					focus = 0;
					menu = 0;
					submode[mode] = 4;
					subselect[mode][0] = 0;
					break;
				case ID_MODE_WORLD_SCENES:
					if (!TextLoaded&&strlen(file)) {
						LoadText(file, true);
					}

					mode = 18;
					focus = 0;
					menu = 0;
					submode[mode] = 5;
					subselect[mode][0] = 0;
					break;
				case ID_DEBUG_CAPPALETTE:
					for (s = 0;s < NumGFX[0];s++) {
						if (NumFSPalette[s] > 6)NumFSPalette[s] = 6;
						if (NumFSPalette[s] < 1)NumFSPalette[s] = 1;
					}
					break;
				case ID_DEBUG_PALETTE:
					mode = 255;
					submode[mode] = 0;
					break;
				case ID_DEBUG_GRAPHICSTESTER:
					mode = 255;
					submode[mode] = 1;
					break;
				case ID_DEBUG_RESETBS:
					for (int i = 0; i<NumChars; i++) {
						BattleSprite2[i][0] = BattleSprite[i][0] + 19;
						BattleSprite2[i][1] = BattleSprite[i][1];
					}
					break;
				case ID_DEBUG_FIXEXITS:
					mode = 5;
					select[mode] = 12;
					submode[mode] = 2;
					BattleMode = 4;
					BattleExitSet = 2;

					Exits[18][3 + 33 * 2] = 1;
					Exits[18][4 + 33 * 2] = 1;
					Exits[18][3 + 33 * 3] = 1;
					Exits[18][4 + 33 * 3] = 1;

					Exits[18][27 + 33 * 9] = 2;

					Exits[18][27 + 33 * 27] = 0;
					Exits[18][28 + 33 * 27] = 0;
					Exits[18][27 + 33 * 28] = 0;
					Exits[18][28 + 33 * 28] = 0;

					Exits[52][9 + 89 * 7] = 1;
					Exits[52][5 + 89 * 38] = 0;
					Exits[52][6 + 89 * 38] = 0;
					Exits[52][7 + 89 * 38] = 0;


					Exits[128 + 33][10 + 24 * 22] = 7 + 24 * 40;
					Exits[128 + 33][7 + 24 * 40] = 10 + 24 * 22;

					Exits[115][6 + 16 * 5] = 1;

					Exits[115][6 + 16 * 7] = 126;
					Exits[115][6 + 16 * 17] = 126;
					Exits[115][7 + 16 * 17] = 126;

					Exits[115][6 + 16 * 22] = 127;
					Exits[115][7 + 16 * 22] = 127;

					Exits[115][7 + 16 * 34] = 127;
					Exits[115][8 + 16 * 34] = 127;

					Exits[115][7 + 16 * 53] = 0;
					Exits[115][8 + 16 * 53] = 0;

					Exits[120][7 + 16 * 53] = 0;
					Exits[120][8 + 16 * 53] = 0;

					Exits[128 + 115][6 + 16 * 7] = 7 + 16 * 17;
					Exits[128 + 115][6 + 16 * 17] = 6 + 16 * 7;
					Exits[128 + 115][7 + 16 * 17] = 6 + 16 * 7;

					Exits[128 + 115][6 + 16 * 22] = 7 + 16 * 35;
					Exits[128 + 115][7 + 16 * 22] = 8 + 16 * 35;

					Exits[128 + 115][7 + 16 * 34] = 6 + 16 * 21;
					Exits[128 + 115][8 + 16 * 34] = 7 + 16 * 21;

					Exits[112][379] = 1;
					Exits[112][426] = 3;
					Exits[112][427] = 3;
					Exits[112][428] = 0;
					Exits[112][429] = 0;
					Exits[112][470] = 3;
					Exits[112][471] = 3;
					Exits[112][472] = 0;
					Exits[112][473] = 0;


					MessageBox(NULL, "Save in Battle Editor to apply.", "Note", MB_OK);
					break;

				case ID_FIND:
					if(mode==15&&TextLoaded){
						menu=1;
						InvalidateRect(hWnd,NULL,0);
					}
					if (mode == 18 && ScriptsLoaded) {
						menu = 2;
						InvalidateRect(hWnd, NULL, 0);
					}
					break;
				default:
				   return DefWindowProc(hWnd, message, wParam, lParam);
			}
			break;
		case WM_KEYDOWN:
			switch(mode){
			case -1:
				#include "ExpandKeydown.h"
				break;
			case 0:
			case 1:
				#include "CharKeydown.h"
				break;
			case 2:
				#include "ItemKeydown.h"
				break;
			case 3:
				#include "MonsterKeydown.h"
				break;
			case 4:
				#include "SpellKeydown.h"
				break;
			case 5:
				#include "BattleKeydown.h"
				break;
			case 105:
				#include "BattleKeydown2.h"
				break;
			case 6:
				#include "FontKeydown.h"
				break;
			case 7:
				#include "ShopKeydown.h"
				break;
			case 8:
				#include "MapKeydown.h"
				break;
			case 9:
				#include "ClassKeydown.h"
				break;
			case 10:
				#include "TileKeydown.h"
				break;
			case 12:
				#include "EffectKeydown.h"
				break;
			case 13:
				#include "RangeKeydown.h"
				break;
			case 15:
				#include "TextKeydown.h"
				break;
			case 18:
				switch(submode[mode]){
					case 0:
						#include "DialogKeydown.h"
						break;
					case 1:
						#include "BEKeydown.h"
						break;
					case 2:
						#include "BExitKeydown.h"
						break;
					case 3:
						#include "CSKeydown.h"
						break;
					case 4:
						#include "BSKeydown.h"
						break;
					case 5:
						#include "WCKeydown.h"
						break;
				}
				break;
			}
			InvalidateRect(hWnd,NULL,0);
			break;
		case WM_ERASEBKGND:
			return true;
		case WM_PAINT:
			PatBlt(memdc,0,0,maxx,maxy,PATCOPY);
			PatBlt(tmpdc,0,0,maxx,maxy,PATCOPY);
			switch(mode){
			case 255:
				#include "DebugPaint.h"
				break;
			case -1:
				#include "ExpandPaint.h"
				break;
			case 0:
				#include "CharPaint1.h"
				break;
			case 1:
				#include "CharPaint2.h"
				break;
			case 2:
				#include "ItemPaint.h"
				break;
			case 3:
				#include "MonsterPaint.h"
				break;
			case 4:
				#include "SpellPaint.h"
				break;
			case 5:
				#include "BattlePaint.h"
				break;
			case 105:
				#include "BattlePaint2.h"
				break;
			case 6:
				#include "FontPaint.h"
				break;
			case 7:
				#include "ShopPaint.h"
				break;
			case 8:
				#include "MapPaint.h"
				break;
			case 9:
				#include "ClassPaint.h"
				break;
			case 10:
				#include "TilePaint.h"
				break;
			case 11:
				#include "MechPaint.h"
				break;
			case 12:
				#include "EffectPaint.h"
				break;
			case 13:
				#include "RangePaint.h"
				break;
			case 14:
				#include "PalettePaint.h"
				break;
			case 15:
				#include "TextPaint.h"
				break;
			case 16:
				#include "GFXPaint.h"
				break;
			case 17:
				#include "AnimPaint.h"
				break;
			case 18:
				if (ScriptsLoaded) {
					SelectObject(bmpdc, minus);
					BitBlt(memdc, 195, 8, 20, 20, bmpdc, 0, 0, SRCCOPY);

					sprintf(out, "Script Set: %d", submode[mode]);
					if (focus == 3 && cursor)sprintf(out, "%s|", out);
					TextOut(memdc, 216, 10, out, strlen(out));

					SelectObject(bmpdc, plus);
					BitBlt(memdc, 306, 8, 20, 20, bmpdc, 0, 0, SRCCOPY);

					TextOut(memdc, 240, dheight + 522, "Macros:", 7);

					Rectangle(memdc, 314, dheight + 520, 368, dheight + 542);
					Rectangle(memdc, 394, dheight + 520, 448, dheight + 542);

					TextOut(memdc, 320, dheight + 522, "Create", 7);
					TextOut(memdc, 400, dheight + 522, "Insert", 7);
				}

				TextOut(memdc, 380, 10, ScriptTitles[submode[mode]], strlen(ScriptTitles[submode[mode]]));

				

				switch(submode[mode]){
					case 0:
						#include "DialogPaint.h"
						break;
					case 1:
						#include "BEPaint.h"
						break;
					case 2:
						#include "BExitPaint.h"
						break;
					case 3:
						#include "CSPaint.h"
						break;
					case 4:
						#include "BSPaint.h"
						break;
					case 5:
						#include "WCPaint.h"
						break;
				}

				

				break;
			}

			BitBlt(hdc,0,40,maxx,maxy,memdc,0,0,SRCCOPY);

			PatBlt(memdc,0,0,maxx,maxy,PATCOPY);

			DrawToolbar();

			BitBlt(hdc,0,0,maxx,40,memdc,0,0,SRCCOPY);
			ValidateRect(hWnd,NULL);
			break;
		case WM_RBUTTONDOWN:
			if (ignoremouse)return 0;
			GetCursorPos(&p);
			ScreenToClient(hWnd,&p);
			InvalidateRect(hWnd,NULL,0);

			p.y-=40;
			switch(mode){
			case 2:
				#include "ItemRClick.h"
				break;
			case 5:
				#include "BattleRClick.h"
				break;
			case 105:
				#include "BattleRClick2.h"
				break;
			case 8:
				#include "MapRClick.h"
				break;
			case 16:
				#include "GFXRClick.h"
				break;
			case 17:
				#include "AnimRClick.h"
				break;
			case 18:
				switch(submode[mode]){
					case 0:
						#include "DialogRClick.h"
						break;
					case 1:
						#include "BERClick.h"
						break;
					case 2:
						#include "BExitRClick.h"
						break;
					case 3:
						#include "CSRClick.h"
						break;
					case 4:
						#include "BSRClick.h"
						break;
					case 5:
						#include "WCRClick.h"
						break;
				}
				break;
			}
			break;
		case WM_MBUTTONDOWN:
			if (ignoremouse)return 0;
			GetCursorPos(&p);
			ScreenToClient(hWnd,&p);
			InvalidateRect(hWnd,NULL,0);

			p.y-=40;
			switch(mode){
			case 5:
				#include "BattleMClick.h"
				break;
			case 105:
				#include "BattleMClick2.h"
				break;
			case 8:
				#include "MapMClick.h"
				break;
			}
			break;
		case WM_MBUTTONUP:
			if (ignoremouse)return 0;
			GetCursorPos(&p);
			ScreenToClient(hWnd,&p);
			InvalidateRect(hWnd,NULL,0);

			p.y-=40;
			switch(mode){
			case 5:
				#include "BattleMRelease.h"
				break;
			case 105:
				#include "BattleMRelease2.h"
				break;
			case 8:
				#include "MapMRelease.h"
				break;
			}
			break;
		case WM_LBUTTONUP:
			ldown = false;
			if (ignoremouse)return 0;
			if(mode==16)InvalidateRect(hWnd,NULL,0);
			switch(mode){
			case 18:
				switch(submode[mode]){
					case 0:
						#include "DialogRelease.h"
						break;
					case 1:
						#include "BERelease.h"
						break;
					case 2:
						#include "BExitRelease.h"
						break;
					case 3:
						#include "CSRelease.h"
						break;
					case 4:
						#include "BSRelease.h"
						break;
					case 5:
						#include "WCRelease.h"
						break;
				}
				break;
			}
			break;
		case WM_LBUTTONDBLCLK:
			if (ignoremouse)return 0;
			GetCursorPos(&p);
			ScreenToClient(hWnd,&p);
			p.y-=40;
			switch(mode){
			case 18:
				switch (submode[mode]) {
						case 0:
							#include "DialogDClick.h"
							break;
						case 1:
							#include "BEDClick.h"
							break;
						case 2:
							#include "BExitDClick.h"
							break;
						case 3:
							#include "CSDClick.h"
							break;
						case 4:
							#include "BSDClick.h"
							break;
						case 5:
							#include "WCDClick.h"
							break;
						}
				return true;			
			}
			break; //so unhandled doubles are still processed as single
		case WM_LBUTTONDOWN:
			if (ignoremouse)return 0;
			ldown = true;
			if(!menu){
				lastfocus=focus;
				lastsubfocus=subfocus;
				focus = 0;
				subfocus = -1;
				editneg=false;
			}
			GetCursorPos(&p);
			ScreenToClient(hWnd,&p);
			if(mode!=16)InvalidateRect(hWnd,NULL,0);

			if(p.y<=40){
				menu=0;
				if(p.x<=40){
					mode=0;
					return 0;
				}
				if(p.x<=80){
					mode=1;
					return 0;
				}
				if(p.x<=120){
					mode=2;
					return 0;
				}
				if(p.x<=160){
					mode=3;
					return 0;
				}
				if(p.x<=200){
					mode=4;
					return 0;
				}
				if(p.x<=240){
					mode=5;
					if(!GraphicsLoaded&&strlen(file))LoadGFX(file);
					if(GraphicsLoaded)submode[mode]=2;
					else submode[mode]=0;
					return 0;
				}
				if(p.x<=280){
					mode=6;
					return 0;
				}
				if(p.x<=320){
					mode=7;
					return 0;
				}
				if(p.x<=360){
					mode=8;
					return 0;
				}
				if(p.x<=400){
					mode=9;
					return 0;
				}
				if(p.x<=440){
					mode=10;
					return 0;
				}
				if(p.x<=480){
					mode=11;
					return 0;
				}
				if(p.x<=520){
					mode=12;
					submode[mode] = 0;
					return 0;
				}
				if(p.x<=560){
					mode=13;
					submode[mode] = 0;
					return 0;
				}
				if(p.x<=600){
					mode=14;
					return 0;
				}
				if(p.x<=640){
					mode=15;
					return 0;
				}
				if(p.x<=680){
					mode=16;
					return 0;
				}
				if(p.x<=720){
					mode=17;
					return 0;
				}
				if(p.x<=760){
					if(!TextLoaded&&strlen(file)){
						LoadText(file,true);
					}
					if (!ScriptsLoaded&&strlen(file)) {
						LoadDialog(file);
						LoadBE(file);
						LoadBExit(file);
					}
					mode=18;
					return 0;
				}
				
			}
			p.y-=40;
			switch(mode){
			case -1:
				#include "ExpandClick.h"
				break;
			case 0:
				#include "CharClick1.h"
				break;
			case 1:
				#include "CharClick2.h"
				break;
			case 2:
				#include "ItemClick.h"
				break;
			case 3:
				#include "MonsterClick.h"
				break;
			case 4:
				#include "SpellClick.h"
				break;
			case 5:
				#include "BattleClick.h"
				break;
			case 105:
				#include "BattleClick2.h"
				break;
			case 6:
				#include "FontClick.h"
				break;
			case 7:
				#include "ShopClick.h"
				break;
			case 8:
				#include "MapClick.h"
				break;
			case 9:
				#include "ClassClick.h"
				break;
			case 10:
				#include "TileClick.h"
				break;
			case 11:
				#include "MechClick.h"
				break;
			case 12:
				#include "EffectClick.h"
				break;
			case 13:
				#include "RangeClick.h"
				break;
			case 14:
				#include "PaletteClick.h"
				break;
			case 15:
				#include "TextClick.h"
				break;
			case 16:
				#include "GFXClick.h"
				break;
			case 17:
				#include "AnimClick.h"
				break;
			case 18:

				if (ScriptsLoaded) {

					if (p.x >= 314 && p.x <= 368 && p.y >= dheight + 520 && p.y <= dheight + 542) {
						WndProc(hwnd, WM_COMMAND, IDM_COPY, 0);

						char data[65536];
						char path[256];
						fromClipboard(data, 65536);

						if (!strcmp(data, "EMPTY")) {
							MessageBox(hwnd, "Shift+Drag to select nodes to save.", "Error", MB_OK);
							return 0;
						}

						String folder = EditorDirectory;
						folder += "\\Macros";
						mkdir(folder);
						folder += "\\Macro";

						OPENFILENAME openFileName;

						
						path[0] = '\0';
						sprintf(path, folder);

						memset(&openFileName, 0, sizeof(openFileName));
						openFileName.lStructSize = sizeof(openFileName);
						openFileName.hwndOwner = NULL;
						openFileName.hInstance = NULL;
						openFileName.lpstrFilter = "Text Files(*.txt)\0*.txt\0";
						openFileName.lpstrCustomFilter = NULL;
						openFileName.nMaxCustFilter = 0;
						openFileName.nFilterIndex = 0;
						openFileName.lpstrFile = path;
						openFileName.nMaxFile = 256;
						openFileName.lpstrFileTitle = NULL;
						openFileName.nMaxFileTitle = 0;
						openFileName.lpstrInitialDir = ".";
						openFileName.lpstrTitle = NULL;
						openFileName.Flags = OFN_OVERWRITEPROMPT | OFN_LONGNAMES | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY;
						openFileName.nFileOffset = 0;
						openFileName.nFileExtension = 0;
						openFileName.lpstrDefExt = "txt";
						openFileName.lCustData = NULL;
						openFileName.lpfnHook = NULL;
						openFileName.lpTemplateName = NULL;

						if (GetSaveFileName(&openFileName) != 0) {
							FILE * fp = fopen(path, "w+");

							if (!fp) {
								MessageBox(hwnd, "Could not create file.", "Error", MB_OK);
								return 0;
							}

							fprintf(fp, data);

							fclose(fp);
						}

					}
					if (p.x >= 394 && p.x <= 448 && p.y >= dheight + 520 && p.y <= dheight + 542) {


						char data[65536];
						char path[256];


						String folder = EditorDirectory;
						folder += "\\Macros";
						mkdir(folder);
						folder += "\\Macro";

						OPENFILENAME openFileName;


						path[0] = '\0';
						sprintf(path, folder);

						memset(&openFileName, 0, sizeof(openFileName));
						openFileName.lStructSize = sizeof(openFileName);
						openFileName.hwndOwner = NULL;
						openFileName.hInstance = NULL;
						openFileName.lpstrFilter = "Text Files(*.txt)\0*.txt\0";
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
						openFileName.lpstrDefExt = "txt";
						openFileName.lCustData = NULL;
						openFileName.lpfnHook = NULL;
						openFileName.lpTemplateName = NULL;

						if (GetOpenFileName(&openFileName) != 0) {
							FILE * fp = fopen(path, "r+");

							if (!fp) {
								MessageBox(hwnd, "Could not read file.", "Error", MB_OK);
								return 0;
							}
							unsigned long len;
							fseek(fp, 0, SEEK_END);
							len = ftell(fp);
							fseek(fp, 0, SEEK_SET);

							fread(data, sizeof(char), len, fp);

							fclose(fp);

							toClipboard(data);
							WndProc(hwnd, WM_COMMAND, IDM_PASTE, 0);

							
						}

					}

				}

				if(p.x>=195&&p.x<=215&&p.y>=8&&p.y<=28){
					focus=0;
					menu=0;
					submode[mode]--;
					if(submode[mode]<0)submode[mode]+=6;

					subselect[mode][0] = 0;

					switch (submode[mode]) {
						case 0:
							DialogGraphs[subselect[mode][0]]->w = BEGraphs[subselect[mode][0]]->w;
							DialogGraphs[subselect[mode][0]]->h = BEGraphs[subselect[mode][0]]->h;
							DialogGraphs[subselect[mode][0]]->buildList();
							break;
						case 1:
							BEGraphs[subselect[mode][0]]->w = BExitGraphs[subselect[mode][0]]->w;
							BEGraphs[subselect[mode][0]]->h = BExitGraphs[subselect[mode][0]]->h;
							BEGraphs[subselect[mode][0]]->buildList();
							break;
						case 2:
							BExitGraphs[subselect[mode][0]]->w = CSGraphs[subselect[mode][0]]->w;
							BExitGraphs[subselect[mode][0]]->h = CSGraphs[subselect[mode][0]]->h;
							BExitGraphs[subselect[mode][0]]->buildList();
							break;
						case 3:
							CSGraphs[subselect[mode][0]]->w = BSGraphs[subselect[mode][0]]->w;
							CSGraphs[subselect[mode][0]]->h = BSGraphs[subselect[mode][0]]->h;
							CSGraphs[subselect[mode][0]]->buildList();
							break;
						case 4:
							BSGraphs[subselect[mode][0]]->w = WCGraphs[subselect[mode][0]]->w;
							BSGraphs[subselect[mode][0]]->h = WCGraphs[subselect[mode][0]]->h;
							BSGraphs[subselect[mode][0]]->buildList();
							break;
						case 5:
							WCGraphs[subselect[mode][0]]->w = DialogGraphs[subselect[mode][0]]->w;
							WCGraphs[subselect[mode][0]]->h = DialogGraphs[subselect[mode][0]]->h;
							WCGraphs[subselect[mode][0]]->buildList();
							break;
					}

					return 0;
				}

				if(p.x>=306&&p.x<=326&&p.y>=8&&p.y<=28){
					focus=0;
					menu=0;
					submode[mode]++;
					if(submode[mode]>5)submode[mode]=0;

					subselect[mode][0] = 0;

					switch (submode[mode]) {
					case 0:
						DialogGraphs[subselect[mode][0]]->w = WCGraphs[subselect[mode][0]]->w;
						DialogGraphs[subselect[mode][0]]->h = WCGraphs[subselect[mode][0]]->h;
						DialogGraphs[subselect[mode][0]]->buildList();
						break;
					case 1:
						BEGraphs[subselect[mode][0]]->w = DialogGraphs[subselect[mode][0]]->w;
						BEGraphs[subselect[mode][0]]->h = DialogGraphs[subselect[mode][0]]->h;
						BEGraphs[subselect[mode][0]]->buildList();
						break;
					case 2:
						BExitGraphs[subselect[mode][0]]->w = BEGraphs[subselect[mode][0]]->w;
						BExitGraphs[subselect[mode][0]]->h = BEGraphs[subselect[mode][0]]->h;
						BExitGraphs[subselect[mode][0]]->buildList();
						break;
					case 3:
						CSGraphs[subselect[mode][0]]->w = BExitGraphs[subselect[mode][0]]->w;
						CSGraphs[subselect[mode][0]]->h = BExitGraphs[subselect[mode][0]]->h;
						CSGraphs[subselect[mode][0]]->buildList();
						break;
					case 4:
						BSGraphs[subselect[mode][0]]->w = CSGraphs[subselect[mode][0]]->w;
						BSGraphs[subselect[mode][0]]->h = CSGraphs[subselect[mode][0]]->h;
						BSGraphs[subselect[mode][0]]->buildList();
						break;
					case 5:
						WCGraphs[subselect[mode][0]]->w = BSGraphs[subselect[mode][0]]->w;
						WCGraphs[subselect[mode][0]]->h = BSGraphs[subselect[mode][0]]->h;
						WCGraphs[subselect[mode][0]]->buildList();
						break;
					}

					return 0;
				}

				switch(submode[mode]){
					case 0:
						#include "DialogClick.h"
						break;
					case 1:
						#include "BEClick.h"
						break;
					case 2:
						#include "BExitClick.h"
						break;
					case 3:
						#include "CSClick.h"
						break;
					case 4:
						#include "BSClick.h"
						break;
					case 5:
						#include "WCClick.h"
						break;
				}
				break;
			case 255:
				#include "DebugClick.h"
				break;
			}
			break;
		case WM_MOUSEMOVE:
			if (!(wParam & MK_LBUTTON))ldown = false;
			if (ignoremouse)return 0;
			switch(mode){
			case 0:
				#include "CharMove.h"
				break;
			case 2:
				#include "ItemMove.h"
				break;
			case 4:
				#include "SpellMove.h"
				break;
			case 5:
				#include "BattleMove.h"
				break;
			case 105:
				#include "BattleMove2.h"
				break;
			case 6:
				#include "FontMove.h"
				break;
			case 8:
				#include "MapMove.h"
				break;
			case 16:
				#include "GFXMove.h"
				break;
			case 17:
				#include "AnimMove.h"
				break;

			case 18:
				switch(submode[mode]){
					case 0:
						#include "DialogMove.h"
						break;
					case 1:
						#include "BEMove.h"
						break;
					case 2:
						#include "BExitMove.h"
						break;
					case 3:
						#include "CSMove.h"
						break;
					case 4:
						#include "BSMove.h"
						break;
					case 5:
						#include "WCMove.h"
						break;
				}
				break;
			}
			break;
		case WM_CHAR:
			switch(mode){
			case 0:
				#include "CharChar1.h"
				break;
			case 1:
				#include "CharChar2.h"
				break;
			case 2:
				#include "ItemChar.h"
				break;
			case 3:
				#include "MonsterChar.h"
				break;
			case 4:
				#include "SpellChar.h"
				break;
			case 5:
				#include "BattleChar.h"
				break;
			case 105:
				#include "BattleChar2.h"
				break;
			case 7:
				#include "ShopChar.h"
				break;
			case 8:
				#include "MapChar.h"
				break;
			case 9:
				#include "ClassChar.h"
				break;
			case 10:
				#include "TileChar.h"
				break;
			case 11:
				#include "MechChar.h"
				break;
			case 12:
				#include "EffectChar.h"
				break;
			case 13:
				#include "RangeChar.h"
				break;
			case 14:
				#include "PaletteChar.h"
				break;
			case 15:
				#include "TextChar.h"
				break;
			case 16:
				#include "GFXChar.h"
				break;
			case 17:
				#include "AnimChar.h"
				break;
			case 18:
				switch(submode[mode]){
					case 0:
						#include "DialogChar.h"
						break;
					case 1:
						#include "BEChar.h"
						break;
					case 2:
						#include "BExitChar.h"
						break;
					case 3:
						#include "CSChar.h"
						break;
					case 4:
						#include "BSChar.h"
						break;
					case 5:
						#include "WCChar.h"
						break;
				}
				break;
			case 255:
				#include "DebugChar.h"
				break;
			}
			if(wParam!='-')editneg=false;
			break;
		case WM_MOUSEWHEEL:
			switch (mode) {
				case 8:
					#include "MapWheel.h"
					break;
				case 15:
					#include "TextWheel.h"
					break;
				case 17:
					#include "AnimWheel.h"
					break;
				case 18:
					switch (submode[mode]) {
					case 0:
						#include "DialogWheel.h"
						break;
					case 1:
						#include "BEWheel.h"
						break;
					case 2:
						#include "BExitWheel.h"
						break;
					case 3:
						#include "CSWheel.h"
						break;
					case 4:
						#include "BSWheel.h"
						break;
					case 5:
						#include "WCWheel.h"
						break;
					}
					break;
			}
			break;
		case WM_DESTROY:
			KillTimer(hWnd,0);
			DeleteDC(hdc);
			DeleteDC(memdc);
			DeleteObject(hbit);
			PostQuitMessage(0);
			_fcloseall();
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
   }
   return 0;
}

void DrawToolbar(){
	if(mode==0){
		SelectObject(bmpdc,charaon);
	} else {
		SelectObject(bmpdc,chara);
	}
	BitBlt(memdc,0,0,40,40,bmpdc,0,0,SRCCOPY);
	if(mode==1){
		SelectObject(bmpdc,magicon);
	} else {
		SelectObject(bmpdc,magic);
	}
	BitBlt(memdc,40,0,40,40,bmpdc,0,0,SRCCOPY);
	if(mode==2){
		SelectObject(bmpdc,itemon);
	} else {
		SelectObject(bmpdc,item);
	}
	BitBlt(memdc,80,0,40,40,bmpdc,0,0,SRCCOPY);
	if(mode==3){
		SelectObject(bmpdc,monsteron);
	} else {
		SelectObject(bmpdc,monster);
	}
	BitBlt(memdc,120,0,40,40,bmpdc,0,0,SRCCOPY);
	if(mode==4){
		SelectObject(bmpdc,spellon);
	} else {
		SelectObject(bmpdc,spell);
	}
	BitBlt(memdc,160,0,40,40,bmpdc,0,0,SRCCOPY);
	if(mode==5){
		SelectObject(bmpdc,battleon);
	} else {
		SelectObject(bmpdc,battle);
	}
	BitBlt(memdc,200,0,40,40,bmpdc,0,0,SRCCOPY);
	if(mode==6){
		SelectObject(bmpdc,fonton);
	} else {
		SelectObject(bmpdc,font);
	}
	BitBlt(memdc,240,0,40,40,bmpdc,0,0,SRCCOPY);
	if(mode==7){
		SelectObject(bmpdc,shopon);
	} else {
		SelectObject(bmpdc,shop);
	}
	BitBlt(memdc,280,0,40,40,bmpdc,0,0,SRCCOPY);
	if(mode==8){
		SelectObject(bmpdc,mapon);
	} else {
		SelectObject(bmpdc,map);
	}
	BitBlt(memdc,320,0,40,40,bmpdc,0,0,SRCCOPY);
	if(mode==9){
		SelectObject(bmpdc,classon);
	} else {
		SelectObject(bmpdc,classi);
	}
	BitBlt(memdc,360,0,40,40,bmpdc,0,0,SRCCOPY);
	if(mode==10){
		SelectObject(bmpdc,tileon);
	} else {
		SelectObject(bmpdc,tile);
	}
	BitBlt(memdc,400,0,40,40,bmpdc,0,0,SRCCOPY);
	if(mode==11){
		SelectObject(bmpdc,mechon);
	} else {
		SelectObject(bmpdc,mech);
	}
	BitBlt(memdc,440,0,40,40,bmpdc,0,0,SRCCOPY);
	if(mode==12){
		SelectObject(bmpdc,effecton);
	} else {
		SelectObject(bmpdc,effect);
	}
	BitBlt(memdc,480,0,40,40,bmpdc,0,0,SRCCOPY);
	if(mode==13){
		SelectObject(bmpdc,rangeon);
	} else {
		SelectObject(bmpdc,range);
	}
	BitBlt(memdc,520,0,40,40,bmpdc,0,0,SRCCOPY);
	if(mode==14){
		SelectObject(bmpdc,paletteon);
	} else {
		SelectObject(bmpdc,palette);
	}
	BitBlt(memdc,560,0,40,40,bmpdc,0,0,SRCCOPY);
	if(mode==15){
		SelectObject(bmpdc,texton);
	} else {
		SelectObject(bmpdc,text);
	}
	BitBlt(memdc,600,0,40,40,bmpdc,0,0,SRCCOPY);
	if(mode==16){
		SelectObject(bmpdc,gfxon);
	} else {
		SelectObject(bmpdc,gfx);
	}
	BitBlt(memdc,640,0,40,40,bmpdc,0,0,SRCCOPY);
	if(mode==17){
		SelectObject(bmpdc,animon);
	} else {
		SelectObject(bmpdc,anim);
	}
	BitBlt(memdc,680,0,40,40,bmpdc,0,0,SRCCOPY);
	if(mode==18){
		SelectObject(bmpdc,scripton);
	} else {
		SelectObject(bmpdc,script);
	}
	BitBlt(memdc,720,0,40,40,bmpdc,0,0,SRCCOPY);
}

void GetSize(char * path){
	FILE * stream = fopen( path, "r" );
	if (!stream) {
		romsize = 0;
		return;
	}
	fseek( stream, 0L, SEEK_END );
	romsize = ftell( stream );
	fclose( stream );
	for(int i=0;i<8;i++){
		if(romsize==1572864+524288*i){
			sizesel=i;
		}
	}
}