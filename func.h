#ifndef __FUNC_H__
#define __FUNC_H__
#include"sims.h"

MYSQL_RES* search_all(MYSQL* con, char* table_name);
MYSQL_RES* search_by_name(MYSQL* con, char* table_name,char* stu_name);
MYSQL_RES* search_by_id(MYSQL* con, char* table_name,int stu_id);
void show_result(MYSQL_RES* res);
void update_infor(MYSQL*con, char* table_name, char* stu_name,char *stu_gender,double stu_score,int id);
void insert(MYSQL *con,char*table,int id,char*stu_name,char* stu_gender,double stu_score);
void delete_by_id(MYSQL* con,char* table, int stu_id);

int role_confirm(MYSQL* con,char* table);

void insert_account(MYSQL *con,char*table,char *name,char *password,int role);

void delete_account(MYSQL* con,char* table, char *acc_name);

void update_acc(MYSQL*con, char* table_name,char *acc_name, char* acc_pwd,int acc_role);

int show_system_menu(int role);

int show_search_menu(int role);




#endif