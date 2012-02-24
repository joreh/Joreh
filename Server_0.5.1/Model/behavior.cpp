#include "behavior.h"
#include <QString>
#include <QStringList>

behavior::behavior()
{
}
behavior::behavior(QString n,QString f,QString d,QString v)
{
    Name = n;
    FaName = f;
    Desc = d;
    preq = v;

}
behavior::behavior(QString n)
{
    Name = n;
}
behavior::behavior(QString n,QString f)
{
    Name = n;
    FaName = f;
}
behavior::behavior(QString n,QString f,QString d)
{
    Name = n;
    FaName = f;
    Desc = d;
}
