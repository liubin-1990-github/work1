#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "thread_sever.h"
#include "currentdatatreeview.h"
#include <QStandardItemModel>
#include <QDateTime>
#include "presenter.h"
#include <QGridLayout>
#include "linkwidget.h"
#include "chartdata.h"
#include <QList>
#include <QMap>

class NewPoints
{
public:
    QPointF p_cpu;
    QPointF p_gpu;
    QPointF p_dis;
    QPointF p_mem;
    QPointF p_net;
    QString ip;
    QDateTime m_DateTime;
};
class OverAllVar
{
public:
    static QStandardItemModel m_model;
    static NewPoints m_PointS;
    static QVector<QString>m_ip_vector;
    static QList<chartData*>m_chartData_List;
};

class presenter;

//extern QStandardItemModel* m_model;

//extern QVector<QString>m_ip_vector;


namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
public:
    void getDataFromSer(Data data);


    void initMenuBar();
    void intiUIConnect();

    void showCurrentData();
    void getText();

private:
    Ui::Widget *ui;
public:
    Current_data_tree_view m_dataTreeView;
    QVector<MyButton*> m_btn_list;
    presenter *p_p;
    QGridLayout *layout;
    QString m_ip;
    LinkWidget m_link;

signals:
    void buttonClicked(QString);

};

#endif // WIDGET_H
