#include "GISServer.h"
#include "MapSetParser.h"
#include "GISUtility.h"
#include "DBServer.h"

#include <QDebug>
#include <QVariant>


namespace GIS
{

    GISServer::GISServer()
    {
        db = new GIS::DBServer();
        db->Connect("localhost", "gis", "gisuser", "");

//        QSqlQuery *q = db->QQuery(db->SQ_postgrresqlVersion);
//        q->next();
//        qDebug() << '\n' << q->value(0).toString();

//        q = db->QQuery(db->SQ_postgisVersion);
//        q->next();
//        qDebug() << q->value(0).toString();



        if(db->CheckExistenceOfSchema("SGIS") == false) // its the first connect of gisserver to DB
        {
            qDebug() << "Creating tables for GISServer";
            db->CreateSchemas("SGIS", "gisuser");

            QFileInfo qFile("/home/mohammad/mGIS/createGISTables");
            db->RunQueryFile(qFile);

        }
    }

    GISServer::~GISServer()
    {
        delete db;
    }

    bool GISServer::LoadMapSet(QFileInfo mapSetFileInfo)
    {
        //parsing the xml using SAX method
        GIS::MapSetData msd;
        GIS::MapSetParser parser(&msd);
        QFile file(mapSetFileInfo.absoluteFilePath());
        QXmlInputSource source(&file);

        QXmlSimpleReader reader;
        reader.setContentHandler(&parser);
        reader.parse(source);
        // now the msd contains the contents of mapset

        qDebug() << msd.heigthFileName << '\n';
        qDebug() << msd.name << '\n';

        ///...

        // check that if the mapset already loaded



        //.....


        //create and update related tables in database

        ///...

        return true;

    }

    bool GISServer::SearchForMapSet(QString mapsetName)
    {
        //QString query = "select"
        //QSqlQuery *q = db->QQuery()
        return true;
    }

}
