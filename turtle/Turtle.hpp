#ifndef _TURTLE_H_
#define _TURTLE_H_

#include <string>
#include <cmath>
#include "../image/Image.hpp"

class cTurtle
{
private:
    int m_x;
    int m_y;
    int m_angle;          
    bool m_penDown;
    int m_penSize;
    cImage* m_image;

    std::string m_penColor;
    std::string m_bgColor;

    void DrawPoint(int x, int y);
    void DrawLine(int x0, int y0, int x1, int y1);

public:
    cTurtle();

    void SetImage(cImage* image);

    // movement
    void Forward(int distance);
    void Backward(int distance);
    void Right(int angle);
    void Left(int angle);
    void GotoXY(int x, int y);
    void Setx(int x);
    void Sety(int y);
    void Home();

    // pen control
    void PenUp();
    void PenDown();
    bool IsDown() const;
    void PenSize(int size);

    // color
    void PenColor(const std::string& color);
    void BgColor(const std::string& color);

    // state
    int xCordenate() const;
    int yCordenate() const;
    int Heading() const;
};

#endif