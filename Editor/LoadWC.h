int WCHeader[256];
int WCScript[64][768];
long WCScriptO[64][768];
unsigned char * WCScriptE[64][768];

long WCHeaderOffset;
long WCSpriteOffset;

int WCPatterns[512][512];
int NumWCPatterns = 0;
int WCLength[512];
char WCNames[512][32];
int WCPatternNodes[512];

int WCArgs[16];
//int NumArgs = 0;
int WCBranches[128];
//int NumBranches = 0;

WCGraph * WCGraphs[64];
unsigned char WCSprites[64];

void addWCPattern(int len, int node, char * name, ...) {
	va_list vl;
	va_start(vl, name);
	int c = 0;
	for (int i = 0; i<len; i++) {
		WCPatterns[NumWCPatterns][c] = va_arg(vl, int);
		c++;
	}
	sprintf(WCNames[NumWCPatterns], name);
	WCLength[NumWCPatterns] = len;
	WCPatternNodes[NumWCPatterns] = node;
	NumWCPatterns++;
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
bool checkWCEnd(FILE * fp);

bool checkWCPattern(FILE * fp, int pat) {
	int r = 0;
	int r2 = 0;
	int t, k;
	int v;
	long o, o2;
	NumArgs = 0;
	int lastarg = 0;
	for (int i = 0; i<WCLength[pat]; i++) {
		fscanf(fp, "%c", &r);
		t = WCPatterns[pat][i];
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
				switch (WCArgs[NumArgs - 1]) {
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
				WCArgs[NumArgs] = o + v - 1;
				NumArgs++;
				for (int j = 1; j < v / 2; j++) {
					int v2 = 0;
					for (int j2 = 0; j2 <= k; j2++) {
						fscanf(fp, "%c", &r);
						v2 *= 256;
						v2 += r;
					}
					if (v2 < v)v = v2;
					WCArgs[NumArgs] = o + v2 - 1;

					NumArgs++;
				}
			} else {
				WCArgs[NumArgs] = v;
				NumArgs++;
			}

			if (t<5) {

			} else if (t<9) {
				i++;
				if (NumArgs&&lastarg>20 && lastarg<25) {
					if (v != WCPatterns[pat][i])return false;
				} else {
					if (o - 1 + v != WCPatterns[pat][i])return false;
					WCArgs[NumArgs - 1] = o - 1 + v;
				}
			} else if (t<13) {
				i++;
				if (v != WCPatterns[pat][i])return false;
			} else if (t<17) {
				o2 = ftell(fp);
				fseek(fp, v, SEEK_SET);
				fscanf(fp, "%c", &r);
				fscanf(fp, "%c", &r2);

				if (r == 0x60) {
					fseek(fp, o + v, SEEK_SET);
					if (!checkWCEnd(fp))return false;
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
				WCArgs[NumArgs] = o + v - k;
				//negative branch
				if (!strcmp(WCNames[pat], "Branch"))
					fseek(fp, o + v - k, SEEK_SET);
			}
			lastarg = t;
		}
	}
	return true;
}

bool checkWCEnd(FILE * fp) {
	unsigned long o = ftell(fp);
	for (int i = 0; i<NumWCPatterns; i++) {
		if (!strcmp("End", WCNames[i])) {
			fseek(fp, o, SEEK_SET);
			if (checkWCPattern(fp, i))return true;
		}
		if (!strcmp("Trigger Exit", WCNames[i])) {
			fseek(fp, o, SEEK_SET);
			if (checkWCPattern(fp, i))return true;
		}
	}
	return false;
}

bool checkWCEnd(int p) {
	if (p == NumWCPatterns - 2 || p == NumWCPatterns - 3)
		return false;
	if (!strcmp("End", WCNames[p]))return true;
	if (!strcmp("Trigger Exit", WCNames[p]))return true;
	//if (WCPatterns[p][0] == 0x60)return true;
	//if (WCPatterns[p][0] == -21 && WCArgs[0] == 0x60)return true;
	if (WCPatterns[p][WCLength[p] - 2] == 0x4E && WCPatterns[p][WCLength[p] - 1] == 0xD5)
		return true;
	if (WCPatterns[p][WCLength[p] - 1] == -30)return true;
	return false;
}

int checkAllWCPatterns(FILE * fp) {
	unsigned long o = ftell(fp);
	for (int i = 0; i<NumWCPatterns; i++) {
		//if (!strcmp(WCNames[i], "Trigger Exit"))
			//i = i;
		fseek(fp, o, SEEK_SET);
		if (checkWCPattern(fp, i))
			return i;
	}
	return -1;
}

int getWCPatternArgs(int pat) {
	int c = 0;
	for (int i = 0; i<WCLength[pat]; i++) {
		if (WCPatterns[pat][i]<0) {
			c++;
		}
	}
	return c;
}

void addWCNodeType(char * n, int s, char * l = "", char * l2 = "", char * l3 = "", char * l4 = "", int al = -1, int an = 0) {
	nodeTypesWC[NumWCNodeTypes].set(n, s, l, l2, l3, l4, al, an);
	NumWCNodeTypes++;
}

void setWCNodeOuts(int n, char * l = "", char * l2 = "", char * l3 = "", char * l4 = "") {
	nodeTypesWC[NumWCNodeTypes - 1].setout(n, l, l2, l3, l4);
}

void setWCNodeArgs(int n, int t = -1, char * l = "", int t2 = -1, char * l2 = "", int t3 = -1, char * l3 = "", int t4 = -1, char * l4 = "") {
	nodeTypesWC[NumWCNodeTypes - 1].setargs(n, t, l, t2, l2, t3, l3, t4, l4);
}

void setWCNodeHelp(char * h) {
	nodeTypesWC[NumWCNodeTypes - 1].setHelpText(h);
}


void initWC() {
	int i;
	for (i = 0; i<NUM_WC; i++) {
		WCGraphs[i] = new WCGraph(240, 50, 640, 480);
	}

	addWCNodeType("Start", 2, "Start");
	addWCNodeType("End", 3, "End");

	addWCNodeType("Set Event", 0, "Set", "Event", "", "", 3, 0);
		setWCNodeArgs(1, ARG_WORD, "Event Number");
		setWCNodeHelp("Sets an event number as completed.\n\nEvent Number: Event to set");

	addWCNodeType("Clear Event", 0, "Clear", "Event", "", "", 3, 0);
		setWCNodeArgs(1, ARG_WORD, "Event Number");
		setWCNodeHelp("Clears the completed state of an event number.\n\nEvent Number: Event to clear");

	addWCNodeType("Show Message Window", 0, "Show", "Message", "Window", "");
		setWCNodeHelp("Opens the message window.");

	addWCNodeType("Reset Message Window", 0, "Reset", "Message", "Window", "");
		setWCNodeHelp("Reset the message window, loading its graphics and clearing text/position.");

	addWCNodeType("Display Message", 0, "Display", "Message", "", "", 3, 0);
		setWCNodeArgs(1, ARG_MESSAGE, "Message Number");
		setWCNodeHelp("Displays a message to the screen.\n\nMessage Number: Message number to display.");

	addWCNodeType("Close Message Window", 0, "Close", "Message", "Window", "");
		setWCNodeHelp("Closes the message window.");

	addWCNodeType("More Text Prompt", 0, "More", "Text");
		setWCNodeHelp("Pauses the message and displays the flashing arrow indicating more text to follow.");

	addWCNodeType("Wait Frames", 0, "Wait", "Frames", "", "", 3, 0);
		setWCNodeArgs(1, ARG_BYTE, "Frames");
		setWCNodeHelp("Runs the game for a while.\n\nFrames: Number of frames to advance.");


	addWCNodeType("Check Event", 1, "Check", "Event", "", "", 2, 0);
		setWCNodeOuts(2, "Clear", "Set");
		setWCNodeArgs(4, ARG_WORD, "Event Number", ARG_IGNORE, "", ARG_SBRANCH, "Branch On", ARG_IGNORE, "");
		setWCNodeHelp("Branches the script depending on whether a specific event has been set.\n\nEvent Number: Event to check");


	addWCNodeType("Initialize Cursor?", 0, "Initialize", "Cursor", "", "");
		setWCNodeHelp("Gets the battle cursor ready?");

	addWCNodeType("Check Character Present", 1, "Check", "Character", "Present", "", 3, 0);
		setWCNodeOuts(2, "Not Present", "Present");
		setWCNodeArgs(4, ARG_WORD, "Character Number", ARG_IGNORE, "", ARG_BRANCH, "", ARG_IGNORE, "");
		setWCNodeHelp("Branches the script depending on whether a member is present.\n\Character Number: Character to check");

	addWCNodeType("Set Active Member", 0, "Set", "Active", "Member", "");
		setWCNodeArgs(1, ARG_BYTE, "Member");
		setWCNodeHelp("Sets the active member based on their position in the battle list.");

	addWCNodeType("Get Speaking Sound", 0, "Get", "Speaking", "Sound", "");
		setWCNodeHelp("Gets the proper speaking sound for the selected character. Only use after a member present check.");

	addWCNodeType("Set Speaking Sound", 0, "Set", "Speaking", "Sound", "");
		setWCNodeArgs(1,ARG_BYTE,"Map Sprite");
		setWCNodeHelp("Sets the speaking sound to the sound for the chosen map sprite.");

	addWCNodeType("Set Portrait",0,"Set","Portrait","","",3,0);//10
		setWCNodeArgs(1,ARG_BYTE,"Portrait");
		setWCNodeHelp("Sets the portrait to be displayed with a message.\n\nPortrait: The gfx number of the portrait to display");


	addWCNodeType("Cursor to Character", 0, "Cursor", "to", "Character", "");
		setWCNodeHelp("Moves the screen and cursor to the current character. Only use after a member present check.");

	addWCNodeType("Move Cursor", 0, "Move", "Cursor", "", "");
		setWCNodeArgs(2, ARG_BYTE, "X", ARG_BYTE, "Y");
		setWCNodeHelp("Moves the screen and cursor to the chosen position.");

	addWCNodeType("Set Sprite Direction", 0, "Set Sprite", "Direction", "", "", 3, 0);
		setWCNodeArgs(1, ARG_DIR, "Direction");
		setWCNodeHelp("Changes the direction of the current character.");

	addWCNodeType("Move Sprite", 0, "Move", "Sprite", "", "", 3, 1);
		setWCNodeArgs(2, ARG_DIR, "Direction", ARG_BYTE, "Squares");
		setWCNodeHelp("Moves current character a number of squares in the chosen direction.");

	addWCNodeType("Move and Change Sprite", 0, "Move", "and", "Change", "Sprite");
		setWCNodeArgs(2, ARG_DIR, "Direction", ARG_BYTE, "Squares", ARG_WORD, "Map Sprite");
		setWCNodeHelp("Moves current character a number of squares in the chosen direction and also overrides its map sprite.");

	addWCNodeType("Step and Change Sprite", 0, "Step", "and", "Change", "Sprite");
		setWCNodeArgs(2, ARG_DIR, "Direction", ARG_WORD, "Map Sprite");
		setWCNodeHelp("Moves current character one square in the chosen direction and also overrides its map sprite.");

	addWCNodeType("Flicker Member", 0, "Flicker", "Member", "", "");
		setWCNodeHelp("Flickers the current member's sprite, used before removing to fade out. Only use after a member present check.");

	addWCNodeType("Remove Member", 0, "Remove", "Member", "", "");
		setWCNodeHelp("Removes the current character from the battle. Only use after a member present check.");

	addWCNodeType("Initialize Earthquake", 0, "Initialize", "Earthquake", "", "");
		setWCNodeHelp("Begins an earthquake animation. Does not need a 'Prepare for Animation'");

	addWCNodeType("Initialize Earthquake 2", 0, "Initialize", "Earthquake", "", "");
		setWCNodeHelp("Begins an earthquake animation. Needs a 'Prepare for Animation'");

	addWCNodeType("Set Earthquake Strength", 0, "Set", "Earthquake", "Strength", "", 3, 0);
		setWCNodeArgs(1, ARG_WORD, "Strength");
		setWCNodeHelp("Changes the strength of the earthquake animation.");

	addWCNodeType("Initialize 'No Sprite Update'", 0, "Initialize", "No", "Sprite", "Update");
		setWCNodeHelp("Begins an animation state where map sprites stop walking in place and don't revert to their normal sprites if altered.");

	addWCNodeType("Prepare for Animation", 0, "Prepare", "Animation", "", "");
		setWCNodeHelp("Backs up and clears the current frame routine in preparation for certain animations.");

	addWCNodeType("End Animation", 0, "End", "Animation", "", "");
		setWCNodeHelp("Ends animations like earthquake.");

	addWCNodeType("Flash Screen", 0, "Flash", "Screen", "", "");
		setWCNodeHelp("Rapidly flashes screen white several times.");

	addWCNodeType("Set Copy Location", 0, "Set", "Copy", "Location", "");
		setWCNodeArgs(4, ARG_BYTE, "X Source", ARG_BYTE, "Y Source", ARG_BYTE, "X Target", ARG_BYTE, "Y Target");
		setWCNodeHelp("Sets up the location to copy tiles from and to on the map.");

	addWCNodeType("Copy Tiles", 0, "Copy", "Tiles", "", "");
		setWCNodeArgs(2, ARG_BYTE, "Width", ARG_BYTE, "Height");
		setWCNodeHelp("Copies a rectangle of tiles from one part of the map to another.");

	addWCNodeType("Change B7C6?", 0, "Change", "B7C6", "", "", 3, 0);
		setWCNodeArgs(1, ARG_WORD, "?");
		setWCNodeHelp("?");

	addWCNodeType("Clear B7C6?", 0, "Clear", "B7C6", "", "", 3, 0);
		setWCNodeHelp("?");

	addWCNodeType("Play Sound", 0, "Play", "Sound", "", "", 3, 0);
		setWCNodeArgs(1, ARG_WORD, "Sound Effect");
		setWCNodeHelp("Plays a sound effect.");

	addWCNodeType("Wait for Sound", 0, "Wait", "For", "Sound", "");
		setWCNodeHelp("Waits for sound to finish playing.");

	addWCNodeType("Reduce Earthquake Strength", 1, "Reduce", "Earthquake", "Strength", "");
		setWCNodeOuts(2, "Equal", "Not Equal");
		setWCNodeArgs(2, ARG_BRANCH, "Branch On", ARG_IGNORE, "");
		setWCNodeHelp("Reduces strength by one and then branches if it is not zero.");

	addWCNodeType("Dark Dragon Anim 1", 0, "Dark", "Dragon", "Anim", "1");
		setWCNodeHelp("Animates the palettes for when dark dragon fails to emerge in the second to last battle.");

	addWCNodeType("Run Scripted Movement", 0, "Run", "Scripted", "Movement", "");
		setWCNodeArgs(2, ARG_MOVEMENT, "", ARG_BYTE, "Target");
		setWCNodeHelp("Makes the target character run through a series of movements.");

	addWCNodeType("End Cutscene", 0, "End", "Cutscene", "", "");
		setWCNodeHelp("Ends the cutscene and returns to normal game flow.");

	addWCNodeType("Trigger Exit", 0, "Trigger", "Exit", "", "", 3, 0);
		setWCNodeArgs(1, ARG_BYTE, "Target");
		setWCNodeHelp("Leaves the map by the chosen exit and ends the script.");


	for (i = 0; i<NUM_WC; i++) {
		WCGraphs[i]->addNode(16, 16);

		WCGraphs[i]->buildList();
	}

	addWCPattern(7, 2, "Set Event", 0x30, 0x3C, -2, 0x4E, 0xB9, -12, 0x38C);
	addWCPattern(6, 2, "Set Event", 0x70, -1, 0x4E, 0xB9, -12, 0x38C);
	addWCPattern(6, 2, "Set Event", 0x70, -1, 0x61, 0, -6, 0x38C);
	addWCPattern(7, 3, "Clear Event", 0x30, 0x3C, -2, 0x4E, 0xB9, -12, 0x390);
	addWCPattern(6, 3, "Clear Event", 0x70, -1, 0x4E, 0xB9, -12, 0x390);
	addWCPattern(6, 3, "Clear Event", 0x70, -1, 0x61, 0, -6, 0x390);
	addWCPattern(2, 4, "Show Message Window", 0x4E, 0x45);
	addWCPattern(4, 5, "Reset Message Window", 0x4E, 0xB9, -12, 0x8030);
	addWCPattern(5, 6, "Display Message", 0x30, 0x3C, -2, 0x4E, 0x48);

	addWCPattern(2, 7, "Close Message Window", 0x4E, 0x46);

	addWCPattern(2, 8, "More Text Prompt", 0x4E, 0x47);

	addWCPattern(8, 9, "Wait Frames", 0x70, -1, 0x4E, 0xB9, 0, 0, 0x02, 0x44);
	addWCPattern(10, 9, "Wait Frames", 0x30, 0x3C, 0, -1, 0x4E, 0xB9, 0, 0, 0x02, 0x44);
	
	addWCPattern(10, 10, "Check Event", 0x30, 0x3C, -2, 0x4E, 0xB9, -12, 0x394, -21, 0, -2);
	addWCPattern(9, 10, "Check Event", 0x70, -1, 0x4E, 0xB9, -12, 0x394, -21, 0, -2);
	addWCPattern(8, 10, "Check Event", 0x70, -1, 0x4E, 0xB9, -12, 0x394, -21, -1);
	addWCPattern(9, 10, "Check Event", 0x70, -1, 0x61, 0, -6, 0x394, -21, 0, -2);
	addWCPattern(8, 10, "Check Event", 0x70, -1, 0x61, 0, -6, 0x394, -21, -1);

	addWCPattern(4, 11, "Initialize Battle Cursor", 0x4E, 0xB9, -12, 0x8094);

	addWCPattern(12, 12,  "Check Member Present", 0x34, 0x3C, -2, 0x4E, 0xB9, -12, 0x12BFB6, 0x4A, 0x40,-21, 0, -2);
	addWCPattern(11, 12,  "Check Member Present", 0x34, 0x3C, -2, 0x4E, 0xB9, -12, 0x12BFB6, 0x4A, 0x40,-21, -1);
	addWCPattern(12, 12,  "Check Member Present", 0x34, 0x3C, -2, 0x61, 0, -6,     0x12BFB6, 0x4A, 0x40,-21, 0, -2);
	addWCPattern(11, 12,  "Check Member Present", 0x34, 0x3C, -2, 0x61, 0, -6,     0x12BFB6, 0x4A, 0x40,-21, -1);

	addWCPattern(6, 13, "Set Active Character", 0x70, -1, 0x4E, 0xB9, -12, 0x20054);

	addWCPattern(4, 14, "Get Speaking Sound", 0x4E, 0xB9, -12, 0x12C342);
	addWCPattern(4, 14, "Get Speaking Sound", 0x61, 0, -6, 0x12C342);

	addWCPattern(6, 15, "Set Speaking Sound", 0x72, -1, 0x4E, 0xB9, -12, 0x12C34E);
	addWCPattern(6, 15, "Set Speaking Sound", 0x72, -1, 0x61, 0, -6, 0x12C34E);

	addWCPattern(6, 16, "Set Portrait", 0x70, -1, 0x4E, 0xB9, -12, 0x802C);

	addWCPattern(38, 17, "Cursor to Character", 0x4E, 0xB9, -12, 0x20058, 0xE1, 0X49, 0x3C, 0x01, 0x4E, 0xB9, -12, 0x2005C, 0x8C, 0x41, 0x30, 0x06, 0x4E, 0xB9, -12, 0x8098, 0x33, 0xFC, 0, 0x01, 0, 0xFF, 0x0C, 0x98, 0x23, 0xFC, 0, 0x01, 0x0F, 0x3F, 0, 0xFF, 0x0E, 0x30);
	addWCPattern(38, 17, "Cursor to Character", 0x4E, 0xB9, -12, 0x20058, 0xE1, 0X49, 0x3C, 0x01, 0x4E, 0xB9, -12, 0x2005C, 0x8C, 0x41, 0x30, 0x06, 0x4E, 0xB9, -12, 0x8098, 0x33, 0xFC, 0, 0x01, 0, 0xFF, 0x0C, 0x98, 0x23, 0xFC, 0, 0x01, 0x0F, 0x3F, 0, 0xFF, 0x0E, 0x30);

	addWCPattern(16, 18, "Move Cursor", 0x32, 0x3C, 0, -1, 0x30, 0x3C, 0, -1, 0xE1, 0x49, 0x80, 0x41, 0x4E, 0xB9, -12, 0x8098);

	addWCPattern(8, 19, "Set Direction", 0x34, 0x3C, 0, -1, 0x4E, 0xB9, -12, 0x12C2DC);
	addWCPattern(8, 19, "Set Direction", 0x34, 0x3C, 0, -1, 0x61, 0, -6, 0x12C2DC);

	addWCPattern(8, 20, "Move Sprite", 0x74, -1, 0x72, -1, 0x4E, 0xB9, -12, 0x12C0AE);
	addWCPattern(8, 20, "Move Sprite", 0x74, -1, 0x72, -1, 0x61, 0, -6, 0x12C0AE);

	addWCPattern(11, 21, "Move Sprite and Change", 0x74, -1, 0x72, -1, 0x36, 0x3C, -2, 0x4E, 0xB9, -12, 0x12C09E);
	addWCPattern(11, 21, "Move Sprite and Change", 0x74, -1, 0x72, -1, 0x36, 0x3C, -2, 0x61, 0, -6, 0x12C09E);

	addWCPattern(11, 22, "Step Sprite and Change", 0x34, 0x3C, 0, -1, 0x36, 0x3C, -2, 0x4E, 0xB9, -12, 0x12C2BE);
	addWCPattern(11, 22, "Step Sprite and Change", 0x34, 0x3C, 0, -1, 0x36, 0x3C, -2, 0x61, 0, -6, 0x12C2BE);

	addWCPattern(4, 23, "Flicker Member", 0x4E, 0xB9, -12, 0x12C036);
	addWCPattern(4, 23, "Flicker Member", 0x61, 0, -6, 0x12C036);

	addWCPattern(6, 24, "Remove Member", 0x72, 0xFF, 0x4E, 0xB9, -12, 0x20104);

	addWCPattern(20, 25, "Initialize Earthquake", 0x2F, 0x39, 0, 0xFF, 0x0E, 0xF6, 0x4E, 0xB9, -12, 0x12C312, 0x23, 0xFC, 0, 0x12, 0xC3, 0x6E, 0, 0xFF, 0x0E, 0xF6);
	addWCPattern(20, 25, "Initialize Earthquake", 0x2F, 0x39, 0, 0xFF, 0x0E, 0xF6, 0x61, 0, -6, 0x12C312, 0x23, 0xFC, 0, 0x12, 0xC3, 0x6E, 0, 0xFF, 0x0E, 0xF6);
	
	addWCPattern(32, 26, "Initialize Earthquake 2", 0x33, 0xFC, 0, 0x01, 0, 0xFF, 0x0C, 0x98, 0x23, 0xFC, 0, 0x01, 0x0F, 0x3F, 0, 0xFF, 0x0E, 0x30, 0x4E, 0xB9, -12, 0x12C312, 0x23, 0xFC, 0, 0x12, 0xC3, 0x6E, 0, 0xFF, 0x0E, 0xF6);
	addWCPattern(32, 26, "Initialize Earthquake 2", 0x33, 0xFC, 0, 0x01, 0, 0xFF, 0x0C, 0x98, 0x23, 0xFC, 0, 0x01, 0x0F, 0x3F, 0, 0xFF, 0x0E, 0x30, 0x61, 0, -6, 0x12C312, 0x23, 0xFC, 0, 0x12, 0xC3, 0x6E, 0, 0xFF, 0x0E, 0xF6);

	addWCPattern(5, 27, "Set Earthquake Strength", 0x31,0xFC, -2, 0xB7, 0xC4);

	addWCPattern(16, 28, "Initialize No Sprite Walk", 0x2F, 0x39, 0, 0xFF, 0x0E, 0xF6, 0x23, 0xFC, 0, 0, 0x80, 0x34, 0, 0xFF, 0x0E, 0xF6);

	addWCPattern(12, 29, "Prepare for Animation", 0x2F, 0x39, 0, 0xFF, 0x0E, 0xF6, 0x42, 0xB9, 0, 0xFF, 0x0E, 0xF6);

	addWCPattern(6, 30, "End Animation", 0x23, 0xDF, 0, 0xFF, 0x0E, 0xF6);

	addWCPattern(4, 31, "Flash Screen", 0x4E, 0xB9, -12, 0x128F98);
	addWCPattern(4, 31, "Flash Screen", 0x61, 0, -6, 0x128F98);

	addWCPattern(8, 32, "Set Copy Location", 0x72, -1, 0x74,-1, 0x76, -1, 0x78, -1);

	addWCPattern(8, 33, "Copy Tiles", 0x7A, -1, 0x7C, -1, 0x4E, 0xB9, -12, 0x80AC);

	addWCPattern(5, 34, "B7C6?", 0x31, 0xFC, -2, 0xB7, 0xC6);

	addWCPattern(4, 35, "B7C6?", 0x42, 0x78, 0xB7, 0xC6);

	addWCPattern(3, 36, "Play Sound", 0x4E, 0x40, -2);
	addWCPattern(4, 37, "Wait for Sound", 0x4E, 0xB9, -12, 0x240);

	addWCPattern(7, 38, "Reduce Earthquake Strength", 0x53, 0x78, 0xB7, 0xC4, -21, 0, -2);
	addWCPattern(6, 38, "Reduce Earthquake Strength", 0x53, 0x78, 0xB7, 0xC4, -21, -1);

	addWCPattern(34, 39, "Dark Dragon Anim 1", 0x41, 0xFA, 0xFF, 0x46, 0x42, 0x40, 0x10, 0x18, 0x6B, 0x1A, 0x2F, 0x08, 0x4E, 0xB9, -12, 0x12B598, 0x20, 0x5F, 0x42, 0x40, 0x10, 0x18, 0x2F, 0x08, 0x4E, 0xB9, 0, 0, 0x02, 0x44, 0x20, 0x5F, 0x60, 0xE0);
	addWCPattern(34, 39, "Dark Dragon Anim 1", 0x41, 0xFA, 0xFF, 0x46, 0x42, 0x40, 0x10, 0x18, 0x6B, 0x18, 0x2F, 0x08, 0x61, 0, -6, 0x12B598, 0x20, 0x5F, 0x42, 0x40, 0x10, 0x18, 0x2F, 0x08, 0x4E, 0xB9, 0, 0, 0x02, 0x44, 0x20, 0x5F, 0x60, 0xE2);

	addWCPattern(13, 40, "Run Scripted Movement", 0x41, 0xFA, -2, 0x11, 0xFC, 0, -1, 0xB4, 0xC5, 0x4E, 0xB9, -12, 0x12C404);
	addWCPattern(13, 40, "Run Scripted Movement", 0x41, 0xFA, -2, 0x11, 0xFC, 0, -1, 0xB4, 0xC5, 0x61, 0, -6, 0x12C404);

	addWCPattern(8, 41, "End Cutscene", 0x72, 0xFF, 0x70, 0x38, 0x4E, 0xB9, -12, 0x384);
	addWCPattern(6, 41, "End Cutscene", 0x70, 0x38, 0x4E, 0xB9, -12, 0x384);

	addWCPattern(10, 42, "Trigger Exit", 0x11, 0xFC, 0, -1, 0x9C, 0x02, 0x4E, 0xF9, -12, 0x12BF66);
	addWCPattern(10, 42, "Trigger Exit", 0x11, 0xFC, 0, -1, 0x9C, 0x02, 0x60, 0, -6, 0x12BF66);

	AdvancedNodes(WC, 43)

	addWCPattern(2, 1, "End", 0x60, -13);
	addWCPattern(3, 1, "End", 0x60, 0, -14);

	addWCPattern(3, 1, "Branch", 0x60, 0, -26);//just follow, shouldn't create a node
	addWCPattern(2, 1, "Branch", 0x60, -25);

	addWCPattern(3, 1, "Branch", 0x60, 0, -18);//just follow, shouldn't create a node
	addWCPattern(2, 1, "Branch", 0x60, -17);

	addWCPattern(2, 1, "End", 0x4E, 0x75);



}

int findWCLabel(int script, int label) {
	int i = 0;
	int p;
	while (WCScript[script][i] != -1) {
		p = WCScript[script][i];
		switch (p) {
			case -2:
				i++;
				if (WCScript[script][i] == label)return i + 1;
				break;
			case -3:
				i++;
				break;
			case -4:
				break;
			default:
				i += getWCPatternArgs(p);
				break;
		}
		i++;
	}
	return -1;
}

void labelWCBranches(WCGraphNode * node, int arg, bool set = false, bool yn = false) {
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


void BuildWCGraphLine(int script, int start, int sx, int sy, WCGraphNode * prev = 0, int b = 0, int bb = 0) {

	WCGraphNode * last = prev;

	int i = start;

	int x = sx;
	int y = sy;

	int p, a;

	int bank = b;
	int bbank = bb;

	int oldline = maxline;

	while (WCScript[script][i] != -1) {
		p = WCScript[script][i];
		/*if(p==NumWCPatterns-2||p==NumWCPatterns-3){
		i+=2;
		continue;
		}*/
		switch (p) {
			case -2:
				i++;
				break;
			case -3:
				i++;
				if (last && last != WCGraphs[script]->nodes.head->data) {
					if (last->branch && last->branch != WCScript[script][i]) {
						last->branch2 = WCScript[script][i];
						last->brasec2 = false;
					} else {
						last->branch = WCScript[script][i];
						last->brasec = false;
					}
				} else {
					if (WCGraphs[script]->nodes.head->data->branch && WCGraphs[script]->nodes.head->data->branch != WCScript[script][i]) {
						WCGraphs[script]->nodes.head->data->branch2 = WCScript[script][i];
						WCGraphs[script]->nodes.head->data->brasec2 = true;
					} else {
						WCGraphs[script]->nodes.head->data->branch = WCScript[script][i];
						WCGraphs[script]->nodes.head->data->brasec = true;
					}
				}
				break;
			case -4:
				return;
			default:
				LLNode<WCGraphNode*>* cur = WCGraphs[script]->nodes.head;

				WCGraphNode * temp;
				if (last && last != WCGraphs[script]->nodes.head->data) {
					temp = last;
				} else {
					temp = WCGraphs[script]->nodes.head->data;
				}

				if (WCGraphs[script]->nodes.head->data->type->numout<3 && nodeTypesWC[WCPatternNodes[p]].numout<3)
				while (cur) {
					if (cur->data->offset == WCScriptO[script][i] && strcmp(cur->data->type->name, "End")) {
						WCGraphs[script]->connect(temp, cur->data);
						return;
					}
					cur = cur->next;
				}

				WCGraphs[script]->addNode(x, y, WCPatternNodes[p], WCScriptO[script][i]);
				switch (p) {
					default:
						a = getWCPatternArgs(p);
						break;
				}

				for (int j = 0; j<a; j++) {
					WCGraphs[script]->nodes.head->data->args[j] = WCScript[script][i + j + 1];
				}


				if (!strcmp(WCGraphs[script]->nodes.head->data->type->name, "Run Scripted Movement")) {
					if (WCGraphs[script]->nodes.head->data->extra)delete WCGraphs[script]->nodes.head->data->extra;

					WCGraphs[script]->nodes.head->data->extra = WCScriptE[script][i];


				}



				i += a;

				if (last) {
					WCGraphs[script]->connect(last, WCGraphs[script]->nodes.head->data);
					last = 0;
				} else {
					WCGraphs[script]->connect(WCGraphs[script]->nodes.head->next->data, WCGraphs[script]->nodes.head->data);
				}

				if (WCGraphs[script]->nodes.head->data->type->numout>1) {

					last = WCGraphs[script]->nodes.head->data;

					int lb = findWCLabel(script, WCScript[script][i]);

					labelWCBranches(last, a - 2, strcmp(WCNames[p], "Check Event") == 0, strcmp(WCNames[p], "Branch on Yes/No") == 0);

					LLNode<WCGraphNode*>* cur = WCGraphs[script]->nodes.head;
					if (WCGraphs[script]->nodes.head->data->type->numout<3)
					while (cur) {
						if (cur->data->offset == WCScript[script][i] && strcmp(cur->data->type->name, "End")) {
							WCGraphs[script]->connect(WCGraphs[script]->nodes.head->data, cur->data);
							lb = -1;
							break;
						}
						cur = cur->next;
					}

					if (lb != -1) {
						int topline = maxline;

						maxline++;
						

						BuildWCGraphLine(script, lb, x + 112, maxline * 96 + 16, WCGraphs[script]->nodes.head->data, bank, bbank);

						LLNode<DialogGraphNode*>* curs = DialogGraphs[script]->nodes.head;
						while (curs) {
							if (curs->data->y > topline * 96 + 16) {
								curs->data->y -= 96 * (topline - oldline);
								curs->data->y -= 10000;
							}
							curs = curs->next;
						}
						curs = DialogGraphs[script]->nodes.head;
						while (curs) {
							if (curs->data->y > oldline * 96 + 16) {
								curs->data->y += 96 * (maxline - topline);
							}
							curs = curs->next;
						}
						curs = DialogGraphs[script]->nodes.head;
						while (curs) {
							if (curs->data->y < -100) {
								curs->data->y += 10000;
							}
							curs = curs->next;
						}
					}

				}

				if (checkWCEnd(p)) {
					if (p == 5 || p == 6)return;
					int v;
					if (last)v = last->type->shape;
					else v = WCGraphs[script]->nodes.head->data->type->shape;
					if (v != 3) {
						WCGraphs[script]->addNode(x + 112, y, 1);
						if (last) {
							WCGraphs[script]->connect(last, WCGraphs[script]->nodes.head->data);
							last = 0;
						} else {
							WCGraphs[script]->connect(WCGraphs[script]->nodes.head->next->data, WCGraphs[script]->nodes.head->data);
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

void BuildWCGraph(int script) {
	maxline = 0;

	WCGraphs[script]->clear();

	BuildWCGraphLine(script, 0, 128, 16);

	LLNode<WCGraphNode*>* cur = WCGraphs[script]->nodes.head;
	while (cur) {
		if (cur->data->type->shape == 3) {
			cur = cur->next;
			continue;
		}
		if (cur->data->out.size < cur->data->type->numout && cur->data->type->numargs && cur->data->type->numout<3) {


			LLNode<WCGraphNode*>* cur2 = WCGraphs[script]->nodes.head;
			while (cur2) {
				if (cur->data->branch < 0)cur->data->branch *= -1;
				if (cur2->data->offset == cur->data->branch && cur->data->branch) {
					WCGraphs[script]->connect(cur->data, cur2->data);

					if (cur->data->brasec && cur->data->out.size > 1) {
						WCGraphNode * temp = cur->data->out.head->data;

						cur->data->out.head->data = cur->data->out.tail->data;
						cur->data->out.tail->data = temp;
					}
				}

				if (cur->data->branch2 < 0)cur->data->branch2 *= -1;
				if (cur2->data->offset == cur->data->branch2 && cur->data->branch2) {
					WCGraphs[script]->connect(cur->data, cur2->data);

					if (cur->data->brasec2 && cur->data->out.size > 1) {
						WCGraphNode * temp = cur->data->out.head->data;

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


void LoadWC(char * path, bool single = false) {
	//return;
	unsigned char r, c;
	long o, mo, to;
	int i, j;

	mo = 0;

	for (int i = 0; i < 64; i++) {
		for (int j = 0; j < 768; j++) {
			WCScript[i][j] = 0;
			WCScriptO[i][j] = 0;
		}
		WCSprites[i] = 0;
	}

	FILE * fp = fopen(path, "rb");
	

	fseek(fp, 0x9BEC, SEEK_SET);
	fscanf(fp, "%c", &r);
	if (r != 0x4E) {
		WCSpriteOffset = 0x9BCA;
	} else {
		WCSpriteOffset = 0x1ED1B0;// relocate ***
	}

	fseek(fp, WCSpriteOffset, SEEK_SET);

	fscanf(fp, "%c", &r);

	for (i = 0; i<NUM_WC; i++) {
		fscanf(fp, "%c", &r);
		WCSprites[i] = r;
	}
	

	fseek(fp, 0x12C494, SEEK_SET);
	fscanf(fp, "%c", &r);
	if (r != 0x4E) {
		WCHeaderOffset = 0x12C49E;
	} else {
		WCHeaderOffset = 0x1ED100;// relocate ***
	}

	fseek(fp, WCHeaderOffset, SEEK_SET);

	if (WCHeaderOffset == 0x1ED100) {
		fscanf(fp, "%c", &r);
		fscanf(fp, "%c", &r);
	}

	for (i = 0; i<NUM_WC; i++) {
		fscanf(fp, "%c", &r);
		fscanf(fp, "%c", &c);
		if (single&&i != subselect[mode][0])continue;
		WCHeader[i] = 256 * r;
		WCHeader[i] += c;
	}

	o = ftell(fp);

	for (i = 0; i<NUM_WC; i++) {
		if (single&&i != subselect[mode][0])continue;
		o = WCHeaderOffset + WCHeader[i] - 2 * (WCHeaderOffset == 0x12C49E);

		int p = 0;
		int c = 0;
		int k;

		for (k = 0; k<128; k++) {
			WCBranches[k] = 0;
		}

		WCBranches[0] = o;
		NumBranches = 1;

		while (NumBranches) {
			p = 0;
			o = 0;
			for (k = 0; k<128; k++) {
				if (WCBranches[k] && (WCBranches[k]<o || !o))o = WCBranches[k];
			}

			fseek(fp, o, SEEK_SET);

			while (!checkWCEnd(p)) {

				o = ftell(fp);
				if (o>mo)mo = o;

				for (k = 0; k<128; k++) {
					if (WCBranches[k] == o) {
						WCScript[i][c] = -2;
						c++;
						WCScript[i][c] = o;
						c++;

						if (c == 0x56 || c == 0x55)
							o = o;

						WCBranches[k] = 0;

						for (int k2 = k; k2 < 127; k2++) {
							WCBranches[k2] = WCBranches[k2 + 1];
						}
						WCBranches[127] = 0;

						NumBranches--;
						for (; k<128; k++) {
							if (WCBranches[k] == o) {
								WCBranches[k] = 0;

								for (int k2 = k; k2 < 127; k2++) {
									WCBranches[k2] = WCBranches[k2 + 1];
								}
								WCBranches[127] = 0;

								NumBranches--;
							}
						}
					}
				}

				if (o == 0x12C4E8) {
					o = o;
				}

				bool f = false;
				for (k = 0; k < c; k++) {
					if (WCScriptO[i][k] == o) {
						f = true;
						WCScript[i][c] = -3;
						WCScriptO[i][c] = 0;
						c++;
						WCScript[i][c] = o;
						WCScriptO[i][c] = 0;
						c++;

						WCScript[i][c] = -4;
						WCScriptO[i][c] = 0;
						c++;
						break;
					}
				}
				if (f)break;

				



				p = checkAllWCPatterns(fp);

				if (c == 0x56 || c== 0x55)
					o = o;

				if (p == -1) {
					fseek(fp, o, SEEK_SET);
					char out[512];
					unsigned char r;
					sprintf(out, "Error parsing World Cutscene scripts.\n\nPlease submit a screenshot of this message to the forums.\n\nOffset: 0x%X Data:\n\n", o);
					for (i = 0; i<32; i++) {
						fscanf(fp, "%c", &r);
						sprintf(out, "%s%.2hX", out, r);
					}
					MessageBox(NULL, out, "Error", MB_OK);
					fclose(fp);
					return;
				}

				if (!strcmp(WCNames[p], "Branch")) {
					WCScript[i][c] = -3;
					WCScriptO[i][c] = 0;
					c++;
					WCScript[i][c] = WCArgs[1];
					WCScriptO[i][c] = 0;
					c++;
					continue;
				}

				WCScript[i][c] = p;
				WCScriptO[i][c] = o;

				if (!strcmp(WCNames[p], "Run Scripted Movement")) {
					WCScriptE[i][c] = new unsigned char[256];

					int ie = 0;
					unsigned long oe = ftell(fp);

					fseek(fp,o + WCArgs[0] + 2,SEEK_SET);

					do {
						fscanf(fp, "%c", &r);
						WCScriptE[i][c][ie] = r;
						ie++;
					} while (r != 0xFF);

					fseek(fp, oe, SEEK_SET);

					WCArgs[0] = 0x10;
				} else {
					WCScriptE[i][c] = 0;
				}


				c++;
				for (j = 0; j<NumArgs; j++) {
					WCScript[i][c] = WCArgs[j];

					if (c == 0x56 || c == 0x55)
						o = o;

					c++;
				}




				j = 0;
				for (k = 0; k<128; k++) {
					if (WCBranches[k])j = k + 1;
				}

				switch (WCPatterns[p][WCLength[p] - 3]) {
					case -21:
						if (WCPatterns[p][WCLength[p] - 2] == 0) {
							to = WCArgs[getWCPatternArgs(p) - 1];
							if (to > o) {
								switch (to) {
									case 0x18074:
									case 0x1808A:
									case 0x180B4:

										break;
									default:
										WCBranches[j] = to;//+ftell(fp)-2;
										NumBranches++;
										break;
								}
							} else
								to=to;

						}
						break;
				}
				switch (WCPatterns[p][WCLength[p] - 2]) {
					case -21:
						if (WCPatterns[p][WCLength[p] - 1] == -1) {
							to = WCArgs[getWCPatternArgs(p) - 1];
							if (to>o){
								switch (to) {
									case 0x18074:
									case 0x1808A:
									case 0x180B4:

										break;
									default:
										WCBranches[j] = to;//+ftell(fp)-2;
										NumBranches++;
										break;
								}
							} else
								to = to;
						}
						break;
				}

				for (int k = 0; k < WCLength[p]; k++) {
					if (WCPatterns[p][k] == -30) {

						int sarg = getWCPatternArgs(p) - 1;

						for (int iarg = sarg; iarg < NumArgs; iarg++) {
							to = WCArgs[iarg];

							for (k = 0; k < j; k++) {
								if (WCBranches[j] == WCBranches[k]) {
									to = 0;
									break;
								}
							}
							if (to>o){
								if (to) {
									WCBranches[j] = to;
									NumBranches++;
									j++;
								}
							} else
								to = to;
						}
						break;
					}
				}

				if (WCBranches[j])
					for (k = 0; k<j; k++) {
						if (WCBranches[j] == WCBranches[k]) {
							WCBranches[j] = 0;
							NumBranches--;
							k = j;
						}
					}
			}
		}
		WCScript[i][c] = -1;
		BuildWCGraph(i);
	}
	o = ftell(fp);

	mo = mo;
	fclose(fp);
}
