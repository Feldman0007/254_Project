#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "listcontroller.h"

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(listcontroller *control, QWidget *parent = nullptr);
    ~MainWindow();

public slots: //callback

    void createEntry();

private:
    Ui::MainWindow *ui;
    listcontroller *control;
};

#endif // MAINWINDOW_H
