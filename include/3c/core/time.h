#pragma once

#include "3c/core/api.h"

namespace tc {
    class TC_API Time {
    public:
        static void sleep(double seconds);

        static double getDeltaTime() {
            return s_deltaTime;
        }

    private:
        static void setDeltaTime(double deltaTime) {
            s_deltaTime = deltaTime;
        }

        // window classes need to access setting the deltaTime
        friend class GlfwWindow;

    private:
        static double s_deltaTime;
    };

    class TC_API Timer {
    public:
        Timer();

        void start();

        void stop();

        void reset();

        double getElapsedSeconds();

        double getElapsedMilliseconds();

    private:
        template<typename Duration>
        double elapsed();

    private:
        bool m_isRunning;
        std::chrono::time_point<std::chrono::high_resolution_clock> m_startTime;
        std::chrono::time_point<std::chrono::high_resolution_clock> m_endTime;
    };
} // namespace tc
