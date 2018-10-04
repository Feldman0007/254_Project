#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(listcontroller *controller, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    control(controller)

{
    Q_ASSERT(controller != nullptr);
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createEntry()
{
    //auto entry = tasklist->createEntry();
}
