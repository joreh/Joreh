#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H


#include <QGraphicsView>
#include <QPainter>
#include <vector>
#include <map>

class QGraphicsEllipseItem;
class QStatusBar;
class QMouseEvent;

struct GraphicPoint
{
  double realX;
  double realY;

  QGraphicsEllipseItem *gCircle;
};

class graphicsview : public QGraphicsView
{
	Q_OBJECT

public:
    graphicsview(QWidget *widget = NULL);

    void drawBackground( QPainter *painter, const QRectF &rect );

    void clear();
    void setStatusBar( QStatusBar *stBar );

    void setPoint( int indx, double realX, double realY );
    void addPoint( double realX, double realY, int model_id );

protected:

    void drawVerticalText( QPainter *painter,
                           int x, int y, QString str );

    void mousePressEvent( QMouseEvent *event );
    void mouseReleaseEvent( QMouseEvent *event );
    void mouseDoubleClickEvent( QMouseEvent *event );
    void resizeEvent( QResizeEvent *event );
    void mouseMoveEvent( QMouseEvent *event );
    void updatePosition( GraphicPoint *gPoint );
    int getIndexOfMousePointingCircle(QMouseEvent *event);

    void updateImageRect( int x, int y );

private:
    std::map<int,QColor> agentColor;
    double PIX_TO_CENT_X;
    double PIX_TO_CENT_Y;

    QStatusBar *m_statusBar;
    std::vector<GraphicPoint> m_points;

    int m_zoomSize;
    int m_pressX;
    int m_pressY;

    QImage m_image;
    QRect m_imageRect;

};

#endif // GRAPHICSVIEW_H
