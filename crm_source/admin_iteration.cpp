#include <iostream>
#include "Classes.h"
using namespace std;

void admin_iteration() { 
	Admin A; Database DB;
	cout << "Admin access" << endl;
	bool t = true;
	do {
		cout << "1. Show applications\n2. Mark application as fulfilled\n3.Delete fulfilled applications\n4.Exit admin seccion" << endl;
		int q; cin >> q;
		switch (q) {
		case 1: {
			A.show(DB.get_table_name());
			break;
		}
		case 2: {
			cout << "Enter application's ID" << endl;
			int id; cin >> id;
			A.mark_as_done(DB.get_table_name(), id);
			break;
		}
		case 3: {
			A.delete_done(DB.get_table_name());
			break;
		}
		case 4: {

		}
		case 5: {
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