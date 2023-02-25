#define AdvancedNodes(TYPE, N) \
add##TYPE##NodeType("Call Function", 4, "Call", "Function", "", "", 3, 0); \
set##TYPE##NodeArgs(1, ARG_LONG, "Function"); \
set##TYPE##NodeHelp("Calls the chosen offset as a function."); \
add##TYPE##NodeType("Get Random Number", 4, "Get", "Random", "Number", "", 3, 0); \
set##TYPE##NodeArgs(1, ARG_WORD, "Range"); \
set##TYPE##NodeHelp("Gets a random number from 0 to Range-1 in D7."); \
add##TYPE##NodeType("Set D0 Byte", 4, "Set", "D0", "Byte", "", 3, 0); \
set##TYPE##NodeArgs(1, ARG_BYTE, "Value"); \
add##TYPE##NodeType("Set D1 Byte", 4, "Set", "D1", "Byte", "", 3, 0); \
set##TYPE##NodeArgs(1, ARG_BYTE, "Value"); \
add##TYPE##NodeType("Set D2 Byte", 4, "Set", "D2", "Byte", "", 3, 0); \
set##TYPE##NodeArgs(1, ARG_BYTE, "Value"); \
add##TYPE##NodeType("Set D3 Byte", 4, "Set", "D3", "Byte", "", 3, 0); \
set##TYPE##NodeArgs(1, ARG_BYTE, "Value"); \
add##TYPE##NodeType("Set D4 Byte", 4, "Set", "D4", "Byte", "", 3, 0); \
set##TYPE##NodeArgs(1, ARG_BYTE, "Value"); \
add##TYPE##NodeType("Set D5 Byte", 4, "Set", "D5", "Byte", "", 3, 0); \
set##TYPE##NodeArgs(1, ARG_BYTE, "Value"); \
add##TYPE##NodeType("Set D6 Byte", 4, "Set", "D6", "Byte", "", 3, 0); \
set##TYPE##NodeArgs(1, ARG_BYTE, "Value"); \
add##TYPE##NodeType("Set D7 Byte", 4, "Set", "D7", "Byte", "", 3, 0); \
set##TYPE##NodeArgs(1, ARG_BYTE, "Value"); \
add##TYPE##NodeType("Set D0 Word", 4, "Set", "D0", "Word", "", 3, 0); \
set##TYPE##NodeArgs(1, ARG_WORD, "Value"); \
add##TYPE##NodeType("Set D1 Word", 4, "Set", "D1", "Word", "", 3, 0); \
set##TYPE##NodeArgs(1, ARG_WORD, "Value"); \
add##TYPE##NodeType("Set D2 Word", 4, "Set", "D2", "Word", "", 3, 0); \
set##TYPE##NodeArgs(1, ARG_WORD, "Value"); \
add##TYPE##NodeType("Set D3 Word", 4, "Set", "D3", "Word", "", 3, 0); \
set##TYPE##NodeArgs(1, ARG_WORD, "Value"); \
add##TYPE##NodeType("Set D4 Word", 4, "Set", "D4", "Word", "", 3, 0); \
set##TYPE##NodeArgs(1, ARG_WORD, "Value"); \
add##TYPE##NodeType("Set D5 Word", 4, "Set", "D5", "Word", "", 3, 0); \
set##TYPE##NodeArgs(1, ARG_WORD, "Value"); \
add##TYPE##NodeType("Set D6 Word", 4, "Set", "D6", "Word", "", 3, 0); \
set##TYPE##NodeArgs(1, ARG_WORD, "Value"); \
add##TYPE##NodeType("Set D7 Word", 4, "Set", "D7", "Word", "", 3, 0); \
set##TYPE##NodeArgs(1, ARG_WORD, "Value"); \
add##TYPE##NodeType("Copy to D0 Byte", 4, "Copy to", "D0", "Byte", "", 3, 0); \
set##TYPE##NodeArgs(1, ARG_BYTE, "From Reg D"); \
add##TYPE##NodeType("Copy to D1 Byte", 4, "Copy to", "D1", "Byte", "", 3, 0); \
set##TYPE##NodeArgs(1, ARG_BYTE, "From Reg D"); \
add##TYPE##NodeType("Copy to D2 Byte", 4, "Copy to", "D2", "Byte", "", 3, 0); \
set##TYPE##NodeArgs(1, ARG_BYTE, "From Reg D"); \
add##TYPE##NodeType("Copy to D3 Byte", 4, "Copy to", "D3", "Byte", "", 3, 0); \
set##TYPE##NodeArgs(1, ARG_BYTE, "From Reg D"); \
add##TYPE##NodeType("Copy to D4 Byte", 4, "Copy to", "D4", "Byte", "", 3, 0); \
set##TYPE##NodeArgs(1, ARG_BYTE, "From Reg D"); \
add##TYPE##NodeType("Copy to D5 Byte", 4, "Copy to", "D5", "Byte", "", 3, 0); \
set##TYPE##NodeArgs(1, ARG_BYTE, "From Reg D"); \
add##TYPE##NodeType("Copy to D6 Byte", 4, "Copy to", "D6", "Byte", "", 3, 0); \
set##TYPE##NodeArgs(1, ARG_BYTE, "From Reg D"); \
add##TYPE##NodeType("Copy to D7 Byte", 4, "Copy to", "D7", "Byte", "", 3, 0); \
set##TYPE##NodeArgs(1, ARG_BYTE, "From Reg D"); \
add##TYPE##NodeType("Copy to D0 Word", 4, "Copy to", "D0", "Word", "", 3, 0); \
set##TYPE##NodeArgs(1, ARG_WORD, "From Reg D"); \
add##TYPE##NodeType("Copy to D1 Word", 4, "Copy to", "D1", "Word", "", 3, 0); \
set##TYPE##NodeArgs(1, ARG_WORD, "From Reg D"); \
add##TYPE##NodeType("Copy to D2 Word", 4, "Copy to", "D2", "Word", "", 3, 0); \
set##TYPE##NodeArgs(1, ARG_WORD, "From Reg D"); \
add##TYPE##NodeType("Copy to D3 Word", 4, "Copy to", "D3", "Word", "", 3, 0); \
set##TYPE##NodeArgs(1, ARG_WORD, "From Reg D"); \
add##TYPE##NodeType("Copy to D4 Word", 4, "Copy to", "D4", "Word", "", 3, 0); \
set##TYPE##NodeArgs(1, ARG_WORD, "From Reg D"); \
add##TYPE##NodeType("Copy to D5 Word", 4, "Copy to", "D5", "Word", "", 3, 0); \
set##TYPE##NodeArgs(1, ARG_WORD, "From Reg D"); \
add##TYPE##NodeType("Copy to D6 Word", 4, "Copy to", "D6", "Word", "", 3, 0); \
set##TYPE##NodeArgs(1, ARG_WORD, "From Reg D"); \
add##TYPE##NodeType("Copy to D7 Word", 4, "Copy to", "D7", "Word", "", 3, 0); \
set##TYPE##NodeArgs(1, ARG_WORD, "From Reg D"); \
add##TYPE##NodeType("Add to D0 Byte", 4, "Add to", "D0", "Byte", "", 3, 0); \
set##TYPE##NodeArgs(1, ARG_BYTE, "From Reg D"); \
add##TYPE##NodeType("Add to D1 Byte", 4, "Add to", "D1", "Byte", "", 3, 0); \
set##TYPE##NodeArgs(1, ARG_BYTE, "From Reg D"); \
add##TYPE##NodeType("Add to D2 Byte", 4, "Add to", "D2", "Byte", "", 3, 0); \
set##TYPE##NodeArgs(1, ARG_BYTE, "From Reg D"); \
add##TYPE##NodeType("Add to D3 Byte", 4, "Add to", "D3", "Byte", "", 3, 0); \
set##TYPE##NodeArgs(1, ARG_BYTE, "From Reg D"); \
add##TYPE##NodeType("Add to D4 Byte", 4, "Add to", "D4", "Byte", "", 3, 0); \
set##TYPE##NodeArgs(1, ARG_BYTE, "From Reg D"); \
add##TYPE##NodeType("Add to D5 Byte", 4, "Add to", "D5", "Byte", "", 3, 0); \
set##TYPE##NodeArgs(1, ARG_BYTE, "From Reg D"); \
add##TYPE##NodeType("Add to D6 Byte", 4, "Add to", "D6", "Byte", "", 3, 0); \
set##TYPE##NodeArgs(1, ARG_BYTE, "From Reg D"); \
add##TYPE##NodeType("Add to D7 Byte", 4, "Add to", "D7", "Byte", "", 3, 0); \
set##TYPE##NodeArgs(1, ARG_BYTE, "From Reg D"); \
add##TYPE##NodeType("Add D0 to D0 Word", 4, "Add D0", "to D0", "Word", ""); \
add##TYPE##NodeType("Add D1 to D0 Word", 4, "Add D1", "to D0", "Word", ""); \
add##TYPE##NodeType("Add D2 to D0 Word", 4, "Add D2", "to D0", "Word", ""); \
add##TYPE##NodeType("Add D3 to D0 Word", 4, "Add D3", "to D0", "Word", ""); \
add##TYPE##NodeType("Add D4 to D0 Word", 4, "Add D4", "to D0", "Word", ""); \
add##TYPE##NodeType("Add D5 to D0 Word", 4, "Add D5", "to D0", "Word", ""); \
add##TYPE##NodeType("Add D6 to D0 Word", 4, "Add D6", "to D0", "Word", ""); \
add##TYPE##NodeType("Add D7 to D0 Word", 4, "Add D7", "to D0", "Word", ""); \
add##TYPE##NodeType("Add # To D0 Word", 4, "Add #","To D0", "Word", "", 3, 0); \
set##TYPE##NodeArgs(1, ARG_WORD, "From Reg D"); \
add##TYPE##NodeType("Add # To D1 Word", 4, "Add #","To D1", "Word", "", 3, 0); \
set##TYPE##NodeArgs(1, ARG_WORD, "From Reg D"); \
add##TYPE##NodeType("Add # To D2 Word", 4, "Add #","To D2", "Word", "", 3, 0); \
set##TYPE##NodeArgs(1, ARG_WORD, "From Reg D"); \
add##TYPE##NodeType("Add # To D3 Word", 4, "Add #","To D3", "Word", "", 3, 0); \
set##TYPE##NodeArgs(1, ARG_WORD, "From Reg D"); \
add##TYPE##NodeType("Add # To D4 Word", 4, "Add #","To D4", "Word", "", 3, 0); \
set##TYPE##NodeArgs(1, ARG_WORD, "From Reg D"); \
add##TYPE##NodeType("Add # To D5 Word", 4, "Add #","To D5", "Word", "", 3, 0); \
set##TYPE##NodeArgs(1, ARG_WORD, "From Reg D"); \
add##TYPE##NodeType("Add # To D6 Word", 4, "Add #","To D6", "Word", "", 3, 0); \
set##TYPE##NodeArgs(1, ARG_WORD, "From Reg D"); \
add##TYPE##NodeType("Add # To D7 Word", 4, "Add #","To D7", "Word", "", 3, 0); \
set##TYPE##NodeArgs(1, ARG_WORD, "From Reg D"); \
add##TYPE##NodeType("Negate D0 Word", 4, "Negate", "D0", "Word", ""); \
add##TYPE##NodeType("Negate D1 Word", 4, "Negate", "D1", "Word", ""); \
add##TYPE##NodeType("Negate D2 Word", 4, "Negate", "D2", "Word", ""); \
add##TYPE##NodeType("Negate D3 Word", 4, "Negate", "D3", "Word", ""); \
add##TYPE##NodeType("Negate D4 Word", 4, "Negate", "D4", "Word", ""); \
add##TYPE##NodeType("Negate D5 Word", 4, "Negate", "D5", "Word", ""); \
add##TYPE##NodeType("Negate D6 Word", 4, "Negate", "D6", "Word", ""); \
add##TYPE##NodeType("Negate D7 Word", 4, "Negate", "D7", "Word", ""); \
add##TYPE##NodeType("Backup D0", 4, "Backup", "D0", "", ""); \
add##TYPE##NodeType("Backup D1", 4, "Backup", "D1", "", ""); \
add##TYPE##NodeType("Backup D2", 4, "Backup", "D2", "", ""); \
add##TYPE##NodeType("Backup D3", 4, "Backup", "D3", "", ""); \
add##TYPE##NodeType("Backup D4", 4, "Backup", "D4", "", ""); \
add##TYPE##NodeType("Backup D5", 4, "Backup", "D5", "", ""); \
add##TYPE##NodeType("Backup D6", 4, "Backup", "D6", "", ""); \
add##TYPE##NodeType("Backup D7", 4, "Backup", "D7", "", ""); \
add##TYPE##NodeType("Restore D0", 4, "Restore", "D0", "", ""); \
add##TYPE##NodeType("Restore D1", 4, "Restore", "D1", "", ""); \
add##TYPE##NodeType("Restore D2", 4, "Restore", "D2", "", ""); \
add##TYPE##NodeType("Restore D3", 4, "Restore", "D3", "", ""); \
add##TYPE##NodeType("Restore D4", 4, "Restore", "D4", "", ""); \
add##TYPE##NodeType("Restore D5", 4, "Restore", "D5", "", ""); \
add##TYPE##NodeType("Restore D6", 4, "Restore", "D6", "", ""); \
add##TYPE##NodeType("Restore D7", 4, "Restore", "D7", "", ""); \
add##TYPE##NodeType("Compare D0 to # Byte", 4, "Compare", "D0 to #", "Byte", "", 3, 0); \
set##TYPE##NodeArgs(1, ARG_BYTE, "Value"); \
add##TYPE##NodeType("Compare D1 to # Byte", 4, "Compare", "D1 to #", "Byte", "", 3, 0); \
set##TYPE##NodeArgs(1, ARG_BYTE, "Value"); \
add##TYPE##NodeType("Compare D2 to # Byte", 4, "Compare", "D2 to #", "Byte", "", 3, 0); \
set##TYPE##NodeArgs(1, ARG_BYTE, "Value"); \
add##TYPE##NodeType("Compare D3 to # Byte", 4, "Compare", "D3 to #", "Byte", "", 3, 0); \
set##TYPE##NodeArgs(1, ARG_BYTE, "Value"); \
add##TYPE##NodeType("Compare D4 to # Byte", 4, "Compare", "D4 to #", "Byte", "", 3, 0); \
set##TYPE##NodeArgs(1, ARG_BYTE, "Value"); \
add##TYPE##NodeType("Compare D5 to # Byte", 4, "Compare", "D5 to #", "Byte", "", 3, 0); \
set##TYPE##NodeArgs(1, ARG_BYTE, "Value"); \
add##TYPE##NodeType("Compare D6 to # Byte", 4, "Compare", "D6 to #", "Byte", "", 3, 0); \
set##TYPE##NodeArgs(1, ARG_BYTE, "Value"); \
add##TYPE##NodeType("Compare D7 to # Byte", 4, "Compare", "D7 to #", "Byte", "", 3, 0); \
set##TYPE##NodeArgs(1, ARG_BYTE, "Value"); \
add##TYPE##NodeType("Compare to D0 Byte", 4, "Compare", "to D0", "Byte", "", 3, 0); \
set##TYPE##NodeArgs(1, ARG_BYTE, "From Reg D"); \
add##TYPE##NodeType("Compare to D1 Byte", 4, "Compare", "to D1", "Byte", "", 3, 0); \
set##TYPE##NodeArgs(1, ARG_BYTE, "From Reg D"); \
add##TYPE##NodeType("Compare to D2 Byte", 4, "Compare", "to D2", "Byte", "", 3, 0); \
set##TYPE##NodeArgs(1, ARG_BYTE, "From Reg D"); \
add##TYPE##NodeType("Compare to D3 Byte", 4, "Compare", "to D3", "Byte", "", 3, 0); \
set##TYPE##NodeArgs(1, ARG_BYTE, "From Reg D"); \
add##TYPE##NodeType("Compare to D4 Byte", 4, "Compare", "to D4", "Byte", "", 3, 0); \
set##TYPE##NodeArgs(1, ARG_BYTE, "From Reg D"); \
add##TYPE##NodeType("Compare to D5 Byte", 4, "Compare", "to D5", "Byte", "", 3, 0); \
set##TYPE##NodeArgs(1, ARG_BYTE, "From Reg D"); \
add##TYPE##NodeType("Compare to D6 Byte", 4, "Compare", "to D6", "Byte", "", 3, 0); \
set##TYPE##NodeArgs(1, ARG_BYTE, "From Reg D"); \
add##TYPE##NodeType("Compare to D7 Byte", 4, "Compare", "to D7", "Byte", "", 3, 0); \
set##TYPE##NodeArgs(1, ARG_BYTE, "From Reg D"); \
add##TYPE##NodeType("Load Address to A0", 4, "Load", "Address", "To A0", "", 3, 0); \
set##TYPE##NodeArgs(1, ARG_LONG, "Offset"); \
add##TYPE##NodeType("Load Address to A1", 4, "Load", "Address", "To A1", "", 3, 0); \
set##TYPE##NodeArgs(1, ARG_LONG, "Offset"); \
add##TYPE##NodeType("Load Ram To D0 Byte", 4, "Load", "To D0", "Byte", "", 3, 0); \
set##TYPE##NodeArgs(1, ARG_WORD, "Address"); \
add##TYPE##NodeType("Load Ram To D1 Byte", 4, "Load","To D1", "Byte", "", 3, 0); \
set##TYPE##NodeArgs(1, ARG_WORD, "Address"); \
add##TYPE##NodeType("Load Ram To D2 Byte", 4, "Load","To D2", "Byte", "", 3, 0); \
set##TYPE##NodeArgs(1, ARG_WORD, "Address"); \
add##TYPE##NodeType("Load Ram To D3 Byte", 4, "Load","To D3", "Byte", "", 3, 0); \
set##TYPE##NodeArgs(1, ARG_WORD, "Address"); \
add##TYPE##NodeType("Load Ram To D4 Byte", 4, "Load","To D4", "Byte", "", 3, 0); \
set##TYPE##NodeArgs(1, ARG_WORD, "Address"); \
add##TYPE##NodeType("Load Ram To D5 Byte", 4, "Load","To D5", "Byte", "", 3, 0); \
set##TYPE##NodeArgs(1, ARG_WORD, "Address"); \
add##TYPE##NodeType("Load Ram To D6 Byte", 4, "Load","To D6", "Byte", "", 3, 0); \
set##TYPE##NodeArgs(1, ARG_WORD, "Address"); \
add##TYPE##NodeType("Load Ram To D7 Byte", 4, "Load","To D7", "Byte", "", 3, 0); \
set##TYPE##NodeArgs(1, ARG_WORD, "Address"); \
add##TYPE##NodeType("Load Ram To D0 Word", 4, "Load", "To D0", "Word", "", 3, 0); \
set##TYPE##NodeArgs(1, ARG_WORD, "Address"); \
add##TYPE##NodeType("Load Ram To D1 Word", 4, "Load","To D1", "Word", "", 3, 0); \
set##TYPE##NodeArgs(1, ARG_WORD, "Address"); \
add##TYPE##NodeType("Load Ram To D2 Word", 4, "Load","To D2", "Word", "", 3, 0); \
set##TYPE##NodeArgs(1, ARG_WORD, "Address"); \
add##TYPE##NodeType("Load Ram To D3 Word", 4, "Load","To D3", "Word", "", 3, 0); \
set##TYPE##NodeArgs(1, ARG_WORD, "Address"); \
add##TYPE##NodeType("Load Ram To D4 Word", 4, "Load","To D4", "Word", "", 3, 0); \
set##TYPE##NodeArgs(1, ARG_WORD, "Address"); \
add##TYPE##NodeType("Load Ram To D5 Word", 4, "Load","To D5", "Word", "", 3, 0); \
set##TYPE##NodeArgs(1, ARG_WORD, "Address"); \
add##TYPE##NodeType("Load Ram To D6 Word", 4, "Load","To D6", "Word", "", 3, 0); \
set##TYPE##NodeArgs(1, ARG_WORD, "Address"); \
add##TYPE##NodeType("Load Ram To D7 Word", 4, "Load","To D7", "Word", "", 3, 0); \
set##TYPE##NodeArgs(1, ARG_WORD, "Address"); \
add##TYPE##NodeType("Save Ram From D0 Byte", 4, "Save", "From D0", "Byte", "", 3, 0); \
set##TYPE##NodeArgs(1, ARG_WORD, "Address"); \
add##TYPE##NodeType("Save Ram From D1 Byte", 4, "Save","From D1", "Byte", "", 3, 0); \
set##TYPE##NodeArgs(1, ARG_WORD, "Address"); \
add##TYPE##NodeType("Save Ram From D2 Byte", 4, "Save","From D2", "Byte", "", 3, 0); \
set##TYPE##NodeArgs(1, ARG_WORD, "Address"); \
add##TYPE##NodeType("Save Ram From D3 Byte", 4, "Save","From D3", "Byte", "", 3, 0); \
set##TYPE##NodeArgs(1, ARG_WORD, "Address"); \
add##TYPE##NodeType("Save Ram From D4 Byte", 4, "Save","From D4", "Byte", "", 3, 0); \
set##TYPE##NodeArgs(1, ARG_WORD, "Address"); \
add##TYPE##NodeType("Save Ram From D5 Byte", 4, "Save","From D5", "Byte", "", 3, 0); \
set##TYPE##NodeArgs(1, ARG_WORD, "Address"); \
add##TYPE##NodeType("Save Ram From D6 Byte", 4, "Save","From D6", "Byte", "", 3, 0); \
set##TYPE##NodeArgs(1, ARG_WORD, "Address"); \
add##TYPE##NodeType("Save Ram From D7 Byte", 4, "Save","From D7", "Byte", "", 3, 0); \
set##TYPE##NodeArgs(1, ARG_WORD, "Address"); \
add##TYPE##NodeType("Save Ram From D0 Word", 4, "Save", "From D0", "Word", "", 3, 0); \
set##TYPE##NodeArgs(1, ARG_WORD, "Address"); \
add##TYPE##NodeType("Save Ram From D1 Word", 4, "Save","From D1", "Word", "", 3, 0); \
set##TYPE##NodeArgs(1, ARG_WORD, "Address"); \
add##TYPE##NodeType("Save Ram From D2 Word", 4, "Save","From D2", "Word", "", 3, 0); \
set##TYPE##NodeArgs(1, ARG_WORD, "Address"); \
add##TYPE##NodeType("Save Ram From D3 Word", 4, "Save","From D3", "Word", "", 3, 0); \
set##TYPE##NodeArgs(1, ARG_WORD, "Address"); \
add##TYPE##NodeType("Save Ram From D4 Word", 4, "Save","From D4", "Word", "", 3, 0); \
set##TYPE##NodeArgs(1, ARG_WORD, "Address"); \
add##TYPE##NodeType("Save Ram From D5 Word", 4, "Save","From D5", "Word", "", 3, 0); \
set##TYPE##NodeArgs(1, ARG_WORD, "Address"); \
add##TYPE##NodeType("Save Ram From D6 Word", 4, "Save","From D6", "Word", "", 3, 0); \
set##TYPE##NodeArgs(1, ARG_WORD, "Address"); \
add##TYPE##NodeType("Save Ram From D7 Word", 4, "Save","From D7", "Word", "", 3, 0); \
set##TYPE##NodeArgs(1, ARG_WORD, "Address"); \
add##TYPE##NodeType("Read A0 To D0 Byte", 4, "Read A0", "To D0", "Byte", ""); \
add##TYPE##NodeType("Read A0 To D0 Word", 4, "Read A0", "To D0", "Word", ""); \
add##TYPE##NodeType("Write D0 To A0 Byte", 4, "Write D0", "To A0", "Byte", ""); \
add##TYPE##NodeType("Write D0 To A0 Word", 4, "Write D0", "To A0", "Word", ""); \
add##TYPE##NodeType("Read A1 To D0 Byte", 4, "Read A1", "To D0", "Byte", ""); \
add##TYPE##NodeType("Read A1 To D0 Word", 4, "Read A1", "To D0", "Word", ""); \
add##TYPE##NodeType("Write D0 To A1 Byte", 4, "Write D0", "To A1", "Byte", ""); \
add##TYPE##NodeType("Write D0 To A1 Word", 4, "Write D0", "To A1", "Word", ""); \
add##TYPE##NodeType("Branch If Equal", 4, "Branch", "If Equal", "", ""); \
set##TYPE##NodeArgs(2, ARG_IGNBRA, "", ARG_IGNORE, ""); \
set##TYPE##NodeOuts(2, "Equal", "Not Equal"); \
add##TYPE##NodeType("Branch If Greater", 4, "Branch", "If Greater", "", ""); \
set##TYPE##NodeArgs(2, ARG_IGNBRA, "", ARG_IGNORE, ""); \
set##TYPE##NodeOuts(2, "Greater", "Not Greater"); \
add##TYPE##NodeType("Branch If Less", 4, "Branch", "If Less", "", ""); \
set##TYPE##NodeArgs(2, ARG_IGNBRA, "", ARG_IGNORE, ""); \
set##TYPE##NodeOuts(2, "Less", "Not Less"); \
add##TYPE##Pattern(5, N, "Call Function", 0x4E, 0x71, 0x4E, 0xB9, -4); \
add##TYPE##Pattern(15,N + 1  , "Get Random Number", 0x4E, 0x71, 0x2F, 0x06, 0x3C, 0x3C, -2, 0x4E, 0xB9, 0, 0, 0x02, 0xE0, 0x2C, 0x1F); \
add##TYPE##Pattern(4, N + 2  , "Set D0 Byte", 0x4E, 0x71, 0x70, -1); \
add##TYPE##Pattern(4, N + 3  , "Set D1 Byte", 0x4E, 0x71, 0x72, -1); \
add##TYPE##Pattern(4, N + 4  , "Set D2 Byte", 0x4E, 0x71, 0x74, -1); \
add##TYPE##Pattern(4, N + 5  , "Set D3 Byte", 0x4E, 0x71, 0x76, -1); \
add##TYPE##Pattern(4, N + 6  , "Set D4 Byte", 0x4E, 0x71, 0x78, -1); \
add##TYPE##Pattern(4, N + 7  , "Set D5 Byte", 0x4E, 0x71, 0x7A, -1); \
add##TYPE##Pattern(4, N + 8  , "Set D6 Byte", 0x4E, 0x71, 0x7C, -1); \
add##TYPE##Pattern(4, N + 9  , "Set D7 Byte", 0x4E, 0x71, 0x7E, -1); \
add##TYPE##Pattern(5, N + 10 , "Set D0 Word", 0x4E, 0x71, 0x30, 0x3C, -2); \
add##TYPE##Pattern(5, N + 11 , "Set D1 Word", 0x4E, 0x71, 0x32, 0x3C, -2); \
add##TYPE##Pattern(5, N + 12 , "Set D2 Word", 0x4E, 0x71, 0x34, 0x3C, -2); \
add##TYPE##Pattern(5, N + 13 , "Set D3 Word", 0x4E, 0x71, 0x36, 0x3C, -2); \
add##TYPE##Pattern(5, N + 14 , "Set D4 Word", 0x4E, 0x71, 0x38, 0x3C, -2); \
add##TYPE##Pattern(5, N + 15 , "Set D5 Word", 0x4E, 0x71, 0x3A, 0x3C, -2); \
add##TYPE##Pattern(5, N + 16 , "Set D6 Word", 0x4E, 0x71, 0x3C, 0x3C, -2); \
add##TYPE##Pattern(5, N + 17 , "Set D7 Word", 0x4E, 0x71, 0x3E, 0x3C, -2); \
add##TYPE##Pattern(4, N + 18 , "Copy to D0 Byte", 0x4E, 0x71, 0x10, -1); \
add##TYPE##Pattern(4, N + 19 , "Copy to D1 Byte", 0x4E, 0x71, 0x12, -1); \
add##TYPE##Pattern(4, N + 20 , "Copy to D2 Byte", 0x4E, 0x71, 0x14, -1); \
add##TYPE##Pattern(4, N + 21 , "Copy to D3 Byte", 0x4E, 0x71, 0x16, -1); \
add##TYPE##Pattern(4, N + 22 , "Copy to D4 Byte", 0x4E, 0x71, 0x18, -1); \
add##TYPE##Pattern(4, N + 23 , "Copy to D5 Byte", 0x4E, 0x71, 0x1A, -1); \
add##TYPE##Pattern(4, N + 24 , "Copy to D6 Byte", 0x4E, 0x71, 0x1C, -1); \
add##TYPE##Pattern(4, N + 25 , "Copy to D7 Byte", 0x4E, 0x71, 0x1E, -1); \
add##TYPE##Pattern(4, N + 26 , "Copy to D0 Word", 0x4E, 0x71, 0x30, -1); \
add##TYPE##Pattern(4, N + 27 , "Copy to D1 Word", 0x4E, 0x71, 0x32, -1); \
add##TYPE##Pattern(4, N + 28 , "Copy to D2 Word", 0x4E, 0x71, 0x34, -1); \
add##TYPE##Pattern(4, N + 29 , "Copy to D3 Word", 0x4E, 0x71, 0x36, -1); \
add##TYPE##Pattern(4, N + 30 , "Copy to D4 Word", 0x4E, 0x71, 0x38, -1); \
add##TYPE##Pattern(4, N + 31 , "Copy to D5 Word", 0x4E, 0x71, 0x3A, -1); \
add##TYPE##Pattern(4, N + 32 , "Copy to D6 Word", 0x4E, 0x71, 0x3C, -1); \
add##TYPE##Pattern(4, N + 33 , "Copy to D7 Word", 0x4E, 0x71, 0x3E, -1); \
add##TYPE##Pattern(4, N + 34 , "Add to D0 Byte", 0x4E, 0x71, 0xD0, -1); \
add##TYPE##Pattern(4, N + 35 , "Add to D1 Byte", 0x4E, 0x71, 0xD2, -1); \
add##TYPE##Pattern(4, N + 36 , "Add to D2 Byte", 0x4E, 0x71, 0xD4, -1); \
add##TYPE##Pattern(4, N + 37 , "Add to D3 Byte", 0x4E, 0x71, 0xD6, -1); \
add##TYPE##Pattern(4, N + 38 , "Add to D4 Byte", 0x4E, 0x71, 0xD8, -1); \
add##TYPE##Pattern(4, N + 39 , "Add to D5 Byte", 0x4E, 0x71, 0xDA, -1); \
add##TYPE##Pattern(4, N + 40 , "Add to D6 Byte", 0x4E, 0x71, 0xDC, -1); \
add##TYPE##Pattern(4, N + 41 , "Add to D7 Byte", 0x4E, 0x71, 0xDE, -1); \
add##TYPE##Pattern(4, N + 42 , "Add D0 to D0 Word", 0x4E, 0x71, 0xD0, 0x40); \
add##TYPE##Pattern(4, N + 43 , "Add D1 to D0 Word", 0x4E, 0x71, 0xD0, 0x41); \
add##TYPE##Pattern(4, N + 44 , "Add D2 to D0 Word", 0x4E, 0x71, 0xD0, 0x42); \
add##TYPE##Pattern(4, N + 45 , "Add D3 to D0 Word", 0x4E, 0x71, 0xD0, 0x43); \
add##TYPE##Pattern(4, N + 46 , "Add D4 to D0 Word", 0x4E, 0x71, 0xD0, 0x44); \
add##TYPE##Pattern(4, N + 47 , "Add D5 to D0 Word", 0x4E, 0x71, 0xD0, 0x45); \
add##TYPE##Pattern(4, N + 48 , "Add D6 to D0 Word", 0x4E, 0x71, 0xD0, 0x46); \
add##TYPE##Pattern(4, N + 49 , "Add D7 to D0 Word", 0x4E, 0x71, 0xD0, 0x47); \
add##TYPE##Pattern(5, N + 50 , "Add # to D0 Word", 0x4E, 0x71, 0x06, 0x40, -2); \
add##TYPE##Pattern(5, N + 51 , "Add # to D1 Word", 0x4E, 0x71, 0x06, 0x41, -2); \
add##TYPE##Pattern(5, N + 52 , "Add # to D2 Word", 0x4E, 0x71, 0x06, 0x42, -2); \
add##TYPE##Pattern(5, N + 53 , "Add # to D3 Word", 0x4E, 0x71, 0x06, 0x43, -2); \
add##TYPE##Pattern(5, N + 54 , "Add # to D4 Word", 0x4E, 0x71, 0x06, 0x44, -2); \
add##TYPE##Pattern(5, N + 55 , "Add # to D5 Word", 0x4E, 0x71, 0x06, 0x45, -2); \
add##TYPE##Pattern(5, N + 56 , "Add # to D6 Word", 0x4E, 0x71, 0x06, 0x46, -2); \
add##TYPE##Pattern(5, N + 57 , "Add # to D7 Word", 0x4E, 0x71, 0x06, 0x47, -2); \
add##TYPE##Pattern(4, N + 58 , "Negate D0", 0x4E, 0x71, 0x44, 0x40); \
add##TYPE##Pattern(4, N + 59 , "Negate D1", 0x4E, 0x71, 0x44, 0x41); \
add##TYPE##Pattern(4, N + 60 , "Negate D2", 0x4E, 0x71, 0x44, 0x42); \
add##TYPE##Pattern(4, N + 61 , "Negate D3", 0x4E, 0x71, 0x44, 0x43); \
add##TYPE##Pattern(4, N + 62 , "Negate D4", 0x4E, 0x71, 0x44, 0x44); \
add##TYPE##Pattern(4, N + 63 , "Negate D5", 0x4E, 0x71, 0x44, 0x45); \
add##TYPE##Pattern(4, N + 64 , "Negate D6", 0x4E, 0x71, 0x44, 0x46); \
add##TYPE##Pattern(4, N + 65 , "Negate D7", 0x4E, 0x71, 0x44, 0x47); \
add##TYPE##Pattern(4, N + 66 , "Backup D0", 0x4E, 0x71, 0x2F, 0x00); \
add##TYPE##Pattern(4, N + 67 , "Backup D1", 0x4E, 0x71, 0x2F, 0x01); \
add##TYPE##Pattern(4, N + 68 , "Backup D2", 0x4E, 0x71, 0x2F, 0x02); \
add##TYPE##Pattern(4, N + 69 , "Backup D3", 0x4E, 0x71, 0x2F, 0x03); \
add##TYPE##Pattern(4, N + 70 , "Backup D4", 0x4E, 0x71, 0x2F, 0x04); \
add##TYPE##Pattern(4, N + 71 , "Backup D5", 0x4E, 0x71, 0x2F, 0x05); \
add##TYPE##Pattern(4, N + 72 , "Backup D6", 0x4E, 0x71, 0x2F, 0x06); \
add##TYPE##Pattern(4, N + 73 , "Backup D7", 0x4E, 0x71, 0x2F, 0x07); \
add##TYPE##Pattern(4, N + 74 , "Restore D0", 0x4E, 0x71, 0x20, 0x1F); \
add##TYPE##Pattern(4, N + 75 , "Restore D1", 0x4E, 0x71, 0x22, 0x1F); \
add##TYPE##Pattern(4, N + 76 , "Restore D2", 0x4E, 0x71, 0x24, 0x1F); \
add##TYPE##Pattern(4, N + 77 , "Restore D3", 0x4E, 0x71, 0x28, 0x1F); \
add##TYPE##Pattern(4, N + 78 , "Restore D4", 0x4E, 0x71, 0x26, 0x1F); \
add##TYPE##Pattern(4, N + 79 , "Restore D5", 0x4E, 0x71, 0x2A, 0x1F); \
add##TYPE##Pattern(4, N + 80 , "Restore D6", 0x4E, 0x71, 0x2C, 0x1F); \
add##TYPE##Pattern(4, N + 81 , "Restore D7", 0x4E, 0x71, 0x2E, 0x1F); \
add##TYPE##Pattern(6, N + 82 , "Compare D0 to # Byte", 0x4E, 0x71, 0x0C, 0x00, 0, -1); \
add##TYPE##Pattern(6, N + 83 , "Compare D1 to # Byte", 0x4E, 0x71, 0x0C, 0x01, 0, -1); \
add##TYPE##Pattern(6, N + 84 , "Compare D2 to # Byte", 0x4E, 0x71, 0x0C, 0x02, 0, -1); \
add##TYPE##Pattern(6, N + 85 , "Compare D3 to # Byte", 0x4E, 0x71, 0x0C, 0x03, 0, -1); \
add##TYPE##Pattern(6, N + 86 , "Compare D4 to # Byte", 0x4E, 0x71, 0x0C, 0x04, 0, -1); \
add##TYPE##Pattern(6, N + 87 , "Compare D5 to # Byte", 0x4E, 0x71, 0x0C, 0x05, 0, -1); \
add##TYPE##Pattern(6, N + 88 , "Compare D6 to # Byte", 0x4E, 0x71, 0x0C, 0x06, 0, -1); \
add##TYPE##Pattern(6, N + 89 , "Compare D7 to # Byte", 0x4E, 0x71, 0x0C, 0x07, 0, -1); \
add##TYPE##Pattern(4, N + 90 , "Compare to D0 Byte", 0x4E, 0x71, 0xB0, -1); \
add##TYPE##Pattern(4, N + 91 , "Compare to D1 Byte", 0x4E, 0x71, 0xB2, -1); \
add##TYPE##Pattern(4, N + 92 , "Compare to D2 Byte", 0x4E, 0x71, 0xB4, -1); \
add##TYPE##Pattern(4, N + 93 , "Compare to D3 Byte", 0x4E, 0x71, 0xB6, -1); \
add##TYPE##Pattern(4, N + 94 , "Compare to D4 Byte", 0x4E, 0x71, 0xB8, -1); \
add##TYPE##Pattern(4, N + 95 , "Compare to D5 Byte", 0x4E, 0x71, 0xBA, -1); \
add##TYPE##Pattern(4, N + 96 , "Compare to D6 Byte", 0x4E, 0x71, 0xBC, -1); \
add##TYPE##Pattern(4, N + 97 , "Compare to D7 Byte", 0x4E, 0x71, 0xBE, -1); \
add##TYPE##Pattern(5, N + 98 , "Load Address to A0", 0x4E, 0x71, 0x41, 0xF9, -4); \
add##TYPE##Pattern(5, N + 99 , "Load Address to A1", 0x4E, 0x71, 0x43, 0xF9, -4);\
add##TYPE##Pattern(5, N + 100 , "Load Ram to D0 Byte", 0x4E, 0x71, 0x10, 0x38, -2); \
add##TYPE##Pattern(5, N + 101 , "Load Ram to D1 Byte", 0x4E, 0x71, 0x12, 0x38, -2); \
add##TYPE##Pattern(5, N + 102 , "Load Ram to D2 Byte", 0x4E, 0x71, 0x14, 0x38, -2); \
add##TYPE##Pattern(5, N + 103 , "Load Ram to D3 Byte", 0x4E, 0x71, 0x16, 0x38, -2); \
add##TYPE##Pattern(5, N + 104 , "Load Ram to D4 Byte", 0x4E, 0x71, 0x18, 0x38, -2); \
add##TYPE##Pattern(5, N + 105 , "Load Ram to D5 Byte", 0x4E, 0x71, 0x1A, 0x38, -2); \
add##TYPE##Pattern(5, N + 106 , "Load Ram to D6 Byte", 0x4E, 0x71, 0x1C, 0x38, -2); \
add##TYPE##Pattern(5, N + 107 , "Load Ram to D7 Byte", 0x4E, 0x71, 0x1E, 0x38, -2); \
add##TYPE##Pattern(5, N + 108, "Load Ram to D0 Word", 0x4E, 0x71, 0x30, 0x38, -2); \
add##TYPE##Pattern(5, N + 109, "Load Ram to D1 Word", 0x4E, 0x71, 0x32, 0x38, -2); \
add##TYPE##Pattern(5, N + 110, "Load Ram to D2 Word", 0x4E, 0x71, 0x34, 0x38, -2); \
add##TYPE##Pattern(5, N + 111, "Load Ram to D3 Word", 0x4E, 0x71, 0x36, 0x38, -2); \
add##TYPE##Pattern(5, N + 112, "Load Ram to D4 Word", 0x4E, 0x71, 0x38, 0x38, -2); \
add##TYPE##Pattern(5, N + 113, "Load Ram to D5 Word", 0x4E, 0x71, 0x3A, 0x38, -2); \
add##TYPE##Pattern(5, N + 114, "Load Ram to D6 Word", 0x4E, 0x71, 0x3C, 0x38, -2); \
add##TYPE##Pattern(5, N + 115, "Load Ram to D7 Word", 0x4E, 0x71, 0x3E, 0x38, -2); \
add##TYPE##Pattern(5, N + 116, "Save Ram From D0 Byte", 0x4E, 0x71, 0x11, 0xC0, -2); \
add##TYPE##Pattern(5, N + 117, "Save Ram From D1 Byte", 0x4E, 0x71, 0x11, 0xC1, -2); \
add##TYPE##Pattern(5, N + 118, "Save Ram From D2 Byte", 0x4E, 0x71, 0x11, 0xC2, -2); \
add##TYPE##Pattern(5, N + 119, "Save Ram From D3 Byte", 0x4E, 0x71, 0x11, 0xC3, -2); \
add##TYPE##Pattern(5, N + 120, "Save Ram From D4 Byte", 0x4E, 0x71, 0x11, 0xC4, -2); \
add##TYPE##Pattern(5, N + 121, "Save Ram From D5 Byte", 0x4E, 0x71, 0x11, 0xC5, -2); \
add##TYPE##Pattern(5, N + 122, "Save Ram From D6 Byte", 0x4E, 0x71, 0x11, 0xC6, -2); \
add##TYPE##Pattern(5, N + 123, "Save Ram From D7 Byte", 0x4E, 0x71, 0x11, 0xC7, -2); \
add##TYPE##Pattern(5, N + 124, "Save Ram From D0 Word", 0x4E, 0x71, 0x31, 0xC0, -2); \
add##TYPE##Pattern(5, N + 125, "Save Ram From D1 Word", 0x4E, 0x71, 0x31, 0xC1, -2); \
add##TYPE##Pattern(5, N + 126, "Save Ram From D2 Word", 0x4E, 0x71, 0x31, 0xC2, -2); \
add##TYPE##Pattern(5, N + 127, "Save Ram From D3 Word", 0x4E, 0x71, 0x31, 0xC3, -2); \
add##TYPE##Pattern(5, N + 128, "Save Ram From D4 Word", 0x4E, 0x71, 0x31, 0xC4, -2); \
add##TYPE##Pattern(5, N + 129, "Save Ram From D5 Word", 0x4E, 0x71, 0x31, 0xC5, -2); \
add##TYPE##Pattern(5, N + 130, "Save Ram From D6 Word", 0x4E, 0x71, 0x31, 0xC6, -2); \
add##TYPE##Pattern(5, N + 131, "Save Ram From D7 Word", 0x4E, 0x71, 0x31, 0xC7, -2); \
add##TYPE##Pattern(4, N + 132, "Read A0 to D0 Byte",  0x4E, 0x71, 0x10, 0x18); \
add##TYPE##Pattern(4, N + 133, "Read A0 to D0 Word",  0x4E, 0x71, 0x30, 0x18); \
add##TYPE##Pattern(4, N + 134, "Write D0 to A0 Byte", 0x4E, 0x71, 0x10, 0xC0); \
add##TYPE##Pattern(4, N + 135, "Write D0 to A0 Word", 0x4E, 0x71, 0x30, 0xC0); \
add##TYPE##Pattern(4, N + 136, "Read A1 to D0 Byte",  0x4E, 0x71, 0x10, 0x19); \
add##TYPE##Pattern(4, N + 137, "Read A1 to D0 Word",  0x4E, 0x71, 0x30, 0x19); \
add##TYPE##Pattern(4, N + 138, "Write D0 to A1 Byte", 0x4E, 0x71, 0x12, 0xC0); \
add##TYPE##Pattern(4, N + 139, "Write D0 to A1 Word", 0x4E, 0x71, 0x32, 0xC0); \
add##TYPE##Pattern(5, N + 140, "Branch if Equal", 0x4E, 0x71, -21, 0, -2); \
add##TYPE##Pattern(5, N + 141, "Branch if Greater", 0x4E, 0x71, -21, 0, -2); \
add##TYPE##Pattern(5, N + 142, "Branch if Less", 0x4E, 0x71, -21, 0, -2); 