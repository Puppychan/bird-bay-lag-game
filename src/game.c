#include "game.h"
#define DEFAULT_BIRD_SHRINK_RATIO 6;
#define DEFAULT_BIRD 0


static int screenHeight = 675;
static int screenWidth = 1080;
unsigned int arrowColorCode = 0x000000;
unsigned int startColorCode = 0x000000;
unsigned int helpColorCode = 0x000000;
unsigned int gameoverColorCode = 0x000000;
static int gameOver = 0;

unsigned short current_bg = DEFAULT_BACKGROUND;
unsigned short is_set_bg = false;
static unsigned short current_bird = DEFAULT_BIRD;
static unsigned short is_set_bird = false;
static double bird_scale = (double) 1/DEFAULT_BIRD_SHRINK_RATIO;


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
                is_set_bg = true;
                break;
            
            case setBird:
                setBirdStateDisplay();
                nextState = 0;
                currState = setBird;
                is_set_bird = true;
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
                        drawRectARGB32(0, 0, screenWidth, screenHeight, 0x00000000, 1);
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
                    is_set_bg = false;
                    nextState = setBird;
                }
                else if (c == 'a' && is_set_bg) { // slide to previous image
                    if (current_bg == 0) current_bg = background_LEN-1;
                    else current_bg--;
                    setBackgroundStateDisplay();
                }
                else if (c == 'd' && is_set_bg) { // slide to next image
                    if (current_bg == background_LEN-1) current_bg = 0;
                    else current_bg++;
                    setBackgroundStateDisplay();
                }
                break;

            case setBird:
                c = getUart();
                if (c == '\n') {
                    is_set_bird = false;
                    playGame();
                    nextState = mainMenu;
                }
                else if (c == 'a' && is_set_bird) { // slide to previous image
                    if (current_bird == 0) current_bird = bird_allArray_LEN-1;
                    else current_bird--;
                    setBirdStateDisplay();
                }
                else if (c == 'd' && is_set_bird) { // slide to next image
                    if (current_bird == bird_allArray_LEN-1) current_bird = 0;
                    else current_bird++;
                    setBirdStateDisplay();
                }
                break;


            default:
                break;
        }
    }
}

void backgroundDisplay() {
    drawImage(background_allArray[current_bg], screenWidth, screenHeight, 0, 0);
}


void birdDisplay(double scale, int x, int y) {
    drawScaledImage2(bird_allArray[current_bird], birdWidth, birdHeight, scale, scale, x, y);
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

void playGame() {
    while(1) {
        //Testing Debug
        gameOver = 1;
        if (gameOver) {
            gameoverDisplay();
            gameOver = 0;
            break;
        }
    }
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
    birdDisplay((double)1/3, screenWidth/2 - 70, 450);
}