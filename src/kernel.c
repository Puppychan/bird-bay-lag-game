#include "uart.h"
#include "mbox.h"
// #include "framebf.h"
#include "printf.h"
// #include "bird.h"
#include "game.h"
// #include "./data/test.h"

// const int screenHeight = 640;
// const int screenWidth = 1024;
// const int virtualScreenHeight = 675;
// const int virtualScreenWidth = 1080;
const int screenHeight = 675;
const int screenWidth = 1080;

void display_image() {
	// drawImage(background_sky, virtualScreenWidth, virtualScreenHeight, 0, 0, -1);
	// backupRegion(0, 0, virtualScreenWidth, virtualScreenHeight);
	drawImage(background_sky, screenWidth, screenHeight, 0, 0, -1);
	backupRegion(0, 0, screenWidth, screenHeight);
}
void display_video() {
	// infinite_move_image(background_sky, screenWidth, screenHeight, screenWidth, screenHeight);
	drawVideo(first_video_array, first_video_array_LEN, 480, 636, 1);
}
void display_moving_background() {
	// infinite
	sizing size_display = { screenWidth, screenHeight };
	// no infinite
	// move_image(background_sky, size_display, size_display, -1, LEFT, 0);
	// infinite
	move_image(background_sky, size_display, size_display, -1, LEFT, 1);
}
/* CLI read and handle actions */
void cli() {
	// char c = uart_getc(); // read each char
	char c = getUart(); // read each char
	// move_pipes(screenWidth, screenHeight);

	if (c == 'w') { // 'w' pressed: scroll up image
	}
	else if (c == 's') { // 's' pressed: scroll down image  
	}
	else if (c == 'a') { // slide to previous image
	}
	else if (c == 'd') { // slide to next image
	}
	else if (c == 'p') { // start game
		// if (is_game_window) { // only start when the user is opening the game window
		// 	// start game here
		// 	is_start_game = 1;
		// }
		start_game();
		// game_loop(screenWidth, screenHeight);
	}
	else if (c == ' ') {
		// if start game
		// if (is_game_window) {

		// }
		// init_pipes();
		// printf("Input space\n");

		flap_bird();
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
	// current time
	int time = get_current_time(); // get time to have different seed for testing purpose
	printf("time: %d", time);
	srand_custom(6361625);
	// srand_custom(time);
	// set up serial console
	uart_init();

	// say hello
	uart_puts("\n\nHello World!\n");

	// Initialize frame buffer
	framebf_init();

	// display_image();
	init_pipes(screenWidth, screenHeight);
	init_bird(screenWidth, screenHeight);

	// wait_msec(500);

	// draw_pipes(screenWidth, screenHeight);

	// drawScaledImage(bird_allArray[0], bird_player_info.width, bird_player_info.height, bird_player_info.width / 6, bird_player_info.height / 6, 0, 0, bird_player_info.exclude_color);
	// drawScaledImage(bird_allArray[1], bird_player_info_2.width, bird_player_info_2.height, bird_player_info_2.width / 6, bird_player_info_2.height / 6, screenWidth - bird_player_info_2.width / 6, screenHeight - bird_player_info_2.height / 6, bird_player_info_2.exclude_color);
	// drawScaledImage(bird_allArray[1], bird_player_info_2.width, bird_player_info_2.height, bird_player_info_2.width / 6, bird_player_info_2.height / 6, 0, 0, bird_player_info_2.exclude_color);

	// display_moving_background();
	// initialize_positions((float)screenWidth / 3, (float)screenHeight / 2);
	// choose_bird(0, 0);
	// draw_bird();
	// clear_bird();

	// Display group name
	// display_video();


	// echo everything back
	while (1) {
		// game_run(screenWidth, screenHeight);

		if (is_start_game()) {
			update_bird(screenWidth, screenHeight);
			move_pipes(screenWidth, screenHeight);
		}

		cli();
	}
}