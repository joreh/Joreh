#include "ObjectManager/ObjectManager.h"

#include "MessageGenerator/ServerMessage.h"
#include "Utilities/SwarmException.h"
#include "Utilities/General.h"
#include "Parser/Command.h"

#include <ctime>
#include <cstdlib>
#include <iostream>

using namespace std;

ObjectManager::ObjectManager()
{
  m_worldModel.setField().setFieldGeom( -100.0, 100.0, 100.0, -100.0 );

  srand( time( 0 ) );
}

unsigned ObjectManager::registerNewAgent( AgentCommands *commands )
{
  double minX = m_worldModel.getField().getLeftX();
  double maxX = m_worldModel.getField().getRightX();
  double maxY = m_worldModel.getField().getTopY();
  double minY = m_worldModel.getField().getBottomY  ();
  Command *cmd = commands->back();
  InitCommand *initCmd = dynamic_cast<InitCommand *>(cmd);
  int mid = atoi( initCmd->getModelName().substr(1).c_str());
  cout << mid;
  m_worldModel.addObject( Object( m_worldModel.getNumOfObjects() + 1,
      Vector3D( General::random( minX, maxX ),
                General::random( minY, maxY ), 0.0 ),Vector3D(0,0,0),mid ) );

  m_commandsBuffer.push_back( NULL );
  m_messagesBuffer.push_back( NULL );

  pushAgentCommands( m_worldModel.getNumOfObjects(), commands );

  return m_worldModel.getNumOfObjects();
}

void ObjectManager::pushAgentCommands( unsigned id, AgentCommands *commands )
{
  if( id == 0 || id > m_commandsBuffer.size() )
    throw SwarmException( "(ObjectManager::pushAgentCommands) invalid agent id" );

  if( commands->size() > 1 )
    cerr << "multiple commands received from agent " << id << endl;

  m_commandsBuffer[id-1] = commands;
}

AgentMessages *ObjectManager::popAgentMessages( unsigned id )
{
  if( id == 0 || id > m_commandsBuffer.size() )
    throw SwarmException( "(ObjectManager::pushAgentCommands) invalid agent id" );

  AgentMessages *retMessages = m_messagesBuffer[id-1];
  m_messagesBuffer[id-1] = NULL;
  return retMessages;
}

AgentMessages *ObjectManager::popObserverMessages()
{
  AgentMessages *retMessages = m_observerMessage;
  m_observerMessage = NULL;
  return retMessages;
}

void ObjectManager::update( int cycle )
{
  m_worldModel.setCurCycle( cycle );

  for( unsigned i = 0; i < m_commandsBuffer.size(); i ++ )
  {
    m_messagesBuffer[i] = new vector<ServerMessage *>();
    Object &obj = m_worldModel.setObject( i + 1 );

    if( m_commandsBuffer[i] == NULL )
    {
      //cout << "no command is received from agent " << i + 1 << endl;

      obj.setPosition( obj.getPosition() + obj.getVelocity() );
      obj.setVelocity( obj.getVelocity() * 0.9 );
    }
    else
    {

      Command *cmd = m_commandsBuffer[i]->back();

      if( dynamic_cast<InitCommand *>(cmd) )
      {
        //cout << "process init command for agent " << i + 1 << endl;

        m_messagesBuffer[i]->push_back(
            new ConMessage( obj.getID(),
                m_worldModel.getField().getLeftX(),
                m_worldModel.getField().getRightX(),
                m_worldModel.getField().getTopY(),
                m_worldModel.getField().getBottomY() ) );
      }
      else if( dynamic_cast<MoveCommand *>(cmd) &&
          m_worldModel.getCurCycle() > 0 )
      {
        //cout << "process move command for agent " << i + 1 << endl;

        MoveCommand *moveCmd = (MoveCommand *)cmd;
        obj.setPosition(
            m_worldModel.getField().modifyPositionOutBound(
            obj.getPosition() +
            Vector3D( moveCmd->getVelX(), moveCmd->getVelY() ) ) );
      }
      else if( dynamic_cast<WalkCommand *>(cmd) &&
          m_worldModel.getCurCycle() > 0 )
      {
        //cout << "process move command for agent " << i + 1 << endl;

        WalkCommand *walkCmd = (WalkCommand *)cmd;
        double oneSize =sqrt(pow(walkCmd->getVelX(),2) + pow(walkCmd->getVelY(),2));
        obj.setPosition(
            m_worldModel.getField().modifyPositionOutBound(
            obj.getPosition() +
            Vector3D( walkCmd->getVelX()/oneSize, walkCmd->getVelY()/oneSize ) ) );
      }

      for( vector<Command *>::iterator itr = m_commandsBuffer[i]->begin();
           itr != m_commandsBuffer[i]->end(); itr ++ )
        delete (*itr);

      delete m_commandsBuffer[i];
      m_commandsBuffer[i] = NULL;
    }

    obj.setPosFitness( m_worldModel.getField().getPosFitness(
          obj.getPosition().getX(), obj.getPosition().getY() ) );
  }

  {
    m_observerMessage = new vector<ServerMessage *>;


    SeeMessage *seeMessage =  new SeeMessage( m_worldModel.getCurCycle() );

    for( unsigned i = 1; i <= m_worldModel.getNumOfObjects(); i ++ )
    {
      seeMessage->addSeeParam( i,
          m_worldModel.getObject(i).getPosition().getX(),
          m_worldModel.getObject(i).getPosition().getY(),
          m_worldModel.getObject(i).getPosFitness(),m_worldModel.getObject(i).getModelId() );
    }

    seeMessage->closeBuf();

    m_observerMessage->push_back( seeMessage );
  }

  for( unsigned i = 0; i < m_worldModel.getNumOfObjects(); i ++ )
  {
    SeeMessage *seeMessage = new SeeMessage( m_worldModel.getCurCycle() );

    for( unsigned j = 1; j <= m_worldModel.getNumOfObjects(); j ++ )
    {
      seeMessage->addSeeParam( j,
          m_worldModel.getObject(j).getPosition().getX(),
          m_worldModel.getObject(j).getPosition().getY(),
          m_worldModel.getObject(j).getPosFitness(),m_worldModel.getObject(j).getModelId() );
    }

    seeMessage->closeBuf();

    m_messagesBuffer[i]->push_back( seeMessage );
  }

}

const WorldModel &ObjectManager::getWorldModel() const
{
  return m_worldModel;
}

WorldModel &ObjectManager::setWorldModel()
{
  return m_worldModel;
}
