void framebf_init();
void drawPixelARGB32(int x, int y, unsigned int attr);
void drawRectARGB32(int x1, int y1, int x2, int y2, unsigned int attr, int fill);


void drawLetter(char ch, int x, int y, unsigned int colorCode);
void drawImage(const unsigned long *bitmap, int width, int height, int x, int y);
