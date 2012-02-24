#ifndef __CLIENT_SOCKET_H
#define __CLIENT_SOCKET_H

#include <QTcpSocket>

class ClientSocket : public QTcpSocket
{
  Q_OBJECT
public:
  ClientSocket( QObject *parent = 0 );

  void setIndx( unsigned indx );
  unsigned getIndx() const;

private:
  unsigned m_indx;

signals:
  void messageReceived( unsigned indx, std::string msg );
  void clientDisconnected( unsigned indx );


private slots:
  void readClient();
  void disconnectedClient();
};

#endif

