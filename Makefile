CXX = g++
CXXFLAGS = -std=c++17

SRC = main.cpp \
      image/Image.cpp \
      turtle/Turtle.cpp \
      parser/ScriptParser.cpp

TARGET = turtle_draw

SCRIPT = scripts/sample_script.txt
OUTPUT = output/output.ppm

all: build run view

build:
	$(CXX) $(SRC) -o $(TARGET)

run:
	./$(TARGET) $(SCRIPT) $(OUTPUT)

view:
	FoxViewPPM.exe $(OUTPUT)

clean:
	del $(TARGET).exe
	del $(OUTPUT)