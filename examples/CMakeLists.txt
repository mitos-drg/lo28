cmake_minimum_required(VERSION 3.0)

# Create target <target> example
# add_executable(target target.cpp)
# set_target_properties(target PROPERTIES FOLDER dependencies)
# target_link_libraries(target PUBLIC lo28)

# Create logExample target example
add_executable(logExample logExample.cpp)
set_target_properties(logExample PROPERTIES FOLDER examples)
target_link_libraries(logExample PUBLIC lo28)