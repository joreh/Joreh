#include "Comp_Geom.h"

int sign( double d1 )
{
  return (d1>0)?1:-1;
}

double max( double d1, double d2 )
{
  return (d1>d2)?d1:d2;
}

double min( double d1, double d2 )
{
  return (d1<d2)?d1:d2;
}

bool Equal(double d1, double d2)
{
	return (fabs(d1-d2)<EPSILON);
}
double sqr ( double d)
{
	return (d*d);
}
AngDeg normalizeAngle( AngDeg angle )
{
  while( angle > 180.0  ) angle -= 360.0;
  while( angle < -180.0 ) angle += 360.0;

  return ( angle );
}


AngDeg Rad2Deg( AngRad x )
{
  return ( x * 180 / 3.14 );
}

AngRad Deg2Rad( AngDeg x )
{
  return ( x * 3.14 / 180 );
}

double cosDeg( AngDeg x )
{
  return ( cos( Deg2Rad( x ) ) );
}

double sinDeg( AngDeg x )
{
  return ( sin( Deg2Rad( x ) ) );
}

double tanDeg( AngDeg x )
{
  return ( tan( Deg2Rad( x ) ) );
}

AngDeg atanDeg( double x )
{
  return ( Rad2Deg( atan( x ) ) );
}

double atan2Deg( double x, double y )
{
  if( fabs( x ) < EPSILON && fabs( y ) < EPSILON )
    return ( 0.0 );

  return ( Rad2Deg( atan2( x, y ) ) );
}

AngDeg acosDeg( double x )
{
  if( x >= 1 )
    return ( 0.0 );
  else if( x <= -1 )
    return ( 180.0 );

  return ( Rad2Deg( acos( x ) ) );
}

AngDeg asinDeg( double x )
{
  if( x >= 1 )
    return ( 90.0 );
  else if ( x <= -1 )
    return ( -90.0 );

  return ( Rad2Deg( asin( x ) ) );
}

/*! This function returns a boolean value which indicates whether the value
   'ang' (from interval [-180..180] lies in the interval [angMin..angMax].
    Examples: isAngInInterval( -100, 4, -150) returns false
             isAngInInterval(   45, 4, -150) returns true
    \param ang angle that should be checked
    \param angMin minimum angle in interval
    \param angMax maximum angle in interval
    \return boolean indicating whether ang lies in [angMin..angMax] */
bool isAngInInterval( AngDeg ang, AngDeg angMin, AngDeg angMax )
{
  // convert all angles to interval 0..360
  if( ( ang    + 360 ) < 360 ) ang    += 360;
  if( ( angMin + 360 ) < 360 ) angMin += 360;
  if( ( angMax + 360 ) < 360 ) angMax += 360;

  if( angMin < angMax ) // 0 ---false-- angMin ---true-----angMax---false--360
    return angMin < ang && ang < angMax ;
  else                  // 0 ---true--- angMax ---false----angMin---true---360
    return !( angMax < ang && ang < angMin );
}

/*! This method returns the bisector (average) of two angles. It deals
    with the boundary problem, thus when 'angMin' equals 170 and 'angMax'
    equals -100, -145 is returned.
    \param angMin minimum angle [-180,180]
    \param angMax maximum angle [-180,180]
    \return average of angMin and angMax. */
AngDeg getBisectorTwoAngles( AngDeg angMin, AngDeg angMax )
{
  // separate sine and cosine part to circumvent boundary problem
  return normalizeAngle(
            atan2Deg( (sinDeg( angMin) + sinDeg( angMax ) )/2.0,
                      (cosDeg( angMin) + cosDeg( angMax ) )/2.0 ) );
}

int abcFormula(double a, double b, double c, double *s1, double *s2)
{
  double dDiscr = b*b - 4*a*c;       // discriminant is b^2 - 4*a*c
  if (fabs(dDiscr) < EPSILON )       // if discriminant = 0
  {
    *s1 = -b / (2 * a);              //  only one solution
    return 1;
  }
  else if (dDiscr < 0)               // if discriminant < 0
    return 0;                        //  no solutions
  else                               // if discriminant > 0
  {
    dDiscr = sqrt(dDiscr);           //  two solutions
    *s1 = (-b + dDiscr ) / (2 * a);
    *s2 = (-b - dDiscr ) / (2 * a);
    return 2;
  }
}
