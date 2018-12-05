/*
*   Prioritizer header.
*   Declare functions for program + define private variables
*/

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
    Ui::Prioritizer *ui;            // initialize GUI
    list<Task> taskList;            // the list of all tasks entered by the user
    list<Task>::iterator cursor;    // iterates/moves through the list taskList
    bool save_the_file = false;     // flag action variables (saving, loading, and creating new files, etc.)
    QString currentFileName = "";   // the current working file
};

#endif // PRIORITIZER_H
