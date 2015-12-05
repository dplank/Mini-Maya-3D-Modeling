#include "myTreeWidget.h"

myTreeWidget::myTreeWidget(QWidget *parent) :
    QTreeWidget(parent)
{

}

void myTreeWidget::slot_getTopItem(QTreeWidgetItem *item) {
    QTreeWidget::addTopLevelItem(item);
}

void myTreeWidget::slot_getSelectedItem(QTreeWidgetItem *item){
    QTreeWidget::setCurrentItem(item);
    if(item!=nullptr)
        emit itemClicked(item,0);
}


myTreeWidget::~myTreeWidget()
{

}
