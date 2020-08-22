![](coke.png)
# Basic-Libtorch-DLL
A "Hello World" example for building a DLL using Libtorch. This example runs Style Transfer on a live video feed, and is designed to work with `Unreal Engine`.

## About
This is one of two repositories which are required to build this project:
- [basic-unreal-libtorch-plugin](https://github.com/NeuralVFX/basic-unreal-libtorch-plugin)
- [basic-libtorch-dll](https://github.com/NeuralVFX/basic-libtorch-dll) - You are here.

This runs on CPU(I don't own a GPU), however with only minor changes I believe this should work on GPU.

## Requirements:
- Cmake
- Visual Studio
- OpenCV 4.1
- LibTorch 1.5

## Project Setup
- Open `vision.cpp` and replace the `traced_style_transfer_model.pt` path to match the path on your system
- Open `build/CMakeLists.txt` and replace the directories `Torch_DIR`, `OpenCV_DIR`, `OpenCV_INC_DIR` and `OpenCV_LIB_DIR`
- Run these commands to build the project(replace `DCMAKE_PREFIX_PATH` with your libtorch install directory):
```
cmake ./build -DCMAKE_PREFIX_PATH=C:\libtorch -DCMAKE_GENERATOR_PLATFORM=x64  ..cmake --build . --config Release
cmake --build . --config Release
```
- This should generate a Visual Studio Project and a file called `Release/export_wrapper.dll`
- Copy this file wherever you need!

