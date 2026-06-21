#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>
#include <QDebug>
#include <fstream>
#include <QAbstractItemView>
#include <QHeaderView>
#include <QFile>
#include <QTextStream>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableWidget_students->setColumnCount(3);
    ui->tableWidget_students->setRowCount(0);
    ui->tableWidget_students->verticalHeader()->setVisible(false);

    QStringList headers = {"Student ID", "Full Name", "Academic Year"};
    ui->tableWidget_students->setHorizontalHeaderLabels(headers);
    // This forces the columns to scale dynamically and fill the entire available width
    ui->tableWidget_students->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    // Allow the header row to accept a custom size, then set its height to 40 pixels
    ui->tableWidget_students->horizontalHeader()->setMinimumSectionSize(60);
    ui->tableWidget_students->horizontalHeader()->setDefaultSectionSize(60);
    ui->tableWidget_students->horizontalHeader()->setFixedHeight(60);

    ui->tableWidget_students->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget_students->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_students->setAlternatingRowColors(true);
    ui->tableWidget_students->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget_room->horizontalHeader()

        ->setSectionResizeMode(QHeaderView::Stretch);

    ui->tableWidget_room->verticalHeader()->setVisible(false);
    // Update this in your MainWindow constructor
    ui->restaurantTable->setColumnCount(5);

    // Ensure the columns stretch beautifully across your panel
    ui->restaurantTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->restaurantTable->horizontalHeader()->setFixedHeight(45);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// ==========================================
// ACTIVE LOGIN FUNCTIONALITY
// ==========================================

void MainWindow::on_btn_login_clicked()
{
    QString username = ui->lineEditusername->text().trimmed();
    QString password = ui->lineEditpassword->text().trimmed();

    // Check empty fields
    if (username.isEmpty() || password.isEmpty())
    {
        QMessageBox::warning(this, "Error", "Please fill in all fields!");
        return;
    }

    // ==========================
    // Username validation
    // ==========================
    bool hasLetter = false;

    for (QChar ch : username)
    {
        if (ch.isLetter())
            hasLetter = true;

        if (!(ch.isLetterOrNumber() || ch == '_'))
        {
            QMessageBox::warning(this, "Invalid Username",
                                 "Username can contain only letters, numbers and '_'.");
            return;
        }
    }

    if (username.length() < 4)
    {
        QMessageBox::warning(this, "Invalid Username",
                             "Username must contain at least 4 characters.");
        return;
    }

    if (!hasLetter)
    {
        QMessageBox::warning(this, "Invalid Username",
                             "Username must contain at least one letter.");
        return;
    }


    // ==========================
    // Password validation
    // ==========================
    bool hasUpper = false;
    bool hasLower = false;
    bool hasNumber = false;
    bool hasSpecial = false;

    for (QChar ch : password)
    {
        if (ch.isUpper())
            hasUpper = true;
        else if (ch.isLower())
            hasLower = true;
        else if (ch.isDigit())
            hasNumber = true;
        else
            hasSpecial = true;
    }

    if (password.length() < 8)
    {
        QMessageBox::warning(this, "Weak Password",
                             "Password must contain at least 8 characters.");
        return;
    }

    if (!hasLower)
    {
        QMessageBox::warning(this, "Weak Password",
                             "Password must contain at least one lowercase letter.");
        return;
    }

    if (!hasNumber)
    {
        QMessageBox::warning(this, "Weak Password",
                             "Password must contain at least one number.");
        return;
    }

    if (!hasSpecial)
    {
        QMessageBox::warning(this, "Weak Password",
                             "Password must contain at least one special character (!,@,#,$,%,...).");
        return;
    }

    // ==========================
    // Admin login
    // ==========================
    if (username == "admin" && password == "Admin1234!")
    {
        currentLoggedInUser = "admin"; // Track session
        QMessageBox::information(this, "Admin", "Welcome Admin!");
        on_btn_loadData_clicked(); // Load admin files if any exist
        ui->stackedWidget->setCurrentIndex(1);
        return;
    }

    // ===========================================
    // Personal User File Auth & Persistence Hook
    // ===========================================
    QString authFileName = username + "_auth.txt";
    QFile authFile(authFileName);

    if (authFile.exists()) {
        // User already exists -> Verify Password
        if (authFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&authFile);
            QString savedPassword = in.readLine().trimmed();
            authFile.close();

            if (password != savedPassword) {
                QMessageBox::critical(this, "Access Denied", "Incorrect password for this user account!");
                return; // Crash stop right here
            }
        }
    } else {
        // Brand New User -> Register Password
        if (authFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&authFile);
            out << password;
            authFile.close();
            QMessageBox::information(this, "Account Created", "New account registered successfully!");
        }
    }

    // Set the session state variables
    currentLoggedInUser = username;

    QMessageBox::information(this, "Login", "Login successful!");

    // Auto-load this specific profile's elements
    on_btn_loadData_clicked();

    ui->stackedWidget->setCurrentIndex(1);
}
void MainWindow::on_btn_addstudent_clicked()
{
    if (ui->lineEdit_studentId->text().isEmpty() ||
        ui->lineEdit_studentName->text().isEmpty() ||
        ui->lineEdit_year->text().isEmpty())
    {
        QMessageBox::warning(this, "Error", "Please fill all fields!");
        return;
    }

    int id = ui->lineEdit_studentId->text().toInt();
    QString name = ui->lineEdit_studentName->text();
    int year = ui->lineEdit_year->text().toInt();

    Student s(id, year, name.toStdString());
    students.push_back(s);

    int row = ui->tableWidget_students->rowCount();
    ui->tableWidget_students->insertRow(row);

    ui->tableWidget_students->setItem(row,0,new QTableWidgetItem(QString::number(id)));
    ui->tableWidget_students->setItem(row,1,new QTableWidgetItem(name));
    ui->tableWidget_students->setItem(row,2,new QTableWidgetItem(QString::number(year)));

    ui->lineEdit_studentId->clear();
    ui->lineEdit_studentName->clear();
    ui->lineEdit_year->clear();

    QMessageBox::information(this,"Success","Student added successfully!");
}

void MainWindow::on_btn_removeStudent_clicked()
{
    int id = ui->lineEdit_searchId->text().toInt();

    for(int i=0;i<students.size();i++)
    {
        if(students[i].getId()==id)
        {
            students.erase(students.begin()+i);
            ui->tableWidget_students->removeRow(i);

            QMessageBox::information(this,"Success","Student removed!");
            return;
        }
    }

    QMessageBox::warning(this,"Error","Student not found!");
}

void MainWindow::on_btn_searchStudent_clicked()
{
    int id = ui->lineEdit_searchId->text().toInt();

    for(int i=0;i<students.size();i++)
    {
        if(students[i].getId()==id)
        {
            ui->tableWidget_students->selectRow(i);

            QMessageBox::information(
                this,
                "Student Found",
                "ID: " + QString::number(students[i].getId()) +
                    "\nName: " + QString::fromStdString(students[i].getFullName()) +
                    "\nYear: " + QString::number(students[i].getAcademicYear())
                );

            return;
        }
    }

    QMessageBox::warning(this,"Not Found","Student not found!");
}

 /* void MainWindow::on_btn_addRoom_clicked()
{
    int number = ui->lineEdit_roomNumber->text().toInt();
    int capacity = ui->lineEdit_capacity->text().toInt();

    if (number <= 0 || capacity <= 0) {
        QMessageBox::warning(this, "Error", "Invalid room data!");
        return;
    }

    Room r(number, capacity);
    rooms.push_back(r);

    QMessageBox::information(this, "Success", "Room added successfully!");
}

void MainWindow::on_btn_assignStudent_clicked()
{
    int studentId = ui->lineEdit_assignStudentId->text().toInt();
    int roomNumber = ui->lineEdit_assignRoomNumber->text().toInt();

    Student *foundStudent = nullptr;
    Room *foundRoom = nullptr;

    // find student
    for (auto &s : students) {
        if (s.getId() == studentId) {
            foundStudent = &s;
            break;
        }
    }

    // find room
    for (auto &r : rooms) {
        if (r.getRoomNumber() == roomNumber) {
            foundRoom = &r;
            break;
        }
    }

    if (!foundStudent || !foundRoom) {
        QMessageBox::warning(this, "Error", "Student or Room not found!");
        return;
    }

    if (foundRoom->isFull()) {
        QMessageBox::warning(this, "Error", "Room is full!");
        return;
    }

    foundRoom->addStudent(*foundStudent);

    QMessageBox::information(this, "Success", "Student assigned to room!");
}

void MainWindow::on_btn_showRooms_clicked()
{
    ui->roomList->clear();

    for (const Room &r : rooms)
    {
        QString text =
            "Room " + QString::number(r.getRoomNumber()) +
            " - " + QString::number(r.getCurrentOccupancy()) +
            "/" + QString::number(r.getCapacity()) + " students";

        if (r.isFull())
            text += " (FULL)";

        ui->roomList->addItem(text);
    }
}

void MainWindow::on_btn_addDormitory_clicked()
{
        QString name = ui->lineEdit_dormitoryName->text();
        int capacity = ui->lineEdit_dormitoryCapacity->text().toInt();

        if(name.isEmpty())
        {
            QMessageBox::warning(this,"Error","Enter dormitory name!");
            return;
        }

        Dormitory d(name.toStdString(),capacity);

        dormitories.push_back(d);

        ui->dormitoryList->addItem(name);

        QMessageBox::information(this,
                                 "Success",
                                 "Dormitory added!");
}

void MainWindow::on_btn_setMenu_clicked()
{
        QString breakfast = ui->lineEdit_breakfast->text();
        QString lunch = ui->lineEdit_lunch->text();
        QString dinner = ui->lineEdit_dinner->text();

        ui->menuList->clear();

        ui->menuList->addItem("Breakfast: " + breakfast);
        ui->menuList->addItem("Lunch: " + lunch);
        ui->menuList->addItem("Dinner: " + dinner);

        QMessageBox::information(this,
                                 "Success",
                                 "Menu saved successfully!");
}

void MainWindow::on_btn_addRoomToDormitory_clicked()
{
        QString dormName = ui->lineEdit_dormitoryName->text();
        int roomNumber = ui->lineEdit_dormRoomNumber->text().toInt();

        Dormitory *foundDorm = nullptr;
        Room *foundRoom = nullptr;

        for (auto &d : dormitories)
        {
            if (d.getName() == dormName.toStdString())
            {
                foundDorm = &d;
                break;
            }
        }

        for (auto &r : rooms)
        {
            if (r.getRoomNumber() == roomNumber)
            {
                foundRoom = &r;
                break;
            }
        }

        if (!foundDorm || !foundRoom)
        {
            QMessageBox::warning(this,
                                 "Error",
                                 "Dormitory or Room not found!");
            return;
        }

        foundDorm->addRoom(*foundRoom);

        QMessageBox::information(this,
                                 "Success",
                                 "Room added to dormitory!");
}

void MainWindow::on_btn_saveData_clicked()
{
        std::ofstream file("students.txt");

        for (const Student &s : students)
        {
            file << s.getId() << " "
                 << s.getAcademicYear() << " "
                 << s.getFullName() << std::endl;
        }

        file.close();

        QMessageBox::information(this,
                                 "Success",
                                 "Students saved!");
}

void MainWindow::on_btn_loadData_clicked()
{
        students.clear();
        ui->studentList->clear();

        std::ifstream file("students.txt");

        int id, year;
        std::string name;

        while (file >> id >> year)
        {
            file.ignore();
            getline(file, name);

            Student s(id, year, name);

            students.push_back(s);

            QString text =
                QString::number(id) +
                " - " +
                QString::fromStdString(name);

            ui->studentList->addItem(text);
        }

        file.close();

        QMessageBox::information(this,
                                 "Success",
                                 "Students loaded!");
}

void MainWindow::on_btn_showUniversity_clicked()
{
    ui->universityList->clear();

    ui->universityList->addItem("Students: " +
                                QString::number(students.size()));

    ui->universityList->addItem("Rooms: " +
                                QString::number(rooms.size()));

    ui->universityList->addItem("Dormitories: " +
                                QString::number(dormitories.size()));
}
*/
void MainWindow::on_btn_dashboard_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}
void MainWindow::on_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}


void MainWindow::on_btn_room_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}


void MainWindow::on_btn_dormitory_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}


void MainWindow::on_btn_restaurant_clicked()
{
   ui->stackedWidget->setCurrentIndex(5);
}


void MainWindow::on_btn_logout_clicked()
{
        QMessageBox::StandardButton reply;

        reply = QMessageBox::question(
            this,
            "Logout",
            "Are you sure you want to logout?",
            QMessageBox::Yes | QMessageBox::No);

        if (reply == QMessageBox::Yes)
        {
            ui->lineEditusername->clear();
            ui->lineEditpassword->clear();

            ui->stackedWidget->setCurrentIndex(0);
        }
}



void MainWindow::on_btn_dashboard_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_btn_room_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}


void MainWindow::on_btn_dormitory_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}


void MainWindow::on_btn_restaurant_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
}


void MainWindow::on_btn_logout_2_clicked()
{
    QMessageBox::StandardButton reply;

    reply = QMessageBox::question(
        this,
        "Logout",
        "Are you sure you want to logout?",
        QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes)
    {
        ui->lineEditusername->clear();
        ui->lineEditpassword->clear();

        ui->stackedWidget->setCurrentIndex(0);
    }
}


void MainWindow::on_pushButton_2_clicked()
{
     ui->stackedWidget->setCurrentIndex(2);
}


void MainWindow::on_btn_addRoom_clicked()
{
    int roomNumber =
            ui->lineEdit_roomNumber->text().toInt();

        int capacity =
            ui->lineEdit_capacity->text().toInt();

        if(ui->lineEdit_roomNumber->text().isEmpty() ||
            ui->lineEdit_capacity->text().isEmpty())
        {
            QMessageBox::warning(
                this,
                "Error",
                "Please fill all fields!"
                );
            return;
        }

        Room r(roomNumber, capacity);

        rooms.push_back(r);

        int row = ui->tableWidget_room->rowCount();
        ui->tableWidget_room->insertRow(row);

        ui->tableWidget_room->setItem(
            row,0,
            new QTableWidgetItem(
                QString::number(roomNumber)));

        ui->tableWidget_room->setItem(
            row,1,
            new QTableWidgetItem(
                QString::number(capacity)));

        ui->tableWidget_room->setItem(
            row,2,
            new QTableWidgetItem("0"));

        ui->tableWidget_room->setItem(
            row,3,
            new QTableWidgetItem("Empty"));

        ui->tableWidget_room->setItem(
            row,4,
            new QTableWidgetItem(
                QString::number(capacity)));

        QMessageBox::information(
            this,
            "Success",
            "Room added!");

}


void MainWindow::on_btn_searchroom_clicked()
{
    // 1. Get the room number from the search input box
    QString searchStr = ui->lineEdit_roomNumber_2->text().trimmed();

    if (searchStr.isEmpty()) {
        return; // Exit if the user didn't type anything
    }

    int roomNumber = searchStr.toInt();
    int rowCount = ui->tableWidget_room->rowCount();
    bool found = false;

    // 2. Loop through every row in your Table Widget
    for (int row = 0; row < rowCount; ++row) {
        // Assuming Room Number is stored in Column 0 of your table
        QTableWidgetItem *roomItem = ui->tableWidget_room->item(row, 0);

        if (roomItem) {
            // Check if the table row's room number matches the searched number
            if (roomItem->text().toInt() == roomNumber) {
                found = true;

                // 3. Highlight the matching row with a soft blue tint
                QColor highlightColor("#dbeafe");

                for (int col = 0; col < ui->tableWidget_room->columnCount(); ++col) {
                    QTableWidgetItem *item = ui->tableWidget_room->item(row, col);
                    if (item) {
                        item->setBackground(highlightColor);
                        item->setForeground(QColor("#000050")); // Crisp dark text
                    }
                }

                // Automatically scroll the table view down to show this row
                ui->tableWidget_room->scrollToItem(roomItem);
            }
            else {
                // 4. Reset other non-matching rows back to normal white/gray layout
                for (int col = 0; col < ui->tableWidget_room->columnCount(); ++col) {
                    QTableWidgetItem *item = ui->tableWidget_room->item(row, col);
                    if (item) {
                        item->setBackground(Qt::white);
                        item->setForeground(QColor("#1e293b"));
                    }
                }
            }
        }
    }

    // 5. Optional: Keep a warning popup ONLY if the room doesn't exist anywhere
    if (!found) {
        QMessageBox::warning(this, "Not Found", "Room not found in the table!");
    }
}


void MainWindow::on_btn_removeroom_clicked()
{
        int roomNumber =
            ui->lineEdit_roomNumber_2->text().toInt();

        for(int i=0;i<rooms.size();i++)
        {
            if(rooms[i].getRoomNumber()
                == roomNumber)
            {
                rooms.erase(
                    rooms.begin()+i);

                ui->tableWidget_room->removeRow(i);

                QMessageBox::information(
                    this,
                    "Success",
                    "Room removed!");

                return;
            }
        }

        QMessageBox::warning(
            this,
            "Error",
            "Room not found!");
}


void MainWindow::on_btn_dashboard_4_clicked()
{
     ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_pushButton_4_clicked()
{
      ui->stackedWidget->setCurrentIndex(2);
}


void MainWindow::on_btn_room_4_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}


void MainWindow::on_btn_dormitory_4_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}


void MainWindow::on_btn_restaurant_4_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
}


void MainWindow::on_btn_logout_4_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_btn_addDormitory_clicked()
{
        QString name =
            ui->lineEdit_dormitoryName->text();

        int capacity =
            ui->lineEdit_dormitoryCapacity->text().toInt();

        if(name.isEmpty() ||
            ui->lineEdit_dormitoryCapacity->text().isEmpty())
        {
            QMessageBox::warning(
                this,
                "Error",
                "Please fill all fields!");
            return;
        }

        Dormitory d(
            name.toStdString(),
            capacity);

        dormitories.push_back(d);

        int row =
            ui->dormitoryTable->rowCount();

        ui->dormitoryTable->insertRow(row);

        ui->dormitoryTable->setItem(
            row,0,
            new QTableWidgetItem(name));

        ui->dormitoryTable->setItem(
            row,1,
            new QTableWidgetItem(
                QString::number(capacity)));

        ui->dormitoryTable->setItem(
            row,2,
            new QTableWidgetItem("0"));

        QMessageBox::information(
            this,
            "Success",
            "Dormitory added!");
}


void MainWindow::on_btn_searchDormitory_clicked()
{
    // 1. Get the dormitory name from the input box
    QString searchName = ui->lineEdit_searchDormitory->text().trimmed();

    if (searchName.isEmpty()) {
        return; // Stop if the search bar is completely blank
    }

    int rowCount = ui->dormitoryTable->rowCount();
    bool found = false;

    // 2. Loop through every row in your Dormitories Table Widget
    for (int row = 0; row < rowCount; ++row) {
        // Assuming the Dormitory Name is in Column 0
        QTableWidgetItem *nameItem = ui->dormitoryTable->item(row, 0);

        if (nameItem) {
            // Check if the cell text matches what the user searched for
            if (nameItem->text().trimmed().compare(searchName, Qt::CaseInsensitive) == 0) {
                found = true;

                // 3. Highlight the matching row with our soft blue color
                QColor highlightColor("#dbeafe");

                for (int col = 0; col < ui->dormitoryTable->columnCount(); ++col) {
                    QTableWidgetItem *item = ui->dormitoryTable->item(row, col);
                    if (item) {
                        item->setBackground(highlightColor);
                        item->setForeground(QColor("#000050")); // Clean dark blue text
                    }
                }

                // Automatically scroll the table down to bring the highlighted row into view
                ui->dormitoryTable->scrollToItem(nameItem);
            }
            else {
                // 4. Reset all non-matching rows back to clean white
                for (int col = 0; col < ui->dormitoryTable->columnCount(); ++col) {
                    QTableWidgetItem *item = ui->dormitoryTable->item(row, col);
                    if (item) {
                        item->setBackground(Qt::white);
                        item->setForeground(QColor("#1e293b")); // Normal text
                    }
                }
            }
        }
    }

    // 5. Keep the fallback popup warning only if absolutely nothing was found
    if (!found) {
        QMessageBox::warning(this, "Not Found", "Dormitory not found in the table!");
    }
}

void MainWindow::on_btn_removeDormitory_clicked()
{
     QString name =
            ui->lineEdit_searchDormitory->text();

        for(int i=0;i<dormitories.size();i++)
        {
            if(QString::fromStdString(
                    dormitories[i].getName()) == name)
            {
                dormitories.erase(
                    dormitories.begin()+i);

                ui->dormitoryTable->removeRow(i);

                QMessageBox::information(
                    this,
                    "Success",
                    "Dormitory removed!");

                return;
            }
        }

        QMessageBox::warning(
            this,
            "Error",
            "Dormitory not found!");
}


void MainWindow::on_btn_dashboard_6_clicked()
{
     ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_pushButton_6_clicked()
{
     ui->stackedWidget->setCurrentIndex(2);
}


void MainWindow::on_btn_room_6_clicked()
{
     ui->stackedWidget->setCurrentIndex(3);
}


void MainWindow::on_btn_dormitory_6_clicked()
{
     ui->stackedWidget->setCurrentIndex(4);
}


void MainWindow::on_btn_restaurant_6_clicked()
{
     ui->stackedWidget->setCurrentIndex(5);
}


void MainWindow::on_btn_logout_6_clicked()
{
     ui->stackedWidget->setCurrentIndex(0);
}
void MainWindow::on_btn_addMenu_clicked()
{
    // 1. Get the inputs (Make sure to create a lineEdit_day or similar in your UI)
    QString day = ui->lineEdit_day->text().trimmed();
    QString breakfast = ui->lineEdit_breakfast->text().trimmed();
    QString lunch = ui->lineEdit_lunch->text().trimmed();
    QString dinner = ui->lineEdit_dinner->text().trimmed();

    if (day.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please enter the Day (e.g., Monday)!");
        return;
    }

    int currentRow = ui->restaurantTable->rowCount();
    ui->restaurantTable->insertRow(currentRow);

    // Column 0: Day
    ui->restaurantTable->setItem(currentRow, 0, new QTableWidgetItem(day));

    // Column 1: Breakfast
    ui->restaurantTable->setItem(currentRow, 1, new QTableWidgetItem(breakfast.isEmpty() ? "Not Served" : breakfast));

    // Column 2: Lunch
    ui->restaurantTable->setItem(currentRow, 2, new QTableWidgetItem(lunch.isEmpty() ? "Not Served" : lunch));

    // Column 3: Dinner
    ui->restaurantTable->setItem(currentRow, 3, new QTableWidgetItem(dinner.isEmpty() ? "Not Served" : dinner));

    // Column 4: "Meal Served" Status (Defaults to No)
    QTableWidgetItem *statusItem = new QTableWidgetItem("No");
    statusItem->setTextAlignment(Qt::AlignCenter);
    ui->restaurantTable->setItem(currentRow, 4, statusItem);

    // Clear inputs
    ui->lineEdit_day->clear();
    ui->lineEdit_breakfast->clear();
    ui->lineEdit_lunch->clear();
    ui->lineEdit_dinner->clear();
}

void MainWindow::on_btn_searchMenu_clicked()
{
      QString searchDay = ui->lineEdit_searchMenu->text().trimmed();

        if (searchDay.isEmpty()) {
            return;
        }

        int rowCount = ui->restaurantTable->rowCount();
        bool found = false;

        for (int row = 0; row < rowCount; ++row) {
            QTableWidgetItem *dayItem = ui->restaurantTable->item(row, 0); // Column 0: Day

            // Explicitly search by day row
            if (dayItem && dayItem->text().compare(searchDay, Qt::CaseInsensitive) == 0) {
                found = true;
                QColor highlightColor("#dbeafe"); // Your soft search focus blue

                for (int col = 0; col < ui->restaurantTable->columnCount(); ++col) {
                    QTableWidgetItem *item = ui->restaurantTable->item(row, col);
                    if (item) {
                        item->setBackground(highlightColor);
                        // Keep custom green text readable if it's already being served
                        if (item->foreground().color() != QColor("#065f46")) {
                            item->setForeground(QColor("#000050"));
                        }
                    }
                }
                ui->restaurantTable->scrollToItem(dayItem);
            }
            else {
                // Revert non-matching rows cleanly
                for (int col = 0; col < ui->restaurantTable->columnCount(); ++col) {
                    QTableWidgetItem *item = ui->restaurantTable->item(row, col);
                    if (item) {
                        // If it's a green served item, leave its background/foreground intact
                        if (item->foreground().color() == QColor("#065f46")) {
                            item->setBackground(QColor("#d1fae5"));
                        } else {
                            item->setBackground(Qt::white);
                            item->setForeground(QColor("#1e293b"));
                        }
                    }
                }
            }
        }

        if (!found) {
            QMessageBox::warning(this, "Not Found", "The specified day was not found in the schedule table.");
        }
}
void MainWindow::on_btn_serveMeal_clicked()
{
    // 1. Get the selected day row
    int currentRow = ui->restaurantTable->currentRow();

    if (currentRow < 0) {
        QMessageBox::warning(this, "Selection Error", "Please select a day row from the table first!");
        return;
    }

    // 2. See what meal type they selected in the dropdown
    QString serveType = ui->comboBox_serveType->currentText();
    int targetColumn = 1; // Default to Column 1 (Breakfast)

    if (serveType == "Lunch") {
        targetColumn = 2; // Column 2
    } else if (serveType == "Dinner") {
        targetColumn = 3; // Column 3
    }

    // 3. Get the item in that specific meal slot
    QTableWidgetItem *mealItem = ui->restaurantTable->item(currentRow, targetColumn);

    if (mealItem && mealItem->text() != "Not Served") {
        // Highlight just this specific meal slot with a lively green color
        mealItem->setBackground(QColor("#d1fae5")); // Soft light green
        mealItem->setForeground(QColor("#065f46")); // Deep professional forest green

        // Optional: Update the "Meal Served" summary column (Column 4) to track it
        ui->restaurantTable->setItem(currentRow, 4, new QTableWidgetItem(serveType + " is Active"));

        QMessageBox::information(this, "Success", serveType + " is now marked as currently served!");
    } else {
        QMessageBox::warning(this, "Menu Error", "Cannot serve this meal because it is marked as 'Not Served'!");
    }
}


void MainWindow::on_btn_removeMenu_clicked()
{
        QString meal = ui->lineEdit_searchMenu->text().trimmed();

        if(meal.isEmpty())
        {
            QMessageBox::warning(
                this,
                "Error",
                "Enter a meal name!");
            return;
        }

        for(int i = 0; i < restaurants.size(); i++)
        {
            if(QString::fromStdString(restaurants[i].getBreakfastMenu()) == meal ||
                QString::fromStdString(restaurants[i].getLunchMenu()) == meal ||
                QString::fromStdString(restaurants[i].getDinnerMenu()) == meal)
            {
                restaurants.erase(restaurants.begin() + i);

                ui->restaurantTable->removeRow(i);

                QMessageBox::information(
                    this,
                    "Success",
                    "Menu removed!");

                return;
            }
        }

        QMessageBox::warning(
            this,
            "Not Found",
            "Meal not found!");
}


void MainWindow::on_btn_dashboard_10_clicked()
{
     ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_pushButton_10_clicked()
{
     ui->stackedWidget->setCurrentIndex(2);
}


void MainWindow::on_btn_room_10_clicked()
{
     ui->stackedWidget->setCurrentIndex(3);
}


void MainWindow::on_btn_dormitory_10_clicked()
{
     ui->stackedWidget->setCurrentIndex(4);
}


void MainWindow::on_btn_restaurant_10_clicked()
{
     ui->stackedWidget->setCurrentIndex(5);
}


void MainWindow::on_btn_logout_10_clicked()
{
     ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_btn_reset_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirm Reset", "Are you sure you want to wipe all tables clean?",
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        // Clear UI View Tables
        ui->restaurantTable->setRowCount(0);
        ui->tableWidget_students->setRowCount(0);

        // If you are using backend vectors/lists for OOP validation, clear them here too:
        // restaurants.clear();
        // students.clear();

        QMessageBox::information(this, "Reset Complete", "All local runtime data has been cleared.");
    }
}
void MainWindow::showMessage(QString title, QString text)
{
    QMessageBox msg;

    msg.setWindowTitle(title);
    msg.setText(text);

    msg.setStyleSheet(
        "QMessageBox {"
        "background-color: white;"
        "}"
        "QLabel {"
        "font-size: 14px;"
        "color: #2C3E50;"
        "font-weight: bold;"
        "min-width: 250px;"
        "}"
        "QPushButton {"
        "background-color: #3498DB;"
        "color: white;"
        "border-radius: 8px;"
        "padding: 6px 15px;"
        "font-weight: bold;"
        "}"
        "QPushButton:hover {"
        "background-color: #2980B9;"
        "}"
        );

    msg.exec();
}


void MainWindow::on_pushButton_11_clicked()
{
    if (currentLoggedInUser.isEmpty()) {
        QMessageBox::warning(this, "Session Error", "No active user session found. Please login.");
        return;
    }

    // Notice how the files are now unique per user profile!
    QFile menuFile(currentLoggedInUser + "_menu_data.txt");
    if (menuFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&menuFile);
        int rows = ui->restaurantTable->rowCount();
        for (int i = 0; i < rows; ++i) {
            out << ui->restaurantTable->item(i, 0)->text() << "|"
                << ui->restaurantTable->item(i, 1)->text() << "|"
                << ui->restaurantTable->item(i, 2)->text() << "|"
                << ui->restaurantTable->item(i, 3)->text() << "|"
                << ui->restaurantTable->item(i, 4)->text() << "\n";
        }
        menuFile.close();
    }

    QFile studentFile(currentLoggedInUser + "_student_data.txt");
    if (studentFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&studentFile);
        int rows = ui->tableWidget_students->rowCount();
        for (int i = 0; i < rows; ++i) {
            out << ui->tableWidget_students->item(i, 0)->text() << "|"
                << ui->tableWidget_students->item(i, 1)->text() << "|"
                << ui->tableWidget_students->item(i, 2)->text() << "\n";
        }
        studentFile.close();
    }

    QMessageBox::information(this, "Success", "Your profile data has been saved successfully!");
}


void MainWindow::on_btn_loadData_clicked()
{
    if (currentLoggedInUser.isEmpty()) return;

    // Load custom files for this specific user session
    QFile menuFile(currentLoggedInUser + "_menu_data.txt");
    if (menuFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&menuFile);
        ui->restaurantTable->setRowCount(0);
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList fields = line.split("|");
            if (fields.size() >= 5) {
                int row = ui->restaurantTable->rowCount();
                ui->restaurantTable->insertRow(row);
                ui->restaurantTable->setItem(row, 0, new QTableWidgetItem(fields[0]));
                ui->restaurantTable->setItem(row, 1, new QTableWidgetItem(fields[1]));
                ui->restaurantTable->setItem(row, 2, new QTableWidgetItem(fields[2]));
                ui->restaurantTable->setItem(row, 3, new QTableWidgetItem(fields[3]));

                QTableWidgetItem *statusItem = new QTableWidgetItem(fields[4]);
                statusItem->setTextAlignment(Qt::AlignCenter);
                if (fields[4].contains("Active") || fields[4] == "Yes") {
                    statusItem->setForeground(QColor("#16a34a"));
                    statusItem->setFont(QFont("Segoe UI", -1, QFont::Bold));
                }
                ui->restaurantTable->setItem(row, 4, statusItem);
            }
        }
        menuFile.close();
    } else {
        ui->restaurantTable->setRowCount(0); // If user has no data yet, keep it fresh and clean
    }

    QFile studentFile(currentLoggedInUser + "_student_data.txt");
    if (studentFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&studentFile);
        ui->tableWidget_students->setRowCount(0);
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList fields = line.split("|");
            if (fields.size() >= 3) {
                int row = ui->tableWidget_students->rowCount();
                ui->tableWidget_students->insertRow(row);
                ui->tableWidget_students->setItem(row, 0, new QTableWidgetItem(fields[0]));
                ui->tableWidget_students->setItem(row, 1, new QTableWidgetItem(fields[1]));
                ui->tableWidget_students->setItem(row, 2, new QTableWidgetItem(fields[2]));
            }
        }
        studentFile.close();
    } else {
        ui->tableWidget_students->setRowCount(0);
    }
}


void MainWindow::on_btn_home_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void MainWindow::on_btn_home1_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void MainWindow::on_btn_Home2_clicked()
{
     ui->stackedWidget->setCurrentIndex(1);
}


void MainWindow::on_btn_home3_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void MainWindow::on_btn_home3_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}


