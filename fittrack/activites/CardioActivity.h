#pragma once
#include "Activity.h"

class CardioActivity: public Activity{
private:
    double distance; // in km

public:
    CardioActivity(const std::string& date, double dur, double cal, double dist);
    double getDistance() const;
    std::string getType() const;
    std::string describe() const;
    
    CardioActivity& operator=(const CardioActivity& other);
    friend std::ostream& operator<<(std::ostream& out, const CardioActivity& ca);
    friend std::istream& operator>>(std::istream& in, CardioActivity& ca);
};