#include "ui_MainWindow.h"
#include "MessageParser.h"
#include "Geom/Vector3D.h"
#include "MainWindow.h"

#include <ctime>
#include <cstdlib>
#include <iostream>

#include <QRegExp>
#include <QErrorMessage>
#include <QDesktopWidget>
using namespace std;

#define EPS 0.000001

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), m_ui(new Ui::MainWindowClass),
      m_errorDialog( this ), m_connection( this ), 
      m_regIpPort( "(\\w*):(\\d*)" )
{
    m_worldModel = NULL;
    m_lastNumObjects = 0;

    m_ui->setupUi(this);

    QRect rect = QApplication::desktop()->screen()->geometry();

    move( ( rect.width() - width() ) / 2.0,
          ( rect.height() - height() ) / 2.0 );
    m_ui->graphicsView->setStatusBar( m_ui->statusBar );

    srand( time( 0 ) );

    QObject::connect( &m_connection, SIGNAL(messageReceived(std::string)),
             this, SLOT(parseMessage(std::string)) );
    QObject::connect( &m_connection, SIGNAL(disconnected()),      
                      this, SLOT(monitorDisconnected()) );
    connect( &m_connection, SIGNAL(error(QAbstractSocket::SocketError)),
             this, SLOT(displayError(QAbstractSocket::SocketError)));
}

MainWindow::~MainWindow()
{
    if( m_worldModel )
      delete m_worldModel;
    delete m_ui;
}

void MainWindow::on_actionShow_Options_triggered()
{
    if( m_ui->actionShow_Options->isChecked() )
        m_ui->groupBox->setVisible( true );
    else
        m_ui->groupBox->setVisible( false );
}

void MainWindow::on_actionExit_triggered()
{
    this->close();
}

void MainWindow::repaintView()
{
    m_ui->graphicsView->repaint();
}

void MainWindow::parseMessage( string msg )
{
  update_world_model( msg, m_worldModel );

  if( m_worldModel->isGameFinished() )
    on_actionExit_triggered();

  showWorldModel();
}

void MainWindow::showWorldModel()
{
  Vector3D position;

  if( m_lastNumObjects < m_worldModel->getNumOfObjects() )
  {
    for( int i = m_lastNumObjects; i <
                 m_worldModel->getNumOfObjects(); i ++ )
    {
      position = m_worldModel->getObjectByIndex( i ).getPosition();
      m_ui->graphicsView->addPoint( scaleX( position.getX() ),
                                    scaleY(  position.getY() ),m_worldModel->getObjectByIndex(i).getModelID() );
    }

    m_lastNumObjects = m_worldModel->getNumOfObjects();
  }

  for( int i = 0; i < (int)m_worldModel->getNumOfObjects(); i ++ )
  {
    position = m_worldModel->getObjectByIndex( i ).getPosition();
    m_ui->graphicsView->setPoint( i, scaleX( position.getX() ), 
                                     scaleY( position.getY() ) );
  }

  m_ui->graphicsView->repaint();
}

double MainWindow::scaleX( double x )
{
  return ( ( x - m_worldModel->getField().getLeftX() ) /
         ( m_worldModel->getField().getRightX() -
           m_worldModel->getField().getLeftX() ) - 0.5 ) * 2.0;
}

double MainWindow::scaleY( double y )
{
  return ( ( y - m_worldModel->getField().getBottomY() ) /
         ( m_worldModel->getField().getTopY() -
           m_worldModel->getField().getBottomY() ) - 0.5 ) * -2.0;

}

void MainWindow::monitorDisconnected()
{
  m_errorDialog.showMessage( "monitor is disconnected from the server" );
}

void MainWindow::displayError( QAbstractSocket::SocketError socketError )
{
  switch (socketError) 
  {
    case QAbstractSocket::RemoteHostClosedError:
      break;
    case QAbstractSocket::HostNotFoundError:
      m_errorDialog.showMessage( tr("The host was not found. Please check the "
                                   "host name and port settings."));
      break;
    case QAbstractSocket::ConnectionRefusedError:
      m_errorDialog.showMessage( tr("The connection was refused by the peer. "
                                    "Make sure the fortune server is running, "
                                    "and check that the host name and port "
                                    "settings are correct."));
      break;
    default:
      m_errorDialog.showMessage( tr("The following error occurred: %1.")
                                    .arg(m_connection.errorString()));
  }
}

void MainWindow::on_connectButton_clicked()
{
  if( m_ui->connectButton->text() == "Disconnect" )
  {
    m_connection.close();

    m_ui->ipEdit->setEnabled( true );
    m_ui->connectButton->setText( "Connect" );
    return;
  }

  QString ipPortStr = m_ui->ipEdit->text();

  if( !ipPortStr.contains( m_regIpPort ) )
  {
    m_errorDialog.showMessage( "IP & Port must be in IP:Port format" );
    return;
  }

  int colonIndx = ipPortStr.indexOf( ':' );
  QString ipStr = ipPortStr.left( colonIndx );
  QString portStr = ipPortStr.mid( colonIndx + 1 );

  if( m_worldModel )
  {
    delete m_worldModel;
    m_worldModel = NULL;
    m_lastNumObjects = 0;
  }

  m_ui->graphicsView->clear();

  m_connection.connectToHost( QHostAddress( ipStr ), portStr.toShort() );

  if( !m_connection.waitForConnected() )
  {
    m_errorDialog.showMessage( "can't connect to server" );
    return;
  }

  m_connection.sendData( "(init \"test\" \"monitor\")" ); 

  m_ui->connectButton->setText( "Disconnect" );
  m_ui->ipEdit->setEnabled( false );

  m_worldModel = new WorldModel();

}

