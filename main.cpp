#include "batterywidget.h"
#include <QApplication>
#include <QSharedPointer>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCoreApplication::setApplicationName("BatMon");

    QSharedPointer <BatteryWidget> w;

    int mseconds = 0;
    int mode = 0;
    bool sConverted = false;
    bool mConverted = false;

    if (QCoreApplication::arguments().count() > 1){
        mseconds = QCoreApplication::arguments().at(1).toInt(&sConverted) * 1000;
        if (QCoreApplication::arguments().count() == 3){
             mode = QCoreApplication::arguments().at(2).toInt(&mConverted);
             if(mConverted && sConverted){
                 if (mseconds > 0){
                     w = QSharedPointer <BatteryWidget>(new BatteryWidget (mseconds,mode));
                 }
                 else w = QSharedPointer <BatteryWidget>(new BatteryWidget (30000,mode));

              }
             else w = QSharedPointer <BatteryWidget>(new BatteryWidget (mseconds,0));
        }else{
            //Test if the arg can be parsed into a int if not set default 30 seconds.
            if(sConverted)
                if (mseconds > 0) w = QSharedPointer <BatteryWidget>(new BatteryWidget (mseconds,0));
                else  w = QSharedPointer <BatteryWidget>(new BatteryWidget (30000,0));
            else  w = QSharedPointer <BatteryWidget>(new BatteryWidget (30000,0));
        }
    }else{
        w = QSharedPointer <BatteryWidget>(new BatteryWidget (30000,0));
    }

    w.data()->show();
    return a.exec();
}

