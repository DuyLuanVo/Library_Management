#include "student.h"
#include <ctype.h>
#include <iomanip>
struct studentnode
{
    student data;
    bool funish;
    int numberborrow;
    studentnode *pnext;
    studentnode *pback;
};
struct studentlist
{
    studentnode *phead;
    studentnode *ptail;
};
student::student(){};
student::student(string libid, string studentid, string studentname, int level)
{
    this->libid = libid;
    this->studentid = studentid;
    this->studentname = studentname;
    this->level = level;
}
void student::studentout()
{
    cout << setw(2) << left << "|";
    cout << setw(2) << left << this->libid;
    cout << setw(3) << left << "|";
    cout << setw(1) << left << this->studentid;
    cout << setw(5) << left << "|";
    cout << setw(20) << left << this->studentname;
    cout << setw(3) << left << "|";
    cout << setw(4) << left << this->level;
    cout << setw(6) << left << "|";
    // cout << endl;
}
void createstudentlist(studentlist &slist)
{
    slist.phead = slist.ptail = NULL;
}
studentnode *inputstudentdata(student stu1, int number)
{
    studentnode *p = new studentnode();
    p->pback = p->pnext = NULL;
    p->data.libid = stu1.libid;
    p->data.studentid = stu1.studentid;
    p->data.studentname = stu1.studentname;
    p->data.level = stu1.level;
    p->numberborrow = number;
    p->funish = false;
    return p;
}
void studentinputtail(studentlist &slist, studentnode *p)
{
    if (slist.phead == NULL)
    {
        slist.phead = slist.ptail = p;
    }
    else
    {
        slist.ptail->pnext = p;
        p->pback = slist.ptail;
        slist.ptail = p;
    }
}

void studentprint(studentlist slist)
{
    if (slist.phead == NULL)
        cout << "No students." << endl;
    else
    {

        cout << endl;
        cout << "+++++++++++++++++++++++++++ LIST OF STUDENT +++++++++++++++++++++++++++ " << endl
             << endl;
        cout << "_______________________________________________________________________ " << endl
             << endl;
        cout << setw(2) << left << "|";
        cout << setw(10) << left << "LIBRARY ID";
        cout << setw(3) << left << "|";
        cout << setw(10) << left << "STUDENT ID";
        cout << setw(5) << left << "|";
        cout << setw(20) << left << "STUDENT NAME";
        cout << setw(2) << left << "|";
        cout << setw(2) << left << "level";
        cout << setw(3) << left << "|";
        cout << setw(2) << left << "Number borrow";
        cout << setw(3) << left << "|";
        cout << endl;
        studentnode *temp = slist.phead;
        while (temp != NULL)
        {
            temp->data.studentout();
            cout << setw(7) << left << temp->numberborrow; // k->numberborrow;
            cout << setw(9) << left << "|" << endl;
            temp = temp->pnext;
        }

        /*for (studentnode *k = slist.phead; k != NULL; k = k->pnext)
        {
            k->data.studentout();
            cout << setw(7) << left << k->numberborrow;
            cout << setw(9) << left << "|" << endl;
        }*/
    }
}
void studentwork(studentlist &slist)
{
    string lbid, stuid, stuname;
    ifstream studentfile;
    int level, number;
    char temp;
    string tam;
    studentfile.open("student.txt", ios::in);
    while (!studentfile.eof())
    {
        getline(studentfile, lbid, ',');
        if (lbid == "")
            return;
        getline(studentfile, stuid, ',');
        getline(studentfile, stuname, ',');
        studentfile >> level;
        studentfile >> temp;
        studentfile >> number;
        getline(studentfile, tam);
        student stu(lbid, stuid, stuname, level);
        studentnode *s = inputstudentdata(stu, number);
        studentinputtail(slist, s);
    }
    studentfile.close();
}
bool checkid(studentlist slist, string id)
{
    for (studentnode *k = slist.phead; k != NULL; k = k->pnext)
    {
        if (k->data.libid == id)
            return false;
    }
    return true;
}
void searchstudent(studentlist &slist, string searchname)
{
    for (studentnode *k = slist.phead; k != NULL; k = k->pnext)
    {
        if (k->data.studentname == searchname)
        {
            k->data.studentout();
            cout << endl;
        }
    }
}
void studentreturnfile(studentlist slist)
{
    ofstream studentfile;
    studentfile.open("student.txt", ios::out);
    for (studentnode *k = slist.phead; k != NULL; k = k->pnext)
    {
        if (k->pnext != NULL)
        {
            studentfile << k->data.libid << "," << k->data.studentid << "," << k->data.studentname << "," << k->data.level << "," << k->numberborrow << endl;
        }
        else
        {
            studentfile << k->data.libid << "," << k->data.studentid << "," << k->data.studentname << "," << k->data.level << "," << k->numberborrow;
        }
    }
    studentfile.close();
}
bool checksp(string s)
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
void addstudent(studentlist &slist)
{
    string libraryid, stuid, stuname;
    fflush(stdin);
    bool ok = false, ok1 = false;
    cout << "Input library ID: ";
    getline(cin, libraryid);
    do
    {
        if (libraryid.length() != 10 || libraryid[0] != 'T' || libraryid[1] != 'V')
        {
            cout << "Library ID is 10 characters and the first and second character is 'T' and 'V', Re-enter Library ID: ";
            getline(cin, libraryid);
        }
        else if (checksp(libraryid) == false)
        {
            while (checksp(libraryid) == false)
            {
                cout << "Library ID no space, Re-enter Library ID: ";
                getline(cin, libraryid);
            }
        }
        while (checkid(slist, libraryid) == false)
        {
            cout << "Library ID already exists. Re-enter Library ID: ";
            getline(cin, libraryid);
        }
    } while (libraryid.length() != 10 || libraryid[0] != 'T' || libraryid[1] != 'V' || checksp(libraryid) == false);

    if (checkid(slist, libraryid) == true)
    {
        cout << "Input student ID: ";
        getline(cin, stuid);
        do
        {
            if (stuid.length() != 10)
            {
                cout << "Student ID beyond the permissible limit, Re-enter Student ID: ";
                getline(cin, stuid);
            }
            else if (checksp(stuid) == false)
            {
                while (checksp(stuid) == false)
                {
                    cout << "Student ID no space, Re-enter Library ID: ";
                    getline(cin, stuid);
                }
            }
        } while (stuid.length() != 10 || checksp(stuid) == false);

        for (studentnode *k = slist.phead; k != NULL; k = k->pnext)
        {
            while (k->data.studentid == stuid)
            {
                if (k->data.studentid == stuid)
                {
                    cout << "Student ID already exists. Re-enter Student ID: ";
                    getline(cin, stuid);
                }
            }
        }
        cout << "Input student name: ";
        getline(cin, stuname);
    }
    student stu(libraryid, stuid, stuname, 1);
    studentnode *p = inputstudentdata(stu, 0);
    studentinputtail(slist, p);
}

void studentdeletehead(studentlist &slist)
{
    slist.phead = slist.phead->pnext;
    slist.phead->pback = NULL;
}
void studentdeletetail(studentlist &slist)
{
    slist.ptail = slist.ptail->pback;
    slist.ptail->pnext = NULL;
}
bool deletestudent(studentlist &slist, string tam)
{
    do
    {
        if (tam.length() != 10 || tam[0] != 'T' || tam[1] != 'V')
        {
            cout << "Library ID is 10 characters and the first and second character is 'T' and 'V', Re-enter Library ID: ";
            getline(cin, tam);
        }
        else if (checksp(tam) == false)
        {
            while (checksp(tam) == false)
            {
                cout << "Library ID no space, Re-enter Library ID: ";
                getline(cin, tam);
            }
        }
    } while (tam.length() != 10 || tam[0] != 'T' || tam[1] != 'V' || checksp(tam) == false);
    for (studentnode *k = slist.phead; k != NULL; k = k->pnext)
    {
        if (k->data.libid == tam)
        {
            if (slist.ptail == slist.phead)
            {
                slist.phead = slist.ptail = NULL;
                return true;
            }
            else if (k->data.libid == slist.phead->data.libid)
            {
                studentdeletehead(slist);
                return true;
            }
            else if (k->data.libid == slist.ptail->data.libid)
            {
                studentdeletetail(slist);
                return true;
            }
            else
            {
                k->pnext->pback = k->pback;
                k->pback->pnext = k->pnext;
                return true;
            }
        }
    }
    return false;
}
bool editstudentdata(studentlist &slist, string edit)
{
    int ch;
    string tam;
    do
    {
        if (edit.length() != 10 || edit[0] != 'T' || edit[1] != 'V')
        {
            cout << "Library ID is 10 characters and the first and second character is 'T' and 'V', Re-enter Library ID: ";
            getline(cin, edit);
        }
        else if (checksp(edit) == false)
        {
            while (checksp(edit) == false)
            {
                cout << "Library ID no space, Re-enter Library ID: ";
                getline(cin, edit);
            }
        }
    } while (edit.length() != 10 || edit[0] != 'T' || edit[1] != 'V' || checksp(edit) == false);
    for (studentnode *k = slist.phead; k != NULL; k = k->pnext)
    {
        if (k->data.libid == edit)
        {
            while (69)
            {
                fflush(stdin);
                system("cls");
                cout << "1. Change name" << endl;
                cout << "2. Change student ID" << endl;
                cout << "0. Exit" << endl;
                cin >> ch;
                if (ch == 1)
                {
                    fflush(stdin);
                    cout << "Input new name: ";
                    getline(cin, tam);
                    k->data.studentname = tam;
                }
                else if (ch == 2)
                {
                    fflush(stdin);
                    cout << "Input new student ID: ";
                    getline(cin, tam);
                    do
                    {
                        if (tam.length() != 10)
                        {
                            cout << "Student ID beyond the permissible limit, Re-enter Student ID: ";
                            getline(cin, tam);
                        }
                        else if (checksp(tam) == false)
                        {
                            while (checksp(tam) == false)
                            {
                                cout << "Student ID no space, Re-enter Library ID: ";
                                getline(cin, tam);
                            }
                        }
                    } while (tam.length() != 10 || checksp(tam) == false);
                    for (studentnode *k = slist.phead; k != NULL; k = k->pnext)
                    {
                        while (k->data.studentid == tam)
                        {
                            if (k->data.studentid == tam)
                            {
                                cout << "Student ID already exists. Re-enter Student ID: ";
                                getline(cin, tam);
                            }
                        }
                    }
                    k->data.studentid = tam;
                }
                else
                {
                    break;
                }
            }
            return true;
        }
    }
    return false;
}
void borrowup(studentlist &slist, string id)
{
    for (studentnode *k = slist.phead; k != NULL; k = k->pnext)
    {
        if (k->data.libid == id)
        {
            k->numberborrow++;
            return;
        }
    }
}
studentnode *merge(studentnode *first, studentnode *second)
{
    if (!first)
        return second;

    if (!second)
        return first;

    if (first->data.libid < second->data.libid)
    {
        first->pnext = merge(first->pnext, second);
        first->pnext->pback = first;
        first->pback = NULL;
        return first;
    }
    else
    {
        second->pnext = merge(first, second->pnext);
        second->pnext->pback = second;
        second->pback = NULL;
        return second;
    }
}
studentnode *split(studentnode *phead)
{
    studentnode *fast = phead, *slow = phead;
    while (fast->pnext && fast->pnext->pnext)
    {
        fast = fast->pnext->pnext;
        slow = slow->pnext;
    }
    studentnode *temp = slow->pnext;
    slow->pnext = NULL;
    return temp;
}
studentnode *mergeSort(studentnode *phead)
{
    if (!phead || !phead->pnext)
        return phead;
    studentnode *second = split(phead);
    phead = mergeSort(phead);
    second = mergeSort(second);
    return merge(phead, second);
}
void capNhatNodeTail(studentlist &slist)
{
    studentnode *temp = slist.phead;
    while (temp->pnext != NULL)
    {
        temp = temp->pnext;
    }
    slist.ptail = temp;
}
