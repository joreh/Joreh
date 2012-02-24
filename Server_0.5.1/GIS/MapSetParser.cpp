#include "MapSetParser.h"
#include <vector>

namespace GIS
{

    MapSetParser::MapSetParser(MapSetData *d)
    {
         msd = d;
    }

    bool MapSetParser::startElement(const QString &, const QString &, const QString &qName, const QXmlAttributes &attrs)
    {
        if( inMapSet && qName == "heigthFile" )
        {
          QString name, addr;

          for( int i=0; i<attrs.count(); i++ )
          {
            if( attrs.localName( i ) == "name" )
              name = attrs.value( i );
            else if( attrs.localName( i ) == "address" )
              addr = attrs.value( i );
          }
          msd->heigthFileName = name;
          msd->heigthFileAddr = addr;
        }

        else if( inMapSet && qName == "heigthInfo" )
        {
            QString maxi, mini;
            for( int i=0; i<attrs.count(); i++ )
            {
                if( attrs.localName( i ) == "max" )
                    maxi = attrs.value( i );
                else if( attrs.localName( i ) == "min" )
                    mini = attrs.value( i );
            }
            msd->hMax = maxi;
            msd->hMin = mini;
        }

        if( inMapSet && qName == "shapeFile" )
        {
            QString name, addr, type;
            for( int i=0; i<attrs.count(); i++ )
            {
                if( attrs.localName( i ) == "name" )
                    name = attrs.value( i );
                else if( attrs.localName( i ) == "address" )
                    addr = attrs.value( i );
                else if( attrs.localName( i ) == "type" )
                    type = attrs.value( i );
            }
            msd->shapeFileName.push_back(name);
            msd->shapeFileAddr.push_back(addr);
            msd->shapeFileType.push_back(type);
        }

        if( inMapSet && qName == "rasterFile" )
        {
            QString name, addr;
            for( int i=0; i<attrs.count(); i++ )
            {
                if( attrs.localName( i ) == "name" )
                    name = attrs.value( i );
                else if( attrs.localName( i ) == "address" )
                    addr = attrs.value( i );

            }
            msd->rasterFileName.push_back(name);
            msd->rasterFileAddr.push_back(addr);

        }
        else if( qName == "MapSet" )
        {
            inMapSet = true;
            msd->name = attrs.value(0);
        }
        return true;
    };

    bool MapSetParser::startDocument()
    {
        inMapSet = false;

        return true;
    };

    bool MapSetParser::endElement(const QString &, const QString &, const QString &qName)
    {
        if( qName == "MapSet" )
        {
            inMapSet = false;
        }
        return true;
    };
}
