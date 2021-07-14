#include <iostream>
#include "Structures.h"
#include <nanodbc.h>
#include <vector>
#include <string>
#include "InsertFunctions.h"
using namespace std;

vector<USER> getUsers(nanodbc::connection conn)
{
	vector<USER> users;
	nanodbc::statement statement(conn);
	nanodbc::prepare(statement, NANODBC_TEXT(R"( 
        SELECT *
            FROM [ProjectManagement].[dbo].[Users]
		WHERE 
			isDeleted<>1
    )"));

	auto result = execute(statement);

	while (result.next())
	{
		USER user;
		user.id = result.get<int>("Id");
		user.username = result.get<nanodbc::string>("UserName", "");
		user.password = result.get<nanodbc::string>("Password", "");
		user.firstName = result.get<nanodbc::string>("FirstName", "");
		user.lastName = result.get<nanodbc::string>("LastName", "");
		user.dateOfCreation = result.get<nanodbc::string>("DateOfCreation", "");
		user.idOfCreator = result.get<int>("IdOfCreator");
		user.dateLastChange = result.get<nanodbc::string>("DateLastChange", "");
		user.idLastChange = result.get<int>("IdLastChange");
		user.isAdmin = result.get<int>("IsAdmin");

		users.push_back(user);
	}

	return users;
}

void getAllUsers(nanodbc::connection conn)
{
	vector<USER> users = getUsers(conn);

	for (size_t i = 0; i < users.size(); i++)
	{
		users[i].displayUser();
		cout << endl;
	}

	cout << endl << endl;
	
	int choice = 1;
	do {
		cout << "Enter 0 to get back to the menu: ";
		choice = enterInt();
	} while (choice != 0);
}

void insertUser(nanodbc::connection conn)
{
	nanodbc::statement statement(conn);
	nanodbc::prepare(statement, NANODBC_TEXT(R"(
        INSERT INTO
            [ProjectManagement].[dbo].[Users]
            (UserName, Password, FirstName, LastName, IdOfCreator, IdLastChange, IsAdmin)
            VALUES
            (?, ?, ?, ?, ?, ?, ?)
    )"));

	cout << "Enter the username: ";
	const string username = enterText(true);
	statement.bind(0, username.c_str());

	cout << "Enter the password: ";
	const string password = enterText(false);
	statement.bind(1, password.c_str());

	cout << "Enter the user's first name: ";
	const string firstName = enterText(false);
	statement.bind(2, firstName.c_str());

	cout << "Enter the user's last name: ";
	const string lastName = enterText(false);
	statement.bind(3, lastName.c_str());

	cout << "Enter your id: ";
	const int creatorId = enterInt();
	statement.bind(4, &creatorId);
	statement.bind(5, &creatorId);

	cout << "Enter 1 if the user is an admin or 0 is they are not: ";
	const int isAdmin = enterInt();
	statement.bind(6, &isAdmin);

	execute(statement);
}

void editUserById(nanodbc::connection conn, const int& id)
{
	nanodbc::statement statement(conn);
	nanodbc::prepare(statement, NANODBC_TEXT(R"(
        UPDATE [ProjectManagement].[dbo].[Users]
        SET    
            UserName = ?,
			Password = ?, 
			FirstName = ?, 
			LastName = ?, 
			IdLastChange = ?,
			DateLastChange = GETDATE()
		WHERE	
			Id = ?
    )"));



	cout << "Enter the new username: ";
	const string username = enterText(true);
	statement.bind(0, username.c_str());

	cout << "Enter the new password: ";
	const string password = enterText(false);
	statement.bind(1, password.c_str());

	cout << "Enter the user's new first name: ";
	const string firstName = enterText(false);
	statement.bind(2, firstName.c_str());

	cout << "Enter the user's new last name: ";
	const string lastName = enterText(false);
	statement.bind(3, lastName.c_str());

	cout << "Enter your id: ";
	const int creatorId = enterInt();
	statement.bind(4, &creatorId);

	statement.bind(5, &id);

	execute(statement);
}

void deleteUserById(nanodbc::connection conn, const int& id)
{
	nanodbc::statement statement(conn);
	nanodbc::prepare(statement, NANODBC_TEXT(R"(
		UPDATE	
			Users 
		SET 
			isDeleted = 1
        WHERE 
			Id = ?
    )"));

	statement.bind(0, &id);

	auto result = execute(statement);
}