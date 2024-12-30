cmake_minimum_required(VERSION 3.21)
project(3c LANGUAGES CXX)


# ------------------------------------------------ [CMake settings] -------------------------------------------------- #
set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE})

# --------------------------------------------------- [Options] ------------------------------------------------------ #
option(TC_BUILD_SHARED "Build 3c as shared library" ON)

# --------------------------------------------------- [Library] ------------------------------------------------------ #
set(
        SOURCE_FILES

        src/context.cpp
        src/core/log.cpp
        src/core/time.cpp
        src/window/window.cpp
        src/window/glfw/glfw_window.cpp
        src/input/input.cpp
        src/input/glfw/glfw_input.cpp
        src/graphics/renderer.cpp
        src/graphics/vertex_array.cpp
        src/graphics/vertex_buffer.cpp
        src/graphics/index_buffer.cpp
        src/graphics/shader.cpp
        src/graphics/texture.cpp
        src/graphics/opengl/opengl_renderer.cpp
        src/graphics/opengl/opengl_vertex_array.cpp
        src/graphics/opengl/opengl_vertex_buffer.cpp
        src/graphics/opengl/opengl_index_buffer.cpp
        src/graphics/opengl/opengl_shader.cpp
        src/graphics/opengl/opengl_texture.cpp
        src/graphics/camera/orthographic_camera.cpp
        src/graphics/camera/perspective_camera.cpp
        src/graphics/renderables/quad.cpp
)

if (TC_BUILD_SHARED)
    message(STATUS "Building 3c as shared library")
    add_library(3c SHARED ${SOURCE_FILES})
else ()
    message(STATUS "Building 3c as static library")
    add_library(3c STATIC ${SOURCE_FILES})
endif ()

# --------------------------------------------- [Compile definitions] ------------------------------------------------ #
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

set(GLM_BUILD_LIBRARY OFF)
set(GLM_BUILD_TESTS OFF)
set(GLM_BUILD_INSTALL OFF)
add_subdirectory(deps/glm) # Math

add_subdirectory(deps/stb) # Image loading

set(FASTNOISE2_NOISETOOL OFF)
set(FASTNOISE2_TESTS OFF)
add_subdirectory(deps/FastNoise2) # Noise

target_link_libraries(
        3c PRIVATE

        glfw
        glad
        spdlog
        glm
        stb
        FastNoise2
)

# --------------------------------------------- [Include directories] ------------------------------------------------ #
target_include_directories(
        3c PUBLIC

        deps/glfw/include
        deps/glad/include
        deps/spdlog/include
        deps/glm
        deps/stb
        deps/FastNoise2/include

        include
        src
)

# --------------------------------------------- [Precompiled headers] ------------------------------------------------ #
target_precompile_headers(
        3c PRIVATE

        src/pch.h
)

# ----------------------------------------------- [Compiler flags] --------------------------------------------------- #
target_compile_options(
        3c PRIVATE

        $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX /permissive- /sdl /analyze>
        $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Werror -pedantic -Wshadow -Wconversion -Wsign-conversion -Wfloat-equal>
)