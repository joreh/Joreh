#ifndef __OBJECT_MANAGER_H
#define __OBJECT_MANAGER_H

#include "WorldModel/WorldModel.h"
#include "WorldModel/Object.h"
#include "GIS/DBServer.h"
#include "GIS/GISServer.h"
#include "GIS/MapSetParser.h"

#include <vector>

class InitCommand;
class MoveCommand;
class WalkCommand;
class RestCommand;
class ReadyCommand;
class RunCommand;
class EvadeCommand;
class ShootCommand;
class XShootCommand;
class MineCommand;
class DemineCommand;
class HealCommand;
class SupportCommand;
class StandCommand;
class LieCommand;
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

  void setModel(std::map<int,Model*> m);
  std::map<int,Model*> getModel();

  void handleInitCommand( Object *obj, InitCommand *initCmd );
  void handleMoveCommand( Object *obj, MoveCommand *moveCmd );
  void handleWalkCommand( Object *obj, WalkCommand *walkCmd );
  void handleRestCommand( Object *obj, RestCommand *restCmd );
  void handleReadyCommand( Object *obj, ReadyCommand *readyCmd );
  void handleRunCommand( Object *obj, RunCommand *runCmd );
  void handleEvadeCommand( Object *obj, EvadeCommand *evadeCmd );
  void handleShootCommand( Object *obj, ShootCommand *shootCmd );
  void handleXShootCommand( Object *obj, XShootCommand *xshootCmd );
  void handleMineCommand( Object *obj, MineCommand *mineCmd );
  void handleDemineCommand( Object *obj, DemineCommand *demineCmd );
  void handleHealCommand( Object *obj, HealCommand *healCmd );
  void handleSupportCommand( Object *obj, SupportCommand *supportCmd );
  void handleStandCommand( Object *obj, StandCommand *standCmd );
  void handleLieCommand( Object *obj, LieCommand *likeCmd );

  void updateObjectVelPos( Object *obj );
  void updateGISDBByModels();
  void updateObjectParameters( Object *obj, std::string cmdName );
  void updateObjectPostParameter( Object *obj, std::string cmdName );

private:
  WorldModel m_worldModel;
  std::vector<AgentCommands *> m_commandsBuffer;
  std::vector<AgentMessages *> m_messagesBuffer;
  std::map<int,Model*> m_models;
  AgentMessages *m_observerMessage;

  GIS::GISServer *m_gis;

};

#endif
