#include "ThreadPoolTest.h"

// Qt Includes
#include <QDebug>
#include <QEventLoop>
#include <QThread>

// Pro Includes
#include "PanelDriver.h"

/*!
 * @brief 构造函数
 * @details
 * @note 主线程
 */
ThreadPoolTest::ThreadPoolTest(QObject *parent) : QObject(parent)
{
#if 0
    qDebug() << __FUNCTION__ << QThread::currentThread();
#endif

    setAutoDelete(true);
    mTimerId = startTimer(1000);
}

/*!
 * @brief 析构函数
 * @details
 * @note 子线程
 */
ThreadPoolTest::~ThreadPoolTest()
{
#if 0
    qDebug() << __FUNCTION__ << QThread::currentThread();
#endif

    killTimer(mTimerId);
    mTimerId = 0;
}

/*!
 * @brief 主循环
 * @details
 * @note 子线程
 */
void ThreadPoolTest::run()
{
#if 0
    qDebug() << __FUNCTION__ << QThread::currentThread();
#endif

    PanelDriver *panelDriver = new PanelDriver(this);

    QEventLoop eventLoop;
    eventLoop.exec();
}


/*!
 * @brief 定时器事件
 * @details
 * @note
 */
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

