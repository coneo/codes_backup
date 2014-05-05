#include "test.h"

int main()
{
    std::forward_list<int> fl1{1,2,3,4,5};

    std::forward_list<int> fl2;
    for(auto it = fl1.begin(); it != fl1.end(); ++it)
        fl2.insert_after(fl2.begin(), *it);

    print(fl2);
    return 0;
}
