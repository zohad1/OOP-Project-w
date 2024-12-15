#include <iostream>
#include <string>
#include "items.h"
#include "user.h"
#include "cart.h"
#include "order.h"
using namespace std;

void displaymenu() {
    cout << "\n==== Online Shopping System ====\n";
    cout << "1. Add Item to Cart\n";
    cout << "2. Display Cart\n";
    cout << "3. Place Order\n";
    cout << "4. Load Cart from File\n";
    cout << "5. Save Cart to File\n";
    cout << "6. Load Orders from File\n";
    cout << "7. Search Items by Budget\n";
    cout << "8. Exit\n";
    cout << "Enter your choice: ";
}

int main() {
    Cart cart;
    User currentUser;
    Order order;

    // Input user details
    cout << "Enter Your Name: ";
    getline(cin, currentUser.name);
    cout << "Enter Your Email: ";
    getline(cin, currentUser.email);
    cout << "Enter Your Address: ";
    getline(cin, currentUser.address);
    cout << "Enter Your Phone Number: ";
    cin >> currentUser.phone;
    cin.ignore();

    // Load all items from items.txt at the start
    vector<Items> allItems = Items::loadfromfile("items.txt");
    if (allItems.empty()) {
        cout << "No items loaded from items.txt.\n";
    }

    int choice;
    do {
        displaymenu();
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1: {
            // Display all items
            if (allItems.empty()) {
                cout << "No items available.\n";
            }
            else {
                cout << "Available Items:\n";
                for (const auto& it : allItems) {
                    it.displayItems();
                }

                cout << "Enter the ID of the item you want to add to cart: ";
                int selectedID;
                cin >> selectedID;
                cin.ignore();

                // Find the item in allItems
                bool found = false;
                for (const auto& it : allItems) {
                    if (it.id == selectedID) {
                        cart.additem(it);
                        cout << "Item added to cart.\n";
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    cout << "Item not found with that ID.\n";
                }
            }
            break;
        }
        case 2:
            cart.displaycart();
            break;
        case 3:
            order.placeOrder(currentUser, cart);
            cart = Cart(); // Reset cart after placing order
            break;
        case 4:
            cart.loadCartFromFile("carts.txt");
            break;
        case 5:
            cart.savetofile("carts.txt");
            break;
        case 6:
            order.loadorder("orders.txt");
            break;
        case 7: {
            if (allItems.empty()) {
                cout << "No items available for budget search.\n";
            }
            else {
                Items::serach_by_budget(allItems);
            }
            break;
        }
        case 8:
            cout << "Thank you for using the system!\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 8);

    return 0;
}
