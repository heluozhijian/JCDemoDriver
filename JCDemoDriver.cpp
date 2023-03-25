#include "JCDemoDriver.h"

// Qt Includes
#include <QApplication>
#include <QDebug>
#include <QProcess>
#include <QKeyEvent>
#include <QLayout>
#include <QThread>

// Sys Includes
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <sys/signal.h>
#include <sys/fcntl.h>
#include <sys/unistd.h>
#include <sys/socket.h>

// Pro Includes
#include "PanelDriver.h"

JCDemoDriver::JCDemoDriver(QWidget *parent) : QWidget(parent)
{
    mTimerId = startTimer(100);
    initDriver();
}

JCDemoDriver::~JCDemoDriver()
{
    killTimer(mTimerId);
    mTimerId = 0;
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

void JCDemoDriver::timerEvent(QTimerEvent *event)
{
    if (event->timerId() != mTimerId) {
        qDebug() << __FUNCTION__ << __LINE__;
        return;
    }
#if 1
    static int cnt = 0;
    qDebug() << __FUNCTION__ << cnt++;
#endif
    QThread::msleep(100); // causes the application blocking
}




