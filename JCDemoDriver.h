#ifndef JCDEMODRIVER_H
#define JCDEMODRIVER_H

#include <QWidget>
#include <QLabel>

#include "ThreadPoolTest.h"

class JCDemoDriver : public QWidget
{
    Q_OBJECT
public:
    JCDemoDriver(QWidget *parent = nullptr);
    ~JCDemoDriver();

private:
    QLabel *label = nullptr;
    void setupUi();

private:
    ThreadPoolTest *threadPoolTest = nullptr;
    int mTimerId = 0;
protected:
    virtual void timerEvent(QTimerEvent *event);
};
#endif // JCDEMODRIVER_H
