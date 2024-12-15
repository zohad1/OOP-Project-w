#pragma once
#include <iostream>
#include <string>
using namespace std;

class User {
public:
    string name, email, address, giftnote;
    int phone;

    void displayuserinfo() const {
        cout << "Name: " << name << endl;
        cout << "Email: " << email << endl;
        cout << "Address: " << address << endl;
        cout << "Phone: " << phone << endl;
        if (!giftnote.empty()) {
            cout << "Gift Note: " << giftnote << endl;
        }
    }
};
