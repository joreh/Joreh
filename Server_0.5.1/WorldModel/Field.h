#ifndef __FIELD_H
#define __FIELD_H

#include "Geom/Vector3D.h"
#include <string>

class Field
{
public:
  Field( double lx = 0.0, double rx = 0.0,
         double ty = 0.0, double by = 0.0 );

  void setFieldGeom( double lx, double rx,
                     double ty, double by );

  void setLeftX( double x );
  double getLeftX() const;

  void setRightX( double x );
  double getRightX() const;

  void setTopY( double y );
  double getTopY() const;

  void setBottomY( double y );
  double getBottomY() const;

  double getPosFitness( double x, double y ) const;

  Vector3D modifyPositionOutBound( Vector3D position ) const;

  std::string toString() const;

private:

  double m_lx;
  double m_rx;
  double m_ty;
  double m_by;

};

#endif

