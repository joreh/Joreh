#include "MapSetParser.h"
#include <vector>
#include <QDebug>
#include <QDomDocument>

#include <iostream>
#include <cstdlib>

using namespace std;

namespace GIS
{
    MapSetParser::MapSetParser(QFile* file)
    {
        this->xmlFile = file;
        QFileInfo info(*this->xmlFile);
        this->path = info.absolutePath();

        if(!Parse())
        {
            qDebug() << "xml parsing was not successful" << endl;
            return;
        }
    }

    bool MapSetParser::Parse()
    {
        QDomDocument doc("Mapset");
        if(!this->xmlFile->open(QIODevice::ReadOnly))
        {
            qDebug() << "Error in reading xml file" << endl;
            return false;
        }
        if(!doc.setContent(this->xmlFile))
        {
            qDebug() << "Error in xml Format" << endl;
            return false;
        }
        this->xmlFile->close();

        QDomElement e = doc.documentElement();
        MapsetParse(e);

        return true;
    }

    QString MapSetParser::SetFileAddress(QString str)
    {
        while(str[0] == ' ')
            str.remove(0,1);
        while(str[str.count()-1] == ' ')
            str.remove(str.count()-1,1);
        if(str[0] == '.')
        {
            str.remove(0,1);
            return this->path + str;
        }
        else
            return str;
    }

    void MapSetParser::ShapefileParse(QDomElement element, MapsetData& ms)
    {
        ShapefileData shf;
        shf.address = SetFileAddress(element.attribute("address"));
        shf.type = element.attribute("type");

        ms.shapefiles.push_back(shf);


        QDomElement e = element.firstChild().toElement();

        while(!e.isNull())
        {
            if(e.tagName() == "Column")
            {
                ColumnParse(e, ms.shapefiles[ms.shapefiles.size()-1]);
            }

            e = e.nextSibling().toElement();
        }
    }

    void MapSetParser::ColumnParse(QDomElement element, ShapefileData &shf)
    {
        ColumnData c;
        c.source = element.attribute("source");
        c.target = element.attribute("target");

        shf.columns.push_back(c);


        QDomElement e = element.firstChild().toElement();

        while(!e.isNull())
        {
            if(e.tagName() == "Mapping")
            {
                MappingParse(e, shf.columns[shf.columns.size()-1]);
            }

            e = e.nextSibling().toElement();
        }
    }

    void MapSetParser::MappingParse(QDomElement element, ColumnData &c)
    {
        MappingData m;
        m.from = element.attribute("from");
        m.to = element.attribute("to");

        c.mappings.push_back(m);


    }

    void MapSetParser::RasterfileParse(QDomElement element, MapsetData &ms)
    {
        RasterfileData r;
        r.address = SetFileAddress(element.attribute("address"));
        r.id = element.attribute("id").toInt();

        ms.rasterfiels.push_back(r);
    }

    void MapSetParser::MapSizeParse(QDomElement element, MapsetData &ms)
    {
        MapSizeData r;
        r.maxX = element.attribute("maxX").toFloat();
        r.minX = element.attribute("minX").toFloat();
        r.maxY = element.attribute("maxY").toFloat();
        r.minY = element.attribute("minY").toFloat();
        data.mapSize = r;
    }

    void MapSetParser::MapsetParse(QDomElement element)
    {

        this->data.name = element.attribute("name");


        QDomElement e = element.firstChild().toElement();
        while(!e.isNull())
        {
            if(e.tagName() == "Shapefile")
            {
                ShapefileParse(e, this->data);
            }
            else if(e.tagName() == "Rasterfile")
            {
                RasterfileParse(e, this->data);
            }
            else if(e.tagName() == "MapSize")
            {
                MapSizeParse(e, this->data);
            }

            e = e.nextSibling().toElement();
        }
    }

    MapsetData MapSetParser::GetData()
    {
        return data;
    }
}
