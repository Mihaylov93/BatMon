#include "batterywidget.h"
#include "ui_batterywidget.h"
#include <QPainter>
#include <QRegularExpression>
BatteryWidget::BatteryWidget(int iMseconds, int iMode, QWidget *parent) : QWidget(parent), ui(new Ui::BatteryWidget)
{

    ui->setupUi(this);

    this->_mseconds = iMseconds;
    this->_mode = iMode;
    this->setFocusPolicy(Qt::FocusPolicy::NoFocus);
    _timer = new QTimer(this);
    const int ph = this->geometry().height();
    const int px = this->geometry().x();
    const int py = this->geometry().y();
    const int dw = this->width();
    const int dh = this->height();

    this->setGeometry(px, py + ph - dh, dw, dh);

    switch (this->_mode) {
        case BatteryOnly:
            this->resize(QSize(21, 9));
            break;
        case BatteryAndTimeHorizontal:
            this->resize(QSize(44, 9));
            break;
        case BatteryAndTimeVertical:
            this->resize(QSize(21, 18));
            break;
    }

    setWindowFlags(Qt::Widget | Qt::X11BypassWindowManagerHint | Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);

    setParent(nullptr);    // Set to TopLevel-Widget
    setAttribute(Qt::WA_NoSystemBackground, true);
    setAttribute(Qt::WA_TranslucentBackground, true);

    this->showNormal();
    this->UpdateLabel();

    QObject::connect(_timer, SIGNAL(timeout()), this, SLOT(UpdateLabel()));

    _timer->start(iMseconds);
}

QString BatteryWidget::GetBatteryValue()
{
    QString mPercentage;

    _process.start("upower",
                   QStringList() << "-i"
                                 << "/org/freedesktop/UPower/devices/battery_axp20x_battery");
    _process.waitForFinished();

    QRegularExpression re
        = QRegularExpression("^\\s+percentage:\\s+([0-9]{1,3}%)$", QRegularExpression::MultilineOption);

    QRegularExpressionMatch match = re.match(_process.readAllStandardOutput().trimmed());
    if (Q_LIKELY(match.hasMatch()))
        mPercentage = match.captured(1);
    else
        mPercentage = GetBatteryValueFromSys();

    return mPercentage;
}

QString BatteryWidget::GetBatteryValueFromSys()
{
    QFile inputFile(QString("/sys/class/power_supply/axp20x-battery/uevent"), this);
    inputFile.open(QIODevice::ReadOnly);
    if (!inputFile.isOpen()) return nullptr;

    QTextStream mStream(&inputFile);

    skipLine(mStream, 4);
    const double voltage_now = mStream.readLine().split("=")[1].toInt();
    skipLine(mStream, 4);
    const double voltage_max = mStream.readLine().split("=")[1].toInt();
    const double voltage_min = mStream.readLine().split("=")[1].toInt();

    QString mPercentage = QString::number(((voltage_now - voltage_min) / (voltage_max - voltage_min)) * 100);
    mPercentage.contains(".") ? mPercentage = mPercentage.split(".")[0].append("%")
                              : mPercentage = mPercentage.append("%");
    inputFile.close();

    return mPercentage;
}

QString BatteryWidget::GetTime()
{
    _process.start("sh",
                   QStringList() << "-c"
                                 << "date '+%H:%M'");
    _process.waitForFinished();
    return _process.readAllStandardOutput().trimmed();
}

void BatteryWidget::UpdateLabel()
{

    QString mText;

    switch (_mode) {
        case BatteryOnly:
            mText = GetBatteryValue();
            break;
        case BatteryAndTimeHorizontal:
            mText = GetBatteryValue().append(QString(" ").append(GetTime()));
            break;
        case BatteryAndTimeVertical:
            mText = GetBatteryValue().append(QString("\n").append(GetTime()));
            break;
    }

    ui->label->setText(mText);
    ui->label->adjustSize();
    this->raise();
}

BatteryWidget::~BatteryWidget()
{
    delete ui;
}
