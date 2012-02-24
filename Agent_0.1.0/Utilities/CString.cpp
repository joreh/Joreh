#include <cstdlib>
#include "CString.h"
#include "SwarmException.h"

using namespace std;

CString::CString()
{
  setStdString( "" );
}

CString::CString( string str )
{
  setStdString( str );
}

CString::CString( char *str )
{
  setStdString( string( str ) );
}

void CString::setStdString( string str )
{
  m_str = str;
}

int CString::toInt() const
{
  return atoi( m_str.c_str() );
}

double CString::toDouble() const
{
  return atof( m_str.c_str() );
}

bool CString::toBool() const
{
  if( m_str == "true" || m_str == "True" )
    return true;

  if( m_str == "false" || m_str == "False" )
    return false;

  throw SwarmException( "(CString::toBool) can't convert" );
}


const string &CString::toString() const
{
  return m_str;
}


/*
int main()
{
  CString str( "test" );
  cout << str << endl;
}
*/
