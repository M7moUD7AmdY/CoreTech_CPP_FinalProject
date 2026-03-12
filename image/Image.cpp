#include "Image.hpp"

 cImage ::cImage():m_height(1),m_width(1)
{
    m_pixels.resize(m_height*m_width);
}

cImage :: cImage(int width,int height):m_height(height),m_width(width)
{
        m_pixels.resize(m_height*m_width);

}

void cImage :: Resize(int width,int height)
{
    
    m_width = width;
    m_height = height;

    m_pixels.resize(width * height);

}

void cImage :: SetPixel(int x,int y,const std::string& color)
{
    if(x < 0 || x >= m_width || y < 0 || y >= m_height)
    {
        return;
    }

    int pixel_index=y * m_width + x; //to get pixel index for the vector
    m_pixels[pixel_index]=ColorTable.at(color);

}

bool cImage :: SavePPM(const std::string& file)
{
    std::ofstream output_image(file);
    if(!output_image)
    {
        printf("Faild to open file\n");
        return false;
    }
    output_image << "P3\n";
    output_image << m_width << " " << m_height << "\n";
    output_image << "255\n";

    int index;
    for(int y = 0; y < m_height; y++)
    {
        for(int x = 0; x < m_width; x++)
        {
                index = y * m_width + x;

            output_image 
                << (int)m_pixels[index].R << " "
                << (int)m_pixels[index].G << " "
                << (int)m_pixels[index].B << " ";
        }

        output_image << "\n";
    }

    return true;

}

int cImage :: GetImageSize(void)
{
    if((m_width*m_height) != m_pixels.size() )
    {
        return -1;
    }

    return m_width*m_height;
}

void cImage::Fill(const std::string& color)
{
    if (!IsValidColor(color))
    {
        return;
    }

    const sPixel pixel = ColorTable.at(color);
    std::fill(m_pixels.begin(), m_pixels.end(), pixel);
}


bool cImage::IsValidColor(const std::string& color)
{
    return ColorTable.find(color) != ColorTable.end();
}