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

void TaskList::prioritizeDate() {
    for(int i = 0; i < _list.size(); i++) {
        for(int j = 0; j < _list.size()-i-1; i++) {
            if(_list.at(j)->getDue() > _list.at(j+1)->getDue()) {
                _list.swap(j, j+1);
            }
        }
    }
}

