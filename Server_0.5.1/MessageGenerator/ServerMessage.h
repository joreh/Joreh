#ifndef __SERVER_MESSAGE_H
#define __SERVER_MESSAGE_H

#include <string>
#include <sstream>
#include "Model/model.h"

/** \brief an abstract class for Message structures which
  *        is used for buffering messages
  *
  */
class ServerMessage
{
public:

  /** \brief server message constructor
    *
    * \param objectID the id of object which message sould be
    *        send to
    */
  ServerMessage(); 


  /** \brief this function stop writing to the message buffer
    *
    *  warning : do not override this function
    *
    */
  void closeBuf();

  /** \brief checks the validity of the message buffer
    *
    *  warning : do not override this function
    * 
    * \returns true if the buffer is closed
    */
  bool isBufClosed() const;

  /** \brief ServerMessage destructor
    *
    */
  virtual ~ServerMessage();

  /** \brief a function that converts Message intra-parameters
    *        to a string
    *
    *  warning : do not override this function
    *
    * \returns converted string(message string)
    */
  virtual std::string toString() const;

  /** \brief an abstract function that returns class name
    *
    * \returns class name
    */
  virtual std::string getClassName() const = 0;


public:
  /** \brief string buffer for message
    *
    */
  std::ostringstream m_strBuf;



private:

  /** \brief a variable for checking buffer validitiy
    *
    */
  bool m_chkClosedBuff;
};

/** \brief the class makes the message which will be sent to the agents
  *        and monitor when they are connected to the server
  */
class ConMessage : public ServerMessage
{
public:

  /** \brief the constructor makes the message
    *
    * \param agent/monitor id
    * \param lx the left x-coordinate of the field
    * \param rx the right x-coordinate of the field
    * \param ty the top y-coordinate of the field
    * \param by the bottom y-coordinate of the field
    */
  ConMessage( unsigned id, double lx, double rx, double ty, double by );

  /** \brief a get function for class name
    *
    * \returns class name
    */
  std::string getClassName() const;

};

/** \brief a class which makes see messages
  *
  */
class SeeMessage : public ServerMessage
{
public:

  /** \brief SeeMessage constructor
    *
    * \param cycle current cycle of the server
    */
  SeeMessage( int cycle );

  /** \brief adds a new object status for sending see message
    *
    * \param objectID the id of the object which is seen
    * \param x x-coordinate of the object
    * \param y y-coordinate of the object
    * \param fitness fitness of the agent's position
    */
  void addSeeParam( int objectID, double x, double y,double fittness, int Mid );

  /** \brief a get function for class name
    *
    * \returns class name
    */
  std::string getClassName() const;

};

/** \brief this class makes a message containing agent status information
  *
  */
class AStatusMessage : public ServerMessage
{
public:

  /** \brief the constructor makes the message 
    *
    * \param x x-coordinate of the agent
    * \param y y-coordinate of the agent
    * \param fitness the fitness of the position in which agent is located
    */
  AStatusMessage( double x, double y, double fitness );

  /** \brief a get function for class name
    *
    * \returns class name
    */
  std::string getClassName() const;

};


/** \brief this class makes a message containing available models
  *
  */
class ModelMessage : public ServerMessage
{
public:

  /** \brief the constructor makes the ModelMessage
    *
    * \param models map containig model information
    */
 ModelMessage(  std::map<int,Model*> models );

  /** \brief a get function for class name
    *
    * \returns class name
    */
  std::string getClassName() const;

};

/** \brief a message which would be sent to the agent before diconnection
  *
  */
class ByeMessage : public ServerMessage
{
public:

  /** \brief theconstructor
    *
    */
  ByeMessage();

  /** \brief a get function for class name
    *
    * \returns class name
    */
  std::string getClassName() const;
  
};


#endif

