#ifndef __MESSAGE_GENERATOR_H
#define __MESSAGE_GENERATOR_H

#include <string>

/** \brief this class mainain a set of messages in order to
  *        form a single complete message to send to agents
  *
  */
class MessageGenerator
{
public:

  /** \brief default constructor
    *
    */
  MessageGenerator();

  /** \brief a message param in whichi must be added to server message
    *
    * \param strMessage the message param
    */
  void addMessageParam( std::string strMessage );

  /** \brief shows how many parameters are added to the message generator
    *
    */
  unsigned getNumOfParameter() const;

  /** \brief clears message buffer
    *
    */
  void clearBuffer();

  /** \brief this function transform the messages to a single string
    *        which can be sent to the agents
    *
    * \returns message string
    */
  std::string toString() const;

private:
  std::string m_strBuf;
  unsigned m_numParameters;
};

#endif

