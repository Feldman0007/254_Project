#ifndef TASKLIST_H
#define TASKLIST_H
#include "taskentry.h"

#include <QObject>
#include <QList>

//The list of tasks
class TaskList : public QObject
{
    Q_OBJECT
public:
    //Alias for QT list class of task pointers
    typedef QList<TaskEntry*> ToDoList;

    explicit TaskList(QObject *parent = nullptr);
    ToDoList getTDL() const;

    TaskEntry* createTask();
    bool deleteTask(TaskEntry *task);

    void prioritizeDate();
signals:
    //Alerts when tasks are added or removed
    void entryAdded(TaskEntry *task);
    void entryRemoved(TaskEntry *task);

public slots:

private:
    ToDoList _list;
};

#endif // TASKLIST_H
