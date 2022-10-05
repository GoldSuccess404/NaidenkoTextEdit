#include "menuwind.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MenuWind w;
    w.showMaximized();
    return a.exec();
}
