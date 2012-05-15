#include "GraphicsView.h"
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QGraphicsItem>
#include <QMouseEvent>
#include <QStatusBar>
#include <QPainter>
#include <iostream>
#include <cmath>
#include <QBitmap>

#include "DemoMap.h"

using namespace Demo;
using namespace std;

#define LINE_STEP 20.0

#define CIRCLE_RADIUS 5
#define magnitude(X,Y)(sqrt(pow(X,2)+pow(Y,2)))

graphicsview::graphicsview(QWidget *widget)
    : m_image( "Plane.png" )
{
    Q_UNUSED( widget );
    /* Set Model Colors */

    agentColor[24] = QColor( 255, 0, 0 ); //anti-armor_soldier
    agentColor[25] = QColor( 150, 146, 0 );//mincraft_soldier
    agentColor[28]=QColor( 0, 0, 205 );//scout_soldier
    agentColor[26]=QColor( 0, 150, 150 );//engineer_soldier
    agentColor[23]=QColor( 200, 50, 50 );//ordinary_soldier
    agentColor[29]=QColor( 100, 100, 100 );//support_soldier
    agentColor[27]=QColor( 220, 220, 220 );//medic_soldier
    agentColor[23]=QColor( 150, 50, 150 );//radioman
    QGraphicsScene *scene = new QGraphicsScene( this );
    scene->setSceneRect( QRect( -this->width() / 2.0 + 30,
                                -this->height() / 2.0 + 30,
                                this->width() - 60, this->height() - 60 ) );
    scene->setItemIndexMethod( QGraphicsScene::NoIndex );
    setScene( scene );
    setMouseTracking(true); //added by Aramik

    m_imageRect = m_image.rect();

    m_pressX = m_pressY = -1;
    m_zoomSize = 1;
}

void graphicsview::clear()
{
    m_points.clear();
    scene()->clear();

    update();
}

void graphicsview::setStatusBar( QStatusBar *stBar )
{
    m_statusBar = stBar;
}

void graphicsview::drawVerticalText(
        QPainter *painter, int x, int y, QString str )
{
    painter->save();

    painter->translate( x, y );
    painter->rotate( 90 );
    painter->drawText( 0, 0, str );

    painter->restore();
}

void graphicsview::resizeEvent( QResizeEvent *event )
{
    Q_UNUSED( event );
    this->setSceneRect( QRect( -this->width() / 2 + 10,
                               -this->height() / 2 + 10,
                                this->width() - 20,
                                this->height() - 20 ) );
    PIX_TO_CENT_X = this->sceneRect().width() / 2.0;
    PIX_TO_CENT_Y = this->sceneRect().height() / 2.0;
}

void graphicsview::setPoint( int indx, double realX, double realY )
{
    m_points[indx].realX = realX;
    m_points[indx].realY = realY;
    updatePosition( &m_points[indx] );
    cout << realX << " " << realY << endl;
}

void graphicsview::addPoint( double realX, double realY, int model_id )
{
    GraphicPoint gPoint;
    gPoint.realX = realX;
    gPoint.realY = realY;

    QGraphicsEllipseItem *item =
            new QGraphicsEllipseItem( QRectF(
                        -CIRCLE_RADIUS,
                        -CIRCLE_RADIUS,
                        CIRCLE_RADIUS * 2,
                        CIRCLE_RADIUS * 2 ) );

    QRadialGradient g = QRadialGradient( item->pos(), 10.0 );
    g.setColorAt( 0.0, agentColor[model_id]);
    g.setColorAt( 0.5, agentColor[model_id] );

    item->setZValue( 1 );
    item->setCacheMode( QGraphicsItem::DeviceCoordinateCache );
    item->setBrush( g );
    item->setPen( QPen(Qt::black) );

    this->scene()->addItem( item );

    gPoint.gCircle = item;
    updatePosition(&gPoint);
    m_points.push_back( gPoint );
}

void graphicsview::updatePosition( GraphicPoint *gPoint )
{
   if( !gPoint )
         return;

   gPoint->gCircle->setPos( gPoint->realX * PIX_TO_CENT_X,
                            gPoint->realY * PIX_TO_CENT_Y );
}

void graphicsview::updateImageRect( int x, int y )
{
    double clickedPosX = x / (double)sceneRect().width() *
            m_imageRect.width() + m_imageRect.topLeft().x();
    double clickedPosY = y / (double)sceneRect().height() *
            m_imageRect.height() + m_imageRect.topLeft().y();

    double newWidth = m_image.width() * ( 11 - m_zoomSize ) * 0.1;
    double newHeight = m_image.height() * ( 11 - m_zoomSize ) * 0.1;

    double topX = clickedPosX - newWidth / 2.0;
    double topY = clickedPosY - newHeight / 2.0;

    if( topX < 0 )
        topX = 0;
    if( topY < 0 )
        topY = 0;

    if( topX + newWidth > m_image.width() )
        topX = m_image.width() - newWidth;
    if( topY + newHeight > m_image.height() )
        topY = m_image.height() - newHeight;

    m_imageRect = QRect( topX, topY, newWidth, newHeight );

    repaint();
}

void graphicsview::mouseDoubleClickEvent( QMouseEvent *event )
{
    if( event->button() == Qt::LeftButton )
        m_zoomSize ++;
    else if( event->button() == Qt::RightButton )
        m_zoomSize --;

    if( m_zoomSize > 10 )
    {
        m_zoomSize = 10;
        return;
    }

    if( m_zoomSize < 1 )
    {
        m_zoomSize = 1;
        return;
    }
    updateImageRect( event->x(), event->y() );
}

void graphicsview::mousePressEvent( QMouseEvent *event )
{
    m_pressX = event->x();
    m_pressY = event->y();
}

void graphicsview::mouseReleaseEvent( QMouseEvent *event )
{
    m_pressX = -1;
    m_pressY = -1;
}

void graphicsview::mouseMoveEvent( QMouseEvent *event )
{

    if( m_pressX > 0 &&
            max( abs( event->x() - m_pressX ), abs( event->y() - m_pressY ) ) > 10 )
    {
        updateImageRect( event->x(), event->y() );
        m_pressX = event->x();
        m_pressY = event->y();
    }

    int index=getIndexOfMousePointingCircle(event);
    if( m_statusBar )
        m_statusBar->showMessage( QString(""));
    if(index==-1)
        return;
    int xP = event->x() + sceneRect().x() - x() + 4;
    int yP = event->y() + sceneRect().y() - y() + 1;

    if( m_statusBar )
        m_statusBar->showMessage( QString( "(index=%1)" ).arg(index));

    QGraphicsView::mouseMoveEvent( event );

}
int graphicsview::getIndexOfMousePointingCircle(QMouseEvent *event){
    //cout<<"+++++++++++++++++++ getIndexOfMousePointingCircle ++++++++++++++++++"<<endl;
    //cout<<" eventX="<<event->x()<<"  eventY="<<event->y()<<endl;
    int xP = event->x() + sceneRect().x() - x() + 4;
    int yP = event->y() + sceneRect().y() - y() + 1;
    for(unsigned int i=0;i<m_points.size();i++){
        GraphicPoint gp=m_points[i];
        //cout<<i<<"  rX="<<gp.realX<<"   rY="<<gp.realY<<"   cX="<<gp.gCircle->x()<<"   cY="<<gp.gCircle->y()<<endl;
        if(magnitude(xP-gp.gCircle->x(),yP-gp.gCircle->y())<CIRCLE_RADIUS){
            //cout<<"inde= "<<i<<endl;
            return i;
        }
    }
    return -1;
}
void graphicsview::drawBackground( QPainter *painter, const QRectF &rect )
{
    Q_UNUSED( rect );

    QRectF sceneRect = this->sceneRect();
    
    painter->drawImage(sceneRect, m_image, m_imageRect );
    //painter->fillRect( rect, QBrush( Qt::white ) );

    double xStep = floor( sceneRect.width() / 16 );
    double yStep = floor( sceneRect.height() / 16 );

    LandType **landTypes = GetLandType();
    int ** landHeight = GetHeight();

    int i = 0;
    int j = 0;

    for( int x = sceneRect.topLeft().x();
         x < sceneRect.bottomRight().x() && j < 32; x += xStep, j++ )
    {
        for( int y = sceneRect.topLeft().y(), i = 0;
             y < sceneRect.bottomRight().y() && i < 16; y += yStep, i ++ )
        {
      //    painter->fillRect( QRect( x, y, xStep, yStep ), GetColor( landTypes[i][j] ,255-(landHeight[i][j])/6,i,j) );

        painter->setPen( QColor( Qt::gray ) );
          painter->drawLine( sceneRect.x(), y, sceneRect.bottomRight().x(), y );
          painter->setPen( QColor( Qt::black ) );
          painter->drawLine( -2, y, 2, y );
       }


        painter->setPen( QColor( Qt::gray ) );
        painter->drawLine( x, sceneRect.y(), x, sceneRect.bottomRight().y() );
        painter->setPen( QColor( Qt::black ) );
        painter->drawLine( x, -2, x, 2 );
    }

    painter->setPen( QColor( Qt::black ) );
    painter->drawLine( 0, rect.y(), 0, rect.bottomRight().y() );
    painter->drawLine( rect.x(), 0, rect.bottomRight().x(), 0 );

    

   for( int i = 0; i < (int)m_points.size(); i ++ )
     updatePosition( &m_points[i] );

}

