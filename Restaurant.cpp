#include "Restaurant.h"
#include <stdexcept>
using namespace std;
Restaurant::Restaurant()
{
    breakfastMenu = "";
    lunchMenu = "";
    dinnerMenu = "";
    mealsServed = 0;
}

Restaurant::Restaurant(string breakfast, string lunch, string dinner)
{
    setBreakfastMenu(breakfast);
    setLunchMenu(lunch);
    setDinnerMenu(dinner);

    mealsServed = 0;
}

void Restaurant::setBreakfastMenu(string breakfast)
{
    if (breakfast.empty())
        throw invalid_argument("Breakfast menu cannot be empty.");

    breakfastMenu = breakfast;
}

void Restaurant::setLunchMenu(string lunch)
{
    if (lunch.empty())
        throw invalid_argument("Lunch menu cannot be empty.");

    lunchMenu = lunch;
}

void Restaurant::setDinnerMenu(string dinner)
{
    if (dinner.empty())
        throw invalid_argument("Dinner menu cannot be empty.");

    dinnerMenu = dinner;
}

string Restaurant::getBreakfastMenu() const
{
    return breakfastMenu;
}

string Restaurant::getLunchMenu() const
{
    return lunchMenu;
}

string Restaurant::getDinnerMenu() const
{
    return dinnerMenu;
}

void Restaurant::serveMeal()
{
    mealsServed++;
}

int Restaurant::getMealsServed() const
{
    return mealsServed;
}

void Restaurant::displayMenu() const
{
    cout << "----- Restaurant Menu -----" << endl;
    cout << "Breakfast: " << breakfastMenu << endl;
    cout << "Lunch: " << lunchMenu << endl;
    cout << "Dinner: " << dinnerMenu << endl;
    cout << "Meals Served Today: " << mealsServed << endl;
    cout << "-----------------------------" << endl;
}
