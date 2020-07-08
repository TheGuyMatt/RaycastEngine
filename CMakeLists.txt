cmake_minimum_required(VERSION 3.17.3)

project(RaycastEngine)

# Find Libraries
set (CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/modules")
find_package(SDL2 REQUIRED COMPONENTS main)
find_package(SDL2_image REQUIRED)

# Add SDL libraries
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2main_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})

# Load Headers
file(GLOB_RECURSE HDRS "${CMAKE_SOURCE_DIR}/src/*.h")
# Load Sources
file(GLOB_RECURSE SRCS "${CMAKE_SOURCE_DIR}/src/*.c")

add_executable(RaycastEngine ${HDRS} ${SRCS})

target_link_libraries(RaycastEngine ${SDL2_LIBS} ${SDL2_IMAGE_LIBRARIES}) 
