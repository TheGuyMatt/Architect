# Architect
A 2D game engine written in C++ using the SDL2 libraries.

## Requirements
### Windows (Visual Studio)
CMake expects to find the SDL2 headers and libraries in a subfolder named `extern\SDL-2.0.5`. Download [here](https://www.libsdl.org/release/SDL2-devel-2.0.5-VC.zip) and extract to the `extern` directory.
Make sure the SDL2_image library is also within the `extern directory`

### MacOS (Xcode)
Install the SDL2 and SDL2_image headers and libraries using [MacPorts](https://www.macports.org/)

    sudo port install libsdl2 libsdl2_image

### Linux
Install the SDL2 headers and libraries using your package manager.

For example, in Arch Linux run:

    sudo pacman -S sdl2 sdl2_image

## Build Instructions
Clone this repository:

    git clone https://github.com/TheGuyMatt/Architect

Build the project:
```
cd Architect
mkdir build
cd build
cmake ..
make
```
You should now have your executable. For specific instructions on Visual Studio or Xcode, please see the [CMake Documentation](https://cmake.org/documentation/).
