#ifndef JCDEMODRIVER_H
#define JCDEMODRIVER_H

#include <QWidget>

class JCDemoDriver : public QWidget
{
    Q_OBJECT
public:
    JCDemoDriver(QWidget *parent = nullptr);

private:
    void setupUi();
    void initDriver();
    QString shell(const QString &cmd);
};
#endif // JCDEMODRIVER_H
