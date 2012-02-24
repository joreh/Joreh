#ifndef __VECTOR_H
#define __VECTOR_H

#include <iostream>

class Vector
{
  public:
    Vector( int numOfDim, double *valArr = 0 );
    Vector( const Vector &vec );
    ~Vector();

    int getNumOfDim() const;

    const double *getDimValues() const;
    void setDimValues( double *valArr );

    void setDimValue( int dim, double value );
    double getDimValue( int dim ) const;    

    double getLength() const;
    double getDistanceTo( const Vector &vec );

    double &operator[]( int index ) const;

    const Vector &operator=( const Vector &vec );
    Vector operator*( double d );
    Vector operator/( double d );
    Vector operator+( const Vector &vec );
    Vector operator-( const Vector &vec );
    Vector operator-();

    const Vector &operator*=( double d );
    const Vector &operator/=( double d );
    const Vector &operator+=( const Vector &vec );
    const Vector &operator-=( const Vector &vec );

    void print( std::ostream *out ) const;

    friend std::ostream &operator<<(
          std::ostream &out, const Vector &vec );

  private:

    int m_numOfDim;
    double *m_vector;
};

std::ostream &operator<<( std::ostream &out, const Vector &vec );

#endif

