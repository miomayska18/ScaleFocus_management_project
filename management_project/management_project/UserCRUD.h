#pragma once
#include <vector>
#include <nanodbc.h>
#include "Structures.h"


std::vector<USER> getUsers(nanodbc::connection conn);
void getAllUsers(nanodbc::connection conn);
void insertUser(nanodbc::connection conn, USER& user);
void editUserById(nanodbc::connection conn, const int& id, USER& user);
void deleteUserById(nanodbc::connection conn, const int& id);
