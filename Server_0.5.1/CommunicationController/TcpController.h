#ifndef __TCP_CONTROLLER_H
#define __TCP_CONTROLLER_H

#include "CommunicationController/CommunicationController.h"
#include "CommunicationController/Tcp/ClientSocket.h"
#include <vector>

class TcpController : public CommunicationController
{
  Q_OBJECT
public:
  TcpController( QObject *parent = 0 );
  ~TcpController();

  void sendMessage( unsigned indx, std::string msg );
  void disconnectClient( unsigned indx );
  unsigned getNumOfClients() const;

private:
  void incomingConnection( int socketf );

  std::vector<ClientSocket *> m_clients;

private slots:
  void forwardClientDisconnected( unsigned indx );
  void forwardMessageReceived( unsigned indx, std::string msg );

};

#endif

