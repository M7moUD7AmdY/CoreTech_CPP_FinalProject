#ifndef _IMAGE_H_
#define _IMAGE_H_

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include "../common/Color.h"

class cImage
{
private:
    int m_width;
    int m_height;
    std::vector<sPixel> m_pixels;

public:
    cImage();
    cImage(int width, int height);
    bool IsValidColor(const std::string& color);
    void Fill(const std::string& color);
    void Resize(int width, int height);
    void SetPixel(int x, int y, const std::string& color);
    bool SavePPM(const std::string& file);
    int GetImageSize(void);
};

#endif