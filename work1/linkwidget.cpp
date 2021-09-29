#include "linkwidget.h"
#include <QPushButton>
#include <QGridLayout>
#include <QDebug>
#include "widget.h"

LinkWidget::LinkWidget(QWidget *parent) : QWidget(parent)
{
    resize(800,600);
    link=NOLINK;
    QGridLayout *layout=new QGridLayout(this);
    this->setLayout(layout);
    connect(&m_chartCurrent,&chartCurrentData::chartDataClosed,this,[&](){
       link=NOLINK;
       this->firstRefresh = true;
       this->show();
    });
//![1]
    QPushButton *btn1= new QPushButton(this);
    btn1->setText("cpu");
    layout->addWidget(btn1,1,1);
    connect(btn1,&QPushButton::clicked,this,[&](){
        link = C;
        this->hide();
        m_chartCurrent.link_cpu();
        m_chartCurrent.show();
    });
//![1]

//![2]
    QPushButton *btn2= new QPushButton(this);
    btn2->setText("gpu");
    layout->addWidget(btn2,1,2);
    connect(btn2,&QPushButton::clicked,this,[&](){
        link = G;
        this->hide();
        m_chartCurrent.link_gpu();
        m_chartCurrent.show();
    });
//![2]
//![3]
    QPushButton *btn3= new QPushButton(this);
    btn3->setText("cpu gpu");
    layout->addWidget(btn3,1,3);
    connect(btn3,&QPushButton::clicked,this,[&](){
        link = CG;
        this->hide();
        m_chartCurrent.link_CG();
        m_chartCurrent.show();
    });


//! [4]
    QPushButton *btn4= new QPushButton(this);
    btn4->setText("net");
    layout->addWidget(btn4,2,0);
    connect(btn4,&QPushButton::clicked,this,[&](){
        link = N;
        this->hide();
        m_chartCurrent.link_N();
        m_chartCurrent.show();
    });


//! [4]

}

void LinkWidget::closeEvent(QCloseEvent *)
{
    emit linkWidgetClose();
}

void LinkWidget::wantGetData(int ret)
{
    switch (link) {
    case C:
        m_chartCurrent.m_current_cpu->refresh(ret);

        break;
    case G:
        m_chartCurrent.m_current_gpu->refresh(ret);

        break;
    case CG:
        qDebug()<<"want get cpu data";

        m_chartCurrent.m_current_cpu->refresh(ret);
        m_chartCurrent.m_current_gpu->refresh(ret);

        break;



    case N:
        m_chartCurrent.m_current_net->refresh(ret);

        break;
    default:
        break;

    }
    firstRefresh=!firstRefresh;
}

void LinkWidget::wantAppendP()
{
    switch (link) {
    case C:
        m_chartCurrent.m_current_cpu->appendPoint(OverAllVar::m_PointS.p_cpu,
                                                  OverAllVar::m_PointS.m_DateTime);
        break;
    case G:
        m_chartCurrent.m_current_gpu->appendPoint(OverAllVar::m_PointS.p_gpu,
                                                  OverAllVar::m_PointS.m_DateTime);
        break;
    case CG:
        m_chartCurrent.m_current_cpu->appendPoint(OverAllVar::m_PointS.p_cpu,
                                                  OverAllVar::m_PointS.m_DateTime);
        m_chartCurrent.m_current_gpu->appendPoint(OverAllVar::m_PointS.p_gpu,
                                                  OverAllVar::m_PointS.m_DateTime);
        break;
    case N:
        m_chartCurrent.m_current_net->appendPoint(OverAllVar::m_PointS.p_net,
                                                  OverAllVar::m_PointS.m_DateTime);
        break;
    default:
        break;
    }
}



