#include "PanelDriver.h"

// Qt Includes
#include <QDebug>
#include <QApplication>
#include <QCoreApplication>
#include <QThread>

// Sys Includes
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <sys/signal.h>
#include <sys/fcntl.h>
#include <sys/unistd.h>
#include <sys/socket.h>
#include <sys/file.h>
#include <stdio.h>

PanelDriver::PanelDriver(QObject *parent) : JUnixDriver(parent)
{
    // 1. file descriptor
    mFileDesc = ::open("/dev/demo", O_RDWR | O_NONBLOCK);
    if (mFileDesc < 0) {
        qDebug() << __PRETTY_FUNCTION__ << __LINE__;
    }

    // 2. signal number
    mSignum = SIGIO;

    // 3. init
    if (init(mFileDesc, mSignum) < 0) {
        qDebug() << __PRETTY_FUNCTION__ << __LINE__;
    }
}

PanelDriver::~PanelDriver()
{

}

void PanelDriver::signalHandler()
{
    qDebug() << __FUNCTION__ << cnt;
}

