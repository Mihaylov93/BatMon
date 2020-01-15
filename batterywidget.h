#pragma once

#include <QWidget>
#include <QFile>
#include <QTextStream>
#include <QTimer>
#include <QProcess>

namespace Ui {
class BatteryWidget;
}

class BatteryWidget : public QWidget {
    Q_OBJECT

public:
    BatteryWidget() = delete;
    explicit BatteryWidget(int iMseconds = 30000, int iMode = 0, QWidget *parent = nullptr);
    ~BatteryWidget() override;
    BatteryWidget(const BatteryWidget &obj) = delete;
    BatteryWidget &operator=(const BatteryWidget &obj) = delete;
    BatteryWidget(BatteryWidget &&obj) = delete;
    BatteryWidget &operator=(BatteryWidget &&other) = delete;

private:
    enum WidgetMode { BatteryOnly = 0, BatteryAndTimeHorizontal, BatteryAndTimeVertical };

    Ui::BatteryWidget *ui;
    QString GetBatteryValue();
    QString GetBatteryValueFromSys();
    QString GetTime();
    QTimer *_timer;
    QProcess _process;
    int _mode;
    int _mseconds;

private slots:
    void UpdateLabel();
};

inline void skipLine(QTextStream &iStream, int iLines)
{
    for (int i = 0; i < iLines; i++) {
        iStream.readLine();
    }
}
