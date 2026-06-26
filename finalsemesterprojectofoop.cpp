#include "User.h"       //all the .h files are included here for implementation of all the classes in one file
#include "Student.h"  
#include "Admin.h"
#include "Driver.h"
#include "Vehicle.h"
#include "Bus.h"
#include "Van.h"
#include "Route.h"
#include "Bill.h"
#include "TransportManager.h"
#include <iostream>
#include <fstream>
#include <string>
#include <limits>

#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

// ========== SIMPLE COLOR FUNCTIONS ==========
// Cross-platform console color management
#ifdef _WIN32
// Windows-specific color setting using Windows API
void setColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}
#else
// Unix/Linux/Mac color setting using ANSI escape codes
void setColor(int color) {
    cout << "\033[" << color << "m";
}
#endif

// Function to print success messages in green
void printSuccess(const string& msg) {
    setColor(10); // Green
    cout << msg;
    setColor(7); // Reset to white
}

// Function to print error messages in light red
void printError(const string& msg) {
    setColor(12); // Light Red
    cout << msg;
    setColor(7);
}

// Function to print informational messages in yellow
void printInfo(const string& msg) {
    setColor(14); // Yellow
    cout << msg;
    setColor(7);
}

// Function to set border color to light cyan
void printBorder() {
    setColor(11); // Light Cyan for borders
}

// Function to reset color to default white
void resetColor() {
    setColor(7); // Reset to white
}

// ========== USER CLASS IMPLEMENTATION ==========
// Base class for all system users (Student, Admin, Driver)
User::User() : userID(0), name(""), email(""), password(""), userType("") {}

// Parameterized constructor for User class
User::User(int id, string n, string e, string pwd, string type) : userID(id), name(n), email(e), password(pwd), userType(type) {}

// Virtual destructor for proper cleanup of derived classes
User::~User() {}

// Getter methods for private member variables
int User::getUserID() const { return userID; }  
string User::getName() const { return name; }
string User::getEmail() const { return email; }
string User::getPassword() const { return password; }
string User::getUserType() const { return userType; }

// Setter methods for modifiable attributes
void User::setName(string n) { name = n; }
void User::setEmail(string e) { email = e; }
void User::setPassword(string pwd) { password = pwd; }

// Equality operator overload to compare users by ID
bool User::operator==(const User& other) const {
    return (userID == other.userID);
}

// Output stream operator overload for displaying user information
ostream& operator<<(ostream& os, const User& user) {
    os << "ID: " << user.userID << ", Name: " << user.name << ", Email: " << user.email << ", Type: " << user.userType;
    return os;
}

// ========== STUDENT CLASS IMPLEMENTATION ==========
// Student class inheriting from User, representing student users
Student::Student() : User(), studentID(""), department(""), balance(0), hasTransport(false), assignedRouteID(-1) {}

// Parameterized constructor for Student
Student::Student(int id, string n, string e, string pwd, string stuID, string dept)
    : User(id, n, e, pwd, "Student"), studentID(stuID), department(dept), 
      balance(0), hasTransport(false), assignedRouteID(-1) {}

Student::~Student() {}

// Getter methods for student-specific attributes
string Student::getStudentID() const { return studentID; }
string Student::getDepartment() const { return department; }
double Student::getBalance() const { return balance; }
bool Student::getHasTransport() const { return hasTransport; }
int Student::getAssignedRouteID() const { return assignedRouteID; }

// Setter methods for student attributes
void Student::setBalance(double bal) { balance = bal; }
void Student::setHasTransport(bool status) { hasTransport = status; }
void Student::setAssignedRouteID(int routeID) { assignedRouteID = routeID; }

// Display student information in formatted output
void Student::displayInfo() const {
    cout << "\n========== STUDENT INFO ==========\n";
    cout << " Name       : " << name << endl;
    cout << " User ID    : " << userID << endl;
    cout << " Student ID : " << studentID << endl;
    cout << " Department : " << department << endl;
    cout << " Balance    : Rs. " << balance << endl;
    cout << "==================================\n";
}

// Return user role as string
string Student::getUserRole() const {
    return "Student";
}

// Add fee to student's balance
void Student::addFee(double amount) {
    balance += amount;
}

// Process payment and deduct from balance
void Student::makePayment(double amount) {
    if (amount <= balance) {
        balance -= amount;
        printSuccess("Payment of Rs." + to_string(amount) + " received. Remaining balance: Rs." + to_string(balance) + "\n");
    } else {
        printError("Insufficient balance. Please pay full amount.\n");
    }
}

// Overloaded += operator to add amount to balance
Student& Student::operator+=(double amount) {
    balance += amount;
    return *this;
}

// Overloaded -= operator to subtract amount from balance
Student& Student::operator-=(double amount) {
    if (amount <= balance) {
        balance -= amount;
    }
    return *this;
}

// ========== ADMIN CLASS IMPLEMENTATION ==========
// Admin class inheriting from User, representing system administrators
Admin::Admin() : User(), adminCode(""), accessLevel(1) {}

// Parameterized constructor for Admin
Admin::Admin(int id, string n, string e, string pwd, string code, int level) : User(id, n, e, pwd, "Admin"), adminCode(code), accessLevel(level) {}

Admin::~Admin() {}

// Getter methods for admin-specific attributes
string Admin::getAdminCode() const { return adminCode; }
int Admin::getAccessLevel() const { return accessLevel; }

// Display admin information
void Admin::displayInfo() const {
    cout << "Admin - ID: " << userID << ", Name: " << name << ", Access Level: " << accessLevel;
}

// Return user role as string
string Admin::getUserRole() const {
    return "Admin";
}

// ========== DRIVER CLASS IMPLEMENTATION ==========
// Driver class inheriting from User, representing vehicle drivers
Driver::Driver() : User(), licenseNo(""), phoneNumber("") {}

// Parameterized constructor for Driver
Driver::Driver(int id, string n, string e, string pwd, string license, string phone) : User(id, n, e, pwd, "Driver"), licenseNo(license), phoneNumber(phone) {}

Driver::~Driver() {}

// Getter methods for driver-specific attributes
string Driver::getLicenseNo() const { return licenseNo; }
string Driver::getPhoneNumber() const { return phoneNumber; }

// Setter methods for driver attributes
void Driver::setLicenseNo(string license) { licenseNo = license; }
void Driver::setPhoneNumber(string phone) { phoneNumber = phone; }

// Display driver information
void Driver::displayInfo() const {
    cout << "Driver - ID: " << userID
         << ", Name: " << name
         << ", Email: " << email
         << ", License No: " << licenseNo
         << ", Phone: " << phoneNumber;
}

// Return user role as string
string Driver::getUserRole() const { return "Driver"; }

// ========== VEHICLE CLASS IMPLEMENTATION ==========
// Abstract base class for all vehicle types (Bus, Van)
Vehicle::Vehicle() : vehicleID(0), registrationNumber(""), capacity(0), model(""), assignedRouteID(-1) {}

// Parameterized constructor for Vehicle
Vehicle::Vehicle(int id, string regNo, int cap, string mdl) : vehicleID(id), registrationNumber(regNo), capacity(cap), model(mdl), assignedRouteID(-1) {}

Vehicle::~Vehicle() {}

// Getter methods for vehicle attributes
int Vehicle::getVehicleID() const { return vehicleID; }
string Vehicle::getRegistrationNumber() const { return registrationNumber; }
int Vehicle::getCapacity() const { return capacity; }
string Vehicle::getModel() const { return model; }
int Vehicle::getAssignedRouteID() const { return assignedRouteID; }
int Vehicle::getAvailableSeats() const { return capacity; }

// Setter methods for vehicle attributes
void Vehicle::setAssignedRouteID(int routeID) { assignedRouteID = routeID; }
void Vehicle::setCapacity(int cap) { capacity = cap; }

// Overloaded < operator to compare vehicle capacities with validation
bool Vehicle::operator<(const Vehicle& other) const {
    if (capacity > 150 || other.capacity > 150) {
        printError("Capacity cannot exceed 150.\n");
        return false;
    }
    return (capacity < other.capacity);
}

// Output stream operator for displaying vehicle information
ostream& operator<<(ostream& os, const Vehicle& vehicle) {
    os << "Vehicle ID: " << vehicle.vehicleID << ", Reg: " << vehicle.registrationNumber << ", Capacity: " << vehicle.capacity << ", Model: " << vehicle.model;
    return os;
}

// ========== BUS CLASS IMPLEMENTATION ==========
// Bus class inheriting from Vehicle, representing bus vehicles
Bus::Bus() : Vehicle(), numberOfDoors(2), hasAC(true) {}

// Parameterized constructor for Bus
Bus::Bus(int id, string regNo, int cap, string mdl, int doors, bool ac) : Vehicle(id, regNo, cap, mdl), numberOfDoors(doors), hasAC(ac) {}

Bus::~Bus() {}

// Return vehicle type as string
string Bus::getVehicleType() const { return "Bus"; }

// Calculate maintenance cost based on capacity with validation
double Bus::getMaintenanceCost() const {
    if (capacity > 150) {
        printError("Capacity cannot exceed 150.\n");
        return 0;
    }
    return capacity * 500;
}

// Display bus-specific information with validation
void Bus::displayVehicle() const {
    if (numberOfDoors > 2) {
        printError("Number of doors cannot exceed 2.\n");
        return;
    }
    cout << "Bus - " << registrationNumber << " | Capacity: " << capacity
         << " | AC: " << (hasAC ? "Yes" : "No") << " | Doors: " << numberOfDoors;
}

// ========== VAN CLASS IMPLEMENTATION ==========
// Van class inheriting from Vehicle, representing van vehicles
Van::Van() : Vehicle(), cargoSpace(0), isHighRoof(false) {}

// Parameterized constructor for Van
Van::Van(int id, string regNo, int cap, string mdl, int cargo, bool roof) : Vehicle(id, regNo, cap, mdl), cargoSpace(cargo), isHighRoof(roof) {}

Van::~Van() {}

// Return vehicle type as string
string Van::getVehicleType() const { return "Van"; }

// Calculate maintenance cost for van
double Van::getMaintenanceCost() const { return capacity * 300; }

// Display van-specific information
void Van::displayVehicle() const {
    cout << "Van - " << registrationNumber << " | Capacity: " << capacity << " | Cargo Space: " << cargoSpace << " cu ft | High Roof: " << (isHighRoof ? "Yes" : "No");
}

// ========== ROUTE CLASS IMPLEMENTATION ==========
// Route class managing travel routes and student assignments
Route::Route() : routeID(0), startPoint(""), endPoint(""), distance(0), fare(0), assignedVehicle(nullptr), currentOccupancy(0), maxStudents(100) {
    // Dynamic allocation for student IDs array
    studentIDs = new int[maxStudents];
    // Initialize all entries to -1 (empty)
    for (int i = 0; i < maxStudents; i++) studentIDs[i] = -1;
}

// Parameterized constructor for Route
Route::Route(int id, string start, string end, double dist, double f): routeID(id), startPoint(start), endPoint(end), distance(dist), fare(f), assignedVehicle(nullptr), currentOccupancy(0), maxStudents(100) {
    studentIDs = new int[maxStudents];
    for (int i = 0; i < maxStudents; i++) studentIDs[i] = -1;
}

// Destructor to free dynamically allocated memory
Route::~Route() {
    delete[] studentIDs;
}

// Copy constructor for deep copy
Route::Route(const Route& other) {
    routeID = other.routeID;
    startPoint = other.startPoint;
    endPoint = other.endPoint;
    distance = other.distance;
    fare = other.fare;
    assignedVehicle = other.assignedVehicle;
    currentOccupancy = other.currentOccupancy;
    maxStudents = other.maxStudents;
    
    // Deep copy of student IDs array
    studentIDs = new int[maxStudents];
    for (int i = 0; i < maxStudents; i++) {
        studentIDs[i] = other.studentIDs[i];
    }
}

// Assignment operator overload for deep copy
Route& Route::operator=(const Route& other) {
    if (this != &other) {
        delete[] studentIDs;
        
        routeID = other.routeID;
        startPoint = other.startPoint;
        endPoint = other.endPoint;
        distance = other.distance;
        fare = other.fare;
        assignedVehicle = other.assignedVehicle;
        currentOccupancy = other.currentOccupancy;
        maxStudents = other.maxStudents;
        
        studentIDs = new int[maxStudents];
        for (int i = 0; i < maxStudents; i++) {
            studentIDs[i] = other.studentIDs[i];
        }
    }
    return *this;
}

// Getter methods for route attributes
int Route::getRouteID() const { return routeID; }
string Route::getStartPoint() const { return startPoint; }
string Route::getEndPoint() const { return endPoint; }
double Route::getDistance() const { return distance; }
double Route::getFare() const { return fare; }
Vehicle* Route::getAssignedVehicle() const { return assignedVehicle; }
int Route::getCurrentOccupancy() const { return currentOccupancy; }

// Assign vehicle to route and adjust capacity if needed
void Route::setAssignedVehicle(Vehicle* vehicle) {
    assignedVehicle = vehicle;
    if (vehicle && vehicle->getCapacity() < maxStudents) {
        maxStudents = vehicle->getCapacity();
    }
}

// Set fare for the route
void Route::setFare(double f) { fare = f; }

// Add student to route if seats are available
bool Route::addStudent(int studentID) {
    if (!hasAvailableSeats()) {
        printError("No seats available on this route!\n");
        return false;
    }
    
    // Find first empty slot and add student
    for (int i = 0; i < maxStudents; i++) {
        if (studentIDs[i] == -1) {
            studentIDs[i] = studentID;
            currentOccupancy++;
            return true;
        }
    }
    return false;
}

// Remove student from route
bool Route::removeStudent(int studentID) {
    for (int i = 0; i < maxStudents; i++) {
        if (studentIDs[i] == studentID) {
            studentIDs[i] = -1;
            currentOccupancy--;
            return true;
        }
    }
    return false;
}

// Check if student is registered on this route
bool Route::isStudentRegistered(int studentID) const {
    for (int i = 0; i < maxStudents; i++) {
        if (studentIDs[i] == studentID) {
            return true;
        }
    }
    return false;
}

// Check if there are available seats on the route
bool Route::hasAvailableSeats() const {
    return currentOccupancy < maxStudents;
}

// Display detailed route information
void Route::displayRoute() const {
    cout << "\n=========================================\n";
    cout << "            ROUTE DETAILS\n";
    cout << "=========================================\n";
    cout << " Route ID        : " << routeID << endl;
    cout << " Start Point     : " << startPoint << endl;
    cout << " Destination     : " << endPoint << endl;
    cout << " Distance        : " << distance << " km" << endl;
    cout << " Fare            : Rs. " << fare << endl;
    cout << " Occupancy       : " << currentOccupancy << "/" << maxStudents << endl;
    if (assignedVehicle) {
        cout << " Assigned Vehicle: " << assignedVehicle->getRegistrationNumber() << endl;
    } else {
        cout << " Assigned Vehicle: None" << endl;
    }
    cout << "=========================================\n";
}

// Equality operator to compare routes by ID
bool Route::operator==(const Route& other) const {
    return (routeID == other.routeID);
}

// Output stream operator for route information
ostream& operator<<(ostream& os, const Route& route) {
    os << "Route ID: " << route.routeID << ", " << route.startPoint << " to " << route.endPoint << ", Fare: Rs." << route.fare;
    return os;
}

// ========== BILL CLASS IMPLEMENTATION ==========
// Bill class for managing student fee bills
Bill::Bill() : billID(0), studentID(0), amount(0), lateFee(0), isPaid(false), dueDate(""), issueDate("") {}

// Parameterized constructor for Bill
Bill::Bill(int id, int stuID, double amt, string issue, string due) : billID(id), studentID(stuID), amount(amt), lateFee(0), isPaid(false), issueDate(issue), dueDate(due) {}

Bill::~Bill() {}

// Getter methods for bill attributes
int Bill::getBillID() const { return billID; }
int Bill::getStudentID() const { return studentID; }
double Bill::getTotalAmount() const { return amount + lateFee; }
bool Bill::getIsPaid() const { return isPaid; }
string Bill::getDueDate() const { return dueDate; }

// Setter methods for bill attributes
void Bill::setLateFee(double fee) { lateFee = fee; }
void Bill::markAsPaid() { isPaid = true; }
void Bill::setAmount(double amt) { amount = amt; }

// Calculate late fee based on current date
void Bill::calculateLateFee(string currentDate) {
    if (!isPaid && currentDate > dueDate) {
        lateFee = amount * 0.10; // 10% late fee
    }
}

// Display bill information
void Bill::displayBill() const {
    cout << "\n========== BILL ==========" << endl;
    cout << "Bill ID: " << billID << endl;
    cout << "Student ID: " << studentID << endl;
    cout << "Base Amount: Rs." << amount << endl;
    if (lateFee > 0) {
        cout << "Late Fee: Rs." << lateFee << endl;
    }
    cout << "Total Amount: Rs." << (amount + lateFee) << endl;
    cout << "Status: " << (isPaid ? "PAID" : "UNPAID") << endl;
    cout << "Due Date: " << dueDate << endl;
    cout << "===========================\n";
}

// Greater than operator to compare bill amounts
bool Bill::operator>(const Bill& other) const {
    return (amount + lateFee) > (other.amount + other.lateFee);
}

// Output stream operator for bill information
ostream& operator<<(ostream& os, const Bill& bill) {
    os << "Bill " << bill.billID << ": Rs." << (bill.amount + bill.lateFee) << " - " << (bill.isPaid ? "Paid" : "Unpaid");
    return os;
}

// ========== TRANSPORT MANAGER CLASS IMPLEMENTATION ==========
// Main management class handling all system operations
TransportManager::TransportManager() : userCount(0), userCapacity(10), vehicleCount(0), vehicleCapacity(10), routeCount(0), routeCapacity(10), billCount(0), billCapacity(10), nextUserID(100), nextVehicleID(1), nextRouteID(1), nextBillID(1) {
    // Dynamic allocation for all collections
    users = new User*[userCapacity];
    vehicles = new Vehicle*[vehicleCapacity];
    routes = new Route*[routeCapacity];
    bills = new Bill*[billCapacity];
    
    // Initialize all pointers to nullptr
    for (int i = 0; i < userCapacity; i++) users[i] = nullptr;
    for (int i = 0; i < vehicleCapacity; i++) vehicles[i] = nullptr;
    for (int i = 0; i < routeCapacity; i++) routes[i] = nullptr;
    for (int i = 0; i < billCapacity; i++) bills[i] = nullptr;
    
    // Load existing data from file
    loadData();
}

// Destructor to clean up all dynamically allocated memory
TransportManager::~TransportManager() {
    saveData(); // Save data before exit
    
    // Delete all objects in collections
    for (int i = 0; i < userCount; i++) delete users[i];
    for (int i = 0; i < vehicleCount; i++) delete vehicles[i];
    for (int i = 0; i < routeCount; i++) delete routes[i];
    for (int i = 0; i < billCount; i++) delete bills[i];
    
    // Delete array pointers
    delete[] users;
    delete[] vehicles;
    delete[] routes;
    delete[] bills;
}

// Register new user with dynamic array resizing
bool TransportManager::registerUser(User* user) {
    // Resize if capacity is reached
    if (userCount >= userCapacity) {
        userCapacity *= 2;
        User** newUsers = new User*[userCapacity];
        for (int i = 0; i < userCount; i++) newUsers[i] = users[i];
        delete[] users;
        users = newUsers;
    }
    users[userCount++] = user;
    nextUserID++;
    return true;
}

// Authenticate user login
User* TransportManager::login(string email, string password) {
    for (int i = 0; i < userCount; i++) {
        if (users[i]->getEmail() == email && users[i]->getPassword() == password) {
            return users[i];
        }
    }
    return nullptr;
}

// Retrieve student by user ID
Student* TransportManager::getStudent(int userID) {
    for (int i = 0; i < userCount; i++) {
        if (users[i]->getUserID() == userID && users[i]->getUserType() == "Student") {
            return dynamic_cast<Student*>(users[i]);
        }
    }
    return nullptr;
}

// Retrieve driver by user ID
Driver* TransportManager::getDriver(int userID) {
    for (int i = 0; i < userCount; i++) {
        if (users[i]->getUserID() == userID && users[i]->getUserType() == "Driver") {
            return dynamic_cast<Driver*>(users[i]);
        }
    }
    return nullptr;
}

// Add new vehicle with dynamic array resizing
void TransportManager::addVehicle(Vehicle* vehicle) {
    if (vehicleCount >= vehicleCapacity) {
        vehicleCapacity *= 2;
        Vehicle** newVehicles = new Vehicle*[vehicleCapacity];
        for (int i = 0; i < vehicleCount; i++) newVehicles[i] = vehicles[i];
        delete[] vehicles;
        vehicles = newVehicles;
    }
    vehicles[vehicleCount++] = vehicle;
    nextVehicleID++;
}

// Update vehicle information
void TransportManager::updateVehicle(int vehicleID, string regNo, int capacity) {
    for (int i = 0; i < vehicleCount; i++) {
        if (vehicles[i]->getVehicleID() == vehicleID) {
            printSuccess("Vehicle updated successfully!\n");
            return;
        }
    }
    printError("Vehicle not found!\n");
}

// Remove vehicle from system
void TransportManager::removeVehicle(int vehicleID) {
    for (int i = 0; i < vehicleCount; i++) {
        if (vehicles[i]->getVehicleID() == vehicleID) {
            delete vehicles[i];
            // Shift remaining vehicles
            for (int j = i; j < vehicleCount - 1; j++) {
                vehicles[j] = vehicles[j + 1];
            }
            vehicleCount--;
            printSuccess("Vehicle removed successfully!\n");
            return;
        }
    }
    printError("Vehicle not found!\n");
}

// Display all vehicles in system
void TransportManager::displayAllVehicles() const {
    if (vehicleCount == 0) {
        printError("No vehicles available.\n");
        return;
    }
    printBorder();
    cout << "\n========== VEHICLES ==========\n";
    resetColor();
    for (int i = 0; i < vehicleCount; i++) {
        vehicles[i]->displayVehicle();
        cout << endl;
    }
    printBorder();
    cout << "===============================\n";
    resetColor();
}

// Get vehicle by ID
Vehicle* TransportManager::getVehicle(int vehicleID) const {
    for (int i = 0; i < vehicleCount; i++) {
        if (vehicles[i]->getVehicleID() == vehicleID) {
            return vehicles[i];
        }
    }
    return nullptr;
}

// Add new route with dynamic array resizing
void TransportManager::addRoute(Route* route) {
    if (routeCount >= routeCapacity) {
        routeCapacity *= 2;
        Route** newRoutes = new Route*[routeCapacity];
        for (int i = 0; i < routeCount; i++) newRoutes[i] = routes[i];
        delete[] routes;
        routes = newRoutes;
    }
    routes[routeCount++] = route;
    nextRouteID++;
}

// Assign vehicle to specific route
void TransportManager::assignVehicleToRoute(int routeID, int vehicleID) {
    Route* route = getRoute(routeID);
    Vehicle* vehicle = getVehicle(vehicleID);
    
    if (route && vehicle) {
        route->setAssignedVehicle(vehicle);
        vehicle->setAssignedRouteID(routeID);
        printSuccess("Vehicle assigned to route successfully!\n");
    } else {
        printError("Invalid route or vehicle ID!\n");
    }
}

// Display all routes in system
void TransportManager::displayAllRoutes() const {
    if (routeCount == 0) {
        printError("No routes available.\n");
        return;
    }
    for (int i = 0; i < routeCount; i++) {
        routes[i]->displayRoute();
    }
}

// Get route by ID
Route* TransportManager::getRoute(int routeID) const {
    for (int i = 0; i < routeCount; i++) {
        if (routes[i]->getRouteID() == routeID) {
            return routes[i];
        }
    }
    return nullptr;
}

// Apply for transport service
bool TransportManager::applyForTransport(int studentID, int routeID) {
    Student* student = getStudent(studentID);
    Route* route = getRoute(routeID);
    
    if (!student || !route) {
        printError("Invalid student or route!\n");
        return false;
    }
    
    if (student->getHasTransport()) {
        printError("Student already has transport registration!\n");
        return false;
    }
    
    if (!route->hasAvailableSeats()) {
        printError("No seats available on this route!\n");
        return false;
    }
    
    route->addStudent(studentID);
    student->setHasTransport(true);
    student->setAssignedRouteID(routeID);
    
    generateBill(studentID);
    
    printSuccess("Application submitted and approved successfully!\n");
    return true;
}

// Approve student registration
bool TransportManager::approveRegistration(int studentID, int routeID) {
    Student* student = getStudent(studentID);
    Route* route = getRoute(routeID);
    
    if (!student || !route) return false;
    
    if (route->addStudent(studentID)) {
        student->setHasTransport(true);
        student->setAssignedRouteID(routeID);
        generateBill(studentID);
        return true;
    }
    return false;
}

// Cancel student's transport registration
bool TransportManager::cancelRegistration(int studentID) {
    Student* student = getStudent(studentID);
    if (!student || !student->getHasTransport()) {
        printError("Student does not have active transport registration!\n");
        return false;
    }
    
    Route* route = getRoute(student->getAssignedRouteID());
    if (route) {
        route->removeStudent(studentID);
    }
    
    student->setHasTransport(false);
    student->setAssignedRouteID(-1);
    
    printSuccess("Registration cancelled successfully!\n");
    return true;
}

// View all transport applications
void TransportManager::viewApplications() {
    printBorder();
    cout << "\nStudents with transport applications:\n";
    resetColor();
    bool found = false;
    for (int i = 0; i < userCount; i++) {
        if (users[i]->getUserType() == "Student") {
            Student* s = dynamic_cast<Student*>(users[i]);
            if (s && !s->getHasTransport()) {
                s->displayInfo();
                found = true;
            }
        }
    }
    if (!found) {
        printInfo("No pending applications.\n");
    }
}

// Generate bill for student
void TransportManager::generateBill(int studentID) {
    Student* student = getStudent(studentID);
    Route* route = getRoute(student->getAssignedRouteID());
    
    if (student && route) {
        Bill* bill = new Bill(nextBillID++, studentID, route->getFare(), "2024-01-01", "2024-01-31");
        
        // Resize bill array if needed
        if (billCount >= billCapacity) {
            billCapacity *= 2;
            Bill** newBills = new Bill*[billCapacity];
            for (int i = 0; i < billCount; i++) newBills[i] = bills[i];
            delete[] bills;
            bills = newBills;
        }
        bills[billCount++] = bill;
        
        student->addFee(route->getFare());
        printSuccess("Bill generated for student " + to_string(studentID) + " - Amount: Rs." + to_string(route->getFare()) + "\n");
    }
}

// Apply late fees to unpaid bills
void TransportManager::applyLateFees() {
    string currentDate = "2024-02-15";
    for (int i = 0; i < billCount; i++) {
        if (!bills[i]->getIsPaid()) {
            bills[i]->calculateLateFee(currentDate);
        }
    }
    printSuccess("Late fees applied successfully!\n");
}

// Process payment from student
void TransportManager::makePayment(int studentID, double amount) {
    for (int i = 0; i < billCount; i++) {
        if (bills[i]->getStudentID() == studentID && !bills[i]->getIsPaid()) {
            Student* student = getStudent(studentID);
            if (student) {
                student->makePayment(amount);
                if (student->getBalance() <= 0) {
                    bills[i]->markAsPaid();
                }
                printSuccess("Payment processed successfully!\n");
                return;
            }
        }
    }
    printError("No pending bill found for student!\n");
}

// Generate revenue report
void TransportManager::generateRevenueReport() const {
    double totalRevenue = 0;
    int paidCount = 0;
    int pendingCount = 0;
    
    printBorder();
    cout << "\n========== REVENUE REPORT ==========\n";
    resetColor();
    for (int i = 0; i < billCount; i++) {
        if (bills[i]->getIsPaid()) {
            totalRevenue += bills[i]->getTotalAmount();
            paidCount++;
        } else {
            pendingCount++;
        }
    }
    
    cout << "Total Revenue Collected: Rs." << totalRevenue << endl;
    cout << "Paid Bills: " << paidCount << endl;
    cout << "Pending Bills: " << pendingCount << endl;
    printBorder();
    cout << "=====================================\n";
    resetColor();
}

// Generate route usage report
void TransportManager::generateRouteUsageReport() const {
    printBorder();
    cout << "\n========== ROUTE USAGE REPORT ==========\n";
    resetColor();
    for (int i = 0; i < routeCount; i++) {
        routes[i]->displayRoute();
        int maxCap = (routes[i]->getAssignedVehicle() ? routes[i]->getAssignedVehicle()->getCapacity() : 100);
        double usage = (routes[i]->getCurrentOccupancy() * 100.0 / maxCap);
        cout << "Usage Percentage: " << usage << "%" << endl;
        cout << "-------------------------------------\n";
    }
}

// Display all students in system
void TransportManager::displayAllStudents() const {
    printBorder();
    cout << "\n========== ALL STUDENTS ==========\n";
    resetColor();
    for (int i = 0; i < userCount; i++) {
        if (users[i]->getUserType() == "Student") {
            users[i]->displayInfo();
        }
    }
    printBorder();
    cout << "===================================\n";
    resetColor();
}

// Display all drivers in system
void TransportManager::displayAllDrivers() const {
    printBorder();
    cout << "\n========== ALL DRIVERS ==========\n";
    resetColor();
    for (int i = 0; i < userCount; i++) {
        if (users[i]->getUserType() == "Driver") {
            users[i]->displayInfo();
            cout << endl;
        }
    }
    printBorder();
    cout << "==================================\n";
    resetColor();
}

// View route assigned to driver
void TransportManager::viewAssignedRoute(int driverID) const {
    for (int i = 0; i < routeCount; i++) {
        Vehicle* v = routes[i]->getAssignedVehicle();
        if (v && v->getVehicleID() == driverID) {
            printInfo("Driver assigned to route:\n");
            routes[i]->displayRoute();
            return;
        }
    }
    printError("No route assigned to this driver.\n");
}

// View students on driver's route
void TransportManager::viewStudentListOnRoute(int driverID) const {
    for (int i = 0; i < routeCount; i++) {
        Vehicle* v = routes[i]->getAssignedVehicle();
        if (v && v->getVehicleID() == driverID) {
            printInfo("\nStudents on Route " + to_string(routes[i]->getRouteID()) + ":\n");
            printInfo("Student list feature - requires student tracking\n");
            return;
        }
    }
    printError("No route assigned to this driver.\n");
}

// Load data from file
void TransportManager::loadData() {
    ifstream file("transport_data.txt");
    if (!file.is_open()) {
        printInfo("No existing data file found. Starting with fresh system.\n");
        file.close();
        
        // Create default admin if no users exist
        if (userCount == 0) {
            Admin* defaultAdmin = new Admin(nextUserID++, "Admin", "admin@university.edu", "admin123", "ADMIN001", 5);
            registerUser(defaultAdmin);
            printInfo("Default admin created! Email: admin@university.edu, Password: admin123\n");
        }
        return;
    }
    
    file.close();
    
    // Create default admin if no users exist
    if (userCount == 0) {
        Admin* defaultAdmin = new Admin(nextUserID++, "Admin", "admin@university.edu", "admin123", "ADMIN001", 5);
        registerUser(defaultAdmin);
    }
}

// Save data to file
void TransportManager::saveData() {
    ofstream file("transport_data.txt");

    if (!file.is_open()) {
        printError("Error: Could not save data to file!\n");
        return;
    }

    // ================= USERS =================
    file << "\n====================================\n";
    file << "            USERS DATA\n";
    file << "====================================\n";

    for (int i = 0; i < userCount; i++) {
        file << "ID        : " << users[i]->getUserID() << "\n"
             << "Name      : " << users[i]->getName() << "\n"
             << "Email     : " << users[i]->getEmail() << "\n"
             << "Password  : " << users[i]->getPassword() << "\n"
             << "User Type : " << users[i]->getUserType() << "\n"
             << "------------------------------------\n";
    }

    // ================= VEHICLES =================
    file << "\n====================================\n";
    file << "          VEHICLES DATA\n";
    file << "====================================\n";

    for (int i = 0; i < vehicleCount; i++) {
        file << "Vehicle ID   : " << vehicles[i]->getVehicleID() << "\n"
             << "Reg No       : " << vehicles[i]->getRegistrationNumber() << "\n"
             << "Capacity     : " << vehicles[i]->getCapacity() << "\n"
             << "Model        : " << vehicles[i]->getModel() << "\n"
             << "Type         : " << vehicles[i]->getVehicleType() << "\n"
             << "------------------------------------\n";
    }

    // ================= ROUTES =================
    file << "\n====================================\n";
    file << "           ROUTES DATA\n";
    file << "====================================\n";

    for (int i = 0; i < routeCount; i++) {
        file << "Route ID     : " << routes[i]->getRouteID() << "\n"
             << "Start Point  : " << routes[i]->getStartPoint() << "\n"
             << "End Point    : " << routes[i]->getEndPoint() << "\n"
             << "Distance     : " << routes[i]->getDistance() << " km\n"
             << "Fare         : Rs. " << routes[i]->getFare() << "\n"
             << "------------------------------------\n";
    }

    file.close();

    printSuccess("\n====================================\n");
    printSuccess(" Data saved successfully!\n");
    printSuccess(" File: transport_data.txt\n");
    printSuccess("====================================\n");
}

// ========== MAIN FUNCTION ==========
// Function prototypes for menu handlers
void showMainMenu();
void handleStudentMenu(TransportManager& manager, Student* student);
void handleAdminMenu(TransportManager& manager, Admin* admin);
void handleDriverMenu(TransportManager& manager, Driver* driver);

int main() {
    TransportManager manager;
    int choice;
    bool running = true;
    
    // Display system header
    printBorder();
    cout << "\n========================================" << endl;
    cout << "  UNIVERSITY TRANSPORT MANAGEMENT SYSTEM" << endl;
    cout << "========================================" << endl;
    resetColor();
    cout << "         Object Oriented Programming    " << endl;
    cout << "               2025-SE-512              " << endl;
    cout << "                 and                     " << endl;
    cout << "               2025-SE-485               " << endl;
    printBorder();
    cout << "========================================" << endl;
    resetColor();
    
    // Main program loop
    while (running) {
        showMainMenu();
        cout << "Enter your choice: ";

        // Input validation for numeric choice
        while (!(cin >> choice)) {
            printError("Error: Only digits are allowed. Try again: ");
            cin.clear(); 
            cin.ignore(10000, '\n');
        } 
        
        switch (choice) {
            case 1: {  // User Registration
                int userType;

                printBorder();
                cout << "\n=====================================\n";
                cout << "        USER REGISTRATION\n";
                cout << "=====================================\n";
                resetColor();
                cout << " Select User Type:\n";
                cout << "-------------------------------------\n";
                cout << "  1. Student\n";
                cout << "  2. Admin\n";
                cout << "  3. Driver\n";
                cout << " Enter your choice (1-3): ";
                cin >> userType;
                printBorder();
                cout << "=====================================\n";
                resetColor();

                string name, email, password;

                cout << "Enter Name (alphabets only): ";
                cin.ignore();
                getline(cin, name);

                // Validate name (only alphabets and spaces)
                for (int i = 0; i < name.length(); i++) {
                    if (!isalpha(name[i]) && name[i] != ' ') {
                        printError("Error: Name should contain only alphabets!\n");
                        return 0;
                    }
                }

                cout << "Enter Email: ";
                getline(cin, email);

                cout << "Enter Password (numbers only): ";
                getline(cin, password);

                // Validate password (only digits)
                for (int i = 0; i < password.length(); i++) {
                    if (!isdigit(password[i])) {
                        printError("Error: Password should contain only numbers!\n");
                        return 0;
                    }
                }
                
                if (userType == 1) {  // Student registration
                    string studentID, department;
                    cout << "Enter Student ID (numbers): ";
                    getline(cin, studentID);
                    cout << "Enter Department (alphabets only): ";
                    getline(cin, department);

                    // Validate department (only alphabets and spaces)
                    for (int i = 0; i < department.length(); i++) {
                        if (!isalpha(department[i]) && department[i] != ' ') {
                            printError("Error: Department should contain only alphabets!\n");
                            return 0;
                        }
                    }

                    Student* student = new Student(manager.getNextUserID(), name, email, password, studentID, department);
                    if (manager.registerUser(student)) {
                        printSuccess("Student registered successfully!\n");
                        cout << "Your User ID is: " << manager.getNextUserID() - 1 << endl;
                    }
                } else if (userType == 2) {  // Admin registration
                    string adminCode;
                    int accessLevel;
                    cout << "Enter Admin Code (numbers): ";
                    getline(cin, adminCode);
                    cout << "Enter Access Level (1-5): ";
                    cin >> accessLevel;
                    
                    Admin* admin = new Admin(manager.getNextUserID(), name, email, password, adminCode, accessLevel);
                    if (manager.registerUser(admin)) {
                        printSuccess("Admin registered successfully!\n");
                        cout << "Your User ID is: " << manager.getNextUserID() - 1 << endl;
                    }
                } else if (userType == 3) {  // Driver registration
                    string licenseNo, phoneNumber;
                    cout << "Enter License Number: ";
                    getline(cin, licenseNo);
                    cout << "Enter Phone Number : ";
                    getline(cin, phoneNumber);
                    
                    Driver* driver = new Driver(manager.getNextUserID(), name, email, password, licenseNo, phoneNumber);
                    if (manager.registerUser(driver)) {
                        printSuccess("Driver registered successfully!\n");
                        cout << "Your User ID is: " << manager.getNextUserID() - 1 << endl;
                    }
                }
                break;
            }
            case 2: {  // Login
                string email, password;
                printBorder();
                cout << "\nLogin\n";
                resetColor();
                cout << "Email: ";
                cin >> email;
                cout << "Password: ";
                cin >> password;
                
                User* user = manager.login(email, password);
                if (user) {
                    printSuccess("Login successful! Welcome " + user->getName() + "\n");
                    
                    // Route to appropriate menu based on user type
                    if (user->getUserType() == "Student") {
                        handleStudentMenu(manager, dynamic_cast<Student*>(user));
                    } else if (user->getUserType() == "Admin") {
                        handleAdminMenu(manager, dynamic_cast<Admin*>(user));
                    } else if (user->getUserType() == "Driver") {
                        handleDriverMenu(manager, dynamic_cast<Driver*>(user));
                    }
                } else {
                    printError("Invalid email or password!\n");
                }
                break;
            }
            case 3:  // Exit
                printInfo("Saving data and exiting system...\n");
                manager.saveData();
                running = false;
                break;
            default:
                printError("Invalid choice! Please try again.\n");
        }
        
        if (running) {
            cout << "\nPress Enter to continue...";
            cin.ignore();
            cin.get();
        }
    }
    
    printSuccess("\nThank you for using University Transport Management System!\n");
    return 0;
}

// Display main menu options
void showMainMenu() {
    printBorder();
    cout << "\n========== MAIN MENU ==========\n";
    resetColor();
    cout << "1. Register User" << endl;
    cout << "2. Login" << endl;
    cout << "3. Exit" << endl;
    printBorder();
    cout << "================================\n";
    resetColor();
}

// Handle student-specific menu options
void handleStudentMenu(TransportManager& manager, Student* student) {
    int choice;
    bool loggedIn = true;
    
    while (loggedIn) {
        printBorder();
        cout << "\n========== STUDENT MENU ==========\n";
        resetColor();
        cout << "Welcome, " << student->getName() << endl;
        cout << "1. View All Routes" << endl;
        cout << "2. Apply for Transport" << endl;
        cout << "3. View My Registration" << endl;
        cout << "4. Cancel Registration" << endl;
        cout << "5. View My Balance" << endl;
        cout << "6. Make Payment" << endl;
        cout << "7. Logout" << endl;
        printBorder();
        cout << "===================================\n";
        resetColor();
        cout << "Enter your choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1:  // View all routes
                manager.displayAllRoutes();
                break;
            case 2:  // Apply for transport
                if (student->getHasTransport()) {
                    printError("You already have active transport registration!\n");
                    break;
                }
                manager.displayAllRoutes();
                int routeID;
                cout << "Enter Route ID to apply: ";
                cin >> routeID;
                manager.applyForTransport(student->getUserID(), routeID);
                break;
            case 3:  // View registration
                if (student->getHasTransport()) {
                    printInfo("You are registered for route ID: " + to_string(student->getAssignedRouteID()) + "\n");
                    Route* route = manager.getRoute(student->getAssignedRouteID());
                    if (route) {
                        route->displayRoute();
                    }
                } else {
                    printError("You are not registered for any transport service.\n");
                }
                break;
            case 4:  // Cancel registration
                manager.cancelRegistration(student->getUserID());
                break;
            case 5:  // View balance
                cout << "Your current balance: Rs." << student->getBalance() << endl;
                break;
            case 6:  // Make payment
                double amount;
                cout << "Enter amount to pay: Rs.";
                cin >> amount;
                manager.makePayment(student->getUserID(), amount);
                break;
            case 7:  // Logout
                loggedIn = false;
                printSuccess("Logged out successfully!\n");
                break;
            default:
                printError("Invalid choice!\n");
        }
        
        if (loggedIn) {
            cout << "\nPress Enter to continue...";
            cin.ignore();
            cin.get();
        }
    }
}

// Handle admin-specific menu options
void handleAdminMenu(TransportManager& manager, Admin* admin) {
    int choice;
    bool loggedIn = true;
    
    while (loggedIn) {
        printBorder();
        cout << "\n========== ADMIN MENU ==========\n";
        resetColor();
        cout << "Welcome, " << admin->getName() << " (Access Level: " << admin->getAccessLevel() << ")" << endl;
        cout << "1. Add Vehicle" << endl;
        cout << "2. Update Vehicle" << endl;
        cout << "3. Remove Vehicle" << endl;
        cout << "4. Add Route" << endl;
        cout << "5. Assign Vehicle to Route" << endl;
        cout << "6. View All Applications" << endl;
        cout << "7. Approve/Reject Requests" << endl;
        cout << "8. Generate Revenue Report" << endl;
        cout << "9. Generate Route Usage Report" << endl;
        cout << "10. View All Vehicles" << endl;
        cout << "11. View All Routes" << endl;
        cout << "12. View All Students" << endl;
        cout << "13. View All Drivers" << endl;
        cout << "14. Apply Late Fees" << endl;
        cout << "15. Save Data" << endl;
        cout << "16. Logout" << endl;
        printBorder();
        cout << "=================================\n";
        resetColor();
        cout << "Enter your choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1: {  // Add Vehicle
                int vehicleType;

                printBorder();
                cout << "\n=================================\n";
                cout << "         VEHICLE TYPE\n";
                cout << "=================================\n";
                resetColor();
                cout << "  1. Bus\n";
                cout << "  2. Van\n";
                cout << "---------------------------------\n";
                cout << " Enter your choice (1-2): ";
                cin >> vehicleType;
                
                string regNo, model;
                int capacity;

                cout << "Enter Registration Number: ";
                cin >> regNo;
                cout << "Enter Model: ";
                cin >> model;

                // Validate capacity (max 120)
                do {
                    cout << "Enter Capacity (max 120): ";
                    cin >> capacity;
                    if (capacity > 120) {
                        printError("Error: Capacity cannot be more than 120. Try again.\n");
                    }
                } while (capacity > 120);

                if (vehicleType == 1) {  // Bus
                    int doors;
                    bool ac;
                    do {
                        cout << "Enter Number of Doors (1-2): ";
                        cin >> doors;
                        if (doors < 1 || doors > 2) {
                            printError("Error: Doors must be between 1 and 2.\n");
                        }
                    } while (doors < 1 || doors > 2);
                    cout << "Has AC (1 for Yes, 0 for No): ";
                    cin >> ac;
                    manager.addVehicle(new Bus(manager.getNextVehicleID(), regNo, capacity, model, doors, ac));
                } else {  // Van
                    int cargo;
                    bool highRoof;
                    cout << "Enter Cargo Space (cu ft): ";
                    cin >> cargo;
                    cout << "Has High Roof (1 for Yes, 0 for No): ";
                    cin >> highRoof;
                    manager.addVehicle(new Van(manager.getNextVehicleID(), regNo, capacity, model, cargo, highRoof));
                }
                printSuccess("Vehicle added successfully!\n");
                break;
            }
            case 2: {  // Update Vehicle
                int vehicleID;
                manager.displayAllVehicles();
                cout << "Enter Vehicle ID to edit: ";
                cin >> vehicleID;
                string regNo;
                int capacity;
                cout << "Enter new Registration Number: ";
                cin >> regNo;
                do {
                    cout << "Enter new Capacity (max 120): ";
                    cin >> capacity;
                    if (capacity > 120) {
                        printError("Error: Capacity cannot exceed 120. Try again.\n");
                    }
                } while (capacity > 120);
                manager.updateVehicle(vehicleID, regNo, capacity);
                break;
            }
            case 3: {  // Remove Vehicle
                int vehicleID;
                manager.displayAllVehicles();
                cout << "Enter Vehicle ID to remove: ";
                cin >> vehicleID;
                manager.removeVehicle(vehicleID);
                break;
            }
            case 4: {  // Add Route
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
                printSuccess("Route added successfully!\n");
                break;
            }
            case 5: {  // Assign Vehicle to Route
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
            case 6:  // View All Applications
                manager.viewApplications();
                break;
            case 7: {  // Approve/Reject Requests
                int studentID, routeID;
                cout << "Enter Student ID to approve: ";
                cin >> studentID;
                cout << "Enter Route ID: ";
                cin >> routeID;
                if (manager.approveRegistration(studentID, routeID)) {
                    printSuccess("Application approved successfully!\n");
                } else {
                    printError("Failed to approve application!\n");
                }
                break;
            }
            case 8:  // Generate Revenue Report
                manager.generateRevenueReport();
                break;
            case 9:  // Generate Route Usage Report
                manager.generateRouteUsageReport();
                break;
            case 10:  // View All Vehicles
                manager.displayAllVehicles();
                break;
            case 11:  // View All Routes
                manager.displayAllRoutes();
                break;
            case 12:  // View All Students
                manager.displayAllStudents();
                break;
            case 13:  // View All Drivers
                manager.displayAllDrivers();
                break;
            case 14:  // Apply Late Fees
                manager.applyLateFees();
                break;
            case 15:  // Save Data
                manager.saveData();
                break;
            case 16:  // Logout
                loggedIn = false;
                printSuccess("Logged out successfully!\n");
                break;
            default:
                printError("Invalid choice!\n");
        }
        
        if (loggedIn) {
            cout << "\nPress Enter to continue...";
            cin.ignore();
            cin.get();
        }
    }
}

// Handle driver-specific menu options
void handleDriverMenu(TransportManager& manager, Driver* driver) {
    int choice;
    bool loggedIn = true;
    
    while (loggedIn) {
        printBorder();
        cout << "\n========== DRIVER MENU ==========\n";
        resetColor();
        cout << "Welcome, " << driver->getName() << endl;
        cout << "1. View My Assigned Route" << endl;
        cout << "2. View Students on My Route" << endl;
        cout << "3. Update My Information" << endl;
        cout << "4. View All Routes" << endl;
        cout << "5. Logout" << endl;
        printBorder();
        cout << "==================================\n";
        resetColor();
        cout << "Enter your choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1:  // View My Assigned Route
                manager.viewAssignedRoute(driver->getUserID());
                break;
            case 2:  // View Students on My Route
                manager.viewStudentListOnRoute(driver->getUserID());
                break;
            case 3: {  // Update My Information
                string phone, license;
                cout << "Enter new Phone Number: ";
                cin >> phone;
                cout << "Enter new License Number: ";
                cin >> license;
                driver->setPhoneNumber(phone);
                driver->setLicenseNo(license);
                printSuccess("Information updated successfully!\n");
                break;
            }
            case 4:  // View All Routes
                manager.displayAllRoutes();
                break;
            case 5:  // Logout
                loggedIn = false;
                printSuccess("Logged out successfully!\n");
                break;
            default:
                printError("Invalid choice!\n");
        }
        
        if (loggedIn) {
            cout << "\nPress Enter to continue...";
            cin.ignore();
            cin.get();
        }
    }
}