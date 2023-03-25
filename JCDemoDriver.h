#ifndef JCDEMODRIVER_H
#define JCDEMODRIVER_H

#include <QWidget>
#include <QLabel>

#include "PanelDriver.h"

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
    PanelDriver *panelDriver = nullptr;
    int mTimerId = 0;
protected:
    virtual void timerEvent(QTimerEvent *event);
};
#endif // JCDEMODRIVER_H
