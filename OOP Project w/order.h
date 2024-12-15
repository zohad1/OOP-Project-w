#pragma once
#include "cart.h"
#include "user.h"
#include <sstream>

class Order {
public:
    void placeOrder(const User& u, const Cart& c) {
        if (c.gettotalprice() == 0) {
            cout << "Your cart is empty. Cannot place order.\n";
            return;
        }
        saveorder("orders.txt", u, c);
        cout << "Order placed successfully!\n";
    }

    void saveorder(const string& orderpath, const User& u, const Cart& c) {
        ofstream orderfile(orderpath, ios::app);
        if (!orderfile.is_open()) {
            cout << "Error: Cannot open file for saving order.\n";
            return;
        }

        cout << "Saving order data to " << orderpath << "...\n";
        orderfile << "Customer Details:\n";
        orderfile << "Name: " << u.name << "\n";
        orderfile << "Email: " << u.email << "\n";
        orderfile << "Address: " << u.address << "\n";
        orderfile << "Phone: " << u.phone << "\n";
        orderfile << "Order Details:\n";
        for (const auto& oderitem : c.getcartitems()) {
            orderfile << oderitem.id << " " << oderitem.name << " " << oderitem.price << "\n";
        }
        orderfile << "Total Price: $" << c.gettotalprice() << "\n";
        orderfile << "--------------------------\n";
        orderfile.close();
        cout << "Order saved successfully.\n";
    }

    void loadorder(const string& orderpath) {
        ifstream orderfile(orderpath);
        if (!orderfile.is_open()) {
            cout << "Error: Cannot open file for loading orders.\n";
            return;
        }

        cout << "Loading orders from " << orderpath << ":\n";
        string line;
        while (getline(orderfile, line)) {
            cout << line << "\n";
        }
        orderfile.close();
    }
};
