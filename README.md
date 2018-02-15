# FSE : Fast and Simple Engine

This is a simple real-time 3D engine who actually provide some basic features easily.

You can:
  - Load mesh (.obj, .fbx, .3ds, ...)
  - Place and control a camera.
  - Apply texture on mesh
  - Place lights
  - Use your own shader, or the default shader

# Linux

First you need to install all dependencies :

```
sudo apt update
sudo apt install libgles2-mesa-dev libsdl2-dev libglm-dev libglew-dev libassimp-dev libbullet-dev cmake
```

Now you can configure the project :

```
mkdir build; cd build;
cmake ..
```

Then copy the library on your system (assuming you are in the project folder) :
```
sudo cp include /usr/
sudo cp build/libfse.so /usr/lib/
```

# Use

To link the library use
```
-lfse
```

# Windows

On Windows you will need to have all dependencies installed/build in your environment (or -DVAR_NAME="")

Those variables needs to be set:
    - SDL2_PATH
    - ASSIMP_ROOT_DIR
    - GLM_ROOT_DIR
    - GLEW_LOCATION
    - BULLET_ROOT

Use CMake GUI or open the project in a shell and type:
```
mkdir build
cd build
cmake .. -G "Visual Studio 15 Win64" -DSDL2_PATH="..."
```

Finally open the generated project on Visual Studio to compile the library.

Two file will be generated, the dll and it's import library :
    - fse.dll
    - fse.lib

Erwan Daniel
