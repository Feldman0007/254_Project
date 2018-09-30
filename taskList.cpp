#include "taskList.h"
#include <iostream>
#include <stdexcept>

TaskList::TaskList() {        // constructor
     size = 0;							// initially empty
     header = new Task;              // create sentinels
     trailer = new Task;
     header->next = trailer;             // have them point to each other
     trailer->prev = header;
}

bool TaskList::empty() const	   // is list empty?
{
     return (header->next == trailer);
}

Task* TaskList::front() 	// return front element
{
     if (empty()) throw length_error("empty list");
     else {
          Task* ptr = header->next;
          return ptr;
     }
}

Task* TaskList::back() 	// get back element
{
     if (empty()) throw length_error("empty list");
     else {
          Task* ptr = trailer->prev;
          return ptr;
     }
}

TaskList::~TaskList() {	      // destructor
     while (!empty()) removeFront();     // remove all but sentinels
     delete header;				            // remove the sentinels
     delete trailer;
}

void TaskList::add(Task* v, Task e) {
     Task* newNode = new Task;               // create a new node for e
     newNode->taskName = e.taskName;
     newNode->dueMonth = e.dueMonth;
     newNode->dueDay = e.dueDay;
     newNode->effort = e.effort;
     newNode->impact = e.impact;
     newNode->next = v;				                  // link u in between v
     newNode->prev = v->prev;				            // ...and v->prev
     v->prev->next = newNode;
     v->prev = newNode;
     size++;
}


void TaskList::addFront(Task& e)	   // add to front of list
{
     add(header->next, e);
}

void TaskList::addBack(Task& e)	   // add to back of list
{
     add(trailer, e);
}

void TaskList::remove(Task* v) {	// remove node v
     Task* u = v->prev;				         // predecessor
     Task* w = v->next;				         // successor
     u->next = w;				                  // unlink v from list
     w->prev = u;
     delete v;
     size--;
}

void TaskList::removeFront()		// remove from font
{
     if (empty()) throw length_error("empty list");
     remove(header->next);
}

void TaskList::removeBack()		// remove from back
{
     if (empty()) throw length_error("empty list");
     remove(trailer->prev);
}

int TaskList::sizeOf() {				// list size
     return size;
}
