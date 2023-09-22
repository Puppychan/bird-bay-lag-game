#include "uart.h"
#include "../data/data.h"
#include "framebf.h"
#include "mylib.h"
#define DEFAULT_BACKGROUND 0
#define DEFAULT_BIRD 0
#define DEFAULT_BIRD_SCALE 6;
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
extern unsigned short current_bird;
extern unsigned short is_set_bird;
extern unsigned int bird_scale;

void gameMenu();
void backgroundDisplay();
void birdDisplay();
void displayArrow(const unsigned long *arr, int x, int y);
void deleteArrow(int x, int y);
void gameoverDisplay();
void playGame();
void selectBackground();
void selectBird();