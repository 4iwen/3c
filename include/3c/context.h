#pragma once

#include "3c/core/api.h"
#include "3c/window/window.h"
#include "3c/graphics/renderer.h"
#include "3c/events/event.h"

namespace tc {
    struct TC_API ContextConfig {
        struct {
            std::string title;
            uint32_t width;
            uint32_t height;
            WindowBackendType backend;
        } window;

        struct {
            GraphicsAPIType api;
        } renderer;
    };

    class TC_API Context {
    public:
        static Context *get() {
            return m_instance;
        }

        Context() = default;

        ~Context() = default;

        void init(const ContextConfig &config);

        static void shutdown();

        const std::shared_ptr<Window> &getWindow() { return m_data.window; }

        const std::shared_ptr<Renderer> &getRenderer() { return m_data.renderer; }

        void setUserEventCallback(const EventCallback &callback) {
            m_data.m_userEventCallback = callback;
        }

    private:
        void setEngineEventCallback(const EventCallback &callback) {
            m_data.m_engineEventCallback = callback;
        }

        void callEventCallbacks(Event &event);

        // window classes need to access callbacks
        friend class GlfwWindow;

    private:
        static Context *m_instance;

        struct ContextData {
            std::shared_ptr<Window> window;
            std::shared_ptr<Renderer> renderer;
            EventCallback m_engineEventCallback;
            EventCallback m_userEventCallback;
        } m_data;
    };
} // namespace tc
