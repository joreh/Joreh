#ifndef GISSERVER_H
#define GISSERVER_H

#include <QFileInfo>
#include "DBServer.h"
#include <map>
#include <string>


namespace GIS{



    class GISServer
    {
    public:

        GISServer(QString ConfigFile);
        ~GISServer();

        // mapSetFile is the info of a mapset's xml file,
        // this function add that to database
        bool LoadMapSet(QString mapSetFile);

        // this function create the dynamic layers (agents, teams, ...) in db
        bool CreateDLTables();

        // if the mapset already loaded in db retuens true
        bool SearchForMapSet(QString mapsetName);

        // this function load the SGIS-DL-Standard.xml into AgentType
        bool LoadStandardList(QString StandardFile);

//        double getHeight( Vector3D pos ) const;
//        bool isObservable( Vector3D orgPos, Vector3D destPos ) const;
//        bool canGo( Vector3D source, Vector3D target ) const;
//        GroundType getGroundType( Vector3D pos ) const;
//        Map getMap() const;

//        void update();

        // initialize team in db
        bool InitTeam( QString id,QString teamName,QString color);
        bool InitTeam( int id,QString teamName,QString color);

        //initialize Agent in db
        bool InitAgent( QString id, QString TypeID, QString TeamID,  QString lat, QString lon, QString life, QString startViewAngle, QString endViewAngle);
        bool InitAgent( int id, int TypeID, int TeamID,  float lon, float lat, int life, float startViewAngle, float endViewAngle);

        bool UpdateAgentsGroundType();
        bool UpdateAgentsView(float radi);

        bool IsObservable(int id1, int id2, float dist, QString gType);


        bool UpdateAgentPos(int id, double lon, double lat, double life = 1000, float startViewAngle = 0, float endViewAngle = 360);

        DBServer *db;

        vector<vector<int> > agentGroundTypes;
        vector<vector<std::string> > agentGroundTypesByName;
        vector<vector<int> > agentView;
        int maxX, minX, maxY, minY;

    private:
        GISServer();
        QString serverName;
        QString dbName;
        QString dbUserName;
        QString dbPassword;
        QString dlSchemaName;
        QString commonSchemaName;
        QString mapsetSchemaName;
        QString tempSchemaName;
        QString GroundTypeMap[100];

        int maxAgentID;

    };


}

#endif // GISSERVER_H
