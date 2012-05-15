#include "WorldModel/WorldModel.h"
#include "Connection/Connection.h"
#include "Base/Agent.h"

#include <QCoreApplication>
#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

int main(int argc, char *argv[])
{
  QCoreApplication app( argc, argv );

  short portNum = 6178;
  string serverAddress = "127.0.0.1";

  string teamName = "Unknown";

  if( argc >=2 )
    teamName = argv[1];

  Connection connection;
  WorldModel worldModel;

  worldModel.setTeamName( teamName );

  connection.connectToHost(
      QHostAddress( serverAddress.c_str() ), portNum );

  if( !connection.waitForConnected() )
  {
    cerr << "can not find server" << endl;
    abort();
  }

  cout << "agent is connected to " << serverAddress << ":" << portNum << endl;

  Agent agent( &connection, &worldModel );

  return app.exec();
}
