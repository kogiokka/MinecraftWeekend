cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

project("minecraft-weekend" VERSION 0.1.0 LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(CMAKE_THREAD_LIBS_INIT "-lpthread")
set(CMAKE_HAVE_THREADS_LIBRARY 1)
set(CMAKE_USE_WIN32_THREADS_INIT 0)
set(CMAKE_USE_PTHREADS_INIT 1)
set(THREADS_PREFER_PTHREAD_FLAG ON)

find_package(OpenGL REQUIRED)
add_subdirectory(lib/cglm)
add_subdirectory(lib/glfw)

add_executable(GameExe)
add_library(glad)
add_library(noise1234)

if (CMAKE_C_COMPILER_ID STREQUAL "GNU")
    list(APPEND CompilerFlags -Wall -Wextra -Wpedantic)
    list(APPEND CompilerFlags_Debug -ggdb ${CompilerFlags})
    list(APPEND CompilerFlags_Release -O3 ${CompilerFlags})
elseif(CMAKE_C_COMPILER_ID STREQUAL "Clang")
    list(APPEND CompilerFlags -Wall -Wextra -Wpedantic)
    list(APPEND CompilerFlags_Debug -ggdb ${CompilerFlags})
    list(APPEND CompilerFlags_Release -O3 ${CompilerFlags})
elseif(CMAKE_C_COMPILER_ID STREQUAL "MSVC")
endif()

target_compile_options(GameExe PRIVATE "$<$<CONFIG:Debug>:${CompilerFlags_Debug}>")
target_compile_options(GameExe PRIVATE "$<$<CONFIG:Release>:${CompilerFlags_Release}>")

message(STATUS "Build Type: ${CMAKE_BUILD_TYPE}")
message(STATUS "C Compiler: ${CMAKE_C_COMPILER_ID} ${CMAKE_C_COMPILER_VERSION}")

set(ExeName "game")
set_target_properties(GameExe PROPERTIES OUTPUT_NAME ${ExeName})

target_include_directories(GameExe PRIVATE "lib/stb")
target_include_directories(glad PUBLIC "lib/glad/include")
target_include_directories(noise1234 PUBLIC "lib/noise")

file(GLOB_RECURSE SourceFiles CONFIGURE_DEPENDS "src/*.c")
target_sources(GameExe PRIVATE ${SourceFiles})
target_sources(glad PRIVATE "lib/glad/src/glad.c")
target_sources(noise1234 PRIVATE "lib/noise/noise1234.c")

target_link_libraries(GameExe PRIVATE cglm glfw glad noise1234)

if (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    target_link_libraries(GameExe PRIVATE OpenGL::OpenGL)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    target_link_libraries(GameExe PRIVATE OpenGL32)
endif()

# Turn on Developer Mode on MS Windows
add_custom_target(ActionSymlinkRes
    COMMAND ${CMAKE_COMMAND} -E create_symlink
        "${CMAKE_SOURCE_DIR}/res"
        "${CMAKE_BINARY_DIR}/res"
    DEPENDS
        "${CMAKE_SOURCE_DIR}/res"
    COMMENT "Creating symlink to resources for executable: ${ExeName}."
    VERBATIM
)

add_dependencies(GameExe ActionSymlinkRes)
