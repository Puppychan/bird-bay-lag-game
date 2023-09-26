#include "../gcclib/stdbool.h"
#include "drawGame.h"

#define false 0
#define true 1

#define mainMenu 1
#define helpMenu 2
#define setBackground 3
#define setBird 4
#define setDifficult 5
#define playGame 6


#define playOption 1
#define helpOption 2
#define exitOption 3

#define easy 1
#define normal 2
#define extreme 3

#define ABS(x) ((x) > 0 ? (x) : -(x))

// Constants for the bird
#define GRAVITY 9.8
#define FLAP_STRENGTH -30
#define PIPE_VERTICAL_SPEED 15 // pixels per frame

#define VERTICAL_MOVEMENT_AMPLITUDE 10 // This is the maximum amount a pipe will move up or down from its initial position.
#define BALLOON_RISE_SPEED 10 // pixels per frame
#define PIPE_VERTICAL_LIMIT 0.01 // This controls how fast the pipes move up and down.

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
bool validate_bird_passing_pipe();

void update_bird();
void flap_bird();
void game_run();

extern int current_bg;
extern int is_set_bg;

void gameMenu();
void backgroundDisplay();

void set_bird_position(float x, float y);
void init_bird();

void reset_round();
void next_round();
bool check_last_round();
void init_round_game();

