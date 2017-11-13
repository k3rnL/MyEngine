# FSE : Fast and Simple Engine

This is a simple real-time 3D engine who actually provide some basic features easily.

You can:
  - Load mesh (.obj, .fbx, .3ds, ...)
  - Place and control a camera.
  - Apply texture on mesh
  - Place lights
  - Use your own shader, or the default shader

# Installation

First you need to install all dependencies :

```
sudo apt update
sudo apt install libgles2-mesa-dev libsdl2-dev libglm-dev libglew-dev libassimp-dev
```

Now you can compile the library and install it :

```
sudo make lib install
```

# Use

To link the library use
```
-lmxe
```



Erwan Daniel
