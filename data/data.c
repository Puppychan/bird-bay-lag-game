#include "data.h"
#include "background.h"
#include "firstVideo.h"
#include "firstVideo2.h"
#include "firstVideo3.h"
#include "firstVideo4.h"
#include "firstVideo5.h"
#include "player.h"

// first video
// extern const int first_video_array_LEN;
// extern const unsigned long* first_video_array[];
// Array of all bitmaps for convenience. (Total bytes used to store images in = 305760)
const int first_video_array_LEN = 89;
const unsigned long* first_video_array[89] = {
	first_video_flappy_frames_0001,
	first_video_flappy_frames_0002,
	first_video_flappy_frames_0003,
	first_video_flappy_frames_0004,
	first_video_flappy_frames_0005,
	first_video_flappy_frames_0006,
	first_video_flappy_frames_0007,
	first_video_flappy_frames_0008,
	first_video_flappy_frames_0009,
	first_video_flappy_frames_0010,
	first_video_flappy_frames_0011,
	first_video_flappy_frames_0012,
	first_video_flappy_frames_0013,
	first_video_flappy_frames_0014,
	first_video_flappy_frames_0015,
	first_video_flappy_frames_0016,
	first_video_flappy_frames_0017,
	first_video_flappy_frames_0018,
	first_video_flappy_frames_0019,
	first_video_flappy_frames_0020,
	first_video_flappy_frames_0021,
	first_video_flappy_frames_0022,
	first_video_flappy_frames_0023,
	first_video_flappy_frames_0024,
	first_video_flappy_frames_0025,
	first_video_flappy_frames_0026,
	first_video_flappy_frames_0027,
	first_video_flappy_frames_0028,
	first_video_flappy_frames_0029,
	first_video_flappy_frames_0030,
	first_video_flappy_frames_0031,
	first_video_flappy_frames_0032,
	first_video_flappy_frames_0033,
	first_video_flappy_frames_0034,
	first_video_flappy_frames_0035,
	first_video_flappy_frames_0036,
	first_video_flappy_frames_0037,
	first_video_flappy_frames_0038,
	first_video_flappy_frames_0039,
	first_video_flappy_frames_0040,
	first_video_flappy_frames_0041,
	first_video_flappy_frames_0042,
	first_video_flappy_frames_0043,
	first_video_flappy_frames_0044,
	first_video_flappy_frames_0045,
	first_video_flappy_frames_0046,
	first_video_flappy_frames_0047,
	first_video_flappy_frames_0048,
	first_video_flappy_frames_0049,
	first_video_flappy_frames_0050,
	first_video_flappy_frames_0051,
	first_video_flappy_frames_0052,
	first_video_flappy_frames_0053,
	first_video_flappy_frames_0054,
	first_video_flappy_frames_0055,
	first_video_flappy_frames_0056,
	first_video_flappy_frames_0057,
	first_video_flappy_frames_0058,
	first_video_flappy_frames_0059,
	first_video_flappy_frames_0060,
	first_video_flappy_frames_0061,
	first_video_flappy_frames_0062,
	first_video_flappy_frames_0063,
	first_video_flappy_frames_0064,
	first_video_flappy_frames_0065,
	first_video_flappy_frames_0066,
	first_video_flappy_frames_0067,
	first_video_flappy_frames_0068,
	first_video_flappy_frames_0069,
	first_video_flappy_frames_0070,
	first_video_flappy_frames_0071,
	first_video_flappy_frames_0072,
	first_video_flappy_frames_0073,
	first_video_flappy_frames_0074,
	first_video_flappy_frames_0075,
	first_video_flappy_frames_0076,
	first_video_flappy_frames_0077,
	first_video_flappy_frames_0078,
	first_video_flappy_frames_0079,
	first_video_flappy_frames_0080,
	first_video_flappy_frames_0081,
	first_video_flappy_frames_0082,
	first_video_flappy_frames_0083,
	first_video_flappy_frames_0084,
	first_video_flappy_frames_0085,
	first_video_flappy_frames_0086,
	first_video_flappy_frames_0087,
	first_video_flappy_frames_0088,
	first_video_flappy_frames_0089
};

// image
extern const unsigned long background_sky[];
extern const int epd_bitmap_allArray_LEN;
extern const unsigned long* epd_bitmap_allArray[];

// player
// Array of all bitmaps for convenience. (Total bytes used to store images in PROGMEM = 4176)
extern const unsigned long bird_player[];
const int bird_allArray_LEN = 1;
const unsigned long* bird_allArray[1] = {
	bird_player
};