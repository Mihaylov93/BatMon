#ifndef BATTERYWIDGET_H
#define BATTERYWIDGET_H

#include <QWidget>
#include <QFile>
#include <QTextStream>
#include <QTimer>

namespace Ui {
    class BatteryWidget;
}

class BatteryWidget : public QWidget
{
    Q_OBJECT

public:
    explicit BatteryWidget(QWidget *parent = nullptr);
    virtual ~BatteryWidget();
    void setTimer(int mseconds);
private:
    Ui::BatteryWidget *ui;
    void GetBatteryValue();
    QTimer *timer;
private slots:
   void refresh();
};

inline void skipLine(QTextStream & stream,int n){
    for (int i = 0; i<n; i++){
        stream.readLine();
    }
}


#endif // BATTERYWIDGET_H
