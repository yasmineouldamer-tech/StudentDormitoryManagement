#include "Dormitory.h"
#include <stdexcept>
using namespace std;
Dormitory::Dormitory()
{
    name = "";
    capacity = 0;
}

Dormitory::Dormitory(string name, int capacity)
{
    setName(name);
    setCapacity(capacity);
}

void Dormitory::setName(string name)
{
    if(name.empty())
        throw invalid_argument("Dormitory name cannot be empty.");

    this->name = name;
}

void Dormitory::setCapacity(int capacity)
{
    if(capacity <= 0)
        throw invalid_argument("Capacity must be positive.");

    this->capacity = capacity;
}

string Dormitory::getName() const
{
    return name;
}

int Dormitory::getCapacity() const
{
    return capacity;
}

Room* Dormitory::findRoom(int roomNumber)
{
    for(int i = 0; i < rooms.size(); i++)
    {
        if(rooms[i].getRoomNumber() == roomNumber)
            return &rooms[i];
    }
    return nullptr;
}

bool Dormitory::addRoom(const Room& room)
{
    if(findRoom(room.getRoomNumber()) != nullptr)
        throw runtime_error("Room already exists.");

    rooms.push_back(room);
    return true;
}

bool Dormitory::assignStudentToRoom(const Student& student, int roomNumber)
{
    Room* room = findRoom(roomNumber);

    if(room == nullptr)
        throw runtime_error("Room not found.");

    if(room->isFull())
        throw runtime_error("Room is full.");

    room->addStudent(student);
    return true;
}

bool Dormitory::removeStudentFromRoom(int studentId)
{
    for(int i = 0; i < rooms.size(); i++)
    {
        if(rooms[i].removeStudent(studentId))
            return true;
    }

    throw runtime_error("Student not found in any room.");
}

Restaurant& Dormitory::getRestaurant()
{
    return restaurant;
}

void Dormitory::display() const
{
    cout << "---------------- Dormitory: " << name << " ----------------" << endl;
    cout << "Capacity: " << capacity << endl;
    cout << "---- Rooms ----" << endl;

    if(rooms.empty())
    {
        cout << "No rooms available." << endl;
    }
    else
    {
        for(int i = 0; i < rooms.size(); i++)
        {
            rooms[i].display();
            cout << endl;
        }
    }

    cout << "--------- Restaurant ---------" << endl;
    restaurant.displayMenu();
}
