#ifndef __SWARM_EXCEPTION_H
#define __SWARM_EXCEPTION_H

#include <string>
#include <stdexcept>

/** \file implementation of exception
  *
  */

/** \brief This class helps to manage logical and run time errors
  * each instance of this class contains a string which can have
  * meaningful description of the happened error
  *
  */
class SwarmException : std::exception
{
public:
  /** \brief the constructor
    *
    * \param message is a string containing description of the error
    */
  SwarmException( std::string message );


  /** \brief the virtual desctructor
    *
    */
  virtual ~SwarmException() throw();

  /** \brief a get function to access the message of exception
    *
    * \returns the message
    */
  const char *what() const throw();

private:

  /** \brief the string which contains the error message
    */
  std::string m_message;

};

#endif

