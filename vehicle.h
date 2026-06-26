#ifndef VEHICLE_H
#define VEHICLE_H

#include <string>
using namespace std;

// Abstract Base Class for Vehicle
class Vehicle {
protected:
    int vehicleID;
    string registrationNumber;
    int capacity;
    string model;
    int assignedRouteID;

public:
    Vehicle();
    Vehicle(int id, string regNo, int cap, string mdl);
    virtual ~Vehicle();
    
    // Getters
    int getVehicleID() const;
    string getRegistrationNumber() const;
    int getCapacity() const;
    string getModel() const;
    int getAssignedRouteID() const;
    int getAvailableSeats() const;
    
    // Setters
    void setAssignedRouteID(int routeID);
    void setCapacity(int cap);
    
    // Pure virtual functions
    virtual string getVehicleType() const = 0;
    virtual double getMaintenanceCost() const = 0;
    virtual void displayVehicle() const = 0;
    
    // Overloaded operators
    bool operator<(const Vehicle& other) const;
    friend ostream& operator<<(ostream& os, const Vehicle& vehicle);
};

#endif