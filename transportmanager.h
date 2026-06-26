#ifndef TRANSPORTMANAGER_H
#define TRANSPORTMANAGER_H

#include "User.h"
#include "Student.h"
#include "Admin.h"
#include "Driver.h"
#include "Vehicle.h"
#include "Route.h"
#include "Bill.h"

#include <string>
using namespace std;

class TransportManager {
private:
    User** users;
    int userCount;
    int userCapacity;

    Vehicle** vehicles; // Array of pointers to Vehicle objects
    int vehicleCount;
    int vehicleCapacity;

    Route** routes;
    int routeCount;
    int routeCapacity;

    Bill** bills;
    int billCount;
    int billCapacity;

    int nextUserID;
    int nextVehicleID;
    int nextRouteID;
    int nextBillID;

public:
    TransportManager();
    ~TransportManager();

    // User management
    bool registerUser(User* user);
    User* login(string email, string password);
    Student* getStudent(int userID);
    Driver* getDriver(int userID);

    // Vehicle management
    void addVehicle(Vehicle* vehicle);
    void updateVehicle(int vehicleID, string regNo, int capacity);
    void removeVehicle(int vehicleID);
    void displayAllVehicles() const;
    Vehicle* getVehicle(int vehicleID) const;

    // Route management
    void addRoute(Route* route);
    void assignVehicleToRoute(int routeID, int vehicleID);
    void displayAllRoutes() const;
    Route* getRoute(int routeID) const;

    // Transport registration
    bool applyForTransport(int studentID, int routeID);
    bool approveRegistration(int studentID, int routeID);
    bool cancelRegistration(int studentID);
    void viewApplications();

    // Billing
    void generateBill(int studentID);
    void applyLateFees();
    void makePayment(int studentID, double amount);

    // Reports
    void generateRevenueReport() const;
    void generateRouteUsageReport() const;
    void displayAllStudents() const;
    void displayAllDrivers() const;

    // Driver management
    void viewAssignedRoute(int driverID) const;
    void viewStudentListOnRoute(int driverID) const;
    
    // Admin: assign driver to route
    void assignDriverToRoute(int routeID, int driverID);


    // File handling
    void loadData();
    void saveData();

    // Counts for saveData()
    int countStudents() const;
    int countAdmins() const;
    int countDrivers() const;
    int countBuses() const;
    int countVans() const;
    int countActiveTransportStudents() const;

    // Getters for IDs
    int getNextUserID() const { return nextUserID; }
    int getNextVehicleID() const { return nextVehicleID; }
    int getNextRouteID() const { return nextRouteID; }
};


#endif

