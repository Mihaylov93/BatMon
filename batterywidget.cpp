#include "batterywidget.h"
#include "ui_batterywidget.h"

BatteryWidget::BatteryWidget(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BatteryWidget)
{
    ui->setupUi(this);
    this->setFocusPolicy(Qt::FocusPolicy::NoFocus);
    this->move(this->rect().topLeft().x(),this->rect().topLeft().y());

    setWindowFlags( Qt::Tool | Qt::X11BypassWindowManagerHint | Qt::WindowStaysOnTopHint| Qt::FramelessWindowHint   );


    this->setAttribute( Qt::WA_TranslucentBackground, true );
    this->setAttribute(Qt::WA_NoSystemBackground, true);
    this->setAttribute(Qt::WA_PaintOnScreen, true);
    this->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    // This probably does nothing as TWM doesnt implement ewmh
    this->setAttribute(Qt::WA_X11NetWmWindowTypeDock,true);
    this->setAttribute(Qt::WA_ShowWithoutActivating);
    this->setPalette(Qt::transparent);
    setStyleSheet("background-color: rgba(0,0,0,0)");
    setAutoFillBackground(false);

    this->showNormal();
    this->GetBatteryValue();
}

void BatteryWidget::GetBatteryValue(){

    QFile inputFile(QString("/sys/class/power_supply/axp20x-battery/uevent"),this);
    inputFile.open(QIODevice::ReadOnly);
    if (!inputFile.isOpen())
        return;

    QTextStream stream(&inputFile);
    QString line = stream.readLine();

    stream.readLine();
    stream.readLine();
    stream.readLine();
    double voltage_now = stream.readLine().split("=")[1].toInt();
    stream.readLine();
    stream.readLine();
    stream.readLine();
    stream.readLine();
    double voltage_max = stream.readLine().split("=")[1].toInt();
    double voltage_min = stream.readLine().split("=")[1].toInt();

    QString percentage = QString::number(((voltage_now-voltage_min)/(voltage_max-voltage_min)) * 100);
    percentage.contains(".") ?  ui->label->setText(percentage.split(".")[0].append("%")) : ui->label->setText(percentage.append("%"));

    inputFile.close();
}

BatteryWidget::~BatteryWidget()
{
    delete ui;
}


