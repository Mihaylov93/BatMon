#ifndef BATTERYWIDGET_H
#define BATTERYWIDGET_H

#include <QMainWindow>
#include <QFile>
#include <QTextStream>

#include <QDebug>

namespace Ui {
    class BatteryWidget;
}

class BatteryWidget : public QMainWindow
{
    Q_OBJECT

public:
    explicit BatteryWidget(QWidget *parent = nullptr);
    virtual ~BatteryWidget();

private:
    Ui::BatteryWidget *ui;
    void GetBatteryValue();

};

#endif // BATTERYWIDGET_H
