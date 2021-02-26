cmake_minimum_required(VERSION 3.16)

# add cmake project
project(lo28 CXX C)

### Global dependencies and project settings ###

# Use folders in project
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Force every project to use /MT<d> flag on MSVC compiler
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

if (MSVC)

# Reduce the config types to only Debug and Release
set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "" FORCE)

# Set project binary output (in source)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/bin)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/bin)

endif()


### LO28 LIBRARY TARGET SETUP ###

# list of source files of library
set(LO28_SRC 
    src/main.cpp

    src/debug/log.h
    src/debug/assertions.h
    src/debug/logUtils.h
    src/debug/glUtils.h
    src/debug/glUtils.cpp

    src/core/Application.cpp

    src/graphics/Graphics.cpp
    src/graphics/GraphicsTypes.h
  )

# list of include files for lo28 library
set(LO28_H
    include/lo28/lo28.h

    include/lo28/core.h

    include/lo28/Application.h
    include/lo28/DataTypes.h
    include/lo28/Graphics.h
)

# add the lo28 library target
add_library(lo28 STATIC ${LO28_SRC} ${LO28_H})

# add glfw library
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

add_subdirectory(deps/glfw)

# add glad library
add_subdirectory(deps/glad)

# link all required libraries
target_link_libraries(lo28 glfw glad)

# add library include directories
target_include_directories(lo28 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

# add debug mode defines
target_compile_definitions(lo28 PUBLIC "$<$<CONFIG:DEBUG>:DEBUG>")

if (WIN32)
    target_compile_definitions(lo28 PUBLIC "WIN32")
    if (MSVC)
        target_compile_definitions(lo28 PUBLIC "_CRT_SECURE_NO_WARNINGS")
        set_property(TARGET lo28 PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
    endif()
elseif(UNIX)
    target_compile_definitions(lo28 PUBLIC "UNIX")
endif()

# structure files inside IDE projects
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${LO28_SRC} ${LO28_H})

### LO28 LIBRARY TARGET SETUP END ###

### DEPENDENCIES STRUCTURE ###

# add glad target to dependencies folder
set_target_properties(glad PROPERTIES FOLDER dependencies)

# add glfw target to dependencies folder
set_target_properties(glfw PROPERTIES FOLDER dependencies)
set_property(TARGET glfw PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")


### EXAMPLES SETUP ###

# cmake variable to enable/disable examples in project
set(LO28_BUILD_EXAMPLES ON)

if (${LO28_BUILD_EXAMPLES})

add_subdirectory(examples)

endif()