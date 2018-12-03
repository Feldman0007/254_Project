#ifndef PRIORITIZER_H
#define PRIORITIZER_H
#include "tasklist.h"
#include <list>
#include <QMainWindow>

namespace Ui {
class Prioritizer;
}

class Prioritizer : public QMainWindow
{
    Q_OBJECT

public:
    explicit Prioritizer(QWidget *parent = nullptr);
    ~Prioritizer();

    void updateListDisplay();

    void sortList(int);

private slots:
    void on_AddTask_clicked();

    void on_RemoveTask_clicked();

    void on_SortList_clicked();

    void on_actionLoad_triggered();

    void on_actionNew_triggered();

    void on_actionSave_triggered();

private:
    Ui::Prioritizer *ui;    // initializes the gui
    list<Task> taskList;    // taskList will be a list of all tasks entered by the user so that they may be re-organized to help in prioritizing tasks
    list<Task>::iterator cursor;        // this iterator will be used to cycle through the contents of the current assignment list
    bool save_the_file = false;      //flag variables that wll be used for saving, loading, and creating new files
    QString currentFileName = "";    // this variable will keep track of the current working file
};

#endif // PRIORITIZER_H
