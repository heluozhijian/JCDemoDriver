#ifndef JCDEMODRIVER_H
#define JCDEMODRIVER_H

#include <QWidget>

class JCDemoDriver : public QWidget
{
    Q_OBJECT
public:
    JCDemoDriver(QWidget *parent = nullptr);
    ~JCDemoDriver();

private:
    void initDriver();
    QString shell(const QString &cmd);

private:
    int mTimerId = 0;
protected:
    virtual void timerEvent(QTimerEvent *event);
};
#endif // JCDEMODRIVER_H
