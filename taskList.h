#pragma once
#ifndef TASKLIST_H
#define TASKLIST_H

#include <string>

using namespace std;

struct Task {
     string  taskName;
     int dueMonth, dueDay, impact, effort; // Task attributes
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
