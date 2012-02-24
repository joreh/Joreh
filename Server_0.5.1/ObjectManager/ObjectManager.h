#ifndef __OBJECT_MANAGER_H
#define __OBJECT_MANAGER_H

#include "WorldModel/WorldModel.h"

#include <vector>

class Command;
class ServerMessage;
typedef std::vector<Command *> AgentCommands;
typedef std::vector<ServerMessage *> AgentMessages;

class ObjectManager
{
public:
  ObjectManager();

  unsigned registerNewAgent( AgentCommands *commands );
  void pushAgentCommands( unsigned id, AgentCommands *commands );

  AgentMessages *popAgentMessages( unsigned id );
  AgentMessages *popObserverMessages();

  void update( int cycle );

  const WorldModel &getWorldModel() const;
  WorldModel &setWorldModel();

private:
  WorldModel m_worldModel;
  std::vector<AgentCommands *> m_commandsBuffer;
  std::vector<AgentMessages *> m_messagesBuffer;

  AgentMessages *m_observerMessage;

};

#endif
