#include "test.h"

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
    cout << i + 10 << endl;
}

void fun3(int i)
{
    cout << i + 100 << endl;
}

int main()
{
    
/*
    std::map<int, int> m1;
    std::map<int, int> m2;
    {
        volatile int i = 0;
        std::chrono::time_point<std::chrono::system_clock> start, end;

        start = std::chrono::system_clock::now();
        for(int i = 0; i < 1000000; i++)
            m1.insert({i, i});
        end = std::chrono::system_clock::now();

        cout << "m1:" << i << endl;

        std::chrono::duration<double> elapsed_seconds = end-start;
        std::time_t end_time = std::chrono::system_clock::to_time_t(end);

        std::cout << "finished computation at " << std::ctime(&end_time)
        << "elapsed time: " << elapsed_seconds.count() << "s\n";
    }
    {
        volatile int i = 0;
        std::chrono::time_point<std::chrono::system_clock> start, end;

        start = std::chrono::system_clock::now();
        for(int i = 0; i < 1000000; i++)
            m2.insert(m2.end(), {i, i});
        end = std::chrono::system_clock::now();

        cout << "m2:" << i << endl;

        std::chrono::duration<double> elapsed_seconds = end-start;
        std::time_t end_time = std::chrono::system_clock::to_time_t(end);

        std::cout << "finished computation at " << std::ctime(&end_time)
        << "elapsed time: " << elapsed_seconds.count() << "s\n";
    }
    */
    std::map<int, int> m;
    std::unordered_map<int, int> u;
    std::set<int> s;
    std::list<int> l;
    std::forward_list<int> f;
    std::vector<int> v(1000000);

    for(int i = 0; i < 1000000; i++)
    {
        m.insert({i, i});
        u.insert({i, i});
        s.insert({i, i});
        l.push_back(i);
        f.push_front(i);
        v.push_back(i);
    }

    {
        volatile int i = 0;
        std::chrono::time_point<std::chrono::system_clock> start, end;

        start = std::chrono::system_clock::now();
        for(auto it = m.begin(); it != m.end(); ++it)
            i = it->first;
        end = std::chrono::system_clock::now();

        cout << "m:" << i << endl;

        std::chrono::duration<double> elapsed_seconds = end-start;
        std::time_t end_time = std::chrono::system_clock::to_time_t(end);

        std::cout << "finished computation at " << std::ctime(&end_time)
        << "elapsed time: " << elapsed_seconds.count() << "s\n";
    }
    {
        volatile int i = 0;
        std::chrono::time_point<std::chrono::system_clock> start, end;

        start = std::chrono::system_clock::now();
        for(auto it = u.begin(); it != u.end(); ++it)
            i = it->first;
        end = std::chrono::system_clock::now();

        cout << "u:" << i << endl;

        std::chrono::duration<double> elapsed_seconds = end-start;
        std::time_t end_time = std::chrono::system_clock::to_time_t(end);

        std::cout << "finished computation at " << std::ctime(&end_time)
        << "elapsed time: " << elapsed_seconds.count() << "s\n";
    }
    {
        volatile int i = 0;
        std::chrono::time_point<std::chrono::system_clock> start, end;

        start = std::chrono::system_clock::now();
        for(auto it = s.begin(); it != s.end(); ++it)
            i = *it;
        end = std::chrono::system_clock::now();
        
        cout << "s:" << i << endl;

        std::chrono::duration<double> elapsed_seconds = end-start;
        std::time_t end_time = std::chrono::system_clock::to_time_t(end);

        std::cout << "finished computation at " << std::ctime(&end_time)
        << "elapsed time: " << elapsed_seconds.count() << "s\n";
    }
    {
        volatile int i = 0;
        std::chrono::time_point<std::chrono::system_clock> start, end;

        start = std::chrono::system_clock::now();
        for(auto it = l.begin(); it != l.end(); ++it)
            i = *it;
        end = std::chrono::system_clock::now();
        
        cout << "l:" << i << endl;

        std::chrono::duration<double> elapsed_seconds = end-start;
        std::time_t end_time = std::chrono::system_clock::to_time_t(end);

        std::cout << "finished computation at " << std::ctime(&end_time)
        << "elapsed time: " << elapsed_seconds.count() << "s\n";
    }
    {
        volatile int i = 0;
        std::chrono::time_point<std::chrono::system_clock> start, end;

        start = std::chrono::system_clock::now();
        for(auto it = f.begin(); it != f.end(); ++it)
            i = *it;
        end = std::chrono::system_clock::now();
        
        cout << "f:" << i << endl;

        std::chrono::duration<double> elapsed_seconds = end-start;
        std::time_t end_time = std::chrono::system_clock::to_time_t(end);

        std::cout << "finished computation at " << std::ctime(&end_time)
        << "elapsed time: " << elapsed_seconds.count() << "s\n";
    }
    {
        volatile int i = 0;
        std::chrono::time_point<std::chrono::system_clock> start, end;

        start = std::chrono::system_clock::now();
        for(auto it = v.begin(); it != v.end(); ++it)
            i = *it;
        end = std::chrono::system_clock::now();
        
        cout << "v:" << i << endl;

        std::chrono::duration<double> elapsed_seconds = end-start;
        std::time_t end_time = std::chrono::system_clock::to_time_t(end);

        std::cout << "finished computation at " << std::ctime(&end_time)
        << "elapsed time: " << elapsed_seconds.count() << "s\n";
    }
    return 0;
}

