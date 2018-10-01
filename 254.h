#include<iostream>
#include<string>
#include<list>
#include<iterator>
using namespace std;


struct Date {
	int month, day;

	Date(int mo, int dy) : month(mo), day(dy) {}
};

class Task {
private: 
	string tname;
	Date dueDate;
	int percentage, difficulty;

public:
	Task(string t, int dm, int dd, int per, int diff)
		: tname(t), percentage(per), difficulty(diff), dueDate(dm, dd) {}
	
	// Accessor Functions
	string getName() { return tname; }
	Date getDueDate() { return dueDate; }
	int getPercentage() { return percentage; }
	int getDifficulty() { return difficulty; }

	//  Mutator Functions
	// Do we want to allow them to edit a tasklist?

};

class TaskList {
private:
	list<Task> tasklist;
public:
	TaskList();

	void addTask(Task add); // { tasklist.push_front(add); }				//add a Task to the TaskList
	void removeTask(Task remove);//	{ tasklist.erase(); }	//remove a Task from the TaskList
	void completeTask(Task complete);// { removeTask(complete); }	//complete a Task (optional)
	void print();												//output the TaskList
	TaskList prioritize();						//categorize the TaskList by user option
		//menu driven(1 = name, 2 = date, etc.)
	
};