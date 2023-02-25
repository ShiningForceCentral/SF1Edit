int BEHeader[256];
int BEScript[64][768];
long BEScriptO[64][768];

long BEHeaderOffset;

int BEPatterns[512][512];
int NumBEPatterns = 0;
int BELength[512];
char BENames[512][32];
int BEPatternNodes[512];

int BEArgs[16];
//int NumArgs = 0;
int BEBranches[32];
//int NumBranches = 0;

BEGraph * BEGraphs[64];

void addBEPattern(int len, int node, char * name, ... ){
	va_list vl;
	va_start(vl, name);
	int c=0;
	for(int i=0;i<len;i++){
		BEPatterns[NumBEPatterns][c] = va_arg(vl,int);
		c++;
	}
	sprintf(BENames[NumBEPatterns],name);
	BELength[NumBEPatterns]=len;
	BEPatternNodes[NumBEPatterns]=node;
	NumBEPatterns++;
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
//		29-32 = 1-4 bytes, jump table offsets (not implemented in battle ends)
bool checkBEEnd(FILE * fp);

bool checkBEPattern(FILE * fp, int pat){
	int r=0;
	int r2=0;
	int t,k;
	int v;
	long o,o2;
	NumArgs=0;
	int lastarg=0;
	for(int i=0;i<BELength[pat];i++){
		fscanf(fp,"%c",&r);
		t = BEPatterns[pat][i];
		if(t>=0){
			if(r!=t)return false;
		} else {
			t*=-1;
			k=t%4;
			if(!k)k=4;
			k--;
			v=r;
			o = ftell(fp);
			for(int j=0;j<k;j++){
				fscanf(fp,"%c",&r);
				v*=256;
				v+=r;
			}

			if(k==0)
				if(v&0x80)
					v=v|(-1-0xFF);

			if(k==1)
				if(v&0x8000)v=v|(-1-0xFFFF);

			if(NumArgs&&lastarg>20&&lastarg<25)
			switch(BEArgs[NumArgs-1]){
					case 0x60://always
					case 0x64://carry clear
					case 0x65://carry set
					case 0x66://not equal
					case 0x67://equal
					case 0x6D://less than
						v += o;
						if(t%2==0)v-=1;
						break;
			}

			BEArgs[NumArgs]=v;
			NumArgs++;

			if(t<5){

			} else if(t<9){
				i++;
				if(NumArgs&&lastarg>20&&lastarg<25){
					if(v!=BEPatterns[pat][i])return false;
				} else {
					if(o-1+v!=BEPatterns[pat][i])return false;
					BEArgs[NumArgs-1]=o-1+v;
				}
			} else if(t<13){
				i++;
				if(v!=BEPatterns[pat][i])return false;
			} else if(t<17){
				o2 = ftell(fp);
				fseek(fp,v,SEEK_SET);
				fscanf(fp,"%c",&r);
				fscanf(fp,"%c",&r2);

				if(r==0x60){
					fseek(fp,o+v,SEEK_SET);
					if(!checkBEEnd(fp))return false;
				} else {
					if(r!=0x4E||r2!=0x75)return false;
				}
				fseek(fp,o2,SEEK_SET);
			} else if(t<21){
				if(v<0)return false;
				fseek(fp,o+v-k,SEEK_SET);//**** break here and make sure not missing.. something
			} else if(t<25){
				switch(r){
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
			} else if(t<29){
				if(v>=0)return false;
				BEArgs[NumArgs]=o+v-k;
				//negative branch
				if (!strcmp(BENames[pat], "Branch"))
					fseek(fp, o + v - k, SEEK_SET);
			}
			lastarg=t;
		}
	}
	return true;
}

bool checkBEEnd(FILE * fp){
	unsigned long o = ftell(fp);
	for(int i=0;i<NumBEPatterns;i++){
		if(!strcmp("End",BENames[i])){
			fseek(fp,o,SEEK_SET);
			if(checkBEPattern(fp,i))return true;
		}
	}
	return false;
}

bool checkBEEnd(int p){
	if(p==NumBEPatterns-2||p==NumBEPatterns-3)
		return false;
	if(!strcmp("End",BENames[p]))return true;
	//if(BEPatterns[p][0]==0x60)return true;
	//if(BEPatterns[p][0]==-21&&BEArgs[0]==0x60)return true;
	if(BEPatterns[p][BELength[p]-2]==0x4E&&BEPatterns[p][BELength[p]-1]==0xD5)
		return true;
	return false;
}

int checkAllBEPatterns(FILE * fp){
	unsigned long o = ftell(fp);
	for(int i=0;i<NumBEPatterns;i++){
		//if(!strcmp(BENames[i],"Clear Message Box?"))
		//	i=i;
		fseek(fp,o,SEEK_SET);
		if(checkBEPattern(fp,i))
			return i;
	}
	return -1;
}

int getBEPatternBytes(int pat){
	int c=0;
	int t;
	for(int i=0;i<BELength[pat];i++){
		if(BEPatterns[pat][i]>=0){
			c++;
		} else {
			t = (-1*BEPatterns[pat][i]) % 4;
			if(!t)t=4;
			c+=t;
		}
	}
	return c;
}

int getBEPatternArgs(int pat){
	int c=0;
	for(int i=0;i<BELength[pat];i++){
		if(BEPatterns[pat][i]<0){
			c++;
		}
	}
	return c;
}

void addBENodeType(char * n, int s, char * l="", char * l2="", char * l3="", char * l4="",int al=-1, int an=0){
	nodeTypesBE[NumBENodeTypes].set(n,s,l,l2,l3,l4,al,an);
	NumBENodeTypes++;
}

void setBENodeOuts(int n, char * l="", char * l2="", char * l3="", char * l4=""){
	nodeTypesBE[NumBENodeTypes-1].setout(n,l,l2,l3,l4);
}

void setBENodeArgs(int n, int t=-1, char * l="", int t2=-1, char * l2="", int t3=-1, char * l3="", int t4=-1, char * l4=""){
	nodeTypesBE[NumBENodeTypes-1].setargs(n,t,l,t2,l2,t3,l3,t4,l4);
}

void setBENodeHelp(char * h){
	nodeTypesBE[NumBENodeTypes-1].setHelpText(h);
}


void initBE(){
	int i;
	for(i=0;i<NUM_BE;i++){
		BEGraphs[i] = new BEGraph(240,50,640,480);
	}

	addBENodeType("Start",2,"Start");
	addBENodeType("End",3, "End");

	addBENodeType("Check Character Dying",1,"Check","Dying","","",2,0);
		setBENodeOuts(2,"Dying","Alive");
		setBENodeArgs(4,ARG_WORD,"Character",ARG_IGNORE,"", ARG_IGNBRA,"", ARG_IGNORE,"");
		setBENodeHelp("Branches the script depending on whether a specified character was just killed.\n\nCharacter: Character to check, enemies start at 128 with 128 being the first enemy.");

	addBENodeType("Check Character Dead",1,"Check","Dead","","",2,0);
		setBENodeOuts(2,"Dead","Alive");
		setBENodeArgs(4,ARG_BYTE,"",ARG_IGNORE,"", ARG_IGNBRA,"", ARG_IGNORE,"");
		setBENodeHelp("Branches the script depending on whether a specified character is dead.\n\nCharacter: Character to check, enemies start at 128 with 128 being the first enemy.");

	addBENodeType("Check First Three Dead",1,"Check","Dead","(First 3)","");
		setBENodeOuts(2, "Dead", "Alive");
		setBENodeArgs(2, ARG_IGNBRA,"",ARG_IGNORE,"");
		setBENodeHelp("Branches the script depending on whether the first three enemies are dead. Used in the Dark Dragon battle.");

	addBENodeType("Set Active Character",0,"Set","Active","Character","",3,0);
		setBENodeArgs(2,ARG_BYTE,"Character",ARG_IGNORE,"");
		setBENodeHelp("Sets the currect character to use for actions that effect a character.\n\nCharacter: Character to use, enemies start at 128 with 128 being the first enemy.");

	addBENodeType("Check Character Exists",1,"Check","Character","Exists","");
		setBENodeOuts(2,"Missing","Found");
		setBENodeArgs(2, ARG_IGNBRA,"",ARG_IGNORE,"");
		setBENodeHelp("Branches the script depending on whether the active character is present in the battle or not.");

	addBENodeType("Set Sprite Direction",0,"Set Sprite","Direction","","",3,0);
		setBENodeArgs(2,ARG_DIR,"Direction",ARG_IGNORE,"");
		setBENodeHelp("Changes the direction of the active character.");

	addBENodeType("Fade Character In",0,"Fade","Character","In","");
		setBENodeArgs(2,ARG_IGNORE,"",ARG_IGNORE,"");
		setBENodeHelp("Fades the active character in with a flickering animation.");

	addBENodeType("Fade Character Out",0,"Fade","Character","Out","");
		setBENodeArgs(2,ARG_IGNORE,"",ARG_IGNORE,"");
		setBENodeHelp("Fades the active character out with a flickering animation.");

	addBENodeType("Remove Character",0,"Remove","Character","","");
		setBENodeArgs(1,ARG_IGNORE,"");
		setBENodeHelp("Removes the active character from the battle.");

	addBENodeType("Move Character",0,"Move","Character","","",3,-1);
		setBENodeArgs(2,ARG_BYTE,"X",ARG_BYTE,"Y");
		setBENodeHelp("Repositions the active character and screen.");

	addBENodeType("Set Character Y",0,"Set","Character","Y","",3,0);
		setBENodeArgs(1,ARG_BYTE,"Y");
		setBENodeHelp("Repositions the active character and screen, vertical only.");

	addBENodeType("Open Message Window",0,"Open","Message","Window","");
		setBENodeHelp("Prepares the window for displaying messages.");
	addBENodeType("Close Message Window",0,"Close","Message","Window","");
		setBENodeHelp("Closes the message window when finished.");

	addBENodeType("Display Message",0,"Display","Message","","",3,0);
		setBENodeArgs(1,ARG_MESSAGE,"Message");
		setBENodeHelp("Displays a message to the screen.");

	addBENodeType("More Text Prompt",0,"More","Text","Prompt","");
		setBENodeHelp("Pauses the message and displays the flashing arrow indicating more text to follow.");

	addBENodeType("Get Speaking Sound",0,"Get","Speaking","Sound","");
		setBENodeArgs(1,ARG_IGNORE,"");
		setBENodeHelp("Loads the speaking sound of the active character.");

	addBENodeType("Set Speaking Sound",0,"Set","Speaking","Sound","",3,0);
		setBENodeArgs(2,ARG_BYTE,"Battle Member",ARG_IGNORE,"");
		setBENodeHelp("Sets the sound type to use when displaying a messages. Different characters and enemies use slightly different sounds when speaking.\n\nBattle Member: The member number to pull the text sound from.");


	addBENodeType("Set Text Sound", 0, "Set", "Text", "Sound", "", 3, 0);
		setBENodeArgs(2, ARG_VOICE, "Map Sprite", ARG_IGNORE, "");
		setBENodeHelp("Sets the sound type to use when displaying a messages. Different characters and enemies use slightly different sounds when speaking.\n\nMap Sprite: The map sprite number to pull the text sound from.");


	addBENodeType("Display Portrait",0,"Display","Portrait","","",3,0);
		setBENodeArgs(1,ARG_BYTE,"Portrait");
		setBENodeHelp("Displays a character portrait given the portrait gfx number.");

	addBENodeType("Set Portrait Version", 0, "Set", "Portrait", "Version", "", 3, 0);
		setBENodeArgs(1, ARG_BYTE, "Version");
		setBENodeHelp("Changes the displayed portrait.\n\nVersion: 0 = normal, 1 = eyes closed, 2 = mouth open");

	addBENodeType("Clear Portrait",0,"Clear","Portrait","","");
		setBENodeHelp("Clears the displayed portrait.");

	addBENodeType("Yes/No Choice",1,"Yes","No","Choice","");
		setBENodeOuts(2,"Yes","No");
		setBENodeArgs(3,ARG_IGNORE,"",ARG_IGNORE,"",ARG_IGNORE,"");
		setBENodeHelp("Branches the script depending on the response to a yes/no choice.");

	addBENodeType("Kill Enemy",0,"Kill","Enemy","","",3,0);
		setBENodeArgs(2,ARG_BYTE,"Enemy",ARG_IGNORE,"");
		setBENodeHelp("Kills the specified enemy. Use with 255 to kill all enemies, which is often used to end the battle, such as when the boss dies.");

	addBENodeType("Set Event Flag",0,"Set","Event","Flag","",3,0);
		setBENodeArgs(2,ARG_BYTE,"Event",ARG_IGNORE,"");
		setBENodeHelp("Sets an event number as completed.\n\nEvent Number: Event to set");

	addBENodeType("Clear Event Flag",0,"Clear","Event","Flag","",3,0);
		setBENodeArgs(2,ARG_BYTE,"Event",ARG_IGNORE,"");
		setBENodeHelp("Clears the completed state of an event number.\n\nEvent Number: Event to clear");

	addBENodeType("Pause",0,"Pause","","","",3,0);
		setBENodeArgs(2,ARG_BYTE,"Frames",ARG_IGNORE,"");
		setBENodeHelp("Waits for a specified number of frames, only updating the graphics / animations.");

	addBENodeType("Screen Effect",0,"Screen","Effect","","",3,0);
		setBENodeArgs(1,ARG_WORD,"Effect");
		setBENodeHelp("Performs a screen transition effect.");

	addBENodeType("Flash Screen",0,"Flash","Screen","","");
		setBENodeArgs(2,ARG_IGNORE,"",ARG_IGNORE,"");
		setBENodeHelp("Does a bright screen flash effect.");

	addBENodeType("Move Screen to Character",0,"Move","Screen","to","Character");
		setBENodeHelp("Moves the screen to the active character.");

	addBENodeType("Move Cursor",0,"Move","Cursor","","",3,-1);
		setBENodeArgs(2,ARG_BYTE,"X",ARG_BYTE,"Y");
		setBENodeHelp("Moves the screen to the given location.");

	addBENodeType("Clear GFX RAM?",0,"Clear","GFX","RAM","");

	addBENodeType("Play Sound Effect",0,"Play","Sound","Effect","",3,0);
		setBENodeArgs(1,ARG_WORD,"Sound");
		setBENodeHelp("Plays the given sound effect.");

	addBENodeType("Set Copy Location", 0, "Set", "Copy", "Location", "");
		setBENodeArgs(4, ARG_BYTE, "X Source", ARG_BYTE, "Y Source", ARG_BYTE, "X Target", ARG_BYTE, "Y Target");
		setBENodeHelp("Sets up the location to copy tiles from and to on the map.");

	addBENodeType("Copy Tiles", 0, "Copy", "Tiles", "", "");
		setBENodeArgs(2, ARG_BYTE, "Width", ARG_BYTE, "Height");
		setBENodeHelp("Copies a rectangle of tiles from one part of the map to another.");

	for(i=0;i<NUM_BE;i++){
		BEGraphs[i]->addNode(16,16);

		BEGraphs[i]->buildList();
	}

	addBEPattern(10, 2,  "Check Character Dying", 0x34, 0x3C, -2, 0x4E, 0xB9, -12, 0x12BFD0, -21, 0, -2);
	addBEPattern(9, 2,  "Check Character Dying", 0x34, 0x3C, -2, 0x4E, 0xB9, -12, 0x12BFD0, -21, -1);
	addBEPattern(10, 2,  "Check Character Dying", 0x34, 0x3C, -2, 0x61, 0, -6, 0x12BFD0, -21, 0, -2);
	addBEPattern(9, 2,  "Check Character Dying", 0x34, 0x3C, -2, 0x61, 0, -6, 0x12BFD0, -21, -1);

	addBEPattern(11, 3,  "Check Character Dead", 0x70, -1, 0x4E, 0xB9, -12, 0x2009C, 0x4A, 0x41, -21, 0, -2);
	addBEPattern(35, 4,  "Check Characters Dead", 0x42, 0x42, 0x70, 0x80, 0x4E, 0xB9, 0, 2, 0, 0x9C, 0xD4, 0x41, 0x70, 0x81, 0x4E, 0xB9, 0, 2, 0, 0x9C, 0xD4, 0x41, 0x70, 0x82, 0x4E, 0xB9, 0, 2, 0, 0x9C, 0xD4, 0x41, -21, 0, -2);

	addBEPattern(6, 5,  "Set Active Character", 0x74, -1, 0x4E, 0xB9, -12, 0x12BFB6);
	addBEPattern(7, 5,  "Set Active Character", 0x34, 0x3C, -2, 0x4E, 0xB9, -12, 0x12BFB6);
	addBEPattern(6, 5,  "Set Active Character", 0x74, -1, 0x61, 0, -6, 0x12BFB6);
	addBEPattern(7, 5,  "Set Active Character", 0x34, 0x3C, -2, 0x61, 0, -6, 0x12BFB6);

	addBEPattern(5, 6,  "Check Character Exists", 0x4A, 0x40, -21, 0, -2);
	addBEPattern(4, 6,  "Check Character Exists", 0x4A, 0x40, -21, -1);

	addBEPattern(7, 7,  "Set Character Direction", 0x34, 0x3C, -2, 0x4E, 0xB9, -12, 0x12C2DC);
	addBEPattern(7, 7,  "Set Character Direction", 0x34, 0x3C, -2, 0x61, 0, -6, 0x12C2DC);

	addBEPattern(4, 8,  "Fade Character In", 0x4E, 0xB9, -12, 0x12BFF0);
	addBEPattern(4, 8,  "Fade Character In", 0x61, 0, -6, 0x12BFF0);

	addBEPattern(4, 9,  "Fade Character Out", 0x4E, 0xB9, -12, 0x12C036);
	addBEPattern(4, 9,  "Fade Character Out", 0x61, 0, -6, 0x12C036);

	addBEPattern(6, 10,  "Remove Character", 0x72, 0xFF, 0x4E, 0xB9, -12, 0x20104);

	addBEPattern(22, 11,  "Move Character", 0x72, -1, 0x4E, 0xB9, 0, 2, 1, 8, 0x72, -1, 0x4E, 0xB9, 0, 2, 1, 0x0C, 0x4E, 0xB9, 0, 0, 0x80, 0x94);

	addBEPattern(12, 12,  "Set Character Y", 0x72, -1, 0x4E, 0xB9, 0, 2, 1, 0x0C, 0x4E, 0xB9, -12, 0x8028);

	addBEPattern(2, 13,  "Open Message Window", 0x4E, 0x45);
	addBEPattern(2, 14,  "Close Message Window", 0x4E, 0x46);

	addBEPattern(5, 15,  "Display Message", 0x30, 0x3C, -2, 0x4e, 0x48);

	addBEPattern(2, 16,  "More Text Prompt", 0x4E, 0x47);

	addBEPattern(4, 17,  "Get Speaking Sound", 0x4E, 0xB9, -12, 0x12C342);
	addBEPattern(4, 17,  "Get Speaking Sound", 0x61, 0, -6, 0x12C342);

	addBEPattern(6, 18,  "Set Speaking Sound", 0x72, -1, 0x4E, 0xB9, -12, 0x12C34E);
	addBEPattern(6, 18,  "Set Speaking Sound", 0x72, -1, 0x61, 0, -6, 0x12C34E);

	addBEPattern(11, 19, "Set Text Sound Pitch", 0x2F, 0, 0x10, 0x3C, -2, 0x4E, 0xB9, -12, 0x17F64, 0x20, 0x1F);
	addBEPattern(11, 19, "Set Text Sound Pitch", 0x2F, 0, 0x10, 0x3C, -2, 0x61, 0, -6, 0x17F64, 0x20, 0x1F);


	addBEPattern(6, 20,  "Display Portrait", 0x70, -1, 0x4E, 0xB9, -12, 0x802C);

	addBEPattern(16, 21, "Set portrait version", 0x70, -1, 0x48, 0xE7, 0x02, 0xFE, 0x4E, 0xB9, 0, 0, 0x80, 0xD8, 0x4C, 0xDF, 0x7F, 0x40);

	addBEPattern(4, 22,  "Clear Portrait", 0x4E, 0xB9, -12, 0x8030);

	addBEPattern(13, 23,  "Yes/No Choice", 0x4E, 0xB9, -12, 0x334, 0x4E, 0x47, 0x4A, 0x38, 0xB5, 0x28, -21, 0, -2);
	addBEPattern(12, 23,  "Yes/No Choice", 0x4E, 0xB9, -12, 0x334, 0x4E, 0x47, 0x4A, 0x38, 0xB5, 0x28, -21, -1);

	addBEPattern(6, 24,  "Kill Enemy", 0x74, -1, 0x4E, 0xB9, -12, 0x12C1BA);
	addBEPattern(6, 24,  "Kill Enemy", 0x74, -1, 0x61, 0, -6, 0x12C1BA);

	addBEPattern(6, 25,  "Set Event Flag", 0x70, -1,  0x4E, 0xB9, -12, 0x38C);
	addBEPattern(6, 26,  "Clear Event Flag", 0x70, -1,  0x4E, 0xB9, -12, 0x390);

	addBEPattern(6, 27,  "Pause", 0x70, -1,  0x4E, 0xB9, -12, 0x244);

	addBEPattern(31, 28,  "Screen Effect", 0x13, 0xFC,  -2, 0, 0xFF, 0x0E, 0xB7, 0x42, 0x39, 0, 0xFF, 0x0E, 0xBA, 0x13, 0xF9, 0, 0xFF, 0x0E, 0xB9, 0, 0xFF, 0x0E, 0xBB, 0x13, 0xFC, 0, 0x0D, 0, 0xFF, 0x0E, 0xBC);

	addBEPattern(4, 29,  "Flash Screen", 0x4E, 0xB9, -12, 0x128F98);
	addBEPattern(4, 29,  "Flash Screen", 0x61, 0x00, -6, 0x128F98);

	addBEPattern(44, 30,  "Move Screen to Character", 0x4E, 0xB9, 0, 2, 0, 0x58, 0xE1, 0x49, 0x3C, 1, 0x4E, 0xB9, 0, 2, 0, 0x5C, 0x8C, 0x41, 0x30, 6 , 0x4E, 0xB9, 0, 0, 0x80, 0x98, 0x33, 0xFC, 0, 1, 0, 0xFF, 0x0C, 0x98, 0x23, 0xFC, 0, 1, 0x0F, 0x3F, 0, 0xFF, 0x0E, 0x30);

	addBEPattern(34, 31,  "Move Cursor", 0x32, 0x3C, -2, 0x30, 0x3C, -2, 0xE1, 0x49, 0x80, 0x41, 0x4E, 0xB9, 0, 0, 0x80, 0x98, 0x33, 0xFC, 0, 1, 0, 0xFF, 0x0C, 0x98, 0x23, 0xFC, 0, 1, 0x0F, 0x3F, 0, 0xFF, 0x0E, 0x30);

	addBEPattern(4, 32,  "Clear GFX RAM?", 0x4E, 0xB9, -12, 0x8094);

	addBEPattern(3, 33,  "Play Sound Effect", 0x4E, 0x40,  -2);

	addBEPattern(8, 34, "Set Copy Location", 0x72, -1, 0x74, -1, 0x76, -1, 0x78, -1);

	addBEPattern(8, 35, "Copy Tiles", 0x7A, -1, 0x7C, -1, 0x4E, 0xB9, -12, 0x80AC);

	AdvancedNodes(BE,36)



	addBEPattern(2,  1, "End", 0x60, -13);
	addBEPattern(3,  1, "End", 0x60, 0, -14);

	addBEPattern(3,  1, "Branch", 0x60, 0, -26);//just follow, shouldn't create a node
	addBEPattern(2,  1, "Branch", 0x60, -25);

	addBEPattern(3,  1, "Branch", 0x60, 0, -18);//just follow, shouldn't create a node
	addBEPattern(2,  1, "Branch", 0x60, -17);
	
	addBEPattern(2,  1, "End",0x4E,0x75);
}

int findBELabel(int script, int label){
	int i=0;
	int p;
	while(BEScript[script][i]!=-1){
		p = BEScript[script][i];
		switch(p){
		case -2:
			i++;
			if(BEScript[script][i]==label)return i+1;
			break;
		case -3:
			i++;
			break;
		case -4:
			break;
		default:
			i+=getBEPatternArgs(p);
			break;
		}
		i++;
	}
	return -1;
}

void labelBEBranches(BEGraphNode * node, int arg, bool set=false, bool yn=false){

	if (!strcmp(node->type->name, "Check Character Dying")) {
		switch (node->args[arg]) {
		case 0x66://carry clear
			sprintf(node->outlabel[0], "Alive");
			sprintf(node->outlabel[1], "Dying");
			break;
		case 0x67://carry set
			sprintf(node->outlabel[0], "Dying");
			sprintf(node->outlabel[1], "Alive");
			break;
		}
		return;
	}

	if (!strcmp(node->type->name, "Check Character Dead")) {
		switch (node->args[arg]) {
		case 0x66://carry clear
			sprintf(node->outlabel[0], "Alive");
			sprintf(node->outlabel[1], "Dead");
			break;
		case 0x67://carry set
			sprintf(node->outlabel[0], "Dead");
			sprintf(node->outlabel[1], "Alive");
			break;
		}
		return;
	}

	if (!strcmp(node->type->name, "Check First Three Dead")) {
		switch (node->args[arg]) {
		case 0x66://carry clear
			sprintf(node->outlabel[0], "Alive");
			sprintf(node->outlabel[1], "Dead");
			break;
		case 0x67://carry set
			sprintf(node->outlabel[0], "Dead");
			sprintf(node->outlabel[1], "Alive");
			break;
		}
		return;
	}
	return;//
	switch(node->args[arg]){
		case 0x64://carry clear
			sprintf(node->outlabel[1],"Less");
			sprintf(node->outlabel[0],"Not Less");
			break;
		case 0x65://carry set
			sprintf(node->outlabel[1],"Not Less");
			sprintf(node->outlabel[0],"Less");
			break;
		case 0x66://not equal
			if(!set){
				if(!yn){
					sprintf(node->outlabel[1],"Equal");
					sprintf(node->outlabel[0],"Not Equal");
				} else {
					sprintf(node->outlabel[1],"No");
					sprintf(node->outlabel[0],"Yes");
				}
			} else {
				sprintf(node->outlabel[1],"Clear");
				sprintf(node->outlabel[0],"Set");
			}
			break;
		case 0x67://equal
			if(!set){
				if(!yn){
					sprintf(node->outlabel[1],"Not Equal");
					sprintf(node->outlabel[0],"Equal");
				} else {
					sprintf(node->outlabel[1],"Yes");
					sprintf(node->outlabel[0],"No");
				}
			} else {
				sprintf(node->outlabel[1],"Set");
				sprintf(node->outlabel[0],"Clear");
			}
			break;
	}
}


void BuildBEGraphLine(int script, int start, int sx, int sy, BEGraphNode * prev=0, int b=0, int bb=0){

	BEGraphNode * last = prev;

	int i=start;

	int x=sx;
	int y=sy;

	int p,a;

	int bank=b;
	int bbank=bb;

	int oldline = maxline;

	while(BEScript[script][i]!=-1){
		p = BEScript[script][i];
		/*if(p==NumBEPatterns-2||p==NumBEPatterns-3){
			i+=2;
			continue;
		}*/
		switch(p){
		case -2:
			i++;
			break;
		case -3:
			i++;
			if (last && last != BEGraphs[script]->nodes.head->data) {
				if (last->branch && last->branch != BEScript[script][i]) {
					last->branch2 = BEScript[script][i];
					last->brasec2 = false;
				} else {
					last->branch = BEScript[script][i];
					last->brasec = false;
				}
			} else {
				if (BEGraphs[script]->nodes.head->data->branch && BEGraphs[script]->nodes.head->data->branch != BEScript[script][i]) {
					BEGraphs[script]->nodes.head->data->branch2 = BEScript[script][i];
					BEGraphs[script]->nodes.head->data->brasec2 = true;
				} else {
					BEGraphs[script]->nodes.head->data->branch = BEScript[script][i];
					BEGraphs[script]->nodes.head->data->brasec = true;
				}
			}
			break;
		case -4:
			return;
		default:
			LLNode<BEGraphNode*>* cur = BEGraphs[script]->nodes.head;

			BEGraphNode * temp;
			if (last && last != BEGraphs[script]->nodes.head->data) {
				temp = last;
			} else {
				temp = BEGraphs[script]->nodes.head->data;
			}

			if (BEGraphs[script]->nodes.head->data->type->numout<3 && nodeTypesBE[BEPatternNodes[p]].numout<3)
			while (cur) {
				if (cur->data->offset == BEScriptO[script][i] && strcmp(cur->data->type->name, "End")) {
					BEGraphs[script]->connect(temp, cur->data);
					return;
				}
				cur = cur->next;
			}


			BEGraphs[script]->addNode(x,y,BEPatternNodes[p],BEScriptO[script][i]);
			a = getBEPatternArgs(p);
			for(int j=0;j<a;j++){
				BEGraphs[script]->nodes.head->data->args[j]=BEScript[script][i+j+1];
			}
			if(a&&BEPatternNodes[p]==17&&BEGraphs[script]->nodes.head->data->args[0]==0x180A6)
				BEGraphs[script]->nodes.head->data->args[0]=0x53;
			i+=a;

			if(!strcmp(BENames[p],"Set Message Bank")){
				bank=BEGraphs[script]->nodes.head->data->args[0];
			}
			if(!strcmp(BENames[p],"Clear Message Bank")){
				bank=0;
			}

			if(!strcmp(BENames[p],"Backup Message Bank")){
				bbank = bank;
			}
			if(!strcmp(BENames[p],"Restore Message Bank")){
				bank = BEGraphs[script]->nodes.head->data->bbank;
				BEGraphs[script]->nodes.head->data->bbank = 0;
			}

			BEGraphs[script]->nodes.head->data->bank = bank;
			BEGraphs[script]->nodes.head->data->bbank = bbank;

			if(last){
				BEGraphs[script]->connect(last, BEGraphs[script]->nodes.head->data);
				last=0;
			} else {
				BEGraphs[script]->connect(BEGraphs[script]->nodes.head->next->data, BEGraphs[script]->nodes.head->data);
			}

			if(BEGraphs[script]->nodes.head->data->type->numout>1){
				
				last = BEGraphs[script]->nodes.head->data;

				labelBEBranches(last,a-2,strcmp(BENames[p],"Check Event")==0,strcmp(BENames[p],"Branch on Yes/No")==0);
			
				int lb = findBELabel(script, BEScript[script][i]);

				LLNode<BEGraphNode*>* cur = BEGraphs[script]->nodes.head;
				if (BEGraphs[script]->nodes.head->data->type->numout<3)
				while (cur) {
					if (cur->data->offset == BEScript[script][i] && strcmp(cur->data->type->name, "End")) {
						BEGraphs[script]->connect(BEGraphs[script]->nodes.head->data, cur->data);
						lb = -1;
						break;
					}
					cur = cur->next;
				}

				if (lb != -1) {
					int topline = maxline;

					maxline++;
					switch (BEScript[script][i]) {
						case 0x18074:
						case 0x1808A:
						case 0x180B4:
							BEGraphs[script]->addNode(x + 112, y + maxline * 96, 24);//***** Make sure 24 stays the special message node
							BEGraphs[script]->nodes.head->data->args[0] = BEScript[script][i];
							BEGraphs[script]->connect(BEGraphs[script]->nodes.head->next->data, BEGraphs[script]->nodes.head->data);
							BEGraphs[script]->addNode(x + 224, y + maxline * 96, 1);
							BEGraphs[script]->connect(BEGraphs[script]->nodes.head->next->data, BEGraphs[script]->nodes.head->data);
							break;
						default:
							BuildBEGraphLine(script, lb, x + 112, maxline * 96 + 16, BEGraphs[script]->nodes.head->data, bank, bbank);
							break;
					}


					LLNode<BEGraphNode*>* curs = BEGraphs[script]->nodes.head;
					while (curs) {
						if (curs->data->y > topline * 96 + 16) {
							curs->data->y -= 96 * (topline - oldline);
							curs->data->y -= 10000;
						}
						curs = curs->next;
					}
					curs = BEGraphs[script]->nodes.head;
					while (curs) {
						if (curs->data->y > oldline * 96 + 16) {
							curs->data->y += 96 * (maxline - topline);
						}
						curs = curs->next;
					}
					curs = BEGraphs[script]->nodes.head;
					while (curs) {
						if (curs->data->y < -100) {
							curs->data->y += 10000;
						}
						curs = curs->next;
					}
				}
			}

			if(checkBEEnd(p)){
				int v;
				if(last)v = last->type->shape;
				else v = BEGraphs[script]->nodes.head->data->type->shape;
				if(v!=3){
					BEGraphs[script]->addNode(x+112,y,1);
					if(last){
						BEGraphs[script]->connect(last, BEGraphs[script]->nodes.head->data);
						last=0;
					} else {
						BEGraphs[script]->connect(BEGraphs[script]->nodes.head->next->data, BEGraphs[script]->nodes.head->data);
					}
				}
				return;
			}
			x+=112;
			break;
		}
		i++;
	}
}

void BuildBEGraph(int script){
	maxline=0;

	BEGraphs[script]->clear();

	BuildBEGraphLine(script,0, 128, 16);

	LLNode<BEGraphNode*>* cur = BEGraphs[script]->nodes.head;
	while (cur) {
		if (cur->data->type->shape == 3) {
			cur = cur->next;
			continue;
		}
		if (cur->data->out.size < cur->data->type->numout && cur->data->type->numargs && cur->data->type->numout<3) {

			LLNode<BEGraphNode*>* cur2 = BEGraphs[script]->nodes.head;
			while (cur2) {
				if (cur->data->branch < 0)cur->data->branch *= -1;
				if (cur2->data->offset == cur->data->branch && cur->data->branch) {
					BEGraphs[script]->connect(cur->data, cur2->data);

					if (cur->data->brasec && cur->data->out.size > 1) {
						BEGraphNode * temp = cur->data->out.head->data;

						cur->data->out.head->data = cur->data->out.tail->data;
						cur->data->out.tail->data = temp;
					}
				}

				if (cur->data->branch2 < 0)cur->data->branch2 *= -1;
				if (cur2->data->offset == cur->data->branch2 && cur->data->branch2) {
					BEGraphs[script]->connect(cur->data, cur2->data);

					if (cur->data->brasec2 && cur->data->out.size > 1) {
						BEGraphNode * temp = cur->data->out.head->data;

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


void LoadBE(char * path, bool single=false){
	//return;
	unsigned char r,c;
	long o,mo,to;
	int i,j;

	mo=0;

	for (int i = 0; i < 64; i++) {
		for (int j = 0; j < 768; j++) {
			BEScript[i][j] = 0;
			BEScriptO[i][j] = 0;
		}
	}

	FILE * fp = fopen(path,"rb");

	
	fseek(fp,0x12A4E6,SEEK_SET);
	fscanf(fp,"%c",&r);
	if(r!=0x4E){
		BEHeaderOffset = 0x12A4EE;
	} else {
		BEHeaderOffset = 0x1D8920;
	}

	fseek(fp,BEHeaderOffset,SEEK_SET);
	for(i=0; i<NUM_BE; i++){
		fscanf(fp,"%c",&r);
		fscanf(fp,"%c",&c);
		if(single&&i!=subselect[mode][0])continue;
		BEHeader[i]=256*r;
		BEHeader[i]+=c;
	}

	o = ftell(fp);

	for(i=0; i<NUM_BE; i++){
		if(single&&i!=subselect[mode][0])continue;
		o = BEHeaderOffset+BEHeader[i];

		int p=0;
		int c=0;
		int k;

		for(k=0;k<32;k++){
			BEBranches[k]=0;
		}

		BEBranches[0]=o;
		NumBranches = 1;

		while(NumBranches){
			p = 0;
			o = 0;
			for(k=0;k<32;k++){
				if(BEBranches[k]&&(BEBranches[k]<o||!o))o = BEBranches[k];
			}

			fseek(fp,o,SEEK_SET);

			while(!checkBEEnd(p)){

				o = ftell(fp);
				if(o>mo)mo=o;

				for (k = 0; k<32; k++) {
					if (BEBranches[k] == o) {
						BEScript[i][c] = -2;
						c++;
						BEScript[i][c] = o;
						c++;
						BEBranches[k] = 0;
						NumBranches--;
						for (; k<32; k++) {
							if (BEBranches[k] == o) {
								BEBranches[k] = 0;
								NumBranches--;
							}
						}
					}
				}

				bool f = false;
				for (k = 0; k < c; k++) {
					if (BEScriptO[i][k] == o) {
						f = true;
						BEScript[i][c] = -3;
						BEScriptO[i][c] = 0;
						c++;
						BEScript[i][c] = o;
						BEScriptO[i][c] = 0;
						c++;
						BEScript[i][c] = -4;
						BEScriptO[i][c] = 0;
						c++;
						break;
					}
				}
				if (f)break;

				if(o==0x1D8B9E)
					o=o;

				

				p=checkAllBEPatterns(fp);
				if(p==-1){
					fseek(fp,o,SEEK_SET);
					char out[512];
					unsigned char r;
					sprintf(out,"Error parsing Battle End scripts.\n\nPlease submit a screenshot of this message to the forums.\n\nOffset: 0x%X Data:\n\n",o);
					for(i=0;i<32;i++){
						fscanf(fp,"%c",&r);
						sprintf(out,"%s%.2hX",out,r);
					}
					MessageBox(NULL,out,"Error",MB_OK);
					fclose(fp);
					return;
				}

				if (!strcmp(BENames[p], "Branch")) {
					BEScript[i][c] = -3;
					BEScriptO[i][c] = 0;
					c++;
					BEScript[i][c] = BEArgs[1];
					BEScriptO[i][c] = 0;
					c++;
					continue;
				}

				BEScript[i][c]=p;
				BEScriptO[i][c]=o;
				c++;
				for(j=0;j<NumArgs;j++){
					BEScript[i][c]=BEArgs[j];
					c++;
				}

				j=0;
				for(k=0;k<32;k++){
					if(BEBranches[k])j=k+1;
				}

				switch(BEPatterns[p][BELength[p]-3]){
					case -21:
						if(BEPatterns[p][BELength[p]-2]==0){
							to = BEArgs[getBEPatternArgs(p)-1];
							if (to > o) {
								switch (to) {
									case 0x18074:
									case 0x1808A:
									case 0x180B4:

										break;
									default:
										BEBranches[j] = to;//+ftell(fp)-2;
										NumBranches++;
										break;
								}
							} else
								to = to;
						}
						break;
				}
				switch(BEPatterns[p][BELength[p]-2]){
					case -21:
						if(BEPatterns[p][BELength[p]-1]==-1){
							to = BEArgs[getBEPatternArgs(p)-1];
							if (to > o) {
								switch (to) {
									case 0x18074:
									case 0x1808A:
									case 0x180B4:

										break;
									default:
										BEBranches[j] = to;//+ftell(fp)-2;
										NumBranches++;
										break;
								}
							} else
								to = to;
						}
						break;
				}
				if(BEBranches[j])
				for(k=0;k<j;k++){
					if(BEBranches[j]==BEBranches[k]){
						BEBranches[j]=0;
						NumBranches--;
						k=j;
					}
				}
			}
		}
		BEScript[i][c]=-1;
		BuildBEGraph(i);
	}
	o = ftell(fp);
	mo=mo;
	fclose(fp);
}
