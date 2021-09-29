#include "smallchart.h"


//#include "currentdata.h"
#include <QDebug>
#include "widget.h"



currentData::currentData(QWidget *parent) : QWidget(parent)
{
////    m_chart=new QChart();
////    m_series = new QLineSeries();
////    m_series->setName("data");
////    m_chart->setTheme(QChart::ChartThemeDark);
////    m_chart->addSeries(m_series);

////    m_chart->setDropShadowEnabled(true);



////    QValueAxis *axisY = new QValueAxis();
////    axisY->setRange(0,110);
////    m_chart->setAxisY(axisY,m_series);

////    m_charView=new QChartView(m_chart);
////    m_charView->setRenderHint(QPainter::Antialiasing);
////    QVBoxLayout *pvLayout=new QVBoxLayout(this);
////    pvLayout->addWidget(m_charView);
////    resize(200,200);
////    axisX=new QDateTimeAxis;
//    axisX=new QDateTimeAxis;
//    m_point_list=new QList<QPointF>;
//    m_chart=new QChart();
//    m_series = new QLineSeries();
//    m_series->setName(m_text);
//    m_chart->setTheme(QChart::ChartThemeDark);
//    m_chart->addSeries(m_series);

//    m_chart->setDropShadowEnabled(true);
//    m_chart->setAxisX(axisX,m_series);



//    QValueAxis *axisY = new QValueAxis();
//    axisY->setRange(0,110);
//    m_chart->setAxisY(axisY);

//    m_charView=new QChartView(m_chart);
//    m_charView->setRenderHint(QPainter::Antialiasing);
//    QVBoxLayout *pvLayout=new QVBoxLayout(this);
//    pvLayout->addWidget(m_charView);
//    resize(200,200);
}


currentData::currentData(QString text,QWidget *parent):QWidget(parent),m_text(text)
{

    axisX=new QDateTimeAxis;
    m_point_list=new QList<QPointF>;
    m_chart=new QChart();
    m_series = new QLineSeries();

    m_series->setName(m_text);
    m_chart->setTheme(QChart::ChartThemeDark);
    m_chart->addSeries(m_series);
    m_chart->setDropShadowEnabled(true);
    m_chart->setAxisX(axisX,m_series);
    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(0,110);
    m_chart->setAxisY(axisY,m_series);
    m_charView=new QChartView(m_chart);
    m_charView->setRenderHint(QPainter::Antialiasing);
    QVBoxLayout *pvLayout=new QVBoxLayout(this);
    pvLayout->addWidget(m_charView);
    resize(200,200);
}

void currentData::clearChart()
{
    QLineSeries *series =(QLineSeries*)this->m_chart->series().at(0);
    series->points().clear();
    m_series->points().clear();
    m_series->clear();
    series=nullptr;
    delete series;
}

void currentData::refresh(int ret)
{
    qDebug()<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!";
    chartData *data=OverAllVar::m_chartData_List.at(ret);

//    chartData d= *data;
    qDebug()<<"refresh"<<data->axisX->min();
    qDebug()<<"refresh"<<data->axisX->max();

    clearChart();

    axisX->setRange(data->axisX->min(),data->axisX->max());
//    axisX->setMin(data->m_firstTimte);

//    m_series->append(QList<QPointF>(*(data->point_list_cpu)));
    refresshSeries(data,m_text);
//   QDateTimeAxis* axisX=new QDateTimeAxis;
    axisX->setFormat("h:mm:s");
//    axisX->setRange(data->m_firstTimte,data->CurrentMyTimeToDateTime());
    m_first=data->m_firstTimte;

    data=nullptr;
    delete data;

}



//void currentData::refresh(chartData data)
//{
////    QLineSeries *series =(QLineSeries*)this->m_chart->series().at(0);
////    series->clear();
////    m_point_list.append(QPointF(t.toMSecsSinceEpoch(),data));
////    series->append(m_point_list);
////    QDateTimeAxis *axisX=new QDateTimeAxis;
////    axisX->setFormat("h:mm:ss");
////    axisX->setRange(m_firstDateTime,t);

////    m_chart->setAxisX(axisX,series);

////    QLineSeries *series =(QLineSeries*)this->m_chart->series().at(0);


////    series->clear();
////    m_chart->removeAllSeries();
////    series->clear();
////    m_point_list->clear();
////    m_point_list->append(*(data->point_list_cpu));
////    series->append(*m_point_list);
//    QLineSeries *series =(QLineSeries*)this->m_chart->series().at(0);
//    series->points().clear();
//    axisX->setRange(data.axisX->min(),data.axisX->max());
////    axisX->setMin(data->m_firstTimte);
//    m_series->points().clear();
//    m_series->clear();
////    m_series->append(QList<QPointF>(*(data->point_list_cpu)));
//    refresshSeries(data,m_text);



////   QDateTimeAxis* axisX=new QDateTimeAxis;
//    axisX->setFormat("h:mm:s");
////    axisX->setRange(data->m_firstTimte,data->CurrentMyTimeToDateTime());
//    m_first=data.m_firstTimte;
////    m_chart->setAxisX(axisX,m_series);
////    update();
////    qDebug()<<"refresh11111111111111111111111111111111111111111111111111111111111111111111";

//}

//void currentData::appenPoint(QPointF point, QDateTime t)
//{
////    m_series->append(QPointF(points.p_cpu));
////    m_series->points().clear();
////    m_series->clear();

////    qDebug()<<"dsadsafdsjfkdhsfjkdshfjdsfds";
//    m_series->append(QPointF(point));
//    axisX->setMax(t);
////    update();

////    QDateTimeAxis* axisX=new QDateTimeAxis;
////    axisX->setFormat("h:mm:s");
////    axisX->setRange(data->m_firstTimte,data->CurrentMyTimeToDateTime());

//}

void currentData::refresshSeries(chartData *data, QString text)
{
    if(text=="cpu")
    {
        m_series->append(QList<QPointF>(*(data->point_list_cpu)));
    }
    else if(text=="dis")
    {
        m_series->append(QList<QPointF>(*(data->point_list_dis)));
    }
    else if(text=="mem")
    {
        m_series->append(QList<QPointF>(*(data->point_list_mem)));
    }
    else if(text=="gpu")
    {
        m_series->append(QList<QPointF>(*(data->point_list_gpu)));
    }
    else if(text=="net")
    {
        m_series->append(QList<QPointF>(*(data->point_list_net)));
    }
}

void currentData::appendPoint(QPointF p, QDateTime t)
{
    m_series->append(QPointF(p));
    axisX->setMax(t);
}

