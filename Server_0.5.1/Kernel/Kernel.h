#ifndef __KERNEL_H
#define __KERNEL_H

#include "CommunicationController/CommunicationController.h"
#include "MessageGenerator/MessageGenerator.h"
#include "ObjectManager/ObjectManager.h"
#include "Model/model.h"

#include <map>
#include <string>
#include <QTimer>
#include <QObject>

class Kernel : public QObject
{
Q_OBJECT
public:
  Kernel();
  ~Kernel();

private slots:
  void agentMessageReceived( unsigned indx, std::string msg );
  void monitorMessageReceived( unsigned indx, std::string msg );

  void agentConnected( unsigned indx );
  void monitorConnected( unsigned indx );

  void agentDisconnected( unsigned indx );
  void monitorDisconnected( unsigned indx );

  void newCycle();

private:

  CommunicationController *m_agentsServer;
  CommunicationController *m_monitorsServer;

  ObjectManager m_objectManager;
  std::map<int,Model*> m_models;
  std::map<unsigned, unsigned> m_agentIndxIDMap;
  std::map<unsigned, unsigned> m_agentIDIndxMap;
  std::map<unsigned, bool> m_monitorInitMap;

  unsigned m_lastObserverID;

  MessageGenerator m_messageGenerator;

  QTimer m_timer;
};

#endif
