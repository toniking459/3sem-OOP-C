#ifndef COLLECTION_H
#define COLLECTION_H

#include <QWidget>
#include <QDebug>
#include <QPushButton>
#include <QInputDialog>
#include <QVBoxLayout>
#include <QLabel>
#include <QSlider>
#include <QScrollBar>
#include <QSpinBox>
#include <QRandomGenerator>

enum Widgets
{
    Qlabel =1,
      Qslider = 2,
      QscrollBar = 3,
      QspinBox = 4,

};

class myLabel: public QLabel
{
    Q_OBJECT

   public:
       myLabel()
       {
           this->setText("0");
       };
   signals:
       void valueChanged(int value);
   public slots:
       void setValue(int value)
       {
            this->setText(QString::number(value));
       };
};

class Collection : public QWidget
{

    Q_OBJECT
    int m_value;
    QVector<QWidget*> m_vector;
    QPushButton* addButton;
    QPushButton* removeButton;
    QVBoxLayout* layout;
    int m_delete;

public:
    Collection(QWidget *parent = 0);
    ~Collection() {};
    void addLabel();
    void addSlider();
    void addSpinBox();
    void addScrollBar();
    void connectWidgets();
signals:
    void valueChanged(int val);
public slots:
     void setValue(int);
     void addWidget();
     void removeWidget();

};




#endif // COLLECTION_H
