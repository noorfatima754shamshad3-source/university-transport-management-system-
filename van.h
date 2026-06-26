#ifndef VAN_H
#define VAN_H

#include "Vehicle.h"

class Van : public Vehicle {
private:
    int cargoSpace;
    bool isHighRoof;

public:
    Van();
    Van(int id, string regNo, int cap, string mdl, int cargo, bool roof);
    ~Van();
    
    string getVehicleType() const override;
    double getMaintenanceCost() const override;
    void displayVehicle() const override;

    // Extra getters (used by saveData())
    int getCargoSpace() const;
    bool getIsHighRoof() const;
};


#endif