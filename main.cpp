#include "batterywidget.h"
#include <QApplication>
#include <QSharedPointer>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCoreApplication::setApplicationName("BatMon");
    qSetMessagePattern("[%{type}] %{appname} (%{file}:%{line}) - %{message}");
    QSharedPointer<BatteryWidget> w;

    if (QCoreApplication::arguments().count() > 1) {
        bool secondsConverted = false;
        bool modeConverted = false;
        int milliseconds = QCoreApplication::arguments().at(1).toInt(&secondsConverted) * 1000;
        if (QCoreApplication::arguments().count() == 3) {
            int mode = QCoreApplication::arguments().at(2).toInt(&modeConverted);
            if (modeConverted && secondsConverted) {
                if (milliseconds > 0) {
                    w = QSharedPointer<BatteryWidget>(new BatteryWidget(milliseconds, mode));
                } else
                    w = QSharedPointer<BatteryWidget>(new BatteryWidget(30000, mode));

            } else
                w = QSharedPointer<BatteryWidget>(new BatteryWidget(milliseconds, 0));
        } else {
            // Test if the arg can be parsed into a int if not set default 30 seconds.
            if (secondsConverted)
                if (milliseconds > 0)
                    w = QSharedPointer<BatteryWidget>(new BatteryWidget(milliseconds, 0));
                else
                    w = QSharedPointer<BatteryWidget>(new BatteryWidget(30000, 0));
            else
                w = QSharedPointer<BatteryWidget>(new BatteryWidget(30000, 0));
        }
    } else {
        w = QSharedPointer<BatteryWidget>(new BatteryWidget(30000, 0));
    }

    w.data()->show();
    return QApplication::exec();
}
