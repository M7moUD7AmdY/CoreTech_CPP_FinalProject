CXX = g++
CXXFLAGS = -std=c++17

SRC = main.cpp \
      image/Image.cpp \
      turtle/Turtle.cpp \
      parser/ScriptParser.cpp

TARGET = turtle_draw

all:
	$(CXX) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)