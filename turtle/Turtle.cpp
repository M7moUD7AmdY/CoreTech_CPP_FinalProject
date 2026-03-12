#include "Turtle.hpp"
#include <cstdlib>

namespace
{
    constexpr double PI = 3.14159265358979323846;
}

cTurtle::cTurtle()
    : m_x(0),
      m_y(0),
      m_angle(0),
      m_penDown(false),
      m_penSize(1),
      m_image(nullptr),
      m_penColor("red"),
      m_bgColor("white")
{
}

void cTurtle::SetImage(cImage* image)
{
    m_image = image;
    if (m_image != nullptr)
    {
        m_image->Fill(m_bgColor);
    }
}

void cTurtle::DrawPoint(int x, int y)
{
    if (m_image == nullptr)
    {
        return;
    }

    const int half = m_penSize / 2;

    for (int dy = -half; dy <= half; ++dy)
    {
        for (int dx = -half; dx <= half; ++dx)
        {
            m_image->SetPixel(x + dx, y + dy, m_penColor);
        }
    }
}

void cTurtle::DrawLine(int x0, int y0, int x1, int y1)
{
    if (m_image == nullptr)
    {
        return;
    }

    int dx = std::abs(x1 - x0);
    int dy = std::abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;

    while (true)
    {
        DrawPoint(x0, y0);

        if (x0 == x1 && y0 == y1)
        {
            break;
        }

        const int e2 = 2 * err;

        if (e2 > -dy)
        {
            err -= dy;
            x0 += sx;
        }

        if (e2 < dx)
        {
            err += dx;
            y0 += sy;
        }
    }
}

void cTurtle::Forward(int distance)
{
    const int x0 = m_x;
    const int y0 = m_y;

    const double rad = m_angle * PI / 180.0;
    const int x1 = static_cast<int>(std::lround(m_x + distance * std::cos(rad)));
    const int y1 = static_cast<int>(std::lround(m_y + distance * std::sin(rad)));

    if (m_penDown && m_image != nullptr)
    {
        DrawLine(x0, y0, x1, y1);
    }

    m_x = x1;
    m_y = y1;
}

void cTurtle::Backward(int distance)
{
    Forward(-distance);
}

void cTurtle::Right(int angle)
{
    m_angle = (m_angle + angle) % 360;
    if (m_angle < 0)
    {
        m_angle += 360;
    }
}

void cTurtle::Left(int angle)
{
    m_angle = (m_angle - angle) % 360;
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
    if (m_image->IsValidColor(color))
    {
        m_penColor = color;
    }
}

void cTurtle::BgColor(const std::string& color)
{
    if (m_image->IsValidColor(color))
    {
        m_bgColor = color;

        if (m_image != nullptr)
        {
            m_image->Fill(m_bgColor);
        }
    }
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