#pragma once
#include<mysql.h>
#include<set>
#include"table.h"
#include<vector>
#include<fstream>
#include<map>
using namespace std;


class databaseManager {
public:
	databaseManager();
	//连接数据库
	bool Connect(const char* server, const char* user, const char* password, const char* database, const char* charset = "gbk");
	//记录查询记录 时间+记录+succeed，文件的写入
	void log(string content);
	//执行sql语句
	bool ExeSql(string sql);
	//获取所有的表
	map<string, bool> GetTables();
	//初始化表，查漏补缺
	void Initialize();
	//创建部门表
	void createDepartment();
	//获取部门表
	set<Department, Compare> GetDepartment(string sql = "select * from Department;");
	void createPerson(int mode);
	set<Person, Compare> GetPerson(string sql = "select * from Person;");
	void createCourse();
	void createSc();
	set<Course, Compare> GetCourse(string sql = "select * from Course;");
	set<Sc, Compare> GetSc(string sql = "select * from Sc;");
	MYSQL my;
	//查询结果集
	MYSQL_RES* result;
};
