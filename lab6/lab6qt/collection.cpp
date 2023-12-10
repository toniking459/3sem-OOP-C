#include "collection.h"

void Collection::setValue(int value)
{
    m_value = value;
    emit valueChanged(value);
}

Collection::Collection(QWidget *parent) : QWidget(parent)
{
    layout = new QVBoxLayout(this);
     m_value = 0;
     m_delete = 0;
     addButton = new QPushButton("Добавить виджет");
     removeButton = new QPushButton("Удалить виджет");
     m_vector = {};

     removeButton->setFocusPolicy(Qt::NoFocus);
         addButton->setFocusPolicy(Qt::NoFocus);
         layout->addWidget(addButton);
         layout->addWidget(removeButton);

         connect(addButton, SIGNAL(clicked()), this, SLOT(addWidget()));
             connect(removeButton, SIGNAL(clicked()), this, SLOT(removeWidget()));
}

void Collection::addWidget()
{
    Widgets widget = Widgets(QRandomGenerator::global()->bounded(1,5));
    switch(widget)
        {
            case Qlabel:
                addLabel();
                break;
            case Qslider:
                addSlider();
                break;
            case QscrollBar:
                addScrollBar();
                break;
            case QspinBox:
                addSpinBox();
                break;
        }
    //m_delete++;
    qDebug() << m_delete;
    //emit valueChanged(m_delete);
}

void Collection::addLabel()
{
    myLabel* label = new myLabel;
    label->setText(QString::number(m_value));
    label->setFixedHeight(20);
    label->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    label->setAlignment(Qt::AlignHCenter);
    m_vector.push_back(label);
    layout->addWidget(label);
    connectWidgets();
}
void Collection::addSlider()
{
    QSlider* slider = new QSlider(Qt::Horizontal);
   slider->setValue(m_value);
    m_vector.push_back(slider);
    layout->addWidget(slider);
    connectWidgets();
}
void Collection::addSpinBox()
{
    QSpinBox* box = new QSpinBox;
    box->setValue(m_value);
    m_vector.push_back(box);
    layout->addWidget(box);
    connectWidgets();
}
void Collection::addScrollBar()
{
    QScrollBar* scroll = new QScrollBar(Qt::Horizontal);
    scroll->setValue(m_value);
    m_vector.push_back(scroll);
    layout->addWidget(scroll);
    connectWidgets();
}

void Collection::removeWidget()
{
    bool ok;
    int index = QInputDialog::getInt(this, "Удалить виджет", "Введите номер виджета:", 0, 0,
                                     m_vector.size() - 1, 1, &ok);
    if (!m_vector.isEmpty() && ok)
        {
            QWidget* widget = m_vector.takeAt(index);
            layout->removeWidget(widget);
            delete widget;
        }

}

void Collection::connectWidgets()
{
    if (!m_vector.isEmpty())
    {
        for (int i = 0; i < m_vector.size() - 1; i++)
          {
            QObject::connect(m_vector.last(), SIGNAL(valueChanged(int)),
                             m_vector[i], SLOT(setValue(int)));
            QObject::connect(m_vector.last(), SIGNAL(valueChanged(int)),
                             this, SLOT(setValue(int)));
            qDebug() << m_vector.last() << "connected to" << m_vector[i];

              if (!m_vector[i]->inherits("QLabel"))
              {

                  QObject::connect(m_vector[i], SIGNAL(valueChanged(int)),
                                   m_vector.last(), SLOT(setValue(int)));
                  QObject::connect(m_vector[i], SIGNAL(valueChanged(int)),
                                   this, SLOT(setValue(int)));

              }
          }
    }
}
