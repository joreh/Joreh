#include "Utilities/General.h"
#include <cstdlib>

#define RAND_SCALE 1000000

double General::random( double minVal, double maxVal )
{
  return rand() % (int)( ( maxVal - minVal ) * RAND_SCALE ) / RAND_SCALE
      + minVal;
}

double General::stableNum( double val, double minVal, double maxVal )
{
  if( val < minVal )
    return minVal;
  else if( val > maxVal )
    return maxVal;
  else
    return val;
}

