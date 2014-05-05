#include "test.h"
#include "../tools/serialize_stream.h"

using namespace std;


int main()
{
    SerializeStream ss;

    typedef std::string  TA;
    TA a1{"1234"};
    ss << a1;

    TA a2;
    ss >> a2;
    print(a2);

    typedef std::vector<int> TB;
    TB b1{1, 2, 3, 4, 5};
    ss << b1;
    print(b1);

    TB b2;
    ss >> b2;
    print(b2);



    typedef std::vector<std::set<std::string>> TC;
    TC c1{{"a", "b"}, {"c", "d"}};
    ss << c1;
    print(c1);

    TC c2;
    ss >> c2;
    print(c2);


    typedef std::vector<std::vector<int>> TD;
    TD d1{{1, 2}, {3, 4}};
    ss << d1;
    print(d1);

    TD d2;
    ss >> d2;
    print(d2);

    typedef std::vector<std::pair<std::set<int>, std::string>> TE;
    TE e1
    {
        {{1, 2}, "12"}, 
        {{3, 4}, "34"}
    };
    ss << e1;
    print(e1);

    TE e2;
    ss >> e2;
    print(e2);

    typedef std::list<std::list<int>> TF;
    TF f1{{1,2,3}, {4,5,6}};
    ss << f1;
    
    TF f2;
    ss >> f2;
    print(f2);
    return 0;
}

