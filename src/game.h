#include "uart.h"
#include "../data/data.h"
#include "framebf.h"
#include "mylib.h"
#define DEFAULT_BACKGROUND 0
#define false 0
#define true 1

#define mainMenu 1
#define helpMenu 2
#define setBackground 3
#define setBird 4

#define playOption 1
#define helpOption 2
#define exitOption 3

extern unsigned short current_bg;
extern unsigned short is_set_bg;

void gameMenu();
void backgroundDisplay();
void birdDisplay();
void displayArrow(const unsigned long *arr, int x, int y);
void deleteArrow(int x, int y);
void gameoverDisplay();
void playGame();
void selectBackground();
void selectBird();
void setBirdStateDisplay();
void setBackgroundStateDisplay();