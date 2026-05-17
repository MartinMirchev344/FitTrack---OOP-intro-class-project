#pragma once
#include<string>
#include<vector>
#include "activities/Activity.h"
#include "goals/Goal.h"

class User {
private:
    std::string username;
    std::string password;
    std::vector<Activity*> activities;
    //Goal* goal;

public:
    User(const std::string& username, const std::string& password);
    ~User();

    void addActivity(Activity* a);
    void printHistory() const;
    void printStats() const;

    std::string getUsername() const;
    std::string getPassword() const;
    //void setGoal(Goal* g);
};