#include "prioritizer.h"
#include "ui_prioritizer.h"
#include "taskList.hpp"
#include <QtCore>
#include <QtGui>
#include <QInputDialog>



Prioritizer::Prioritizer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Prioritizer)
{
    ui->setupUi(this);
}

Prioritizer::~Prioritizer()
{
    delete ui;
}

void Prioritizer::on_AddTask_clicked()
{

/*///////////////////////////////////////////////////Get Task Information//////////////////////////////////////////////////////////////////////////////////////////////////*/

   QString taskName = QInputDialog::getText(this, "Assignment name", "Enter the name of the assignment:");         //Get the name for the new assignment

   int month =  QInputDialog::getInt(this, "Due Date", "Enter the month it's due (MM):");                      //Get the month of the assignment's due date
   while (month > 12 || month < 1){
       month =  QInputDialog::getInt(this, "Due Date", "Invalid entry. Retry inputing the month it's due (MM):");     //Input validation
   }
   int day =  QInputDialog::getInt(this, "Due Date", "Enter the day it's due (DD):");               //Get the day of the assignment's due date
   while (day < 1 || day > 31){
       day =  QInputDialog::getInt(this, "Due Date", "Invalid day. Retry inputing the day it's due (DD):");     //Input validation
   }
   if (month == 4 || month == 6 || month == 9 || month == 11){                                                      //Input validation for months with only 30 days
    while (day > 30 || day < 1){
        day =  QInputDialog::getInt(this, "Due Date", "There are only 30 days in this month. Retry inputing the day it's due (DD):");
     }
   }
   else if (month == 2){                   //Input validation for February
     while (day > 28 || day < 1){
       day =  QInputDialog::getInt(this, "Due Date", "There are only 28 days in February. Retry inputing the day it's due (DD):");
    }
 }


   int importance = QInputDialog::getInt(this, "Importance", "Enter the importance of the assignment on a scale of 1-10:");    //Get the level of importance of the assignment
   while (importance < 1 || importance > 10){              //Input validation for assignment impact on grade
       importance = QInputDialog::getInt(this, "Importance", "Invalid entry, pick a number between 1-10:");         //Input validation
   }

   int effort = QInputDialog::getInt(this, "Effort", "Enter the level of difficulty of the assignment on a scale of 1-10:"); //Get the level of effort require to complete the assignment
   while (effort < 1 || effort > 10){              //Input validation for assignment effort level required
       effort = QInputDialog::getInt(this, "Effort", "Invalid entry, pick a number between 1-10:");
   }


   /*///////////////////////////////////////////////////Add the Assignment to List and update display/////////////////////////////////////////////////////////////////////////////////////*/

   string stdString = taskName.toStdString();  //convert taskName from a QString to a string so we can work with it in our list

   Task add(stdString, month, day, importance, effort); //Create a new entry in the list

   mainList.addTask(add);
   updateListDisplay(taskList);   //Update display on the gui
}

/*////////////////////////////////////////////Remove task then update the display//////////////////////////////////////////////////////////////////////////////////////////////*/
void Prioritizer::on_RemoveTask_clicked()
{
   if (mainList.size() == 0){/*If there are no tasks to remove, do nothing*/}
   else{
    int choice =  QInputDialog::getInt(this, "Remove Task", "Enter the number of the task you'd like to remove: "); //If choice greater than list size
        while (choice > mainList.size() || choice < 1){
            choice =  QInputDialog::getInt(this, "Remove Task", "Not a valid task number, try again.");
        }  
        for (int i = 1; i < choice; i++){
            mainList.removeFront();
        }

        updateListDisplay(mainList);
   }
}
 /*///////////////////////////////////////////////////Update the list display //////////////////////////////////////////////////////////////////////////////////////////////////*/
void Prioritizer::updateListDisplay(TaskList myList){

    string data; //Will temporarily hold task info as we convert it to a QString so the gui can use it
    QString q_updateText; //Used to update the gui display

    Task* cursor = myList.front();
    while (cursor->next != myList.back()){            //Run through the entire list and echo the details of each task to the display

      data = cursor->taskName;                  //Store task data
      q_updateText = QString::fromStdString(data); //convert string to QString so our gui can work with it
      ui->listOutput->appendPlainText(q_updateText); //Add it to the gui display
      q_updateText = "/t";
      ui->listOutput->appendPlainText(q_updateText);

      data = std::to_string(cursor->dueMonth);       //convert the integer representing the due dates to a string
      data.append("/");                                 //format to MM/DD
      data.append(std::to_string(cursor->dueDay));
      q_updateText = QString::fromStdString(data);   //convert that string to QString so our gui can work with it
      ui->listOutput->appendPlainText(q_updateText);
      q_updateText = "/t";
      ui->listOutput->appendPlainText(q_updateText);

      data = std::to_string(cursor->impact);            //convert the integer representing the importance  to a string
      q_updateText = QString::fromStdString(data);         //Convert that string to a QString so our gui can work with it
      ui->listOutput->appendPlainText(q_updateText);
      q_updateText = "/t";
      ui->listOutput->appendPlainText(q_updateText);

      data = std::to_string(cursor->effort);                //convert the integer representing the effort  to a string
      q_updateText = QString::fromStdString(data);          //Convert that string to a QString so our gui can work with it
      ui->listOutput->appendPlainText(q_updateText);
      q_updateText = "/n";
      ui->listOutput->appendPlainText(q_updateText);

      cursor = cursor->next;                                   //Move the cursor to the next task in the list
        }
}
