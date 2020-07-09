# Raycast Engine
My first graphical project in C.
I have been inspired to create this program because of Wolfenstien 3D and DOOM.

This was inspired by [this video](https://www.youtube.com/watch?v=gYRrGTC7GtA), though I use SDL instead of glut.

## Requirements
### Windows (Visual Studio)
CMake expects to find the SDL2 headers and libraries in a subfolder named `extern\SDL-2.0.5`. Download [here](https://www.libsdl.org/release/SDL2-devel-2.0.5-VC.zip) and extract to the `extern` directory. Make sure the SDL2_image library is also within the `extern directory`
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
