#include "Connection.h"

using namespace std;

Connection::Connection( QObject *parent )
    : QTcpServer( parent )
{
 if (!connect(this, SIGNAL(newConnection()), this,
SLOT(newConnection()))) 
         {
                        printf("connect failed\n");
         }


}
void Connection::newConnection()
{
 tcpServerConnection = nextPendingConnection();
 connect(tcpServerConnection , SIGNAL(readyRead()),this,SLOT(readyRead()));

 emit handleConnection(tcpServerConnection);

}

void Connection::clearBuffer()
{
  m_currentMsg = "";
}

string Connection::getLastMsg() const
{
  return m_currentMsg;
}

void Connection::readyRead()
{
  QDataStream in(tcpServerConnection);
  in.setVersion(QDataStream::Qt_4_0);

  if (m_blockSize == 0) {
    if (tcpServerConnection->bytesAvailable() < (int)sizeof(quint16))
      return;

    in >> m_blockSize;
  }

  if (tcpServerConnection->bytesAvailable() < m_blockSize)
    return;

  QString rcMsg;
  in >> rcMsg;
  m_currentMsg = rcMsg.toStdString();
  emit messageReceived(m_currentMsg);
}
/**
*function that send specifiec message to a connetion pointer
*
*@param clientConnection a pointer to tcpSocet Connected Connection
*
*@param message string format message to send to client
*/
void Connection::sendData(QTcpSocket* clientConnection,std::string message)
{

     QString qstr(message.c_str());

     QByteArray block;
     QDataStream out(&block, QIODevice::ReadWrite);
     out.setVersion(QDataStream::Qt_4_0);
     out << (quint16)0;
     out << qstr;
     out.device()->seek(0);
     out << (quint16)(block.size() - sizeof(quint16));


     clientConnection->write(block);
}

