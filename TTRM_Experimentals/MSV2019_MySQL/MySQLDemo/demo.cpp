#include <iostream>
#include <mysql.h>
#include <stdio.h>
int qstate;

int main() {
	MYSQL* conn;
	MYSQL_ROW row;
	MYSQL_RES* res;
	conn = mysql_init(0);
	conn = mysql_real_connect(conn, "localhost", "root", "CodexLink121", "testdb", 3306, NULL, 0);
	std::string a = "";
	if (conn) {
		puts("Successful connection to database!");
		std::string query = "SELECT * FROM test";
		const char* q = query.c_str();
		qstate = mysql_query(conn, q);
		if (!qstate) {
			res = mysql_store_result(conn);
			while (row = mysql_fetch_row(res))
			{
				std::cout << "ID: " << row[0] << ", Name: " << row[1] << ", Value: " << row[2] << std::endl;
			}
		}
		else {
			std::cout << "Query Failed. Error Code: " << mysql_error(conn) << std::endl;
		}
	}
	else {
		std::cout << "Connection to the database failed!" << std::endl;
	}
	std::cin >> a;
	delete conn;
	return 0;
}