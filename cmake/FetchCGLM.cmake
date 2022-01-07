include(FetchContent)

set(cglm_SOURCE_DIR "${CMAKE_SOURCE_DIR}/external/cglm")

FetchContent_Declare(
    cglm-v0.8.4
    GIT_REPOSITORY "https://github.com/recp/cglm.git"
    GIT_TAG "34e5704fe88da1e277ef4ab6c498eacfa464a391" # v0.8.4
    SOURCE_DIR "${cglm_SOURCE_DIR}"
    GIT_PROGRESS ON
)

set(FETCHCONTENT_QUIET FALSE)
if (EXISTS ${cglm_SOURCE_DIR})
    set(FETCHCONTENT_SOURCE_DIR_CGLM-V0.8.4 ${cglm_SOURCE_DIR})
endif()

option(CGLM_STATIC "CGLM static build" ON)
option(CGLM_SHARED "CGLM shared build" OFF)
FetchContent_MakeAvailable(cglm-v0.8.4)
