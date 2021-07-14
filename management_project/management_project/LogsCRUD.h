#pragma once
#include <vector>
#include <nanodbc.h>
#include "Structures.h"

std::vector<LOG> getLogs(nanodbc::connection conn);
void getAllLogs(nanodbc::connection conn);
void insertLog(nanodbc::connection conn);
void editLogById(nanodbc::connection conn, const int& id);
void deleteLogById(nanodbc::connection conn, const int& id);
void getAllCertainLogs(nanodbc::connection conn, const int& taskId);