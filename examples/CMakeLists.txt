cmake_minimum_required(VERSION 3.16)

# Global examples settings

# Force every project to use /MT<d> flag on MSVC compiler
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

# Create <target> target example
# add_executable(<target> <target>.cpp)
# set_target_properties(<target> PROPERTIES FOLDER examples)
# target_link_libraries(<target> PUBLIC lo28)

# Create template target example
add_executable(template template.cpp)
set_target_properties(template PROPERTIES FOLDER examples)
target_link_libraries(template PUBLIC lo28)

# Create template target example
add_executable(demo demo.cpp)
set_target_properties(demo PROPERTIES FOLDER examples)
target_link_libraries(demo PUBLIC lo28)

# Create choinka target example
add_executable(choinka choinka.cpp)
set_target_properties(choinka PROPERTIES FOLDER examples)
target_link_libraries(choinka PUBLIC lo28)

# Create circles target example
add_executable(circles circles.cpp)
set_target_properties(circles PROPERTIES FOLDER examples)
target_link_libraries(circles PUBLIC lo28)