#ifndef FUNCTIONS1_HPP_INCLUDED
#define FUNCTIONS1_INCLUDED

#include "classes.hpp"

float min(float x, float y);
float max(float x, float y);
float* equation_droite(float xa,float ya,float xb,float yb);
bool point_in_segment(point A, point B, point C);
bool intersection_segments(point A1, point B1, point A2, point B2);
#endif
