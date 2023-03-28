#include "ThreadPoolTest.h"

// Qt Includes
#include <QDebug>
#include <QEventLoop>
#include <QThread>

// Pro Includes
#include "PanelDriver.h"

ThreadPoolTest::ThreadPoolTest(QObject *parent) : QObject(parent)
{
#if 0
    qDebug() << __FUNCTION__ << QThread::currentThread();
#endif

    setAutoDelete(true);
    mTimerId = startTimer(1000);
}

ThreadPoolTest::~ThreadPoolTest()
{
#if 0
    qDebug() << __FUNCTION__ << QThread::currentThread();
#endif

    killTimer(mTimerId);
    mTimerId = 0;
}

void ThreadPoolTest::run()
{
#if 0
    qDebug() << __FUNCTION__ << QThread::currentThread();
#endif

    PanelDriver *panelDriver = new PanelDriver(this);

    QEventLoop eventLoop;
    eventLoop.exec();
}

void ThreadPoolTest::timerEvent(QTimerEvent *event)
{
    if (event->timerId() != mTimerId) {
        qDebug() << __FUNCTION__ << __LINE__;
        return;
    }

#if 1
    static int cnt = 0;
    qDebug() << __PRETTY_FUNCTION__ << cnt++;
#endif
}

