#include "Utilities/General.h"
#include <cstdlib>

#define RAND_SCALE 1000000

double General::random( double minVal, double maxVal )
{
  return rand() % (int)( ( maxVal - minVal ) * RAND_SCALE ) / RAND_SCALE
      + minVal;
}
