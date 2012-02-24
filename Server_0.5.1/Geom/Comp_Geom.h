#ifndef _COMP_GEOM_H_
#define _COMP_GEOM_H_

#include <cmath>  
#include <stdarg.h>
#include <string>  
#include <vector>
#include <iostream>
#include <stdio.h>

using namespace std;

typedef double AngRad;
typedef double AngDeg;

#define EPSILON 0.01
#define sq(a) ((a)*(a))
double max     ( double d1, double d2 );
double min     ( double d1, double d2 );
int    sign    ( double d1            );
bool	Equal  ( double d1, double d2 );

AngDeg normalizeAngle ( AngDeg angle  );
AngDeg Rad2Deg ( AngRad x             );
AngRad Deg2Rad ( AngDeg x             );

double cosDeg  ( AngDeg x             );
double sinDeg  ( AngDeg x             );
double tanDeg  ( AngDeg x             );
AngDeg atanDeg ( double x             );
double atan2Deg( double x,  double y  );
AngDeg acosDeg ( double x             );
AngDeg asinDeg ( double x             );

// various goniometric functions
bool   isAngInInterval     ( AngDeg ang,    AngDeg angMin,    AngDeg angMax );
AngDeg getBisectorTwoAngles( AngDeg angMin, AngDeg angMax );
int    abcFormula(double a,double b, double c, double *s1,double *s2);

enum CoordSystemT {
  CARTESIAN,
  POLAR,
  KORAVI
  
};

#endif
