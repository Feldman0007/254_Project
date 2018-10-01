#ifndef PRIORITIZER_H
#define PRIORITIZER_H
#include "taskList.h"
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

    TaskList mainList;
    void updateListDisplay(TaskList);

private slots:
    void on_AddTask_clicked();

    void on_RemoveTask_clicked();

private:
    Ui::Prioritizer *ui;
};

#endif // PRIORITIZER_H
