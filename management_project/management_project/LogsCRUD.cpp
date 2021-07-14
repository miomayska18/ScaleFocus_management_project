#include <iostream>
#include "Structures.h"
#include <nanodbc.h>
#include <vector>
#include <string>
#include "InsertFunctions.h"
using namespace std;


vector<LOG> getLogs(nanodbc::connection conn)
{
	vector<LOG> logs;
	nanodbc::statement statement(conn);
	nanodbc::prepare(statement, NANODBC_TEXT(R"( 
        SELECT *
            FROM [ProjectManagement].[dbo].[Logs]
		WHERE
			IsDelted<>1
    )"));

	auto result = execute(statement);

	while (result.next())
	{
		LOG log;
		log.id = result.get<int>("Id");
		log.userId = result.get<int>("UserId");
		log.timeSpent = result.get<double>("TimeSpent");
		log.date = result.get<nanodbc::string>("Date");
		log.taskId = result.get<int>("TaskId");

		logs.push_back(log);
	}

	return logs;
}

void getAllLogs(nanodbc::connection conn)
{
	vector<LOG> logs = getLogs(conn);

	for (size_t i = 0; i < logs.size(); i++)
	{
		logs[i].displayLog();
		cout << endl;
	}

}

void insertLog(nanodbc::connection conn)
{
	nanodbc::statement statement(conn);
	nanodbc::prepare(statement, NANODBC_TEXT(R"(
        INSERT INTO
            [ProjectManagement].[dbo].[Logs]
            (UserId, TimeSpent, Date, TaskId)
            VALUES
            (?, ?, ?, ?)
    )"));

	cout << "Enter the user's id: ";
	const int userId = enterInt();
	statement.bind(0, &userId);

	cout << "Enter the time spent working (in hours): ";
	const double timeSpent = enterDouble();
	statement.bind(1, &timeSpent);

	cout << "Enter the date (format: 2021-07-13): ";
	const string date = enterText(true);
	statement.bind(2, date.c_str());

	cout << "Enter the task's id: ";
	const int taskId = enterInt();
	statement.bind(3, &taskId);

	execute(statement);
}

void editLogById(nanodbc::connection conn, const int& id)
{
	nanodbc::statement statement(conn);
	nanodbc::prepare(statement, NANODBC_TEXT(R"(
        UPDATE [ProjectManagement].[dbo].[Logs]
        SET    
            UserId = ?, 
			TimeSpent = ?,
			Date = ?,
			TaskId = ?
		WHERE	
			Id = ?
    )"));



	cout << "Enter the new assigned user's id: ";
	const int userId = enterInt();
	statement.bind(0, &userId);

	cout << "Enter the time spent (in hours): ";
	const double timeSpent = enterDouble();
	statement.bind(1, &timeSpent);

	cout << "Enter the date (format: 2021-07-13): ";
	const string date = enterText(true);
	statement.bind(2, date.c_str());

	cout << "Enter the task's id: ";
	const int taskId = enterInt();
	statement.bind(3, &taskId);

	statement.bind(4, &id);

	execute(statement);
}

void deleteLogById(nanodbc::connection conn, const int& id)
{
	nanodbc::statement statement(conn);
	nanodbc::prepare(statement, NANODBC_TEXT(R"(
        UPDATE 
            Logs
		SET
			IsDeleted = 1
        WHERE 
			Id = ?
    )"));

	statement.bind(0, &id);

	auto result = execute(statement);

}
