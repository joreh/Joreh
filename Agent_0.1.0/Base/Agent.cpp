#include "Agent.h"
#include "Utilities/General.h"

#include <cstdlib>
#include <ctime>
#include <cmath>
#include <QString>
#include <QFile>
#include <QTextStream>

extern void update_world_model( std::string str, WorldModel *wm );

Agent::Agent( Connection *connection, WorldModel *worldModel )
{
  m_bestLocalFitness = 99999999;
  m_bestGlobalFitness = 99999999;
  m_model = new Model();
  m_connection = connection;
  m_worldModel = worldModel;
  srand( time(0) ); 
  connect( m_connection, SIGNAL(messageReceived(std::string)),
           this, SLOT(messageReceived(std::string)) );
  connect( m_connection, SIGNAL(disconnected()),
           this, SLOT(disconnected()) );
}

void Agent::messageReceived( string msg )
{
    for(int j=1;j<m_worldModel->getNumOfObjects();j++){
      cout<<"obj ID: "<<m_worldModel->getObject(j).getModelID()<<endl;
  }
  if(msg.find("(")== string::npos){
      if(! ParseModel(msg,"test") )abort();
      cout<<m_model->getAttribute("wellness").GetValue();
  }
  else{
      update_world_model( msg, m_worldModel );
      if(msg.find("models")!= string::npos ){
         // int itEnd;;
         // int itEnd;
         map<unsigned, map<int, int>::const_iterator> fast_random_lookup;
         map<int, int>::const_iterator it = m_worldModel->m_models.begin() , itEnd = m_worldModel->m_models.end();
         for (unsigned i = 0; it != itEnd; ++it, ++i) {
           fast_random_lookup[i] = it;
         }
		
		   pair<int,int> v = *fast_random_lookup[rand()%2];

	          QString a  = QString::number(v.first);
	  
     
          m_connection->sendData( InitAction( m_worldModel->getTeamName(), 
                                              a.toStdString() ).toString() );
      }
      else
      {
      Action *action = decide();
      m_connection->sendData( action->toString() );
      delete action;
      }
   }
}
bool Agent::ParseModel(string input,string filename)
{

    string fileplacce = "./Model/Models/"+filename+".xml";
    string f = filename+".xml";
    const QString fileplace = QString::fromStdString(fileplacce);
    QFile file(fileplace);
    if(file.exists())file.remove();
    file.open(QIODevice::Append | QIODevice::Text);
    QTextStream out(&file);
    out<<input.data();
    file.close();
    if(m_model->getModelFromFile(QString::fromStdString(f)))return true;
    return false;
}

void Agent::disconnected()
{
    abort();
}
double fRand(double fMin, double fMax)
{
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}
Action *Agent::decide()
{

  const Object &obj = m_worldModel->getObject( m_worldModel->getAgentID() );
  Vector3D pos =  obj.getPosition();
  static double X=0.0;
  static double Y=-0.8;
  
  if (m_worldModel->getCurCycle() == 0)
  {
	return new MoveAction(50,-50);
  }
  else
  {
	if( pos.getX() > 20 || pos.getY() > 20)
	{
		//return new StandAction();	

		if( obj.getModelID() == 13 )
		  	return new WalkAction(X,Y*-1);
	   	else 
			return new RunAction(X,Y*-1);
	}
	else
	{

		if( obj.getModelID() == 23 )
		  	return new WalkAction(X,Y);
	   	else 
			return new RunAction(X,Y);
	}
  }
}
