#include "Connection.h"

using namespace std;

Connection::Connection( QObject *parent )
    : QTcpSocket( parent )
{
    connect( this, SIGNAL(readyRead()), this, SLOT(readClient()) );
    m_blockSize = 0;
}

void Connection::readClient()
{
  while( canReadLine() )
  {
    m_currentMsg = QString::fromUtf8(readLine()).trimmed().toStdString();
    emit messageReceived( m_currentMsg );
  }
}

void Connection::clearBuffer()
{
  m_currentMsg = "";
}

string Connection::getLastMsg() const
{
  return m_currentMsg;
}

void Connection::sendData( string message )
{
  write( ( message + "\n" ).c_str() );
  flush();
}
