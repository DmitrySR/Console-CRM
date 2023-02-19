#include <iostream>
#include "Classes.h"
#include <fstream>
#include <string>
using namespace std;

void create_application(Client C,Database DB) {
    do {
        cin.ignore();
        string name;
        string application = "";
        cout << "Enter your name: " << endl;
        getline(cin, name);
        application += name + " ";
        C.set_name(name);
        string request;
        cout << "Enter your request" << endl;
        getline(cin, request);
        application += request + " ";
        C.set_request(request);
        string phone;
        cout << "Enter your phone number in international format without '+'." << endl;
        do {
            cin >> phone;
        } while (!C.set_phone(phone));
        application += C.get_phone();
        cout << "This is your application: " << endl;;
        cout << application << endl;
        cout << "Do you want to edit it? Y/n" << endl;
        string ans; cin >> ans;
        if (ans == "n") break;
    } while (true);
    C.insert(DB.get_table_name(), C.get_name(), C.get_request(), C.get_phone());
    cout << "Data has been inserted in DB" << endl;
}

void show_application(Client C,Database DB) {
    cout << "Enter your phone number in international format without '+': " << endl;
    string phone;
    cin.ignore();
    getline(cin, phone);
    cout << "Your applications:" << endl;
    C.show_applications(DB.get_table_name(),phone);
}
void client_iteration() {
    Client C; Database DB;
   bool t = true;
   cout << "Welcome!\n";
    do {
        cout << "What do you need?\n1.Create new application\n2.Show active applications\n3.End client session" << endl;
        int q; cin >> q;
        switch (q) {
        case 1: {
            create_application(C, DB);
            break;
        }
        case 2: {

            show_application(C, DB);
            break;
        }
        case 3: {
            t = false;
            break;
        }
        default: {
            cout << "Wrong number" << endl;
            break;
        }
        }
    } while (t);    
}





