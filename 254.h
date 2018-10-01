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

	void addTask(Task add) { //add a Task to the TaskList 
		tasklist.push_front(add);
	}

	void removeTask(Task remove) {	//remove a Task from the TaskList
		list<Task>::iterator rm;
		if rm = tasklist.end() { cout << "Task is not in the list!"; }
		else { 
			rm = findTask(remove);
			tasklist.erase(rm);
		}
	}
	
	list<Task>::iterator findTask(Task find) {
		//need a check if it's not in the list
		list<Task>::iterator notfound = tasklist.end();
		for(list<Task>::iterator it = tasklist.begin(); it != tasklist.end(); ++it) {
			if(it->getName() == find.getName()) 
			{ return it; }
		}
		return notfound;
		
	}

	void completeTask(Task complete) {
		removeTask(complete); 
	}

	void print();												//output the TaskList
	TaskList prioritize();						//categorize the TaskList by user option
		//menu driven(1 = name, 2 = date, etc.)
	
};