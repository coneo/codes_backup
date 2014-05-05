#include "test.h"
using namespace std;


class A
{
public:
    explicit A(int i)
    :_i(i)
    {
    }

    ~A()
    {
        cout << "destructor, " << _i << "," << flag << endl;
    }

    A(const A& o)
    {
        _i = o._i;
        cout << "copy" << o._i << endl;
    }

    A(A&& o)
    {
        _i = o._i;
        o.flag = 1;
        cout << "move" << o._i << endl;
    }

    A(const A&& o)
    {
        _i = o._i;
        o.flag = 2;
        cout << "move const" << o._i << endl;
    }

    A& operator=(const A& o)
    {
        _i = o._i;
        cout << "copy assign" << o._i << endl;
    }

    A& operator=(A&& o)
    {
        _i = o._i;
        o.flag = 1;
        cout << "move assign" << o._i << endl;
    }

    int _i;
    mutable int flag = 0;
};


int main()
{
  //  A a1(1);

    /*
    A a2(2);

    A a3(a1);
    A a4(std::move(A(4)));
    A a5(A(5));
    */

    /*
    cout << "----------------"  << endl;

    std::vector<A> v;
    v.push_back(A(11));
*/

    std::vector<A> v = {111};
    cout << "----------------"  << endl;
    

    std::vector<std::vector<A>> vv;
    vv.push_back(std::move(v));

    cout << v.size() << endl;
    cout << "----------------"  << endl;
    return 0;
}



