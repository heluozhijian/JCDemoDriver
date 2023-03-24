#include "JCDemoDriver.h"

// Qt Includes
#include <QApplication>
#include <QDebug>
#include <QProcess>
#include <QKeyEvent>
#include <QLayout>

// Sys Includes
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <sys/signal.h>
#include <sys/fcntl.h>
#include <sys/unistd.h>
#include <sys/socket.h>

// Pro Includes
#include "JOscilloscopeView.h"
#include "PanelDriver.h"

JCDemoDriver::JCDemoDriver(QWidget *parent) : QWidget(parent)
{
    setupUi();
    initDriver();
}

void JCDemoDriver::setupUi()
{
    JOscilloscopeView *view = new JOscilloscopeView(this);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(5);
    mainLayout->setContentsMargins(10, 10, 10, 10); // left top right bottom
    mainLayout->addWidget(view);
}

void JCDemoDriver::initDriver()
{
    shell("depmod");
    shell("rmmod jcmpanel.ko");
    shell("modprobe jcmpanel.ko signum=37");

    PanelDriver *panelDriver = new PanelDriver(this);
}

QString JCDemoDriver::shell(const QString &cmd)
{
    QProcess process;
    process.start(cmd);
    process.waitForFinished();
    QString str = process.readAllStandardOutput();
    process.close();
    return str;
}




