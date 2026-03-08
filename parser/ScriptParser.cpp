#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

#include "ScriptParser.hpp"

using namespace std;

//[need to add some error handling]

void LineParsing(const string line)
{
    //early Exit 
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
            cout << "Invalid  command" << endl;

        }

        pos = hToken.find('=');
        if (pos != string::npos)
        {
            height = stoi(hToken.substr(pos + 1));

        } 
        else
        {
            cout << "Invalid  command" << endl;

        }

        cout << "SIZE -> width = " << width<< ", height = " << height << endl;
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
            cout << "Invalid  command" << endl;

        }

        pos = bgToken.find('=');
        if (pos != string::npos)
        {
            bgColor = bgToken.substr(pos + 1);
        } 
        else
        {
            cout << "Invalid  command" << endl;

        }

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
            cout << "PEN -> state = down, x = " << x
                 << ", y = " << y << endl;
        }
        else if (state == "up")
        {
            cout << "PEN -> state = up" << endl;
        }
        else
        {
            cout << "Invalid  command" << endl;
        }
    }
    else if (command == "move")
    {
        string direction,distance;
        int Distance;

        ss >> direction >> distance;
        Distance=stoi(distance);

        cout << "MOVE -> direction = " << direction
             << ", distance = " << distance << endl;
    }
    else
    {
        cout << "Unknown command: " << command << endl;
    }
}
