#include "ArcadiaEngine.h"
#include <iomanip>
#include <vector>
#include <iostream>
using namespace std;

void RegistryApplication() {
    cout << "Registry Application Placeholder\n";
    // Implement registry application logic here
}

void InventorySystemApplication() {
    int choice;
    while (true) {
        cout << "\n=============================\n";
        cout << "    INVENTORY SYSTEM MENU\n";
        cout << "=============================\n";
        cout << "1. Optimize Loot Split\n";
        cout << "2. Maximize Carry Value\n";
        cout << "3. Count String Possibilities\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            cout << "Enter number of coins: ";
            int n;
            cin >> n;
            vector<int> coins(n);
            cout << "Enter coin values: ";
            for (int i = 0; i < n; i++) {
                cin >> coins[i];
            }
            const int result = InventorySystem::optimizeLootSplit(n, coins);
            cout << "Minimum difference between two stacks: " << result << endl;
        }

        else if (choice == 2) {
            cout << "Enter capacity: ";
            int capacity;
            cin >> capacity;

            vector<pair<int, int>> items(3);

            cout << "Enter 3 items (weight value): \n";
            for (auto & item : items) {
                cin >> item.first >> item.second;
            }

            const int result = InventorySystem::maximizeCarryValue(capacity, items);
            cout << "Maximum carry value: " << result << endl;
        }

        else if (choice == 3) {
            cout << "Enter string: ";
            string s;
            cin >> s;
            const long long result = InventorySystem::countStringPossibilities(s);
            cout << "Number of possible decodings: " << result << endl;
        }

        else if (choice == 4) {
            cout << "Exiting...\n";
            return;
        }
        else {
            cout << "Invalid option, try again.\n";
        }
    }
}

void NavigatorApplication() {
    cout << "World Navigator Application Placeholder\n";
    // Implement world navigator application logic here
}

void ServerKernelApplication() {
    cout << "Server Kernel Application Placeholder\n";
    // Implement server kernel application logic here
}

int main() {
    // RegistryApplication();
    InventorySystemApplication();
    // NavigatorApplication();
    // ServerKernelApplication();
    return 0;
}