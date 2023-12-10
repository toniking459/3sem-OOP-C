#include <QApplication>
#include "collection.h"

int main(int argc, char ** argv)
{
    QApplication app(argc, argv);
    Collection collection;
    collection.show();
    return app.exec();
}

