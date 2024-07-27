#include "window.hpp"

#include <string_view>

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

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "logger.hpp"

Window::Window(const int width, const int height, const std::string &title,
               const int hint_major, const int hint_minor,
               const int hint_profile, const GLFWerrorfun error_callback) {
    glfwSetErrorCallback(error_callback);

    if (!glfwInit()) {
        LOG_FATAL("GLFW - Failed to initialise, exiting...");
        std::exit(1);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, hint_major);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, hint_minor);
    glfwWindowHint(GLFW_OPENGL_PROFILE, hint_profile);

    auto profile = hint_profile == GLFW_OPENGL_CORE_PROFILE ? "core"
                   : hint_profile == GLFW_OPENGL_COMPAT_PROFILE
                       ? "compatibility"
                       : "any";
    LOG_INFO("Initialised GLFW window (with hints: OpenGL {} profile, "
             "version {}.{})",
             profile, hint_major, hint_minor);

    window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

    if (window == nullptr) {
        LOG_FATAL("GLFW - Failed to create window, terminating...");
        glfwTerminate();
        std::exit(1);
    }
}

void Window::set_icon(const std::string &path) {
    GLFWimage icon;
    int n;
    icon.pixels = stbi_load(path.c_str(), &icon.width, &icon.height, &n,
                            0); // this data gets leaked, don't tell anyone 🤫
    glfwSetWindowIcon(window, 1, &icon);
}

void Window::set_framebuf_size_callback(const GLFWframebuffersizefun callback) {
    glfwSetFramebufferSizeCallback(window, callback);
}

void Window::set_key_callback(GLFWkeyfun callback) {
    glfwSetKeyCallback(window, callback);
}

void Window::load_gl_loader() {
    glfwMakeContextCurrent(window);

    glbinding::initialize(glfwGetProcAddress, false);
    glbinding::aux::enableGetErrorCallback();
}

void Window::dump_gpu_info() {
    LOG_DEBUG("OpenGL - Version: {}, Vendor: {}, Renderer: {}",
              aux::ContextInfo::version().toString(),
              aux::ContextInfo::vendor(), aux::ContextInfo::renderer());
}

void Window::resize_callback(GLFWwindow *window, int width, int height) {
    (void)window;
    glViewport(0, 0, width, height);
    LOG_INFO("GLFW - Resized window to {}x{}", width, height);
}

void Window::handle_error(GLint error_code, const GLchar *error_message) {
    LOG_FATAL("[Code {}] - {}", error_code, error_message);
}

Window::~Window() {
    glfwTerminate();
    window = nullptr;
}
