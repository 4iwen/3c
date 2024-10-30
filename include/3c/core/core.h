#pragma once

#include "3c/core/api.h"

#define TC_UNUSED(x) (void)(x)

namespace tc {
    class TC_API Core {
    public:
        static void init();
    };
} // namespace tc