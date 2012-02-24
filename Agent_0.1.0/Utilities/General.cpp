#include "Utilities/General.h"
#include <cstdlib>

#define RAND_SCALE 1000000

double General::random( double minVal, double maxVal )
{
  return rand() % RAND_SCALE / (double)RAND_SCALE * ( maxVal - minVal )
      + minVal;
}
