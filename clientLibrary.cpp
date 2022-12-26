#include "borrow.cpp"
#include "admin.cpp"
#include <iostream>
#include <conio.h>
#include <windows.h>

void login();

int main()
{
	login();
	return 0;
}

void login()
{
	borrowlist mlist;
	createborrowlist(mlist);
	booklist blist;
	createbooklist(blist);
	studentlist slist;
	createstudentlist(slist);
	fstream filepass;
	filepass.open("password.txt", ios::in);
	string s, s1;
	getline(filepass, s);
	admin ad(s);
	int count = 0;
	cout << "You're signed in with an account that: ";
	cout << "\033[31m";
	cout << "ADMIN" << endl;
	cout << "\033[0m";
	while (s1 != s)
	{
		if (count == 3)
			break;
		cout << "Input password: ";
		cout << "\033[31m";
		cin >> s1;
		cout << "\033[0m";
		if (s1 == s)
		{
			cout << "\033[32m";
			cout << "Sign in success" << endl;
			cout << "\033[0m";
			system("pause");
			studentwork(slist);
			bookwork(blist);
			borrowfromfile(mlist, blist, slist);
			punishstudent(mlist, slist);
			levelup(slist);
			makehash(blist);
			int i, menu1, menu2, menu3, menu4;
			char mn;
			// display loading
			cout << "\033[32m";
			cout << "\n\n\n\t\t\t\t    LOADING...\n\n";
			char a = 177, b = 219;
			cout << "\t\t\t\t";
			for (int i = 0; i <= 16; i++)
				cout << a;
			cout << "\r";
			cout << "\t\t\t\t";
			for (int i = 0; i <= 15; i++)
			{
				cout << b;
				for (int j = 0; j <= 1e8; j++)
					;
			}
			cout << "\033[0m";
			while (69)
			{
				system("cls");
				cout << "\033[32m";
				cout << "++++++++++++++++++++++ LIBRARY MANAGEMENT ++++++++++++++++++++++" << endl;
				cout << "+++++++++++++++++++++++++++++ MENU +++++++++++++++++++++++++++++" << endl;
				cout << "\033[0m";
				cout << "                _______________________________" << endl;
				cout << endl;
				cout << "------------------- 1. Account Management ----------------------" << endl;
				cout << "------------------- 2. Book Management -------------------------" << endl;
				cout << "------------------- 3. Manage library cards --------------------" << endl;
				cout << "------------------- 4. Management borrow books and fines -------" << endl;
				cout << "------------------- 0. Exit and save ---------------------------" << endl;
				cout << "                _______________________________" << endl;
				cout << endl;
				cout << "\033[31m";
				do
				{
					cout << "++++++++++++++++++++ Your choice is: ";
				} while (((scanf("%d%c", &i, &mn) != 2 || mn != '\n') && clean_stdin()));
				cout << "\033[0m";

				if (i == 1)
				{
					while (10)
					{
						system("cls");
						cout << "++++++++++++++++++++++ Account Management ++++++++++++++++++++++" << endl;
						cout << "               __________________________________" << endl
							 << endl;
						cout << "-------------------- 1. Change password ------------------------" << endl;
						cout << "-------------------- 2. See password ---------------------------" << endl;
						cout << "-------------------- 0. Exit to main menu ----------------------" << endl;
						cout << "               __________________________________" << endl
							 << endl;
						cout << "\033[31m";
						do
						{
							cout << "++++++++++++++++++++ Your choice is: ";
						} while (((scanf("%d%c", &menu1, &mn) != 2 || mn != '\n') && clean_stdin()));
						cout << "\033[0m";
						if (menu1 == 1)
						{
							ad.changepass();
							ofstream f3;
							f3.open("password.txt", ios::out);
							f3 << ad.getpass();
							f3.close();
							system("pause");
						}
						else if (menu1 == 2)
						{
							cout << ad.getpass() << endl;
							system("pause");
						}
						else if (menu1 == 0)
						{
							break;
						}
					}
				}

				if (i == 2)
				{
					while (10)
					{
						system("cls");
						cout << "++++++++++++++++++++++++ Book Management +++++++++++++++++++++" << endl;
						cout << "               __________________________________" << endl
							 << endl;
						cout << "--------------------- 1. Add book ----------------------------" << endl;
						cout << "--------------------- 2. Edit book ---------------------------" << endl;
						cout << "--------------------- 3. Delete book ---------------------" << endl;
						cout << "--------------------- 4. Search book -------------------------" << endl;
						cout << "--------------------- 5. Show all book -----------------------" << endl;
						cout << "--------------------- 6. Show 5 book have max borrow ---------" << endl;
						cout << "--------------------- 0. Exit to main menu -------------------" << endl;
						cout << "               __________________________________" << endl
							 << endl;
						cout << "\033[31m";
						do
						{
							cout << "++++++++++++++++++++ Your choice is: ";
						} while (((scanf("%d%c", &menu2, &mn) != 2 || mn != '\n') && clean_stdin()));
						cout << "\033[0m";
						if (menu2 == 1)
						{
							add_book(blist);
							system("pause");
						}
						else if (menu2 == 2)
						{
							edit_book(blist);
							system("pause");
						}
						else if (menu2 == 3)
						{
							delete_book(blist);
							system("pause");
						}
						else if (menu2 == 4)
						{
							search_book(blist);
							system("pause");
						}
						else if (menu2 == 5)
						{
							bookprint(blist);
							system("pause");
						}
						else if (menu2 == 6)
						{
							printtop5book(blist);
							system("pause");
						}
						else if (menu2 == 0)
						{
							break;
						}
					}
				}

				if (i == 3)
				{
					while (10)
					{
						system("cls");
						cout << "+++++++++++++++++++++ Manage library cards ++++++++++++++++++++" << endl;
						cout << "               __________________________________" << endl
							 << endl;
						cout << "----------------- 1. Add student card -------------------------" << endl;
						cout << "----------------- 2. Delete student card ----------------------" << endl;
						cout << "----------------- 3. Edit student card ------------------------" << endl;
						cout << "----------------- 4. Find cards by first and last name student " << endl;
						cout << "----------------- 5. Sort student by Library ID ---------------" << endl;
						cout << "----------------- 6. Show all library cards -------------------" << endl;
						cout << "----------------- 0. Exit to main menu ------------------------" << endl;
						cout << "               __________________________________" << endl
							 << endl;
						cout << "\033[31m";
						do
						{
							cout << "++++++++++++++++++++ Your choice is: ";
						} while (((scanf("%d%c", &menu3, &mn) != 2 || mn != '\n') && clean_stdin()));
						cout << "\033[0m";
						if (menu3 == 1)
						{
							addstudent(slist);
							system("pause");
						}
						else if (menu3 == 2)
						{
							fflush(stdin);
							string tam;
							cout << "Input library ID: ";
							getline(cin, tam);
							while (!deletestudent(slist, tam))
							{
								cout << "Library ID is not exists. Re-Enter Library ID: ";
								getline(cin, tam);
							}
							system("pause");
						}
						else if (menu3 == 3)
						{
							string edit;
							fflush(stdin);
							cout << "Input libray id student you want to edit: ";
							getline(cin, edit);
							while (!editstudentdata(slist, edit))
							{
								cout << "Library ID is not exists. Re-Enter Library ID: ";
								getline(cin, edit);
							}
						}
						else if (menu3 == 4)
						{
							string searchname;
							fflush(stdin);
							cout << "Input student name: ";
							getline(cin, searchname);
							searchstudent(slist, searchname);
							system("pause");
						}
						else if (menu3 == 5)
						{
							slist.phead = mergeSort(slist.phead);
							capNhatNodeTail(slist);
							cout << "Sort success " << endl;
							system("pause");
						}
						else if (menu3 == 6)
						{
							studentprint(slist);
							system("pause");
						}
						else if (menu3 == 0)
						{
							break;
						}
					}
				}

				if (i == 4)
				{
					while (10)
					{
						system("cls");
						cout << "++++++++++++++ Management borrow books and fines ++++++++++++++" << endl;
						cout << "               __________________________________" << endl
							 << endl;
						cout << "-------------------- 1. Borrow book ---------------------------" << endl;
						cout << "-------------------- 2. Return books --------------------------" << endl;
						cout << "-------------------- 3. Show list on borrow -------------------" << endl;
						cout << "-------------------- 4. List of penalized students ------------" << endl;
						cout << "-------------------- 5. Search by library ID ------------------" << endl;
						cout << "-------------------- 0. Exit to main menu ---------------------" << endl;
						cout << "               __________________________________" << endl
							 << endl;
						cout << "\033[31m";
						do
						{
							cout << "++++++++++++++++++++ Your choice is: ";
						} while (((scanf("%d%c", &menu4, &mn) != 2 || mn != '\n') && clean_stdin()));
						cout << "\033[0m";
						if (menu4 == 1)
						{
							bool ok, ok1 = true;
							string idthuvien, idsach;
							int soluong;
							date da;
							fflush(stdin);
							do
							{
								cout << "Input library ID: ";
								getline(cin, idthuvien);
							} while (checklibid(slist, idthuvien, ok) == false && ok == true);
							if (countborrow(mlist, idthuvien) > returnlevel(slist, idthuvien) + 2)
							{
								ok1 = false;
								cout << "Level is not enough to borrow more" << endl;
							}
							if (ok == true && ok1 == true)
							{
								int numnum;
								do
								{
									int num2 = returnlevel(slist, idthuvien) + 2;
									int num3 = countborrow(mlist, idthuvien);
									cout << "This student can borrow more " << num2 - num3 << endl;
									cout << "input number of book borrow ";
									cin >> numnum;
								} while ((numnum + countborrow(mlist, idthuvien)) > (returnlevel(slist, idthuvien) + 2));
								fflush(stdin);
								for (int m = 0; m < numnum; m++)
								{
									do
									{
										cout << "Input book ID: ";
										getline(cin, idsach);
									} while (checkbookid(blist, idsach) == false);
									fflush(stdin);
									do
									{
										do
										{
											cout << "Input day: ";
										} while (((scanf("%d%c", &da.day, &mn) != 2 || mn != '\n') && clean_stdin()));
										do
										{
											cout << "Input month: ";
										} while (((scanf("%d%c", &da.month, &mn) != 2 || mn != '\n') && clean_stdin()));
										do
										{
											cout << "Input year: ";
										} while (((scanf("%d%c", &da.year, &mn) != 2 || mn != '\n') && clean_stdin()));
									} while (checkinputday(da) == false);
									do
									{
										cout << "Input number borrow: ";
									} while (((scanf("%d%c", &soluong, &mn) != 2 || mn != '\n') && clean_stdin()));
									borrowbook(mlist, slist, blist, idthuvien, idsach, da, soluong);
									punishstudent(mlist, slist);
									borrowup(slist, idthuvien);
								}
							}
							system("pause");
						}
						else if (menu4 == 2)
						{
							string returnbookid;
							fflush(stdin);
							cout << "Input student libraryid: ";
							getline(cin, returnbookid);
							returnbook(mlist, blist, slist, returnbookid);
							system("pause");
						}
						else if (menu4 == 3)
						{
							borrowprint(mlist);
							system("pause");
						}
						else if (menu4 == 4)
						{
							punishprint(slist);
							system("pause");
						}
						else if (menu4 == 5)
						{
							string id5;
							fflush(stdin);
							cout << "Input library id: ";
							getline(cin, id5);
							borrowprintbyid(mlist, id5);
							system("pause");
						}
						else if (menu4 == 0)
						{
							break;
						}
					}
					levelup(slist);
				}

				else if (i == 0)
				{
					cout << "\033[32m";
					cout << "The information was saved successfully. Goodbye" << endl;
					cout << "\033[0m";
					break;
				}
			}

			borrowbackfile(mlist, blist);
			write_file(blist);
			studentreturnfile(slist);
		}
		else
		{
			cout << "\033[33m";
			cout << "Wrong password you can try again " << 2 - count << " time" << endl;
			cout << "\033[0m";
			count++;
		}
	}
	filepass.close();
}