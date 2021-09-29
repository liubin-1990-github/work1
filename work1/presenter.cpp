#include "presenter.h"
#include <QStandardItemModel>
#include <QDebug>
#include "chartdata.h"
presenter::presenter(Widget *v)
{
    v_p=v;

    connect(this,&presenter::newIp,[=](QString ip,Data data){
        addNewIpChart *work=new addNewIpChart;
        work->m_ip=ip;
        work->m_data=data;
        QThreadPool::globalInstance()->start(work);
    });

    connect(this,&presenter::oldIP,[=](int ret,Data data){
        WorkChartAddNew *work=new WorkChartAddNew;
        work->data=data;
        work->ret=ret;
        connect(work,&WorkChartAddNew::oldIpRefresh,[=](int ret,QString ip){
            emit oldIpRefresh__(ret,ip);
        });

        QThreadPool::globalInstance()->start(work);

        dealNewPoint(ret,data);

    });
}

presenter::~presenter()
{

}

void presenter::dealData(Data data)
{

//    dealNewPoint(data);
    dealTreeView(data);
    dealMainUIBtn(data);

}

void presenter::dealTreeView(Data data)
{
    if(v_p->m_dataTreeView.isHidden()) return;
    WorkTreeView * work = new WorkTreeView();
    work->data.init(data.m_fd,data.m_ip,data.m_cpu,data.m_gpu,data.m_dis,data.m_mem,data.m_time,data.m_netS);
    QThreadPool::globalInstance()->start(work);
}

void presenter::dealMainUIBtn(Data data)
{
     WorkUIBTN *work=new WorkUIBTN;
     work->m_ip=data.m_ip;
     connect(work,&WorkUIBTN::IfConIp,[=](int i){
         if(i>=0)
         {
             qDebug()<<"old ip";
             emit oldIP(i,data);
             return;
         }
         else
         {
             emit newIp(data.m_ip,data);
         }
     });
     QThreadPool::globalInstance()->start(work);
}

void presenter::dealNewPoint(int ret, Data data)
{
    WorkNewPs *work=new WorkNewPs;
    work->ret=ret;
    work->data.init(data.m_fd,data.m_ip,data.m_cpu,data.m_gpu,data.m_dis,data.m_mem,data.m_time,data.m_netS);

    connect(work,&WorkNewPs::newPsChanged,[=](int ret,QString ip){
        emit newPsChanged_(ret,ip);
    });

    QThreadPool::globalInstance()->start(work);
}



WorkTreeView::WorkTreeView(QObject *parent):QObject(parent),QRunnable()
{
    setAutoDelete(true);
}

WorkTreeView::~WorkTreeView()
{

}

void WorkTreeView::run()
{
    qDebug()<<"refresh tree view"<<QThread::currentThreadId();
    int ret = ifIpSaved(data.m_ip);
    QModelIndex temp_index=OverAllVar::m_model.index(ret,0);
        if(ret>=0)
        {
            temp_index= OverAllVar::m_model.index(ret,1);
            OverAllVar::m_model.setData(temp_index,QVariant::fromValue(data.m_time));
            temp_index=OverAllVar::m_model.index(ret,2);
            OverAllVar::m_model.setData(temp_index,QVariant::fromValue(data.m_cpu));
            temp_index=OverAllVar::m_model.index(ret,3);
            OverAllVar::m_model.setData(temp_index,QVariant::fromValue(data.m_gpu));
            temp_index=OverAllVar::m_model.index(ret,4);
            OverAllVar::m_model.setData(temp_index,QVariant::fromValue(data.m_dis));
            temp_index=OverAllVar::m_model.index(ret,5);
            OverAllVar::m_model.setData(temp_index,QVariant::fromValue(data.m_mem));
            temp_index=OverAllVar::m_model.index(ret,6);
            OverAllVar::m_model.setData(temp_index,QVariant::fromValue(data.m_netS));

        }
        else
        {
//            qDebug()<<"ret=-1 zhuijia";
            QStandardItem* item1=new QStandardItem(data.m_ip);
            QStandardItem* item2=new QStandardItem(data.m_time);
            QStandardItem* item3=new QStandardItem(QString::number(data.m_cpu));
            QStandardItem* item4=new QStandardItem(QString::number(data.m_gpu));
            QStandardItem* item5=new QStandardItem(QString::number(data.m_dis));
            QStandardItem* item6=new QStandardItem(QString::number(data.m_mem));
            QStandardItem* item7=new QStandardItem(QString::number(data.m_netS));
            QList<QStandardItem*>m_data_items;
            m_data_items.append(item1);
            m_data_items.append(item2);
            m_data_items.append(item3);
            m_data_items.append(item4);
            m_data_items.append(item5);
            m_data_items.append(item6);
            m_data_items.append(item7);
            OverAllVar::m_model.appendRow(m_data_items);
            m_data_items.clear();

//            qDebug()<<"ret=-1 zhuijiawanbi";
        }
}

int WorkTreeView::ifIpSaved(QString ip)
{
    for(int j=0;j<OverAllVar::m_model.rowCount();++j)
    {
        QModelIndex index=OverAllVar::m_model.index(j,0);
        QVariant data=OverAllVar::m_model.data(index);
        QString str=data.toString();
        if(ip!=str) continue;
        return j;

    }
    return -1;
}

WorkUIBTN::WorkUIBTN(QObject *parent): QObject(parent),QRunnable()
{
    setAutoDelete(true);
}

WorkUIBTN::~WorkUIBTN()
{

}

void WorkUIBTN::run()
{
    qDebug()<<"if new ip"<<QThread::currentThreadId();
    int ret =ipAt(m_ip);
    emit IfConIp(ret);
}

int  WorkUIBTN::ipAt(QString ip)
{
    for(int i=0;i<OverAllVar::m_chartData_List.size();++i)
    {
        if(ip ==OverAllVar::m_chartData_List.at(i)->ip )
        {
            return i;
        }
    }
    return -1;
}

//addNewIpChart::addNewIpChart(QObject *parent): QObject(parent),QRunnable()
//{
//    setAutoDelete(true);
//}

addNewIpChart::addNewIpChart(QObject *parent):QObject(parent),QRunnable()

{
    setAutoDelete(true);
}

addNewIpChart::~addNewIpChart()
{

}

void addNewIpChart::run()
{
    chartData *cd=new chartData;
    qDebug()<<"add  new ip chart"<<QThread::currentThreadId();
    cd->getFirstData(m_data);
    OverAllVar::m_chartData_List.append(cd);
}

WorkChartAddNew::WorkChartAddNew(QObject *parent):QObject(parent),QRunnable()
{
    setAutoDelete(true);
}

WorkChartAddNew::~WorkChartAddNew()
{

}



void WorkChartAddNew::run()
{
    qDebug()<<"chart refresh"<<QThread::currentThreadId();
    chartData *c =OverAllVar::m_chartData_List.at(ret);
    QString time1=c->myTimeToQString();
    while(1)
    {
        if(c->pointSize>PNUM)
        {
            c->point_list_cpu->removeAt(0);
            c->point_list_dis->removeAt(0);
            c->point_list_mem->removeAt(0);
            c->point_list_gpu->removeAt(0);
            c->pointSize--;
            c->m_firstMyTime.addSec();
            c->m_firstTimte=c->MyTimeToQDateTime();

            continue;
        }
        else
        {
            charDataApend(c,data);
            break;
//            while(1)
//            {
////                c->m_currentTime.addSec();

////                if(time1==data.m_time)
////                {
//                      charDataApend(c,data);
////                    qDebug()<<c->m_firstTimte;
////                    for(int i=0;i<c->point_list_cpu->size();++i)
////                    {
//////                        qDebug()<<"cpucpu++++"<<c->point_list_cpu->at(i).y();
//////                        qDebug()<<"cpucpu++++"<<c->point_list_gpu->at(i).y();

////                    }
//                    break;
//                }
////                else
////                {
////                    Data d;
////                    d.init(data.m_fd,data.m_ip,0,0,0,0,data.m_time,0);
////                    charDataApend(c,d);
////                    continue;
////                }
//            }
//            break;
        }
    }
//    delete c;
    c=nullptr;
    delete c;
    emit oldIpRefresh(ret,data.m_ip);
}

void WorkChartAddNew::charDataApend(chartData *cdata, Data data)
{
    cdata->pointSize++;
    MyTime t;

    t.inti(data.m_time);
    cdata->m_currentTime=t;
    QDateTime _time;
    _time.setDate(QDate(cdata->m_currentTime.year,cdata->m_currentTime.month,cdata->m_currentTime.day));
    _time.setTime(QTime(cdata->m_currentTime.hour,cdata->m_currentTime.minute,cdata->m_currentTime.second));
//    qDebug()<<"current time"<<_time;

//    cdata->axisX->setRange(cdata->m_firstTimte,_time);
//    qDebug()<<"first time"<<cdata->m_firstTimte;
    qDebug()<<"m_cpu!!!!!!!"<<data.m_cpu;

    QDateTime tt =QDateTime::fromMSecsSinceEpoch(
                cdata->point_list_cpu->at(0).x());


    cdata->axisX->setRange(tt,_time);
    qDebug()<<"first"<<tt;
    qDebug()<<"current"<<_time;

    cdata->point_list_cpu->append(QPointF(_time.toMSecsSinceEpoch(),data.m_cpu));
    cdata->point_list_gpu->append(QPointF(_time.toMSecsSinceEpoch(),data.m_gpu));
    cdata->point_list_dis->append(QPointF(_time.toMSecsSinceEpoch(),data.m_dis));
    cdata->point_list_mem->append(QPointF(_time.toMSecsSinceEpoch(),data.m_mem));
    cdata->point_list_net->append(QPointF(_time.toMSecsSinceEpoch(),data.m_netS));
    cdata->ip=data.m_ip;
}

WorkNewPs::WorkNewPs(QObject *parent):QObject(parent),QRunnable()
{
    setAutoDelete(true);
}

WorkNewPs::~WorkNewPs()
{

}



void WorkNewPs::run()
{
    MyTime t;
    t.inti(data.m_time);
    QDateTime _time;
    _time.setDate(QDate(t.year,t.month,t.day));
    _time.setTime(QTime(t.hour,t.minute,t.second));
     OverAllVar::m_PointS.ip=data.m_ip;
     OverAllVar::m_PointS.p_cpu=QPointF(_time.toMSecsSinceEpoch(),data.m_cpu);
     OverAllVar::m_PointS.p_gpu=QPointF(_time.toMSecsSinceEpoch(),data.m_gpu);
     OverAllVar::m_PointS.p_dis=QPointF(_time.toMSecsSinceEpoch(),data.m_dis);
     OverAllVar::m_PointS.p_mem=QPointF(_time.toMSecsSinceEpoch(),data.m_mem);
     OverAllVar::m_PointS.p_net=QPointF(_time.toMSecsSinceEpoch(),data.m_netS);
     OverAllVar::m_PointS.m_DateTime=_time;


     emit newPsChanged(ret,data.m_ip);
}
