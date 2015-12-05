#include "mainwindow.h"
#include <ui_mainwindow.h>


MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow) {
  ui->setupUi(this);
  ui->mygl->setFocus();

  //for HW 3, Making current Item to null
  currentItem=nullptr;
  nodeName = ""; //undefined name to none


}

MainWindow::~MainWindow() {
  delete ui;
}

void MainWindow::on_actionQuit_triggered() {
  QApplication::exit();
}


//for HW 3

//item from QTreeWidget
void MainWindow::slot_recieveClicked(QTreeWidgetItem *item){
    //adding as current active tree item
    currentItem = (sceneNode*)item;

    //displaying all respective transformations on screen
    emit sig_tX(currentItem->translate[0]);
    emit sig_tY(currentItem->translate[1]);
    emit sig_tZ(currentItem->translate[2]);

    emit sig_rX(currentItem->rotation[0]);
    emit sig_rY(currentItem->rotation[1]);
    emit sig_rZ(currentItem->rotation[2]);

    emit sig_sX(currentItem->scale[0]);
    emit sig_sY(currentItem->scale[1]);
    emit sig_sZ(currentItem->scale[2]);

    emit sig_cR((int)currentItem->color[0]*100);
    emit sig_cG((int)currentItem->color[1]*100);
    emit sig_cB((int)currentItem->color[2]*100);
}

//item from respective spin box
void MainWindow::slot_tX(double value) {
    if(currentItem!=nullptr)
       currentItem->translate[0] = value;
}
void MainWindow::slot_tY(double value){
    if(currentItem!=nullptr)
        currentItem->translate[1] = value;
}
void MainWindow::slot_tZ(double value){
    if(currentItem!=nullptr)
        currentItem->translate[2] = value;
}


void MainWindow::slot_rX(double value){
    if(currentItem!=nullptr)
        currentItem->rotation[0] = value;
}

void MainWindow::slot_rY(double value){
    if(currentItem!=nullptr)
        currentItem->rotation[1] = value;
}

void MainWindow::slot_rZ(double value){
    if(currentItem!=nullptr)
        currentItem->rotation[2] = value;
}


void MainWindow::slot_sX(double value){
    if(currentItem!=nullptr)
        currentItem->scale[0] = value;
}
void MainWindow::slot_sY(double value){
    if(currentItem!=nullptr)
        currentItem->scale[1] = value;
}
void MainWindow::slot_sZ(double value){
    if(currentItem!=nullptr)
        currentItem->scale[2] = value;
}

void MainWindow::slot_cR(int value){
    if(currentItem!=nullptr)
        currentItem->color[0] = value/100.0;
}
void MainWindow::slot_cG(int value){
    if(currentItem!=nullptr)
        currentItem->color[1] = value/100.0;
}
void MainWindow::slot_cB(int value){
    if(currentItem!=nullptr)
        currentItem->color[2] = value/100.0;
}

//HW3 //Slots for creating new, delete and rename
void MainWindow::slot_storeNode(int t){
    geometry = (sceneNode::geomType)t;
}

void MainWindow::slot_storeName(QString name){
    nodeName=name;
}

void MainWindow::slot_storeRename(QString name){
    rename = name;
}

void MainWindow::slot_buttonNew(){
    emit sig_addChild(currentItem,geometry,nodeName); //signal to mygl
    slot_recieveClicked(currentItem->childNode[(currentItem->childNode.size())-1]);
}

void MainWindow::slot_buttonRename(){
    currentItem->setText(0,rename);
}

void MainWindow::slot_buttonDelete(){
    //** removing currentItem from it's parent vector list **//
    //first removing current node from it's parent vector list
    if(currentItem!=nullptr){
        sceneNode *parent = currentItem->getParent();
        std::vector<sceneNode*>::iterator index; //iterator of vector, use for find index and delete it's element
        for(index = ((parent->childNode).begin()); index!=((parent->childNode).end());index++)
            if(*index == currentItem) //if current iterator item equals currentItem //check memory location
                break;
        (parent->childNode).erase(index); // delete currentItem from parent's child vector

        //emmiting signal to mygl if this or it's children points to any geometry
        emit sig_removeGeomNodes(currentItem);

        delete currentItem;
        currentItem=nullptr;
    }
}
