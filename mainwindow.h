#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <vector>
#include "Student.h"
#include "Room.h"
#include "dormitory.h"
#include "restaurant.h"
#include "university.h"
#include <QMainWindow>

using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    // This is the active slot we want to test right now
    void on_btn_login_clicked();

    /* Commented out temporarily to match mainwindow.cpp
    void on_pushButton_clicked();
    void on_btn_addStudent_clicked();
    void on_btn_removeStudent_clicked();
    void on_btn_searchStudent_clicked();
    void on_btn_addRoom_clicked();
    void on_btn_assignStudent_clicked();
    void on_btn_showRooms_clicked();
    void on_btn_addDormitory_clicked();
    void on_btn_setMenu_clicked();
    void on_btn_addRoomToDormitory_clicked();
    void on_btn_saveData_clicked();
    void on_btn_loadData_clicked();
    void on_btn_showUniversity_clicked();
    */

    void on_btn_dashboard_clicked();

    void on_pushButton_clicked();

    void on_btn_room_clicked();

    void on_btn_dormitory_clicked();

    void on_btn_restaurant_clicked();

    void on_btn_logout_clicked();

    void on_btn_addstudent_clicked();

    void on_btn_removeStudent_clicked();

    void on_btn_searchStudent_clicked();

    void on_btn_dashboard_2_clicked();

    void on_pushButton_2_clicked();

    void on_btn_room_2_clicked();

    void on_btn_dormitory_2_clicked();

    void on_btn_restaurant_2_clicked();

    void on_btn_logout_2_clicked();

    void on_btn_addRoom_clicked();

    void on_btn_searchroom_clicked();

    void on_btn_removeroom_clicked();

    void on_btn_dashboard_4_clicked();

    void on_pushButton_4_clicked();

    void on_btn_room_4_clicked();

    void on_btn_dormitory_4_clicked();

    void on_btn_restaurant_4_clicked();

    void on_btn_logout_4_clicked();

    void on_btn_addDormitory_clicked();

    void on_btn_searchDormitory_clicked();

    void on_btn_removeDormitory_clicked();

    void on_btn_dashboard_6_clicked();

    void on_pushButton_6_clicked();

    void on_btn_room_6_clicked();

    void on_btn_dormitory_6_clicked();

    void on_btn_restaurant_6_clicked();

    void on_btn_logout_6_clicked();

    void on_btn_addMenu_clicked();

    void on_btn_searchMenu_clicked();

    void on_btn_serveMeal_clicked();

    void on_btn_removeMenu_clicked();

    void on_btn_dashboard_10_clicked();

    void on_pushButton_10_clicked();

    void on_btn_room_10_clicked();

    void on_btn_dormitory_10_clicked();

    void on_btn_restaurant_10_clicked();

    void on_btn_logout_10_clicked();

    void on_btn_reset_clicked();
    void showMessage(QString title, QString text);

    void on_pushButton_11_clicked();

    void on_pushButton_12_clicked();

    void on_btn_home_clicked();

    void on_btn_home1_clicked();

    void on_btn_Home2_clicked();

    void on_btn_home3_clicked();

    void on_btn_home3_2_clicked();
    void on_btn_pushButton_11_clicked();
    void on_btn_loadData_clicked();

private:
    Ui::MainWindow *ui;
    vector<Student> students;
    vector<Room> rooms;
    vector<Dormitory> dormitories;
    University university;
    vector<Restaurant> restaurants;
    // Inside mainwindow.h under the private or public section
    QString currentLoggedInUser;
};

#endif // MAINWINDOW_H
