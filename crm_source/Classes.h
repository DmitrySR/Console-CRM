#pragma once
#include <string>
#include <iostream>
#include "sqlite3.h"

using namespace std;

class Database {
	sqlite3* db = 0;
	char* err = 0;
	const char* unused = 0;
	string sqls;
	string Table_name = "tab";
	const char* SQL = 0;
	static int callback(void* unused, int argc, char** argv, char** azColName) {
		int i;
		
		for (i = 0; i < argc; i++) {
			if (strcmp(azColName[i], "activity")==0 && strcmp(argv[i],"1")==0) {
				cout << "Status: active" << endl;;
			}
			else if (strcmp(azColName[i], "activity")==0 && strcmp(argv[i], "0")==0) {
				cout << "Status: done"<<endl;
			}
			else {
				printf("%s: %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
			}
			
		}
		printf("\n");
		return 0;
	}
public:
	string get_table_name() {
		return Table_name;
	}
	void set_table_name(string table_name) {
		Table_name = table_name;
	}
	void create_table(string table_name) {
		sqls = "CREATE TABLE IF NOT EXISTS " + table_name + "\
		 (id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, \
		name TEXT NOT NULL, activity INTEGER NOT NULL, \
		request TEXT NOT NULL,phone TEXT NOT NULL);";
		SQL = sqls.c_str();
		
		int rc = sqlite3_open("data.db", &db);
		if (rc) cout << "Can't open/create datase " << sqlite3_errmsg(db);
		
		else if (sqlite3_exec(db, SQL, 0, 0, &err))
		{
			cout << "Wrong SQL-query: " << err;
			sqlite3_free(err);
		}

	}

	void exec(string sqls) {
		SQL = sqls.c_str();
		if (sqlite3_exec(db, SQL, 0, 0, &err))
		{
			cout << "Wrong SQL-query: " << err;
			sqlite3_free(err);
		}
	}

	void exec_select(string sqls) {
		SQL = sqls.c_str();
		int rc = sqlite3_exec(db, SQL, callback, (void*)unused, &err);
		if (rc != SQLITE_OK) {
			fprintf(stderr, "SQL error: %s\n", err);
			sqlite3_free(err);
		}
	}
	
	void close() {
		sqlite3_close(db);
	}
};

class Client
{
private:

	string Name;
	string Request;
	string Phone;
	string SQLS;
	bool isnum(string x) {
		for (int i = 0; i < x.size(); ++i) {
			if (!(isdigit(x.at(i)))) return false;
		}
		return true;
	}
	
public:
	
	string get_name() {
		return Name;
	}
	
	void set_name(string name) {
		Name = name;
	}
	
	string get_phone() {
		return Phone;
	}
	bool set_phone(string phone) {
		if (isnum(phone)) {
			Phone = phone;
			return true;
		}
		else {
			cout << "Wrong format" << endl;
			return false;
		}
	}
	string get_request() {
		return Request;
	}
	void set_request(string request) {
		Request = request;
	}
	void insert(string table_name, string name, string request, string phone ) {
		Database db;
		db.create_table(db.get_table_name());
		SQLS = "INSERT INTO " + table_name + " (name, activity,request,phone)\
			 VALUES('" + name + "',1,'" + request + "','" + phone + "');";
		db.exec(SQLS);
		db.close();
		
	}
	
	void show_applications(string table_name,string phone) {
		Database db;
		db.create_table(db.get_table_name());
		SQLS = "SELECT * FROM " + table_name+" WHERE phone = "+phone+" ;";
		db.exec_select(SQLS);
		db.close();
	}
};

class Admin {
	string SQLS;
	string password;

public:
	void show(string table_name) {
		Database db;
		db.create_table(db.get_table_name());
		SQLS = "SELECT * FROM " + table_name +" ;";
		db.exec_select(SQLS);
		db.close();
	 }
	void delete_done(string table_name) {
		Database db;
		db.create_table(db.get_table_name());
		SQLS = "DELETE FROM " + table_name + " WHERE activity = 0";
		db.exec(SQLS);
		db.close();
	}
	void mark_as_done(string table_name, int id) {
		Database db;
		db.create_table(db.get_table_name());
		SQLS = "UPDATE " + table_name + " \
			SET activity = 0\
			WHERE id = " + to_string(id) + "; ";;
		db.exec(SQLS);
		db.close();
	}
};


