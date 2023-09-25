// ----------------------------------- framebf.c -------------------------------------
#include "framebf.h"
#include "mbox.h"
#include "uart.h"
#include "../data/fontAutolova.h"
#include "mylib.h"
#include "printf.h"


#define MAX_WIDTH 1080   // maximum expected width
#define MAX_HEIGHT 675  // maximum expected height
uint32_t backupBuffer[MAX_WIDTH * MAX_HEIGHT];

//Use RGBA32 (32 bits for each pixel)
#define COLOR_DEPTH 32

//Pixel Order: BGR in memory order (little endian --> RGB in byte order)
#define PIXEL_ORDER 0

//Screen info
unsigned int width, height, pitch;


//Virtual screen height and width (from frambuffer setup)
const int virScreenHeight = 675;
const int virScreenWidth = 1080;

//Physical width/height (from frambuffer setup)
const int screenHeight = 640;
const int screenWidth = 1024;

/* Frame buffer address
 * (declare as pointer of unsigned char to access each byte) */
unsigned char* fb;

/**
 * Set screen resolution to 1024x768
 */

void framebf_init() {
    mBuf[0] = 35 * 4; // Length of message in bytes
    mBuf[1] = MBOX_REQUEST;

    mBuf[2] = MBOX_TAG_SETPHYWH; //Set physical width-height
    mBuf[3] = 8; // Value size in bytes
    mBuf[4] = 0; // REQUEST CODE = 0

    // ratio: 16/10
    mBuf[5] = screenWidth; // Value(width)
    mBuf[6] = screenHeight; // Value(height)

    mBuf[7] = MBOX_TAG_SETVIRTWH; //Set virtual width-height
    mBuf[8] = 8;
    mBuf[9] = 0;
    mBuf[10] = virScreenWidth;
    mBuf[11] = virScreenHeight;

    mBuf[12] = MBOX_TAG_SETVIRTOFF; //Set virtual offset
    mBuf[13] = 8;
    mBuf[14] = 0;
    mBuf[15] = 0; // x offset
    mBuf[16] = 0; // y offset

    mBuf[17] = MBOX_TAG_SETDEPTH; //Set color depth
    mBuf[18] = 4;
    mBuf[19] = 0;
    mBuf[20] = COLOR_DEPTH; //Bits per pixel

    mBuf[21] = MBOX_TAG_SETPXLORDR; //Set pixel order
    mBuf[22] = 4;
    mBuf[23] = 0;
    mBuf[24] = PIXEL_ORDER;

    mBuf[25] = MBOX_TAG_GETFB; //Get frame buffer
    mBuf[26] = 8;
    mBuf[27] = 0;
    mBuf[28] = 16; //alignment in 16 bytes
    mBuf[29] = 0;  //will return Frame Buffer size in bytes

    mBuf[30] = MBOX_TAG_GETPITCH; //Get pitch
    mBuf[31] = 4;
    mBuf[32] = 0;
    mBuf[33] = 0; //Will get pitch value here

    mBuf[34] = MBOX_TAG_LAST;

    // Call Mailbox
    if (mbox_call(ADDR(mBuf), MBOX_CH_PROP) //mailbox call is successful ?
        && mBuf[20] == COLOR_DEPTH //got correct color depth ?
        && mBuf[24] == PIXEL_ORDER //got correct pixel order ?
        && mBuf[28] != 0 //got a valid address for frame buffer ?
        ) {

        /* Convert GPU address to ARM address (clear higher address bits)
         * Frame Buffer is located in RAM memory, which VideoCore MMU
         * maps it to bus address space starting at 0xC0000000.
         * Software accessing RAM directly use physical addresses
         * (based at 0x00000000)
        */
        mBuf[28] &= 0x3FFFFFFF;

        // Access frame buffer as 1 byte per each address
        fb = (unsigned char*)((unsigned long)mBuf[28]);
        // uart_puts("Got allocated Frame Buffer at RAM physical address: ");
        // uart_hex(mBuf[28]);
        // uart_puts("\n");

        // uart_puts("Frame Buffer Size (bytes): ");
        // uart_dec(mBuf[29]);
        // uart_puts("\n");

        width = mBuf[5];     	// Actual physical width
        height = mBuf[6];     	// Actual physical height
        pitch = mBuf[33];       // Number of bytes per line
        printf("Pitch: %d\n", pitch);

    }
    else {
        uart_puts("Unable to get a frame buffer with provided setting\n");
    }
}

void drawPixelARGB32(int x, int y, unsigned int attr) {
    int offs = (y * pitch) + (COLOR_DEPTH / 8 * x);

    /*	//Access and assign each byte
        *(fb + offs    ) = (attr >> 0 ) & 0xFF; //BLUE
        *(fb + offs + 1) = (attr >> 8 ) & 0xFF; //GREEN
        *(fb + offs + 2) = (attr >> 16) & 0xFF; //RED
        *(fb + offs + 3) = (attr >> 24) & 0xFF; //ALPHA
    */

    //Access 32-bit together
    *((unsigned int*)(fb + offs)) = attr;
}

void drawRectARGB32(int x1, int y1, int x2, int y2, unsigned int attr, int fill) {
    for (int y = y1; y <= y2; y++)
        for (int x = x1; x <= x2; x++) {
            if ((x == x1 || x == x2) || (y == y1 || y == y2))
                drawPixelARGB32(x, y, attr);
            else if (fill)
                drawPixelARGB32(x, y, attr);
        }
}

void clear_screen() {
    drawRectARGB32(0, 0, virScreenWidth, virScreenHeight, 0x00000000, 1);
}

void drawLetter(char ch, int x, int y, unsigned int colorCode) {
    int indexCount = 0;
    //Nest loop run through 40x40 pixel area
    for (int i = y; i < y + 40;i++) {
        for (int j = x; j < x + 40; j++) {
            if (fontData[(unsigned int)ch][indexCount] == 0x00000000) {
                drawPixelARGB32(j, i, colorCode);
            }
            indexCount++;
        }
    }
}

void drawWord(const char* word, int x, int y, unsigned int colorCode) {
    int offset = 0;
    for (int i = 0; word[i] != '\0'; i++) {
        drawLetter(word[i], x + offset, y, colorCode);
        offset += 40; // assuming each letter is 40 pixels wide
    }
}

void drawSentence(const char* word, int x, int y, unsigned int colorCode) {
    int offset = 0;
    for (int i = 0; word[i] != '\0'; i++) {
        if (word[i] != ' ') drawLetter(word[i], x + offset, y, colorCode);
        offset += 40; // assuming each letter is 40 pixels wide
    }
}


void drawImage(const unsigned long* bitmap, int width, int height, int x, int y) {
    int index = 0;
    for (int h = y; h < y + height; h++) {
        for (int w = x; w < x + width; w++) {
            drawPixelARGB32(w, h, bitmap[index]);
            index++;
        }
    }
}

void backupRegion(int x, int y, int width, int height) {
    int backupIndex = 0;
    // printf("Pitch backup region: %d\n", pitch);
    for (int h = y; h < y + height; h++) {
        for (int w = x; w < x + width; w++) {
            backupIndex = h * MAX_WIDTH + w;

            int offs = (h * pitch) + (COLOR_DEPTH / 8 * w);
            uint32_t pixel_value = *((unsigned int*)(fb + offs));
            backupBuffer[backupIndex] = pixel_value;
            // printf("Backup: offs (%d, %d): %d, pixel: %x, current buffer: %x \n", w, h, offs, pixel_value, backupBuffer[index]);
        }
    }
}

void clearImageOverlay(int x, int y, int width, int height) {
    // int index = 0;
    for (int h = y; h < y + height; h++) {
        for (int w = x; w < x + width; w++) {
            // unsigned int originalColor = backupBuffer[index++];

            unsigned int originalColor = backupBuffer[h * MAX_WIDTH + w];
            drawPixelARGB32(w, h, originalColor);
            // printf("Clear image overlay: %x\n", originalColor);
        }
    }
}
void clearImage(int x, int y, int width, int height) {
    // clear image
    for (int h = y; h < y + height; h++) {
        for (int w = x; w < x + width; w++) {
            drawPixelARGB32(w, h, 0x00000000);
        }
    }
}

void drawScaledImage(const unsigned long* bitmap, int orig_width, int orig_height, int new_width, int new_height, int x, int y, unsigned int exclude_color) {
    float x_scale = (float)orig_width / new_width;
    float y_scale = (float)orig_height / new_height;
    int orig_i, orig_j;

    for (int i = 0; i < new_height; i++) {
        orig_i = (int)(i * y_scale);
        for (int j = 0; j < new_width; j++) {
            // Find the corresponding pixel in the original image
            orig_j = (int)(j * x_scale);

            // Get the color of the original pixel
            unsigned long color = bitmap[orig_i * orig_width + orig_j];

            // Draw this pixel in the new image
            if (color != exclude_color) {
                drawPixelARGB32(j + x, i + y, color);
            }
        }
    }
}

void drawScaledImage_byRatio(const unsigned long* bitmap, int orig_width, int orig_height, double x_scale, double y_scale, int x, int y, unsigned int exclude_color) {
    
    int new_width = orig_width*x_scale;
    int new_height = orig_height*y_scale;

    int orig_i, orig_j;

    for (int i = 0; i < new_height; i++) {
        orig_i = (int)(i / y_scale);

        for (int j = 0; j < new_width; j++) {
            // Find the corresponding pixel in the original image
            orig_j = (int)(j / x_scale);

            // Get the color of the original pixel
            unsigned long color = bitmap[orig_i * orig_width + orig_j];

            // draw
            // drawPixelARGB32(j + x, i + y, color);
            if (color != exclude_color) {
                drawPixelARGB32(j + x, i + y, color);
            }
        }
    }
}

void drawVideo(const unsigned long* videoArray[], int num_frames, int img_width, int img_height, int is_infinite) {
    // is_infinite: if users want to loop the video - 1, if users dont want - 0
    // define index for looping frames
    int i = 0;
    while (1) {
        // if reaching final frame
        if (i == num_frames) {
            if (is_infinite == 1) {
                i = 0;
            }
            else {
                return;
            }
        }
        // draw image
        drawImage(videoArray[i], img_width, img_height, 0, 0);  // Draw the image at the top-left corner
        // delay(FRAME_DURATION_VIDEO);  // Delay for the next frame
        wait_msec(1000 / FRAME_DURATION_VIDEO);
        i++;
    }
}


void move_image(const unsigned long* bitmap, sizing img_size, sizing screen_size, int speed, direction direction, int is_infinite) {
    // speed: number > 0
    // direction: 'l': left to right, 'r': right to left, 't': top to bottom, 'b': bottom to top
    // is_infinite: the moving image loops or not? 1: true - 0: false

    position prev = { 0, 0 };
    position current = { 0, 0 };
    int index = 0;
    int max_index = VIDEO_DURATION * FRAME_DURATION_MOVING;
    if (speed <= 0) speed = 1;

    while (1) {
        if (current.x != prev.x || current.y != prev.y) {
            if (current.x > prev.x + img_size.width || prev.x > current.x + img_size.width
                || current.y > prev.y + img_size.height || prev.y > current.y + img_size.height) {
                clearImage(prev.x, prev.y, prev.x + img_size.width, prev.y + img_size.height);
            }
            else {
                drawImage(bitmap, img_size.width, img_size.height, current.x, current.y);
            }
            prev = current;

        }

        // delay(FRAME_DURATION_MOVING);
        set_wait_timer(1, FRAME_DURATION_MOVING);  // Delay for the next frame

        current = identify_next_position(direction, current, img_size, screen_size, index);
        index += speed;
        if (index >= max_index) {
            if (is_infinite == 0) break;
            index = 0; // reset index for infinite loop
        }
    }
}


position identify_next_position(direction direction, position current_position, sizing img_size, sizing screen_size, int index) {
    position new_pos = current_position;

    switch (direction) {
    case LEFT:
        // moving from left to right
        // width + img_width: total space
        // index % (width + img_width): avoid outbound - [0, width + img_width)
        // if x reach (width + img_width - 1) % (width + img_width) = width + img_width - 1 => x returns 0
        new_pos.x = (index + 1) % (screen_size.width + img_size.width);
        break;
    case RIGHT:
        // moving from right to left
        // width + img_width: total space
        // index % (width + img_width): avoid outbound - [0, width + img_width)
        // minus 1 -> to give new position in the left of the screen
        new_pos.x = (screen_size.width + img_size.width) - (index % (screen_size.width + img_size.width)) - 1;
        break;
    case TOP:
        new_pos.y = (index + 1) % (screen_size.height + img_size.height);
        break;
    case BOTTOM:
        new_pos.y = (screen_size.height + img_size.height) - (index % (screen_size.height + img_size.height)) - 1;
        break;
    case TOP_LEFT:
        new_pos.x = (index + 1) % (screen_size.width + img_size.width);
        new_pos.y = (index + 1) % (screen_size.height + img_size.height);
        break;
    case TOP_RIGHT:
        new_pos.x = (screen_size.width + img_size.width) - (index % (screen_size.width + img_size.width)) - 1;
        new_pos.y = (index + 1) % (screen_size.height + img_size.height);
        break;
    case BOTTOM_LEFT:
        new_pos.x = (index + 1) % (screen_size.width + img_size.width);
        new_pos.y = (screen_size.height + img_size.height) - (index % (screen_size.height + img_size.height)) - 1;
        break;
    case BOTTOM_RIGHT:
        new_pos.x = (screen_size.width + img_size.width) - (index % (screen_size.width + img_size.width)) - 1;
        new_pos.y = (screen_size.height + img_size.height) - (index % (screen_size.height + img_size.height)) - 1;
        break;
    }
    return new_pos;
}