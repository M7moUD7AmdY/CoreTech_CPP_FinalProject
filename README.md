
Turtle Drawing Engine (C++)

A C++ project that reads drawing commands from a script file and generates an image using a turtle graphics system.
The generated image is saved in PPM format and can be viewed using FoxViewPPM.

Project Overview
----------------
The program simulates a turtle drawing engine similar to the Logo programming language.

A text script contains drawing commands.
The program reads these commands, moves a virtual turtle across a canvas, and draws lines accordingly.

The final drawing is saved as a PPM image.

Workflow
--------
Script File
    ↓
Script Parser
    ↓
Turtle Engine
    ↓
Image Buffer
    ↓
PPM Image File
    ↓
Image Viewer (FoxViewPPM)

Steps:
1. The program reads commands from a script file.
2. ScriptParser interprets each command.
3. Commands control turtle movement and drawing.
4. The turtle updates pixels inside the Image class.
5. The image is exported as a .ppm file.
6. The Makefile opens the image automatically using FoxViewPPM.

Project Structure
-----------------
CoreTech_CPP_FinalProject
│
├── main.cpp
│
├── image
│   ├── Image.cpp
│   └── Image.hpp
│
├── turtle
│   ├── Turtle.cpp
│   └── Turtle.hpp
│
├── parser
│   ├── ScriptParser.cpp
│   └── ScriptParser.hpp
│
├── scripts
│   └── sample_script.txt
│
├── output
│
├── Makefile
│
└── FoxViewPPM.exe

Example Script
--------------
size w=512 h=512
color pen=red bg=white
pen down 256 256
move forward 100
move right 90
move forward 100
move right 90
move forward 100
move right 90
move forward 100

This script generates a red square.

Supported Commands
------------------

Canvas Size
size w=<width> h=<height>

Example:
size w=512 h=512

Colors
color pen=<color> bg=<color>

Example:
color pen=blue bg=white

Pen Control
pen down x y
pen up

Movement
move forward <distance>
move backward <distance>
move right <angle>
move left <angle>

Requirements
------------
To run this project you need:

- C++17 compatible compiler (g++)
- Make
- FoxViewPPM image viewer

Installing Tools
----------------

Install GCC:
https://www.mingw-w64.org/downloads/

Verify installation:
g++ --version

Install Make:
Use MSYS2 or GNU Make for Windows

Verify:
make --version

Build and Run
-------------
From the project directory run:

make

The Makefile will:
1. Compile the project
2. Run the program
3. Generate the PPM image
4. Open the image using FoxViewPPM

Output
------
Generated image:
output/output.ppm

Cleaning Build Files
--------------------
make clean

This removes:
turtle_draw.exe
output/output.ppm

Author
------
Mahmoud Hamdi
C++ CoreTech Final Project
