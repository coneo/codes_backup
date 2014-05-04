#include "event.h"
#include <iostream>
#include <chrono>
#include <ctime>
#include <map>
#include <set>
#include <forward_list>
#include <list>
#include <vector>
using namespace std;


void fun1(int i)
{
    cout << i << endl;
}

void fun2(int i)
{
    cout << i << i << endl;
}

void fun3(int i)
{
    cout << i << i << i << endl;
}

void fun4(int i)
{
    cout << i << i << i << i << endl;
}

int main()
{
    
    typedef Event<void(int)> E;
    

    E e;
    E::RegID regID1 = e.reg(fun1);
    E::RegID regID2 = e.reg(fun2);
    E::RegID regID3 = e.reg(fun3);
    E::RegID regID4 = e.reg(fun4);
    
    cout << regID1 << endl;
    cout << regID2 << endl;
    cout << regID3 << endl;
    cout << regID4 << endl;

    e(1);

    e.unreg(regID2);

    e(2);
    return 0;
}

