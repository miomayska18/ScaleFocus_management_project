#include <iostream>
#include <string>
#include <nanodbc.h>
#include <exception>
#include <vector>
#include "Structures.h"

using namespace std;

void USER::displayUser()
{
	cout << "User id: " << this->id << endl;
	cout << "Username: " << this->username << endl;
	cout << "Password: " << this->password << endl;
	cout << "Firsrt name: " << this->firstName << endl;
	cout << "Last name: " << this->lastName << endl;
	cout << "Date of creation of this profile: " << this->dateOfCreation << endl;
	cout << "Id of creator of this profile: " << this->idOfCreator << endl;
	cout << "Date of the last modification: " << this->dateLastChange << endl;
	cout << "Id of the user that last modified this profile: " << this->idLastChange << endl;
	cout << "Is this user an admin: ";
	if (this->isAdmin)
	{
		cout << "yes" << endl;
	}
	else
	{
		cout << "no" << endl;
	}
}

void TEAM::displayTeam()
{
	cout << "Team id: " << this->id << endl;
	cout << "Team name " << this->teamName << endl;
	cout << "Assigned project id: " << this->projectId << endl;
	cout << "Date of creation: " << this->dateOfCreation << endl;
	cout << "Id of creator: " << this->idOfCreator << endl;
	cout << "Date of last modification: " << this->dateLastChange << endl;
}



void PROJECT::displayProject()
{
	cout << "Project id: " << this->id << endl;
	cout << "Project's name: " << this->name << endl;
	cout << "Description: " << this->description << endl;
	cout << "Owner id: " << this->ownerId << endl;
	cout << "Date of creation: " << this->dateOfCreation << endl;
	cout << "Id of creator: " << this->idOfCreator << endl;
	cout << "Date of last modification: " << this->dateLastChange << endl;
}


void TASK::displayTask()
{
	cout << "Task id: " << this->id << endl;
	cout << "Task title: " << this->title << endl;
	cout << "Description: " << this->description << endl;
	cout << "Project id: " << this->projectId << endl;
	cout << "Task status: ";
	if (this->status)
	{
		cout << "complete" << endl;
	}
	else
	{
		cout << "pending" << endl;
	}
}


void LOG::displayLog()
{
	cout << "Log id: " << endl;
	cout << "User id: " << endl;
	cout << "Timse spent working (in minutes): " << endl;
	cout << "Date: " << endl;
	cout << "Task id: " << endl;
}

string enterText()
{
	cin.ignore(0, '\n');
	string text;
	getline(cin, text);

	return text;
}

int enterInt()
{
	int num;
	cin >> num;
	return num;
}

double enterDouble()
{
	double num;
	cin >> num;
	return num;
}

vector<USER> getUsers(nanodbc::connection conn)
{
	vector<USER> users;
	nanodbc::statement statement(conn);
	nanodbc::prepare(statement, NANODBC_TEXT(R"( 
        SELECT *
            FROM [ProjectManagement].[dbo].[Users]
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
	const string username = enterText();
	statement.bind(0, username.c_str());

	cout << "Enter the password: ";
	const string password = enterText();
	statement.bind(1, password.c_str());

	cout << "Enter the user's first name: ";
	const string firstName = enterText();
	statement.bind(2, firstName.c_str());

	cout << "Enter the user's last name: ";
	const string lastName = enterText();
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
	const string username = enterText();
	statement.bind(0, username.c_str());

	cout << "Enter the new password: ";
	const string password = enterText();
	statement.bind(1, password.c_str());

	cout << "Enter the user's new first name: ";
	const string firstName = enterText();
	statement.bind(2, firstName.c_str());

	cout << "Enter the user's new last name: ";
	const string lastName = enterText();
	statement.bind(3, lastName.c_str());

	cout << "Enter your id: ";
	const int creatorId = enterInt();
	statement.bind(4, &creatorId);
	
	statement.bind(5, &id);

	execute(statement);
}

bool deleteUserById(nanodbc::connection conn, const int& id)
{
	nanodbc::statement statement(conn);
	nanodbc::prepare(statement, NANODBC_TEXT(R"(
        DELETE 
            FROM [ProjectManagement].[dbo].[Users]
            WHERE Id = ?
    )"));

	statement.bind(0, &id);

	auto result = execute(statement);

	return result.affected_rows() != 0;
}

int main()
{
	try
	{
		nanodbc::string connstr = NANODBC_TEXT("DRIVER={ODBC Driver 17 for SQL Server};SERVER=(localdb)\\MSSQLLocalDB;DATABASE=ProjectManagement;Trusted_Connection=yes;"); // an ODBC connection string to your database

		nanodbc::connection conn(connstr);

		/*do
		{
			runProgram(conn);
		} while (runProgram(conn));*/

		//insertUser(conn);
		//getAllUsers(conn);
		editUserById(conn, 3);

		return EXIT_SUCCESS;
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
