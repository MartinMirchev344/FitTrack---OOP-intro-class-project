#pragma once
#include "Activity.h"

class StrengthActivity: public Activity{
private:
    int sets;
    int reps;
    std::string exerciseName;

public:
    StrengthActivity(const std::string& date, double dur, double cal, const std::string& exerciseName, int sets, int reps);
    int getSets() const;
    int getReps() const;
    std::string getExerciseName() const;
    std::string getType() const override;
    std::string describe() const override;

    StrengthActivity& operator=(const StrengthActivity& other);
    friend std::ostream& operator<<(std::ostream& out, const StrengthActivity& ca);
    friend std::istream& operator>>(std::istream& in, StrengthActivity& ca);
};
