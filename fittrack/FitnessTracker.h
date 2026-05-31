#pragma once
#include <string>
#include <vector>
#include "User.h"

class FitnessTracker {
private:
    std::vector<User*> users;
    User* currentUser;

public:
    FitnessTracker();
    ~FitnessTracker();

    void registerUser(const std::string& username, const std::string& password,
                      int age, double weight, double height);
    bool login(const std::string& username, const std::string& password);
    void logout();
    User* getCurrentUser() const;
    void saveToFile(const std::string& filename) const;
};
