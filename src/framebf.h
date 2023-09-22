#define FRAME_DURATION 30  // duration for each frame in milliseconds
#define VIDEO_DURATION 30  // display the static image as a 10-second video

void framebf_init();
void drawPixelARGB32(int x, int y, unsigned int attr);
void drawRectARGB32(int x1, int y1, int x2, int y2, unsigned int attr, int fill);

void drawLetter(char ch, int x, int y, unsigned int colorCode);
void drawWord(const char* word, int x, int y, unsigned int colorCode);
void drawImage(const unsigned long* bitmap, int width, int height, int x, int y);
void drawScaledImage(const unsigned long* bitmap, int orig_width, int orig_height, int new_width, int new_height, int x, int y, unsigned int exclude_color);
void drawScaledImage2(const unsigned long* bitmap, int orig_width, int orig_height, double x_scale, double y_scale, int x, int y);

// void drawVideo(const unsigned long* frames, int num_frames, int img_width, int img_height, int width, int height);
void drawVideo(const unsigned long* videoArray[], int num_frames, int img_width, int img_height, int is_infinite);
void move_image(const unsigned long* bitmap, int img_width, int img_height, int width, int height);
void infinite_move_image(const unsigned long* bitmap, int img_width, int img_height, int screen_width, int screen_height);
