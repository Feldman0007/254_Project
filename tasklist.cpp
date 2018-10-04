#include "tasklist.h"


TaskList::TaskList(QObject *parent) : QObject(parent)
{

}

TaskList::ToDoList TaskList::getTDL() const
{
    return _list;
}

TaskEntry *TaskList::createTask()
{
    auto result = new TaskEntry(this);
    if(result != nullptr) {
        _list.append(result);
        emit entryAdded(result);
    }
    return result;
}

bool TaskList::deleteTask(TaskEntry *task)
{
    if(_list.contains(task)) {
        emit entryRemoved(task);
        _list.removeOne(task);
        delete task;
        return true;
    }
    return false;
}

