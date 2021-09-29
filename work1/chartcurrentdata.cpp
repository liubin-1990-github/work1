#include "chartcurrentdata.h"

chartCurrentData::chartCurrentData(QWidget *parent) : QWidget(parent)
{
    resize(800,500);
    m_current_cpu=new currentData("cpu");
    m_current_gpu=new currentData("gpu");
    m_current_dis=new currentData("dis");
    m_current_mem=new currentData("mem");
    m_current_net=new currentData("net");
//    m_current_cpu->hide();
//    m_current_gpu->hide();
//    m_current_dis->hide();
//    m_current_mem->hide();
    layout=new QGridLayout;
    this->setLayout(layout);
}

void chartCurrentData::removeAllWidget()
{
    layout->removeWidget(m_current_cpu);
    layout->removeWidget(m_current_gpu);
    layout->removeWidget(m_current_dis);
    layout->removeWidget(m_current_mem);
    layout->removeWidget(m_current_net);

    m_current_cpu->setVisible(false);
    m_current_gpu->setVisible(false);
    m_current_dis->setVisible(false);
    m_current_mem->setVisible(false);
    m_current_net->setVisible(false);
}

void chartCurrentData::link_cpu()
{  
    removeAllWidget();
    layout->addWidget(m_current_cpu,0,0,2,2);
    m_current_cpu->setVisible(true);
}

void chartCurrentData::link_gpu()
{    
    removeAllWidget();
    layout->addWidget(m_current_gpu,0,0,2,2);
    m_current_gpu->setVisible(true);
}

void chartCurrentData::link_CG()
{
    removeAllWidget();
    layout->addWidget(m_current_gpu,0,0,2,2);
    layout->addWidget(m_current_cpu,2,0,2,2);
    m_current_cpu->setVisible(true);
    m_current_gpu->setVisible(true);
}

void chartCurrentData::link_N()
{
    removeAllWidget();
    layout->addWidget(m_current_net,0,0,2,2);

    m_current_net->setVisible(true);

}

void chartCurrentData::closeEvent(QCloseEvent *)
{
    m_current_cpu->clearChart();
    m_current_gpu->clearChart();
    m_current_dis->clearChart();
    m_current_mem->clearChart();
    m_current_net->clearChart();
    emit chartDataClosed();
}
