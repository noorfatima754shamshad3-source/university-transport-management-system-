#ifndef ROUTE_H
#define ROUTE_H

#include <string>
#include "Vehicle.h"
using namespace std;

class Route {
private:
    int routeID;
    string startPoint;
    string endPoint;
    double distance;
    double fare;
    Vehicle* assignedVehicle;  // Aggregation relationship
    int assignedDriverID;     // Driver assigned to this route
    int currentOccupancy;

    int* studentIDs;  // Dynamic array for students on this route
    int maxStudents;

public:
    Route();
    Route(int id, string start, string end, double dist, double f);
    ~Route();
    
    // Getters
    int getRouteID() const;
    string getStartPoint() const;
    string getEndPoint() const;
    double getDistance() const;
    double getFare() const;
    Vehicle* getAssignedVehicle() const;
    int getCurrentOccupancy() const;
    int getAssignedDriverID() const;

    // Extra student-route getters (used by saveData())
    int getMaxStudents() const;
    int getStudentID(int index) const;


    
    // Setters
    void setAssignedVehicle(Vehicle* vehicle);
    void setAssignedDriverID(int driverID);
    void setFare(double f);

    
    // Student management
    bool addStudent(int studentID);
    bool removeStudent(int studentID);
    bool isStudentRegistered(int studentID) const;
    bool hasAvailableSeats() const;
    
    // Copy constructor
    Route(const Route& other);
    
    // Assignment operator
    Route& operator=(const Route& other);
    
    // Display
    void displayRoute() const;
    
    // Overloaded operators
    bool operator==(const Route& other) const;
    friend ostream& operator<<(ostream& os, const Route& route);
};

#endif