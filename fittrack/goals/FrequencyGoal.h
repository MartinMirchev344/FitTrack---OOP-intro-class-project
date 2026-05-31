#pragma once
#include "Goal.h"

class FrequencyGoal : public Goal {
private:
    int periodDays;

public:
    FrequencyGoal(int targetSessions, int periodDays);

    std::string getType() const;
    bool isAchieved(const User* user) const;
    std::string describe() const;
    int getPeriodDays() const;
};
