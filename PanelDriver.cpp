#include "PanelDriver.h"

// Qt Includes
#include <QDebug>

// Sys Includes
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <sys/signal.h>
#include <sys/fcntl.h>
#include <sys/unistd.h>
#include <sys/socket.h>

// Drv Includes
#include "jcmpanel.h"

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
    mFileDesc = ::open("/dev/jcmpanel", O_RDWR);
    if (mFileDesc < 0) {
        qDebug() << __PRETTY_FUNCTION__ << __LINE__;
    }

    // 2. signal number
    ::ioctl(mFileDesc, JCMPANEL_IOR_SIGNUM, &mSignum);
    qDebug() << __FUNCTION__ << mSignum;

    // 3. fcntl
    int flags = ::fcntl(mFileDesc, F_GETFL);
    ::fcntl(mFileDesc, F_SETFL, flags | FASYNC);
    ::fcntl(mFileDesc, F_SETOWN, getpid());
    ::fcntl(mFileDesc, F_SETSIG, mSignum);

    // 4. socket
    if (::socketpair(AF_UNIX, SOCK_STREAM, 0, mSocketFd)) { // create socketpair
        qDebug() << __PRETTY_FUNCTION__ << __LINE__;
    }
    mSocketNotifier = new QSocketNotifier(mSocketFd[1], QSocketNotifier::Read, this);
    QObject::connect(mSocketNotifier, SIGNAL(activated(int)), this, SLOT(qtSignalHandler()));

    // 5. setup unix signal handlers
    setup_unix_signal_handlers();
}

int PanelDriver::mFileDesc = 0;
int PanelDriver::mSignum = 0;
int PanelDriver::mSocketFd[2];

void PanelDriver::unixSignalHandler(int)
{
    char a = 1;
    ::write(mSocketFd[0], &a, sizeof(a));
}

void PanelDriver::qtSignalHandler()
{
    qDebug() << __FUNCTION__ << 0;

    mSocketNotifier->setEnabled(false);
    char tmp;
    ::read(mSocketFd[1], &tmp, sizeof(tmp));
    qDebug() << __FUNCTION__ << 1;

    // do Qt stuff
//    static int cnt = 0;
//    qDebug() << __FUNCTION__ << cnt++;
    emit panelChanged();
    qDebug() << __FUNCTION__ << 2;

    mSocketNotifier->setEnabled(true);
    qDebug() << __FUNCTION__ << 3;
}





