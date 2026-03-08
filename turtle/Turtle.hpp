#ifndef _TURTLE_H_
#define _TURTLE_H_

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
    void forward(int distance);
    void backward(int distance);
    void right(int angle);
    void left(int angle);
    void gotoXY(int x,int y);
    void setx(int x);
    void sety(int y);
    void home();

    // pen control
    void penup();
    void pendown();
    bool isdown();
    void pensize(int size);

    // color
    void pencolor(const std::string color);
    void bgcolor(const std::string color);

    // state
    int xcordenate();
    int ycordenate();
    int heading();
};

#endif