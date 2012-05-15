#ifndef StandardsParser_H
#define StandardsParser_H


#include "GISServer.h"
#include "GISUtility.h"
#include <vector>
#include <QDomDocument>


using namespace std;

namespace GIS
{

    struct AgentData
    {
        QString id;
        QString name;
        QString color;
        QString description;
    };
        
    struct AgentstdData
    {
        vector<AgentData> Agents;
    };

    struct GroundTypeData
    {
        QString id;
        QString name;
    };

    struct GroundTypestdData
    {
        vector<GroundTypeData> GroundTypes;
    };

class StandardsParser
    {
    public:
        StandardsParser(QFile* file);
        AgentstdData GetData();
        GroundTypestdData GetGroundData();

    private:
        bool Parse();
        void AgentstdParse(QDomElement element, AgentstdData& agtl);
        void GroundTypestdParse(QDomElement element, GroundTypestdData& grndl);
        QString SetFileAddress(QString str);
        AgentstdData data;
        GroundTypestdData groundData;
        QFile* xmlFile;
        QString path;
    };


}

#endif // SGIS-DL-Standard-Parser_H



