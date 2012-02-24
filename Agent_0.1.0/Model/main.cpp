#include <QtCore/QCoreApplication>
#include <QtXml/QXmlStreamReader>
#include <QFile>
#include <QList>
#include <QMap>
#include <QString>
#include <iostream>
#include "attribute.h"
#include "behavior.h"
#include "model.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Model* b = new Model("C:\\ordinary_soldier.xml");
    Attribute tt = b->getAttribute(2);
    behavior test = b->getBehavior(3);
    std::cout<<tt.GetName().toAscii().data()<<"\n"<<b->getColor().toAscii().data()<<"\n"<<test.GetName().toAscii().data();
    //
   // std::cout<<test.GetName().toAscii().data();
  //  b->getModelFromFile();

/*    Attribute* b = new Attribute("salam");
    std::cout<<b->GetDesc().toAscii().data();
    QFile* file = new QFile("C:\\ordinary_soldier.xml");
    if (!file->open(QIODevice::ReadOnly | QIODevice::Text)) {
        std::cout<<"FILE Does Not exist";
        return 0;
    }
    QList< QMap<QString, QString> > attr;
    QMap<QString,QString> temp;
    QXmlStreamReader xml(file);
    while(!xml.atEnd()&&!xml.hasError()){
        QXmlStreamReader::TokenType token = xml.readNext();
        if(token == QXmlStreamReader::StartDocument) {
                                continue;
        }
        if(token == QXmlStreamReader::StartElement) {
                                /* If it's named persons, we'll go to the next.*/
                                /*if(xml.name() == "model") {
                                    QXmlStreamAttributes attrs = xml.attributes();
                                    std::cout<<xml.text().toString().toAscii().data();
                                    std::cout<<"\n";
                                    std::cout<<attrs.value("id").toString().toAscii().data();
                                }
                                if(xml.name() == "attr") {
                                    QXmlStreamAttributes attrs = xml.attributes();
                                    xml.readNext();
                                    std::cout<<xml.text().toString().toAscii().data()<<" - ";
                                    std::cout<<attrs.value("key").toString().toAscii().data()<<"\n";
                                   // temp.insert("name",attrs.value("key").toString());
                                   // attr.append(temp);
                                }
                        }

    }
  //  std::cout<<attr.count();
  /*  for(int i=0;i<attr.count();i++){
        std::cout<<i<<"\n";
        QMap<QString,QString> a = attr.takeAt(i);
        std::cout<<a["name"].toAscii().data()<<"\n";
    }*/
    return a.exec();
}
