#define ARG_IGNORE	-1
#define ARG_BYTE	0
#define ARG_WORD	1
#define ARG_LONG	2
#define ARG_BRANCH	3
#define ARG_MESSAGE	4
#define ARG_DIR		5
#define ARG_SBRANCH	6 //set clear instead of equal not equal
#define ARG_BANKED	7
#define ARG_YESNO	8
#define ARG_SPECIAL	9
#define ARG_REPEAT	10
#define ARG_ADDSUB	11
#define ARG_DIR2	12
#define ARG_ITEM	13
#define ARG_CHAR	14
#define ARG_JUMP	15
#define ARG_IGNBRA  16 //ignored branch, just for default value
#define ARG_VOICE	17
#define ARG_MOVEMENT 18

struct NodeType{
	int shape;
	char name[32];

	char label[4][32];

	int argline,argnum;
	int numargs;
	int argtypes[4];
	char arglabel[4][32];

	int numout;
	char outlabel[4][32];

	char helptext[1024];

	void set(char * n,int s,char * l, char * l2, char * l3, char * l4,int al, int an){
		sprintf(label[0],l);
		sprintf(label[1],l2);
		sprintf(label[2],l3);
		sprintf(label[3],l4);
		shape = s;
		sprintf(name,n);
		argline=al;
		argnum=an;

		numout = 1;
		sprintf(outlabel[0],"");

		setargs(0,ARG_IGNORE,"",ARG_IGNORE,"",ARG_IGNORE,"",ARG_IGNORE,"");
		setHelpText("");
	}

	void setout(int n, char * l, char * l2, char * l3, char * l4){
		numout = n;
		sprintf(outlabel[0],l);
		sprintf(outlabel[1],l2);
		sprintf(outlabel[2],l3);
		sprintf(outlabel[3],l4);
	}

	void setargs(int n, int t, char * l, int t2, char * l2, int t3, char * l3, int t4, char * l4){
		numargs = n;
		argtypes[0]=t;
		argtypes[1]=t2;
		argtypes[2]=t3;
		argtypes[3]=t4;
		sprintf(arglabel[0],l);
		sprintf(arglabel[1],l2);
		sprintf(arglabel[2],l3);
		sprintf(arglabel[3],l4);
	}

	void setHelpText(char * h){
		sprintf(helptext,h);
	}

};

//char nodeCategories[][32] = {"Message","Event"
//#define

NodeType nodeTypesDialog[512];
int NumDialogNodeTypes = 0;

NodeType nodeTypesBE[512];
int NumBENodeTypes = 0;

NodeType nodeTypesBExit[512];
int NumBExitNodeTypes = 0;

NodeType nodeTypesCS[512];
int NumCSNodeTypes = 0;

NodeType nodeTypesBS[512];
int NumBSNodeTypes = 0;

NodeType nodeTypesWC[512];
int NumWCNodeTypes = 0;