#include "./ncug.h"
#define STB_IMAGE_IMPLEMENTATION
#include "../stb_image.h"

struct mouse global_mouse;
struct keyboard keys = {0};

double ncug_delta_time(double current_time)
{
        static double last_frame;

        double delta_time = last_frame - current_time;
        last_frame = current_time;

        return delta_time;
}

// ------- KEYBOARD SECTION


void key_callback(GLFWwindow *pWindow, int key, int scancode, int action, int mods)
{
        switch (action) {
                case GLFW_PRESS:
                        keys.keys[key] = GLFW_PRESS;
                        break;

                case GLFW_RELEASE:
                        keys.keys[key] = GLFW_RELEASE;
                        break;

                default:
                        break;
        }
}

struct keyboard *ncug_keyboard_create(GLFWwindow *pWindow)
{
        glfwSetKeyCallback(pWindow, key_callback);
        return &keys;
}


// ------- KEYBOARD SECTION


// ------- MOUSE SECTION
void cursor_position_callback(GLFWwindow *pWindow, double xpos, double ypos)
{
        global_mouse.xpos = xpos;
        global_mouse.ypos = ypos;
}

void scroll_position_callback(GLFWwindow *pWindow, double xscroll, double yscroll)
{
        global_mouse.xscroll = xscroll;
        global_mouse.yscroll = yscroll;
}

void cursor_entered_callback(GLFWwindow *pWindow, int entered)
{
        global_mouse.cursor_enter = entered;
}

void mouse_button_callback(GLFWwindow *pWindow, int button, int state, int mods)
{
        switch (button) {
                case GLFW_MOUSE_BUTTON_4:  
                        global_mouse.button0 = state;
                        break;
                case GLFW_MOUSE_BUTTON_5:  
                        global_mouse.button1 = state;
                        break;
                case GLFW_MOUSE_BUTTON_6:
                        global_mouse.button2 = state;
                        break;
                case GLFW_MOUSE_BUTTON_7:
                        global_mouse.button3 = state;
                        break;
                case GLFW_MOUSE_BUTTON_8:
                        global_mouse.button4 = state;
                        break;
                case GLFW_MOUSE_BUTTON_LEFT:
                        global_mouse.button_left = state;
                        break;
                case GLFW_MOUSE_BUTTON_RIGHT:  
                        global_mouse.button_right = state;
                        break;
                case GLFW_MOUSE_BUTTON_MIDDLE: 
                        global_mouse.button_middle = state;
                        break;
        }
}

struct mouse *ncug_mouse_create(GLFWwindow *pWindow, struct mouse_config config)
{
        if (glfwRawMouseMotionSupported() && config.raw_input) {
                glfwSetInputMode(pWindow, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);

        } else {
                glfwSetInputMode(pWindow, GLFW_CURSOR, config.input_mode);
        }

        // callbacks
        glfwSetCursorPosCallback(pWindow, cursor_position_callback);
        glfwSetCursorEnterCallback(pWindow, cursor_entered_callback);
        glfwSetMouseButtonCallback(pWindow, mouse_button_callback);
        glfwSetScrollCallback(pWindow, scroll_position_callback);

        return &global_mouse;
}

GLFWcursor* ncug_cursor_create(char pPath[static 1], int channels)
{
        int comp; // useless for now ig?
        GLFWimage cursor_image;

        uint8_t* image = stbi_load(pPath, &cursor_image.width, &cursor_image.height, &comp, channels);

        cursor_image.pixels = image;
        GLFWcursor* cursor = glfwCreateCursor(&cursor_image, 0, 0);
        stbi_image_free(image);
        return cursor;
}
// ------- MOUSE SECTION
