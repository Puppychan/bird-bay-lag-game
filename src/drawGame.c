#include "drawGame.h"

pipe pipes[PIPES_SIZE];  // We can have a maximum of 3 pipes on screen for simplicity.
Bird bird;
int bird_width;
int bird_height;
int current_bird = DEFAULT_BIRD;
int current_bg = DEFAULT_BACKGROUND;

unsigned int arrowColorCode = 0x000000;
unsigned int startColorCode = 0x000000;
unsigned int helpColorCode = 0x000000;
unsigned int gameoverColorCode = 0x000000;

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
    // clearImageOverlay(p.bottom.x, p.bottom.y, PIPE_WIDTH, screenHeight - p.bottom.y);
    clearImage(p.top.x, 0, PIPE_WIDTH, p.top.y);
    clearImage(p.bottom.x, p.bottom.y, PIPE_WIDTH, screenHeight - p.bottom.y);
}

void clear_bird() {
    clearImage(bird.x, bird.y, bird_width, bird_height);
}
void backup_pipe(pipe p) {
    backupRegion(p.top.x, 0, PIPE_WIDTH, p.top.y);
    backupRegion(p.bottom.x, p.bottom.y, PIPE_WIDTH, screenHeight - p.bottom.y);
}

void draw_bird(Bird bird, int width, int height) {
    drawScaledImage(bird_allArray[current_bird], bird_info_allArray[current_bird]->width, bird_info_allArray[current_bird]->height, width, height, bird.x, bird.y, bird_info_allArray[current_bird]->exclude_color);
}

void draw_bird_ratio(Bird bird, double scale) {
    drawScaledImage_byRatio(bird_allArray[current_bird], bird_info_allArray[current_bird]->width, bird_info_allArray[current_bird]->height, scale, scale, bird.x, bird.y, bird_info_allArray[current_bird]->exclude_color);
}

void backgroundDisplay() {
    drawImage(background_allArray[current_bg], virScreenWidth, virScreenHeight, 0, 0);
}

// 'arrow', 80x40px
void displayArrow(const unsigned long* arr, int x, int y) { //
    for (int i = 0; i < 40; i++) {
        for (int j = 0; j < 80; j++) {
            if (*arr != 0x00FFFFFF) {
                drawPixelARGB32(x + j, y + i, arrowColorCode);
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

void helpMenuDisplay() {
    backgroundDisplay();
    drawSentence("Instruction", 300, 100, helpColorCode);
    drawSentence("Press Space To Play", 140, 200, helpColorCode);
    drawSentence("Dodge Obstacles To", 140, 300, helpColorCode);
    drawSentence("Gain Point", 340, 350, helpColorCode);
    drawSentence("Back", 420, 430, helpColorCode);
}

void mainMenuDisplay() {
    backgroundDisplay();
    drawWord("Welcome", 300, 150, startColorCode);
    drawWord("To", 620, 150, startColorCode);
    drawWord("Bird", 200, 250, startColorCode);
    drawWord("Bay", 460, 220, startColorCode);
    drawWord("LAG", 700, 280, startColorCode);

    drawWord("Start", 400, 350, startColorCode);
    drawWord("Help", 400, 400, startColorCode);
    drawWord("Exit", 400, 450, startColorCode);
}

void gameoverDisplay() {
    backgroundDisplay();
    drawSentence("GameOver!", 350, 80, gameoverColorCode);
    //Test Score Data
    int score = 10;

    char cScore[10];
    citoa(score, cScore, 10);
    drawSentence("Highest Score", 150, 150, helpColorCode);
    drawSentence(cScore, 800, 150, gameoverColorCode);

    drawSentence("Press any key", 250, 320, helpColorCode);
    drawSentence("to continue", 290, 390, helpColorCode);

    char c = 0;
    do {
        c = getUart();
    } while (c == 0);

    return;
}

void setBackgroundStateDisplay() {
    backgroundDisplay();
    drawSentence("Instruction", 300, 100, helpColorCode);
    drawSentence("Press 'a' or 'd' to slide", 20, 200, helpColorCode);
    drawSentence("Enter to set background", 30, 300, helpColorCode);
}


void setBirdStateDisplay() {
    backgroundDisplay();
    drawSentence("Instruction", 300, 100, helpColorCode);
    drawSentence("Press 'a' or 'd' to slide", 20, 200, helpColorCode);
    drawSentence("Enter to set bird", 160, 300, helpColorCode);
    draw_bird(bird, 120, 100);
}

