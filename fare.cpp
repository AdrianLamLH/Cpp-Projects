#include <iostream>
#include <string>
using namespace std;

int main()
{
    // Initialize variables with their respective data types
    int age;
    string student;
    string destination;
    int zones;
    double amount;

    // Produces prompts for the data to be entered followed by input fields
    cout << "Age of rider: ";
    cin >> age;
    cin.ignore(10000, '\n');

    cout << "Student? (y/n): ";
    getline(cin, student);

    cout << "Destination: ";
    getline(cin, destination);

    cout << "Number of zone boundaries crossed: ";
    cin >> zones;
    cin.ignore(10000, '\n');

    cout << "---" << endl;

    // Error checking from the data entered in the fields above
    if (age < 0) {
        cout << "The age must not be negative" << endl;
    }
    else if (!((student == "y") || (student == "n"))) {
        cout << "You must enter y or n" << endl;
    }
    else if (destination == "") {
        cout << "You must enter a destination";
    }
    else if (zones < 0) {
        cout << "The number of zone boundaries crossed must not be negative";
    }
    else {
        // Considering discounts according to age and zones travelled through
        if ((age < 18) && (zones < 2)) {
            amount = 0.65;
        }
        else if ((age >= 18) && (zones < 2)) {
            amount = 0.65;
        }
        else if ((age >= 65) && (zones == 0)) {
            amount = 0.45;
        }
        else if (age >= 65) {
            amount = 0.55 + 0.35 * zones;
        }
        else {
            amount = 1.45 + 0.55 * zones;
        }
        cout << "The fare to " << destination << " is $" << amount;
    }

}