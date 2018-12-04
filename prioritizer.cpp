#include "prioritizer.h"
#include "ui_prioritizer.h"
#include <QtCore>
#include <QtGui>
#include <QInputDialog>
#include <QMessageBox>
#include <fstream>
#include <sstream>



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
/*///////////////////////////////////////////////////Get new assignment info////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
   bool ok; // Flag variable used to handle user hitting cancel
   int day;
   int month;
   QString taskName = QInputDialog::getText(this, "Assignment name", "Enter the name of the assignment:",QLineEdit::Normal,"",&ok);         //Get the name for the new assignment
   if (!ok){
       return;
   }
   month =  QInputDialog::getInt(this, "Due Date", "Enter the month it's due (MM):",0,1,12,1,&ok);                      //Get the month of the assignment's due date
   if(!ok){
       return;
   }
   if (month == 4 || month == 6 || month == 9 || month == 11) //Input Validation for April, June, September, and November
   {
       day =  QInputDialog::getInt(this, "Due Date", "Enter the day that it's due. (1-30):",0,1,30,1,&ok);
       if(!ok){
           return;
       }

   }
   else if (month == 2)
   {                   //Input validation for February
      day =  QInputDialog::getInt(this, "Due Date", "Enter the day that it's due. (1-28):",0,1,28,1,&ok);
      if(!ok){
           return;
       }
   }
   else
   {
       day =  QInputDialog::getInt(this, "Due Date", "Enter the day it's due (1-31):",0,1,31,1,&ok);               //Get the day of the assignment's due date
       if(!ok){
           return;
       }
   }
   int importance = QInputDialog::getInt(this, "Importance", "Enter the importance of the assignment on a scale of 1-10:",0,1,10,1,&ok);    //Get the level of importance of the assignment
   if(!ok){
       return;
   }
   int effort = QInputDialog::getInt(this, "Effort", "Enter the level of difficulty of the assignment on a scale of 1-10:",0,1,10,1,&ok); //Get the level of effort require to complete the assignment
   if(!ok){
       return;
   }
/*///////////////////////////////////////////////////Add the Assignment to List and update display//////////////////////////////////////////////////////////////////////////////////////////////////////*/

   string stdString = taskName.toStdString();  //convert taskName from a QString to a string so we can work with it in our list

   Task newTask(stdString, month, day, importance, effort); //Create a new entry in the list

   taskList.push_back(newTask);
   save_the_file = true; // We've made a change to the list so we should prompt the user to save before creating a new file
   updateListDisplay();   //Update display on the gui
}

/*////////////////////////////////////////////Remove task then update the display///////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
void Prioritizer::on_RemoveTask_clicked()
{
   bool ok;
   if (taskList.empty()){/*If there are no tasks to remove, do nothing*/}
   else
   {
        int choice =  QInputDialog::getInt(this, "Remove Task", "Enter the number of the task you'd like to remove: ",0,1,taskList.size(),1,&ok); //If choice greater than list size
        if(!ok)
        {
        return;
        }
        cursor = taskList.begin();
        for (int taskNum = 1;  taskNum != choice; taskNum++ ) //move to the task we wish to remove
        {
           cursor++;
        }
        taskList.erase(cursor); // erase that task
        save_the_file = true;   // since we have made a change we set the save file flag on
        if (taskList.empty())
        {
            save_the_file = false; //If the list is empty, we can safely start a new file without worrying about saving work
        }
        updateListDisplay(); //update the display to reflect the change
   }
}
 /*///////////////////////////////////////////////////Update the list display //////////////////////////////////////////////////////////////////////////////////////////////////*/
void Prioritizer::updateListDisplay(){
    ui->taskOutput->clear(); //Refresh the list output
    ui->dateOutput->clear();
    ui->importanceOutput->clear();
    ui->difficultyOutput->clear();
    ui->taskOutput->setAlignment(Qt::AlignLeft); //formatting
    ui->dateOutput->setAlignment(Qt::AlignCenter);
    ui->importanceOutput->setAlignment(Qt::AlignCenter);
    ui->difficultyOutput->setAlignment(Qt::AlignCenter);
    ui->taskOutput->append("Assignment");                 //  Place Headings
    ui->dateOutput->append("Due Date");
    ui->importanceOutput->append("Importance");
    ui->difficultyOutput->append("Difficulty");

    string output; //Will temporarily hold info to be converted to QString in order to display
    QString q_updateText; //Used to update the gui display

   cursor = taskList.begin();
   int taskNumber = 1; //used to output the corresponding task number
   while (cursor != taskList.end()){            //Run through the entire list and echo the details of each task to the display

      output = std::to_string(taskNumber);   //Display the task number
      output.append(". ");
      output.append(cursor->taskName);
      q_updateText = QString::fromStdString(output); //convert string to QString so our gui can work with it
      ui->taskOutput->append(q_updateText);

      output = std::to_string(cursor->dueMonth);
      output.append("/");
      output.append(std::to_string(cursor->dueDay));       //convert the integer representing the due dates to a string
      q_updateText = QString::fromStdString(output); //convert string to QString so our gui can work with it
      ui->dateOutput->append(q_updateText);

      output = std::to_string(cursor->impact);
      q_updateText = QString::fromStdString(output); //convert string to QString so our gui can work with it
      ui->importanceOutput->append(q_updateText);

      output = std::to_string(cursor->difficulty);
      q_updateText = QString::fromStdString(output); //convert string to QString so our gui can work with it
      ui->difficultyOutput->append(q_updateText); //Add it to the gui display

      cursor++;                                   //Move the cursor to the next task in the list
      taskNumber++;
   }
}
   /*///////////////////////////////////////////////////Sort list by selected priority/////////////////////////////////////////////////////////////////////////////////////*/
void Prioritizer::sortList(int choice)
{
    list<Task> tempList; //will be used to temporarily hold the reorganized the list
    list<Task>::iterator target; //this will point to the task we are targeting w/ the desired priority

    switch(choice){
    case 1: //Sort by Due Date
      while(!taskList.empty()){
        target = taskList.begin();
        for (cursor = taskList.begin(); cursor != taskList.end(); cursor++)
        {
            if(target->dueMonth == cursor->dueMonth)
            { //If they have the same due month
                if(target->dueDay > cursor->dueDay)
                { //Prioritize that which has the more recent due date
                    target = cursor; // it will currently be the target for the next item in the list
                }
            }
            else if(target->dueMonth > cursor->dueMonth){ // if the current target has a later due date than the assignment we are observing
                target = cursor; // update the target to the task we are observing
            }
        }  // The target will be the next item in the list. Adding it to the list...
        Task temp;
        temp.taskName = target->taskName;
        temp.dueMonth = target->dueMonth;
        temp.dueDay = target->dueDay;
        temp.impact = target->impact;
        temp.difficulty = target->difficulty;
        tempList.push_back(temp); // store target in temporary list
        taskList.erase(target); // we don't want to resuse that target so we remove it from the remaining pool of assignments in the original list
       }
     taskList = tempList; //assign the sorted list back to the original list
     tempList.clear(); //delete temporary list
        break;
    case 2: //Sort by impact on grade
        while(!taskList.empty()){
          target = taskList.begin();
          for (cursor = taskList.begin(); cursor != taskList.end(); cursor++){
              if(target->impact == cursor->impact){  //If their impact is equal
                  if(target->dueMonth == cursor->dueMonth){  //Check which has a more immediate due date
                      if(target->dueDay > cursor->dueDay){
                          target = cursor;
                      }
                   }
                  else if(target->dueMonth > cursor->dueMonth){
                      target = cursor;
                  }
              }
              else if(target->impact < cursor->impact){
                  target = cursor;
              }
          }
          Task temp;
          temp.taskName = target->taskName;
          temp.dueMonth = target->dueMonth;
          temp.dueDay = target->dueDay;
          temp.impact = target->impact;
          temp.difficulty = target->difficulty;
          tempList.push_back(temp);
          taskList.erase(target);
       }
       taskList = tempList;
       tempList.clear();
       break;
    case 3: //Sort by difficulty of the assignment
       while(!taskList.empty()){
         target = taskList.begin();
         for (cursor = taskList.begin(); cursor != taskList.end(); cursor++){
             if(target->difficulty == cursor->difficulty){  //If their difficulty is equal
                 if(target->dueMonth == cursor->dueMonth){  //Check which has a more immediate due date
                     if(target->dueDay > cursor->dueDay){
                         target = cursor;
                     }
                  }
                 else if(target->dueMonth > cursor->dueMonth){
                     target = cursor;
                 }
             }
             else if(target->difficulty < cursor->difficulty){
                 target = cursor;
             }
         }
         Task temp;
         temp.taskName = target->taskName;
         temp.dueMonth = target->dueMonth;
         temp.dueDay = target->dueDay;
         temp.impact = target->impact;
         temp.difficulty = target->difficulty;
         tempList.push_back(temp);
         taskList.erase(target);
      }
      taskList = tempList;
      tempList.clear();
      break;
    }
}
   /*///////////////////////////////////////////////////Sort List button handle/////////////////////////////////////////////////////////////////////////////////////*/
void Prioritizer::on_SortList_clicked()
{
    bool ok;
    if (taskList.empty())
    {
        //if list is empty do nothing
    }
    else
    {
       int choice = QInputDialog::getInt(this, "Select an attribute to prioritize by", "Enter: 1.Due Date; 2. Importance; 3. Difficulty",0,1,3,1,&ok);
       if(!ok)
       {
           return;
       }
       sortList(choice);
       updateListDisplay();
   }
}
   /*///////////////////////////////////////////////////Load File button handle/////////////////////////////////////////////////////////////////////////////////////////////*/
void Prioritizer::on_actionLoad_triggered()
{
    bool loadComplete = false; // Flag variable that determines whether the file was successfully loaded


    fstream newFile; //Will handle reading and writing from the specified file
    QString Qfilename;  //Will hold the filename the user enters
    string filename; // string version of the filename so that it may be used with std file operations

    bool ok; // will be used to handle user's selection on the popup dialogue

    while(!loadComplete)
    {
      Qfilename = QInputDialog::getText(this, "Load Existing File", "Enter the name of the file you'd like load", QLineEdit::Normal,".txt",&ok); //prompt user to name new file
      if (!ok)
      {
          return;
      }
        filename = Qfilename.toStdString(); //fstream works with std::string so we must convert it
        newFile.open(filename, ios::in | ios::out);
        if (newFile.is_open()) //if file opened successfully we can continue to load it
        {
            if (save_the_file) //If the current file has changes, prompt the user whether or not to save their progress before loading another file
            {
                 int choice = QInputDialog::getInt(this, "Current changes have not been saved", "Enter: 1. Save Changes; 2. Continue without saving;",0,1,2,1,&ok);
                 if (!ok)
                 {
                     newFile.close(); //Cancel button hit
                     return;
                 }
                 if (choice == 1){
                     on_actionSave_triggered(); // Save current changes
                 }
            }
            save_the_file = false; //continue without saving
            taskList.clear();
            Task temp;
            stringstream stringToint; //used to convert string values into int values
            string tempstr;

            while(!newFile.eof())             //populate the list from existing file
            {
             std::getline(newFile, temp.taskName, ',');
             std::getline(newFile, tempstr, '/');
             stringToint << tempstr;
             stringToint >> temp.dueMonth;
             stringToint.clear();
             std::getline(newFile, tempstr, ',');
             stringToint << tempstr;
             stringToint >> temp.dueDay;
             stringToint.clear();
             std::getline(newFile, tempstr, ',');
             stringToint << tempstr;
             stringToint >> temp.impact;
             stringToint.clear();
             std::getline(newFile, tempstr, '\n');
             stringToint << tempstr;
             stringToint >> temp.difficulty;
             stringToint.clear();
             taskList.push_back(temp);
            }
            taskList.pop_back(); //Fixes bug that would add extra empty task in loaded list
            updateListDisplay();
            currentFileName = Qfilename; // update current working file
            loadComplete = true; // Save complete. Mark the flag as true.
            newFile.close();
        }
        else
        {
            QMessageBox::information(this, "filename error", "Error opening file! ");
        }
    }
}
   /*///////////////////////////////////////////////////Create new file button handle/////////////////////////////////////////////////////////////////////////////////////*/

void Prioritizer::on_actionNew_triggered()
{
    bool filenameOccupied = true; //used as a flag to see if the selected filename is already an existing file

    fstream newFile;
    QString Qfilename;
    string filename;

    bool ok;

    while(filenameOccupied)
    {
        Qfilename = QInputDialog::getText(this, "Create a new file", "Enter the name of the new task list you'd like to create", QLineEdit::Normal,".txt",&ok); //prompt user to name new file
        if (!ok)
            {
              return;
            }
        filename = Qfilename.toStdString(); //fstream works with std::string so we must convert it
        newFile.open(filename, ios::app);
        if (newFile.is_open())
        {
            newFile.clear();
            newFile.seekg(0, ios::end);
            if (newFile.tellg() == 0)    //if file opened successfully and is empty file, proceed to create new file
            {
                newFile.close();
                newFile.open(filename, ios::out | ios::trunc);
                if (save_the_file) //If the current file has changes, prompt the user whether or not to save their progress before creating the new file
                {
                     int choice = QInputDialog::getInt(this, "Current changes have not been saved", "Enter: 1. Save Changes; 2. Continue without saving;",0,1,2,1,&ok);
                     if(!ok)
                     {
                         newFile.close();
                         return;
                     }
                     if(choice == 1){
                        on_actionSave_triggered(); // Save current changes
                     }
                }
                     save_the_file = false; //continue without saving
                     currentFileName = Qfilename; //update current working file.
                     taskList.clear(); //Clear contents of the current list
                     updateListDisplay(); // clear the display
                     filenameOccupied = false;
                     newFile.close();
            }
            else // else it is an existing file and we do not want to overwrite file contents.
                {
                  QMessageBox::information(this, "filename error", "Your selected filename is already used by an existing file! ");

                }
        }
        else
        {
        QMessageBox::information(this, "file error", "Error opening file or filename DNE!");
        return;
        }
    }
}
   /*///////////////////////////////////////////////////Save file button handle/////////////////////////////////////////////////////////////////////////////////////*/
void Prioritizer::on_actionSave_triggered()
{
    fstream newFile;
    QString Qfilename;
    string filename;

    bool ok;

    Qfilename = QInputDialog::getText(this, "Save file", "Enter the filename of this save", QLineEdit::Normal, currentFileName,&ok); //prompt user to name new file
    if (!ok) // If user does not hit cancel continue
    {
     return;
    }
    filename = Qfilename.toStdString(); //fstream works with std::string so we must convert it

    newFile.open(filename, ios::app);
    if (newFile.is_open())
    {
        newFile.clear();
        newFile.seekg(0, ios::end);
        cursor = taskList.begin();
        if (newFile.tellg() == 0)    // If file is empty save right away
        {
            newFile.close();
            newFile.open(filename, ios:: out | ios::trunc);
            while (cursor != taskList.end()) // Save contents of the list to a file in the required format
            {
                newFile << cursor->taskName;
                newFile << ',';
                newFile << cursor->dueMonth;
                newFile << '/';
                newFile << cursor->dueDay;
                newFile << ',';
                newFile << cursor->impact;
                newFile << ',';
                newFile << cursor->difficulty;
                newFile << '\n';
                cursor++;
            }
            currentFileName = Qfilename; //update current working file.
            save_the_file = false; //turn of the save flag
        }
        else //Selected filename has contents, prompt user to overwrite
        {
          QString garbage = QInputDialog::getText(this, "Save file", "Filename has contents. If you you like to overwrite it, press ok.", QLineEdit::Normal, "", &ok); //prompt user to name new file
          newFile.close();
          if (!ok)
          {
              //else user hit cancel
              return;
          }
            newFile.open(filename, ios:: out | ios::trunc);
            while (cursor != taskList.end()) // Save contents of the list to a file in the required format
            {
                newFile << cursor->taskName;
                newFile << ',';
                newFile << cursor->dueMonth;
                newFile << '/';
                newFile << cursor->dueDay;
                newFile << ',';
                newFile << cursor->impact;
                newFile << ',';
                newFile << cursor->difficulty;
                newFile << '\n';
                cursor++;
            }
            currentFileName = Qfilename; //update current working file.
            save_the_file = false;
       }
     }
     else
     {
        QMessageBox::information(this, "filename error", "Error opening file. ");
        newFile.close();
        return;
     }
}
