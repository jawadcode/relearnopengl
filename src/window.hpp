#ifndef RELEARNOPENGL_WINDOW_HPP
#define RELEARNOPENGL_WINDOW_HPP

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <glbinding/CallbackMask.h>
#include <glbinding/FunctionCall.h>
#include <glbinding/Version.h>
#include <glbinding/glbinding.h>

#include <glbinding/getProcAddress.h>
#include <glbinding/gl/gl.h>

#include <glbinding-aux/ContextInfo.h>
#include <glbinding-aux/Meta.h>
#include <glbinding-aux/ValidVersions.h>
#include <glbinding-aux/debug.h>
#include <glbinding-aux/types_to_string.h>

using namespace gl;
using namespace glbinding;

class Window {
  public:
    Window(const int width, const int height,
           const std::string &title = "GLFW Window", const int hint_major = 3,
           const int hint_minor = 3,
           const int hint_profile = GLFW_OPENGL_CORE_PROFILE,
           const GLFWerrorfun error_callback = handle_error);

    void set_icon(const std::string &path = "assets/icon.png");

    void set_framebuf_size_callback(
        const GLFWframebuffersizefun callback = resize_callback);

    void set_key_callback(GLFWkeyfun callback);

    void load_gl_loader();

    void dump_gpu_info();

    inline bool is_open() { return !glfwWindowShouldClose(window); }

    inline void swap_bufs() { glfwSwapBuffers(window); }

    inline void poll_events() { glfwPollEvents(); }

    ~Window();

  private:
    GLFWwindow *window;
    int width;
    int height;

    // A good default framebuffer resize callback
    static void resize_callback(GLFWwindow *window, int width, int height);

    // A good default error handler
    static void handle_error(GLint error_code, const GLchar *error_message);
};

#endif
