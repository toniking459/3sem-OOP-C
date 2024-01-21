#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tableitem.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableWidget->setSortingEnabled(true); //устанавливаем сортировку для полей таблицы
    ui->tableWidget->setItemPrototype(new MytableItem()); //устанавливаем прототип элемента для таблицы в указанное значение item
    //определяем может ли пользователь выбрать один или несколько элементов и, при выборе со многими элементами, должен ли выбор представлять собой непрерывный диапазон элементов;
    //SelectRows - 	выбираем только строки
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->setWindowFlags(this->windowFlags() | Qt::MSWindowsFixedSizeDialogHint); //устанавливаем фиксированное значение размера окна
    str = ""; //задаем пустую строку для пользовательского ввода
    connect(ui->tableWidget,SIGNAL(cellPressed(int,int)),this,SLOT(save_cell(int,int)));
    connect(ui->tableWidget,SIGNAL(cellChanged(int,int)),this,SLOT(check_cell(int,int)));
}

void MainWindow::save_cell(int row, int column){
    if (column ==  3 or column == 4){
        return;
    }
    str = ui->tableWidget->item(row,column)->text(); //записываем в строку то, что пользователь ввёл в ячейку
}

void MainWindow::check_cell(int row, int column){
    bool flag = 0;
    if (column == 3 or column == 4){
        return;
    }
    QString str_1 = ui->tableWidget->item(row,column)->text(); //записываем в новую строку то, что пользователь ввёл в ячейку
    if (str_1 == ""){
        return;
    }
    //в зависимости от колонки вызываем разные функции для проверки ввода пользователя
    if (column == 0){
        flag = isRightName(str_1);
        qDebug() << flag;
    }
    if (column == 1){
        flag = isRightName(str_1);
    }
    if (column == 2){
        flag = isRightName(str_1);
    }
    if (column == 5){
        flag = isRightEmail(str_1);
    }
    if (column == 6){
        flag = isRightPhone(str_1);
    }
    if (!flag){
        qDebug() << flag;
        ui->tableWidget->item(row, column)->setText(str); //записываем в ячейку старый текст
    }
}

void MainWindow::on_deleteButton_clicked()
{
    QModelIndexList selectedRows = ui->tableWidget->selectionModel()->selectedRows();
    while (!selectedRows.empty()) {
        ui->tableWidget->removeRow(selectedRows[0].row());
        selectedRows = ui->tableWidget->selectionModel()->selectedRows();
    }
}



void MainWindow::on_addButton_clicked()
{
    ui->tableWidget->insertRow(ui->tableWidget->rowCount());
    int rows = ui->tableWidget->rowCount()-1;
    //int columns = ui->tableWidget->columnCount();

    for (int i = 0; i<ui->tableWidget->columnCount(); i++){
        //если колонка с датой, то пропустить шаги
        if (i == 4) {
            continue;
        }
        //добавляем ячейку для ввода пользователя
        MytableItem* item = new MytableItem("");
        ui->tableWidget->setItem(rows, i, item);
    }

    //для ячеек с датой задаем параметры
    QDateEdit* date = new QDateEdit();
    date->setMaximumDate(QDate::currentDate());
    date->setMinimumDate(QDate(1, 1, 1200));
    date->setDate(QDate::currentDate());
    date->setDisplayFormat("dd.MM.yyyy");
    ui->tableWidget->setCellWidget(rows, 4, date);

    QDate tmp = date->date();
    MytableItem* item = new MytableItem(dateToString(tmp));
    ui->tableWidget->setItem(rows, 4, item);

    connect(date, SIGNAL(dateChanged(QDate)), item, SLOT(setDate(QDate)));
}


void MainWindow::on_saveButton_clicked()
{
    QFile file("C:/Qt/kurss/date.txt");

    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "", "Файл не найден");
    }

    QTextStream out(&file);
    QString text;


    for (int i = 0; i < ui->tableWidget->rowCount(); i++) {
        int count = 0;
        for (int j = 0; j < ui->tableWidget->columnCount(); j++){
                 QTableWidgetItem *tmp = ui->tableWidget->item(i, j);
                 if (tmp->text() == ""){
                     count+=1;
                 }
            }
        qDebug( ) << count;
        if (count != 6){
            for (int j = 0; j < ui->tableWidget->columnCount(); j++) {
                if (j != 4){
                    QTableWidgetItem *tmp = ui->tableWidget->item(i, j);
                    if (tmp != nullptr) {
                        text += tmp->text() + ',';
                    }
                    else {
                        text += ',';

                    }
                }
                else {
                    QDate tmp = (qobject_cast<QDateEdit*>(ui->tableWidget->cellWidget(i,j)))->date();
                    text += QString::number(tmp.day()) + ',' + QString::number(tmp.month())
                            + ',' + QString::number(tmp.year()) + ',';
                }
            }
             text += '\n';
        }
    }



    out << text;
    file.flush();
    file.close();
}


void MainWindow::on_readButton_clicked()
{
    QFile file("C:/Qt/kurss/date.txt");
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "", "Файл не найден");
    }

    QTextStream in(&file);
    int i = 0;

    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setSortingEnabled(false);

    while (!in.atEnd()) {
        on_addButton_clicked();

        int flag = 0;
        QString text = in.readLine();
        QStringList list = text.split(u','); //устанавливаем разделитель

        for (int j = 0; j < ui->tableWidget->columnCount(); j++) {
            QTableWidgetItem *tmp = ui->tableWidget->item(i, j);
            if (tmp->text() != ","){
                if (j != 4) {
                    MytableItem *item = new MytableItem(list[j + flag]);
                    ui->tableWidget->setItem(i, j, item);

                }
                else {
                    QDateEdit *date = qobject_cast<QDateEdit*>(ui->tableWidget->cellWidget(i,j));
                    date->setDisplayFormat("dd.MM.yyyy");
                    date->setDate(QDate((list[j]).toInt(), (list[j + 1]).toInt(), (list[j + 2]).toInt()));
                    flag = 2;
                    MytableItem *tmp = new MytableItem(dateToString(date->date()));
                    ui->tableWidget->setItem(i, j, tmp);
                    connect(date, SIGNAL(dateChanged(QDate)), tmp, SLOT(setDate(QDate)));
                }
            }

        }
        i++;
    }
    file.close();
    ui->tableWidget->setSortingEnabled(true);
}

QString dateToString(QDate date) {
    QString day = QString::number(date.day());
    QString month = QString::number(date.month());
    QString year =  QString::number(date.year());

    if (month.size() == 1) {
        month = "0" + month;
    }
    if (day.size() == 1) {
        day = "0" + day;
    }

    return day + "." + month + "." + year;
}


void MainWindow::on_searchButton_clicked() {
    ui->tableWidget->clearSelection();
    if (ui->lineEdit->text() == "") {
        return;
    }
    for (int i = 0; i < ui->tableWidget->rowCount(); i++) {
        for (int j = 0; j < ui->tableWidget->columnCount(); j++) {
            if (ui->tableWidget->item(i, j) == 0) {
                continue;
            }
            if (ui->tableWidget->item(i, j)->text().toLower().indexOf(ui->lineEdit->text().toLower()) != -1) {
                ui->tableWidget->selectionModel()->select(ui->tableWidget->model()->index(i, j), QItemSelectionModel::Select | QItemSelectionModel::Rows);
            }
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

