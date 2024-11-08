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

        const std::vector<EventCallback> &getEventCallbacks() { return m_eventCallbacks; }

        void setEventCallback(const EventCallback &callback) {
            m_eventCallbacks.emplace_back(callback);
        }

        void callEventCallbacks(Event &event) {
            for (auto &callback: m_eventCallbacks) {
                callback(event);
            }
        }

        Context(Context const &) = delete;

        void operator=(Context const &) = delete;

    private:
        static Context *m_instance;

        struct ContextData {
            std::shared_ptr<Window> window;
            std::shared_ptr<Renderer> renderer;
        } m_data;

        std::vector<EventCallback> m_eventCallbacks;
    };
} // namespace tc
