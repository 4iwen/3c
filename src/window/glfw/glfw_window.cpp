#include "pch.h"

#include "3c/window/glfw/glfw_window.h"
#include "3c/core/assert.h"
#include "3c/events/window_events.h"
#include "3c/events/mouse_events.h"
#include "3c/events/key_events.h"
#include "3c/core/utils.h"
#include "3c/context.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/gl.h>

namespace tc {
    void glfwErrorCallback(int error, const char *description) {
        TC_ERROR("GLFW error ({0}): {1}", error, description);
    }

    GlfwWindow::GlfwWindow(const std::string &title, uint32_t width, uint32_t height) {
        glfwSetErrorCallback(glfwErrorCallback);

        TC_ASSERT(glfwInit(), "Failed to initialize GLFW");
        TC_INFO("Initialized GLFW");

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef TC_PLATFORM_MACOS
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
        m_windowHandle = glfwCreateWindow(
            static_cast<int32_t>(width),
            static_cast<int32_t>(height),
            title.c_str(),
            nullptr, nullptr
        );
        if (m_windowHandle == nullptr) {
            glfwTerminate();
            TC_ASSERT(false, "Failed to create window");
        }
        TC_INFO("Created window");

        glfwMakeContextCurrent(m_windowHandle);

        if (!gladLoadGL(glfwGetProcAddress)) {
            glfwTerminate();
            TC_ASSERT(false, "Failed to initialize GLAD");
        }
        TC_INFO("Initialized GLAD");

        setGlfwCallbacks();

        Context::get()->setEventCallback(TC_BIND_CALLBACK(onEvent));
    }

    GlfwWindow::~GlfwWindow() {
        glfwDestroyWindow(m_windowHandle);
        TC_INFO("Destroyed window");
        glfwTerminate();
        TC_INFO("Terminated GLFW");
    }

    void GlfwWindow::update() {
        glfwSwapBuffers(m_windowHandle);
        glfwPollEvents();
    }

    void GlfwWindow::onEvent(Event &event) {
        if (event.getType() == EventType::WINDOW_CLOSE) {
            close();
        }
    }

    void GlfwWindow::close() {
        m_isRunning = false;
    }

    bool GlfwWindow::shouldClose() {
        return !m_isRunning;
    }

    double GlfwWindow::getTimeSinceCreation() {
        return glfwGetTime();
    }

    void GlfwWindow::setGlfwCallbacks() {
        // Window events
        glfwSetWindowSizeCallback(m_windowHandle, [](GLFWwindow *window, int width, int height) {
            TC_UNUSED(window);

            WindowResizeEvent event(width, height);
            // get all the callbacks and call them
            Context::get()->callEventCallbacks(event);
        });

        glfwSetWindowCloseCallback(m_windowHandle, [](GLFWwindow *window) {
            TC_UNUSED(window);

            WindowCloseEvent event;
            Context::get()->callEventCallbacks(event);
        });

        glfwSetWindowFocusCallback(m_windowHandle, [](GLFWwindow *window, int focused) {
            TC_UNUSED(window);

            if (focused) {
                WindowFocusEvent event;
                Context::get()->callEventCallbacks(event);
            } else {
                WindowLostFocusEvent event;
                Context::get()->callEventCallbacks(event);
            }
        });

        // Key events
        glfwSetKeyCallback(m_windowHandle, [](GLFWwindow *window, int key, int scancode, int action, int mods) {
            TC_UNUSED(window);
            TC_UNUSED(scancode);
            TC_UNUSED(mods);

            switch (action) {
                case GLFW_PRESS: {
                    KeyPressedEvent event(key, 0);
                    Context::get()->callEventCallbacks(event);
                    break;
                }
                case GLFW_RELEASE: {
                    KeyReleasedEvent event(key);
                    Context::get()->callEventCallbacks(event);
                    break;
                }
                case GLFW_REPEAT: {
                    KeyPressedEvent event(key, 1);
                    Context::get()->callEventCallbacks(event);
                    break;
                }
                default: {
                    TC_ASSERT(false, "Unknown key action");
                }
            }
        });

        glfwSetCharCallback(m_windowHandle, [](GLFWwindow *window, unsigned int keycode) {
            TC_UNUSED(window);

            KeyTypedEvent event(keycode);
            Context::get()->callEventCallbacks(event);
        });

        // Mouse events
        glfwSetMouseButtonCallback(m_windowHandle, [](GLFWwindow *window, int button, int action, int mods) {
            TC_UNUSED(window);
            TC_UNUSED(mods);

            switch (action) {
                case GLFW_PRESS: {
                    MouseButtonPressedEvent event(button);
                    Context::get()->callEventCallbacks(event);
                    break;
                }
                case GLFW_RELEASE: {
                    MouseButtonReleasedEvent event(button);
                    Context::get()->callEventCallbacks(event);
                    break;
                }
                default: {
                    TC_ASSERT(false, "Unknown mouse action");
                }
            }
        });

        glfwSetCursorPosCallback(m_windowHandle, [](GLFWwindow *window, double xPos, double yPos) {
            TC_UNUSED(window);

            MouseMovedEvent event(static_cast<float>(xPos), static_cast<float>(yPos));
            Context::get()->callEventCallbacks(event);
        });

        glfwSetScrollCallback(m_windowHandle, [](GLFWwindow *window, double xOffset, double yOffset) {
            TC_UNUSED(window);

            MouseScrolledEvent event(static_cast<float>(xOffset), static_cast<float>(yOffset));
            Context::get()->callEventCallbacks(event);
        });
    }
} // namespace tc
