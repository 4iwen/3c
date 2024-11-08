#pragma once

#define TC_UNUSED(x) (void)(x)

#define TC_BIND_CALLBACK(function) [this](auto &&...args) { \
    return this->function(std::forward<decltype(args)>(args)...); \
}
