#ifndef SMALLCHART_H
#define SMALLCHART_H


#include <QWidget>
#include <QChart>
#include <QChartView>
#include <QtCharts>
#include <QList>
//#include "mainmodel.h"
#include  "chartdata.h"
//class chartData{
//public:
//    chartData();
////    chartData( Data data);
//    ~chartData();
//    void getFirstData( Data data);
//    QDateTimeAxis *axisX;
//    QList<QPointF>* point_list_cpu;
//    QList<QPointF>* point_list_gpu;
//    QList<QPointF>* point_list_mem;
//    QList<QPointF>* point_list_dis;
//    MyTime m_currentTime;
//    MyTime m_firstMyTime;
//    int pointSize=0;
//    QString ip="";
//    QDateTime m_firstTimte;
//    QDateTime MyTimeToQDateTime();
//    bool currentTimeAddSecIsDatasTime(MyTime t);
//    QString myTimeToQString();

//};


class currentData : public QWidget
{
    Q_OBJECT
public:
    explicit currentData(QWidget *parent = nullptr);
    explicit currentData(QString text,QWidget *parent = nullptr);

    QChart *m_chart;
    QString m_text;
    QLineSeries *m_series;
    QChartView* m_charView;
//    QDateTimeAxis *axisX;
    QDateTime m_first;
    QDateTimeAxis *axisX;
    QList<QPointF>*m_point_list;

    void clearChart();
    void refresh(int ret);
    void refresshSeries(chartData* data, QString text);
    void appendPoint(QPointF p,QDateTime t);


signals:



//    explicit currentData(QWidget *parent = nullptr);
//    QChart* m_chart;
//    QLineSeries *m_series;
//    QList<QPointF>m_point_list;
//    qlonglong m_firstTime;
//    QDateTime m_firstDateTime;
//    QChartView* m_charView;

//    void appendData(QDateTime t,int data);
signals:

public slots:
};

#endif // SMALLCHART_H
