#include "Logger.h"
#include "../Utilities/SwarmException.h"

#include <iostream>

using namespace std;

Logger::Logger( ostream *out )
{
  if( out )
    setOutStream( out );
}

void Logger::setOutStream( ostream *out )
{
  if( !out )
    throw SwarmException( "(Logger::Logger) invalid ostream" );

  m_lastWChannel = -1;
  m_out = out;
}

void Logger::addNewCycleTag( int cycle )
{
  (*m_out) << "[" << cycle << "]" << endl;
}

ostream &Logger::operator[]( int channel )
{
  if( !m_out )
    throw SwarmException( "(Logger::Logger) invalid ostream" );    

  if( channel != m_lastWChannel )
  {
    m_lastWChannel = channel;
    (*m_out) << endl << channel << ":";
  }

  return (*m_out);
}

Logger logger;

/*
#include <fstream>

int main()
{
  ofstream stream( "test.txt" );

  Logger logger( &stream );

  logger[10] << "test " << endl;

  for( int i = 0; i < 10; i ++ )
    logger[10] << i << endl;

  stream.close();

  return 1;
}
*/
