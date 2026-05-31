#pragma once
#include<string>
#include<vector>
#include "activities/Activity.h"
#include "goals/Goal.h"

class User {
private:
    std::string username;
    std::string password;
    int age;
    double weight;
    double height;
    std::vector<Activity*> activities;
    Goal* goal;

public:
    User(const std::string& username, const std::string& password, int age, double weight, double height);
    ~User();

    void addActivity(Activity* a);
    void printHistory() const;
    void printStats(int days) const;
    double getTotalCaloriesForLastDays(int days) const;
    int getActivityCountForLastDays(int days) const;

    std::string getUsername() const;
    std::string getPassword() const;
    int getAge() const;
    double getWeight() const;
    double getHeight() const;
    const std::vector<Activity*>& getActivities() const;
    Goal* getGoal() const;
    void setGoal(Goal* g);
    bool hasGoal() const;
    bool checkGoal() const;
    void printGoalProgress() const;
};
