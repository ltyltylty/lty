#include "func.h"

MYSQL_RES* search_all(MYSQL* con, char* table_name)
{
	char sql_line[1024] ="";
	int rt ;
	sprintf(sql_line,"select * from %s",table_name);
	rt = mysql_real_query(con,sql_line,strlen(sql_line));
	if(rt )
	{
		printf("query error ! \n");
		return NULL ;
	}
	return mysql_store_result(con);
}
MYSQL_RES* search_by_name(MYSQL* con, char* table_name,char* stu_name)
{
	char sql_line[1024] ="";
	int rt ;
	sprintf(sql_line,"select * from %s where name=\'%s\'",table_name,stu_name);
	rt = mysql_real_query(con,sql_line,strlen(sql_line));
	if(rt )
	{
		printf("query error ! \n");
		return NULL ;
	}
	return mysql_store_result(con);
}
MYSQL_RES* search_by_id(MYSQL* con, char* table_name,int stu_id)
{
	char sql_line[1024] ="";
	int rt ;
	sprintf(sql_line,"select * from %s where id=\'%d\'",table_name,stu_id);
	rt = mysql_real_query(con,sql_line,strlen(sql_line));
	if(rt )
	{
		printf("query error ! \n");
		return NULL ;
	}
	return mysql_store_result(con);
}
void show_result(MYSQL_RES* res)
{
	int index_field,count ;
	MYSQL_ROW row ;
	count = 0 ;
	printf("\n-------------------------------------------------------\n");
	while(row = mysql_fetch_row(res))
	{
		for(index_field = 0 ; index_field < mysql_num_fields(res); index_field ++ )
		{
			printf("%10s\t|",row[index_field]);
		}
		count ++ ;
		printf("\n---------------------------------------\n");
	}
	printf("total results:%d\n", count);
	mysql_free_result(res);
}
void update_infor(MYSQL*con, char* table_name, char* stu_name,char *stu_gender,double stu_score,int id)
{
	char sql_line[1024] ="";
	int rt ;
	sprintf(sql_line,"update %s set name=\'%s\',sex=\'%s\',score=%lf where id=%d",table_name,stu_name,stu_gender,stu_score,id);
	rt = mysql_real_query(con,sql_line,strlen(sql_line));
	if(rt )
	{
		printf("query error ! \n");
		return ;
	}
	return ;
}
void insert(MYSQL *con,char*table,int id,char*stu_name,char* stu_gender,double stu_score)
{
	char sql_line[1024] ="";
	int rt ;
	sprintf(sql_line,"insert into %s values(%d,\'%s\',\'%s\',%f)",table,id,stu_name,stu_gender,stu_score);
	rt = mysql_real_query(con,sql_line,strlen(sql_line));
	if(rt )
	{
		printf("query error ! \n");
		return ;
	}
	printf("insert success!\n");
	return ;
}
void delete_by_id(MYSQL* con,char* table, int stu_id)
{
	char sql_line[1024] ="";
	int rt ;
	sprintf(sql_line,"delete from %s where id=%d",table,stu_id);
	rt = mysql_real_query(con,sql_line,strlen(sql_line));
	if(rt )
	{
		printf("query error ! \n");
		return ;
	}
	return ;
}

void update_acc(MYSQL*con, char* table_name, char *acc_name,char *acc_pwd,int acc_role)
{
	char sql_line[1024] ="";
	int rt ;
	sprintf(sql_line,"update %s set password=\'%s\',role=%d where name=\'%s\'",table_name,acc_pwd,acc_role,acc_name);
	rt = mysql_real_query(con,sql_line,strlen(sql_line));
	if(rt )
	{
		printf("query error ! \n");
		return ;
	}
	printf("update success!\n");
	return ;
}



int role_confirm(MYSQL* con,char* table)
{
	int role,i,rt,count = 0,a=1;
	char name[20];
	char password[10];
	char sql_line[1024] ="";
	MYSQL_ROW row ;
	MYSQL_RES* res ;
	printf("*******************************************************************************\n");
	printf("***************************Student Information Management System***************\n");
	printf("*******************************************************************************\n");
	while(a==1){
	printf("enter user_name:");
	gets(name);
	printf("enter user_password:");
	for(i=0;i<10;i++)
	{
		password[i]=getch();
		if(password[i]==13)
		{
			password[i]='\0';
			break;
		}else if(password[i]==8)
		{
			printf("\b");
			printf(" ");
			printf("\b");
			i=i-2;
		}else{
			printf("*");
		}
	}
	sprintf(sql_line,"select * from %s where (name,password)=(\'%s\',\'%s\')",table,name,password);
	mysql_real_query(con,sql_line,strlen(sql_line));
	res = mysql_store_result(con);
	if(row = mysql_fetch_row(res))
	{
		role=atoi(row[2]);
		mysql_free_result(res);
		return role;
	}
	printf("没有此账户！请重输！\n");
	mysql_free_result(res);
	}
}
	
int show_system_menu(int role)
{
		int i;
		printf("*******************************************************************************\n");
		printf("***************************Student Information Management System***************\n");
		printf("*******************************************************************************\n");
	if(role==0)
	{
		printf("*******************************欢迎来到管理员界面!*****************************\n");
		printf("1.search student information\n");
		printf("2.add student information\n");
		printf("3.update student information\n");
		printf("4.delete student information\n");
		printf("5.add user account\n");
		printf("6.update user account\n");
		printf("7.delete user account\n");
		printf("8.search user account\n");
		printf("9.exit\n");
		printf("select a number:");
		scanf("%d",&i);
		return i;
	}else{
		printf("*******************************欢迎来到学生界面!*******************************\n");
		printf("1.search student information\n");
		printf("9.exit\n");
		printf("select a number:");
		scanf("%d",&i);
		return i;
	}
}

int show_search_menu(int role)
{
		int i;
		printf("*******************************************************************************\n");
		printf("***************************Student Information Management System***************\n");
		printf("*******************************************************************************\n");
	if(role==0)
	{
		printf("0.search all\n");
		printf("1.search by name\n");
		printf("2.search by id\n");
		printf("3.return\n");
		printf("select a number:");
		scanf("%d",&i);
		return i;
	}else{
		printf("1.search by name\n");
		printf("2.search by id\n");
		printf("3.return\n");
		printf("select a number:");
		scanf("%d",&i);
		return i;
	}
}


void insert_account(MYSQL *con,char*table,char *name,char *password,int role)
{
	char sql_line[1024] ="";
	int rt ;
	sprintf(sql_line,"insert into %s values(\'%s\',\'%s\',%d)",table,name,password,role);
	rt = mysql_real_query(con,sql_line,strlen(sql_line));
	if(rt )
	{
		printf("query error ! \n");
		return ;
	}
	printf("insert success!\n");
	return ;
}

void delete_account(MYSQL* con,char* table, char *acc_name)
{
	char sql_line[1024] ="";
	int rt ;
	sprintf(sql_line,"delete from %s where name=\'%s\'",table,acc_name);
	rt = mysql_real_query(con,sql_line,strlen(sql_line));
	if(rt )
	{
		printf("query error ! \n");
		return ;
	}
	printf("delete success!\n");
	return ;
}







	
