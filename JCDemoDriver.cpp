#include "JCDemoDriver.h"

// Qt Includes
#include <QApplication>
#include <QDebug>
#include <QProcess>
#include <QKeyEvent>
#include <QLayout>
#include <QThread>
#include <QTime>

// Sys Includes
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <sys/signal.h>
#include <sys/fcntl.h>
#include <sys/unistd.h>
#include <sys/socket.h>

// Pro Includes
#include "PanelDriver.h"

JCDemoDriver::JCDemoDriver(QWidget *parent) : QWidget(parent)
{
    resize(480, 320);
    setupUi();
#if 1
    panelDriver = new PanelDriver(this);
#endif
    mTimerId = startTimer(100);

}

JCDemoDriver::~JCDemoDriver()
{
    killTimer(mTimerId);
    mTimerId = 0;
}

//int JCDemoDriver::cnt = 0;

void JCDemoDriver::setupUi()
{
    label = new QLabel(this);
    QFont font = label->font();
    font.setPixelSize(30);
    label->setFont(font);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(label, 1, Qt::AlignCenter);
}

void JCDemoDriver::timerEvent(QTimerEvent *event)
{
    if (event->timerId() != mTimerId) {
        qDebug() << __FUNCTION__ << __LINE__;
        QWidget::timerEvent(event);
        return;
    }

    static int cnt = 0;
#if 0
    qDebug() << __FUNCTION__ << cnt++;
#else
    label->setText(QString::number(cnt++));
#endif

#if 1
    int ms = 0;
    do {
        QThread::msleep(1);
        QCoreApplication::processEvents();
        if (ms % 10 == 0)
            qDebug() << __FUNCTION__ << ms;
    } while ((ms++) < 200);
#else
    QThread::msleep(200);
#endif

    qDebug() << __FUNCTION__ << QTime::currentTime();
}




