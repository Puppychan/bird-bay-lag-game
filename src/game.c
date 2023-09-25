#include "game.h"
#include "printf.h"

/*
- Chim bay
- Dynamic pipes
- Game over / Win
- Score
- Other obstacle
*/

#define DEFAULT_BIRD_SHRINK_RATIO 2;

int gameOver = 0;
int current_round = 1;
extern int current_bg;
extern int current_bird;

extern unsigned int arrowColorCode;
extern unsigned int startColorCode;
extern unsigned int helpColorCode;
extern unsigned int gameoverColorCode;


bool _is_resumed = 0;
int _is_game_window = 0; // change later for demo
int _is_start_game = 0;
int _num_active_pipes = 0;
int _remaining_pipes = 0;

extern Bird bird;
extern pipe pipes[PIPES_SIZE];
extern int bird_width;
extern int bird_height;
extern int difficulty = 0;

int pipe_gap = PIPE_GAP_MIN;
// backup_buffer pipeBackupBuffers[PIPES_SIZE];
// unsigned long pipeBackupBuffer[MAX_WIDTH * MAX_HEIGHT];

void end_game() {
    gameOver = 1;
}

// Bird
void set_bird_position(float x, float y) {
    bird.x = x;
    bird.y = y;
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
void init_pipes() {
    int current_offset_x = screenWidth / 2;
    for (int i = 0; i < PIPES_SIZE; i++) {
        // init pipes x and y
        // init x position
        int pipe_distance = rand_range(PIPE_DISTANCE_MIN, screenWidth / 6); // easy
        // TODO: add hard-core
        // int pipe_distance = rand_range(PIPE_DISTANCE_MIN, PIPE_DISTANCE_MAX); // hard
        // pipes[i].top.x = 200 + i * PIPE_DISTANCE;

        pipes[i].top.x = current_offset_x + pipe_distance;
        current_offset_x = pipes[i].top.x + PIPE_WIDTH;
        pipes[i].bottom.x = pipes[i].top.x;

        pipes[i].top.y = rand_range(screenHeight - PIPE_GAP_MAX, PIPE_TOP_MIN);  // Random height for top pipe's bottom end
        pipe_gap = rand_range(PIPE_GAP_MAX, PIPE_GAP_MIN);  // Random gap between pipes
        pipes[i].bottom.y = pipes[i].top.y + pipe_gap;

        if (pipes[i].top.x < screenWidth) {
            draw_pipe(pipes[i]);
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

void init_bird() {
    bird_width = 60;
    bird_height = 60;
    // TODO: add round - change bird
    set_bird_position(200, 400);
    bird.vertical_velocity = 0;
    draw_bird(bird, bird_width, bird_height);
}

void move_pipes() {
    for (int index = 0; index < PIPES_SIZE; index++) {
        if (pipes[index].top.x + PIPE_WIDTH <= screenWidth && pipes[index].top.x > 0) {
            clear_pipe(pipes[index]);
        }

        pipes[index].top.x -= PIPE_MOVE_SPEED;
        pipes[index].bottom.x -= PIPE_MOVE_SPEED;

        if (pipes[index].top.x + PIPE_WIDTH <= 0 || pipes[index].top.x <= 0) continue;  // If this pipe skip the screen, skip it


        // if in the screen, draw it
        if (pipes[index].top.x + PIPE_WIDTH <= screenWidth) {
            // backup_pipe(pipes[index]);
            // Display the pipe on the screen at its new position.
            draw_pipe(pipes[index]);
        }

    }

}

bool validate_bird_overflow() {
    if (bird.y + bird_height > screenHeight || bird.y < 0) {
        return true;
    }
    return false;
}

bool validate_bird_obstacle_collision() {
    for (int index = 0; index < PIPES_SIZE; index++) {
        // Check if the bird's right side is beyond the left edge of the pipe
        // and if the bird's left side is before the right edge of the pipe
        if (bird.x + bird_width >= pipes[index].top.x && bird.x <= pipes[index].top.x + PIPE_WIDTH) {
            // Check for collisions with the top pipe
            if (bird.y < pipes[index].top.y) {
                return true; // collision with top pipe
            }

            // Check for collisions with the bottom pipe
            if (bird.y + bird_height > pipes[index].bottom.y) {
                return true; // collision with bottom pipe
            }
        }
    }
    return false;
}

void update_bird() {
    clear_bird();

    bird.vertical_velocity += GRAVITY;  // Gravity pulls the bird down
    bird.y += bird.vertical_velocity;   // Modify y-coordinate by vertical velocity

    // Check for ceiling collision
    if (validate_bird_overflow() || validate_bird_obstacle_collision()) {
        // bird.y = (bird.y < 0) ? 0 : screenHeight;  // Reset position if overflow detected
        // bird.vertical_velocity = 0;  // Reset velocity
        // // printf("Bird overflow detected");
        // end_game();

        printf("Bird overflow detected %d %d\n", bird.y, bird.vertical_velocity);
    }

    draw_bird(bird, bird_width, bird_height);
}

void flap_bird() {
    bird.vertical_velocity = FLAP_STRENGTH;
}

void game_run() {
    
    while (_is_resumed == false) {
        char c = uart_getc();
        if (c == ' ' && _is_resumed == false) { // if space is pressed and game is not resumed
            _is_resumed = true;
            printf("Called after converting resume\n");
            wait_msec(1000 / 20);
            printf("Called after waiting resume\n");
            break;
        }
    }
    // if resume, then start game
    while (1) {
        // set_wait_timer(1, 100);
        set_wait_timer(1, 1000 / 15);
        printf("Called after true resume\n");
        char play_char = getUart();
        if (play_char == ' ') {
            // bird.vertical_velocity -= 3;       // Gravity pulls the bird down
            // bird.y -= FLAP_STRENGTH;
            flap_bird();
        }

        backgroundDisplay();
        update_bird();
        move_pipes();
        if (gameOver) {
            gameoverDisplay();
            gameOver = 0;
            break;
        }
        // set_wait_timer(0, 100);
        set_wait_timer(0, 1000 / 15);
        // wait_msec(400);
    }

}

void gameMenu() {
    int arrowPos = mainMenu;
    int currState = mainMenu;
    int nextState = mainMenu;
    char c;
    while (1) {
        switch (nextState) {
        case mainMenu:
            mainMenuDisplay();
            arrowPos = playOption;
            nextState = 0;
            currState = mainMenu;
            break;

        case helpMenu:
            helpMenuDisplay();
            nextState = 0;
            currState = helpMenu;
            break;

        case setBackground:
            setBackgroundStateDisplay();
            nextState = 0;
            currState = setBackground;
            break;

        case setBird:
            set_bird_position(500, 430);
            setBirdStateDisplay();
            nextState = 0;
            currState = setBird;
            break;

        case setDifficult:
            difficultSelectDisplay();
            nextState = 0;
            currState = setDifficult;
            break;

        case playGame:
            clear_screen();
            // set_bird_position(200, 400);
            // bird.vertical_velocity = 3;
            init_bird();
            init_pipes();
            nextState = 0;
            currState = playGame;
            break;

        default:
            break;
        }

        switch (currState) {
        case mainMenu:
            c = getUart();
            //Enter to choose option
            if (c == '\n') {
                if (arrowPos == helpOption) {
                    nextState = helpMenu;
                }
                else if (arrowPos == playOption) {
                    // //Play Game Here
                    // playGame();
                    // nextState = mainMenu;
                    nextState = setBackground;
                }
                else if (arrowPos == exitOption) {
                    //Clear screen
                    clear_screen();
                    return;
                }
            }
            //Delete Arrow Position
            if (c == 's') {
                if (arrowPos != exitOption) {
                    deleteArrow(300, 300 + arrowPos * 50);
                    arrowPos++;
                }
            }
            else if (c == 'w') {
                if (arrowPos != playOption) {
                    deleteArrow(300, 300 + arrowPos * 50);
                    arrowPos--;
                }
            }
            //Display Arrow Position
            if (arrowPos == playOption) {
                displayArrow(arrow, 300, 300 + arrowPos * 50);
            }
            else if (arrowPos == helpOption) {
                displayArrow(arrow, 300, 300 + arrowPos * 50);
            }
            else if (arrowPos == exitOption) {
                displayArrow(arrow, 300, 300 + arrowPos * 50);
            }
            break;

        case helpMenu:
            c = getUart();
            if (c == '\n') {
                nextState = mainMenu;
            }
            displayArrow(arrow, 300, 330 + arrowPos * 50);
            break;

        case setBackground:
            c = getUart();
            if (c == '\n') {
                nextState = setBird;
            }
            else if (c == 'a') { // slide to previous image
                if (current_bg == 0) current_bg = background_LEN - 1;
                else current_bg--;
                setBackgroundStateDisplay();
            }
            else if (c == 'd') { // slide to next image
                if (current_bg == background_LEN - 1) current_bg = 0;
                else current_bg++;
                setBackgroundStateDisplay();
            }
            break;

        case setBird:
            c = getUart();
            if (c == '\n') {
                nextState = setDifficult;
            }
            else if (c == 'a') { // slide to previous image
                if (current_bird == 0) current_bird = bird_allArray_LEN - 1;
                else current_bird--;
                setBirdStateDisplay();
            }
            else if (c == 'd') { // slide to next image
                if (current_bird == bird_allArray_LEN - 1) current_bird = 0;
                else current_bird++;
                setBirdStateDisplay();
            }
            break;

        case setDifficult:
            c = getUart();
            //Enter to choose option
            if (c == '\n') {
                if (arrowPos == easy) {
                    difficulty = 1;
                    nextState = playGame;
                }
                else if (arrowPos == normal) {
                    difficulty = 2;
                    nextState = playGame;
                }
                else if (arrowPos == extreme) {
                    difficulty = 3;
                    nextState = playGame;
                }
            }
            //Delete Arrow Position
            if (c == 's') {
                if (arrowPos != extreme) {
                    deleteArrow(200, 300 + arrowPos * 50);
                    arrowPos++;
                }
            }
            else if (c == 'w') {
                if (arrowPos != easy) {
                    deleteArrow(200, 300 + arrowPos * 50);
                    arrowPos--;
                }
            }
            //Display Arrow Position
            if (arrowPos == easy) {
                displayArrow(arrow, 200, 300 + arrowPos * 50);
            }
            else if (arrowPos == normal) {
                displayArrow(arrow, 200, 300 + arrowPos * 50);
            }
            else if (arrowPos == extreme) {
                displayArrow(arrow, 200, 300 + arrowPos * 50);
            }
            break;

        case playGame:
            game_run();
            nextState = mainMenu;
            break;

        default:
            break;
        }
    }
}

