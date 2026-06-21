#include "Student.h"
#include <iostream>
#include <string>
#include <stdexcept>
using namespace std;
Student::Student()
{
    id = 0;
    fullName = "";
    academicYear = 0;
}

Student::Student(int id, int AYear, string fName)
{
    setId(id);
    setAcademicYear(AYear);
    setFullName(fName);
}

void Student::setId(int id)
{
    if (id <= 0)
        throw invalid_argument("Student ID must be positive.");

    this->id = id;
}

void Student::setFullName(string fName)
{
    if (fName.empty())
        throw invalid_argument("Full name cannot be empty.");

    fullName = fName;
}

void Student::setAcademicYear(int AYear)
{
    if (AYear <= 0)
        throw invalid_argument("Academic year must be positive.");

    academicYear = AYear;
}

int Student::getId() const
{
    return id;
}

string Student::getFullName() const
{
    return fullName;
}

int Student::getAcademicYear() const
{
    return academicYear;
}

void Student::display() const
{
    cout << "Full Name: " << fullName << endl;
    cout << "Student ID: " << id << endl;
    cout << "Academic Year: " << academicYear << endl;
}
