#ifndef JUNIXDRIVER_H
#define JUNIXDRIVER_H

// Qt Includes
#include <QObject>
#include <QSocketNotifier>
#include <QMutex>
#include <QReadWriteLock>

/*!
 * @brief JUnixDriver
 * @details
 * @note
 */
class JUnixDriver: public QObject
{
    Q_OBJECT
public:
    JUnixDriver(QObject *parent = nullptr);
    ~JUnixDriver();

public:
    int fileDesc();
    int signum();

protected:
    int mFileDesc = 0;
    int mSignum;
    QReadWriteLock mFileDescLock;
    QReadWriteLock mSignumLock;
    bool init(const int fileDesc, const int signum);
    virtual void signalHandler();

private:
    static void unixSignalHandler(int unused);
    int setupUnixSignalHandler(int signum,
                               void (*sighandler)(int));

public:
    static int cnt;
    static QMutex mMutexCnt;

private:
    static int mSocket[2];
    static QReadWriteLock mSocketLock; // not used
    QSocketNotifier *mSocketNotifier;
private slots:
    void qtSignalHandler();
};

#endif // JUNIXDRIVER_H
