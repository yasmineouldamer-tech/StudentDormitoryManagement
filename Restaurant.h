#ifndef RESTAURANT_H
#define RESTAURANT_H
#include <iostream>
#include <string>
#include <stdexcept>
using namespace std;
class Restaurant
{
private:
    string breakfastMenu;
    string lunchMenu;
    string dinnerMenu;
    int mealsServed;

public:
    Restaurant();
    Restaurant(string breakfast, string lunch, string dinner);
    void setBreakfastMenu(string breakfast);
    void setLunchMenu(string lunch);
    void setDinnerMenu(string dinner);
    string getBreakfastMenu() const;
    string getLunchMenu() const;
    string getDinnerMenu() const;
    void serveMeal();
    int getMealsServed() const;
    void displayMenu() const;
};
#endif
