#include <iostream>
#include <string>
#include "User.h"
#include "activities/CardioActivity.h"
#include "activities/StrengthActivity.h"
#include "goals/CalorieGoal.h"
#include "goals/FrequencyGoal.h"

using namespace std;

int main() {
    User* currentUser = nullptr;
    int choice;

    while (true) {
        cout << "\n=== FitTrack ===\n";
        cout << "1. Register\n";
        cout << "2. Add workout\n";
        cout << "3. History\n";
        cout << "4. Stats\n";
        cout << "5. Set goal\n";
        cout << "0. Exit\n";
        cout << "Choice: ";
        cin >> choice;

        if (choice == 0) break;

        if (choice == 1) {
            string username, password;
            int age;
            double weight, height;
            cout << "Username: "; cin >> username;
            cout << "Password: "; cin >> password;
            cout << "Age: "; cin >> age;
            cout << "Weight (kg): "; cin >> weight;
            cout << "Height (cm): "; cin >> height;
            delete currentUser;
            currentUser = new User(username, password, age, weight, height);
            cout << "Registration successful.\n";
        }
        else if (choice == 2) {
            if (!currentUser) { cout << "Please register first.\n"; continue; }
            int type;
            cout << "1. Cardio  2. Strength: "; cin >> type;
            string date; double dur, cal;
            cout << "Date: "; cin >> date;
            cout << "Duration (min): "; cin >> dur;
            cout << "Calories: "; cin >> cal;
            if (type == 1) {
                double dist;
                cout << "Distance (km): "; cin >> dist;
                currentUser->addActivity(new CardioActivity(date, dur, cal, dist));
            } else {
                string name; int sets, reps;
                cout << "Exercise: "; cin >> name;
                cout << "Sets: "; cin >> sets;
                cout << "Reps: "; cin >> reps;
                currentUser->addActivity(new StrengthActivity(date, dur, cal, name, sets, reps));
            }
            cout << "Workout added.\n";
        }
        else if (choice == 3) {
            if (!currentUser) { cout << "Please register first.\n"; continue; }
            currentUser->printHistory();
        }
        else if (choice == 4) {
            if (!currentUser) { cout << "Please register first.\n"; continue; }
            currentUser->printStats();
        }
        else if (choice == 5) {
            if (!currentUser) { cout << "Please register first.\n"; continue; }
            int type, days;
            cout << "1. Calorie goal  2. Frequency goal: "; cin >> type;
            cout << "Period (days): "; cin >> days;
            if (type == 1) {
                double calories;
                cout << "Target calories: "; cin >> calories;
                currentUser->setGoal(new CalorieGoal(calories, days));
            } else {
                int sessions;
                cout << "Target training sessions: "; cin >> sessions;
                currentUser->setGoal(new FrequencyGoal(sessions, days));
            }
            cout << "Goal set.\n";
        }
    }

    delete currentUser;
    return 0;
}
