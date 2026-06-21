#include "University.h"
#include <stdexcept>
using namespace std;

University::University()
{
    name = "";
}

University::University(string name)
{
    setName(name);
}

void University::setName(string name)
{
    if(name.empty())
        throw invalid_argument("University name cannot be empty.");

    this->name = name;
}

string University::getName() const
{
    return name;
}

void University::addStudent(const Student& student)
{
    if(findStudent(student.getId()) != nullptr)
        throw runtime_error("Student already exists.");

    students.push_back(student);
}

Student* University::findStudent(int studentId)
{
    for(int i = 0; i < students.size(); i++)
    {
        if(students[i].getId() == studentId)
            return &students[i];
    }
    return nullptr;
}

bool University::removeStudent(int studentId)
{
    for(int i = 0; i < students.size(); i++)
    {
        if(students[i].getId() == studentId)
        {
            students.erase(students.begin() + i);
            return true;
        }
    }

    throw runtime_error("Student not found.");
}

void University::addDormitory(const Dormitory& dorm)
{
    if(findDormitory(dorm.getName()) != nullptr)
        throw runtime_error("Dormitory already exists.");

    dormitories.push_back(dorm);
}

Dormitory* University::findDormitory(string dormName)
{
    for(int i = 0; i < dormitories.size(); i++)
    {
        if(dormitories[i].getName() == dormName)
            return &dormitories[i];
    }
    return nullptr;
}

bool University::assignStudentToDormitory(int studentId, string dormName, int roomNumber)
{
    Student* student = findStudent(studentId);
    Dormitory* dorm = findDormitory(dormName);

    if(student == nullptr)
        throw runtime_error("Student not found.");

    if(dorm == nullptr)
        throw runtime_error("Dormitory not found.");

    return dorm->assignStudentToRoom(*student, roomNumber);
}

bool University::removeStudentFromSystem(int studentId)
{
    Student* student = findStudent(studentId);

    if(student == nullptr)
        throw runtime_error("Student not found.");

    for(int i = 0; i < dormitories.size(); i++)
    {
        try
        {
            dormitories[i].removeStudentFromRoom(studentId);
        }
        catch(...)
        {
        }
    }

    return removeStudent(studentId);
}

void University::display() const
{
    cout << "---------------- University: " << name << " ----------------" << endl;
    cout << "---- Students ----" << endl;

    if(students.empty())
    {
        cout << "No students." << endl;
    }
    else
    {
        for(int i = 0; i < students.size(); i++)
        {
            students[i].display();
            cout << endl;
        }
    }

    cout << "---------- Dormitories ----------" << endl;

    if(dormitories.empty())
    {
        cout << "No dormitories." << endl;
    }
    else
    {
        for(int i = 0; i < dormitories.size(); i++)
        {
            dormitories[i].display();
            cout << endl;
        }
    }

    cout << "----------------------------------------" << endl;
}
