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
Bird bird;
pipe pipes[PIPES_SIZE];  // We can have a maximum of 3 pipes on screen for simplicity.

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
bool is_game_window() {
    return _is_game_window;
}
// handle game state
void start_game() {
    _is_start_game = 1;
}
void end_game() {
    _is_start_game = 0;
}
bool is_start_game() {
    return _is_start_game;
}

void draw_pipes(unsigned int max_width, unsigned int max_height) {
    // Draw the pipes
    for (int i = 0; i < PIPES_SIZE; i++) {
        if (pipes[i].top.x + PIPE_WIDTH <= max_width) {
            drawScaledImage(obstacle_tube, tube_info.width, tube_info.height, PIPE_WIDTH, pipes[i].top.y, pipes[i].top.x, 0, tube_info.exclude_color);
            drawScaledImage(obstacle_tube_up, tube_up_info.width, tube_up_info.height, PIPE_WIDTH, max_height - pipes[i].bottom.y, pipes[i].bottom.x, pipes[i].bottom.y, tube_up_info.exclude_color);
        }
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
    // clearImageOverlay(p.top.x, 0, PIPE_WIDTH, p.top.y);
    // clearImageOverlay(p.bottom.x, p.bottom.y, PIPE_WIDTH, max_height - p.bottom.y);
    clearImage(p.top.x, 0, PIPE_WIDTH, p.top.y);
    clearImage(p.bottom.x, p.bottom.y, PIPE_WIDTH, max_height - p.bottom.y);
}
void clear_bird() {
    clearImage(bird.x, bird.y, BIRD_WIDTH, BIRD_HEIGHT);
}
void backup_pipe(pipe p, unsigned int max_width, unsigned int max_height) {
    backupRegion(p.top.x, 0, PIPE_WIDTH, p.top.y);
    backupRegion(p.bottom.x, p.bottom.y, PIPE_WIDTH, max_height - p.bottom.y);
}
void draw_bird(Bird bird) {
    // Draw the bird
    drawScaledImage(bird_allArray[0], bird_player_info.width, bird_player_info.height, BIRD_WIDTH, BIRD_HEIGHT, bird.x, bird.y, bird_player_info.exclude_color);
}

// Bird
void init_bird(unsigned int max_width, unsigned int max_height) {
    bird.x = max_width / 3;
    bird.y = max_height / 2;
    bird.vertical_velocity = 0;
    draw_bird(bird);
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
        if (pipes[index].top.x + PIPE_WIDTH <= 0 || pipes[index].top.x <= 0) continue;  // If this pipe skip the screen, skip it if in the screen, draw it
        if (pipes[index].top.x + PIPE_WIDTH <= max_width) {
            clear_pipe(pipes[index], max_width, max_height);
        }

        // Update the position of the pipe.
        pipes[index].top.x -= PIPE_MOVE_SPEED;
        pipes[index].bottom.x -= PIPE_MOVE_SPEED;

        if (pipes[index].top.x + PIPE_WIDTH <= 0 || pipes[index].top.x <= 0) continue;  // If this pipe skip the screen, skip it

        // if in the screen, draw it
        if (pipes[index].top.x + PIPE_WIDTH <= max_width) {
            // backup_pipe(pipes[index], max_width, max_height);
            // Display the pipe on the screen at its new position.
            draw_pipe(pipes[index], max_width, max_height);
        }

    }

    wait_msec(30);  // Roughly 60 frames per second
}


void update_bird() {
    clear_bird();

    bird.vertical_velocity += GRAVITY;       // Gravity pulls the bird down
    bird.y += bird.vertical_velocity;

    // Check for ground collision (assuming ground is at y=480)
    if (bird.y + BIRD_HEIGHT > 480) {
        bird.y = 480 - BIRD_HEIGHT; // Prevent bird from moving below ground
    }

    // Check for ceiling collision
    if (bird.y < 0) {
        // bird death
        bird.y = 0;
    }
    draw_bird(bird);
}

void flap_bird() {
    bird.vertical_velocity = FLAP_STRENGTH;
}

void game_loop(unsigned int max_width, unsigned int max_height) {
    // printf("Before init\n");
    // unsigned long pipeBackupBuffer3D[PIPES_SIZE][max_height * max_width];
    // printf("Called game loop \n");

    while (1) {
        // for (size_t i = 0; i < 3; i++) {
        move_pipes(max_width, max_height);

        // Redraw the bird and pipes here
        // draw_bird(bird_position);
        // draw_pipes();


    }
}
