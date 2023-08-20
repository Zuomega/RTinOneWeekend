#ifndef UTILS_H
#define UTILS_H

#include <cmath>
#include <limits>
#include <memory>

// Usings
using std::shared_ptr;
using std::make_shared;
using std::sqrt;

#define  FLOAT_FORMAT double 

// Constants
const FLOAT_FORMAT infinity = std::numeric_limits<FLOAT_FORMAT>::infinity();
const FLOAT_FORMAT pi = 3.1415926535897932385;

// Utility Functions
inline FLOAT_FORMAT degrees_to_radians(FLOAT_FORMAT degrees)
{
    return degrees * pi / 180.0;
}

// Common Headers
//#include "ray.h"
//#include "vector3.h"

#endif