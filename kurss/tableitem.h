#ifndef TABLEITEM_H
#define TABLEITEM_H
#include <QWidget>
#include <QTableWidgetItem>
#include <QDate>
#include "mainwindow.h"

bool isRightEmail(QString& email);
bool isRightPhone(QString& phone);
bool isRightName(QString& name);

class MytableItem : public QObject, public QTableWidgetItem
{
    Q_OBJECT
public:
    MytableItem();
    MytableItem(QString);
    virtual ~MytableItem() {};
signals:

public slots:
    void setDate(const QDate& date);
};

#endif // TABLEITEM_H
