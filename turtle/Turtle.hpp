#ifndef _TURTLE_H_
#define _TURTLE_H_
#include <string>


class cTurtle
{
private:

    int m_x;
    int m_y;
    int am_ngle;
    bool m_penDown;
    int m_penSize;
    std::string m_penColor;
    std::string m_bgColor;

public:

    cTurtle();

    // movement
    void Forward(int distance);
    void Backward(int distance);
    void Right(int angle);
    void Left(int angle);
    void GotoXY(int x,int y);
    void Setx(int x);
    void Sety(int y);
    void Home();

    // pen control
    void PenUp();
    void PenDown();
    bool IsDown();
    void PenSize(int size);

    // color
    void PenColor(const std::string color);
    void BgColor(const std::string color);

    // state
    int xCordenate();
    int yCordenate();
    int Heading();
};

#endif