#include "attribute.h"
#include <QString>

Attribute::Attribute()
{
}
Attribute::Attribute(QString n)
{
    Name = n;
}
Attribute::Attribute(QString n,QString f)
{
    Name = n;
    FaName = f;
}
Attribute::Attribute(QString n,QString f,QString d)
{
    Name = n;
    FaName = f;
    Desc = d;
}
Attribute::Attribute(QString n,QString f,QString d,int v)
{
    Name = n;
    FaName = f;
    Desc = d;
    Value = v;
}

