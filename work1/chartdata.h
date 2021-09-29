#ifndef CHARTDATAMAP_H
#define CHARTDATAMAP_H

//#include <QtCharts/qdatetimeaxis.h>
//#include <QtCharts/qdatetimeaxis.h>

#include "mytime.h"
#include <QWidget>
#include <QChart>
#include <QChartView>
#include <QtCharts>
#include <QList>
#include "data.h"

//!  data struct
class chartData{
public:
    chartData();
//    chartData( Data data);
    ~chartData();
    void getFirstData( Data data);
    QDateTimeAxis *axisX;
    QList<QPointF>* point_list_cpu;
    QList<QPointF>* point_list_gpu;
    QList<QPointF>* point_list_mem;
    QList<QPointF>* point_list_dis;
    QList<QPointF>* point_list_net;
    MyTime m_currentTime;
    MyTime m_firstMyTime;
    int pointSize=0;
    QString ip="";
    QDateTime m_firstTimte;
    QDateTime MyTimeToQDateTime();
    QDateTime CurrentMyTimeToDateTime();
    bool currentTimeAddSecIsDatasTime(MyTime t);
    QString myTimeToQString();

};
Q_DECLARE_METATYPE(chartData)

#endif // CHARTDATAMAP_H
