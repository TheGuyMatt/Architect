cmake_minimum_required(VERSION 3.17.3)

# Set C++ version to 20
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(Architect)

# Find Libraries
set (CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/modules")
find_package(SDL2 REQUIRED COMPONENTS main)
find_package(SDL2_image REQUIRED)

# Compile the Executable
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2main_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})

# Load Headers
file(GLOB_RECURSE HDRS "${CMAKE_SOURCE_DIR}/src/*.hpp")
# Load Sources
file(GLOB_RECURSE SRCS "${CMAKE_SOURCE_DIR}/src/*.cpp")

add_executable(Architect ${HDRS} ${SRCS})

target_link_libraries(Architect ${SDL2_LIBS} ${SDL2_IMAGE_LIBRARIES}) 

# Copy SDL2 DLLs to output folder on Windows
# if(WIN32)
#   foreach(DLL ${SDL2_DLLS})
#     add_custom_command(TARGET Architect POST_BUILD COMMAND
#       ${CMAKE_COMMAND} -E copy_if_different ${DLL} $<TARGET_FILE_DIR:ArchitectLinux>)
#   endforeach()
# endif()
