#include "batterywidget.h"
#include "ui_batterywidget.h"
#include <QPainter>
#include <QRegularExpression>
BatteryWidget::BatteryWidget(int mseconds, int mode, QWidget *parent) : QWidget(parent), ui(new Ui::BatteryWidget)
{

    ui->setupUi(this);

    this->mseconds = mseconds;
    this->mode = mode;
    this->setFocusPolicy(Qt::FocusPolicy::NoFocus);
    timer = new QTimer(this);
    const int ph = this->geometry().height();
    const int px = this->geometry().x();
    const int py = this->geometry().y();
    const int dw = this->width();
    const int dh = this->height();

    this->setGeometry(px, py + ph - dh, dw, dh);

    switch (this->mode) {
        case 0:
            this->resize(QSize(21, 9));
            break;    // Battery only
        case 1:
            this->resize(QSize(44, 9));
            break;    // Battery and time horizontal layout
        case 2:
            this->resize(QSize(21, 18));
            break;    // Battery and time vertical layout
    }

    setWindowFlags(Qt::Widget | Qt::X11BypassWindowManagerHint | Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);

    setParent(nullptr);    // Set to TopLevel-Widget
    setAttribute(Qt::WA_NoSystemBackground, true);
    setAttribute(Qt::WA_TranslucentBackground, true);

    this->showNormal();
    this->UpdateLabel();

    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(refresh()));

    timer->start(mseconds);
}

QString BatteryWidget::GetBatteryValue()
{
    QString percentage;

    upowerProc.start("upower",
                     QStringList() << "-i"
                                   << "/org/freedesktop/UPower/devices/battery_axp20x_battery");
    upowerProc.waitForFinished();

    QRegularExpression re
        = QRegularExpression("^\\s+percentage:\\s+([0-9]{1,3}%)$", QRegularExpression::MultilineOption);

    QRegularExpressionMatch match = re.match(upowerProc.readAllStandardOutput().trimmed());
    if (!match.hasMatch())
        percentage = GetBatteryValueFromSys();
    else
        percentage = match.captured(1);

    return percentage;
}

QString BatteryWidget::GetBatteryValueFromSys()
{
    QFile inputFile(QString("/sys/class/power_supply/axp20x-battery/uevent"), this);
    inputFile.open(QIODevice::ReadOnly);
    if (!inputFile.isOpen()) return nullptr;

    QTextStream stream(&inputFile);

    skipLine(stream, 4);
    const double voltage_now = stream.readLine().split("=")[1].toInt();
    skipLine(stream, 4);
    const double voltage_max = stream.readLine().split("=")[1].toInt();
    const double voltage_min = stream.readLine().split("=")[1].toInt();

    QString percentage = QString::number(((voltage_now - voltage_min) / (voltage_max - voltage_min)) * 100);
    percentage.contains(".") ? percentage = percentage.split(".")[0].append("%") : percentage = percentage.append("%");
    inputFile.close();

    return percentage;
}

QString BatteryWidget::GetTime()
{
    process.start("sh",
                  QStringList() << "-c"
                                << "date '+%H:%M'");
    process.waitForFinished();
    return process.readAllStandardOutput().trimmed();
}

void BatteryWidget::UpdateLabel()
{

    QString text;

    switch (mode) {
        case 0:
            text = GetBatteryValue();
            break;
        case 1:
            text = GetBatteryValue().append(QString(" ").append(GetTime()));
            break;
        case 2:
            text = GetBatteryValue().append(QString("\n").append(GetTime()));
            break;
    }

    ui->label->setText(text);
    ui->label->adjustSize();
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
