#include "Field.h"
#include <sstream>

using namespace std;

Field::Field( double lx, double rx, double ty, double by )
{
  setFieldGeom( lx, rx, ty, by );
}

void Field::setFieldGeom( double lx, double rx, double ty, double by )
{
  setLeftX( lx );
  setRightX( rx );
  setTopY( ty );
  setBottomY( by );
}

void Field::setLeftX( double x )
{
  m_lx = x;
}

double Field::getLeftX() const
{
  return m_lx;
}

void Field::setRightX( double x )
{
  m_rx = x;
}

double Field::getRightX() const
{
  return m_rx;
}

void Field::setTopY( double y )
{
  m_ty = y;
}

double Field::getTopY() const
{
  return m_ty;
}

void Field::setBottomY( double y )
{
  m_by = y;
}

double Field::getBottomY() const
{
  return m_by;
}

double Field::getPosFitness( double x, double y ) const
{
  return x * x + y * y;
}

Vector3D Field::modifyPositionOutBound( Vector3D position ) const
{
  if( position.getX() < m_lx )
    position.setX( m_lx );

  if( position.getX() > m_rx )
    position.setX( m_rx );

  if( position.getY() > m_ty )
    position.setY( m_ty );

  if( position.getY() < m_by )
    position.setY( m_by );

  return position;
}

string Field::toString() const
{
  ostringstream out;

  out << "( " << getLeftX() << " " << getRightX() << " " 
      << getTopY() << " " << getBottomY() << ")";

  return out.str();
}

