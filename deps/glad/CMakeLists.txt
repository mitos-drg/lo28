cmake_minimum_required(VERSION 3.0)

# add glad library to cmake creation
add_library(glad STATIC src/glad.c include/glad/glad.h)
target_include_directories(glad PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)