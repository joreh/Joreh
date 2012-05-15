#include "Kernel/Kernel.h"
#include "Parser/CommandParser.h"
#include "MessageGenerator/ServerMessage.h"
#include "CommunicationController/TcpController.h"
#include "ObjectManager/ObjectParameters.h"

#include <vector>
#include <QDir>
#include <iostream>

using namespace std;

Kernel::Kernel()
      : m_timer( this )
{
  m_initWait = 0;
  ObjectParameters::initParameters();

  /* Read the Models : By Milad */
  
  QDir dir("Model/Models");
  dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
  dir.setSorting(QDir::Size | QDir::Reversed);
  QFileInfoList list = dir.entryInfoList();
  
  for (int i = 0; i < list.size(); ++i) {
    Model * m = new Model(QString( (list.at(i).baseName().toStdString()+".xml").c_str()));
    m_models[m->getID()] = m;
   }

  m_objectManager.setModel( m_models );
  m_objectManager.updateGISDBByModels();
  m_lastObserverID = 0;

  m_agentsServer = new TcpController( this );
  m_monitorsServer = new TcpController( this );

  m_agentsServer->listen( QHostAddress::Any, 6178 );
  m_monitorsServer->listen( QHostAddress::Any, 6179 );

  connect( m_agentsServer, SIGNAL(messageReceived(unsigned, std::string)),
           this, SLOT(agentMessageReceived(unsigned, std::string)) );
  connect( m_monitorsServer, SIGNAL(messageReceived(unsigned, std::string)),
           this, SLOT(monitorMessageReceived(unsigned, std::string)) );

  connect( m_agentsServer, SIGNAL(clientConnected(unsigned)),
           this, SLOT(agentConnected(unsigned)) );
  connect( m_monitorsServer, SIGNAL(clientConnected(unsigned)),
           this, SLOT(monitorConnected(unsigned)) );

  connect( m_agentsServer, SIGNAL(clientDisconnected(unsigned)),
             this, SLOT(agentDisconnected(unsigned)) );
  connect( m_monitorsServer, SIGNAL(clientDisconnected(unsigned)),
             this, SLOT(monitorDisconnected(unsigned)) );

  connect( &m_timer, SIGNAL(timeout()), this, SLOT(newCycle()) );
  m_timer.start( 200 );
}

Kernel::~Kernel()
{
  delete m_agentsServer;
  delete m_monitorsServer;

  for( map<int, Model *>::iterator itr = m_models.begin(); 
       itr != m_models.end(); itr ++ )
    delete itr->second;
}

void Kernel::agentMessageReceived( unsigned indx, string msg )
{
  vector<Command *> *commands = parseCommandMessage( msg );

  if( !commands->size() )
  {
    cerr << "could not parse the message " << msg << endl;
    return;
  }

  if( !m_agentIndxIDMap[indx] )
  {

    if( dynamic_cast<InitCommand *>(commands->back()) )
    {
      unsigned id = m_objectManager.registerNewAgent( commands );

      m_agentIDIndxMap[id] = indx;
      m_agentIndxIDMap[indx] = id;
    }
    else
    {
      cout << "agent " << indx << " didn't send init command" << endl;
      m_agentsServer->disconnectClient( indx );
    }

    return;
  }

  m_objectManager.pushAgentCommands( m_agentIndxIDMap[indx], commands );
}

void Kernel::monitorMessageReceived( unsigned indx, string msg )
{
  //cout << "monitor " << indx << " received" << msg << endl;

  vector<Command *> *commands = parseCommandMessage( msg );

  if( !m_monitorInitMap[indx] )
  {
    if( dynamic_cast<InitCommand *>(commands->back()) )
      m_monitorInitMap[indx] = true;
    else
    {
      //cout << "monitor " << indx << " didn't send init command" << endl;
      m_monitorsServer->disconnectClient( indx );
      return;
    }

    m_lastObserverID ++;

    const Field &field = m_objectManager.getWorldModel().getField();

    ConMessage conMessage( m_lastObserverID,
        field.getLeftX(), field.getRightX(), field.getTopY(), field.getBottomY() );

    m_monitorsServer->sendMessage( indx, "(" + conMessage.toString() + ")" );
  }
}

void Kernel::agentConnected( unsigned indx )
{
  cout << "an agent connected with id " << indx << endl;


  /*Sending model information to agent :By Milad*/

  ServerMessage *model_message = new ModelMessage(m_models);

  m_messageGenerator.addMessageParam(model_message->toString());

  m_agentsServer->sendMessage( indx, m_messageGenerator.toString() );
  cout << m_messageGenerator.toString() << endl;
  m_messageGenerator.clearBuffer();

  m_agentIndxIDMap[indx] = 0;

}
void Kernel::monitorConnected( unsigned indx )
{
  cout << "a monitor connected with id " << indx << endl;

  m_monitorInitMap[indx] = false;
}

void Kernel::agentDisconnected( unsigned indx )
{
  cout << "agent " << indx << " disconnected" << endl;
}

void Kernel::monitorDisconnected( unsigned indx )
{
  cout << "monitor " << indx << " disconnected" << endl;
}

void Kernel::newCycle()
{
  int curCycle = m_objectManager.getWorldModel().getCurCycle();

  if( curCycle == 0 )
  {
    if( m_initWait > 100 )
      curCycle ++;
    else
      m_initWait ++;
  }
  else
    curCycle ++;
  m_objectManager.update( curCycle );

  for( unsigned i = 1; i <=
      m_objectManager.getWorldModel().getNumOfObjects(); i ++ )
  {
    AgentMessages *messages = m_objectManager.popAgentMessages( i );

    for( AgentMessages::iterator itr = messages->begin();
        itr != messages->end(); itr ++ )
    {
      m_messageGenerator.addMessageParam( (*itr)->toString() );
      delete (*itr);
    }

    delete messages;

    m_agentsServer->sendMessage( m_agentIDIndxMap[i], m_messageGenerator.toString() );
    m_messageGenerator.clearBuffer();
  }

  AgentMessages *messages = m_objectManager.popObserverMessages();

  for( AgentMessages::iterator itr = messages->begin();
      itr != messages->end(); itr ++ )
  {
    m_messageGenerator.addMessageParam( (*itr)->toString() );
    delete (*itr);
  }

  delete messages;

  for( map<unsigned, bool>::iterator itr = m_monitorInitMap.begin();
        itr != m_monitorInitMap.end(); itr ++ )
  {
    if( itr->second )
      m_monitorsServer->sendMessage( itr->first, m_messageGenerator.toString() );
  }

  m_messageGenerator.clearBuffer();

}
