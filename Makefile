CXX = g++
CXXFLAGS = -std=c++17 

SRC = main.cpp \
      image/Image.cpp \
      turtle/Turtle.cpp \
      parser/ScriptParser.cpp


TARGET = turtle_draw.exe

SCRIPT = scripts/sample_script.txt
OUTPUT = output/output.ppm

FOX = FoxViewPPM.exe

all: build run view

Build:
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

run: build
	.\$(TARGET) $(SCRIPT) $(OUTPUT)

view: run
	$(FOX) $(OUTPUT)

clean:
	del /Q $(TARGET)
	del /Q $(OUTPUT)