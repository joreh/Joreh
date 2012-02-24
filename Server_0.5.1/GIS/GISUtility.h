#ifndef GISUTILITY_H
#define GISUTILITY_H

#include <QString>
#include <vector>

using namespace std;

namespace GIS
{
    // we need a struct to obtain the reade data from xml
    struct MapSetData
    {
        QString name;
        vector<QString> shapeFileName;
        vector<QString> shapeFileAddr;
        vector<QString> shapeFileType;
        vector<QString> rasterFileName;
        vector<QString> rasterFileAddr;
        QString heigthFileName;
        QString heigthFileAddr;
        QString hMax, hMin;
    };
}


#endif // GISUTILITY_H
