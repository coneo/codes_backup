#include "test.h"


#define M(continerT, ...) continerT<__VA_ARGS__>


#define PASS(a,b) a,b
#define P(a, b) ((a) + (b))


#define TYPE(a)                  a
#define DECL(t)                  int t
#define DECL_U(l)                DECL(l)
#define DECL_B(l, m)             DECL(l), DECL(m)

#define U(l)    DECL_U(l), TYPE(l)
#define B(l, m) DECL_B(l, m), TYPE_B(l, m)

#define FUN(...)\
{\
    __VA_ARGS__;\
}\

int main()
{
    FUN(DECL(1));
    FUN(DECL_B(2, 4));   
}
