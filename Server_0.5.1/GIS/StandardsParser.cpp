#include "StandardsParser.h"
#include <vector>
#include <QDebug>
#include <QDomDocument>

namespace GIS
{
    StandardsParser::StandardsParser(QFile* file)
    {
        this->xmlFile = file;
        QFileInfo info(*this->xmlFile);
        this->path = info.path();

        if(!Parse())
        {
            qDebug() << "xml parsing was not successful" << endl;
            return;
        }
    }

    bool StandardsParser::Parse()
    {
        QDomDocument doc("SGIS-Type-Standard");
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

        QDomElement root = doc.documentElement();

        QDomNode n = root.firstChild();



        while(!n.isNull())
        {
            QDomElement e = n.toElement(); // try to convert the node to an element.
            qDebug() << e.tagName();
            if(!e.isNull() && e.tagName() == "Agentstd")
            {
                AgentstdParse(e, this->data);
                //code to parse Standard
            }
            if(!e.isNull() && e.tagName() == "GroundTypestd")
            {
                GroundTypestdParse(e, this->groundData);
                //code to parse Standard
            }
            n = n.nextSibling();
        }

        return true;
    }

    QString StandardsParser::SetFileAddress(QString str)
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

    void StandardsParser::AgentstdParse(QDomElement element, AgentstdData& agtl)
    {

        AgentData agt;

        QDomElement e = element.firstChild().toElement();
        while(!e.isNull())
        {
            agt.id = e.attribute("id");
            agt.name = e.attribute("name");
            agt.color = e.attribute("color");
            agt.description = e.attribute("description");

            agtl.Agents.push_back(agt);

            e = e.nextSibling().toElement();
        }
    }


    void StandardsParser::GroundTypestdParse(QDomElement element, GroundTypestdData &grndl)
    {
        GroundTypeData grnd;


        QDomElement e = element.firstChild().toElement();
        while(!e.isNull())
        {
            grnd.id = e.attribute("id");
            grnd.name = e.attribute("name");
            grndl.GroundTypes.push_back(grnd);
            e = e.nextSibling().toElement();
        }
    }

    AgentstdData StandardsParser::GetData()
    {
        return data;
    }

    GroundTypestdData StandardsParser::GetGroundData()
    {
        return groundData;
    }
}
