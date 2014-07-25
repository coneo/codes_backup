#include "test.h"

#include <iostream>

using std::cout;
using std::endl;


int main()
{
    std::vector<std::list<int>> v = {{1, 2, 3, 4, 5}, {10, 11, 12, }};
    cout << v << endl;
    return 0;
}
