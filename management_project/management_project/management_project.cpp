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
	nanodbc::timestamp dateOfCreation;
	int idOfCreator = 0;
	nanodbc::timestamp dateLastChange;
	int idLastChange = 0;
	bool isAdmin;
};

struct TEAM
{
	int id = 0;
	string teamName = "";
	int projectId = 0;
	nanodbc::timestamp dateOfCreation;
	int idOfCreator = 0;
	nanodbc::timestamp dateLastChange;
};


struct PROJECT
{
	int id = 0;
	string name = "";
	string description = "";
	int ownerId = 0;
	int projectId = 0;
	nanodbc::timestamp dateOfCreation;
	int idOfCreator = 0;
	nanodbc::timestamp dateLastChange;
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
	nanodbc::timestamp date;
	int taskId = 0;
};

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
