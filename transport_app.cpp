#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <limits>

#include "User.h"
#include "Student.h"
#include "Admin.h"
#include "Driver.h"
#include "Vehicle.h"
#include "Bus.h"
#include "Van.h"
#include "Route.h"
#include "Bill.h"
#include "TransportManager.h"

using namespace std;

static void showMainMenu();
static void handleStudentMenu(TransportManager& manager, Student* student);
static void handleAdminMenu(TransportManager& manager, Admin* admin);
static void handleDriverMenu(TransportManager& manager, Driver* driver);

int main() {
    TransportManager manager;
    int choice;
    bool running = true;

    cout << "\n========================================" << endl;
    cout << "  UNIVERSITY TRANSPORT MANAGEMENT SYSTEM" << endl;
    cout << "========================================" << endl;
    cout << "         Object Oriented Programming    " << endl;
    cout << "                CSC-103                 " << endl;
    cout << "========================================" << endl;

    while (running) {
        showMainMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int userType;
                cout << "\nUser Registration" << endl;
                cout << "1. Student" << endl;
                cout << "2. Admin" << endl;
                cout << "3. Driver" << endl;
                cout << "Enter user type: ";
                cin >> userType;

                string name, email, password;
                cout << "Enter Name: ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, name);
                cout << "Enter Email: ";
                getline(cin, email);
                cout << "Enter Password: ";
                getline(cin, password);

                if (userType == 1) {
                    string studentID, department;
                    cout << "Enter Student ID: ";
                    getline(cin, studentID);
                    cout << "Enter Department: ";
                    getline(cin, department);

                    Student* student = new Student(manager.getNextUserID(), name, email, password, studentID, department);
                    if (manager.registerUser(student)) {
                        cout << "Student registered successfully! Your User ID is: " << manager.getNextUserID() - 1 << endl;
                    }
                } else if (userType == 2) {
                    string adminCode;
                    int accessLevel;
                    cout << "Enter Admin Code: ";
                    getline(cin, adminCode);
                    cout << "Enter Access Level (1-5): ";
                    cin >> accessLevel;

                    Admin* admin = new Admin(manager.getNextUserID(), name, email, password, adminCode, accessLevel);
                    if (manager.registerUser(admin)) {
                        cout << "Admin registered successfully! Your User ID is: " << manager.getNextUserID() - 1 << endl;
                    }
                } else if (userType == 3) {
                    // Driver registration via admin is implemented in menu,
                    // but allow basic driver self-registration as well.
                    string licenseNo, phone;
                    cout << "Enter LicenseNo (unique): ";
                    cin >> licenseNo;
                    cout << "Enter PhoneNumber: ";
                    cin >> phone;

                    Driver* driver = new Driver(manager.getNextUserID(), name, email, password, licenseNo, phone);
                    if (manager.registerUser(driver)) {
                        cout << "Driver registered successfully! Your User ID is: " << manager.getNextUserID() - 1 << endl;
                    }
                } else {
                    cout << "Invalid user type!" << endl;
                }
                break;
            }

            case 2: {
                string email, password;
                cout << "\nLogin" << endl;
                cout << "Email: ";
                cin >> email;
                cout << "Password: ";
                cin >> password;

                User* user = manager.login(email, password);
                if (!user) {
                    cout << "Invalid email or password!" << endl;
                    break;
                }

                cout << "Login successful! Welcome " << user->getName() << endl;

                if (user->getUserType() == "Student") {
                    handleStudentMenu(manager, dynamic_cast<Student*>(user));
                } else if (user->getUserType() == "Admin") {
                    handleAdminMenu(manager, dynamic_cast<Admin*>(user));
                } else if (user->getUserType() == "Driver") {
                    handleDriverMenu(manager, dynamic_cast<Driver*>(user));
                } else {
                    cout << "Unknown user type." << endl;
                }

                break;
            }

            case 3:
                cout << "Saving data and exiting system..." << endl;
                manager.saveData();
                running = false;
                break;

            default:
                cout << "Invalid choice! Please try again." << endl;
        }

        if (running) {
            cout << "\nPress Enter to continue...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
        }
    }

    cout << "\nThank you for using University Transport Management System!" << endl;
    return 0;
}

static void showMainMenu() {
    cout << "\n========== MAIN MENU ==========" << endl;
    cout << "1. Register User" << endl;
    cout << "2. Login" << endl;
    cout << "3. Exit" << endl;
    cout << "================================" << endl;
}

static void handleStudentMenu(TransportManager& manager, Student* student) {
    int choice;
    bool loggedIn = true;

    while (loggedIn) {
        cout << "\n========== STUDENT MENU ==========" << endl;
        cout << "Welcome, " << student->getName() << endl;
        cout << "1. View All Routes" << endl;
        cout << "2. Apply for Transport" << endl;
        cout << "3. View My Registration" << endl;
        cout << "4. Cancel Registration" << endl;
        cout << "5. View My Balance" << endl;
        cout << "6. Make Payment" << endl;
        cout << "7. Logout" << endl;
        cout << "===================================" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                manager.displayAllRoutes();
                break;

            case 2: {
                if (student->getHasTransport()) {
                    cout << "You already have active transport registration!" << endl;
                    break;
                }
                manager.displayAllRoutes();
                int routeID;
                cout << "Enter Route ID to apply: ";
                cin >> routeID;
                manager.applyForTransport(student->getUserID(), routeID);
                break;
            }

            case 3:
                if (student->getHasTransport()) {
                    cout << "You are registered for route ID: " << student->getAssignedRouteID() << endl;
                    Route* route = manager.getRoute(student->getAssignedRouteID());
                    if (route) route->displayRoute();
                } else {
                    cout << "You are not registered for any transport service." << endl;
                }
                break;

            case 4:
                manager.cancelRegistration(student->getUserID());
                break;

            case 5:
                cout << "Your current balance: Rs." << student->getBalance() << endl;
                break;

            case 6: {
                double amount;
                cout << "Enter amount to pay: Rs.";
                cin >> amount;
                manager.makePayment(student->getUserID(), amount);
                break;
            }

            case 7:
                loggedIn = false;
                cout << "Logged out successfully!" << endl;
                break;

            default:
                cout << "Invalid choice!" << endl;
        }

        if (loggedIn) {
            cout << "\nPress Enter to continue...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
        }
    }
}

static void handleAdminMenu(TransportManager& manager, Admin* admin) {
    int choice;
    bool loggedIn = true;

    while (loggedIn) {
        cout << "\n========== ADMIN MENU ==========" << endl;
        cout << "Welcome, " << admin->getName() << " (Access Level: " << admin->getAccessLevel() << ")" << endl;
        cout << "1. Add Vehicle" << endl;
        cout << "2. Edit Vehicle" << endl;
        cout << "3. Remove Vehicle" << endl;
        cout << "4. Add Route" << endl;
        cout << "5. Assign Vehicle to Route" << endl;
        cout << "6. View All Applications" << endl;
        cout << "7. Approve/Reject Requests" << endl;
        cout << "8. Add Driver" << endl; // ADDED
        cout << "9. Generate Revenue Report" << endl;
        cout << "10. Generate Route Usage Report" << endl;
        cout << "11. View All Vehicles" << endl;
        cout << "12. View All Routes" << endl;
        cout << "13. View All Students" << endl;
        cout << "14. Apply Late Fees" << endl;
        cout << "15. Save Data" << endl;
        cout << "16. Logout" << endl;
        cout << "=================================" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int vehicleType;
                cout << "Vehicle Type:" << endl;
                cout << "1. Bus" << endl;
                cout << "2. Van" << endl;
                cout << "Enter choice: ";
                cin >> vehicleType;

                string regNo, model;
                int capacity;
                cout << "Enter Registration Number: ";
                cin >> regNo;
                cout << "Enter Model: ";
                cin >> model;
                cout << "Enter Capacity: ";
                cin >> capacity;

                if (vehicleType == 1) {
                    int doors;
                    bool ac;
                    cout << "Enter Number of Doors: ";
                    cin >> doors;
                    cout << "Has AC (1 for Yes, 0 for No): ";
                    cin >> ac;
                    manager.addVehicle(new Bus(manager.getNextVehicleID(), regNo, capacity, model, doors, ac));
                } else {
                    int cargo;
                    bool highRoof;
                    cout << "Enter Cargo Space (cu ft): ";
                    cin >> cargo;
                    cout << "Has High Roof (1 for Yes, 0 for No): ";
                    cin >> highRoof;
                    manager.addVehicle(new Van(manager.getNextVehicleID(), regNo, capacity, model, cargo, highRoof));
                }

                cout << "Vehicle added successfully!" << endl;
                break;
            }

            case 2: {
                int vehicleID;
                manager.displayAllVehicles();
                cout << "Enter Vehicle ID to edit: ";
                cin >> vehicleID;
                string regNo;
                int capacity;
                cout << "Enter new Registration Number: ";
                cin >> regNo;
                cout << "Enter new Capacity: ";
                cin >> capacity;
                manager.updateVehicle(vehicleID, regNo, capacity);
                break;
            }

            case 3: {
                int vehicleID;
                manager.displayAllVehicles();
                cout << "Enter Vehicle ID to remove: ";
                cin >> vehicleID;
                manager.removeVehicle(vehicleID);
                break;
            }

            case 4: {
                string start, end;
                double distance, fare;
                cout << "Enter Start Point: ";
                cin >> start;
                cout << "Enter End Point: ";
                cin >> end;
                cout << "Enter Distance (km): ";
                cin >> distance;
                cout << "Enter Fare (Rs.): ";
                cin >> fare;
                manager.addRoute(new Route(manager.getNextRouteID(), start, end, distance, fare));
                cout << "Route added successfully!" << endl;
                break;
            }

            case 5: {
                int routeID, vehicleID;
                manager.displayAllRoutes();
                cout << "Enter Route ID: ";
                cin >> routeID;
                manager.displayAllVehicles();
                cout << "Enter Vehicle ID to assign: ";
                cin >> vehicleID;
                manager.assignVehicleToRoute(routeID, vehicleID);
                break;
            }

            case 6:
                manager.viewApplications();
                break;

            case 7: {
                int studentID, routeID;
                cout << "Enter Student ID to approve: ";
                cin >> studentID;
                cout << "Enter Route ID: ";
                cin >> routeID;
                if (manager.approveRegistration(studentID, routeID)) {
                    cout << "Application approved successfully!" << endl;
                } else {
                    cout << "Failed to approve application!" << endl;
                }
                break;
            }

            case 8: { // ADD DRIVER functionality
                string name, email, password;
                string licenseNo;
                string phone;

                cout << "Enter Driver Name: ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, name);
                cout << "Enter Email: ";
                getline(cin, email);
                cout << "Enter Password: ";
                getline(cin, password);

                cout << "Enter LicenseNo (unique): ";
                getline(cin, licenseNo);
                cout << "Enter PhoneNumber: ";
                getline(cin, phone);

                // NOTE: uniqueness by LicenseNo can be enforced here if you want;
                // current codebase does not have a helper to check duplicates.
                Driver* driver = new Driver(manager.getNextUserID(), name, email, password, licenseNo, phone);
                if (manager.registerUser(driver)) {
                    cout << "Driver added successfully! User ID is: " << manager.getNextUserID() - 1 << endl;
                }
                break;
            }

            case 9:
                manager.generateRevenueReport();
                break;

            case 10:
                manager.generateRouteUsageReport();
                break;

            case 11:
                manager.displayAllVehicles();
                break;

            case 12:
                manager.displayAllRoutes();
                break;

            case 13:
                manager.displayAllStudents();
                break;

            case 14:
                manager.applyLateFees();
                break;

            case 15:
                manager.saveData();
                break;

            case 16:
                loggedIn = false;
                cout << "Logged out successfully!" << endl;
                break;

            default:
                cout << "Invalid choice!" << endl;
        }

        if (loggedIn) {
            cout << "\nPress Enter to continue...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
        }
    }
}

static void handleDriverMenu(TransportManager& manager, Driver* driver) {
    (void)manager;
    int choice;
    bool loggedIn = true;

    while (loggedIn) {
        cout << "\n========== DRIVER MENU ==========" << endl;
        cout << "Welcome, " << driver->getName() << endl;
        cout << "1. View My Info" << endl;
        cout << "2. Logout" << endl;
        cout << "================================" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                driver->displayInfo();
                cout << endl;
                break;
            case 2:
                loggedIn = false;
                cout << "Logged out successfully!" << endl;
                break;
            default:
                cout << "Invalid choice!" << endl;
        }

        if (loggedIn) {
            cout << "\nPress Enter to continue...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
        }
    }
}

