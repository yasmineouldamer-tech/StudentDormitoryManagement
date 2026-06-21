#ifndef STUDENT_H
#define STUDENT_H
#include <iostream>
#include <string>
#include <stdexcept>
using namespace std;
class Student
{
private:
    int id;
    int academicYear;
    string fullName;
public:
    Student();
    Student(int id, int AYear ,string fName);
    void setId(int id);
    void setAcademicYear(int academicYear);
    void setFullName(string fullName);
    int getId() const;
    int getAcademicYear() const;
    string getFullName() const;
    void display() const;
};
#endif
