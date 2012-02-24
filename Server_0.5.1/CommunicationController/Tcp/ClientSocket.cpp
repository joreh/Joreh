#include "CommunicationController/Tcp/ClientSocket.h"


ClientSocket::ClientSocket( QObject *parent )
             : QTcpSocket( parent )
{
  m_indx = 0;

  connect( this, SIGNAL(readyRead()), this, SLOT(readClient()) );
  connect( this, SIGNAL(disconnected()), this, SLOT(disconnectedClient()) );
}

void ClientSocket::setIndx( unsigned indx )
{
  m_indx = indx;
}

unsigned ClientSocket::getIndx() const
{
  return m_indx;
}

void ClientSocket::readClient()
{
  while( canReadLine() )
  {
    QString lineStr = QString::fromUtf8(readLine()).trimmed();
    emit messageReceived( m_indx, lineStr.toStdString() );
  }
}

void ClientSocket::disconnectedClient()
{
  emit clientDisconnected( m_indx );
}



