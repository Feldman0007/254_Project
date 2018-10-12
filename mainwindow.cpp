#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>

MainWindow::MainWindow(listcontroller *controller, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    control(controller)
{
    Q_ASSERT(controller != nullptr);
    ui->setupUi(this);

    setConnection();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createEntry()
{
    auto entry = control->createEntry();
    if(entry) {
        ui->listWidget->addItem((entry->getName()));
        auto listItem = ui->listWidget->item(ui->listWidget->count()-1);
        map.insert(listItem, entry);

    }
}

void MainWindow::deleteEntry()
{
    auto listItem = ui->listWidget->currentItem();
    if(listItem) {
        auto entry = map.value(listItem);

        if(entry) {
            if(control->deleteEntry(entry)) { //if delete worked, delete from ui
                map.remove(listItem);

                delete listItem;
            }
        }
    }
}

void MainWindow::editEntry()
{
    auto listItem = ui->listWidget->currentItem();
    if(listItem) {
        auto entry = map.value(listItem);

        if(entry) {
            ui->stackedWidget->setCurrentWidget(ui->detailpage); //go to editing page
            ui->menuToDoList->setEnabled(false); //disable drop menu (buttons provided in editing page)
            ui->nameEdit->setText(entry->getName());
            ui->dateEdit->setDate(entry->getDue());
            ui->percentEdit->setValue(entry->getPercent());
            ui->diffEdit->setValue(entry->getDiff());


        }
    }
}

void MainWindow::prioritizeDue()
{
    QList<TaskEntry*> _list = helpPrioritize();

    for(int i = 0; i < _list.size(); i++) {
        for(int j = 0; j < _list.size()-i-1; i++) { //the date coming up first is first
            if(_list.at(j)->getDue() < _list.at(j+1)->getDue()) {
                _list.swap(j, j+1);
            }
        }
    }

    //helpPrint(_list);
}


void MainWindow::saveEntry()
{
    auto listItem = ui->listWidget->currentItem();
        if(listItem) {
            auto entry = map.value(listItem);

            if(entry) {
                //store the entry into the tasklist
                entry->setName(ui->nameEdit->text());
                entry->setDue(ui->dateEdit->date());
                entry->setPercent(ui->percentEdit->value());
                entry->setDiff(ui->diffEdit->value());
                //update the ui entry
                listItem->setText(entry->getName());
                closeEntry(); //return to listing + enable drop menu
            }
        }
}

void MainWindow::closeEntry() //don't do anything and return to list
{
    ui->stackedWidget->setCurrentWidget(ui->listPage);
    ui->menuToDoList->setEnabled(true);
}



void MainWindow::setConnection() //connects the ui action to the appropriate mainwindow funcions
{
    connect(ui->actionAdd, SIGNAL(triggered(bool)), this, SLOT(createEntry()));
    connect(ui->actionComplete_Remove, &QAction::triggered, this, &MainWindow::deleteEntry);
    connect(ui->actionEdit, &QAction::triggered,this, &MainWindow::editEntry);
    connect(ui->actionDue_Date, &QAction::triggered, this, &MainWindow::prioritizeDue);

    //button connections
    connect(ui->buttonBox->button(QDialogButtonBox::Close), &QPushButton::clicked, this, &MainWindow::closeEntry);
    connect(ui->buttonBox->button(QDialogButtonBox::Save), &QPushButton::clicked, this, &MainWindow::saveEntry);
}

QList<TaskEntry*> MainWindow::helpPrioritize()
{
    QList<TaskEntry*> _list;
    QMap<QListWidgetItem*, TaskEntry*>::iterator i = map.begin();
    while(i != map.end()){
        ++i;
        _list.append(i.value());
    }
    return _list;
}

void MainWindow::helpPrint(QList<TaskEntry*> to_print)
{
    ui->stackedWidget->setCurrentWidget(ui->sortedpage);
    for(int i = 0; i < to_print.size(); i++) {
        ui->sortedWidget->addItem(to_print[i]->getName());
    }
}

