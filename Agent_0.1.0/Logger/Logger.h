#ifndef __LOGGER_H
#define __LOGGER_H

#include <iostream>
#include <cstring>

/** \file Logger.h
 *
 * implementation of logger
 */ 


/** \brief Logger helps developers and users to trace the program easier
  *
  * This class redirect log data to an output stream with a few meaningful
  * tags that help developers to find out the process and data flows of
  * the application
  * the tags are organized in a way that helps debuging simulation servers
  */
class Logger
{
public:
  /** \brief Constructor function
    *
    * \param out the output stream
    *
    */
  Logger( std::ostream *out = NULL );

  /** \brief redirect output stream
    *
    * \param out the output stream
    */
  void setOutStream( std::ostream *out );

  /** \brief adds new simulation cycle tag to output stream
    *
    * \param cycle current cycle of simulation
    */
  void addNewCycleTag( int cycle );

  /** \brief the overloaded operator adds new channel tag to the output stream
    * when the channel changes
    *
    * \param channel new channel
    */
  std::ostream &operator[]( int channel );

private:
  /** \brief the output stream
    */
  std::ostream *m_out;

  /**
    * \brief last channel which wrote to the output
    */
  int m_lastWChannel;
};


extern Logger logger;

#endif

