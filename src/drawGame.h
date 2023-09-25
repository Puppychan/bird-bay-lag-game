#include "../data/data.h"
#include "framebf.h"
#include "uart.h"
#include "mylib.h"

#define DEFAULT_BACKGROUND 0
#define DEFAULT_BIRD 0

// Constants for the game mechanics
// #define PIPES_SIZE 10
#define PIPES_SIZE 3
#define PIPE_DISTANCE 100 // make it modifiable later
#define PIPE_GAP 50 // make it modifiable later
#define PIPE_WIDTH 50 

#define PIPE_DISTANCE_MIN 170 // easy
// #define PIPE_DISTANCE_MIN 150 // easy

// #define PIPE_DISTANCE_MIN 0 // hard
// #define PIPE_DISTANCE_MAX 50 // hard
#define PIPE_TOP_MIN 70
// #define PIPE_GAP_MIN 100 // change later for expert round - increase in bird size
#define PIPE_GAP_MIN 130
#define PIPE_GAP_MAX 170


void draw_pipes();
void draw_pipe(pipe p);
void clear_pipe(pipe p);
void clear_bird();

void backup_pipe(pipe p);
void backup_bird();
void backup_game_scores();

void draw_bird(Bird bird, int width, int height);
void draw_bird_ratio(Bird bird, double scale);

void displayArrow(const unsigned long* arr, int x, int y);
void deleteArrow(int x, int y);
void helpMenuDisplay();
void mainMenuDisplay();
void gameoverDisplay();
void setBackgroundStateDisplay();
void setBirdStateDisplay();
void difficultSelectDisplay();
void endgameAnimation();
unsigned int generateColor(int x, int y);
void changeRoundDisplay();
void changeRoundRemove();

void convert_scores_to_str();
void clearGameScoresDisplay();
void gamingScoresDisplay();
