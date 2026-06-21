#ifndef DORMITORY_H
#define DORMITORY_H
#include <iostream>
#include <vector>
#include "Room.h"
#include "Restaurant.h"
#include <stdexcept>
using namespace std;

class Dormitory
{
private:
    string name;
    int capacity;
    vector<Room> rooms;
    Restaurant restaurant;

public:
    Dormitory();
    Dormitory(string name, int capacity);
    void setName(string name);
    void setCapacity(int capacity);
    string getName() const;
    int getCapacity() const;
    bool addRoom(const Room& room);
    Room* findRoom(int roomNumber);
    bool assignStudentToRoom(const Student& student, int roomNumber);
    bool removeStudentFromRoom(int studentId);
    Restaurant& getRestaurant();
    void display() const;
};
#endif
