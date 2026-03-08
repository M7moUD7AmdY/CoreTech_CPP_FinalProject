#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <cstdint>
#include <cmath>
#include <stdexcept>
#include <algorithm>

using namespace std;

struct Color
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
};

struct Point
{
    double x;
    double y;
};

static string trim(const string& s)
{
    size_t start = s.find_first_not_of(" \t\r\n");
    if (start == string::npos)
    {
        return "";
    }

    size_t end = s.find_last_not_of(" \t\r\n");
    return s.substr(start, end - start + 1);
}

static string removeComment(const string& line)
{
    size_t pos = line.find('#');
    if (pos == string::npos)
    {
        return line;
    }
    return line.substr(0, pos);
}

static vector<string> splitBySpaces(const string& line)
{
    vector<string> tokens;
    istringstream iss(line);
    string token;

    while (iss >> token)
    {
        tokens.push_back(token);
    }

    return tokens;
}

static bool startsWith(const string& s, const string& prefix)
{
    return s.rfind(prefix, 0) == 0;
}

static bool parseInteger(const string& s, int& value)
{
    try
    {
        size_t idx = 0;
        int v = stoi(s, &idx);
        if (idx != s.size())
        {
            return false;
        }
        value = v;
        return true;
    }
    catch (...)
    {
        return false;
    }
}

static bool parseDoubleValue(const string& s, double& value)
{
    try
    {
        size_t idx = 0;
        double v = stod(s, &idx);
        if (idx != s.size())
        {
            return false;
        }
        value = v;
        return true;
    }
    catch (...)
    {
        return false;
    }
}

static bool parseKeyValue(const string& token, const string& key, string& value)
{
    string prefix = key + "=";
    if (!startsWith(token, prefix))
    {
        return false;
    }

    value = token.substr(prefix.size());
    return !value.empty();
}

static bool getColorByName(const string& name, Color& color)
{
    static const unordered_map<string, Color> colorTable =
    {
        {"black",   {0,   0,   0}},
        {"white",   {255, 255, 255}},
        {"red",     {255, 0,   0}},
        {"green",   {0,   255, 0}},
        {"blue",    {0,   0,   255}},
        {"yellow",  {255, 255, 0}},
        {"cyan",    {0,   255, 255}},
        {"magenta", {255, 0,   255}},
        {"gray",    {128, 128, 128}},
        {"grey",    {128, 128, 128}},
        {"orange",  {255, 165, 0}},
        {"purple",  {128, 0,   128}}
    };

    auto it = colorTable.find(name);
    if (it == colorTable.end())
    {
        return false;
    }

    color = it->second;
    return true;
}

class Image
{
private:
    int m_width;
    int m_height;
    vector<uint8_t> m_pixels;

public:
    Image()
        : m_width(0),
          m_height(0)
    {
    }

    Image(int width, int height, const Color& bg)
        : m_width(0),
          m_height(0)
    {
        resize(width, height, bg);
    }

    void resize(int width, int height, const Color& bg)
    {
        if (width <= 0 || height <= 0)
        {
            throw runtime_error("image width and height must be positive");
        }

        m_width = width;
        m_height = height;
        m_pixels.assign(static_cast<size_t>(width) * static_cast<size_t>(height) * 3, 0);

        clear(bg);
    }

    bool isInitialized() const
    {
        return m_width > 0 && m_height > 0;
    }

    int width() const
    {
        return m_width;
    }

    int height() const
    {
        return m_height;
    }

    bool isInside(int x, int y) const
    {
        return x >= 0 && x < m_width && y >= 0 && y < m_height;
    }

    void clear(const Color& bg)
    {
        if (!isInitialized())
        {
            return;
        }

        for (int y = 0; y < m_height; ++y)
        {
            for (int x = 0; x < m_width; ++x)
            {
                setPixel(x, y, bg);
            }
        }
    }

    void setPixel(int x, int y, const Color& c)
    {
        if (!isInside(x, y))
        {
            return;
        }

        size_t index = static_cast<size_t>(y) * static_cast<size_t>(m_width) * 3
                     + static_cast<size_t>(x) * 3;

        m_pixels[index + 0] = c.r;
        m_pixels[index + 1] = c.g;
        m_pixels[index + 2] = c.b;
    }

    void drawLine(int x1, int y1, int x2, int y2, const Color& c)
    {
        int dx = abs(x2 - x1);
        int dy = abs(y2 - y1);

        int sx = (x1 < x2) ? 1 : -1;
        int sy = (y1 < y2) ? 1 : -1;

        int err = dx - dy;

        while (true)
        {
            setPixel(x1, y1, c);

            if (x1 == x2 && y1 == y2)
            {
                break;
            }

            int e2 = 2 * err;

            if (e2 > -dy)
            {
                err -= dy;
                x1 += sx;
            }

            if (e2 < dx)
            {
                err += dx;
                y1 += sy;
            }
        }
    }

    bool savePPM(const string& filePath) const
    {
        if (!isInitialized())
        {
            return false;
        }

        ofstream ofs(filePath, ios::out | ios::binary);
        if (!ofs)
        {
            return false;
        }

        ofs << "P6\n" << m_width << " " << m_height << "\n255\n";
        ofs.write(reinterpret_cast<const char*>(m_pixels.data()),
                  static_cast<streamsize>(m_pixels.size()));

        return !ofs.fail();
    }
};

class Turtle
{
private:
    Point m_position;
    double m_angleDeg;
    bool m_penDown;
    Color m_penColor;
    Image* m_image;

public:
    Turtle()
        : m_position{0.0, 0.0},
          m_angleDeg(0.0),
          m_penDown(false),
          m_penColor{0, 0, 0},
          m_image(nullptr)
    {
    }

    void attachImage(Image* image)
    {
        m_image = image;
    }

    void setPenColor(const Color& color)
    {
        m_penColor = color;
    }

    void setPosition(double x, double y)
    {
        m_position.x = x;
        m_position.y = y;
    }

    void penUp()
    {
        m_penDown = false;
    }

    void penDownAt(double x, double y)
    {
        setPosition(x, y);
        m_penDown = true;
    }

    bool isPenDown() const
    {
        return m_penDown;
    }

    double getX() const
    {
        return m_position.x;
    }

    double getY() const
    {
        return m_position.y;
    }

    double getAngle() const
    {
        return m_angleDeg;
    }

    void turnRight(double degrees)
    {
        m_angleDeg += degrees;
    }

    void turnLeft(double degrees)
    {
        m_angleDeg -= degrees;
    }

    void moveForward(double distance)
    {
        if (m_image == nullptr)
        {
            throw runtime_error("turtle has no attached image");
        }

        double rad = m_angleDeg * 3.14159265358979323846 / 180.0;

        double newX = m_position.x + distance * cos(rad);
        double newY = m_position.y + distance * sin(rad);

        if (m_penDown)
        {
            int x1 = static_cast<int>(round(m_position.x));
            int y1 = static_cast<int>(round(m_position.y));
            int x2 = static_cast<int>(round(newX));
            int y2 = static_cast<int>(round(newY));

            m_image->drawLine(x1, y1, x2, y2, m_penColor);
        }

        m_position.x = newX;
        m_position.y = newY;
    }
};

class ScriptParser
{
private:
    Image m_image;
    Turtle m_turtle;

    bool m_hasSize;
    bool m_hasAnyDrawing;
    Color m_penColor;
    Color m_bgColor;

private:
    bool parseSizeCommand(const vector<string>& tokens, string& error)
    {
        if (tokens.size() != 3)
        {
            error = "expected: size w=<int> h=<int>";
            return false;
        }

        string wStr;
        string hStr;

        if (!parseKeyValue(tokens[1], "w", wStr))
        {
            error = "expected width token in form w=<int>";
            return false;
        }

        if (!parseKeyValue(tokens[2], "h", hStr))
        {
            error = "expected height token in form h=<int>";
            return false;
        }

        int w = 0;
        int h = 0;

        if (!parseInteger(wStr, w) || !parseInteger(hStr, h))
        {
            error = "width and height must be valid integers";
            return false;
        }

        if (w <= 0 || h <= 0)
        {
            error = "width and height must be positive";
            return false;
        }

        m_image.resize(w, h, m_bgColor);
        m_turtle.attachImage(&m_image);
        m_hasSize = true;
        return true;
    }

    bool parseColorCommand(const vector<string>& tokens, string& error)
    {
        if (tokens.size() != 3)
        {
            error = "expected: color pen=<name> bg=<name>";
            return false;
        }

        string penName;
        string bgName;

        if (!parseKeyValue(tokens[1], "pen", penName))
        {
            error = "expected pen color token in form pen=<name>";
            return false;
        }

        if (!parseKeyValue(tokens[2], "bg", bgName))
        {
            error = "expected background color token in form bg=<name>";
            return false;
        }

        Color newPenColor;
        Color newBgColor;

        if (!getColorByName(penName, newPenColor))
        {
            error = "unknown pen color: " + penName;
            return false;
        }

        if (!getColorByName(bgName, newBgColor))
        {
            error = "unknown background color: " + bgName;
            return false;
        }

        m_penColor = newPenColor;
        m_bgColor = newBgColor;
        m_turtle.setPenColor(m_penColor);

        if (m_hasSize && !m_hasAnyDrawing)
        {
            m_image.clear(m_bgColor);
        }

        return true;
    }

    bool parsePenCommand(const vector<string>& tokens, string& error)
    {
        if (tokens.size() < 2)
        {
            error = "expected pen command";
            return false;
        }

        if (tokens[1] == "up")
        {
            if (tokens.size() != 2)
            {
                error = "expected: pen up";
                return false;
            }

            m_turtle.penUp();
            return true;
        }

        if (tokens[1] == "down")
        {
            if (tokens.size() != 4)
            {
                error = "expected: pen down <x> <y>";
                return false;
            }

            if (!m_hasSize)
            {
                error = "size must be defined before pen down";
                return false;
            }

            int x = 0;
            int y = 0;

            if (!parseInteger(tokens[2], x) || !parseInteger(tokens[3], y))
            {
                error = "pen down coordinates must be integers";
                return false;
            }

            m_turtle.penDownAt(static_cast<double>(x), static_cast<double>(y));
            return true;
        }

        error = "unknown pen command: " + tokens[1];
        return false;
    }

    bool parseMoveCommand(const vector<string>& tokens, string& error)
    {
        if (tokens.size() != 3)
        {
            error = "expected move command: move forward <n> | move right <deg> | move left <deg>";
            return false;
        }

        if (!m_hasSize)
        {
            error = "size must be defined before move commands";
            return false;
        }

        double value = 0.0;
        if (!parseDoubleValue(tokens[2], value))
        {
            error = "move value must be numeric";
            return false;
        }

        if (tokens[1] == "forward")
        {
            m_turtle.moveForward(value);
            m_hasAnyDrawing = m_hasAnyDrawing || m_turtle.isPenDown();
            return true;
        }

        if (tokens[1] == "right")
        {
            m_turtle.turnRight(value);
            return true;
        }

        if (tokens[1] == "left")
        {
            m_turtle.turnLeft(value);
            return true;
        }

        error = "unknown move command: " + tokens[1];
        return false;
    }

public:
    ScriptParser()
        : m_hasSize(false),
          m_hasAnyDrawing(false),
          m_penColor{0, 0, 0},
          m_bgColor{255, 255, 255}
    {
        m_turtle.attachImage(&m_image);
        m_turtle.setPenColor(m_penColor);
    }

    bool parse(istream& input, string& errorMessage)
    {
        string rawLine;
        int lineNumber = 0;

        while (getline(input, rawLine))
        {
            ++lineNumber;

            string line = trim(removeComment(rawLine));
            if (line.empty())
            {
                continue;
            }

            vector<string> tokens = splitBySpaces(line);
            if (tokens.empty())
            {
                continue;
            }

            string error;

            if (tokens[0] == "size")
            {
                if (!parseSizeCommand(tokens, error))
                {
                    errorMessage = "line " + to_string(lineNumber) + ": " + error;
                    return false;
                }
            }
            else if (tokens[0] == "color")
            {
                if (!parseColorCommand(tokens, error))
                {
                    errorMessage = "line " + to_string(lineNumber) + ": " + error;
                    return false;
                }
            }
            else if (tokens[0] == "pen")
            {
                if (!parsePenCommand(tokens, error))
                {
                    errorMessage = "line " + to_string(lineNumber) + ": " + error;
                    return false;
                }
            }
            else if (tokens[0] == "move")
            {
                if (!parseMoveCommand(tokens, error))
                {
                    errorMessage = "line " + to_string(lineNumber) + ": " + error;
                    return false;
                }
            }
            else
            {
                errorMessage = "line " + to_string(lineNumber) + ": unknown command: " + tokens[0];
                return false;
            }
        }

        if (!m_hasSize)
        {
            errorMessage = "script error: missing size command";
            return false;
        }

        return true;
    }

    const Image& getImage() const
    {
        return m_image;
    }
};

static void printUsage(const char* programName)
{
    cerr << "Usage:\n";
    cerr << "  " << programName << " <script.txt> <output.ppm>\n";
    cerr << "  " << programName << " <output.ppm>    (reads script from stdin)\n";
}

int main(int argc, char* argv[])
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string outputPath;
    ifstream scriptFile;
    istream* input = nullptr;

    if (argc == 3)
    {
        scriptFile.open(argv[1]);
        if (!scriptFile.is_open())
        {
            cerr << "Error: failed to open script file: " << argv[1] << '\n';
            return 1;
        }

        input = &scriptFile;
        outputPath = argv[2];
    }
    else if (argc == 2)
    {
        input = &cin;
        outputPath = argv[1];
    }
    else
    {
        printUsage(argv[0]);
        return 1;
    }

    ScriptParser parser;
    string errorMessage;

    if (!parser.parse(*input, errorMessage))
    {
        cerr << "Parse error: " << errorMessage << '\n';
        return 1;
    }

    if (!parser.getImage().savePPM(outputPath))
    {
        cerr << "Error: failed to save output image: " << outputPath << '\n';
        return 1;
    }

    cout << "Image generated successfully: " << outputPath << '\n';
    return 0;
}