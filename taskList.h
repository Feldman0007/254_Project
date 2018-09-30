#pragma once
#ifndef TASKLIST_H
#define TASKLIST_H

#include <string>

using namespace std;

struct Task {
     string  taskName;
     int dueMonth, dueDay, impact, effort; // Task attributes
     Task *prev;				         // ponter to previous task in the list
     Task *next;				         // pointer to next task in the list

     Task() : prev(nullptr), next(nullptr) {}
     Task(string name, int month, int day, int imp, int input) {
               taskName = name;
               dueMonth = month;
               dueDay = day;
               impact = imp;
               effort = input;
               prev = nullptr;
               next = nullptr;
          }
     };
class TaskList {	                  // a doubly linked list
public:
     TaskList();				            // empty list constructor
     ~TaskList();				         // destructor
     bool empty() const;			         // is list empty?
     Task* front();							// get front element
     Task* back();							// get back element
     void addFront(Task&);		      // add to front of list
     void addBack(Task&);		      // add to back of list
     void removeFront();			         // remove from front
     void removeBack();			         // remove from back
     int sizeOf();					// list size
     void add(Task*, Task);     // insert new node before v
     void remove(Task*);              // remove node v
private:                               // local type definitions
     int size;							// number of items
     Task* header;				         // header sentinel
     Task* trailer;                  // trailer sentinel
};
#endif // TASKLIST_H
