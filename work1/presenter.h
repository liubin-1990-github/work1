#ifndef PRESENTER_H
#define PRESENTER_H

#include "widget.h"
#include "data.h"
#include "presenter.h"
#include <QThreadPool>
#include <QRunnable>
class chartData;
#define PNUM 10

//QStandardItemModel* m_model= new QStandardItemModel;

//QVector<QString>m_ip_vector;

class Widget;
class QStandardItemModel;
class OverAllVar;

class addNewIpChart :public QObject,public QRunnable
{
    Q_OBJECT
public:
    explicit addNewIpChart(QObject *parent=nullptr);
    ~addNewIpChart();
public:
    void run();
//    void getData(Data data);
//    int ifIpSaved(QString ip);


    Data m_data;
    QString m_ip;

};

class WorkNewPs :public QObject,public QRunnable
{
    Q_OBJECT
public:
    explicit WorkNewPs(QObject *parent=nullptr);
    ~WorkNewPs();
public:
    void run();
signals:
    void newPsChanged(int ,QString );

public:

    int ret;
    Data data;

};

class WorkTreeView :public QObject,public QRunnable
{
    Q_OBJECT
public:
    explicit WorkTreeView(QObject *parent=nullptr);
    ~WorkTreeView();
public:
    void run();
    void getData(Data data);
    int ifIpSaved(QString ip);


    Data data;

};
class WorkUIBTN :public QObject,public QRunnable
{
    Q_OBJECT
public:
    explicit WorkUIBTN(QObject *parent=nullptr);
    ~WorkUIBTN();
public:
    void run();
    QString m_ip;
    int ipAt(QString ip);
signals:
    void IfConIp(int );

};
class WorkChartAddNew :public QObject,public QRunnable
{
    Q_OBJECT
public:
    explicit WorkChartAddNew(QObject *parent=nullptr);
    ~WorkChartAddNew();
public:
    void run();
    void charDataApend(chartData *cdata, Data data);
    Data data;
    int ret;

signals:
    void oldIpRefresh(int ,QString);

};



class presenter :public QObject

{
    Q_OBJECT
public:
//    presenter(QObject *parent=nullptr);
    presenter(Widget *v);
    ~presenter();

public:
    Widget *v_p;

public:
    void dealData(Data data);
    void dealTreeView(Data data);
    void dealMainUIBtn(Data data);
    void judgeIfNewIp(Data data);
    void dealNewPoint(int ret, Data data);

signals:
    void newIp(QString ip,Data data);
    void oldIP(int ,Data data);
    void oldIpRefresh__(int,QString ip);
    void newPsChanged_(int ,QString );
};

#endif // PRESENTER_H
