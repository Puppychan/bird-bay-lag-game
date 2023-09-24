#include "../data/data.h"

#define FRAME_DURATION_VIDEO 30  // duration for each frame in milliseconds
#define FRAME_DURATION_MOVING 60  // duration for each frame in milliseconds
#define VIDEO_DURATION 30  // display the static image as a 10-second video

//Virtual screen height and width (from frambuffer setup)
extern const int virScreenHeight;
extern const int virScreenWidth;

//Physical width/height (from frambuffer setup)
extern const int screenHeight;
extern const int screenWidth;

void framebf_init();
void drawPixelARGB32(int x, int y, unsigned int attr);
void drawRectARGB32(int x1, int y1, int x2, int y2, unsigned int attr, int fill);

void clear_screen();
void drawLetter(char ch, int x, int y, unsigned int colorCode);
void drawWord(const char* word, int x, int y, unsigned int colorCode);
void drawImage(const unsigned long* bitmap, int width, int height, int x, int y);
void drawScaledImage(const unsigned long* bitmap, int orig_width, int orig_height, int new_width, int new_height, int x, int y, unsigned int exclude_color);
void drawScaledImage_byRatio(const unsigned long* bitmap, int orig_width, int orig_height, double x_scale, double y_scale, int x, int y, unsigned int exclude_color);
void drawVideo(const unsigned long* videoArray[], int num_frames, int img_width, int img_height, int is_infinite);
// void move_image(const unsigned long* bitmap, int img_width, int img_height, int width, int height);
void infinite_move_image(const unsigned long* bitmap, int img_width, int img_height, int screen_width, int screen_height);


void backupRegion(int x, int y, int width, int height);
void clearImageOverlay(int x, int y, int width, int height);
void clearImage(int x, int y, int width, int height);
void move_image(const unsigned long* bitmap, sizing img_size, sizing screen_size, int speed, direction direction, int is_infinite);
position identify_next_position(direction direction, position current_position, sizing img_size, sizing screen_size, int index);

