#include <QString>
#include <QStringList>
#ifndef BEHAVIOR_H
#define BEHAVIOR_H

class behavior
{
private:
    QString Name;
    QString FaName;
    QString preq;
    QString Desc;
public:
    behavior();
    behavior(QString);
    behavior(QString,QString);
    behavior(QString,QString,QString);
    behavior(QString,QString,QString,QString);
    void SetName(QString n){ Name = n; }
    void SetFaName(QString n){ FaName = n; }
    void SetPreq(QString n){ preq = n; }
    void SetDesc(QString n){ Desc = n;}
 //   void addPreq(QString n){preqs.append(n);}

    QString GetName(){return Name;}
    QString GetFaName(){return FaName;}
    QString GetPreq(){return preq;}
    QString GetDesc(){return Desc;}

    //   QStringList GetPreqs(){return preqs;}
 //   QString GetPreqs(int i){return preqs.takeAt(i);}
};

#endif // BEHAVIOR_H
