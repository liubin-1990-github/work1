#ifndef CURRENT_DATA_TREE_VIEW_H
#define CURRENT_DATA_TREE_VIEW_H

#include <QWidget>
#include <QTreeView>
class Current_data_tree_view : public QTreeView
{
    Q_OBJECT
public:
    explicit Current_data_tree_view(QWidget *parent = nullptr);

signals:
    void currentDataTreeViewClose();
protected:
    void closeEvent(QCloseEvent*);

public slots:
};

#endif // CURRENT_DATA_TREE_VIEW_H
