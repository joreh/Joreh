#ifndef __FIELD_H
#define __FIELD_H

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

  std::string toString() const;

private:

  double m_lx;
  double m_rx;
  double m_ty;
  double m_by;

};

#endif

