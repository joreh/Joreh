#include "SwarmException.h"
#include <iostream>

using std::string;

SwarmException::SwarmException( string message )
{
  m_message = message;
//  std::cout << message << std::endl;
}


SwarmException::~SwarmException() throw()
{

}

const char *SwarmException::what() const throw()
{
  return m_message.c_str();
}

