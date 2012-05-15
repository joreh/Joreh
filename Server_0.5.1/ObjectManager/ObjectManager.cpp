#include "ObjectManager/ObjectManager.h"
#include "ObjectManager/ObjectParameters.h"

#include "MessageGenerator/ServerMessage.h"
#include "Utilities/SwarmException.h"
#include "Utilities/General.h"
#include "Parser/Command.h"

#include <ctime>
#include <cstdlib>
#include <iostream>
#include <sstream>

using namespace std;

ObjectManager::ObjectManager()
{

  m_gis = new GIS::GISServer( "ConfFiles/GISServer_config.txt" );
  m_gis->db->RunQueryFile( "ConfFiles/Init_SGISdb.sql" );
  m_gis->LoadMapSet( "ConfFiles/ShapeFile/test.xml" );
  m_gis->LoadStandardList( "ConfFiles/SGIS-Type-Standard.xml" );

  m_worldModel.setField().setFieldGeom(
                          m_gis->minX, m_gis->maxX, 
                          m_gis->minY, m_gis->maxY );

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

  cout << mid << endl;

  m_worldModel.addObject( Object( m_worldModel.getNumOfObjects() + 1,
      Vector3D( General::random( minX, maxX ),
                General::random( minY, maxY ), 0.0 ),Vector3D(0,0,0),
                initCmd->getTeamName(), m_models[mid]) );

  cout << initCmd->getTeamName() << endl;

  unsigned teamId = 
         m_worldModel.setupTeam( initCmd->getTeamName() );

  if( teamId )
  {
    map<string, string> cols;
    ostringstream sstream;
    sstream << teamId;
    cols["id"] = "\'" + sstream.str() + "\'";
    cols["name"] = "\'" + initCmd->getTeamName() + "\'";
    cols["color"] = "\'" + 
           string(teamId % 2 ? "AA0000" : "0000AA") + "\'";
    m_gis->db->Insert( "sgis_dl", "Team", cols );
  }

  teamId = m_worldModel.getTeamId( initCmd->getTeamName() );
  m_gis->InitAgent( m_worldModel.getNumOfObjects(), mid, teamId, 0.0, 0.0,
                    m_models[mid]->getValue( "wellness" ), 0.0, 360.0 );

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

  std::vector<Object> objects;

  for( unsigned i = 1; i <= m_worldModel.getNumOfObjects(); i ++ )
    objects.push_back( m_worldModel.getObject( i ) );

  for( unsigned i = 0; i < m_commandsBuffer.size(); i ++ )
  {
    m_messagesBuffer[i] = new vector<ServerMessage *>();
    Object &obj = objects[i];

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
      else if( dynamic_cast<MoveCommand *>(cmd)  )
      {
        if( m_worldModel.getCurCycle() == 0 )
        {
          cout << "process move command for agent " << i + 1 << endl;
          handleMoveCommand( &obj, (MoveCommand *)cmd );
        }
      }
      else
      {
        updateObjectParameters( &obj, cmd->getCommandName() );

        if( dynamic_cast<WalkCommand *>(cmd) )
        {
          cout << "process walk command for agent " << i + 1 << endl;

          handleWalkCommand( &obj, (WalkCommand *)cmd );
        }
        else if( dynamic_cast<RunCommand *>(cmd) )
        {
          cout << "process run command for agent " << i + 1 << endl;

          handleRunCommand( &obj, (RunCommand *)cmd );
        }
        else if( dynamic_cast<ReadyCommand *>(cmd) )
        {
          cout << "process ready command for agent " << i + 1 << endl;

          handleReadyCommand( &obj, (ReadyCommand *)cmd );
        }
        else if( dynamic_cast<StandCommand *>(cmd) )
        {
          cout << "process stand command for agent " << i + 1 << endl;

          handleStandCommand( &obj, (StandCommand *)cmd );
        }
        else if( dynamic_cast<EvadeCommand *>(cmd) )
        {
          cout << "process evade command for agent " << i + 1 << endl;

          handleEvadeCommand( &obj, (EvadeCommand *)cmd );
        }       
        else if( dynamic_cast<MineCommand *>(cmd) )
        {
          cout << "process mine command for agent " << i + 1 << endl;

          handleMineCommand( &obj, (MineCommand *)cmd );
        }
        else if( dynamic_cast<DemineCommand *>(cmd) )
        {
          cout << "process demine command for agent " << i + 1 << endl;

          handleDemineCommand( &obj, (DemineCommand *)cmd );
        }
        else if( dynamic_cast<LieCommand *>(cmd) )
        {
          cout << "process lie command for agent " << i + 1 << endl;

          handleLieCommand( &obj, (LieCommand *)cmd );
        }       
        else if( dynamic_cast<SupportCommand *>(cmd) )
        {
          cout << "process support command for agent " << i + 1 << endl;
          handleSupportCommand( &obj, (SupportCommand *)cmd );
        }       
        else if( dynamic_cast<HealCommand *>(cmd) )
        {
          cout << "process heal command for agent " << i + 1 << endl;

          handleHealCommand( &obj, (HealCommand *)cmd );
        }
        else if( dynamic_cast<ShootCommand *>(cmd) )
        {
          cout << "process shoot command for agent " << i + 1 << endl;
          handleShootCommand( &obj, (ShootCommand *)cmd );
        }
        else if( dynamic_cast<XShootCommand *>(cmd) )
        {
          cout << "process xshoot command for agent " << i + 1 << endl;
          handleXShootCommand( &obj, (XShootCommand *)cmd );
        }


     }


      for( vector<Command *>::iterator itr = m_commandsBuffer[i]->begin();
           itr != m_commandsBuffer[i]->end(); itr ++ )
        delete (*itr);

      delete m_commandsBuffer[i];
      m_commandsBuffer[i] = NULL;

    }

    updateObjectVelPos( &objects[i] );
    cout << "pos: " << objects[i].getPosition() << endl;
    m_gis->UpdateAgentPos( objects[i].getID(), objects[i].getPosition().getX(),
                               objects[i].getPosition().getY(),
                               objects[i].getAttrVal( "wellness" ) );
 

//    obj.setPosFitness( m_worldModel.getField().getPosFitness(
//          obj.getPosition().getX(), obj.getPosition().getY() ) );
  }


  m_gis->UpdateAgentsGroundType();

  unsigned id;
  bool bTest;
  bool bMine;

  for( unsigned i = 1; i <= m_worldModel.getNumOfObjects(); i ++ )
  {
    id = objects[i-1].getID();
    bTest = false;
    bMine = false;

    for( vector<string>::iterator itr = 
                 m_gis->agentGroundTypesByName[id].begin();
         itr != m_gis->agentGroundTypesByName[id].end(); itr ++ )
    {
      if( *itr == "lake" || *itr == "rocky" || *itr == "river" ||
          *itr == "mountain" || *itr == "swamp" )
        bTest = true;
      if( *itr == "mine" )
        bMine = true;
    }


    if( bMine )
    {
      // agent should be killed To Do
      bTest = true;
    }

    if( bTest )
    {
      m_gis->UpdateAgentPos( objects[i-1].getID(), 
             m_worldModel.getObject( i ).getPosition().getX(),
             m_worldModel.getObject( i ).getPosition().getY(),
             m_worldModel.setObject( i ).getAttrVal( "wellness" ) );
      m_worldModel.setObject( i ).setVelocity( Vector3D( 0.0, 0.0 ) );
    }
    else 
      m_worldModel.setObject( i ) = objects[i-1];
  }

  m_gis->UpdateAgentsGroundType();

  {
    m_observerMessage = new vector<ServerMessage *>;


    SeeMessage *seeMessage =  new SeeMessage( m_worldModel.getCurCycle() );

    for( unsigned i = 1; i <= m_worldModel.getNumOfObjects(); i ++ )
    {
      seeMessage->addSeeParam( i,
          m_worldModel.getObject(i).getPosition().getX(),
          m_worldModel.getObject(i).getPosition().getY(),
          1.0, m_worldModel.getObject(i).getModel()->getID() );
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
          1.0, m_worldModel.getObject(j).getModel()->getID() );
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

void ObjectManager::setModel(std::map<int,Model*> m)
{
    m_models = m;
}

std::map<int,Model*> ObjectManager::getModel()
{
    return m_models;
}

void ObjectManager::handleInitCommand( Object *obj, 
                                     InitCommand *initCmd )
{

}

void ObjectManager::handleMoveCommand( Object *obj, 
                                      MoveCommand *moveCmd )
{
  obj->setPosition(
          Vector3D( moveCmd->getX(), moveCmd->getY() ) );
  obj->setVelocity( Vector3D( 0.0, 0.0 ) );
}

void ObjectManager::handleWalkCommand( Object *obj, 
                                      WalkCommand *walkCmd )
{
  Vector3D velocity( walkCmd->getVelX(), walkCmd->getVelY() );
  obj->setVelocity( velocity );

}

void ObjectManager::handleRestCommand( Object *obj, 
                                      RestCommand *restCmd )
{

}

void ObjectManager::handleReadyCommand( Object *obj, 
                                       ReadyCommand *readyCmd )
{

}

void ObjectManager::handleRunCommand( Object *obj, 
                                     RunCommand *runCmd )
{
  Vector3D velocity( runCmd->getVelX(), runCmd->getVelY() );
  obj->setVelocity( velocity );
}

void ObjectManager::handleEvadeCommand( Object *obj, 
                                       EvadeCommand *evadeCmd )
{
  Vector3D velocity( evadeCmd->getVelX(), evadeCmd->getVelY() );
  obj->setVelocity( velocity );
}

void ObjectManager::handleShootCommand( Object *obj, 
                                       ShootCommand *shootCmd )
{

}

void ObjectManager::handleXShootCommand( Object *obj, 
                                        XShootCommand *xshootCmd )
{

}

void ObjectManager::handleMineCommand( Object *obj, 
                                      MineCommand *mineCmd )
{

}

void ObjectManager::handleDemineCommand( Object *obj, 
                                        DemineCommand *demineCmd )
{

}

void ObjectManager::handleHealCommand( Object *obj, 
                                      HealCommand *healCmd )
{

}

void ObjectManager::handleSupportCommand( Object *obj, 
                                         SupportCommand *supportCmd )
{

}

void ObjectManager::handleStandCommand( Object *obj, 
                                       StandCommand *standCmd )
{
}

void ObjectManager::handleLieCommand( Object *obj, 
                                     LieCommand *likeCmd )
{
}

void ObjectManager::updateGISDBByModels()
{
  ostringstream stream;

  for( map<int, Model *>::iterator itr = m_models.begin();
       itr != m_models.end(); itr ++ )
  {
    map<string, string> cols;

    stream.str( "" );
    stream << itr->first;
    cols["id"] = stream.str();
    stream.str( "" );
    cols["name"] = "\'" + itr->second->getName().toStdString() + "\'";
    cols["color"] = "\'" + itr->second->getColor().toStdString() + "\'";
    cols["description"] = "\'" + itr->second->getDesc().toStdString() + "\'"; 

    m_gis->db->Insert( "sgis_common", "AgentType", cols );
  }  

}

void ObjectManager::updateObjectVelPos( Object *obj )
{
  Vector3D velocity = obj->getVelocity();

  unsigned id = obj->getID();
  unsigned maxTypes = m_gis->agentGroundTypesByName[id].size();

  double grdEff = 1.0;

  for( unsigned i = 0; i < maxTypes; i ++ )
    grdEff = min( grdEff, (*ObjectParameters::groundEffect)
               [m_gis->agentGroundTypesByName[id][i]]["soldier"] );
  

  velocity *= obj->getAttrVal( "speed" ) * 
                    (*ObjectParameters::wheatherEffect)["sunny"]["soldier"] *
                    grdEff * ( 1.0 - obj->getAttrVal( "tiredness" ) ) *
                    obj->getAttrVal( "wellness" );


  if( velocity.getMagnitude() > obj->getModel()->getValue( "speed" ) )
    velocity.setMagnitude( obj->getModel()->getValue( "speed" ) );


  obj->setPosition( obj->getPosition() + velocity );
}

void ObjectManager::updateObjectParameters( Object *obj, string cmdName )
{
 
  if( ObjectParameters::solActEffect->find( cmdName ) == 
      ObjectParameters::solActEffect->end() )
    return;

  for( map<string, double>::iterator itr = 
       (*ObjectParameters::solActEffect)[cmdName].begin();
       itr != (*ObjectParameters::solActEffect)[cmdName].end(); itr ++ )
    obj->setAttrVal( itr->first, itr->second );
}

void ObjectManager::updateObjectPostParameter( Object *obj, string cmdName )
{
 
  if( ObjectParameters::solActEffect->find( cmdName ) == 
      ObjectParameters::solActEffect->end() )
    return;

  obj->setAttrVal( "tiredness",
          General::stableNum( obj->getAttrVal( "tiredness" ) +
          obj->getAttrVal( "tiredness_delay" ) , 0.0, 1.0 ) );
  obj->setAttrVal( "wellness",
          General::stableNum( obj->getAttrVal( "wellness" ) +
          obj->getAttrVal( "wellness_delay" ), 0.0, 1.0 ) );
  obj->setAttrVal( "spirit",
          General::stableNum( obj->getAttrVal( "spirit" ) +
          obj->getAttrVal( "spirit_delay" ) , 0.0, 1.0 ) );
  obj->setAttrVal( "stress",
          General::stableNum( obj->getAttrVal( "stress" ) +
          obj->getAttrVal( "stress_delay" ), 0.0, 1.0 ) );



}

