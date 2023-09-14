// data.h

#ifndef DATA_H
#define DATA_H

typedef struct {
    int x;
    int y;
} position;

typedef struct {
    unsigned int width;
    unsigned int height;
} sizing;

typedef enum {
    LEFT, RIGHT, TOP, BOTTOM, TOP_LEFT, TOP_RIGHT, BOTTOM_LEFT, BOTTOM_RIGHT
} direction;

// Define structure to hold the information of a mailbox tag
typedef struct {
    unsigned int width;
    unsigned int height;
    unsigned int exclude_color;
} image_info;

// first video
extern const int first_video_array_LEN;
extern const unsigned long* first_video_array[];
// image
extern const unsigned long background_sky[];
extern const int epd_bitmap_allArray_LEN;
extern const unsigned long* epd_bitmap_allArray[];

// players
// birds
extern const int bird_allArray_LEN;
extern const unsigned long* bird_allArray[];
extern const image_info bird_player_info;
extern const image_info bird_player_info_2;
// obstacles
// tube
extern const unsigned long obstacle_tube[];
extern const image_info tube_info;
// balloon
extern const int obstacle_balloon_allArray_LEN;
extern const unsigned long* obstacle_balloon_list[];
extern const image_info balloon_info_1;
extern const image_info balloon_info_2;
extern const image_info balloon_info_3;
extern const image_info balloon_info_4;
extern const image_info balloon_info_5;
extern const image_info balloon_info_6;


#endif // DATA_H