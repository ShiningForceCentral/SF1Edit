#define COMP_CONSTANT	0
#define COMP_DATAREG	1
#define COMP_ADDRREG	2
#define COMP_WIDEIND	3
#define COMP_LONGIND	4
#define COMP_WIDEDIR	5
#define COMP_LONGDIR	6
#define COMP_FUNCTION	7

char ScriptCategories[4][32] = { "Variables", "Sprite Properties","Animation Properties","Functions" };

struct ScriptComponent {
	char name[32];
	int type;
	int value;
	int category;

	ScriptComponent() {
		type = -1;
	}

	void set(char * n, int t, int v, int c){
		sprintf(name, n);
		type = t;
		value = v;
		category = c;
	}
};

ScriptComponent ScriptComponents[24];

void initScriptComponents() {
	ScriptComponents[0].set("Constant", COMP_CONSTANT, 0, 0);
	ScriptComponents[1].set("A", COMP_DATAREG, 0, 0);
	ScriptComponents[2].set("B", COMP_DATAREG, 1, 0);
	ScriptComponents[3].set("C", COMP_DATAREG, 2, 0);
	ScriptComponents[4].set("D", COMP_DATAREG, 3, 0);
	ScriptComponents[5].set("E", COMP_DATAREG, 4, 0);
	ScriptComponents[6].set("F", COMP_DATAREG, 5, 0);
	ScriptComponents[7].set("G", COMP_DATAREG, 6, 0);
	ScriptComponents[8].set("H", COMP_DATAREG, 7, 0);

	ScriptComponents[9].set("X", COMP_WIDEIND, 0, 1);
	ScriptComponents[10].set("Y", COMP_WIDEIND, 2, 1);
	ScriptComponents[11].set("Exists", COMP_WIDEIND, 4, 1);
	ScriptComponents[12].set("Frame", COMP_WIDEIND, 6, 1);
	ScriptComponents[13].set("Sprite #", COMP_CONSTANT, 1, 1);
	ScriptComponents[14].set("Prev Sprite", COMP_FUNCTION, 1, 1);
	ScriptComponents[15].set("Next Sprite", COMP_FUNCTION, 2, 1);

	ScriptComponents[16].set("From Enemy", COMP_CONSTANT, 2, 2);
	ScriptComponents[17].set("Level", COMP_CONSTANT, 3, 2);
	ScriptComponents[18].set("In Progress", COMP_CONSTANT, 4, 2);
	ScriptComponents[19].set("Finished", COMP_CONSTANT, 5, 2);
	ScriptComponents[20].set("Flicker Color", COMP_CONSTANT, 6, 2);
	ScriptComponents[21].set("Screen Shake", COMP_CONSTANT, 7, 2);

	ScriptComponents[22].set("Add Sprite", COMP_FUNCTION, 3, 3);


}
