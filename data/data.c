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

// first video
const int first_video_array_LEN = 75;
const unsigned long* first_video_array[75] = {
	first_video_flappy_frames_frame_flappy_0001,
	first_video_flappy_frames_frame_flappy_0002,
	first_video_flappy_frames_frame_flappy_0003,
	first_video_flappy_frames_frame_flappy_0004,
	first_video_flappy_frames_frame_flappy_0005,
	first_video_flappy_frames_frame_flappy_0006,
	first_video_flappy_frames_frame_flappy_0007,
	first_video_flappy_frames_frame_flappy_0008,
	first_video_flappy_frames_frame_flappy_0009,
	first_video_flappy_frames_frame_flappy_0010,
	first_video_flappy_frames_frame_flappy_0011,
	first_video_flappy_frames_frame_flappy_0012,
	first_video_flappy_frames_frame_flappy_0013,
	first_video_flappy_frames_frame_flappy_0014,
	first_video_flappy_frames_frame_flappy_0015,
	first_video_flappy_frames_frame_flappy_0016,
	first_video_flappy_frames_frame_flappy_0017,
	first_video_flappy_frames_frame_flappy_0018,
	first_video_flappy_frames_frame_flappy_0019,
	first_video_flappy_frames_frame_flappy_0020,
	first_video_flappy_frames_frame_flappy_0021,
	first_video_flappy_frames_frame_flappy_0022,
	first_video_flappy_frames_frame_flappy_0023,
	first_video_flappy_frames_frame_flappy_0024,
	first_video_flappy_frames_frame_flappy_0025,
	first_video_flappy_frames_frame_flappy_0026,
	first_video_flappy_frames_frame_flappy_0027,
	first_video_flappy_frames_frame_flappy_0028,
	first_video_flappy_frames_frame_flappy_0029,
	first_video_flappy_frames_frame_flappy_0030,
	first_video_flappy_frames_frame_flappy_0031,
	first_video_flappy_frames_frame_flappy_0032,
	first_video_flappy_frames_frame_flappy_0033,
	first_video_flappy_frames_frame_flappy_0034,
	first_video_flappy_frames_frame_flappy_0035,
	first_video_flappy_frames_frame_flappy_0036,
	first_video_flappy_frames_frame_flappy_0037,
	first_video_flappy_frames_frame_flappy_0038,
	first_video_flappy_frames_frame_flappy_0039,
	first_video_flappy_frames_frame_flappy_0040,
	first_video_flappy_frames_frame_flappy_0041,
	first_video_flappy_frames_frame_flappy_0042,
	first_video_flappy_frames_frame_flappy_0043,
	first_video_flappy_frames_frame_flappy_0044,
	first_video_flappy_frames_frame_flappy_0045,
	first_video_flappy_frames_frame_flappy_0046,
	first_video_flappy_frames_frame_flappy_0047,
	first_video_flappy_frames_frame_flappy_0048,
	first_video_flappy_frames_frame_flappy_0049,
	first_video_flappy_frames_frame_flappy_0050,
	first_video_flappy_frames_frame_flappy_0051,
	first_video_flappy_frames_frame_flappy_0052,
	first_video_flappy_frames_frame_flappy_0053,
	first_video_flappy_frames_frame_flappy_0054,
	first_video_flappy_frames_frame_flappy_0055,
	first_video_flappy_frames_frame_flappy_0056,
	first_video_flappy_frames_frame_flappy_0057,
	first_video_flappy_frames_frame_flappy_0058,
	first_video_flappy_frames_frame_flappy_0059,
	first_video_flappy_frames_frame_flappy_0060,
	first_video_flappy_frames_frame_flappy_0061,
	first_video_flappy_frames_frame_flappy_0062,
	first_video_flappy_frames_frame_flappy_0063,
	first_video_flappy_frames_frame_flappy_0064,
	first_video_flappy_frames_frame_flappy_0065,
	first_video_flappy_frames_frame_flappy_0066,
	first_video_flappy_frames_frame_flappy_0067,
	first_video_flappy_frames_frame_flappy_0068,
	first_video_flappy_frames_frame_flappy_0069,
	first_video_flappy_frames_frame_flappy_0070,
	first_video_flappy_frames_frame_flappy_0071,
	first_video_flappy_frames_frame_flappy_0072,
	first_video_flappy_frames_frame_flappy_0073,
	first_video_flappy_frames_frame_flappy_0074,
	first_video_flappy_frames_frame_flappy_0075
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
const image_info bird_player_info = { 169, 127, 0x00000000 };
const image_info bird_player_info_2 = { 391, 354, 0x009d22b2 };
const image_info nhung_player_info = { 169, 127, 0x00000000 };
const image_info khanh_player_info = { 169, 127, 0x00000000 };
const image_info minhnguyen_player_info = { 169, 127, 0x00000000 };
const image_info minhphan_player_info = { 169, 127, 0x00000000 };

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
extern const unsigned long arrow[];

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
