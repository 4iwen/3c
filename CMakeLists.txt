cmake_minimum_required(VERSION 3.21)
project(3c LANGUAGES CXX)

# ------------------------------------------------ [CMake settings] -------------------------------------------------- #
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE})
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Werror -pedantic")

# --------------------------------------------------- [Options] ------------------------------------------------------ #
option(TC_BUILD_SHARED "Build 3c as shared library" ON)

# --------------------------------------------------- [Library] ------------------------------------------------------ #
set(
        SOURCE_FILES

        src/core/core.cpp
        src/core/log.cpp
        src/window/window.cpp
)

if (TC_BUILD_SHARED)
    message(STATUS "Building 3c as shared library")
    add_library(3c SHARED ${SOURCE_FILES})
else ()
    message(STATUS "Building 3c as static library")
    add_library(3c STATIC ${SOURCE_FILES})
endif ()

# --------------------------------------------- [Compile definitions] ------------------------------------------------ #
if (CMAKE_BUILD_TYPE MATCHES "^[Dd]ebug")
    target_compile_definitions(
            3c PRIVATE

            TC_DEBUG
    )
endif ()

target_compile_definitions(
        3c PRIVATE

        TC_EXPORTS
)

if (TC_BUILD_SHARED)
    target_compile_definitions(
            3c PRIVATE

            TC_BUILD_SHARED
    )
endif ()

# ------------------------------------------------- [Properties] ----------------------------------------------------- #
set_target_properties(
        3c PROPERTIES

        C_VISIBILITY_PRESET hidden
        CXX_VISIBILITY_PRESET hidden
        VISIBILITY_INLINES_HIDDEN YES
)

# ------------------------------------------------ [Dependencies] ---------------------------------------------------- #
set(GLFW_BUILD_DOCS OFF)
set(GLFW_BUILD_EXAMPLES OFF)
set(GLFW_BUILD_TESTS OFF)
set(GLFW_INSTALL OFF)
add_subdirectory(deps/glfw) # Windowing

add_subdirectory(deps/glad) # OpenGL loader

set(SPDLOG_BUILD_EXAMPLES OFF)
set(SPDLOG_BUILD_TESTS OFF)
add_subdirectory(deps/spdlog) # Logging

target_link_libraries(
        3c PRIVATE

        glfw
        glad
        spdlog
)

# --------------------------------------------- [Include directories] ------------------------------------------------ #
target_include_directories(
        3c PUBLIC

        deps/glfw/include
        deps/glad/include
        deps/spdlog/include

        include
        src
)

# --------------------------------------------- [Precompiled headers] ------------------------------------------------ #
target_precompile_headers(
        3c PRIVATE

        src/pch.h
)