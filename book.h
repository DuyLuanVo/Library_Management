#ifndef BOOK_H
#define BOOK_H
#include <iostream>
#include <string>
#include <string.h>
#include <fstream>
using namespace std;

class book
{
public:
	string bookid;
	string bookname;
	string authorname;
	string type;
	book();
	book(string bookid, string bookname, string authorname, string type);
	void bookout();
};
#endif
