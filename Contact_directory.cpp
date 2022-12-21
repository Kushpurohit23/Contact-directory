#include <bits/stdc++.h>
using namespace std;
typedef int ii;

class hs
{
public:
    string date, time;
    string duration;
    struct hs *nxt;
};
class ll
{
public:
    string name;
    string contact;
    struct ll *next;
    struct ll *prev;
    struct hs *hd;
    struct hs *ed;
};
ll *dr[26] = {NULL};
void dial(ll *no)
{
    time_t st, ed;
    time(&st);
    cout << "Enter e to end ";
    char a = 'f';

    while (a != 'e')
    {
        cin >> a;
    }
    time(&ed);

    struct tm *t1, *t2;
    string c, b, d;
    t1 = localtime(&st);
    int x = (t1->tm_hour * 60 + t1->tm_sec + t1->tm_min * 60);
    b += to_string(t1->tm_mday) + " " + to_string(t1->tm_mon+1) + " " + to_string(t1->tm_year + 1900);

    if (t1->tm_hour < 10)
    {
        d += '0';
        d += to_string(t1->tm_hour) + ":";
    }
    else
        d += to_string(t1->tm_hour) + ":";
    if (t1->tm_min < 10)
    {
        d += '0';
        d += to_string(t1->tm_min) + ":";
    }
    else
        d += to_string(t1->tm_min) + ":";
    if (t1->tm_sec < 10)
    {
        d += '0';
        d += to_string(t1->tm_sec);
    }
    else
        d += to_string(t1->tm_sec);

    t2 = localtime(&ed);
    x = (t2->tm_hour * 60 + t2->tm_sec + t2->tm_min * 60) - x;

    // cout << x << endl;
    for (int i = 0; i < 2; i++)
    {
        if (x / 60 < 10)
        {
            c += '0';
            c += to_string(x / 60) + ":";
            x %= 60;
        }
        else
        {
            c += to_string(x / 60) + ":";
            x %= 60;
        }
    }
    if (x < 10)
    {
        c += '0';
        c += to_string(x);
    }
    else
    {
        c += to_string(x);
    }

    hs *h = new hs();
    h->date = b;
    h->duration = c;
    h->time = d;
    if (no->hd == NULL)
    {
        no->hd = h;
        no->ed = h;

        return;
    }

    h->nxt = NULL;
    no->ed->nxt = h;
    no->ed = h;
}
ll *add(ll *ptr, ll *head)
{

    struct ll *trv;

    char c = tolower(ptr->name[0]);

    if (head == NULL)
    {
        // cout << "y";
        ptr->prev = ptr;
        ptr->next = ptr;
        head = ptr;
        return head;
    }

    trv = head;
    ii tst = 1;
    if ((ptr->name).compare(head->name) == -1)
    {
        ptr->prev = head->prev;
        ptr->next = head;
        head->prev->next = ptr;
        head->prev = ptr;
        head = ptr;
        return head;
    }
    while (trv != head || tst)
    {
        tst = 0;
        if (ptr->name.compare(trv->name) == 0 && ptr->contact.compare(trv->contact) == 0)
        {
            cout << "Contact already exist" << endl;
            return head;
        }
        if ((ptr->name).compare(trv->next->name) >= 0 && trv->next != head)
        {

            trv = trv->next;
        }
        else
            break;
    }

    // cout << trv->contact << endl;
    ptr->prev = trv;
    ptr->next = trv->next;
    trv->next->prev = ptr;
    trv->next = ptr;
    // cout << head->next->contact << endl;

    return head;
}
ll *search_byno(string s)
{

    for (int i = 0; i < 26; i++)
    {
        ll *head = dr[i];
        ii tst = 1, cnt = 0;
        if (head == NULL)
            continue;

        while (head != dr[i] || tst)
        {
            tst = 0;
            if (s.compare(head->contact) == 0)
            {
                return head;
            }
            head = head->next;
        }
    }
    return NULL;
}
void print()
{
    ii cnt = 0;
    cout<<"Name"<<"     "<<"Number"<<endl;
    for (ii i = 0; i < 26; i++)
    {
        ll *head = dr[i];
        ll *ts = head;
        if (head == NULL)
            continue;
        ii tt = 1;
        cnt++;
        while (head != ts || tt)
        {
            tt = 0;
            cout << head->name << "      ";
            cout << head->contact << endl;
            head = head->next;
        }
    }
    if (!cnt)
        cout << " Your Contact list is empty" << endl;
}
ll *search_byname(string s, ii x = 1)
{
    ll *head = NULL, *trv, *tmp;
    char c = tolower(s[0]);
    trv = dr[c - 'a'];
    if (trv == NULL)
        return NULL;

    ii tst = 1;
    ii ct = 0;
    while (trv != dr[c - 'a'] || tst)
    {
        ll *ptr = new ll();
        tst = 0;

        if (s.compare(trv->name) == 0)
        {
            ct++;
            head = trv;
            ii tp = 1;

            while ((trv != dr[c - 'a'] || tp) && s.compare(trv->name) == 0)
            {
                tp = 0;
                cout << ct << " .   " << trv->name << "   " << trv->contact << endl;
                trv = trv->next;
                ct++;
            }
            if (ct == 1)
                return head;
            if (x)
            {
                int wi = 0;
                cout << "Enter your choice : -" << endl;
                cin >> wi;
                while (wi == 0 || wi > ct-1)
                {
                    cout << "Enter valid choice : ";
                    cin >> wi;
                }
                wi--;

                while (wi--)
                {
                    head = head->next;
                }
            }

            return head;
        }
        trv = trv->next;
    }
    return NULL;
}
void remov(ll *tmp)
{
    if ((tmp->next == tmp) && (tmp->prev == tmp))
    {
        dr[tolower(tmp->name[0]) - 'a'] = NULL;
    }
    else
    {
        tmp->prev->next = tmp->next;
        tmp->next->prev = tmp->prev;
    }
    ll *tt = tmp;
    while (tmp->hd != NULL)
    {
        hs *trv;
        trv = tmp->hd;
        tmp->hd = tmp->hd->nxt;
        free(trv);
    }
    free(tt);
}
void del()
{
    cout << "1.  For delete  by name\n"
         << "2.  For delete by contact\n";

    cout << "Enter your choice :";
    ii t = -1, cnt = 0;
    cin >> t;
    ll *tmp;
    if (t == 1)
    {
        cout << "Enter the name of contact : ";
        string pt;
        fflush(stdin);
        getline(cin, pt);
        tmp = search_byname(pt);
    }
    else if (t == 2)
    {
        cout << "Enter the contact : ";
        string pt;
        fflush(stdin);
        getline(cin, pt);
        tmp = search_byno(pt);
    }
    if (tmp != NULL)
        remov(tmp);
    else
        cout << "NO MATCH FOUND!!" << endl;
}
void edit()
{
    cout << "1.  For search by name\n"
         << "2   For search by contact\n";

    cout << "Enter your choice :";
    ii t = -1, cnt = 0;
    cin >> t;
    ll *tmp;
    if (t == 1)
    {
        cout << "Enter the name of contact : ";
        string tt;
        fflush(stdin);
        getline(cin, tt);

        tmp = search_byname(tt);
    }
    else if (t == 2)
    {
        cout << "Enter the contact number : ";
        string tt;
        fflush(stdin);
        getline(cin, tt);

        tmp = search_byno(tt);
    }
    if (tmp != NULL)
    {
        string s, s1;
        ll *a = new ll();

        cout << "Current details is\n"
             << tmp->name << "   ";
        cout << tmp->contact << endl;
        cout << "Enter updated name : ";
        fflush(stdin);
        getline(cin, s);
        s1 = tmp->contact;

        a->name = s;
        a->contact = s1;
        a->hd = tmp->hd;
        a->ed = tmp->ed;
        if (tmp->next ==tmp)
        {
            dr[tolower(tmp->name[0]) - 'a'] = NULL;
            free(tmp);
        }
        else
        {
            if(tmp == dr[tolower(tmp->name[0]) - 'a'])
            {
                dr[tolower(tmp->name[0]) - 'a'] = tmp->next;
                cout<<"hi";
            }
            tmp->prev->next = tmp->next;
            tmp->next->prev = tmp->prev;
            free(tmp);
        }

        dr[tolower(a->name[0]) - 'a'] = add(a, dr[tolower(a->name[0]) - 'a']);
    }
    else
        cout << "NO CONTACT FOUND" << endl;
}
void history(hs *hd)
{
    if (hd == NULL)
        return;
    cout << "Date"
         << "          "
         << "Time"
         << "         "
         << "Duration" << endl;

    while (hd != NULL)
    {
        cout << hd->date << "   " << hd->time << "   " << hd->duration << endl;
        hd = hd->nxt;
    }
}

void call()
{
    system("cls");
    cout << "1.  For search by name\n"
         << "2.  For search by contact\n";

    cout << "Enter your choice :";
    ii t = -1, cnt = 0;
    cin >> t;
    ll *tmp;
    if (t == 1)
    {
        cout << "Enter the name of contact : ";
        string tt;
        fflush(stdin);
        getline(cin, tt);

        tmp = search_byname(tt);
    }
    else if (t == 2)
    {
        cout << "Enter the contact : ";
        string tt;
        fflush(stdin);

        getline(cin, tt);
        tmp = search_byno(tt);
    }
    if (tmp != NULL)
    {
        dial(tmp);
        history(tmp->hd);
    }
    else
        cout << "NO MATCH FOUND!!" << endl;
}
int main()
{
    ii n = 0;

    while (1)
    {

        cout << "*****WELCOME TO PHONE DIRECTORY*****" << endl;

        cout << "      1.   To add contact\n      2.   To print contact list\n      3.   To make a call\n      4.   To delete contact\n      5.   To edit\n      6.   To search contact by name\n      7.   To search contact by number\n      8.   History\n      9.   EXIT\n" << endl;
        cout << "Please enter your choice :";
        cin >> n;

        if (n == 1)
        {
            ll *ptr = new ll();
            string s, s1;
            cout << "Enter name : ";

            fflush(stdin);
            getline(cin, s);

            cout << "Enter number : ";
            fflush(stdin);
            getline(cin, s1);
            ll *x = search_byno(s1);

            if (x == NULL)
            {
                ptr->name = s;
                ptr->contact = s1;
                ptr->hd = NULL;
                ptr->ed = NULL;

                dr[tolower(s[0]) - 'a'] = add(ptr, dr[tolower(s[0]) - 'a']);
                system("cls");
                continue;
            }
            system("cls");
            cout << "Contact already exist" << endl;
            cout << "Name:-" << x->name << " "
                 << "Number:-" << x->contact << endl;
            continue;
        }
        else if (n == 2)
        {
            system("cls");
            print();
        }
        else if (n == 3)
        {
            call();
        }
        else if (n == 4)
        {
            del();
            system("cls");
        }
        else if (n == 5)
        {
            edit();
            system("cls");
        }
        else if (n == 6)
        {
            system("cls");
            string s;
            cout << "Enter name : ";
            fflush(stdin);
            getline(cin, s);
            if (search_byname(s, 0) == NULL)
                cout << "NO MATCH FOUND!!" << endl;
        }
        else if (n == 7)
        {
            system("cls");
            string s;
            cout << "Enter Contact number : ";
            fflush(stdin);
            getline(cin, s);
            ll *tp = search_byno(s);
            if (tp == NULL)
                cout << "NO MATCH FOUND!!" << endl;
            else
            {
                cout << "Name:  " << tp->name << " "<<endl
                     << "Contact:  " << tp->contact << endl;
            }
        }
        else if(n==8){
            string s;
            cout<<"Enter your name"<<endl;
            fflush(stdin);
            getline(cin,s);
            ll *tt=search_byname(s);
            if(tt!=NULL)
            history(tt->hd);

        }

        else if (n == 9)
            break;
        else
        {
            cout << "Enter valid choice" << endl;
            system("cls");
        }
    }
}