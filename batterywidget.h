#ifndef BATTERYWIDGET_H
#define BATTERYWIDGET_H

#include <QWidget>
#include <QFile>
#include <QTextStream>

#include <QDebug>

namespace Ui {
    class BatteryWidget;
}

class BatteryWidget : public QWidget
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
