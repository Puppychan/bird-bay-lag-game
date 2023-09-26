typedef struct {
    float x, y;   // Position
    float vertical_velocity;     // Vertical velocity
} Bird;

typedef struct {
    unsigned int width;
    unsigned int height;
} sizing;

typedef struct {
    int x;
    int y;
    sizing size;
} position;

// Pipe struct
typedef struct {
    position top;
    position bottom;
    int display_index; // for choosing which image to display
    int type; // type: 0 - pipe, 1 - balloon
} pipe;

typedef enum {
    LEFT, RIGHT, TOP, BOTTOM, TOP_LEFT, TOP_RIGHT, BOTTOM_LEFT, BOTTOM_RIGHT
} direction;

typedef struct {
    unsigned int width;
    unsigned int height;
    unsigned int exclude_color;
} image_info;