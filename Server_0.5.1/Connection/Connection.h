#ifndef __CONNECTION_H
#define __CONNECTION_H 

#include <string>
#include <QObject>
#include <QtNetwork>
#include <QTcpServer>
#include <QTcpSocket>

class Connection : public QTcpServer
{
  Q_OBJECT
public:
  Connection( QObject *parent = 0 );
  QTcpSocket* tcpServerConnection ;

  void clearBuffer();

  std::string getLastMsg() const;
  void sendData(QTcpSocket* client ,  std::string message );

signals:
  void messageReceived( std::string msg );
  void handleConnection( QTcpSocket* client);
private slots:
  void newConnection();
  void readyRead();
 

private:
  quint16 m_blockSize;
  std::string m_currentMsg;
};

#endif
