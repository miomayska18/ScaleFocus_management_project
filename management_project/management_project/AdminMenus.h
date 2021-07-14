#pragma once


void adminLogMenu(nanodbc::connection conn, USER& user);
void adminTaskMenu(nanodbc::connection conn, USER& user);
void adminProjectMenu(nanodbc::connection conn, USER& user);
void adminTeamMenu(nanodbc::connection conn, USER& user);
void adminUserMenu(nanodbc::connection conn, USER& user);
void adminMenu(nanodbc::connection conn, USER& user);