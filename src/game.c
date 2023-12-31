#include "game.h"

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
int difficulty = 1;
extern int game_scores;
extern int current_round;

extern Bird bird;
extern pipe pipes[MAX_PIPES_SIZE];
extern int bird_width;
extern int bird_height;


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
    // check if last round
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
    // reset
    // vertical move: none, balloon: none, pipe: yes
    _is_vertical_move = false;
    _is_have_balloon = false;
    _is_have_pipe = true;
}

// Difficulty Utilities
void init_difficulty_setting() {
    switch (difficulty) {
    case 1: // Easy
        // set number of pipes
        pipes_size = EASY_pipes_size;
        // set pipe speed
        pipe_move_speed = 15;
        break;
    case 2: // Medium
        // set number of pipes
        pipes_size = MEDIUM_pipes_size;
        // set pipe speed
        pipe_move_speed = 17;
        break;
    case 3: // Hard
        // set number of pipes
        pipes_size = HARD_pipes_size;
        // set pipe speed
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
        // pipes[index].bottom.y = screenHeight;
        pipes[index].bottom.y = rand_range(screenHeight / 2, screenHeight + 10);
        pipes[index].bottom.size.width = BALLOON_WIDTH;
        pipes[index].bottom.size.height = 150;

        // offset for next pipe or balloon
        *p_current_offset_x = pipes[index].bottom.x + pipes[index].bottom.size.width;
        pipes[index].type = 1; // balloon
        // random balloon in the image list
        int temp_index = rand_range(0, obstacle_balloon_allArray_LEN - 1);
        pipes[index].display_index = temp_index;
        
        // if inside the screen, then draw it
        if (pipes[index].bottom.x < screenWidth) {
            draw_balloon(pipes[index]);
        }
    }
}

// handle game logics
void init_pipes() {
    // define current offset x
    int current_offset_x = screenWidth / 2;
    // define current pipe index
    current_pipe_index = 0;
    // define display type based on characteristics
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

    }
}

void move_pipes() {
    static int vertical_directions[MAX_PIPES_SIZE]; // 0 for up, 1 for down. Initialize all pipes to move up initially.
    static int initialized = 0; // To check whether static variables are initialized or not.
    // Initialize vertical_directions array
    if (!initialized) {
        for (int i = 0; i < pipes_size; i++) vertical_directions[i] = 0; // Initialize all pipes to move up initially.
        initialized = 1;
    }

    for (int index = 0; index < pipes_size; index++) {
        // Moving pipe
        if (pipes[index].type == 0) {
            // clear old
            if (pipes[index].top.x + pipes[index].top.size.width <= screenWidth && pipes[index].top.x > 0) {
                clear_pipe(pipes[index]);
            }
            // Move the pipe to the left
            pipes[index].top.x -= pipe_move_speed;
            pipes[index].bottom.x -= pipe_move_speed;
            // Skip drawing if the pipe is off the screen
            if (pipes[index].top.x + pipes[index].top.size.width <= 0 || pipes[index].top.x <= 0) continue;  // If this pipe skip the screen, skip it
            // Check if the pipe is moving vertically
            if (is_vertical_move()) {
                // Vertical Movement for balloon and pipe having vertical movement
                int movement = vertical_directions[index] == 0 ? -PIPE_VERTICAL_SPEED : PIPE_VERTICAL_SPEED;
                // Move the pipe up or down
                pipes[index].top.y += movement;
                pipes[index].bottom.y += movement;

                // Change direction if hitting vertical limits
                if (pipes[index].top.y <= PIPE_VERTICAL_LIMIT || pipes[index].top.y >= screenHeight - PIPE_VERTICAL_LIMIT - pipe_gap) {
                    vertical_directions[index] = 1 - vertical_directions[index]; // Toggle direction
                }
            }

            // if in the screen, draw it
            if (pipes[index].top.x + pipes[index].top.size.width <= screenWidth) {
                // Display the pipe on the screen at its new position.
                draw_pipe(pipes[index]);
            }
        }
        // Moving balloon
        else if (pipes[index].type == 1) {
            // clear balloon
            if (pipes[index].bottom.x <= screenWidth && pipes[index].bottom.x > 0) {
                clear_balloon(pipes[index]);
            }
            // Move the balloon to the left
            pipes[index].bottom.x -= (pipe_move_speed);
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
        // win game
        end_game_win();
        // exit
        return;
    }

    bird.vertical_velocity += GRAVITY;  // Gravity pulls the bird down
    bird.y += bird.vertical_velocity;   // Modify y-coordinate by vertical velocity

    // Check for ceiling collision
    if (validate_bird_overflow() || validate_bird_obstacle_collision()) {
        // game over - lose
        end_game_over();
        // exit
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

        // pipe size
        pipes_size *= 3;
        // set characteristics
        enable_balloon();
        // extreme mode: have both balloon and pipe
        if (difficulty == 1 || difficulty == 2) { // only have balloon
            disable_pipe();
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

        // pipe size
        if (difficulty == 1) {
            pipes_size = EASY_pipes_size;
        }
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
    // Initialize the arrow position to the play option
    int arrowPos = mainMenu;
    int currState = mainMenu;
    int nextState = mainMenu;
    char c;
    while (1) {
        //Display corresponding views and reset nextState variable.
        switch (nextState) {
        case mainMenu:
            // Display the main menu
            mainMenuDisplay();
            // Set the arrow position to the play option
            arrowPos = playOption;
            // Set the current state to the main menu
            nextState = 0;
            currState = mainMenu;
            break;

        case helpMenu:
            // Display the help menu
            helpMenuDisplay();
            // Set the current state to the help menu
            nextState = 0;
            currState = helpMenu;
            break;

        case setBackground:
            // Display the background selection menu
            setBackgroundStateDisplay();
            // Set the current state to the background selection menu
            nextState = 0;
            currState = setBackground;
            break;

        case setBird:
            // Set the bird position to the middle of the screen to display selected bird
            set_bird_position((screenWidth / 2) - 130, 430);
            // Display the bird selection menu
            setBirdStateDisplay();
            // Set the current state to the bird selection menu
            nextState = 0;
            currState = setBird;
            break;

        case setDifficult:
            // Display the difficulty selection menu
            difficultSelectDisplay();
            // Set the current state to the difficulty selection menu
            nextState = 0;
            currState = setDifficult;
            break;

        case playGame:
            // Clear the screen
            clear_screen();
            // Set the difficulty setting
            init_difficulty_setting();
            // init
            game_scores = 0;
            // Display the background
            backgroundDisplay();
            backupRegion(0, 0, screenWidth, screenHeight);
            // Reset the round and characteristics
            reset_round();
            reset_characteristics();
            // Set the current state to the game
            nextState = 0;
            currState = playGame;
            break;

        default:
            break;
        }

        //Waiting for input at current state
        switch (currState) {
        case mainMenu:
            // Get input from UART
            c = getUart();
            //Enter to choose option
            if (c == '\n') { // enter
                // Arrow position determines the next state
                if (arrowPos == helpOption) {
                    // Next state is help menu
                    nextState = helpMenu;
                }
                else if (arrowPos == playOption) {
                    // Next state is background selection menu
                    nextState = setBackground;
                }
                else if (arrowPos == exitOption) {
                    //Clear screen
                    clear_screen();
                    // Exit the game - back to console
                    return;
                }
            }
            // Move down arrow position
            if (c == 's') {
                // Prevent arrow from moving out of bounds
                if (arrowPos != exitOption) {
                    // Clear the arrow by using backup region
                    deleteArrow(300, 300 + arrowPos * 50);
                    // Move the arrow down
                    arrowPos++;
                }
            }
            // Move up arrow position
            else if (c == 'w') {
                // Prevent arrow from moving out of bounds
                if (arrowPos != playOption) {
                    // Clear the arrow by using backup region
                    deleteArrow(300, 300 + arrowPos * 50);
                    // Move the arrow up
                    arrowPos--;
                }
            }
            //Display Arrow Position
            displayArrow(arrow, 300, 300 + arrowPos * 50);
            break;

        case helpMenu:
            // Get input from UART
            c = getUart();
            // ENter to go back to main menu
            if (c == '\n') {
                nextState = mainMenu;
            }
            displayArrow(arrow, 300, 330 + arrowPos * 50);
            break;

        case setBackground:
            // Get input from UART
            c = getUart();
            // Enter to go to bird selection menu
            if (c == '\n') {
                nextState = setBird;
            }
            else if (c == 'a') { // slide to previous image
                // Prevent background from moving out of bounds
                if (current_bg == 0) current_bg = background_LEN - 1;
                // Move to previous background
                else current_bg--;
                // Display the background
                setBackgroundStateDisplay();
            }
            else if (c == 'd') { // slide to next image
                // Prevent background from moving out of bounds
                if (current_bg == background_LEN - 1) current_bg = 0;
                // Move to next background
                else current_bg++;
                // Display the background
                setBackgroundStateDisplay();
            }
            break;

        case setBird:
            // Get input from UART
            c = getUart();
            // Enter to go to difficulty selection menu
            if (c == '\n') {
                nextState = setDifficult;
            }
            else if (c == 'a') { // slide to previous image
                // Prevent bird from moving out of bounds
                if (current_bird == 0) current_bird = bird_allArray_LEN - 1;
                // Move to previous bird
                else current_bird--;
                // Display the bird
                setBirdStateDisplay();
            }
            else if (c == 'd') { // slide to next image
                // Prevent bird from moving out of bounds
                if (current_bird == bird_allArray_LEN - 1) current_bird = 0;
                // Move to next bird
                else current_bird++;
                // Display the bird
                setBirdStateDisplay();
            }
            break;

        case setDifficult:
            // Get input from UART
            c = getUart();
            //Enter to choose option difficulty
            if (c == '\n') {
                // Arrow position determines the choice
                if (arrowPos == easy) {
                    difficulty = 1;
                }
                else if (arrowPos == normal) {
                    difficulty = 2;
                }
                else if (arrowPos == extreme) {
                    difficulty = 3;
                }
                // Next state is game
                nextState = playGame;
            }
            // Move down arrow position
            if (c == 's') {
                // Prevent arrow from moving out of bounds
                if (arrowPos != extreme) {
                    // Clear the arrow by using backup region
                    deleteArrow(280, 150 + arrowPos * 100);
                    // Move the arrow down
                    arrowPos++;
                }
            }
            // Move up arrow position
            else if (c == 'w') {
                // Prevent arrow from moving out of bounds
                if (arrowPos != easy) {
                    // Clear the arrow by using backup region
                    deleteArrow(280, 150 + arrowPos * 100);
                    // Move the arrow up
                    arrowPos--;
                }
            }
            //Display Arrow Position
            displayArrow(arrow, 280, 150 + arrowPos * 100);
            break;

        case playGame:
            // Init game and start
            init_round_game();
            // Next state is main menu
            nextState = mainMenu;
            break;

        default:
            break;
        }
    }
}

