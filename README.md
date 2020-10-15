# Raycast Engine
My first graphical project in C.
I have been inspired to create this program because of Wolfenstien 3D and DOOM.

This was inspired by [this video](https://www.youtube.com/watch?v=gYRrGTC7GtA), though I use SDL instead of glut.

## Requirements
### Windows
It is a bit more difficult to get working on windows. Depending on wether you are using Visual Studio, MinGW, or another compiler the process will vary. If you are using CMake to help compile the project, you need to add two CMake variables named SDL2_DIR and SDL2_IMAGE_DIR pointing to the directories where you downloaded SDL2 and SDL2_image. After that, you need tocopy the dll files from each of the library's bin folders.
### MacOS (Xcode)
Install the SDL2 and SDL2_image headers and libraries using [MacPorts](https://www.macports.org/)

  sudo port install libsdl2 libsdl2_image

### Linux
Install the SDL2 headers and libraries using your package manager.

For example, in Arch Linux run:
```
sudo pacman -S sdl2 sdl2_image
```
## Build Instructions
Clone this repository:
```
git clone https://github.com/TheGuyMatt/RaycastEngine
```
Build the project:
```
cd RaycastEngine
mkdir build
cd build
cmake ..
make
```

For specific instructions on Visual Studio, Xcode, or another platform, please see the [CMake Documentation](https://cmake.org/documentation/).
