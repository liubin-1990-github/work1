#include "widget.h"
#include "ui_widget.h"

#include <QMenuBar>
#include <QMenu>
#include <QDebug>



QStandardItemModel OverAllVar::m_model;
QVector<QString> OverAllVar::m_ip_vector;
QList<chartData*>OverAllVar::m_chartData_List;
NewPoints OverAllVar::m_PointS;

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    p_p=new presenter(this);
    layout=new QGridLayout(this);
    this->setLayout(layout);
    m_dataTreeView.setModel(&(OverAllVar::m_model));
    initMenuBar();
    intiUIConnect();



    thread_sever *thread_sev = new thread_sever(this);
    thread_sev->start();

    connect(thread_sev,&thread_sever::sendData,this,&Widget::getDataFromSer);
    connect(this,&Widget::destroyed,thread_sev,[=](){
        thread_sev->wait();
        thread_sev->quit();
        thread_sev->deleteLater();
    });

    connect(p_p,&presenter::oldIpRefresh__,[=](int ret,QString ip){
        qDebug()<<"ret ==============="<<ret;
        if(ip!=m_ip) {
            qDebug()<<"ip not equal";
            return;}
        if(m_ip==NULL) {
            qDebug()<<"ip == null";
            return;}
        if(m_link.link==NOLINK) {
            qDebug()<<"no link";
            return;}
//        chartData *data=OverAllVar::m_chartData_List.at(ret);
//        qDebug()<<data->m_firstTimte;

        if(!m_link.firstRefresh) return;

        m_link.wantGetData(ret);
    });

    connect(p_p,&presenter::newPsChanged_,[=](int ret,QString ip){
        if(ip!=m_ip) {
            qDebug()<<"ip not equal";
            return;}
        if(m_ip==NULL) {
            qDebug()<<"ip == null";
            return;}
        if(m_link.link==NOLINK) {
            qDebug()<<"no link";
            return;}


        if(m_link.firstRefresh) return;

        m_link.wantAppendP();
    });
}

Widget::~Widget()
{
    delete ui;
//    delete m_model;
    delete p_p;

}

void Widget::getDataFromSer(Data data)
{
    qDebug()<<"main ui get data"<<data.m_cpu;
    if(data.m_ip=="") return;
    p_p->dealData(data);


}


void Widget::initMenuBar()
{
    QMenuBar *mBar=new QMenuBar(this);
    QMenu *oper=mBar->addMenu("op");
    QMenu *alarmVi=mBar->addMenu("alarm");
    QAction *current_data=oper->addAction("current data");
    QAction *alarmViewShow=alarmVi->addAction("view alarm");

//    connect(alarmViewShow,&QAction::triggered,this,&Widget::showAlarm);
    connect(current_data,&QAction::triggered,this,&Widget::showCurrentData);
//    connect(&m_treeWidget,&current_data_tree_view::tree_Widget_close,this,&MainWindow::show);
//    connect(&m_alarm_view,&alarmView::alarmViewClose,this,&MainWindow::show);
    //    connect(this,SIGNAL(buttonClicked(QString)),this,SLOT(dealButtonClicked(QString)));
}

void Widget::intiUIConnect()
{
    connect(&m_dataTreeView,&Current_data_tree_view::currentDataTreeViewClose,this,&Widget::show);
    connect(this,&Widget::buttonClicked,this,[&](){
        this->hide();
        m_link.show();
    });
    connect(&m_link,&LinkWidget::linkWidgetClose,this,[&](){
        this->m_ip="";
        this->show();
    });
    connect(p_p,&presenter::newIp,this,[=](QString ip){
        MyButton *btn=new MyButton(this);
        btn->setText(ip);
        connect(btn,&MyButton::clicked,this,&Widget::getText);
        m_btn_list.append(btn);
        layout->addWidget(btn,m_btn_list.size()/4 ,m_btn_list.size()%4-1);

    });
}
void Widget::getText()
{
    MyButton *btn=qobject_cast<MyButton*>(sender());
    m_ip=btn->text();
    emit buttonClicked(btn->text());
}
void Widget::showCurrentData()
{
    this->hide();
    m_dataTreeView.show();
}
