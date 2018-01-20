#include "clientinterface.h"
#include <QApplication>
#include "registeinterface.h"
#include <iostream>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Clientinterface w;

    w.show();


    return a.exec();
}
