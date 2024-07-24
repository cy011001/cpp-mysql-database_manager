#pragma once
#include<iostream>
#include<string>
using namespace std;
//定义基类具有编号和名字
class Base {
public:
	Base();
	Base(string number, string name);
	void setNumber(string number);
	string getNumber();
	void setName(string name);
	string getName();
protected:
	string number;
	string name;
};
//定义person类继承基类
class Person :public Base{
public:
	Person();
	Person(string number, string name, string sex, string age, string dname, string password);
	void setSex(string sex);
	string getSex();
	void setAge(string age);
	string getAge();
	void setDname(string dname);
	string getDname();
	void setPassword(string password);
	string getPassword();

protected:
	string sex;
	string age;
	string dname;
	string password;
};

//定义Course类继承基类
class Course :public Base{
public:
	Course();
	Course(string number, string name, string tname);
	void setTname(string tname);
	string getTname();

	bool status;
protected:
	string tname;
};
//定义Department类继承基类
class Department :public Base {
public:
	Department();
	Department(string number, string name);

};

//Sc类
class Sc {
public:
	Sc();
	Sc(string sno, string cno, string score);
	void setSno(string sno);
	string getSno();
	void setCno(string cno);
	string getCno();
	void setScore(string score);
	string getScore();
protected:
	string sno;
	string cno;
	string score;
};
//重载compare函数作为上述类的排序函数
class Compare {
public:
	bool operator()(Department t1, Department t2) const {
		return t1.getNumber().compare(t2.getNumber()) < 0;
	}
	bool operator()(Person t1, Person t2) const {
		return t1.getNumber().compare(t2.getNumber()) < 0;
	}
	bool operator()(Course t1, Course t2) const {
		return t1.getNumber().compare(t2.getNumber()) < 0;
	}
	bool operator()(Sc t1, Sc t2) const {
		return t1.getCno().compare(t2.getCno()) < 0;
	}
};