include(FetchContent)

set(glfw_SOURCE_DIR "${CMAKE_SOURCE_DIR}/external/glfw")

FetchContent_Declare(
    glfw
    GIT_REPOSITORY "https://github.com/glfw/glfw.git"
    GIT_TAG "7d5a16ce714f0b5f4efa3262de22e4d948851525" # tag 3.3.6
    SOURCE_DIR "${glfw_SOURCE_DIR}"
    GIT_PROGRESS ON
)

set(FETCHCONTENT_QUIET FALSE)
if (EXISTS ${glfw_SOURCE_DIR})
    set(FETCHCONTENT_SOURCE_DIR_GLFW ${glfw_SOURCE_DIR})
endif()

option(GLFW_BUILD_DOCS "GLFW documentation" OFF)
option(GLFW_BUILD_EXAMPLES "GLFW examples" OFF)
option(GLFW_BUILD_TESTS "GLFW tests" OFF)
option(GLFW_BUILD_INSTALL "GLFW installation target" OFF)
FetchContent_MakeAvailable(glfw)
