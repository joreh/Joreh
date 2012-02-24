#ifndef DBSERVER_H
#define DBSERVER_H



#include <vector>
#include <QString>
#include <QSqlQuery>
#include <QFileInfo>

using namespace std;



namespace GIS
{

    class DBServer
    {
    public:
        DBServer();
        bool Connect(QString host, QString db, QString username, QString password);

        bool CreateSchemas(QString schemasName, QString owner);
        bool CheckExistenceOfSchema(QString schemaName);
        bool RunQueryFile(QFileInfo qFile);

        //bool CreateTable()


        QSqlQuery* QQuery(QString queryStr);
        vector< vector<QString> > SQuery(QString queryStr);


        // special queries //
        QString SQ_postgrresqlVersion;
        QString SQ_postgisVersion;



        ~DBServer();
    private:
        QSqlDatabase connection;
        bool isPsqlSupported;
        bool connected;

        QSqlQuery *query; //used in QQuery
    };
}
#endif // DBSERVER_H
