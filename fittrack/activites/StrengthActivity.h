#pragma once
#include "Activity.h"

class StrengthActivity: public Activity{
private:
    int sets;
    int reps;
    std::string exerciseName;

public:
    StrengthActivity(const std::string& date, double dur, double cal, const std::string& exerciseName, int sets, int reps);
    int getsets() const;
    int getreps() const;
    std::string getType() const;
    std::string describe() const;

    StrengthActivity& operator=(const StrengthActivity& other);
    friend std::ostream& operator<<(std::ostream& out, const StrengthActivity& ca);
    friend std::istream& operator>>(std::istream& in, StrengthActivity& ca);
};