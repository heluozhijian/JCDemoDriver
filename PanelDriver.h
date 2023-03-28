#ifndef PANELDRIVER_H
#define PANELDRIVER_H

#include <QObject>
#include <QSocketNotifier>
#include <QMutex>
#include <QRunnable>

#include "JUnixDriver.h"
/*!
 * @brief PanelDriver
 * @details
 * @note
 */
class PanelDriver: public JUnixDriver
{
    Q_OBJECT
public:
    PanelDriver(QObject *parent = nullptr);
    ~PanelDriver();

private:
    void signalHandler() override;              //!< 信号处理程序
signals:
    void signalHandler(int signum);
};

#endif // PANELDRIVER_H
