#define NUM_SOUNDS 108

char SoundNames[108][32] = {
	"Member Joins",
	"Cursed",
	"Town Theme",
	"Simone Ending Theme",
	"Simone Main Theme",
	"Battle Closeup Theme",
	"Prologue",
	"Battle Theme",
	"Battle Theme 2",
	"Battle Theme 3",
	"Sad Theme",
	"Promotion",
	"Find Item",
	"Save",
	"Game Over",
	"Battle Theme 4",
	"-",
	"HQ Theme",
	"Main theme",
	"End of Chapter",
	"Revive",
	"Member Joins(Sad)",
	"Battle Theme 5",
	"Sad Town Theme",
	"-",
	"-",
	"-",
	"-",
	"-",
	"-",
	"Quake",
	"-",
	"Battle Theme 6",
	"Castle Theme",
	"Title Screen",
	"Battle Theme 7",
	"Dark Dargon Awakened",
	"End Credits",
	"Ending",
	"-",
	"-",
	"-",
	"-",
	"-",
	"-",
	"-",
	"-",
	"-",
	"-",
	"-",
	"-",
	"-",
	"-",
	"-",
	"-",
	"-",
	"-",
	"-",
	"-",
	"-",
	"-",
	"-",
	"-",
	"-",
	"-",
	"Select Noise",
	"Confirm Noise",
	"Invalid Noise",
	"Simone Voice",
	"Child / Animal Voice",
	"Female Voice (High)",
	"Female Voice (Low)",
	"Medium Voice",
	"Male Voice(Low)",
	"Male Voice(Medium)",
	"Male Voice(Deep)",
	"Teleportation",
	"Hit / explode",
	"-",
	"-",
	"Ding",
	"Roar 1",
	"Roar 2",
	"Roar 3",
	"Stairs",
	"Open Passage",
	"Jingle",
	"Door",
	"Unknown",
	"Critical",
	"Unknown",
	"Pao Wagons",
	"Laser",
	"Ding",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Falling",
	"Scratch",
	"Healing",
	"Unknown",
	"Unknown",
	"Kane Mask Break",
	"Unknown",
	"-",
	"-",
	"-"
};

void drawSoundList(HDC hdc, int x, int y, int s, int o = 0) {
	RECT r;
	s--;
	char out[32];
	r.top = y;
	r.left = x;
	r.right = x + 604;
	r.bottom = y + (NUM_SOUNDS-o)/3 * 14;
	FillRect(hdc, &r, (HBRUSH)GetStockObject(WHITE_BRUSH));
	for (int i = 0; i<(NUM_SOUNDS - o)/3; i++) {

		if (s == i)Rectangle(hdc, x, y + 14 * i, x + 200, y + 14 * (i + 1));

		sprintf(out, "%s", SoundNames[i+o]);
		TextOut(hdc, x + 4, y + 14 * i, out, strlen(out));

		if (s == i + (NUM_SOUNDS - o) / 3)Rectangle(hdc, x+200, y + 14 * i, x + 400, y + 14 * (i + 1));

		sprintf(out, "%s", SoundNames[i+o+ (NUM_SOUNDS-o) / 3]);
		TextOut(hdc, x + 200 + 4, y + 14 * i , out, strlen(out));

		if (s == i + 2 * (NUM_SOUNDS - o) / 3)Rectangle(hdc, x + 400, y + 14 * i, x + 600, y + 14 * (i + 1));

		sprintf(out, "%s", SoundNames[i+o + 2 * (NUM_SOUNDS - o) / 3]);
		TextOut(hdc, x + 400 + 4, y + 14 * i, out, strlen(out));
	}
}