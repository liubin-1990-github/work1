#include "chartdata.h"
#include <QDebug>
chartData::chartData()
{
    axisX=new QDateTimeAxis;
    point_list_cpu=new QList<QPointF>;
    point_list_gpu=new QList<QPointF>;
    point_list_dis=new QList<QPointF>;
    point_list_mem=new QList<QPointF>;
    point_list_net=new QList<QPointF>;

}

//chartData::chartData( Data data)
//{
//    ip=data->m_ip;
//    MyTime t;
//    t.inti(data->m_time);
//    QDateTime _time;
//    _time.setDate(QDate(t.year,t.month,t.day));
//    _time.setTime(QTime(t.hour,t.minute,t.second));
//    m_firstTimte=_time;
//    axisX=new QDateTimeAxis;
//    axisX->setFormat("h:mm:ss");
//    axisX->setRange(_time,_time);

//}

chartData::~chartData()
{
    point_list_cpu->clear();
    point_list_gpu->clear();
    point_list_dis->clear();
    point_list_mem->clear();
    point_list_net->clear();
    axisX->deleteLater();
}

void chartData::getFirstData( Data data)
{
    ip=data.m_ip;
    pointSize++;
    MyTime t;
    t.inti(data.m_time);
    m_firstMyTime=t;
    m_currentTime=t;
    MyTime t1=t;
    t1.addSec();
    QDateTime _time;
    _time.setDate(QDate(t.year,t.month,t.day));
    _time.setTime(QTime(t.hour,t.minute,t.second));
    qDebug()<<"first time"<<_time;
    QDateTime _time1;
    _time1.setDate(QDate(t1.year,t1.month,t1.day));
    _time1.setTime(QTime(t1.hour,t1.minute,t1.second));
    qDebug()<<"first time  +1"<<_time1;
    m_firstTimte=_time;
//    axisX=new QDateTimeAxis;
//    axisX->setFormat("h:mm:ss");
    axisX->setRange(_time,_time1);
//    qDebug()<<"current time!!!!!"<<_time;

    point_list_cpu->append(QPointF(_time.toMSecsSinceEpoch(),data.m_cpu));

    point_list_gpu->append(QPointF(_time.toMSecsSinceEpoch(),data.m_gpu));
    point_list_dis->append(QPointF(_time.toMSecsSinceEpoch(),data.m_dis));
    point_list_mem->append(QPointF(_time.toMSecsSinceEpoch(),data.m_mem));
    point_list_net->append(QPointF(_time.toMSecsSinceEpoch(),data.m_netS));
    //huoqu first time

//    class chartData{
//        chartData(Data data);
//        QDateTimeAxis *axisX;
//        QList<QPointF*>* point_list_cpu;
//        QList<QPointF*>* point_list_gpu;
//        QList<QPointF*>* point_list_mem;
//        QList<QPointF*>* point_list_dis;
//        QString ip="";

//    };
//    class Data
//    {
//    public:
//        Data();
//        Data(int fd,QString ip,int cpu,int gpu,int dis,int mem,QString time);

//    //    int fd,QString ip,int cpu,int gpu,int dis,int mem,QString time
//        int m_fd;
//        QString m_ip;
//        int m_cpu;
//        int m_gpu;
//        int m_dis;
//        int m_mem;
//        QString m_time;
    //    };
}

QDateTime chartData::MyTimeToQDateTime()
{
    QDateTime _time;
    _time.setDate(QDate(m_firstMyTime.year,m_firstMyTime.month,m_firstMyTime.day));
    _time.setTime(QTime(m_firstMyTime.hour,m_firstMyTime.minute,m_firstMyTime.second));
    return _time;
}

QDateTime chartData::CurrentMyTimeToDateTime()
{
    QDateTime _time;
    _time.setDate(QDate(m_currentTime.year,m_currentTime.month,m_currentTime.day));
    _time.setTime(QTime(m_currentTime.hour,m_currentTime.minute,m_currentTime.second));
    return _time;
}

bool chartData::currentTimeAddSecIsDatasTime(MyTime t)
{
    MyTime t1=m_currentTime;
    t1.addSec();
    return t1==t;
}

QString chartData::myTimeToQString()
{
    qlonglong num=m_currentTime.year*10000000000+m_currentTime.month*100000000+m_currentTime.day*1000000
            +m_currentTime.hour*10000+m_currentTime.minute*100+m_currentTime.second;
    return QString::number(num);
}
