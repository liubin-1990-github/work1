#include "currentdatatreeview.h"

Current_data_tree_view::Current_data_tree_view(QWidget *parent) : QTreeView(parent)
{
    resize(800,600);
}

void Current_data_tree_view::closeEvent(QCloseEvent *)
{
    emit currentDataTreeViewClose();
}
