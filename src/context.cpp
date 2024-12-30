#include "pch.h"

#include "3c/context.h"
#include "3c/core/log.h"

namespace tc {
    Context *Context::m_instance = new Context();

    void Context::init(const ContextConfig &config) {
        m_instance = this;

        Log::init();

        m_data.window = Window::create(
            config.window.title,
            config.window.width,
            config.window.height,
            config.window.backend
        );

        m_data.renderer = Renderer::create(
            config.renderer.api
        );
    }

    void Context::shutdown() {
        Log::shutdown();

        delete m_instance;
        m_instance = nullptr;
    }

    void Context::callEventCallbacks(Event &event) {
        if (m_data.m_engineEventCallback) {
            m_data.m_engineEventCallback(event);
        }

        if (m_data.m_userEventCallback) {
            m_data.m_userEventCallback(event);
        }
    }
} // namespace tc
