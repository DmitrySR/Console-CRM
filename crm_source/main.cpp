#include <iostream>
#include "sqlite3.h"
#include "Classes.h"
#include <fstream>
using namespace std;

void client_iteration();
void admin_iteration();

int main() {
	
	do {
		int q;
		cout << "1. Start\n2. Help\n3. Exit\n";
		cin >> q;
		switch (q) {
		case 1: {
			cout << "Who are you?\n1.Client\n2.Admin\n";
			int q1; cin >> q1;
			switch (q1) {
			case 1: {
				client_iteration();
				break;
			}
			case 2: {
				admin_iteration();
				break;
			}
			default: {
				cout << "Wrong number"<<endl;
				break;
			}
			}
			break;
		}

		case 2: {
			cout << "Manual will be here";
			break;
		}
		case 3: {
			exit(1);
			break;
		}
		default:
			cout << "Wrong number";
			break;
		}
		string ans;
		cout << "Do you want to end session? Y/n" << endl;
		cin >> ans;
		if (ans == "Y") {
			break;
		}

	} while (true);
	

	
	
	return 0;
}
