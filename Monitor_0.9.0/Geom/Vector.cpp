#include "Vector.h"
#include <cstring>
#include <cmath>

using namespace std;

#define EPS 0.00000001

double sqr( double x )
{
  return x * x;
}

Vector::Vector( int numOfDim, double *valArr )
      : m_numOfDim( numOfDim )
{
  m_vector = new double[m_numOfDim];

  if( valArr )
    setDimValues( valArr );
  else
    memset( m_vector, 0, sizeof( double ) * m_numOfDim );
}

Vector::Vector( const Vector &vec )
{
  m_numOfDim = vec.getNumOfDim();
  m_vector = new double[m_numOfDim];

  *this = vec;
}

Vector::~Vector()
{
  delete[] m_vector;
}

const double *Vector::getDimValues() const
{
  return m_vector;
}

void Vector::setDimValues( double *valArr )
{
  if( !valArr )
  {
    cerr << "(Vector::setDimValues) null valArr" << endl;
    return;
  }

  for( int i = 0; i < m_numOfDim; i ++ )
    m_vector[i] = valArr[i];
}

int Vector::getNumOfDim() const
{
  return m_numOfDim;
}

void Vector::setDimValue( int dim, double val )
{
  m_vector[dim] = val;
}


double Vector::getDimValue( int dim ) const
{
  return m_vector[dim];
}

double Vector::getLength() const
{
  double length = 0.0;

  for( int i = 0; i < m_numOfDim; i ++ )
    length += sqr( m_vector[i] );

  return sqrt( length );
}

double Vector::getDistanceTo( const Vector &vec )
{
  if( vec.getNumOfDim() != getNumOfDim() )
  {
    cerr << "(Vector::getDistanceTo) dimension not match" << endl;
    return 0.0;
  }

  double distance = 0.0;

  for( int i = 0; i < m_numOfDim; i ++ )
    distance += sqr( getDimValue( i ) - vec.getDimValue( i ) );


  return sqrt( distance );
}

double &Vector::operator[]( int index ) const
{
  return m_vector[index];
}

void Vector::print( ostream *out ) const
{
  (*out) << "(";
  for( int i = 0; i < m_numOfDim - 1; i ++ )
    (*out) << m_vector[i] << ", ";
  (*out) << m_vector[m_numOfDim-1] << ")";
}

const Vector &Vector::operator=( const Vector &vec )
{

  if( !m_vector || vec.getNumOfDim() != m_numOfDim  )
  {
    delete[] m_vector;
    m_numOfDim = vec.getNumOfDim();
    m_vector = new double[m_numOfDim];
  }

  setDimValues( vec.m_vector );
  return *this;
}

Vector Vector::operator*( double d )
{
  Vector outVec( getNumOfDim() );
  for( int i = 0; i < m_numOfDim; i ++ )
    outVec[i] = m_vector[i] * d;

  return outVec;
}

Vector Vector::operator/( double d )
{
  Vector outVec( getNumOfDim() );
  for( int i = 0; i < m_numOfDim; i ++ )
    outVec[i] = m_vector[i] / d;

  return outVec;
}

Vector Vector::operator+( const Vector &vec )
{
  Vector outVec( getNumOfDim() );

  for( int i = 0; i < m_numOfDim; i ++ )
    outVec[i] = m_vector[i] + vec[i];
  return outVec;
}

Vector Vector::operator-( const Vector &vec )
{
  Vector outVec( getNumOfDim() );

  for( int i = 0; i < m_numOfDim; i ++ )
    outVec[i] = m_vector[i] - vec[i];

  return outVec;
}

Vector Vector::operator-()
{
  Vector outVec( getNumOfDim() );

  for( int i = 0; i < m_numOfDim; i ++ )
    outVec[i] = m_vector[i] * -1.0;

  return outVec;
}

const Vector &Vector::operator*=( double d )
{
  for( int i = 0; i < m_numOfDim; i ++ )
    m_vector[i] *= d;

  return *this;
}

const Vector &Vector::operator/=( double d )
{
  for( int i = 0; i < m_numOfDim; i ++ )
    m_vector[i] /= d;

  return *this;
}

const Vector &Vector::operator+=( const Vector &vec )
{
  for( int i = 0; i < m_numOfDim; i ++ )
    m_vector[i] += vec[i];
  return *this;
}

const Vector &Vector::operator-=( const Vector &vec )
{
  for( int i = 0; i < m_numOfDim; i ++ )
    m_vector[i] -= vec[i];
  return *this;
}


ostream &operator<<( ostream &out, const Vector &vec )
{
  vec.print( &out );
  return out;
}

/*
int main()
{

  double vec1Arr[2] = {-0.126, -0.0158};
  double vec2Arr[2] = {-0.8792, -0.1578};

  Vector vec1( 2, vec1Arr );
  Vector vec2( 2, vec2Arr );

  cout << vec1.getDistanceTo( vec2 ) << endl;
  
  cout << vec1 << endl;
  vec1 = vec1 - vec2;
  cout << -vec1 << endl;
}
*/

