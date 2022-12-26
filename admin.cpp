#include "admin.h"
admin::admin(string s)
{
	this->pass = s;
}
string admin::getpass()
{
	return this->pass;
}
void admin::changepass()
{
	cout << "Input new password: ";
	string s1;
	cout << "\033[31m";
	cin >> s1;
	cout << "\033[0m";
	this->pass = s1;
	cout << "Your password had change" << endl;
	return;
}