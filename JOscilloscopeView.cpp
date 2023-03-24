#include "JOscilloscopeView.h"

// Qt Includes
#include <QChart>
#include <QDebug>
#include <QLayout>

JOscilloscopeView::JOscilloscopeView(QWidget *parent) : QWidget(parent)
{
    setupUi();
    mTimerId = startTimer(100); // 50Hz
}

JOscilloscopeView::~JOscilloscopeView()
{
    killTimer(mTimerId);
    mTimerId = 0;
}

void JOscilloscopeView::setupUi()
{
    /* 1. Axis */
    QValueAxis *xAxis = new QValueAxis(this);
    xAxis->setTitleText("X");
    xAxis->setRange(0, 10);
    QValueAxis *yAxis = new QValueAxis(this);
    yAxis->setTitleText("Y");
    yAxis->setRange(-10, 10);

    /* 2. Line Series */
    mLineSeries = new QLineSeries(this);
    mLineSeries->setPointsVisible(true);
    mLineSeries->setName("rand");

    /* 3. Chart */
    mChart = new QChart(nullptr); // TODO: parent
    mChart->addAxis(xAxis, Qt::AlignBottom);
    mChart->addAxis(yAxis, Qt::AlignLeft);
    mChart->addSeries(mLineSeries);
    mChart->setAnimationOptions(QChart::SeriesAnimations);

    /* Attach Axis */
    mLineSeries->attachAxis(xAxis);
    mLineSeries->attachAxis(yAxis);

    /* 4. Chart View */
    mChartView = new QChartView(this);
    mChartView->setChart(mChart);
    mChartView->setRenderHint(QPainter::Antialiasing);

    /* 5. Main Layout */
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(5);
    mainLayout->setContentsMargins(10, 10, 10, 10); // left top right bottom
    mainLayout->addWidget(mChartView);
}

void JOscilloscopeView::timerEvent(QTimerEvent *event)
{
    if (event->timerId() != mTimerId) {
        qDebug() << __PRETTY_FUNCTION__ << __LINE__;
        return;
    }

#if 0
    qDebug() << __FUNCTION__ << __LINE__;
#else
    int count = mLineSeries->points().size();
    if(count > 10) {
        mChart->axisX()->setMax(count);
    }
    mLineSeries->append(QPointF(count, rand() % 10));
#endif
}
