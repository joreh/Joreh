#include <QString>
#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

class Attribute
{
public:
    Attribute();
    Attribute(QString);
    Attribute(QString,QString);
    Attribute(QString,QString,QString);
    Attribute(QString,QString,QString,int);
    void SetName(QString n){ Name = n; }
    void SetFaName(QString n){ FaName = n; }
    void SetValue(int n){ Value = n; }
    void SetDesc(QString n){ Desc = n; }
    QString GetName(){return Name;}
    QString GetFaName(){return FaName;}
    int GetValue(){return Value;}
    QString GetDesc(){return Desc;}
private:
    QString Name;
    QString FaName;
    int Value;
    QString Desc;
};

#endif // ATTRIBUTE_H
