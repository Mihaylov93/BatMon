#include "batterywidget.h"
#include "ui_batterywidget.h"

BatteryWidget::BatteryWidget(int mseconds,int mode, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BatteryWidget)
{

    ui->setupUi(this);
    this->mseconds = mseconds;
    this->mode = mode;
    this->setFocusPolicy(Qt::FocusPolicy::NoFocus);
    timer = new QTimer(this);
    int ph = this->geometry().height();
    int	px = this->geometry().x();
    int	py = this->geometry().y();
    int	dw = this->width();
    int	dh = this->height();
    this->setGeometry(px, py + ph - dh, dw, dh);

    switch (this->mode)
    {
        case 0: this->resize(QSize(16,9)); break; // Battery only
        case 1: this->resize(QSize(38,9)); break; // Battery and time horizontal layout
        case 2: this->resize(QSize(20,18)); break;// Battery and time vertical layout
    }

    setWindowFlags( Qt::Tool | Qt::X11BypassWindowManagerHint | Qt::WindowStaysOnTopHint| Qt::FramelessWindowHint  );

   
    this->setAttribute(Qt::WA_PaintOnScreen, true);

    this->setPalette(Qt::transparent);
    setStyleSheet("background-color: transparent");
    setAutoFillBackground(false);


    this->showNormal();
    this->UpdateLabel();

    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(refresh()));

    timer->start(mseconds);


}

QString BatteryWidget::GetBatteryValue(){

    QFile inputFile(QString("/sys/class/power_supply/axp20x-battery/uevent"),this);
    inputFile.open(QIODevice::ReadOnly);
    if (!inputFile.isOpen())
        return nullptr;

    QTextStream stream(&inputFile);
    QString line = stream.readLine();

    skipLine(stream,3);
    double voltage_now = stream.readLine().split("=")[1].toInt();
    skipLine(stream,4);
    double voltage_max = stream.readLine().split("=")[1].toInt();
    double voltage_min = stream.readLine().split("=")[1].toInt();

    QString percentage = QString::number(((voltage_now-voltage_min)/(voltage_max-voltage_min)) * 100);
    percentage.contains(".") ?  percentage = percentage.split(".")[0].append("%") : percentage = percentage.append("%");
    inputFile.close();

    return percentage;
}

QString BatteryWidget::GetTime()
{
    process.start("sh", QStringList()<<"-c"<<"date '+%H:%M'");
    process.waitForFinished();
    return process.readAllStandardOutput().trimmed();
}

void BatteryWidget::UpdateLabel()
{

    QString text;

    switch (mode)
    {
        case 0: text = GetBatteryValue(); break;
        case 1:
            text = GetBatteryValue().append(QString(" ").append(GetTime())); break;
        case 2:
            text = GetBatteryValue().append(QString("\n").append(GetTime())); break;
    }

    ui->label->setText(text);
    ui->label->adjustSize();
    //this->showNormal();
}

void BatteryWidget::refresh()
{
    this->UpdateLabel();
    this->hide();
    this->showNormal();
}

BatteryWidget::~BatteryWidget()
{
    delete ui;
}

