#include "JUnixDriver.h"

// Qt Includes
#include <QDebug>
#include <QTime>

// Pro Includes

// Sys Includes
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/signal.h>
#include <sys/fcntl.h>
#include <sys/unistd.h>
#include <sys/socket.h>

// NOTE:
// <Calling Qt Functions From Unix Signal Handlers>
// https://doc.qt.io/qt-5/unix-signals.html


JUnixDriver::JUnixDriver(QObject *parent) : QObject(parent)
{

}

JUnixDriver::~JUnixDriver()
{

}

int JUnixDriver::cnt = 0;
QMutex JUnixDriver::mMutexCnt;
int JUnixDriver::mSocket[2];
QReadWriteLock JUnixDriver::mSocketLock;

int JUnixDriver::fileDesc()
{
    QReadLocker locker(&mFileDescLock);
    return mFileDesc;
}

int JUnixDriver::signum()
{
    QReadLocker locker(&mSignumLock);
    return mSignum;
}

bool JUnixDriver::init(const int fileDesc, const int signum)
{
    // (1) fcntl
    int flags = ::fcntl(fileDesc, F_GETFL);
    ::fcntl(fileDesc, F_SETFL, flags | FASYNC);
    ::fcntl(fileDesc, F_SETOWN, getpid());
    ::fcntl(fileDesc, F_SETSIG, signum);

    // (2) signal
    if (setupUnixSignalHandler(signum, unixSignalHandler) != 0) {
        qDebug() << __PRETTY_FUNCTION__ << __LINE__;
        return false;
    }

    // (3) socket
    if (::socketpair(AF_UNIX, SOCK_STREAM, 0, mSocket)) { // create socketpair
        qDebug() << __PRETTY_FUNCTION__ << __LINE__;
        return false;
    }
    mSocketNotifier = new QSocketNotifier(mSocket[1], QSocketNotifier::Read, this);
    QObject::connect(mSocketNotifier, SIGNAL(activated(int)), this, SLOT(qtSignalHandler()));

    return true;
}

void JUnixDriver::signalHandler()
{
    qDebug() << __FUNCTION__;
}

void JUnixDriver::unixSignalHandler(int)
{
#if 0
    // without socket
    QMutexLocker locker(&mMutexCnt);
    cnt++;
#else
    // with socket
    // QWriteLocker locker(&mSocketLock); // not used
    char a = 1;
    ::write(mSocket[0], &a, sizeof(a));
#endif

}

int JUnixDriver::setupUnixSignalHandler(int signum, void (*sighandler)(int))
{
    struct sigaction sa;

    sa.sa_handler = sighandler;
    ::sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sa.sa_flags |= SA_RESTART;

    if (::sigaction(signum, &sa, 0))
        return -1;

    return 0;
}

void JUnixDriver::qtSignalHandler()
{
    // QReadLocker locker(&mSocketLock); // not used

    mSocketNotifier->setEnabled(false);
    char tmp;
    ::read(mSocket[1], &tmp, sizeof(tmp));

    // do Qt stuff
    signalHandler();

    mSocketNotifier->setEnabled(true);
}


