#include <cmath>
#include "Turtle.hpp"

cTurtle::cTurtle()
    : m_x(0),
      m_y(0),
      m_angle(0),
      m_penDown(false),
      m_penSize(1),
      m_penColor("black"),
      m_bgColor("white")
{
}

void cTurtle::Forward(int distance)
{
    const double PI = 3.14159265358979323846;
    double rad = m_angle * PI / 180.0;

    m_x = static_cast<int>(std::round(m_x + distance * std::cos(rad)));
    m_y = static_cast<int>(std::round(m_y + distance * std::sin(rad)));
}

void cTurtle::Backward(int distance)
{
    Forward(-distance);
}

void cTurtle::Right(int angle)
{
    m_angle += angle;
    m_angle %= 360;

    if (m_angle < 0)
    {
        m_angle += 360;
    }
}

void cTurtle::Left(int angle)
{
    m_angle -= angle;
    m_angle %= 360;

    if (m_angle < 0)
    {
        m_angle += 360;
    }
}

void cTurtle::GotoXY(int x, int y)
{
    m_x = x;
    m_y = y;
}

void cTurtle::Setx(int x)
{
    m_x = x;
}

void cTurtle::Sety(int y)
{
    m_y = y;
}

void cTurtle::Home()
{
    m_x = 0;
    m_y = 0;
    m_angle = 0;
}

void cTurtle::PenUp()
{
    m_penDown = false;
}

void cTurtle::PenDown()
{
    m_penDown = true;
}

bool cTurtle::IsDown() const
{
    return m_penDown;
}

void cTurtle::PenSize(int size)
{
    if (size > 0)
    {
        m_penSize = size;
    }
}

void cTurtle::PenColor(const std::string& color)
{
    m_penColor = color;
}

void cTurtle::BgColor(const std::string& color)
{
    m_bgColor = color;
}

int cTurtle::xCordenate() const
{
    return m_x;
}

int cTurtle::yCordenate() const
{
    return m_y;
}

int cTurtle::Heading() const
{
    return m_angle;
}

std::string cTurtle::GetPenColor() const
{
    return m_penColor;
}

std::string cTurtle::GetBgColor() const
{
    return m_bgColor;
}