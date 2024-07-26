#pragma once

#include<iostream>
#include<string>
#include<vector>
#include<set>
#include<conio.h>
#include<windows.h>
#include<io.h>
#include"databaseManager.h"
using namespace std;


class Console {
public:
	Console();
	//连接数据库
	bool ConnectDatabase();
	//记录登录记录
	void WriteRecord();
	//设置光标位置是否隐藏状态
	void SetCursor(int x, int y, bool visible = false);
	//移动箭头，当获取到ENTER及ESC退出移动箭头
	void ArrowsMove(int x, int y, int low, int high, vector<char> operand = {});
	//输入信息
	void Input(string& str);
	//弹出提示信息的界面
	bool Alert(string content);
	//设计登录页面
	void LoadinPage();
	//控制函数控制函数逻辑
	void Control();
	//登录判断函数
	bool SignIn();
	//老师登录的主页面
	void MainPage();
	//设计页面方便后续复用
	void InfoPage(string title, string no = "", string name = "", string sex = "", string age = "", string dname = "", string password = "");
	//设计选择部门的功能，并返回选择的部门
	Department ChoiceDepartment();
	//老师注册的函数
	void AddTeacherInfo();
	//注销老师的函数
	void DeleteTeacherInfo();
	//配置数据库
	void Config();
	//管理学生
	void ManageStudent();
	//管理课程
	void ManageCourse();
	//选课表
	void ChoiceCourse();
	//学生注册函数
	void AddStudentInfo();
	//查询学生函数
	void SearchStudentInfo();
	//修改学生信息
	void ModifyStudentInfo(Person& p);
	//删除学生
	void DeleteStudentInfo(Person& p);
	//选择教师
	Person ChoiceTeacher();
	//课程信息表
	void CourseInfoPage(string title, string cno = "", string name = "", string tname = "");
	//增加课程
	void AddCourseInfo();
	//查询当前选课的所有学生
	void ShowCourseAllStudent(Course& c);
	//删除学生选课
	void DeleteStudentCourse(Person& p, Course& c);
	//删除课程
	void DeleteCourse(Course& c);
	COORD pos;
	CONSOLE_CURSOR_INFO cci;
	char operand;//操作符
	string account;
	string password;
	int mode = 1;
	databaseManager data;
	//数据库的设置信息
	string server = "localhost";
	string user = "root";
	string Dpassword = "123456";
	string database = "education";
	string charset = "GBK";
	char sqlStr[1024];
	string type[2] = { "教职工","学生" };
	set<Person, Compare> st;
	set<Person, Compare> te;
	set<Department, Compare> de;
	set<Course, Compare> co;
	set<Sc, Compare> sc;
};