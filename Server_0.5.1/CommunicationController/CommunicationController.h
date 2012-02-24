#ifndef __COMMUNICATION_CONTROLLER_H
#define __COMMUNICATION_CONTROLLER_H

#include <QTcpServer>
#include <string>

class CommunicationController : public QTcpServer
{
Q_OBJECT
public:
  CommunicationController( QObject *parent )
        : QTcpServer( parent )
  {
  }

  virtual void sendMessage( unsigned indx, std::string msg ) = 0;

  virtual void disconnectClient( unsigned indx ) = 0;

  virtual unsigned getNumOfClients() const = 0;

signals:
  void messageReceived( unsigned indx, std::string msg );

  void clientConnected( unsigned indx );

  void clientDisconnected( unsigned indx );

};

#endif

