#ifndef PANELDRIVER_H
#define PANELDRIVER_H

#include <QObject>
#include <QSocketNotifier>
#include <QMutex>

/*!
 * @brief PanelDriver
 * @details
 * @note
 */
class PanelDriver: public QObject
{
    Q_OBJECT
public:
    PanelDriver(QObject *parent = nullptr);
    ~PanelDriver();

public:
    // file descriptor
    static int mFileDesc;
    // signal number
    static int mSignum;
    // mutex
    static QMutex mMutex;
    // counter
    static int cnt;

public:
    // Unix signal handlers.
    static void unixSignalHandler(int unused);
};

#endif // PANELDRIVER_H
