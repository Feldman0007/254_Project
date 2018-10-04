#include "listcontroller.h"

listcontroller::listcontroller(
        TaskList *tasklist, QObject *parent) :
    QObject(parent),
    controller(tasklist)
{
    Q_ASSERT(tasklist != nullptr);
}

TaskEntry *listcontroller::createEntry()
{
    auto result = controller->createTask();
    if(result != nullptr) {
        result->setName(tr("New entry..."));
    }
    return result;
}

bool listcontroller::deleteEntry(TaskEntry *entry)
{
    return controller->deleteTask(entry);
}