#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

#include "ScriptParser.hpp"
#include "../turtle/Turtle.hpp"
#include "../image/Image.hpp"

using namespace std;

void LineParsing(const string& line, cTurtle& turtle, cImage& image)
{
    if (line.empty() || line[0] == '#')
    {
        return;
    }

    stringstream ss(line);
    string command;
    ss >> command;

    if (command == "size")
    {
        string wToken, hToken;
        ss >> wToken >> hToken;

        int width = 0, height = 0;

        size_t pos = wToken.find('=');
        if (pos != string::npos)
        {
            width = stoi(wToken.substr(pos + 1));
        }
        else
        {
            cout << "Invalid size command\n";
            return;
        }

        pos = hToken.find('=');
        if (pos != string::npos)
        {
            height = stoi(hToken.substr(pos + 1));
        }
        else
        {
            cout << "Invalid size command\n";
            return;
        }

        image.Resize(width, height);

        cout << "SIZE -> width = " << width
             << ", height = " << height << endl;
    }
    else if (command == "color")
    {
        string penToken, bgToken;
        ss >> penToken >> bgToken;

        string penColor, bgColor;

        size_t pos = penToken.find('=');
        if (pos != string::npos)
        {
            penColor = penToken.substr(pos + 1);
        }
        else
        {
            cout << "Invalid color command\n";
            return;
        }

        pos = bgToken.find('=');
        if (pos != string::npos)
        {
            bgColor = bgToken.substr(pos + 1);
        }
        else
        {
            cout << "Invalid color command\n";
            return;
        }

        turtle.PenColor(penColor);
        turtle.BgColor(bgColor);

        cout << "COLOR -> pen = " << penColor
             << ", bg = " << bgColor << endl;
    }
    else if (command == "pen")
    {
        string state;
        ss >> state;

        if (state == "down")
        {
            int x, y;
            ss >> x >> y;

            turtle.PenDown();
            turtle.GotoXY(x, y);

            cout << "PEN -> state = down, x = " << x
                 << ", y = " << y << endl;
        }
        else if (state == "up")
        {
            turtle.PenUp();
            cout << "PEN -> state = up" << endl;
        }
        else
        {
            cout << "Invalid pen command\n";
            return;
        }
    }
    else if (command == "move")
    {
        string direction;
        int value;

        ss >> direction >> value;

        if (direction == "forward")
        {
            turtle.Forward(value);
        }
        else if (direction == "backward")
        {
            turtle.Backward(value);
        }
        else if (direction == "right")
        {
            turtle.Right(value);
        }
        else if (direction == "left")
        {
            turtle.Left(value);
        }
        else
        {
            cout << "Invalid move command\n";
            return;
        }

        cout << "MOVE -> direction = " << direction
             << ", value = " << value << endl;
    }
    else
    {
        cout << "Unknown command: " << command << endl;
    }
}