#ifndef MAPSETPARSER_H
#define MAPSETPARSER_H


#include <QXmlDefaultHandler>
#include "GISServer.h"
#include "GISUtility.h"

using namespace std;

namespace GIS
{

class MapSetParser : public QXmlDefaultHandler
    {
    public:
        MapSetParser(MapSetData *d);
        bool startDocument();
        bool endElement(const QString &, const QString &, const QString &qName);
        bool startElement(const QString &, const QString &, const QString &qName, const QXmlAttributes &attrs);
    private:
        bool inMapSet;
        MapSetData *msd;
    };

}

#endif // MAPSETPARSER_H
