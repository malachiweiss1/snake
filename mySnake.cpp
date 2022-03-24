#include <iostream>
#include <Windows.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
using namespace std;
void gotoxy(int x, int y)
{
    static HANDLE h = NULL;
    if (!h)
        h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD c = { x, y };
    SetConsoleCursorPosition(h, c);
}
void printBaby(int x = 8, int y = 8)
{
    gotoxy(x, y);
    cout << (char)2;
    for (int i = 1; i <= 3; i++)
    {
        gotoxy(x, y - i);
        cout << (char)-70;
    }
    gotoxy(x, y - 4);
    cout << (char)-37;
}
class Node
{
public:
    int x;
    int y;
    char c;
    Node* next;
    void init()
    {
        next = new Node();
    }
    void print()
    {
        gotoxy(x, y);
        cout << c;
    }
    ~Node()
    {
        gotoxy(x, y);
        cout << " ";
    }
};
class Snake
{
public:
    Node* head;
    Node* tail;
    int direction;//1 up,2 down, 3 left, 4 right
    int xPresent = 15;
    int yPresent = 4;
    int score = 0;
    char c = '*';
    void printLimit(int size = 30)
    {
        int x = size * 2;
        int y = size / 2;
        char up = -70;
        char side = -51;
        putchar(-55);
        for (int i = 2; i < x; i++)
            cout << side;
        putchar(-69);
        cout << endl;
        for (int i = 2; i < y; i++)
        {
            for (int j = 0; j < x; j++)
            {
                if (j == 0 || j == x - 1)
                    cout << up;
                else
                    cout << " ";
            }
            cout << endl;
        }
        putchar(-56);
        for (int i = 2; i < x; i++)
            cout << side;
        putchar(-68);
        cout << endl;
        gotoxy(4, 16);
        cout << "your score is : 0";

    }
    Snake()
    {
        Node* temp = new Node();
        head = new Node();
        tail = new Node();
        printLimit();
        head->c = 2;
        head->x = 8;
        head->y = 8;
        head->init();
        temp = head->next;
        for (int i = 1; i < 7; i++)
        {
            temp->x = head->x;
            temp->y = head->y - i;
            temp->c = -70;
            temp->init();
            temp = temp->next;
        }
        temp->init();
        tail = temp;
        tail->x = head->x;
        tail->y = head->y - 7;
        tail->c = -37;
        direction = 2;//down
        gotoxy(xPresent, yPresent);
        cout << c;//present
    }
    void printAllsnake()
    {
        Node* temp = head;
        while (temp->next != NULL)
        {
            temp->print();
            temp = temp->next;
        }
    }
    void pushTail()
    {
        Node* temp = new Node();
        temp = head;
        while (temp->next != tail)
            temp = temp->next;
        temp->c = -37;
        delete tail;
        tail = temp;
        tail->print();
    }
    void initNewHead(int pniya)
    {
        Node* newHead = new Node();
        newHead->init();
        newHead->c = 2;
        newHead->next = head;
        if (direction == 1 && pniya == 0 || pniya == 72)
        {
            newHead->x = head->x;
            newHead->y = head->y - 1;
            if (newHead->y == 0)
                newHead->y = 13;
        }
        else if (direction == 2 && pniya == 0 || pniya == 80)
        {
            newHead->x = head->x;
            newHead->y = head->y + 1;
            if (newHead->y == 14)
                newHead->y = 1;
        }
        else if (direction == 3 && pniya == 0 || pniya == 75)
        {
            newHead->x = head->x - 1;
            newHead->y = head->y;
            if (newHead->x == 0)
                newHead->x = 58;
        }
        else if (direction == 4 && pniya == 0 || pniya == 77)
        {
            newHead->x = head->x + 1;
            newHead->y = head->y;
            if (newHead->x == 58)
                newHead->x = 1;
        }
        head = newHead;
        head->print();
    }
    void drawSecond(int pniya)
    {
        char temp = 0;
        if (direction < 3 && pniya == 0)
            temp = -70;
        else if (direction > 2 && pniya == 0)
            temp = -51;
        else if (direction == 2 && pniya == 77 || direction == 3 && pniya == 72)
            temp = -56;
        else if (direction == 2 && pniya == 75 || direction == 4 && pniya == 72)
            temp = -68;
        else if (direction == 1 && pniya == 77 || direction == 3 && pniya == 80)
            temp = -55;
        else if (direction == 1 && pniya == 75 || direction == 4 && pniya == 80)
            temp = -69;
        head->next->c = temp;
        head->next->print();
    }
    void changeDirection(int pniya)
    {
        if (pniya == 72)
            direction = 1;
        else if (pniya == 80)
            direction = 2;
        else if (pniya == 75)
            direction = 3;
        else if (pniya == 77)
            direction = 4;
    }
    bool checkEat()
    {
        if (head->x == xPresent && head->y == yPresent)
        {
            bool flag = false;
            score++;
            gotoxy(20, 16);
            cout << score;
            while (!flag)
            {
                Node* temp = new Node();
                temp = head;
                flag = true;
                yPresent = (rand() % 13) + 1;
                xPresent = (rand() % 50) + 1;
                while (temp->c != -37)
                {
                    if (temp->x == xPresent && temp->y == yPresent)
                    {
                        flag = false;
                        break;
                    }
                    temp = temp->next;
                }
            }
            gotoxy(xPresent, yPresent);
            cout << c;
            return true;
        }
        return false;
    }
    bool move(int pniya = 0)
    {
        bool flag = checkEat();
        initNewHead(pniya);
        if (over())
        {
            gotoxy(head->x, head->y);
            cout << "#";
            return false;
        }
        drawSecond(pniya);
        if (!flag)
            pushTail();
        if (pniya != 0)
            changeDirection(pniya);
        return true;
    }
    bool stam(int get)
    {
        return (direction < 3 && get % 2 == 0 || direction >2 && get % 2 == 1);
    }
    bool over()
    {
        int cx = head->x;
        int cy = head->y;
        Node* temp = new Node();
        temp = head;
        do
        {
            temp = temp->next;
            if (temp->x == cx && temp->y == cy)
                return true;
        } while (temp != tail);
        return false;
    }
};
int main()
{
    Snake s;
    s.printAllsnake();
    char get = 0;
    while (get != 120)
    {
        while (!_kbhit())
        {
            if (!s.move())
            {
                gotoxy(0, 18);
                return 0;
            }
            gotoxy(0, 0);
            Sleep(50);
        }
        get = _getch();
        if (get == -32)
        {
            get = _getch();
            if (!s.stam((int)get))
                s.move((int)get);
        }
    }
}