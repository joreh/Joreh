#include "model.h"
#include <QFile>
#include <QList>
#include <QMap>
#include <QString>
#include <QtXml/QXmlStreamReader>

#include "behavior.h"
#include "attribute.h"
#include "iostream"

using namespace std;

Model::Model()
{
}
Model::Model(QString file){
    getModelFromFile(file);
}
bool Model::getModelFromFile(QString filename){
    QFile* file = new QFile("./Model/Models/"+filename);
        if (!file->open(QIODevice::ReadOnly | QIODevice::Text)) {
            return false;
        }
        QXmlStreamReader xml(file);
        while(!xml.atEnd()&&!xml.hasError()){
            QXmlStreamReader::TokenType token = xml.readNext();
            if(token == QXmlStreamReader::StartDocument) {
                                    continue;
            }
            if(token == QXmlStreamReader::StartElement) {
                                    if(xml.name() == "model") {
                                        QXmlStreamAttributes attrs = xml.attributes();
                                        number = (int)attrs.value("number").toString().toInt();
					id =  (int)attrs.value("id").toString().toInt();
                                        Name = attrs.value("name").toString();
                                        Color = attrs.value("color").toString();
                                    }
                                    if(xml.name() == "desc") {
                                        xml.readNext();
                                        Desc = xml.text().toString();
                                    }
                                    if(xml.name() == "attr") {
                                        QXmlStreamAttributes attrs = xml.attributes();
                                        Attribute* b = new Attribute();
                                        xml.readNext();
                                        b->SetName( attrs.value("key").toString() );
                                        b->SetFaName( attrs.value("name").toString() );
                                        b->SetValue( xml.text().toString() );
                                        m_attrVal[attrs.value( "key" ).toString().toStdString()] = 
                                                  xml.text().toString().toFloat();
                                        attribute.append(*b);
                                        free(b);
                                    }
                                    if(xml.name() == "bhv") {
                                        QXmlStreamAttributes attrs = xml.attributes();
                                        behavior *b = new behavior();
                                        xml.readNext();
                                        b->SetName( attrs.value("key").toString() );
                                        b->SetFaName( attrs.value("name").toString() );
                                        if(xml.name() == "preq"){ xml.readNext();b->SetPreq( xml.text().toString() );}
                                        Behavior.append(*b);
                                        free(b);
                                    }
                            }

        }

      //  std::cout<<Behavior.count();
        return true;
}
void Model::printBehavior(){
    //std::cout<<Behavior.count()<<"\n";
    for(int i=0;i<Behavior.count();i++)
    {
        std::cout<<i<<" - ";
        behavior a = Behavior[i];
        std::cout<<"Name:"<<a.GetName().toAscii().data()<<" -Fa Name:"<<a.GetFaName().toAscii().data()<<" -Preq:"<<a.GetPreq().toAscii().data()<<" -desc:"<<a.GetDesc().toAscii().data()<<std::endl;
    }
    return;

}
void Model::printAttribute(){
    for(int i=0;i<attribute.count();i++)
    {
        std::cout<<i<<" - ";
        Attribute a = attribute[i];
        std::cout<<"Name:"<<a.GetName().toAscii().data()<<" -Fa Name:"<<a.GetFaName().toAscii().data()<<" -Value:"<<a.GetValue().toAscii().data()<<" -desc:"<<a.GetDesc().toAscii().data()<<std::endl;
    }
    return;

}

const map<string, double> &Model::getAttrValMap() const
{
  return m_attrVal;
}

double Model::getValue( string attr )
{
  return m_attrVal[attr];
}

void Model::setValue( string attr, double val )
{
  m_attrVal[attr] = val;
}

