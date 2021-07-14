#pragma once
#include <vector>
#include <nanodbc.h>
#include "Structures.h"

std::vector<TASK> getTasks(nanodbc::connection conn);
void getAllTasks(nanodbc::connection conn);
void insertTask(nanodbc::connection conn, USER& user);
void editTaskById(nanodbc::connection conn, const int& id, USER& user);
void deleteTaskById(nanodbc::connection conn, const int& id);