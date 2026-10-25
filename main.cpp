// COMSC 210 | Lab 28 | Yeji Kim
#include <iostream>
#include <fstream>
#include <iomanip>
#include <list>
#include "Goat.h"
#include <algorithm>
#include <numeric>
using namespace std;

const int SZ_NAMES = 200, SZ_COLORS = 25;

int select_goat(list<Goat> trip);
void delete_goat(list<Goat> &trip);
void add_goat(list<Goat> &trip, string [], string []);
void display_trip(list<Goat> trip);
int main_menu();
void find_goat(list<Goat> trip);
void check_goat_age(list<Goat> trip);
void display_goats_algorithm(list<Goat> trip);
void calculate_total_age(list<Goat> trip);
void change_goat_color(list<Goat> &trip);
void reverse_goats(list<Goat> &trip);

int main() {
    srand(time(0));
    bool again;

    // read & populate arrays for names and colors
    ifstream fin("names.txt");
    string names[SZ_NAMES];
    int i = 0;
    while (fin >> names[i++]);
    fin.close();
    ifstream fin1("colors.txt");
    string colors[SZ_COLORS];
    i = 0;
    while (fin1 >> colors[i++]);
    fin1.close();

    // create & populate a trip of Goats using std::list of random size 8-15
    int tripSize = rand() % 8 + 8;
    list<Goat> trip;
    int age;
    string name, color;
    for (int i = 0; i < tripSize; i++) {
        age = rand() % MAX_AGE;  // defined in Goat.h
        name = names[rand() % SZ_NAMES];
        color = colors[rand() % SZ_COLORS];
        Goat tmp(name, age, color);
        trip.push_back(tmp);
    }
    
    // Goat Manager 3001 Engine
    int sel = main_menu();
    while (sel != 10) {
        switch (sel) {
            case 1:
                cout << "Adding a goat.\n";
                add_goat(trip, names, colors);
                break;
            case 2:    
                cout << "Removing a goat.\n";
                delete_goat(trip);
                break;
            case 3:    
                cout << "Displaying goat data.\n";
                display_trip(trip);
                break;
            case 4:
                cout << "Searching for a goat.\n";
                find_goat(trip);
                break;
            case 5:
                cout << "Checking goat ages.\n";
                check_goat_age(trip);
                break;
            case 6:
                cout << "Displaying goats using for_each.\n";
                display_goats_algorithm(trip);
                break;
            case 7:
                cout << "Calculating total goat age.\n";
                calculate_total_age(trip);
                break;
            case 8:
                cout << "Changing goat color.\n";
                change_goat_color(trip);
                break;
            case 9:
                cout << "Reversing goat order.\n";
                reverse_goats(trip);
                break;
            default:
                cout << "Invalid selection.\n";
                break;
        }
        sel = main_menu();
    }
    

    return 0;
}

int main_menu() {
    cout << "*** GOAT MANAGER 3001 ***\n";
    cout << "[1] Add a goat\n";
    cout << "[2] Delete a goat\n";
    cout << "[3] List goats\n";
    cout << "[4] Find a goat by name\n";
    cout << "[5] Check for goats older than an age\n";
    cout << "[6] Display goats using for_each\n";
    cout << "[7] Calculate total age of all goats\n";
    cout << "[8] Change goats' color\n";
    cout << "[9] Reverse goat order\n";
    cout << "[10] Quit\n";
    cout << "Choice --> ";
    int choice;
    cin >> choice;
    while (choice < 1 || choice > 10) {
        cout << "Invalid, again --> ";
        cin >> choice;
    }
    return choice;
}

void delete_goat(list<Goat> &trip) {
    cout << "DELETE A GOAT\n";
    int index = select_goat(trip);
    auto it = trip.begin();
    advance(it, index-1);
    trip.erase(it);
    cout << "Goat deleted. New trip size: " << trip.size() << endl;
}

void add_goat(list<Goat> &trip, string nms[], string cls[]) {
    cout << "ADD A GOAT\n";
    int age = rand() % MAX_AGE;
    string nm = nms[rand() % SZ_NAMES];
    string cl = cls[rand() % SZ_COLORS];
    Goat tmp(nm, age, cl);
    trip.push_back(tmp);
    cout << "Goat added. New trip size: " << trip.size() << endl;
}

void display_trip(list<Goat> trp) {
    int i = 1;
    for (auto gt: trp)
        cout << "\t" 
             << "[" << i++ << "] "
             << gt.get_name() 
             << " (" << gt.get_age() 
             << ", " << gt.get_color() << ")\n";
}

int select_goat(list<Goat> trp) {
    int input;
    cout << "Make a selection:\n";
    display_trip(trp);
    cout << "Choice --> ";
    cin >> input;
    while (input < 1 or input > trp.size()) {
        cout << "Invalid choice, again --> ";
        cin >> input;
    }
    return input;
}

void find_goat(list<Goat> trip) {
    string searchName;

    cout << "Enter goat name: ";
    cin >> searchName;

    auto it = find_if(trip.begin(), trip.end(),
        [searchName](const Goat& gt) {
            return gt.get_name() == searchName;
        });

    if (it != trip.end()) {
        cout << "Found goat: "
             << it->get_name()
             << " (" << it->get_age()
             << ", " << it->get_color() << ")" << endl;
    } else {
        cout << searchName << " not found." << endl;
    }
}

void check_goat_age(list<Goat> trip) {
    int ageLimit;

    cout << "Enter an age limit: ";
    cin >> ageLimit;

    bool found = any_of(trip.begin(), trip.end(),
        [ageLimit](const Goat& gt) {
            return gt.get_age() > ageLimit;
        });

    if (found) {
        cout << "There is at least one goat older than "
             << ageLimit << ".\n";
    } else {
        cout << "No goats are older than "
             << ageLimit << ".\n";
    }
}

void display_goats_algorithm(list<Goat> trip) {
    int i = 1;

    for_each(trip.begin(), trip.end(),
        [&i](const Goat& gt) {
            cout << "[" << i++ << "] "
                 << gt.get_name()
                 << " (" << gt.get_age()
                 << ", " << gt.get_color() << ")\n";
        });
}

void calculate_total_age(list<Goat> trip) {
    int totalAge = accumulate(
        trip.begin(), trip.end(), 0,
        [](int total, const Goat& gt) {
            return total + gt.get_age();
        });

    cout << "Total age of all goats: "
         << totalAge << endl;
}

void change_goat_color(list<Goat> &trip) {
    string oldColor, newColor;

    cout << "Enter the current color: ";
    cin >> oldColor;

    cout << "Enter the new color: ";
    cin >> newColor;

    int changed = count_if(trip.begin(), trip.end(),
        [oldColor](const Goat& gt) {
            return gt.get_color() == oldColor;
        });

    if (changed == 0) {
        cout << "No goats found with color "
             << oldColor << ".\n";
        return;
    }

    transform(trip.begin(), trip.end(), trip.begin(),
        [oldColor, newColor](const Goat& gt) {
            if (gt.get_color() == oldColor) {
                return Goat(gt.get_name(),
                            gt.get_age(),
                            newColor);
            }
            return gt;
        });

    cout << changed << " goat(s) changed from "
         << oldColor << " to " << newColor << ".\n";
}

void reverse_goats(list<Goat> &trip) {
    trip.reverse();

    cout << "Goat order reversed.\n";
    display_trip(trip);
}
