#ifndef __CONNECTION_H
#define __CONNECTION_H 

#include <string>
#include <QObject>
#include <QtNetwork>
#include <QTcpServer>
#include <QTcpSocket>

class Connection : public QTcpSocket
{
  Q_OBJECT
public:
  Connection( QObject *parent = 0 );

  void clearBuffer();

  std::string getLastMsg() const;
  void sendData( std::string message );

signals:
  void messageReceived( std::string msg );

private slots:
  void readClient();

private:
  quint16 m_blockSize;
  std::string m_currentMsg;
};

#endif
