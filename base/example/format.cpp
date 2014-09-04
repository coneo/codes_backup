#include "test.h"


#include "../format.h"
#include <sstream>

class T : public IStringAble
{
public:
    void toString(std::string* str) const override
    {   
        char buf[128];
        snprintf(buf, 128, "%s", "class_T");
        str->append(buf);
    }   
};

void format()
{
    static uint64_t num = 0;
    const char manName[] = "john";
    std::string str = format("{manName,w:10,holder:0} take {若干个} apple;", manName, 99, T());
    num += str.size();
}

void stream1()
{
    static uint64_t num = 0;
    std::stringstream ss; 
    const char manName[] = "john";
    ss << manName << " take " << 99 << " apple;";
    num += ss.str().size();
}

int main()
{
    uint32_t times = 1000000;
    run(format, times);
    run(stream1, times);
}

