/*
*    Task object made of type struct. The tasklist consists of Task structs.
*/

#pragma once
#ifndef TASKLIST_H
#define TASKLIST_H

#include <string>

using namespace std;

/*
*    Task attributes:
*    @ dueMonth: month task is due
*    @ dueDay: day task is due
*    @ impact: percent/impact on grade
*    @ effort: amount of effort/ level of difficulty (subjective trait)
*/
struct Task {
     // task attributes
     string  taskName;
     int dueMonth, dueDay, impact, effort; 

     // constructors
     Task() : taskName(""), dueMonth(0),dueDay(0), impact(0), effort(0) {}
     Task(string name, int month, int day, int imp, int input) {
               taskName = name;
               dueMonth = month;
               dueDay = day;
               impact = imp;
               effort = input;
     }
};
#endif
