#ifndef CLASSES_HPP_INCLUDED
#define CLASSES_INCLUDED

#include <vector>
class point{
public:
float x;
float y;
bool operator==(const point& );	
};
/*---------------------------------------------------------------*/
class obstacle{
public:
int n_sommets; //nombre de sommets
std::vector<point> sommets;
};
#endif
