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
    explicit BatteryWidget(int mseconds = 30000, int mode = 0, QWidget *parent = nullptr);
    ~BatteryWidget() override;
    BatteryWidget(const BatteryWidget &obj) = delete;
    BatteryWidget &operator=(const BatteryWidget &obj) = delete;
    BatteryWidget(BatteryWidget &&obj) = delete;
    BatteryWidget &operator=(BatteryWidget &&other) = delete;

private:
    Ui::BatteryWidget *ui;
    QString GetBatteryValue();
    QString GetTime();
    void UpdateLabel();
    QTimer *timer;
    QProcess process;
    int mode;
    int mseconds;
    private slots:
    void refresh();
};

inline void skipLine(QTextStream &stream, int n)
{
    for (int i = 0; i < n; i++) {
        stream.readLine();
    }
}
