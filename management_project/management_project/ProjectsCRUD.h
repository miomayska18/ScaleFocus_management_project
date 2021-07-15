#pragma once
#include <vector>
#include <nanodbc.h>
#include "Structures.h"

std::vector<PROJECT> getProjects(nanodbc::connection conn);
void getAllProjects(nanodbc::connection conn);
void insertProject(nanodbc::connection conn, USER& user);
void editProjectById(nanodbc::connection conn, const int& id, USER& user);
void deleteProjectById(nanodbc::connection conn, const int& id);
void assignTeamToProject(nanodbc::connection conn, const int& projectId);