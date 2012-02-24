#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QTimer>
#include <QErrorMessage>
#include <QtGui/QMainWindow>
#include <WorldModel/WorldModel.h>

#include "Connection/Connection.h"

namespace Ui
{
    class MainWindowClass;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow( QWidget *parent = 0 );
    ~MainWindow();

    void showWorldModel();

protected:
    void drawBackground( QPainter *painter, const QRectF &rect );

    double scaleX( double x );
    double scaleY( double y );

private:
    WorldModel *m_worldModel;
    unsigned m_lastNumObjects;
    Ui::MainWindowClass *m_ui;

    QErrorMessage m_errorDialog;

    Connection m_connection;
    QRegExp m_regIpPort;

private slots:
    void on_actionExit_triggered();
    void on_actionShow_Options_triggered();
    void repaintView();

    void parseMessage( std::string msg );
    void on_connectButton_clicked();

    void monitorDisconnected();
    void displayError( QAbstractSocket::SocketError socketError );

};

#endif // MAINWINDOW_H
