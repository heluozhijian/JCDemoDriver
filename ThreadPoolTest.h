#ifndef THREADPOOLTEST_H
#define THREADPOOLTEST_H

// Qt Includes
#include <QObject>
#include <QRunnable>
#include <QTimerEvent>

// Lib Includes

// Pro Includes

/*!
 * @brief ThreadPoolTest
 * @details
 * @note
 */
class ThreadPoolTest : public QObject, public QRunnable
{
    Q_OBJECT
public:
    ThreadPoolTest(QObject *parent = nullptr);      //!< 构造函数
    ~ThreadPoolTest();                              //!< 析构函数

private:
    void run();                                     //!< 主循环

private:
    int mTimerId = 0;
protected:
    virtual void timerEvent(QTimerEvent *event);    //!< 定时器事件
};

#endif // THREADPOOLTEST_H
