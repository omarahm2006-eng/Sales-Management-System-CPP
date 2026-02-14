//Programmer Omar Hamdan :)

//  In the code, I didn't create a separate employee registration process. Instead, I restricted employee management to the Admin level.
//  This aligns with the project requirements and expectations, ensuring the system remains flexible, scalable, and easy to maintain. 

// I implemented a feature that allows the admin to update their username and password. Since the system will be handed over to the company,
// it's essential not to restrict them to static credentials, ensuring full administrative control.

#include <iostream>
#include <string>
using namespace std;
    
class Colors {
    //It was added to make the code clearer and more professional.
public:
    static inline string red = "\033[31m";
    static inline string green = "\033[32m";
    static inline string yellow = "\033[33m";
    static inline string blue = "\033[34m";
    static inline string reset = "\033[0m";
};
struct Transaction {
    //This struct is used to enter customer data and the transaction that took place with them.
    string clientName;
    string contactDetails;
    string result;//Transaction result

};
struct User {
    string username;
    string password;
    string role;
    int loginCount = 0;
    int logoutCount = 0;

    string notifications[20];
    int notifCount = 0;
    Transaction deals[20];
    int dealsCount = 0;
};
//  Functional Methods :

void performLogout(User& u) {   // logout method
    u.logoutCount++;
    cout <<Colors::green<< "\n[System] Logout Successful for: " << u.username << endl;
    cout << "[Stats] Total logout count updated: " << u.logoutCount <<Colors::reset<< endl;

}

void updateAdminProfile(User& admin) {//A note has been added to this section at the beginning of the code. 
    cout << Colors::yellow << "\n---- Update Admin Credentials ---- " << endl;
    cout << "Current Username: " << admin.username <<Colors::reset<< endl;
    cout << "Enter NEW Username: ";
    cin >> admin.username;
    cout << "Enter NEW Password: ";
    cin >> admin.password;
    cout <<Colors::green<< ">> Success: Admin credentials updated!" <<Colors::reset<< endl;

}

void addNewEmployee(User database[], int& userCount) {//A note has been added to this section at the beginning of the code. 
    if (userCount >= 20) {
        cout <<Colors::red<< "\n[Error] System full! Cannot add more than 20 users." <<Colors::reset<< endl;
        return;

    }
    cout << Colors::yellow << "\n---- Register New Employee ----" <<Colors::reset<< endl;
    cout << "Enter username: ";
    cin >> database[userCount].username;
    cout << "Enter password: ";
    cin >> database[userCount].password;
    database[userCount].role = "employee";
    database[userCount].loginCount = 0; // Resetting counters for the new user.
    database[userCount].logoutCount = 0;
    database[userCount].dealsCount = 0;
    database[userCount].notifCount = 0;
    userCount++;
    cout << Colors::green << ">> Success: Employee account created successfully!" << Colors::reset << endl;


}
void employeeMenu(User& u) {// Employee Screen Function: Adding deals and displaying notifications.
    int choice;
    do {
        cout <<Colors::yellow<< "\n---- Employee Menu: " << u.username << " ----" << Colors::reset << endl;
        cout << "1. Show Notifications\n2. Add Contact (Deal)\n3. Logout\nEnter choice: ";
        cin >> choice;

        if (choice == 1) {
            cout << "\n---- Notifications Inbox ----" << endl;
            if (u.notifCount == 0) {
                cout << "No notifications yet." << endl;
            }
            for (int i = 0; i < u.notifCount;i++) {
                cout << "_  " << u.notifications[i] << endl;

            }
        }
        else if (choice == 2) {
            if (u.dealsCount < 20) {
                cout << "Client Name: ";
                cin >> u.deals[u.dealsCount].clientName;
                cout << "Contact Info: ";
                cin.ignore();
                getline(cin, u.deals[u.dealsCount].contactDetails);
                cout << "Deal Result: ";
                getline(cin, u.deals[u.dealsCount].result);
                u.dealsCount++;
                cout <<Colors::green<< ">> Deal saved successfully!" <<Colors::reset<< endl;
            }
            else {
                cout <<Colors::red<< "Error: Max limit reached (20 deals)." <<Colors::reset<< endl;
            }
        }
        else if (choice == 3) {
            performLogout(u);
            return;
        }
        else if (choice != 1 && choice != 2 && choice != 3) {
            cout << Colors::red << "\nThis option is not available." << Colors::reset << endl;

        }
    } while (choice != 3);
}

void adminMenu(User& admin, User database[], int& userCount) {
    int choice;
    do {
        cout << Colors::yellow << "\n---- Admin Control Panel ----" << Colors::reset << endl;
        cout << "1. Manage Employees (View Stats & Deals)\n2. Register New Employee\n3. Update My Profile\n4. Logout\nEnter choice: ";
        cin >> choice;
        switch (choice) {
        case 1: {
            cout << Colors::yellow << "\nRegistered Employees:" << Colors::reset << endl;
            for (int i = 0; i < userCount; i++) {
                if (database[i].role != "admin") {
                    cout << "- " << database[i].username << endl;
                }
            }
            string target;
            cout << "\nEnter username to manage: ";
            cin >> target;
            bool found = false;
            for (int i = 0; i < userCount;i++) {
                if (database[i].username == target && database[i].role != "admin") {
                    found = true;
                    cout << "\n---- Status for " << target << " ----" << endl;
                    cout << "Logins: " << database[i].loginCount << " | Logouts: " << database[i].logoutCount << endl;
                    cout << "Total Deals: " << database[i].dealsCount << endl;


                    cout << "\n---- Transaction History ----" << endl;
                    for (int k = 0; k < database[i].dealsCount; k++) {
                        cout << k + 1 << ". Client: " << database[i].deals[k].clientName
                            << " | Details: " << database[i].deals[k].contactDetails
                            << " | Result: " << database[i].deals[k].result << endl;




                    }

                    char sendNotif;
                    cout << "\nDo you want to send a notification to this employee? (y/n): ";
                    cin >> sendNotif;

                    if (sendNotif == 'y' || sendNotif == 'Y') {
                        cout << "Enter notification message: ";
                        string msg;
                        cin.ignore();
                        getline(cin, msg);


                        if (database[i].notifCount < 20) {
                            database[i].notifications[database[i].notifCount++] = msg;
                            cout << Colors::green << ">> Notification sent successfully." << Colors::reset << endl;
                        }
                        else {
                            cout << ">> Error: Notification limit reached for this user." << endl;
                        }
                    }
                    else {
                        cout << ">> Skipping notification." << endl;
                    }
                }
            }




            if (!found) 
                cout <<Colors::red<< "User not found!" <<Colors::reset<< endl;
                break;
            
        }
        
        case 2: addNewEmployee(database, userCount); 
            break;
        case 3: updateAdminProfile(admin); 
            break;
        case 4: performLogout(admin);

            return;
            }



        } while (choice != 4);
}
int performLogin(User database[], int userCount) {
    string u, p;
    for (int i = 0; i < 3; i++) {
        cout <<Colors::blue<< "\n--- System Login Attempt " << (i + 1) << "/3 ---" <<Colors::reset<< endl;
        cout << "Username: ";
        cin >> u;
        cout << "Password: ";
        cin >> p;

        for (int j = 0; j < userCount; j++) {
            if (database[j].username == u && database[j].password == p) {
                database[j].loginCount++; 
                cout <<Colors::green<< "Login successful! Welcome back." <<Colors::reset<< endl;
                return j;
            }
        }
        cout <<Colors::red<< "Invalid credentials." <<Colors::reset<< endl;
    }
    cout <<Colors::red<< "Maximum attempts reached. Program terminated." <<Colors::reset<< endl; 
    exit(0);
}
void runSalesSystem() {
    User database[20]; 
    int userCount = 1;

    database[0].username = "admin";
    database[0].password = "adminpass";
    database[0].role = "admin";

    while (true) {
        cout <<Colors::blue<< "\n====================================" <<Colors::reset<< endl;
        cout << "   SALES MANAGEMENT SYSTEM  " << endl;
        cout <<Colors::blue<< "====================================" <<Colors::reset<< endl;

        int idx = performLogin(database, userCount);

        if (database[idx].role == "admin")
            adminMenu(database[idx], database, userCount);
        else
            employeeMenu(database[idx]);
    }
}


int main() {
    runSalesSystem(); 
    return 0;
}

