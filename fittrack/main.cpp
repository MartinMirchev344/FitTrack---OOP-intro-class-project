#include <iostream>
#include <stdexcept>
#include <string>
#include "FitnessTracker.h"
#include "activities/CardioActivity.h"
#include "activities/StrengthActivity.h"
#include "goals/CalorieGoal.h"
#include "goals/FrequencyGoal.h"

using namespace std;

int main() {
    FitnessTracker tracker;
    int choice;

    tracker.loadFromFile("data.txt");

    while (true) {
        User* currentUser = tracker.getCurrentUser();
        cout << "\n=== FitTrack ===\n";
        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "3. Logout\n";
        cout << "4. Add workout\n";
        cout << "5. History\n";
        cout << "6. Stats\n";
        cout << "7. Set goal\n";
        cout << "8. Check goal progress\n";
        cout << "0. Exit\n";
        cout << "Choice: ";
        cin >> choice;
        if (!cin) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input.\n";
            continue;
        }

        if (choice == 0) break;

        try {
        if (choice == 1) {
            string username, password;
            int age;
            double weight, height;
            cout << "Username: "; cin >> username;
            cout << "Password: "; cin >> password;
            cout << "Age: "; cin >> age;
            cout << "Weight (kg): "; cin >> weight;
            cout << "Height (cm): "; cin >> height;
            if (!cin) throw invalid_argument("Invalid input");
            tracker.registerUser(username, password, age, weight, height);
            cout << "Registration successful.\n";
        }
        else if (choice == 2) {
            string username, password;
            cout << "Username: "; cin >> username;
            cout << "Password: "; cin >> password;
            if (tracker.login(username, password)) {
                cout << "Login successful.\n";
            } else {
                cout << "Incorrect username or password.\n";
            }
        }
        else if (choice == 3) {
            tracker.logout();
            cout << "Logged out.\n";
        }
        else if (choice == 4) {
            if (!currentUser) { cout << "Please login first.\n"; continue; }
            int type;
            cout << "1. Cardio  2. Strength: "; cin >> type;
            if (!cin) throw invalid_argument("Invalid input");
            if (type != 1 && type != 2) throw invalid_argument("Invalid workout type");
            string date; double dur, cal;
            cout << "Date: "; cin >> date;
            cout << "Duration (min): "; cin >> dur;
            cout << "Calories: "; cin >> cal;
            if (!cin) throw invalid_argument("Invalid input");
            if (type == 1) {
                double dist;
                cout << "Distance (km): "; cin >> dist;
                if (!cin) throw invalid_argument("Invalid input");
                currentUser->addActivity(new CardioActivity(date, dur, cal, dist));
            } else {
                string name; int sets, reps;
                cout << "Exercise: "; cin >> name;
                cout << "Sets: "; cin >> sets;
                cout << "Reps: "; cin >> reps;
                if (!cin) throw invalid_argument("Invalid input");
                currentUser->addActivity(new StrengthActivity(date, dur, cal, name, sets, reps));
            }
            cout << "Workout added.\n";
        }
        else if (choice == 5) {
            if (!currentUser) { cout << "Please login first.\n"; continue; }
            currentUser->printHistory();
        }
        else if (choice == 6) {
            if (!currentUser) { cout << "Please login first.\n"; continue; }
            int days;
            cout << "Period (days): "; cin >> days;
            if (!cin) throw invalid_argument("Invalid input");
            currentUser->printStats(days);
        }
        else if (choice == 7) {
            if (!currentUser) { cout << "Please login first.\n"; continue; }
            int type, days;
            cout << "1. Calorie goal  2. Frequency goal: "; cin >> type;
            cout << "Period (days): "; cin >> days;
            if (!cin) throw invalid_argument("Invalid input");
            if (type != 1 && type != 2) throw invalid_argument("Invalid goal type");
            if (type == 1) {
                double calories;
                cout << "Target calories: "; cin >> calories;
                if (!cin) throw invalid_argument("Invalid input");
                currentUser->setGoal(new CalorieGoal(calories, days));
            } else {
                int sessions;
                cout << "Target training sessions: "; cin >> sessions;
                if (!cin) throw invalid_argument("Invalid input");
                currentUser->setGoal(new FrequencyGoal(sessions, days));
            }
            cout << "Goal set.\n";
        }
        else if (choice == 8) {
            if (!currentUser) { cout << "Please login first.\n"; continue; }
            currentUser->printGoalProgress();
        }
        }
        catch (const invalid_argument& error) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Error: " << error.what() << "\n";
        }
    }

    tracker.saveToFile("data.txt");
    return 0;
}
