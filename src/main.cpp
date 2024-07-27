#define _CRT_SECURE_NO_WARNINGS

#include <cstdlib>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <glbinding/gl/functions.h>

#include "logger.hpp"
#include "window.hpp"

auto main() -> int {
    auto log_path = std::getenv("LOG_PATH");
    if (log_path != nullptr) {
        INIT_LOG(log_path);
    }

    const int WINDOW_WIDTH = 1000;
    const int WINDOW_HEIGHT = 750;

    Window window(WINDOW_WIDTH, WINDOW_HEIGHT, "RelearnOpenGL");

    window.set_icon();

    window.set_framebuf_size_callback();
    window.set_key_callback([](GLFWwindow *window, int key, int scancode,
                               int action, int modifiers) {
        (void)window;
        (void)scancode;
        if (action == GLFW_PRESS &&
            (key == GLFW_KEY_ESCAPE ||
             (modifiers == GLFW_MOD_CONTROL && key == GLFW_KEY_Q))) {
            glfwSetWindowShouldClose(window, true);
            LOG_INFO("Window close event triggered");
        }
    });

    window.load_gl_loader();
    window.dump_gpu_info();

    while (window.is_open()) {
        // do things and stuff

        glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        window.swap_bufs();
        window.poll_events();
    }

    return 0;
}
