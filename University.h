#ifndef UNIVERSITY_H
#define UNIVERSITY_H
#include <iostream>
#include <vector>
#include "Dormitory.h"
#include "Student.h"
#include <stdexcept>
using namespace std;

class University
{
private:
    string name;
    vector<Student> students;
    vector<Dormitory> dormitories;

public:
    University();
    University(string name);
    void setName(string name);
    string getName() const;
    void addStudent(const Student& student);
    bool removeStudent(int studentId);
    Student* findStudent(int studentId);
    void addDormitory(const Dormitory& dorm);
    Dormitory* findDormitory(string dormName);
    bool assignStudentToDormitory(int studentId, string dormName, int roomNumber);
    bool removeStudentFromSystem(int studentId);
    void display() const;
};

#endif
