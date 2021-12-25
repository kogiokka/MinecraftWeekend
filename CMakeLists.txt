cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

project("minecraft-weekend" VERSION 0.1.0)

add_executable(game)
add_library(glad STATIC)
add_library(noise1234 STATIC)

set_target_properties(game
    PROPERTIES
        C_STANDARD 11
        C_STANDARD_REQUIRED ON
        C_EXTENSIONS OFF
)

find_package(OpenGL REQUIRED)
include(cmake/FetchCGLM.cmake)
include(cmake/FetchGLFW.cmake)

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

target_compile_options(game PRIVATE "$<$<CONFIG:Debug>:${CompilerFlags_Debug}>")
target_compile_options(game PRIVATE "$<$<CONFIG:Release>:${CompilerFlags_Release}>")

message(STATUS "Build Type: ${CMAKE_BUILD_TYPE}")
message(STATUS "C Compiler: ${CMAKE_C_COMPILER_ID} ${CMAKE_C_COMPILER_VERSION}")

target_include_directories(game PRIVATE "lib/stb")
target_include_directories(glad PUBLIC "lib/glad/include")
target_include_directories(noise1234 PUBLIC "lib/noise")

file(GLOB_RECURSE SourceFiles CONFIGURE_DEPENDS "src/*.c")
target_sources(game PRIVATE ${SourceFiles})
target_sources(glad PRIVATE "lib/glad/src/glad.c")
target_sources(noise1234 PRIVATE "lib/noise/noise1234.c")

target_link_libraries(game PRIVATE
    cglm
    glfw
    glad
    noise1234
    OpenGL::GL
)

# NOTE: Turn on Developer Mode on MS Windows for symbolic links
add_custom_command(TARGET game POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E create_symlink
        "${CMAKE_SOURCE_DIR}/res"
        "$<TARGET_FILE_DIR:game>/res"
    DEPENDS
        "${CMAKE_SOURCE_DIR}/res"
    COMMENT "Creating symlink to project resources..."
    VERBATIM
)

include(CMakeCPack.cmake)
