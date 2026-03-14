# Turtle Drawing Engine (C++)

A C++ project that reads drawing commands from a script file and generates an image using a **turtle graphics system**.  
The generated image is saved in **PPM format** and can be viewed using **FoxViewPPM**.

This project demonstrates:
- File parsing
- Basic turtle graphics
- Image generation
- Object-oriented design in C++
- Build automation using a Makefile

## Project Overview

The program simulates a turtle drawing engine similar to the Logo programming language.

A text script contains drawing commands.  
The program reads these commands, moves a virtual turtle across a canvas, and draws lines accordingly.

The final drawing is saved as a **PPM image**.

## Workflow

```text
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
FoxViewPPM Viewer
```

### Execution Flow

1. The program reads commands from a script file.
2. `ScriptParser` interprets each command.
3. Commands control turtle movement and drawing.
4. The turtle updates pixels inside the `Image` class.
5. The image is exported as a `.ppm` file.
6. The Makefile can compile, run, and open the generated image automatically.

## Project Structure

```text
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
```

## Supported Commands

### Canvas Size

```text
size w=<width> h=<height>
```

Example:

```text
size w=512 h=512
```

### Colors

```text
color pen=<color> bg=<color>
```

Example:

```text
color pen=red bg=white
```

### Pen Control

```text
pen down x y
pen up
```

### Movement

```text
move forward <distance>
move backward <distance>
move right <angle>
move left <angle>
```

## Example Script

File: `scripts/sample_script.txt`

```text
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
```

This script generates a red square.

## Tools Needed

To build and run this project you need:

- **g++** with C++17 support
- **make**
- **FoxViewPPM** to open `.ppm` images

## Installation

### 1. Install g++

You can install MinGW-w64 or TDM-GCC on Windows.

After installation, add the compiler path to your system `PATH`.

Example path:

```text
C:\TDM-GCC-64\bin
```

Check installation:

```bash
g++ --version
```

### 2. Install make

If `make` is not available on your system, install one of these:
- GNU Make for Windows
- MSYS2
- MinGW/MSYS packages

Check installation:

```bash
make --version
```

### 3. Install FoxViewPPM

Place `FoxViewPPM.exe` in the project root folder, or make sure its path is available when running the Makefile.

## Build and Run

From the project root directory, run:

```bash
make
```

This will:
1. Compile the project
2. Execute the script file
3. Generate the output image
4. Open the image using FoxViewPPM

## Output File

The generated image is saved as:

```text
output/output.ppm
```

## Clean Generated Files

To remove build and output files:

```bash
make clean
```

This removes:
- `turtle_draw.exe`
- `output/output.ppm`

## Notes

- If the image viewer does not open, make sure `FoxViewPPM.exe` exists in the project root.
- If `make` is not recognized, install GNU Make and verify it is added to `PATH`.
- If the script file cannot be opened, check that `scripts/sample_script.txt` exists.

## Author

**Mahmoud Hamdi**  
C++ CoreTech Final Project
