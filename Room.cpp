#include "Room.h"
#include <stdexcept>
using namespace std;
Room::Room()
{
    roomNumber = 0;
    capacity = 0;
}

Room::Room(int roomN, int Capacity)
{
    setRoomNumber(roomN);
    setCapacity(Capacity);
}

void Room::setRoomNumber(int roomN)
{
    if (roomN <= 0)
        throw invalid_argument("Room number must be positive.");

    roomNumber = roomN;
}

void Room::setCapacity(int capacity)
{
    if (capacity <= 0)
        throw invalid_argument("Capacity must be positive.");

    this->capacity = capacity;
}

int Room::getRoomNumber() const
{
    return roomNumber;
}

int Room::getCapacity() const
{
    return capacity;
}

int Room::getCurrentOccupancy() const
{
    return students.size();
}

bool Room::isFull() const
{
    return students.size() >= capacity;
}

bool Room::isEmpty() const
{
    return students.size() == 0;
}

bool Room::addStudent(const Student& student)
{
    if (isFull())
        throw runtime_error("Room is full.");

    students.push_back(student);
    return true;
}

bool Room::removeStudent(int studentId)
{
    if (isEmpty())
        throw runtime_error("Room is empty.");

    for (int i = 0; i < students.size(); i++)
    {
        if (students[i].getId() == studentId)
        {
            students.erase(students.begin() + i);
            return true;
        }
    }

    throw runtime_error("Student not found in room.");
}

void Room::display() const
{
    cout << "Room Number: " << roomNumber << endl;
    cout << "Capacity: " << capacity << endl;
    cout << "Current Occupancy: " << students.size() << endl;
    cout << "Students:" << endl;

    if (isEmpty())
    {
        cout << "No students assigned." << endl;
    }
    else
    {
        for (int i = 0; i < students.size(); i++)
        {
            students[i].display();
            cout << endl;
        }
    }
}
