#include "mainwindow.h"
#include "tasklist.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    TaskList tasklist;
    listcontroller controller(&tasklist);

    MainWindow w(&controller);
    w.show();

    return a.exec();
}
