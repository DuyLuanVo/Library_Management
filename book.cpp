#include "book.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <iomanip>
#include <ctype.h>
#define maxsize 100
struct booknode
{
	book data;
	int amount;
	int topnumber;
	booknode *pnext;
	booknode *pback;
};
struct bamnode
{
	book data;
	bamnode *pnext;
};
bamnode *hashtable[maxsize];
struct booklist
{
	booknode *phead;
	booknode *ptail;
};

book::book(){};

book::book(string bookid, string bookname, string authorname, string type)
{
	this->bookid = bookid;
	this->bookname = bookname;
	this->authorname = authorname;
	this->type = type;
}

void book::bookout()
{
	cout << setw(2) << left << "|";
	cout << setw(10) << left << this->bookid;
	cout << setw(2) << left << "|";
	cout << setw(48) << left << this->bookname;
	cout << setw(2) << left << "|";
	cout << setw(38) << left << this->authorname;
	cout << setw(2) << left << "|";
	cout << setw(14) << left << this->type;
	cout << setw(2) << left << "|";
}

void createbooklist(booklist &blist)
{
	blist.phead = blist.ptail = NULL;
}

booknode *inputbookdata(book b, int amount, int topnum)
{
	booknode *p = new booknode();
	p->pnext = p->pback = NULL;
	p->data = b;
	p->amount = amount;
	p->topnumber = topnum;
	return p;
}

void bookinputtail(booklist &blist, booknode *p)
{
	if (blist.phead == NULL)
	{
		blist.phead = blist.ptail = p;
	}
	else
	{
		blist.ptail->pnext = p;
		p->pback = blist.ptail;
		blist.ptail = p;
	}
}

void book_face()
{
	cout << setw(3) << left << "|";
	cout << setw(9) << left << "Book ID";
	cout << setw(20) << left << "|";
	cout << setw(30) << left << "Book title";
	cout << setw(15) << left << "|";
	cout << setw(25) << left << "Author name";
	cout << setw(6) << left << "|";
	cout << setw(10) << left << "Type";
	cout << setw(3) << left << "|";
	cout << setw(8) << left << "Amount";
	cout << setw(1) << left << "|";
	cout << setw(12) << left << "Top Borrow"
		 << "|" << endl;
}

void bookprint(booklist blist)
{
	if (blist.phead == NULL)
		cout << "No books in the library" << endl;
	else
	{

		cout << endl;
		cout << "                +++++++++++++++++++++++++++ LIST OF BOOKS CURRENTLY IN THE LIBRARY +++++++++++++++++++++++++++ " << endl
			 << endl;
		cout << "                ______________________________________________________________________________________________" << endl
			 << endl;
		book_face();
		for (booknode *k = blist.phead; k != NULL; k = k->pnext)
		{
			k->data.bookout();
			cout << setw(9) << left << k->amount;
			cout << setw(2) << left << "|";
			cout << setw(11) << left << k->topnumber << "|" << endl;
		}
	}
}

int returnmaxborrow(booklist blist)
{
	int max = blist.phead->topnumber;
	for (booknode *k = blist.phead->pnext; k != NULL; k = k->pnext)
	{
		if (k->topnumber > max)
		{
			max = k->topnumber;
		}
	}
	return max;
}

void inserthashtable(int num, book bo)
{
	int index = num;
	bamnode *p = new bamnode();
	p->data.bookid = bo.bookid;
	p->data.bookname = bo.bookname;
	p->data.authorname = bo.authorname;
	p->data.type = bo.type;
	p->pnext = NULL;
	if (hashtable[index] == NULL)
	{
		hashtable[index] = p;
		return;
	}
	p->pnext = hashtable[index];
	hashtable[index] = p;
}

void printtop5book(booklist blist)
{
	int index = returnmaxborrow(blist);
	int dem = 1;
	cout << endl;
	cout << "                ++++++++++++++++++++++++++++++++ TOP FIVE MOST BORROWED BOOKS ++++++++++++++++++++++++++++++++ " << endl
		 << endl;
	cout << "                ______________________________________________________________________________________________" << endl
		 << endl;
	cout << setw(3) << left << "|";
	cout << setw(9) << left << "Book ID";
	cout << setw(20) << left << "|";
	cout << setw(30) << left << "Book title";
	cout << setw(15) << left << "|";
	cout << setw(25) << left << "Author name";
	cout << setw(6) << left << "|";
	cout << setw(10) << left << "Type";
	cout << setw(1) << left << "|";
	cout << setw(12) << left << "Top Borrow"
		 << "|" << endl;
	while (dem <= 5)
	{
		bamnode *tam = hashtable[index];
		if (hashtable[index] != NULL)
		{
			for (bamnode *k = tam; k != NULL; k = k->pnext)
			{
				k->data.bookout();
				cout << setw(11) << left << index << "|" << endl;
				dem++;
			}
		}
		index--;
		if (index == -1)
			break;
	}
}

void bookwork(booklist &blist)
{
	string boid, bname, aname, btype, tam;
	int number, topnum;
	ifstream bookfile;
	bookfile.open("ipbook.txt", ios::in);
	while (!bookfile.eof())
	{
		getline(bookfile, boid, ';');
		if (boid == "")
			return;
		getline(bookfile, bname, ';');
		getline(bookfile, aname, ';');
		bookfile >> number;
		getline(bookfile, btype, ';');
		bookfile >> topnum;
		getline(bookfile, tam);
		book b(boid, bname, aname, btype);
		booknode *p = inputbookdata(b, number, topnum);
		bookinputtail(blist, p);
	}
}
void makehash(booklist blist)
{
	for (booknode *k = blist.phead; k != NULL; k = k->pnext)
	{
		inserthashtable(k->topnumber, k->data);
	}
}
int clean_stdin()
{
	while (getchar() != '\n')
	{
	}
	return 1;
}

bool checkspace(string s)
{
	for (int i = 0; i < s.length(); i++)
	{
		if (isspace(s[i]))
		{
			return false;
		}
	}
	return true;
}

void add_book(booklist &blist)
{
	string boid, bname, aname, btype;
	int number;
	int n;
	char c;
	do
	{
		cout << "Enter the number of books to add: ";
	} while (((scanf("%d%c", &n, &c) != 2 || c != '\n') && clean_stdin()));
	fflush(stdin);
	for (int i = 1; i <= n; i++)
	{
		cout << "Enter the " << i << "st book information" << endl;
		cout << "Enter book ID: ";
		getline(cin, boid);
		while (boid.front() != 'B' || boid.size() < 5 || boid.size() > 7 || checkspace(boid) == false)
		{
			if (boid.front() != 'B')
			{
				cout << "The first character should be 'B'" << endl
					 << "Re-enter book ID: ";
				getline(cin, boid);
			}
			else if (boid.size() < 5 || boid.size() > 7)
			{
				cout << "Book ID from 5 to 7 characters" << endl
					 << "Re-enter book ID: ";
				getline(cin, boid);
			}
			else if (checkspace(boid) == false)
			{
				cout << "Book ID no space" << endl
					 << "Re-enter book ID: ";
				getline(cin, boid);
			}
		}

		for (booknode *k = blist.phead; k != NULL; k = k->pnext)
		{
			if (boid == k->data.bookid)
			{
				cout << "\033[33m";
				cout << "This book is already in the library. Edit as needed" << endl;
				cout << "\033[0m";
				return;
			}
		}
		cout << "Enter book title: ";
		getline(cin, bname);
		cout << "Enter author name: ";
		getline(cin, aname);
		do
		{
			cout << "Enter the number of books: ";
		} while (((scanf("%d%c", &number, &c) != 2 || c != '\n') && clean_stdin()));
		cout << "Enter a book type: ";
		getline(cin, btype);
		book b(boid, bname, aname, btype);
		booknode *p = inputbookdata(b, number, 0);
		bookinputtail(blist, p);
	}
}

void edit_book(booklist &blist)
{
	string idedit;
	bool flag_edit;
	if (blist.phead == NULL)
	{
		cout << "No books in the library to edit" << endl;
		flag_edit = true;
		return;
	}
	cout << "Enter book ID to edit: ";
	cin >> idedit;
	for (booknode *temp = blist.phead; temp != NULL; temp = temp->pnext)
	{
		if (idedit == temp->data.bookid)
		{
			flag_edit = true;
			string boid, bname, aname, btype;
			int amnt, s;
			char edc;
			cout << "The book information you need to edit is: " << endl;
			book_face();
			temp->data.bookout();
			cout << setw(9) << left << temp->amount;
			cout << setw(2) << left << "|";
			cout << setw(11) << left << temp->topnumber << "|" << endl;
			cout << "What attributes of a book you want to edit with ID: " << temp->data.bookid << "?" << endl;
			system("pause");
			while (10)
			{
				cout << "1. Book title" << endl;
				cout << "2. Author name" << endl;
				cout << "3. Amount" << endl;
				cout << "4. Type" << endl;
				cout << "5. Back to main menu" << endl;
				do
				{
					cout << "Enter your selection for books with ID " << temp->data.bookid << ": ";
				} while (((scanf("%d%c", &s, &edc) != 2 || edc != '\n') && clean_stdin()));
				system("cls");
				if (s == 1)
				{
					fflush(stdin);
					cout << "Enter book title: ";
					getline(cin, bname);
					temp->data.bookname = bname;
					cout << "\033[32m";
					cout << "Successfully edit the title of a book with ID: " << temp->data.bookid << endl;
					cout << "\033[0m";
				}
				else if (s == 2)
				{
					fflush(stdin);
					cout << "Enter author name: ";
					getline(cin, aname);
					temp->data.authorname = aname;
					cout << "\033[32m";
					cout << "Successfully edit the author name of a book with ID: " << temp->data.bookid << endl;
					cout << "\033[0m";
				}
				else if (s == 3)
				{
					fflush(stdin);
					do
					{
						cout << "Enter the number of books: ";
					} while (((scanf("%d%c", &amnt, &edc) != 2 || edc != '\n') && clean_stdin()));
					temp->amount = amnt;
					cout << "\033[32m";
					cout << "Successfully edit the number of books with ID: " << temp->data.bookid << endl;
					cout << "\033[0m";
				}
				else if (s == 4)
				{
					fflush(stdin);
					cout << "Enter a book type: ";
					getline(cin, btype);
					temp->data.type = btype;
					cout << "\033[32m";
					cout << "Successfully edit the type of a book with ID: " << temp->data.bookid << endl;
					cout << "\033[0m";
				}
				else if (s == 5)
				{
					return;
				}
			}
		}
	}
	if (flag_edit == false)
	{
		cout << "Can't find the book ID you need" << endl;
	}
}

void delete_first(booklist &blist)
{
	booknode *dlf = blist.phead;
	if (blist.phead == NULL)
		cout << "No books in the library" << endl;
	else
	{
		blist.phead = dlf->pnext;
		delete dlf;
	}
}

void delete_last(booklist &blist)
{
	booknode *dll = blist.phead;
	booknode *dlr = new booknode;
	if (blist.phead == NULL)
		cout << "No books in the library";
	else
	{
		while (dll != blist.ptail)
		{
			dlr = dll;
			dll = dll->pnext;
		}
		blist.ptail = dlr;
		dlr->pnext = NULL;
		delete dll;
	}
}

void delete_book(booklist &blist)
{
	string iddelete;
	bool flag_delete;
	if (blist.phead == NULL)
	{
		cout << "No books in the library" << endl;
		flag_delete = true;
		return;
	}
	cout << "Enter the ID of the book to be deleted: ";
	cin >> iddelete;
	if (iddelete == blist.phead->data.bookid)
	{
		cout << "The book information you need to remove is: " << endl;
		book_face();
		blist.phead->data.bookout();
		cout << setw(9) << left << blist.phead->amount;
		cout << setw(2) << left << "|";
		cout << setw(11) << left << blist.phead->topnumber << "|" << endl;
		delete_first(blist);
		cout << "\033[32m";
		cout << "Successful deletion" << endl;
		cout << "\033[0m";
		flag_delete = true;
		return;
	}
	if (iddelete == blist.ptail->data.bookid)
	{
		cout << "The book information you need to remove is: " << endl;
		book_face();
		blist.ptail->data.bookout();
		cout << setw(9) << left << blist.ptail->amount;
		cout << setw(2) << left << "|";
		cout << setw(11) << left << blist.ptail->topnumber << "|" << endl;
		delete_last(blist);
		cout << "\033[32m";
		cout << "Successful deletion" << endl;
		cout << "\033[0m";
		flag_delete = true;
	}
	for (booknode *tempdlt = blist.phead; tempdlt != NULL; tempdlt = tempdlt->pnext)
	{
		if (iddelete == tempdlt->data.bookid)
		{
			flag_delete = true;
			cout << "The book information you need to remove is: " << endl;
			book_face();
			tempdlt->data.bookout();
			cout << setw(9) << left << tempdlt->amount;
			cout << setw(2) << left << "|";
			cout << setw(11) << left << tempdlt->topnumber << "|" << endl;
			tempdlt->pnext->pback = tempdlt->pback;
			tempdlt->pback->pnext = tempdlt->pnext;
			delete tempdlt;
			cout << "\033[32m";
			cout << "Successful deletion" << endl;
			cout << "\033[0m";
			return;
		}
	}
	if (flag_delete == false)
	{
		cout << "Can't find the book ID you need to delete" << endl;
		return;
	}
}

void search_book(booklist blist)
{
	string idsearch;
	bool flag_sr;
	cout << "Enter the book id to find: ";
	cin >> idsearch;
	for (booknode *tempsr = blist.phead; tempsr != NULL; tempsr = tempsr->pnext)
	{
		if (idsearch == tempsr->data.bookid)
		{
			cout << "The book information you seek is:" << endl;
			book_face();
			tempsr->data.bookout();
			cout << setw(9) << left << tempsr->amount;
			cout << setw(2) << left << "|";
			cout << setw(11) << left << tempsr->topnumber << "|" << endl;
			flag_sr = true;
		}
	}
	if (flag_sr == false)
	{
		cout << "Can't find the book you need" << endl;
	}
}

void write_file(booklist blist)
{
	ofstream wrf;
	wrf.open("ipbook.txt", ios::out);
	for (booknode *tempwr = blist.phead; tempwr != NULL; tempwr = tempwr->pnext)
	{
		if (tempwr->pnext != NULL)
		{
			wrf << tempwr->data.bookid << ";" << tempwr->data.bookname << ";" << tempwr->data.authorname << ";"
				<< tempwr->amount << tempwr->data.type << ";" << tempwr->topnumber << endl;
		}
		else
		{
			wrf << tempwr->data.bookid << ";" << tempwr->data.bookname << ";" << tempwr->data.authorname << ";"
				<< tempwr->amount << tempwr->data.type << ";" << tempwr->topnumber;
		}
	}
	wrf.close();
}