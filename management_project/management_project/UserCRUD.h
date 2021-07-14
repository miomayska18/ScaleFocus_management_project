#pragma once
#include <vector>
#include <nanodbc.h>
#include "Structures.h"


std::vector<USER> getUsers(nanodbc::connection conn);
void getAllUsers(nanodbc::connection conn, USER& user);
void insertUser(nanodbc::connection conn);
void editUserById(nanodbc::connection conn, const int& id);
void deleteUserById(nanodbc::connection conn, const int& id);
