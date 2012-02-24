#include "DBServer.h"
#include <QStringList>
#include <QDebug>
#include <QVariant>
#include <QFile>
#include <QByteArray>

namespace GIS
{
    DBServer::DBServer()
    {
        QStringList sl = QSqlDatabase::drivers();
        QString str;
        isPsqlSupported = false;
        connected = false;

        qDebug("Supported Drivers in QT :");
        for(int i = 0; i < sl.size(); i++)
        {
            str = sl.at(i);
            qDebug() << qPrintable(str);

            if(str == "QPSQL")
            {
                isPsqlSupported = true;
                qDebug("QPSQL support: OK");
            }

        }

        if(isPsqlSupported)
            connection = QSqlDatabase::addDatabase("QPSQL");
        else
            qDebug("QPSQL not supported in QT !");
    }

    bool DBServer::Connect(QString host, QString db, QString username, QString password)
    {
        connection.setHostName(host);
        connection.setDatabaseName(db);
        connection.setUserName(username);
        connection.setPassword(password);

        if((connected = connection.open()) == true)
            qDebug() << "Connection state: OK";
        else
            qDebug() << "Connection state: FAILE \n";

        query = new QSqlQuery(connection);

        //initialize special queries
        SQ_postgrresqlVersion = "select version();";
        SQ_postgisVersion = "select postgis_full_version();";
        //------------------------------

        return connected;
    }

    bool DBServer::CreateSchemas(QString schemasName, QString owner)
    {
        QString q = "CREATE SCHEMA \"" + schemasName + "\" AUTHORIZATION " + "\"" + owner + "\"";

        QSqlQuery *ret = QQuery(q);



        return true;
    }

    bool DBServer::RunQueryFile(QFileInfo qFile)
    {
        QFile f(qFile.absoluteFilePath());

        QString str;

        if(f.open(QIODevice::Text | QIODevice::ReadWrite))
        {

            while (!f.atEnd())
            {
                QByteArray line = f.readLine();
                str.append(line);
            }

            qDebug() << str;

            this->QQuery(str);
            f.close();
        }
        else
        {
            qDebug() << "could not open query file !";
            return false;
        }

        return true;
    }


    bool DBServer::CheckExistenceOfSchema(QString schemaName)
    {
        QString query = "select exists(select schema_name from information_schema.schemata where schema_name = '"
                + schemaName + "');";
        QSqlQuery *q = QQuery(query);
        q->next();
        if(q->value(0).toBool() == true)
            return true;

        return false;
    }



    DBServer::~DBServer()
    {
        connection.close();
        delete query;
    }

    QSqlQuery* DBServer::QQuery(QString queryStr)
    {
        qDebug() << "Executing query : " << qPrintable(queryStr);
        if(query->exec(queryStr))
            qDebug() << "Query execution: OK";
        else
            qDebug() << "Query execution: FAIL";
        return query;
    }


}
