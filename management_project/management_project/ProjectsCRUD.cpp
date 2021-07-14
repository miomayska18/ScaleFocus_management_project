#include <iostream>
#include "Structures.h"
#include <nanodbc.h>
#include <vector>
#include <string>
#include "InsertFunctions.h"
using namespace std;

vector<PROJECT> getProjects(nanodbc::connection conn)
{
	vector<PROJECT> projects;
	nanodbc::statement statement(conn);
	nanodbc::prepare(statement, NANODBC_TEXT(R"( 
        SELECT *
            FROM [ProjectManagement].[dbo].[Projects]
		WHERE
			IsDeleted<>1
    )"));

	auto result = execute(statement);

	while (result.next())
	{
		PROJECT project;
		project.id = result.get<int>("Id");
		project.name = result.get<nanodbc::string>("Name", "");
		project.description = result.get<nanodbc::string>("Description", "");
		project.ownerId = result.get<int>("OwnerId");
		project.dateOfCreation = result.get<nanodbc::string>("DateCreation", "");
		project.idOfCreator = result.get<int>("IdCreator");
		project.dateLastChange = result.get<nanodbc::string>("DateLastChange", "");
		project.idLastChange = result.get<int>("IdLastChange");

		projects.push_back(project);
	}

	return projects;
}

void getAllProjects(nanodbc::connection conn)
{
	vector<PROJECT> projects = getProjects(conn);

	for (size_t i = 0; i < projects.size(); i++)
	{
		projects[i].displayProject();
		cout << endl;
	}

}

void insertProject(nanodbc::connection conn, USER& user)
{
	nanodbc::statement statement(conn);
	nanodbc::prepare(statement, NANODBC_TEXT(R"(
        INSERT INTO
            [ProjectManagement].[dbo].[Projects]
            (Name, Description, OwnerId, DateCreation, IdCreator, DateLastChange, IdLastChange)
            VALUES
            (?, ?, ?, GETDATE(), ?, GETDATE(), ?)
    )"));

	cout << "Enter the Project's name: ";
	const string projectName = enterText(true);
	statement.bind(0, projectName.c_str());

	cout << "Enter the project's description" << endl;
	cout << "Please press Enter only when you are done writing: ";
	const string description = enterText(false);
	statement.bind(1, description.c_str());

	//cout << "Enter your id: ";
	//const int creatorId = enterInt();
	statement.bind(2, &user.id);
	statement.bind(3, &user.id);
	statement.bind(4, &user.id);

	execute(statement);
}

void editProjectById(nanodbc::connection conn, const int& id, USER& user)
{
	nanodbc::statement statement(conn);
	nanodbc::prepare(statement, NANODBC_TEXT(R"(
        UPDATE [ProjectManagement].[dbo].[Projects]
        SET    
            Name = ?, 
			Description = ?,
			IdLastChange = ?,
			DateLastChange = GETDATE()
		WHERE	
			Id = ?
    )"));



	cout << "Enter the project's new name: ";
	const string name = enterText(true);
	statement.bind(0, name.c_str());

	cout << "Enter the project's new description: ";
	const string description = enterText(false);
	statement.bind(1, description.c_str());

	//cout << "Enter your id: ";
	//const int modifierId = enterInt();
	statement.bind(2, &user.id);

	statement.bind(3, &id);

	execute(statement);
}

void deleteProjectById(nanodbc::connection conn, const int& id)
{
	nanodbc::statement statement(conn);
	nanodbc::prepare(statement, NANODBC_TEXT(R"(
        UPDATE 
            Projects
		SET
			isDeleted = 1
        WHERE 
			Id = ?
    )"));

	statement.bind(0, &id);

	auto result = execute(statement);
}
