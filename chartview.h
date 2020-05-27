#ifndef CHARTVIEW_H
#define CHARTVIEW_H

#include <QtCharts/QChartView>

QT_CHARTS_USE_NAMESPACE

class ChartView : public QChartView
{
    Q_OBJECT
public:
    explicit ChartView(QWidget *parent = 0);
};
class ChartView2 : public QChartView
{
    Q_OBJECT
public:
    explicit ChartView2(QWidget *parent = 0);
};

#endif // CHARTVIEW_H
