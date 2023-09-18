#include "game.h"

static int screenHeight = 675;
static int screenWidth = 1080;
unsigned int arrowColorCode = 0x000000;
unsigned int startColorCode = 0x000000;
unsigned int helpColorCode = 0x000000;
unsigned int gameoverColorCode = 0x000000;



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
                        //Play Game Here
                        playGame();
                        nextState = mainMenu;
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

            default:
                break;
        }
    }
    

}

void backgroundDisplay() {
    drawImage(background_sky, screenWidth, screenHeight, 0, 0);
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
            drawPixelARGB32(x + j, y + i, background_sky[index]);
            index++;
        }
        index += screenWidth - 80;
    }
}

void playGame() {

}