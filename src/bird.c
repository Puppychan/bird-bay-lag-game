#include "bird.h"
// #include "framebf.h"
// #include "mylib.h"

// static position bird_position;
// // static int bird_orig_width;
// // static float bird_orig_height;
// static sizing bird_orig_size;
// static image_info current_bird_info;
// static long unsigned int* bird;
// static float bird_velocity_y = 0.0; // Vertical velocity of the bird
// const float gravity = 1.5; // The force of gravity (you might need to adjust this value)
// const float flap_strength = -15.0; // The strength of a flap (negative because it moves the bird upwards)

// void initialize_positions(float width, float height) {
//     bird_position.x = width;
//     bird_position.y = height;
// }
// void choose_bird(int bird_index, int type) {
//     // bird_index: to choose bird in bird_allArray array
//     // type: 0: small scale - 1: large scale
//     // avoid outbound
//     if (type < 0 || type > 1) {
//         type = 0;
//     }

//     switch (bird_index) {
//     case 0:
//         bird = bird_allArray[bird_index];
//         bird_orig_size.width = bird_player_info.width;
//         bird_orig_size.height = bird_player_info.height;
//         if (type == 0) {
//             current_bird_info.width = bird_orig_size.width / 6;
//             current_bird_info.height = bird_orig_size.height / 6;
//             current_bird_info.exclude_color = bird_player_info.exclude_color;
//         }
//         else {
//             // later add double size of bird for hard core
//         }
//         break;

//     default:
//         bird = bird_allArray[0];
//         break;
//     }
// }

// void clear_bird() {
//     clearImageOverlay(bird_position.x, bird_position.y, current_bird_info.width, current_bird_info.height);
// }

// void draw_bird() {
//     // Backup the current region where the bird will be drawn
//     backupRegion(bird_position.x, bird_position.y, bird_orig_size.width, bird_orig_size.height);
//     drawScaledImage(bird, bird_orig_size.width, bird_orig_size.height, current_bird_info.width, current_bird_info.height, bird_position.x, bird_position.y, current_bird_info.exclude_color);

// }

// int check_collision_with_ground(int screenHeight) {
//     return bird_position.y + current_bird_info.height >= screenHeight;
// }
// void bird_flap() {
//     bird_velocity_y = flap_strength;
// }
// void update_bird_position() {
//     bird_velocity_y += gravity; // Add gravity to the vertical velocity
//     bird_position.y += bird_velocity_y; // Update the bird's vertical position based on its velocity
// }

// void game_loop_bird(int screenHeight) {
//     const int frameRate = 60; // for 60 frames per second
//     const int frameDelay = 1000 / frameRate; // in milliseconds
//     unsigned int frameStart, frameTime;
//     clear_bird(); // Clear the current bird image
//     bird_position.x += 100;
//     draw_bird(); // Draw the bird in the new position

//     // while (1) {
//     //     frameStart = SYSTEM_TIMER_COUNTER_LOW; // get the current time in milliseconds using your specific counter.

//     //     clear_bird(); // Clear the current bird image
//     //     // update_bird_position(); // Update bird's position
//     //     bird_position.x += 100;
//     //     draw_bird(); // Draw the bird in the new position

//     //     // if (check_collision_with_ground(screenHeight)) {
//     //     //     // Handle game over or reset bird's position
//     //     //     break;
//     //     // }

//     //     frameTime = SYSTEM_TIMER_COUNTER_LOW - frameStart; // Calculate elapsed time
//     //     if (frameDelay > frameTime) {
//     //         wait_msec(frameDelay - frameTime); // or use delay(frameDelay - frameTime);
//     //     }
//     // }
// }
