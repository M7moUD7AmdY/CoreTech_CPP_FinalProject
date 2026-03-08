#pragma once
#include <vector>
#include <string>
#include <fstream>


struct sPixel
{
    uint8_t  R;
    uint8_t  G;
    uint8_t  B;
};

class cImage
{
private:

    int m_width;
    int m_height;
    
    std::vector<sPixel> m_pixels;

public:

    cImage();

    cImage(int width,int height);

    void Resize(int width,int height);

    void SetPixel(int x,int y,const sPixel& color);

    bool SavePPM(const std::string& file);
    
    int GetImageSize(void);
};