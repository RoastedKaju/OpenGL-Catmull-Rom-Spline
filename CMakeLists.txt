cmake_minimum_required(VERSION 3.21)

project(Splines)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

add_library(glad "vendor/glad/src/glad.c")
target_include_directories(glad PUBLIC "vendor/glad/include")

find_package(OpenGL REQUIRED)
add_subdirectory("vendor/glfw")
target_link_libraries(${PROJECT_NAME} PRIVATE glfw OpenGL::GL glad)