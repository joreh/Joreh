#ifndef _VECTOR3D_H_
#define _VECTOR3D_H_

#include "Comp_Geom.h"

class Vector3D
{
	friend Vector3D operator * ( double, const Vector3D &);
 	friend ostream& operator << ( ostream & , Vector3D );

private:

  double m_x; 
  double m_y;
  double m_z;

public:
  Vector3D  ( double            vx = 0, double            vy = 0,double vz =0,
                                              CoordSystemT      cs =CARTESIAN);

  Vector3D        operator -             (                                );
  Vector3D        operator +             ( const double      &d           );
  Vector3D        operator +             ( const Vector3D &p           );
  Vector3D        operator -             ( const double      &d           );
  Vector3D        operator -             ( const Vector3D &p           );
  Vector3D        operator *             ( const double      &d           );
  Vector3D        operator *             ( const Vector3D &p           );
  double             operator &             ( const Vector3D &p           );
  Vector3D        operator /             ( const double      &d           );
  Vector3D        operator /             ( const Vector3D &p           );
  void               operator =             ( const double      &d           );
  void               operator +=            ( const Vector3D &p           );
  void               operator +=            ( const double      &d           );
  void               operator -=            ( const Vector3D &p           );
  void               operator -=            ( const double      &d           );
  void               operator *=            ( const Vector3D &p           );
  void               operator *=            ( const double      &d           );
  void               operator /=            ( const Vector3D &p           );
  void               operator /=            ( const double      &d           );
  bool               operator !=            ( const Vector3D &p           );
  bool               operator !=            ( const double      &d           );
  bool               operator ==            ( const Vector3D &p           );
  bool               operator ==            ( const double      &d           );

  // methods for producing output
  string             str                    ( CoordSystemT      cs =CARTESIAN);

  // set- and get methods for private member variables
  void               setX                   ( double            dX           );
  double             getX                   (                          ) const;
  void               setY                   ( double            dY           );
  double             getY                   (                          ) const;
  void               setZ                   ( double            dZ           );
  double             getZ                   (                          ) const;

  // set- and get methods for derived position information
  void               setVector3D         ( double            dX = 0,
                                              double            dY = 0,
                                              double            dZ = 0,
                                              CoordSystemT      cs =CARTESIAN);
  double             getDistanceTo          ( const Vector3D p            );
  Vector3D        setMagnitude           ( double            d            );
  double             getMagnitude           (                          ) const;
  AngDeg             getPhiDirection        (                          ) const;
  AngDeg             getTetaDirection       (                          ) const;

  // comparison methods for positions
  bool               isInFrontOf            ( const Vector3D &p           );
  bool               isInFrontOf            ( const double      &d           );
  bool               isBehindOf             ( const Vector3D &p           );
  bool               isBehindOf             ( const double      &d           );
  bool               isLeftOf               ( const Vector3D &p           );
  bool               isLeftOf               ( const double      &d           );
  bool               isRightOf              ( const Vector3D &p           );
  bool               isRightOf              ( const double      &d           );
  bool               isBetweenX             ( const Vector3D &p1,
                                              const Vector3D &p2          );
  bool               isBetweenX             ( const double      &d1,
                                              const double      &d2          );
  bool               isBetweenY             ( const Vector3D &p1,
                                              const Vector3D &p2          );
  bool               isBetweenY             ( const double      &d1,
                                              const double      &d2          );

  // conversion methods for positions
  Vector3D        normalize              (                                );
  Vector3D        rotate                 ( AngDeg 	anglePhi , 
					   AngDeg 	angleTeta	);

  Vector3D        getVector3DOnLineFraction( Vector3D  &p,
                                              double            dFrac        );

  // static class methods
  static Vector3D getVector3DFromPolar( double        ,
                                              AngDeg ,     double     );
  
  static Vector3D getVector3DFromKORAVI( double        ,
                                              AngDeg ,    AngDeg   );
  Vector3D 		 Cross					(const 	Vector3D 	&v);

};

#endif
