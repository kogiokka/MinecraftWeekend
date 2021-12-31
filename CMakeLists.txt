cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

project("minecraft-weekend" VERSION 0.1.0)

add_executable(game)
add_library(glad STATIC)
add_library(stb_image STATIC)
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
    list(APPEND CompileOptions -Wall -Wextra -Wpedantic)
    list(APPEND CompileOptions_Debug -ggdb)
    list(APPEND CompileOptions_Release)
elseif (CMAKE_C_COMPILER_ID STREQUAL "Clang")
    list(APPEND CompileOptions -Wall -Wextra -Wpedantic)
    list(APPEND CompileOptions_Debug)
    list(APPEND CompileOptions_Release)
elseif (CMAKE_C_COMPILER_ID STREQUAL "MSVC")
    message(FATAL_ERROR "MSVC is not supported. Use MinGW on MS Windows instead.")
endif()

target_compile_options(game PRIVATE ${CompileOptions})
target_compile_options(game PRIVATE $<$<CONFIG:Debug>:${CompileOptions_Debug}>)
target_compile_options(game PRIVATE $<$<CONFIG:Release>:${CompileOptions_Release}>)

message(STATUS)
message(STATUS "Build Information")
message(STATUS "\tHost System Name:       ${CMAKE_HOST_SYSTEM_NAME}" )
message(STATUS "\tHost System Version:    ${CMAKE_HOST_SYSTEM_VERSION}" )
message(STATUS "\tHost System Processor:  ${CMAKE_HOST_SYSTEM_PROCESSOR}" )
message(STATUS)
message(STATUS "\tC Compiler:             ${CMAKE_C_COMPILER_ID} ${CMAKE_C_COMPILER_VERSION}")
message(STATUS "\tC Compiler Path:        ${CMAKE_C_COMPILER}")
message(STATUS)

target_include_directories(game PRIVATE "")

target_include_directories(glad PUBLIC "lib/glad/include")
target_include_directories(stb_image PUBLIC "lib/stb")
target_include_directories(noise1234 PUBLIC "lib/noise")

file(GLOB_RECURSE SourceFiles CONFIGURE_DEPENDS "src/*.c")
target_sources(game PRIVATE ${SourceFiles})
target_sources(glad PRIVATE "lib/glad/src/glad.c")
target_sources(stb_image PRIVATE "lib/stb/stb_image.c")
target_sources(noise1234 PRIVATE "lib/noise/noise1234.c")

target_link_libraries(game PRIVATE
    cglm
    glfw
    glad
    stb_image
    noise1234
    OpenGL::GL
)

if(MINGW)
    # This is a workaround.
    # TODO: Improve the world_foreach_* functions in src/world/world.c
    target_link_options(game PRIVATE "LINKER:--stack,4194304")
endif()

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
