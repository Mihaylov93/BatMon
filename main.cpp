#include "batterywidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BatteryWidget w;
    w.show();

    return a.exec();
}
