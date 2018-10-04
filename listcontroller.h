#ifndef LISTCONTROLLER_H
#define LISTCONTROLLER_H

#include "tasklist.h"
#include <QObject>

//Mediator between backend and frontend
class listcontroller : public QObject
{
    Q_OBJECT
public:
    explicit listcontroller(TaskList *tasklist, QObject *parent = nullptr);

    TaskEntry *createEntry();
    bool deleteEntry(TaskEntry *task);

signals:

public slots:

private:
    TaskList *controller;
};

#endif // LISTCONTROLLER_H
