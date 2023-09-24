typedef struct {
    float x, y;   // Position
    float vertical_velocity;     // Vertical velocity
} Bird;

typedef struct {
    int x;
    int y;
} position;

// Pipe struct
typedef struct {
    position top;
    position bottom;
} pipe;

typedef struct {
    unsigned int width;
    unsigned int height;
} sizing;

typedef enum {
    LEFT, RIGHT, TOP, BOTTOM, TOP_LEFT, TOP_RIGHT, BOTTOM_LEFT, BOTTOM_RIGHT
} direction;

typedef struct {
    unsigned int width;
    unsigned int height;
    unsigned int exclude_color;
} image_info;