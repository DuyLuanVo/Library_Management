#ifndef STUDENT_H
#define STUDENT_H
#include <iostream>
#include <string>
#include <fstream>
using namespace std;
class student
{
public:
	string libid;
	string studentid;
	string studentname;
	int level;
	student();
	student(string libid, string studentid, string studentname, int level);
	void studentout();
};
#endif
