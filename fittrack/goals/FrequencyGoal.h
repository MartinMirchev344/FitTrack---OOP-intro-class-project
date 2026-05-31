#pragma once
#include "Goal.h"

class FrequencyGoal : public Goal {
private:
    int periodDays;

public:
    FrequencyGoal(int targetSessions, int periodDays);

    bool isAchieved(const User* user) const;
    std::string describe() const;
};
