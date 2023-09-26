#include "data.h"
#include "player.h"
#include "background.h"
#include "arrow.h"
#include "obstacleTube.h"
#include "obstacleBalloon.h"
#include "firstVideo.h"
#include "firstVideo2.h"
#include "firstVideo3.h"
#include "firstVideo4.h"
#include "firstVideo5.h"
// #include "firstVideo6.h"
// #include "firstVideo7.h"
// #include "firstVideo8.h"

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
	// first_video_flappy_frames_0090,
	// first_video_flappy_frames_0091,
	// first_video_flappy_frames_0092,
	// first_video_flappy_frames_0093,
	// first_video_flappy_frames_0094,
	// first_video_flappy_frames_0095,
	// first_video_flappy_frames_0096,
	// first_video_flappy_frames_0097,
	// first_video_flappy_frames_0098,
	// first_video_flappy_frames_0099,
	// first_video_flappy_frames_0100,
	// first_video_flappy_frames_0101,
	// first_video_flappy_frames_0102,
	// first_video_flappy_frames_0103,
	// first_video_flappy_frames_0104,
	// first_video_flappy_frames_0105,
	// first_video_flappy_frames_0106,
	// first_video_flappy_frames_0107,
	// first_video_flappy_frames_0108,
	// first_video_flappy_frames_0109,
	// first_video_flappy_frames_0110,
	// first_video_flappy_frames_0111,
	// first_video_flappy_frames_0112,
	// first_video_flappy_frames_0113,
	// first_video_flappy_frames_0114,
	// first_video_flappy_frames_0115,
	// first_video_flappy_frames_0116,
	// first_video_flappy_frames_0117,
	// first_video_flappy_frames_0118,
	// first_video_flappy_frames_0119,
	// first_video_flappy_frames_0120,
	// first_video_flappy_frames_0121,
	// first_video_flappy_frames_0122,
	// first_video_flappy_frames_0123,
	// first_video_flappy_frames_0124,
	// first_video_flappy_frames_0125,
	// first_video_flappy_frames_0126,
	// first_video_flappy_frames_0127,
	// first_video_flappy_frames_0128,
	// first_video_flappy_frames_0129,
	// first_video_flappy_frames_0130,
	// first_video_flappy_frames_0131,
	// first_video_flappy_frames_0132,
	// first_video_flappy_frames_0133,
	// first_video_flappy_frames_0134,
	// first_video_flappy_frames_0135,
	// first_video_flappy_frames_0136,
	// first_video_flappy_frames_0137,
	// first_video_flappy_frames_0138,
	// first_video_flappy_frames_0139,
	// first_video_flappy_frames_0140,
	// first_video_flappy_frames_0141,
	// first_video_flappy_frames_0142,
	// first_video_flappy_frames_0143,
	// first_video_flappy_frames_0144,
	// first_video_flappy_frames_0145,
	// first_video_flappy_frames_0146,
	// first_video_flappy_frames_0147,
	// first_video_flappy_frames_0148
};

// background
const int background_LEN = 3;
const unsigned long* background_allArray[3] = {
	background_sky,
	background_sun,
	background_cloud
};

// player
// Array of all bitmaps for convenience. (Total bytes used to store images in PROGMEM = 4176)

const int bird_allArray_LEN = 6;
const image_info bird_player_info = {169, 127, 0x00000000};
const image_info bird_player_info_2 = {391, 354, 0x009d22b2};
const image_info nhung_player_info = {169, 127, 0x00000000};
const image_info khanh_player_info = {169, 127, 0x00000000};
const image_info minhnguyen_player_info = {169, 127, 0x00000000};
const image_info minhphan_player_info = {169, 127, 0x00000000};

const image_info* bird_info_allArray[6] = {
	&bird_player_info,
	&bird_player_info_2,
	&nhung_player_info,
	&khanh_player_info,
	&minhnguyen_player_info,
	&minhphan_player_info
};
const unsigned long* bird_allArray[6] = {
	bird_player,
	bird_player_2,
	nhung_player,
	khanh_player,
	minhnguyen_player,
	minhphan_player
};

// image
extern const unsigned long arrow [];

// obstacles
// tube
extern const unsigned long obstacle_tube[];
extern const unsigned long obstacle_tube_up[];
const image_info tube_info = { 167, 571, 0x00ea1863 };
const image_info tube_up_info = { 167, 571, 0x00ea1863 };
// balloon
// Array of all bitmaps for convenience. (Total bytes used to store images in PROGMEM = 13376)
const int obstacle_balloon_allArray_LEN = 6;
const unsigned long* obstacle_balloon_list[6] = {
	obstacle_balloon_1,
	obstacle_balloon_2,
	obstacle_balloon_3,
	obstacle_balloon_4,
	obstacle_balloon_5,
	obstacle_balloon_6
};

const image_info balloon_info_1 = { 339, 714, 0x008cc449 };
const image_info balloon_info_2 = { 479, 622, 0x009d91fd };
const image_info balloon_info_3 = { 358, 286, 0x0000bdd5 };
const image_info balloon_info_4 = { 317, 352, 0x009d22b2 };
const image_info balloon_info_5 = { 327, 702, 0x009d22b2 };
const image_info balloon_info_6 = { 313, 753, 0x004bb14f };

const image_info* obstacle_balloon_info_allArray[6] = {
	&balloon_info_1,
	&balloon_info_2,
	&balloon_info_3,
	&balloon_info_4,
	&balloon_info_5,
	&balloon_info_6
};
