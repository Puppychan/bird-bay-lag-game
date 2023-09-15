// data.h

#ifndef DATA_H
#define DATA_H

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
extern const int bird_allArray_LEN;
const unsigned long* bird_allArray[];
// birds
extern const image_info bird_player_info;
extern const unsigned long bird_player[];


#endif // DATA_H