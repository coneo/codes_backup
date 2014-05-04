#include "exception.h"
#include "../test/test.h"

DEFINE_EXCEPTION(MyExp, ExceptionBase)
void fun()
{
    MyExp ex("haha", __FILE__, __PRETTY_FUNCTION__, __LINE__);
    throw ex;
}



int main()
{
    try
    {
        fun();
    }
    catch(ExceptionBase& ex)
    {
        std::cout << ex.what() << std::endl;
    }
    catch(...)
    {
        std::cout << "unknow" << std::endl;
    }
    return 0;
}
