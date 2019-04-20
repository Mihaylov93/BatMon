#include "batterywidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCoreApplication::setApplicationName("BatMon");
    BatteryWidget w;

    int mseconds = 0;
    bool converted = false;

    if (QCoreApplication::arguments().count() > 1){
        mseconds = QCoreApplication::arguments().at(1).toInt(&converted) * 1000;
    }else{
        mseconds = 30000;
    }


    //Test if the arg can be parsed into a int if not set default 30 seconds.
    if(converted)
        mseconds > 0 ? w.setTimer(mseconds) : w.setTimer(30000);
    else
        w.setTimer(30000);

    w.show();
    return a.exec();
}
