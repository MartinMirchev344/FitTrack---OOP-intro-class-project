
#pragma once
#include <string>

class User;

class Goal {
protected:
    double targetValue;
    std::string description;

public:
    Goal(double targetValue, const std::string& description);
    virtual ~Goal();

    virtual std::string getType() const = 0;
    virtual bool isAchieved(const User* user) const = 0;
    virtual std::string describe() const = 0;

    double getTarget() const;
};
