#include "framebf.h"
#include "mylib.h"

#define ABS(x) ((x) > 0 ? (x) : -(x))

// Constants for the game mechanics
#define GRAVITY 1
#define FLAP_POWER -15
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

#define PIPE_MOVE_SPEED 5 // pixels per frame

// Constants for the bird
#define BIRD_WIDTH 50 // make it modifiable later
#define BIRD_HEIGHT 50 // make it modifiable later


#define MOVE_SPEED 5 // pixels per frame

void clear_pipe(pipe p, unsigned int max_width, unsigned int max_height);
void backup_pipe(pipe p, unsigned int max_width, unsigned int max_height);

void draw_pipes(unsigned int max_width, unsigned int max_height);
void draw_pipe(pipe p, unsigned int max_width, unsigned int max_height);
int validate_tube_height(pipe prev_pipe, pipe current_pipe, int current_gap);
void init_pipes(unsigned int max_width, unsigned int max_height);
// void move_pipes();
void move_pipes(unsigned int max_width, unsigned int max_height);
void update_bird();
void flap();
void game_loop(unsigned int max_width, unsigned int max_height);