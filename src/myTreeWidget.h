#ifndef MYTREEWIDGET_H
#define MYTREEWIDGET_H

#include<QTreeWidget>

class myTreeWidget : public QTreeWidget
{
    Q_OBJECT

public:
    myTreeWidget(QWidget *parent=0);
    ~myTreeWidget();

public slots:
    void slot_getTopItem(QTreeWidgetItem *item);
    //get item by ray-cast and make it as current HW4
    void slot_getSelectedItem(QTreeWidgetItem *item);

};

#endif // MYTREEWIDGET_H
