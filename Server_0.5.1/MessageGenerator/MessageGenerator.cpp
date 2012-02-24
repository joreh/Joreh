#include "MessageGenerator.h"

using namespace std;

MessageGenerator::MessageGenerator()
{
  clearBuffer();
}

void MessageGenerator::addMessageParam( string strMessage )
{
  m_strBuf = m_strBuf + strMessage;
  m_numParameters ++;
}

unsigned MessageGenerator::getNumOfParameter() const
{
  return m_numParameters;
}

void MessageGenerator::clearBuffer()
{
  m_strBuf = "(";
  m_numParameters = 0;
}

string MessageGenerator::toString() const
{
  return m_strBuf + ")";
}

