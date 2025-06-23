cmake_minimum_required(VERSION 3.14)

project(RTSGame)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
SET(CMAKE_CXX_EXTENSIONS OFF)

IF (CMAKE_BUILD_TYPE STREQUAL "Debug")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
ENDIF()

include(FetchContent)

# GLFW
FetchContent_Declare(
  glfw
  GIT_REPOSITORY https://github.com/glfw/glfw.git
  GIT_TAG 3.3.8
)
FetchContent_MakeAvailable(glfw)

# GLAD
FetchContent_Declare(
  glad
  GIT_REPOSITORY https://github.com/Dav1dde/glad.git
  GIT_TAG v0.1.36
)
FetchContent_MakeAvailable(glad)

# GLM (Math)
FetchContent_Declare(
  glm
  GIT_REPOSITORY https://github.com/g-truc/glm.git
  GIT_TAG 0.9.9.8
)
FetchContent_MakeAvailable(glm)
SET_TARGET_PROPERTIES(glm PROPERTIES CXX_STANDARD 20)

# STB Image
FetchContent_Declare(
  stb
  GIT_REPOSITORY https://github.com/nothings/stb.git
  GIT_BRANCH master
)
FetchContent_MakeAvailable(stb)

# Sources
FILE(GLOB_RECURSE SOURCES "src/*.cpp" "main.cpp")

ADD_EXECUTABLE(${PROJECT_NAME} ${SOURCES})

ADD_LIBRARY(stb_image INTERFACE)
TARGET_INCLUDE_DIRECTORIES(stb_image INTERFACE ${stb_SOURCE_DIR})

TARGET_LINK_LIBRARIES(
    ${PROJECT_NAME}
    PRIVATE
    glfw
    glad
    glm
    stb_image)

TARGET_INCLUDE_DIRECTORIES(
    ${PROJECT_NAME}
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${glfw_SOURCE_DIR}/include
    ${glad_SOURCE_DIR}/include
    ${glm_SOURCE_DIR}
)

# MacOS-specific frameworks
IF(APPLE)
    TARGET_LINK_LIBRARIES(
        ${PROJECT_NAME}
        PRIVATE
        "-framework OpenGL"
        "-framework Cocoa"
        "-framework IOKit"
        "-framework CoreVideo"
    )
ENDIF()

# macOS specific frameworks
#IF (${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Darwin")
#    TARGET_LINK_LIBRARIES(
#        ${PROJECT_NAME}
#        PRIVATE
#        "-framework Cocoa"
#        "-framework IOKit"
#        "-framework CoreFoundation"
#        "-framework CoreVideo"
#        "-framework AudioToolbox"
#        "-framework CoreAudio"
#        "-framework AVFoundation"
#        "-framework GameController"
#        "-framework Metal"
#        "-framework Foundation"
#        "-framework ForceFeedback"
#        "-framework CoreHaptics"
#        "-framework Carbon"
#    )
#ENDIF()

# Assets (copy to build directory)
SET(ASSETS_SOURCE_DIR "${CMAKE_SOURCE_DIR}/assets")
SET(ASSETS_DEST_DIR "${CMAKE_BINARY_DIR}/assets")
ADD_CUSTOM_COMMAND(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${ASSETS_SOURCE_DIR} ${ASSETS_DEST_DIR}
)

MESSAGE(STATUS "C++ standard set to: ${CMAKE_CXX_STANDARD}")