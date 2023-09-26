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

bool gameOver = 0;
bool gameWin = 0;
int pipe_move_speed; // pixels per frame
extern int current_bg;
extern int current_bird;
extern int pipes_size;

extern unsigned int arrowColorCode;
extern unsigned int startColorCode;
extern unsigned int helpColorCode;
extern unsigned int gameoverColorCode;


bool _is_resumed = 0;
bool _is_vertical_move = false;
bool _is_have_balloon = false;
bool _is_have_pipe = false;
int current_pipe_index = 0;
extern int game_scores;
extern int current_round;

extern Bird bird;
extern pipe pipes[MAX_PIPES_SIZE];
extern int bird_width;
extern int bird_height;
extern int difficulty = 0;

int pipe_gap = PIPE_GAP_MIN;

// Game State Utilities
void end_game_over() {
    gameOver = true;
    bird.y = (bird.y < 0) ? 0 : screenHeight;  // Reset position if overflow detected
    bird.vertical_velocity = 0;  // Reset velocity
}

void end_game_over_action() {
    gameoverDisplay();
    // reset
    gameOver = false;
    reset_round();
}

void end_game_win() {
    gameWin = true;
    bird.y = (bird.y < 0) ? 0 : screenHeight;  // Reset position if overflow detected
    bird.vertical_velocity = 0;  // Reset velocity
}

void end_game_win_action() {
    gameoverDisplay();
    // reset
    reset_round();
    gameWin = false;
}
void resume_game() {
    _is_resumed = true;
}
void pause_game() {
    _is_resumed = false;
}

// Round Utilities
void reset_round() {
    current_round = 1;
}
void next_round() {
    current_round++;
}
bool check_last_round() {
    return current_round == 3;
}

// Characteristic Utilities
// enable
void enable_vertical_move() {
    _is_vertical_move = true;
}
void enable_balloon() {
    _is_have_balloon = true;
}
void enable_pipe() {
    _is_have_pipe = true;
}
// disable
void disable_vertical_move() {
    _is_vertical_move = false;
}
void disable_balloon() {
    _is_have_balloon = false;
}
void disable_pipe() {
    _is_have_pipe = false;
}
// check
bool is_vertical_move() {
    return _is_vertical_move;
}
bool is_have_balloon() {
    return _is_have_balloon;
}
bool is_have_pipe() {
    return _is_have_pipe;
}
// reset
void reset_characteristics() {
    _is_vertical_move = false;
    _is_have_balloon = false;
    _is_have_pipe = true;
}

// Difficulty Utilities
void init_difficulty_setting() {
    switch (difficulty) {
    case 1: // Easy
        pipes_size = EASY_pipes_size;
        pipe_move_speed = 15;
        break;
    case 2: // Medium
        pipes_size = MEDIUM_pipes_size;
        pipe_move_speed = 17;
        break;
    case 3: // Hard
        pipes_size = HARD_pipes_size;
        pipe_move_speed = 25;
        break;
    default:
        pipes_size = EASY_pipes_size; // Fallback to a default value
        break;
    }
}


// Bird Utilities
void set_bird_position(float x, float y) {
    bird.x = x;
    bird.y = y;
}
bool validate_bird_overflow() {
    if (bird.y + bird_height > screenHeight || bird.y < 0) {
        return true;
    }
    return false;
}

bool validate_bird_obstacle_collision() {
    // For pipes, check collision with both top and bottom parts.
    if (pipes[current_pipe_index].type == 0) {
        // Check collision with top part of the pipe.
        if (bird.x < pipes[current_pipe_index].top.x + PIPE_WIDTH &&
            bird.x + bird_width > pipes[current_pipe_index].top.x &&
            bird.y < pipes[current_pipe_index].top.y) {
            return true;
        }



        // Check collision with bottom part of the pipe.
        if (bird.x < pipes[current_pipe_index].bottom.x + PIPE_WIDTH &&
            bird.x + bird_width > pipes[current_pipe_index].bottom.x &&
            bird.y + bird_height > pipes[current_pipe_index].bottom.y) {
            return true;
        }
    }
    // For balloons, only check collision with the balloon's body (bottom).
    else if (pipes[current_pipe_index].type == 1) {
        if (bird.x < pipes[current_pipe_index].bottom.x + BALLOON_WIDTH &&
            bird.x + bird_width > pipes[current_pipe_index].bottom.x) {
            int balloon_upper_limit = pipes[current_pipe_index].bottom.y;
            int balloon_lower_limit = pipes[current_pipe_index].bottom.y + pipes[current_pipe_index].bottom.size.height;

            // Return true if bird passes above the upper limit or below the lower limit of the balloon
            if (bird.y + bird_height >= balloon_upper_limit && bird.y <= balloon_lower_limit) {
                return true;
            }

        }
    }
    return false;
}

bool validate_bird_passing_pipe() {
    if (bird.x >= pipes[current_pipe_index].bottom.x + pipes[current_pipe_index].bottom.size.width &&
        bird.x <= pipes[current_pipe_index].bottom.x + pipes[current_pipe_index].bottom.size.width + pipe_move_speed)
        return true;
    return false;
}
void flap_bird() {
    bird.vertical_velocity = FLAP_STRENGTH;
}


// Pipe utilities
int validate_tube_height(pipe prev_pipe, pipe current_pipe, int current_gap) {
    // TODO hard core - later + appear some times only
    // prev_pipe.top.y >= current_pipe.top.y || 
    if (prev_pipe.top.y >= current_pipe.top.y || prev_pipe.bottom.y <= current_pipe.top.y + PIPE_GAP_MIN) return 0;
    return 1;
}
void generate_obstacle(int type, int index, int pipe_distance, int* p_current_offset_x) {
    // type: 0 - pipe, 1 - balloon
    if (type == 0) {
        pipes[index].type = 0; // pipe
        pipes[index].top.x = *p_current_offset_x + pipe_distance;
        pipes[index].top.size.width = PIPE_WIDTH;

        // offset for next pipe or balloon
        *p_current_offset_x = pipes[index].top.x + pipes[index].top.size.width;
        pipes[index].bottom.x = pipes[index].top.x;
        pipes[index].bottom.size.width = pipes[index].top.size.width;

        pipes[index].top.y = rand_range(screenHeight - PIPE_GAP_MAX, PIPE_TOP_MIN);  // Random height for top pipe's bottom end
        pipe_gap = rand_range(PIPE_GAP_MAX, PIPE_GAP_MIN);  // Random gap between pipes
        pipes[index].bottom.y = pipes[index].top.y + pipe_gap;

        if (pipes[index].top.x < screenWidth) {
            draw_pipe(pipes[index]);
        }
    }
    else if (type == 1) {
        // generate balloon
        pipes[index].bottom.x = *p_current_offset_x + pipe_distance;
        pipes[index].bottom.y = screenHeight;
        pipes[index].bottom.size.width = BALLOON_WIDTH;
        pipes[index].bottom.size.height = 150; // random height can be added later

        // offset for next pipe or balloon
        *p_current_offset_x = pipes[index].bottom.x + pipes[index].bottom.size.width;
        pipes[index].type = 1; // balloon

        if (pipes[index].bottom.x < screenWidth) {
            int temp_index = rand_range(0, obstacle_balloon_allArray_LEN - 1);
            pipes[index].display_index = temp_index;
            draw_balloon(pipes[index]);
        }
    }
}

// handle game logics
void init_pipes() {
    int current_offset_x = screenWidth / 2;
    current_pipe_index = 0;
    int display_type = 0;
    if (is_have_balloon() && is_have_pipe()) { // both have pipe and balloon
        display_type = 3;
    }
    else if (is_have_pipe()) { // only have pipe
        display_type = 1;
    }
    else { // only have balloon
        display_type = 0;
    }
    for (int i = 0; i < pipes_size; i++) {
        // init pipes x and y
        // init x position
        int pipe_distance = rand_range(PIPE_DISTANCE_MIN, screenWidth / 3); // easy
        // TODO: add hard-core
        // int pipe_distance = rand_range(PIPE_DISTANCE_MIN, PIPE_DISTANCE_MAX); // hard
        // pipes[i].top.x = 200 + i * PIPE_DISTANCE;


        // Decide randomly whether to initialize a balloon or a pipe
        if (display_type == 3) { // both have pipe and balloon
            if (rand() % 2 == 0) { // 50% chance to create a balloon
                generate_obstacle(1, i, pipe_distance, &current_offset_x);
            }
            else {
                generate_obstacle(0, i, pipe_distance, &current_offset_x);
            }
        }
        else if (display_type == 1) { // only have pipe
            generate_obstacle(0, i, pipe_distance, &current_offset_x);
        }
        else { // only have balloon
            generate_obstacle(1, i, pipe_distance, &current_offset_x);
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

void move_pipes() {
    static int vertical_directions[MAX_PIPES_SIZE]; // 0 for up, 1 for down. Initialize all pipes to move up initially.
    static int initialized = 0; // To check whether static variables are initialized or not.

    if (!initialized) {
        for (int i = 0; i < pipes_size; i++) vertical_directions[i] = 0; // Initialize all pipes to move up initially.
        initialized = 1;
    }

    for (int index = 0; index < pipes_size; index++) {
        if (pipes[index].type == 0) {
            // clear old
            if (pipes[index].top.x + pipes[index].top.size.width <= screenWidth && pipes[index].top.x > 0) {
                clear_pipe(pipes[index]);
            }

            pipes[index].top.x -= pipe_move_speed;
            pipes[index].bottom.x -= pipe_move_speed;
            // Skip drawing if the pipe is off the screen
            if (pipes[index].top.x + pipes[index].top.size.width <= 0 || pipes[index].top.x <= 0) continue;  // If this pipe skip the screen, skip it

            if (is_vertical_move()) {
                // Vertical Movement for balloon and pipe having vertical movement
                int movement = vertical_directions[index] == 0 ? -PIPE_VERTICAL_SPEED : PIPE_VERTICAL_SPEED;
                pipes[index].top.y += movement;
                pipes[index].bottom.y += movement;

                // Change direction if hitting vertical limits
                if (pipes[index].top.y <= PIPE_VERTICAL_LIMIT || pipes[index].top.y >= screenHeight - PIPE_VERTICAL_LIMIT - pipe_gap) {
                    vertical_directions[index] = 1 - vertical_directions[index]; // Toggle direction
                }
            }

            // if in the screen, draw it
            if (pipes[index].top.x + pipes[index].top.size.width <= screenWidth) {
                // backup_pipe(pipes[index]);
                // Display the pipe on the screen at its new position.
                draw_pipe(pipes[index]);
            }
        }
        else if (pipes[index].type == 1) {
            // clear balloon
            if (pipes[index].bottom.x + pipes[index].bottom.size.width <= screenWidth && pipes[index].bottom.x > 0) {
                clear_balloon(pipes[index]);
            }

            pipes[index].bottom.x -= pipe_move_speed;
            int movement = vertical_directions[index] == 0 ? -BALLOON_RISE_SPEED : BALLOON_RISE_SPEED;
            pipes[index].bottom.y += movement; // Move balloon upwards.

            if (pipes[index].bottom.y < 0) { // If balloon goes off the screen at the top, reset position or remove it
                pipes[index].bottom.y = screenHeight; // Reset balloon position to bottom.
            }
            // redraw
            if (pipes[index].bottom.x + pipes[index].bottom.size.width <= screenWidth && pipes[index].bottom.x > 0) {
                draw_balloon(pipes[index]);
            }
        }

    }
}

void init_bird() {
    bird_width = 60;
    bird_height = 60;
    // TODO: add round - change bird
    set_bird_position(200, screenHeight / 2);
    bird.vertical_velocity = 0;
    draw_bird(bird, bird_width, bird_height);
}

void update_bird() {
    clear_bird();

    // Win game
    if (current_pipe_index == pipes_size) {
        end_game_win();
        return;
    }

    bird.vertical_velocity += GRAVITY;  // Gravity pulls the bird down
    bird.y += bird.vertical_velocity;   // Modify y-coordinate by vertical velocity

    // Check for ceiling collision
    if (validate_bird_overflow() || validate_bird_obstacle_collision()) {
        // game over - lose
        end_game_over();

        // printf("Bird overflow detected %d %d\n", bird.y, bird.vertical_velocity);
        return;
    }
    else if (validate_bird_passing_pipe()) {
        // if pass pipe, then increase score
        current_pipe_index++;
        game_scores++;
        convert_scores_to_str();
        // display changed scores
        clearGameScoresDisplay();
        gamingScoresDisplay();
    }

    // backup_bird();
    draw_bird(bird, bird_width, bird_height);
}

// Round
void init_round_game() {
    // function to init game for each round
    switch (current_round) {
    case 1:
        // scores
        convert_scores_to_str();
        gamingScoresDisplay();

        init_bird();
        init_pipes();
        // run game
        game_run();
        break;
    case 2:
        // reset
        gameWin = false;
        // scores
        convert_scores_to_str();
        gamingScoresDisplay();

        // set characteristics
        if (difficulty == 1 && difficulty == 2) { // only have balloon
            disable_pipe();
            enable_balloon();
        }
        else { // extreme mode: have both balloon and pipe
            enable_balloon();
        }

        // setting up game
        init_bird();
        init_pipes();
        // run game
        game_run();
        break;
    case 3:
        // reset
        gameWin = false;
        // scores
        convert_scores_to_str();
        gamingScoresDisplay();

        // set characteristics
        enable_vertical_move();
        enable_pipe();
        if (difficulty == 3) {
            pipe_move_speed += 5;
        }

        // setting up game
        init_bird();
        init_pipes();
        // run game
        game_run();
        break;
    default:
        break;
    }
}


void game_run() {

    while (_is_resumed == false) {
        char c = uart_getc();
        if (c == ' ' && _is_resumed == false) { // if space is pressed and game is not resumed
            if (current_round != 1) {
                changeRoundRemove();
            }
            resume_game();
            wait_msec(FRAME_MOVING_GAME);
            break;
        }
    }
    // if resume, then start game
    while (1) {
        // set_wait_timer(1, 100);
        // 10: easy - 15: normal - 20: extreme
        set_wait_timer(1, FRAME_MOVING_GAME);
        char play_char = getUart();
        if (play_char == ' ') {
            // bird.vertical_velocity -= 3;       // Gravity pulls the bird down
            // bird.y -= FLAP_STRENGTH;
            flap_bird();
        }
        move_pipes();
        update_bird();

        gamingScoresDisplay();

        if (gameOver) {
            end_game_over_action();
            break;
        }
        if (gameWin) {
            // if win, then check if last round
            // if last round, then end game
            if (check_last_round()) {
                end_game_win_action();
            }
            // if not last round, then change round
            else {
                next_round();
                pause_game();
                changeRoundDisplay();
                init_round_game();
            }
            break;
        }
        // set_wait_timer(0, 100);
        set_wait_timer(0, FRAME_MOVING_GAME);
        // wait_msec(400);
    }

}

//Handle game state
void gameMenu() {
    int arrowPos = mainMenu;
    int currState = mainMenu;
    int nextState = mainMenu;
    char c;
    while (1) {
        //Display corresponding views and reset nextState variable.
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
            set_bird_position(screenWidth / 2, 430);
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

            // init
            init_difficulty_setting();
            game_scores = 0;
            backgroundDisplay();
            backupRegion(0, 0, screenWidth, screenHeight);

            reset_round();
            reset_characteristics();
            nextState = 0;
            currState = playGame;
            break;

        default:
            break;
        }

        //Waiting for input at current state
        switch (currState) {
        case mainMenu:
            c = getUart();
            //Enter to choose option
            if (c == '\n') {
                if (arrowPos == helpOption) {
                    nextState = helpMenu;
                }
                else if (arrowPos == playOption) {
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
            displayArrow(arrow, 300, 300 + arrowPos * 50);
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
            //Enter to choose option difficulty
            if (c == '\n') {
                if (arrowPos == easy) {
                    difficulty = 1;
                }
                else if (arrowPos == normal) {
                    difficulty = 2;
                }
                else if (arrowPos == extreme) {
                    difficulty = 3;
                }
                nextState = playGame;
            }
            //Delete Arrow Position
            if (c == 's') {
                if (arrowPos != extreme) {
                    deleteArrow(280, 150 + arrowPos * 100);
                    arrowPos++;
                }
            }
            else if (c == 'w') {
                if (arrowPos != easy) {
                    deleteArrow(280, 150 + arrowPos * 100);
                    arrowPos--;
                }
            }
            //Display Arrow Position
            displayArrow(arrow, 280, 150 + arrowPos * 100);
            break;

        case playGame:
            // game_run();
            init_round_game();
            nextState = mainMenu;
            break;

        default:
            break;
        }
    }
}

