#ifndef BUS_H
#define BUS_H

#include "Vehicle.h"

class Bus : public Vehicle {
private:
    int numberOfDoors;
    bool hasAC;

public:
    Bus();
    Bus(int id, string regNo, int cap, string mdl, int doors, bool ac);
    ~Bus();
    
    string getVehicleType() const override;
    double getMaintenanceCost() const override;
    void displayVehicle() const override;

    // Extra getters (used by saveData())
    int getNumberOfDoors() const;
    bool getHasAC() const;
};


#endif