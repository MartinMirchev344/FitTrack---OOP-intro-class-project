#pragma once
#include "Goal.h"

class CalorieGoal : public Goal {
private:
    int periodDays;

public:
    CalorieGoal(double targetCalories, int periodDays);

    bool isAchieved(const User* user) const;
    std::string describe() const;
};
