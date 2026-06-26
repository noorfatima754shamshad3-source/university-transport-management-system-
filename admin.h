#ifndef ADMIN_H
#define ADMIN_H

#include "User.h"
#include <string>
using namespace std;

class Admin : public User {
private:
    string adminCode;
    int accessLevel;

public:
    Admin();
    Admin(int id, string n, string e, string pwd, string code, int level);
    ~Admin();
    
    string getAdminCode() const;
    int getAccessLevel() const;
    
    void displayInfo() const override;
    string getUserRole() const override;
};

#endif