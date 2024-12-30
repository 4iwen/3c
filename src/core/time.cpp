#include "pch.h"

#include "3c/core/time.h"
#include "3c/core/log.h"

namespace tc {
    double Time::s_deltaTime = 0.0;

    void Time::sleep(double seconds) {
        std::this_thread::sleep_for(std::chrono::duration<double>(seconds));
    }

    Timer::Timer(): m_isRunning(false) {
    }

    void Timer::start() {
        m_startTime = std::chrono::high_resolution_clock::now();
        m_isRunning = true;
    }

    void Timer::stop() {
        if (m_isRunning) {
            m_endTime = std::chrono::high_resolution_clock::now();
            m_isRunning = false;
        }
    }

    void Timer::reset() {
        m_isRunning = false;
    }

    double Timer::getElapsedSeconds() {
        return elapsed<std::chrono::seconds>();
    }

    double Timer::getElapsedMilliseconds() {
        return elapsed<std::chrono::milliseconds>();
    }

    template<typename Duration>
    double Timer::elapsed() {
        if (m_isRunning) {
            auto now = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration<double, typename Duration::period>(now - m_startTime).count();
            return duration;
        }

        auto duration = std::chrono::duration<double, typename Duration::period>(m_endTime - m_startTime).count();
        return duration;
    }
} // namespace tc
