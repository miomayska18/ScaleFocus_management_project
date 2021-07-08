#include <iostream>
#include <string>
#include <nanodbc.h>
#include <exception>
#include <vector>

using namespace std;

struct USER
{
	int id = 0;
	string username = "";
	string password = "";
	string firstName = "";
	string lastName = "";
	string dateOfCreation = "";
	int idOfCreator = 0;
	string dateLastChange = "";
	int idLastChange = 0;
	bool isAdmin = 0;

	void displayUser()
	{
		cout << "User id: " << this->id << endl;
		cout << "Username: " << this->username << endl;
		cout << "Password: " << this->password << endl;
		cout << "Firsrt name: " << this->firstName << endl;
		cout << "Last name: " << this->lastName << endl;
		//cout << "Date of creation of this user: " << this->dateOfCreation.day << "/" << this->dateOfCreation.month << this->dateOfCreation.year << endl;
		cout << "Date of creation of this profile: " << this->dateOfCreation << endl;
		cout << "Id of creator of this profile: " << this->idOfCreator << endl;
		//cout << "Date of last modification of this profile: " << this->dateLastChange.day << "/" << this->dateLastChange.month << "/" << this->dateLastChange.year << endl;
		cout << "Date of the last modification of this profile: " << this->dateLastChange << endl;
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
};

struct TEAM
{
	int id = 0;
	string teamName = "";
	int projectId = 0;
	string dateOfCreation = "";
	int idOfCreator = 0;
	string dateLastChange = "";
};


struct PROJECT
{
	int id = 0;
	string name = "";
	string description = "";
	int ownerId = 0;
	int projectId = 0;
	string dateOfCreation = "";
	int idOfCreator = 0;
	string dateLastChange = "";
	int taskId = 0;
};

struct TASK
{
	int id = 0;
	string title = "";
	string description = "";
	int projectId = 0;
	bool status;
};

struct LOG
{
	int id = 0;
	int userId = 0;
	int timeSpent = 0;
	string date = "";
	int taskId = 0;
};

string enterText()
{
	cin.ignore(1, '\n');
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
	}
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

		getAllUsers(conn);

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
