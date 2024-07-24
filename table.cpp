#include<iostream>
#include"table.h"
using namespace std;
Base::Base() {

}
Base::Base(string number, string name) {
	this->number = number;
	this->name = name;
}
void Base::setNumber(string number) {
	this->number = number;
}
string Base::getNumber() {
	return this->number;
}
void Base::setName(string name) {
	this->name = name;
}
string Base::getName() {
	return this->name;
}
Person::Person() {

}
Person::Person(string number, string name, string sex, string age, string dname, string password) :Base(number, name) {
	this->sex = sex;
	this->age = age;
	this->dname = dname;
	this->password = password;
}
void Person::setSex(string sex) {
	this->sex = sex;
}
string Person::getSex() {
	return this->sex;
}
void Person::setAge(string age) {
	this->age = age;
}
string Person::getAge() {
	return this->age;
}
void Person::setDname(string dname) {
	this->dname = dname;
}
string Person::getDname() {
	return this->dname;
}
void Person::setPassword(string password) {
	this->password = password;
}
string Person::getPassword() {
	return this->password;
}
Course::Course() {

}
Course::Course(string number, string name, string tname) :Base(number, name) {
	this->tname = tname;
}
void Course::setTname(string tname) {
	this->tname = tname;
}
string Course::getTname() {
	return this->tname;
}
Department::Department() {

}
Department::Department(string number, string name) :Base(number, name) {

}
Sc::Sc() {

}
Sc::Sc(string sno, string cno, string score) {
	this->sno = sno;
	this->cno = cno;
	this->score = score;
}
void Sc::setSno(string sno) {
	this->sno = sno;
}
string Sc::getSno() {
	return this->sno;
}
void Sc::setCno(string cno) {
	this->cno = cno;
}
string Sc::getCno() {
	return this->cno;
}
void Sc::setScore(string score) {
	this->score = score;
}
string Sc::getScore() {
	return this->score;
}