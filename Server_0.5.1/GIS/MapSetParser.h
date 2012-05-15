#ifndef MAPSETPARSER_H
#define MAPSETPARSER_H


#include "GISServer.h"
#include "GISUtility.h"
#include <vector>
#include <QDomDocument>

using namespace std;

namespace GIS
{

    struct MapSizeData
    {
        int minX, minY, maxX, maxY;
    };
    struct RasterfileData
    {
        QString address;
        int id;
    };
    struct MappingData
    {
        QString from;
        QString to;
    };
    struct ColumnData
    {
        QString source;
        QString target;
        vector<MappingData> mappings;
    };
    struct ShapefileData
    {
        QString address;
        QString type;
        vector<ColumnData> columns;
    };
    struct MapsetData
    {
        QString name;
        vector<ShapefileData> shapefiles;
        vector<RasterfileData> rasterfiels;
        MapSizeData mapSize;
    };

class MapSetParser
    {
    public:
        MapSetParser(QFile* file);
        MapsetData GetData();

    private:
        bool Parse();
        void ShapefileParse(QDomElement element, MapsetData& ms);
        void RasterfileParse(QDomElement element, MapsetData& ms);
        void MapSizeParse(QDomElement element, MapsetData& ms);
        void MapsetParse(QDomElement element);
        void ColumnParse(QDomElement element, ShapefileData& shf);
        void MappingParse(QDomElement element, ColumnData& c);
        QString SetFileAddress(QString str);
        MapsetData data;
        QFile* xmlFile;
        QString path;
    };


}

#endif // MAPSETPARSER_H



