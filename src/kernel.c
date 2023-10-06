#include "../data/data.h"
#include "./my-submodule/uart.h"
#include "./my-submodule/mbox.h"
#include "framebf.h"
#include "mylib.h"
#include "./my-submodule/printf.h"
#include "game.h"
#include "../gcclib/stddef.h"

// Maximum command size
#define MAX_CMD_SIZE 100
// Maximum history size
#define MAX_HISTORY 10
// Define NULL
#define NULL ((void *)0)

static int y_offset = 0;

//History Terminal CMD
char cmd_history[MAX_HISTORY][MAX_CMD_SIZE];
// Command history index
int history_cmd = 0;
// Current command index
int current_cmd = 0;

//Command list
char *commands[] = {
  "help",
  "clear",
  "setcolor",
	"displayName",
	"displayImage",
  "displayVideo",
  "playGame"
};
// Command info for help command
char *commandsInfo[] = {
    "clear 					Clears the cmd screen\n",
    "setcolor -t <color> 			Sets text color\n",
	"setcolor -b <color> 			Sets background color\n",
	"setcolor -t <color> -b <color> 		Sets text and background color\n",
    "displayName				Display name of all members\n",
	"displayImage 				Displays image slideshow\n",
    "displayVideo 				Displays a video\n",
    "playGame 				Play flappy bird game\n"
};
// Command detail for help <command> command
char *commandsDetail[] = {
	"help		Show brief information of all commands\n",
    "clear		Clear screen (in our terminal it will scroll down to current position of the cursor).\n",
	"setcolor	Set text color, and/or background color of the console to one of the following colors: BLACK, RED, GREEN, YELLOW, BLUE, PURPLE, CYAN, WHITE\n",
    "displayName 	Display name of all members in the group\n",
	"displayImage	Display image slideshow. Press w and s keys to scroll up and down. Press a and d keys to switch between images\n",
    "displayVideo	Displays an awesome video\n",
    "playGame	Interract with a fun build-in flappy bird game.\n"
};

//Text and Background terminal preset color
char *colors[] = {
    "BLACK",
    "RED",
    "GREEN",
    "YELLOW",
    "BLUE",
    "PURPLE",
    "CYAN",
    "WHITE"
};
// ANSI escape sequences for text and background colors
// Text color
char *ansiTextColors[] = {
    "\033[30m", // BLACK
    "\033[31m", // RED
    "\033[32m", // GREEN
    "\033[33m", // YELLOW
    "\033[34m", // BLUE
    "\033[35m", // PURPLE
    "\033[36m", // CYAN
    "\033[37m", // WHITE
};
// Background color
char *ansiBackgroundColors[] = {
    "\033[40m", // BLACK
    "\033[41m", // RED
    "\033[42m", // GREEN
    "\033[43m", // YELLOW
    "\033[44m", // BLUE
    "\033[45m", // PURPLE
    "\033[46m", // CYAN
    "\033[47m", // WHITE
};

// Get History Command
char *get_history_command(int direction) {
    if (direction == 1 && current_cmd != history_cmd) {
        // DOWN: Navigate to the newer command
        current_cmd = (current_cmd + 1) % MAX_HISTORY;
    } 
    else if (direction == -1 && (current_cmd + MAX_HISTORY - 1) % MAX_HISTORY != history_cmd) {
        // UP: Navigate to the older command
        current_cmd = (current_cmd + MAX_HISTORY - 1) % MAX_HISTORY;
    }
    return cmd_history[current_cmd];
}

// Handle history key (UP and DOWN)
void handle_history_key(char c, char *cli_buffer, int *index) {
    int direction = (c == '+') ? 1 : -1;
    char *historic_command = get_history_command(direction);

    if (historic_command && historic_command[0] != '\0') {
        // Clear the line and reset the cursor
        uart_puts("\rMyOS>                                                                                              ");
        uart_puts("\rMyOS> ");
        
        // Print the historic command
        uart_puts(historic_command);
        
        // Update the command buffer
        strncpy(cli_buffer, historic_command, MAX_CMD_SIZE);
        *index = strlen(cli_buffer);
    }
    return;
}

// Set color
void set_color(const char *option, const char *color) {
	if (!option || !color) {
        return;
    }
    int color_index = -1;
    for (int i = 0; i < 8; i++) {
        if (strcmp(color, colors[i]) == 0) {
            color_index = i;
            break;
        }
    }
    
	if (color_index == -1) {
        uart_puts("Invalid color\n");
        return;
    }

    if (strcmp(option, "-t") == 0) {
        uart_puts(ansiTextColors[color_index]);
    } else if (strcmp(option, "-b") == 0) {
        uart_puts(ansiBackgroundColors[color_index]);
    }
}


void scroll_up_image() {
	if (y_offset > 0)  y_offset--;
  unsigned int *res_data = 0;
  mbox_buffer_setup(ADDR(mBuf), MBOX_TAG_SETVIRTOFF, &res_data, 8, 8, 0, y_offset);
  mbox_call(ADDR(mBuf), MBOX_CH_PROP);
}

void scroll_down_image() {
	if (y_offset + screenHeight < virScreenHeight) y_offset++;
  unsigned int *res_data = 0;
  mbox_buffer_setup(ADDR(mBuf), MBOX_TAG_SETVIRTOFF, &res_data, 8, 8, 0, y_offset);
  mbox_call(ADDR(mBuf), MBOX_CH_PROP);
}

void reset_offset() {
	unsigned int *res_data = 0;
	mbox_buffer_setup(ADDR(mBuf), MBOX_TAG_SETVIRTOFF, &res_data, 8, 8, 0, 0);
	mbox_call(ADDR(mBuf), MBOX_CH_PROP);
}

void display_image() {
	drawImage(background_allArray[current_bg], virScreenWidth, virScreenHeight, 0, 0);
}

void display_video() {
	clear_screen();
	drawVideo(first_video_array, first_video_array_LEN, 480, 636, 0);
	wait_msec(100);
}


void display_moving_background() {
	// infinite
	sizing size_display = { screenWidth, screenHeight };
	// no infinite
	// move_image(background_sky, size_display, size_display, -1, LEFT, 0);
	// infinite
	move_image(background_allArray[current_bg], size_display, size_display, -1, LEFT, 1);
}

void printName() {
	// Background color
	drawRectARGB32(0, 0, screenWidth, screenHeight, 0x00B8C3E3, 1);

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

/* CLI read and handle actions */
void cli() {

	static char cli_buffer[MAX_CMD_SIZE];
	static int index = 0;

	// read and send back each char
	char c = uart_getc();

	
	// Autocomplete
	if (c == '\t') {
		for (int i = 0; i <  sizeof(commands) / sizeof(commands[0]); i++)
		{
			if (strncmp(cli_buffer, commands[i], strlen(cli_buffer)) == 0)
			{
				// Complete the command
				strcpy(cli_buffer, commands[i]);
				index = strlen(cli_buffer);    // Update the index
				//Clear and reprint the prompt with the new command
				uart_puts("\rMyOS>                                  ");
				uart_puts("\rMyOS> ");
				uart_puts(cli_buffer);
				break;
			}
		}
	} 
	else if (c == '+' || c == '_') { //DOWN Key + and UP Key _
		handle_history_key(c, cli_buffer, &index);
	}
	else if (c == '\b' || c == 0x7F) { //Backspace and Delete character
		if (index > 0) {
			index--;
            cli_buffer[index] = '\0';
			uart_puts("\b \b");
			uart_puts("\rMyOS>                                  ");
            uart_puts("\rMyOS> ");
            uart_puts(cli_buffer);
		}
		//Error handling when delete pass the prompt
		else {
			uart_puts("\rMyOS> ");
		}
	} 
	else if (c != '\n') { //put into a buffer until got new line character
		uart_sendc(c);
		cli_buffer[index] = c; //Store into the buffer
		index++;
	} 
	else if (c == '\n') {
		uart_puts("\n");
		cli_buffer[index] = '\0';

		strncpy(cmd_history[history_cmd], cli_buffer, MAX_CMD_SIZE);
    	history_cmd = (history_cmd + 1) % MAX_HISTORY;
    	current_cmd = history_cmd;

		/* Compare with supported commands and execute
		* ........................................... */
		// Help Command
		if (strcmp(cli_buffer, commands[0]) == 0) {
			uart_puts("For more information on a specific command, type help <command-name> \n");
			uart_puts(commandsInfo[0]);
			uart_puts(commandsInfo[1]);
			uart_puts(commandsInfo[2]);
			uart_puts(commandsInfo[3]);
			uart_puts(commandsInfo[4]);
			uart_puts(commandsInfo[5]);
			uart_puts(commandsInfo[6]);
			uart_puts(commandsInfo[7]);
			uart_puts("\n");
		}
		else if (strcmp(cli_buffer, "help help") == 0) {
			uart_puts(commandsDetail[0]);
		}
		else if (strcmp(cli_buffer, "help clear") == 0) {
			uart_puts(commandsDetail[1]);
		}
		else if (strcmp(cli_buffer, "help setcolor") == 0) {
			uart_puts(commandsDetail[2]);
		}
		else if (strcmp(cli_buffer, "help displayName") == 0) {
			uart_puts(commandsDetail[3]);
		}
		else if (strcmp(cli_buffer, "help displayImage") == 0) {
			uart_puts(commandsDetail[4]);
		}
		else if (strcmp(cli_buffer, "help displayVideo") == 0) {
			uart_puts(commandsDetail[5]);
		}
		else if (strcmp(cli_buffer, "help playGame") == 0) {
			uart_puts(commandsDetail[6]);
		}
		//Clear Command
		else if (strcmp(cli_buffer, commands[1]) == 0) {
			clear();
		}
		//Setcolor Command
		else if (strncmp(cli_buffer, commands[2], 8) == 0) {
			// Tokenize the copied buffer to get the command arguments
			char *token = strtok(cli_buffer, " ");
			char *option = NULL;
			char *color = NULL;

			while ((token = strtok(NULL, " ")) != NULL) {
				if (token[0] == '-') { // This is an option
					option = token;
				} else { // This is a color
					color = token;
					if (option == NULL) {
						break;
					} else {
						to_upper(color);
						set_color(option, color);
						option = NULL; // Reset for the next pair, if any
					}
				}
			}
		}
		//displayName Command
		else if (strcmp(cli_buffer, commands[3]) == 0) {
			printName();
		}
		//displayImage Command
		else if (strcmp(cli_buffer, commands[4]) == 0) {
			display_image();
			while (1) {
				char c = uart_getc();
				if (c == '\n') break;
				else if (c == 'a') { // slide to previous image
					if (current_bg == 0) current_bg = background_LEN-1;
					else current_bg--;
					display_image();
				}
				else if (c == 'd') { // slide to next image
					if (current_bg == background_LEN-1) current_bg = 0;
					else current_bg++;
					display_image();
				}
				else if (c == 'w') { // scroll up image
					scroll_up_image();
				}
				else if (c == 's') { // scroll down image
					scroll_down_image();
				}
			}
			// clear sreen and reset virtual offset when command finishes
			clear_screen();
			reset_offset();

		}
		//displayVideo Command
		else if (strcmp(cli_buffer, commands[5]) == 0) {
			display_video();
		}
		//playGame Command
		else if (strcmp(cli_buffer, commands[6]) == 0) {
			gameMenu();
			
		}
		//Error handling
		else {
			uart_puts("Unrecognized as an internal command!\n");
		}
		wait_msec(100);

		//Return to command line
		index = 0;
		displayPrompt();
	}
	
}


void main() {
	// current time
	int time = get_current_time(); // get time to have different seed for testing purpose
	printf("time: %d\n", time);
	// srand_custom(6361625);
	srand_custom(time);
	// set up serial console
	uart_init();

	// Initialize frame buffer
	framebf_init();

	//WelcomeMessage
	welcomeMessage();
	displayPrompt();
	while (1) {
		cli();
	}
}