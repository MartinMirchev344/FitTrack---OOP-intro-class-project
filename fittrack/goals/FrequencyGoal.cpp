#include "FrequencyGoal.h"
#include "../User.h"
#include <sstream>
#include <stdexcept>

FrequencyGoal::FrequencyGoal(int targetSessions, int periodDays)
    : Goal(targetSessions, "Frequency goal"), periodDays(periodDays) {
    if (periodDays <= 0) {
        throw std::invalid_argument("Goal period must be a positive number of days");
    }
}

std::string FrequencyGoal::getType() const {
    return "Frequency";
}

bool FrequencyGoal::isAchieved(const User* user) const {
    return user->getActivityCountForLastDays(periodDays) >= targetValue;
}

std::string FrequencyGoal::describe() const {
    std::ostringstream output;
    output << description << ": complete " << targetValue
           << " training sessions in " << periodDays << " days";
    return output.str();
}

int FrequencyGoal::getPeriodDays() const {
    return periodDays;
}
