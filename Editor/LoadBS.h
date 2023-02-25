int BSHeader[256];
int BSScript[64][768];
long BSScriptO[64][768];

long BSHeaderOffset;

int BSPatterns[512][512];
int NumBSPatterns = 0;
int BSLength[512];
char BSNames[512][32];
int BSPatternNodes[512];

int BSArgs[16];
//int NumArgs = 0;
int BSBranches[128];
//int NumBranches = 0;

BSGraph * BSGraphs[64];

void addBSPattern(int len, int node, char * name, ...) {
	va_list vl;
	va_start(vl, name);
	int c = 0;
	for (int i = 0; i<len; i++) {
		BSPatterns[NumBSPatterns][c] = va_arg(vl, int);
		c++;
	}
	sprintf(BSNames[NumBSPatterns], name);
	BSLength[NumBSPatterns] = len;
	BSPatternNodes[NumBSPatterns] = node;
	NumBSPatterns++;
	va_end(vl);
}

//positive values just match bytes
//negative values
//		1-4  = 1-4 bytes, anything
//		5-8  = 1-4 bytes, must match next value as a relative branch offset
//		9-12 = 1-4 bytes, must match next value as an absolute branch offset
//		13-16 = 1-4 bytes, relative offset must lead to a RTS
//		17-20 = 1-4 bytes, relative branch positive, seek to target
//		21	  = 1 byte, check for branch opcode
//		25-28 = 1-4 bytes, relative branch negative just save
//		29-32 = 1-4 bytes, jump table offsets
bool checkBSEnd(FILE * fp);

bool checkBSPattern(FILE * fp, int pat) {
	int r = 0;
	int r2 = 0;
	int t, k;
	int v;
	long o, o2;
	NumArgs = 0;
	int lastarg = 0;
	for (int i = 0; i<BSLength[pat]; i++) {
		fscanf(fp, "%c", &r);
		t = BSPatterns[pat][i];
		if (t >= 0) {
			if (r != t)return false;
		} else {
			t *= -1;
			k = t % 4;
			if (!k)k = 4;
			k--;
			v = r;
			o = ftell(fp);
			for (int j = 0; j<k; j++) {
				fscanf(fp, "%c", &r);
				v *= 256;
				v += r;
			}

			if (k == 0)
				if (v & 0x80)
					v = v | (-1 - 0xFF);

			if (k == 1)
				if (v & 0x8000)v = v | (-1 - 0xFFFF);

			if (NumArgs&&lastarg>20 && lastarg<25)
				switch (BSArgs[NumArgs - 1]) {
					case 0x60://always
					case 0x64://carry clear
					case 0x65://carry set
					case 0x66://not equal
					case 0x67://equal
					case 0x6D://less than
						v += o;
						if (t % 2 == 0)v -= 1;
						break;
				}

			if (t > 28 && t < 33) {
				BSArgs[NumArgs] = o + v - 1;
				NumArgs++;
				for (int j = 1; j < v / 2; j++) {
					int v2 = 0;
					for (int j2 = 0; j2 <= k; j2++) {
						fscanf(fp, "%c", &r);
						v2 *= 256;
						v2 += r;
					}
					if (v2 < v)v = v2;
					BSArgs[NumArgs] = o + v2 - 1;

					NumArgs++;
				}
			} else {
				BSArgs[NumArgs] = v;
				NumArgs++;
			}

			if (t<5) {

			} else if (t<9) {
				i++;
				if (NumArgs&&lastarg>20 && lastarg<25) {
					if (v != BSPatterns[pat][i])return false;
				} else {
					if (o - 1 + v != BSPatterns[pat][i])return false;
					BSArgs[NumArgs - 1] = o - 1 + v;
				}
			} else if (t<13) {
				i++;
				if (v != BSPatterns[pat][i])return false;
			} else if (t<17) {
				o2 = ftell(fp);
				fseek(fp, v, SEEK_SET);
				fscanf(fp, "%c", &r);
				fscanf(fp, "%c", &r2);

				if (r == 0x60) {
					fseek(fp, o + v, SEEK_SET);
					if (!checkBSEnd(fp))return false;
				} else {
					if (r != 0x4E || r2 != 0x75)return false;
				}
				fseek(fp, o2, SEEK_SET);
			} else if (t<21) {
				if (v<0)return false;
				fseek(fp, o + v - k, SEEK_SET);//**** break here and make sure not missing.. something
			} else if (t<25) {
				switch (r) {
					case 0x60://always
					case 0x64://carry clear
					case 0x65://carry set
					case 0x66://not equal
					case 0x67://equal
					case 0x6D://less than
						break;
					default:
						return false;
				}
			} else if (t<29) {
				if (v >= 0)return false;
				BSArgs[NumArgs] = o + v - k;
				//negative branch
				if (!strcmp(BSNames[pat], "Branch"))
					fseek(fp, o + v - k, SEEK_SET);
			}
			lastarg = t;
		}
	}
	return true;
}

bool checkBSEnd(FILE * fp) {
	unsigned long o = ftell(fp);
	for (int i = 0; i<NumBSPatterns; i++) {
		if (!strcmp("End", BSNames[i])) {
			fseek(fp, o, SEEK_SET);
			if (checkBSPattern(fp, i))return true;
		}
	}
	return false;
}

bool checkBSEnd(int p) {
	if (p == NumBSPatterns - 2 || p == NumBSPatterns - 3)
		return false;
	if (!strcmp("End", BSNames[p]))return true;
	//if (BSPatterns[p][0] == 0x60)return true;
	//if (BSPatterns[p][0] == -21 && BSArgs[0] == 0x60)return true;
	if (BSPatterns[p][BSLength[p] - 2] == 0x4E && BSPatterns[p][BSLength[p] - 1] == 0xD5)
		return true;
	if (BSPatterns[p][BSLength[p] - 1] == -30)return true;
	return false;
}

int checkAllBSPatterns(FILE * fp) {
	unsigned long o = ftell(fp);
	for (int i = 0; i<NumBSPatterns; i++) {
		//if(!strcmp(BENames[i],"Clear Message Box?"))
		//	i=i;
		fseek(fp, o, SEEK_SET);
		if (checkBSPattern(fp, i))
			return i;
	}
	return -1;
}

int getBSPatternArgs(int pat) {
	int c = 0;
	for (int i = 0; i<BSLength[pat]; i++) {
		if (BSPatterns[pat][i]<0) {
			c++;
		}
	}
	return c;
}

void addBSNodeType(char * n, int s, char * l = "", char * l2 = "", char * l3 = "", char * l4 = "", int al = -1, int an = 0) {
	nodeTypesBS[NumBSNodeTypes].set(n, s, l, l2, l3, l4, al, an);
	NumBSNodeTypes++;
}

void setBSNodeOuts(int n, char * l = "", char * l2 = "", char * l3 = "", char * l4 = "") {
	nodeTypesBS[NumBSNodeTypes - 1].setout(n, l, l2, l3, l4);
}

void setBSNodeArgs(int n, int t = -1, char * l = "", int t2 = -1, char * l2 = "", int t3 = -1, char * l3 = "", int t4 = -1, char * l4 = "") {
	nodeTypesBS[NumBSNodeTypes - 1].setargs(n, t, l, t2, l2, t3, l3, t4, l4);
}

void setBSNodeHelp(char * h) {
	nodeTypesBS[NumBSNodeTypes - 1].setHelpText(h);
}


void initBS() {
	int i;
	for (i = 0; i<NUM_BS; i++) {
		BSGraphs[i] = new BSGraph(240, 50, 640, 480);
	}

	addBSNodeType("Start", 2, "Start");
	addBSNodeType("End", 3, "End");

	addBSNodeType("Set Event", 0, "Set", "Event", "", "", 3, 0);
		setBSNodeArgs(1, ARG_WORD, "Event Number");
		setBSNodeHelp("Sets an event number as completed.\n\nEvent Number: Event to set");

	addBSNodeType("Clear Event", 0, "Clear", "Event", "", "", 3, 0);
		setBSNodeArgs(1, ARG_WORD, "Event Number");
		setBSNodeHelp("Clears the completed state of an event number.\n\nEvent Number: Event to clear");

	addBSNodeType("Show Message Window", 0, "Show", "Message", "Window", "");
		setBSNodeHelp("Opens the message window.");

	addBSNodeType("Reset Message Window", 0, "Reset", "Message", "Window", "");
		setBSNodeHelp("Reset the message window, loading its graphics and clearing text/position.");

	addBSNodeType("Display Message", 0, "Display", "Message", "", "", 3, 0);
		setBSNodeArgs(1, ARG_MESSAGE, "Message Number");
		setBSNodeHelp("Displays a message to the screen.\n\nMessage Number: Message number to display.");

	addBSNodeType("Close Message Window", 0, "Close", "Message", "Window", "");
		setBSNodeHelp("Closes the message window.");

	addBSNodeType("More Text Prompt", 0, "More", "Text");
		setBSNodeHelp("Pauses the message and displays the flashing arrow indicating more text to follow.");

	addBSNodeType("Wait Frames", 0, "Wait", "Frames", "", "", 3, 0);
		setBSNodeArgs(1, ARG_BYTE, "Frames");
		setBSNodeHelp("Runs the game for a while.\n\nFrames: Number of frames to advance.");


	addBSNodeType("Check Event", 1, "Check", "Event", "", "", 2, 0);
		setBSNodeOuts(2, "Clear", "Set");
		setBSNodeArgs(4, ARG_WORD, "Event Number", ARG_IGNORE, "", ARG_SBRANCH, "Branch On", ARG_IGNORE, "");
		setBSNodeHelp("Branches the script depending on whether a specific event has been set.\n\nEvent Number: Event to check");


	addBSNodeType("Initialize Cursor?", 0, "Initialize", "Cursor", "", "");
		setBSNodeHelp("Gets the battle cursor ready?");

	addBSNodeType("Check Character Present", 1, "Check", "Character", "Present", "", 3, 0);
		setBSNodeOuts(2, "Not Present", "Present");
		setBSNodeArgs(4, ARG_WORD, "Character Number", ARG_IGNORE, "", ARG_BRANCH, "", ARG_IGNORE, "");
		setBSNodeHelp("Branches the script depending on whether a member is present.\n\Character Number: Character to check");

	addBSNodeType("Set Active Member", 0, "Set", "Active", "Member", "");
		setBSNodeArgs(1, ARG_BYTE, "Member");
		setBSNodeHelp("Sets the active member based on their position in the battle list.");

	addBSNodeType("Get Speaking Sound", 0, "Get", "Speaking", "Sound", "");
		setBSNodeHelp("Gets the proper speaking sound for the selected character. Only use after a member present check.");

	addBSNodeType("Set Speaking Sound", 0, "Set", "Speaking", "Sound", "");
		setBSNodeArgs(1,ARG_BYTE,"Map Sprite");
		setBSNodeHelp("Sets the speaking sound to the sound for the chosen map sprite.");

	addBSNodeType("Set Portrait",0,"Set","Portrait","","",3,0);//10
		setBSNodeArgs(1,ARG_BYTE,"Portrait");
		setBSNodeHelp("Sets the portrait to be displayed with a message.\n\nPortrait: The gfx number of the portrait to display");


	addBSNodeType("Cursor to Character", 0, "Cursor", "to", "Character", "");
		setBSNodeHelp("Moves the screen and cursor to the current character. Only use after a member present check.");

	addBSNodeType("Set Sprite Direction", 0, "Set Sprite", "Direction", "", "", 3, 0);
		setBSNodeArgs(1, ARG_DIR, "Direction");
		setBSNodeHelp("Changes the direction of the current character.");

	addBSNodeType("Move Sprite", 0, "Move", "Sprite", "", "", 3, 1);
		setBSNodeArgs(2, ARG_DIR, "Direction", ARG_BYTE, "Squares");
		setBSNodeHelp("Moves current character a number of squares in the chosen direction.");

	addBSNodeType("Move and Change Sprite", 0, "Move", "and", "Change", "Sprite");
		setBSNodeArgs(2, ARG_DIR, "Direction", ARG_BYTE, "Squares", ARG_WORD, "Map Sprite");
		setBSNodeHelp("Moves current character a number of squares in the chosen direction and also overrides its map sprite.");

	addBSNodeType("Step and Change Sprite", 0, "Step", "and", "Change", "Sprite");
		setBSNodeArgs(2, ARG_DIR, "Direction", ARG_WORD, "Map Sprite");
		setBSNodeHelp("Moves current character one square in the chosen direction and also overrides its map sprite.");

	addBSNodeType("Flicker Member", 0, "Flicker", "Member", "", "");
		setBSNodeHelp("Flickers the current member's sprite, used before removing to fade out. Only use after a member present check.");

	addBSNodeType("Remove Member", 0, "Remove", "Member", "", "");
		setBSNodeHelp("Removes the current character from the battle. Only use after a member present check.");

	addBSNodeType("Initialize Earthquake", 0, "Initialize", "Earthquake", "", "");
		setBSNodeHelp("Begins an earthquake animation.");

	addBSNodeType("Set Earthquake Strength", 0, "Set", "Earthquake", "Strength", "", 3, 0);
		setBSNodeArgs(1, ARG_WORD, "Strength");
		setBSNodeHelp("Changes the strength of the earthquake animation.");

	addBSNodeType("Initialize 'No Sprite Update'", 0, "Initialize", "No", "Sprite", "Update");
		setBSNodeHelp("Begins an animation state where map sprites stop walking in place and don't revert to their normal sprites if altered.");

	addBSNodeType("End Animation", 0, "End", "Animation", "", "");
		setBSNodeHelp("Ends animations like earthquake.");

	addBSNodeType("Flash Screen", 0, "Flash", "Screen", "", "");
		setBSNodeHelp("Rapidly flashes screen white several times.");

	addBSNodeType("Set Copy Location", 0, "Set", "Copy", "Location", "");
		setBSNodeArgs(4, ARG_BYTE, "X Source", ARG_BYTE, "Y Source", ARG_BYTE, "X Target", ARG_BYTE, "Y Target");
		setBSNodeHelp("Sets up the location to copy tiles from and to on the map.");

	addBSNodeType("Copy Tiles", 0, "Copy", "Tiles", "", "");
		setBSNodeArgs(2, ARG_BYTE, "Width", ARG_BYTE, "Height");
		setBSNodeHelp("Copies a rectangle of tiles from one part of the map to another.");

	addBSNodeType("Change B7C6?", 0, "Change", "B7C6", "", "", 3, 0);
		setBSNodeArgs(1, ARG_WORD, "?");
		setBSNodeHelp("?");

	addBSNodeType("Clear B7C6?", 0, "Clear", "B7C6", "", "", 3, 0);
		setBSNodeHelp("?");

	addBSNodeType("Play Sound", 0, "Play", "Sound", "", "", 3, 0);
		setBSNodeArgs(1, ARG_WORD, "Sound Effect");
		setBSNodeHelp("Plays a sound effect.");

	addBSNodeType("Wait for Sound", 0, "Wait", "For", "Sound", "");
		setBSNodeHelp("Waits for sound to finish playing.");

	addBSNodeType("Reduce Earthquake Strength", 1, "Reduce", "Earthquake", "Strength", "");
		setBSNodeOuts(2, "Equal", "Not Equal");
		setBSNodeArgs(2, ARG_BRANCH, "Branch On", ARG_IGNORE, "");
		setBSNodeHelp("Reduces strength by one and then branches if it is not zero.");

	addBSNodeType("Dark Dragon Anim 1", 0, "Dark", "Dragon", "Anim", "1");
		setBSNodeHelp("Animates the palettes for when dark dragon fails to emerge in the second to last battle.");

	for (i = 0; i<NUM_BS; i++) {
		BSGraphs[i]->addNode(16, 16);

		BSGraphs[i]->buildList();
	}

	addBSPattern(7, 2, "Set Event", 0x30, 0x3C, -2, 0x4E, 0xB9, -12, 0x38C);
	addBSPattern(6, 2, "Set Event", 0x70, -1, 0x4E, 0xB9, -12, 0x38C);
	addBSPattern(6, 2, "Set Event", 0x70, -1, 0x61, 0, -6, 0x38C);
	addBSPattern(7, 3, "Clear Event", 0x30, 0x3C, -2, 0x4E, 0xB9, -12, 0x390);
	addBSPattern(6, 3, "Clear Event", 0x70, -1, 0x4E, 0xB9, -12, 0x390);
	addBSPattern(6, 3, "Clear Event", 0x70, -1, 0x61, 0, -6, 0x390);
	addBSPattern(2, 4, "Show Message Window", 0x4E, 0x45);
	addBSPattern(4, 5, "Reset Message Window", 0x4E, 0xB9, -12, 0x8030);
	addBSPattern(5, 6, "Display Message", 0x30, 0x3C, -2, 0x4E, 0x48);

	addBSPattern(2, 7, "Close Message Window", 0x4E, 0x46);

	addBSPattern(2, 8, "More Text Prompt", 0x4E, 0x47);
	addBSPattern(8, 9, "Wait Frames", 0x70, -1, 0x4E, 0xB9, 0, 0, 0x02, 0x44);
	
	addBSPattern(10, 10, "Check Event", 0x30, 0x3C, -2, 0x4E, 0xB9, -12, 0x394, -21, 0, -2);
	addBSPattern(9, 10, "Check Event", 0x70, -1, 0x4E, 0xB9, -12, 0x394, -21, 0, -2);
	addBSPattern(8, 10, "Check Event", 0x70, -1, 0x4E, 0xB9, -12, 0x394, -21, -1);
	addBSPattern(9, 10, "Check Event", 0x70, -1, 0x61, 0, -6, 0x394, -21, 0, -2);
	addBSPattern(8, 10, "Check Event", 0x70, -1, 0x61, 0, -6, 0x394, -21, -1);

	addBSPattern(4, 11, "Initialize Battle Cursor", 0x4E, 0xB9, -12, 0x8094);

	addBSPattern(12, 12,  "Check Member Present", 0x34, 0x3C, -2, 0x4E, 0xB9, -12, 0x12BFB6, 0x4A, 0x40,-21, 0, -2);
	addBSPattern(11, 12,  "Check Member Present", 0x34, 0x3C, -2, 0x4E, 0xB9, -12, 0x12BFB6, 0x4A, 0x40,-21, -1);
	addBSPattern(12, 12,  "Check Member Present", 0x34, 0x3C, -2, 0x61, 0, -6,     0x12BFB6, 0x4A, 0x40,-21, 0, -2);
	addBSPattern(11, 12,  "Check Member Present", 0x34, 0x3C, -2, 0x61, 0, -6,     0x12BFB6, 0x4A, 0x40,-21, -1);

	addBSPattern(6, 13, "Set Active Character", 0x70, -1, 0x4E, 0xB9, -12, 0x20054);

	addBSPattern(4, 14, "Get Speaking Sound", 0x4E, 0xB9, -12, 0x12C342);
	addBSPattern(4, 14, "Get Speaking Sound", 0x61, 0, -6, 0x12C342);

	addBSPattern(6, 15, "Set Speaking Sound", 0x72, -1, 0x4E, 0xB9, -12, 0x12C34E);
	addBSPattern(6, 15, "Set Speaking Sound", 0x72, -1, 0x61, 0, -6, 0x12C34E);

	addBSPattern(6, 16, "Set Portrait", 0x70, -1, 0x4E, 0xB9, -12, 0x802C);

	addBSPattern(38, 17, "Cursor to Character", 0x4E, 0xB9, -12, 0x20058, 0xE1, 0X49, 0x3C, 0x01, 0x4E, 0xB9, -12, 0x2005C, 0x8C, 0x41, 0x30, 0x06, 0x4E, 0xB9, -12, 0x8098, 0x33, 0xFC, 0, 0x01, 0, 0xFF, 0x0C, 0x98, 0x23, 0xFC, 0, 0x01, 0x0F, 0x3F, 0, 0xFF, 0x0E, 0x30);
	addBSPattern(38, 17, "Cursor to Character", 0x4E, 0xB9, -12, 0x20058, 0xE1, 0X49, 0x3C, 0x01, 0x4E, 0xB9, -12, 0x2005C, 0x8C, 0x41, 0x30, 0x06, 0x4E, 0xB9, -12, 0x8098, 0x33, 0xFC, 0, 0x01, 0, 0xFF, 0x0C, 0x98, 0x23, 0xFC, 0, 0x01, 0x0F, 0x3F, 0, 0xFF, 0x0E, 0x30);

	addBSPattern(8, 18, "Set Direction", 0x34, 0x3C, 0, -1, 0x4E, 0xB9, -12, 0x12C2DC);
	addBSPattern(8, 18, "Set Direction", 0x34, 0x3C, 0, -1, 0x61, 0, -6, 0x12C2DC);

	addBSPattern(8, 19, "Move Sprite", 0x74, -1, 0x72, -1, 0x4E, 0xB9, -12, 0x12C0AE);
	addBSPattern(8, 19, "Move Sprite", 0x74, -1, 0x72, -1, 0x61, 0, -6, 0x12C0AE);

	addBSPattern(11, 20, "Move Sprite and Change", 0x74, -1, 0x72, -1, 0x36, 0x3C, -2, 0x4E, 0xB9, -12, 0x12C09E);
	addBSPattern(11, 20, "Move Sprite and Change", 0x74, -1, 0x72, -1, 0x36, 0x3C, -2, 0x61, 0, -6, 0x12C09E);

	addBSPattern(11, 21, "Step Sprite and Change", 0x34, 0x3C, 0, -1, 0x36, 0x3C, -2, 0x4E, 0xB9, -12, 0x12C2BE);
	addBSPattern(11, 21, "Step Sprite and Change", 0x34, 0x3C, 0, -1, 0x36, 0x3C, -2, 0x61, 0, -6, 0x12C2BE);

	addBSPattern(4, 22, "Flicker Member", 0x4E, 0xB9, -12, 0x12C036);
	addBSPattern(4, 22, "Flicker Member", 0x61, 0, -6, 0x12C036);

	addBSPattern(6, 23, "Remove Member", 0x72, 0xFF, 0x4E, 0xB9, -12, 0x20104);

	addBSPattern(20, 24, "Initialize Earthquake", 0x2F, 0x39, 0, 0xFF, 0x0E, 0xF6, 0x4E, 0xB9, -12, 0x12C312, 0x23, 0xFC, 0, 0x12, 0xC3, 0x6E, 0, 0xFF, 0x0E, 0xF6);
	addBSPattern(20, 24, "Initialize Earthquake", 0x2F, 0x39, 0, 0xFF, 0x0E, 0xF6, 0x61, 0, -6, 0x12C312, 0x23, 0xFC, 0, 0x12, 0xC3, 0x6E, 0, 0xFF, 0x0E, 0xF6);
	
	addBSPattern(5, 25, "Set Earthquake Strength", 0x31,0xFC, -2, 0xB7, 0xC4);

	addBSPattern(16, 26, "Initialize No Sprite Walk", 0x2F, 0x39, 0, 0xFF, 0x0E, 0xF6, 0x23, 0xFC, 0, 0, 0x80, 0x34, 0, 0xFF, 0x0E, 0xF6);

	addBSPattern(6, 27, "End Animation", 0x23, 0xDF, 0, 0xFF, 0x0E, 0xF6);

	addBSPattern(4, 28, "Flash Screen", 0x4E, 0xB9, -12, 0x128F98);
	addBSPattern(4, 28, "Flash Screen", 0x61, 0, -6, 0x128F98);

	addBSPattern(8, 29, "Set Copy Location", 0x72, -1, 0x74,-1, 0x76, -1, 0x78, -1);

	addBSPattern(8, 30, "Copy Tiles", 0x7A, -1, 0x7C, -1, 0x4E, 0xB9, -12, 0x80AC);

	addBSPattern(5, 31, "B7C6?", 0x31, 0xFC, -2, 0xB7, 0xC6);

	addBSPattern(4, 32, "B7C6?", 0x42, 0x78, 0xB7, 0xC6);

	addBSPattern(3, 33, "Play Sound", 0x4E, 0x40, -2);
	addBSPattern(4, 34, "Wait for Sound", 0x4E, 0xB9, -12, 0x240);

	addBSPattern(7, 35, "Reduce Earthquake Strength", 0x53, 0x78, 0xB7, 0xC4, -21, 0, -2);
	addBSPattern(6, 35, "Reduce Earthquake Strength", 0x53, 0x78, 0xB7, 0xC4, -21, -1);

	addBSPattern(34, 36, "Dark Dragon Anim 1", 0x41, 0xFA, 0xFF, 0x46, 0x42, 0x40, 0x10, 0x18, 0x6B, 0x1A, 0x2F, 0x08, 0x4E, 0xB9, -12, 0x12B598, 0x20, 0x5F, 0x42, 0x40, 0x10, 0x18, 0x2F, 0x08, 0x4E, 0xB9, 0, 0, 0x02, 0x44, 0x20, 0x5F, 0x60, 0xE0);
	addBSPattern(34, 36, "Dark Dragon Anim 1", 0x41, 0xFA, 0xFF, 0x46, 0x42, 0x40, 0x10, 0x18, 0x6B, 0x18, 0x2F, 0x08, 0x61, 0, -6, 0x12B598, 0x20, 0x5F, 0x42, 0x40, 0x10, 0x18, 0x2F, 0x08, 0x4E, 0xB9, 0, 0, 0x02, 0x44, 0x20, 0x5F, 0x60, 0xE2);

	AdvancedNodes(BS, 37)

	addBSPattern(2, 1, "End", 0x60, -13);
	addBSPattern(3, 1, "End", 0x60, 0, -14);

	addBSPattern(3, 1, "Branch", 0x60, 0, -26);//just follow, shouldn't create a node
	addBSPattern(2, 1, "Branch", 0x60, -25);

	addBSPattern(3, 1, "Branch", 0x60, 0, -18);//just follow, shouldn't create a node
	addBSPattern(2, 1, "Branch", 0x60, -17);

	addBSPattern(2, 1, "End", 0x4E, 0x75);



}

int findBSLabel(int script, int label) {
	int i = 0;
	int p;
	while (BSScript[script][i] != -1) {
		p = BSScript[script][i];
		switch (p) {
			case -2:
				i++;
				if (BSScript[script][i] == label)return i + 1;
				break;
			case -3:
				i++;
				break;
			case -4:
				break;
			default:
				i += getBSPatternArgs(p);
				break;
		}
		i++;
	}
	return -1;
}

void labelBSBranches(BSGraphNode * node, int arg, bool set = false, bool yn = false) {
	switch (node->args[arg]) {
		case 0x64://carry clear
			sprintf(node->outlabel[1], "Less");
			sprintf(node->outlabel[0], "Not Less");
			break;
		case 0x65://carry set
			sprintf(node->outlabel[1], "Not Less");
			sprintf(node->outlabel[0], "Less");
			break;
		case 0x66://not equal
			if (!set) {
				if (!yn) {
					sprintf(node->outlabel[1], "Equal");
					sprintf(node->outlabel[0], "Not Equal");
				} else {
					sprintf(node->outlabel[1], "No");
					sprintf(node->outlabel[0], "Yes");
				}
			} else {
				sprintf(node->outlabel[1], "Clear");
				sprintf(node->outlabel[0], "Set");
			}
			break;
		case 0x67://equal
			if (!set) {
				if (!yn) {
					sprintf(node->outlabel[1], "Not Equal");
					sprintf(node->outlabel[0], "Equal");
				} else {
					sprintf(node->outlabel[1], "Yes");
					sprintf(node->outlabel[0], "No");
				}
			} else {
				sprintf(node->outlabel[1], "Set");
				sprintf(node->outlabel[0], "Clear");
			}
			break;
	}
}


void BuildBSGraphLine(int script, int start, int sx, int sy, BSGraphNode * prev = 0, int b = 0, int bb = 0) {

	BSGraphNode * last = prev;

	int i = start;

	int x = sx;
	int y = sy;

	int p, a;

	int bank = b;
	int bbank = bb;

	int oldline = maxline;

	while (BSScript[script][i] != -1) {
		p = BSScript[script][i];
		/*if(p==NumBSPatterns-2||p==NumBSPatterns-3){
		i+=2;
		continue;
		}*/
		switch (p) {
			case -2:
				i++;
				break;
			case -3:
				i++;
				if (last && last != BSGraphs[script]->nodes.head->data) {
					if (last->branch && last->branch != BSScript[script][i]) {
						last->branch2 = BSScript[script][i];
						last->brasec2 = false;
					} else {
						last->branch = BSScript[script][i];
						last->brasec = false;
					}
				} else {
					if (BSGraphs[script]->nodes.head->data->branch && BSGraphs[script]->nodes.head->data->branch != BSScript[script][i]) {
						BSGraphs[script]->nodes.head->data->branch2 = BSScript[script][i];
						BSGraphs[script]->nodes.head->data->brasec2 = true;
					} else {
						BSGraphs[script]->nodes.head->data->branch = BSScript[script][i];
						BSGraphs[script]->nodes.head->data->brasec = true;
					}
				}
				break;
			case -4:
				return;
			default:
				LLNode<BSGraphNode*>* cur = BSGraphs[script]->nodes.head;

				BSGraphNode * temp;
				if (last && last != BSGraphs[script]->nodes.head->data) {
					temp = last;
				} else {
					temp = BSGraphs[script]->nodes.head->data;
				}

				if (BSGraphs[script]->nodes.head->data->type->numout<3 && nodeTypesBS[BSPatternNodes[p]].numout<3)
				while (cur) {
					if (cur->data->offset == BSScriptO[script][i] && strcmp(cur->data->type->name, "End")) {
						BSGraphs[script]->connect(temp, cur->data);
						return;
					}
					cur = cur->next;
				}

				BSGraphs[script]->addNode(x, y, BSPatternNodes[p], BSScriptO[script][i]);
				switch (p) {
					default:
						a = getBSPatternArgs(p);
						break;
				}

				for (int j = 0; j<a; j++) {
					BSGraphs[script]->nodes.head->data->args[j] = BSScript[script][i + j + 1];
				}


				i += a;

				if (last) {
					BSGraphs[script]->connect(last, BSGraphs[script]->nodes.head->data);
					last = 0;
				} else {
					BSGraphs[script]->connect(BSGraphs[script]->nodes.head->next->data, BSGraphs[script]->nodes.head->data);
				}

				if (BSGraphs[script]->nodes.head->data->type->numout>1) {

					last = BSGraphs[script]->nodes.head->data;

					int lb = findBSLabel(script, BSScript[script][i]);

					labelBSBranches(last, a - 2, strcmp(BSNames[p], "Check Event") == 0, strcmp(BSNames[p], "Branch on Yes/No") == 0);

					LLNode<BSGraphNode*>* cur = BSGraphs[script]->nodes.head;
					if (BSGraphs[script]->nodes.head->data->type->numout<3)
					while (cur) {
						if (cur->data->offset == BSScript[script][i] && strcmp(cur->data->type->name, "End")) {
							BSGraphs[script]->connect(BSGraphs[script]->nodes.head->data, cur->data);
							lb = -1;
							break;
						}
						cur = cur->next;
					}

					if (lb != -1) {
						int topline = maxline;

						maxline++;
						

						BuildBSGraphLine(script, lb, x + 112, maxline * 96 + 16, BSGraphs[script]->nodes.head->data, bank, bbank);


						LLNode<BSGraphNode*>* curs = BSGraphs[script]->nodes.head;
						while (curs) {
							if (curs->data->y > topline * 96 + 16) {
								curs->data->y -= 96 * (topline - oldline);
								curs->data->y -= 10000;
							}
							curs = curs->next;
						}
						curs = BSGraphs[script]->nodes.head;
						while (curs) {
							if (curs->data->y > oldline * 96 + 16) {
								curs->data->y += 96 * (maxline - topline);
							}
							curs = curs->next;
						}
						curs = BSGraphs[script]->nodes.head;
						while (curs) {
							if (curs->data->y < -100) {
								curs->data->y += 10000;
							}
							curs = curs->next;
						}

					}

				}

				if (checkBSEnd(p)) {
					if (p == 5 || p == 6)return;
					int v;
					if (last)v = last->type->shape;
					else v = BSGraphs[script]->nodes.head->data->type->shape;
					if (v != 3) {
						BSGraphs[script]->addNode(x + 112, y, 1);
						if (last) {
							BSGraphs[script]->connect(last, BSGraphs[script]->nodes.head->data);
							last = 0;
						} else {
							BSGraphs[script]->connect(BSGraphs[script]->nodes.head->next->data, BSGraphs[script]->nodes.head->data);
						}
					}
					return;
				}
				x += 112;
				break;
		}
		i++;
	}
}

void BuildBSGraph(int script) {
	maxline = 0;

	BSGraphs[script]->clear();

	BuildBSGraphLine(script, 0, 128, 16);

	LLNode<BSGraphNode*>* cur = BSGraphs[script]->nodes.head;
	while (cur) {
		if (cur->data->type->shape == 3) {
			cur = cur->next;
			continue;
		}
		if (cur->data->out.size < cur->data->type->numout && cur->data->type->numargs && cur->data->type->numout<3) {

			if (cur->data->offset == 0x1296B2)
				script = script;

			LLNode<BSGraphNode*>* cur2 = BSGraphs[script]->nodes.head;
			while (cur2) {
				if (cur->data->branch < 0)cur->data->branch *= -1;
				if (cur2->data->offset == cur->data->branch && cur->data->branch) {
					BSGraphs[script]->connect(cur->data, cur2->data);

					if (cur->data->brasec && cur->data->out.size > 1) {
						BSGraphNode * temp = cur->data->out.head->data;

						cur->data->out.head->data = cur->data->out.tail->data;
						cur->data->out.tail->data = temp;
					}
				}

				if (cur->data->branch2 < 0)cur->data->branch2 *= -1;
				if (cur2->data->offset == cur->data->branch2 && cur->data->branch2) {
					BSGraphs[script]->connect(cur->data, cur2->data);

					if (cur->data->brasec2 && cur->data->out.size > 1) {
						BSGraphNode * temp = cur->data->out.head->data;

						cur->data->out.head->data = cur->data->out.tail->data;
						cur->data->out.tail->data = temp;
					}
				}

				cur2 = cur2->next;
			}

		}
		cur = cur->next;
	}
}


void LoadBS(char * path, bool single = false) {
	//return;
	unsigned char r, c;
	long o, mo, to;
	int i, j;

	mo = 0;

	for (int i = 0; i < 64; i++) {
		for (int j = 0; j < 768; j++) {
			BSScript[i][j] = 0;
			BSScriptO[i][j] = 0;
		}
	}

	FILE * fp = fopen(path, "rb");


	fseek(fp, 0x128FCE, SEEK_SET);
	fscanf(fp, "%c", &r);
	if (r != 0x4E) {
		BSHeaderOffset = 0x128FD6;
	} else {
		BSHeaderOffset = 0x1EA800;// relocate ***
	}

	fseek(fp, BSHeaderOffset, SEEK_SET);
	for (i = 0; i<NUM_BS; i++) {
		fscanf(fp, "%c", &r);
		fscanf(fp, "%c", &c);
		if (single&&i != subselect[mode][0])continue;
		BSHeader[i] = 256 * r;
		BSHeader[i] += c;
	}

	o = ftell(fp);

	for (i = 0; i<NUM_BS; i++) {
		if (single&&i != subselect[mode][0])continue;
		o = BSHeaderOffset + BSHeader[i];

		int p = 0;
		int c = 0;
		int k;

		for (k = 0; k<128; k++) {
			BSBranches[k] = 0;
		}

		BSBranches[0] = o;
		NumBranches = 1;

		while (NumBranches) {
			p = 0;
			o = 0;
			for (k = 0; k<128; k++) {
				if (BSBranches[k] && (BSBranches[k]<o || !o))o = BSBranches[k];
			}

			fseek(fp, o, SEEK_SET);

			while (!checkBSEnd(p)) {

				o = ftell(fp);
				if (o>mo)mo = o;

				for (k = 0; k<128; k++) {
					if (BSBranches[k] == o) {
						BSScript[i][c] = -2;
						c++;
						BSScript[i][c] = o;
						c++;

						if (c == 0x56 || c == 0x55)
							o = o;

						BSBranches[k] = 0;

						for (int k2 = k; k2 < 127; k2++) {
							BSBranches[k2] = BSBranches[k2 + 1];
						}
						BSBranches[127] = 0;

						NumBranches--;
						for (; k<128; k++) {
							if (BSBranches[k] == o) {
								BSBranches[k] = 0;

								for (int k2 = k; k2 < 127; k2++) {
									BSBranches[k2] = BSBranches[k2 + 1];
								}
								BSBranches[127] = 0;

								NumBranches--;
							}
						}
					}
				}

				if (o == 0x1296B2) {
					o = o;
				}

				bool f = false;
				for (k = 0; k < c; k++) {
					if (BSScriptO[i][k] == o) {
						f = true;
						BSScript[i][c] = -3;
						BSScriptO[i][c] = 0;
						c++;
						BSScript[i][c] = o;
						BSScriptO[i][c] = 0;
						c++;

						BSScript[i][c] = -4;
						BSScriptO[i][c] = 0;
						c++;
						break;
					}
				}
				if (f)break;

				



				p = checkAllBSPatterns(fp);

				if (c == 0x56 || c== 0x55)
					o = o;

				if (p == -1) {
					fseek(fp, o, SEEK_SET);
					char out[512];
					unsigned char r;
					sprintf(out, "Error parsing Battle Start scripts.\n\nPlease submit a screenshot of this message to the forums.\n\nOffset: 0x%X Data:\n\n", o);
					for (i = 0; i<32; i++) {
						fscanf(fp, "%c", &r);
						sprintf(out, "%s%.2hX", out, r);
					}
					MessageBox(NULL, out, "Error", MB_OK);
					fclose(fp);
					return;
				}

				if (!strcmp(BSNames[p], "Branch")) {
					BSScript[i][c] = -3;
					BSScriptO[i][c] = 0;
					c++;
					BSScript[i][c] = BSArgs[1];
					BSScriptO[i][c] = 0;
					c++;
					continue;
				}

				BSScript[i][c] = p;
				BSScriptO[i][c] = o;
				c++;
				for (j = 0; j<NumArgs; j++) {
					BSScript[i][c] = BSArgs[j];

					if (c == 0x56 || c == 0x55)
						o = o;

					c++;
				}

				j = 0;
				for (k = 0; k<128; k++) {
					if (BSBranches[k])j = k + 1;
				}

				switch (BSPatterns[p][BSLength[p] - 3]) {
					case -21:
						if (BSPatterns[p][BSLength[p] - 2] == 0) {
							to = BSArgs[getBSPatternArgs(p) - 1];
							if (to > o) {
								switch (to) {
									case 0x18074:
									case 0x1808A:
									case 0x180B4:

										break;
									default:
										BSBranches[j] = to;//+ftell(fp)-2;
										NumBranches++;
										break;
								}
							} else
								to=to;

						}
						break;
				}
				switch (BSPatterns[p][BSLength[p] - 2]) {
					case -21:
						if (BSPatterns[p][BSLength[p] - 1] == -1) {
							to = BSArgs[getBSPatternArgs(p) - 1];
							if (to>o){
								switch (to) {
									case 0x18074:
									case 0x1808A:
									case 0x180B4:

										break;
									default:
										BSBranches[j] = to;//+ftell(fp)-2;
										NumBranches++;
										break;
								}
							} else
								to = to;
						}
						break;
				}

				for (int k = 0; k < BSLength[p]; k++) {
					if (BSPatterns[p][k] == -30) {

						int sarg = getBSPatternArgs(p) - 1;

						for (int iarg = sarg; iarg < NumArgs; iarg++) {
							to = BSArgs[iarg];

							for (k = 0; k < j; k++) {
								if (BSBranches[j] == BSBranches[k]) {
									to = 0;
									break;
								}
							}
							if (to>o){
								if (to) {
									BSBranches[j] = to;
									NumBranches++;
									j++;
								}
							} else
								to = to;
						}
						break;
					}
				}

				if (BSBranches[j])
					for (k = 0; k<j; k++) {
						if (BSBranches[j] == BSBranches[k]) {
							BSBranches[j] = 0;
							NumBranches--;
							k = j;
						}
					}
			}
		}
		BSScript[i][c] = -1;
		BuildBSGraph(i);
	}
	o = ftell(fp);

	mo = mo;
	fclose(fp);
}
