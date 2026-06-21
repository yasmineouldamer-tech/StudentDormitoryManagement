#ifndef ROOM_H
#define ROOM_H
#include <iostream>
#include <vector>
#include "Student.h"
#include <stdexcept>
using namespace std;
class Room
{
private:
    int roomNumber;
    int capacity;
    vector<Student> students;

public:
    Room();
    Room(int roomNumber, int capacity);
    void setRoomNumber(int roomNumber);
    void setCapacity(int capacity);
    int getRoomNumber() const;
    int getCapacity() const;
    int getCurrentOccupancy() const;
    bool isFull() const;
    bool isEmpty() const;
    bool addStudent(const Student& student);
    bool removeStudent(int studentId);
    void display() const;
};
#endif
