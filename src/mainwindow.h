#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include<QTreeWidgetItem>
#include"sceneNode.h"

namespace Ui {
  class MainWindow;
}


class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

  private slots:
    void on_actionQuit_triggered();

 private:
    Ui::MainWindow *ui;


private :  //for HW 3
    sceneNode *currentItem;
    QString nodeName;
    QString rename;
    sceneNode::geomType geometry;

public slots: // For HW 3 // Slots for transformations
    //item from QTreeWidget
    void slot_recieveClicked(QTreeWidgetItem *item);
    //item from respective spin box
    void slot_tX(double value);
    void slot_tY(double value);
    void slot_tZ(double value);

    void slot_rX(double value);
    void slot_rY(double value);
    void slot_rZ(double value);

    void slot_sX(double value);
    void slot_sY(double value);
    void slot_sZ(double value);

    void slot_cR(int value);
    void slot_cG(int value);
    void slot_cB(int value);

signals:
    void sig_tX(double value);
    void sig_tY(double value);
    void sig_tZ(double value);

    void sig_rX(double value);
    void sig_rY(double value);
    void sig_rZ(double value);

    void sig_sX(double value);
    void sig_sY(double value);
    void sig_sZ(double value);

    //Adding color controls //during HW4
    void sig_cR(int value);
    void sig_cG(int value);
    void sig_cB(int value);

public slots:  //HW3 //Slots for creating new, delete and rename
    void slot_storeNode(int t);
    void slot_storeName(QString name);
    void slot_storeRename(QString name);

    void slot_buttonNew();
    void slot_buttonRename();
    void slot_buttonDelete();

signals:
    //signal to mygl, which helps to add new node along with geometry to newly created node
    void sig_addChild(sceneNode*,sceneNode::geomType, QString);
    //sinal to mygl, which remove current deleted item from list of nodes contaion geometry
    //in mainGraph data structure
    void sig_removeGeomNodes(sceneNode *);

};


#endif // MAINWINDOW_H
