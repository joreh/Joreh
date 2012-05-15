#include "GISServer.h"
#include "MapSetParser.h"
#include "StandardsParser.h"
#include "GISUtility.h"
#include "DBServer.h"

#include <QDebug>
#include <QVariant>
#include <vector>

using namespace std;


namespace GIS
{

    GISServer::GISServer()
    {
        db = new GIS::DBServer();
        db->Connect("localhost", "GISdb", "postgres", "");

        //code to load mapsets and dynamic layers here ...

    }

    GISServer::GISServer(QString configFile)
    {
        qDebug() << "IN GISServer()";
        QFile config(configFile);
        if(!config.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            qDebug() << "Error in reading GISServer_config file";
            abort();
            return;
        }

        QTextStream ts(&config);
        QString line;
        while(!ts.atEnd())
        {
            line = ts.readLine();
            QStringList pair = line.split("=");
            if(pair[0] == "dbServerName")
                this->serverName = pair[1];
            if(pair[0] == "dbCatalogName")
                this->dbName = pair[1];
            if(pair[0] == "dbUserName")
                this->dbUserName = pair[1];
            if(pair[0] == "dbPassword")
                this->dbPassword = pair[1];
            if(pair[0] == "maxAgentID")
                this->maxAgentID = pair[1].toInt() + 1;
            qDebug() << pair[0] << " set to " << pair[1];
        }
        config.close();

        this->agentGroundTypes = vector< vector<int> >(this->maxAgentID, vector<int>());
        this->agentView = vector< vector<int> >(this->maxAgentID, vector<int>());
        this->dlSchemaName = "sgis_dl";
        this->mapsetSchemaName = "sgis_ms";
        this->commonSchemaName = "sgis_common";
        this->tempSchemaName = "sgis_temp";

        db = new GIS::DBServer();
        if(db->Connect(this->serverName, this->dbName, this->dbUserName,this->dbPassword))
            qDebug() << "GISServer successfully connected to db";

        //this->CreateDLTables();

        qDebug() << "OUT GISServer()";
    }

    GISServer::~GISServer()
    {
        delete db;
    }

    bool GISServer::LoadMapSet(QString mapSetFile)
    {
        qDebug() << "*** Loading Mapset *** " + mapSetFile;
        int j, k, p;

        QFile xml(mapSetFile);

        GIS::MapSetParser msp(&xml);

        GIS::MapsetData d = msp.GetData();

        this->maxX = d.mapSize.maxX;
        this->minX = d.mapSize.minX;
        this->maxY = d.mapSize.maxY;
        this->minY = d.mapSize.minY;



            // check that if the mapset already loaded
            QString schemaName = this->tempSchemaName;
            bool exists = false;
            if(db->CheckExistenceOfSchema(schemaName))
            {
                exists = true;
                qDebug() << schemaName << ' ' << "exists in database";
                // delete schema or ...
            }
            else
            {
                db->CreateSchemas(schemaName, db->userName);
            }

            //create shapefile tables
            for(j = 0; j < (int)d.shapefiles.size(); j++)
            {
                ShapefileData *s = &d.shapefiles[j];

                db->MakeShapeFileTable(s->address, schemaName, s->type, "Geom", exists);

                for(k = 0; k < (int)s->columns.size(); k++)
                {
                    ColumnData *c = &s->columns[k];
                    if(c->source != c->target && !db->MDL_RenameColumn(schemaName, s->type, c->source, c->target))
                        qDebug() << "Error in renaming column " + c->source;
                    for(p = 0; p < (int)c->mappings.size(); p++)
                    {
                        MappingData *mapping = &c->mappings[p];
                        if(!db->Update(schemaName, s->type, QStringList()
                                   << c->target <<"\'" + mapping->to + "\'",
                                   "gType = \'" + mapping->from + "\'"
                                   ))
                            qDebug() << "Error in Updating column " + c->source;
                    }
                }

                QString queryStr = "insert into \"" + this->mapsetSchemaName + "\".\"" + s->type
                        + "\"(id, gtype, geom) select id, gtype, geom from \"" + this->tempSchemaName +
                        "\".\"" + s->type + "\";";
                bool res;
                db->QQuery(queryStr, &res);
                if(!res)
                    qDebug() << "Error in importing shapefile";
            }

            for(j = 0; j < (int)d.rasterfiels.size(); j++)
            {
                RasterfileData *r = &d.rasterfiels[j];
                QString idStr;
                QTextStream ts(&idStr);
                ts << r->id;
                db->Insert(this->mapsetSchemaName, "raster", QStringList()
                           << "id" << idStr
                           << "rasterfile" << "\'"+r->address+"\'");
            }

        qDebug() << "Mapset List Loading complete";
        return true;
    }

    bool GISServer::LoadStandardList(QString StandardFile)
    {
        int i;

        QFile xml(StandardFile);

        GIS::StandardsParser agts(&xml);

        GIS::AgentstdData d = agts.GetData();
        GIS::GroundTypestdData gd = agts.GetGroundData();

        for(i = 0; i < (int)gd.GroundTypes.size(); i++)
        {
            GroundTypeData *g = &gd.GroundTypes[i];
            GroundTypeMap[g->id.toInt()] = g->name;
        }

        bool res = true;

        for(i = 0; i < (int)d.Agents.size(); i++)
        {
            AgentData *m = &d.Agents[i];
            //InsertIntoAgentTypeTable(m->name, "SGIS_Common", "AgentType", m->id, m->color, m->description);
            if( db->Insert(this->commonSchemaName, "AgentType",
                       QStringList()
                       << "id" << m->id
                       <<"name" << "\'" + m->name + "\'"
//                       <<"color" << "\'" + m->color + "\'"
//                       <<"discription" << "\'" + m->description + "\'"
                           ) == false)
                res = false;
        }
        return res;
    }

    bool GISServer::InitTeam(QString id, QString teamName, QString color)
    {
        return db->Insert(this->dlSchemaName, "Team", QStringList()
                                  << "id" << id
                                  <<"name" << "\'" + teamName + "\'"
                                  << "color" << "\'" + color + "\'"
                                  );
    }

    bool GISServer::InitTeam(int id, QString teamName, QString color)
    {
        QString idStr;
        QTextStream st(&idStr);
        st << id;
        return InitTeam(idStr, teamName, color);
    }

    bool GISServer::InitAgent( int id, int TypeID, int TeamID,  float lon, float lat, int life, float startViewAngle, float endViewAngle)
    {
        QString idStr, TypeIDStr, TeamIDStr, latStr, lonStr,
                lifeStr, startViewAngleStr, endViewAngleStr;
        QTextStream st(&idStr);
        st << id;
        st.setString(&TypeIDStr);
        st << TypeID;
        st.setString(&TeamIDStr);
        st << TeamID;
        st.setString(&latStr);
        st << lat;
        st.setString(&lonStr);
        st << lon;
        st.setString(&lifeStr);
        st << life;
        st.setString(&startViewAngleStr);
        st << startViewAngle;
        st.setString(&endViewAngleStr);
        st << endViewAngle;
        return InitAgent(idStr, TypeIDStr, TeamIDStr, latStr,lonStr ,lifeStr,startViewAngleStr, endViewAngleStr);
    }

    bool GISServer::InitAgent( QString id, QString TypeID, QString TeamID,  QString lat, QString lon, QString life, QString startViewAngle, QString endViewAngle)
    {
        bool res;
        // F_AgentInsert used to calculate g_pos column (geometry(point, 4326))
        db->RunFunction(this->commonSchemaName, "F_AgentInsert", QStringList()
            << id
            << TypeID
            << TeamID
            << lat
            << lon
            << life
            << startViewAngle
            << endViewAngle
               , &res
            );
        return res;
    }

    bool GISServer::IsObservable(int id1, int id2, float dist, QString gType="5")
    {
        bool res;
        QString id1Str, id2Str, distStr;

        QTextStream st(&id1Str);
        st << id1;
        st.setString(&id2Str);
        st << id2;
        st.setString(&distStr);
        st << dist;

        QSqlQuery *q = db->RunFunction(this->commonSchemaName, "F_IsObservable", QStringList()
                        << id1Str
                        << id2Str
                        << distStr
                        << gType
                        , &res
                        );
        q->next();
        if(q->value(0).toBool() == true)
            return true;
        else
            return false;

        return res;
    }

    bool GISServer::CreateDLTables()
    {
        return db->RunQueryFile("Init_DynamicLayer.sql");
    }

    bool GISServer::UpdateAgentPos(int id, double lon, double lat, double life, float startViewAngle, float endViewAngle)
    {
        QString idStr, latStr, lonStr, lifeStr,startViewAngleStr,endViewAngleStr;
        QTextStream ts(&idStr);
        ts << id;
        ts.setString(&latStr);
        ts << lat;
        ts.setString(&lonStr);
        ts << lon;
        ts.setString(&lifeStr);
        ts << life;
	ts.setString(&startViewAngleStr);
        ts << startViewAngle;
        ts.setString(&endViewAngleStr);
        ts << endViewAngle;

        bool res;
        db->RunFunction(this->commonSchemaName, "F_UpdateAgentPos", QStringList()
                       << idStr << latStr << lonStr << lifeStr << startViewAngleStr << endViewAngleStr, &res);
        return res;
    }

    bool GISServer::UpdateAgentsGroundType()
    {
        bool res;
        QSqlQuery *q = db->RunTableFunction("sgis_common", "F_GetAgentsGroundType", QStringList(), &res);

        agentGroundTypes = vector<vector <int> >(this->maxAgentID, vector<int>());

        while(q->next())
        {
            agentGroundTypes[q->value(0).toInt()].push_back(q->value(1).toInt());
            agentGroundTypesByName[q->value(0).toInt()].push_back(GroundTypeMap[q->value(1).toInt()].toStdString());
        }
        return res;
    }

    bool GISServer::UpdateAgentsView(float radi)
    {
        bool res;
        QString radiStr;
        QTextStream st(&radiStr);
        st << radi;
        QSqlQuery *q = db->RunTableFunction("sgis_common", "F_GetAgentsView",
                                            QStringList() << radiStr, &res);

        agentView = vector<vector <int> >(this->maxAgentID, vector<int>());

        while(q->next())
        {
            agentView[q->value(0).toInt()].push_back(q->value(1).toInt());
        }
        return res;
    }
}
