#include "../test/test.h"
#include "serialize_stream.h"

using namespace std;

#define GCC_VERSION (__GNUC__ * 10000 \
                     + __GNUC_MINOR__ * 100 \
                     + __GNUC_PATCHLEVEL__)


int main()
{
    SerializeStream<RawMemoryBuffer> ss;
    uint8_t buffer[1024] = {0};

    ss.assign(buffer, 1024);

    typedef std::string  TA;
    TA a1{"1234"};
    ss << a1;
    print(a1);
    cout << endl;

    TA a2;
    ss >> a2;
    print(a2);
    cout << endl;

    typedef std::vector<int> TB;
    TB b1{1, 2, 3, 4, 5};
    ss << b1;
    print(b1);
    cout << endl;

    TB b2;
    ss >> b2;
    print(b2);
    cout << endl;



    typedef std::vector<std::set<std::string>> TC;
    TC c1{{"a", "b"}, {"c", "d"}};
    ss << c1;
    print(c1);
    cout << endl;

    TC c2;
    ss >> c2;
    print(c2);
    cout << endl;


    typedef std::vector<std::vector<int>> TD;
    TD d1{{1, 2}, {3, 4}};
    ss << d1;
    print(d1);
    cout << endl;

    TD d2;
    ss >> d2;
    print(d2);
    cout << endl;

    typedef std::vector<std::pair<std::set<int>, std::string>> TE;
    TE e1
    {
        {{1, 2}, "12"}, 
        {{3, 4}, "34"}
    };
    ss << e1;
    print(e1);
    cout << endl;

    TE e2;
    ss >> e2;
    print(e2);
    cout << endl;

    typedef std::list<std::list<int>> TF;
    TF f1{{1,2,3}, {4,5,6}};
    ss << f1;
    print(f1);
    cout << endl;
    
    TF f2;
    ss >> f2;
    print(f2);
    cout << endl;

    return 0;
}

