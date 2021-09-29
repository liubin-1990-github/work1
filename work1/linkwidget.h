#ifndef LINKWIDGET_H
#define LINKWIDGET_H

#include <QWidget>
#include "chartcurrentdata.h"
class chartData;

enum links
{
    NOLINK,
    C,
    G,
    M,
    D,
    N,
    CG,
    CM,
    CD,
};

class LinkWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LinkWidget(QWidget *parent = nullptr);

signals:
    void linkWidgetClose();
protected:
    void closeEvent(QCloseEvent*);
public:
    void wantGetData(int ret);
    void wantAppendP();



public:
    chartCurrentData m_chartCurrent;
    links link;

    bool firstRefresh=true;

public slots:
};

#endif // LINKWIDGET_H
