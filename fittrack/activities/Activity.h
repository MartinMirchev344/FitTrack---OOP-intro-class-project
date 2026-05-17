#pragma once
#include<iostream>
#include<string>

class Activity{
protected:
    std::string date;
    double duration;
    double calories;

public:
    Activity(const std::string& date, double dur, double cal);
    virtual ~Activity();

    virtual std::string getType() const = 0;
    virtual std::string describe() const = 0;
    double getCalories() const;
    int getDuration() const;
    std::string getDate() const;

    friend std::ostream& operator<<(std::ostream& out, const Activity& a);
};