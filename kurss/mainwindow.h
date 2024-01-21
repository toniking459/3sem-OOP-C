#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDateEdit>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include "tableitem.h"
#include <QDebug>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

QString dateToString(QDate date);

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void on_deleteButton_clicked();
    void on_addButton_clicked();
    void on_saveButton_clicked();
    void on_readButton_clicked();
    void on_searchButton_clicked();

    void check_cell(int row,int column);
    void save_cell(int row,int column);

private:
    Ui::MainWindow *ui;
    QString str; //строка для ввода пользователя
};
#endif // MAINWINDOW_H
