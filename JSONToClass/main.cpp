#include "jsonwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    JsonWindow w;
    w.show();

    return a.exec();
}
