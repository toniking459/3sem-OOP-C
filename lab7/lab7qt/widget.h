#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMessageBox>
#include <QLabel>
#include <QRadioButton>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsView>
#include <QRandomGenerator>
#include <QPushButton>
#include <QVBoxLayout>
#include <QAbstractGraphicsShapeItem>
#include <QPainter>
#include <QDebug>
#include <QSpinBox>

class Widget : public QWidget
{
    Q_OBJECT
    QGraphicsScene *scene;
    QPushButton* addButton;
    QPushButton* removeButton;
    QVBoxLayout* layout;
    QGraphicsView* view;
    QSpinBox* xCor;
    QSpinBox* yCor;

    int type;
public:
    Widget(QWidget *parent = 0);
    ~Widget();

  public slots:
      void addButtonClicked();
      //void deleteButtonClicked();
      void setType();
};


class Figure : public QObject, public QAbstractGraphicsShapeItem
{
    Q_OBJECT
    public:
        explicit Figure(QObject *parent = 0, int t = 1);
        ~Figure();
    void drawRect(QPainter* painter);
    void drawTriangle(QPainter* painter);
    void drawStar(QPainter* painter);
    void drawEllipse(QPainter* painter);


    signals:

    private:
     QColor qc;
     int type;

        QPainterPath shape() const;
        QRectF boundingRect() const {return shape().boundingRect();} ;
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
        void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
        void mousePressEvent(QGraphicsSceneMouseEvent *event);
        void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
        void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
        void addButtonClicked();

    public slots:
};

#endif // WIDGET_H
