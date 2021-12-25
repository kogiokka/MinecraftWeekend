include(FetchContent)

set(cglm_SOURCE_DIR "${CMAKE_SOURCE_DIR}/lib/cglm")

FetchContent_Declare(
    cglm
    GIT_REPOSITORY "https://github.com/recp/cglm.git"
    GIT_TAG "34e5704fe88da1e277ef4ab6c498eacfa464a391" # v0.8.4
    SOURCE_DIR "${cglm_SOURCE_DIR}"
    GIT_PROGRESS ON
)

set(FETCHCONTENT_QUIET FALSE)
if (EXISTS ${cglm_SOURCE_DIR})
    set(FETCHCONTENT_SOURCE_DIR_CGLM ${cglm_SOURCE_DIR})
endif()

option(CGLM_STATIC "CGLM static build" ON)
option(CGLM_SHARED "CGLM shared build" OFF)
FetchContent_MakeAvailable(cglm)
