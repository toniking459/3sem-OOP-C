#include "tableitem.h"

MytableItem::MytableItem():QTableWidgetItem(){

}
MytableItem::MytableItem(QString str):QTableWidgetItem(str){

}

void MytableItem::setDate(const QDate& date){
    this->setText(dateToString(date));
}


bool isRightEmail(QString& email){
    email = email.trimmed();//возвращаем строку, в начале и конце которой удалены пробелы
    //Когда ^ является первым символом в регулярном выражении, это означает, что регулярное выражение должно совпадать с начала строки.
    //Когда $ является последним символом регулярного выражения, это означает, что регулярное выражение должно совпадать с концом строки.
    //+ - одно или несколько вхождений
    // \. - просто точка
    //{2,} - не менее двух вхождений
    QRegularExpression email_reg(R"(^[A-Za-z0-9._]+@[A-Za-z0-9.-]+\.[A-Za-z]{2,}$)");
    return email_reg.match(email).hasMatch(); //проверяем, что введенный email соответсвует регулярному выражению
}

bool isRightPhone(QString& phonenumb){
    phonenumb = phonenumb.trimmed();
    // \d - число
    // {1,3} Соответствует не менее 1 и не более 3 вхождений.
    //можно ввести несколько телефонов через ;
    //QRegularExpression phone_reg("^(\\+\\d{1,3}\\(\\d{1,4}\\)\\d{1,4}-\\d{1,9};)+$");
    //+7(952)642-8952;+7(952)642-8952;
    QRegularExpression phone_reg("^(\\+?[1-9][0-9]{7,14};)+$");
    return phone_reg.match(phonenumb).hasMatch();//проверяем, что введенный номер телефона соответсвует регулярному выражению
}



bool isRightName(QString& name){
    name = name.trimmed();
    //? соответствует любому отдельному символу
    QRegularExpression name_reg("^[A-Za-zА-Яа-яЁё]+[- ]?[A-Za-zА-Яа-яЁё]*$");
    return name_reg.match(name).hasMatch();
}

