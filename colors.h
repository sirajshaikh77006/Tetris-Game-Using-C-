#pragma once 
#include <raylib.h>
#include <vector>

extern const Color darkGray;// extern keyword allow to define a variable in one file and use it in multiple file
extern const Color green;
extern const Color red;
extern const Color orange;
extern const Color yellow;
extern const Color purple;
extern const Color cyan;
extern const Color blue;
extern const Color lightBlue;
extern const Color darkBlue;

std::vector<Color> GetCellColors();