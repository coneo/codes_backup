/*
 * Author: LiZhaojia - dantezhu@vip.qq.com
 *
 * Last modified: 2014-07-24 17:29 +0800
 *
 * Description: 通用反射机制，可以通过name来索引不同的类型，并在运行期动态的通过name来构建对应类型的对象
 */

#ifndef WATER_BASE_REFLECTOR_H
#define WATER_BASE_REFLECTOR_H


namespace water{


//反射构建器，args   
template <typename Name, typename BaseType, typename... ConstructorArgs>
class Reflector
{
private:
    //抽象构建器， 实际构建器的基类
    class AbstructCreater
    {
    public:
        virtual ~AbstructCreater(){};
        virtual BaseType* create(ConstructorArgs... args) const = 0;
    };

    //实际对象构建器
    template <typename RealType>
    class Creater : public AbstructCreater
    {
        BaseType* create(ConstructorArgs... args) const
        {
            return new(std::nothrow) RealType(std::forward<ConstructorArgs>(args)...); 
        }

        uint32_t sizeofObj() const
        {
            return sizeof(RealType);
        }
    };

public:
    //注册一种类型
    template <typename RealType>
    bool reg(const Name& name)
    {
        if(createrMap.find(name) != createrMap.end())//name 已被注册过， 不能重复注册
            return false;

        AbstructCreater* creater = new Creater<RealType>();
        if(creater == nullptr)
            return false;

        return createrMap.insert(std::make_pair(name, creater)).second;
    }

    //取消一种类型的注册
    void unreg(const Name& name)
    {
        createrMap.erase(name);
    }

    //创建一个指定类型的对象
    BaseType* produce(const Name& name, ConstructorArgs... args) const
    {
        typename std::map<Name, AbstructCreater*>::const_iterator it = createrMap.find(name);
        if(it == createrMap.end() || nullptr == it->second)
            return nullptr;

        return it->second->create(std::forward<ConstructorArgs>(args)...);
    }

    //得到指定类型的sizeof
    uint32_t sizeofType(const Name& name) const
    {
        typename std::map<Name, AbstructCreater*>::const_iterator it = createrMap.find(name);
        if(it == createrMap.end() || nullptr == it->second)
            return 0;

        return it->second->sizeofObj();
    }

private:
    std::map<Name, AbstructCreater*> createrMap;
};

}

#endif



#ifdef WATER_DEBUG
namespace test
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

    struct B0 : A
    {
        virtual std::string name()
        {
            return "[B0]";
        }
    };

    struct B1 : A
    {
        B1(std::string c)
        : code(c)
        {
        }
        virtual std::string name()
        {
            return code + "[B1]";
        }
        std::string code;
    };

    struct B2 : A
    {
        B2(std::string code1_, std::string code2_)
        : code1(code1_), code2(code2_)
        {
        }
        virtual std::string name()
        {
            return code1 + code2 + "[B2]";
        }
        std::string code1;
        std::string code2;
    };

    void reflector()
    {
        Reflector<std::string, A> reflector0;
        reflector0.reg<B0>("B0");

        Reflector<std::string, A, std::string> reflector1;
        reflector1.reg<B1>("B1");

        Reflector<std::string, A, std::string, std::string> reflector2;
        reflector2.reg<B2>("B2");


        A* l[3] = 
        {
            reflector0.produce("B0") ,
            reflector1.produce("B1", "haha"),
            reflector2.produce("B2", "b2", "2b"),
        };

        for(A* a : l)
            cout << a << ":" << a->name() << endl;
    
    }
}
#endif

