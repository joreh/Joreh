#ifndef GISSERVER_H
#define GISSERVER_H

#include <QFileInfo>
#include "DBServer.h"

namespace GIS{

    class GISServer
    {
    public:
        GISServer();
        ~GISServer();


        // mapSetFileInfo is the info of a mapset's xml file,
        // this function add that to database
        bool LoadMapSet(QFileInfo mapSetFileInfo);

        // if the mapset already loaded in db retuens true
        bool SearchForMapSet(QString mapsetName);



    private:
        DBServer *db;
    };
}

#endif // GISSERVER_H
