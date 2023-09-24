#include "game.h"
#include "printf.h"
#define DEFAULT_BIRD_SHRINK_RATIO 2;
#define DEFAULT_BIRD 0

unsigned int arrowColorCode = 0x000000;
unsigned int startColorCode = 0x000000;
unsigned int helpColorCode = 0x000000;
unsigned int gameoverColorCode = 0x000000;

int gameOver = 0;
int current_bg = DEFAULT_BACKGROUND;
int current_bird = DEFAULT_BIRD;
int BIRD_WIDTH = 60;
int BIRD_HEIGHT = 60;

int _is_game_window = 0; // change later for demo
int _is_start_game = 0;
int _num_active_pipes = 0;
int _remaining_pipes = 0;

Bird bird;
pipe pipes[PIPES_SIZE];  // We can have a maximum of 3 pipes on screen for simplicity.

int pipe_gap = PIPE_GAP_MIN;
// backup_buffer pipeBackupBuffers[PIPES_SIZE];
// unsigned long pipeBackupBuffer[MAX_WIDTH * MAX_HEIGHT];

void end_game() {
    gameOver = 1;
}

void draw_pipes() {
    // Draw the pipes
    for (int i = 0; i < PIPES_SIZE; i++) {
        if (pipes[i].top.x + PIPE_WIDTH <= screenWidth) {
            drawScaledImage(obstacle_tube, tube_info.width, tube_info.height, PIPE_WIDTH, pipes[i].top.y, pipes[i].top.x, 0, tube_info.exclude_color);
            drawScaledImage(obstacle_tube_up, tube_up_info.width, tube_up_info.height, PIPE_WIDTH, screenHeight - pipes[i].bottom.y, pipes[i].bottom.x, pipes[i].bottom.y, tube_up_info.exclude_color);
        }
        // if (i != 0) {
        // }
        // drawRectARGB32(pipes[i].top.x, 0, pipes[i].top.x + PIPE_WIDTH, pipes[i].top.y, 0x0074c69d, 1);
        // drawRectARGB32(pipes[i].bottom.x, pipes[i].bottom.y, pipes[i].bottom.x + PIPE_WIDTH, max_height, 0x0074c69d, 1);
    }
}

void draw_pipe(pipe p) {
    // Draw the images for top and bottom pipe parts
    drawScaledImage(obstacle_tube, tube_info.width, tube_info.height, PIPE_WIDTH, p.top.y, p.top.x, 0, tube_info.exclude_color);
    drawScaledImage(obstacle_tube_up, tube_up_info.width, tube_up_info.height, PIPE_WIDTH, screenHeight - p.bottom.y, p.bottom.x, p.bottom.y, tube_up_info.exclude_color);
}

void clear_pipe(pipe p) {
    // clearImageOverlay(p.top.x, 0, PIPE_WIDTH, p.top.y);
    // clearImageOverlay(p.bottom.x, p.bottom.y, PIPE_WIDTH, max_height - p.bottom.y);
    clearImage(p.top.x, 0, PIPE_WIDTH, p.top.y);
    clearImage(p.bottom.x, p.bottom.y, PIPE_WIDTH, screenHeight - p.bottom.y);
}

void clear_bird() {
    clearImage(bird.x, bird.y, BIRD_WIDTH, BIRD_HEIGHT);
}
void backup_pipe(pipe p) {
    backupRegion(p.top.x, 0, PIPE_WIDTH, p.top.y);
    backupRegion(p.bottom.x, p.bottom.y, PIPE_WIDTH, screenHeight - p.bottom.y);
}

void draw_bird(Bird bird, int width, int height) {
    drawScaledImage(bird_allArray[current_bird], bird_info_allArray[current_bird]->width, bird_info_allArray[current_bird]->height, width, height, bird.x, bird.y, bird_info_allArray[current_bird]->exclude_color);
}

void draw_bird_ratio(Bird bird, double scale) {
    drawScaledImage_byRatio(bird_allArray[current_bird],  bird_info_allArray[current_bird]->width, bird_info_allArray[current_bird]->height, scale, scale, bird.x, bird.y, bird_info_allArray[current_bird]->exclude_color);
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


void move_pipes() {
    set_wait_timer(1, 1000 / 60);
    for (int index = 0; index < PIPES_SIZE; index++) {
        if (pipes[index].top.x + PIPE_WIDTH <= screenWidth && pipes[index].top.x > 0) {
            clear_pipe(pipes[index]);
        }

        pipes[index].top.x -= PIPE_MOVE_SPEED;
        pipes[index].bottom.x -= PIPE_MOVE_SPEED;

        if (pipes[index].top.x + PIPE_WIDTH <= 0 || pipes[index].top.x <= 0) continue;  // If this pipe skip the screen, skip it


        // if in the screen, draw it
        if (pipes[index].top.x + PIPE_WIDTH <= screenWidth) {
            // backup_pipe(pipes[index], max_width, max_height);
            // Display the pipe on the screen at its new position.
            draw_pipe(pipes[index]);
        }

    }
    set_wait_timer(0, 1000 / 60);
}

bool validate_bird_overflow() {
    if (bird.y + BIRD_HEIGHT > screenHeight || bird.y < 0) {
        return true;
    }
    return false;
}

bool validate_bird_obstacle_collision() {
    for (int index = 0; index < PIPES_SIZE; index++) {
        // Check if the bird's right side is beyond the left edge of the pipe
        // and if the bird's left side is before the right edge of the pipe
        if (bird.x + BIRD_WIDTH >= pipes[index].top.x && bird.x <= pipes[index].top.x + PIPE_WIDTH) {
            // Check for collisions with the top pipe
            if (bird.y < pipes[index].top.y) {
                return true; // collision with top pipe
            }

            // Check for collisions with the bottom pipe
            if (bird.y + BIRD_HEIGHT > pipes[index].bottom.y) {
                return true; // collision with bottom pipe
            }
        }
    }
    return false;
}

void update_bird() {
    // clear_bird();

    // bird.vertical_velocity += GRAVITY;       // Gravity pulls the bird down
    bird.y += GRAVITY;

    // Check for ceiling collision
    if (validate_bird_overflow() || validate_bird_obstacle_collision()) {
        bird.y = (bird.y < 0) ? 0 : screenHeight;  // Reset position if overflow detected
        // bird.vertical_velocity = 0;  // Reset velocity
        printf("Bird overflow detected");
        end_game();
    }

    draw_bird(bird, BIRD_WIDTH, BIRD_HEIGHT);
}

void flap_bird() {
    bird.vertical_velocity = FLAP_STRENGTH;
}

// void game_run() {
//     // printf("Before init\n");
//     // unsigned long pipeBackupBuffer3D[PIPES_SIZE][max_height * max_width];
//     // printf("Called game loop \n");

//     if (is_start_game()) {
//         update_bird();
//         move_pipes();
//     }
// }

void game_run() {
    while(1) {
        char c = getUart();
        if (c == ' ') {
            // bird.vertical_velocity -= 3;       // Gravity pulls the bird down
            bird.y -= FLAP_STRENGTH;
        }
        backgroundDisplay();
        update_bird();
        move_pipes();
        if (gameOver) {
            // gameoverDisplay();
            // gameOver = 0;
            break;
        }
    }
}

void gameMenu() {
    int arrowPos = mainMenu;
    int currState = mainMenu;
    int nextState = mainMenu;
    char c;
    while (1)
    {
        switch (nextState)
        {
            case mainMenu:
                backgroundDisplay();
                drawWord("Welcome", 80, 170, startColorCode);
                drawWord("To", 400, 170, startColorCode);
                drawWord("Flappy", 520, 170, startColorCode);
                drawWord("Bird", 800, 170, startColorCode);

                drawWord("Start", 400, 350, startColorCode);
                drawWord("Help", 400, 400, startColorCode);
                drawWord("Exit", 400, 450, startColorCode);
                // drawWord("Exit", 400, 450, startColorCode);
                arrowPos = playOption;
                nextState = 0;
                currState = mainMenu;
                break;

            case helpMenu:
                backgroundDisplay();
                drawWord("Instruction", 300, 100, helpColorCode);

                drawWord("Press", 140, 200, helpColorCode);
                drawWord("Space", 380, 200, helpColorCode);
                drawWord("To", 620, 200, helpColorCode);
                drawWord("Play", 740, 200, helpColorCode);

                drawWord("Dodge", 140, 300, helpColorCode);
                drawWord("Obstacles", 380, 300, helpColorCode);
                drawWord("To", 780, 300, helpColorCode);
                drawWord("Gain", 340, 350, helpColorCode);
                drawWord("Point", 540, 350, helpColorCode);

                drawWord("Back", 420, 430, helpColorCode);
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
            
            case playGame:
                clear_screen();
                set_bird_position(200, 400);
                bird.vertical_velocity = 3;
                init_pipes();
                nextState = 0;
                currState = playGame;
                break;

            default:
                break;
        }

        switch (currState)
        {
            case mainMenu:
                c = getUart();
                //Enter to choose option
                if (c == '\n') {
                    if (arrowPos == helpOption) {
                        nextState = helpMenu;
                    } else if (arrowPos == playOption) {
                        // //Play Game Here
                        // playGame();
                        // nextState = mainMenu;
                        nextState = setBackground;
                    } else if (arrowPos == exitOption){
                        //Clear screen
                        clear_screen();
                        return;
                    } 
                }
                //Delete Arrow Position
                if (c == 's') {
                    if(arrowPos != exitOption) {
                        deleteArrow(300, 300 + arrowPos * 50);
                        arrowPos++;
                    }
                } else if (c == 'w') {
                    if(arrowPos != playOption) {
                        deleteArrow(300, 300 + arrowPos * 50);
                        arrowPos--;
                    }
                }
                //Display Arrow Position
                if (arrowPos == playOption) {
                    displayArrow(arrow, 300, 300 + arrowPos*50);
                } else if (arrowPos == helpOption) {
                    displayArrow(arrow, 300,  300 + arrowPos*50);
                } else if (arrowPos == exitOption) {
                    displayArrow(arrow, 300,  300 + arrowPos*50);
                }

                break;

            case helpMenu:
                c = getUart();
                if (c == '\n') {
                    nextState = mainMenu;
                }
                displayArrow(arrow, 300, 330 + arrowPos*50);
                break;

            case setBackground:
                c = getUart();
                if (c == '\n') {
                    nextState = setBird;
                }
                else if (c == 'a') { // slide to previous image
                    if (current_bg == 0) current_bg = background_LEN-1;
                    else current_bg--;
                    setBackgroundStateDisplay();
                }
                else if (c == 'd') { // slide to next image
                    if (current_bg == background_LEN-1) current_bg = 0;
                    else current_bg++;
                    setBackgroundStateDisplay();
                }
                break;

            case setBird:
                c = getUart();
                if (c == '\n') {
                    nextState = playGame;
                }
                else if (c == 'a') { // slide to previous image
                    if (current_bird == 0) current_bird = bird_allArray_LEN-1;
                    else current_bird--;
                    setBirdStateDisplay();
                }
                else if (c == 'd') { // slide to next image
                    if (current_bird == bird_allArray_LEN-1) current_bird = 0;
                    else current_bird++;
                    setBirdStateDisplay();
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

void backgroundDisplay() {
    drawImage(background_allArray[current_bg], virScreenWidth, virScreenHeight, 0, 0);
}

// 'arrow', 80x40px
void displayArrow(const unsigned long *arr, int x, int y) { //
    for (int i = 0; i < 40; i++) {
        for (int j = 0; j < 80; j++) {
            if (*arr != 0x00FFFFFF) {
                drawPixelARGB32(x+j, y+i, arrowColorCode);
            }
            arr++;
        }
    }
}

//Delete the arrow in the menu screen
void deleteArrow(int x, int y) {
    int index = x + y * screenWidth;
    for (int i = 0; i < 40; i++) {
        for (int j = 0; j < 80; j++) {
            drawPixelARGB32(x + j, y + i, background_allArray[current_bg][index]);
            index++;
        }
        index += screenWidth - 80;
    }
}

void gameoverDisplay() {
    backgroundDisplay();
    drawWord("GameOver!", 350, 80, gameoverColorCode);
    //Test Score Data
    int score = 10;
    
    char cScore[10];
    citoa(score, cScore, 10);
    drawWord("Highest", 150, 150, gameoverColorCode);
    drawWord("Score:", 500, 150, gameoverColorCode);
    drawWord(cScore, 800, 150, gameoverColorCode);

    drawWord("Press", 250, 320, gameoverColorCode);
    drawWord("any", 490, 320, gameoverColorCode);
    drawWord("key", 650, 320, gameoverColorCode);
    drawWord("to", 290, 390, gameoverColorCode);
    drawWord("continue", 410, 390, gameoverColorCode);

    char c = 0;
    do {
    c = getUart();
    } while (c == 0);
    
    return;
}

void setBackgroundStateDisplay() {
    backgroundDisplay();
    drawWord("Instruction", 300, 100, helpColorCode);
    drawWord("Press", 20, 200, helpColorCode);
    drawWord("'a'", 260, 200, helpColorCode);
    drawWord("or", 420, 200, helpColorCode);
    drawWord("'d'", 540, 200, helpColorCode);
    drawWord("to", 660, 200, helpColorCode);
    drawWord("silde", 780, 200, helpColorCode);
    drawWord("Enter", 30, 300, helpColorCode);
    drawWord("to", 270, 300, helpColorCode);
    drawWord("set", 390, 300, helpColorCode);
    drawWord("background", 550, 300, helpColorCode);
}


void setBirdStateDisplay() {
    backgroundDisplay();
    drawWord("Instruction", 300, 100, helpColorCode);
    drawWord("Press", 20, 200, helpColorCode);
    drawWord("'a'", 260, 200, helpColorCode);
    drawWord("or", 420, 200, helpColorCode);
    drawWord("'d'", 540, 200, helpColorCode);
    drawWord("to", 660, 200, helpColorCode);
    drawWord("silde", 780, 200, helpColorCode);
    drawWord("Enter", 160, 300, helpColorCode);
    drawWord("to", 400, 300, helpColorCode);
    drawWord("set", 520, 300, helpColorCode);
    drawWord("bird", 680, 300, helpColorCode);     
    draw_bird(bird, 120, 100);
}