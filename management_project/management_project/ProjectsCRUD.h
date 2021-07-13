#pragma once
#pragma once
#include <vector>
#include <nanodbc.h>
#include "Structures.h"

std::vector<PROJECT> getProjects(nanodbc::connection conn);
void getAllProjects(nanodbc::connection conn);
void insertProject(nanodbc::connection conn);
void editProjectById(nanodbc::connection conn, const int& id);
bool deleteProjectById(nanodbc::connection conn, const int& id);