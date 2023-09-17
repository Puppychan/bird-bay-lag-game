#include "game.h"
#include "uart.h" // temp
#include "printf.h"

/*
- Chim bay
- Dynamic pipes
- Game over / Win
- Score
- Other obstacle
*/

#define PIPES_SIZE 10

int _is_game_window = 0; // change later for demo
int _is_start_game = 0;
int _num_active_pipes = 0;
int _remaining_pipes = 0;
position bird_position;  // start in the middle of the screen
pipe pipes[PIPES_SIZE];  // We can have a maximum of 3 pipes on screen for simplicity.
static int bird_velocity = 0;

int pipe_gap = PIPE_GAP_MIN;
// backup_buffer pipeBackupBuffers[PIPES_SIZE];
// unsigned long pipeBackupBuffer[MAX_WIDTH * MAX_HEIGHT];

// handle game window
void open_game() {
    _is_game_window = 1;
}
void close_game() {
    _is_game_window = 0;
}
int is_game_window() {
    return _is_game_window;
}
// handle game state
void start_game() {
    _is_start_game = 1;
}
void end_game() {
    _is_start_game = 0;
}
int is_start_game() {
    return _is_start_game;
}

void draw_pipes(unsigned int max_width, unsigned int max_height) {
    // Draw the pipes
    for (int i = 0; i < PIPES_SIZE; i++) {
        drawScaledImage(obstacle_tube, tube_info.width, tube_info.height, PIPE_WIDTH, pipes[i].top.y, pipes[i].top.x, 0, tube_info.exclude_color);
        drawScaledImage(obstacle_tube_up, tube_up_info.width, tube_up_info.height, PIPE_WIDTH, max_height - pipes[i].bottom.y, pipes[i].bottom.x, pipes[i].bottom.y, tube_up_info.exclude_color);
        // if (i != 0) {
        // }
        // drawRectARGB32(pipes[i].top.x, 0, pipes[i].top.x + PIPE_WIDTH, pipes[i].top.y, 0x0074c69d, 1);
        // drawRectARGB32(pipes[i].bottom.x, pipes[i].bottom.y, pipes[i].bottom.x + PIPE_WIDTH, max_height, 0x0074c69d, 1);
    }
}

void draw_pipe(pipe p, unsigned int max_width, unsigned int max_height) {
    // Draw the images for top and bottom pipe parts
    drawScaledImage(obstacle_tube, tube_info.width, tube_info.height, PIPE_WIDTH, p.top.y, p.top.x, 0, tube_info.exclude_color);
    drawScaledImage(obstacle_tube_up, tube_up_info.width, tube_up_info.height, PIPE_WIDTH, max_height - p.bottom.y, p.bottom.x, p.bottom.y, tube_up_info.exclude_color);
}
void clear_pipe(pipe p, unsigned int max_width, unsigned int max_height) {
    clearImageOverlay(p.top.x, 0, PIPE_WIDTH, p.top.y);
    clearImageOverlay(p.bottom.x, p.bottom.y, PIPE_WIDTH, max_height - p.bottom.y);
}
void backup_pipe(pipe p, unsigned int max_width, unsigned int max_height) {
    backupRegion(p.top.x, 0, PIPE_WIDTH, p.top.y);
    backupRegion(p.bottom.x, p.bottom.y, PIPE_WIDTH, max_height - p.bottom.y);
}

// Bird
void initBird() {
    bird_position.x = 50;
    bird_position.y = 240;
    bird_velocity = 0;
}

// Pipe
int validate_tube_height(pipe prev_pipe, pipe current_pipe, int current_gap) {
    // TODO hard core - later + appear some times only
    printf("prev_pipe.top.y: %d - current_pipe.bottom.y: %d - current_gap: %d\n", prev_pipe.top.y, current_pipe.bottom.y, current_gap);
    // prev_pipe.top.y >= current_pipe.top.y || 
    if (prev_pipe.top.y >= current_pipe.top.y || prev_pipe.bottom.y <= current_pipe.top.y + PIPE_GAP_MIN) return 0;
    return 1;
}

// handle game logics
void init_pipes(unsigned int max_width, unsigned int max_height) {
    int current_offset_x = max_width / 2;
    for (int i = 0; i < PIPES_SIZE; i++) {
        // init pipes x and y
        // init x position
        int pipe_distance = rand_range(PIPE_DISTANCE_MIN, max_width / 6); // easy
        // TODO: add hard-core
        // int pipe_distance = rand_range(PIPE_DISTANCE_MIN, PIPE_DISTANCE_MAX); // hard
        // pipes[i].top.x = 200 + i * PIPE_DISTANCE;

        pipes[i].top.x = current_offset_x + pipe_distance;
        current_offset_x = pipes[i].top.x + PIPE_WIDTH;
        pipes[i].bottom.x = pipes[i].top.x;

        pipes[i].top.y = rand_range(max_height - PIPE_GAP_MAX, PIPE_TOP_MIN);  // Random height for top pipe's bottom end
        pipe_gap = rand_range(PIPE_GAP_MAX, PIPE_GAP_MIN);  // Random gap between pipes
        pipes[i].bottom.y = pipes[i].top.y + pipe_gap;

        if (pipes[i].top.x < max_width) {
            draw_pipe(pipes[i], max_width, max_height);
        }
        else {
            printf("i: %d - top x: %d\n", i, pipes[i].top.x);
        }

        // init y position
        // TODO: add hard core
        // do {
        //     pipes[i].top.y = rand_range(max_height - PIPE_GAP_MAX, PIPE_TOP_MIN);  // Random height for top pipe's bottom end
        //     pipe_gap = rand_range(PIPE_GAP_MAX, PIPE_GAP_MIN);  // Random gap between pipes
        //     pipes[i].bottom.y = pipes[i].top.y + pipe_gap;
        // } while (i > 0 && validate_tube_height(pipes[i - 1], pipes[i], pipe_gap) == 0);  // Make sure pipes don't overlap

    }
}


void move_pipes(unsigned int max_width, unsigned int max_height) {
    for (int index = 0; index < PIPES_SIZE; index++) {
        if (pipes[index].top.x + PIPE_WIDTH <= 0 || pipes[index].top.x <= 0) continue;  // If this pipe skip the screen, skip it
        // if in the screen, draw it
        if (pipes[index].top.x + PIPE_WIDTH <= max_width) {
            clear_pipe(pipes[index], max_width, max_height);
        }

        // Update the position of the pipe.
        pipes[index].top.x -= PIPE_MOVE_SPEED;
        pipes[index].bottom.x -= PIPE_MOVE_SPEED;

        printf("index: %d - top x: %d\n", index, pipes[index].top.x);
        if (pipes[index].top.x + PIPE_WIDTH <= 0 || pipes[index].top.x <= 0) continue;  // If this pipe skip the screen, skip it

        // if in the screen, draw it
        if (pipes[index].top.x + PIPE_WIDTH <= max_width) {
            backup_pipe(pipes[index], max_width, max_height);
            // Display the pipe on the screen at its new position.
            draw_pipe(pipes[index], max_width, max_height);
        }
    }
    wait_msec(20);  // Roughly 60 frames per second
}


void update_bird() {
    bird_velocity += GRAVITY;
    bird_position.y += bird_velocity;

    if (bird_position.y < 0 || bird_position.y > 480) {
        // Bird has hit the ground or top, game over
        end_game();
    }

    for (int i = 0; i < PIPES_SIZE; i++) {
        // Collision detection with pipes
        if (bird_position.x + BIRD_WIDTH >= pipes[i].top.x && bird_position.x <= pipes[i].top.x + PIPE_WIDTH) {
            if (bird_position.y <= pipes[i].top.y || bird_position.y + BIRD_HEIGHT >= pipes[i].bottom.y) {
                // Bird has collided with a pipe, game over
                end_game();
            }
        }
    }
}

void flap() {
    bird_velocity = FLAP_POWER;
}

void game_loop(unsigned int max_width, unsigned int max_height) {
    // printf("Before init\n");
    // unsigned long pipeBackupBuffer3D[PIPES_SIZE][max_height * max_width];
    // printf("Called game loop \n");

    while (1) {
        // for (size_t i = 0; i < 3; i++) {
        // update_bird();
        move_pipes(max_width, max_height);

        // Redraw the bird and pipes here
        // draw_bird(bird_position);
        // draw_pipes();


    }
}
