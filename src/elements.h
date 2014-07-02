Window *window;

TextLayer *watch_layer, *last_buzz_layer;
InverterLayer *theme;
int minute, second, hour, fixed;
int custommin = 0;
int customfix, chimes;

char watch_buffer[] = "Test post........";
char buzz_buffer[] = "Last buzzed 2 times";

//You got a problem with pyramids?
static const uint32_t const seg_1[] = { 300 };
static const uint32_t const seg_2[] = { 300, 200, 300 };
static const uint32_t const seg_3[] = { 300, 200, 300, 1500, 300 };
static const uint32_t const seg_4[] = { 300, 200, 300, 1500, 300, 200, 300 };
static const uint32_t const seg_5[] = { 300, 200, 300, 1500, 300, 200, 300, 1500, 300 };
static const uint32_t const seg_6[] = { 300, 200, 300, 1500, 300, 200, 300, 1500, 300, 200, 300 };
static const uint32_t const seg_7[] = { 300, 200, 300, 1500, 300, 200, 300, 1500, 300, 200, 300, 1500, 300 };
static const uint32_t const seg_8[] = { 300, 200, 300, 1500, 300, 200, 300, 1500, 300, 200, 300, 1500, 300, 200, 300 };

VibePattern vibe_segments_1 = {
	.durations = seg_1,
	.num_segments = ARRAY_LENGTH(seg_1),
};

VibePattern vibe_segments_2 = {
	.durations = seg_2,
	.num_segments = ARRAY_LENGTH(seg_2),
};

VibePattern vibe_segments_3 = {
	.durations = seg_3,
	.num_segments = ARRAY_LENGTH(seg_3),
};

VibePattern vibe_segments_4 = {
	.durations = seg_4,
	.num_segments = ARRAY_LENGTH(seg_4),
};

VibePattern vibe_segments_5 = {
	.durations = seg_5,
	.num_segments = ARRAY_LENGTH(seg_5),
};

VibePattern vibe_segments_6 = {
	.durations = seg_6,
	.num_segments = ARRAY_LENGTH(seg_6),
};

VibePattern vibe_segments_7 = {
	.durations = seg_7,
	.num_segments = ARRAY_LENGTH(seg_7),
};

VibePattern vibe_segments_8 = {
	.durations = seg_8,
	.num_segments = ARRAY_LENGTH(seg_8),
};

int normal_watch[5][8] = {
	{
		30, 100, 130, 200, 230, 300, 330, 400
	},
	{
		430, 500, 530, 600, 630, 700, 730, 800
	},
	{
		830, 900, 930, 1000, 1030, 1100, 1130, 1200
	},
	{
		1230, 1300, 1330, 1400, 1430, 1500, 1530, 1600
	},
	{
		2030, 2100, 2130, 2200, 2230, 2300, 2330, 0
	},
};

int dog_watch[2][4] = {
	{
		1630, 1700, 1730, 1800
	},
	{
		1830, 1900, 1930, 2000
	},
};

char *watch_char[5] = {
	"Middle watch", "Morning watch", "Forenoon watch", "Afternoon watch", "First watch",
};

char *dog_char[2] = {
	"First dog watch", "Second dog watch",
};