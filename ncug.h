#ifndef NCUG_H
#define NCUG_H

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "../glfw3.h"

#ifdef __cplusplus__
extern "C" {
#endif

                // GENERAL STUFF

double get_delta_time(double current_time);

typedef enum {
        RELEASE = GLFW_RELEASE,
        PRESSED = GLFW_PRESS,
        REPEAT = GLFW_REPEAT
}key;
                // GENERAL STUFF

                        // MOUSE SECTION
enum cursor_state {
        DEFAULT,
        CLICK,
        HOVERING
};

struct mouse_config {
        bool raw_input;
        int input_mode;
};

GLFWcursor* cursor_create(char *pPath, int channels);



struct mouse {
        double xpos;
        double ypos;
        double xscroll;
        double yscroll;
        int cursor_enter;

        key button_left;
        key button_right;
        key button_middle;

        key button0;
        key button1;
        key button2;
        key button3;
        key button4;
};

struct mouse *mouse_create(GLFWwindow *pWindow, struct mouse_config config);
                        // MOUSE SECTION


                        // KEYBOARD SECTION

bool key_held(GLFWwindow *pWindow, int key_code);

                        // KEYBOARD SECTION

#ifdef __cplusplus__
}
#endif


#endif // NCUG_H
