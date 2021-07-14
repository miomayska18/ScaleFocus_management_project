#pragma once
#include <vector>
#include <nanodbc.h>
#include "Structures.h"

std::vector<TEAM> getTeams(nanodbc::connection conn);
void getAllTeams(nanodbc::connection conn);
void insertTeam(nanodbc::connection conn);
void editTeamById(nanodbc::connection conn, const int& id);
void deleteTeamById(nanodbc::connection conn, const int& id);
