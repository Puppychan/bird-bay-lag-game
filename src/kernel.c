#include "../data/data.h"
#include "uart.h"
#include "mbox.h"
#include "framebf.h"
#include "mylib.h"
// #include "./data/test.h"

static int screenHeight = 675;
static int screenWidth = 1080;

void display_image() {
	drawImage(background_sky, screenWidth, screenHeight, 0, 0);
}
void display_video() {
	// infinite_move_image(background_sky, screenWidth, screenHeight, screenWidth, screenHeight);
	drawVideo(first_video_array, first_video_array_LEN, 480, 636, 1);
}
void display_moving_background() {
	// infinite
	// move_image(background_sky, screenWidth, screenHeight, screenWidth, screenHeight, 1);
	// no infinite
	move_image(background_sky, screenWidth, screenHeight, screenWidth, screenHeight, -1, 1, 0);
}
/* CLI read and handle actions */
void cli() {
	char c = uart_getc(); // read each char

	if (c == 'w') { // 'w' pressed: scroll up image
	}
	else if (c == 's') { // 's' pressed: scroll down image
	}
	else if (c == 'a') { // slide to previous image
	}
	else if (c == 'd') { // slide to next image
	}
}


void printName() {
	// Background color
	drawRectARGB32(0, 0, 1024, 768, 0x00B8C3E3, 1);

	//Group name
	drawLetter('P', 20, 20, 0x009400D3);
	drawLetter('h', 60, 20, 0x004B0082);
	drawLetter('a', 100, 20, 0x000000FF);
	drawLetter('n', 140, 20, 0x0000FF00);
	drawLetter('N', 200, 20, 0x00FFFF00);
	drawLetter('h', 240, 20, 0x00FF7F00);
	drawLetter('a', 280, 20, 0x00FF0000);
	drawLetter('t', 320, 20, 0x009400D3);
	drawLetter('M', 380, 20, 0x004B0082);
	drawLetter('i', 420, 20, 0x000000FF);
	drawLetter('n', 460, 20, 0x0000FF00);
	drawLetter('h', 500, 20, 0x00FFFF00);

	drawLetter('T', 20, 80, 0x00FF7F00);
	drawLetter('r', 60, 80, 0x00FF0000);
	drawLetter('a', 100, 80, 0x009400D3);
	drawLetter('n', 140, 80, 0x004B0082);
	drawLetter('M', 200, 80, 0x000000FF);
	drawLetter('a', 240, 80, 0x0000FF00);
	drawLetter('i', 280, 80, 0x00FFFF00);
	drawLetter('N', 340, 80, 0x00FF7F00);
	drawLetter('h', 380, 80, 0x00FF0000);
	drawLetter('u', 420, 80, 0x009400D3);
	drawLetter('n', 460, 80, 0x004B0082);
	drawLetter('g', 500, 80, 0x000000FF);

	drawLetter('N', 20, 140, 0x0000FF00);
	drawLetter('g', 60, 140, 0x00FFFF00);
	drawLetter('u', 100, 140, 0x00FF7F00);
	drawLetter('y', 140, 140, 0x00FF0000);
	drawLetter('e', 180, 140, 0x009400D3);
	drawLetter('n', 220, 140, 0x004B0082);
	drawLetter('N', 280, 140, 0x000000FF);
	drawLetter('g', 320, 140, 0x0000FF00);
	drawLetter('o', 360, 140, 0x00FFFF00);
	drawLetter('c', 400, 140, 0x00FF7F00);
	drawLetter('M', 460, 140, 0x00FF0000);
	drawLetter('i', 500, 140, 0x009400D3);
	drawLetter('n', 540, 140, 0x004B0082);
	drawLetter('h', 580, 140, 0x000000FF);

	drawLetter('T', 20, 200, 0x0000FF00);
	drawLetter('r', 60, 200, 0x00FFFF00);
	drawLetter('a', 100, 200, 0x00FF7F00);
	drawLetter('n', 140, 200, 0x00FF0000);
	drawLetter('N', 200, 200, 0x009400D3);
	drawLetter('g', 240, 200, 0x004B0082);
	drawLetter('u', 280, 200, 0x000000FF);
	drawLetter('y', 320, 200, 0x0000FF00);
	drawLetter('e', 360, 200, 0x00FFFF00);
	drawLetter('n', 400, 200, 0x00FF7F00);
	drawLetter('H', 460, 200, 0x00FF0000);
	drawLetter('a', 500, 200, 0x009400D3);
	drawLetter('K', 560, 200, 0x004B0082);
	drawLetter('h', 600, 200, 0x000000FF);
	drawLetter('a', 640, 200, 0x0000FF00);
	drawLetter('n', 680, 200, 0x00FFFF00);
	drawLetter('h', 720, 200, 0x00FF7F00);
}

void main() {
	// set up serial console
	uart_init();

	// say hello
	uart_puts("\n\nHello World!\n");

	// Initialize frame buffer
	framebf_init();

	// Display group name
	// printName();

	// display_image();
	// display_video();
	display_moving_background();


	// echo everything back
	while (1) {
		cli();
	}
}