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
  srand( time( 0 ) );

  connect( m_connection, SIGNAL(messageReceived(std::string)),
           this, SLOT(messageReceived(std::string)) );
  connect( m_connection, SIGNAL(disconnected()),
           this, SLOT(disconnected()) );
}

void Agent::messageReceived( string msg )
{
  cout << msg << endl;
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
         // int itEnd;
         map<unsigned, map<int, int>::const_iterator> fast_random_lookup;
         map<int, int>::const_iterator it = m_worldModel->m_models.begin() , itEnd = m_worldModel->m_models.end();
         for (unsigned i = 0; it != itEnd; ++it, ++i) {
           fast_random_lookup[i] = it;
         }
          pair<int,int> v = *fast_random_lookup[rand()%m_worldModel->m_models.size()];
          QString a  = QString::number(v.first);
          cout<<"Creating new Agent with a class of "<<a.toAscii().data()<<endl;
          m_connection->sendData( InitAction( "team1", a.toStdString() ).toString() );
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
  cout << "agent is disconnected from the server" << endl;
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
  static double X=fRand(-100,100);
  static double Y=fRand(-100,100);
  cout<<"XXXXXXXXXXXXX "<<X<<" "<<Y<<endl<<"AG : "<<pos.getX()<<"  "<<pos.getY()<<endl;
  if( pow((pos.getX()-X),2)+pow((Y-pos.getY()),2)>4  ){
      cout<<"Hasn't Arrived!!"<<endl;
      return new WalkAction( X,Y );
  }
  else{
      X=fRand(-100,100);
      Y=fRand(-100,100);
  return new WalkAction(X,Y);
  }
/*
  Vector3D vel = obj.getVelocity();

  if( obj.getPosFitness() < m_bestLocalFitness )
  {
    m_bestLocalFitness = obj.getPosFitness();
    m_bestLocalPos = obj.getPosition();
  }

  for( unsigned i = 0; i < m_worldModel->getNumOfObjects(); i ++ )
  {
    const Object &particleObject = m_worldModel->getObjectByIndex( i );

    if( particleObject.getPosFitness() < m_bestGlobalFitness )
    {
      m_bestGlobalFitness = particleObject.getPosFitness();
      m_bestGlobalPos = particleObject.getPosition();
    }
  }


  vel = vel * ( 1000 - min( 1000, m_worldModel->getCurCycle() ) ) / 1000.0
        + ( m_bestLocalPos - obj.getPosition() ) * 2.0 * General::random( 0, 1.0 )
        + ( m_bestGlobalPos - obj.getPosition() ) * 2.0 * General::random( 0, 1.0 );

*/



}
