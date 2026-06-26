#ifndef STUDENT_H
#define STUDENT_H

#include "User.h"
#include <string>
using namespace std;

class Student : public User {
private: 
    string studentID;
    string department;
    double balance;
    bool hasTransport;
    int assignedRouteID; // if hasTransport=true -> approved route; if false -> pending requested route


public:
    Student();
    Student(int id, string n, string e, string pwd, string stuID, string dept);
    ~Student();
    
    // Getters
    string getStudentID() const;
    string getDepartment() const;
    double getBalance() const;
    bool getHasTransport() const;
    int getAssignedRouteID() const;
    
    // Setters
    void setBalance(double bal);
    void setHasTransport(bool status);
    // In pending state: stores requested route id. In approved state: stores assigned route id.
    void setAssignedRouteID(int routeID);

    
    // Override virtual functions
    void displayInfo() const override;
    string getUserRole() const override;
    
    // Billing methods
    void addFee(double amount);
    void makePayment(double amount);
    
    // Operator overloading
    Student& operator+=(double amount);  // Add balance
    Student& operator-=(double amount);  // Deduct balance
};

#endif