#include <iostream>
#include "University.h"
using namespace std;

int main()
{
    try
    {
        University uni("University of Sidi Bel Abbes");

        Student s1(1, 2, "Ahmed Ali");
        Student s2(2, 1, "Rania Mokhtari");
        Student s3(3, 3, "Karim Chaabi");

        uni.addStudent(s1);
        uni.addStudent(s2);
        uni.addStudent(s3);

        Dormitory dorm("Zahra", 100);

        Room r1(101, 2);
        Room r2(102, 2);

        dorm.addRoom(r1);
        dorm.addRoom(r2);

        dorm.getRestaurant().setBreakfastMenu("Milk Bread Eggs");
        dorm.getRestaurant().setLunchMenu("Rice Chicken Salad");
        dorm.getRestaurant().setDinnerMenu("Soup Bread Tea");

        uni.addDormitory(dorm);

        uni.assignStudentToDormitory(1, "Zahra", 101);
        uni.assignStudentToDormitory(2, "Zahra", 101);
        uni.assignStudentToDormitory(3, "Zahra", 102);

        uni.display();

        cout << "\n--- Restaurant Access ---" << endl;

        Dormitory* d = uni.findDormitory("Zahra");

        if(d != nullptr)
        {
            d->getRestaurant().serveMeal();
            d->getRestaurant().serveMeal();

            d->getRestaurant().displayMenu();
        }
    }
    catch(const exception& e)
    {
        cout << "Error: " << e.what() << endl;
    }

    return 0;
}
