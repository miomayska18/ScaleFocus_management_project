#pragma once
#include "Structures.h"
#include "nanodbc.h"
#include <string>

USER getLoggedUserInfo(nanodbc::connection conn, std::string username, std::string password);