#include "ServerMessage.h"

using namespace std;

ServerMessage::ServerMessage()
{
  m_chkClosedBuff = false;
  m_strBuf << showpoint << fixed;
}

void ServerMessage::closeBuf()
{
  m_chkClosedBuff = true;
  m_strBuf << ")";
}

bool ServerMessage::isBufClosed() const
{
  return m_chkClosedBuff;
}

ServerMessage::~ServerMessage()
{
}

string ServerMessage::toString() const
{
  if( isBufClosed() )
    return m_strBuf.str();

  // log
  return "";
}

/**************************************************************
 *************************** See Message **********************
 **************************************************************
 */

SeeMessage::SeeMessage( int cycle )
{
  m_strBuf << "(see " << cycle;
}

void SeeMessage::addSeeParam( int objectID, double x, double y,
                             double fittness, int mId )
{
  m_strBuf << "(" << objectID << " " << x
           << " " << y << " "<< fittness << " " << mId << ")";
}

string SeeMessage::getClassName() const
{
  return "SeeMessage";
}


/**************************************************************
 *************************** Con Message **********************
 **************************************************************
 */

ConMessage::ConMessage( unsigned id, double lx, double rx,
                        double ty, double by                 )
{
  m_strBuf << "(con " << id << " " << lx << " " << rx << " "
           << ty << " " << by;
  closeBuf();
}

string ConMessage::getClassName() const
{
  return "ConMessage";
}


/**************************************************************
 ************************ AStatus Message *********************
 **************************************************************
 */

AStatusMessage::AStatusMessage( double x, double y, double fitness )
{
  m_strBuf << "(agent (" << x << " " << y << " " << fitness << ")";

  closeBuf();
}

string AStatusMessage::getClassName() const
{
  return "AStatusMessage";
}


/**************************************************************
 ************************ Model Message *********************
 **************************************************************
 */

ModelMessage::ModelMessage( std::map<int,Model*> models )
{
  m_strBuf << "(models ";


 for( map<int, Model*>::iterator itr = models.begin();
            itr != models.end(); itr ++ )
 {

      m_strBuf << "(" << models[itr->first]->getID() << " "
                  << models[itr->first]->getNumber() << ")";
 }


  closeBuf();
}

string ModelMessage::getClassName() const
{
  return "ModelMessage";
}

/**************************************************************
 *************************** Bye Message **********************
 **************************************************************
 */

ByeMessage::ByeMessage()
{
  m_strBuf << "(bye";

  closeBuf();
}

string ByeMessage::getClassName() const
{
  return "ByeMessage";
}


