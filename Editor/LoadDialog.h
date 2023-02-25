int DialogHeader[256][3];
int DialogScript[64][2000];
long DialogScriptO[64][2000];

//long DialogHeaderOffset; Moved to loadmap so it had access

int DialogPatterns[512][512];
int NumDialogPatterns = 0;
int DialogLength[512];
char DialogNames[512][32];
int DialogPatternNodes[512];

int DialogArgs[16];
int NumArgs = 0;
int DialogBranches[32];
int NumBranches = 0;

DialogGraph * DialogGraphs[64];

void addDialogPattern(int len, int node, char * name, ... ){
	va_list vl;
	va_start(vl, name);
	int c=0;
	for(int i=0;i<len;i++){
		DialogPatterns[NumDialogPatterns][c] = va_arg(vl,int);
		c++;
	}
	sprintf(DialogNames[NumDialogPatterns],name);
	DialogLength[NumDialogPatterns]=len;
	DialogPatternNodes[NumDialogPatterns]=node;
	NumDialogPatterns++;
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
//		29-32 = 1-4 bytes, jump table offsets (not implemented in dialogs)
bool checkDialogEnd(FILE * fp);

bool checkDialogPattern(FILE * fp, int pat){
	int r=0;
	int r2=0;
	int t,k;
	int v;
	long o,o2;
	NumArgs=0;
	int lastarg=0;
	for(int i=0;i<DialogLength[pat];i++){
		fscanf(fp,"%c",&r);
		t = DialogPatterns[pat][i];
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
			switch(DialogArgs[NumArgs-1]){
					case 0x60://always
					case 0x64://carry clear
					case 0x65://carry set
					case 0x66://not equal
					case 0x67://equal
						v += o;
						if(t%2==0)v-=1;
						break;
			}

			DialogArgs[NumArgs]=v;
			NumArgs++;

			if(t<5){

			} else if(t<9){
				i++;
				if(NumArgs&&lastarg>20&&lastarg<25){
					if(v!=DialogPatterns[pat][i])return false;
				} else {
					if(o-1+v!=DialogPatterns[pat][i])return false;
					DialogArgs[NumArgs-1]=o-1+v;
				}
			} else if(t<13){
				i++;
				if(v!=DialogPatterns[pat][i])return false;
			} else if(t<17){
				o2 = ftell(fp);
				fseek(fp,o+v,SEEK_SET);
				fscanf(fp,"%c",&r);
				fscanf(fp,"%c",&r2);

				if(r==0x60){
					fseek(fp,o+v,SEEK_SET);
					if(!checkDialogEnd(fp))return false;
				} else {
					if(r!=0x4E||r2!=0x75)return false;
				}
				fseek(fp,o2,SEEK_SET);
			} else if(t<21){
				if(v<0)return false;
				fseek(fp,o+v-k,SEEK_SET);//**** break here and make sure not missing.. something
				DialogArgs[NumArgs] = o + v - k;
			} else if(t<25){
				switch(r){
					case 0x60://always
					case 0x64://carry clear
					case 0x65://carry set
					case 0x66://not equal
					case 0x67://equal
						break;
					default:
						return false;
				}
			} else if(t<29){
				if(v>=0)return false;
				DialogArgs[NumArgs]=o+v-k;
				if (!strcmp(DialogNames[pat], "Branch"))
					fseek(fp, o + v - k, SEEK_SET);
				//negative branch
			}
			lastarg=t;
		}
	}
	return true;
}

bool checkDialogEnd(FILE * fp){
	unsigned long o = ftell(fp);
	for(int i=0;i<NumDialogPatterns;i++){
		if(!strcmp("End",DialogNames[i])){
			fseek(fp,o,SEEK_SET);
			if(checkDialogPattern(fp,i))return true;
		}
	}
	return false;
}

bool checkDialogEnd(int p){
	if(p==NumDialogPatterns-2||p==NumDialogPatterns-3)
		return false;
	if(!strcmp("End",DialogNames[p]))return true;
	if (!strcmp("Special Message", DialogNames[p]))return true;
	//return true;
	//if(DialogPatterns[p][0]==-21&&DialogArgs[0]==0x60)return true;
	
	
	if (!strcmp("Display Message (ID-1)", DialogNames[p])) {
		if (DialogPatterns[p][0] == 0x60)return true;
	}
	if (DialogPatterns[p][0] == 0x60) {
		p = p;
	}

	if(DialogPatterns[p][DialogLength[p]-2]==0x4E&&DialogPatterns[p][DialogLength[p]-1]==0xD5)
		return true;
	return false;
}

int checkAllDialogPatterns(FILE * fp){
	unsigned long o = ftell(fp);
	for(int i=0;i<NumDialogPatterns;i++){
		//if(!strcmp(DialogNames[i],"Clear Message Box?"))
		//	i=i;
		fseek(fp,o,SEEK_SET);
		if(checkDialogPattern(fp,i))
			return i;
	}
	return -1;
}

int getDialogPatternBytes(int pat){
	int c=0;
	int t;
	for(int i=0;i<DialogLength[pat];i++){
		if(DialogPatterns[pat][i]>=0){
			c++;
		} else {
			t = (-1*DialogPatterns[pat][i]) % 4;
			if(!t)t=4;
			c+=t;
		}
	}
	return c;
}

int getDialogPatternArgs(int pat){
	int c=0;
	for(int i=0;i<DialogLength[pat];i++){
		if(DialogPatterns[pat][i]<0){
			c++;
		}
	}
	return c;
}

void addDialogNodeType(char * n, int s, char * l="", char * l2="", char * l3="", char * l4="",int al=-1, int an=0){
	nodeTypesDialog[NumDialogNodeTypes].set(n,s,l,l2,l3,l4,al,an);
	NumDialogNodeTypes++;
}

void setDialogNodeOuts(int n, char * l="", char * l2="", char * l3="", char * l4=""){
	nodeTypesDialog[NumDialogNodeTypes-1].setout(n,l,l2,l3,l4);
}

void setDialogNodeArgs(int n, int t=-1, char * l="", int t2=-1, char * l2="", int t3=-1, char * l3="", int t4=-1, char * l4=""){
	nodeTypesDialog[NumDialogNodeTypes-1].setargs(n,t,l,t2,l2,t3,l3,t4,l4);
}

void setDialogNodeHelp(char * h){
	nodeTypesDialog[NumDialogNodeTypes-1].setHelpText(h);
}

void initDialog(){
	int i;
	for(i=0;i<NUM_DIALOG;i++){
		DialogGraphs[i] = new DialogGraph(240,50,640,480);
	}

	addDialogNodeType("Start",2,"Start");
	addDialogNodeType("End",3, "End");

	addDialogNodeType("Check Event",1,"Check","Event","","",2,0);
		setDialogNodeOuts(2, "Clear", "Set");
		setDialogNodeArgs(4,ARG_WORD,"Event Number",ARG_IGNORE,"",ARG_SBRANCH,"Branch On",ARG_IGNORE,"");
		setDialogNodeHelp("Branches the script depending on whether a specific event has been set.\n\nEvent Number: Event to check");

	addDialogNodeType("Set Event",0, "Set", "Event","","",3,0);
		setDialogNodeArgs(2,ARG_WORD,"Event Number",ARG_IGNORE,"");
		setDialogNodeHelp("Sets an event number as completed.\n\nEvent Number: Event to set");

	addDialogNodeType("Clear Event",0, "Clear", "Event","","",3,0);
		setDialogNodeArgs(2,ARG_WORD,"Event Number",ARG_IGNORE,"");
		setDialogNodeHelp("Clears the completed state of an event number.\n\nEvent Number: Event to clear");

	addDialogNodeType("Check Dialog Number",1,"Dialog","Number","","",2,0);
		setDialogNodeOuts(2,"Equal","Not Equal");
		setDialogNodeArgs(3,ARG_WORD,"Dialog Number",ARG_BRANCH,"Branch On",ARG_IGNORE,"");
		setDialogNodeHelp("Looks for a specific dialog number. When talking \\ interacting, each target will have a dialog number and group assigned.\n\nDialog Number: Dialog number to look for");

	addDialogNodeType("Check Dialog Group",1,"Dialog","Group","","",2,0);
		setDialogNodeOuts(2,"Equal","Not Equal");
		setDialogNodeArgs(3,ARG_WORD,"Group Number",ARG_BRANCH,"Branch On",ARG_IGNORE,"");
		setDialogNodeHelp("Looks for a specific dialog group. When talking \\ interacting, each target will have a dialog number and group assigned.\n\nDialog Group: Group to look for");

	addDialogNodeType("Set Message Bank",0,"Set","Message","Bank","",3,0);
		setDialogNodeArgs(1,ARG_MESSAGE,"Message Number");
		setDialogNodeHelp("Sets the starting message number for future messages. Generally when displaying a message, the number is added to the message bank.\n\nMessage Number: The message to start at");

	addDialogNodeType("Clear Message Bank",0,"Clear","Message","Bank");
		setDialogNodeHelp("Resets the message bank, future messages will use their actual number instead of being added to anything.");

	addDialogNodeType("Backup Message Bank",0,"Backup","Message","Bank");
		setDialogNodeHelp("Saves the current message bank, to be retrieved later.");

	addDialogNodeType("Restore Message Bank",0,"Restore","Message","Bank");
		setDialogNodeHelp("Loads the last saved message bank.");

	addDialogNodeType("Set Portrait",0,"Set","Portrait","","",3,0);//10
		setDialogNodeArgs(1,ARG_BYTE,"Portrait");
		setDialogNodeHelp("Sets the portrait to be displayed with a message.\n\nPortrait: The gfx number of the portrait to display");

	addDialogNodeType("Set Text Sound",0,"Set","Text","Sound","",3,0);
		setDialogNodeArgs(2,ARG_VOICE,"Map Sprite",ARG_IGNORE,"");
		setDialogNodeHelp("Sets the sound type to use when displaying a messages. Different characters and enemies use slightly different sounds when speaking.\n\nMap Sprite: The map sprite number to pull the text sound from.");

	addDialogNodeType("Set Message Argument",0,"Set","Message","Argument","",3,0);
		setDialogNodeArgs(1,ARG_WORD,"Value");
		setDialogNodeHelp("Sets the value to use for messages which have a variable section like a characters name or a number.");
	addDialogNodeType("Set Msg Argument From ID",0,"Set","Message","Argument","From ID");
		setDialogNodeHelp("Sets the message argument based on the current dialog group.");

	addDialogNodeType("Clear Message",0,"Clear","Message");
		setDialogNodeHelp("Closes the message window.");
	addDialogNodeType("Display Message",0,"Display","Message","","",3,0);
		setDialogNodeArgs(1,ARG_BANKED,"Message Offset");
		setDialogNodeHelp("Displays a message to the screen.\n\nMessage Offset: Number to add to the current message bank to get the message to display.");

	addDialogNodeType("Display Message From ID",0,"Display","Message", "From ID","");
		setDialogNodeArgs(1,ARG_ADDSUB,"Message Offset");
		setDialogNodeHelp("Displays a message to the screen, uses the current dialog number in addition to the message bank.\n\nMessage Offset: Number to add to the current message bank + dialog number to get the message to display.");

	addDialogNodeType("Display Shop",0,"Display","Shop","","",3,0);
		setDialogNodeArgs(2,ARG_BYTE,"Shop Number",ARG_IGNORE,"");
		setDialogNodeHelp("Opens a shop menu.\n\nShop Number: Shop to display");

	addDialogNodeType("Priest Menu",0,"Priest","Menu");
		setDialogNodeHelp("Opens the priest menu.");

	addDialogNodeType("Display Yes/No",0,"Display","Yes/No");
		setDialogNodeArgs(2,ARG_YESNO,"Message (Y/N)",ARG_IGNORE,"");
		setDialogNodeHelp("Displays a yes/no choice and then one of two messages depending on the response.\n\nMessage (Y/N): Messages to display for yes and no, added to the current message bank.");

	addDialogNodeType("Display Yes/No Sequence",0,"Display","Yes/No","Seqeunce");
		setDialogNodeHelp("Displays a sequence of yes/no choices. Memory value 2 is used as the starting message, and is increased by 1 for yes and decreased by 1 for no.");

	addDialogNodeType("Branch on Yes/No",1,"Yes/No");
		setDialogNodeOuts(2,"No","Yes");
		setDialogNodeArgs(2,ARG_IGNORE,"",ARG_BRANCH,"Branch On");
		setDialogNodeHelp("Branches the script depending on the response to a yes/no choice.");

	addDialogNodeType("More Text Prompt",0,"More","Text");//20
		setDialogNodeHelp("Pauses the message and displays the flashing arrow indicating more text to follow.");

	addDialogNodeType("Special Message",0, "Special", "Message","","",3,0);
		setDialogNodeArgs(1,ARG_SPECIAL,"Message");
		setDialogNodeHelp("Displays one of a few standard messages, click to cycle.");

	addDialogNodeType("Give Item To Hero",1, "Give", "Item","To Hero","",3,0);
		setDialogNodeOuts(2,"Have Room","No Room");
		setDialogNodeArgs(4,ARG_ITEM,"Item",ARG_REPEAT,"",ARG_IGNORE,"",ARG_BRANCH,"Branch On");
		setDialogNodeHelp("Attempts to give an item to the hero and branches the script depending on if they have room.");

	addDialogNodeType("Give Item To Hero (No Msg)",1, "Give", "Item","To Hero","",3,0);
		setDialogNodeOuts(2,"Have Room","No Room");
		setDialogNodeArgs(3,ARG_ITEM,"Item",ARG_IGNORE,"",ARG_BRANCH,"Branch On");
		setDialogNodeHelp("Attempts to give an item to the hero and branches the script depending on if they have room, doesn't display a message stating the item was recieved.");

	addDialogNodeType("Remove Item From Force",0, "Remove", "Item","From Force","",3,0);
		setDialogNodeArgs(1,ARG_ITEM,"Item");
		setDialogNodeHelp("Searches all characters for an item and removes it.");

	addDialogNodeType("Replace Item From Force",0, "Replace", "Item","From Force","",3,0);
		setDialogNodeArgs(4,ARG_ITEM,"Find Item",ARG_IGNORE,"",ARG_ITEM,"Replace With",ARG_REPEAT,"");
		setDialogNodeHelp("Searches all characters for an item and replaces it with another item.");

	addDialogNodeType("Check Force For Item",1, "Check", "Force","For Item","",3,0);
		setDialogNodeOuts(2,"Have","Don't Have");
		setDialogNodeArgs(4,ARG_ITEM,"Item",ARG_IGNORE,"",ARG_IGNBRA,"",ARG_IGNORE,"");
		setDialogNodeHelp("Searches all characters for an item and branches the scripting depending on if it is found.");

	addDialogNodeType("Set Money",0, "Set", "Money","","",3,0);
		setDialogNodeArgs(1,ARG_LONG,"Money");
		setDialogNodeHelp("Sets the current gold to exactly a given value.");

	addDialogNodeType("Add Money",0, "Add", "Money","","",3,0);
		setDialogNodeArgs(1,ARG_LONG,"Money");
		setDialogNodeHelp("Adds an amount to the current gold.");

	addDialogNodeType("Set Sprite Direction",0, "Set Sprite", "Direction","","",3,0);
		setDialogNodeArgs(2,ARG_BYTE,"Sprite",ARG_DIR,"Direction");
		setDialogNodeHelp("Changes the direction of one of the characters on the map.");

	addDialogNodeType("Set Sprite Direction From ID",0, "Set Sprite", "Direction","From ID","",3,0);
		setDialogNodeArgs(1,ARG_DIR,"Direction");
		setDialogNodeHelp("Changes the direction of one of the characters on the map, using the current dialog number to determine the character.");

	addDialogNodeType("Check Hero Direction",1, "Hero", "Direction","","",2,0);//30
		setDialogNodeOuts(2,"Equal","Not Equal");
		setDialogNodeArgs(3,ARG_DIR2,"Direction",ARG_IGNBRA,"",ARG_IGNORE,"");
		setDialogNodeHelp("Branches the script depending on if the hero is facing a specified direction.");

	addDialogNodeType("Add to Force (Data Only)",0, "Add Force", "Member","(Data)","",3,0);
		setDialogNodeArgs(1,ARG_CHAR,"Member");
		setDialogNodeHelp("Adds a character to the force, but gives no notice of any kind.");
	addDialogNodeType("Add to Force (Sound+MSG)",0, "Add Force", "Member","(Message)","",3,0);
		setDialogNodeArgs(3,ARG_BYTE,"Sound Effect",ARG_WORD,"Message", ARG_CHAR,"Member");
		setDialogNodeHelp("Plays a sound effect and displays a message together, to be used with the data only add to force for custom sound / message.");
	addDialogNodeType("Add to Force (Standard)",0, "Add Force", "Member","(Standard)","",3,0);
		setDialogNodeArgs(1,ARG_CHAR,"Member");
		setDialogNodeHelp("Adds a character to the force, using the basic sound and message.");

	addDialogNodeType("Clear Portrait", 0, "Clear", "Portrait", "", "");
		setDialogNodeHelp("Clears the currently displayed portrait.");

	addDialogNodeType("Set Memory Flag",0, "Set", "Memory","Flag","",3,0);
		setDialogNodeArgs(1,ARG_BYTE,"Flag Number");
		setDialogNodeHelp("Sets a temporary memory value to true.");
	addDialogNodeType("Clear Memory Flag",0, "Clear", "Memory","Flag","",3,0);
		setDialogNodeArgs(1,ARG_BYTE,"Flag Number");
		setDialogNodeHelp("Sets a temporary memory value to false.");
	addDialogNodeType("Test Memory Flag",1, "Memory","Flag","","",2,0);//40
		setDialogNodeOuts(2,"Zero","Not Zero");
		setDialogNodeArgs(2,ARG_BYTE,"Flag Number",ARG_SBRANCH,"Branch On");
		setDialogNodeHelp("Branches the script depending on if a temporary memory value is set or not.");
	addDialogNodeType("Load Memory Flag",0, "Load", "Memory","Flag","",3,0);
		setDialogNodeArgs(1,ARG_BYTE,"Flag Number");
		setDialogNodeHelp("Loads a temporary memory value to be used later.");
	addDialogNodeType("Test Loaded Flag",1, "Loaded","Flag","","",2,0);
		setDialogNodeOuts(2,"Zero","Not Zero");
		setDialogNodeArgs(1,ARG_SBRANCH,"Branch On");
		setDialogNodeHelp("Branches the script depending on if the last loaded value is set or not.");
	addDialogNodeType("Load Memory Value",0, "Load", "Memory","Value","",3,0);
		setDialogNodeArgs(1,ARG_BYTE,"Flag Number");
		setDialogNodeHelp("Loads a saved memory value to be used by other actions.");
	addDialogNodeType("Load/Test Memory Value",1, "Load/Test", "Memory","Value","",3,0);
		setDialogNodeOuts(2,"Zero","Not Zero");
		setDialogNodeArgs(2,ARG_BYTE,"Flag Number",ARG_SBRANCH,"Branch On");
		setDialogNodeHelp("Loads a saved memory value to be used by other actions. Then branches script depending on if the value is set.");
	addDialogNodeType("Increment Memory Value",0, "Increment", "Memory","Value","",3,0);
		setDialogNodeArgs(1,ARG_BYTE,"Flag Number");
		setDialogNodeHelp("Adds one to a temporary memory value.");
	addDialogNodeType("Decrement Memory Value",0, "Decrement", "Memory","Value","",3,0);
		setDialogNodeArgs(1,ARG_BYTE,"Flag Number");
		setDialogNodeHelp("Subtracts one from a temporary memory value.");
	addDialogNodeType("Play Sound",0, "Play", "Sound","","",3,0);
		setDialogNodeArgs(1,ARG_WORD,"Sound Effect");
		setDialogNodeHelp("Plays a sound effect.");
	addDialogNodeType("Clear Sound?",0, "Clear", "Sound?","","",3,0);
		setDialogNodeHelp("Stops current sound effects?");
	addDialogNodeType("Restore Music",0, "Restore", "Music","","",3,0);
		setDialogNodeHelp("Restarts music after certain events / sound effects which break music.");
	addDialogNodeType("Unknown 1",0, "Unknown", "1","","",3,0);//50?
	addDialogNodeType("Unknown 2",0, "Unknown", "2","","",3,0);
		setDialogNodeArgs(1,ARG_WORD,"?");
	addDialogNodeType("Unknown 3",0, "Unknown", "3","","",3,0);
	addDialogNodeType("Unknown 4",0, "Unknown", "4","","",3,0);
	addDialogNodeType("Set Portrait Version",0, "Set", "Portrait","Version","",3,0);
		setDialogNodeArgs(1,ARG_BYTE,"Version");
		setDialogNodeHelp("Changes the displayed portrait.\n\nVersion: 0 = normal, 1 = eyes closed, 2 = mouth open");
	addDialogNodeType("Unknown 6",0, "Unknown", "6","","",3,0);
	addDialogNodeType("Unknown 7",0, "Unknown", "7","","",3,0);
	addDialogNodeType("Unknown 8",0, "Unknown", "8","","",3,0);

	for(i=0;i<NUM_DIALOG;i++){
		DialogGraphs[i]->addNode(16,16);

		DialogGraphs[i]->buildList();
	}

	addDialogPattern(10, 2,  "Check Event", 0x30, 0x3C, -2, 0x4E, 0xB9, -12, 0x17C6A, -21, 0, -2);
	addDialogPattern(9,  2,  "Check Event", 0x30, 0x3C, -2, 0x4E, 0xB9, -12, 0x17C6A, -21, -1);
	addDialogPattern(10, 2,  "Check Event", 0x30, 0x3C, -2, 0x61, 0, -6, 0x17C6A, -21, 0, -2);
	addDialogPattern(9,  2,  "Check Event", 0x30, 0x3C, -2, 0x61, 0, -6, 0x17C6A, -21, -1);
	addDialogPattern(7,  3,  "Set Event", 0x30, 0x3C, -2, 0x4E, 0xB9, -12, 0x17C5E);
	addDialogPattern(7,  3,  "Set Event", 0x30, 0x3C, -2, 0x61, 0, -6, 0x17C5E);
	addDialogPattern(7,  4,  "Clear Event", 0x30, 0x3C, -2, 0x4E, 0xB9, -12, 0x17C64);
	addDialogPattern(7,  4,  "Clear Event", 0x30, 0x3C, -2, 0x61, 0, -6, 0x17C64);
	addDialogPattern(6,  5,  "Check Dialog Number", 0x0C, 0x01, -2, -21, 0, -2);
	addDialogPattern(5,  5,  "Check Dialog Number", 0x0C, 0x01, -2, -21, -1);
	addDialogPattern(6,  5,  "Check Dialog Number", 0x0C, 0x41, -2, -21, 0, -2);
	addDialogPattern(5,  5,  "Check Dialog Number", 0x0C, 0x41, -2, -21, -1);
	addDialogPattern(6,  6,  "Check Dialog Group", 0x0C, 0x02, -2,-21, 0, -2);
	addDialogPattern(5,  6,  "Check Dialog Group", 0x0C, 0x02, -2,-21, -1);
	addDialogPattern(6,  6,  "Check Dialog Group", 0x0C, 0x42, -2,-21, 0, -2);
	addDialogPattern(5,  6,  "Check Dialog Group", 0x0C, 0x42, -2,-21, -1);
	addDialogPattern(3,  7,  "Set Message Bank", 0x3C, 0x3C, -2);
	addDialogPattern(2,  8,  "Clear Message Bank", 0x42, 0x46);
	addDialogPattern(2,  9,  "Backup Message Bank", 0x3F, 0x06);
	addDialogPattern(2,  10,  "Restore Message Bank", 0x3C, 0x1F);
	addDialogPattern(4,  11,  "Set Portrait", 0x70, -1, 0x4E, 0x94);
	addDialogPattern(11, 12,  "Set Text Sound Pitch", 0x2F, 0, 0x10, 0x3C, -2, 0x4E, 0xB9, -12, 0x17F64, 0x20, 0x1F);
	addDialogPattern(11, 12,  "Set Text Sound Pitch", 0x2F, 0, 0x10, 0x3C, -2, 0x61, 0, -6, 0x17F64, 0x20, 0x1F);
	addDialogPattern(7,  13, "Set Message Argument", 0x30, 0x3C, -2, 0x31, 0xC0, 0xF8, 0x44);
	addDialogPattern(8,  14, "Set Message Argument to Dialog #", 0x42, 0x40, 0x10, 0x02, 0x31, 0xC0, 0xF8, 0x44);
	addDialogPattern(4,  15, "Clear Message Box?", 0x4E, 0xB9, -12, 0x0328);
	addDialogPattern(4,  15, "Clear Message Box 2?", 0x4E, 0xB9, -12, 0x017E58);
	addDialogPattern(4,  15, "Clear Message Box 2?", 0x61, 0, -6, 0x017E58);
	addDialogPattern(4,  16, "Display Message", 0x70, -1, 0x4E, 0x95);
	addDialogPattern(2,  16, "Display Message", 0x4E, 0x95);
	//if this changes from 17 need to adjust BuildDialogGraphLine
	addDialogPattern(6,  17, "Display Message (ID-X)", 0x30, 0x01, -1, 0x40, 0x4E, 0x95);//-1 value needs special handling...
	addDialogPattern(4,  17, "Display Message (ID)", 0x30, 0x01, 0x4E, 0x95);
	addDialogPattern(4,  17, "Display Message (ID-1)", 0x4E, 0xB9, -12, 0x180A6);
	addDialogPattern(4,  17, "Display Message (ID-1)", 0x60, 0, -6, 0x180A6);
	addDialogPattern(6,  17, "Display Message (ID+X)", -1, 0x41, 0x30, 0x01, 0x4E, 0x95);//-1 value needs special handling...
	addDialogPattern(6,  17, "Display Message (ID+X)", -1, 0x41, 0x30, 0x01, 0x4E, 0xD5);//-1 value needs special handling...
	addDialogPattern(4,  17, "Display Message (ID)", 0x30, 0x01, 0x4E, 0xD5);
	addDialogPattern(32, 18, "Display Shop", 0x70, -1, 0x42, 0x41, 0x12, 0x2E, 0xFF, 0xFD, 0x14, 0x2E, 0xFF, 0xFF, 0xE1, 0x4A, 0x14, 0x2E, 0xFF, 0xFE, 0x4E, 0xB9, -12, 0x168FE, 0x4A, 0x41, 0x56, 0xEE, 0xFF, 0xFD, 0x1D, 0x42, 0xFF, 0xFE);
	addDialogPattern(32, 18, "Display Shop", 0x70, -1, 0x42, 0x41, 0x12, 0x2E, 0xFF, 0xFD, 0x14, 0x2E, 0xFF, 0xFF, 0xE1, 0x4A, 0x14, 0x2E, 0xFF, 0xFE, 0x61, 0x00, -6, 0x168FE, 0x4A, 0x41, 0x56, 0xEE, 0xFF, 0xFD, 0x1D, 0x42, 0xFF, 0xFE);
	addDialogPattern(30, 19, "Priest Menu", 0x42, 0x41, 0x12, 0x2E, 0xFF, 0xFD, 0x14, 0x2E, 0xFF, 0xFF, 0xE1, 0x4A, 0x14, 0x2E, 0xFF, 0xFE, 0x4E, 0xB9, -12, 0x17028, 0x4A, 0x41, 0x56, 0xEE, 0xFF, 0xFD, 0x1D, 0x42, 0xFF, 0xFE);
	addDialogPattern(30, 19, "Priest Menu", 0x42, 0x41, 0x12, 0x2E, 0xFF, 0xFD, 0x14, 0x2E, 0xFF, 0xFF, 0xE1, 0x4A, 0x14, 0x2E, 0xFF, 0xFE, 0x61, 0x00, -6, 0x17028, 0x4A, 0x41, 0x56, 0xEE, 0xFF, 0xFD, 0x1D, 0x42, 0xFF, 0xFE);
	addDialogPattern(7,  20, "Display Yes/No", 0x30, 0x3C, -2, 0x4E, 0xB9, -12, 0x18046);
	addDialogPattern(7,  20, "Display Yes/No", 0x30, 0x3C, -2, 0x61, 0, -6, 0x18046);
	addDialogPattern(4,  21, "Display Yes/No Sequence", 0x4E, 0xB9, -12, 0x180CA);
	addDialogPattern(4,  21, "Display Yes/No Sequence", 0x61, 0, -6, 0x180CA);
	addDialogPattern(7,  22, "Branch on Yes/No", 0x4E, 0xB9, -12, 0x18056, -21, 0, -2);
	addDialogPattern(6,  22, "Branch on Yes/No", 0x4E, 0xB9, -12, 0x18056, -21, -1);
	addDialogPattern(7,  22, "Branch on Yes/No", 0x61, 0, -6, 0x18056, -21, 0, -2);
	addDialogPattern(6,  22, "Branch on Yes/No", 0x61, 0, -6, 0x18056, -21, -1);
	addDialogPattern(22, 23, "More Text?", 0x48, 0xE7, 0, 0xFE, 0x4E, 0xB9, -12, 0x17E42, 0x70, 0x14, 0x4E, 0xB9, -12, 0x244, 0x4E, 0xB9, -12, 0x15DE2, 0x4C, 0xDF, 0x7F, 0);
	addDialogPattern(22, 23, "More Text?", 0x48, 0xE7, 0, 0xFE, 0x61, 0, -6, 0x17E42, 0x70, 0x14, 0x4E, 0xB9, -12, 0x244, 0x61, 0, -6, 0x15DE2, 0x4C, 0xDF, 0x7F, 0);
	//if this changes from 24, need to update the findDialogLabel call
	addDialogPattern(4,  24, "Special Message", 0x4E, 0xB9, -12, 0x180B4);
	addDialogPattern(4,  24, "Special Message", 0x60, 0, -6, 0x180B4);
	addDialogPattern(4,  24, "Special Message", 0x4E, 0xB9, -12, 0x18074);
	addDialogPattern(4,  24, "Special Message", 0x60, 0, -6, 0x18074);
	addDialogPattern(4,  24, "Special Message", 0x4E, 0xB9, -12, 0x1808A);
	addDialogPattern(4,  24, "Special Message", 0x60, 0, -6, 0x1808A);

	addDialogPattern(34, 28, "Replace Item from Force", 0x70, -1, 0x4E, 0xB9, -12, 0x17EEC, 0x70, -1, 0x31, 0xC0, 0xF8, 0x44, 0x48, 0xE7, 0xC0, 0x00, 0x42, 0x40, 0x10, 0x39, 0, 0xFF, 0xF0, 0x01, 0x72, -1, 0x4E, 0xB9, -12, 0x2024C, 0x4C, 0xDF, 0, 0x03);
	addDialogPattern(34, 28, "Replace Item from Force", 0x70, -1, 0x61, 0, -6, 0x17EEC, 0x70, -1, 0x31, 0xC0, 0xF8, 0x44, 0x48, 0xE7, 0xC0, 0x00, 0x42, 0x40, 0x10, 0x39, 0, 0xFF, 0xF0, 0x01, 0x72, -1, 0x4E, 0xB9, -12, 0x2024C, 0x4C, 0xDF, 0, 0x03);
	addDialogPattern(19, 25, "Give Item to Hero", 0x42, 0x78, 0xF8, 0x44, 0x31, 0xFC,  0,   -1, 0xF8, 0x46, 0x70, -1, 0x4E, 0xB9, -12, 0x17ED6, -21, 0, -2);
	addDialogPattern(18, 25, "Give Item to Hero", 0x42, 0x78, 0xF8, 0x44, 0x31, 0xFC,  0,   -1, 0xF8, 0x46, 0x70, -1, 0x4E, 0xB9, -12, 0x17ED6, -21, -1);
	addDialogPattern(19, 25, "Give Item to Hero", 0x42, 0x78, 0xF8, 0x44, 0x31, 0xFC,  0,   -1, 0xF8, 0x46, 0x70, -1, 0x61, 0, -6, 0x17ED6, -21, 0, -2);
	addDialogPattern(18, 25, "Give Item to Hero", 0x42, 0x78, 0xF8, 0x44, 0x31, 0xFC,  0,   -1, 0xF8, 0x46, 0x70, -1, 0x61, 0, -6, 0x17ED6, -21, -1);
	addDialogPattern(19, 25, "Give Item to Hero", 0x42, 0x78, 0xF8, 0x44, 0x70, -1, 0x31, 0xC0, 0xF8, 0x46, 0x70, -1, 0x4E, 0xB9, -12, 0x17ED6, -21, 0, -2);
	addDialogPattern(18, 25, "Give Item to Hero", 0x42, 0x78, 0xF8, 0x44, 0x70, -1, 0x31, 0xC0, 0xF8, 0x46, 0x70, -1, 0x4E, 0xB9, -12, 0x17ED6, -21, -1);
	addDialogPattern(9,  26, "Give Item to Hero (no msg)", 0x70, -1, 0x4E, 0xB9, -12, 0x17ED6, -21, 0, -2);
	addDialogPattern(8,  26, "Give Item to Hero (no msg)", 0x70, -1, 0x4E, 0xB9, -12, 0x17ED6, -21, -1);
	addDialogPattern(9,  26, "Give Item to Hero (no msg)", 0x70, -1, 0x61, 0, -6, 0x17ED6, -21, 0, -2);
	addDialogPattern(8,  26, "Give Item to Hero (no msg)", 0x70, -1, 0x61, 0, -6, 0x17ED6, -21, -1);
	addDialogPattern(11, 29, "Check Force for Item", 0x42, 0x40, 0x72, -1, 0x4E, 0xB9, -12, 0x20370, -21, 0, -2);
	addDialogPattern(10, 29, "Check Force for Item", 0x42, 0x40, 0x72, -1, 0x4E, 0xB9, -12, 0x20370, -21, -1);
	addDialogPattern(9, 29, "Check Force for Item", 0x72, -1, 0x4E, 0xB9, -12, 0x20370, -21, 0, -2);
	addDialogPattern(8, 29, "Check Force for Item", 0x72, -1, 0x4E, 0xB9, -12, 0x20370, -21, -1);
	addDialogPattern(6,  27, "Remove Item from Force", 0x70, -1, 0x4E, 0xB9, -12, 0x17EEC);
	addDialogPattern(6,  27, "Remove Item from Force", 0x70, -1, 0x61, 0, -6, 0x17EEC);

	addDialogPattern(9,  30, "Set Money", 0x22, 0x3C, -4, 0x4E, 0xB9, 0, 0x02, 0x03, 0x50);
	addDialogPattern(8,  30, "Set Money", 0x72, -1, 0x4E, 0xB9, 0, 0x02, 0x03, 0x50);
	addDialogPattern(9,  31, "Add Money", 0x22, 0x3C, -4, 0x4E, 0xB9, 0, 0x02, 0x03, 0x54);

	addDialogPattern(8,  32, "Set Sprite Direction", 0x70, -1, 0x72, -1, 0x4E, 0xB9, -12, 0x11126);
	addDialogPattern(8,  33, "Set Sprite Direction (From Dialog Group?)", 0x30, 0x01, 0x72, -1, 0x4E, 0xB9, -12, 0x11126);

	addDialogPattern(15, 34, "Check Hero Direction", 0x70, 0x18, 0xC0, 0x39, 0, 0xFF, 0x50, 0x02, 0x0C, 0, 0, -1, -21, 0, -2);
	addDialogPattern(14, 34, "Check Hero Direction", 0x70, 0x18, 0xC0, 0x39, 0, 0xFF, 0x50, 0x02, 0x0C, 0, 0, -1, -21, -1);

	addDialogPattern(12, 35, "Add Force Member", 0x2F, 0, 0x70, -1, 0x4E, 0xB9, -12, 0x17FE0, 0x4C, 0xDF, 0, 0x01);
	addDialogPattern(12, 35, "Add Force Member", 0x2F, 0, 0x70, -1, 0x61, 0, -6, 0x17FE0, 0x4C, 0xDF, 0, 0x01);
	addDialogPattern(19, 36, "Add Force Member (Sound + MSG)", 0x48, 0xE7, 0xC2, 0, 0x70, -1, 0x3C, 0x3C, -2, 0x72, -1, 0x4E, 0xB9, -12, 0x17FF6, 0x4C, 0xDF, 0, 0x43);
	addDialogPattern(19, 36, "Add Force Member (Sound + MSG)", 0x48, 0xE7, 0xC2, 0, 0x70, -1, 0x3C, 0x3C, -2, 0x72, -1, 0x61, 0, -6, 0x17FF6, 0x4C, 0xDF, 0, 0x43);
	addDialogPattern(10, 37, "Add Force Member (Standard)", 0x2F, 0, 0x70, -1, 0x4E, 0xB9, -12, 0x17F88, 0x20, 0x1F);
	addDialogPattern(10, 37, "Add Force Member (Standard)", 0x2F, 0, 0x70, -1, 0x61, 0, -6, 0x17F88, 0x20, 0x1F);

	addDialogPattern(4, 38, "Clear Portrait", 0x4E, 0xB9, -12, 0x17EB6);

	addDialogPattern(4,  39, "Set some flag?", 0x50, 0xF8, 0xF0, -1);
	addDialogPattern(4,  40, "Clear some flag?", 0x51, 0xF8, 0xF0, -1);

	addDialogPattern(7,  41, "Test some flag?", 0x4A, 0x38, 0xF0, -1, -21, 0, -2);
	addDialogPattern(6,  41, "Test some flag?", 0x4A, 0x38, 0xF0, -1, -21, -1);

	addDialogPattern(4,  42, "Load flag?", 0x1E, 0x38, 0xF0, -1);
	addDialogPattern(5,  43, "Test loaded flag?", 0x4A, 0x07, -21, 0, -2);
	addDialogPattern(4,  43, "Test loaded flag?", 0x4A, 0x07, -21, -1);

	addDialogPattern(6,  44, "Load Scratch?", 0x30, 0x39, 0, 0xFF, 0xF0, -1);
	addDialogPattern(9,  45, "Load and test Scratch?", 0x20, 0x38, 0xF0, -1, 0x4A, 0, -21, 0, -2);
	addDialogPattern(8,  45, "Load and test Scratch?", 0x20, 0x38, 0xF0, -1, 0x4A, 0, -21, -1);
	addDialogPattern(6,  46, "Increment Scratch?", 0x52, 0x79, 0, 0xFF, 0xF0, -1);
	addDialogPattern(6,  47, "Decrement Scratch?", 0x53, 0x79, 0, 0xFF, 0xF0, -1);

	addDialogPattern(3,  48, "Play Sound?", 0x4E, 0x40, -2);
	addDialogPattern(4,  49, "Clear Sound?", 0x42, 0x78, 0xC0, 0xBE);

	addDialogPattern(10,  50 ,"Restore Music", 0x30, 0x3C, 0, 0xFB, 0x4E, 0xB9, 0, 0, 0x02, 0xE4);


	//split these up after more research
	addDialogPattern(6,  51, "Wait for Sound?", 0x4E, 0xF9, 0, 0, 0x02, 0xCC);
	addDialogPattern(9,  52, "Clear, Play, Wait for Sound?", 0x30, 0x3C, -2, 0x4E, 0xB9, 0, 0, 0x02, 0xE4);
	addDialogPattern(6,  53, "Backup Sound?", 0x3D, 0x78, 0xC0, 0xBE, 0xFF, 0xFA);
	addDialogPattern(6,  54, "Restore Sound?", 0x31, 0xEE, 0xFF, 0xFA, 0xC0, 0xBE);
	addDialogPattern(16, 55, "Set Portrait Version", 0x70, -1, 0x48, 0xE7, 0x02, 0xFE,0x4E, 0xB9, 0, 0, 0x80, 0xD8, 0x4C, 0xDF, 0x7F, 0x40);
	addDialogPattern(2,  56, "Sound Something?", 0x4E, 0x93);
	addDialogPattern(4,  57, "Sound Something?", 0x4E, 0xB9, -12, 0x17E42);
	addDialogPattern(4,  57, "Sound Something?", 0x61, 0, -6, 0x17E42);
	addDialogPattern(14, 58, "Sound Something?", 0x48, 0xE7, 0x02, 0xFE,0x4E, 0xB9, 0, 0x12, 0x40, 0x28, 0x4C, 0xDF, 0x7F, 0x40);

	AdvancedNodes(Dialog,59)

	addDialogPattern(2,  1, "End", 0x60, -13);
	addDialogPattern(3,  1, "End", 0x60, 0, -14);

	addDialogPattern(3,  1, "Branch", 0x60, 0, -26);//just follow, shouldn't create a node
	addDialogPattern(2,  1, "Branch", 0x60, -25);

	addDialogPattern(3,  1, "Branch", 0x60, 0, -18);//just follow, shouldn't create a node
	addDialogPattern(2,  1, "Branch", 0x60, -17);
	
	addDialogPattern(2,  1, "End",0x4E,0x75);
}

int maxline;

int findDialogLabel(int script, int label){
	int i=0;
	int p;
	while(DialogScript[script][i]!=-1){
		p = DialogScript[script][i];
		switch(p){
		case -2:
			i++;
			if(DialogScript[script][i]==label)return i+1;
			break;
		case -3:
			i++;
			break;
		case -4:
			break;
		default:
			i+=getDialogPatternArgs(p);
			break;
		}
		i++;
	}
	return -1;
}

void labelDialogBranches(DialogGraphNode * node, int arg, bool set=false, bool yn=false){
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

void propagateBank(DialogGraphNode * node, int bank, bool wait=false,bool set=true, bool ignore=false){
	bool s=set;
	bool w=wait;

	if(node->visited)return;
	node->visited=true;

	if(!ignore){
		if(!strcmp(node->type->name,"Set Message Bank")){
			if(!wait)return;
			s = false;
		}
		if(!strcmp(node->type->name,"Clear Message Bank")){
			if(!wait)return;
			s = false;
		}
	}
	if(!strcmp(node->type->name,"Backup Message Bank")){
		node->bbank = bank;
		w=true;
	}
	if(!strcmp(node->type->name,"Restore Message Bank")){
		w=false;
		s=true;
	}

	if(s)node->bank = bank;
	if(w)node->bbank = bank;

	LLNode<DialogGraphNode*>* cur = node->out.head;
	while(cur){
		propagateBank(cur->data,bank,w,s);
		cur=cur->next;
	}
}

void propagateBank(DialogGraph * graph, DialogGraphNode * node, int bank){
	graph->clearVisited();
	propagateBank(node,bank,false,true,true);
}

void BuildDialogGraphLine(int script, int start, int sx, int sy, DialogGraphNode * prev=0, int b=0, int bb=0){

	DialogGraphNode * last = prev;

	int i=start;

	int x=sx;
	int y=sy;

	int p,a;

	int bank=b;
	int bbank=bb;

	int oldline = maxline;

	while(DialogScript[script][i]!=-1){
		p = DialogScript[script][i];

		/*if(p==NumDialogPatterns-2||p==NumDialogPatterns-3){
			i+=2;
			continue;
		}*/
		switch(p){
		case -2:
			i++;
			break;
		case -3:
			i++;
			if (last && last != DialogGraphs[script]->nodes.head->data) {
				if (last->branch && last->branch != DialogScript[script][i]) {
					last->branch2 = DialogScript[script][i];
					last->brasec2 = false;
				} else {
					last->branch = DialogScript[script][i];
					last->brasec = false;
				}
			} else {
				if (DialogGraphs[script]->nodes.head->data->branch && DialogGraphs[script]->nodes.head->data->branch != DialogScript[script][i]) {
					DialogGraphs[script]->nodes.head->data->branch2 = DialogScript[script][i];
					DialogGraphs[script]->nodes.head->data->brasec2 = true;
				} else {
					DialogGraphs[script]->nodes.head->data->branch = DialogScript[script][i];
					DialogGraphs[script]->nodes.head->data->brasec = true;
				}
			}
			break;
		case -4:
			return;
		default:
			LLNode<DialogGraphNode*>* cur = DialogGraphs[script]->nodes.head;

			DialogGraphNode * temp;
			if (last && last != DialogGraphs[script]->nodes.head->data) {
				temp = last;
			} else {
				temp = DialogGraphs[script]->nodes.head->data;
			}

			if (DialogGraphs[script]->nodes.head->data->type->numout<3)
			while (cur) {
				if (cur->data->offset == DialogScriptO[script][i] && strcmp(cur->data->type->name,"End")) {
					DialogGraphs[script]->connect(temp, cur->data);
					return;
				}
				cur = cur->next;
			}


			DialogGraphs[script]->addNode(x,y,DialogPatternNodes[p],DialogScriptO[script][i]);
			a = getDialogPatternArgs(p);
			for(int j=0;j<a;j++){
				DialogGraphs[script]->nodes.head->data->args[j]=DialogScript[script][i+j+1];
			}
			if(a&&DialogPatternNodes[p]==17&&DialogGraphs[script]->nodes.head->data->args[0]==0x180A6)
				DialogGraphs[script]->nodes.head->data->args[0]=0x53;
			i+=a;

			if(!strcmp(DialogNames[p],"Set Message Bank")){
				bank=DialogGraphs[script]->nodes.head->data->args[0];
			}
			if(!strcmp(DialogNames[p],"Clear Message Bank")){
				bank=0;
			}

			if(!strcmp(DialogNames[p],"Backup Message Bank")){
				bbank = bank;
			}
			if(!strcmp(DialogNames[p],"Restore Message Bank")){
				bank = DialogGraphs[script]->nodes.head->data->bbank;
				DialogGraphs[script]->nodes.head->data->bbank = 0;
			}

			DialogGraphs[script]->nodes.head->data->bank = bank;
			DialogGraphs[script]->nodes.head->data->bbank = bbank;

			if(last){
				DialogGraphs[script]->connect(last, DialogGraphs[script]->nodes.head->data);
				last=0;
			} else {
				DialogGraphs[script]->connect(DialogGraphs[script]->nodes.head->next->data, DialogGraphs[script]->nodes.head->data);
			}

			if(DialogGraphs[script]->nodes.head->data->type->numout>1){
				//maxline++;
				last = DialogGraphs[script]->nodes.head->data;

				if(strcmp(DialogNames[p], "Check Force for Item"))
					labelDialogBranches(last,a-2,strcmp(DialogNames[p],"Check Event")==0,strcmp(DialogNames[p],"Branch on Yes/No")==0);
			
				int lb = findDialogLabel(script, DialogScript[script][i]);



				switch(DialogScript[script][i]){
					case 0x18074:
					case 0x1808A:
					case 0x180B4:
						DialogGraphs[script]->addNode(x+112,y+maxline*96,24);//***** Make sure 24 stays the special message node
						DialogGraphs[script]->nodes.head->data->args[0]=DialogScript[script][i];
						DialogGraphs[script]->connect(DialogGraphs[script]->nodes.head->next->data, DialogGraphs[script]->nodes.head->data);
						DialogGraphs[script]->addNode(x+224,y+maxline*96,1);
						DialogGraphs[script]->connect(DialogGraphs[script]->nodes.head->next->data, DialogGraphs[script]->nodes.head->data);
						break;
					default:
						LLNode<DialogGraphNode*>* cur = DialogGraphs[script]->nodes.head;
						if (DialogGraphs[script]->nodes.head->data->type->numout<3)
						while (cur) {
							if (cur->data->offset == DialogScript[script][i] && strcmp(cur->data->type->name, "End")) {
								DialogGraphs[script]->connect(DialogGraphs[script]->nodes.head->data, cur->data);
								lb = -1;
								break;
							}
							cur = cur->next;
						}

						if (lb != -1) {
							
							int topline = maxline;

							maxline++;


							BuildDialogGraphLine(script, lb, x + 112, maxline * 96 + 16, DialogGraphs[script]->nodes.head->data, bank, bbank);

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


						
						break;
				}
			}

			if(checkDialogEnd(p)){
				int v;
				if(last)v = last->type->shape;
				else v = DialogGraphs[script]->nodes.head->data->type->shape;
				if(v!=3){
					DialogGraphs[script]->addNode(x+112,y,1);
					if(last){
						DialogGraphs[script]->connect(last, DialogGraphs[script]->nodes.head->data);
						last=0;
					} else {
						DialogGraphs[script]->connect(DialogGraphs[script]->nodes.head->next->data, DialogGraphs[script]->nodes.head->data);
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

void BuildDialogGraph(int script){
	maxline=0;

	DialogGraphs[script]->clear();

	BuildDialogGraphLine(script,0, 128, 16);

	LLNode<DialogGraphNode*>* cur = DialogGraphs[script]->nodes.head;
	while (cur) {
		if (cur->data->type->shape == 3) {
			cur = cur->next;
			continue;
		}

		if (cur->data->offset == 0x1c5c58) {
			maxline = maxline;
		}

		if (cur->data->out.size < cur->data->type->numout && cur->data->type->numargs && cur->data->type->numout<3) {
			
			LLNode<DialogGraphNode*>* cur2 = DialogGraphs[script]->nodes.head;
			while (cur2) {
				if (cur->data->branch < 0)cur->data->branch *= -1;
				if (cur2->data->offset == cur->data->branch && cur->data->branch) {
					DialogGraphs[script]->connect(cur->data, cur2->data);

					if (cur->data->brasec && cur->data->out.size > 1) {
						DialogGraphNode * temp = cur->data->out.head->data;
						
						cur->data->out.head->data = cur->data->out.tail->data;
						cur->data->out.tail->data = temp;
					}
				}

				if (cur->data->branch2 < 0)cur->data->branch2 *= -1;
				if (cur2->data->offset == cur->data->branch2 && cur->data->branch2) {
					DialogGraphs[script]->connect(cur->data, cur2->data);

					if (cur->data->brasec2 && cur->data->out.size > 1) {
						DialogGraphNode * temp = cur->data->out.head->data;

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


void LoadDialog(char * path, bool single=false){
	//return;
	ScriptsLoaded = true;
	unsigned char r,c;
	long o,mo,to;
	int i,j;

	mo=0;

	for (int i = 0; i < 64; i++) {
		for (int j = 0; j < 2000; j++) {
			DialogScript[i][j]=0;
			DialogScriptO[i][j]=0;
		}
	}


	FILE * fp = fopen(path,"rb");

	if(TeleOffset != 0x1A5880){
		fseek(fp,0x17CE9,SEEK_SET);
	} else {
		fseek(fp,0x17CEF,SEEK_SET);
	}
	fscanf(fp,"%c",&r);
	if(r!=0xF9){
		DialogHeaderOffset = 0x17D62;
	} else {
		fscanf(fp,"%c",&r);
		DialogHeaderOffset = r;
		fscanf(fp,"%c",&r);
		DialogHeaderOffset = DialogHeaderOffset*256+r;
		fscanf(fp,"%c",&r);
		DialogHeaderOffset = DialogHeaderOffset*256+r;
		fscanf(fp,"%c",&r);
		DialogHeaderOffset = DialogHeaderOffset*256+r;
	}

	fseek(fp,DialogHeaderOffset,SEEK_SET);
	for(i=0; i<NUM_DIALOG; i++){
		for(j=0; j<3; j++){
			fscanf(fp,"%c",&r);
			fscanf(fp,"%c",&c);
			if(single&&i!=subselect[mode][0])continue;
			DialogHeader[i][j]=256*r;
			DialogHeader[i][j]+=c;
		}
	}

	o = ftell(fp);

	for(i=0; i<NUM_DIALOG; i++){
		if(single&&i!=subselect[mode][0])continue;
		o = DialogHeaderOffset+DialogHeader[i][1];

		int p=0;
		int c=0;
		int k;

		for(k=0;k<32;k++){
			DialogBranches[k]=0;
		}

		DialogBranches[0]=o;
		NumBranches = 1;

		while(NumBranches){
			p = 0;
			o = 0;
			for(k=0;k<32;k++){
				if(DialogBranches[k]&&(DialogBranches[k]<o||!o))o = DialogBranches[k];
			}

			fseek(fp,o,SEEK_SET);

			while(!checkDialogEnd(p)){

				o = ftell(fp);
				if(o>mo)mo=o;

				for (k = 0; k<32; k++) {
					if (DialogBranches[k] == o) {
						DialogScript[i][c] = -2;
						c++;
						DialogScript[i][c] = o;
						c++;
						DialogBranches[k] = 0;
						NumBranches--;
						for (; k<32; k++) {
							if (DialogBranches[k] == o) {
								DialogBranches[k] = 0;
								NumBranches--;
							}
						}
					}
				}

				bool f = false;
				for (k = 0; k < c; k++) {
					if (DialogScriptO[i][k] == o) {
						f = true;
						DialogScript[i][c] = -3;
						DialogScriptO[i][c] = 0;
						c++;
						DialogScript[i][c] = o;
						DialogScriptO[i][c] = 0;
						c++;
						DialogScript[i][c] = -4;
						DialogScriptO[i][c] = 0;
						c++;
						break;
					}
				}
				if (f)break;

				

				p=checkAllDialogPatterns(fp);
				if(p==-1){
					fseek(fp,o,SEEK_SET);
					char out[512];
					unsigned char r;
					sprintf(out,"Error parsing dialog scripts.\n\nPlease submit a screenshot of this message to the forums.\n\nOffset: 0x%X Data:\n\n",o);
					for(i=0;i<32;i++){
						fscanf(fp,"%c",&r);
						sprintf(out,"%s%.2hX",out,r);
					}
					MessageBox(NULL,out,"Error",MB_OK);
					fclose(fp);
					return;
				}

				if (!strcmp(DialogNames[p], "Branch")) { 
					DialogScript[i][c] = -3;
					DialogScriptO[i][c] = 0;
					c++;
					DialogScript[i][c] = DialogArgs[1];
					DialogScriptO[i][c] = 0;
					c++;
					continue;
				}

				if (!strcmp(DialogNames[p], "Check Dialog Group")) {
					//DialogArgs[0] /= 4;
				}

				DialogScript[i][c]=p;
				DialogScriptO[i][c]=o;
				c++;
				for(j=0;j<NumArgs;j++){
					DialogScript[i][c]=DialogArgs[j];
					c++;
				}





				j=0;
				for(k=0;k<32;k++){
					if(DialogBranches[k])j=k+1;
				}

				switch(DialogPatterns[p][DialogLength[p]-3]){
					case -21:
						if(DialogPatterns[p][DialogLength[p]-2]==0){
							to = DialogArgs[getDialogPatternArgs(p)-1];

							switch (to) {
								case 0x18074:
								case 0x1808A:
								case 0x180B4:

									break;
								default:
									if (to > o) {
										DialogBranches[j] = to;//+ftell(fp)-2;
										NumBranches++;
									} else
										to = to;
									break;
							}

						}
						break;
				}
				switch(DialogPatterns[p][DialogLength[p]-2]){
					case -21:
						if(DialogPatterns[p][DialogLength[p]-1]==-1){
							to = DialogArgs[getDialogPatternArgs(p)-1];

							switch (to) {
								case 0x18074:
								case 0x1808A:
								case 0x180B4:

									break;
								default:
									if (to > o || to == 0x18208) {
										DialogBranches[j] = to;//+ftell(fp)-2;
										NumBranches++;
									} else
										to = to;
									break;
							}

						}
						break;
				}
				if(DialogBranches[j])
				for(k=0;k<j;k++){
					if(DialogBranches[j]==DialogBranches[k]){
						DialogBranches[j]=0;
						NumBranches--;
						k=j;
					}
				}
			}
		}
		DialogScript[i][c]=-1;
		BuildDialogGraph(i);
	}
	o = ftell(fp);
	mo=mo;
	fclose(fp);
}
