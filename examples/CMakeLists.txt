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