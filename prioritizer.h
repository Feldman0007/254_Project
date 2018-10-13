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

private:
    Ui::Prioritizer *ui;
    list<Task> taskList;
    list<Task>::iterator cursor;
};

#endif // PRIORITIZER_H
