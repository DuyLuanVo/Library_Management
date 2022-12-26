#pragma once
#include <iostream>
#include <string>
#include <fstream>
using namespace std;
class admin
{
private:
	string pass;

public:
	admin(string s);
	string getpass();
	void changepass();
};