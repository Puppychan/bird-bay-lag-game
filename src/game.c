#include "uart.h"
#include "../data/data.h"
#include "framebf.h"

static int screenHeight = 675;
static int screenWidth = 1080;
unsigned int startColorCode = 0xD80032;
unsigned int instrucColorCode = 0xD80032;
unsigned int gameoverColorCode = 0xD80032;
// 1 = gameover
int isGameover = 0;

int addscore(int* score) {
    (*score)++;
    return *score;
}

void startDisplay() {
    drawImage(background_sky, screenWidth, screenHeight, 0, 0);
    int startY = 170;
    int startX = 80;
    drawLetter('W', startX, startY, startColorCode);
    drawLetter('E', startX+=40, startY, startColorCode);
    drawLetter('L', startX+=40, startY, startColorCode);
    drawLetter('C', startX+=40, startY, startColorCode);
    drawLetter('O', startX+=40, startY, startColorCode);
    drawLetter('M', startX+=40, startY, startColorCode);
    drawLetter('E', startX+=40, startY, startColorCode);
    drawLetter('T', startX+=80, startY, startColorCode);
    drawLetter('O', startX+=40, startY, startColorCode);
    drawLetter('F', startX+=80, startY, startColorCode);
    drawLetter('L', startX+=40, startY, startColorCode);
    drawLetter('A', startX+=40, startY, startColorCode);
    drawLetter('P', startX+=40, startY, startColorCode);
    drawLetter('P', startX+=40, startY, startColorCode);
    drawLetter('Y', startX+=40, startY, startColorCode);
    drawLetter('B', startX+=80, startY, startColorCode);
    drawLetter('I', startX+=40, startY, startColorCode);
    drawLetter('R', startX+=40, startY, startColorCode);
    drawLetter('D', startX+=40, startY, startColorCode);

    startY = 317;
    startX = 80;
    drawLetter('P', startX, startY, startColorCode);
    drawLetter('R', startX+=40, startY, startColorCode);
    drawLetter('E', startX+=40, startY, startColorCode);
    drawLetter('S', startX+=40, startY, startColorCode);
    drawLetter('S', startX+=40, startY, startColorCode);
    drawLetter('A', startX+=80, startY, startColorCode);
    drawLetter('N', startX+=40, startY, startColorCode);
    drawLetter('Y', startX+=40, startY, startColorCode);
    drawLetter('K', startX+=80, startY, startColorCode);
    drawLetter('E', startX+=40, startY, startColorCode);
    drawLetter('Y', startX+=40, startY, startColorCode);
    drawLetter('T', startX+=80, startY, startColorCode);
    drawLetter('O', startX+=40, startY, startColorCode);
    drawLetter('S', startX+=80, startY, startColorCode);
    drawLetter('T', startX+=40, startY, startColorCode);
    drawLetter('A', startX+=40, startY, startColorCode);
    drawLetter('R', startX+=40, startY, startColorCode);
    drawLetter('T', startX+=40, startY, startColorCode);

}

void instructDisplay() {
    drawImage(background_sky, screenWidth, screenHeight, 0, 0);

    int startX = 300;
    int startY = 100;
    drawLetter('I', startX, startY, instrucColorCode);
    drawLetter('N', startX+=40, startY, instrucColorCode);
    drawLetter('S', startX+=40, startY, instrucColorCode);
    drawLetter('T', startX+=40, startY, instrucColorCode);
    drawLetter('R', startX+=40, startY, instrucColorCode);
    drawLetter('U', startX+=40, startY, instrucColorCode);
    drawLetter('C', startX+=40, startY, instrucColorCode);
    drawLetter('T', startX+=40, startY, instrucColorCode);
    drawLetter('I', startX+=40, startY, instrucColorCode);
    drawLetter('O', startX+=40, startY, instrucColorCode);
    drawLetter('N', startX+=40, startY, instrucColorCode);

    startX = 140;
    startY = 317;
    drawLetter('P', startX, startY, instrucColorCode);
    drawLetter('R', startX+=40, startY, instrucColorCode);
    drawLetter('E', startX+=40, startY, instrucColorCode);
    drawLetter('S', startX+=40, startY, instrucColorCode);
    drawLetter('S', startX+=40, startY, instrucColorCode);
    drawLetter('S', startX+=80, startY, instrucColorCode);
    drawLetter('P', startX+=40, startY, instrucColorCode);
    drawLetter('A', startX+=40, startY, instrucColorCode);
    drawLetter('C', startX+=40, startY, instrucColorCode);
    drawLetter('E', startX+=40, startY, instrucColorCode);
    drawLetter('T', startX+=80, startY, instrucColorCode);
    drawLetter('O', startX+=40, startY, instrucColorCode);
    drawLetter('P', startX+=80, startY, instrucColorCode);
    drawLetter('L', startX+=40, startY, instrucColorCode);
    drawLetter('A', startX+=40, startY, instrucColorCode);
    drawLetter('Y', startX+=40, startY, instrucColorCode);

    startX = 140;
    startY = 370;
    drawLetter('D', startX, startY, instrucColorCode);
    drawLetter('O', startX+=40, startY, instrucColorCode);
    drawLetter('D', startX+=40, startY, instrucColorCode);
    drawLetter('G', startX+=40, startY, instrucColorCode);
    drawLetter('E', startX+=40, startY, instrucColorCode);
    drawLetter('O', startX+=80, startY, instrucColorCode);
    drawLetter('B', startX+=40, startY, instrucColorCode);
    drawLetter('S', startX+=40, startY, instrucColorCode);
    drawLetter('T', startX+=40, startY, instrucColorCode);
    drawLetter('A', startX+=40, startY, instrucColorCode);
    drawLetter('C', startX+=40, startY, instrucColorCode);
    drawLetter('L', startX+=40, startY, instrucColorCode);
    drawLetter('E', startX+=40, startY, instrucColorCode);
    drawLetter('S', startX+=40, startY, instrucColorCode);

    startX = 140;
    startY = 430;
    drawLetter('T', startX+=160, startY, instrucColorCode);
    drawLetter('O', startX+=40, startY, instrucColorCode);
    drawLetter('G', startX+=80, startY, instrucColorCode);
    drawLetter('A', startX+=40, startY, instrucColorCode);
    drawLetter('I', startX+=40, startY, instrucColorCode);
    drawLetter('N', startX+=40, startY, instrucColorCode);
    drawLetter('P', startX+=80, startY, instrucColorCode);
    drawLetter('O', startX+=40, startY, instrucColorCode);
    drawLetter('I', startX+=40, startY, instrucColorCode);
    drawLetter('N', startX+=40, startY, instrucColorCode);
    drawLetter('T', startX+=40, startY, instrucColorCode);
}

void gameoverDisplay() {
    drawImage(background_sky, screenWidth, screenHeight, 0, 0);
    int startX = 140;
    int startY = 100;
    // Display "GAME OVER"
    char* text = "GAME OVER";
    for (int i = 0; text[i] != '\0'; i++) {
        drawLetter(text[i], startX, startY, gameoverColorCode);
        startX += 40; // move position for next letter
    }
    // Display Score
    startX = 140;
    startY += 80;  // position below "GAME OVER"
    text = "SCORE: ";
    for (int i = 0; text[i] != '\0'; i++) {
        drawLetter(text[i], startX, startY, startColorCode);
        startX += 40; // move position for next letter
    }
    
}

void playGame() {
    int score = 0;
    //Display welcome screen
    startDisplay();
    //Wait receive any key
    while (!getUart());
    //Display instruction screen
    instructDisplay();
    char key = 0;
    //Press q to quit
    while (key != 'q') {
        //Space character ASCII Table
        if (key == 32) {

            //Game Code Here
            drawRectARGB32(0, 0, screenWidth, screenHeight, 0xFFFFFFFF, 1);




            //Add score here
            score = addscore(&score);



            //Gameover display
            if(isGameover) {
                gameoverDisplay();
            }

            key = uart_getc();
        }
        else {
            key = uart_getc();
        }
    }
    //Clear screen
    drawRectARGB32(0, 0, screenWidth, screenHeight, 0x00000000, 1);
}