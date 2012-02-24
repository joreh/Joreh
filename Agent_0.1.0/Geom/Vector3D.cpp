#include "Vector3D.h"


Vector3D operator * ( double d, const Vector3D &v)
{
  return ( Vector3D( v.m_x * d, v.m_y * d, v.m_z * d  ) );
}


Vector3D::Vector3D( double x, double y,double z, CoordSystemT cs )
{
  setVector3D( x, y,z, cs );
}

Vector3D Vector3D::operator - (  )
{
  return ( Vector3D( -m_x, -m_y, -m_z ) );
}

Vector3D Vector3D::operator + ( const double &d )
{
  return ( Vector3D( m_x + d, m_y + d, m_z + d ) );
}

Vector3D Vector3D::operator + ( const Vector3D &p )
{
  return ( Vector3D( m_x + p.m_x, m_y + p.m_y, m_z+ p.m_z ) );
}

Vector3D Vector3D::operator - ( const double &d )
{
  return ( Vector3D( m_x - d, m_y - d, m_z - d ) );
}

Vector3D Vector3D::operator - ( const Vector3D &p )
{
  return ( Vector3D( m_x - p.m_x, m_y - p.m_y, m_z - p.m_z ) );
}

Vector3D Vector3D::operator * ( const double &d  )
{
  return ( Vector3D( m_x * d, m_y * d, m_z * d  ) );
}

Vector3D Vector3D::operator * ( const Vector3D &p )
{
  return ( Vector3D( m_x * p.m_x, m_y * p.m_y, m_z * p.m_z ) );
}

double Vector3D::operator &(const Vector3D &p)
{
	return ( m_x * p.m_x+ m_y * p.m_y+ m_z * p.m_z );
}

Vector3D Vector3D::operator / ( const double &d )
{
  return ( Vector3D( m_x / d, m_y / d, m_z / d  ) );
}

Vector3D Vector3D::operator / ( const Vector3D &p )
{
  return ( Vector3D( m_x / p.m_x, m_y / p.m_y, m_z / p.m_z ) );
}

void Vector3D::operator = ( const double &d )
{
  m_x = d;
  m_y = d;
  m_z = d;
}

void Vector3D::operator +=( const Vector3D &p )
{
  m_x += p.m_x;
  m_y += p.m_y;
  m_z += p.m_z;
}

void Vector3D::operator += ( const double &d )
{
  m_x += d;
  m_y += d;
  m_z += d;
}

void Vector3D::operator -=( const Vector3D &p )
{
  m_x -= p.m_x;
  m_y -= p.m_y;
  m_z -= p.m_z;
}

void Vector3D::operator -=( const double &d )
{
  m_x -= d;
  m_y -= d;
  m_z -= d;
}

void Vector3D::operator *=( const Vector3D &p )
{
  m_x *= p.m_x;
  m_y *= p.m_y;
  m_z *= p.m_z;
}

void Vector3D::operator *=( const double &d )
{
  m_x *= d;
  m_y *= d;
  m_z *= d;
}

void Vector3D::operator /=( const Vector3D &p )
{
  m_x /= p.m_x;
  m_y /= p.m_y;
  m_z /= p.m_z;
}

void Vector3D::operator /=( const double &d )
{
  m_x /= d;
  m_y /= d;
  m_z /= d;
}

bool Vector3D::operator !=( const Vector3D &p )
{
  return ( ( m_x != p.m_x ) || ( m_y != p.m_y ) || ( m_z != p.m_z ) );
}

bool Vector3D::operator !=( const double &d )
{
  return ( ( m_x != d ) || ( m_y != d ) || ( m_z != d ) );
}

bool Vector3D::operator ==( const Vector3D &p )
{
  return ( ( m_x == p.m_x ) && ( m_y == p.m_y ) && ( m_z == p.m_z ) );
}

bool Vector3D::operator ==( const double &d )
{
  return ( ( m_x == d ) && ( m_y == d ) && ( m_z == d )  );
}
ostream& operator << (ostream & output ,Vector3D vec)
{
	output <<"( "<<vec.getX()<<" , "<<vec.getY()<<" , "<<vec.getZ()<<" )" ;
	return output ;
}
string Vector3D::str( CoordSystemT cs )
{
  char buf[ 1024 ];

  if( cs == CARTESIAN )
    sprintf( buf, "( %f, %f, %f )", getX( ), getY( ), getZ( ) );
  else
	if(cs==POLAR)
    		sprintf( buf, "( r: %f, phi: %f ,Z: %f)", getMagnitude( ), getPhiDirection( ), getZ( ) );
	else
		sprintf( buf, "( r: %f, phi: %f ,teta: %f)", getMagnitude( ), getPhiDirection( ), getTetaDirection( ) );		
  string str( buf );
  return ( str );
}

void Vector3D::setX( double dX )
{
  m_x = dX;
}

double Vector3D::getX( ) const
{
  return ( m_x );
}

void Vector3D::setY( double dY )
{
  m_y = dY;
}

double Vector3D::getY( ) const
{
  return ( m_y );
}

void Vector3D::setZ( double dZ )
{
  m_z = dZ;
}

double Vector3D::getZ( ) const
{
  return ( m_z );
}

void Vector3D::setVector3D( double dX, double dY,double dZ, CoordSystemT cs)
{
  if( cs == CARTESIAN )
  {
    m_x = dX;
    m_y = dY;
    m_z = dZ;
  }
  else
    if(cs == POLAR)
	*this = getVector3DFromPolar( dX, dY, dZ );
    else
	*this = getVector3DFromKORAVI( dX, dY, dZ );
}

double Vector3D::getDistanceTo( const Vector3D p )
{
  return ( ( *this - p ).getMagnitude( ) );
}

Vector3D Vector3D::setMagnitude( double d )
{
  if( getMagnitude( ) > EPSILON )
     ( *this ) *= ( d / getMagnitude( ) );

  return ( *this );
}

double Vector3D::getMagnitude( ) const
{
  return ( sqrt( m_x * m_x + m_y * m_y + m_z * m_z ) );
}

AngDeg Vector3D::getPhiDirection( ) const
{
  return (  atan2Deg( m_y, m_x )  );
}

AngDeg Vector3D::getTetaDirection()const
{
    double g = getMagnitude();
    if ( g > EPSILON)
	return ( asinDeg( m_z / g ) );
    else
	return 1;
}

bool Vector3D::isInFrontOf( const Vector3D &p )
{
  return ( ( m_x > p.getX( ) ) ? true : false );
}

bool Vector3D::isInFrontOf( const double &d )
{
  return ( ( m_x > d ) ? true : false );
}

bool Vector3D::isBehindOf( const Vector3D &p )
{
  return ( ( m_x < p.getX( ) ) ? true : false );
}

bool Vector3D::isBehindOf( const double &d )
{
  return ( ( m_x < d ) ? true : false );
}

bool Vector3D::isLeftOf( const Vector3D &p )
{
  return ( ( m_y < p.getY( ) ) ? true : false );
}

bool Vector3D::isLeftOf( const double &d )
{
  return ( ( m_y < d ) ? true : false );
}

bool Vector3D::isRightOf( const Vector3D &p )
{
  return ( ( m_y > p.getY( ) ) ? true : false );
}

bool Vector3D::isRightOf( const double &d )
{
  return ( ( m_y > d ) ? true : false );
}

bool Vector3D::isBetweenX( const Vector3D &p1, const Vector3D &p2 )
{
  return ( ( isInFrontOf( p1 ) && isBehindOf( p2 ) ) ? true : false );
}

bool Vector3D::isBetweenX( const double &d1, const double &d2 )
{
  return ( ( isInFrontOf( d1 ) && isBehindOf( d2 ) ) ? true : false );
}

bool Vector3D::isBetweenY( const Vector3D &p1, const Vector3D &p2 )
{
  return ( ( isRightOf( p1 ) && isLeftOf( p2 ) ) ? true : false );
}

bool Vector3D::isBetweenY( const double &d1, const double &d2 )
{
  return ( ( isRightOf( d1 ) && isLeftOf( d2 ) ) ? true : false );
}

Vector3D Vector3D::normalize( )
{
  return ( setMagnitude( 1.0 ) );
}

Vector3D Vector3D::rotate( AngDeg anglePhi , AngDeg angleTeta )
{
  double dMag    = getMagnitude( );
  double dNewDirPhi = getPhiDirection( ) + anglePhi; 
  double dNewDirTeta = getTetaDirection( ) + angleTeta;
  (* this) = getVector3DFromKORAVI( dMag, dNewDirPhi, dNewDirTeta );     
  return ( *this );
}

Vector3D Vector3D::getVector3DOnLineFraction( Vector3D &p,
                                                       double      dFrac )
{
  // determine point on line that lies at fraction dFrac of whole line
  // example: this --- 0.25 ---------  p
  // formula: this + dFrac * ( p - this ) = this - dFrac * this + dFrac * p =
  //          ( 1 - dFrac ) * this + dFrac * p
  return ( ( *this ) * ( 1.0 - dFrac ) + ( p * dFrac ) );
}

Vector3D Vector3D::getVector3DFromKORAVI( double dMag, AngDeg phi, AngDeg teta)
{
  // cos(phi) = x/r <=> x = r*cos(phi); sin(phi) = y/r <=> y = r*sin(phi)
  return ( Vector3D( dMag * cosDeg( teta ) * cosDeg (phi) , dMag * cosDeg( teta ) * sinDeg (phi), dMag * sinDeg( teta ) ) );
}

Vector3D Vector3D::getVector3DFromPolar(double dMag,AngDeg phi,double z)
{
	return ( Vector3D( dMag *  cosDeg (phi) , dMag * sinDeg (phi), z ) );
}

Vector3D Vector3D::Cross(const Vector3D &v)
{
	return (Vector3D(getY()*v.getZ() - getZ()*v.getY(),
						getZ()*v.getX() - getX()*v.getZ(),
						getX()*v.getY() - getY()*v.getX()));
}
