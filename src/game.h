#include "uart.h"
#include "../data/data.h"
#include "framebf.h"
#include "mylib.h"

#define mainMenu 1
#define helpMenu 2

#define playOption 1
#define helpOption 2
#define exitOption 3

void gameMenu();
void backgroundDisplay();
void displayArrow(const unsigned long *arr, int x, int y);
void deleteArrow(int x, int y);
void gameoverDisplay();
void playGame();