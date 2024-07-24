#include"databaseManager.h"

databaseManager::databaseManager() {

}
//构建数据库连接
bool databaseManager:: Connect(const char* server, const char* user, const char* password, const char* database, const char* charset) {
	//检查是否连接安全
	if (mysql_library_init(0, NULL, NULL) != 0)
	{
		
		return false;
	}
	//初始化mysql
	if (mysql_init(&my) == NULL)
	{
		return false;
	}
	//设置字符集
	if (mysql_options(&my, MYSQL_SET_CHARSET_NAME, charset) != 0)
	{
		return false;
	}
	//创建mysql连接
	if (mysql_real_connect(&my, server, user, password, database, 3306, NULL, 0) == NULL)
	{
		return false;
	}
	return true;
}

//记录查询记录 时间+记录+succeed，文件的写入
void databaseManager::log(string content) {
	SYSTEMTIME time;
	GetLocalTime(&time);
	char arr[128];
	sprintf_s(arr, "%04d/%02d/%02d %02d:%02d:%02d", time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond);
	string str = arr + content + " [succeed]\n";
	ofstream o("C:\edu\log.txt");
	if (o.is_open())
	{
		o << str;

	}
	o.close();
}
//执行sql语句
bool databaseManager::ExeSql(string sql) {
	//记录sql语句
	log(sql);
	if (mysql_query(&my, sql.c_str()) == 0)
	{
		result = mysql_store_result(&my);
		return true;
	}
	else {
		mysql_close(&my);
		return false;
	}
}
//键值对存储各种表，bool值表示是否遍历过
map<string, bool> databaseManager::GetTables() {
	map<string, bool> m;
	m.insert(pair<string, bool>("teacher",false));
	m.insert(pair<string, bool>("student",false));
	m.insert(pair<string, bool>("department",false));
	m.insert(pair<string, bool>("course",false));
	m.insert(pair<string, bool>("sc",false));
	if (ExeSql("show tables;"))
	{
		//定义count统计result结果集的列数
		unsigned int count = mysql_num_fields(result);
		MYSQL_ROW row = NULL;
		//row是一个数组  mysql_fecth_row获取result一行的内容
		row = mysql_fetch_row(result);
		while (row != NULL)
		{
			for (int i = 0; i < count; i++)
			{
				if (row[i] != NULL)
				{
					if (m[row[i]] == false)
					{
						m[row[i]] = true;
					}
				}
			}
			row = mysql_fetch_row(result);
		}
	}
	return m;

}
//查询各个表是否创建否则就调用创建函数
void databaseManager::Initialize() {
	map<string, bool> tables = GetTables();
	if (tables["teacher"] == false)
	{
		createPerson(0);
	}
	if (tables["student"] == false)
	{
		createPerson(1);
	}
	if (tables["department"] == false)
	{
		createDepartment();
	}
	if (tables["course"] == false)
	{
		createCourse();
	}
	if (tables["sc"] == false)
	{
		createSc();
	}
}
//新建部门表 并直接插入初始部门信息
void databaseManager::createDepartment() {
	string str = "create table department(dno varchar(10) primary key,name varchar(10) not null);";
	ExeSql(str);
	str = "insert into department values('1','计算机科学与技术'),('2','土木工程'),('3','市场营销'),\
	('4','物流管理'),('5','人工智能');";
}
//获取部门表全部信息
set<Department, Compare> databaseManager::GetDepartment(string sql) {
	set<Department, Compare> res;
	if (ExeSql(sql)) {
		unsigned int count = mysql_num_fields(result);
		MYSQL_ROW row = NULL;
		row = mysql_fetch_row(result);
		while (row != NULL)
		{
			string arr[4] = {};
			for (int i = 0; i < count; i++)
			{

				if (row[i] != NULL)
				{
					arr[i] = row[i];
				}
			}
			res.insert(Department(arr[0], arr[1]));
			row = mysql_fetch_row(result);
		}
	}
	return res;
}

//mode标识是创建student/teacher表  两者结构相同只是名字不同
void databaseManager::createPerson(int mode) {
	char temp[] ="create table %s(no varchar(20) primary key,name varchar(10) not null,\
	sex char(1),age char(4),dno varchar(10) not null,password varchar(20) not null,\
	foreign key(dno) references department(dno) on delete cascade on update cascade);";
	char str[1024];
	if (mode == 0)
	{
		sprintf_s(str, temp, "teacher");
	}
	if (mode == 1)
	{
		sprintf_s(str, temp,"student");
	}
	ExeSql(str);
}
//获取Person表的全部信息
set<Person, Compare> databaseManager::GetPerson(string sql) {
	set<Person, Compare> res;
	if (ExeSql(sql)) {
		unsigned int count = mysql_num_fields(result);
		MYSQL_ROW row = NULL;
		row = mysql_fetch_row(result);
		while (row != NULL)
		{
			string arr[6] = {};
			for (int i = 0; i < count; i++)
			{
				if (row[i] != NULL)
				{
					arr[i] = row[i];
				}
			}
			res.insert(Person(arr[0], arr[1], arr[2], arr[3], arr[4], arr[5]));
			row = mysql_fetch_row(result);
		}
	}
	return res;
}
void databaseManager::createCourse() {
	string sql = "create table course(cno varchar(10) primary key,name varchar(10) not null,\
	tno varchar(10),foreign key(tno) references teacher(no) on delete cascade on update cascade);";
	ExeSql(sql);
}
//获取课程表的全部信息
set<Course, Compare> databaseManager::GetCourse(string sql) {
	set<Course, Compare> res;
	if (ExeSql(sql))
	{
		unsigned int count = mysql_num_fields(result);
		MYSQL_ROW row = NULL;
		row = mysql_fetch_row(result);
		while (row != NULL)
		{
			string arr[4] = {};
			for (int i = 0; i < count; i++)
			{
				if (row[i] != NULL)
				{
					arr[i] = row[i];
				}
			}
			res.insert(Course(arr[0], arr[1], arr[2]));
			row = mysql_fetch_row(result);
		}
	}
	return res;
}
void databaseManager::createSc() {
	string sql = "create table sc(sno varchar(10),cno varchar(10),score char(4),\
	primary key(sno,cno),foreign key(sno) references student(no) on delete cascade on update cascade,\
	foreign key(cno) references course(cno) on delete cascade on update cascade);";
	ExeSql(sql);
}
//获取Sc表中的全部信息
set<Sc, Compare> databaseManager::GetSc(string sql){
	set<Sc, Compare> res;
	if (ExeSql(sql))
	{
		unsigned int count = mysql_num_fields(result);
		MYSQL_ROW row = NULL;
		row = mysql_fetch_row(result);
		while (row != NULL) {
			string arr[4] = {};
			for (int i = 0; i < count; i++)
			{
				if (row[i] != NULL)
				{
					arr[i] = row[i];
				}
			}
			res.insert(Sc(arr[0], arr[1], arr[2]));
			row = mysql_fetch_row(result);
		}
	}
	return res;
}

