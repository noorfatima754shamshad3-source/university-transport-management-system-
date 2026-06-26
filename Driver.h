#ifndef DRIVER_H
#define DRIVER_H

#include "User.h"
#include <string>

using namespace std;

class Driver : public User {
private:
    // Using LicenseNo as unique identifier as requested
    string licenseNo;
    string phoneNumber;

public:
    Driver();
    Driver(int id, string n, string e, string pwd, string license, string phone);
    ~Driver();

    string getLicenseNo() const;
    string getPhoneNumber() const;

    void setLicenseNo(string license);
    void setPhoneNumber(string phone);

    void displayInfo() const override;
    string getUserRole() const override;
};

#endif

