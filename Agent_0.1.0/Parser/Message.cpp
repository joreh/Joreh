#include "Message.h"
#include "../Utilities/SwarmException.h"

#include <sstream>

using namespace std;

/******************************************************************************
 * ***************************** Message class ********************************
 * ****************************************************************************
 */

Message::~Message()
{
}

/******************************************************************************
 * *************************** ConMessage class *******************************
 * ****************************************************************************
 */

ConMessage::ConMessage( unsigned id, double lx, double rx,
              double ty, double by )
{
  m_monID = id;
  m_lx = lx;
  m_rx = rx;
  m_ty = ty;
  m_by = by;
}

unsigned ConMessage::getMonitorID() const
{
  return m_monID;
}

double ConMessage::getLeftX() const
{
  return m_lx;
}

double ConMessage::getRightX() const
{
  return m_rx;
}

double ConMessage::getTopY() const
{
  return m_ty;
}

double ConMessage::getBottomY() const
{
  return m_by;
}

string ConMessage::toString() const
{
  ostringstream out;

  out << "(con " << getMonitorID() << " " << m_lx << " "
      << m_rx << " " << m_ty << " " << m_by << ")";

  return out.str();
}

string ConMessage::getMessageName() const
{
  return "ConMessage";
}

/******************************************************************************
 * *************************** SeeMessage class *******************************
 * ****************************************************************************
 */

InterObject::InterObject( unsigned _id, double _x, double _y )
{
  id = _id;
  x = _x;
  y = _y;
}


SeeMessage::SeeMessage()
{
  m_simTime = 0;
}

void SeeMessage::setSimTime( unsigned time )
{
  m_simTime = time;
}

unsigned SeeMessage::getSimTime() const
{
  return m_simTime;
}

void SeeMessage::addObject( InterObject obj )
{
  m_objects.push_back( obj );
}

const InterObject &SeeMessage::getObject( unsigned indx ) const
{
  if( indx >= m_objects.size() )
    throw SwarmException( "(SeeMessage) index out of bound" );

  return m_objects[indx];
}

unsigned SeeMessage::getNumOfObjects() const
{
  return m_objects.size();
}

string SeeMessage::toString() const
{
  ostringstream out;

  out << "(see " << getSimTime() << " ";

  for( unsigned i = 0; i < getNumOfObjects(); i ++ )
    out << "(" << m_objects[i].id << " "
       << m_objects[i].x << " " << m_objects[i].y << ")";

  out << ")";

  return out.str();
}

string SeeMessage::getMessageName() const
{
  return "SeeMessage";
}

/******************************************************************************
 * *************************** DisMessage class *******************************
 * ****************************************************************************
 */

DisMessage::DisMessage()
{
}

string DisMessage::toString() const
{
  return "(dis)";
}

string DisMessage::getMessageName() const
{
  return "DisMessage";
}
