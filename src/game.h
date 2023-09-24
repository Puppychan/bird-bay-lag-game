#include "uart.h"
#include "../gcclib/stdbool.h"
#include "../data/data.h"
#include "framebf.h"
#include "mylib.h"
#define DEFAULT_BACKGROUND 0
#define false 0
#define true 1

#define mainMenu 1
#define helpMenu 2
#define setBackground 3
#define setBird 4
#define playGame 5


#define playOption 1
#define helpOption 2
#define exitOption 3

#define ABS(x) ((x) > 0 ? (x) : -(x))

// Constants for the game mechanics
#define PIPES_SIZE 10
#define PIPE_DISTANCE 100 // make it modifiable later
#define PIPE_GAP 50 // make it modifiable later
#define PIPE_WIDTH 50 

#define PIPE_DISTANCE_MIN 130 // easy
// #define PIPE_DISTANCE_MIN 0 // hard
// #define PIPE_DISTANCE_MAX 50 // hard
#define PIPE_TOP_MIN 70
// #define PIPE_GAP_MIN 100 // change later for expert round - increase in bird size
#define PIPE_GAP_MIN 100
#define PIPE_GAP_MAX 150

#define PIPE_MOVE_SPEED 3 // pixels per frame

// Constants for the bird
#define GRAVITY 1
#define FLAP_STRENGTH -10

#define MOVE_SPEED 5 // pixels per frame

void end_game();

void clear_pipe(pipe p);
void clear_bird();
void backup_pipe(pipe p);

void draw_pipes();
void draw_pipe(pipe p);
int validate_tube_height(pipe prev_pipe, pipe current_pipe, int current_gap);
void init_bird();
void init_pipes();
// void move_pipes();
void move_pipes();
bool validate_bird_overflow();
bool validate_bird_obstacle_collision();
void update_bird();
void flap_bird();
void game_run();

extern int current_bg;
extern int is_set_bg;

void gameMenu();
void backgroundDisplay();
void birdDisplay();
void displayArrow(const unsigned long *arr, int x, int y);
void deleteArrow(int x, int y);
void gameoverDisplay();
void selectBackground();
void selectBird();
void setBirdStateDisplay();
void setBackgroundStateDisplay();
