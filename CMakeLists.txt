cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

project("minecraft-weekend" VERSION 0.1.0 LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

find_package(OpenGL REQUIRED)

option(CGLM_STATIC "CGLM static build" ON)
option(CGLM_SHARED "CGLM shared build" OFF)
option(GLFW_BUILD_DOCS "GLFW documentation" OFF)
option(GLFW_BUILD_INSTALL "GLFW installation target" OFF)
add_subdirectory(lib/cglm)
add_subdirectory(lib/glfw)

add_executable(game-exe)
add_library(glad STATIC)
add_library(noise1234 STATIC)

if (CMAKE_C_COMPILER_ID STREQUAL "GNU")
    list(APPEND CompilerFlags -Wall -Wextra -Wpedantic)
    list(APPEND CompilerFlags_Debug -ggdb ${CompilerFlags})
    list(APPEND CompilerFlags_Release ${CompilerFlags})
elseif(CMAKE_C_COMPILER_ID STREQUAL "Clang")
    list(APPEND CompilerFlags -Wall -Wextra -Wpedantic)
    list(APPEND CompilerFlags_Debug -ggdb ${CompilerFlags})
    list(APPEND CompilerFlags_Release ${CompilerFlags})
elseif(CMAKE_C_COMPILER_ID STREQUAL "MSVC")
endif()

target_compile_options(game-exe PRIVATE "$<$<CONFIG:Debug>:${CompilerFlags_Debug}>")
target_compile_options(game-exe PRIVATE "$<$<CONFIG:Release>:${CompilerFlags_Release}>")

message(STATUS "Build Type: ${CMAKE_BUILD_TYPE}")
message(STATUS "C Compiler: ${CMAKE_C_COMPILER_ID} ${CMAKE_C_COMPILER_VERSION}")

set(ExeName "game")
set_target_properties(game-exe PROPERTIES OUTPUT_NAME ${ExeName})

target_include_directories(game-exe PRIVATE "lib/stb")
target_include_directories(glad PUBLIC "lib/glad/include")
target_include_directories(noise1234 PUBLIC "lib/noise")

file(GLOB_RECURSE SourceFiles CONFIGURE_DEPENDS "src/*.c")
target_sources(game-exe PRIVATE ${SourceFiles})
target_sources(glad PRIVATE "lib/glad/src/glad.c")
target_sources(noise1234 PRIVATE "lib/noise/noise1234.c")

target_link_libraries(game-exe PRIVATE cglm glfw glad noise1234)

if (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    target_link_libraries(game-exe PRIVATE OpenGL::OpenGL)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    target_link_libraries(game-exe PRIVATE OpenGL32)
endif()

# Turn on Developer Mode on MS Windows
add_custom_target(symlink-res
    COMMAND ${CMAKE_COMMAND} -E create_symlink
        "${CMAKE_SOURCE_DIR}/res"
        "${CMAKE_BINARY_DIR}/res"
    DEPENDS
        "${CMAKE_SOURCE_DIR}/res"
    COMMENT "Creating symlink to resources for executable: ${ExeName}."
    VERBATIM
)

add_dependencies(game-exe symlink-res)
