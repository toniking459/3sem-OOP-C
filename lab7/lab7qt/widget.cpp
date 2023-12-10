#include "widget.h"
int count = 0;

Widget::Widget(QWidget *parent) :
    QWidget(parent)
{
    type = 1;
    resize(900,900);
    setFixedSize(900,900);
    scene = new QGraphicsScene(this);
    xCor = new QSpinBox;
    yCor = new QSpinBox;
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    scene->setSceneRect(0,0,600,600);

    layout = new QVBoxLayout(this);
    QLabel *label = new QLabel(tr("Фигура для добавления"));
    label->setAlignment(Qt::AlignCenter);
    layout->addWidget(label);
    QRadioButton *radio1 = new QRadioButton(tr("Квадрат"));
    QRadioButton *radio2 = new QRadioButton(tr("Треугольник"));
    QRadioButton *radio3 = new QRadioButton(tr("Круг"));
    QRadioButton *radio4 = new QRadioButton(tr("Звезда"));


    layout->addWidget(radio1);
    layout->addWidget(radio2);
    layout->addWidget(radio3);
    layout->addWidget(radio4);
       radio1->setChecked(true);

       QLabel *label1 = new QLabel(tr("Координаты для добавления"));
       label1->setAlignment(Qt::AlignCenter);
       layout->addWidget(label1);
       xCor->setRange(50, 650);
       yCor->setRange(50, 650);
       layout->addWidget(xCor);
       layout->addWidget(yCor);

     addButton = new QPushButton("Добавить фигуру");
     addButton->setFocusPolicy(Qt::NoFocus);
     layout->addWidget(addButton);

    connect(radio1, SIGNAL(toggled(bool)), this, SLOT(setType()));
    connect(radio2, SIGNAL(toggled(bool)), this, SLOT(setType()));
    connect(radio3, SIGNAL(toggled(bool)), this, SLOT(setType()));
    connect(radio4, SIGNAL(toggled(bool)), this, SLOT(setType()));
         connect(addButton, SIGNAL(clicked()), this, SLOT(addButtonClicked()));
             //connect(removeButton, SIGNAL(clicked()), this, SLOT(removeWidget()));

        view = new QGraphicsView(scene);
        layout->addWidget(view);
}

Widget::~Widget()
{

}

void Widget::setType()
{
    QRadioButton * rb = qobject_cast<QRadioButton*>(sender());
    QString text = rb->text();
    if (text == "Треугольник") type = 2;
    else if (text == "Круг") type = 3;
    else if (text == "Звезда") type = 4;
    else type = 1;

}
void Widget::addButtonClicked()
{
    int x = xCor->value();
    int y = yCor->value();
    qDebug() << "x: " << x << " y: " << y;

    Figure *item = new Figure(nullptr, type);
    item->setPos(x, y);
    scene->addItem(item);
    //view = new QGraphicsView(scene);
}


Figure::Figure(QObject *parent, int t) :
    QObject(parent),
    QAbstractGraphicsShapeItem()
{
    type = t;
    int red = QRandomGenerator::global()->bounded(0,360);
    int green = QRandomGenerator::global()->bounded(0,256);
    int blue = QRandomGenerator::global()->bounded(0,200);
    qc = QColor::fromHsl(red,green,blue);
    count++;
}

Figure::~Figure()
{

}

QPainterPath Figure::shape() const
{
    QPainterPath path;
    switch (type)
    {
        case 1:
    {
        path.addRect(-60, -60, 120, 120);
        break;
    }
        case 2:
    {
        qDebug() << "Test triangle";
        path.moveTo(0, -60);
        path.lineTo(60,60);
        path.lineTo(-60,60);
        path.lineTo(0, -60);
        break;
    }

        case 3:
    {
        path.addEllipse(-60, -60, 120, 120);
        break;
    }

        case 4:
    {
        path.moveTo(QPointF(0, -60));
        path.lineTo(QPointF(-35,60));
        path.lineTo(QPointF(60, -15));
        path.lineTo(QPointF(-60, -15));
        path.lineTo(QPointF(35, 60));
        path.lineTo(QPointF(0, -60));
        break;
    }

    }

    return path;
}

void Figure::drawRect(QPainter* painter)
{
    painter->drawRect(-60,-60,120,120);
}

void Figure::drawTriangle(QPainter* painter)
{
    QPolygonF triag;
    triag<<QPointF(0,-60)<<QPointF(60,60)<<QPointF(-60,60);
    painter->drawPolygon(triag);
}
void Figure::drawEllipse(QPainter* painter)
{
   painter->drawEllipse(-60, -60, 120, 120);
}
void Figure::drawStar(QPainter* painter)
{
    QPolygonF star;
    star<< QPointF(0, -60) << QPointF(-35,60) << QPointF(60, -15) <<
           QPointF(-60, -15) << QPointF(35, 60);
   painter->drawPolygon(star);
}

void Figure::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(Qt::black);
    painter->setBrush(QBrush(qc, Qt::SolidPattern));


    switch(type)
    {
        case 1:
        {
            drawRect(painter);
            break;
        }
    case 2:
    {
        drawTriangle(painter);
        break;
    }
    case 3:
    {
        drawEllipse(painter);
        break;
    }
    case 4:
    {
        drawStar(painter);
        break;
    }
    }


    Q_UNUSED(option);
    Q_UNUSED(widget);
}
void Figure::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    setPos(mapToScene(event->pos()));
}

void Figure::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    setZValue(++count);
    setCursor(QCursor(Qt::ClosedHandCursor));
    Q_UNUSED(event);
}

void Figure::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    setCursor(QCursor(Qt::ArrowCursor));
    Q_UNUSED(event);
}

void Figure::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    QMessageBox msgBox;
    msgBox.setText("Вы точно хотите удалить эту фигуру?");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::Yes);
    int ret = msgBox.exec();
    if (ret == QMessageBox::Yes)
    {
        scene()->removeItem(this);
        delete this;
    }
}
