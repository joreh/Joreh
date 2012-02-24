#include "CommunicationController/TcpController.h"
#include "Utilities/SwarmException.h"

using namespace std;

TcpController::TcpController( QObject *parent )
             : CommunicationController( parent )
{
}

TcpController::~TcpController()
{
  for( vector<ClientSocket *>::iterator itr = m_clients.begin();
        itr != m_clients.end(); itr ++ )
  {
    (*itr)->close();
    delete *itr;
  }
}

void TcpController::sendMessage( unsigned indx, string msg )
{
  if( indx >= (unsigned)m_clients.size() )
    throw SwarmException( "(TcpController::sendMessage) index out of bound" );

  if( !m_clients[indx] )
    throw SwarmException( "(TcpController::sendMessage) client is disconnected" );

  m_clients[indx]->write( ( msg + "\n" ).c_str() );
}

void TcpController::disconnectClient( unsigned indx )
{
  if( indx >= (unsigned)m_clients.size() )
    throw SwarmException( "(TcpController::sendMessage) index out of bound" );

  m_clients[indx]->close();
  m_clients[indx] = NULL;
}

unsigned TcpController::getNumOfClients() const
{
  return m_clients.size();
}

void TcpController::incomingConnection( int socketfd )
{
  ClientSocket *client = new ClientSocket( this );
  client->setSocketDescriptor( socketfd );

  client->setIndx( m_clients.size() );
  m_clients.push_back( client );

  connect( client, SIGNAL(messageReceived(unsigned, std::string)), this,
                   SLOT(forwardMessageReceived(unsigned, std::string)) );
  connect( client, SIGNAL(clientDisconnected(unsigned)),
           this, SLOT(forwardClientDisconnected(unsigned)) );

  emit clientConnected( client->getIndx() );
}

void TcpController::forwardClientDisconnected( unsigned indx )
{
  emit clientDisconnected( indx );
}

void TcpController::forwardMessageReceived( unsigned indx, string msg )
{
  emit messageReceived( indx, msg );
}

