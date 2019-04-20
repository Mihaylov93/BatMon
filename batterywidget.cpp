#include "batterywidget.h"
#include "ui_batterywidget.h"

BatteryWidget::BatteryWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BatteryWidget)

{
    ui->setupUi(this);
    this->setFocusPolicy(Qt::FocusPolicy::NoFocus);
    timer = new QTimer(this);
    int ph = this->geometry().height();
    int	px = this->geometry().x();
    int	py = this->geometry().y();
    int	dw = this->width();
    int	dh = this->height();
    this->setGeometry(px, py + ph - dh, dw, dh);
    this->resize(QSize(16,9));

    setWindowFlags( Qt::Tool | Qt::X11BypassWindowManagerHint | Qt::WindowStaysOnTopHint| Qt::FramelessWindowHint  );

   
    this->setAttribute(Qt::WA_PaintOnScreen, true);

    this->setPalette(Qt::transparent);
    setStyleSheet("background-color: transparent");
    setAutoFillBackground(false);

    this->showNormal();
    this->GetBatteryValue();

    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(refresh()));
}

void BatteryWidget::GetBatteryValue(){

    QFile inputFile(QString("/sys/class/power_supply/axp20x-battery/uevent"),this);
    inputFile.open(QIODevice::ReadOnly);
    if (!inputFile.isOpen())
        return;

    QTextStream stream(&inputFile);
    QString line = stream.readLine();

    skipLine(stream,3);
    double voltage_now = stream.readLine().split("=")[1].toInt();
    skipLine(stream,4);
    double voltage_max = stream.readLine().split("=")[1].toInt();
    double voltage_min = stream.readLine().split("=")[1].toInt();

    QString percentage = QString::number(((voltage_now-voltage_min)/(voltage_max-voltage_min)) * 100);
    percentage.contains(".") ?  ui->label->setText(percentage.split(".")[0].append("%")) : ui->label->setText(percentage.append("%"));
    
    inputFile.close();
}

void BatteryWidget::refresh()
{
    this->GetBatteryValue();
    this->hide();
    this->showNormal();
}

BatteryWidget::~BatteryWidget()
{
    delete ui;
}

void BatteryWidget::setTimer(int mseconds)
{
    timer->start(mseconds);
}

