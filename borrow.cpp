#include "book.cpp"
#include "student.cpp"
#include <ctime>
struct date
{
    int day;
    int month;
    int year;
};

struct borrownode
{
    string brlibid;
    string brstudentname;
    string brbookid;
    date borrowday;
    int numberborrow;
    borrownode *pnext;
    borrownode *pback;
};
struct borrowlist
{
    borrownode *phead;
    borrownode *ptail;
};

date inputday(int day, int month, int year)
{
    date x;
    x.day = day;
    x.month = month;
    x.year = year;
    return x;
}
bool checkinputday(date d)
{
    int maxday;
    if (d.year < 0 || d.month < 0 || d.month > 12 || d.day < 0 || d.day > 31)
    {
        cout << "the day is incorret" << endl;
        return false;
    }
    else
    {
        switch (d.month)
        {
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            maxday = 31;
            break;
        case 2:
            if ((d.year % 4 == 0 && d.year % 100 != 0) || (d.year % 400 == 0))
                maxday = 29;
            else
                maxday = 28;
            break;
        case 4:
        case 6:
        case 9:
        case 11:
            maxday = 30;
            break;
        }
        if (d.day > maxday)
        {
            cout << "the day is incorret" << endl;
            return false;
        }
    }
    return true;
}
date nowday()
{
    int day, month, year;
    time_t now = time(0);
    tm *ltm = localtime(&now);
    date da;
    da.day = ltm->tm_mday;
    da.month = 1 + ltm->tm_mon;
    da.year = 1900 + ltm->tm_year;
    return da;
}

void printday(date da)
{
    cout << da.day << "/" << da.month << "/" << da.year;
}

date dayup(date da)
{
    if (da.month < 12)
    {
        da.month = da.month + 1;
    }
    else
    {
        da.month = 1;
        da.year = da.year + 1;
    }
    return da;
}

bool checkday(date da1, date da2)
{
    if (da1.year > da2.year)
        return true;
    if (da1.year < da2.year)
        return false;
    else if (da1.month < da2.month)
        return false;
    else if (da1.day < da2.day)
        return false;
    return true;
};
void createborrowlist(borrowlist &mlist)
{
    mlist.phead = mlist.ptail = NULL;
}

borrownode *borrowinputdata(student stu, book bo, date da, int brnumber)
{
    borrownode *p = new borrownode();
    p->pback = p->pnext = NULL;
    p->brlibid = stu.libid;
    p->brstudentname = stu.studentname;
    p->brbookid = bo.bookid;
    p->borrowday = da;
    p->numberborrow = brnumber;
    return p;
}
bool checklibid(studentlist slist, string s, bool &ok)
{
    ok = true;
    for (studentnode *k = slist.phead; k != NULL; k = k->pnext)
    {
        if (s == k->data.libid)
            if (k->funish == true)
            {
                cout << "This student in punish list can't borrow book " << endl;
                ok = false;
                return false;
            }
            else
                return true;
    }
    cout << "can't not find this library ID " << endl;
    return false;
}
bool checkbookid(booklist blist, string s)
{
    for (booknode *k = blist.phead; k != NULL; k = k->pnext)
        if (k->data.bookid == s)
            return true;
    cout << "can't find this book id " << endl;
    return false;
}
int returnlevel(studentlist slist, string id)
{
    for (studentnode *k = slist.phead; k != NULL; k = k->pnext)
    {
        if (k->data.libid == id)
            return k->data.level;
    }
}
void borrowinputtail(borrowlist &mlist, borrownode *p)
{
    if (mlist.phead == NULL)
    {
        mlist.phead = mlist.ptail = p;
    }
    else
    {
        mlist.ptail->pnext = p;
        p->pback = mlist.ptail;
        mlist.ptail = p;
    }
}
int countborrow(borrowlist mlist, string id)
{
    int dem = 1;
    borrowlist tam;
    tam.phead = tam.ptail = NULL;
    for (borrownode *k = mlist.phead; k != NULL; k = k->pnext)
    {
        if (k->brlibid == id)
        {
            borrowinputtail(tam, k);
        }
    }
    if (tam.phead == NULL)
    {
        return 0;
    }
    else
    {
        if (tam.phead == tam.ptail)
        {
            return 1;
        }
        else
        {
            borrownode *k = tam.phead;
            while (k != NULL)
            {
                for (borrownode *j = k->pnext; j != NULL; j = j->pnext)
                {
                    if (j->brbookid == k->brbookid)
                    {
                        break;
                    }
                    else if (j->pnext == NULL)
                    {
                        dem++;
                    }
                }
                k = k->pnext;
            }
        }
    }
    return dem;
}
void borrowprint(borrowlist mlist)
{
    cout << endl;
    cout << "                +++++++++++++++++++++++++++++++++ LIST OF STUDENT BORROW BOOK ++++++++++++++++++++++++++++++++ " << endl
         << endl;
    cout << "                ______________________________________________________________________________________________" << endl
         << endl;
    cout << setw(3) << left << "|";
    cout << setw(11) << left << "Library ID";
    cout << setw(5) << left << "|";
    cout << setw(15) << left << "Student name";
    cout << setw(2) << left << "|";
    cout << setw(7) << left << "Book ID";
    cout << setw(6) << left << "|";
    cout << setw(10) << left << "Number";
    cout << setw(3) << left << "|";
    cout << setw(8) << left << "Borrow day"
         << "|" << endl;
    for (borrownode *k = mlist.phead; k != NULL; k = k->pnext)
    {
        cout << setw(3) << left << "|";
        cout << setw(11) << left << k->brlibid;
        cout << setw(5) << left << "|";
        cout << setw(15) << left << k->brstudentname;
        cout << setw(2) << left << "|";
        cout << setw(7) << left << k->brbookid;
        cout << setw(8) << left << "|";
        cout << setw(8) << left << k->numberborrow;
        cout << setw(3) << left << "|";
        printday(k->borrowday);
        cout << setw(3) << left << "|" << endl;
    }
}

void borrowbook(borrowlist &mlist, studentlist slist, booklist &blist, string libid, string bookid, date da, int brnumber)
{
    student tam;
    book tam1;
    for (studentnode *k = slist.phead; k != NULL; k = k->pnext)
    {
        if (k->data.libid == libid)
        {
            if (k->funish == true)
            {
                cout << "This student in punish list can't borrow book" << endl;
                return;
            }
            tam = k->data;
            break;
        }
        else if (k->pnext == NULL)
        {
            cout << "Can't not find library card" << endl;
            return;
        }
    }
    for (booknode *k = blist.phead; k != NULL; k = k->pnext)
    {
        if (k->data.bookid == bookid)
        {
            tam1 = k->data;
            k->topnumber++;
            if (k->amount < brnumber)
            {
                brnumber = k->amount;
                k->amount = 0;
            }
            else
                k->amount = k->amount - brnumber;
            break;
        }
        else if (k->pnext == NULL)
        {
            cout << "Can't not find this book in library" << endl;
            return;
        }
    }
    borrownode *p = borrowinputdata(tam, tam1, da, brnumber);
    borrowinputtail(mlist, p);
}

void borrowdeletehead(borrowlist &mlist)
{
    mlist.phead = mlist.phead->pnext;
    mlist.phead->pback = NULL;
}

void borrowdeletetail(borrowlist &mlist)
{
    mlist.ptail = mlist.ptail->pback;
    mlist.ptail->pnext = NULL;
}
int countid(borrowlist mlist, string id)
{
    int dem = 0;
    for (borrownode *k = mlist.phead; k != NULL; k = k->pnext)
    {
        if (k->brlibid == id)
            dem++;
    }
    return dem;
}
void returnbook(borrowlist &mlist, booklist &blist, studentlist &slist, string libraryid)
{
    int count = countid(mlist, libraryid);
    for (borrownode *k = mlist.phead; k != NULL; k = k->pnext)
    {
        if (k->brlibid == libraryid)
        {
            char ok;
            cout << "Library ID: " << k->brlibid << " | ";
            cout << "Name:" << k->brstudentname << endl;
            cout << "Book ID: " << k->brbookid << endl
                 << "Number borrow: " << k->numberborrow << endl;
            cout << "Borrow day: ";
            printday(k->borrowday);
            cout << endl;
            cout << "Want to pay back book" << endl;
            cout << "Input y mean 'Yes' or n mean 'No' have return book: ";
            cin >> ok;
            if (ok == 'y')
            {
                for (booknode *j = blist.phead; j != NULL; j = j->pnext)
                {
                    if (j->data.bookid == k->brbookid)
                    {
                        j->amount = j->amount + k->numberborrow;
                        break;
                    }
                }
                for (studentnode *x = slist.phead; x != NULL; x = x->pnext)
                {
                    if (x->data.libid == k->brlibid && count == 0)
                    {
                        x->funish = false;
                        break;
                    }
                }
                if (mlist.ptail == mlist.phead)
                {
                    mlist.phead = mlist.ptail = NULL;
                    return;
                }
                else if (k->brlibid == mlist.phead->brlibid)
                {
                    borrowdeletehead(mlist);
                    count--;
                    for (studentnode *x = slist.phead; x != NULL; x = x->pnext)
                    {
                        if (x->data.libid == k->brlibid && count == 0)
                        {
                            x->funish = false;
                            break;
                        }
                    }
                }
                else if (k->brlibid == mlist.ptail->brlibid)
                {
                    borrowdeletetail(mlist);
                    k = k->pback;
                    count--;
                    for (studentnode *x = slist.phead; x != NULL; x = x->pnext)
                    {
                        if (x->data.libid == k->brlibid && count == 0)
                        {
                            x->funish = false;
                            break;
                        }
                    }
                }
                else
                {
                    k->pnext->pback = k->pback;
                    k->pback->pnext = k->pnext;
                    k = k->pback;
                    count--;
                    for (studentnode *x = slist.phead; x != NULL; x = x->pnext)
                    {
                        if (x->data.libid == k->brlibid && count == 0)
                        {
                            x->funish = false;
                            break;
                        }
                    }
                }
            }
            else
            {
                cout << "Have not return book" << endl;
            }
        }
    }
}

void punishstudent(borrowlist &mlist, studentlist &slist)
{
    date now = nowday();
    student tam1;
    for (borrownode *k = mlist.phead; k != NULL; k = k->pnext)
    {
        date tam = dayup(k->borrowday);
        if (checkday(tam, now) == false)
        {
            for (studentnode *j = slist.phead; j != NULL; j = j->pnext)
            {
                if (j->data.libid == k->brlibid)
                {
                    j->funish = true;
                    j->numberborrow -= 2;
                    if (j->numberborrow < 0)
                        j->numberborrow = 0;
                }
            }
        }
    }
}

void punishprint(studentlist slist)
{
    for (studentnode *k = slist.phead; k != NULL; k = k->pnext)
    {
        if (k->funish == true)
            k->data.studentout();
    }
}

void borrowfromfile(borrowlist &mlist, booklist &blist, studentlist &slist)
{
    ifstream borrowfile;
    borrowfile.open("borrow.txt", ios::in);
    string brid, brname, brboid;
    date x;
    char tam, tam1;
    string tam3, tam4;
    int num;
    while (!borrowfile.eof())
    {
        getline(borrowfile, brid, ';');
        if (brid == "")
            return;
        getline(borrowfile, brname, ';');
        getline(borrowfile, brboid);
        borrowfile >> x.day;
        borrowfile >> tam;
        borrowfile >> x.month;
        borrowfile >> tam1;
        borrowfile >> x.year;
        getline(borrowfile, tam4);
        borrowfile >> num;
        getline(borrowfile, tam3);
        borrowbook(mlist, slist, blist, brid, brboid, x, num);
    }
    borrowfile.close();
}

void borrowbackfile(borrowlist mlist, booklist &blist)
{
    ofstream borrowfile;
    borrowfile.open("borrow.txt", ios::out);
    for (borrownode *k = mlist.phead; k != NULL; k = k->pnext)
    {
        for (booknode *j = blist.phead; j != NULL; j = j->pnext)
        {
            if (j->data.bookid == k->brbookid)
            {
                j->amount += k->numberborrow;
            }
        }
        if (k->pnext != NULL)
        {
            borrowfile << k->brlibid << ";";
            borrowfile << k->brstudentname << ";";
            borrowfile << k->brbookid << endl;
            borrowfile << k->borrowday.day << "/" << k->borrowday.month << "/" << k->borrowday.year << endl;
            borrowfile << k->numberborrow << endl;
        }
        else
        {
            borrowfile << k->brlibid << ";";
            borrowfile << k->brstudentname << ";";
            borrowfile << k->brbookid << endl;
            borrowfile << k->borrowday.day << "/" << k->borrowday.month << "/" << k->borrowday.year << endl;
            borrowfile << k->numberborrow;
        }
    }
    borrowfile.close();
}
void levelup(studentlist &slist)
{
    for (studentnode *k = slist.phead; k != NULL; k = k->pnext)
    {
        if (k->numberborrow < 10 and k->numberborrow >= 0)
        {
            k->data.level = 1;
        }
        else if (k->numberborrow >= 10 && k->numberborrow < 20)
        {
            k->data.level = 2;
        }
        else if (k->numberborrow >= 20 && k->numberborrow < 36)
        {
            k->data.level = 3;
        }
        else if (k->numberborrow >= 36 && k->numberborrow < 60)
        {
            k->data.level = 4;
        }
        else if (k->numberborrow > 59)
        {
            k->data.level = 5;
        }
    }
}
void borrowprintbyid(borrowlist mlist, string id)
{
    for (borrownode *k = mlist.phead; k != NULL; k = k->pnext)
    {
        if (k->brlibid == id)
        {
            cout << setw(3) << left << "|";
            cout << setw(11) << left << k->brlibid;
            cout << setw(5) << left << "|";
            cout << setw(15) << left << k->brstudentname;
            cout << setw(2) << left << "|";
            cout << setw(7) << left << k->brbookid;
            cout << setw(8) << left << "|";
            cout << setw(8) << left << k->numberborrow;
            cout << setw(3) << left << "|";
            printday(k->borrowday);
            cout << setw(3) << left << "|" << endl;
        }
    }
}