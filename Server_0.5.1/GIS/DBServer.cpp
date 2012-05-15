#include "DBServer.h"
#include <QStringList>
#include <QDebug>
#include <QVariant>
#include <QFile>
#include <QByteArray>
#include <QProcess>

using namespace std;

namespace GIS
{
    DBServer::DBServer()
    {
        QStringList sl = QSqlDatabase::drivers();
        QString str;
        isPsqlSupported = false;
        connected = false;

        this->PGCONFIG = "/usr/bin/pg_config";

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
        this->userName = username;
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

        bool res;
        QQuery(q, &res);

        return true;
    }

    bool DBServer::RunQueryFile(QString sqlAddress)
    {

        QFile f(sqlAddress);

        QString str;
        bool res;

        if(f.open(QIODevice::Text | QIODevice::ReadWrite))
        {

            while (!f.atEnd())
            {
                QByteArray line = f.readLine();
                str.append(line);
            }

            //qDebug() << str;

            this->QQuery(str, &res);
            f.close();
        }
        else
        {
            qDebug() << "could not open query file !";
            return false;
        }

        if(res == true)
            return true;
        return false;
    }

    bool DBServer::CheckExistenceOfSchema(QString schemaName)
    {
        QString query = "select exists(select schema_name from information_schema.schemata where schema_name = '"
                + schemaName + "');";
        bool res;
        QSqlQuery *q = QQuery(query, &res);
        q->next();
        if(q->value(0).toBool() == true && res)
            return true;

        return false;
    }

    DBServer::~DBServer()
    {
        connection.close();
        delete query;
    }

    QSqlQuery* DBServer::QQuery(QString queryStr, bool* res)
    {
        qDebug() << "Executing query : " << qPrintable(queryStr);
        if(query->exec(queryStr))
        {
            qDebug() << "Query execution: OK";
            *res = true;
        }
        else
        {
            *res = false;
            qDebug() << "Query execution: FAIL";
        }
        return query;
    }

    QSqlQuery* DBServer::RunFunction(QString schemaName, QString functionName, QStringList args, bool *res)
    {
        QString queryStr;
        queryStr = "SELECT \"" + schemaName + "\".\"" + functionName + "\"(";
        for(int i = 0; i < args.count(); i++)
        {
            if(i)
                queryStr += " ,";
            queryStr += "\'"+args[i]+"\'";
        }
        queryStr += ");";
        //qDebug() << queryStr;

        return QQuery(queryStr, res);
    }

    QSqlQuery* DBServer::RunTableFunction(QString schemaName, QString functionName, QStringList args, bool *res)
    {
        QString queryStr;
        queryStr = "SELECT * from \"" + schemaName + "\".\"" + functionName + "\"(";
        for(int i = 0; i < args.count(); i++)
        {
            if(i)
                queryStr += " ,";
            queryStr += "\'"+args[i]+"\'";
        }
        queryStr += ");";
        //qDebug() << queryStr;

        return QQuery(queryStr, res);
    }

    QByteArray DBServer::RunShelCommand(QString command, QProcess::ProcessChannelMode mode)
    {
        QProcess *proc = new QProcess();
        proc->setProcessChannelMode(mode);

        proc->start(command);
        if(!proc->waitForStarted())
        {
            qDebug() << "problem in executing : " + command;
            return NULL;
        }

        QByteArray data;

        while(proc->waitForReadyRead())
            data.append(proc->readAll());

        // to remove the '\n' at the end of resault (it's not a good approach to do this)
        data.remove(data.count()-1,1);

        delete proc;

        return data;
    }

    //آدرس یک فایل لایه ی برداری را میگیرد و جدول داده شده
    //در اسکیمای مورد نظر را میسازد و نام ستون هندسی آن را نیز از ورودی میگیرد
    bool DBServer::MakeShapeFileTable(QString shpFile, QString schemaName, QString tableName, QString GeomName, bool reCreate = false)
    {
        QFile file(shpFile);
        if(!file.exists())
        {
            qDebug() << shpFile << " does not exists";
            return false;
        }

        //finding the location of shp2pgsql
        QString postgresqlBinPath(RunShelCommand(PGCONFIG + " --bindir", QProcess::MergedChannels).data());

        qDebug() << postgresqlBinPath << endl;

       // postgresqlBinPath = postgresqlBinPath  + "/shp2pgsql ";
        postgresqlBinPath = "/usr/bin/shp2pgsql ";

        QString command;
        if(reCreate == true)
        {
        command = postgresqlBinPath + "-s 4326 -S -k -d -g geom " + shpFile + " "
                + schemaName + "." + tableName;
        }
        else
        {
            command = postgresqlBinPath + "-s 4326 -S -k -g geom " + shpFile + " "
                    + schemaName + "." + tableName;
        }


        //resault query for making table
        QString query(RunShelCommand(command, QProcess::SeparateChannels).data());

        bool res;

        //code for running the query
        QSqlQuery *q = QQuery(query, &res);
        q->next();
        qDebug() << '\n' << q->value(0).toString();
        //        qDebug() << endl << query << endl;

        return res;

    }

    bool DBServer::MDL_RenameColumn(QString schemaName, QString tableName, QString preCol, QString postCol)
    {
        QString queryStr = "ALTER TABLE \"" + schemaName + "\".\"" + tableName +
                "\" RENAME COLUMN " + preCol + " TO " + postCol + ";";
        bool res;
        this->QQuery(queryStr, &res);
        return res;
    }


    bool DBServer::IsTableExists(QString schemaName, QString tableName)
    {
        bool res;
        QSqlQuery *q = RunFunction("SGIS-Common", "F_IsExistsTable",
                    QStringList() << schemaName << tableName, &res);
        q->next();
        if(q->value(0).toBool() == true)
             return true;
        return false;

    }

    bool DBServer::Insert(string schemaName, 
                    string tableName, map<string, string> args )
    {
      QString qSchemaName( schemaName.c_str() );
      QString qTableName( tableName.c_str() );

      QStringList stringList;

      for( map<string, string>::iterator itr = args.begin();
           itr != args.end(); itr ++ )
        stringList << itr->first.c_str() << itr->second.c_str();

      return Insert( qSchemaName, qTableName, stringList );

    }

    bool DBServer::Insert(QString schemaName, QString tableName, QStringList args)
    {
        int i;
        QString queryStr = "INSERT INTO \"" + schemaName + "\".\"" + tableName + "\"(";
        for(i = 0; i < args.count(); i+=2)
        {
            if(i)
                queryStr += ", ";
            queryStr += args[i];
        }
        queryStr +=") VALUES(";
        for(i = 1; i < args.count(); i+=2)
        {
            if(i != 1)
                queryStr += ", ";
            queryStr += args[i];
        }
        queryStr +=");";

        bool res;
        QSqlQuery *q = QQuery(queryStr, &res);
        q->next();
        if(res)
            return true;
        return false;
    }

    bool DBServer::Update(QString schemaName, QString tableName, QStringList vals, QString condition)
    {
        int i;
        QString queryStr = "UPDATE \"" + schemaName + "\".\"" + tableName + "\" SET ";
        for(i = 0; i < vals.count(); i+=2)
        {
            if(i)
                queryStr += ", ";
            queryStr += vals[i] + " = " + vals[i+1];
        }

        queryStr +=" WHERE " + condition + " ;";

        bool res;
        QSqlQuery *q = QQuery(queryStr, &res);
        q->next();
        if(res)
            return true;
        return false;
    }
}
