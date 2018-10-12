#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "listcontroller.h"

#include <QMainWindow>
#include <QHash>

namespace Ui {
class MainWindow;
}

class QListWidgetItem;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(listcontroller *control, QWidget *parent = nullptr);
    ~MainWindow();

public slots: //callback

    //drop menu fuctions
    void createEntry();
    void deleteEntry();
    void editEntry();

    //priority functions
    void prioritizeDue();
    //void prioritizePer();
    //void prioritizeDiff();

    //buttons
    void saveEntry();
    void closeEntry();


private:
    Ui::MainWindow *ui;
    listcontroller *control;
    QMap<QListWidgetItem*, TaskEntry*> map;
    QList<TaskEntry*> myList;

    void setConnection();
    QList<TaskEntry*> helpPrioritize();
    void helpPrint(QList<TaskEntry*> to_print);
};

#endif // MAINWINDOW_H
