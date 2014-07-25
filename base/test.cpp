
#include "../test/test.h"
#include "serialize_stream.h"
#include "scope_guard.h"
#include "event.h"
#include "exception.h"

using namespace std;

#define GCC_VERSION (__GNUC__ * 10000 \
                     + __GNUC_MINOR__ * 100 \
                     + __GNUC_PATCHLEVEL__)
using namespace water;
struct S
{
    S(int i_ = 0)
    {
        memset(this, 0, sizeof(*this));
        i = i_;
    }

    void set(int a)
    {
        i = a;
    }

    void print() const
    {
        cout << i << endl;
    }
    int i;
};

std::ostream& operator << (std::ostream& os, const S& s)
{
    os << s.i;
    return os;
}

SerializeStream<buffer::RawBuffer>& operator << (SerializeStream<buffer::RawBuffer>& ss, const S& s)
{
    ss << s.i;
    return ss;
}

SerializeStream<buffer::RawBuffer>& operator >> (SerializeStream<buffer::RawBuffer>& ss, S& s)
{
    ss >> s.i;
    return ss;
}



void eventTest1(S& s, int value)
{
    Event<void(S::*)(int)> event1;
    Event<void (S::*)(int)>::Handler handler1 = std::mem_fun(&S::set);

    Event<void(S::*)()> event2;
    Event<void (S::*)()>::Handler handler2 = std::mem_fun(&S::print);
    event1.reg(handler1);
    event2.reg(handler2);
    event1(&s, value);
    event2(&s);
}

void eventTest2()
{
    S s;
    Event<void(S&, int)> event;
    event.reg(eventTest1);
    event(s, 5);
}

void serializeTest()
{
    SerializeStream<buffer::RawBuffer> ss;
    uint8_t buffer[1024] = {0};

    ss.assignOutBuffer(buffer, 1024);

    typedef std::string  TA;
    TA a1{"1234"};
    ss << a1;
    cout << (a1);
    cout << endl;

    TA a2;
    ss >> a2;
    cout << (a2);
    cout << endl;

    typedef std::vector<int> TB;
    TB b1{1, 2, 3, 4, 5};
    ss << b1;
    cout << (b1);
    cout << endl;

    TB b2;
    ss >> b2;
    cout << (b2);
    cout << endl;


    typedef std::vector<std::set<std::string>> TC;
    TC c1{{"a", "b"}, {"c", "d"}};
    ss << c1;
    cout << (c1);
    cout << endl;

    TC c2;
    ss >> c2;
    cout << (c2);
    cout << endl;


    typedef std::vector<std::vector<int>> TD;
    TD d1{{1, 2}, {3, 4}};
    ss << d1;
    cout << (d1);
    cout << endl;

    TD d2;
    ss >> d2;
    cout << (d2);
    cout << endl;

    typedef std::vector<std::pair<std::set<int>, std::string>> TE;
    TE e1
    {
        {{1, 2}, "12"}, 
        {{3, 4}, "34"}
    };
    ss << e1;
    cout << (e1);
    cout << endl;

    TE e2;
    ss >> e2;
    cout << (e2);
    cout << endl;

    typedef std::list<std::list<int>> TF;
    TF f1{{1,2,3}, {4,5,6}};
    ss << f1;
    cout << (f1);
    cout << endl;

    TF f2;
    ss >> f2;
    cout << (f2);
    cout << endl;


    typedef std::vector<S> TG;
    TG g1{1};
    ss << g1;
    cout << g1;
    cout << endl;

    TG g2;
    ss >> g2;
    cout << (g2);
    cout << endl;
}

#include "circular_queue.h"
void circularQueue()
{
    CircularQueue<int> q;

    for(int i = 0; i < 19; ++i)
    {
        if(!q.push(i))
            break;
    }

    if(q.full())
        cout << "isFull" << endl;

    q.traverse([](const int& item)->bool { cout << item << " "; return true; });
    cout << endl;

    for(int i = 0; !q.empty(); ++i)
    {
        cout << q.get() << " ";
        q.pop();
    }

    cout << endl;
    cout << q.size() << endl;

    return;
}

#include "reflector.h"
namespace reflect
{
    struct A
    {
        A()
        {
        }
        virtual std::string name()
        {
            return "A";
        }

        int code = 0;
    };

    struct B1 : A
    {
        B1(std::string c)
        : code(c)
        {
        }
        virtual std::string name()
        {
            return code + "B1";
        }
        std::string code;
    };

    struct B2 : A
    {
        virtual std::string name()
        {
            return "B2";
        }
    };

    void test()
    {
        Reflector<std::string, A> reflector0;
        reflector0.reg<A>("A");

        Reflector<std::string, A, std::string> reflector1;
        
        reflector1.reg<B1>("B1");
        reflector0.reg<B2>("B2");

        A* l[3] = 
        {
            reflector0.produce("A") ,
            reflector0.produce("B2"),
            reflector1.produce("B1", "haha"),
        };

        for(A* a : l)
            cout << a << ":" << a->name() << endl;
    }
}

int main()
{
    reflect::test();
 //   eventTest2();
 //   serializeTest();
 //   circularQueue();

 //   SYS_EXCEPTION(ExceptionBase, "test");
    return 0;
}
