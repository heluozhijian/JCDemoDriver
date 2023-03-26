#include "PanelDriver.h"

// Qt Includes
#include <QDebug>
#include <QApplication>
#include <QCoreApplication>

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

uint qGlobalPostedEventsCount();

static int setup_unix_signal_handlers()
{
    struct sigaction sa;

    sa.sa_handler = PanelDriver::unixSignalHandler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sa.sa_flags |= SA_RESTART;

    if (sigaction(PanelDriver::mSignum, &sa, 0))
       return 1;

    return 0;
}

PanelDriver::PanelDriver(QObject *parent) : QObject(parent)
{
    // 1. file descriptor
    mFileDesc = ::open("/dev/demo", O_RDWR);
    if (mFileDesc < 0) {
        qDebug() << __PRETTY_FUNCTION__ << __LINE__;
    }

    // 2. signal number
    mSignum = SIGIO;

    // 3. fcntl
    int flags = ::fcntl(mFileDesc, F_GETFL);
    ::fcntl(mFileDesc, F_SETFL, flags | FASYNC);
    ::fcntl(mFileDesc, F_SETOWN, getpid());
    ::fcntl(mFileDesc, F_SETSIG, mSignum);

    // 4. setup unix signal handlers
    setup_unix_signal_handlers();
}

PanelDriver::~PanelDriver()
{

}

int PanelDriver::mFileDesc = 0;
int PanelDriver::mSignum = 0;

void PanelDriver::unixSignalHandler(int)
{
    static int cnt = 0;
    qDebug() << __FUNCTION__ << cnt++;
}
