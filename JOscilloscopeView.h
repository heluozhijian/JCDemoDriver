#ifndef JOSCILLOSCOPEVIEW_H
#define JOSCILLOSCOPEVIEW_H

// Qt Includes
#include <QtCharts>
#if 0
#include <QChart>
#include <QChartView>
#endif
#include <QWidget>

/*!
 * @brief JOscilloscopeView
 * @details
 * @note
 */
class JOscilloscopeView : public QWidget
{
    Q_OBJECT
public:
    JOscilloscopeView(QWidget *parent = nullptr);
    ~JOscilloscopeView();

private:
    QLineSeries *mLineSeries = nullptr;
    QChart *mChart = nullptr;
    QChartView *mChartView = nullptr;
    void setupUi();

private:
    int mTimerId = 0;
protected:
    virtual void timerEvent(QTimerEvent *event);
};

#endif // JOSCILLOSCOPEVIEW_H
