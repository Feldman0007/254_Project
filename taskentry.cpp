#include "taskentry.h"

TaskEntry::TaskEntry(QObject *parent) : QObject(parent)
{

}

QString TaskEntry::getName() const
{
    return name;
}

void TaskEntry::setName(const QString &value)
{
    if (name != value) { emit nameChanged(); }
    name = value;
}

QDate TaskEntry::getDue() const
{
    return due;
}

void TaskEntry::setDue(const QDate &value)
{
    due = value;
}

int TaskEntry::getPercent() const
{
    return percent;
}

void TaskEntry::setPercent(int value)
{
    percent = value;
}

int TaskEntry::getDiff() const
{
    return diff;
}

void TaskEntry::setDiff(int value)
{
    diff = value;
}
