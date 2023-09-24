#ifndef DATA_H
#define DATA_H

#include "struct.h"


// first video
extern const int first_video_array_LEN;
extern const unsigned long* first_video_array[];

// background
extern const int background_LEN;
extern const unsigned long* background_allArray[];

// bird skins
extern const int bird_allArray_LEN;
extern const unsigned long* bird_allArray[];
extern const image_info* bird_info_allArray[];

// obstacles
// tube
extern const unsigned long obstacle_tube[];
extern const unsigned long obstacle_tube_up[];
extern const image_info tube_info;
extern const image_info tube_up_info;

// balloon
extern const int obstacle_balloon_allArray_LEN;
extern const unsigned long* obstacle_balloon_list[];
extern const image_info* obstacle_balloon_info_allArray[];

// arrow
extern const unsigned long arrow [];

#endif // DATA_H