#ifndef _COLOR_H_
#define _COLOR_H_

#include <string>
#include <map>
#include <cstdint>

struct sPixel
{
    uint8_t R;
    uint8_t G;
    uint8_t B;
};

const std::map<std::string, sPixel> ColorTable =
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

#endif