cmake_minimum_required(VERSION 3.16.3)

project(RaycastEngine)

# Find Libraries
set (CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/modules")
find_package(SDL2 REQUIRED COMPONENTS main)
#find_package(SDL2_image REQUIRED)

# Add SDL libraries
#${SDL2_IMAGE_INCLUDE_DIRS}
include_directories(${SDL2_INCLUDE_DIRS})

# Load Headers
file(GLOB_RECURSE HDRS "${CMAKE_SOURCE_DIR}/src/*.h")
# Load Sources
file(GLOB_RECURSE SRCS "${CMAKE_SOURCE_DIR}/src/*.c")

add_executable(RaycastEngine ${HDRS} ${SRCS})

#${SDL2_IMAGE_LIBRARIES}
target_link_libraries(RaycastEngine m ${SDL2_LIBS})

# Copy SDL2 DLLs to output folder on Windows
if(WIN32)
      foreach(DLL ${SDL2_DLLS})
        add_custom_command(TARGET RaycastEngine POST_BUILD COMMAND
          ${CMAKE_COMMAND} -E copy_if_different ${DLL} $<TARGET_FILE_DIR:RaycastEngine>)
      endforeach()
endif()
