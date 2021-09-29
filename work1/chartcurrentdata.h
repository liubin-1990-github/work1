#ifndef CHARTCURRENTDATA_H
#define CHARTCURRENTDATA_H

#include <QWidget>
#include "smallchart.h"
#include <QGridLayout>

class chartCurrentData : public QWidget
{
    Q_OBJECT
public:
    explicit chartCurrentData(QWidget *parent = nullptr);

    void removeAllWidget();

    void link_cpu();
    void link_gpu();
    void link_CG();
    void link_N();
public:
    currentData* m_current_net;
    currentData* m_current_cpu;
    currentData* m_current_gpu;
    currentData* m_current_mem;
    currentData* m_current_dis;
    QGridLayout* layout;

    int fisrtGetData = 0;

signals:
    void chartDataClosed();

protected:
    void closeEvent(QCloseEvent *);

public slots:
};

#endif // CHARTCURRENTDATA_H
