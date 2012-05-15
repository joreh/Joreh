#ifndef DBSERVER_H
#define DBSERVER_H

#include <string>
#include <vector>
#include <QString>
#include <QSqlQuery>
#include <QFileInfo>
#include <QString>
#include <QProcess>
#include <map>

using namespace std;

namespace GIS
{
    class DBServer
    {
    public:
        DBServer();
        // connect to Postgresql server
        bool Connect(QString host, QString db, QString username, QString password);

        // create an schema
        bool CreateSchemas(QString schemasName, QString owner);

        // return true if schemaName exists in db
        bool CheckExistenceOfSchema(QString schemaName);

        // execute an sql file in db
        bool RunQueryFile(QString sqlAddress);

        // this function use shp2pgsql tool of postGIS to add a shapefile to postgresql db
        bool MakeShapeFileTable(QString shpFile, QString schemaName, QString tableName, QString GeomName, bool reCreate);


        bool Insert(std::string schemaName, std::string tableName, std::map<std::string, std::string> args);

        // insert a row in a table, args are the pair column, value
        bool Insert(QString schemaName, QString tableName, QStringList args);

        bool Update(QString schemaName, QString tableName, QStringList vals, QString condition);

        // calling the function F_IsExistsTable in db
        bool IsTableExists(QString schemaName, QString tableName);

        // rename a column in db
        bool MDL_RenameColumn(QString schemaName, QString tableName, QString preCol, QString postCol);


        QByteArray RunShelCommand(QString command, QProcess::ProcessChannelMode mode);

        //bool CreateTable()

        QSqlQuery* RunFunction(QString schemaName, QString functionName, QStringList args, bool* res);
        QSqlQuery* RunTableFunction(QString schemaName, QString functionName, QStringList args, bool* res);

        QSqlQuery* QQuery(QString queryStr, bool* res);

        vector< vector<QString> > SQuery(QString queryStr);

        // special queries //
        QString SQ_postgrresqlVersion;
        QString SQ_postgisVersion;


        QString userName;

        ~DBServer();
    private:

        QString PGCONFIG;
        QSqlDatabase connection;
        bool isPsqlSupported;
        bool connected;
        QSqlQuery *query; //used in QQuery
    };
}
#endif // DBSERVER_H
