#pragma once
#include <vector>
#include <nanodbc.h>
#include "Structures.h"

std::vector<TEAM> getTeams(nanodbc::connection conn);
void getAllTeams(nanodbc::connection conn);
void insertTeam(nanodbc::connection conn, USER& user);
void editTeamById(nanodbc::connection conn, const int& id, USER& user);
void deleteTeamById(nanodbc::connection conn, const int& id);
void insertUserIntoTeam(nanodbc::connection conn, const int& teamId);
