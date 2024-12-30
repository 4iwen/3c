#pragma once

#define TC_UNUSED(x) (void)(x)

#define TC_BIND_CALLBACK(callback) \
    [this](auto&&... args) -> decltype(auto) { \
        return this->callback(std::forward<decltype(args)>(args)...); \
    }

#define TC_NOT_IMPLEMENTED() TC_ASSERT(false, "Not implemented")