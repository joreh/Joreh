#ifndef __AGENT_H
#define __AGENT_H

#include <QObject>
#include "Geom/Vector.h"
#include "Action/Action.h"
#include "WorldModel/WorldModel.h"
#include "Connection/Connection.h"
#include "MessageGenerator/MessageGenerator.h"
#include "Model/model.h"

class Agent : public QObject
{
Q_OBJECT
public:
  Agent( Connection *connection, WorldModel *worldModel );

  Action *decide();
  bool ParseModel(string,string);

public slots:
  void messageReceived( std::string msg );
  void disconnected();

private:
  Connection *m_connection;
  WorldModel *m_worldModel;
  MessageGenerator m_messageGenerator;
  Model *m_model;

  Vector3D m_bestLocalPos;
  double m_bestLocalFitness;

  Vector3D m_bestGlobalPos;
  double m_bestGlobalFitness;

};

#endif
